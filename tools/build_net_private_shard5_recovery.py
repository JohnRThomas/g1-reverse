#!/usr/bin/env python3
"""Build the fail-closed CFG receipt for CPUNET private recovery shard 5."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

import cfg_verify


ROOT = Path(__file__).resolve().parents[1]
WORKLIST = ROOT / "recon/catalogs/net_private_recovery_worklist.json"
OUTPUT = ROOT / "recon/ownership/net_private_shard5_recovery.json"
SHARD = "net-private-5"
EXPECTED = {
    0x01012150: ("FUN_01012150", 38, "evaluate controller event eligibility"),
    0x01013DA8: ("FUN_01013da8", 238, "catch a connection event cursor up to controller time"),
    0x01019EB4: ("FUN_01019eb4", 68, "inspect the resolved controller buffer mode"),
    0x01019EF8: ("FUN_01019ef8", 58, "match resolved controller buffer metadata"),
    0x0101E090: ("FUN_0101e090", 20, "resolve an inactive connection typed handle"),
    0x01022A50: ("FUN_01022a50", 48, "program the radio channel mask and descriptor"),
    0x0102590C: ("FUN_0102590c", 138, "perform an overlap-safe private byte move"),
    0x010269CE: ("FUN_010269ce", 176, "reserve payload space in a packed controller packet"),
    0x01026DAE: ("FUN_01026dae", 154, "test for another packed controller packet item"),
    0x01027ED4: ("FUN_01027ed4", 30, "invoke a private helper in fixed mode one"),
    0x010280D8: ("FUN_010280d8", 26, "invoke a private helper with option zero"),
    0x0102A208: ("sdc_byte_lock_release", 18, "release a byte lock under PRIMASK"),
}

# Full-width random size_t values manufacture multi-billion-iteration moves.
# These values cover empty, short byte, word-copy threshold, aligned body, and
# each trailing-byte count without weakening the shared verifier globally.
MOVE_LENGTHS = (0, 1, 2, 3, 4, 7, 8, 9, 10, 15, 16, 31, 44)


def _sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def _jsonable(value):
    if isinstance(value, dict):
        return {str(key): _jsonable(item) for key, item in value.items()}
    if isinstance(value, (list, tuple)):
        return [_jsonable(item) for item in value]
    return value


def _worklist_rows() -> list[dict]:
    document = json.loads(WORKLIST.read_text())
    if document.get("schema") != "g1.net.private_recovery_worklist.v1":
        raise RuntimeError("unexpected private-recovery worklist schema")
    expected_policy = {
        "no_blobs": True,
        "private_sdc_mpsl_report_only": True,
        "archive_replacement_forbidden": True,
        "fail_closed": True,
    }
    if document.get("policy") != expected_policy:
        raise RuntimeError("private-recovery policy changed")
    rows = [row for row in document["entries"]
            if row.get("suggested_shard") == SHARD]
    observed = {
        int(row["analysis_address"], 16):
        (row["primary_symbol"], row["true_executable_extent"])
        for row in rows
    }
    expected = {va: values[:2] for va, values in EXPECTED.items()}
    if observed != expected:
        raise RuntimeError(f"{SHARD} membership/extent changed: {observed!r}")
    return sorted(rows, key=lambda row: int(row["analysis_address"], 16))


def _verify(va: int, raw_symbol: str, source: str) -> tuple[dict, int]:
    trials = len(MOVE_LENGTHS) if va == 0x0102590C else 40
    previous = cfg_verify.BOUNDED_RANDOM_ARGS.get(("net", va))
    try:
        if va == 0x0102590C:
            cfg_verify.BOUNDED_RANDOM_ARGS[("net", va)] = {2: MOVE_LENGTHS}
        verdict = cfg_verify.verify(
            "net", raw_symbol, trials_random=trials, source_override=source)
    finally:
        if previous is None:
            cfg_verify.BOUNDED_RANDOM_ARGS.pop(("net", va), None)
        else:
            cfg_verify.BOUNDED_RANDOM_ARGS[("net", va)] = previous
    if verdict.get("status") != "PASS" or not verdict.get("checked"):
        raise RuntimeError(f"CFG verification failed for {raw_symbol}: {verdict}")
    return _jsonable(verdict), trials


def build() -> dict:
    results = []
    for work in _worklist_rows():
        va = int(work["analysis_address"], 16)
        primary, extent, readable_role = EXPECTED[va]
        raw_symbol = f"FUN_{va:08x}"
        source_path = ROOT / "recon/net/src" / f"{raw_symbol}.c"
        if not source_path.is_file():
            raise RuntimeError(f"missing canonical source: {source_path}")
        source = source_path.read_text()
        first_line = source.splitlines()[0]
        address = re.search(r"@\s+(0x[0-9a-fA-F]+)", first_line)
        if not address or int(address.group(1), 16) != va:
            raise RuntimeError(f"missing raw address header in {source_path}")
        if raw_symbol not in source:
            raise RuntimeError(f"missing raw back-map in {source_path}")
        lowered = source.lower()
        if any(marker in lowered for marker in (".incbin", ".byte", ".inst")):
            raise RuntimeError(f"blob-like source forbidden in {source_path}")

        verdict, random_trials = _verify(va, raw_symbol, source)
        results.append({
            "analysis_address": f"0x{va:08x}",
            "runtime_address": work["runtime_address"],
            "primary_symbol": primary,
            "raw_symbol": raw_symbol,
            "readable_role": readable_role,
            "required_spellings": work["required_spellings"],
            "archive_family": work["archive_family"],
            "true_executable_extent": extent,
            "extent_basis": work["extent_basis"],
            "source": source_path.relative_to(ROOT).as_posix(),
            "source_sha256": _sha256(source_path),
            "cfg_verify": {
                "status": verdict["status"],
                "checked": verdict["checked"],
                "random_trials_requested": random_trials,
                "selectors": verdict.get("selectors", {}),
                "pointer_cases": verdict.get("pointer_cases", []),
                "callback_slots": verdict.get("callback_slots", []),
                "data_pointer_slots": verdict.get("data_pointer_slots", []),
                "cover_cases": verdict.get("cover_cases", 0),
            },
        })

    return {
        "schema": "g1.net.private_shard_recovery_receipt.v1",
        "shard": SHARD,
        "worklist": WORKLIST.relative_to(ROOT).as_posix(),
        "worklist_sha256": _sha256(WORKLIST),
        "policy": {
            "canonical_readable_c_only": True,
            "raw_address_headers_and_backmaps_required": True,
            "archive_or_blob_substitution_forbidden": True,
            "private_sdc_mpsl": "report_only_unchanged",
            "authoritative_verifier": "tools/cfg_verify.py",
            "bounded_move_length_strategy":
                "process-local reviewed argument-2 lengths",
            "shared_generated_name_adoption_cfg_outputs_untouched": True,
        },
        "build_observations": {
            "buffer_descriptor_helpers":
                "GCC optimize(O2) reproduces the firmware stack-frame contract; Os does not",
            "interpretation":
                "object-level optimization flags must be matched in addition to SDK version",
        },
        "summary": {
            "function_count": len(results),
            "total_true_executable_extent": sum(
                row["true_executable_extent"] for row in results),
            "cfg_pass_count": sum(
                row["cfg_verify"]["status"] == "PASS" for row in results),
            "cfg_checked_trials": sum(
                row["cfg_verify"]["checked"] for row in results),
            "cfg_directed_cover_cases": sum(
                row["cfg_verify"]["cover_cases"] for row in results),
        },
        "functions": results,
    }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    rendered = json.dumps(build(), indent=2, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.is_file() or OUTPUT.read_text() != rendered:
            raise SystemExit("net-private-5 receipt is stale")
    else:
        OUTPUT.write_text(rendered)


if __name__ == "__main__":
    main()
