#!/usr/bin/env python3
"""Source-level raw CPUNET RAM-literal collision checker (P4 iteration 20).

`check_ram_pin_collisions.py` gates the *linker* pins (`PROVIDE(name = 0x…)`).
It is structurally blind to the second half of the same defect class: a raw
`0x21xxxxxx` address written **directly into a C source** of the net core.  The
reconstruction pins recovered globals to their ORIGINAL absolute addresses, and
where the pin lives in the body rather than in a linker script nothing in the
build can see that, in the relocated cohesive link, the address now falls
INSIDE a live linker-allocated object (iteration 19: `0x2100095c` inside the
stock `hci_cmd_pool`, `0x21004608` inside `sdc_mempool`, `0x2100076c` 0x64
bytes inside `_sw_isr_table`).

Method (exact with respect to `#if` branches, so the parity-only `#else` arms
of `G1_COHESIVE_BUILD` are never counted):

  * read the build's `compile_commands.json` and re-run each translation unit
    through the SAME compiler and flags with `-E`;
  * attribute every preprocessed line to its originating file with the `# line
    "file"` markers and keep only lines that came from a repository
    reconstruction source (never from an NCS/Zephyr header);
  * collect every `0x21xxxxxx` hex literal on those lines;
  * score each distinct literal against the extent of every live object of the
    linked ELF.

Usage:
    check_net_raw_literals.py <zephyr.elf> [--build DIR] [--json OUT]
                              [--repo DIR] [--jobs N] [--max-print N]

`--build` defaults to the ELF's build directory (two levels up from
`zephyr/zephyr.elf`).  Exit status is 0 when no source literal lands inside a
live object.
"""
import argparse
import bisect
import json
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
SDK_ROOT = os.environ.get(
    "G1_ZEPHYR_SDK", "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin"
)
READELF = os.path.join(SDK_ROOT, "arm-zephyr-eabi-readelf")

# CPUNET SRAM window (nRF5340 network core: 64 KiB at 0x21000000).
RAM_LO = 0x21000000
RAM_HI = 0x21010000

# 0x21xxxxxx, with any integer suffix (0x21000914u / …UL) but NOT a longer
# hex constant (0x210009140 is a different number and must not match).
LITERAL_RE = re.compile(r"0[xX]21[0-9a-fA-F]{6}(?![0-9a-fA-F])")
LINEMARK_RE = re.compile(r'^#\s+(\d+)\s+"([^"]*)"')
STACK_HINTS = ("stack", "_stacks", "stack_area")


# ---------------------------------------------------------------- ELF objects
def read_objects(elf):
    out = subprocess.run([READELF, "-sW", elf], capture_output=True, text=True).stdout
    objects, seen = [], set()
    for line in out.splitlines():
        parts = line.split()
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
        if not name or ndx == "ABS" or styp not in ("OBJECT", "NOTYPE", "FUNC"):
            continue
        if not (RAM_LO <= value < RAM_HI) or size <= 0:
            continue
        key = (value, size, name)
        if key in seen:
            continue
        seen.add(key)
        objects.append((value, size, name, styp))
    objects.sort()
    return objects


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


# ------------------------------------------------------------- preprocessing
def is_recon_source(path, repo):
    if not path:
        return False
    ap = os.path.abspath(path)
    return ap.startswith(os.path.join(repo, "recon") + os.sep)


