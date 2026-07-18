#!/usr/bin/env python3
"""Audit the current CPUAPP interior_or_tail_alias residue snapshot.

This catalog deliberately does not emit aliases or regenerate derivative trees.
Every residue is manually assigned one identity class; proximity alone never
authorizes a linker alias or a fabricated function body.
"""
import argparse
import gzip
import hashlib
import json
import os
import re

from capstone import Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RESIDUE = os.path.join(ROOT, "recon/analysis/app_link_residue.json")
CLASSIFIED = os.path.join(ROOT, "recon/catalogs/classified.json.gz")
REFGRAPH = os.path.join(ROOT, "recon/catalogs/refgraph_app.json.gz")
IMAGE = os.path.join(ROOT, "app_update.bin")
JSON_OUT = os.path.join(ROOT, "recon/catalogs/app_interior_alias_audit.json")
MD_OUT = os.path.join(ROOT, "recon/catalogs/app_interior_alias_audit.md")
LINK_BASE = 0xC200
IMAGE_HEADER = 512


SAME_ENTRY_ALIAS = {
    # The residue identity is the exact existing catalog entry at 0x7f7c4.
    # Its spelling describes the uncatalogued branch destination, so it still
    # cannot be materialized without a strong owner at 0x7f7d2.
    "thunk_FUN_0007f7d2",
}

LEGITIMATE_INTERIOR_TAIL_OR_ISLAND = {
    # Noreturn SVC islands embedded in FUN_000545f0.
    "FUN_0005463e",
    "FUN_00054688",
    # Exact four-byte branch veneer to bt_le_adv_set_enable_legacy.
    "FUN_0008131c",
}

# These uncatalogued spellings are owned by configured SDK/newlib source
# units or library identities. They require linkage/name reconciliation, not a
# new firmware reconstruction or an invented interior alias.
SDK_STATIC_OR_LIBRARY_IDENTITY = {
    "FUN_0004d7d8",
    "FUN_00056e24",
    "strtol_reentrant",
}

# No current residue address lands in literal/data bytes. Keep this explicit:
# future residue drift must be reviewed rather than silently taking a default.
DATA_OR_LITERAL_MISREFERENCE = set()

TRUE_MISSING_CATALOG_ENTRY = {"ext77c8c", "tail_77d30"}

# Seven residues now have cfg_verify-accepted strong owners.  For the two
# veneers this is the exact four-byte entry, preserving the original call
# target while giving the linker a real owner rather than an alias.
CFG_VERIFIED_STRONG_OWNERS = {
    "FUN_0004d7d8",
    "FUN_00056e24",
    "strtol_reentrant",
    "thunk_FUN_0007f7d2",
    "FUN_0008131c",
    "ext77c8c",
    "tail_77d30",
}
CFG_VERIFIED_SOURCE_FILES = {
    "FUN_0004d7d8": "FUN_0004d7d8.c",
    "FUN_00056e24": "FUN_00056e24.c",
    "strtol_reentrant": "FUN_00077a28.c",
    "thunk_FUN_0007f7d2": "FUN_0007f7c4.c",
    "FUN_0008131c": "FUN_0008131c.c",
    "ext77c8c": "__swbuf_r.c",
    "tail_77d30": "_write_r.c",
}

SAFE_CALLER_CORRECTIONS = {
    "strtol.c": "strtol_reentrant",
    "FUN_00086c88.c": "ext77c8c",
    "FUN_00086f5a.c": "tail_77d30",
}

CLASS_TABLE = {
    "same_entry_alias": SAME_ENTRY_ALIAS,
    "legitimate_interior_tail_or_island": LEGITIMATE_INTERIOR_TAIL_OR_ISLAND,
    "sdk_static_or_library_identity": SDK_STATIC_OR_LIBRARY_IDENTITY,
    "data_or_literal_misreference": DATA_OR_LITERAL_MISREFERENCE,
    "true_missing_catalog_entry": TRUE_MISSING_CATALOG_ENTRY,
}


def load(path):
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt", encoding="utf-8") as stream:
        return json.load(stream)


def digest(path):
    with open(path, "rb") as stream:
        return hashlib.sha256(stream.read()).hexdigest()


