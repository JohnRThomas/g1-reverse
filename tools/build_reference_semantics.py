#!/usr/bin/env python3
"""Build viewer-ready, evidence-grounded CPUAPP reference semantics.

The Ghidra reference graph deliberately records only unique function/data
targets.  This pass enriches those durable edges without inventing new ones:

* function and address maps supply stable human/raw identities;
* readable reconstructed C supplies line-level use sites and access modes;
* the firmware image supplies conservative string/byte previews;
* verified recovered layouts attach structure and field meaning; and
* reconstructed rodata files distinguish tables/pools from arbitrary flash.

The result is presentation metadata.  It never rewrites the parity corpus or
claims a type/layout beyond the evidence already present in the repository.
"""

from __future__ import annotations

import argparse
import bisect
import gzip
import hashlib
import json
import re
from collections import Counter, defaultdict
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_OUTPUT = ROOT / "recon" / "viewer_sweep" / "reference_semantics.json"

NAMES = ROOT / "recon" / "catalogs" / "function_names_app.json"
ADDRESS_NAMES = ROOT / "recon" / "catalogs" / "address_names_app.json"
REFGRAPH = ROOT / "recon" / "catalogs" / "refgraph_app.json.gz"
FUNCTIONS = ROOT / "recon" / "catalogs" / "app_funcs.json.gz"
READABLE_MANIFEST = ROOT / "recon" / "readable_sources" / "app" / "manifest.json"
STRUCT_CATALOG = ROOT / "recon" / "structs" / "struct_catalog_app.json"
FIRMWARE = ROOT / "app_update.bin"
DATA_DIR = ROOT / "recon" / "data"

APP_LINK_BASE = 0xC200
APP_HEADER_SIZE = 512

ADDRESS_COMMENT = re.compile(r"/\*=\s*(0x[0-9a-fA-F]+)\s*\*/")
HEX_LITERAL = re.compile(r"(?<![A-Za-z0-9_])(0x[0-9a-fA-F]+)(?:[uUlL]*)")
ASSIGNMENT = re.compile(r"(?<![=!<>])(?:\+=|-=|\*=|/=|%=|\|=|&=|\^=|=(?!=))")
IDENTIFIER = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]*\b")


SUBSYSTEM_RULES = [
    ("bluetooth", ("ble", "bt_", "gatt", "l2cap", "hci", "ancs", "smp_", "att_", "uuid")),
    ("audio", ("audio", "lc3", "codec", "dmic", "mic_", "pdm", "i2s", "speaker")),
    ("display", ("display", "projector", "panel", "pixel", "render", "dashboard", "quicknote", "ui_", "font")),
    ("sensors", ("imu", "sensor", "opt300", "lux", "acceler", "gyro", "fusion")),
    ("power", ("battery", "fuel", "charging", "power", "suspend", "resume", "gpio")),
    ("storage", ("flash", "nvs", "settings", "filesystem", "file_", "fs_", "qspi")),
    ("ipc_radio", ("ipc", "rpmsg", "openamp", "esb", "mailbox", "mbox", "remote")),
    ("crypto", ("crypto", "aes", "sha", "cc3", "entropy", "random", "hash", "cipher")),
    ("nfc", ("nfc", "ndef", "st25")),
    ("firmware_update", ("dfu", "mcumgr", "image_mgmt", "boot", "upgrade")),
    ("logging", ("log_", "print", "format", "cbprintf", "trace")),
    ("kernel", ("thread", "work_", "queue", "fifo", "sem", "mutex", "timer", "poll", "slab")),
    ("libc_math", ("memcpy", "memset", "strlen", "malloc", "free", "float", "double", "math", "dtoa")),
    ("input", ("button", "click", "gesture", "key_", "touch", "input")),
]

ASSET_HINTS = [
    ("font", ("font", "glyph", "unicode", "word_table")),
    ("bitmap", ("bitmap", "image", "logo", "pixel", "framebuffer")),
    ("audio_table", ("lc3_", "spectrum", "tns_", "sns_", "band_lim", "codec_table")),
    ("lookup_table", ("lookup", "table", "lut", "coeff", "window", "twiddle", "model", "codebook")),
    ("protocol_descriptor", ("uuid", "gatt", "service", "descriptor", "characteristic")),
]


def read_json(path: Path, *, compressed: bool = False) -> dict:
    if compressed:
        with gzip.open(path, "rt", encoding="utf-8") as stream:
            return json.load(stream)
    return json.loads(path.read_text())


def canonical_address(value: int | str) -> str:
    if isinstance(value, str):
        value = int(value, 16)
    return f"0x{value & ~1:08x}"


def display_address(value: int) -> str:
    return f"0x{value:08x}"


def ref_value(value: str) -> int:
    """Parse Ghidra's unusual ``0x-38`` spelling as well as normal hex."""
    if value.startswith("0x-"):
        return -int(value[3:], 16)
    return int(value, 16)


