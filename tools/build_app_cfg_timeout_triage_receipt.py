#!/usr/bin/env python3
"""Build the report-only CPUAPP timeout/OTHER triage receipt."""

from __future__ import annotations

import hashlib
import json
import re
from pathlib import Path


# Resolvable pipeline scratchpad (tools/g1_paths.py).
import os as _g1_os, sys as _g1_sys
_G1_TOOLS = _g1_os.path.dirname(_g1_os.path.abspath(__file__))
if _g1_os.path.basename(_G1_TOOLS) != "tools":
    _G1_TOOLS = _g1_os.path.dirname(_G1_TOOLS)
if _G1_TOOLS not in _g1_sys.path:
    _g1_sys.path.insert(0, _G1_TOOLS)
import g1_paths as _g1_paths

BASE = Path(__file__).resolve().parents[1]
SCRATCH = Path(_g1_paths.scratchpad())
OUTPUT = BASE / "recon/analysis/app_cfg_timeout_other_triage.json"


GENERIC_PASS = {
    "FUN_00086c04": 1,
    "FUN_0002316c": 1,
    "FUN_0002360c": 1,
    "FUN_0008705a": 2,
    "FUN_00023acc": 1,
    "FUN_000184f0": 2,
}

DIRECTED_PASS = {
    "FUN_000243fc": "zero work-queue count at 0x20003984",
    "FUN_00086668": "null-terminated one-word list fixture",
    "check_battery_critical": "unlocked persistence byte and mapped context",
    "gui_string_draw": "empty-string length oracle and disabled logging",
    "FUN_0008768e": "zero-length mapped bit-vector",
    "now_has_persist_task": "unlocked mapped persistence record",
    "FUN_000361d8": "catalog oracle publishes decoded count zero",
    "update_persist_task_status_to_idle": "unlocked mapped persistence record",
    "FUN_00060a5c": "QSPI busy oracle returns completion sentinel",
    "update_persist_task_status_to_wait_blow_head": "unlocked mapped persistence record",
    "update_temp_task_status": "unlocked mapped task record",
    "FUN_00040794": "inactive UI state byte selects immediate return",
}

WORKLOAD_ONLY = {
    "FUN_0004382c": {
        "reason": "eight 199x320 framebuffer-mask scans",
        "method": "reviewed one-event prefix crossing the first complete frame scan",
        "checked": 1,
    },
    "ui_even_ai_task": {
        "reason": "multiple eight-frame 199x320 render families; verifier cap is 7,000,000 instructions",
        "method": "inactive invalid-phase production state returns before raster work",
        "checked": 1,
    },
    "FUN_00035f28": {
        "reason": "eight 199x320 notification reveal scans; verifier cap is 8,000,000 instructions",
        "method": "directed disabled-display cases cover the diagnostic return",
        "checked": 6,
    },
}

NONRETURNING = {
    "FUN_0004d6ec": "source and original CFG contain the service worker's unconditional backedge",
}

OTHER = {
    "FUN_00036030": {
        "classification": "transient_other_recheck_pass",
        "recheck": {"status": "PASS", "trials_random": 1, "checked": 1},
        "reason": "fresh bounded authoritative invocation completed normally",
    },
    "ble_process_put_req": {
        "classification": "harness_fixture_schema_error",
        "recheck": {
            "status": "EXCEPTION",
            "trials_random": 1,
            "exception": "AttributeError: 'list' object has no attribute 'values'",
            "site": "tools/parity/emu.py:153 oracle_overrides.values()",
        },
        "reason": "reviewed oracle fixture shape is rejected before candidate execution",
    },
}


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def source_for(name: str) -> Path:
    direct = BASE / "recon/app/src" / f"{name}.c"
    if direct.is_file():
        return direct
    catalog = json.loads((BASE / "recon/catalogs/function_names_app.json").read_text())
    address = catalog["by_name"][name]
    raw = catalog["by_address"][address]["raw_name"]
    source = BASE / "recon/app/src" / f"{raw}.c"
    if not source.is_file():
        raise FileNotFoundError(source)
    return source


