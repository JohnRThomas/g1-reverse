#!/usr/bin/env python3
"""Build an evidence-rich CPUAPP constant/data catalog for the local viewer.

Run from outside the repository with PYTHONSAFEPATH=1.  The project root contains
``struct.py`` which otherwise shadows Python's standard-library module.

This is intentionally a presentation/evidence pass.  It does not rewrite any
parity-authoritative reconstruction.
"""

from __future__ import annotations

import bisect
import gzip
import json
import re
from collections import Counter, defaultdict
from datetime import datetime, timezone
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
READABLE = ROOT / "recon/readable_sources/app"
SYMBOLS_H = ROOT / "recon/symbols/g1_app_symbols.h"
DATA_DIR = ROOT / "recon/data"
STRUCTS = ROOT / "recon/structs/struct_catalog_app.json"
REFGRAPH = ROOT / "recon/catalogs/refgraph_app.json.gz"
APP_BIN = ROOT / "app_update.bin"
OUT_DIR = ROOT / "recon/viewer_sweep"
CATALOG_OUT = OUT_DIR / "constants_catalog_app.json"
REPORT_OUT = OUT_DIR / "constants_report.json"
APP_LINK_BASE = 0xC200
APP_FILE_BASE = 512

ADDR_RE = re.compile(r"0x[0-9a-fA-F]+")
PROV_RE = re.compile(r"/\*=\s*(0x[0-9a-fA-F]+)\s*\*/")
IDENT_RE = re.compile(r"\b[A-Za-z_]\w*\b")


def load_json(path: Path):
    with path.open("r", encoding="utf-8") as f:
        return json.load(f)


def load_json_gz(path: Path):
    with gzip.open(path, "rt", encoding="utf-8") as f:
        return json.load(f)


def hx(value: int) -> str:
    return f"0x{value:08x}"


def bounded(text: str, limit: int = 300) -> str:
    return " ".join(text.strip().split())[:limit]


def evidence(source: str, line: int | None, excerpt: str, kind: str) -> dict:
    return {
        "source": source,
        "line": line,
        "excerpt": bounded(excerpt),
        "kind": kind,
    }


def subsystem_for(words: str) -> str:
    s = words.lower()
    rules = [
        ("audio_codec", ("lc3", "audio", "mic", "dmic", "pdm", "i2s", "fir", "twiddle")),
        ("display_ui", ("display", "projector", "panel", "glyph", "font", "canvas", "dashboard", "pixel", "image", "icon")),
        ("bluetooth", ("ble", "gatt", "att_", "l2cap", "smp", "hci", "bt_", "ancs")),
        ("g1_protocol", ("esb", "ipc", "rpmsg", "transport", "packet", "command", "protocol")),
        ("sensors_motion", ("imu", "fusion", "accel", "gyro", "opt300", "lux", "motion")),
        ("storage_settings", ("flash", "nvs", "settings", "fs_", "file", "qspi", "nvmc")),
        ("input", ("touch", "key", "click", "button", "gesture")),
        ("power", ("battery", "fuel", "regulator", "power", "charger")),
        ("crypto", ("aes", "sha", "md5", "crypto", "ecdh", "p256", "tinycrypt")),
        ("radio_nfc", ("nfc", "st25", "radio")),
        ("kernel_runtime", ("k_", "zephyr", "work", "thread", "queue", "sem", "mutex", "libc", "newlib")),
    ]
    for name, needles in rules:
        if any(n in s for n in needles):
            return name
    return "cross_cutting_or_unknown"


def function_ref(row: dict) -> dict:
    return {
        "name": row["public_name"],
        "raw": row["raw_symbol"],
        "address": row["address"],
        "source": row["output"],
        "ownership": row["category"],
    }


