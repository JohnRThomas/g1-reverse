#!/usr/bin/env python3
"""Build the fail-closed receipt for four recovered CPUNET link targets."""

from __future__ import annotations

import hashlib
import json
from pathlib import Path

import cfg_verify
from parity import emu, recon


ROOT = Path(__file__).resolve().parents[1]
EXPECTED = {
    0x0101E404: {
        "symbol": "FUN_0101e404", "readable": "controller_access_address_pattern_is_valid",
        "extent": 0x5E, "family": "softdevice_controller",
        "boundary": "final branch ends at 0x0101e462; literal 0x003fffe0 starts at 0x0101e464",
    },
    0x01025734: {
        "symbol": "FUN_01025734", "readable": "controller_deferred_irq_set_pending",
        "extent": 0x20, "family": "mpsl",
        "boundary": "BX LR ends at 0x01025754; aligned global/MMIO literals start there",
    },
    0x01025BF8: {
        "symbol": "FUN_01025bf8", "readable": "controller_apply_pending_transition",
        "extent": 0x3C, "family": "mpsl",
        "boundary": "POP return ends at 0x01025c34; state-base literal starts there",
    },
    0x0102689C: {
        "symbol": "FUN_0102689c", "readable": "controller_encoded_stride_scale",
        "extent": 0x32, "family": "softdevice_controller",
        "boundary": "POP return ends at 0x010268ce; next independent PUSH begins there",
    },
}


def _sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def _install_directed_cases() -> None:
    access_addresses = (
        0x00000000, 0x80000000, 0xFFFFFFFF, 0x55530000, 0x55540000,
        0x55550000, 0x55560000, 0x2AA90000, 0x2AAA0000, 0x2AAB0000,
        0xAAAA0000, 0x12345678, 0x8E89BED6,
    )
    cfg_verify.REVIEWED_STATE_CASES[("net", 0x0101E404)] = [
        ({0: value}, []) for value in access_addresses
    ]
    cfg_verify.REVIEWED_STATE_CASES[("net", 0x01025734)] = [
        ({}, [(0x21001C20, bytes((value,)))])
        for value in (0xFF, 0x00, 0x01, 0x1F, 0x20, 0x3F, 0x7F)
    ]
    cfg_verify.REVIEWED_ORACLE_CASES[("net", 0x0102689C)] = [
        ({0: 0, 1: 0, 2: 0}, [], {0: {0: 0}}),
        ({0: 0xFFFF0001, 1: 0xFFFFFF02, 2: 0xFFFF0001}, [], {0: {0: 1}}),
        ({0: 0xFFFF8000, 1: 0xFFFFFF03, 2: 0xFFFF0002}, [], {0: {0: 0x8000}}),
        ({0: 0xFFFFFFFF, 1: 0xFFFFFFFF, 2: 0xFFFFFFFF}, [], {0: {0: 0xFFFF}}),
        ({0: 0xABCD1234, 1: 0xDEADBEEF, 2: 0x98760007}, [], {0: {0: 0x12345678}}),
        ({0: 0x00001234, 1: 5, 2: 0xFFFF}, [], {0: {0: 0xFFFF0002}}),
    ]


