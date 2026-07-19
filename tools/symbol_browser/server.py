#!/usr/bin/env python3
"""Local G1 symbol browser and concurrent-safe canonical rename server."""

from __future__ import annotations

import argparse
import fcntl
import gzip
import json
import mimetypes
import os
import re
import subprocess
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
OVERRIDES = ROOT / "recon" / "catalogs" / "function_name_overrides.json"
RENAME_LOCK = ROOT / ".git" / "g1-symbol-browser.rename.lock"
COORDINATION = ROOT / "recon" / "SESSION_COORDINATION.md"
APP_SOURCE_MANIFEST = ROOT / "recon" / "application" / "application_sources.json"
ADOPTION_MANIFEST = ROOT / "recon" / "ownership" / "adoption_manifest.json"
NET_OWNERSHIP = ROOT / "recon" / "ownership" / "net_function_ownership.json"
STRUCT_CATALOG = ROOT / "recon" / "structs" / "struct_catalog_app.json"
STRUCT_COVERAGE = ROOT / "recon" / "structs" / "struct_coverage_app.json"
STRUCT_VERIFICATION = ROOT / "recon" / "structs" / "struct_verification_report.json"
IDENTIFIER = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
ADDRESS_TOKEN = re.compile(r"^(?:0x)?([0-9a-fA-F]{4,8})$")
C_KEYWORDS = set("auto break case char const continue default do double else enum extern float for goto if inline int long register restrict return short signed sizeof static struct switch typedef union unsigned void volatile while _Bool _Complex _Imaginary".split())


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


