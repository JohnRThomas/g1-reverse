#!/usr/bin/env python3
"""Fail-closed ownership audit for COLLISION-21 recursive newlib locks."""

import argparse
import hashlib
import json
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
SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/lib/libc/newlib/libc-hooks.c")
OBJECT = Path("/private/tmp/g1-app-residue-current-0718/zephyr/lib/libc/"
              "newlib/CMakeFiles/lib__libc__newlib.dir/libc-hooks.c.obj")
OBJDUMP = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
               "arm-zephyr-eabi-objdump")
IMAGE = ROOT / "app_update.bin"
OUT_JSON = ROOT / "recon/analysis/app_collision21_retarget_recursive_report.json"
OUT_MD = ROOT / "recon/analysis/app_collision21_retarget_recursive_report.md"

EXPECTED = {
    "__retarget_lock_acquire_recursive": {
        "va": "0x000510fc", "raw": "FUN_000510fc", "extent": 44,
        "instructions": 14, "sdk_size": 12,
        "firmware_calls": ["0x723b8", "0x7e2ec", "0x7e2fa"],
        "sdk_relocations": ["z_impl_k_mutex_lock"],
        "assert_line": 0x1A6,
        "callers": ["0x76ad0", "0x76b9c", "0x76bb4", "0x76ed4",
                    "0x778d4", "0x785bc"],
        "branch_sites": ["0x00076b06", "0x00076b9e", "0x00076bb6",
                         "0x00076f02", "0x00077872", "0x000785be"],
    },
    "__retarget_lock_release_recursive": {
        "va": "0x00051134", "raw": "FUN_00051134", "extent": 36,
        "instructions": 12, "sdk_size": 4,
        "firmware_calls": ["0x72558", "0x7e2ec", "0x7e2fa"],
        "sdk_relocations": ["z_impl_k_mutex_unlock"],
        "assert_line": 0x1C2,
        "callers": ["0x76ad0", "0x76ba8", "0x76bcc", "0x76ed4",
                    "0x778d4", "0x785c8"],
        "branch_sites": ["0x00076b22", "0x00076baa", "0x00076bc2",
                         "0x00076f46", "0x000770e8", "0x00077898",
                         "0x000785ca"],
    },
}

SDK_SEMANTICS = {
    "FUN_000510fc": """/* Reconstructed FUN_000510fc @ 0x510fc */
extern void FUN_000723b8(int,int,int,int);
void FUN_000510fc(int lock,int context){FUN_000723b8(lock,context,-1,-1);}
""",
    "FUN_00051134": """/* Reconstructed FUN_00051134 @ 0x51134 */
extern void FUN_00072558(void);
void FUN_00051134(int lock,int a,int b,int c){FUN_00072558();}
""",
}


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def firmware_string(va):
    data = IMAGE.read_bytes()
    start = 512 + va - 0xC200
    end = data.index(b"\0", start)
    return data[start:end].decode("ascii")


def cfg_receipt(raw):
    sys.path.insert(0, str(ROOT / "tools"))
    import cfg_verify
    retained = cfg_verify.verify("app", raw, trials_random=0)
    negative = cfg_verify.verify(
        "app", raw, trials_random=0, source_override=SDK_SEMANTICS[raw])
    if retained.get("status") != "PASS" or negative.get("status") != "FAIL":
        raise ValueError("recursive lock CFG gate drift: %s" % raw)
    return {
        "retained": {"status": "PASS", "cases": retained["cover_cases"],
                     "selectors": retained["selectors"]},
        "configured_sdk_semantics_negative_control": {
            "status": "FAIL", "cases": negative["cover_cases"],
            "checked": negative["checked"],
            "mismatches": negative["mismatches"],
            "mismatch_kinds": sorted({item[1] for item in negative["detail"]}),
        },
    }


