#!/usr/bin/env python3
"""Local G1 symbol browser and concurrent-safe rename proposal server."""

from __future__ import annotations

import argparse
import fcntl
import gzip
import json
import mimetypes
import os
import re
import tempfile
import threading
import time
from datetime import datetime, timezone
from http import HTTPStatus
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
from urllib.parse import parse_qs, unquote, urlparse


ROOT = Path(__file__).resolve().parents[2]
STATIC = Path(__file__).resolve().parent / "static"
PROPOSAL_DIR = ROOT / "recon" / "symbol_browser"
PROPOSALS = PROPOSAL_DIR / "user_renames.json"
PROPOSAL_LOCK = PROPOSAL_DIR / ".user_renames.lock"
COORDINATION = ROOT / "recon" / "SESSION_COORDINATION.md"
IDENTIFIER = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
ADDRESS_TOKEN = re.compile(r"^(?:0x)?([0-9a-fA-F]{4,8})$")


def canonical_address(value: int | str) -> str:
    if isinstance(value, str):
        value = int(value, 16) if value.lower().startswith("0x") else int(value)
    return f"0x{value:08x}"


def read_json_retry(path: Path, *, compressed: bool = False) -> dict:
    error = None
    for _ in range(8):
        try:
            opener = gzip.open if compressed else open
            with opener(path, "rt") as stream:
                return json.load(stream)
        except (OSError, EOFError, json.JSONDecodeError) as exc:
            error = exc
            time.sleep(0.035)
    raise RuntimeError(f"could not read concurrently updated {path}: {error}")


def atomic_json_write(path: Path, payload: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix=f".{path.name}.", dir=path.parent)
    try:
        with os.fdopen(fd, "w") as stream:
            json.dump(payload, stream, indent=2, sort_keys=True)
            stream.write("\n")
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary, path)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)