def coordination_active() -> bool:
    if not COORDINATION.exists():
        return False
    for line in COORDINATION.read_text(errors="replace").splitlines():
        if line.lstrip().startswith(">"):
            continue
        if "**HELD**" in line:
            return True
    return False


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
        paths = [OVERRIDES, COORDINATION, APP_SOURCE_MANIFEST, ADOPTION_MANIFEST, NET_OWNERSHIP,
                 STRUCT_CATALOG, STRUCT_COVERAGE, STRUCT_VERIFICATION]
        for paths_by_kind in self.CATALOGS.values():
            paths.extend(paths_by_kind.values())
        return tuple((str(path), path.stat().st_mtime_ns if path.exists() else 0) for path in paths)

    @staticmethod
    def _ownership_maps() -> dict[str, dict[str, dict]]:
        app_manifest = read_json_retry(APP_SOURCE_MANIFEST)
        adoption = read_json_retry(ADOPTION_MANIFEST)
        net_audit = read_json_retry(NET_OWNERSHIP)
        app = {}
        for row in app_manifest.get("functions", []):
            address = canonical_address(row["address"])
            library = row.get("status") == "excluded_library"
            app[address] = {
                "ownership": "library" if library else "g1_application",
                "ownership_status": row.get("status", "application_candidate"),
                "ownership_evidence": row.get("reasons", []),
            }
        net = {}
        for address, row in net_audit.get("entries", {}).items():
            if row.get("status") != "sdk_library":
                continue
            net[canonical_address(address)] = {
                "ownership": "library",
                "ownership_status": "proven_sdk_library",
                "ownership_evidence": [f"net_function_ownership:{row.get('confidence', 'reviewed')}"]
            }
        for row in adoption.get("cores", {}).get("net", {}).get("entries", []):
            address = canonical_address(row["va"])
            net.setdefault(address, {
                "ownership": "library",
                "ownership_status": "upstream_owned",
                "ownership_evidence": [f"adoption_manifest:{row.get('component', 'upstream')}"]
            })
        return {"app": app, "net": net}

    @staticmethod
    def _source_inventory(directory: Path) -> dict[str, Path]:
        return {path.stem: path for path in directory.glob("*.c")}

    @staticmethod
    def _source_address_inventory(inventory: dict[str, Path], names: dict) -> dict[str, tuple[Path, str]]:
        result = {}
        for stem, path in inventory.items():
            header = path.read_text(errors="replace")[:2048]
            leading_comment = "\n".join(header.splitlines()[:8])
            raw_match = re.fullmatch(r"FUN_([0-9a-fA-F]{8})", stem)
            address_match = re.search(r"@\s*(0x[0-9a-fA-F]+)", leading_comment)
            mapped = names.get("by_name", {}).get(stem)
            if raw_match:
                address = canonical_address(int(raw_match.group(1), 16) & ~1)
                raw_name = raw_match.group(0)
            elif address_match:
                address = canonical_address(int(address_match.group(1), 16) & ~1)
                owner = re.search(r"(FUN_[0-9a-fA-F]+)", leading_comment[:address_match.start()])
                raw_name = owner.group(1) if owner else f"FUN_{address[2:]}"
            elif mapped:
                address = canonical_address(int(mapped, 16) & ~1)
                raw_name = f"FUN_{address[2:]}"
            else:
                continue
            result[address] = (path, raw_name)
        return result

    def refresh(self, *, force: bool = False) -> None:
        signature = self._signature()
        if not force and signature == self.signature:
            return
        with self.lock:
            signature = self._signature()
            if not force and signature == self.signature:
                return
            overrides = read_json_retry(OVERRIDES) if OVERRIDES.exists() else {"app": {}, "net": {}}
            ownership_maps = self._ownership_maps()
            cores = {}
            for core, paths in self.CATALOGS.items():
                names = read_json_retry(paths["names"])
                functions_payload = read_json_retry(paths["functions"], compressed=True)
                refs_payload = read_json_retry(paths["refs"], compressed=True)
                address_names = read_json_retry(paths["addresses"])
                functions = {canonical_address(item["entry"]): item for item in functions_payload["functions"]}
                refs = {canonical_address(key): value for key, value in refs_payload["functions"].items()}
                source_inventory = self._source_inventory(paths["source"])
                source_by_address = self._source_address_inventory(source_inventory, names)
                if core == "app":
                    readable_inventory = self._source_inventory(ROOT / "recon/named")
                else:
                    readable_inventory = {}
                records = {}
                by_name = {}
                for address, identity in names["by_address"].items():
                    address = canonical_address(address)
                    override = overrides.get(core, {}).get(address)
                    display_name = identity["display_name"]
                    raw_name = identity["raw_name"]
                    function = functions.get(address, {})
                    ref = refs.get(address, {})
                    ownership = ownership_maps[core].get(address, {
                        "ownership": "g1_application_candidate",
                        "ownership_status": "unclassified_application_candidate",
                        "ownership_evidence": [],
                    })
                    canonical_path = source_by_address.get(address, (None, None))[0]
                    source_path = readable_inventory.get(identity["display_name"]) or canonical_path
                    record = {
                        "core": core,
                        "address": address,
                        "raw_name": raw_name,
                        "canonical_name": identity["display_name"],
                        "display_name": display_name,
                        "human": not identity["display_name"].startswith("FUN_"),
                        "edited": bool(override and str(override.get("evidence", "")).startswith("[symbol-browser")),
                        "override": override,
                        "name_source": identity.get("source"),
                        "aliases": identity.get("aliases", []),
                        "size": ref.get("size", function.get("size")),
                        "signature": function.get("signature"),
                        "calling_convention": function.get("calling_convention"),
                        "is_thunk": bool(function.get("is_thunk")),
                        "has_source": source_path is not None,
                        "canonical_corpus": canonical_path is not None,
                        **ownership,
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
                # Newly recovered functions can land before the naming catalogs
                # regenerate. Keep them browsable by deriving their durable VA.
                for address, (source_path, derived_raw_name) in source_by_address.items():
                    stem = source_path.stem
                    if address in records:
                        records[address]["canonical_corpus"] = True
                        records[address]["has_source"] = True
                        records[address]["source_path"] = readable_inventory.get(records[address]["canonical_name"]) or source_path
                        continue
                    raw_name = derived_raw_name
                    function = functions.get(address, {})
                    ref = refs.get(address, {})
                    override = overrides.get(core, {}).get(address)
                    display_name = stem
                    ownership = ownership_maps[core].get(address, {
                        "ownership": "g1_application_candidate",
                        "ownership_status": "unclassified_application_candidate",
                        "ownership_evidence": [],
                    })
                    records[address] = {
                        "core": core, "address": address, "raw_name": raw_name,
                        "canonical_name": stem, "display_name": display_name,
                        "human": not stem.startswith("FUN_"),
                        "edited": bool(override and str(override.get("evidence", "")).startswith("[symbol-browser")),
                        "override": override,
                        "name_source": "canonical source pending catalog refresh", "aliases": [],
                        "size": ref.get("size", function.get("size")), "signature": function.get("signature"),
                        "calling_convention": function.get("calling_convention"), "is_thunk": bool(function.get("is_thunk")),
                        "has_source": True, "canonical_corpus": True, "source_path": source_path,
                        **ownership,
                        "calls": ref.get("calls", []), "callers": ref.get("callers", []),
                        "data_refs": ref.get("data_refs", []), "decompiled": function.get("decompiled", ""),
                    }
                    for name in {stem, display_name, raw_name}:
                        by_name.setdefault(name.lower(), address)
                cores[core] = {
                    "records": records,
                    "by_name": by_name,
                    "address_names": address_names,
                    "sorted": sorted(records, key=lambda value: int(value, 16)),
                }
            struct_payload = read_json_retry(STRUCT_CATALOG)
            coverage = read_json_retry(STRUCT_COVERAGE)
            verification = read_json_retry(STRUCT_VERIFICATION)
            structs = []
            struct_by_token = {}
            structs_by_function = {}
            for source in struct_payload.get("structs", []):
                row = dict(source)
                row["members"] = [dict(member) for member in source.get("members", [])]
                row["fields"] = [dict(field) for field in source.get("fields", [])]
                search_parts = [row.get("cid"), row.get("struct_name"), row.get("purpose"),
                                row.get("library_name"), row.get("library_header")]
                search_parts.extend(row.get("merged_cids", []))
                for field in row["fields"]:
                    search_parts.extend((field.get("name"), field.get("type"), field.get("library_member")))
                for member in row["members"]:
                    search_parts.extend((member.get("func"), member.get("entry"), member.get("base")))
                    try:
                        address = canonical_address(member["entry"])
                    except (KeyError, TypeError, ValueError):
                        continue
                    member["address"] = address
                    function = cores["app"]["records"].get(address)
                    if function:
                        member.update({
                            "display_name": function["display_name"],
                            "raw_name": function["raw_name"],
                            "resolvable": True,
                        })
                    else:
                        member.update({"display_name": member.get("func", address), "resolvable": False})
                    structs_by_function.setdefault(address, []).append(row)
                row["search"] = " ".join(str(part) for part in search_parts if part).lower()
                structs.append(row)
                for token in [row.get("cid"), row.get("struct_name"), *row.get("merged_cids", [])]:
                    if token:
                        struct_by_token.setdefault(str(token).lower(), row)
            structs.sort(key=lambda row: (row.get("is_library", False), row.get("struct_name", "").lower()))
            self.data = {
                "cores": cores,
                "structs": structs,
                "struct_by_token": struct_by_token,
                "structs_by_function": structs_by_function,
                "struct_coverage": coverage,
                "struct_verification": verification,
            }
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
        return candidate or (exact, 0)

    @staticmethod
    def _public_record(record: dict) -> dict:
        return {key: value for key, value in record.items() if key not in {"source_path", "decompiled", "calls", "callers", "data_refs"}}

    def list_symbols(self, core: str, query: str, state: str, page: int, limit: int, application_only: bool = True) -> dict:
        data = self._core(core)
        query = query.strip().lower()
        rows = []
        for address in data["sorted"]:
            record = data["records"][address]
            if not record["canonical_corpus"]:
                continue
            if application_only and record["ownership"] == "library":
                continue
            if state == "unnamed" and record["human"]:
                continue
            if state == "named" and not record["human"]:
                continue
            if state == "edited" and not record["edited"]:
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

    @staticmethod
    def _public_struct(row: dict) -> dict:
        return {key: value for key, value in row.items() if key not in {"search", "fields", "members", "verify_errors", "verify_warnings"}}

    def list_structs(self, query: str, scope: str, feature: str, page: int, limit: int) -> dict:
        self.refresh()
        query = query.strip().lower()
        rows = []
        for record in self.data["structs"]:
            if scope == "g1" and record.get("is_library"):
                continue
            if scope == "library" and not record.get("is_library"):
                continue
            if feature == "union" and not record.get("is_union"):
                continue
            if feature == "array" and not record.get("is_array"):
                continue
            if feature == "header" and not record.get("library_verified"):
                continue
            if query and query not in record["search"]:
                continue
            rows.append(self._public_struct(record))
        total = len(rows)
        start = max(page - 1, 0) * limit
        return {"items": rows[start:start + limit], "total": total, "page": page, "limit": limit}

    def struct_detail(self, token: str) -> dict | None:
        self.refresh()
        record = self.data["struct_by_token"].get(unquote(token).strip().lower())
        if not record:
            return None
        return {key: value for key, value in record.items() if key != "search"}

    def _reference(self, core: str, value: str, kind: str) -> dict:
        raw_value = value
        try:
            address = canonical_address(value)
        except (ValueError, TypeError):
            return {"kind": kind, "address": value, "display_name": value, "resolvable": False}
        owner, offset = self.resolve(core, address)
        if owner and owner in self._core(core)["records"]:
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
                "kind": "function",
                "goto_offset": offset,
                "source": source,
                "source_kind": source_kind,
                "source_path": source_path,
                "calls": [self._reference(core, value, "call") for value in record["calls"]],
                "callers": [self._reference(core, value, "caller") for value in record["callers"]],
                "data_refs": [self._reference(core, value, "data") for value in record["data_refs"] if not str(value).startswith("0x-")],
                "stack_refs": [value for value in record["data_refs"] if str(value).startswith("0x-")],
                "usages": self._usages(core, record),
                "structs": [self._public_struct(row) for row in self.data["structs_by_function"].get(address, [])],
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
            "edited": False,
            "override": None,
            "ownership": "data",
            "ownership_status": "non_function_reference",
            "ownership_evidence": [],
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
            "structs": [],
        }

    def meta(self) -> dict:
        self.refresh()
        cores = {}
        for core, data in self.data["cores"].items():
            records = [item for item in data["records"].values() if item["canonical_corpus"]]
            cores[core] = {
                "total": len(records),
                "application": sum(item["ownership"] != "library" for item in records),
                "library": sum(item["ownership"] == "library" for item in records),
                "named": sum(item["human"] for item in records),
                "unnamed": sum(not item["human"] for item in records),
                "edited": sum(item["edited"] for item in records),
                "with_source": sum(item["has_source"] for item in records),
            }
        struct_rows = self.data["structs"]
        coverage = self.data["struct_coverage"]
        verification = self.data["struct_verification"]
        return {
            "cores": cores,
            "structs": {
                "total": len(struct_rows),
                "g1": sum(not row.get("is_library") for row in struct_rows),
                "library": sum(bool(row.get("is_library")) for row in struct_rows),
                "verified": sum(bool(row.get("verified")) for row in struct_rows),
                "library_verified": sum(bool(row.get("library_verified")) for row in struct_rows),
                "unions": sum(bool(row.get("is_union")) for row in struct_rows),
                "arrays": sum(bool(row.get("is_array")) for row in struct_rows),
                "clusters_target": coverage.get("target_clusters", coverage.get("target", 0)),
                "clusters_covered": coverage.get("covered_clusters", coverage.get("covered", 0)),
                "verification_pass": verification.get("pass", 0),
                "verification_fail": verification.get("fail", 0),
            },
            "coordination_active": coordination_active(),
            "coordination_path": str(COORDINATION.relative_to(ROOT)),
            "rename_mode": "canonical_pipeline",
            "override_path": str(OVERRIDES.relative_to(ROOT)),
        }

    def apply_rename(self, core: str, address_token: str, name: str, evidence: str) -> dict:
        address, offset = self.resolve(core, address_token)
        if not address or offset:
            raise ValueError("renames require an exact function entry address")
        name = name.strip()
        if not IDENTIFIER.match(name) or name in C_KEYWORDS:
            raise ValueError("name must be a valid C identifier")
        data = self._core(core)
        collision = data["by_name"].get(name.lower())
        if collision and collision != address:
            raise ValueError(f"name already belongs to {collision}")
        if coordination_active():
            raise ValueError("canonical naming files are still HELD by the active sweep; apply after it lands")
        record = data["records"][address]
        RENAME_LOCK.parent.mkdir(parents=True, exist_ok=True)
        with open(RENAME_LOCK, "a+") as lock_file:
            fcntl.flock(lock_file, fcntl.LOCK_EX)
            original = OVERRIDES.read_bytes() if OVERRIDES.exists() else None
            payload = read_json_retry(OVERRIDES) if OVERRIDES.exists() else {"schema": 1, "app": {}, "net": {}}
            payload.setdefault(core, {})
            previous = payload[core].get(address, {})
            entry = dict(previous)
            entry["name"] = name
            entry["evidence"] = (
                f"[symbol-browser user {datetime.now(timezone.utc).isoformat()}] "
                f"{evidence.strip() or 'Interactive reviewed rename.'} "
                f"Raw identity remains {record['raw_name']}."
            )
            payload[core][address] = entry
            atomic_json_write(OVERRIDES, payload)
            commands = [
                [str(ROOT / ".venv/bin/python"), str(ROOT / "tools/build_function_names.py"), core],
                [str(ROOT / ".venv/bin/python"), str(ROOT / "tools/apply_names.py"), core],
                [str(ROOT / ".venv/bin/python"), str(ROOT / "tools/symbolize.py"), core, "--write"],
            ]
            if core == "app":
                commands.append([str(ROOT / ".venv/bin/python"), str(ROOT / "tools/build_app_source_view.py")])
            commands.append([str(ROOT / ".venv/bin/python"), str(ROOT / "tools/validate_name_maps.py"), core])
            output = []
            environment = dict(os.environ, PYTHONSAFEPATH="1")
            try:
                for command in commands:
                    result = subprocess.run(command, cwd="/tmp", env=environment, capture_output=True, text=True, timeout=180, check=True)
                    output.append(result.stdout.strip())
            except (subprocess.CalledProcessError, subprocess.TimeoutExpired) as exc:
                if original is None:
                    OVERRIDES.unlink(missing_ok=True)
                else:
                    fd, temporary = tempfile.mkstemp(prefix=".function_name_overrides.rollback.", dir=OVERRIDES.parent)
                    with os.fdopen(fd, "wb") as stream:
                        stream.write(original)
                        stream.flush()
                        os.fsync(stream.fileno())
                    os.replace(temporary, OVERRIDES)
                detail = (getattr(exc, "stderr", "") or getattr(exc, "stdout", "") or str(exc)).strip()
                rollback_detail = ""
                try:
                    # The derived maps/trees may already have changed before a
                    # later pipeline stage failed. Rebuild them from the
                    # restored override so rollback covers the whole pipeline.
                    for command in commands:
                        subprocess.run(command, cwd="/tmp", env=environment, capture_output=True, text=True, timeout=180, check=True)
                except (subprocess.CalledProcessError, subprocess.TimeoutExpired) as rollback_exc:
                    rollback_detail = (getattr(rollback_exc, "stderr", "") or getattr(rollback_exc, "stdout", "") or str(rollback_exc)).strip()
                suffix = f"; rollback rebuild also failed: {rollback_detail[-600:]}" if rollback_detail else ""
                raise RuntimeError(f"rename pipeline failed; canonical state rolled back: {detail[-1200:]}{suffix}") from exc
            finally:
                fcntl.flock(lock_file, fcntl.LOCK_UN)
        self.refresh(force=True)
        return {
            "core": core, "address": address, "raw_name": record["raw_name"],
            "previous_name": record["canonical_name"], "name": name,
            "status": "applied_canonical", "pipeline_output": output,
        }


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
                application_only = query.get("application_only", ["1"])[0].lower() not in {"0", "false", "no"}
                return self._json(INDEX.list_symbols(core, search, state, page, limit, application_only))
            if parsed.path == "/api/structs":
                search = query.get("q", [""])[0]
                scope = query.get("scope", ["all"])[0]
                feature = query.get("feature", ["all"])[0]
                page = max(1, int(query.get("page", ["1"])[0]))
                limit = min(100, max(10, int(query.get("limit", ["60"])[0])))
                return self._json(INDEX.list_structs(search, scope, feature, page, limit))
            if parsed.path.startswith("/api/struct/"):
                token = parsed.path.removeprefix("/api/struct/")
                detail = INDEX.struct_detail(token)
                return self._json(detail) if detail else self._error("structure not found", 404)
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
            applied = INDEX.apply_rename(
                payload.get("core", ""),
                payload.get("address", ""),
                payload.get("name", ""),
                payload.get("evidence", ""),
            )
            return self._json({"ok": True, "applied": applied}, HTTPStatus.CREATED)
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
    print(f"Canonical overrides: {OVERRIDES.relative_to(ROOT)}")
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        server.server_close()


if __name__ == "__main__":
    main()
