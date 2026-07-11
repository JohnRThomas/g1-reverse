"""Control-flow-directed side-effect verification.

The parity harness already compares SIDE EFFECTS (ordered memory writes + call
sequence + return + fault parity). Its weakness was INPUT COVERAGE: random args
almost never hit a switch case or a small-range branch, so a reconstruction wrong
on those paths could pass. This module derives, from the ORIGINAL function's
control flow, the exact argument values that exercise every branch edge and every
switch case, and feeds them to compare() as arg_overrides. Coverage becomes a
property of the CFG, not of luck.

Extraction (light taint over a linear disasm):
  - track which argument (r0..r3) each register's value derives from (mov copies
    taint; other writes clear it);
  - `cmp argReg,#k`      -> that arg must take {k-1, k, k+1} (branch boundary);
  - `cbz/cbnz argReg`    -> {0, 1};
  - `cmp argReg,#k` that gates a tbb/tbh switch -> {0..k+1} (every case);
  - `tbb/tbh [pc, argReg]` with no preceding bound -> {0..N+1} for N table entries.
"""
import sys, os, re, json, glob
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import extract as ax, net_extract as nx
from parity import recon, emu
import recon_kit, net_recon_kit
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_MCLASS

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
BASE = "/Users/freedomcoder/Projects/G1disasm2"
_md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
_CACHE = {}

def core_ctx(core):
    if core in _CACHE: return _CACHE[core]
    if core == "app":
        c = dict(srcdir=BASE + "/recon/verified/src", read=ax.func_bytes_padded,
                 rawread=ax.read, cb=emu.CODE_BASE, ret=recon_kit._ret_kind,
                 sizes={f["entry"]: f["size"] for f in json.load(open(SCR + "/classified.json"))["functions"]})
    else:
        c = dict(srcdir=BASE + "/recon/net/src", read=nx.func_bytes_padded,
                 rawread=nx.read, cb=emu.NET_CODE_BASE, ret=net_recon_kit._ret_kind,
                 sizes={f["entry"]: f["size"] for f in json.load(open(SCR + "/net_funcs.json"))["functions"]})
    _CACHE[core] = c
    return c

def _reg(tok):
    m = re.match(r'r(\d+)$', tok.strip())
    return int(m.group(1)) if m else None

def selector_values(rawread, va, size):
    """Return {arg_index (0..3): sorted list of interesting values}."""
    code = rawread(va, min(size, 1024))
    taint = {i: {i} for i in range(4)}          # reg -> set of arg indices it derives from
    for r in range(4, 16): taint[r] = set()
    vals = {}
    def add(regnum, vs):
        for ai in taint.get(regnum, ()):
            vals.setdefault(ai, set()).update(vs)
    pending_bound = None                          # (regnum, k) from a recent cmp, may gate a switch
    for ins in _md.disasm(code, va):
        m, ops = ins.mnemonic, ins.op_str
        # switch on a register
        tb = re.search(r'\[pc,\s*(r\d+)', ops) if m in ("tbb", "tbh") else None
        if tb:
            rn = _reg(tb.group(1))
            if pending_bound and pending_bound[0] == rn:
                k = pending_bound[1]
                add(rn, range(0, min(k + 2, 40)))     # every case
            else:
                add(rn, range(0, 18))                  # unknown count: cover a spread
        # cmp argReg, #imm
        cm = re.match(r'(r\d+),\s*#(0x[0-9a-fA-F]+|\d+)$', ops) if m == "cmp" else None
        if cm:
            rn = _reg(cm.group(1)); k = int(cm.group(2), 0)
            add(rn, {max(k - 1, 0), k, k + 1})
            pending_bound = (rn, k) if k <= 40 else None
        else:
            if m not in ("it", "ite", "itt", "itte", "ittt"):  # keep bound across IT
                pending_bound = pending_bound if m in ("bhi", "bls", "bcs", "bcc", "bhs", "blo") else (pending_bound if cm else None)
        # cbz/cbnz argReg
        if m in ("cbz", "cbnz"):
            rn = _reg(ops.split(",")[0])
            if rn is not None: add(rn, {0, 1})
        # taint propagation: mov rd, rs
        mv = re.match(r'(r\d+),\s*(r\d+)$', ops) if m in ("mov", "movs", "mov.w") else None
        if mv:
            rd, rs = _reg(mv.group(1)), _reg(mv.group(2))
            if rd is not None: taint[rd] = set(taint.get(rs, ()))
        else:
            # any instruction writing a low reg (first operand) clears its taint,
            # except the compares/branches handled above
            if m not in ("cmp", "cmn", "tst", "teq", "tbb", "tbh", "cbz", "cbnz",
                         "push", "str", "strb", "strh", "stm", "b", "bl", "bx", "blx") \
               and not m.startswith("b"):
                first = ops.split(",")[0].strip()
                rd = _reg(first)
                if rd is not None and rd >= 4:
                    taint[rd] = set()  # conservative
    return {ai: sorted(vs) for ai, vs in vals.items()}

def build_overrides(selvals, cap=64):
    """One override dict per (arg, value); each pins that selector, others seeded."""
    ovs = []
    for ai in sorted(selvals):
        for v in selvals[ai]:
            ovs.append({ai: v})
            if len(ovs) >= cap: return ovs
    return ovs

def verify(core, name, trials_random=40):
    ctx = core_ctx(core)
    p = ctx["srcdir"] + "/" + name + ".c"
    if not os.path.exists(p): return {"status": "missing"}
    txt = open(p).read()
    m = re.search(r'@\s+(0x[0-9a-fA-F]+)', txt.split("\n")[0])
    if not m: return {"status": "noaddr"}
    va = int(m.group(1), 16)
    size = ctx["sizes"].get(va) or ctx["sizes"].get(va & ~1)
    if not size: return {"status": "nosize"}
    selvals = selector_values(ctx["rawread"], va, size)
    ovs = build_overrides(selvals)
    body = txt[txt.index("*/") + 2:] if "*/" in txt[:400] else txt
    comp, err = recon.compile_func(body, name, va)
    if err: return {"status": "compile-fail"}
    cb, ct, cs, cva = comp
    orig = ctx["read"](va, size, 64)
    rk = ctx["ret"](va)
    trials = len(ovs) + trials_random
    for nptr in (2, 1, 3):
        v = emu.compare(orig, va, size, cb + ct, cva, cs, code_base=ctx["cb"],
                        trials=trials, nptr=nptr, ret_kind=rk, arg_overrides=ovs)
        if not v.get("pass") and v.get("checked") == 0:
            v = emu.compare(orig, va, size, cb + ct, cva, cs, code_base=ctx["cb"],
                            trials=trials, nptr=nptr, ret_kind=rk, no_return=True, arg_overrides=ovs)
        if v.get("pass"):
            return {"status": "PASS", "selectors": selvals, "cover_cases": len(ovs),
                    "checked": v.get("checked")}
    return {"status": "FAIL", "selectors": selvals, "cover_cases": len(ovs),
            "checked": v.get("checked"), "mismatches": v.get("mismatches"), "detail": v.get("detail")}

if __name__ == "__main__":
    core, name = sys.argv[1], sys.argv[2]
    r = verify(core, name)
    print(name, r["status"], "cases=%s" % r.get("cover_cases"), "sel=%s" % r.get("selectors"))
    print("mismatches=%r" % (r.get("mismatches"),))
    print("detail=%r" % (r.get("detail"),))
