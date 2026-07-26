#!/usr/bin/env python3
"""Decode the shipped `.rodata` sector (CPUAPP and CPUNET) into byte-verified C.

WHY THIS EXISTS
---------------
Large parts of the recovered CPUAPP `.rodata` are still referenced through
ABSOLUTE PINS into the original image -- `PROVIDE(rodata_<hex> = 0x<hex>)` lines
in `recon/symbols/g1_app_globals.ld`.  Our image is relocated, so every one of
those addresses now names unrelated bytes in OUR build.  That defect class has
already produced, among others, the SPI driver base pointer, the nPM1300 linear
range tables, six GPIO descriptors, the Bluetooth advertising parameters and --
most expensively -- the entire default-font glyph directory and bitmap blob,
whose entry count read back as 536,918,600 and hung the display thread
(`recon/emulator/reports/our_boot_bringup.md` section 33.7).

This generator is the sibling of `gen_app_data_image.py` (`.data`) and
`gen_app_string_rodata.py` (the printable-string subset of `.rodata`).  It
sweeps what those two leave behind: every numeric `rodata_` pin in the `.rodata`
sector that no recovered source defines, decodes it by kind, and emits real C
objects whose bytes are proven equal to `app_update.bin`.

SECTOR EXTENT (proven, not assumed)
-----------------------------------
* LOW edge 0x879a8.  The highest catalogued CPUAPP function
  (`recon/catalogs/app_funcs.json.gz`) is `FUN_00087996`, which ends at
  0x879a6; 0x879a6..0x879a8 is alignment padding.  From 0x879b0 the image holds
  the Zephyr `struct init_entry` array -- 8-byte records `{ int (*init)(const
  struct device *); const struct device *dev; }` whose first words are Thumb
  function pointers (0x4c145, 0x51199, 0x61575, ...) and whose second words are
  either NULL or `struct device` pointers into 0x87b..-0x87d.. .  That array is
  the first subsection of `.rodata` in Zephyr's `common-rom.ld`.
* HIGH edge 0xf6d64.  This is the `.data` load address, proven three
  independent ways in `gen_app_data_image.py` (`--selftest` reproduces all
  three: `g_st25dv_i2c_dev`, the product-code/serial ASCII, the MD5 padding
  block).  `.rodata` ends where the `.data` load image begins.

REGIONS AND EXTENTS
-------------------
A pin's extent is `[pin_va, next_boundary)` where the boundary set is the union
of every other numeric pin VA, the start and end of every object already
emitted (`recon/data/*.c`, `g1_app_string_rodata.c`, `g1_app_font_rodata.c`)
and the sector edges.  That is exactly the two-sided argument section 33.7 used
for the font directory ("0x98e3c is where the next recovered rodata symbol
begins"), applied uniformly.

Consecutive pins whose extents touch are emitted as ONE object named after the
run's first pin, and the interior pins are re-pinned as `PROVIDE(rodata_X =
<run> + delta)` in the generated linker fragment.  This is deliberate: emitting
each pin as its own object would let the linker separate bytes the shipped
image had adjacent, so any consumer that indexes past one pin into the next --
which is exactly how the font directory and blob are read -- would read the
wrong object.  `PROVIDE(rodata_883b0 = rodata_0x88340 + 0x70)` is the existing
precedent for interior pins.  The one place a run is split is a pin that starts
its own NUL-terminated string (see `independent_string`): a C string is
addressed by its first byte and every reader stops at its NUL, so nothing can
index out of it, and splitting there restores `--gc-sections` granularity.

CPUNET
------
`--core net` runs the same pipeline over `netcore_image.bin`.  Its sector is
[0x0103be56, 0x0103ed24) in RUNTIME coordinates and all reads go through
`net_extract.read_runtime`; see `CoreSpec` for the oracle that establishes the
coordinate space of the net pins, which is the hazard AGENTS.md warns about.

KINDS
-----
`string`/`string_pool`  the extent is exactly a sequence of NUL-terminated
                        printable strings  -> `const char []`
`ptr_table`             4-aligned, size % 4 == 0, and EVERY non-zero word is a
                        flash or SRAM pointer -> emitted as an array of
                        RELOCATED symbol references through the `__asm__`-alias
                        mechanism of `recon/emulator/reports/pointer_rebind.md`.
                        Atomic: unless every pointer word resolves, the whole
                        region is deferred.  A raw absolute word is never
                        emitted.
`u8/u16/u32_table`      element width PROVEN from the access footprint -- the
                        literal-pool site in `.text` that names the region is
                        located, the `ldr rD,[pc,#imm]` that loads it is
                        disassembled, and the load/store width of the first
                        access through rD (with intra-function taint
                        propagation) is read off.  Width is never guessed.
`blob`                  everything else -> `const unsigned char []`, byte-exact.
                        Font/bitmap blobs land here; their nibble histograms
                        (0x00/0x0f/0xf0/0xff dominant) identify them as the
                        packed 4bpp glyph bitmaps of the three font families
                        section 33.12 item 4 lists as unrecovered.

VERIFICATION (ON BY DEFAULT -- an object that fails is never written)
---------------------------------------------------------------------
Every candidate is compiled with the pinned Zephyr toolchain in a scratch
directory; each defined symbol's bytes are read out of the object and
byte-compared with the shipped image read through `tools/extract.py` /
`tools/net_extract.py` -- the same gate `tools/verify_data.py` applies to
`recon/data`.  Only then is the tree written, so a failing object is reported
as `deferred` in the ledger and does not exist as a source file.  `--no-verify`
skips the gate for diagnosis only.

For a pointer-bearing region byte equality can only hold MODULO RELOCATION: the
pointer words are compared with their windows masked, and the object is
additionally required to carry an `R_ARM_ABS32` relocation at exactly each
masked offset naming exactly the expected symbol.  That status is recorded
verbatim as `byte-exact-modulo-relocation`, never as `byte-exact`.

THIS PASS EMITS AND VERIFIES ONLY.  Nothing here is added to any CMake source
list; `recon/symbols/g1_{app,net}_globals.ld` are not modified.  The generated
linker fragment is written next to the sources for a later wiring pass.

Usage:
  PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_rodata_sources.py \\
      --core app --elf /private/tmp/g1-i33c-app/zephyr/zephyr.elf
  PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_rodata_sources.py \\
      --core net --elf /private/tmp/g1-i30e-net/zephyr/zephyr.elf
  PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_rodata_sources.py \\
      --core app --check      # deterministic-output gate
"""

