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

RELOCATION-AWARE POINTERS (P4 iteration 16)
-------------------------------------------
Dropping every group that contains a pointer left 106 pinned globals at zero,
and at least one of them is fatal: `g_cjson_hooks` (0x20002bac) is cJSON's
`internal_hooks = { malloc, free, realloc }`, so with it zeroed
`alloc_zeroed_node` executed `blx r3` with r3 = 0 and took a USAGE FAULT
("Illegal use of the EPSR", INVSTATE) that reset the SoC.

Stage a3 therefore restores such a group *relocation-aware*: the group's bytes
are copied verbatim and then every pointer word is OVERWRITTEN with the address
the symbol actually has in OUR link.  A group is only accepted when EVERY
pointer word in it resolves, so the iteration-15 rule ("a half-initialised
table is worse than an all-zero one") still holds.  Two resolution classes are
allowed, both of which are exact:

  * FLASH pointer -> the catalogued function name for `word & ~1`, referenced
    through an `__asm__`-alias extern so the LINKER supplies the relocated
    address (never a raw absolute).  Emitted with the Thumb bit re-set.
  * SRAM pointer that points INSIDE THE GROUP'S OWN BYTES -> `g1_ram_arena +
    (word - 0x20002000)`.  These are the self-referential `sys_dlist_t` heads of
    the shipped kernel objects (k_mutex wait_q, k_mem_slab, work queues).
    Restricting to self-references is what makes this safe: a pointer to some
    *other* RAM address could name an object that is bound OUT of the arena
    (like g_st25dv_i2c_dev), whose arena slot is dead storage.

Anything else still stays zero, exactly as before.

DEVICE POINTERS AND ARCHIVE-DEFINED TARGETS (P4 iteration 17)
-------------------------------------------------------------
Stage a3 as first written could not restore the ops table at arena +0x408 (the
one `pt_nfc_eeprom_link_init`, 0x30b3c, requires to be all-non-zero, and whose
absence reset the SoC at t ~ 0.104 s), because none of its five pointers
resolved.  Two further exact classes close that gap:

  * `struct device` pointer -> `DEVICE_DT_GET(DT_NODELABEL(<node>))`.  Only
    devices whose SHIPPED `struct device` was read out of app_update.bin and
    whose `name` string and `config->base` identify the node beyond doubt are
    listed in DEVICE_POINTERS below; anything else stays unresolvable.  This is
    the same treatment `g1_st25dv_i2c_dev` already gets in g1_app_ram_relocs.c.
  * A flash function pointer whose target is compiled by our build but was
    GARBAGE-COLLECTED from the previous link, because the zeroed `.data` word
    was its only referrer.  `our_symbols` therefore reads the build's static
    archives as well as the ELF: the question the gate must answer is "can this
    link define the symbol", and emitting the address-taken reference here is
    itself what roots it.  The 0-undefined `nm -u` link gate still re-checks it.

Stages (kept so the bring-up bisect ledger can reproduce each measurement):
  --stage a1   only g_dashboard_display_level (arena +0x544, u32)
  --stage a2   the full reviewed non-pointer restore
  --stage a3   a2 + the relocation-aware pointer groups described above

Usage:
  PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_data_image.py \
      --stage a3 -o recon/application/app/src/g1_app_data_image.c
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

# Reviewed exclusions, by arena offset range [lo, hi, atomic, why).  Stage a2
# never restores these.  `atomic` says whether stage a3 may restore the region
# as ONE unit once every pointer word in it resolves (iteration 17): that is the
# only way a structured object gets its ids and its handlers together, and it is
# what stops a3 from producing the half-initialised table this list exists to
# prevent.  An `atomic = False` region stays dropped in every stage.
EXCLUDE = [
    # g_st25dv_i2c_dev (0x200023cc) is emitted as its own object and bound out
    # of the arena (g1_app_ram_relocs.c); its arena slot is dead storage, so
    # there is nothing to gain from restoring it and it is never atomic.
    (0x3CC, 0x3D4, False, "g_st25dv_i2c_dev is bound out of the arena"),
    # g_screen_render_table (0x20002430, 11 x 16 B) interleaves a u32 screen id
    # with two original-image Thumb function pointers.  Restoring the ids while
    # the handlers stay NULL turns "no entry matches" into "matched, call 0",
    # which is strictly worse than today's all-zero table.  Iteration 17 makes
    # it atomic: all eleven handlers are now catalogued (the eight `movs r0,#0 /
    # bx lr` leaves Ghidra folded into neighbouring symbols were reconstructed
    # byte-exactly), so the whole table -- ids AND handlers -- is restored
    # together or not at all.
    (0x430, 0x4E0, True, "g_screen_render_table mixes ids with function pointers"),
    # Kernel objects whose wait_q dlist heads are self-referential SRAM
    # pointers: only a scalar field (k_mem_slab.num_blocks, k_mutex
    # owner_orig_prio) survives the pointer filter, and a half-initialised
    # kernel object is not an improvement over an all-zero one.  Atomic since
    # iteration 17: stage a3's self-reference class resolves the dlist heads
    # (an empty sys_dlist_t is exactly head == tail == &head), so the object is
    # restored whole.
    (0x17B8, 0x1890, True, "k_mem_slab / k_mutex objects need pointer relocation"),
]