def file_sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def strip_line_comments(line: str) -> str:
    line = re.sub(r"/\*.*?\*/", "", line)
    return re.sub(r"//.*$", "", line)


def source_line_is_code(line: str) -> bool:
    stripped = line.lstrip()
    return bool(stripped and not stripped.startswith(("/*", "*", "//", "#", "extern ")))


def source_line_is_meaningful(line: str) -> bool:
    """True for code or a macro definition, false for provenance-only text."""
    stripped = line.lstrip()
    return bool(stripped and not stripped.startswith(("/*", "*", "//", "extern ")))


def infer_subsystem(*names: str) -> str:
    haystack = " ".join(name or "" for name in names).lower()
    scores = []
    for subsystem, needles in SUBSYSTEM_RULES:
        hits = sum(needle in haystack for needle in needles)
        if hits:
            scores.append((hits, subsystem))
    return max(scores)[1] if scores else "platform_core"


def infer_asset(name: str, role: str, target_address: str | None) -> dict | None:
    lowered = (name or "").lower()
    if role in {"format_string", "diagnostic_string"}:
        return {
            "candidate_id": f"string_{(target_address or 'unknown')[2:]}",
            "kind": "string",
            "reason": "firmware bytes decode as a printable string",
        }
    for kind, needles in ASSET_HINTS:
        if any(needle in lowered for needle in needles):
            return {
                "candidate_id": re.sub(r"[^a-z0-9_]+", "_", lowered).strip("_") or f"asset_{target_address}",
                "kind": kind,
                "reason": f"target name contains a {kind.replace('_', ' ')} marker",
            }
    return None


class FunctionIndex:
    def __init__(self, names: dict, refs: dict, manifest: dict):
        self.by_address = {canonical_address(key): dict(value) for key, value in names["by_address"].items()}
        self.manifest = {canonical_address(row["address"]): row for row in manifest.get("sources", [])}
        self.refs = {canonical_address(key): value for key, value in refs["functions"].items()}
        self.starts: list[int] = []
        self.ranges: list[tuple[int, int, str]] = []
        for address, row in self.refs.items():
            start = int(address, 16)
            size = max(0, int(row.get("size") or 0))
            if size:
                self.ranges.append((start, start + size, address))
        self.ranges.sort()
        self.starts = [item[0] for item in self.ranges]

    def identity(self, address: str) -> dict:
        address = canonical_address(address)
        row = self.by_address.get(address, {})
        manifest = self.manifest.get(address, {})
        human = manifest.get("public_name") or row.get("display_name") or row.get("name") or f"function_{address[2:]}"
        raw = manifest.get("raw_symbol") or row.get("raw_name") or f"FUN_{address[2:]}"
        return {
            "address": address,
            "human_name": human,
            "raw_name": raw,
            "category": manifest.get("category", "unknown"),
        }

    def owner(self, value: int) -> tuple[dict | None, int | None]:
        index = bisect.bisect_right(self.starts, value) - 1
        # Ghidra functions can overlap when trailing data is folded into a
        # symbol. Check a short predecessor window and prefer the tightest.
        candidates = []
        for pos in range(max(0, index - 6), index + 1):
            start, end, address = self.ranges[pos]
            if start <= value < end:
                candidates.append((end - start, start, address))
        if not candidates:
            return None, None
        _, start, address = min(candidates)
        return self.identity(address), value - start