import argparse
import bisect
import glob
import gzip
import json
import os
import re
import struct
import subprocess
import sys
import tempfile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REPO = os.path.dirname(REPO) if os.path.basename(REPO) == "recon" else REPO
sys.path.insert(0, os.path.join(REPO, "tools"))
import extract as E  # noqa: E402

# ---------------------------------------------------------------------------
# per-core geometry (see module docstring for the proof of the CPUAPP edges)
# ---------------------------------------------------------------------------
class CoreSpec:
    """Everything that differs between CPUAPP and CPUNET.

    CPUNET carries the extra hazard AGENTS.md warns about: the image was
    imported for analysis at 0x01008000 but executes at 0x01008800, and the two
    windows overlap numerically, so an untyped integer is ambiguous.  The
    `rodata_<hex>` pins in `recon/symbols/g1_net_globals.ld` are RUNTIME
    addresses.  That is an oracle result, not an assumption: reading each of the
    222 numeric net pins one byte early, 93 of them sit immediately after a NUL
    and start a printable C string when read through `net_extract.read_runtime`
    versus 2 through `read_analysis`; the runtime reads land exactly on
    "(null)", "HCI rpmsg TX", "cpunet-esbs" and "WEST_TOPDIR/zephyr/lib/...",
    while the analysis reads land mid-word ("f_timer.h", "ion (%u)").
    CPUNET *function* catalogue entries stay in ANALYSIS space, so the
    footprint prober converts explicitly and never by arithmetic on a bare int.
    """

    def __init__(self, name, **kw):
        self.name = name
        self.__dict__.update(kw)

    def read(self, va, n):
        return self._read(va, n)


def _app_spec():
    return CoreSpec(
        "app",
        _read=E.read,
        text_lo=0x0000C200,
        # highest catalogued function FUN_00087996 ends at 0x879a6; 0x879a8 is
        # the first `.rodata` word (the Zephyr `struct init_entry` array).
        rodata_lo=0x879A8,
        # == DATA_LMA in gen_app_data_image.py, proven three ways there.
        rodata_hi=0xF6D64,
        flash=(0x0000C200, 0x00100000),
        sram=(0x20000000, 0x20080000),
        globals_ld=os.path.join(REPO, "recon/symbols/g1_app_globals.ld"),
        data_dirs=[os.path.join(REPO, "recon/data")],
        hand_sources=[os.path.join(REPO, "recon/application/app/src",
                                   "g1_app_string_rodata.c"),
                      os.path.join(REPO, "recon/application/app/src",
                                   "g1_app_font_rodata.c")],
        source_globs=["recon/application/app/src/*.c", "recon/app/src/*.c",
                      "recon/data/*.c", "recon/generated/*.c"],
        func_catalog=os.path.join(REPO,
                                  "recon/catalogs/function_names_app.json"),
        func_dump=os.path.join(REPO, "recon/catalogs/app_funcs.json.gz"),
        func_space_delta=0,
        out_dir=os.path.join(REPO, "recon/application/rodata"),
        prefix="g1_app_rodata",
        ledger=os.path.join(REPO,
                            "recon/ownership/rodata_decode_ledger.json"),
    )


def _net_spec():
    import net_extract as NE
    from net_address_space import ANALYSIS_TO_RUNTIME_DELTA
    return CoreSpec(
        "net",
        _read=NE.read_runtime,
        text_lo=0x01008800,
        # highest catalogued function FUN_0103b650 ends at analysis 0x0103b656
        # = runtime 0x0103be56.
        rodata_lo=0x0103BE56,
        # shipped netcore `.data` load image, runtime LMA (the same read
        # recon/application/verify_net_stock_data_window.py and
        # gen_net_ram_relocs.py make); 0x0103ed24 - 0x01008800 + 0xc3c is
        # exactly the 225632-byte netcore_image.bin.
        rodata_hi=0x0103ED24,
        flash=(0x01008800, 0x01048000),
        sram=(0x20000000, 0x21010000),
        globals_ld=os.path.join(REPO, "recon/symbols/g1_net_globals.ld"),
        data_dirs=[os.path.join(REPO, "recon/net/data")],
        hand_sources=[],
        source_globs=["recon/application/net/src/*.c", "recon/net/src/*.c",
                      "recon/net/data/*.c"],
        func_catalog=os.path.join(REPO,
                                  "recon/catalogs/function_names_net.json"),
        func_dump=os.path.join(REPO, "recon/catalogs/net_funcs.json.gz"),
        # catalogue entries are ANALYSIS addresses; a pointer word stored in
        # the image is a RUNTIME address.
        func_space_delta=ANALYSIS_TO_RUNTIME_DELTA,
        out_dir=os.path.join(REPO, "recon/application/rodata"),
        prefix="g1_net_rodata",
        ledger=os.path.join(REPO,
                            "recon/ownership/rodata_decode_ledger_net.json"),
    )


CORE = None

CC = ("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
      "arm-zephyr-eabi-gcc")
CFLAGS = ["-c", "-Os", "-mcpu=cortex-m33", "-mthumb", "-ffreestanding",
          "-fdata-sections", "-w"]

SHARDS = 8
PTR_BEARING_MAX = 4096       # below this, one pointer word makes it a table
PTR_DENSE = 0.20             # above it, only a dense region counts as one
STRING_MIN_BODY = 1

PIN_RE = re.compile(r"^\s*PROVIDE\((rodata_[0-9a-fA-F]+)\s*=\s*"
                    r"(0x[0-9a-fA-F]+)\);")
ANY_PIN_RE = re.compile(r"^\s*PROVIDE\((rodata_[0-9a-fA-F]+)\s*=\s*(.+?)\);")
DEF_RE = re.compile(r"\b(?:const\s+)?(?:unsigned\s+char|char|uint\d+_t|"
                    r"int\d+_t|float|double)\s+(rodata_[0-9a-fA-F]+)\s*\[")
HAND_OBJ_RE = re.compile(r"/\*\s*(0x[0-9a-fA-F]+)[^*]*\*/\s*const\s+unsigned"
                         r"\s+char\s+(\w+)\[(\d+)\]")


# ---------------------------------------------------------------------------
# inputs
# ---------------------------------------------------------------------------
def numeric_pins():
    """{name: va} for every `PROVIDE(rodata_X = 0x...)` numeric pin."""
    out = {}
    with open(CORE.globals_ld, encoding="utf-8") as fh:
        for line in fh:
            m = PIN_RE.match(line)
            if m:
                out[m.group(1)] = int(m.group(2), 16)
    return out


