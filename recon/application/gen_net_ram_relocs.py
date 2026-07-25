#!/usr/bin/env python3
"""Structural CPUNET absolute-RAM-address relocation pass (P4 iteration 26).

WHY THIS EXISTS
---------------
The recovered CPUNET corpus addresses its globals by their ORIGINAL absolute
addresses, through two independent channels:

  * linker pins  -- `PROVIDE(name = 0x21xxxxxx)` in recon/symbols/g1_net_globals.ld
    (gated by recon/emulator/scripts/check_ram_pin_collisions.py --core net);
  * raw literals -- `0x21xxxxxx` written straight into a reconstruction source
    (gated by recon/emulator/scripts/check_net_raw_literals.py).

In the cohesive relocated link the linker places its own objects wherever it
likes, so such an address routinely lands INSIDE a live linker-allocated
object.  Writing through it then silently corrupts that object.  This class has
produced a defect in FIVE consecutive iterations (18, 20, 21, 24, 25), each
time found one at a time by chasing a symptom, and 54 of the 69 colliding
source literals of iteration 25 land inside `sdc_mempool` -- the SoftDevice
Controller's own heap.

The app core closed the identical class structurally in iteration 11 with a
single 0x27000-byte arena at the original base.  The CPUNET **cannot** copy
that (iteration 18 §18.8(2)): the pinned span is 0x8a00 and the core has 64 KiB
of RAM with ~60 KiB already used.  So this pass does the per-address
equivalent: every raw in-region address is CLASSIFIED and then bound to real
storage, to a real SDK owner, or left literal with a reason.

WHAT IT EMITS
-------------
  * recon/application/net/src/g1_net_ram_relocs.c -- one `used, retain` block
    per CLUSTER of original addresses.  Clustering (gap <= --gap bytes) keeps
    every original RELATIVE distance inside a cluster exact, which is what
    interior views (`base + field`) and short sweeps need, at a fraction of the
    arena's cost.  Each block starts at a multiple of 8 at or below its first
    address, so every original offset keeps its alignment up to 8 bytes.
  * recon/symbols/g1_net_ram_reloc.h -- `G1N_<addr>` macros.  Under
    G1_COHESIVE_BUILD they expand to `block + off`; otherwise to the original
    literal, so the parity harness still sees the shipped address and no proven
    body changes meaning.
  * the rewritten `PROVIDE(...)` lines of recon/symbols/g1_net_globals.ld.
  * the rewritten source literals (`--rewrite`).  Sources that already include
    g1_net_symbols.h pick the macros up from there; the handful of canonical
    recon/net/src bodies that include nothing get a SELF-CONTAINED guard block
    injected, so `net_recon_kit.prove` keeps compiling them unchanged.

SHIPPED `.data` INITIALISERS
----------------------------
The shipped netcore `.data` load image is at runtime LMA 0x0103ed24 and is
0xc3c bytes long, i.e. it covers RAM 0x21000000..0x21000c3c; everything above
that was `.bss` in the shipped firmware and zeroed storage reproduces it
exactly.  For every block inside the `.data` window this generator restores the
shipped bytes, with the same policy recon/application/gen_app_data_image.py
established: a word that looks like a POINTER is meaningless in our link, so a
block containing one is restored only when every pointer word resolves --
either to an address inside the SAME relocation map (rewritten to the relocated
address) or to a catalogued flash symbol -- and is otherwise EXCLUDED ATOMICALLY
and left zero, because a half-initialised object is worse than an all-zero one.

Usage:
  PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_net_ram_relocs.py \
      --pins  <check_ram_pin_collisions --core net --json>  \
      --lits  <check_net_raw_literals --json>               \
      [--rewrite] [--report OUT.json]
"""

import argparse
import json
import os
import re
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(REPO, "tools"))

RAM_LO = 0x21000000
RAM_HI = 0x21010000

# Shipped netcore .data: runtime LMA 0x0103ed24, length 0xc3c, VMA 0x21000000
# (recon/application/net/src/g1_product_endpoints.c documents the same read).
DATA_VMA = 0x21000000
DATA_LMA_RUNTIME = 0x0103ED24
DATA_LEN = 0x0C3C

OUT_C = os.path.join(REPO, "recon", "application", "net", "src",
                     "g1_net_ram_relocs.c")