class SourceIndex:
    def __init__(self, manifest: dict, decompiled_rows: dict, functions: FunctionIndex):
        self.functions = functions
        self.sources: dict[str, dict] = {}
        for row in manifest.get("sources", []):
            address = canonical_address(row["address"])
            path = ROOT / row["output"]
            if not path.exists():
                continue
            self.sources[address] = {
                "path": row["output"],
                "kind": "readable_reconstruction",
                "lines": path.read_text(errors="replace").splitlines(),
            }
        for address, row in decompiled_rows.items():
            address = canonical_address(address)
            if address in self.sources:
                continue
            self.sources[address] = {
                "path": "recon/catalogs/app_funcs.json.gz",
                "kind": "ghidra_decompilation",
                "lines": str(row.get("decompiled") or "").splitlines(),
            }

    @staticmethod
    def access_modes(line: str, symbol_tokens: list[str], *, is_call: bool = False) -> list[str]:
        code = strip_line_comments(line)
        if is_call:
            return ["call"]
        token = next((item for item in symbol_tokens if item and re.search(rf"\b{re.escape(item)}\b", code)), None)
        target_pos = code.find(token) if token else -1
        modes = set()
        if token and (f"&{token}" in code.replace(" ", "") or re.search(rf"\b{re.escape(token)}\s*\[", code)):
            modes.add("address_taken" if f"&{token}" in code.replace(" ", "") else "indexed")
        if target_pos >= 0:
            before, after = code[:target_pos], code[target_pos:]
            assignment = ASSIGNMENT.search(code)
            if re.search(r"\+\+|--", before[-3:] + after[: len(token or "") + 3]):
                modes.update(("read", "write"))
            elif assignment and target_pos < assignment.start():
                # An address in a pointer initializer is not a write to the
                # addressed object.  Dereferencing that expression is.
                if "&" in after[: assignment.start() - target_pos] and "*(" not in before[-3:]:
                    modes.add("address_taken")
                elif "*" in before[-3:] or (token and re.search(rf"\b{re.escape(token)}\s*\[", code)):
                    modes.add("write")
                else:
                    modes.add("address_taken")
            else:
                modes.add("read")
        if not modes:
            modes.add("read")
        return sorted(modes, key=("call", "address_taken", "indexed", "read", "write").index)

    def locate(self, source_address: str, *, target_address: str | None, target_names: list[str], is_call: bool) -> dict | None:
        source = self.sources.get(canonical_address(source_address))
        if not source:
            return None
        lines = source["lines"]
        names = [name for name in target_names if name]
        address_patterns = []
        if target_address:
            value = int(target_address, 16)
            address_patterns = [
                re.compile(rf"(?<![0-9a-fA-F])0x0*{value:x}(?![0-9a-fA-F])", re.I),
                re.compile(rf"\b(?:DAT|UNK)_{value:08x}\b", re.I),
            ]
        candidates = []
        for line_number, line in enumerate(lines, 1):
            code = strip_line_comments(line)
            matched_names = [name for name in names if re.search(rf"\b{re.escape(name)}\b", code)]
            matched_address = any(pattern.search(line) for pattern in address_patterns)
            if is_call:
                called = any(re.search(rf"\b{re.escape(name)}\s*\(", code) for name in names)
                if not called:
                    continue
            elif not (matched_names or matched_address):
                continue
            score = 10 if source_line_is_code(line) else 0
            score += 8 if matched_names else 0
            score += 5 if ADDRESS_COMMENT.search(line) else 0
            score += 6 if is_call else 0
            score += 2 if ASSIGNMENT.search(code) else 0
            if code.lstrip().startswith(("extern ", "struct ")):
                score -= 12
            modes = self.access_modes(line, matched_names or names, is_call=is_call)
            candidates.append((score, line_number, line, modes, matched_names))
        if not candidates:
            return None
        meaningful = [item for item in candidates if source_line_is_meaningful(item[2])]
        if not meaningful:
            return None
        candidates = meaningful
        if any(source_line_is_code(item[2]) for item in candidates):
            candidates = [item for item in candidates if source_line_is_code(item[2])]
        candidates.sort(key=lambda item: (-item[0], item[1]))
        _, line_number, line, modes, matched_names = candidates[0]
        use_sites = [{
            "line": number,
            "snippet": text.strip(),
            "access_modes": found_modes,
        } for _, number, text, found_modes, _ in candidates[:6]]

        # Follow a simple local pointer alias to reveal indexed/read/write
        # usage hidden behind a one-time fixed-address initializer.
        code = strip_line_comments(line)
        target_position = min([code.find(name) for name in matched_names if name in code] or [len(code)])
        prefix = code[:target_position]
        left = prefix.rsplit("=", 1)[0].strip() if "=" in prefix else ""
        # Only follow `type *simple_alias = &target`.  Expressions such as
        # `W32(context, off) = ADDR_callback` do not alias the target.
        simple_initializer = bool(left and not re.search(r"[()\[\],]", left))
        alias_matches = IDENTIFIER.findall(left) if simple_initializer and not is_call else []
        alias = alias_matches[-1] if alias_matches else None
        if alias and alias not in {"return", "if", "while", "const", "volatile"}:
            for number in range(line_number + 1, min(len(lines), line_number + 100) + 1):
                text = lines[number - 1]
                alias_code = strip_line_comments(text)
                if not re.search(rf"\b{re.escape(alias)}\b", alias_code):
                    continue
                alias_modes = self.access_modes(text, [alias], is_call=False)
                if re.search(rf"\b{re.escape(alias)}\s*\[|\b{re.escape(alias)}\s*\+", alias_code):
                    alias_modes = sorted(set(alias_modes) | {"indexed"}, key=("call", "address_taken", "indexed", "read", "write").index)
                use_sites.append({"line": number, "snippet": text.strip(), "access_modes": alias_modes, "via_alias": alias})
                if len(use_sites) >= 10:
                    break
        use_sites.sort(key=lambda site: site["line"])
        all_modes = sorted({mode for site in use_sites for mode in site["access_modes"]}, key=("call", "address_taken", "indexed", "read", "write").index)
        return {
            "source_path": source["path"],
            "source_kind": source["kind"],
            "line": line_number,
            "snippet": line.strip(),
            "use_sites": use_sites,
            "access_modes": all_modes,
        }


