#!/usr/bin/env python3
"""Authoritatively verify and receipt CPUNET private recovery shard 7."""

import argparse
import hashlib
import json
import re
from pathlib import Path

import cfg_verify


ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "recon/net/src"
WORKLIST = ROOT / "recon/catalogs/net_private_recovery_worklist.json"
OUTPUT = ROOT / "recon/ownership/net_private_7_recovery.json"
TRIALS = 80

FUNCTIONS = (
    (0x01010890, 40, "FUN_01010890"),
    (0x01011664, 186, "FUN_01011664"),
    (0x01018DF8, 50, "FUN_01018df8"),
    (0x01021634, 28, "FUN_01021634"),
    (0x01025D0C, 24, "FUN_01025d0c"),
    (0x01026BFE, 150, "FUN_01026bfe"),
    (0x010270E8, 98, "FUN_010270e8"),
    (0x01027A4A, 74, "FUN_01027a4a"),
    (0x01027A94, 62, "FUN_01027a94"),
    (0x0102961A, 18, "FUN_0102961a"),
    (0x0102971E, 26, "FUN_0102971e"),
    (0x010297B4, 206, "FUN_010297b4"),
    (0x01029882, 38, "FUN_01029882"),
)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def jsonable(value):
    if isinstance(value, dict):
        return {str(key): jsonable(item) for key, item in value.items()}
    if isinstance(value, (list, tuple)):
        return [jsonable(item) for item in value]
    return value


def worklist_entries():
    data = json.loads(WORKLIST.read_text())
    entries = {int(row["analysis_address"], 16): row for row in data["entries"]
               if row.get("suggested_shard") == "net-private-7"}
    expected = {va for va, _, _ in FUNCTIONS}
    if set(entries) != expected:
        raise ValueError("net-private-7 worklist membership changed")
    return entries


def build():
    entries = worklist_entries()
    context = cfg_verify.core_ctx("net")
    rows = []
    for va, extent, name in FUNCTIONS:
        entry = entries[va]
        if entry["true_executable_extent"] != extent:
            raise ValueError("true extent changed for 0x%08x" % va)
        path = SRC / (name + ".c")
        source = path.read_text()
        first = source.splitlines()[0]
        match = re.search(r"@\s+(0x[0-9a-fA-F]+)", first)
        if not match or int(match.group(1), 16) != va:
            raise ValueError("missing raw address header in %s" % path.name)
        if name not in source:
            raise ValueError("missing raw backmap %s" % name)
        if ".byte" in source or "__asm__(\".inst" in source:
            raise ValueError("blob-like source forbidden in %s" % path.name)

        catalogued_size = context["sizes"].get(va)
        if catalogued_size is None:
            # cfg_verify remains authoritative; the two catalog-missed entries
            # receive only the reviewed worklist extent in its in-memory map.
            context["sizes"][va] = extent
        verdict = cfg_verify.verify(
            "net", name, trials_random=TRIALS, source_override=source)
        if verdict.get("status") != "PASS" or verdict.get("checked", 0) < TRIALS:
            raise ValueError("cfg_verify failed for %s: %r" % (name, verdict))
        rows.append({
            "analysis_address": "0x%08x" % va,
            "runtime_address": entry["runtime_address"],
            "raw_backmap": name,
            "worklist_primary_symbol": entry["primary_symbol"],
            "source": str(path.relative_to(ROOT)),
            "source_sha256": sha(source.encode()),
            "true_executable_extent": extent,
            "extent_basis": entry["extent_basis"],
            "catalogued_start": entry["catalogued_start"],
            "verifier_extent_injection": catalogued_size is None,
            "cfg_verify": {
                "status": verdict["status"],
                "checked": verdict["checked"],
                "random_trials_requested": TRIALS,
                "selectors": jsonable(verdict.get("selectors", {})),
                "pointer_cases": jsonable(verdict.get("pointer_cases", [])),
                "callback_slots": jsonable(verdict.get("callback_slots", [])),
                "data_pointer_slots": jsonable(verdict.get("data_pointer_slots", [])),
                "cover_cases": verdict.get("cover_cases", 0),
            },
        })
    return {
        "schema_version": 1,
        "shard": "net-private-7",
        "policy": {
            "canonical_readable_c_only": True,
            "raw_address_headers_and_backmaps_required": True,
            "archive_or_blob_substitution_forbidden": True,
            "authoritative_verifier": "tools/cfg_verify.py",
            "shared_generated_or_name_outputs_untouched": True,
        },
        "summary": {
            "function_count": len(rows),
            "total_true_executable_extent": sum(row["true_executable_extent"] for row in rows),
            "all_cfg_pass": all(row["cfg_verify"]["status"] == "PASS" for row in rows),
            "minimum_checked_per_function": min(row["cfg_verify"]["checked"] for row in rows),
            "catalog_missed_extent_injections": sum(row["verifier_extent_injection"] for row in rows),
        },
        "functions": rows,
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    text = json.dumps(build(), indent=2, sort_keys=True) + "\n"
    if args.check:
        if OUTPUT.read_text() != text:
            raise SystemExit("net-private-7 receipt is stale")
    else:
        OUTPUT.write_text(text)


if __name__ == "__main__":
    main()
