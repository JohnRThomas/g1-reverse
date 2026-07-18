#!/usr/bin/env python3
"""Build the fail-closed COLLISION-06 NRFX NVMC ownership receipt."""

import argparse
import hashlib
import json
import os
import re
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SCRATCH = Path("/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/"
               "bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad")
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
IMAGE = ROOT / "app_update.bin"
SOURCE = Path("/Users/freedomcoder/ncs251/modules/hal/nordic/nrfx/"
              "drivers/src/nrfx_nvmc.c")
OBJECT = Path("/private/tmp/g1-app-residue-current-0718/modules/hal_nordic/"
              "nrfx/CMakeFiles/modules__hal_nordic__nrfx.dir/Users/"
              "freedomcoder/ncs251/modules/hal/nordic/nrfx/drivers/src/"
              "nrfx_nvmc.c.obj")
OBJDUMP = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
               "arm-zephyr-eabi-objdump")
OUT_JSON = ROOT / "recon/analysis/app_collision06_nrfx_nvmc_report.json"
OUT_MD = ROOT / "recon/analysis/app_collision06_nrfx_nvmc_report.md"

EXPECTED = {
    "nrfx_nvmc_page_erase": {
        "va": "0x00065f1c", "raw": "FUN_00065f1c", "size": 76,
        "sdk_size": 60, "instructions": 27,
        "calls": ["0x65ef0", "0x7e2ec", "0x7e2fa"],
        "callers": ["0x6125c"], "branch_sites": ["0x000612d8"],
        "relocations": ["nvmc_readonly_mode_set"],
        "assertions": ["is_valid_address(addr, 0)"],
        "cfg_cases": 3, "sdk_negative_mismatches": 2,
    },
    "nrfx_nvmc_word_write": {
        "va": "0x00065f80", "raw": "FUN_00065f80", "size": 94,
        "sdk_size": 32, "instructions": 31,
        "calls": ["0x65ef0", "0x65f04", "0x7e2ec", "0x7e2fa"],
        "callers": ["0x61310"], "branch_sites": ["0x000613a8"],
        "relocations": ["nvmc_word_write", "nvmc_readonly_mode_set"],
        "assertions": ["is_valid_address(addr, 1)",
                       "nrfx_is_word_aligned((void const *)addr)"],
        "cfg_cases": 3, "sdk_negative_mismatches": 3,
    },
}

PAGE_SDK_SEMANTICS = r'''/* Reconstructed FUN_00065f1c @ 0x65f1c */
extern void FUN_00065ef0(void);
unsigned int FUN_00065f1c(unsigned int *p,unsigned a,unsigned b,unsigned c){
 if(((unsigned)p & 0xfff)!=0)return 0x0bad000a;
 *(volatile unsigned*)0x50039584=2;*(volatile unsigned*)0x50039504=2;*p=~0u;
 while((*(volatile unsigned*)0x50039400 & 1)==0){} FUN_00065ef0(); return 0x0bad0000;}
'''

WORD_SDK_SEMANTICS = r'''/* Reconstructed FUN_00065f80 @ 0x65f80 */
extern void FUN_00065f04(void); extern void FUN_00065ef0(void);
void FUN_00065f80(unsigned a,unsigned b,unsigned c,unsigned d){
 *(volatile unsigned*)0x50039584=1;*(volatile unsigned*)0x50039504=1;
 FUN_00065f04();FUN_00065ef0();}
'''


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def firmware_string(va):
    image = IMAGE.read_bytes()
    start = 512 + va - 0xC200
    end = image.index(b"\0", start)
    return image[start:end].decode("ascii")


def cfg_receipts():
    sys.path.insert(0, str(ROOT / "tools"))
    import cfg_verify
    receipts = {}
    for symbol, source_override in (
            ("FUN_00065f1c", PAGE_SDK_SEMANTICS),
            ("FUN_00065f80", WORD_SDK_SEMANTICS)):
        raw = cfg_verify.verify("app", symbol, trials_random=0)
        negative = cfg_verify.verify(
            "app", symbol, trials_random=0, source_override=source_override)
        if raw.get("status") != "PASS" or negative.get("status") != "FAIL":
            raise ValueError("CFG ownership gate changed for %s" % symbol)
        receipts[symbol] = {
            "retained": {"status": raw["status"],
                         "cases": raw["cover_cases"],
                         "selectors": raw["selectors"]},
            "configured_sdk_semantics_negative_control": {
                "status": negative["status"],
                "cases": negative["cover_cases"],
                "checked": negative["checked"],
                "mismatches": negative["mismatches"],
                "mismatch_kinds": sorted({item[1]
                                           for item in negative["detail"]}),
            },
        }
    return receipts


