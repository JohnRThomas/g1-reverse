#!/usr/bin/env python3
"""Build the fail-closed CPUAPP interior/tail resolution catalog.

Only explicitly reviewed, instruction-exact Thumb tail branches and exact
same-entry historical spellings are emitted as linker aliases.  Every residue
symbol is catalogued; an unlisted symbol is blocked rather than inferred from
proximity or a plausible prologue.
"""

import gzip
import hashlib
import json
import os
import re
import tempfile

from capstone import Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB
from capstone.arm import ARM_OP_IMM


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IMAGE = os.path.join(ROOT, "app_update.bin")
LINK_BASE = 0xC200
IMAGE_HEADER = 512

# Reviewed against the shipped image.  The value is the exact branch target.
REVIEWED_TAILS = {
    "FUN_0007c010": 0x00072880,
    "FUN_0007c0a4": 0x00074844,
    "FUN_0007c872": 0x000723b8,
    "FUN_0007c876": 0x00072558,
    "FUN_0007ca72": 0x00074844,
    "FUN_0007ce5c": 0x00074844,
    "FUN_0007d376": 0x000723b8,
    "FUN_0007d37a": 0x00072558,
    "FUN_000859b2": 0x00072880,
    "FUN_000861aa": 0x00085cf2,
    "FUN_0008641c": 0x00073a78,
    "process_sync_buffer": 0x00072880,
    "process_touch_event": 0x000745c8,
    "thunk_FUN_00043308": 0x00043308,
    "thunk_FUN_000727ac": 0x000727ac,
    "thunk_FUN_00072908": 0x00072908,
    "thunk_FUN_00074844": 0x00074844,
    "thunk_FUN_0007d77c": 0x0007d77c,
    "thunk_FUN_000868b4": 0x000868b4,
    "update_sync_buffer": 0x00072908,
    "uptime_ticks_get": 0x00074f68,
    "wait_for_event": 0x00074844,
}

# Historical spellings at an exact retained/adopted catalog entry.  These are
# not interior-address guesses: source and target have the same even VA.
REVIEWED_SAME_ENTRY = {
    "FUN_00080294_i": (0x00080294, "tc_cmac_final"),
    "thunk_FUN_000723b8": (0x000723b8, "k_mutex_lock"),
    "thunk_FUN_00072558": (0x00072558, "k_mutex_unlock"),
    "thunk_FUN_00085cf2": (0x00085cf2, "FUN_00085cf2"),
}

# Exact branches whose destination has no retained/adopted owner.  Keeping
# these explicit prevents a future generator change from silently promoting
# them merely because Capstone can decode the four bytes.
REVIEWED_BLOCKED_TARGETS = {
    "FUN_0008131c": 0x000812d2,
    "thunk_FUN_0007f7d2": 0x0007f7d2,
}

# Catalog-missing entries independently recovered from their exact shipped
# Thumb boundaries and accepted by cfg_verify's side-effect comparison.  They
# are strong owners, not aliases: retain the raw address identity and omit a
# veneer PROVIDE once the canonical source exists.
REVIEWED_RECONSTRUCTED_ENTRIES = {
    "FUN_00016574": (0x00016574, "FUN_00016574.c"),
    "FUN_00016834": (0x00016834, "FUN_00016834.c"),
    "FUN_00017a04": (0x00017a04, "FUN_00017a04.c"),
    "FUN_00017a10": (0x00017a10, "FUN_00017a10.c"),
    "FUN_00017a1c": (0x00017a1c, "FUN_00017a1c.c"),
    "touch_pmic_reset_assert": (0x00017a28, "FUN_00017a28.c"),
    "touch_pmic_reset_deassert": (0x00017a34, "FUN_00017a34.c"),
    "FUN_0002893c": (0x0002893c, "FUN_0002893c.c"),
    "FUN_00032fdc": (0x00032fdc, "FUN_00032fdc.c"),
    # Static zcbor string encoder omitted from the catalog.  Exact prologue,
    # complete 0x76-byte CFG and typed BSTR/TSTR tail veneers establish it as
    # an independent owner rather than an interior alias of 0x86208.
    "FUN_00086228": (0x00086228, "FUN_00086228.c"),
}

# Identity regeneration completed while this residue snapshot remained
# durable.  These exact veneers now have strong reconstructed owners, so the
# linker fragment must remain non-owning and omit redundant PROVIDEs.
ALREADY_STRONG_OWNERS = {
    "thunk_FUN_00072908",
    "update_sync_buffer",
    "process_sync_buffer",
    "thunk_FUN_00074844",
    "thunk_FUN_000727ac",
    "uptime_ticks_get",
}


def load(path):
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt") as stream:
        return json.load(stream)


def symbol_va(record):
    identities = record.get("identities", [])
    if identities:
        return int(identities[0]["va"], 16)
    match = re.search(
        r"(?:FUN_000|ext|tail_|thunk_FUN_000)([0-9a-fA-F]+)",
        record["symbol"])
    if not match:
        raise RuntimeError("cannot recover VA for %s" % record["symbol"])
    return int(match.group(1), 16)