class RepositoryIndex:
    CATALOGS = {
        "app": {
            "names": ROOT / "recon/catalogs/function_names_app.json",
            "functions": ROOT / "recon/catalogs/app_funcs.json.gz",
            "refs": ROOT / "recon/catalogs/refgraph_app.json.gz",
            "addresses": ROOT / "recon/catalogs/address_names_app.json",
            "source": ROOT / "recon/app/src",
        },
        "net": {
            "names": ROOT / "recon/catalogs/function_names_net.json",
            "functions": ROOT / "recon/catalogs/net_funcs.json.gz",
            "refs": ROOT / "recon/catalogs/refgraph_net.json.gz",
            "addresses": ROOT / "recon/catalogs/address_names_net.json",
            "source": ROOT / "recon/net/src",
        },
    }

    def __init__(self) -> None:
        self.lock = threading.RLock()
        self.signature: tuple = ()
        self.data: dict = {}
        self.refresh(force=True)

    def _signature(self) -> tuple:
        paths = [PROPOSALS, COORDINATION]
        for paths_by_kind in self.CATALOGS.values():
            paths.extend(paths_by_kind.values())
        return tuple((str(path), path.stat().st_mtime_ns if path.exists() else 0) for path in paths)

    @staticmethod
    def _proposal_map() -> dict[str, dict]:
        if not PROPOSALS.exists():
            return {}
        payload = read_json_retry(PROPOSALS)
        return {f"{item['core']}:{item['address'].lower()}": item for item in payload.get("proposals", [])}

    @staticmethod
    def _source_inventory(directory: Path) -> dict[str, Path]:
        return {path.stem: path for path in directory.glob("*.c")}

    def refresh(self, *, force: bool = False) -> None:
        signature = self._signature()
        if not force and signature == self.signature:
            return
        with self.lock:
            signature = self._signature()
            if not force and signature == self.signature:
                return
            proposals = self._proposal_map()
            cores = {}
            for core, paths in self.CATALOGS.items():
                names = read_json_retry(paths["names"])
                functions_payload = read_json_retry(paths["functions"], compressed=True)
                refs_payload = read_json_retry(paths["refs"], compressed=True)
                address_names = read_json_retry(paths["addresses"])
                functions = {canonical_address(item["entry"]): item for item in functions_payload["functions"]}
                refs = {canonical_address(key): value for key, value in refs_payload["functions"].items()}
                source_inventory = self._source_inventory(paths["source"])
                if core == "app":
                    readable_inventory = self._source_inventory(ROOT / "recon/named")
                else:
                    readable_inventory = {}
                records = {}
                by_name = {}
                for address, identity in names["by_address"].items():
                    address = canonical_address(address)
                    proposal = proposals.get(f"{core}:{address}")
                    display_name = proposal["name"] if proposal else identity["display_name"]
                    raw_name = identity["raw_name"]
                    function = functions.get(address, {})
                    ref = refs.get(address, {})
                    source_path = (
                        readable_inventory.get(identity["display_name"])
                        or source_inventory.get(identity["display_name"])
                        or source_inventory.get(identity["name"])
                        or source_inventory.get(raw_name)
                    )
                    record = {
                        "core": core,
                        "address": address,
                        "raw_name": raw_name,
                        "canonical_name": identity["display_name"],
                        "display_name": display_name,
                        "human": not identity["display_name"].startswith("FUN_") or bool(proposal),
                        "proposed": bool(proposal),
                        "proposal": proposal,
                        "name_source": identity.get("source"),
                        "aliases": identity.get("aliases", []),
                        "size": ref.get("size", function.get("size")),
                        "signature": function.get("signature"),
                        "calling_convention": function.get("calling_convention"),
                        "is_thunk": bool(function.get("is_thunk")),
                        "has_source": source_path is not None,
                        "source_path": source_path,
                        "calls": ref.get("calls", []),
                        "callers": ref.get("callers", []),
                        "data_refs": ref.get("data_refs", []),
                        "decompiled": function.get("decompiled", ""),
                    }
                    records[address] = record
                    for name in {display_name, identity["display_name"], identity["name"], raw_name, *identity.get("aliases", [])}:
                        if name:
                            by_name.setdefault(name.lower(), address)
                cores[core] = {
                    "records": records,
                    "by_name": by_name,
                    "address_names": address_names,
                    "sorted": sorted(records, key=lambda value: int(value, 16)),
                }
            self.data = {"cores": cores, "proposals": proposals}
            self.signature = signature

    def _core(self, core: str) -> dict:
        self.refresh()
        if core not in self.data["cores"]:
            raise KeyError(f"unknown core: {core}")
        return self.data["cores"][core]

    def resolve(self, core: str, token: str) -> tuple[str | None, int]:
        data = self._core(core)
        token = unquote(token).strip()
        address = data["by_name"].get(token.lower())
        if address:
            return address, 0
        global_address = data["address_names"].get("by_name", {}).get(token)
        if global_address:
            return canonical_address(global_address), 0
        match = ADDRESS_TOKEN.match(token)
        if not match:
            return None, 0
        value = int(match.group(1), 16)
        exact = canonical_address(value)
        if exact in data["records"]:
            return exact, 0
        # GoToRef supports interior code/literal addresses, including unnamed owners.
        candidate = None
        for address in data["sorted"]:
            start = int(address, 16)
            if start > value:
                break
            record = data["records"][address]
            size = int(record.get("size") or 0)
            if size and start <= value < start + size:
                candidate = (address, value - start)
        return candidate or (None, 0)

    @staticmethod
    def _public_record(record: dict) -> dict:
        return {key: value for key, value in record.items() if key not in {"source_path", "decompiled", "calls", "callers", "data_refs"}}

    def list_symbols(self, core: str, query: str, state: str, page: int, limit: int) -> dict:
        data = self._core(core)
        query = query.strip().lower()
        rows = []
        for address in data["sorted"]:
            record = data["records"][address]
            if not record["has_source"]:
                continue
            if state == "unnamed" and record["human"]:
                continue
            if state == "named" and not record["human"]:
                continue
            if state == "proposed" and not record["proposed"]:
                continue
            haystack = " ".join((address, record["raw_name"], record["display_name"], record["canonical_name"])).lower()
            if query and query not in haystack:
                continue
            row = self._public_record(record)
            row["caller_count"] = len(record["callers"])
            row["callee_count"] = len(record["calls"])
            row["data_ref_count"] = len(record["data_refs"])
            rows.append(row)
        total = len(rows)
        start = max(page - 1, 0) * limit
        return {"items": rows[start : start + limit], "total": total, "page": page, "limit": limit}

    def _reference(self, core: str, value: str, kind: str) -> dict:
        raw_value = value
        try:
            address = canonical_address(value)
        except (ValueError, TypeError):
            return {"kind": kind, "address": value, "display_name": value, "resolvable": False}
        owner, offset = self.resolve(core, address)
        if owner:
            record = self._core(core)["records"][owner]
            return {
                "kind": kind,
                "address": address,
                "owner_address": owner,
                "offset": offset,
                "display_name": record["display_name"],
                "raw_name": record["raw_name"],
                "resolvable": True,
            }
        named = self._core(core)["address_names"].get("by_address", {}).get(address, {})
        return {
            "kind": kind,
            "address": address,
            "display_name": named.get("name", raw_value),
            "resolvable": not str(value).startswith("0x-"),
        }

    def _read_source(self, record: dict) -> tuple[str, str, str | None]:
        source_path = record.get("source_path")
        if source_path and source_path.exists():
            return source_path.read_text(errors="replace"), "reconstructed", str(source_path.relative_to(ROOT))
        return record.get("decompiled", ""), "ghidra_decompiled", None

    def _usages(self, core: str, record: dict) -> list[dict]:
        usages = []
        needles = {record["raw_name"], record["canonical_name"], record["display_name"]}
        for caller_value in record["callers"]:
            caller_address, _ = self.resolve(core, canonical_address(caller_value))
            if not caller_address:
                continue
            caller = self._core(core)["records"][caller_address]
            source, _, path = self._read_source(caller)
            hits = []
            for number, line in enumerate(source.splitlines(), 1):
                if any(needle and needle in line for needle in needles):
                    hits.append({"line": number, "preview": line.strip()[:240]})
            usages.append(
                {
                    "address": caller_address,
                    "display_name": caller["display_name"],
                    "raw_name": caller["raw_name"],
                    "source_path": path,
                    "hits": hits[:12],
                }
            )
        return usages

    def detail(self, core: str, token: str) -> dict | None:
        address, offset = self.resolve(core, token)
        if not address:
            return None
        if address not in self._core(core)["records"]:
            return self._data_detail(core, address)
        record = self._core(core)["records"][address]
        source, source_kind, source_path = self._read_source(record)
        result = self._public_record(record)
        result.update(
            {
                "goto_offset": offset,
                "source": source,
                "source_kind": source_kind,
                "source_path": source_path,
                "calls": [self._reference(core, value, "call") for value in record["calls"]],
                "callers": [self._reference(core, value, "caller") for value in record["callers"]],
                "data_refs": [self._reference(core, value, "data") for value in record["data_refs"] if not str(value).startswith("0x-")],
                "stack_refs": [value for value in record["data_refs"] if str(value).startswith("0x-")],
                "usages": self._usages(core, record),
            }
        )
        return result

    def _data_detail(self, core: str, address: str) -> dict:
        data = self._core(core)
        named = data["address_names"].get("by_address", {}).get(address, {})
        usages = []
        numeric = int(address, 16)
        for record in data["records"].values():
            matches = []
            for value in record["data_refs"]:
                try:
                    if int(value, 16) == numeric:
                        matches.append(value)
                except (TypeError, ValueError):
                    pass
            if not matches:
                continue
            source, _, path = self._read_source(record)
            needles = {address.lower(), address[2:].lower(), named.get("name", "").lower()}
            hits = []
            for number, line in enumerate(source.splitlines(), 1):
                lowered = line.lower()
                if any(needle and needle in lowered for needle in needles):
                    hits.append({"line": number, "preview": line.strip()[:240]})
            usages.append(
                {
                    "address": record["address"],
                    "display_name": record["display_name"],
                    "raw_name": record["raw_name"],
                    "source_path": path,
                    "hits": hits[:12],
                }
            )
        return {
            "kind": "data",
            "core": core,
            "address": address,
            "raw_name": address,
            "canonical_name": named.get("name", address),
            "display_name": named.get("name", address),
            "human": bool(named.get("name")),
            "proposed": False,
            "proposal": None,
            "name_source": ", ".join(named.get("evidence", [])) or "reference graph",
            "aliases": [],
            "size": None,
            "signature": None,
            "calling_convention": None,
            "is_thunk": False,
            "has_source": False,
            "goto_offset": 0,
            "source": "",
            "source_kind": "data_reference",
            "source_path": None,
            "calls": [],
            "callers": [],
            "data_refs": [],
            "stack_refs": [],
            "usages": usages,
        }

    def meta(self) -> dict:
        self.refresh()
        cores = {}
        for core, data in self.data["cores"].items():
            records = [item for item in data["records"].values() if item["has_source"]]
            cores[core] = {
                "total": len(records),
                "named": sum(item["human"] for item in records),
                "unnamed": sum(not item["human"] for item in records),
                "proposed": sum(item["proposed"] for item in records),
                "with_source": sum(item["has_source"] for item in records),
            }
        coordination = COORDINATION.read_text(errors="replace") if COORDINATION.exists() else ""
        return {
            "cores": cores,
            "coordination_active": "**HELD" in coordination,
            "coordination_path": str(COORDINATION.relative_to(ROOT)),
            "rename_mode": "proposal_overlay",
            "proposal_path": str(PROPOSALS.relative_to(ROOT)),
        }

    def save_proposal(self, core: str, address_token: str, name: str, evidence: str) -> dict:
        address, offset = self.resolve(core, address_token)
        if not address or offset:
            raise ValueError("renames require an exact function entry address")
        name = name.strip()
        if not IDENTIFIER.match(name):
            raise ValueError("name must be a valid C identifier")
        data = self._core(core)
        collision = data["by_name"].get(name.lower())
        if collision and collision != address:
            raise ValueError(f"name already belongs to {collision}")
        record = data["records"][address]
        proposal = {
            "core": core,
            "address": address,
            "raw_name": record["raw_name"],
            "previous_name": record["canonical_name"],
            "name": name,
            "evidence": evidence.strip(),
            "status": "pending_user_proposal",
            "updated_at": datetime.now(timezone.utc).isoformat(),
        }
        PROPOSAL_DIR.mkdir(parents=True, exist_ok=True)
        with open(PROPOSAL_LOCK, "a+") as lock_file:
            fcntl.flock(lock_file, fcntl.LOCK_EX)
            payload = read_json_retry(PROPOSALS) if PROPOSALS.exists() else {"schema": 1, "proposals": []}
            proposals = [
                item for item in payload.get("proposals", [])
                if not (item.get("core") == core and item.get("address", "").lower() == address)
            ]
            proposals.append(proposal)
            payload = {
                "schema": 1,
                "purpose": "Concurrent-safe user rename overlay; merge into canonical overrides only after SESSION_COORDINATION lock is released.",
                "proposals": sorted(proposals, key=lambda item: (item["core"], item["address"])),
            }
            atomic_json_write(PROPOSALS, payload)
            fcntl.flock(lock_file, fcntl.LOCK_UN)
        self.refresh(force=True)
        return proposal