OUT_H = os.path.join(REPO, "recon", "symbols", "g1_net_ram_reloc.h")
LEDGER = os.path.join(REPO, "recon", "application", "net_ram_reloc_ledger.json")
GLOBALS_LD = os.path.join(REPO, "recon", "symbols", "g1_net_globals.ld")

# ---------------------------------------------------------------------------
# Addresses that ALREADY have real, correctly-initialised storage in this build
# (emitted by earlier iterations in recon/application/net/src/*.c and bound by
# NAME, not by address).  They must never be pulled into a generic relocation
# block: doing so would give the recovered accessor private storage instead of
# the real object.  Each range is [lo, hi) with the owning symbol.
OWNED = [
    (0x21000584, 0x2100059C, "g1_ipc0_endpoint_config"),
    (0x2100059C, 0x210005B4, "g1_hci_endpoint_config"),
    (0x210005B4, 0x210005B8, "g_net_radio_op_state"),
    (0x210005B8, 0x210005C8, "g1_timeslot_request_normal"),
    (0x210005C8, 0x210005D8, "g1_timeslot_request_normal_role1"),
    (0x210005D8, 0x210005E8, "g1_timeslot_request_earliest"),
    (0x21000670, 0x21000680, "g1_esb_window_request"),
    (0x21000698, 0x210006A0, "g_net_log_msg_ctx (nrfx_timer_t)"),
    (0x210006A0, 0x210006A4, "g_net_dppi_group_pool"),
    (0x210006A4, 0x210006A8, "g_sdc_res_pool_free_bitmap"),
    (0x21000760, 0x2100076C, "g1_esb_pipe_addr_block"),
    (0x210008E0, 0x21000914, "g1_timeslot_api_msgq"),
    (0x21000914, 0x2100092C, "g1_ipc0_bound_sem"),
    (0x2100092C, 0x21000944, "g1_hci_bound_sem"),
    (0x2100095C, 0x21000978, "g1_hci_rx_queue"),
    (0x21000978, 0x21000994, "g1_hci_tx_queue"),
    (0x21001D08, 0x21001DA0, "g1_hci_rpmsg_rx_thread"),
    (0x21001DA0, 0x21001E38, "g1_hci_rpmsg_tx_thread"),
    (0x21001E38, 0x21001ED0, "g1_esb_worker_thread"),
    (0x210045F8, 0x21004600, "g1_ipc0_ept"),
    (0x21004600, 0x21004604, "g1_ipc0_ept_ready"),
    (0x21004608, 0x21004610, "g1_hci_ept"),
]

# Byte-exact recovered rodata tables that happen to hold a RAM pointer.  They
# are DATA of the shipped image and are gated byte-for-byte elsewhere, so they
# are deliberately left literal here and reported.
LEAVE_LITERAL_FILES = ("recon/net/data/",)

# recon/symbols/g1_net_symbols.h is a DECLARATION header: every 0x21xxxxxx in it
# is provenance in a comment or (once) part of an identifier's spelling.  It
# gets the macros by #include, never by rewriting.
NEVER_REWRITE = ("recon/symbols/g1_net_symbols.h",)


def owned_of(addr):
    for lo, hi, name in OWNED:
        if lo <= addr < hi:
            return name
    return None


# ---------------------------------------------------------------------------
def load_inputs(pins_json, lits_json):
    pins, lits = {}, {}
    p = json.load(open(pins_json))
    for r in p["raw_colliding"] + p["raw_free"]:
        pins.setdefault(r["value"], []).append(r["name"])
    l = json.load(open(lits_json))
    collide = {r["literal"] for r in l["colliding"]}
    for r in l["colliding"] + l["free"]:
        lits.setdefault(r["literal"], []).extend(r["sites"])
    return pins, lits, collide, {r["value"] for r in p["raw_colliding"]}


def cluster(addrs, gap, pad):
    out, cur = [], [addrs[0]]
    for a in addrs[1:]:
        if a - cur[-1] <= gap:
            cur.append(a)
        else:
            out.append(cur)
            cur = [a]
    out.append(cur)
    blocks = []
    for c in out:
        base = c[0] & ~7
        end = c[-1] + 1 + pad
        end = (end + 7) & ~7
        blocks.append({"base": base, "size": end - base, "addrs": c})
    return blocks


