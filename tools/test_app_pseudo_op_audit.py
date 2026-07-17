#!/usr/bin/env python3
"""Regression checks for the exact CPUAPP pseudo-op lowerings."""

import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))

import extract
import recon_kit


def test_default_arm_extent_and_literal_boundary():
    entry = 0x00056A68
    assert recon_kit.TRUE_SIZE_OVERRIDES[entry] == 0x68
    owned = extract.read(entry, 0x68)
    # Default: mvn.w r0,#127; b.n shared epilogue at 0x56a94.
    assert owned[-6:] == bytes.fromhex("6ff07f00e1e7")
    assert entry + len(owned) == 0x00056AD0
    # First literal is the logging module string pointer 0x000f3a5d.
    assert extract.read_u32(0x00056AD0) == 0x000F3A5D


if __name__ == "__main__":
    test_default_arm_extent_and_literal_boundary()
    print("PASS app pseudo-op audit regression")
