"""
Improved library sig-matcher (v2). Diagnosis showed same-version (NCS 2.5.1)
functions have IDENTICAL opcode-sequence length but set-based 3-gram Jaccard
scores them low. Fix: length-anchored ORDERED sequence similarity
(difflib ratio on the opcode stream), which reflects that these are the same
compiled code.

We self-validate/tune the threshold on the 360 functions named in BOTH the
firmware (IDA .idc) and the reference ELFs — ground truth — then apply to the
unnamed sub_ functions to name library code.
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
import sys, re, json, difflib
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import extract
from capstone import *
from elftools.elf.elffile import ELFFile

SCR = _g1_paths.scratchpad()
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
REF_ELFS = ["elfs/zephyr_size_optimizations.elf", "elfs/zephyr_speed_optimizations.elf",
            "elfs/zephyr_no_optimizations.elf", "elfs/zephyr_debug_optimizations.elf",
            # config-matched NCS 2.5.1 rebuild (BLE host, crypto, audio, nrfx...)
            "/Users/freedomcoder/ncs251/refapp/build/zephyr/zephyr.elf"]

def ops(code, addr):
    return tuple(i.mnemonic.split(".")[0] for i in md.disasm(code, addr))

import glob as _glob
# all compiled objects from the config-matched build (pre-GC: every library fn)
REF_OBJ_GLOB = "/Users/freedomcoder/ncs251/refapp/build/**/*.obj"

def build_ref():
    from collections import defaultdict
    by_len = defaultdict(list)   # opcode-length -> [(name, opseq)]
    seen = set()
    sources = [(p if p.startswith("/") else "/Users/freedomcoder/Projects/G1disasm2/" + p)
               for p in REF_ELFS]
    sources += _glob.glob(REF_OBJ_GLOB, recursive=True)
    for full in sources:
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
            sz = s["st_size"]
            shndx = s["st_shndx"]
            if not isinstance(shndx, int) or shndx >= nsec:
                continue  # SHN_UNDEF / SHN_ABS etc.
            sec = elf.get_section(shndx)
            if sec is None or not sec.data():
                continue
            # offset within the symbol's own section (handles both -ffunction-
            # sections .obj with sh_addr=0 and fully-linked ELFs)
            off = (s["st_value"] & ~1) - sec["sh_addr"]
            if off < 0 or off + sz > len(sec.data()):
                continue
            code = sec.data()[off:off+sz]
            seq = ops(code, s["st_value"] & ~1)
            if len(seq) < 6:
                continue
            key = (s.name, len(seq))
            if key in seen:
                continue
            seen.add(key)
            by_len[len(seq)].append((s.name, seq))
    return by_len

def best_match(seq, by_len, tol=2):
    best = (0.0, None)
    L = len(seq)
    for dl in range(-tol, tol+1):
        for nm, rseq in by_len.get(L+dl, ()):
            r = difflib.SequenceMatcher(None, seq, rseq).ratio()
            if r > best[0]:
                best = (r, nm)
    return best

def fw_opseq(entry, size):
    try:
        return ops(extract.func_bytes_padded(entry, size, 0), entry)
    except Exception:
        return None

def main():
    fw = {f["entry"]: f for f in json.load(open(SCR+"/app_funcs.json"))["functions"]}
    cls = {c["entry"]: c for c in json.load(open(SCR+"/classified.json"))["functions"]}
    idc = open("/Users/freedomcoder/Projects/G1disasm2/g1_rev_1.idc", errors="ignore").read()
    fwnames = {int(m.group(1),16): m.group(2)
               for m in re.finditer(r'set_name\((0x[0-9A-Fa-f]+),\s*"([^"]+)"\)', idc)}
    by_len = build_ref()
    print("reference opcode-seqs indexed:", sum(len(v) for v in by_len.values()))

    # 1) validate on ground truth (named in both) to pick a threshold
    import statistics
    gt = []
    for e, nm in fwnames.items():
        f = fw.get(e) or fw.get(e & ~1)
        if not f or f["size"] < 16:
            continue
        seq = fw_opseq(f["entry"], f["size"])
        if not seq or len(seq) < 6:
            continue
        r, match = best_match(seq, by_len)
        if match == nm:          # correctly recovered the known name
            gt.append(r)
    gt.sort()
    if gt:
        print("ground-truth self-match ratios: n=%d min=%.2f p10=%.2f median=%.2f"
              % (len(gt), gt[0], gt[max(0,len(gt)//10)], statistics.median(gt)))

    # 2) apply to UNNAMED application sub_ functions
    THRESH = 0.90
    hits = {}
    for e, c in cls.items():
        if c["class"] != "APPLICATION" or c["is_thunk"] or c["ida_name"]:
            continue
        f = fw[e]
        if f["size"] < 16:
            continue
        seq = fw_opseq(e, f["size"])
        if not seq or len(seq) < 6:
            continue
        r, match = best_match(seq, by_len)
        if match and r >= THRESH:
            hits["0x%x" % e] = {"name": match, "ratio": round(r, 3)}
    json.dump(hits, open(SCR+"/lib_sig2_hits.json", "w"), indent=1)
    print("NEW library matches on unnamed sub_ (ratio>=%.2f): %d" % (THRESH, len(hits)))
    for a, d in list(hits.items())[:30]:
        print("  %s -> %-34s r=%.3f" % (a, d["name"], d["ratio"]))

if __name__ == "__main__":
    main()