class DataIndex:
    def __init__(self, address_names: dict, firmware: bytes):
        # Data symbols can legitimately start at odd byte addresses.  Never
        # apply Thumb-address canonicalization to this map.
        self.address_names = {
            display_address(int(key, 16)): dict(value)
            for key, value in address_names.get("by_address", {}).items()
        }
        self.firmware = firmware
        self.tables = self._load_tables()
        self.table_starts = [row[0] for row in self.tables]

    @staticmethod
    def _load_tables() -> list[tuple[int, int, dict]]:
        rows = []
        address_pattern = re.compile(r"(?:app-core\s+(?:VA|rodata\s*@)|\bVA)\s*(0x[0-9a-fA-F]+)", re.I)
        size_patterns = [re.compile(r"\b(\d+)\s+bytes\b", re.I), re.compile(r"\bspan\s*=\s*(\d+)\s+bytes", re.I)]
        for path in sorted(DATA_DIR.glob("*.c")):
            head = path.read_text(errors="replace")[:1600]
            address_match = address_pattern.search(head)
            if not address_match:
                stem_match = re.search(r"(?:0x)?([0-9a-fA-F]{4,8})$", path.stem)
                if not stem_match:
                    continue
                start = int(stem_match.group(1), 16)
            else:
                start = int(address_match.group(1), 16)
            size = None
            for pattern in size_patterns:
                match = pattern.search(head)
                if match:
                    size = int(match.group(1))
                    break
            if not size:
                declaration = re.search(r"\b(?:uint8_t|unsigned\s+char)\s+\w+\s*\[(\d+)\]", head)
                size = int(declaration.group(1)) if declaration else 1
            description = " ".join(re.sub(r"[/\*]", "", line).strip() for line in head.splitlines()[:4])
            rows.append((start, start + size, {
                "address": display_address(start),
                "size": size,
                "symbol": path.stem,
                "source": str(path.relative_to(ROOT)),
                "description": description[:320],
            }))
        rows.sort()
        return rows

    def table_at(self, value: int) -> tuple[dict | None, int | None]:
        index = bisect.bisect_right(self.table_starts, value) - 1
        candidates = []
        for pos in range(max(0, index - 5), index + 1):
            start, end, row = self.tables[pos]
            if start <= value < end:
                candidates.append((end - start, start, row))
        if not candidates:
            return None, None
        _, start, row = min(candidates)
        return row, value - start

    def bytes_at(self, value: int, count: int = 32) -> bytes:
        offset = value - APP_LINK_BASE + APP_HEADER_SIZE
        if offset < 0 or offset >= len(self.firmware):
            return b""
        return self.firmware[offset: offset + count]

    def printable_string(self, value: int) -> str | None:
        blob = self.bytes_at(value, 192)
        if not blob:
            return None
        payload = blob.split(b"\x00", 1)[0]
        if len(payload) < 4 or len(payload) >= len(blob):
            return None
        try:
            decoded = payload.decode("utf-8")
        except UnicodeDecodeError:
            return None
        if any(ord(char) < 0x20 and char not in "\t\r\n" for char in decoded):
            return None
        if sum(char.isprintable() or char in "\t\r\n" for char in decoded) / len(decoded) < 0.95:
            return None
        return decoded

    def address_identity(self, value: int) -> dict:
        address = display_address(value)
        row = self.address_names.get(address)
        if row:
            base = row.get("base_address") or address
            return {
                "address": address,
                "human_name": row.get("name") or f"data_{value:08x}",
                "raw_name": f"DAT_{value:08x}",
                "base_address": display_address(int(base, 16)),
                "offset": int(row.get("offset") or (value - int(base, 16))),
                "naming_evidence": row.get("evidence", []),
            }
        return {
            "address": address,
            "human_name": f"data_{value:08x}",
            "raw_name": f"DAT_{value:08x}",
            "base_address": address,
            "offset": 0,
            "naming_evidence": [],
        }


