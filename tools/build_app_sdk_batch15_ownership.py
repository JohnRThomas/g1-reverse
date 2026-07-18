#!/usr/bin/env python3
"""Build fail-closed ownership evidence for CPUAPP SDK residue batch 15."""
import argparse
import hashlib
import json
import os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RESIDUE = os.path.join(ROOT, "recon/analysis/app_link_residue.json")
JSON_OUT = os.path.join(ROOT, "recon/ownership/app_sdk_batch15_ownership.json")
MD_OUT = os.path.join(ROOT, "recon/ownership/app_sdk_batch15_ownership.md")

OWNERS = {
    "is_regular_addr_valid": ("0x000839dc", 34,
        "zephyr/drivers/flash/soc_flash_nrf.c:is_regular_addr_valid", 42, 2,
        "7c548598426d6174ea437fb936cd3102eac1273d63abec2ad1ca628d79f5301b"),
    "nvmc_word_write": ("0x00065f04", 18,
        "modules/hal/nordic/nrfx/drivers/src/nrfx_nvmc.c:nvmc_word_write", 1, 1,
        "2247b34b04b9fd4f15e729017166056606023b6df1c142566dea047bcf86be04"),
    "process_queue": ("0x00082114", 50,
        "zephyr/subsys/bluetooth/host/att.c:process_queue (CONFIG_BT_EATT=n)", 3, 3,
        "1eea63e21d3af1177d2a05c1aba9f2c84ce2716090f28b5084e97bfe804956dc"),
    "qspi_deactivate": ("0x00066478", 28,
        "modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c:qspi_deactivate", 40, 0,
        "e68a05e1f31ab33df380f05fa82ee87346e35c57cd498d7bbcf07f3fe17eacd0"),
    "remove_timeout": ("0x00074bbc", 50,
        "zephyr/kernel/timeout.c:remove_timeout", 2, 2,
        "652b27ffc8c42f143f6c4404d5bbf8aeb18adbc32a93f44e5c224f1404c0d3f8"),
    "sys_slist_find_and_remove": ("0x0008137e", 54,
        "zephyr/include/zephyr/sys/slist.h:sys_slist_find_and_remove", 5, 5,
        "d5587e689c9d16e89d80b4e2a845c6d47c288f5abdaafc71155f246c881f438a"),
    "sys_slist_find_and_remove_2": ("0x00081de2", 50,
        "zephyr/include/zephyr/sys/slist.h:sys_slist_find_and_remove (discarded result)", 5, 5,
        "677152b0a2f6352c141fe10f09ced933c57810c743a117c2f4720bd038567919"),
}

STRTOD_CORRECTION = {
    "symbol": "strtoll_internal",
    "va": "0x00077a10",
    "raw_target": "0x00013f58",
    "correct_owner": "newlib-nano _strtod_l",
    "source": "recon/app/src/FUN_00077a10.c",
    "verified_mirror": "recon/verified/src/FUN_00077a10.c",
    "sha256": "ba49b63a7672881bea73a00779d402c58ee7f7109f95bbef5cc553a23361c9a3",
    "firmware_target_prefix": "2de9f04f1f469db0",
    "lib_a_strtoll_prefix": "2de9f04f904685b0",
    "checked": 2,
    "cfg_cases": 2,
}


def digest(path):
    with open(path, "rb") as stream:
        return hashlib.sha256(stream.read()).hexdigest()


