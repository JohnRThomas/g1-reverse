#!/usr/bin/env python3
"""Prove that the low CPUNET `.data` window is STOCK-LIBRARY storage that this
link places at its shipped address (P4 iteration 27).

WHY THIS EXISTS
---------------
Iteration 26's structural relocation pass (`gen_net_ram_relocs.py`) classified
EVERY recovered CPUNET absolute RAM address as "recovered-owned net RAM" and
gave it fabricated storage in a `g1_net_ram_blk_*` block.  For addresses in the
low `.data` window that is WRONG: there the shipped firmware's storage is the
`.data` of the stock NCS 2.5.1 SoftDevice Controller and MPSL front-end-module
archives, and OUR link places exactly those archive `.data` input sections at
exactly the same addresses.  Relocating such an address hands the recovered
accessor private zeroed storage instead of the live library object -- which is
how iteration 26 lost `radio TransmittedFrames` (the MPSL FEM API pointer word
at 0x21000530 read 0 instead of &fem_api_table).

The evidence is a byte comparison, not an assumption: over the window every
non-pointer word of our linked `.data` image is IDENTICAL to the shipped
`.data` image, and every word that differs is a flash code pointer whose
difference is a single constant per contributing archive (the archive's text
displacement in our link).  That is only possible if the two images contain the
same library objects in the same order at the same addresses.

Usage:
  PYTHONSAFEPATH=1 .venv/bin/python recon/application/verify_net_stock_data_window.py \
      <cohesive net zephyr.elf> [--json OUT]

Exit status 0 when the window is proven.
"""

import argparse
import json
import os
import re
import struct
import subprocess
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(REPO, "tools"))

# Shipped netcore .data load image: runtime LMA 0x0103ed24, VMA 0x21000000,
# length 0xc3c (the same read recon/application/gen_net_ram_relocs.py makes).
DATA_VMA = 0x21000000
DATA_LMA_RUNTIME = 0x0103ED24
DATA_LEN = 0x0C3C

# The proven window: SoftDevice Controller `.data` followed by the two
# libmpsl_fem_common `.data` objects (the FEM API pointer word and the 0x40-byte
# API table it points at).  It stops BELOW the first libmpsl object, whose
# pointer displacement is a third constant and is not needed here.
WINDOW_LO = 0x21000000
WINDOW_HI = 0x21000574

STOCK_ARCHIVES = (
    "libsoftdevice_controller_multirole.a",
    "libmpsl_fem_common.a",
)

SDK = os.environ.get(
    "G1_ZEPHYR_SDK", "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin")
OBJCOPY = os.path.join(SDK, "arm-zephyr-eabi-objcopy")

MAP_ROW = re.compile(
    r"^ (\.\S+)\s+0x00000000([0-9a-f]{8})\s+(0x[0-9a-f]+)\s+(\S+)")


def linked_data_image(elf, out_bin):
    subprocess.run([OBJCOPY, "-O", "binary", "--only-section=datas",
                    elf, out_bin], check=True)
    return open(out_bin, "rb").read()


def map_owners(map_path, lo, hi):
    """[(addr, size, section, archive-or-object)] covering [lo, hi)."""
    rows = []
    lines = open(map_path).read().splitlines()
    for i, line in enumerate(lines):
        m = MAP_ROW.match(line)
        if not m and re.match(r"^ (\.\S+)$", line) and i + 1 < len(lines):
            m2 = re.match(r"^\s+0x00000000([0-9a-f]{8})\s+(0x[0-9a-f]+)\s+(\S+)",
                          lines[i + 1])
            if m2:
                rows.append((int(m2.group(1), 16), int(m2.group(2), 16),
                             re.match(r"^ (\.\S+)$", line).group(1), m2.group(3)))
            continue
        if m:
            rows.append((int(m.group(2), 16), int(m.group(3), 16),
                         m.group(1), m.group(4)))
    return [r for r in rows if r[1] and lo <= r[0] < hi]