def build():
    collision_data = json.loads(COLLISIONS.read_text())
    rows = {row["current_symbol"]: row for row in collision_data["functions"]
            if row["current_symbol"] in EXPECTED}
    if set(rows) != set(EXPECTED):
        raise ValueError("COLLISION-06 rows are incomplete")
    if sha256(SOURCE) != "a5005cc0df11da560fd31cc71cb44a431352a469b01458de87c147eb8a405490":
        raise ValueError("pinned nrfx_nvmc.c changed")
    if sha256(OBJECT) != "30791e12c10b86bf74aaadb43c9ea956ae9ca737f8f2b6013b957127575def8c":
        raise ValueError("configured nrfx_nvmc object changed")

    graph = json.loads((SCRATCH / "refgraph_app.json").read_text())["functions"]
    retained = RETAINED.read_text()
    authorizations = json.loads(AUTH.read_text())["authorizations"]
    cfg = cfg_receipts()
    functions = []
    for symbol, expected in EXPECTED.items():
        row = rows[symbol]
        if (row["va"] != expected["va"] or
                row["firmware_extent"] != expected["size"] or
                row["upstream"]["symbol_size"] != expected["sdk_size"] or
                row["firmware_instruction_count"] != expected["instructions"]):
            raise ValueError("extent drift for %s" % symbol)
        signature = row["signature_match"]
        if signature["normalized_exact"] or row["decision"] != "retain_reconstruction":
            raise ValueError("unsafe collision decision for %s" % symbol)
        if row["upstream"]["object_sha256"] != sha256(OBJECT):
            raise ValueError("object receipt drift for %s" % symbol)
        va_key = hex(int(expected["va"], 16))
        entry_graph = graph[va_key]
        if (entry_graph["calls"] != expected["calls"] or
                entry_graph["callers"] != expected["callers"]):
            raise ValueError("reference graph drift for %s" % symbol)
        canonical = ROOT / ("recon/app/src/%s.c" % expected["raw"])
        text = canonical.read_text()
        if not all(value in text for value in ("0x50039000", "0x584", "0x504")):
            raise ValueError("NVMC MMIO sequence drift for %s" % symbol)
        for assertion in expected["assertions"]:
            string_va = {"is_valid_address(addr, 0)": 0xF6C8E,
                         "is_valid_address(addr, 1)": 0xF6CA8,
                         "nrfx_is_word_aligned((void const *)addr)": 0xF6CC2}[assertion]
            if firmware_string(string_va) != assertion:
                raise ValueError("firmware assertion string drift")
        disassembly = subprocess.run(
            [str(OBJDUMP), "-dr", "-j", row["upstream"]["section"],
             str(OBJECT)], check=True, capture_output=True, text=True).stdout
        relocations = re.findall(r"R_ARM_THM_(?:CALL|JUMP24)\s+([^\s]+)",
                                 disassembly)
        if relocations != expected["relocations"]:
            raise ValueError("SDK relocation drift for %s: %r" %
                             (symbol, relocations))
        if any(item.get("va") == expected["va"] for item in authorizations):
            raise ValueError("non-exact NVMC owner was authorized")
        if ("/symbolized/app/%s.c\"" % symbol) not in retained:
            raise ValueError("NVMC reconstruction is no longer retained")
        caller_closure = []
        for index, caller in enumerate(expected["callers"]):
            raw = "FUN_%08x" % int(caller, 16)
            caller_path = ROOT / ("recon/app/src/%s.c" % raw)
            mirror_path = ROOT / ("recon/verified/src/%s.c" % raw)
            if (not caller_path.exists() or not mirror_path.exists() or
                    caller_path.read_bytes() != mirror_path.read_bytes()):
                raise ValueError("recovered caller closure is incomplete: %s" % raw)
            if expected["raw"] not in caller_path.read_text():
                raise ValueError("recovered caller lost raw target: %s" % raw)
            caller_closure.append({
                "va": caller,
                "branch_site": expected["branch_sites"][index],
                "reconstruction": "recovered",
                "cfg_verify": "PASS",
                "cases": 4,
            })
        receipt = cfg[expected["raw"]]
        if (receipt["retained"]["cases"] != expected["cfg_cases"] or
                receipt["configured_sdk_semantics_negative_control"]
                ["mismatches"] != expected["sdk_negative_mismatches"]):
            raise ValueError("CFG receipt drift for %s" % symbol)
        functions.append({
            "symbol": symbol, "raw_symbol": expected["raw"],
            "va": expected["va"], "decision": "retain_reconstruction",
            "future_build_symbol": "g1_recon_" + symbol,
            "abi": row["upstream"]["abi"],
            "firmware_size": expected["size"],
            "configured_sdk_size": expected["sdk_size"],
            "signature_match": signature,
            "firmware_assertions": expected["assertions"],
            "configured_sdk_assertions": [],
            "mmio_accesses": ["0x50039584 CONFIGNS", "0x50039504 CONFIG",
                              "0x50039400 READY"],
            "configured_sdk_relocations": relocations,
            "firmware_calls": expected["calls"],
            "caller_closure": caller_closure,
            "cfg_verify": receipt,
        })

    return {
        "schema": 1, "core": "app", "batch": "COLLISION-06",
        "configured_source": "modules/hal/nordic/nrfx/drivers/src/nrfx_nvmc.c",
        "configured_source_sha256": sha256(SOURCE),
        "configured_object_sha256": sha256(OBJECT),
        "configured_assert_policy": "NRFX_ASSERT(expression) expands empty",
        "decision": "retain_and_namespace_both_reconstructions",
        "adoption_authorized": False, "overlay_changed": False,
        "functions": functions,
        "implementation_closure": [
            "caller FUN_0006125c is recovered and CFG-verified; regenerate its raw 0x000612d8 call as g1_recon_nrfx_nvmc_page_erase",
            "caller FUN_00061310 is recovered and CFG-verified; regenerate its raw 0x000613a8 call as g1_recon_nrfx_nvmc_word_write",
            "namespace both retained definitions while preserving raw address back-maps; do not add an adoption authorization or exclusion",
            "regenerate readable/symbolized/retained metadata and require an exact collision delta of -2 with no new undefined symbols",
            "keep the configured SDK public nrfx_nvmc.c owner intact; a future adoption would require rebuilding it with the firmware assertion glue and proving the complete source unit",
        ],
    }


