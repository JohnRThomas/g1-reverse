#!/usr/bin/env python3
"""Build a standalone, fully named CPUAPP presentation source tree.

The parity corpus is deliberately immutable.  This generator copies the
function/global-symbolized sources into ``recon/readable_sources/app`` and adds
the verified structure catalog as named byte-exact layout declarations plus
per-function binding comments.  Library bodies are kept, but separated from G1
product code.  Raw identities remain in provenance comments and manifest data.
"""

from __future__ import annotations

import hashlib
import json
import re
import shutil
from collections import Counter, defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "recon" / "symbolized" / "app"
OUTPUT = ROOT / "recon" / "readable_sources" / "app"
G1_OUTPUT = OUTPUT / "g1"
LIB_OUTPUT = OUTPUT / "library"
INCLUDE_OUTPUT = OUTPUT / "include"
NAMES = ROOT / "recon" / "catalogs" / "function_names_app.json"
OWNERSHIP = ROOT / "recon" / "application" / "application_sources.json"
STRUCTS = ROOT / "recon" / "structs" / "struct_catalog_app.json"
SYMBOL_HEADER = ROOT / "recon" / "symbols" / "g1_app_symbols.h"

IDENTIFIER = re.compile(r"[^A-Za-z0-9_]")
TAIL_CALL = re.compile(r"\breturn\s+([A-Za-z_][A-Za-z0-9_]*)\s*\(")
FUNCTION_DEF = re.compile(
    r"(?:^|[;}])\s*(?!extern\b)(?:[A-Za-z_][\w\s*]*?\s+)"
    r"([A-Za-z_][A-Za-z0-9_]*)\s*\([^;{}]*\)\s*\{")
SKIP_C = re.compile(
    r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
    re.DOTALL,
)
RAW_FUNCTION = re.compile(r"\bFUN_[0-9a-fA-F]{8}\b")
RAW_ADDRESS_SYMBOL = re.compile(r"\b(DAT|UNK|LAB)_([0-9a-fA-F]{4,8})\b")
ADDRESS_PREFIX = {
    "DAT": "firmware_data",
    "UNK": "firmware_unknown_data",
    "LAB": "control_label",
}

WIDTHS = {
    "uint8_t": 1, "int8_t": 1, "char": 1,
    "uint16_t": 2, "int16_t": 2,
    "uint32_t": 4, "int32_t": 4, "float": 4, "void *": 4,
    "uint64_t": 8, "int64_t": 8, "double": 8,
}


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def ident(value: str) -> str:
    value = IDENTIFIER.sub("_", value or "unnamed")
    if value[:1].isdigit():
        value = "n_" + value
    return value


def c_comment(value: str) -> str:
    return str(value or "").replace("*/", "* /").replace("\r", " ").replace("\n", " ")


def width(ctype: str) -> int:
    ctype = ctype.strip()
    return 4 if ctype.endswith("*") else WIDTHS.get(ctype, 4)


def layout_type(row: dict) -> str:
    return "g1_layout_%s__%s" % (ident(row["struct_name"]), ident(row["cid"]))


def named_layout_header(rows: list[dict]) -> str:
    lines = [
        "#ifndef G1_RECOVERED_LAYOUTS_H",
        "#define G1_RECOVERED_LAYOUTS_H",
        "#include <stdint.h>",
        "#include <stddef.h>",
        "",
        "/* Generated from struct_catalog_app.json.  Each declaration is a",
        " * byte-slot presentation of verified offsets, not a replacement for",
        " * an authoritative SDK type.  Names preserve the catalog CID because",
        " * distinct observed objects can legitimately share a semantic type. */",
        "",
    ]
    for row in rows:
        type_name = layout_type(row)
        fields = sorted(row.get("fields", []), key=lambda item: int(item["offset"], 16))
        offsets = [int(field["offset"], 16) for field in fields]
        lines.extend([
            "/* %s | %s | %s | D1+D2 %s" % (
                row["cid"], "library" if row.get("is_library") else "G1-original",
                c_comment(row.get("purpose", "")), "verified" if row.get("verified") else "FAILED"),
            " * review: %s */" % c_comment(row.get("review_note", "")),
            "struct __attribute__((packed)) %s {" % type_name,
        ])
        cursor = 0
        used_names: Counter[str] = Counter()
        assertions = []
        for index, field in enumerate(fields):
            offset = offsets[index]
            if offset > cursor:
                lines.append("    uint8_t _pad_0x%x[0x%x];" % (cursor, offset - cursor))
            declared = width(field.get("type", "uint32_t"))
            next_offset = offsets[index + 1] if index + 1 < len(offsets) else offset + declared
            slot = max(1, min(declared, max(1, next_offset - offset)))
            base_name = ident(field.get("name") or "field_0x%x" % offset)
            used_names[base_name] += 1
            field_name = base_name if used_names[base_name] == 1 else "%s_0x%x" % (base_name, offset)
            note = "catalog type: %s" % c_comment(field.get("type", "unknown"))
            if field.get("library_member"):
                note += "; SDK member: %s" % c_comment(field["library_member"])
            lines.append("    uint8_t %s[0x%x]; /* %s */" % (field_name, slot, note))
            assertions.append(
                '_Static_assert(offsetof(struct %s, %s) == 0x%x, "%s.%s");' %
                (type_name, field_name, offset, type_name, field_name))
            cursor = offset + slot
        size = max(cursor, int(row.get("size_lower_bound") or 0))
        if size > cursor:
            lines.append("    uint8_t _tail_pad[0x%x];" % (size - cursor))
        lines.append("};")
        lines.extend(assertions)
        lines.extend([
            '_Static_assert(sizeof(struct %s) >= 0x%x, "%s.size");' %
            (type_name, size, type_name),
            "",
        ])
    lines.extend(["#endif", ""])
    return "\n".join(lines)