def expression_pins():
    """Names already re-pinned onto a real symbol (`= sym + delta`).

    These are NOT unswept: the linker resolves them through a relocated
    definition even though `nm` still prints them as class `A`.
    """
    out = set()
    with open(CORE.globals_ld, encoding="utf-8") as fh:
        for line in fh:
            m = ANY_PIN_RE.match(line)
            if m and not re.fullmatch(r"0x[0-9a-fA-F]+", m.group(2).strip()):
                out.add(m.group(1))
    return out


def defined_rodata_symbols():
    """`rodata_<hex>` symbols an already-recovered .c defines."""
    out = set()
    for pat in CORE.source_globs:
        for path in sorted(glob.glob(os.path.join(REPO, pat))):
            if os.path.dirname(path) == CORE.out_dir:
                continue
            with open(path, errors="ignore") as fh:
                out |= {m.group(1) for m in DEF_RE.finditer(fh.read())}
    return out


def emitted_objects():
    """[(va, size, symbol)] for every rodata object a recovered .c defines."""
    out = []
    for data_dir in CORE.data_dirs:
        for path in sorted(glob.glob(os.path.join(data_dir, "*.c"))):
            m = re.search(r"rodata_((?:0x)?[0-9a-fA-F]+)",
                          os.path.basename(path))
            if not m:
                continue
            base = int(m.group(1), 16)
            text = open(path).read()
            dl = re.search(r"(\d+)\s*bytes", text)
            size = int(dl.group(1)) if dl else 0
            cand = [g for g in
                    re.findall(r"\b(\w+)\s*(?:\[\s*\d*\s*\])?\s*=\s*\{", text)
                    if ("%x" % base) in g.lower()]
            if cand and size:
                out.append((base, size, cand[0]))
    for path in CORE.hand_sources:
        text = open(path).read()
        for m in HAND_OBJ_RE.finditer(text):
            out.append((int(m.group(1), 16), int(m.group(3)), m.group(2)))
    out.sort()
    return out


def function_entries():
    """{entry_va: symbol_name} for every catalogued function of this core.

    CPUNET catalogue entries are ANALYSIS addresses while a pointer word stored
    in the image is a RUNTIME address, so the conversion is applied explicitly
    here (`CoreSpec.func_space_delta`) rather than left to the caller.
    """
    doc = json.load(open(CORE.func_catalog))
    return {int(v["address"], 16) + CORE.func_space_delta: v["name"]
            for v in doc["by_address"].values()}


# ---------------------------------------------------------------------------
# access-footprint width evidence
# ---------------------------------------------------------------------------
LOAD_WIDTH = {"ldrb": 1, "ldrsb": 1, "ldrh": 2, "ldrsh": 2, "ldr": 4,
              "ldrd": 8, "strb": 1, "strh": 2, "str": 4, "strd": 8}


class Footprint:
    """Element width read off the code that actually reads the region.

    A rodata address reaches code as a literal-pool word in `.text`.  For each
    such word we locate the `ldr rD,[pc,#imm]` that loads it, then follow rD
    forward inside the same catalogued function (propagating through
    mov/add/sub) and record the width of the first memory access based on it.
    Nothing is inferred from the data's own shape.
    """

    def __init__(self):
        from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_MCLASS
        from capstone.arm import ARM_OP_MEM, ARM_OP_REG, ARM_REG_PC
        self._MEM, self._REG, self._PC = ARM_OP_MEM, ARM_OP_REG, ARM_REG_PC
        self.md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
        self.md.detail = True
        doc = json.load(gzip.open(CORE.func_dump, "rt"))
        # normalised to the same coordinate space `CORE.read` uses
        self.funcs = sorted((f["entry"] + CORE.func_space_delta, f["size"],
                             f["name"]) for f in doc["functions"])
        self.entries = [f[0] for f in self.funcs]
        self.text_hi = CORE.rodata_lo
        self.lits = self._scan_literals()
        self._dis = {}

    def _scan_literals(self):
        blob = CORE.read(CORE.text_lo, self.text_hi - CORE.text_lo)
        lits = {}
        for off in range(0, len(blob) - 3, 4):
            word = struct.unpack_from("<I", blob, off)[0]
            if CORE.rodata_lo <= word < CORE.rodata_hi:
                lits.setdefault(word, []).append(CORE.text_lo + off)
        return lits

    def _func_of(self, va):
        i = bisect.bisect_right(self.entries, va) - 1
        if i < 0:
            return None
        entry, size, name = self.funcs[i]
        return (entry, size, name) if va < entry + max(size, 4) else None

    def _insns(self, entry, size):
        if (entry, size) not in self._dis:
            self._dis[(entry, size)] = list(
                self.md.disasm(CORE.read(entry, size), entry))
        return self._dis[(entry, size)]

    def widths(self, va):
        """[(mnemonic, width, site_va)] evidence for the region at `va`."""
        ev = []
        for site in self.lits.get(va, [])[:8]:
            fn = self._func_of(site)
            if not fn:
                continue
            for insn in self._probe(fn, site):
                ev.append(insn)
        return ev

    def _probe(self, fn, site):
        entry, size, _name = fn
        out = []
        insns = self._insns(entry, size)
        for k, ins in enumerate(insns):
            ops = ins.operands
            if not (ins.mnemonic.startswith("ldr") and ops
                    and ops[-1].type == self._MEM
                    and ops[-1].mem.base == self._PC):
                continue
            if ((ins.address + 4) & ~3) + ops[-1].mem.disp != site:
                continue
            taint = {ops[0].reg}
            for nxt in insns[k + 1:]:
                mn = nxt.mnemonic.split(".")[0]
                nops = nxt.operands
                if nops and nops[-1].type == self._MEM \
                        and nops[-1].mem.base in taint:
                    if mn in LOAD_WIDTH:
                        out.append((mn, LOAD_WIDTH[mn], nxt.address))
                    elif mn in ("vldr", "vstr"):
                        wide = nxt.reg_name(nops[0].reg).startswith("d")
                        out.append((mn, 8 if wide else 4, nxt.address))
                    continue
                if mn in ("mov", "movs", "add", "adds", "sub", "subs", "orr") \
                        and len(nops) >= 2 and nops[0].type == self._REG:
                    if {o.reg for o in nops[1:]
                            if o.type == self._REG} & taint:
                        taint.add(nops[0].reg)
                        continue
                if nops and nops[0].type == self._REG and nops[0].reg in taint \
                        and not mn.startswith(("cmp", "tst", "str", "push",
                                               "b")):
                    taint.discard(nops[0].reg)
                if not taint:
                    break
        return out