def atomic_write(path, text):
    fd, temporary = tempfile.mkstemp(
        prefix=os.path.basename(path) + ".", dir=os.path.dirname(path), text=True)
    try:
        with os.fdopen(fd, "w") as stream:
            stream.write(text)
        os.replace(temporary, path)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)


def build():
    residue_path = os.path.join(ROOT, "recon/analysis/app_link_residue.json")
    classified_path = os.path.join(ROOT, "recon/catalogs/classified.json.gz")
    names_path = os.path.join(ROOT, "recon/catalogs/function_names_app.json")
    residue = load(residue_path)
    functions = load(classified_path)["functions"]
    names = load(names_path)["by_address"]
    with open(IMAGE, "rb") as stream:
        image = stream.read()
    functions = sorted(functions, key=lambda item: int(item["entry"]))
    by_entry = {int(item["entry"]): item for item in functions}
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
    md.detail = True

    def image_bytes(va, size):
        offset = va - LINK_BASE + IMAGE_HEADER
        return image[offset:offset + size]

    def containing(va):
        hits = [item for item in functions
                if int(item["entry"]) <= va <
                int(item["entry"]) + int(item["size"])]
        return max(hits, key=lambda item: int(item["entry"])) if hits else None

    def sequential_boundary(owner, va):
        if not owner:
            return False
        start = int(owner["entry"])
        size = va - start + 4
        return any(item.address == va for item in md.disasm(image_bytes(start, size), start))

    rows = []
    source_rows = [item for item in residue["entries"]
                   if item["category"] == "interior_or_tail_alias"]
    for source in source_rows:
        symbol = source["symbol"]
        va = symbol_va(source)
        owner = containing(va)
        raw = image_bytes(va, 4)
        instruction = next(md.disasm(raw, va, count=1), None)
        evidence = {
            "bytes": raw.hex(),
            "decode": ("%s %s" % (instruction.mnemonic, instruction.op_str)).strip()
                      if instruction else None,
            "catalog_entry": va in by_entry,
            "containing_owner": ("0x%08x" % int(owner["entry"])) if owner else None,
            "containing_owner_name": owner.get("name") if owner else None,
            "sequential_owner_boundary": sequential_boundary(owner, va),
        }
        row = {
            "va": "0x%08x" % va,
            "symbol": symbol,
            "reference_count": source["reference_count"],
            "reference_sites": source["reference_sites"],
            "evidence": evidence,
        }

        if symbol in REVIEWED_TAILS:
            expected = REVIEWED_TAILS[symbol]
            if (not instruction or instruction.size != 4 or
                    instruction.mnemonic not in ("b", "b.w") or
                    len(instruction.operands) != 1 or
                    instruction.operands[0].type != ARM_OP_IMM or
                    (instruction.operands[0].imm & ~1) != expected):
                raise RuntimeError("reviewed tail changed at %s" % symbol)
            if "0x%08x" % expected not in names:
                raise RuntimeError("tail target is not a catalog identity: %s" % symbol)
            if va not in by_entry and not evidence["sequential_owner_boundary"]:
                raise RuntimeError("reviewed tail is no longer a proven boundary: %s" % symbol)
            target = names["0x%08x" % expected]["name"]
            row.update({
                "decision": ("already_resolved_by_strong_owner"
                             if symbol in ALREADY_STRONG_OWNERS else
                             "materialize_reviewed_tail_alias"),
                "target_va": "0x%08x" % expected,
                "target_symbol": target,
                "reason": "exact four-byte unconditional Thumb tail branch",
            })
        elif symbol in REVIEWED_SAME_ENTRY:
            expected_va, target = REVIEWED_SAME_ENTRY[symbol]
            if va != expected_va or va not in by_entry:
                raise RuntimeError("same-entry review changed at %s" % symbol)
            name_record = names.get("0x%08x" % va, {})
            if target not in (name_record.get("name"), name_record.get("raw_name")):
                raise RuntimeError("same-entry target identity changed at %s" % symbol)
            row.update({
                "decision": "materialize_reviewed_same_entry_alias",
                "target_va": "0x%08x" % va,
                "target_symbol": target,
                "reason": "historical spelling shares the exact catalog entry",
            })
        elif symbol in REVIEWED_BLOCKED_TARGETS:
            row.update({
                "decision": "blocked",
                "target_va": "0x%08x" % REVIEWED_BLOCKED_TARGETS[symbol],
                "reason": "exact tail target has no retained or adopted owner",
            })
        elif symbol in REVIEWED_RECONSTRUCTED_ENTRIES:
            expected_va, filename = REVIEWED_RECONSTRUCTED_ENTRIES[symbol]
            source_path = os.path.join(ROOT, "recon/app/src", filename)
            if va != expected_va or not os.path.isfile(source_path):
                raise RuntimeError("reconstructed owner changed at %s" % symbol)
            # The raw/human residue spelling itself is already a durable
            # address back-map.  Name-manifest regeneration may intentionally
            # lag this canonical-source commit, so use it only as enrichment.
            target = names.get("0x%08x" % va, {}).get("name") or symbol
            row.update({
                "decision": "already_resolved_by_strong_owner",
                "target_va": "0x%08x" % va,
                "target_symbol": target,
                "reason": "exact standalone entry reconstructed and CFG-side-effect verified",
            })
        elif symbol == "k_sem_take":
            row.update({
                "decision": "blocked",
                "reason": "SDK/config public owner is outside this interior-alias pass",
            })
        elif va not in by_entry and owner is None:
            row.update({
                "decision": "blocked",
                "reason": "uncatalogued candidate entry; proximity or a prologue is not ABI evidence",
            })
        elif va in by_entry:
            row.update({
                "decision": "blocked",
                "reason": "distinct catalog entry is not an alias without exact ownership evidence",
            })
        else:
            row.update({
                "decision": "blocked",
                "reason": "interior instruction or split entry has no exact alias/ABI proof",
            })
        rows.append(row)

    expected = (set(REVIEWED_TAILS) | set(REVIEWED_SAME_ENTRY) |
                set(REVIEWED_BLOCKED_TARGETS) |
                set(REVIEWED_RECONSTRUCTED_ENTRIES))
    actual = {item["symbol"] for item in source_rows}
    if not expected <= actual:
        raise RuntimeError("review table contains stale symbols: %s" % sorted(expected - actual))
    if len(rows) != 119 or len({item["symbol"] for item in rows}) != 119:
        raise RuntimeError("residue set changed; expected 119 unique symbols")

    materialized = [item for item in rows
                    if item["decision"].startswith("materialize_")]
    already_owned = [item for item in rows
                     if item["decision"] == "already_resolved_by_strong_owner"]
    resolved = materialized + already_owned
    catalog = {
        "schema": 1,
        "core": "app",
        "scope": "interior_or_tail_alias entries from app_link_residue.json",
        "image_sha256": hashlib.sha256(image).hexdigest(),
        "policy": {
            "fail_closed": True,
            "guessed_aliases": False,
            "ambiguous_entries_blocked": True,
            "sdk_or_config_candidates_touched": False,
            "pseudo_ops_touched": False,
            "raw_address_backmap_preserved": True,
        },
        "summary": {
            "residue_symbols": len(rows),
            "unique_vas": len({item["va"] for item in rows}),
            "resolved_symbols": len(resolved),
            "resolved_unique_vas": len({item["va"] for item in resolved}),
            "materialized_symbols": len(materialized),
            "materialized_unique_vas": len({item["va"] for item in materialized}),
            "already_strong_symbols": len(already_owned),
            "blocked_symbols": len(rows) - len(resolved),
        },
        "entries": sorted(rows, key=lambda item: (int(item["va"], 16), item["symbol"])),
    }
    return catalog