# ---------------------------------------------------------------------------
def shipped_data(lo, size):
    """Shipped .data bytes for [lo, lo+size) or None when out of the window."""
    import net_extract
    if lo < DATA_VMA or lo + size > DATA_VMA + DATA_LEN:
        return None
    off = lo - DATA_VMA
    return bytes(net_extract.read_runtime(DATA_LMA_RUNTIME + off, size))


def looks_like_pointer(word):
    return (0x21000000 <= word < 0x21010000) or (0x01008800 <= word < 0x01040000)


def elf_func_names(elf):
    """FUNC/OBJECT symbol names defined by the baseline cohesive link."""
    import subprocess
    sdk = os.environ.get(
        "G1_ZEPHYR_SDK",
        "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin")
    out = subprocess.run([os.path.join(sdk, "arm-zephyr-eabi-readelf"),
                          "-sW", elf], capture_output=True, text=True).stdout
    names = set()
    for line in out.splitlines():
        p = line.split()
        if len(p) >= 8 and p[0].endswith(":") and p[3] == "FUNC" and p[6] != "UND":
            names.add(p[7].split("@")[0])
    return names


def resolve_pointers(blocks, elf, catalog):
    """Relocation-aware pointer restore, per gen_app_data_image.py's policy.

    Two exact resolution classes, everything else leaves the block ATOMICALLY
    excluded (zero), because a half-initialised object is worse than an
    all-zero one:

      * an SRAM pointer that targets an address INSIDE one of the emitted
        relocation blocks -> `block + off` (the self-referential sys_dlist_t /
        k_fifo / k_sem heads the shipped kernel objects carry);
      * a FLASH pointer whose analysis address (runtime - 0x800, Thumb bit
        stripped) is a catalogued net function that THIS link defines -> the
        symbol, with the Thumb bit re-set, so the LINKER supplies the relocated
        address and no raw absolute survives.
    """
    extents = [(b["base"], b["base"] + b["size"], b["name"]) for b in blocks]
    defined = elf_func_names(elf) if elf else set()
    by_addr = catalog.get("by_address", {}) if catalog else {}

    for b in blocks:
        raw = b.pop("_raw", None)
        if raw is None or not any(raw):
            continue
        words = [int.from_bytes(raw[i:i + 4], "little")
                 for i in range(0, len(raw), 4)]
        relocs, unresolved = {}, []
        for i, w in enumerate(words):
            if not looks_like_pointer(w):
                continue
            if 0x21000000 <= w < 0x21010000:
                hit = next((e for e in extents if e[0] <= w < e[1]), None)
                if hit:
                    # The byte offset must survive even when the OWNING block is
                    # emitted as `unsigned long[]` (which it is whenever it carries
                    # a relocation), so index through `unsigned char *`.
                    relocs[i] = ("(unsigned long)((unsigned char *)%s + 0x%x)"
                                 % (hit[2], w - hit[0]))
                else:
                    unresolved.append((i, w))
                continue
            ana = (w & ~1) - 0x800
            rec = by_addr.get("0x%08x" % ana)
            name = rec.get("name") if rec else None
            if name not in defined:
                # Ghidra-gap siblings reconstructed after the catalogue was
                # frozen keep their raw FUN_<analysis-address> identity.
                alt = "FUN_%08x" % ana
                name = alt if alt in defined else name
            if name and name in defined:
                relocs[i] = "((unsigned long)&%s | %du)" % (name, w & 1)
                b.setdefault("_externs", set()).add(name)
            else:
                unresolved.append((i, w))
        if unresolved:
            b["data"] = None
            b["data_note"] = ("EXCLUDED (atomic): pointer word(s) %s do not "
                              "resolve in this link" %
                              ", ".join("+0x%x=0x%08x" % (i * 4, w)
                                        for i, w in unresolved))
            b.pop("_externs", None)
            continue
        b["words"] = words
        b["relocs"] = relocs
        b["data"] = raw
        b["data_note"] = ("shipped .data initialiser restored"
                          + (" (%d pointer word(s) relocation-aware)" % len(relocs)
                             if relocs else ""))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pins", required=True)
    ap.add_argument("--lits", required=True)
    ap.add_argument("--gap", type=int, default=32)
    ap.add_argument("--pad", type=int, default=16)
    ap.add_argument("--rewrite", action="store_true")
    ap.add_argument("--elf", default=None,
                    help="baseline cohesive net ELF: used only to check that a\n                          restored flash pointer names a symbol THIS link defines")
    ap.add_argument("--report", default=None)
    args = ap.parse_args()

    pins, lits, collide_l, collide_p = load_inputs(args.pins, args.lits)

    classified = {"owned": [], "relocate": [], "left_literal": []}
    todo = []
    for a in sorted(set(pins) | set(lits)):
        own = owned_of(a)
        sites = lits.get(a, [])
        if own:
            classified["owned"].append({"addr": a, "owner": own,
                                        "pins": pins.get(a, []), "sites": sites})
            continue
        if sites and all(s.startswith(LEAVE_LITERAL_FILES) for s in sites) \
                and not pins.get(a):
            classified["left_literal"].append(
                {"addr": a, "sites": sites,
                 "reason": "byte-exact recovered rodata table"})
            continue
        todo.append(a)

    blocks = cluster(todo, args.gap, args.pad)

    # ---------------------------------------------------------- shipped .data
    addr2block = {}
    for b in blocks:
        b["name"] = "g1_net_ram_blk_%08x" % b["base"]
        raw = shipped_data(b["base"], b["size"])
        b["data"] = None
        b["words"] = None
        b["relocs"] = {}
        b["data_note"] = ""
        if raw is not None:
            if any(raw):
                b["_raw"] = raw
                b["data"] = raw
                b["data_note"] = "shipped .data initialiser restored"
            else:
                b["data_note"] = "shipped .data bytes are all zero"
        for a in b["addrs"]:
            addr2block[a] = (b["name"], a - b["base"])

    catalog = {}
    cat_path = os.path.join(REPO, "recon", "catalogs", "function_names_net.json")
    if os.path.exists(cat_path):
        catalog = json.load(open(cat_path))
    resolve_pointers(blocks, args.elf, catalog)

    total = sum(b["size"] for b in blocks)
    with_data = [b for b in blocks if b["data"]]
    reloc_words = sum(len(b["relocs"]) for b in blocks)

    # ------------------------------------------------------------------ emit
    hdr = ["/* GENERATED by recon/application/gen_net_ram_relocs.py "
           "(P4 iteration 26) -- do not edit.",
           " *",
           " * Structural close of the CPUNET absolute-RAM-address collision "
           "class.",
           " * Under G1_COHESIVE_BUILD each macro resolves to real linked "
           "storage;",
           " * otherwise it is the shipped literal, so parity bodies are "
           "unchanged.",
           " */",
           "#ifndef G1_NET_RAM_RELOC_H_",
           "#define G1_NET_RAM_RELOC_H_",
           "",
           "#ifdef G1_COHESIVE_BUILD"]
    for b in blocks:
        hdr.append("extern unsigned char %s[];" % b["name"])
    hdr.append("")
    for a in sorted(addr2block):
        n, off = addr2block[a]
        hdr.append("#define G1N_%08x ((unsigned long)(%s + 0x%x))" % (a, n, off))
    hdr.append("#else")
    for a in sorted(addr2block):
        hdr.append("#define G1N_%08x 0x%08xul" % (a, a))
    hdr.append("#endif")
    hdr.append("")
    hdr.append("#endif /* G1_NET_RAM_RELOC_H_ */")
    open(OUT_H, "w").write("\n".join(hdr) + "\n")

    src = ['/* GENERATED by recon/application/gen_net_ram_relocs.py '
           '(P4 iteration 26) -- do not edit.',
           ' *',
           ' * One storage block per cluster of recovered CPUNET absolute RAM',
           ' * addresses.  `used, retain` is MANDATORY: iteration 10 measured a',
           ' * sibling block being silently discarded by --gc-sections, after',
           ' * which every PROVIDE(x = block + off) resolved against a base of 0',
           ' * (iteration 11 §11.1).',
           ' *',
           ' * Blocks inside the shipped .data window (0x21000000..0x21000c3c)',
           ' * carry their shipped initialiser; blocks above it were .bss in the',
           ' * shipped firmware, so zeroed storage reproduces them exactly.',
           ' */',
           '',
           '#define G1_NET_RAM_BLOCK __attribute__((used, retain, aligned(8)))',
           '']
    externs = sorted({n for b in blocks for n in b.get("_externs", ())})
    if externs:
        src.append("/* Targets of the relocation-aware pointer words restored below. */")
        for n in externs:
            src.append("extern void %s(void);" % n)
        src.append("")
    for b in blocks:
        note = b["data_note"]
        src.append("/* original 0x%08x..0x%08x, %d B%s%s */" % (
            b["base"], b["base"] + b["size"], b["size"],
            "  -- " if note else "", note))
        if b["data"] and b["relocs"]:
            items = []
            for i, w in enumerate(b["words"]):
                items.append(b["relocs"].get(i, "0x%08xul" % w))
            src.append("unsigned long %s[%d] G1_NET_RAM_BLOCK = {" %
                       (b["name"], len(b["words"])))
            for i in range(0, len(items), 2):
                src.append("    " + ", ".join(items[i:i + 2]) + ",")
            src.append("};")
        elif b["data"]:
            body = ", ".join("0x%02x" % c for c in b["data"])
            src.append("unsigned char %s[%d] G1_NET_RAM_BLOCK = { %s };" %
                       (b["name"], b["size"], body))
        else:
            src.append("unsigned char %s[%d] G1_NET_RAM_BLOCK;" %
                       (b["name"], b["size"]))
        src.append("")
    open(OUT_C, "w").write("\n".join(src) + "\n")

    ledger = {
        "gap": args.gap, "pad": args.pad,
        "blocks": [{"name": b["name"], "base": b["base"], "size": b["size"],
                    "addrs": b["addrs"], "data_restored": bool(b["data"]),
                    "data_note": b["data_note"]} for b in blocks],
        "map": {"0x%08x" % a: {"block": addr2block[a][0],
                               "offset": addr2block[a][1]}
                for a in sorted(addr2block)},
        "owned": [{"addr": "0x%08x" % r["addr"], "owner": r["owner"]}
                  for r in classified["owned"]],
        "left_literal": [{"addr": "0x%08x" % r["addr"], "reason": r["reason"],
                          "sites": r["sites"]}
                         for r in classified["left_literal"]],
        "pins": {"0x%08x" % a: n for a, n in pins.items()},
        "totals": {
            "addresses_in": len(pins) + len(set(lits) - set(pins)),
            "owned": len(classified["owned"]),
            "left_literal": len(classified["left_literal"]),
            "relocated": len(addr2block),
            "blocks": len(blocks),
            "block_bytes": total,
            "blocks_with_shipped_data": len(with_data),
            "shipped_data_bytes": sum(len(b["data"]) for b in with_data),
            "relocation_aware_pointer_words": reloc_words,
            "colliding_pins_in": len(collide_p),
            "colliding_literals_in": len(collide_l),
        },
    }
    json.dump(ledger, open(LEDGER, "w"), indent=1)

    for k, v in ledger["totals"].items():
        print("%-32s %s" % (k, v))

    if args.rewrite:
        rewrite_linker(addr2block, pins)
        n_files, n_sites = rewrite_sources(addr2block, lits)
        print("%-32s %s" % ("sources rewritten", n_files))
        print("%-32s %s" % ("literal sites rewritten", n_sites))

    if args.report:
        json.dump(ledger, open(args.report, "w"), indent=1)
    return 0


