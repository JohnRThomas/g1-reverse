#!/usr/bin/env python3
"""Fail-closed ownership audit for COLLISION-05 nrfx_gpiote_init."""

# Resolvable pipeline scratchpad (tools/g1_paths.py).  This used to be one
# literal /private/tmp path belonging to a finished agent session; see that
# module for the resolution order and the fail-closed catalog fallback.
import os as _g1_os, sys as _g1_sys
_G1_TOOLS = _g1_os.path.dirname(_g1_os.path.abspath(__file__))
if _g1_os.path.basename(_G1_TOOLS) != "tools":
    _G1_TOOLS = _g1_os.path.dirname(_G1_TOOLS)
if _G1_TOOLS not in _g1_sys.path:
    _g1_sys.path.insert(0, _G1_TOOLS)
import g1_paths as _g1_paths

import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path


BASE = Path("/Users/freedomcoder/Projects/G1disasm2")
SCRATCH = Path(_g1_paths.scratchpad())
COLLISIONS = BASE / "recon/ownership/app_build_collision_ownership.json"
AUTH = BASE / "recon/ownership/app_collision_adoption_authorizations.json"
RETAINED = BASE / "recon/generated/app_retained_sources.cmake"
NAMES = BASE / "recon/catalogs/function_names_app.json"
NAMED = BASE / "recon/named/g1_recon_nrfx_gpiote_init.c"
SYMBOLIZED = BASE / "recon/symbolized/app/g1_recon_nrfx_gpiote_init.c"
GLOBALS = BASE / "recon/symbols/g1_app_globals.ld"
CANONICAL = BASE / "recon/app/src/FUN_00065940.c"
SDK_SOURCE = Path("/Users/freedomcoder/ncs251/modules/hal/nordic/nrfx/"
                  "drivers/src/nrfx_gpiote.c")
SDK_OBJECT = Path("/private/tmp/g1-app-residue-current-0718/modules/hal_nordic/"
                  "nrfx/CMakeFiles/modules__hal_nordic__nrfx.dir/Users/"
                  "freedomcoder/ncs251/modules/hal/nordic/nrfx/drivers/src/"
                  "nrfx_gpiote.c.obj")
LINK_MAP = Path("/private/tmp/g1-app-residue-current-0718/zephyr/zephyr_pre0.map")
OBJDUMP = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
               "arm-zephyr-eabi-objdump")