def build():
    with open(RESIDUE, encoding="utf-8") as stream:
        refs = {row["symbol"]: row for row in json.load(stream)["entries"]}
    rows = []
    for symbol, (va, size, owner, checked, cases, sha) in OWNERS.items():
        source = f"recon/app/src/{symbol}.c"
        mirror = f"recon/verified/src/{symbol}.c"
        actual = digest(os.path.join(ROOT, source))
        if actual != sha or digest(os.path.join(ROOT, mirror)) != actual:
            raise RuntimeError("source/mirror drift: " + symbol)
        residue = refs.get(symbol)
        if not residue or residue["reference_count"] != 1:
            raise RuntimeError("residue drift: " + symbol)
        rows.append({"symbol": symbol, "va": va, "size": size,
            "upstream_owner": owner, "checked": checked,
            "cfg_cases": cases, "sha256": sha, "source": source,
            "verified_mirror": mirror, "reference_count_before": 1,
            "reference_sites_before": residue["reference_sites"],
            "decision": "retain_cfg_verified_configured_reconstruction"})

    correction = dict(STRTOD_CORRECTION)
    residue = refs.get(correction["symbol"])
    if not residue or residue["reference_count"] != 1:
        raise RuntimeError("strtoll residue drift")
    actual = digest(os.path.join(ROOT, correction["source"]))
    if actual != correction["sha256"] or \
            digest(os.path.join(ROOT, correction["verified_mirror"])) != actual:
        raise RuntimeError("strtod wrapper/mirror drift")
    with open(os.path.join(ROOT, correction["source"]), encoding="utf-8") as stream:
        wrapper = stream.read()
    if "_strtod_l" not in wrapper or "strtoll_internal" in wrapper or \
            "/*=0x00013f58*/" not in wrapper:
        raise RuntimeError("false strtoll identity reintroduced")
    correction.update({"reference_count_before": 1,
        "reference_sites_before": residue["reference_sites"],
        "decision": "correct_false_residue_to_strtod_l",
        "rejection": "lib_a-strtoll.o has a different entry ABI/code prefix and integer grammar; do not synthesize a strtoll body"})
    rows.append(correction)

    with open(os.path.join(ROOT, "tools/cfg_verify.py"), encoding="utf-8") as stream:
        verifier = stream.read()
    required = (
        'REVIEWED_ORACLE_CASES[("app", 0x00065f04)]',
        'ABSOLUTE_READ_TRANSITION_CASES[("app", 0x00065f04)]',
        'REVIEWED_ORACLE_CASES[("app", 0x00082114)]',
        'for _slist_remove_va in (0x0008137e, 0x00081de2)',
        'REVIEWED_ORACLE_CASES[("app", 0x00074bbc)]',
    )
    if any(marker not in verifier for marker in required):
        raise RuntimeError("batch15 verifier contract drift")
    return {"schema": 1, "core": "app",
        "policy": {"fail_closed": True,
            "forbid": ["weak stub", "byte blob", "assembly wrapper",
                       "same-name alias guess", "fake strtoll_internal body"]},
        "summary": {"item_count": len(rows),
            "reconstructed_function_count": len(OWNERS),
            "corrected_identity_count": 1,
            "reference_count_before": sum(r["reference_count_before"] for r in rows),
            "cfg_verified": len(rows)},
        "identity_evidence": {"strtoll_rejected": True,
            "raw_target": correction["raw_target"],
            "correct_owner": correction["correct_owner"],
            "firmware_target_prefix": correction["firmware_target_prefix"],
            "lib_a_strtoll_prefix": correction["lib_a_strtoll_prefix"]},
        "functions": rows}


def markdown(data):
    out = ["# CPUAPP SDK residue batch 15 ownership", "",
        "Seven configured SDK helpers are retained as readable CFG-verified C;",
        "the eighth residue is corrected from the false `strtoll_internal`",
        "identity to the shipped newlib-nano `_strtod_l` call.", "",
        "| Residue | VA | Bytes | Pinned owner / decision | CFG |",
        "|---|---:|---:|---|---|"]
    for row in data["functions"]:
        size = row.get("size", "wrapper")
        owner = row.get("upstream_owner", row.get("correct_owner"))
        out.append(f"| `{row['symbol']}` | `{row['va']}` | {size} | `{owner}` | PASS ({row['checked']}) |")
    out += ["", "The raw target `0x00013f58` parses floating syntax and returns a double;",
        "its entry prefix differs from `lib_a-strtoll.o`. A synthetic strtoll body is forbidden.", "",
        f"Canonical result: **{data['summary']['item_count']} residues / {data['summary']['reference_count_before']} prior references**, digest-pinned and CFG-verified.", ""]
    return "\n".join(out)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build()
    json_text = json.dumps(data, indent=1) + "\n"
    markdown_text = markdown(data)
    if args.check:
        assert open(JSON_OUT, encoding="utf-8").read() == json_text
        assert open(MD_OUT, encoding="utf-8").read() == markdown_text
    else:
        open(JSON_OUT, "w", encoding="utf-8").write(json_text)
        open(MD_OUT, "w", encoding="utf-8").write(markdown_text)


if __name__ == "__main__":
    main()