STAGE_A1 = [(0x544, 4, "g_dashboard_display_level")]

# Reviewed literal runs that are always restored, whatever the group/pointer
# policy decides.  (P4 iteration 33: recorded explicitly so regenerating the
# image is reproducible.  The committed iteration-17 image contains this run;
# the group machinery drops it because the 4-byte word grid around it pulls in
# the neighbouring pointer word 0x20002d24, which is not a self-reference.)
#
#   0x20002d1c holds the float 0x7fc00000 = NaN -- the two non-zero high bytes
#   are at +0x1e/+0x1f.  They carry no pointer and restoring them alone
#   reproduces the shipped word exactly, because the low half is zero.
KEEP_ALWAYS = [
    (0xD1E, 2, "high half of the shipped NaN float at 0x20002d1c"),
]

ARENA_LIMIT = 0x20029000    # g1_ram_arena end (g1_app_ram_relocs.c)

# Uncatalogued flash leaves that a shipped .data pointer names.  Each entry is
# justified from raw disassembly of app_update.bin.
UNCATALOGUED = {
    # 0x778e4: `ldr r3,[pc,#8] (=0x20002d20, _impure_ptr) ; mov r2,r1 ;
    #           mov r1,r0 ; ldr r0,[r3] ; b.w 0x876ec` -- the newlib
    # `realloc(p,n) -> _realloc_r(_impure_ptr, p, n)` thunk.  It is the third
    # member of cJSON's internal_hooks at 0x20002bb4.
    0x778E4: "realloc",
}

# Shipped `struct device` objects a `.data` pointer names.  Each entry was read
# out of app_update.bin through tools/extract.py: word 0 is the `name` string
# and word 1 the driver config whose first word is the peripheral base, so the
# devicetree node is identified, not guessed.
#
#   0x00087c50: name "i2c@b000", config->base 0x5000b000  -> i2c2 (TWIM2)
#   0x00087c68: name "i2c@9000", config->base 0x50009000  -> i2c1 (TWIM1)
#
# 0x87c68 is the same device g1_st25dv_i2c_dev is already bound to in
# recon/application/app/src/g1_app_ram_relocs.c.
DEVICE_POINTERS = {
    0x00087C50: "i2c2",
    0x00087C68: "i2c1",
}