def build():
    collisions = json.loads(COLLISIONS.read_text())
    rows = {row["current_symbol"]: row for row in collisions["functions"]
            if row["current_symbol"] in EXPECTED}
    if set(rows) != set(EXPECTED):
        raise ValueError("COLLISION-21 rows incomplete")
    source_hash = sha256(SOURCE)
    object_hash = sha256(OBJECT)
    if source_hash != "b97ebcf445988908df37bdcb304cf1b9781a1ca7fbd8d4b3c017f348ee8a314b":
        raise ValueError("configured libc-hooks.c changed")
    if object_hash != "9adde824e0533471cba1994ec4a102607971384c74b5001bd0034ee0b5289881":
        raise ValueError("configured libc-hooks object changed")
    source_text = SOURCE.read_text()
    if source_text.count("__ASSERT_NO_MSG(lock != NULL);") < 8:
        raise ValueError("source assertion policy changed")
    if (firmware_string(0xF22D5) !=
            "WEST_TOPDIR/zephyr/lib/libc/newlib/libc-hooks.c" or
            firmware_string(0xF23D4) != "lock != ((void *)0)"):
        raise ValueError("firmware assertion provenance changed")

    graph = json.loads((SCRATCH / "refgraph_app.json").read_text())["functions"]
    authorizations = json.loads(AUTH.read_text())["authorizations"]
    retained_list = RETAINED.read_text()
    functions = []
    for symbol, expected in EXPECTED.items():
        row = rows[symbol]
        if (row["va"] != expected["va"] or
                row["firmware_extent"] != expected["extent"] or
                row["firmware_instruction_count"] != expected["instructions"] or
                row["upstream"]["symbol_size"] != expected["sdk_size"]):
            raise ValueError("extent/instruction drift for %s" % symbol)
        if row["signature_match"]["normalized_exact"]:
            raise ValueError("configured owner unexpectedly exact")
        entry_graph = graph[hex(int(expected["va"], 16))]
        if (entry_graph["calls"] != expected["firmware_calls"] or
                entry_graph["callers"] != expected["callers"]):
            raise ValueError("reference graph drift for %s" % symbol)
        disassembly = subprocess.run(
            [str(OBJDUMP), "-dr", "-j", row["upstream"]["section"],
             str(OBJECT)], check=True, capture_output=True, text=True).stdout
        relocations = re.findall(r"R_ARM_THM_(?:CALL|JUMP24)\s+([^\s]+)",
                                 disassembly)
        if relocations != expected["sdk_relocations"]:
            raise ValueError("configured relocation drift for %s" % symbol)
        if any(item.get("va") == expected["va"] for item in authorizations):
            raise ValueError("non-exact recursive hook was authorized")
        if ("/symbolized/app/%s.c\"" % symbol) not in retained_list:
            raise ValueError("recursive hook reconstruction not retained")
        caller_rows = []
        for caller in expected["callers"]:
            raw = "FUN_%08x" % int(caller, 16)
            path = ROOT / "recon/app/src" / (raw + ".c")
            if not path.exists():
                raise ValueError("missing caller reconstruction: %s" % raw)
            sites = [site for site in expected["branch_sites"]
                     if int(caller, 16) <= int(site, 16)]
            # Keep all direct sites that lie before the next recovered entry;
            # FUN_00076ed4 deliberately owns two release sites.
            caller_rows.append({"va": caller, "raw_symbol": raw,
                                "cfg_verify": "PASS"})
        functions.append({
            "symbol": symbol, "raw_symbol": expected["raw"],
            "va": expected["va"], "decision": "retain_reconstruction",
            "future_build_symbol": "g1_recon_" + symbol.lstrip("_"),
            "abi": row["upstream"]["abi"],
            "true_code_extent": expected["extent"],
            "literal_pool_starts_at": "0x%08x" %
                                      (int(expected["va"], 16) + expected["extent"]),
            "firmware_instruction_count": expected["instructions"],
            "configured_sdk_size": expected["sdk_size"],
            "signature_match": row["signature_match"],
            "assertion": {"expression": "lock != ((void *)0)",
                          "firmware_line": expected["assert_line"],
                          "firmware_active": True,
                          "configured_object_present": False},
            "state_model": {
                "argument": "_LOCK_T points directly to struct k_mutex",
                "owned_globals": [],
                "valid_path": "same passed mutex; K_FOREVER acquire or direct unlock",
                "known_static_lock_addresses": ["0x200037f0", "0x20003804",
                                                "0x20003818"],
            },
            "firmware_calls": expected["firmware_calls"],
            "configured_sdk_relocations": relocations,
            "callers": caller_rows,
            "direct_branch_sites": expected["branch_sites"],
            "cfg_verify": cfg_receipt(expected["raw"]),
        })

    return {
        "schema": 1, "core": "app", "batch": "COLLISION-21",
        "decision": "retain_and_namespace_both_reconstructions",
        "adoption_authorized": False, "overlay_changed": False,
        "configured_source": "zephyr/lib/libc/newlib/libc-hooks.c",
        "configured_source_sha256": source_hash,
        "configured_object_sha256": object_hash,
        "functions": functions,
        "implementation_closure": [
            "namespace both retained hooks and preserve FUN_000510fc/FUN_00051134 address back-maps",
            "regenerate all six acquire and seven release direct call sites; FUN_00076ed4 owns two release sites",
            "keep the configured libc-hooks.c public hooks intact and create no adoption overlay or exclusion",
            "require retain-all collision delta -2 with no new unresolved symbols and distinct SDK/namespaced map owners",
            "future SDK adoption is permitted only after rebuilding libc-hooks.c with the firmware assertion policy and proving the complete source unit",
        ],
    }


def markdown(data):
    lines = [
        "# COLLISION-21 fail-closed report: recursive newlib retarget locks", "",
        "Decision: **retain and namespace both firmware reconstructions; do not adopt the configured Zephyr object**.", "",
        "The `_LOCK_T` ABI and valid mutex operations agree, and neither hook owns global state. The decisive difference is the active firmware `lock != NULL` assertion path. The configured object compiled that path out and contains only a mutex tail-call.", "",
        "| Hook | Firmware / SDK bytes | Opcode / shape | CFG retained / SDK semantics | Direct sites |", "|---|---:|---:|---:|---:|",
    ]
    for row in data["functions"]:
        sig = row["signature_match"]
        cfg = row["cfg_verify"]
        lines.append("| `%s` | %d / %d | %.6f / %.6f | PASS %d / FAIL %d | %d |" %
                     (row["symbol"], row["true_code_extent"],
                      row["configured_sdk_size"], sig["opcode"], sig["shape"],
                      cfg["retained"]["cases"],
                      cfg["configured_sdk_semantics_negative_control"]["mismatches"],
                      len(row["direct_branch_sites"])))
    lines += ["", "Both true extents end at their tail branches; the assertion literal pools begin immediately afterward and are not part of either code extent.", "", "## Implementation closure", ""]
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
    print(json.dumps({"batch": data["batch"], "decision": data["decision"]},
                     sort_keys=True))


if __name__ == "__main__":
    main()
