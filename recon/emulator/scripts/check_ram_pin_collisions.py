#!/usr/bin/env python3
"""Residual absolute-RAM-pin collision checker (P4 iteration 11).

The reconstruction pins recovered globals to their ORIGINAL absolute addresses
(`PROVIDE(name = 0x2000xxxx)` in recon/symbols/g1_app_globals.ld).  In the
relocated cohesive build the linker places its own objects wherever it likes,
so such a pin can land INSIDE a live linked object; writing through the pin
then silently corrupts that object (iteration 10: `msg_queue_init` memset
8720 B across `z_idle_stacks` / `z_main_stack`).

Iteration 11 closed the class structurally by rebinding every pin inside the
linked RAM region to `g1_ram_arena + off` (or to a real SDK owner such as
`bt_dev + off`).  This script is the mechanical gate for that property.  It
combines two sources of truth:

  * the LINKER SCRIPTS, which say whether a pin is still a RAW hex literal or
    is bound relative to a real symbol; and
  * the LINKED ELF, which gives the final value of every pin and the extent of
    every linker-allocated object.

It then reports

  * RAW literal pins that land inside a live object   -- the defect class;
  * RAW literal pins outside the linked RAM region    -- structurally safe;
  * BOUND pins that do NOT land inside the extent of the object they were
    bound to -- i.e. a rebind whose offset escapes its owner (also a defect).

Usage:
    check_ram_pin_collisions.py <zephyr.elf> [--ld FILE]... [--json OUT]

With no --ld the app pin scripts of this repository are used.
Exit status: 0 when there is no raw in-region collision and no escaped bind.
"""
import argparse
import bisect
import json
import os
import re
import subprocess
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
DEFAULT_LDS = [
    os.path.join(REPO, "recon", "symbols", "g1_app_globals.ld"),
    os.path.join(REPO, "recon", "symbols", "g1_app_sdk_state.ld"),
    os.path.join(REPO, "recon", "symbols", "g1_app_aliases.ld"),
]

SDK_ROOT = os.environ.get(
    "G1_ZEPHYR_SDK", "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin"
)
READELF = os.path.join(SDK_ROOT, "arm-zephyr-eabi-readelf")

RAM_LO = 0x20000000
RAM_HI = 0x20080000

STACK_HINTS = ("stack", "_stacks", "stack_area")

# PROVIDE(name = expr);  or  name = expr;
ASSIGN = re.compile(
    r"^\s*(?:PROVIDE\s*\(\s*)?([A-Za-z_][A-Za-z_0-9]*)\s*=\s*([^;)]+?)\s*\)?\s*;"
)
LITERAL = re.compile(r"^0x[0-9a-fA-F]+$")
SYMOFF = re.compile(r"^([A-Za-z_][A-Za-z_0-9]*)(?:\s*\+\s*(0x[0-9a-fA-F]+|\d+))?$")


def read_pin_kinds(ld_files):
    """name -> ('literal', value) | ('bound', base_symbol, offset).

    A STRONG script assignment (`name = expr;`) always wins over a PROVIDE,
    whatever the file order, so strong records overwrite provided ones.
    Between two records of the same strength the first one wins, as in ld.
    """
    kinds, strong = {}, set()
    for path in ld_files:
        if not os.path.exists(path):
            continue
        for line in open(path):
            line = line.split("/*")[0]
            m = ASSIGN.match(line)
            if not m:
                continue
            name, expr = m.group(1), m.group(2).strip()
            is_strong = "PROVIDE" not in line.split("=")[0]
            if name in kinds and not (is_strong and name not in strong):
                continue
            rec = None
            if LITERAL.match(expr):
                rec = ("literal", int(expr, 16))
            else:
                s = SYMOFF.match(expr)
                if s:
                    off = s.group(2)
                    rec = ("bound", s.group(1), int(off, 0) if off else 0)
            if rec is None:
                continue
            kinds[name] = rec
            if is_strong:
                strong.add(name)
    return kinds


def read_symbols(elf):
    out = subprocess.run([READELF, "-sW", elf], capture_output=True, text=True).stdout
    abs_syms = []      # (value, name)
    objects = []       # (value, size, name, type)
    seen = set()
    for line in out.splitlines():
        parts = line.split()
        # Num: Value Size Type Bind Vis Ndx Name
        if len(parts) < 8 or not parts[0].endswith(":"):
            continue
        try:
            value = int(parts[1], 16)
        except ValueError:
            continue
        size_s = parts[2]
        try:
            size = int(size_s) if size_s.isdigit() else int(size_s, 16)
        except ValueError:
            size = 0
        styp, ndx, name = parts[3], parts[6], parts[7]
        if not name:
            continue
        key = (value, size, styp, ndx, name)
        if key in seen:
            continue
        seen.add(key)
        if ndx == "ABS":
            if RAM_LO <= value < RAM_HI:
                abs_syms.append((value, name))
            continue
        if styp not in ("OBJECT", "NOTYPE", "FUNC"):
            continue
        if not (RAM_LO <= value < RAM_HI) or size <= 0:
            continue
        objects.append((value, size, name, styp))
    abs_syms.sort()
    objects.sort()
    return abs_syms, objects