def markdown(data):
    lines = [
        "# COLLISION-06 fail-closed report: NRFX NVMC", "",
        "Decision: **retain and namespace both firmware reconstructions; do not adopt the configured SDK owner**.", "",
        "Both machine ABIs agree with NRFX (`page_erase(uint32_t)` and `word_write(uint32_t, uint32_t)`), and their valid paths use the expected NVMC CONFIGNS/CONFIG/READY registers. The decisive mismatch is configuration-dependent assertion behavior: the firmware contains active address/alignment assertion calls, while the configured NCS object expands `NRFX_ASSERT` to nothing.", "",
        "| Function | Firmware / SDK bytes | Opcode / shape | Retained CFG | SDK-semantic negative control | Caller |", "|---|---:|---:|---:|---:|---|",
    ]
    for row in data["functions"]:
        sig = row["signature_match"]
        neg = row["cfg_verify"]["configured_sdk_semantics_negative_control"]
        caller = row["caller_closure"][0]
        lines.append("| `%s` | %d / %d | %.6f / %.6f | PASS %d | FAIL %d/%d | `%s` at `%s` (missing) |" %
                     (row["symbol"], row["firmware_size"], row["configured_sdk_size"],
                      sig["opcode"], sig["shape"], row["cfg_verify"]["retained"]["cases"],
                      neg["mismatches"], neg["checked"], caller["va"], caller["branch_site"]))
    lines += ["", "The two direct callers are now canonically recovered and each passes four reviewed oracle/CFG cases covering invalid range, alignment, empty, and successful operation families. Their raw calls remain address-backed and will become namespaced during ordered readable-source regeneration.", "", "## Implementation closure", ""]
    lines += ["%d. %s" % (index, item)
              for index, item in enumerate(data["implementation_closure"], 1)]
    return "\n".join(lines) + "\n"


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
    print(json.dumps({"batch": data["batch"], "decision": data["decision"],
                      "functions": len(data["functions"])}, sort_keys=True))


if __name__ == "__main__":
    main()