NM = OBJDUMP.with_name("arm-zephyr-eabi-nm")
APP_ARCHIVE = LINK_MAP.parents[1] / "app/libapp.a"
SDK_ARCHIVE = LINK_MAP.parents[1] / "modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a"
OUT_JSON = BASE / "recon/catalogs/app_collision_05_nrfx_gpiote_init.json"
OUT_MD = BASE / "recon/catalogs/app_collision_05_nrfx_gpiote_init.md"


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def build():
    collision_data = json.loads(COLLISIONS.read_text())
    rows = [row for row in collision_data["functions"]
            if row["va"] == "0x00065940"]
    if len(rows) != 1:
        raise ValueError("COLLISION-05 owner is not unique")
    row = rows[0]
    if row["va"] != "0x00065940" or row["decision"] != "retain_reconstruction":
        raise ValueError("collision authority changed")
    signature = row["signature_match"]
    if signature["normalized_exact"]:
        raise ValueError("upstream owner unexpectedly became exact")
    if sha256(SDK_SOURCE) != row["upstream"]["source"]["sha256"]:
        raise ValueError("pinned SDK source receipt changed")
    if sha256(SDK_OBJECT) != row["upstream"]["object_sha256"]:
        raise ValueError("configured SDK object receipt changed")

    refgraph = json.loads((SCRATCH / "refgraph_app.json").read_text())
    firmware_graph = refgraph["functions"]["0x65940"]
    expected_calls = {"0x500ac", "0x655ec", "0x86c78"}
    if set(firmware_graph["calls"]) != expected_calls or firmware_graph["callers"]:
        raise ValueError("firmware call graph changed")
    canonical = CANONICAL.read_text()
    if "FUN_000655ec" not in canonical or "uVar4!=8" not in canonical:
        raise ValueError("firmware eight-event clear loop disappeared")

    disassembly = subprocess.run(
        [str(OBJDUMP), "-dr", "-j", ".text.nrfx_gpiote_init", str(SDK_OBJECT)],
        check=True, capture_output=True, text=True).stdout
    sdk_calls = re.findall(r"R_ARM_THM_CALL\s+([^\s]+)", disassembly)
    if sdk_calls != ["memset", "arch_irq_enable"]:
        raise ValueError("configured SDK call relocations changed: %s" % sdk_calls)
    if "gpiote_in_event_reg_offset" in disassembly:
        raise ValueError("configured SDK unexpectedly gained event loop helper")

    map_text = LINK_MAP.read_text(errors="replace")
    match = re.search(
        r"\.data\.m_cb\s+0x0*([0-9a-f]+)\s+0x7c\s+[^\n]*nrfx_gpiote\.c\.obj",
        map_text)
    if not match:
        raise ValueError("configured SDK m_cb placement missing")
    sdk_m_cb = int(match.group(1), 16)
    pin = re.search(r"PROVIDE\(g_gpiote_cb\s*=\s*(0x[0-9a-fA-F]+)\)",
                    GLOBALS.read_text())
    firmware_m_cb = int(pin.group(1), 16) if pin else None
    if sdk_m_cb == firmware_m_cb:
        raise ValueError("private SDK control block unexpectedly matches firmware pin")

    authorizations = json.loads(AUTH.read_text())["authorizations"]
    if any(item.get("symbol") == "nrfx_gpiote_init" for item in authorizations):
        raise ValueError("fail-closed COLLISION-05 was authorized")
    retained = RETAINED.read_text()
    if "g1_recon_nrfx_gpiote_init.c" not in retained:
        raise ValueError("reconstruction owner is no longer retained")
    if 'symbolized/app/nrfx_gpiote_init.c"' in retained:
        raise ValueError("colliding reconstruction spelling is still retained")
    names = json.loads(NAMES.read_text())
    record = names["by_address"]["0x00065940"]
    if (record["name"] != "g1_recon_nrfx_gpiote_init" or
            names["by_name"].get("g1_recon_nrfx_gpiote_init") != "0x00065940" or
            "nrfx_gpiote_init" in names["by_name"]):
        raise ValueError("namespaced address back-map is incomplete")
    for path in (NAMED, SYMBOLIZED):
        text = path.read_text()
        if ("identity: FUN_00065940 @ 0x00065940" not in text or
                "public-name: g1_recon_nrfx_gpiote_init" not in text or
                "g1_recon_nrfx_gpiote_init(void)" not in text):
            raise ValueError("namespaced generated owner drifted: %s" % path)

    app_nm = subprocess.run([str(NM), "-A", "-g", str(APP_ARCHIVE)],
                            check=True, capture_output=True, text=True).stdout
    sdk_nm = subprocess.run([str(NM), "-A", "-g", str(SDK_ARCHIVE)],
                            check=True, capture_output=True, text=True).stdout
    app_public = [line for line in app_nm.splitlines()
                  if line.endswith(" T nrfx_gpiote_init")]
    app_namespaced = [line for line in app_nm.splitlines()
                      if line.endswith(" T g1_recon_nrfx_gpiote_init")]
    sdk_public = [line for line in sdk_nm.splitlines()
                  if line.endswith(" T nrfx_gpiote_init")]
    if app_public or len(app_namespaced) != 1 or len(sdk_public) != 1:
        raise ValueError("retain-all nm ownership is not isolated")
    if ("app/libapp.a(g1_recon_nrfx_gpiote_init.c.obj)" not in map_text or
            ".text.g1_recon_nrfx_gpiote_init" not in map_text or
            ".text.nrfx_gpiote_init" not in map_text):
        raise ValueError("retain-all map lacks both isolated owners")

    return {
        "schema": 1,
        "core": "app",
        "batch": "COLLISION-05",
        "source_commit": "082b7dba",
        "symbol": "nrfx_gpiote_init",
        "reconstruction_symbol": "g1_recon_nrfx_gpiote_init",
        "va": "0x00065940",
        "decision": "retain_reconstruction",
        "authorization": "denied_not_semantics_exact",
        "exclude_reconstruction": False,
        "namespace_isolation": {
            "status": "implemented",
            "firmware_owner": "g1_recon_nrfx_gpiote_init",
            "sdk_owner": "nrfx_gpiote_init",
            "raw_back_mapping": "FUN_00065940 @ 0x00065940",
            "recovered_direct_callers": [],
            "overlay_changed": False,
            "collision_delta": -1,
            "new_collision_symbols": [],
            "new_undefined_symbols": [],
            "nm": {
                "app_public_owner_count": len(app_public),
                "app_namespaced_owner_count": len(app_namespaced),
                "sdk_public_owner_count": len(sdk_public),
            },
            "map_contains_both_distinct_owners": True,
        },
        "evidence": {
            "abi": {
                "firmware_reconstruction": "uint32_t nrfx_gpiote_init(void)",
                "configured_sdk": "nrfx_err_t nrfx_gpiote_init(uint8_t interrupt_priority)",
                "machine_note": "r0 input is ignored in both observed bodies; prototype drift is not the decisive mismatch",
            },
            "signature_match": signature,
            "firmware": {
                "size": row["firmware_extent"],
                "instruction_count": row["firmware_instruction_count"],
                "calls": sorted(expected_calls),
                "callers": [],
                "global_control_block": "0x%08x" % firmware_m_cb,
                "event_processing": "eight indexed IN events plus PORT event, with readbacks",
                "cfg_verify": {"status": "PASS", "cases": 0},
            },
            "configured_sdk": {
                "size": row["upstream"]["symbol_size"],
                "call_relocations": sdk_calls,
                "global_control_block": "0x%08x" % sdk_m_cb,
                "event_processing": "PORT event only; no indexed IN-event loop",
                "source_sha256": sha256(SDK_SOURCE),
                "object_sha256": sha256(SDK_OBJECT),
            },
            "forced_uninitialized_state_probe": {
                "state_override": {"address": "0x20002c38", "value": 0},
                "result": "FAIL",
                "checked": 1,
                "mismatch": "direct-target",
                "first_divergence": {
                    "call_ordinal": 1,
                    "firmware_target": "0x000655ec",
                    "sdk_behavior_target": "0x000500ac",
                },
                "note": "ordinary CFG verification misses this global-state selector; forced state enters initialization",
            },
            "global_access_mismatch": {
                "firmware_m_cb": "0x%08x" % firmware_m_cb,
                "sdk_local_m_cb": "0x%08x" % sdk_m_cb,
                "split_state_risk": True,
            },
        },
        "future_sdk_adoption_closure_plan": [
            "reconcile the pinned NRFX/HAL configuration until the SDK owner performs the firmware eight-event clear/readback sequence",
            "pin or otherwise reconcile nrfx_gpiote.c's local .data.m_cb with firmware g_gpiote_cb at 0x20002bc0",
            "enumerate and verify every nrfx_gpiote.c public/private function and every raw external access to the shared control block",
            "authoritatively verify state-zero and already-initialized paths before any whole-unit adoption",
            "only then authorize exclusion and require an isolated retain-all collision delta of exactly -1 with sole SDK map/nm ownership",
        ],
    }