def symbol_va(record):
    if record.get("identities"):
        return int(record["identities"][0]["va"], 16)
    match = re.search(r"(?:ext|tail_)([0-9a-fA-F]+)", record["symbol"])
    if not match:
        raise RuntimeError("addressless residue: " + record["symbol"])
    return int(match.group(1), 16)


def build():
    residue = load(RESIDUE)
    source_rows = [row for row in residue["entries"]
                   if row["category"] == "interior_or_tail_alias"]
    actual = {row["symbol"] for row in source_rows}
    assigned = set().union(*CLASS_TABLE.values())
    overlap = sum((list(values) for values in CLASS_TABLE.values()), [])
    if actual != assigned or len(overlap) != len(set(overlap)):
        raise RuntimeError("manual classification drift: missing=%r extra=%r" %
                           (sorted(actual - assigned), sorted(assigned - actual)))
    if len(source_rows) != 9:
        raise RuntimeError("residue snapshot changed: expected 9")

    functions = sorted(load(CLASSIFIED)["functions"],
                       key=lambda row: int(row["entry"]))
    by_entry = {int(row["entry"]): row for row in functions}
    refgraph = load(REFGRAPH)["functions"]
    with open(IMAGE, "rb") as stream:
        image = stream.read()
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)

    def raw(va, size):
        offset = va - LINK_BASE + IMAGE_HEADER
        return image[offset:offset + size]

    def containing(va):
        hits = [row for row in functions
                if int(row["entry"]) <= va <
                int(row["entry"]) + int(row["size"])]
        return max(hits, key=lambda row: int(row["entry"])) if hits else None

    rows = []
    for source in source_rows:
        symbol = source["symbol"]
        va = symbol_va(source)
        owner = containing(va)
        decoded = list(md.disasm(raw(va, 16), va))
        classification = next(name for name, values in CLASS_TABLE.items()
                              if symbol in values)
        if classification != "data_or_literal_misreference" and not decoded:
            raise RuntimeError("reviewed code no longer decodes: " + symbol)
        previous = max((row for row in functions if int(row["entry"]) < va),
                       key=lambda row: int(row["entry"]), default=None)
        following = min((row for row in functions if int(row["entry"]) > va),
                        key=lambda row: int(row["entry"]), default=None)
        refgraph_row = refgraph.get(hex(va))
        incoming_callers = sorted(
            entry for entry, record in refgraph.items()
            if hex(va) in record.get("calls", []))
        resolution = "requires_independent_reconstruction"
        reason = "independent callable entry shape/reference, absent from catalog"
        if symbol in CFG_VERIFIED_STRONG_OWNERS:
            filename = CFG_VERIFIED_SOURCE_FILES.get(symbol, symbol + ".c")
            source_path = os.path.join(ROOT, "recon/app/src", filename)
            mirror_path = os.path.join(ROOT, "recon/verified/src", filename)
            if not os.path.isfile(source_path) or digest(source_path) != digest(mirror_path):
                raise RuntimeError("CFG-verified owner/mirror drift: " + symbol)
            resolution = "already_resolved_by_cfg_verified_strong_owner"
            reason = "exact-entry strong owner accepted by cfg_verify"
        elif symbol in ("FUN_0005463e", "FUN_00054688"):
            resolution = "blocked_embedded_noreturn_svc_island"
            reason = "embedded SVC continuation is not an ordinary function ABI"
        rows.append({
            "symbol": symbol,
            "va": "0x%08x" % va,
            "classification": classification,
            "resolution": resolution,
            "reason": reason,
            "reference_count": source["reference_count"],
            "reference_sites": source["reference_sites"],
            "evidence": {
                "bytes16": raw(va, 16).hex(),
                "decode": [((ins.mnemonic + " " + ins.op_str).strip())
                           for ins in decoded[:4]],
                "catalog_entry": va in by_entry,
                "containing_owner": ("0x%08x" % int(owner["entry"]))
                                    if owner else None,
                "previous_catalog_entry": ("0x%08x" % int(previous["entry"]))
                                          if previous else None,
                "previous_catalog_end": ("0x%08x" %
                                         (int(previous["entry"]) +
                                          int(previous["size"])))
                                        if previous else None,
                "next_catalog_entry": ("0x%08x" % int(following["entry"]))
                                      if following else None,
                "refgraph_entry": refgraph_row is not None,
                "refgraph_callers": refgraph_row.get("callers", [])
                                    if refgraph_row else [],
                "refgraph_incoming_call_edges": incoming_callers,
            },
        })

    parser_source = os.path.join(ROOT, "recon/app/src/FUN_00064290.c")
    parser_mirror = os.path.join(ROOT, "recon/verified/src/FUN_00064290.c")
    expected_parser_sha = "4929d7877e2cf4990a9a58a43d7294ababb6c90030b4101425be45178907c001"
    if digest(parser_source) != expected_parser_sha or \
            digest(parser_mirror) != expected_parser_sha:
        raise RuntimeError("internal-island caller correction drift")
    with open(parser_source, encoding="utf-8") as stream:
        parser_text = stream.read()
    if "FUN_0006446c" in parser_text or "return 0;" not in parser_text:
        raise RuntimeError("internal island re-externalized")

    for filename, stale_symbol in SAFE_CALLER_CORRECTIONS.items():
        source_path = os.path.join(ROOT, "recon/app/src", filename)
        mirror_path = os.path.join(ROOT, "recon/verified/src", filename)
        if digest(source_path) != digest(mirror_path):
            raise RuntimeError("corrected caller/mirror drift: " + filename)
        with open(source_path, encoding="utf-8") as stream:
            if stale_symbol in stream.read():
                raise RuntimeError("stale residue caller identity: " + stale_symbol)

    counts = {name: sum(row["classification"] == name for row in rows)
              for name in CLASS_TABLE}
    return {
        "schema": 1,
        "core": "app",
        "scope": "current interior_or_tail_alias entries from app_link_residue.json",
        "image_sha256": digest(IMAGE),
        "residue_sha256": digest(RESIDUE),
        "policy": {
            "fail_closed": True,
            "aliases_emitted": False,
            "invented_bodies": False,
            "weak_aliases": False,
            "blobs": False,
            "derivatives_regenerated": False,
        },
        "summary": {"residue_count": len(rows),
                    "reference_count": sum(row["reference_count"] for row in rows),
                    "classification_counts": counts,
                    "safe_caller_corrections": len(SAFE_CALLER_CORRECTIONS),
                    "already_strong_owners": sum(
                        row["resolution"] ==
                        "already_resolved_by_cfg_verified_strong_owner"
                        for row in rows),
                    "requires_reconstruction": sum(
                        row["resolution"] == "requires_independent_reconstruction"
                        for row in rows)},
        "entries": sorted(rows,
                          key=lambda row: (int(row["va"], 16), row["symbol"])),
    }