def _transition_directed() -> dict:
    """Exercise absolute phase state and callback-induced state changes."""
    va, size = 0x01025BF8, 0x3C
    state_address = 0x21001C88
    ops_address = emu.SCRATCH + 0x1000
    completion, stop, replacement = 0x00080001, 0x00080005, 0x00080009

    def fixture(busy: int, phase: int, callback: int = 0):
        state = bytearray(0x20)
        state[0], state[1] = busy, phase
        state[4:8] = callback.to_bytes(4, "little")
        state[8:12] = ops_address.to_bytes(4, "little")
        ops = bytearray(0x20)
        ops[0x14:0x18] = stop.to_bytes(4, "little")
        return [(state_address, bytes(state)), (ops_address, bytes(ops))]

    source = (ROOT / "recon/net/src/FUN_01025bf8.c").read_text()
    body = source[source.index("*/") + 2:]
    compiled, error = recon.compile_func(body, "FUN_01025bf8", va)
    if error is not None:
        raise RuntimeError(error)
    candidate_body, candidate_tail, candidate_size, candidate_va = compiled
    labels = (
        "busy", "idle", "start-null", "start-callback", "active",
        "stop-null", "stop-callback", "start-callback-advances-stop",
        "stop-replaces-completion",
    )
    memory = [
        fixture(1, 1, completion), fixture(0, 0, completion), fixture(0, 1),
        fixture(0, 1, completion), fixture(0, 2, completion), fixture(0, 3),
        fixture(0, 3, completion), fixture(0, 1, completion),
        fixture(0, 3, completion),
    ]
    callback_writes = [{}, {}, {}, {}, {}, {}, {},
        {0: [(None, state_address + 1, b"\x03")]},
        {0: [(None, state_address + 4, replacement.to_bytes(4, "little"))]},
    ]
    ctx = cfg_verify.core_ctx("net")
    result = emu.compare(
        ctx["read"](va, size, 1024), va, size,
        candidate_body + candidate_tail, candidate_va, candidate_size,
        code_base=ctx["cb"], trials=len(labels), nptr=1, ret_kind="void",
        arg_overrides=[{} for _ in labels], absolute_memory_overrides=memory,
        oracle_memory_writes=callback_writes, call_arities=[0, 0],
    )
    if result != {"pass": True, "trials": 9, "checked": 9,
                  "mismatches": 0, "detail": []}:
        raise RuntimeError(f"directed transition parity failed: {result}")
    return {"status": "PASS", "checked": 9, "cases": list(labels)}


def build() -> dict:
    _install_directed_cases()
    # The hidden entry is absent from Ghidra's catalog. The exact reviewed
    # bound is injected only in this process, leaving shared verifier state on
    # disk untouched.
    cfg_verify.core_ctx("net")["sizes"][0x01025734] = 0x20
    rows = []
    for va, expected in EXPECTED.items():
        source = ROOT / "recon/net/src" / (expected["symbol"] + ".c")
        if not source.is_file():
            raise RuntimeError(f"missing canonical source: {source}")
        text = source.read_text()
        if expected["symbol"] not in text or f"0x{va:08x}" not in text:
            raise RuntimeError(f"missing raw symbol/address back-map: {source}")
        if expected["readable"] not in text:
            raise RuntimeError(f"missing readable identity: {source}")
        if "byte-exact blob" in text.lower() or "archive substitution" in text.lower():
            raise RuntimeError(f"forbidden replacement marker: {source}")
        random_trials = 40 if va == 0x01025BF8 else 0
        verified = cfg_verify.verify("net", expected["symbol"],
                                     trials_random=random_trials)
        if verified.get("status") != "PASS":
            raise RuntimeError(f"CFG verification failed: {verified}")
        row = {
            "analysis_address": f"0x{va:08x}",
            "runtime_address": f"0x{va + 0x800:08x}",
            "raw_symbol": expected["symbol"],
            "recommended_readable_name": expected["readable"],
            "archive_family": expected["family"],
            "archive_identity_is_provenance_only": True,
            "catalogued_start": va != 0x01025734,
            "true_executable_extent": expected["extent"],
            "boundary_evidence": expected["boundary"],
            "source": source.relative_to(ROOT).as_posix(),
            "source_sha256": _sha256(source),
            "cfg_verify": {key: verified[key] for key in (
                "status", "selectors", "pointer_cases", "callback_slots",
                "data_pointer_slots", "cover_cases", "checked")},
        }
        if va == 0x01025BF8:
            row["directed_state_callback_parity"] = _transition_directed()
        rows.append(row)
    return {
        "schema": "g1.net.link_gap_recovery.v1",
        "policy": {
            "canonical_c_required": True,
            "no_blobs": True,
            "archive_replacement_forbidden": True,
            "private_sdc_mpsl": "report_only_unchanged",
            "catalog_missed_extent_strategy": "process-local reviewed size injection",
        },
        "summary": {
            "function_count": len(rows),
            "total_true_executable_extent": sum(r["true_executable_extent"] for r in rows),
            "cfg_pass_count": sum(r["cfg_verify"]["status"] == "PASS" for r in rows),
            "cfg_checked_trials": sum(r["cfg_verify"]["checked"] for r in rows),
            "additional_directed_trials": 9,
        },
        "functions": rows,
    }


if __name__ == "__main__":
    print(json.dumps(build(), indent=2, sort_keys=True))
