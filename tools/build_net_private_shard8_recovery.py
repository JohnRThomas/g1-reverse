#!/usr/bin/env python3
"""Build the fail-closed CFG receipt for CPUNET private recovery shard 8."""

from __future__ import annotations

import hashlib
import json
from pathlib import Path

import cfg_verify
import net_recon_kit


ROOT = Path(__file__).resolve().parents[1]
WORKLIST = ROOT / "recon/catalogs/net_private_recovery_worklist.json"
SHARD = "net-private-8"
EXPECTED = {
    0x0100EF08: ("FUN_0100ef08", 60),
    0x0100F86C: ("FUN_0100f86c", 50),
    0x0101233C: ("FUN_0101233c", 230),
    0x01012694: ("FUN_01012694", 18),
    0x0101E1E4: ("controller_timing_defaults_apply", 144),
    0x01022E34: ("FUN_01022e34", 80),
    0x0102665C: ("FUN_0102665c", 32),
    0x01027044: ("FUN_01027044", 90),
    0x01027302: ("FUN_01027302", 196),
    0x010292EC: ("FUN_010292ec", 46),
    0x01029B38: ("FUN_01029b38", 22),
    0x0102A1E0: ("FUN_0102a1e0", 2),
    0x0102A1EA: ("sdc_byte_lock_try_acquire", 30),
}


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
    if observed != EXPECTED:
        raise RuntimeError(f"{SHARD} membership/extent changed: {observed!r}")
    return sorted(rows, key=lambda row: int(row["analysis_address"], 16))


def build() -> dict:
    results = []
    for work in _worklist_rows():
        va = int(work["analysis_address"], 16)
        symbol, extent = EXPECTED[va]
        source = ROOT / "recon/net/src" / f"{symbol}.c"
        if not source.is_file():
            raise RuntimeError(f"missing canonical source: {source}")
        text = source.read_text()
        raw = f"FUN_{va:08x}@0x{va:08x}"
        if raw not in text:
            raise RuntimeError(f"missing raw address back-map {raw} in {source}")
        lowered = text.lower()
        if "blob" in lowered or "archive substitution" in lowered:
            raise RuntimeError(f"forbidden replacement marker in {source}")

        # Four reviewed entries are absent from Ghidra's catalog. Inject the
        # worklist's reviewed executable bound into this verifier process;
        # the shared verifier/catalog code remains unchanged.
        cfg_verify.TRUE_SIZE_OVERRIDES[("net", va)] = extent
        net_recon_kit.TRUE_SIZE_OVERRIDES[va] = extent
        verified = cfg_verify.verify("net", symbol)
        if verified.get("status") != "PASS":
            raise RuntimeError(f"CFG verification failed for {symbol}: {verified}")
        results.append({
            "analysis_address": f"0x{va:08x}",
            "runtime_address": work["runtime_address"],
            "primary_symbol": symbol,
            "raw_symbol": f"FUN_{va:08x}",
            "required_spellings": work["required_spellings"],
            "archive_family": work["archive_family"],
            "catalogued_start": work["catalogued_start"],
            "true_executable_extent": extent,
            "extent_basis": work["extent_basis"],
            "source": source.relative_to(ROOT).as_posix(),
            "source_sha256": _sha256(source),
            "cfg_verify": json.loads(json.dumps({
                key: verified[key]
                for key in ("status", "selectors", "pointer_cases",
                            "callback_slots", "data_pointer_slots",
                            "cover_cases", "checked")
            }, sort_keys=True)),
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
            "catalog_missed_extent_strategy":
                "process-local reviewed true-size injection",
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