def preprocess_literals(entry, repo):
    """-> (source, {literal: [line numbers]}) for one compile_commands entry."""
    src = entry.get("file")
    if not is_recon_source(src, repo):
        return None
    cmd = entry.get("command")
    args = entry.get("arguments")
    if args is None:
        args = cmd.split() if cmd else None
    if not args:
        return None
    args = list(args)
    # drop output/compile-only flags, add -E
    out = []
    skip = False
    for i, a in enumerate(args):
        if skip:
            skip = False
            continue
        if a == "-o":
            skip = True
            continue
        if a in ("-c", "-MD", "-MMD"):
            continue
        if a in ("-MF", "-MT", "-MQ"):
            skip = True
            continue
        if a.startswith("-o") and len(a) > 2:
            continue
        out.append(a)
    out.append("-E")
    proc = subprocess.run(out, cwd=entry.get("directory", repo),
                          capture_output=True, text=True)
    if proc.returncode != 0:
        return (src, None, proc.stderr.strip().splitlines()[-1:] or ["preprocess failed"])

    hits = {}
    cur_file, cur_line = src, 0
    for raw in proc.stdout.splitlines():
        if raw.startswith("#"):
            m = LINEMARK_RE.match(raw)
            if m:
                cur_line = int(m.group(1))
                cur_file = m.group(2)
            continue
        cur_line += 1
        if not is_recon_source(cur_file, repo):
            continue
        for lit in LITERAL_RE.findall(raw):
            hits.setdefault(int(lit, 16), []).append(
                "%s:%d" % (os.path.relpath(cur_file, repo), cur_line - 1))
    return (src, hits, None)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("elf")
    ap.add_argument("--build", default=None)
    ap.add_argument("--repo", default=REPO)
    ap.add_argument("--json", dest="json_out")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--max-print", type=int, default=60)
    args = ap.parse_args()

    repo = os.path.abspath(args.repo)
    build = args.build or os.path.dirname(os.path.dirname(os.path.abspath(args.elf)))
    cc_path = os.path.join(build, "compile_commands.json")
    if not os.path.exists(cc_path):
        print("missing %s" % cc_path, file=sys.stderr)
        return 2
    entries = json.load(open(cc_path))

    objects = read_objects(args.elf)
    starts, max_end = build_owner_index(objects)

    todo = [e for e in entries if is_recon_source(e.get("file"), repo)]
    results = []
    with ThreadPoolExecutor(max_workers=args.jobs) as ex:
        for r in ex.map(lambda e: preprocess_literals(e, repo), todo):
            if r:
                results.append(r)

    failed = [(s, err) for (s, h, err) in results if h is None]
    lit_sites = {}
    for src, hits, err in results:
        if hits is None:
            continue
        for lit, sites in hits.items():
            lit_sites.setdefault(lit, []).extend(sites)

    colliding, free, outside = [], [], []
    for lit in sorted(lit_sites):
        ow = owners_of(lit, objects, starts, max_end)
        row = {
            "literal": lit,
            "sites": sorted(set(lit_sites[lit])),
            "owners": ow,
            "in_stack": any(any(h in o["name"].lower() for h in STACK_HINTS)
                            for o in ow),
        }
        if not (RAM_LO <= lit < RAM_HI):
            outside.append(row)
        elif ow:
            colliding.append(row)
        else:
            free.append(row)

    by_owner = {}
    for r in colliding:
        by_owner[r["owners"][0]["name"]] = by_owner.get(r["owners"][0]["name"], 0) + 1

    summary = {
        "elf": os.path.abspath(args.elf),
        "build": build,
        "ram_region": [hex(RAM_LO), hex(RAM_HI)],
        "recon_translation_units": len(todo),
        "translation_units_failed_to_preprocess": len(failed),
        "distinct_raw_literals": len(lit_sites),
        "raw_literals_inside_a_live_object": len(colliding),
        "raw_literals_in_ram_region_but_free": len(free),
        "raw_literals_outside_ram_region": len(outside),
        "literals_inside_a_stack_object": sum(1 for r in colliding if r["in_stack"]),
    }
    for k, v in summary.items():
        print("%-45s %s" % (k, v))

    if by_owner:
        print()
        print("=== owners of colliding literals ===")
        for n, c in sorted(by_owner.items(), key=lambda kv: -kv[1]):
            print("%-45s %d" % (n, c))

    if colliding:
        print()
        print("=== RAW SOURCE literals INSIDE a live object -- DEFECT (%d) ==="
              % len(colliding))
        for r in colliding[: args.max_print]:
            o = r["owners"][0]
            print("0x%08x -> %-28s +0x%-6x  %s" % (
                r["literal"], o["name"], o["offset"],
                ", ".join(r["sites"][:3]) + (" …" if len(r["sites"]) > 3 else "")))
        if len(colliding) > args.max_print:
            print("... %d more" % (len(colliding) - args.max_print))

    for src, err in failed:
        print("PREPROCESS FAILED %s: %s" % (src, err), file=sys.stderr)

    if args.json_out:
        json.dump({"summary": summary, "colliding": colliding,
                   "free": free, "outside": outside,
                   "failed": [{"file": s, "error": e} for s, e in failed]},
                  open(args.json_out, "w"), indent=1)

    return 0 if not colliding else 1


if __name__ == "__main__":
    sys.exit(main())