class StructIndex:
    def __init__(self, catalog: dict):
        self.by_function: dict[str, list[dict]] = defaultdict(list)
        self.globals: list[tuple[int, int, dict, dict]] = []
        for row in catalog.get("structs", []):
            for member in row.get("members", []):
                try:
                    function = canonical_address(member["entry"])
                except (KeyError, ValueError):
                    continue
                self.by_function[function].append({"row": row, "member": member})
                base = member.get("base", "")
                if re.fullmatch(r"0x[0-9a-fA-F]+", str(base)):
                    start = int(base, 16)
                    self.globals.append((start, start + max(1, int(row.get("size_lower_bound") or 1)), row, member))

    @staticmethod
    def public_relation(row: dict, member: dict, offset: int | None, field: dict | None) -> dict:
        return {
            "cid": row.get("cid"),
            "struct_name": row.get("struct_name"),
            "purpose": row.get("purpose"),
            "base": member.get("base"),
            "offset": f"0x{offset:x}" if offset is not None else None,
            "field": ({
                "name": field.get("name"),
                "type": field.get("type"),
                "offset": field.get("offset"),
                "library_member": field.get("library_member"),
            } if field else None),
            "verified": bool(row.get("verified")),
            "confidence": row.get("confidence"),
        }

    def relations(self, source_address: str, target_value: int | None, source_location: dict | None) -> list[dict]:
        matches = []
        if target_value is not None:
            for start, end, row, member in self.globals:
                if start <= target_value < end:
                    offset = target_value - start
                    field = next((field for field in row.get("fields", []) if int(field["offset"], 16) == offset), None)
                    # Sparse global layouts can span code/data that merely
                    # shares the address interval.  Exact field/base hits are
                    # grounded; interval-only matches are not.
                    if field or offset == 0:
                        matches.append(self.public_relation(row, member, offset, field))
        snippet = (source_location or {}).get("snippet", "")
        if snippet:
            for binding in self.by_function.get(canonical_address(source_address), []):
                row, member = binding["row"], binding["member"]
                for field in row.get("fields", []):
                    if field.get("name") and re.search(rf"\b{re.escape(field['name'])}\b", snippet):
                        matches.append(self.public_relation(row, member, int(field["offset"], 16), field))
        deduped = {}
        for item in matches:
            key = (item["cid"], (item.get("field") or {}).get("offset"))
            deduped.setdefault(key, item)
        return list(deduped.values())[:6]


def source_constants(location: dict | None, target_address: str | None) -> list[dict]:
    if not location:
        return []
    target = int(target_address, 16) if target_address else None
    values = []
    for match in HEX_LITERAL.finditer(strip_line_comments(location.get("snippet", ""))):
        value = int(match.group(1), 16)
        if target is not None and value == target:
            continue
        values.append({"literal": match.group(0), "value": value, "hex": f"0x{value:x}"})
    unique = []
    seen = set()
    for item in values:
        if item["value"] not in seen:
            unique.append(item)
            seen.add(item["value"])
    return unique[:12]


def primary_access_mode(modes: list[str], role: str) -> str:
    if "call" in modes:
        return "call"
    if "write" in modes and "read" in modes:
        return "read_write"
    if "write" in modes:
        return "write"
    if "indexed" in modes:
        return "indexed"
    if "address_taken" in modes:
        return "address_taken"
    if role == "callback_pointer":
        return "address_taken"
    return "read"


def access_phrase(mode: str) -> str:
    return {
        "read": "reads",
        "write": "writes",
        "read_write": "reads and updates",
        "indexed": "indexes",
        "address_taken": "takes the address of",
        "call": "calls",
    }.get(mode, f"uses ({mode})")


def classify_data_edge(
    value: int | None,
    target: dict,
    source_location: dict | None,
    function_owner: dict | None,
    owner_offset: int | None,
    table: dict | None,
    table_offset: int | None,
    decoded_string: str | None,
    related_structs: list[dict],
) -> tuple[str, str, list[str], str]:
    modes = list((source_location or {}).get("access_modes", []))
    evidence = []
    if value is None:
        return "stack_slot", "local_stack_slot", ["Ghidra emitted a negative stack-relative data reference"], "low"
    if function_owner and owner_offset == 0:
        role = "callback_pointer" if "address_taken" in modes or any(word in target["human_name"].lower() for word in ("callback", "handler", "_cb")) else "function_pointer"
        evidence.append("data reference resolves exactly to a mapped function entry")
        return "function", role, evidence, "high" if source_location else "medium"
    if table:
        evidence.append(f"address lies in reconstructed data object {table['symbol']}+0x{table_offset:x}")
    if function_owner and not table:
        evidence.append(f"address lies inside {function_owner['human_name']}+0x{owner_offset:x}")
        return "code_interior", "code_interior_reference", evidence, "medium"
    if 0x40000000 <= value < 0x60000000:
        evidence.append("address is in the nRF peripheral/MMIO range")
        return "mmio_register", "peripheral_register", evidence, "high"
    if 0x20000000 <= value < 0x30000000:
        evidence.append("address is in application SRAM")
        if related_structs:
            evidence.append("address falls within a verified recovered global layout")
            role = "structure_field" if any(item.get("field") for item in related_structs) else "structure_base"
        else:
            role = "named_global_state" if not target["human_name"].startswith("data_") else "global_state"
        confidence = "high" if target.get("naming_evidence") or related_structs else "medium"
        return "ram_global", role, evidence, confidence
    if 0 <= value < 0x1000:
        evidence.append("small non-address value emitted as a Ghidra data reference")
        return "small_literal_or_offset", "small_literal_or_offset", evidence, "low"
    if decoded_string is not None:
        evidence.append("firmware bytes at the target form a bounded NUL-terminated UTF-8 string")
        format_context = "%" in decoded_string or ".format" in (source_location or {}).get("snippet", "")
        return "flash_string", "format_string" if format_context else "diagnostic_string", evidence, "high"
    if table:
        description = table.get("description", "").lower()
        modes_set = set(modes)
        if "literal" in description or "pointer" in description:
            role = "literal_pointer_pool"
        elif "indexed" in modes_set or any(token in target["human_name"].lower() for token in ("table", "lookup", "coeff", "model", "lc3_")):
            role = "lookup_table"
        else:
            role = "immutable_data"
        return "flash_rodata", role, evidence, "high"
    if APP_LINK_BASE <= value < 0x20000000:
        evidence.append("address is in the CPUAPP flash image range")
        role = "lookup_table" if "indexed" in modes or any(token in target["human_name"].lower() for token in ("table", "lookup", "coeff", "model", "lc3_")) else "immutable_constant"
        return "flash_rodata", role, evidence, "medium"
    evidence.append("reference target is outside classified CPUAPP flash, SRAM, and MMIO ranges")
    return "external_address", "external_reference", evidence, "low"