def parse_symbol_header() -> tuple[list[dict], list[dict], dict[int, list[str]]]:
    text = SYMBOLS_H.read_text(encoding="utf-8")
    mmio = []
    for line_no, line in enumerate(text.splitlines(), 1):
        m = re.match(r"#define\s+(\w+)\s+(0x[0-9a-fA-F]+)UL", line)
        if m and int(m.group(2), 16) >= 0x40000000:
            mmio.append({"name": m.group(1), "address": int(m.group(2), 16), "line": line_no, "excerpt": line})

    globals_ = []
    addr_names: dict[int, list[str]] = defaultdict(list)
    in_ram = False
    for line_no, line in enumerate(text.splitlines(), 1):
        if "RAM globals / kernel objects" in line:
            in_ram = True
        elif "rodata table externs" in line:
            in_ram = False
        m = re.match(r"extern\s+(.+?)\s+([A-Za-z_]\w*)(\[\])?;\s*/\*\s*@\s*(0x[0-9a-fA-F]+)", line)
        if not m:
            continue
        typ, name, arr, addr_s = m.groups()
        address = int(addr_s, 16)
        addr_names[address].append(name)
        if in_ram:
            globals_.append({
                "name": name,
                "type": typ.strip() + ("[]" if arr else ""),
                "address": address,
                "line": line_no,
                "excerpt": line,
            })
    return mmio, globals_, addr_names


def parse_data_file(path: Path, addr_names: dict[int, list[str]]) -> dict | None:
    text = path.read_text(encoding="utf-8")
    address_m = re.search(r"(?:VA|@)\s*(0x[0-9a-fA-F]+)", text[:1000])
    if not address_m:
        address_m = re.search(r"(?:rodata_|litpool_)(?:0x)?([0-9a-fA-F]+)", path.name)
        address = int(address_m.group(1), 16) if address_m else None
    else:
        address = int(address_m.group(1), 16)
    if address is None:
        return None

    comment_m = re.match(r"\s*/\*(.*?)\*/", text, re.S)
    comment = bounded(comment_m.group(1), 800) if comment_m else ""
    decls = []
    total_size = 0
    type_sizes = {"uint8_t": 1, "int8_t": 1, "char": 1, "unsigned char": 1,
                  "uint16_t": 2, "int16_t": 2, "uint32_t": 4, "int32_t": 4,
                  "unsigned int": 4, "int": 4, "float": 4, "double": 8}
    for m in re.finditer(r"const\s+([A-Za-z_][\w ]*?)\s+([A-Za-z_]\w*)\[(\d+)\]\s*=", text):
        typ, name, count_s = m.groups()
        typ = " ".join(typ.split())
        count = int(count_s)
        size = type_sizes.get(typ, 1) * count
        total_size += size
        decls.append({"type": typ, "name": name, "count": count, "size": size})
    span_matches = [
        re.search(r"\bspan\s*=\s*(\d+)\s*bytes", comment, re.I),
        re.search(r"\b(\d+)\s*bytes\b", comment, re.I),
    ]
    for sm in span_matches:
        if sm:
            total_size = int(sm.group(1))
            break
    if total_size <= 0:
        return None

    off = address - APP_LINK_BASE + APP_FILE_BASE
    blob = APP_BIN.read_bytes()[off:off + total_size] if off >= 0 else b""
    strings = []
    for part in blob.split(b"\0"):
        if len(part) >= 4 and all(b in (9, 10, 13) or 32 <= b < 127 for b in part):
            strings.append(part.decode("ascii", errors="replace"))
    values = re.findall(r"(?<![\w])(?:0x[0-9a-fA-F]+|-?\d+)(?![\w])", text[text.find("{"):] if "{" in text else "")
    range_names = [name for sym_addr, names in addr_names.items() if address <= sym_addr < address + total_size for name in names]
    low = (comment + " " + " ".join(range_names)).lower()
    # Pointer-table comments routinely say "flash rodata/string ptrs"; that
    # describes their targets, not the table itself.  Require an actual pool
    # label or a named string symbol before choosing the string viewer.
    if "string pool" in low or any("string" in name.lower() for name in range_names if not name.startswith("rodata_")):
        asset_type = "string_pool"
    elif any(k in low for k in ("fir", "filter coefficient", "twiddle", "window")):
        asset_type = "signal_coefficients"
    elif any(k in low for k in ("float coefficient", "polynomial coefficient", "numeric constant")):
        asset_type = "numeric_table"
    elif "function/handler pointer" in low:
        asset_type = "dispatch_table"
    elif "pointer" in low or "literal pool" in low:
        asset_type = "pointer_table"
    elif any(k in low for k in ("lc3", "md5", "aes", "crypto")):
        asset_type = "algorithm_table"
    elif any(k in low for k in ("image", "bitmap", "glyph", "font", "icon")):
        asset_type = "visual_asset"
    else:
        asset_type = "byte_blob"
    symbol_names = range_names
    preferred = next((n for n in symbol_names if not n.startswith("rodata_")), decls[0]["name"] if decls else f"rodata_{address:x}")
    raw = next((n for n in symbol_names if n.startswith("rodata_")), f"DAT_{address:08x}")
    meaning = comment or f"Immutable CPUAPP data at {hx(address)}."
    return {
        "path": str(path.relative_to(ROOT)), "text": text, "address": address,
        "size": total_size, "decls": decls, "symbol": preferred, "raw": raw,
        "aliases": symbol_names, "comment": comment, "asset_type": asset_type,
        "blob_hex": blob[:128].hex(), "strings": strings[:24], "values": values[:96],
        "meaning": meaning,
    }