# ---------------------------------------------------------------------------
# region construction
# ---------------------------------------------------------------------------
def build_regions():
    pins = numeric_pins()
    defined = defined_rodata_symbols()
    expr = expression_pins()
    objs = emitted_objects()

    bounds = {v for v in pins.values()
              if CORE.flash[0] <= v < CORE.flash[1]}
    for va, size, _sym in objs:
        bounds.add(va)
        bounds.add(va + size)
    bounds.add(CORE.rodata_lo)
    bounds.add(CORE.rodata_hi)
    bounds = sorted(bounds)

    todo = sorted((va, name) for name, va in pins.items()
                  if name not in defined and name not in expr
                  and CORE.rodata_lo <= va < CORE.rodata_hi)
    entries = []
    for va, name in todo:
        i = bisect.bisect_right(bounds, va)
        nxt = bounds[i] if i < len(bounds) else CORE.rodata_hi
        ext = min(nxt, CORE.rodata_hi) - va
        if ext > 0:
            entries.append({"va": va, "name": name, "ext": ext})

    runs = []
    cur = []
    for ent in entries:
        if cur and cur[-1]["va"] + cur[-1]["ext"] == ent["va"] \
                and not independent_string(ent):
            cur.append(ent)
        else:
            if cur:
                runs.append(cur)
            cur = [ent]
    if cur:
        runs.append(cur)
    return runs, objs, pins, defined, expr


def independent_string(ent):
    """True when this pin starts its own NUL-terminated string.

    Runs exist so a consumer that indexes past one pin into the next still
    reads the shipped bytes.  A C string is the one shape where that cannot
    happen: it is addressed by its first byte and every reader stops at its
    NUL, so the byte after it is unreachable by definition.  Splitting the run
    there is therefore free of the adjacency hazard and buys `--gc-sections`
    granularity -- which matters, because the CPUNET string table is one
    11 kB contiguous chain of pins on an image that is already 98.5 % full.

    The test is two-sided: the byte BEFORE the pin must be a NUL (so the pin is
    a string-table entry, not an interior offset into one) and the pin's own
    bytes must be printable up to a NUL inside its extent.
    """
    prev = CORE.read(ent["va"] - 1, 1)
    if prev != b"\0":
        return False
    body = CORE.read(ent["va"], ent["ext"])
    end = body.find(b"\0")
    return end >= 1 and text_like(body[:end])


# ---------------------------------------------------------------------------
# classification
# ---------------------------------------------------------------------------
def pointerish(word):
    return CORE.flash[0] <= word < CORE.flash[1] or CORE.sram[0] <= word < CORE.sram[1]


def printable(chunk):
    return all(32 <= b < 127 or b in (9, 10, 13) for b in chunk)


def text_like(chunk):
    """Printable ASCII, or valid UTF-8 with no stray control bytes.

    The G1 UI strings are Chinese, so a large share of the shipped `.rodata`
    text is multi-byte UTF-8 ("\\xe5\\xbe\\xae\\xe4\\xbf\\xa1" = the WeChat
    label).  Treating those as opaque blobs would be byte-exact but would hide
    what they are, so they are decoded as strings with the decoded text in the
    emitted comment.  The bytes are emitted as a byte array either way, so the
    verification result is unchanged.
    """
    if printable(chunk):
        return True
    if not chunk or max(chunk) < 0x80:
        return False
    try:
        text = chunk.decode("utf-8")
    except UnicodeDecodeError:
        return False
    return all(ch in "\t\n\r" or ord(ch) >= 32 for ch in text)