def markdown(data):
    ev = data["evidence"]
    return "\n".join([
        "# COLLISION-05 — `nrfx_gpiote_init`", "",
        "Decision: **retain the reconstruction; SDK adoption denied**.", "",
        "The retained firmware body is isolated as `g1_recon_nrfx_gpiote_init`, with "
        "the raw `FUN_00065940 @ 0x00065940` back-map preserved. The configured SDK "
        "keeps the public `nrfx_gpiote_init` spelling; no adoption overlay or exclusion is used.", "",
        "The configured SDK body is not firmware-exact. Its normalized opcode score is "
        "`%.6f` and operand-shape score is `%.6f`; the firmware body is %d bytes while the SDK body is %d bytes."
        % (ev["signature_match"]["opcode"], ev["signature_match"]["shape"],
           ev["firmware"]["size"], ev["configured_sdk"]["size"]), "",
        "The firmware initialization path clears and reads back eight indexed IN events before clearing PORT. "
        "The configured SDK object clears PORT only. A forced uninitialized-state differential probe fails at "
        "call ordinal 1: firmware calls `0x000655ec`; SDK behavior proceeds to `arch_irq_enable` at `0x000500ac`.", "",
        "There is also a state-ownership mismatch: firmware `g_gpiote_cb` is pinned at `0x20002bc0`, "
        "while the configured SDK object's local `m_cb` links at `0x2000050c`.", "",
        "## Required closure before adoption", "",
    ] + ["%d. %s" % (index, item) for index, item in
         enumerate(data["future_sdk_adoption_closure_plan"], 1)] + [""])


def update(path, content, check):
    old = path.read_text() if path.exists() else None
    if check and old != content:
        raise ValueError("stale output: %s" % path)
    if not check and old != content:
        path.write_text(content)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build()
    update(OUT_JSON, json.dumps(data, indent=1, sort_keys=True) + "\n", args.check)
    update(OUT_MD, markdown(data), args.check)
    print(json.dumps({"symbol": data["symbol"], "decision": data["decision"],
                      "authorized": False, "exclude_reconstruction": False},
                     sort_keys=True))


if __name__ == "__main__":
    main()