# ---------------------------------------------------------------------------
# STATIC `K_MSGQ_DEFINE` OBJECTS  (P4 iteration 33)
# ---------------------------------------------------------------------------
# The shipped CPUAPP has six `K_MSGQ_DEFINE` message queues.  A K_MSGQ_DEFINE
# is a *fully* static object: the struct lives in `.data` with its ring buffer
# pointers already pointing at a `.noinit`/`.bss` array, and NOTHING at runtime
# ever initialises it again.  The shipped struct (sizeof = 0x34, proven by the
# 0x34 stride between the six objects) is
#
#   +0x00 _wait_q_t   wait_q          (self-referential sys_dlist_t)
#   +0x08 k_spinlock  lock            (CONFIG_SPIN_VALIDATE -> 4 B, zero)
#   +0x0c size_t      msg_size
#   +0x10 uint32_t    max_msgs
#   +0x14 char       *buffer_start
#   +0x18 char       *buffer_end      ( == buffer_start + msg_size*max_msgs )
#   +0x1c char       *read_ptr        ( == buffer_start )
#   +0x20 char       *write_ptr       ( == buffer_start )
#   +0x24 uint32_t    used_msgs       (zero)
#   +0x28 sys_dlist_t poll_events     (CONFIG_POLL, self-referential)
#   +0x30 uint8_t     flags + pad     (zero)
#
# Stage a3 as written through iteration 32 restored ONLY the two self-
# referential dlist heads (+0x00 and +0x28), because the four ring-buffer
# pointers name SRAM addresses OUTSIDE the group (and outside the arena
# entirely: 0x2004ca90, 0x200422f0, ... are all above ARENA_LIMIT).  The
# consequence is measured, not theorised: `g_display_msgq` came up with
# msg_size = 0, max_msgs = 0 and buffer_start = NULL, so every
# `k_msgq_put(g_display_msgq, ...)` returned -ENOMSG ("queue full", used_msgs
# == max_msgs == 0).  In the 20 s iteration-32 capture `display_reflash`
# ran 226 times and `submit_display_reflash_work` ran ZERO times: the display
# thread never received a single START message, so `ui_refalsh_warp` and the
# whole raster path below it never executed and no pixel was ever painted.
#
# The ring buffer's ADDRESS carries no semantics -- only its size does -- so
# the exact restore is: give each queue a dedicated buffer of the shipped size
# in our own image and relocate the four pointer words onto it.  The resulting
# object is bit-for-bit what `k_msgq_init(q, buf, msg_size, max_msgs)` builds.
#
# Each row is (shipped object VMA, C identifier, pin name).  msg_size,
# max_msgs and the buffer extent are READ OUT of app_update.bin below and
# cross-checked (buffer_end - buffer_start == msg_size * max_msgs,
# read_ptr == write_ptr == buffer_start, used_msgs == 0); nothing is guessed.
STATIC_MSGQS = [
    (0x20003890, "g1_msgq_ring_audio",              "g_audio_msgq"),
    (0x200038C4, "g1_msgq_ring_display",            "g_display_msgq"),
    (0x200038F8, "g1_msgq_ring_bt_data_pipe",       "g_bt_data_pipe"),
    (0x2000392C, "g1_msgq_ring_dashboard_response", "g_dashboard_response_msgq"),
    (0x20003960, "g1_msgq_ring_quicknote_flash",    "g_quicknote_flash_msgq"),
    (0x20003994, "g1_msgq_ring_flash_store_cmd",    "g_flash_store_cmd_msgq"),
]

# Which of the six the generated image restores.  `display` is the isolating
# build used to attribute the raster result to exactly one object.
MSGQ_SETS = {
    "none": set(),
    "display": {0x200038C4},
    "all": {va for va, _, _ in STATIC_MSGQS},
}

K_MSGQ_MSG_SIZE = 0x0C
K_MSGQ_USED_MSGS = 0x24