# ---------------------------------------------------------------------------
PROVIDE_RE = re.compile(
    r"^(\s*PROVIDE\s*\(\s*)([A-Za-z_][A-Za-z_0-9]*)(\s*=\s*)0x(21[0-9a-fA-F]{6})"
    r"(\s*\)\s*;.*)$")


def rewrite_linker(addr2block, pins):
    lines = open(GLOBALS_LD).read().splitlines()
    out, n = [], 0
    for line in lines:
        m = PROVIDE_RE.match(line)
        if m:
            a = int(m.group(4), 16)
            if a in addr2block:
                blk, off = addr2block[a]
                line = "%s%s%s%s + 0x%x%s" % (m.group(1), m.group(2),
                                              m.group(3), blk, off, m.group(5))
                n += 1
        out.append(line)
    header = ("/* P4 iteration 26 - STRUCTURAL PASS.  %d pins below are bound to a\n"
              "   recon/application/net/src/g1_net_ram_relocs.c storage block plus the\n"
              "   original offset instead of to a raw 0x21xxxxxx literal, so no recovered\n"
              "   CPUNET global can land inside a live linker-allocated object (54 of them\n"
              "   were inside sdc_mempool).  Generated by recon/application/\n"
              "   gen_net_ram_relocs.py; ledger recon/application/net_ram_reloc_ledger.json. */\n"
              % n)
    open(GLOBALS_LD, "w").write(header + "\n".join(out) + "\n")
    print("%-32s %s" % ("linker pins rebound", n))