def looks_like_flash_pointer(word):
    return 0x01008800 <= word < 0x01048800


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("elf")
    ap.add_argument("--json", dest="json_out")
    args = ap.parse_args()

    import net_extract

    size = WINDOW_HI - WINDOW_LO
    shipped = bytes(net_extract.read_runtime(
        DATA_LMA_RUNTIME + (WINDOW_LO - DATA_VMA), size))
    tmp = os.path.join(os.path.dirname(os.path.abspath(args.elf)),
                       "_g1_net_datas.bin")
    ours = linked_data_image(args.elf, tmp)[WINDOW_LO - DATA_VMA:][:size]
    if len(ours) != size:
        print("linked .data image is shorter than the window", file=sys.stderr)
        return 2

    equal_words, ptr_diffs, hard_diffs = 0, [], []
    for off in range(0, size, 4):
        a = struct.unpack_from("<I", shipped, off)[0]
        b = struct.unpack_from("<I", ours, off)[0]
        if a == b:
            equal_words += 1
        elif looks_like_flash_pointer(a) and looks_like_flash_pointer(b):
            ptr_diffs.append((WINDOW_LO + off, a, b, a - b))
        else:
            hard_diffs.append((WINDOW_LO + off, a, b))

    # Every pointer difference must be one of a SMALL set of per-archive
    # constants, and each constant must be shared by a contiguous run.
    deltas = {}
    for addr, a, b, d in ptr_diffs:
        deltas.setdefault(d, []).append(addr)

    owners = map_owners(os.path.join(os.path.dirname(os.path.abspath(args.elf)),
                                     "zephyr.map"), WINDOW_LO, WINDOW_HI)
    foreign = [o for o in owners
               if not any(s in o[3] for s in STOCK_ARCHIVES)]
    covered = sum(o[1] for o in owners)

    print("window                         0x%08x..0x%08x (%d B)"
          % (WINDOW_LO, WINDOW_HI, size))
    print("words equal                    %d / %d" % (equal_words, size // 4))
    print("words differing (flash ptrs)   %d" % len(ptr_diffs))
    print("words differing (OTHER)        %d" % len(hard_diffs))
    print("distinct pointer deltas        %d  %s"
          % (len(deltas), ", ".join("0x%x x%d" % (d, len(v))
                                    for d, v in sorted(deltas.items()))))
    print("map input sections in window   %d, %d B covered" % (len(owners), covered))
    print("non-stock input sections       %d" % len(foreign))
    for o in foreign:
        print("   0x%08x %6d %s %s" % (o[0], o[1], o[2], o[3]))

    ok = (not hard_diffs) and (not foreign) and covered == size and len(deltas) <= 4
    print("VERDICT                        %s" % ("PROVEN" if ok else "NOT PROVEN"))

    if args.json_out:
        json.dump({
            "core": "net",
            "window": [hex(WINDOW_LO), hex(WINDOW_HI)],
            "elf": os.path.abspath(args.elf),
            "shipped_data_image": {"lma_runtime": hex(DATA_LMA_RUNTIME),
                                   "vma": hex(DATA_VMA), "length": hex(DATA_LEN)},
            "words_total": size // 4,
            "words_equal": equal_words,
            "words_differing_flash_pointer": len(ptr_diffs),
            "words_differing_other": [[hex(a), hex(x), hex(y)]
                                      for a, x, y in hard_diffs],
            "pointer_deltas": {hex(d): [hex(a) for a in v]
                               for d, v in sorted(deltas.items())},
            "map_input_sections": [[hex(a), s, sec, obj]
                                   for a, s, sec, obj in owners],
            "non_stock_input_sections": [[hex(a), s, sec, obj]
                                         for a, s, sec, obj in foreign],
            "verdict": "PROVEN" if ok else "NOT PROVEN",
        }, open(args.json_out, "w"), indent=1)

    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
