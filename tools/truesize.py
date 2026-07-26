"""
Compute the TRUE extent of a Thumb function.

Ghidra sometimes reports a size that ends before a shared tail block or a
switch case handler that the function branches into. The parity harness treats
any PC outside [va, va+size) as an external call, so those under-sized functions
fail spuriously. Here we follow the function's own control flow and extend the
end to cover every in-body basic block, using the known function-entry set to
tell an in-body tail block (not an entry) from a real tail-call (an entry).
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
import sys, json
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import extract
from capstone import *

SCR = _g1_paths.scratchpad()
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
md.detail = True

_entries = None
def entry_set():
    global _entries
    if _entries is None:
        fns = json.load(open(SCR + "/app_funcs.json"))["functions"]
        _entries = set(f["entry"] & ~1 for f in fns)
    return _entries

TERM = {"bx", "pop"}                       # bx lr / pop {..,pc} may end a path
UNCOND = {"b", "b.w"}
COND = {"bne", "beq", "bcs", "bcc", "bmi", "bpl", "bvs", "bvc", "bhi", "bls",
        "bge", "blt", "bgt", "ble", "cbz", "cbnz", "bne.w", "beq.w", "bhi.w",
        "bls.w", "bge.w", "blt.w", "bgt.w", "ble.w", "bcc.w", "bcs.w"}

def true_extent(va, ghidra_size, window=0x400, max_scan=0x1000):
    entries = entry_set()
    va &= ~1
    blob = extract.read(va, max_scan)
    visited = set()
    work = [0]                              # offsets from va to explore
    max_end = ghidra_size
    def tgt_off(insn):
        try:
            t = int(insn.op_str.split("#")[-1], 0)
            return t - va
        except Exception:
            return None
    while work:
        off = work.pop()
        if off in visited or off < 0 or off >= max_scan:
            continue
        # linear-scan this block
        for insn in md.disasm(blob[off:], va + off):
            o = insn.address - va
            if o > 0 and (va + o) in entries:
                break        # reached the NEXT function's entry -> stop, no bleed
            visited.add(o)
            end = o + insn.size
            if end > max_end:
                max_end = end
            m = insn.mnemonic
            if m in ("bx",) or (m == "pop" and "pc" in insn.op_str):
                break                       # terminal return
            if m == "bl" or m == "blx":
                continue                    # call, fall through
            if m in UNCOND:
                t = tgt_off(insn)
                if t is not None and (va + t) not in entries and -window <= t < window + max_scan:
                    work.append(t)          # in-body tail block
                break                       # unconditional -> block ends
            if m in COND:
                t = tgt_off(insn)
                if t is not None and (va + t) not in entries and -window <= t < window + max_scan:
                    work.append(t)
                continue                    # cond -> also fall through
            if m in ("tbb", "tbh"):
                break                       # jump table: stop this path
        # end for
    return max_end

if __name__ == "__main__":
    # quantify boundary-underestimate over the deferred set
    import worklist
    cls = {c["entry"]: c for c in json.load(open(SCR + "/classified.json"))["functions"]}
    fw = {f["entry"]: f for f in json.load(open(SCR + "/app_funcs.json"))["functions"]}
    deferred = worklist.attempted_failed_set() | worklist.defer_list()
    bumped = []
    for e in sorted(deferred):
        f = fw.get(e) or fw.get(e & ~1)
        if not f:
            continue
        gs = f["size"]
        try:
            ts = true_extent(e, gs)
        except Exception:
            continue
        if ts > gs:
            bumped.append((e, gs, ts, cls.get(e, {}).get("name", f["name"])))
    print("deferred functions:", len(deferred))
    print("with corrected (larger) true size:", len(bumped))
    for e, gs, ts, nm in bumped[:30]:
        print("  0x%-7x %-34s ghidra=%-4d true=%-4d (+%d)" % (e, nm[:34], gs, ts, ts-gs))
    json.dump({("0x%x" % e): ts for e, gs, ts, nm in bumped},
              open(SCR + "/truesize.json", "w"))