def static_msgq_units(blob, selected):
    """Restore units + relocations for the shipped static K_MSGQ_DEFINEs.

    Returns (runs, ptrs, buffers) where `buffers` is a list of
    (identifier, size, comment) the emitter must define.
    """
    runs, ptrs, buffers = [], [], []
    for va, ident, pin in STATIC_MSGQS:
        if va not in selected:
            continue
        off = va - ARENA_ORIGIN
        w = [int.from_bytes(blob[off + 4 * i:off + 4 * i + 4], "little")
             for i in range(13)]
        lock, msg_size, max_msgs = w[2], w[3], w[4]
        buf_start, buf_end, read_ptr, write_ptr, used = w[5], w[6], w[7], w[8], w[9]
        size = msg_size * max_msgs
        # self-verifying: refuse anything that is not the canonical shape
        assert lock == 0 and used == 0, (pin, hex(lock), hex(used))
        assert msg_size and max_msgs, (pin, msg_size, max_msgs)
        assert buf_end - buf_start == size, (pin, hex(buf_start), hex(buf_end))
        assert read_ptr == buf_start and write_ptr == buf_start, pin
        assert not (SRAM_LO <= buf_start < ARENA_LIMIT), (pin, hex(buf_start))
        lo = off + K_MSGQ_MSG_SIZE
        hi = off + K_MSGQ_USED_MSGS
        runs.append((lo, bytes(blob[lo:hi])))
        for i, delta in ((5, 0), (6, size), (7, 0), (8, 0)):
            ptrs.append((off + 4 * i, "extbuf", (ident, delta), w[i]))
        buffers.append((ident, size, "%s: %d x %d, shipped ring [0x%08x,0x%08x)"
                        % (pin, msg_size, max_msgs, buf_start, buf_end)))
    return runs, ptrs, buffers


def our_symbols(elf):
    """Symbol names OUR build can define, so stage a3 never emits a reference
    that would turn into an undefined symbol at link time.

    Both the linked ELF and the build's static archives are read.  An archive
    member that the previous link garbage-collected (because the zeroed `.data`
    word we are about to restore was the symbol's only referrer) is still a
    definition this link can supply -- and the address-taken reference emitted
    here is exactly what roots it.  The `nm -u` 0-undefined gate re-checks the
    result on the next build.
    """
    import glob
    import subprocess
    nm = os.environ.get(
        "G1_NM",
        "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-nm")
    inputs = [elf]
    build = os.path.dirname(os.path.dirname(os.path.abspath(elf)))
    inputs += sorted(glob.glob(os.path.join(build, "app", "*.a")))
    names = set()
    for path in inputs:
        out = subprocess.run([nm, "--defined-only", path],
                             capture_output=True, text=True)
        if out.returncode != 0:
            raise SystemExit("nm failed on %s: %s" % (path, out.stderr.strip()))
        for line in out.stdout.splitlines():
            parts = line.split()
            if len(parts) == 3 and parts[1] not in "uU":
                names.add(parts[2])
    return names


def catalog_names():
    import json
    path = os.path.join(REPO, "recon/catalogs/function_names_app.json")
    d = json.load(open(path))
    return {int(v["address"], 16): v["name"] for v in d["by_address"].values()}


def resolve_pointer(word, glo, ghi, byaddr, syms):
    """Resolve a shipped .data pointer word to OUR build.

    Returns ("flash", name) | ("arena", arena_offset) | ("device", node)
    | None (unresolvable).
    """
    if word in DEVICE_POINTERS:
        return ("device", DEVICE_POINTERS[word])
    if word < SRAM_LO:
        target = word & ~1
        name = byaddr.get(target) or UNCATALOGUED.get(target)
        if name and (name in syms or target in UNCATALOGUED):
            return ("flash", name)
        return None
    if SRAM_LO <= word < ARENA_LIMIT:
        off = word - ARENA_ORIGIN
        # only self-references INSIDE this group are safe (see module header)
        if glo <= off < ghi:
            return ("arena", off)
    return None


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
    for a, b, _atomic, why in EXCLUDE:
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
    for off, n, why in KEEP_ALWAYS:
        if not any(off < k + len(b) and k < off + n for k, b in keep):
            keep.append((off, bytes(blob[off:off + n])))
            if verbose:
                print("  KEEP  +0x%04x..0x%04x  (%s)" % (off, off + n, why))
    keep.sort()
    return keep, blob


