#!/usr/bin/env python3
"""Build the CPUAPP string/rodata evidence catalog used by the viewer.

The catalog is deliberately reference-grounded: a byte sequence is accepted only
when Ghidra recorded a DATA reference to its start, it lies in the firmware's
read-only data region, and it is a valid NUL-terminated UTF-8 string.  This avoids
turning printable Thumb opcodes and literal-pool words into fictional strings.
"""

from __future__ import annotations

import gzip
import json
import re
from collections import Counter, defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
CATALOGS = ROOT / "recon" / "catalogs"
OUT = ROOT / "recon" / "viewer_sweep" / "string_assets_report.json"
APP_BASE = 0xC200
MCUBOOT_HEADER = 512
# The linked .text ends immediately before this observed immutable-data band.
# Lower exact DATA refs which happen to decode are Thumb/literal-pool accidents.
RODATA_START = 0x98000

FORMAT_RE = re.compile(
    r"%(?:[-+ #0']*)(?:\d+|\*)?(?:\.(?:\d+|\*))?"
    r"(?:hh|h|ll|l|j|z|t|L)?[diuoxXfFeEgGaAcspn%]"
)
HEX_RE = re.compile(r"0x[0-9a-fA-F]+")
TOKEN_RE = re.compile(r"\b[A-Z][A-Z0-9]*(?:_[A-Z0-9]+)+\b")


def load_json(path: Path):
    opener = gzip.open if path.suffix == ".gz" else open
    with opener(path, "rt", encoding="utf-8") as handle:
        return json.load(handle)


def canonical(address: int) -> str:
    return f"0x{address:08x}"


def decode_cstring(blob: bytes, address: int):
    offset = address - APP_BASE + MCUBOOT_HEADER
    if offset < 0 or offset >= len(blob):
        return None, "outside_image"
    window = blob[offset : offset + 1024]
    terminator = window.find(b"\0")
    if terminator < 0:
        return None, "not_terminated"
    raw = window[:terminator]
    if len(raw) < 3:
        return None, "too_short"
    try:
        value = raw.decode("utf-8")
    except UnicodeDecodeError:
        return None, "invalid_utf8"
    if not all(char.isprintable() or char in "\r\n\t" for char in value):
        return None, "non_printable"
    if sum(char.isalnum() for char in value) < 2:
        return None, "no_semantic_text"
    return (raw, value), None


def display_name(name_map, address: int, raw_fallback: str):
    row = name_map.get(canonical(address), {})
    return row.get("display_name") or row.get("name") or raw_fallback


def subsystem_for(text: str, names: list[str]) -> str:
    haystack = (text + " " + " ".join(names)).lower()
    rules = (
        ("ui_display", r"dashboard|display|screen|gui_|draw_|render_|teleprompter|quicknote|navigation|onboard|bitmap|font"),
        ("bluetooth", r"\bble\b|\bbt_|gatt|hci|smp_|l2cap|ancs|bluetooth|uuid"),
        ("settings_storage", r"setting|flash|nvs|eeprom|storage|filesystem|fs_|mx25|qspi"),
        ("audio", r"audio|dmic|microphone|\bmic_|lc3|codec|pdm"),
        ("sensors_motion", r"imu|fusion|3dof|opt300|ambient|acceler|gyro"),
        ("ipc_radio", r"ipc|rpmsg|openamp|virtio|esb|slave|master"),
        ("power", r"power|battery|charge|pm_|suspend|resume"),
        ("security_crypto", r"aes|crypto|mbedtls|random|rnd|hash|security|key"),
        ("firmware_update", r"dfu|mcumgr|img_mgmt|upgrade|bootloader|mcuboot"),
        ("input", r"touch|click|key_event|button"),
        ("kernel_sdk", r"west_topdir|zephyr|nrfx|kernel|spinlock|mutex|sched|newlib|sys_heap"),
        ("protocol_serialization", r"json|cbor|packet|request|response|command|opcode|uart|spi|i2c"),
    )
    for name, pattern in rules:
        if re.search(pattern, haystack):
            return name
    return "application_general"