INDEX = RepositoryIndex()


class Handler(BaseHTTPRequestHandler):
    server_version = "G1SymbolBrowser/1.0"

    def log_message(self, format: str, *args) -> None:
        print(f"[{self.log_date_time_string()}] {format % args}")

    def _json(self, payload: dict, status: int = 200) -> None:
        body = json.dumps(payload, separators=(",", ":")).encode()
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Cache-Control", "no-store")
        self.send_header("X-Content-Type-Options", "nosniff")
        self.end_headers()
        self.wfile.write(body)

    def _error(self, message: str, status: int = 400) -> None:
        self._json({"error": message}, status)

    def do_GET(self) -> None:
        parsed = urlparse(self.path)
        query = parse_qs(parsed.query)
        try:
            if parsed.path == "/api/meta":
                return self._json(INDEX.meta())
            if parsed.path == "/api/symbols":
                core = query.get("core", ["app"])[0]
                state = query.get("state", ["all"])[0]
                search = query.get("q", [""])[0]
                page = max(1, int(query.get("page", ["1"])[0]))
                limit = min(100, max(10, int(query.get("limit", ["60"])[0])))
                return self._json(INDEX.list_symbols(core, search, state, page, limit))
            if parsed.path.startswith("/api/symbol/"):
                parts = parsed.path.split("/", 4)
                if len(parts) != 5:
                    return self._error("expected /api/symbol/<core>/<name-or-address>", 404)
                detail = INDEX.detail(parts[3], parts[4])
                return self._json(detail) if detail else self._error("reference not found", 404)
            return self._static(parsed.path)
        except KeyError as exc:
            return self._error(str(exc), 404)
        except (ValueError, RuntimeError) as exc:
            return self._error(str(exc), 400)

    def do_POST(self) -> None:
        parsed = urlparse(self.path)
        if parsed.path != "/api/rename":
            return self._error("not found", 404)
        try:
            length = int(self.headers.get("Content-Length", "0"))
            if length > 32_768:
                return self._error("request too large", 413)
            payload = json.loads(self.rfile.read(length))
            proposal = INDEX.save_proposal(
                payload.get("core", ""),
                payload.get("address", ""),
                payload.get("name", ""),
                payload.get("evidence", ""),
            )
            return self._json({"ok": True, "proposal": proposal}, HTTPStatus.CREATED)
        except (json.JSONDecodeError, KeyError, ValueError, RuntimeError) as exc:
            return self._error(str(exc), 400)

    def _static(self, request_path: str) -> None:
        relative = "index.html" if request_path in {"", "/"} else unquote(request_path.lstrip("/"))
        if relative not in {"index.html", "app.js", "styles.css"}:
            return self._error("not found", 404)
        path = STATIC / relative
        body = path.read_bytes()
        self.send_response(200)
        self.send_header("Content-Type", mimetypes.guess_type(path.name)[0] or "application/octet-stream")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Cache-Control", "no-cache")
        self.send_header("X-Content-Type-Options", "nosniff")
        self.send_header("Content-Security-Policy", "default-src 'self'; style-src 'self'; script-src 'self'; img-src 'self' data:; connect-src 'self'")
        self.end_headers()
        self.wfile.write(body)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=8765)
    args = parser.parse_args()
    server = ThreadingHTTPServer((args.host, args.port), Handler)
    print(f"G1 Symbol Browser: http://{args.host}:{args.port}")
    print(f"Rename proposals: {PROPOSALS.relative_to(ROOT)}")
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        server.server_close()


if __name__ == "__main__":
    main()