def runs_for_stage_a3(elf, verbose=False, msgq_set="all"):
    """Stage a2 plus every dropped group whose pointer words ALL resolve.

    Returns (runs, ptrs) where ptrs is a list of
    (arena_offset, "flash", symbol_name) | (arena_offset, "arena", target_off).
    """
    keep, blob = runs_for_stage("a2")
    mask = pointer_word_mask(blob)
    bounds = pin_offsets()
    byaddr = catalog_names()
    syms = our_symbols(elf)

    # A reviewed EXCLUDE region is a SINGLE structured object (a dispatch table,
    # a kernel object).  Iteration 16's stage a3 iterated plain groups and could
    # therefore restore some of an excluded object's words while leaving others
    # zero -- exactly the half-initialised table the iteration-15 policy forbids
    # (g_screen_render_table came out with three handlers set and eight screen
    # ids still zero).  Treat each region atomically instead: restore the WHOLE
    # region, bytes plus relocations, only when every pointer word in it
    # resolves, and otherwise drop every group that touches it.
    units, atomic = [], set()
    for lo, hi in groups(blob, bounds):
        if excluded(lo, hi) is None:
            units.append((lo, hi))
    for a, b, is_atomic, _why in EXCLUDE:
        if is_atomic and any(blob[a:b]):
            units.append((a, b))
            atomic.add((a, b))
    units.sort()

    extra, ptrs = [], []
    for lo, hi in units:
        wlo, whi = lo & ~3, (hi + 3) & ~3
        if not any(mask[wlo:whi]) and (lo, hi) not in atomic:
            continue            # already restored verbatim by stage a2
        resolved = []
        ok = True
        for w in range(wlo, whi, 4):
            word = int.from_bytes(blob[w:w + 4], "little")
            if not pointerish(word):
                continue
            r = resolve_pointer(word, wlo, whi, byaddr, syms)
            if r is None:
                ok = False
                break
            resolved.append((w, r, word))
        if not ok:
            if verbose:
                print("  drop  +0x%04x..0x%04x  (unresolvable pointer)" % (lo, hi))
            continue
        # copy the group on the aligned word grid so a pointer word is whole
        extra.append((wlo, bytes(blob[wlo:whi])))
        for w, r, word in resolved:
            ptrs.append((w, r[0], r[1], word))
        if verbose:
            print("  RELOC +0x%04x..0x%04x  (%d B, %d ptr words)"
                  % (wlo, whi, whi - wlo, len(resolved)))
    mq_runs, mq_ptrs, buffers = static_msgq_units(blob, MSGQ_SETS[msgq_set])
    if verbose:
        for ident, size, why in buffers:
            print("  MSGQ  %-34s %6d B  (%s)" % (ident, size, why))
    extra += mq_runs
    ptrs += mq_ptrs

    runs = sorted(keep + extra)
    # a restore unit must never overlap another one
    for (a_off, a_b), (b_off, _b) in zip(runs, runs[1:]):
        assert a_off + len(a_b) <= b_off, (hex(a_off), hex(b_off))
    return runs, ptrs, buffers


