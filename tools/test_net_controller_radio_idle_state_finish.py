#!/usr/bin/env python3
"""Regression for the catalog-missing CPUNET idle-state finisher."""

import json
import sys

sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")

import cfg_verify
import net_extract
import net_recon_kit


VA = 0x0100B594
SIZE = 0x60
SOURCE = (
    "/Users/freedomcoder/Projects/G1disasm2/recon/net/src/FUN_0100b594.c"
)
OVERRIDES = (
    "/Users/freedomcoder/Projects/G1disasm2/recon/catalogs/"
    "function_name_overrides.json"
)


def main():
    assert net_recon_kit.TRUE_SIZE_OVERRIDES[VA] == SIZE
    assert cfg_verify.TRUE_SIZE_OVERRIDES[("net", VA)] == SIZE
    assert net_extract.read_u32(VA + SIZE) == 0x21000C48

    overrides = json.load(open(OVERRIDES))
    record = overrides["net"]["0x0100b594"]
    assert record["name"] == "controller_radio_idle_state_finish"

    source = open(SOURCE).read()
    assert "Raw backmap: FUN_0100b594@0x0100b594" in source
    assert "void controller_radio_idle_state_finish(" in source

    verdict = cfg_verify.verify(
        "net", "controller_radio_idle_state_finish", trials_random=0,
        source_override=source)
    assert verdict["status"] == "PASS", verdict
    assert verdict["cover_cases"] == verdict["checked"] == 7, verdict

    # Both the invalid-state assertion and pending-channel tail fixtures must
    # be live, rather than merely present in the reviewed case registry.
    bad_assert = source.replace("0x224u", "0x225u", 1)
    verdict = cfg_verify.verify(
        "net", "controller_radio_idle_state_finish", trials_random=0,
        source_override=bad_assert)
    assert verdict["status"] == "FAIL", verdict

    bad_tail = source.replace("context[0x7au]", "context[0x79u]", 1)
    verdict = cfg_verify.verify(
        "net", "controller_radio_idle_state_finish", trials_random=0,
        source_override=bad_tail)
    assert verdict["status"] == "FAIL", verdict

    print("controller_radio_idle_state_finish regression: PASS")


if __name__ == "__main__":
    main()