# A LITERAL, never a hex run inside an identifier: recon/symbols/
# g1_net_symbols.h declares `g_net_0x21004604_flag`, whose NAME contains the
# digits.  Require a non-identifier character in front.
LIT_RE = re.compile(r"(?<![A-Za-z0-9_])0[xX](21[0-9a-fA-F]{6})(?![0-9a-fA-F])[uU]?[lL]{0,2}")
SYMBOLS_INCLUDE = '#include "g1_net_symbols.h"'


def strip_comments_mask(text):
    """Return a bool list: True where the character is real code."""
    mask = [True] * len(text)
    i, n = 0, len(text)
    state = None
    while i < n:
        c = text[i]
        if state is None:
            if c == "/" and i + 1 < n and text[i + 1] == "*":
                state = "block"
                mask[i] = mask[i + 1] = False
                i += 2
                continue
            if c == "/" and i + 1 < n and text[i + 1] == "/":
                state = "line"
                mask[i] = mask[i + 1] = False
                i += 2
                continue
            if c in "\"'":
                state = c
                i += 1
                continue
            i += 1
        elif state == "block":
            mask[i] = False
            if c == "*" and i + 1 < n and text[i + 1] == "/":
                mask[i + 1] = False
                state = None
                i += 2
                continue
            i += 1
        elif state == "line":
            mask[i] = False
            if c == "\n":
                state = None
            i += 1
        else:
            if c == "\\":
                i += 2
                continue
            if c == state:
                state = None
            i += 1
    return mask


