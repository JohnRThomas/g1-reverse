#!/usr/bin/env python3
"""Emit the shipped CPUAPP `.data` initial image for the recovered RAM arena.

WHY THIS EXISTS (P4 iteration 15)
---------------------------------
Every recovered CPUAPP global below 0x20003e29 lives in the ORIGINAL image's
`.data` section, i.e. it has a non-zero load image in flash.  Our build binds
those pins into `g1_ram_arena` (recon/application/app/src/g1_app_ram_relocs.c),
which is plain `.bss` — so every one of them starts at ZERO in our firmware
while the original starts at its shipped initialiser.

The `.data` load image base is proven three independent ways (all reproduced by
`--selftest`):
  * flash 0xf6d64 + 0x23cc = 0xf9130 is `g_st25dv_i2c_dev` = { bus=0x00087c68,
    addr=0x53 } and 0x00087c68 is the "i2c@9000" device (iteration 11);
  * flash 0xf6d64 + 0x2fe3 holds the ASCII product code "S100demoglasses" and
    +0x3003 the serial "S100demodevice";
  * flash 0xf6d64 + 0x34f7 holds 0x80 followed by 63 zero bytes — the canonical
    MD5 padding block `g_md5_padding`.
so `LMA(0x20000000 + x) = 0xf6d64 + x` for the whole `.data` section.

POLICY
------
The load image also contains ABSOLUTE ORIGINAL-IMAGE POINTERS (flash function/
rodata pointers and self-referential SRAM pointers).  Those addresses are
meaningless in our build, so restoring them verbatim would replace a loud NULL
with a wild pointer.  This generator therefore restores only bytes that are not
part of a pointer-looking 4-byte-aligned word, and — because a table that got
its selectors but not its function pointers is worse than an all-zero table —
it drops any *structured group* (non-zero bytes separated by < GROUP_GAP zero
bytes) that contains a pointer word at all, plus an explicit review exclusion
list.  Everything dropped keeps today's zero-initialised behaviour exactly.

Stages (kept so the bring-up bisect ledger can reproduce each measurement):
  --stage a1   only g_dashboard_display_level (arena +0x544, u32)
  --stage a2   the full reviewed non-pointer restore

Usage:
  PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_data_image.py \
      --stage a2 -o recon/application/app/src/g1_app_data_image.c
"""

import argparse
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REPO = os.path.dirname(REPO) if os.path.basename(REPO) == "recon" else REPO
sys.path.insert(0, os.path.join(REPO, "tools"))
import extract as E  # noqa: E402

DATA_LMA = 0xF6D64          # flash load address of VMA 0x20000000
DATA_VMA = 0x20000000
DATA_END = 0x20003E29       # first byte past the shipped .data section
ARENA_ORIGIN = 0x20002000   # g1_ram_arena base VMA in the original numbering

GROUP_GAP = 4               # zero bytes that still keep two runs in one group

# Pointer-looking word ranges (original image coordinates).
FLASH_LO, FLASH_HI = 0x0000C200, 0x00100000
SRAM_LO, SRAM_HI = 0x20000000, 0x20080000

# Reviewed exclusions, by arena offset range [lo, hi).  These groups contain no
# pointer word by the automatic test but are still unsafe or meaningless to
# restore; each entry names the reason.
EXCLUDE = [
    # g_st25dv_i2c_dev (0x200023cc) is emitted as its own object and bound out
    # of the arena (g1_app_ram_relocs.c); its arena slot is dead storage.
    (0x3CC, 0x3D4, "g_st25dv_i2c_dev is bound out of the arena"),
    # g_screen_render_table (0x20002430, 11 x 16 B) interleaves a u32 screen id
    # with two original-image Thumb function pointers.  Restoring the ids while
    # the handlers stay NULL turns "no entry matches" into "matched, call 0",
    # which is strictly worse than today's all-zero table.  The table needs the
    # emitted-object treatment (like g1_st25dv_ops_table.c), not a byte copy.
    (0x430, 0x4E0, "g_screen_render_table mixes ids with function pointers"),
    # Kernel objects whose wait_q dlist heads are self-referential SRAM
    # pointers: only a scalar field (k_mem_slab.num_blocks, k_mutex
    # owner_orig_prio) survives the pointer filter, and a half-initialised
    # kernel object is not an improvement over an all-zero one.  These need
    # arena-relative pointer relocation, which this generator does not do yet.
    (0x17B8, 0x1890, "k_mem_slab / k_mutex objects need pointer relocation"),
]