def meaning_for(source: dict, target: dict, role: str, mode: str, decoded_string: str | None, related_structs: list[dict]) -> str:
    actor = source["human_name"]
    name = target.get("human_name") or target.get("expression") or "the referenced object"
    if role == "routine_invocation":
        return f"{actor} invokes {name} as part of its control flow."
    if role == "callback_pointer":
        return f"{actor} takes or uses the address of {name} as a callback/function pointer."
    if role == "function_pointer":
        return f"{actor} references the code entry for {name} without a direct call edge."
    if role == "format_string":
        preview = json.dumps(decoded_string[:96] if decoded_string else name)
        return f"{actor} uses {preview} as formatted diagnostic/log text."
    if role == "diagnostic_string":
        preview = json.dumps(decoded_string[:96] if decoded_string else name)
        return f"{actor} references the firmware text {preview}."
    if role in {"structure_base", "structure_field"} and related_structs:
        relation = related_structs[0]
        field = relation.get("field")
        detail = f" field {field['name']}" if field else ""
        return f"{actor} {access_phrase(mode)} {relation['struct_name']}{detail} at {name}."
    if role == "named_global_state":
        return f"{actor} {access_phrase(mode)} the named global {name}."
    if role == "peripheral_register":
        return f"{actor} {access_phrase(mode)} the memory-mapped peripheral register {name}."
    if role == "lookup_table":
        return f"{actor} uses {name} as indexed immutable lookup data."
    if role == "literal_pointer_pool":
        return f"{actor} loads constants or addresses through the reconstructed literal pool {name}."
    if role == "local_stack_slot":
        return f"Ghidra recorded a stack-relative local used by {actor}; it is not a global object."
    if role == "code_interior_reference":
        return f"{actor} references an interior address associated with {name}, usually embedded code data or a literal location."
    return f"{actor} {access_phrase(mode)} {name} as {role.replace('_', ' ')}."