def code_only(text: str) -> str:
    chunks, position = [], 0
    for match in SKIP_C.finditer(text):
        chunks.append(text[position:match.start()])
        chunks.append(" " * (match.end() - match.start()))
        position = match.end()
    chunks.append(text[position:])
    return "".join(chunks)


def substitute_code(text: str, pattern: re.Pattern, replacement) -> str:
    output, position = [], 0
    for match in SKIP_C.finditer(text):
        output.append(pattern.sub(replacement, text[position:match.start()]))
        output.append(match.group(0))
        position = match.end()
    output.append(pattern.sub(replacement, text[position:]))
    return "".join(output)


def unique_public_name(source_name: str, address: str, text: str) -> tuple[str, str | None]:
    if not source_name.startswith("FUN_"):
        return source_name, None
    calls = TAIL_CALL.findall(code_only(text))
    if len(set(calls)) != 1:
        raise RuntimeError("unnamed source is not a single-target tail thunk: %s" % source_name)
    public_name = "%s_tail_thunk_%s" % (calls[0], address[2:])
    definitions = FUNCTION_DEF.findall(code_only(text))
    if len(definitions) != 1:
        raise RuntimeError("cannot identify thunk definition: %s -> %r" % (source_name, definitions))
    return public_name, definitions[0]


def binding_comment(address: str, rows: list[dict]) -> str:
    if not rows:
        return ""
    lines = [
        "/* Recovered layout bindings (presentation-only; Ghidra-grounded):",
    ]
    for row, member in rows:
        lines.append(" *   %-16s => struct %-48s [%s; %s]" % (
            member.get("base", "object"), layout_type(row), row["cid"],
            "library" if row.get("is_library") else "G1-original"))
    lines.extend([
        " * Raw function identity: %s.  See ../include/g1_recovered_layouts.h. */" % address,
        "",
    ])
    return "\n".join(lines)