STAGE_A1 = [(0x544, 4, "g_dashboard_display_level")]


def pointerish(word):
    return (FLASH_LO <= word < FLASH_HI) or (SRAM_LO <= word < SRAM_HI)


def load_image():
    return E.read(DATA_LMA, DATA_END - DATA_VMA)


def arena_slice(img):
    return img[ARENA_ORIGIN - DATA_VMA:]


def pointer_word_mask(img):
    """True for every byte that belongs to a pointer-looking aligned word."""
    n = len(img)
    mask = bytearray(n)
    for w in range(0, n & ~3, 4):
        word = int.from_bytes(img[w:w + 4], "little")
        if pointerish(word):
            mask[w:w + 4] = b"\x01" * 4
    return mask


def pin_offsets():
    """Arena offsets of every recovered global pinned into the arena.

    These are the only STRUCTURAL object boundaries we know, so a restore unit
    never spans two of them: otherwise a pointer table (e.g.
    g_translate_lang_string_table) and the scalar that happens to follow it in
    RAM would share a unit and the scalar would be lost with the table.
    """
    import re
    offs = set()
    path = os.path.join(REPO, "recon/symbols/g1_app_globals.ld")
    for line in open(path):
        m = re.match(r"\s*PROVIDE\((\w+)\s*=\s*g1_ram_arena\s*\+\s*(0x[0-9a-fA-F]+)\)",
                     line)
        if m:
            offs.add(int(m.group(2), 16))
    return offs


def groups(blob, boundaries):
    """Restore units: maximal groups of non-zero bytes separated by
    >= GROUP_GAP zeros, additionally split at every pinned object boundary."""
    out = []
    start = None
    last = None
    for i, b in enumerate(blob):
        if not b:
            continue
        if start is None:
            start, last = i, i
            continue
        if i - last - 1 >= GROUP_GAP or any(
                b_ in boundaries for b_ in range(last + 1, i + 1)):
            out.append((start, last + 1))
            start = i
        last = i
    if start is not None:
        out.append((start, last + 1))
    return out


def excluded(lo, hi):
    for a, b, why in EXCLUDE:
        if lo < b and a < hi:
            return why
    return None


def runs_for_stage(stage, verbose=False):
    img = load_image()
    blob = arena_slice(img)
    if stage == "a1":
        return [(off, bytes(blob[off:off + n])) for off, n, _ in STAGE_A1], blob
    mask = pointer_word_mask(blob)
    keep = []
    for lo, hi in groups(blob, pin_offsets()):
        # widen to the aligned word grid so a group never splits a word
        wlo, whi = lo & ~3, (hi + 3) & ~3
        if any(mask[wlo:whi]):
            if verbose:
                print("  drop  +0x%04x..0x%04x  (pointer word in group)" % (lo, hi))
            continue
        why = excluded(lo, hi)
        if why:
            if verbose:
                print("  drop  +0x%04x..0x%04x  (%s)" % (lo, hi, why))
            continue
        keep.append((lo, bytes(blob[lo:hi])))
        if verbose:
            print("  keep  +0x%04x..0x%04x  (%d B)" % (lo, hi, hi - lo))
    return keep, blob