def rewrite_sources(addr2block, lits):
    files = {}
    for a, sites in lits.items():
        if a not in addr2block:
            continue
        for s in sites:
            files.setdefault(s.split(":")[0], set()).add(a)
    n_files = n_sites = 0
    for rel, addrs in sorted(files.items()):
        path = os.path.join(REPO, rel)
        if not os.path.exists(path) or rel.startswith(LEAVE_LITERAL_FILES) \
                or rel in NEVER_REWRITE:
            continue
        text = open(path).read()
        mask = strip_comments_mask(text)
        out, last, hits = [], 0, 0
        for m in LIT_RE.finditer(text):
            if not all(mask[m.start():m.end()]):
                continue
            a = int(m.group(1), 16)
            if a not in addr2block:
                continue
            out.append(text[last:m.start()])
            out.append("G1N_%08x" % a)
            last = m.end()
            hits += 1
        if not hits:
            continue
        out.append(text[last:])
        new = "".join(out)
        used = sorted({int(m.group(1), 16) for m in LIT_RE.finditer(text)
                       if all(mask[m.start():m.end()])
                       and int(m.group(1), 16) in addr2block})
        if SYMBOLS_INCLUDE in new:
            pass                      # g1_net_symbols.h pulls the macros in
        else:
            guard = ["/* P4 iteration 26 - structural CPUNET RAM relocation.  Self-contained",
                     "   so tools/parity keeps compiling this canonical body unchanged: the",
                     "   #else arm is the shipped literal.  See recon/application/",
                     "   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */",
                     "#ifdef G1_COHESIVE_BUILD"]
            blks = sorted({addr2block[a][0] for a in used})
            for b in blks:
                guard.append("extern unsigned char %s[];" % b)
            for a in used:
                b, off = addr2block[a]
                guard.append("#define G1N_%08x ((unsigned long)(%s + 0x%x))"
                             % (a, b, off))
            guard.append("#else")
            for a in used:
                guard.append("#define G1N_%08x 0x%08xul" % (a, a))
            guard.append("#endif")
            new = "\n".join(guard) + "\n" + new
        open(path, "w").write(new)
        n_files += 1
        n_sites += hits
    return n_files, n_sites


if __name__ == "__main__":
    sys.exit(main())