def main() -> None:
    names = json.loads(NAMES.read_text())
    readable_raw = {
        row["raw_name"]: (row["name"] if row.get("human") else
                          "firmware_function_%s" % address[2:])
        for address, row in names["by_address"].items()
    }
    ownership_payload = json.loads(OWNERSHIP.read_text())
    ownership = {row["address"].lower(): row for row in ownership_payload["functions"]}
    struct_rows = json.loads(STRUCTS.read_text())["structs"]
    bindings: dict[str, list[tuple[dict, dict]]] = defaultdict(list)
    for row in struct_rows:
        for member in row.get("members", []):
            address = "0x%08x" % (int(member["entry"], 16) & ~1)
            bindings[address].append((row, member))

    if OUTPUT.exists():
        shutil.rmtree(OUTPUT)
    for directory in (G1_OUTPUT, LIB_OUTPUT, INCLUDE_OUTPUT):
        directory.mkdir(parents=True, exist_ok=True)

    (INCLUDE_OUTPUT / "g1_recovered_layouts.h").write_text(named_layout_header(struct_rows))
    shutil.copy2(SYMBOL_HEADER, INCLUDE_OUTPUT / SYMBOL_HEADER.name)
    support_files = [path for path in SOURCE.iterdir() if path.is_file() and path.suffix != ".c"]
    for support in support_files:
        shutil.copy2(support, INCLUDE_OUTPUT / support.name)

    manifest_rows = []
    generated_names = set()
    for source in sorted(SOURCE.glob("*.c")):
        source_name = source.stem
        address = names["by_name"].get(source_name)
        if not address:
            raise RuntimeError("source absent from function name map: %s" % source)
        address = address.lower()
        text = source.read_text(errors="replace")
        public_name, old_definition = unique_public_name(source_name, address, text)
        if public_name in generated_names:
            raise RuntimeError("generated public-name collision: %s" % public_name)
        generated_names.add(public_name)
        if old_definition:
            text = re.sub(r"\b%s\b" % re.escape(old_definition), public_name, text)
            text = re.sub(r"(?m)^ \* public-name: .*?$", " * public-name: %s" % public_name, text)
        text = substitute_code(
            text, RAW_FUNCTION,
            lambda match: readable_raw.get(
                match.group(0), "firmware_function_%s" % match.group(0)[4:].lower()))
        text = substitute_code(
            text, RAW_ADDRESS_SYMBOL,
            lambda match: "%s_%s" %
            (ADDRESS_PREFIX[match.group(1)], match.group(2).lower()))
        annotation = binding_comment(address, bindings.get(address, []))
        if annotation:
            first_newline = text.find("\n") + 1
            text = text[:first_newline] + annotation + text[first_newline:]

        residue = sorted(set(RAW_FUNCTION.findall(code_only(text))))
        if residue:
            raise RuntimeError("raw function token remains in %s: %s" % (source, residue[:5]))

        owner = ownership[address]
        category = "library" if owner["status"] == "excluded_library" else "g1"
        destination = (LIB_OUTPUT if category == "library" else G1_OUTPUT) / (public_name + ".c")
        destination.write_text(text)
        manifest_rows.append({
            "address": address,
            "raw_symbol": owner["raw_symbol"],
            "public_name": public_name,
            "canonical_name": source_name,
            "category": category,
            "source": str(source.relative_to(ROOT)),
            "output": str(destination.relative_to(ROOT)),
            "structure_bindings": [
                {"cid": row["cid"], "type": layout_type(row), "base": member.get("base")}
                for row, member in bindings.get(address, [])
            ],
        })

    summary = Counter(row["category"] for row in manifest_rows)
    source_addresses = {row["address"] for row in manifest_rows}
    unattached = [
        {"address": address, "cid": row["cid"], "type": layout_type(row),
         "base": member.get("base"), "raw_function": member.get("func"),
         "reason": "catalog member has no standalone reconstructed source body"}
        for address, rows in sorted(bindings.items()) if address not in source_addresses
        for row, member in rows
    ]
    attached_count = sum(len(row["structure_bindings"]) for row in manifest_rows)
    manifest = {
        "schema": 1,
        "core": "CPUAPP",
        "purpose": "standalone presentation tree with readable function/global/layout symbols",
        "canonical_parity_sources_untouched": True,
        "automatic_fallback_names": {
            "unmapped_function": "firmware_function_<address>",
            "DAT": "firmware_data_<address>",
            "UNK": "firmware_unknown_data_<address>",
            "LAB": "control_label_<address>",
        },
        "inputs": [
            {"path": str(path.relative_to(ROOT)), "sha256": sha256(path)}
            for path in (NAMES, OWNERSHIP, STRUCTS, SYMBOL_HEADER)
        ],
        "summary": {
            "sources": len(manifest_rows),
            "g1_sources": summary["g1"],
            "library_sources": summary["library"],
            "recovered_layouts": len(struct_rows),
            "functions_with_layout_bindings": sum(bool(row["structure_bindings"]) for row in manifest_rows),
            "layout_bindings_attached": attached_count,
            "layout_bindings_without_body": len(unattached),
            "raw_function_filenames": sum(row["public_name"].startswith("FUN_") for row in manifest_rows),
            "support_files": len(support_files),
        },
        "sources": manifest_rows,
        "unattached_structure_bindings": unattached,
    }
    (OUTPUT / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    (OUTPUT / "README.md").write_text(
        "# Fully named CPUAPP sources\n\n"
        "Generated by `tools/build_readable_sources.py`; do not edit this tree by hand.\n\n"
        "- `g1/`: G1-owned and unclassified product candidates.\n"
        "- `library/`: proven SDK, toolchain, and bundled-library bodies.\n"
        "- `include/g1_app_symbols.h`: named globals, rodata, MMIO, and functions.\n"
        "- `include/g1_recovered_layouts.h`: 676 D1+D2-verified named layouts.\n"
        "- `include/`: also carries generated `.h`/`.inc` support fragments.\n"
        "- `manifest.json`: durable address/raw-name back-map and structure bindings.\n\n"
        "No `FUN_*`, `DAT_*`, `UNK_*`, or `LAB_*` token remains in executable C. "
        "Raw spellings are deliberately retained in provenance comments and the manifest. "
        "Unmapped address-only symbols receive deterministic `firmware_*_<address>` names.\n\n"
        "This is a presentation tree. The parity-authoritative files remain in "
        "`recon/app/src`; applying recovered C types to executable sources is a separate "
        "CFG-verification-gated operation.\n"
    )
    print(json.dumps(manifest["summary"], sort_keys=True))


if __name__ == "__main__":
    main()
