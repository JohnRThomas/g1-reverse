#!/usr/bin/env python3
"""Build the fail-closed CFG receipt for CPUNET private recovery shard 6."""

from __future__ import annotations

import hashlib
import json
import re
from pathlib import Path

import cfg_verify


ROOT = Path(__file__).resolve().parents[1]
WORKLIST = ROOT / "recon/catalogs/net_private_recovery_worklist.json"
SHARD = "net-private-6"
EXPECTED = {
    0x0101DDA8: ("schedule_node_tail_get", 20,
                 "return the tail of the controller schedule-node list"),
    0x0101DED0: ("FUN_0101ded0", 176,
                 "select a common schedule quantum from registered constraints"),
    0x0101E2FC: ("FUN_0101e2fc", 156,
                 "validate and stage a four-way controller request"),
    0x010207CC: ("FUN_010207cc", 72,
                 "program controller and radio deadline state"),
    0x01021940: ("FUN_01021940", 48,
                 "clamp a signed per-channel setting"),
    0x01025998: ("FUN_01025998", 236,
                 "alignment-aware non-overlapping byte copy"),
    0x01026D16: ("FUN_01026d16", 40,
                 "adapt a packed pair of 16-bit controller fields"),
    0x010280BE: ("FUN_010280be", 26,
                 "invoke a controller helper with its enabled selector"),
    0x010282FC: ("controller_default_bounds_build", 126,
                 "build bounded controller timing defaults"),
    0x0102894A: ("FUN_0102894a", 60,
                 "dispatch a compact controller command record"),
    0x0102941C: ("FUN_0102941c", 32,
                 "apply one normalized enable flag to two domains"),
    0x010298A8: ("FUN_010298a8", 18,
                 "normalize controller mode flags"),
}

# Argument 2 is a caller-owned byte count. Full-width random values merely
# manufacture multi-billion-iteration copies. These reviewed values cover
# empty, byte-tail, aligned word, double-word, and the original 44-byte fast
# path boundary without changing shared cfg_verify policy.
COPY_LENGTHS = (0, 1, 2, 3, 4, 7, 8, 43, 44, 47, 48, 49, 52)


def _sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def _worklist_rows() -> list[dict]:
    document = json.loads(WORKLIST.read_text())
    if document["schema"] != "g1.net.private_recovery_worklist.v1":
        raise RuntimeError("unexpected private-recovery worklist schema")
    if document["policy"] != {
        "no_blobs": True,
        "private_sdc_mpsl_report_only": True,
        "archive_replacement_forbidden": True,
        "fail_closed": True,
    }:
        raise RuntimeError("private-recovery policy changed")
    rows = [row for row in document["entries"]
            if row["suggested_shard"] == SHARD]
    observed = {
        int(row["analysis_address"], 16):
        (row["primary_symbol"], row["true_executable_extent"])
        for row in rows
    }
    expected = {va: values[:2] for va, values in EXPECTED.items()}
    if observed != expected:
        raise RuntimeError(f"{SHARD} membership/extent changed: {observed!r}")
    return sorted(rows, key=lambda row: int(row["analysis_address"], 16))


def _verify(va: int, raw_symbol: str) -> dict:
    previous = cfg_verify.BOUNDED_RANDOM_ARGS.get(("net", va))
    try:
        if va == 0x01025998:
            cfg_verify.BOUNDED_RANDOM_ARGS[("net", va)] = {
                2: COPY_LENGTHS,
            }
            result = cfg_verify.verify("net", raw_symbol, trials_random=13)
        else:
            result = cfg_verify.verify("net", raw_symbol)
    finally:
        if previous is None:
            cfg_verify.BOUNDED_RANDOM_ARGS.pop(("net", va), None)
        else:
            cfg_verify.BOUNDED_RANDOM_ARGS[("net", va)] = previous
    if result.get("status") != "PASS" or not result.get("checked"):
        raise RuntimeError(f"CFG verification failed for {raw_symbol}: {result}")
    return result


def build() -> dict:
    results = []
    for work in _worklist_rows():
        va = int(work["analysis_address"], 16)
        primary, extent, readable_role = EXPECTED[va]
        raw_symbol = f"FUN_{va:08x}"
        source = ROOT / "recon/net/src" / f"{raw_symbol}.c"
        if not source.is_file():
            raise RuntimeError(f"missing canonical source: {source}")
        text = source.read_text()
        header = re.compile(
            rf"{re.escape(raw_symbol)}\s*@\s*0x{va:08x}", re.IGNORECASE)
        definition = re.compile(rf"\b{re.escape(raw_symbol)}\s*\(")
        if not header.search(text) or not definition.search(text):
            raise RuntimeError(f"missing raw address back-map in {source}")
        lowered = text.lower()
        if any(marker in lowered for marker in
               (".incbin", "__asm__", "archive substitution", "byte-exact blob")):
            raise RuntimeError(f"forbidden replacement construct in {source}")

        # Normalize tuples and integer selector keys exactly as the persisted
        # JSON representation does, so receipt equality is deterministic.
        verified = json.loads(json.dumps(_verify(va, raw_symbol)))
        results.append({
            "analysis_address": f"0x{va:08x}",
            "runtime_address": work["runtime_address"],
            "primary_symbol": primary,
            "raw_symbol": raw_symbol,
            "source_symbol": raw_symbol,
            "readable_role": readable_role,
            "required_spellings": work["required_spellings"],
            "archive_family": work["archive_family"],
            "catalogued_start": work["catalogued_start"],
            "true_executable_extent": extent,
            "extent_basis": work["extent_basis"],
            "source": source.relative_to(ROOT).as_posix(),
            "source_sha256": _sha256(source),
            "cfg_verify": {
                key: verified[key]
                for key in ("status", "selectors", "pointer_cases",
                            "callback_slots", "data_pointer_slots",
                            "cover_cases", "checked")
            },
        })

    return {
        "schema": "g1.net.private_shard_recovery_receipt.v1",
        "shard": SHARD,
        "worklist": WORKLIST.relative_to(ROOT).as_posix(),
        "worklist_sha256": _sha256(WORKLIST),
        "policy": {
            "canonical_c_required": True,
            "no_blobs": True,
            "archive_replacement_forbidden": True,
            "private_sdc_mpsl": "report_only_unchanged",
            "cfg_verifier": "tools/cfg_verify.py",
            "bounded_copy_length_strategy":
                "process-local reviewed argument-2 lengths",
            "shared_verifier_mutated": False,
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


if __name__ == "__main__":
    print(json.dumps(build(), indent=2, sort_keys=True))