def emit(runs, stage, path, ptrs=None, buffers=None):
    ptrs = ptrs or []
    buffers = buffers or []
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
    lines.append("#include <zephyr/device.h>\n")
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
    if buffers:
        lines.append(
            "/* Ring buffers for the shipped static K_MSGQ_DEFINE objects.  The shipped\n"
            " * struct points at a dedicated array whose ADDRESS carries no semantics --\n"
            " * only its size does -- and that array lives above the recovered RAM arena,\n"
            " * so our build supplies its own of the exact shipped size and the four ring\n"
            " * pointer words below are relocated onto it.  The result is bit-for-bit what\n"
            " * k_msgq_init(q, buf, msg_size, max_msgs) builds. */\n")
        for ident, size, why in buffers:
            lines.append("static unsigned char %s[%d] __aligned(4);\t/* %s */\n"
                         % (ident, size, why))
        lines.append("\n")
    if ptrs:
        flash = sorted({name for _, kind, name, _ in ptrs if kind == "flash"})
        lines.append(
            "/* Relocation-aware pointer words.  The shipped image stores ABSOLUTE\n"
            " * original-image addresses here; our build relocates every one of them, so\n"
            " * each word is taken from the LINKER through an `__asm__`-alias extern (flash\n"
            " * function pointers, Thumb bit re-set), from DEVICE_DT_GET (shipped\n"
            " * `struct device` pointers, identified by the device's own name string and\n"
            " * config base in app_update.bin) or computed from the arena base\n"
            " * (self-referential SRAM pointers).  No raw absolute address is ever stored.\n"
            " */\n")
        for name in flash:
            lines.append("extern const unsigned char __g1_dp_%s[] __asm__(\"%s\");\n"
                         % (name, name))
        lines.append("\nstatic void g1_arena_data_relocate(void)\n{\n")
        for off, kind, name, word in sorted(ptrs):
            if kind == "flash":
                lines.append(
                    "\t*(void **)&g1_ram_arena[0x%05x] ="
                    " (void *)(((unsigned long)&__g1_dp_%s) | 1u);"
                    "\t/* was 0x%08x */\n" % (off, name, word))
            elif kind == "device":
                lines.append(
                    "\t*(const struct device **)&g1_ram_arena[0x%05x] ="
                    " DEVICE_DT_GET(DT_NODELABEL(%s));"
                    "\t/* was 0x%08x */\n" % (off, name, word))
            elif kind == "extbuf":
                ident, delta = name
                lines.append(
                    "\t*(void **)&g1_ram_arena[0x%05x] = (void *)&%s[%d];"
                    "\t/* was 0x%08x (msgq ring) */\n" % (off, ident, delta, word))
            else:
                lines.append(
                    "\t*(void **)&g1_ram_arena[0x%05x] = (void *)&g1_ram_arena[0x%05x];"
                    "\t/* was 0x%08x (self) */\n" % (off, name, word))
        lines.append("}\n\n")
    lines.append(
        "/* PRE_KERNEL_1 priority 0: after z_bss_zero/z_data_copy and before any\n"
        " * recovered device or application initialiser can observe the arena. */\n"
        "static int g1_arena_data_init(void)\n{\n"
        "\tfor (unsigned int i = 0; i < ARRAY_SIZE(g1_arena_data_runs); i++) {\n"
        "\t\tconst struct g1_arena_data_run *r = &g1_arena_data_runs[i];\n\n"
        "\t\tif (r->len == 0U) {\n\t\t\tcontinue;\n\t\t}\n"
        "\t\tmemcpy(&g1_ram_arena[r->off], &g1_arena_data_bytes[r->src], r->len);\n"
        "\t}\n"
        + ("\tg1_arena_data_relocate();\n" if ptrs else "")
        + "\treturn 0;\n}\n\n"
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
    ap.add_argument("--stage", default="a2", choices=("a1", "a2", "a3"))
    ap.add_argument("--elf", default="/private/tmp/g1-i16-app/zephyr/zephyr.elf",
                    help="stage a3 only: our build's ELF, read with `nm` so a "
                         "pointer is never emitted for a symbol this link does "
                         "not define (the 0-undefined link gate re-checks it)")
    ap.add_argument("-o", "--out",
                    default=os.path.join(REPO, "recon/application/app/src/g1_app_data_image.c"))
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("-v", "--verbose", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--static-msgq", default="all", choices=tuple(MSGQ_SETS),
                    help="stage a3 only: which shipped K_MSGQ_DEFINE objects "
                         "get their ring buffer restored (see STATIC_MSGQS)")
    args = ap.parse_args()
    if args.selftest:
        return selftest()
    buffers = []
    if args.stage == "a3":
        runs, ptrs, buffers = runs_for_stage_a3(args.elf, args.verbose,
                                                args.static_msgq)
    else:
        runs, _ = runs_for_stage(args.stage, args.verbose)
        ptrs = []
    if args.dry_run:
        print("stage=%s runs=%d bytes=%d ptrs=%d msgq=%d"
              % (args.stage, len(runs), sum(len(b) for _, b in runs), len(ptrs),
                 len(buffers)))
        return 0
    n, total = emit(runs, args.stage, args.out, ptrs, buffers)
    print("wrote %s: stage=%s runs=%d bytes=%d relocated-pointers=%d"
          % (args.out, args.stage, n, total, len(ptrs)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