def protocols_for(text: str, names: list[str]) -> list[str]:
    haystack = (text + " " + " ".join(names)).lower()
    rules = (
        ("ANCS", r"ancs|ncs_notification|app_identifier"),
        ("Bluetooth LE", r"\bble\b|\bbt_|bluetooth|gatt|hci|smp_|l2cap"),
        ("GATT", r"gatt|characteristic|ccc"),
        ("HCI", r"\bhci\b|hci_"),
        ("SMP", r"\bsmp\b|smp_|pairing"),
        ("L2CAP", r"l2cap"),
        ("ESB", r"\besb\b"),
        ("OpenAMP/RPMsg", r"rpmsg|openamp|virtio"),
        ("Zephyr IPC", r"\bipc\b|ipc_"),
        ("MCUmgr/DFU", r"mcumgr|img_mgmt|\bdfu\b"),
        ("JSON/cJSON", r"json|cjson"),
        ("CBOR", r"cbor"),
        ("UART", r"uart|uarte"),
        ("SPI", r"\bspi\b|spim|qspi"),
        ("I2C/TWI", r"\bi2c\b|twim|twi_"),
        ("LC3", r"\blc3\b"),
        ("Zephyr settings", r"settings|nvs"),
        ("G1 display event bus", r"(?:imu|ble):wakeup:|imu-trigger-|goto (?:idle|suspend)"),
    )
    return [name for name, pattern in rules if re.search(pattern, haystack)]


def looks_like_simple_key(value: str) -> bool:
    return bool(re.fullmatch(r"[A-Za-z][A-Za-z0-9_.-]{1,63}", value))


def category_for(value: str, function_names: list[str]):
    low = value.lower()
    fn = " ".join(function_names).lower()
    placeholders = [item for item in FORMAT_RE.findall(value) if item != "%%"]
    if low.startswith("west_topdir/") or "/src/" in low or re.search(r"\.(?:c|h)$", low):
        return "source_path", "build_source_path"
    if "assertion fail" in low or "assert" in low or " != " in value or " == " in value:
        return "assertion", "runtime_invariant"
    if ("json" in fn or "cjson" in fn) and looks_like_simple_key(value):
        return "structured_key", "json_object_key"
    if ("setting" in fn or "nvs" in fn) and ("/" in value or looks_like_simple_key(value)):
        return "settings_key", "persistent_storage_key"
    if re.match(r"(?:com\.|org\.|net\.)", value) or "@" in value and " " not in value:
        return "identifier", "package_or_device_identifier"
    if re.search(r"\b(?:BLE|IMU|ESB|GATT|HCI|SMP|L2CAP|IPC|DFU)[_:]", value, re.I) or TOKEN_RE.search(value):
        return "protocol_label", "event_or_command_label"
    if re.search(r"gui_|draw_|render_|dashboard|teleprompter|onboard|screen", fn) and not placeholders and "\n" not in value:
        return "ui_text", "rendered_copy"
    if re.search(r"\b\d{4}-\d{2}-\d{2}\b|\bv?\d+\.\d+(?:\.\d+)?\b", value):
        return "build_metadata", "version_date_or_build_marker"
    if placeholders:
        return "format_string", "printf_style_template"
    if "\n" in value or "\r" in value or re.search(r"log|debug|print|error|fail|warn", fn + " " + low):
        return "diagnostic", "log_or_error_message"
    if looks_like_simple_key(value):
        return "plain_label", "symbolic_label"
    return "text", "embedded_text"


def meaning_for(value, category, role, subsystem, function_names):
    preview = value.replace("\r", "\\r").replace("\n", "\\n")
    if len(preview) > 96:
        preview = preview[:93] + "..."
    owner = function_names[0] if function_names else "unknown code"
    templates = {
        "source_path": f"Build-time source location retained for assertions or diagnostics in {owner}.",
        "assertion": f"Runtime invariant text used to explain a failed safety check in the {subsystem} subsystem.",
        "structured_key": f"Structured-data object key `{value}` looked up or emitted by {owner}.",
        "settings_key": f"Persistent settings key/path `{value}` used by {owner}.",
        "identifier": f"Stable external package, device, or resource identifier `{value}` recognized by {owner}.",
        "protocol_label": f"Named event, command, or protocol marker `{preview}` used by {owner}.",
        "ui_text": f"User-visible copy rendered by {owner}: “{preview}”.",
        "build_metadata": f"Firmware build/version metadata consumed by {owner}: `{preview}`.",
        "format_string": f"Printf-style diagnostic or serialization template used by {owner}; placeholders define its runtime values.",
        "diagnostic": f"Diagnostic/status message emitted or checked by {owner}: “{preview}”.",
        "plain_label": f"Symbolic label `{value}` used by {owner} in the {subsystem} subsystem.",
        "text": f"Embedded immutable text referenced by {owner}: “{preview}”.",
    }
    return templates[category]