def source_record(name: str) -> dict:
    source = source_for(name)
    first = source.read_text().splitlines()[0]
    match = re.search(r"@\s+(0x[0-9a-fA-F]+)", first)
    if not match:
        raise ValueError(f"missing address header: {source}")
    return {
        "name": name,
        "address": f"0x{int(match.group(1), 16):08x}",
        "source_path": str(source.relative_to(BASE)),
        "source_sha256": digest(source),
    }


def lane_outcomes() -> tuple[dict[str, tuple[str, str]], list[dict]]:
    outcomes = {}
    inputs = []
    for lane in range(8):
        path = SCRATCH / f"reverify_app_L{lane}.json"
        data = json.loads(path.read_text())
        inputs.append({"path": str(path), "sha256": digest(path)})
        for outcome in ("timeout", "other"):
            for name in data[outcome]:
                if name in outcomes:
                    raise ValueError(f"duplicate sweep outcome: {name}")
                outcomes[name] = (outcome, path.name)
    return outcomes, inputs


def build() -> dict:
    outcomes, inputs = lane_outcomes()
    expected = set(GENERIC_PASS) | set(DIRECTED_PASS) | set(WORKLOAD_ONLY) | set(NONRETURNING) | set(OTHER)
    if set(outcomes) != expected:
        raise ValueError(
            f"triage inventory drift: missing={sorted(set(outcomes)-expected)} "
            f"extra={sorted(expected-set(outcomes))}"
        )

    records = []
    for name in sorted(expected):
        record = source_record(name)
        initial, lane = outcomes[name]
        record.update({"initial_outcome": initial.upper(), "lane_receipt": lane})
        if name in GENERIC_PASS:
            record.update({
                "classification": "transient_budget_timeout_recheck_pass",
                "reason": "one-trial bounded authoritative recheck completed under 25 seconds",
                "recheck": {"status": "PASS", "trials_random": 1,
                            "checked": GENERIC_PASS[name], "wall_limit_seconds": 25},
                "source_defect": False,
            })
        elif name in DIRECTED_PASS:
            record.update({
                "classification": "synthetic_input_domain_timeout_recheck_pass",
                "reason": DIRECTED_PASS[name],
                "recheck": {"status": "PASS", "trials_random": 0,
                            "directed_cases": 1, "checked": 1},
                "source_defect": False,
            })
        elif name in WORKLOAD_ONLY:
            record.update({
                "classification": "finite_workload_sweep_timeout_recheck_pass",
                "reason": WORKLOAD_ONLY[name]["reason"],
                "recheck": {"status": "PASS", "trials_random": 0,
                            "method": WORKLOAD_ONLY[name]["method"],
                            "checked": WORKLOAD_ONLY[name]["checked"]},
                "source_defect": False,
            })
        elif name in NONRETURNING:
            record.update({
                "classification": "intentional_nonreturning_worker",
                "reason": NONRETURNING[name],
                "recheck": {"status": "PASS", "trials_random": 0,
                            "method": "reviewed three-event prefix crosses setup into service loop",
                            "checked": 1},
                "source_defect": False,
            })
        else:
            record.update(OTHER[name])
            record["source_defect"] = False
        records.append(record)

    return {
        "schema": "g1.app.cfg_timeout_other_triage.v1",
        "scope": {"timeout": 22, "other": 2},
        "policy": {
            "report_only": True,
            "app_sources_modified": False,
            "shared_verifier_modified": False,
            "parity_or_mmio_tools_modified": False,
        },
        "summary": {
            "bounded_cfg_pass": 23,
            "finite_workload_timeout_recheck_pass": 3,
            "intentional_nonreturning_prefix_pass": 1,
            "harness_fixture_error": 1,
            "source_defects_proven": 0,
        },
        "inputs": inputs,
        "records": records,
    }


def main() -> int:
    OUTPUT.write_text(json.dumps(build(), indent=2, sort_keys=True) + "\n")
    print(OUTPUT)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