def emit(runs, stage, path):
    total = sum(len(b) for _, b in runs)
    lines = []
    lines.append("/* GENERATED by recon/application/gen_app_data_image.py"
                 " --stage %s -- DO NOT EDIT.\n" % stage)
    lines.append(" *\n")
    lines.append(" * The shipped CPUAPP `.data` initial image for the recovered RAM arena.\n")
    lines.append(" * Bytes come verbatim from app_update.bin (load image base flash 0xf6d64\n")
    lines.append(" * for VMA 0x20000000); see the generator header for the three independent\n")
    lines.append(" * proofs of that base and for the pointer-word policy.\n")
    lines.append(" *\n")
    lines.append(" * stage=%s  runs=%d  bytes=%d\n" % (stage, len(runs), total))
    lines.append(" */\n")
    lines.append("#include <zephyr/init.h>\n")
    lines.append("#include <zephyr/kernel.h>\n")
    lines.append("#include <string.h>\n\n")
    lines.append("extern unsigned char g1_ram_arena[];\n\n")
    lines.append("struct g1_arena_data_run {\n\tunsigned int off;\n"
                 "\tunsigned int len;\n\tunsigned int src;\n};\n\n")
    lines.append("static const unsigned char g1_arena_data_bytes[%d] = {\n" % max(total, 1))
    blob = b"".join(b for _, b in runs)
    if not blob:
        blob = b"\x00"
    for i in range(0, len(blob), 16):
        lines.append("\t" + " ".join("0x%02x," % c for c in blob[i:i + 16]) + "\n")
    lines.append("};\n\n")
    lines.append("static const struct g1_arena_data_run g1_arena_data_runs[%d] = {\n"
                 % max(len(runs), 1))
    src = 0
    for off, b in runs:
        lines.append("\t{ 0x%05x, %5d, %6d },\t/* original 0x%08x */\n"
                     % (off, len(b), src, ARENA_ORIGIN + off))
        src += len(b)
    if not runs:
        lines.append("\t{ 0, 0, 0 },\n")
    lines.append("};\n\n")
    lines.append(
        "/* PRE_KERNEL_1 priority 0: after z_bss_zero/z_data_copy and before any\n"
        " * recovered device or application initialiser can observe the arena. */\n"
        "static int g1_arena_data_init(void)\n{\n"
        "\tfor (unsigned int i = 0; i < ARRAY_SIZE(g1_arena_data_runs); i++) {\n"
        "\t\tconst struct g1_arena_data_run *r = &g1_arena_data_runs[i];\n\n"
        "\t\tif (r->len == 0U) {\n\t\t\tcontinue;\n\t\t}\n"
        "\t\tmemcpy(&g1_ram_arena[r->off], &g1_arena_data_bytes[r->src], r->len);\n"
        "\t}\n\treturn 0;\n}\n\n"
        "SYS_INIT(g1_arena_data_init, PRE_KERNEL_1, 0);\n")
    with open(path, "w") as fh:
        fh.write("".join(lines))
    return len(runs), total


def selftest():
    img = load_image()
    ok = True

    def chk(name, got, want):
        nonlocal ok
        good = got == want
        ok = ok and good
        print("  %-28s %-22s %s" % (name, got, "OK" if good else "MISMATCH want %s" % (want,)))

    o = 0x23CC
    chk("g_st25dv_i2c_dev", img[o:o + 8].hex(), "687c080053000000")
    o = 0x2FE3
    chk("g_product_code_buf", img[o:o + 15].decode(), "S100demoglasses")
    o = 0x3003
    chk("g_device_serial_buf", img[o:o + 14].decode(), "S100demodevice")
    o = 0x34F7
    chk("g_md5_padding", img[o:o + 8].hex(), "8000000000000000")
    o = 0x2544
    chk("g_dashboard_display_level", int.from_bytes(img[o:o + 4], "little"), 0x42)
    return 0 if ok else 1


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--stage", default="a2", choices=("a1", "a2"))
    ap.add_argument("-o", "--out",
                    default=os.path.join(REPO, "recon/application/app/src/g1_app_data_image.c"))
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("-v", "--verbose", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()
    if args.selftest:
        return selftest()
    runs, _ = runs_for_stage(args.stage, args.verbose)
    if args.dry_run:
        print("stage=%s runs=%d bytes=%d" % (args.stage, len(runs),
                                             sum(len(b) for _, b in runs)))
        return 0
    n, total = emit(runs, args.stage, args.out)
    print("wrote %s: stage=%s runs=%d bytes=%d" % (args.out, args.stage, n, total))
    return 0


if __name__ == "__main__":
    sys.exit(main())