def build(output: Path) -> dict:
    names = read_json(NAMES)
    address_names = read_json(ADDRESS_NAMES)
    refs = read_json(REFGRAPH, compressed=True)
    function_rows_payload = read_json(FUNCTIONS, compressed=True)
    function_rows = {canonical_address(row["entry"]): row for row in function_rows_payload["functions"]}
    manifest = read_json(READABLE_MANIFEST)
    structs = read_json(STRUCT_CATALOG)
    firmware = FIRMWARE.read_bytes()

    functions = FunctionIndex(names, refs, manifest)
    sources = SourceIndex(manifest, function_rows, functions)
    data = DataIndex(address_names, firmware)
    struct_index = StructIndex(structs)

    edges = []
    incoming: dict[str, list[str]] = defaultdict(list)
    outgoing: dict[str, list[str]] = defaultdict(list)

    for source_address in sorted(functions.refs, key=lambda address: int(address, 16)):
        ref = functions.refs[source_address]
        source_identity = functions.identity(source_address)
        for call_target in sorted(set(ref.get("calls", [])), key=lambda value: int(value, 16)):
            target_address = canonical_address(call_target)
            target_identity = functions.identity(target_address)
            location = sources.locate(
                source_address,
                target_address=target_address,
                target_names=[target_identity["human_name"], target_identity["raw_name"]],
                is_call=True,
            )
            edge_id = f"app:{source_address[2:]}:call:{target_address[2:]}"
            subsystem = infer_subsystem(source_identity["human_name"], target_identity["human_name"])
            evidence = ["Ghidra refgraph direct-call edge"]
            confidence = "high" if location else "medium"
            if location:
                evidence.append(f"call expression found in {location['source_path']}:{location['line']}")
            call_constants = source_constants(location, None)
            edge = {
                "id": edge_id,
                "edge_kind": "call",
                "source": source_identity,
                "target": {**target_identity, "referenced_address": target_address, "target_kind": "function"},
                "source_location": location,
                "access_mode": "call",
                "access_modes": ["call"],
                "target_kind": "function",
                "inferred_role": "routine_invocation",
                "meaning": meaning_for(source_identity, target_identity, "routine_invocation", "call", None, []),
                "subsystem": subsystem,
                "related_structs": [],
                "related_constant": ({"kind": "call_arguments", "values": call_constants} if call_constants else None),
                "source_constants": call_constants,
                "related_asset": None,
                "confidence": confidence,
                "evidence": evidence,
            }
            edges.append(edge)
            outgoing[source_address].append(edge_id)
            incoming[target_address].append(edge_id)

        for raw_target in sorted(set(ref.get("data_refs", [])), key=ref_value):
            if raw_target.startswith("0x-"):
                value = None
                stack_offset = -int(raw_target[3:], 16)
                target_address = None
                target_identity = {
                    "address": None,
                    "expression": raw_target,
                    "human_name": f"stack_{stack_offset:+#x}",
                    "raw_name": raw_target,
                    "base_address": None,
                    "offset": stack_offset,
                    "naming_evidence": [],
                }
                function_owner = None
                owner_offset = None
                table = None
                table_offset = None
                decoded = None
            else:
                value = int(raw_target, 16)
                target_address = display_address(value)
                function_owner, owner_offset = (
                    functions.owner(value & ~1) if value >= APP_LINK_BASE else (None, None)
                )
                exact_function = (
                    functions.by_address.get(canonical_address(value)) if value >= APP_LINK_BASE else None
                )
                if exact_function:
                    function_owner = functions.identity(canonical_address(value))
                    owner_offset = 0
                    target_identity = {
                        **function_owner,
                        "base_address": function_owner["address"],
                        "offset": 0,
                        "naming_evidence": ["function_names_app.json"],
                    }
                else:
                    target_identity = data.address_identity(value)
                table, table_offset = data.table_at(value)
                decoded = data.printable_string(value) if not function_owner or table else None
            location = sources.locate(
                source_address,
                target_address=target_address,
                target_names=[target_identity.get("human_name"), target_identity.get("raw_name")],
                is_call=False,
            )
            related_structs = struct_index.relations(source_address, value, location)
            target_kind, role, role_evidence, confidence = classify_data_edge(
                value, target_identity, location, function_owner, owner_offset,
                table, table_offset, decoded, related_structs,
            )
            modes = list((location or {}).get("access_modes", []))
            mode = primary_access_mode(modes, role)
            if not modes:
                modes = [mode]
            evidence = ["Ghidra refgraph data-reference edge", *role_evidence]
            if target_identity.get("naming_evidence"):
                evidence.append("target name is backed by " + ", ".join(target_identity["naming_evidence"]))
            if location:
                evidence.append(f"target expression found in {location['source_path']}:{location['line']}")
            if related_structs:
                evidence.append("relation comes from a D1+D2-verified recovered layout")
            if location and confidence == "medium" and target_identity.get("naming_evidence"):
                confidence = "high"
            constant = None
            if decoded is not None:
                constant = {"kind": "string", "value": decoded, "length": len(decoded.encode("utf-8"))}
            elif value is not None and target_kind in {"flash_rodata", "code_interior"}:
                preview = data.bytes_at(value, 16)
                if preview:
                    constant = {
                        "kind": "firmware_bytes",
                        "hex_preview": preview.hex(),
                        "u32_le": int.from_bytes(preview[:4], "little") if len(preview) >= 4 else None,
                    }
            target = {
                **target_identity,
                "referenced_address": target_address,
                "target_kind": target_kind,
                "function_owner": ({**function_owner, "interior_offset": owner_offset} if function_owner else None),
                "data_object": ({**table, "interior_offset": table_offset} if table else None),
            }
            edge_id_target = (target_address or raw_target).replace("0x", "").replace("-", "m")
            edge_id = f"app:{source_address[2:]}:data:{edge_id_target}"
            asset = infer_asset(target_identity.get("human_name", ""), role, target_address)
            edge = {
                "id": edge_id,
                "edge_kind": "data_reference",
                "source": source_identity,
                "target": target,
                "source_location": location,
                "access_mode": mode,
                "access_modes": modes,
                "target_kind": target_kind,
                "inferred_role": role,
                "meaning": meaning_for(source_identity, target_identity, role, mode, decoded, related_structs),
                "subsystem": infer_subsystem(source_identity["human_name"], target_identity.get("human_name", ""), role),
                "related_structs": related_structs,
                "related_constant": constant,
                "source_constants": source_constants(location, target_address),
                "related_asset": asset,
                "confidence": confidence,
                "evidence": evidence,
            }
            edges.append(edge)
            outgoing[source_address].append(edge_id)
            if target_address:
                target_key = target["address"] if target_kind == "function" else target_address
                incoming[target_key].append(edge_id)

    edge_by_id = {edge["id"]: edge for edge in edges}
    if len(edge_by_id) != len(edges):
        raise RuntimeError("semantic edge-id collision")
    function_summary = []
    call_targets = {
        edge["target"]["address"] for edge in edges
        if edge["edge_kind"] == "call"
    }
    all_function_addresses = sorted(
        set(outgoing) | call_targets,
        key=lambda address: int(address, 16),
    )
    for address in all_function_addresses:
        identity = functions.identity(address)
        outgoing_edges = outgoing.get(address, [])
        incoming_edges = incoming.get(address, [])
        roles = Counter(edge_by_id[edge_id]["inferred_role"] for edge_id in outgoing_edges)
        function_summary.append({
            **identity,
            "subsystem": infer_subsystem(identity["human_name"]),
            "outgoing_edge_ids": outgoing_edges,
            "incoming_edge_ids": incoming_edges,
            "outgoing_count": len(outgoing_edges),
            "incoming_count": len(incoming_edges),
            "outgoing_roles": dict(sorted(roles.items())),
        })

    role_counts = Counter(edge["inferred_role"] for edge in edges)
    kind_counts = Counter(edge["target_kind"] for edge in edges)
    access_counts = Counter(edge["access_mode"] for edge in edges)
    confidence_counts = Counter(edge["confidence"] for edge in edges)
    subsystem_counts = Counter(edge["subsystem"] for edge in edges)
    summary = {
        "edges": len(edges),
        "call_edges": sum(edge["edge_kind"] == "call" for edge in edges),
        "data_edges": sum(edge["edge_kind"] == "data_reference" for edge in edges),
        "functions_with_edges": len(function_summary),
        "unique_address_targets": len(incoming),
        "edges_with_source_location": sum(bool(edge["source_location"]) for edge in edges),
        "edges_with_multiple_use_sites": sum(len((edge["source_location"] or {}).get("use_sites", [])) > 1 for edge in edges),
        "edges_with_struct_relation": sum(bool(edge["related_structs"]) for edge in edges),
        "edges_with_constant": sum(bool(edge.get("related_constant")) for edge in edges),
        "asset_candidates": sum(bool(edge.get("related_asset")) for edge in edges),
        "by_role": dict(sorted(role_counts.items())),
        "by_target_kind": dict(sorted(kind_counts.items())),
        "by_access_mode": dict(sorted(access_counts.items())),
        "by_confidence": dict(sorted(confidence_counts.items())),
        "by_subsystem": dict(sorted(subsystem_counts.items())),
    }
    payload = {
        "schema": 1,
        "core": "app",
        "purpose": "viewer-ready semantic enrichment of durable Ghidra call/data-reference edges",
        "method": {
            "ground_truth": "edge existence comes only from refgraph_app.json.gz",
            "inference_boundary": "roles/access/meaning are conservative presentation metadata, not new parity claims",
            "source_locations": "readable reconstructed C when available; Ghidra decompilation otherwise",
            "confidence": {
                "high": "line/object/string/layout evidence directly supports the role",
                "medium": "mapped address range or durable symbol supports the role",
                "low": "range/shape heuristic only; viewer should show as inferred",
            },
        },
        "edge_schema": {
            "source": "canonical address plus human/raw function identity and ownership category",
            "target": "referenced/canonical address, human/raw identity, target kind, owner/object context",
            "source_location": "path, line, primary snippet, and bounded concrete use_sites when found",
            "access_mode": "primary mode; access_modes retains all observed read/write/call/address/index modes",
            "inferred_role": "grounded semantic role shown by the viewer",
            "meaning": "plain-language explanation of this source-to-target edge",
            "relations": "related_structs, related_constant, source_constants, and related_asset",
            "confidence_evidence": "confidence plus the evidence list supporting classification",
        },
        "inputs": {
            str(path.relative_to(ROOT)): file_sha256(path)
            for path in (NAMES, ADDRESS_NAMES, REFGRAPH, FUNCTIONS, READABLE_MANIFEST, STRUCT_CATALOG, FIRMWARE)
        },
        "summary": summary,
        "functions": function_summary,
        "edges": edges,
        "indices": {
            "by_source": dict(sorted(outgoing.items())),
            "by_target": dict(sorted(incoming.items())),
        },
    }
    output.parent.mkdir(parents=True, exist_ok=True)
    temporary = output.with_suffix(output.suffix + ".tmp")
    temporary.write_text(json.dumps(payload, indent=2, ensure_ascii=False) + "\n")
    temporary.replace(output)
    return payload


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    args = parser.parse_args()
    output = args.output if args.output.is_absolute() else ROOT / args.output
    payload = build(output)
    try:
        output_label = str(output.relative_to(ROOT))
    except ValueError:
        output_label = str(output)
    print(json.dumps({"output": output_label, **payload["summary"]}, indent=2))


if __name__ == "__main__":
    main()