def classify_access(line: str, token: str) -> str:
    clean = line.split("//", 1)[0]
    pos = clean.find(token)
    if pos < 0:
        return "reference"
    tail = clean[pos + len(token):]
    head = clean[:pos]
    if re.search(r"(?:\+\+|--)", head[-3:] + tail[:3]):
        return "read_write"
    if re.match(r"\s*(?:\[[^]]*\]\s*)?(?:=|\+=|-=|\|=|&=|\^=)", tail):
        return "write" if re.match(r"\s*(?:\[[^]]*\]\s*)?=", tail) else "read_write"
    return "read"


def main() -> None:
    manifest = load_json(READABLE / "manifest.json")
    functions = manifest["sources"]
    by_address = {int(row["address"], 16): row for row in functions}
    by_raw = {row["raw_symbol"]: row for row in functions}
    mmio_defs, globals_defs, addr_names = parse_symbol_header()
    data_defs = [d for p in sorted(DATA_DIR.glob("*.c")) if (d := parse_data_file(p, addr_names))]
    data_starts = sorted(d["address"] for d in data_defs)
    data_by_start = {d["address"]: d for d in data_defs}

    def data_at(address: int) -> dict | None:
        idx = bisect.bisect_right(data_starts, address) - 1
        if idx < 0:
            return None
        item = data_by_start[data_starts[idx]]
        return item if address < item["address"] + item["size"] else None

    structs = load_json(STRUCTS)["structs"]
    structs_by_base: dict[int, list[dict]] = defaultdict(list)
    structs_by_func: dict[int, list[dict]] = defaultdict(list)
    for st in structs:
        brief = {"cid": st["cid"], "name": st["struct_name"], "purpose": st["purpose"], "confidence": st["confidence"]}
        for member in st.get("members", []):
            base = member.get("base", "")
            if isinstance(base, str) and ADDR_RE.fullmatch(base):
                structs_by_base[int(base, 16)].append(brief)
            entry = member.get("entry", "")
            if isinstance(entry, str) and ADDR_RE.fullmatch(entry):
                structs_by_func[int(entry, 16)].append(brief)

    # One pass over readable sources builds name/address access evidence.
    known_names = {g["name"] for g in globals_defs} | {m["name"] for m in mmio_defs}
    accesses: dict[tuple[str, int], list[dict]] = defaultdict(list)
    address_accesses: dict[int, list[dict]] = defaultdict(list)
    for row in functions:
        path = ROOT / row["output"]
        if not path.exists():
            continue
        for line_no, line in enumerate(path.read_text(encoding="utf-8", errors="replace").splitlines(), 1):
            identifiers = known_names.intersection(IDENT_RE.findall(line))
            for name in identifiers:
                accesses[(name, int(row["address"], 16))].append({"line": line_no, "text": line, "mode": classify_access(line, name)})
            for address_s in PROV_RE.findall(line):
                address_accesses[int(address_s, 16)].append({"function": row, "line": line_no, "text": line, "mode": "read"})

    refgraph = load_json_gz(REFGRAPH)["functions"]
    graph_refs: dict[int, set[int]] = defaultdict(set)
    for entry_s, node in refgraph.items():
        entry = int(entry_s, 16)
        for ref_s in node.get("data_refs", []):
            try:
                ref = int(ref_s, 16)
            except ValueError:
                continue
            if ref >= 0:
                graph_refs[ref].add(entry)

    by_public = {row["public_name"]: row for row in functions}

    records = []

    def parties_for_name(name: str):
        producers, consumers, ev = {}, {}, []
        modes = Counter()
        for (sym, func_addr), hits in accesses.items():
            if sym != name:
                continue
            row = by_address[func_addr]
            for hit in hits:
                modes[hit["mode"]] += 1
                if hit["mode"] in ("write", "read_write"):
                    producers[func_addr] = function_ref(row)
                if hit["mode"] in ("read", "read_write", "reference"):
                    consumers[func_addr] = function_ref(row)
                if len(ev) < 6:
                    ev.append(evidence(row["output"], hit["line"], hit["text"], f"source_{hit['mode']}"))
        return list(producers.values()), list(consumers.values()), dict(modes), ev

    for d in mmio_defs:
        prod, cons, modes, ev = parties_for_name(d["name"])
        meaning = f"Memory-mapped peripheral register/base {d['name']}; behavior is determined by its named producer/consumer functions."
        records.append({
            "id": f"mmio:{d['name']}", "category": "mmio_constant", "asset_type": "register",
            "symbol": {"name": d["name"], "raw": f"REG_{d['address']:08x}", "address": hx(d["address"]), "aliases": []},
            "range": {"start": hx(d["address"]), "end_exclusive": hx(d["address"] + 4), "size": 4, "address_semantics": "physical MMIO address"},
            "subsystem": subsystem_for(d["name"] + " " + " ".join(x["name"] for x in prod + cons)),
            "defining_source": str(SYMBOLS_H.relative_to(ROOT)), "producers": prod, "consumers": cons,
            "access_pattern": {"mutability": "hardware_register", "observed": modes},
            "value": {"type": "uintptr_t/register address", "endianness": "little-endian register accesses on Cortex-M33", "decoded": hx(d["address"]), "raw_preview_hex": d["address"].to_bytes(4, "little").hex()},
            "semantic_meaning": meaning, "related": {"structs": structs_by_base.get(d["address"], []), "protocols": [], "assets": []},
            "confidence": {"level": "high" if not d["name"].startswith("REG_") else "medium", "basis": "generated symbol header; semantic specificity follows symbol quality"},
            "evidence": [evidence(str(SYMBOLS_H.relative_to(ROOT)), d["line"], d["excerpt"], "definition"), *ev],
        })

    for g in globals_defs:
        prod, cons, modes, ev = parties_for_name(g["name"])
        related_structs = structs_by_base.get(g["address"], [])
        actors = prod + cons
        actor_names = ", ".join(x["name"] for x in actors[:4])
        specific = not re.match(r"g_(?:200)?[0-9a-f]+$", g["name"])
        meaning = f"Runtime CPUAPP state `{g['name']}`"
        if actor_names:
            meaning += f" used by {actor_names}"
        if related_structs:
            meaning += f" and serving as the base of {related_structs[0]['name']}"
        meaning += "."
        records.append({
            "id": f"global:{g['name']}", "category": "runtime_global", "asset_type": "mutable_state",
            "symbol": {"name": g["name"], "raw": f"DAT_{g['address']:08x}", "address": hx(g["address"]), "aliases": addr_names.get(g["address"], [])},
            "range": {"start": hx(g["address"]), "end_exclusive": None, "size": None, "address_semantics": "SRAM object; exact extent may be supplied by a related recovered layout"},
            "subsystem": subsystem_for(g["name"] + " " + actor_names), "defining_source": str(SYMBOLS_H.relative_to(ROOT)),
            "producers": prod, "consumers": cons, "access_pattern": {"mutability": "runtime_mutable", "observed": modes},
            "value": {"type": g["type"], "endianness": "little-endian for multi-byte scalar accesses", "decoded": "runtime value; initial value not established by this catalog", "raw_preview_hex": None},
            "semantic_meaning": meaning, "related": {"structs": related_structs, "protocols": [], "assets": []},
            "confidence": {"level": "high" if specific and (actors or related_structs) else "medium" if specific else "low", "basis": "named global plus observed source accesses; generic address names remain unresolved"},
            "evidence": [evidence(str(SYMBOLS_H.relative_to(ROOT)), g["line"], g["excerpt"], "definition"), *ev],
        })

    for d in data_defs:
        start, end = d["address"], d["address"] + d["size"]
        faddrs: set[int] = set()
        src_ev = []
        for ref, fs in graph_refs.items():
            if start <= ref < end:
                faddrs.update(fs)
        for ref, hits in address_accesses.items():
            if start <= ref < end:
                for hit in hits:
                    faddrs.add(int(hit["function"]["address"], 16))
                    if len(src_ev) < 6:
                        src_ev.append(evidence(hit["function"]["output"], hit["line"], hit["text"], "source_read"))
        consumers = [function_ref(by_address[a]) for a in sorted(faddrs) if a in by_address]
        # Reader(s) comments predate some refgraph/name-map updates but remain useful
        # direct evidence, especially for the 45 tables without a graph edge.
        reader_m = re.search(r"Reader\(s\):\s*([^*\n]+)", d["comment"], re.I)
        if reader_m:
            existing = {x["address"] for x in consumers}
            for reader_name in re.split(r"[, ]+", reader_m.group(1).strip()):
                row = by_raw.get(reader_name) or by_public.get(reader_name)
                if row and row["address"] not in existing:
                    consumers.append(function_ref(row)); existing.add(row["address"])
        related_structs = []
        seen_cids = set()
        for a in faddrs:
            for st in structs_by_func.get(a, []):
                if st["cid"] not in seen_cids:
                    seen_cids.add(st["cid"]); related_structs.append(st)
        subsystem = subsystem_for(d["symbol"] + " " + d["comment"] + " " + " ".join(x["name"] for x in consumers))
        visualizer = {
            "string_pool": "string_table", "signal_coefficients": "coefficient_plot",
            "numeric_table": "numeric_plot", "dispatch_table": "pointer_graph",
            "pointer_table": "pointer_graph", "algorithm_table": "numeric_table",
            "visual_asset": "bitmap_or_glyph", "byte_blob": "hex_ascii",
        }[d["asset_type"]]
        pointer_targets = []
        related_assets = []
        seen_assets = set()
        if d["asset_type"] in ("pointer_table", "dispatch_table"):
            raw = bytes.fromhex(d["blob_hex"])
            for offset in range(0, len(raw) - 3, 4):
                target = int.from_bytes(raw[offset:offset + 4], "little")
                target_func = by_address.get(target & ~1)
                target_data = data_at(target)
                if target_func:
                    decoded = {"offset": offset, "value": hx(target), "kind": "function", "target": function_ref(target_func)}
                elif target_data:
                    asset_id = f"data:{target_data['address']:08x}"
                    decoded = {"offset": offset, "value": hx(target), "kind": "builtin_data", "target": {"id": asset_id, "name": target_data["symbol"], "address": hx(target_data["address"]), "interior_offset": target - target_data["address"]}}
                    if asset_id not in seen_assets:
                        seen_assets.add(asset_id); related_assets.append(decoded["target"])
                elif 0x20000000 <= target < 0x30000000:
                    decoded = {"offset": offset, "value": hx(target), "kind": "sram", "target": {"name": (addr_names.get(target) or [None])[0], "address": hx(target)}}
                elif target >= 0x40000000:
                    decoded = {"offset": offset, "value": hx(target), "kind": "mmio", "target": {"name": (addr_names.get(target) or [None])[0], "address": hx(target)}}
                elif APP_LINK_BASE <= target < 0x01000000:
                    decoded = {"offset": offset, "value": hx(target), "kind": "flash", "target": {"name": (addr_names.get(target) or [None])[0], "address": hx(target)}}
                else:
                    decoded = {"offset": offset, "value": hx(target), "kind": "immediate_or_null", "target": None}
                pointer_targets.append(decoded)
        specific = not d["symbol"].startswith(("rodata_", "litpool_"))
        first_lines = "\n".join(d["text"].splitlines()[:8])
        meaning = d["meaning"]
        if consumers:
            meaning += " Behavioral consumers: " + ", ".join(x["name"] for x in consumers[:6]) + "."
        records.append({
            "id": f"data:{start:08x}", "category": "builtin_data", "asset_type": d["asset_type"],
            "symbol": {"name": d["symbol"], "raw": d["raw"], "address": hx(start), "aliases": d["aliases"]},
            "range": {"start": hx(start), "end_exclusive": hx(end), "size": d["size"], "address_semantics": "CPUAPP linked flash virtual address"},
            "subsystem": subsystem, "defining_source": d["path"], "producers": [], "consumers": consumers,
            "access_pattern": {"mutability": "immutable", "observed": {"read": len(consumers)}, "viewer": visualizer},
            "value": {"type": d["decls"], "endianness": "little-endian for multi-byte elements; byte/string views preserve stored order", "decoded": {"strings": d["strings"], "scalar_tokens": d["values"], "pointer_targets": pointer_targets}, "raw_preview_hex": d["blob_hex"]},
            "semantic_meaning": meaning,
            "related": {"structs": related_structs[:16], "protocols": [p for p in ("BLE" if subsystem == "bluetooth" else "", "G1 IPC/ESB" if subsystem == "g1_protocol" else "", "LC3" if "lc3" in (d["symbol"] + d["comment"]).lower() else "") if p], "assets": related_assets},
            "confidence": {"level": "high" if specific or d["comment"] else "medium", "basis": "byte-verified recon/data definition, Ghidra refgraph, readable-source address provenance"},
            "evidence": [evidence(d["path"], 1, first_lines, "definition_and_decode"), *src_ev],
        })

    # Explicit enum and object-like macro constants are few and high-signal.
    constant_files = [p for p in (READABLE / "include").glob("*.h") if p.name != "g1_app_symbols.h"] + list((READABLE / "g1").glob("*.c"))
    for path in constant_files:
        rel = str(path.relative_to(ROOT))
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
        enum_name = None
        for line_no, line in enumerate(lines, 1):
            em = re.search(r"enum\s+(\w+)\s*\{", line)
            if em:
                enum_name = em.group(1)
                continue
            if enum_name and "}" in line:
                enum_name = None
                continue
            cm = re.match(r"\s*([A-Z][A-Z0-9_]+)\s*=\s*(-?(?:0x[0-9a-fA-F]+|\d+))\s*,?", line) if enum_name else None
            dm = re.match(r"\s*#define\s+([A-Z][A-Z0-9_]+)\s+(-?(?:0x[0-9a-fA-F]+|\d+)(?:[uUlL]*))\s*$", line)
            if not cm and not dm:
                continue
            name, val_s = (cm or dm).groups()
            clean_val = re.sub(r"[uUlL]+$", "", val_s)
            value = int(clean_val, 0)
            owner_m = next((re.search(r"@\s*(0x[0-9a-fA-F]+)", x) for x in lines[:18] if "@" in x), None)
            owner_addr = int(owner_m.group(1), 16) if owner_m else None
            owner = by_address.get(owner_addr) if owner_addr is not None else None
            records.append({
                "id": f"constant:{name}:{rel}:{line_no}", "category": "enum_constant" if cm else "macro_constant", "asset_type": "symbolic_constant",
                "symbol": {"name": name, "raw": name, "address": hx(owner_addr) if owner_addr is not None else None, "aliases": []},
                "range": {"start": hx(owner_addr) if owner_addr is not None else None, "end_exclusive": None, "size": None, "address_semantics": "compile-time value; address, when present, is the containing reconstructed function"},
                "subsystem": subsystem_for(name + " " + rel), "defining_source": rel,
                "producers": [], "consumers": [function_ref(owner)] if owner else [],
                "access_pattern": {"mutability": "compile_time_constant", "observed": {"definition": 1}},
                "value": {"type": enum_name or "integer macro", "endianness": "not applicable until serialized/stored", "decoded": value, "raw_preview_hex": None},
                "semantic_meaning": f"Symbolic {'member of '+enum_name if cm else 'macro'} `{name}` with value {value} ({hex(value) if value >= 0 else value}).",
                "related": {"structs": structs_by_func.get(owner_addr, []) if owner_addr is not None else [], "protocols": [], "assets": []},
                "confidence": {"level": "high", "basis": "explicit named C definition in readable source"},
                "evidence": [evidence(rel, line_no, line, "definition")],
            })

    category_counts = Counter(r["category"] for r in records)
    asset_counts = Counter(r["asset_type"] for r in records)
    subsystem_counts = Counter(r["subsystem"] for r in records)
    confidence_counts = Counter(r["confidence"]["level"] for r in records)
    records.sort(key=lambda r: (r["category"], r["symbol"]["address"] or "", r["id"]))
    generated_from = [str(p.relative_to(ROOT)) for p in (SYMBOLS_H, DATA_DIR, STRUCTS, REFGRAPH, READABLE / "manifest.json")]
    catalog = {
        "schema": "g1.viewer.constants.v1", "core": "app", "generated_at": datetime.now(timezone.utc).isoformat(),
        "generated_from": generated_from,
        "summary": {"records": len(records), "by_category": dict(category_counts), "by_asset_type": dict(asset_counts), "by_subsystem": dict(subsystem_counts), "by_confidence": dict(confidence_counts)},
        "records": records,
    }
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    CATALOG_OUT.write_text(json.dumps(catalog, indent=2) + "\n", encoding="utf-8")

    examples = {}
    for kind in ("mmio_constant", "runtime_global", "builtin_data", "enum_constant", "macro_constant"):
        examples[kind] = [r["id"] for r in records if r["category"] == kind][:8]
    report = {
        "schema": "g1.viewer.constants-report.v1", "core": "app",
        "catalog": str(CATALOG_OUT.relative_to(ROOT)),
        "catalog_files": [str(CATALOG_OUT.relative_to(ROOT))],
        "source_files": generated_from,
        "collector": str(Path(__file__).relative_to(ROOT)),
        "summary": catalog["summary"], "coverage": {
            "verified_data_sources_seen": len(data_defs), "generated_ram_globals_seen": len(globals_defs),
            "generated_mmio_definitions_seen": len(mmio_defs), "function_sources_indexed": len(functions),
            "ghidra_refgraph_functions": len(refgraph), "recovered_structs_available": len(structs),
        },
        "record_contract": {
            "identity": ["id", "category", "asset_type", "symbol", "range"],
            "meaning": ["subsystem", "semantic_meaning", "confidence"],
            "behavior": ["producers", "consumers", "access_pattern"],
            "decode": ["value.type", "value.endianness", "value.decoded", "value.raw_preview_hex"],
            "connections": ["related.structs", "related.protocols", "related.assets"],
            "provenance": ["defining_source", "evidence"],
        },
        "viewer_recommendations": {
            "string_pool": "NUL-separated searchable string table with offset, format-token highlighting, and consumer jumps.",
            "coefficient_plot": "Signed/float line plot plus table; permit width/channel reshaping but label it user-selected.",
            "pointer_graph": "Decode little-endian words into function, flash, SRAM, or MMIO targets and make each target GoToRef-enabled.",
            "bitmap_or_glyph": "Offer 1/2/4/8-bpp width controls, stride/endian toggles, and preserve an adjacent hex view because geometry is inferred.",
            "hex_ascii": "Synchronized address, hex, ASCII, integer, and float lanes with range selection.",
            "runtime_state": "Show read/write producers separately, related recovered layout, and every concrete source access excerpt.",
        },
        "decoding_policy": [
            "Never present inferred geometry, enum labels, units, or protocol fields as proven; attach confidence and evidence.",
            "Use recon/data as the byte-verified built-in data source and the linked firmware only for exact preview bytes.",
            "Use refgraph_app plus readable-source provenance for consumers; use C assignment context for producer/read/write classification.",
            "Treat address-only globals and REG_* MMIO names as unresolved even when their addresses are exact.",
        ],
        "examples": examples,
    }
    REPORT_OUT.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"catalog": str(CATALOG_OUT), "report": str(REPORT_OUT), **catalog["summary"]}, indent=2))


if __name__ == "__main__":
    main()