def markdown(data):
    counts = data["summary"]["classification_counts"]
    lines = ["# CPUAPP interior/tail alias audit", "",
        "The current 9-entry residue snapshot was reviewed against the shipped",
        "Thumb bytes, catalog boundaries, and canonical call sites. No linker",
        "aliases, weak owners, blobs, or derivative trees are generated.", "",
        "- Same-entry aliases/identities: %d" % counts["same_entry_alias"],
        "- Legitimate interior tails/islands: %d" % counts["legitimate_interior_tail_or_island"],
        "- SDK static/library identities: %d" % counts["sdk_static_or_library_identity"],
        "- Data/literal misreferences: %d" % counts["data_or_literal_misreference"],
        "- True missing catalog entries: %d" % counts["true_missing_catalog_entry"],
        "- Safe canonical caller corrections: %d" %
        data["summary"]["safe_caller_corrections"], "",
        "| VA | Symbol | Classification | Resolution | Evidence |",
        "|---|---|---|---|---|"]
    for row in data["entries"]:
        decode = "; ".join(row["evidence"]["decode"][:2])
        lines.append("| `%s` | `%s` | `%s` | `%s` | %s; %s |" %
                     (row["va"], row["symbol"], row["classification"],
                      row["resolution"], decode.replace("|", "\\|"),
                      row["reason"]))
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build()
    json_text = json.dumps(data, indent=1) + "\n"
    markdown_text = markdown(data)
    if args.check:
        assert open(JSON_OUT, encoding="utf-8").read() == json_text
        assert open(MD_OUT, encoding="utf-8").read() == markdown_text
    else:
        open(JSON_OUT, "w", encoding="utf-8").write(json_text)
        open(MD_OUT, "w", encoding="utf-8").write(markdown_text)


if __name__ == "__main__":
    main()
