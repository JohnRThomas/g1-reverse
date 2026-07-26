"""
Measure how closely a single reference BUILD reproduces the firmware's known
functions. For the 203 functions named in both the firmware (IDA .idc) and the
build, compute best opcode-sequence match ratio using ONLY that build, and
report the distribution. The build whose distribution is most concentrated at
~1.0 was compiled with the setting closest to the firmware's.

Usage: python opt_sweep.py <build_dir> [label]
       build_dir contains zephyr/zephyr.elf and **/*.obj
"""

# Resolvable pipeline scratchpad (tools/g1_paths.py).  This used to be one
# literal /private/tmp path belonging to a finished agent session; see that
# module for the resolution order and the fail-closed catalog fallback.
import os as _g1_os, sys as _g1_sys
_G1_TOOLS = _g1_os.path.dirname(_g1_os.path.abspath(__file__))
if _g1_os.path.basename(_G1_TOOLS) != "tools":
    _G1_TOOLS = _g1_os.path.dirname(_G1_TOOLS)
if _G1_TOOLS not in _g1_sys.path:
    _g1_sys.path.insert(0, _G1_TOOLS)
import g1_paths as _g1_paths
import sys, re, glob, statistics
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import extract, lib_sigmatch2 as L
from elftools.elf.elffile import ELFFile

def build_index(build_dir):
    from collections import defaultdict
    by_len = defaultdict(list); seen = set()
    srcs = glob.glob(build_dir + "/**/*.obj", recursive=True)
    srcs += glob.glob(build_dir + "/zephyr/zephyr.elf")
    for full in srcs:
        try:
            elf = ELFFile(open(full, "rb"))
        except Exception:
            continue
        st = elf.get_section_by_name(".symtab")
        if st is None:
            continue
        nsec = elf.num_sections()
        for s in st.iter_symbols():
            if s["st_info"]["type"] != "STT_FUNC" or not s.name or s["st_size"] < 16:
                continue
            shndx = s["st_shndx"]
            if not isinstance(shndx, int) or shndx >= nsec:
                continue
            sec = elf.get_section(shndx)
            if sec is None or not sec.data():
                continue
            off = (s["st_value"] & ~1) - sec["sh_addr"]; sz = s["st_size"]
            if off < 0 or off + sz > len(sec.data()):
                continue
            seq = L.ops(sec.data()[off:off+sz], s["st_value"] & ~1)
            if len(seq) < 6:
                continue
            k = (s.name, len(seq))
            if k in seen:
                continue
            seen.add(k); by_len[len(seq)].append((s.name, seq))
    return by_len

def main():
    build_dir = sys.argv[1]
    label = sys.argv[2] if len(sys.argv) > 2 else build_dir
    idc = open("/Users/freedomcoder/Projects/G1disasm2/g1_rev_1.idc", errors="ignore").read()
    fwnames = {m.group(2): int(m.group(1), 16)
               for m in re.finditer(r'set_name\((0x[0-9A-Fa-f]+),\s*"([^"]+)"\)', idc)}
    import json
    SCR = _g1_paths.scratchpad()
    fw = {f["entry"]: f for f in json.load(open(SCR + "/app_funcs.json"))["functions"]}
    by_len = build_index(build_dir)
    ratios = []
    for nm, e in fwnames.items():
        f = fw.get(e) or fw.get(e & ~1)
        if not f or f["size"] < 16:
            continue
        try:
            seq = L.ops(extract.func_bytes_padded(f["entry"], f["size"], 0), f["entry"])
        except Exception:
            continue
        if len(seq) < 6:
            continue
        # best match to the SAME-named function in this build (self-match quality)
        best = 0.0
        for dl in range(-2, 3):
            for rn, rseq in by_len.get(len(seq)+dl, ()):
                if rn == nm:
                    import difflib
                    r = difflib.SequenceMatcher(None, seq, rseq).ratio()
                    if r > best:
                        best = r
        if best > 0:
            ratios.append(best)
    ratios.sort()
    if not ratios:
        print("%-8s: no common functions" % label); return
    n = len(ratios)
    print("%-8s n=%3d  median=%.3f  >=0.99: %3d (%2d%%)  >=0.90: %3d (%2d%%)  <0.90: %d"
          % (label, n, statistics.median(ratios),
             sum(r >= 0.99 for r in ratios), 100*sum(r >= 0.99 for r in ratios)//n,
             sum(r >= 0.90 for r in ratios), 100*sum(r >= 0.90 for r in ratios)//n,
             sum(r < 0.90 for r in ratios)))

if __name__ == "__main__":
    main()