def use_role(category: str, function_name: str, source_lines: list[dict]) -> str:
    joined = " ".join(item["excerpt"] for item in source_lines).lower()
    name = function_name.lower()
    if category == "ui_text" or re.search(r"gui_utf_draw|draw_|render_", joined + name):
        return "display_renderer"
    if category == "structured_key" or re.search(r"find_by_name|cjson", joined + name):
        return "structured_data_lookup"
    if category == "settings_key" or "setting" in name:
        return "persistent_storage_lookup"
    if category in {"format_string", "diagnostic", "assertion", "source_path"}:
        return "diagnostic_consumer"
    if category in {"protocol_label", "identifier"} or re.search(r"send|packet|request|response", name):
        return "protocol_consumer"
    return "read_only_consumer"


def build_source_index(addresses: set[int]):
    refs = defaultdict(list)
    source_root = ROOT / "recon" / "readable_sources" / "app"
    for path in source_root.rglob("*"):
        if not path.is_file() or path.suffix not in {".c", ".h", ".inc"}:
            continue
        try:
            lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
        except OSError:
            continue
        for line_number, line in enumerate(lines, 1):
            values = {int(item, 16) for item in HEX_RE.findall(line)}
            for address in values & addresses:
                stripped = line.strip()
                if "/*=" in line:
                    kind = "code_reference"
                elif stripped.startswith("*") or stripped.startswith("//"):
                    kind = "provenance_inventory"
                elif "extern" in stripped:
                    kind = "symbol_declaration"
                else:
                    kind = "raw_address_reference"
                refs[address].append(
                    {
                        "path": str(path.relative_to(ROOT)),
                        "line": line_number,
                        "kind": kind,
                        "excerpt": stripped[:300],
                    }
                )
    for address in refs:
        refs[address].sort(key=lambda item: (item["kind"] != "code_reference", item["path"], item["line"]))
        refs[address] = refs[address][:16]
    return refs


def build_struct_index():
    result = defaultdict(list)
    path = ROOT / "recon" / "structs" / "struct_catalog_app.json"
    if not path.exists():
        return result
    for record in load_json(path).get("structs", []):
        summary = {
            "cid": record.get("cid"),
            "name": record.get("struct_name"),
            "kind": record.get("kind"),
            "is_library": bool(record.get("is_library")),
            "field_count": len(record.get("fields", [])),
            "relation": "referencing_function_accesses_this_recovered_layout",
        }
        for member in record.get("members", []):
            try:
                entry = int(str(member.get("entry")), 0)
            except (TypeError, ValueError):
                continue
            if summary not in result[entry]:
                result[entry].append(summary)
    return result


