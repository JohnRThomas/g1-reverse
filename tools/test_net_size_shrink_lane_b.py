#!/usr/bin/env python3
"""Regression gate for the proved CPUNET lane-B size reductions."""

from pathlib import Path

import cfg_verify
from parity.recon import compile_func


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "recon/net/src"
EXPECTED_SIZES = {
    "FUN_0103689c": (0x0103689C, 192),
    "FUN_01035fa0": (0x01035FA0, 120),
    "FUN_01033b18": (0x01033B18, 212),
    "FUN_01036128": (0x01036128, 32),
}

MUTATIONS = {
    "FUN_0103689c": lambda text: text.replace(
        "if (FUN_0103610c(kernel_lock) == 0) {", "if (0) {"),
    "FUN_01035fa0": lambda text: text.replace(
        "FUN_01035edc(object, arg2, arg3, arg4, arg5, arg6, arg7, arg8,\n"
        "                  arg9, exception);", "(void)exception;"),
    "FUN_01033b18": lambda text: text.replace(
        "*(volatile unsigned int *)(iVar3 + 0x118) = 0;",
        "*(volatile unsigned int *)(iVar3 + 0x118) = 1;"),
    "FUN_01036128": lambda text: text.replace(
        "unsigned int expected = state->owner | state->nested;",
        "state->owner = 0;\n  unsigned int expected = state->owner | state->nested;"),
}


def main():
    for name, (address, expected_size) in EXPECTED_SIZES.items():
        text = (SOURCE / f"{name}.c").read_text()
        compiled, error = compile_func(text, name, address)
        assert error is None, (name, error)
        assert compiled[2] == expected_size, (name, compiled[2], expected_size)

        verdict = cfg_verify.verify("net", name, trials_random=20)
        assert verdict["status"] == "PASS", (name, verdict)

        mutant = MUTATIONS[name](text)
        assert mutant != text, name
        rejected = cfg_verify.verify("net", name, trials_random=20,
                                     source_override=mutant)
        assert rejected["status"] == "FAIL", (name, rejected)

    print("net size-shrink lane B: PASS")


if __name__ == "__main__":
    main()