def ram_region(map_path):
    """(start, end) of the linked RAM region, read from the map file."""
    if not os.path.exists(map_path):
        return None
    for line in open(map_path):
        p = line.split()
        if len(p) >= 3 and p[0] == "RAM":
            try:
                start = int(p[1], 16)
                size = int(p[2], 16)
                return start, start + size
            except ValueError:
                pass
    return None


def build_owner_index(objects):
    starts = [o[0] for o in objects]
    max_end, m = [], 0
    for v, s, _n, _t in objects:
        m = max(m, v + s)
        max_end.append(m)
    return starts, max_end


def owners_of(addr, objects, starts, max_end):
    i = bisect.bisect_right(starts, addr) - 1
    res = []
    while i >= 0:
        if max_end[i] <= addr:
            break
        v, s, n, t = objects[i]
        if v <= addr < v + s:
            res.append({"name": n, "type": t, "start": v, "size": s,
                        "offset": addr - v})
        i -= 1
    return res


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("elf")
    ap.add_argument("--ld", action="append", default=None)
    ap.add_argument("--json", dest="json_out")
    ap.add_argument("--max-print", type=int, default=40)
    args = ap.parse_args()

    lds = args.ld if args.ld else DEFAULT_LDS
    kinds = read_pin_kinds(lds)
    abs_syms, objects = read_symbols(args.elf)
    starts, max_end = build_owner_index(objects)

    region = ram_region(os.path.join(os.path.dirname(args.elf), "zephyr.map"))
    obj_by_name = {}
    for v, s, n, t in objects:
        obj_by_name.setdefault(n, (v, s))

    raw_colliding, raw_safe, raw_free = [], [], []
    bound_ok, bound_escaped, unknown = [], [], []

    for value, name in abs_syms:
        kind = kinds.get(name)
        ow = owners_of(value, objects, starts, max_end)
        row = {
            "name": name, "value": value,
            "owners": ow,
            "in_stack": any(any(h in o["name"].lower() for h in STACK_HINTS)
                            for o in ow),
        }
        if kind is None:
            unknown.append(row)
        elif kind[0] == "literal":
            row["kind"] = "literal"
            in_region = region is None or (region[0] <= value < region[1])
            row["in_ram_region"] = in_region
            if not in_region:
                raw_safe.append(row)
            elif ow:
                raw_colliding.append(row)
            else:
                raw_free.append(row)
        else:
            row["kind"] = "bound"
            row["base"] = kind[1]
            row["bind_offset"] = kind[2]
            base = obj_by_name.get(kind[1])
            if base is None:
                # base is itself a script symbol (chained bind) -- accept
                row["base_extent"] = None
                bound_ok.append(row)
            else:
                row["base_extent"] = [base[0], base[0] + base[1]]
                if base[0] <= value < base[0] + base[1]:
                    bound_ok.append(row)
                else:
                    bound_escaped.append(row)

    summary = {
        "elf": os.path.abspath(args.elf),
        "ram_region": [hex(region[0]), hex(region[1])] if region else None,
        "abs_ram_symbols": len(abs_syms),
        "raw_literal_pins_inside_a_live_object": len(raw_colliding),
        "raw_literal_pins_inside_ram_region_but_free": len(raw_free),
        "raw_literal_pins_outside_ram_region": len(raw_safe),
        "bound_pins_ok": len(bound_ok),
        "bound_pins_escaping_their_owner": len(bound_escaped),
        "abs_symbols_not_in_linker_scripts": len(unknown),
        "unknown_inside_a_live_object": sum(1 for r in unknown if r["owners"]),
    }

    for k, v in summary.items():
        print("%-45s %s" % (k, v))

    def dump(title, rows):
        if not rows:
            return
        print()
        print("=== %s (%d) ===" % (title, len(rows)))
        for r in rows[: args.max_print]:
            o = r["owners"][0] if r["owners"] else None
            print("0x%08x %-42s %s" % (
                r["value"], r["name"],
                ("-> %s+0x%x (%d B)" % (o["name"], o["offset"], o["size"]))
                if o else "(no owner)"))
        if len(rows) > args.max_print:
            print("... %d more" % (len(rows) - args.max_print))

    dump("RAW literal pins INSIDE a live object -- DEFECT", raw_colliding)
    dump("BOUND pins escaping their owner -- DEFECT", bound_escaped)
    dump("ABS symbols not attributable to a linker script, inside an object",
         [r for r in unknown if r["owners"]])

    if args.json_out:
        json.dump({
            "summary": summary,
            "raw_colliding": raw_colliding,
            "raw_free": raw_free,
            "raw_safe": raw_safe,
            "bound_escaped": bound_escaped,
            "unknown": unknown,
        }, open(args.json_out, "w"), indent=1)

    bad = len(raw_colliding) + len(bound_escaped)
    return 0 if bad == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