def pointer_words(va, data):
    """Indices of 4-aligned words that look like original-image pointers."""
    if va % 4 or len(data) < 4:
        return [], []
    words = [struct.unpack_from("<I", data, i)[0]
             for i in range(0, (len(data) // 4) * 4, 4)]
    return words, [i for i, w in enumerate(words) if pointerish(w)]


def classify(va, data, footprint_ev):
    """(kind, detail) -- see the module docstring for each kind's rule."""
    n = len(data)
    words, ptr_idx = pointer_words(va, data)
    # TEXT FIRST.  A region that is nothing but printable bytes and NULs cannot
    # be a pointer array -- every real pointer word here contains a 0x00 or a
    # high byte that breaks printability -- while the converse false positive is
    # common and would be destructive: ASCII text is full of 4-aligned words
    # that land in a pointer window (any string containing a space gives
    # 0x20xxxxxx, which is inside CPUNET's SRAM window, so "HCI rpmsg TX" scored
    # as pointer-bearing until this test was moved ahead of the pointer test).
    if n > 0 and data[-1] == 0:
        parts = data.split(b"\0")[:-1]
        body = sum(len(p) for p in parts)
        if parts and body >= STRING_MIN_BODY and all(text_like(p)
                                                     for p in parts):
            kind = "string" if len(parts) == 1 else "string_pool"
            return kind, {"strings": len(parts), "text_bytes": body,
                          "utf8": not all(printable(p) for p in parts)}
    if ptr_idx:
        density = len(ptr_idx) / len(words)
        # A region SMALL enough to be a table, or dense enough to be one, is
        # treated as pointer-bearing whatever else it looks like: emitting its
        # raw words would bake ORIGINAL-image absolute addresses into our
        # image, which is the entire defect class this generator exists to
        # remove.  Above PTR_BEARING_MAX the rule flips to density, because a
        # packed 4bpp glyph blob contains thousands of incidental words that
        # happen to fall inside the flash window (nibble runs like 00 f0 0f 00)
        # and deferring 66 kB of pixels over pixel noise would be wrong.
        if n <= PTR_BEARING_MAX or density >= PTR_DENSE:
            nonzero = [w for w in words if w]
            kind = ("ptr_table" if nonzero and all(pointerish(w)
                                                   for w in nonzero)
                    else "ptr_record")
            return kind, {"words": len(words), "ptr_words": len(ptr_idx),
                          "density": round(density, 4),
                          "tail_bytes": n - 4 * len(words)}
    widths = {w for _mn, w, _site in footprint_ev}
    if len(widths) == 1:
        w = widths.pop()
        if w in (1, 2, 4) and n % w == 0 and va % w == 0 and n >= w:
            return ("u8_table" if w == 1 else
                    "u16_table" if w == 2 else "u32_table"), {
                        "width": w, "elements": n // w,
                        "evidence": ["%s@0x%x" % (mn, site)
                                     for mn, _w, site in footprint_ev[:4]]}
    if all(b == 0 for b in data):
        return "zero_fill", {}
    return "blob", {"incidental_ptr_words": len(ptr_idx),
                    "words": len(words)}


# ---------------------------------------------------------------------------
# pointer resolution (relocation-aware)
# ---------------------------------------------------------------------------
class Resolver:
    """Turn a shipped absolute rodata word into a reference OUR link relocates.

    Only exact classes are accepted, mirroring `gen_app_data_image.py`:
      * a Thumb flash word whose `& ~1` is a catalogued function entry;
      * a flash word that lands inside an object this project defines (a
        `recon/data` table, a string/font object, or one of this generator's
        own runs) -- emitted as `symbol + delta`;
      * the zero word -> NULL.
    An SRAM word, or a flash word inside no known object, does not resolve, and
    a region containing one is deferred whole (atomic policy).
    """

    def __init__(self, objs, own_runs, funcs):
        self.funcs = funcs
        self.spans = sorted(objs + own_runs)
        self.starts = [s[0] for s in self.spans]

    def _object_for(self, addr):
        i = bisect.bisect_right(self.starts, addr) - 1
        if i < 0:
            return None
        va, size, sym = self.spans[i]
        return (sym, addr - va) if va <= addr < va + size else None

    def resolve(self, word):
        if word == 0:
            return ("null", None, 0)
        if CORE.flash[0] <= word < CORE.flash[1]:
            if word & 1 and (word & ~1) in self.funcs:
                return ("func", self.funcs[word & ~1], 1)
            hit = self._object_for(word)
            if hit:
                return ("data", hit[0], hit[1])
            if (word & ~1) in self.funcs:
                return ("func", self.funcs[word & ~1], 0)
        return (None, None, 0)


# ---------------------------------------------------------------------------
# emission
# ---------------------------------------------------------------------------
def c_bytes(data, indent="\t"):
    out = []
    for i in range(0, len(data), 16):
        out.append(indent + " ".join("0x%02x," % b for b in data[i:i + 16]))
    return "\n".join(out)


def c_string_comment(data):
    parts = data.split(b"\0")[:-1]
    out = []
    off = 0
    for p in parts:
        out.append(" *   +0x%04x %r" % (off, p.decode("utf-8", "replace")))
        off += len(p) + 1
    return "\n".join(out[:40])


def emit_region(reg):
    """C text for one decoded region.  `reg` is the ledger row."""
    va, sym, kind = reg["va"], reg["symbol"], reg["kind"]
    data = CORE.read(va, reg["bytes"])
    ident = "g1_ro_%x" % va
    head = ["/* 0x%05x  %-12s %6d B  %s" % (va, kind, len(data),
                                            reg["purpose"])]
    if reg["retires"][1:]:
        head.append(" * interior pins: " + ", ".join(reg["retires"][1:][:12])
                    + (" ..." if len(reg["retires"]) > 13 else ""))
    if kind in ("string", "string_pool"):
        head.append(c_string_comment(data))
    head.append(" */")
    body = "\n".join(head) + "\n"

    if kind in ("string", "string_pool"):
        body += ("const char %s[%d] __asm__(\"%s\") = {\n%s\n};\n"
                 % (ident, len(data), sym, c_bytes(data)))
    elif kind == "u16_table":
        vals = struct.unpack("<%dH" % (len(data) // 2), data)
        rows = ["\t" + " ".join("0x%04x," % v for v in vals[i:i + 8])
                for i in range(0, len(vals), 8)]
        body += ("const unsigned short %s[%d] __asm__(\"%s\") = {\n%s\n};\n"
                 % (ident, len(vals), sym, "\n".join(rows)))
    elif kind == "u32_table":
        vals = struct.unpack("<%dI" % (len(data) // 4), data)
        rows = ["\t" + " ".join("0x%08xu," % v for v in vals[i:i + 4])
                for i in range(0, len(vals), 4)]
        body += ("const unsigned int %s[%d] __asm__(\"%s\") = {\n%s\n};\n"
                 % (ident, len(vals), sym, "\n".join(rows)))
    else:                                    # blob / zero_fill / u8_table
        body += ("const unsigned char %s[%d] __asm__(\"%s\") = {\n%s\n};\n"
                 % (ident, len(data), sym, c_bytes(data)))
    return body


def emit_ptr_region(reg):
    """C text for a relocation-aware pointer table."""
    va, sym = reg["va"], reg["symbol"]
    ident = "g1_ro_%x" % va
    plain = reg["kind"] == "ptr_table"
    cast = "(const void *)" if plain else "(unsigned long)"
    externs = []
    seen = {}
    items = []
    for i, res in enumerate(reg["pointers"]):
        kind, name, delta, word = res
        if kind == "null":
            items.append("\t%s,\t\t\t\t/* 0x%08x */" % ("NULL" if plain
                                                        else "0ul", word))
            continue
        if kind == "literal":
            items.append("\t%s0x%08x,\t\t\t/* scalar */"
                         % ("(const void *)" if plain else "", word))
            continue
        alias = seen.get(name)
        if alias is None:
            alias = "__g1_rp_%s" % re.sub(r"\W", "_", name)
            seen[name] = alias
            externs.append("extern const unsigned char %s[] __asm__(\"%s\");"
                           % (alias, name))
        if delta:
            items.append("\t%s((const unsigned char *)%s + %d),"
                         "\t/* was 0x%08x -> %s+%d */"
                         % (cast, alias, delta, word, name, delta))
        else:
            items.append("\t%s%s,\t/* was 0x%08x -> %s */"
                         % (cast, alias, word, name))
    head = ["/* 0x%05x  %-11s %6d B  %s" % (va, reg["kind"], reg["bytes"],
                                            reg["purpose"]),
            " *",
            " * The shipped image stores ABSOLUTE original-image addresses"
            " here.  Our build",
            " * relocates every one of them, so each word is taken from the"
            " LINKER through",
            " * an `__asm__`-alias extern (recon/emulator/reports/"
            "pointer_rebind.md).  No",
            " * raw absolute address is stored.  Byte equality with"
            " app_update.bin therefore",
            " * holds MODULO RELOCATION -- see the ledger's"
            " `verification` field."]
    if reg["retires"][1:]:
        head.append(" * interior pins: " + ", ".join(reg["retires"][1:][:12]))
    head.append(" */")
    decl = ("const void *const" if plain else "const unsigned long")
    return ("\n".join(head) + "\n" + "\n".join(externs) + "\n"
            + "%s %s[%d] __asm__(\"%s\") = {\n%s\n};\n"
            % (decl, ident, reg["bytes"] // 4, sym, "\n".join(items)))


HEADER = """\
/* GENERATED by recon/application/gen_app_rodata_sources.py -- DO NOT EDIT.
 *
 * Byte-exact CPUAPP `.rodata` objects decoded out of app_update.bin through
 * tools/extract.py.  Each object replaces one or more absolute
 * `PROVIDE(rodata_<hex> = 0x<hex>)` pins in recon/symbols/g1_app_globals.ld
 * with a real, relocatable C definition.  See the generator's docstring for
 * the sector-extent proof, the region/extent rule and the per-kind decode
 * policy; see recon/ownership/rodata_decode_ledger.json for the per-region
 * receipt (VA, extent, kind, C type, verification status, pins retired).
 *
 * shard %d of %d -- %d objects, %d bytes
 */
#include <stddef.h>

"""


def write_sources(rows, out_dir):
    os.makedirs(out_dir, exist_ok=True)
    shards = [[] for _ in range(SHARDS)]
    ptr_rows = []
    for row in rows:
        if row["status"] != "emitted":
            continue
        if row["kind"] in ("ptr_table", "ptr_record"):
            ptr_rows.append(row)
        else:
            shards[row["va"] % SHARDS].append(row)
    written = {}
    for i, rows_i in enumerate(shards):
        path = os.path.join(out_dir, CORE.prefix + "_%02d.c" % i)
        text = HEADER % (i, SHARDS, len(rows_i),
                         sum(r["bytes"] for r in rows_i))
        text += "\n".join(emit_region(r) for r in sorted(
            rows_i, key=lambda r: r["va"]))
        written[path] = text
    if ptr_rows:
        path = os.path.join(out_dir, CORE.prefix + "_ptr.c")
        text = HEADER % (SHARDS, SHARDS, len(ptr_rows),
                         sum(r["bytes"] for r in ptr_rows))
        text += "\n".join(emit_ptr_region(r) for r in sorted(
            ptr_rows, key=lambda r: r["va"]))
        written[path] = text
    return written


def write_fragment(rows, out_dir):
    lines = [
        "/* GENERATED by recon/application/gen_app_rodata_sources.py --"
        " DO NOT EDIT.",
        " *",
        " * Interior-pin re-pins for the decoded `.rodata` runs.  Each run is"
        " emitted as",
        " * ONE C object so the shipped adjacency survives the link; the pins"
        " that fall",
        " * inside a run are re-pinned onto it here, the same way",
        " * `PROVIDE(rodata_883b0 = rodata_0x88340 + 0x70)` already is in",
        " * recon/symbols/g1_app_globals.ld.",
        " *",
        " * NOT INSTALLED THIS PASS.  Wiring it means DELETING the matching",
        " * `PROVIDE(<name> = 0x<hex>)` line from g1_app_globals.ld first --"
        " two PROVIDEs",
        " * for one symbol is a conflict, not an override.",
        " */",
        "",
    ]
    n = 0
    for row in sorted(rows, key=lambda r: r["va"]):
        if row["status"] != "emitted" or len(row["retires"]) < 2:
            continue
        for name, delta in row["interior"]:
            lines.append("PROVIDE(%s = %s + 0x%x);" % (name, row["symbol"],
                                                       delta))
            n += 1
    lines.append("")
    path = os.path.join(out_dir, CORE.prefix + "_interior.ld")
    return {path: "\n".join(lines)}, n


# ---------------------------------------------------------------------------
# verification
# ---------------------------------------------------------------------------
def symbol_bytes(obj, name):
    from elftools.elf.elffile import ELFFile
    with open(obj, "rb") as fh:
        elf = ELFFile(fh)
        symtab = elf.get_section_by_name(".symtab")
        for sym in symtab.iter_symbols():
            if sym.name != name:
                continue
            shndx = sym["st_shndx"]
            if not isinstance(shndx, int):
                return None, None, None
            sec = elf.get_section(shndx)
            data = sec.data()[sym["st_value"]:sym["st_value"] + sym["st_size"]]
            relocs = {}
            rel = elf.get_section_by_name(".rel" + sec.name)
            if rel is not None:
                for r in rel.iter_relocations():
                    off = r["r_offset"] - sym["st_value"]
                    if 0 <= off < sym["st_size"]:
                        rsym = elf.get_section_by_name(".symtab").get_symbol(
                            r["r_info_sym"]).name
                        relocs[off] = (r["r_info_type"], rsym)
            return data, relocs, sec.name
    return None, None, None


R_ARM_ABS32 = 2


def verify(rows, sources):
    """Compile every generated file and byte-compare each symbol vs the image."""
    results = {}
    with tempfile.TemporaryDirectory() as td:
        for path, _text in sorted(sources.items()):
            if not path.endswith(".c"):
                continue
            obj = os.path.join(td, os.path.basename(path) + ".o")
            run = subprocess.run([CC] + CFLAGS + [path, "-o", obj],
                                 capture_output=True, text=True)
            if run.returncode != 0:
                for row in rows:
                    if row.get("file") == os.path.basename(path):
                        results[row["symbol"]] = (
                            "compile-fail", run.stderr.strip()[:120])
                continue
            for row in rows:
                if row.get("file") != os.path.basename(path):
                    continue
                data, relocs, _sec = symbol_bytes(obj, row["symbol"])
                if data is None:
                    results[row["symbol"]] = ("sym-not-found", "")
                    continue
                orig = CORE.read(row["va"], row["bytes"])
                if len(data) != len(orig):
                    results[row["symbol"]] = (
                        "size-mismatch", "%d vs %d" % (len(data), len(orig)))
                    continue
                if row["kind"] not in ("ptr_table", "ptr_record"):
                    if bytes(data) == bytes(orig):
                        results[row["symbol"]] = ("byte-exact", "")
                    else:
                        ndiff = sum(1 for a, b in zip(data, orig) if a != b)
                        results[row["symbol"]] = (
                            "byte-diff", "%d/%d" % (ndiff, len(orig)))
                    continue
                # relocation-masked comparison + relocation identity check
                bad = []
                masked = 0
                for i, res in enumerate(row["pointers"]):
                    kind, name, delta, _word = res
                    if kind in ("null", "literal"):
                        continue
                    off = i * 4
                    masked += 4
                    got = relocs.get(off)
                    if not got or got[0] != R_ARM_ABS32:
                        bad.append("no ABS32 @+0x%x" % off)
                    elif got[1] != ("__g1_rp_%s" % re.sub(r"\W", "_", name)) \
                            and got[1] != name:
                        bad.append("reloc @+0x%x -> %s want %s"
                                   % (off, got[1], name))
                keep = [i for i in range(len(orig))
                        if row["pointers"][i // 4][0] in ("null", "literal")]
                diff = [i for i in keep if data[i] != orig[i]]
                if bad:
                    results[row["symbol"]] = ("reloc-mismatch",
                                              "; ".join(bad[:3]))
                elif diff:
                    results[row["symbol"]] = (
                        "byte-diff-outside-relocs", "%d bytes" % len(diff))
                else:
                    results[row["symbol"]] = (
                        "byte-exact-modulo-relocation",
                        "%d/%d bytes are relocation windows"
                        % (masked, len(orig)))
    return results


# ---------------------------------------------------------------------------
# driver
# ---------------------------------------------------------------------------
def purpose_of(kind, va, data, detail):
    if kind == "ptr_table":
        return "%d-word pointer table" % detail["words"]
    if kind == "string":
        return "C string"
    if kind == "string_pool":
        return "%d-string pool" % detail["strings"]
    if kind in ("u8_table", "u16_table", "u32_table"):
        return "%d x uint%d (width from access footprint)" % (
            detail["elements"], detail["width"] * 8)
    if kind == "zero_fill":
        return "all-zero region"
    hist = {}
    for b in data:
        hist[b] = hist.get(b, 0) + 1
    top = sorted(hist.items(), key=lambda kv: -kv[1])[:4]
    if len(data) >= 512 and sum(c for b, c in top if b in (0, 0x0f, 0xf0,
                                                           0xff)) > 0.8 * len(data):
        return "packed 4bpp glyph/bitmap blob (nibble histogram)"
    return "opaque read-only blob"


def build(args):
    runs, objs, pins, defined, expr = build_regions()
    fp = None
    if not args.no_footprint:
        try:
            fp = Footprint()
        except Exception as exc:                     # capstone unavailable
            print("footprint prober unavailable (%s); widths unproven" % exc)

    own = [(r[0]["va"], sum(x["ext"] for x in r), r[0]["name"]) for r in runs]
    funcs = function_entries()
    resolver = Resolver([(va, size, sym) for va, size, sym in objs], own, funcs)

    rows = []
    for run in runs:
        va = run[0]["va"]
        size = sum(x["ext"] for x in run)
        data = CORE.read(va, size)
        if len(data) != size:
            rows.append({"va": va, "symbol": run[0]["name"], "bytes": size,
                         "kind": "unreadable", "status": "deferred",
                         "reason": "short read from app_update.bin",
                         "retires": [x["name"] for x in run],
                         "interior": [], "purpose": ""})
            continue
        ev = fp.widths(va) if fp else []
        kind, detail = classify(va, data, ev)
        row = {
            "va": va,
            "va_hex": "0x%08x" % va,
            "symbol": run[0]["name"],
            "bytes": size,
            "kind": kind,
            "detail": detail,
            "purpose": purpose_of(kind, va, data, detail),
            "retires": [x["name"] for x in run],
            "interior": [(x["name"], x["va"] - va) for x in run[1:]],
            "status": "emitted",
            "reason": "",
        }
        if kind in ("ptr_table", "ptr_record"):
            row["ctype"] = ("const void *const []" if kind == "ptr_table"
                            else "const unsigned long []")
            words = [struct.unpack_from("<I", data, i)[0]
                     for i in range(0, (size // 4) * 4, 4)]
            if size % 4:
                row["status"] = "deferred"
                row["reason"] = ("pointer-bearing but not word-sized "
                                 "(%d bytes, %d-byte tail): the run's extent "
                                 "must be re-derived before its pointer words "
                                 "can be relocated" % (size, size % 4))
            else:
                res = [resolver.resolve(w) + (w,) if pointerish(w)
                       else ("literal", None, 0, w) for w in words]
                unres = [r[3] for r in res if r[0] is None]
                if unres:
                    sram = sum(1 for w in unres if CORE.sram[0] <= w < CORE.sram[1])
                    row["status"] = "deferred"
                    row["reason"] = (
                        "atomic EXCLUDE: %d/%d pointer words do not resolve to "
                        "a symbol this project defines (%d of them are SRAM "
                        "addresses; first unresolved 0x%08x)"
                        % (len(unres), len([i for i in words
                                            if pointerish(i)]), sram,
                           unres[0]))
                    row["unresolved"] = ["0x%08x" % w for w in unres[:16]]
                else:
                    row["pointers"] = res
        else:
            row["ctype"] = {
                "string": "const char []", "string_pool": "const char []",
                "u16_table": "const unsigned short []",
                "u32_table": "const unsigned int []",
            }.get(kind, "const unsigned char []")
        rows.append(row)

    for row in rows:
        if row["status"] != "emitted":
            continue
        row["file"] = (CORE.prefix + "_ptr.c" if row["kind"] in ("ptr_table", "ptr_record")
                       else CORE.prefix + "_%02d.c" % (row["va"] % SHARDS))
    return rows, pins, defined, expr


def sector_coverage(rows):
    """Byte coverage of the whole sector, plus the regions NOTHING names.

    The third inventory class the task asks for: bytes that are neither an
    already-emitted object nor reachable through any pin.  They carry no
    symbol, so no reconstructed source can currently read them; emitting them
    would add flash for an object with no referrer.  They are listed, not
    emitted, so a later pass can attach them to whatever object really owns
    them (several are clearly interior continuations of a neighbouring table).
    """
    lo, hi = CORE.rodata_lo, CORE.rodata_hi
    cov = bytearray(hi - lo)

    def mark(va, size, tag):
        a, b = max(va, lo), min(va + size, hi)
        fresh = 0
        for i in range(a - lo, b - lo):
            if cov[i] == 0:
                fresh += 1
            cov[i] = tag
        return fresh

    prior = sum(mark(va, size, 1) for va, size, _s in emitted_objects())
    new = sum(mark(r["va"], r["bytes"], 2)
              for r in rows if r["status"] == "emitted")
    held = sum(mark(r["va"], r["bytes"], 3)
               for r in rows if r["status"] != "emitted")
    gaps = []
    start = None
    for i, v in enumerate(cov):
        if v == 0 and start is None:
            start = i
        elif v != 0 and start is not None:
            gaps.append((start + lo, i + lo))
            start = None
    if start is not None:
        gaps.append((start + lo, hi))
    unref = [{"va": "0x%08x" % a, "bytes": b - a}
             for a, b in sorted(gaps, key=lambda g: -(g[1] - g[0]))]
    coverage = {
        "sector_bytes": hi - lo,
        "emitted_before_this_pass": prior,
        "emitted_by_this_pass": new,
        "deferred_by_this_pass": held,
        "unreferenced_bytes": cov.count(0),
        "unreferenced_regions": len(gaps),
    }
    return coverage, unref


def out_of_sector_pins(pins, defined, expr):
    """Undefined numeric `rodata_` pins that are NOT in the `.rodata` sector.

    Two classes, both out of scope for a rodata decode and both reported so the
    inventory is complete: pins into `.text` (literal-pool words and Thumb code
    addresses Ghidra spelled `rodata_`) and pins into the `.data` load image
    (which `gen_app_data_image.py` owns).
    """
    text = [n for n, v in pins.items()
            if n not in defined and n not in expr and v < CORE.rodata_lo]
    data = [n for n, v in pins.items()
            if n not in defined and n not in expr and v >= CORE.rodata_hi]
    return {"in_text": sorted(text), "in_data_load_image": sorted(data),
            "in_text_count": len(text), "in_data_load_image_count": len(data)}


def main():
    global CORE
    ap = argparse.ArgumentParser()
    ap.add_argument("--core", default="app", choices=("app", "net"))
    ap.add_argument("-o", "--out-dir", default=None)
    ap.add_argument("--ledger", default=None)
    ap.add_argument("--check", action="store_true",
                    help="regenerate in memory and fail if the tree differs")
    ap.add_argument("--no-verify", action="store_true",
                    help="skip the compile-and-byte-compare gate (diagnostic "
                         "only -- the gate is ON by default and an object that "
                         "does not byte-match is never emitted)")
    ap.add_argument("--no-footprint", action="store_true")
    ap.add_argument("--elf", default=None,
                    help="optional: cross-check which pins that link still "
                         "resolves to an absolute value")
    args = ap.parse_args()
    CORE = _app_spec() if args.core == "app" else _net_spec()
    args.out_dir = args.out_dir or CORE.out_dir
    args.ledger = args.ledger or CORE.ledger

    rows, pins, defined, expr = build(args)

    # The gate runs BEFORE anything is written: an object that does not
    # byte-match is demoted to `deferred` and never reaches the tree.  The
    # candidate text is compiled from a scratch directory so a failing object
    # cannot be left behind on disk by a crashed run.
    verification = {}
    if not args.no_verify:
        with tempfile.TemporaryDirectory() as staging:
            cand = write_sources(rows, staging)
            for path, text in cand.items():
                with open(path, "w") as fh:
                    fh.write(text)
            verification = verify([r for r in rows
                                   if r["status"] == "emitted"], cand)
        for row in rows:
            if row["status"] != "emitted":
                continue
            res = verification.get(row["symbol"], ("not-run", ""))
            row["verification"] = res[0]
            row["verification_detail"] = res[1]
            if res[0] not in ("byte-exact", "byte-exact-modulo-relocation"):
                row["status"] = "deferred"
                row["reason"] = "verification %s: %s" % res
    else:
        for row in rows:
            if row["status"] == "emitted":
                row["verification"] = "not-run"
                row["verification_detail"] = "--no-verify"

    sources = write_sources(rows, args.out_dir)
    frag, n_interior = write_fragment(rows, args.out_dir)
    sources.update(frag)

    if args.check:
        bad = []
        for path, text in sorted(sources.items()):
            cur = open(path).read() if os.path.exists(path) else None
            if cur != text:
                bad.append(path)
        print("check: %d/%d generated files up to date"
              % (len(sources) - len(bad), len(sources)))
        for path in bad:
            print("  STALE %s" % path)
        return 1 if bad else 0

    for path, text in sources.items():
        with open(path, "w") as fh:
            fh.write(text)

    absolute = None
    if args.elf:
        nm = ("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
              "arm-zephyr-eabi-nm")
        out = subprocess.run([nm, args.elf], capture_output=True,
                             text=True).stdout
        absolute = {ln.split()[2] for ln in out.splitlines()
                    if len(ln.split()) == 3 and ln.split()[1] == "A"
                    and ln.split()[2].startswith("rodata_")}

    emitted = [r for r in rows if r["status"] == "emitted"]
    deferred = [r for r in rows if r["status"] != "emitted"]
    retired = sorted({n for r in emitted for n in r["retires"]})
    coverage, unref = sector_coverage(rows)
    out_of_sector = out_of_sector_pins(pins, defined, expr)
    ledger = {
        "schema": 1,
        "core": CORE.name,
        "generator": "recon/application/gen_app_rodata_sources.py",
        "image": ("app_update.bin" if CORE.name == "app"
                  else "netcore_image.bin"),
        "address_space": ("app link base 0x0000c200 (tools/extract.py)"
                          if CORE.name == "app" else
                          "CPUNET RUNTIME base 0x01008800 "
                          "(net_extract.read_runtime); pins in "
                          "g1_net_globals.ld are runtime addresses, function "
                          "catalogue entries are analysis addresses"),
        "sector": {"lo": "0x%08x" % CORE.rodata_lo,
                   "hi": "0x%08x" % CORE.rodata_hi,
                   "bytes": CORE.rodata_hi - CORE.rodata_lo},
        "wired_into_build": False,
        "totals": {
            "regions": len(rows),
            "emitted": len(emitted),
            "deferred": len(deferred),
            "bytes_emitted": sum(r["bytes"] for r in emitted),
            "bytes_deferred": sum(r["bytes"] for r in deferred),
            "pins_retired": len(retired),
            "interior_repins": n_interior,
        },
        "sector_coverage": coverage,
        "out_of_sector_pins": out_of_sector,
        "unreferenced_regions": unref,
        "regions": sorted(rows, key=lambda r: r["va"]),
    }
    if absolute is not None:
        ledger["totals"]["absolute_pins_in_link"] = len(absolute)
        ledger["totals"]["absolute_pins_retired"] = len(
            absolute & set(retired))
    with open(args.ledger, "w") as fh:
        json.dump(ledger, fh, indent=1, sort_keys=False)
        fh.write("\n")

    print("regions %d | emitted %d (%d B) | deferred %d (%d B) | pins retired %d"
          " | interior re-pins %d"
          % (len(rows), len(emitted), ledger["totals"]["bytes_emitted"],
             len(deferred), ledger["totals"]["bytes_deferred"], len(retired),
             n_interior))
    if absolute is not None:
        print("absolute rodata pins in %s: %d | this batch retires %d"
              % (args.elf, len(absolute), len(absolute & set(retired))))
    if verification:
        from collections import Counter
        print("verification:", dict(Counter(v[0] for v in
                                            verification.values())))
    return 0


if __name__ == "__main__":
    sys.exit(main())