def main():
    blob = (ROOT / "app_update.bin").read_bytes()
    graph_doc = load_json(CATALOGS / "refgraph_app.json.gz")
    graph = graph_doc["functions"]
    names = load_json(CATALOGS / "function_names_app.json")["by_address"]
    symbols = load_json(CATALOGS / "address_names_app.json").get("by_address", {})
    classified_doc = load_json(CATALOGS / "classified.json.gz")
    classes = {int(row["entry"]): row for row in classified_doc.get("functions", [])}

    targets = defaultdict(set)
    decode_rejections = Counter()
    excluded_low = []
    decoded = {}
    for entry_hex, function in graph.items():
        entry = int(entry_hex, 16)
        for target_hex in function.get("data_refs", []):
            try:
                address = int(target_hex, 16)
            except ValueError:
                continue
            result, reason = decode_cstring(blob, address)
            if result is None:
                decode_rejections[reason] += 1
                continue
            if address < RODATA_START:
                excluded_low.append(address)
                continue
            decoded[address] = result
            targets[address].add(entry)

    source_index = build_source_index(set(decoded))
    struct_index = build_struct_index()
    function_assets = defaultdict(set)
    assets = []

    for address in sorted(decoded):
        raw, value = decoded[address]
        file_offset = address - APP_BASE + MCUBOOT_HEADER
        prior_nul = blob.rfind(b"\0", max(0, file_offset - 1024), file_offset)
        object_file_offset = prior_nul + 1 if prior_nul >= 0 else file_offset
        object_start = object_file_offset + APP_BASE - MCUBOOT_HEADER
        interior_offset = file_offset - object_file_offset
        # Padding and arbitrary preceding binary data can also contain a NUL.
        # Accept the enclosing-object interpretation only when its whole prefix
        # is valid printable UTF-8; otherwise this DATA ref is the best-known start.
        if interior_offset:
            try:
                prefix_value = blob[object_file_offset:file_offset].decode("utf-8")
            except UnicodeDecodeError:
                prefix_value = ""
            if not prefix_value or not all(char.isprintable() or char in "\r\n\t" for char in prefix_value):
                object_start = address
                interior_offset = 0
        function_entries = sorted(targets[address])
        fn_names = []
        referencers = []
        for entry in function_entries:
            graph_row = graph.get(hex(entry), {})
            raw_name = graph_row.get("name", f"FUN_{entry:08x}")
            name = display_name(names, entry, raw_name)
            fn_names.append(name)
            class_row = classes.get(entry, {})
            source_path = None
            for ref in source_index.get(address, []):
                if Path(ref["path"]).stem == name:
                    source_path = ref["path"]
                    break
            referencers.append(
                {
                    "address": canonical(entry),
                    "name": name,
                    "raw_name": raw_name,
                    "ownership": class_row.get("class", "UNKNOWN").lower(),
                    "viewer_route": f"#/app/{canonical(entry)}",
                    "source_path": source_path,
                }
            )

        category, structured_role = category_for(value, fn_names)
        subsystem = subsystem_for(value, fn_names)
        if category in {"source_path", "assertion"}:
            # Shared SDK assertion strings can have hundreds of unrelated users;
            # those users are not evidence that the string belongs to every
            # protocol represented in the call sites.
            protocols = protocols_for(value, [])
            subsystem = "kernel_sdk" if len(fn_names) > 8 or "west_topdir" in value.lower() else subsystem
        else:
            protocols = protocols_for(value, fn_names)
        placeholders = [item for item in FORMAT_RE.findall(value) if item != "%%"]
        constants = sorted(set(TOKEN_RE.findall(value)))[:16]
        source_refs = source_index.get(address, [])
        consumers = []
        for function in referencers:
            relevant = [
                item for item in source_refs
                if Path(item["path"]).stem == function["name"] and item["kind"] == "code_reference"
            ]
            consumers.append(
                {
                    **function,
                    "role": use_role(category, function["name"], relevant),
                    "evidence_lines": relevant[:4],
                }
            )

        symbol = symbols.get(canonical(address), {})
        symbol_name = symbol.get("name") or f"string_{address:x}"
        confidence_score = 0.72
        confidence_reasons = ["exact Ghidra DATA reference", "valid NUL-terminated UTF-8 in immutable-data address band"]
        if source_refs:
            confidence_score += 0.12
            confidence_reasons.append("address is present in regenerated readable source")
        if symbol:
            confidence_score += 0.08
            confidence_reasons.append("durable address-symbol back-map exists")
        if category not in {"text", "plain_label"}:
            confidence_score += 0.05
            confidence_reasons.append("usage/text pattern determines semantic category")
        confidence_score = min(confidence_score, 0.99)
        level = "high" if confidence_score >= 0.88 else "medium" if confidence_score >= 0.7 else "low"

        asset_id = f"app:string:{address:08x}"
        for entry in function_entries:
            function_assets[entry].add(asset_id)
        related_structs = []
        seen_structs = set()
        for entry in function_entries:
            for struct in struct_index.get(entry, []):
                key = struct["cid"]
                if key not in seen_structs:
                    related_structs.append({**struct, "via_function": canonical(entry)})
                    seen_structs.add(key)
        encoding = "ascii" if all(byte < 0x80 for byte in raw) else "utf-8"
        escaped = json.dumps(value, ensure_ascii=False)
        assets.append(
            {
                "id": asset_id,
                "asset_type": "string",
                "address": {
                    "canonical": canonical(address),
                    "start": address,
                    "end_exclusive": address + len(raw) + 1,
                    "length_bytes": len(raw),
                    "storage_bytes": len(raw) + 1,
                    "terminator": "00",
                    "storage_object_start": canonical(object_start),
                    "interior_offset": interior_offset,
                    "is_interior_reference": bool(interior_offset),
                },
                "symbol": {
                    "name": symbol_name,
                    "base_address": symbol.get("base_address", canonical(address)),
                    "offset": symbol.get("offset", 0),
                    "evidence": symbol.get("evidence", ["derived string_<address> fallback"]),
                    "back_map": canonical(address),
                },
                "decoded": {
                    "value": value,
                    "escaped": escaped,
                    "encoding": encoding,
                    "byte_hex": raw.hex(),
                    "exact": True,
                },
                "category": category,
                "subsystem": subsystem,
                "structured_role": structured_role,
                "meaning": meaning_for(value, category, structured_role, subsystem, fn_names),
                "confidence": {
                    "level": level,
                    "score": round(confidence_score, 2),
                    "rationale": confidence_reasons,
                },
                "evidence": [
                    {"kind": "ghidra_data_reference", "source": "recon/catalogs/refgraph_app.json.gz", "function_count": len(function_entries)},
                    {"kind": "firmware_bytes", "source": "app_update.bin", "file_offset": file_offset},
                    {"kind": "source_occurrences", "count": len(source_refs)},
                ],
                "format": {
                    "is_format": bool(placeholders),
                    "placeholders": placeholders,
                    "arity_lower_bound": len(placeholders),
                    "contains_escaped_percent": "%%" in value,
                },
                "protocols": protocols,
                "constants": constants,
                "functions": {
                    "referencers": referencers,
                    "consumers": consumers,
                    "producers": [],
                    "producer_note": "The asset is immutable firmware data; no writer/producer is evidenced by the reference graph.",
                },
                "source_references": source_refs,
                "related": {"structs": related_structs[:24], "assets": []},
                "viewer_hints": {
                    "primary_view": {
                        "ui_text": "localized_copy_preview",
                        "format_string": "format_template_inspector",
                        "structured_key": "schema_key_graph",
                        "settings_key": "settings_tree",
                        "protocol_label": "protocol_event_inspector",
                        "identifier": "identifier_registry",
                        "source_path": "sdk_provenance",
                        "assertion": "assertion_context",
                    }.get(category, "string_reference_inspector"),
                    "search_terms": sorted(set([symbol_name, category, subsystem, *protocols, *constants, *fn_names]))[:40],
                    "show_hex": encoding != "ascii" or category in {"protocol_label", "identifier"},
                    "preserve_whitespace": "\n" in value or "\r" in value or "\t" in value,
                },
            }
        )

    by_id = {asset["id"]: asset for asset in assets}
    by_address = {asset["address"]["start"]: asset for asset in assets}
    for asset in assets:
        entries = [int(item["address"], 16) for item in asset["functions"]["referencers"]]
        candidates = Counter()
        for entry in entries:
            for related_id in sorted(function_assets[entry]):
                if related_id != asset["id"]:
                    candidates[related_id] += 1
        start = asset["address"]["start"]
        for other_address, other in by_address.items():
            if other["id"] != asset["id"] and abs(other_address - start) <= 96:
                candidates[other["id"]] += 1
        related = []
        ranked_candidates = sorted(candidates.items(), key=lambda item: (-item[1], item[0]))[:10]
        for related_id, score in ranked_candidates:
            other = by_id[related_id]
            relations = []
            shared = sorted(
                set(item["address"] for item in asset["functions"]["referencers"])
                & set(item["address"] for item in other["functions"]["referencers"])
            )
            if shared:
                relations.append("co_referenced_by_function")
            if abs(other["address"]["start"] - start) <= 96:
                relations.append("adjacent_rodata")
            related.append(
                {
                    "id": related_id,
                    "address": other["address"]["canonical"],
                    "symbol": other["symbol"]["name"],
                    "category": other["category"],
                    "preview": other["decoded"]["value"][:100],
                    "relations": relations,
                    "shared_functions": shared,
                }
            )
        asset["related"]["assets"] = related

    categories = Counter(asset["category"] for asset in assets)
    subsystems = Counter(asset["subsystem"] for asset in assets)
    encodings = Counter(asset["decoded"]["encoding"] for asset in assets)
    high_confidence = sum(asset["confidence"]["level"] == "high" for asset in assets)
    report = {
        "schema": "g1-viewer-string-assets/v1",
        "core": "app",
        "generated_from": {
            "firmware": "app_update.bin",
            "reference_graph": "recon/catalogs/refgraph_app.json.gz",
            "function_names": "recon/catalogs/function_names_app.json",
            "address_symbols": "recon/catalogs/address_names_app.json",
            "readable_sources": "recon/readable_sources/app",
            "struct_catalog": "recon/structs/struct_catalog_app.json",
        },
        "coverage": {
            "definition": "Every valid NUL-terminated UTF-8 string at an exact Ghidra DATA-reference target in the observed CPUAPP immutable-data band.",
            "rodata_start": canonical(RODATA_START),
            "assets": len(assets),
            "ghidra_references_covered": sum(len(asset["functions"]["referencers"]) for asset in assets),
            "excluded_low_address_printable_sequences": len(set(excluded_low)),
            "excluded_low_address_reason": "Below the immutable-data band; inspection showed printable Thumb/literal-pool accidents rather than string objects.",
            "decode_rejections": dict(sorted(decode_rejections.items())),
            "limitations": [
                "Unreferenced byte runs are intentionally excluded because code bytes can look printable.",
                "UTF-16/binary-localization formats are handled by separate built-in-data sweeps, not this UTF-8 C-string catalog.",
                "A DATA reference identifies the containing function, not the exact machine-code instruction; regenerated source occurrences provide line evidence where available.",
            ],
        },
        "summary": {
            "asset_count": len(assets),
            "high_confidence": high_confidence,
            "with_durable_symbol_backmap": sum(not asset["symbol"]["name"].startswith("string_") for asset in assets),
            "with_source_references": sum(bool(asset["source_references"]) for asset in assets),
            "with_related_structs": sum(bool(asset["related"]["structs"]) for asset in assets),
            "format_strings": sum(asset["format"]["is_format"] for asset in assets),
            "interior_suffix_references": sum(asset["address"]["is_interior_reference"] for asset in assets),
            "encoding_counts": dict(encodings),
        },
        "categories": dict(categories.most_common()),
        "subsystem_counts": dict(subsystems.most_common()),
        "viewer_recommendations": [
            {"viewer": "localized_copy_preview", "for": ["ui_text"], "features": ["render preserved whitespace", "group adjacent/co-referenced strings as locale variants", "jump to renderer and related recovered layout"]},
            {"viewer": "format_template_inspector", "for": ["format_string", "diagnostic"], "features": ["highlight each printf placeholder", "show inferred argument arity", "list every emitting/reference function and source line"]},
            {"viewer": "schema_key_graph", "for": ["structured_key"], "features": ["group keys by parser/serializer", "show lookup versus emission role", "jump among sibling keys and related structs"]},
            {"viewer": "settings_tree", "for": ["settings_key"], "features": ["split slash-delimited paths", "group readers/writers", "show storage subsystem and defaults when the constants sweep provides them"]},
            {"viewer": "protocol_event_inspector", "for": ["protocol_label", "identifier"], "features": ["protocol badges", "consumer/send path", "co-referenced commands and constants", "raw UTF-8 bytes"]},
            {"viewer": "sdk_provenance", "for": ["source_path", "assertion"], "features": ["collapse stock-library noise by default", "show source/version ownership", "pair assertion text with its invariant and callers"]},
        ],
        "assets": assets,
    }
    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text(json.dumps(report, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(f"wrote {len(assets)} assets to {OUT}")
    print("categories", dict(categories.most_common()))


if __name__ == "__main__":
    main()