def render_ld(catalog):
    lines = [
        "/* Generated by tools/build_app_veneer_resolutions.py.",
        " * Only reviewed exact-entry and four-byte Thumb tail aliases. */",
        "",
    ]
    for row in catalog["entries"]:
        if not row["decision"].startswith("materialize_"):
            continue
        lines.append("PROVIDE(%s = %s); /* %s -> %s */" % (
            row["symbol"], row["target_symbol"], row["va"], row["target_va"]))
    return "\n".join(lines) + "\n"


def render_md(catalog):
    summary = catalog["summary"]
    lines = [
        "# CPUAPP reviewed interior/tail residues", "",
        "This catalog is fail-closed: only exact four-byte Thumb tail branches and",
        "exact same-entry historical spellings are materialized.", "",
        "- Residue symbols: %d (%d unique VAs)" %
        (summary["residue_symbols"], summary["unique_vas"]),
        "- Materialized: %d symbols (%d unique VAs)" %
        (summary["materialized_symbols"], summary["materialized_unique_vas"]),
        "- Already resolved by strong owners: %d symbols" %
        summary["already_strong_symbols"],
        "- Blocked: %d symbols" % summary["blocked_symbols"], "",
        "| VA | Symbol | Decision | Target | Evidence/reason |", "|---|---|---|---|---|",
    ]
    for row in catalog["entries"]:
        target = row.get("target_symbol", "")
        evidence = row["evidence"].get("decode") or row["evidence"]["bytes"]
        lines.append("| `%s` | `%s` | `%s` | `%s` | %s; %s |" % (
            row["va"], row["symbol"], row["decision"], target,
            evidence.replace("|", "\\|"), row["reason"]))
    return "\n".join(lines) + "\n"


def main():
    catalog = build()
    base = os.path.join(ROOT, "recon/catalogs/app_veneer_resolutions")
    atomic_write(base + ".json", json.dumps(catalog, indent=2) + "\n")
    atomic_write(base + ".md", render_md(catalog))
    atomic_write(os.path.join(ROOT, "recon/symbols/g1_app_veneer_aliases.ld"),
                 render_ld(catalog))
    print("materialized=%d blocked=%d" % (
        catalog["summary"]["materialized_symbols"],
        catalog["summary"]["blocked_symbols"]))


if __name__ == "__main__":
    main()
