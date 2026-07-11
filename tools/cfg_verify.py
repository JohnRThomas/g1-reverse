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
from truesize import true_extent
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_MCLASS

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
BASE = "/Users/freedomcoder/Projects/G1disasm2"
_md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
_CACHE = {}
# Ghidra/classification under-reports these resolved jump-table bodies. Values
# are CFG-confirmed executable extents, not trailing data-table inflation.
TRUE_SIZE_OVERRIDES = {
    ("app", 0x1a064): 1764,
    ("app", 0x5fb8c): 218,
    # Ghidra folded nine following utility symbols into this wrapper.
    ("net", 0x103b1c4): 16,
}

def core_ctx(core):
    if core in _CACHE: return _CACHE[core]
    if core == "app":
        c = dict(srcdir=BASE + "/recon/app/src", read=ax.func_bytes_padded,
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
    skip_until = 0
    for ins in _md.disasm(code, va):
        if ins.address < skip_until:
            continue
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
            entries = (pending_bound[1] + 1) if pending_bound and pending_bound[0] == rn else 18
            skip_until = (ins.address + 4 + entries * (2 if m == "tbh" else 1) + 1) & ~1
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
                # Writes replace the prior value of every destination register,
                # including r0-r3.  Keeping argument taint on a later `ldr r3`
                # falsely classifies its pointee and branches as arg3-derived.
                if rd is not None:
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

def pointer_control_inputs(rawread, va, size):
    """Derive byte-valued switch inputs loaded through pointer arguments.

    Tracks the common firmware shape `mov saved,arg; ldrb value,[saved,#off];
    sub selector,value,#base; cmp selector,#last; tbb/tbh`. Also returns
    indirect-call pointer slots loaded from argument-relative memory so tests
    can give those callbacks a deterministic external Thumb target.
    """
    code = rawread(va, min(size, 2048))
    origin = {i: ("arg", i, 0, 0) for i in range(4)}
    pending = None
    skip_until = 0
    cases, callback_slots, data_pointer_slots = [], set(), set()
    loaded_slots = {}
    for ins in _md.disasm(code, va):
        if ins.address < skip_until:
            continue
        m, ops = ins.mnemonic, ins.op_str
        mv = re.match(r'(r\d+),\s*(r\d+)$', ops) if m in ("mov", "movs", "mov.w") else None
        if mv:
            rd, rs = _reg(mv.group(1)), _reg(mv.group(2))
            origin[rd] = origin.get(rs)
            loaded_slots.pop(rd, None)
            continue
        ld = re.match(r'(r\d+),\s*\[(r\d+)(?:,\s*#(0x[0-9a-fA-F]+|\d+))?\]$', ops) \
             if m in ("ldrb", "ldrb.w", "ldr", "ldr.w") else None
        if ld:
            rd, rb = _reg(ld.group(1)), _reg(ld.group(2))
            off = int(ld.group(3), 0) if ld.group(3) else 0
            base = origin.get(rb)
            if base and base[0] == "arg":
                width = 1 if m.startswith("ldrb") else 4
                origin[rd] = ("ptr", base[1], base[2] + off, 0, width)
                if width == 4: loaded_slots[rd] = (base[1], base[2] + off)
                # Common firmware object ABI: callback/send vtable entry at
                # object + 0x0c. Literal islands can prevent linear Capstone
                # decoding from reaching the later BLX, so retain this slot.
                if width == 4 and base[2] + off == 0x0c:
                    callback_slots.add((base[1], base[2] + off))
            else:
                origin[rd] = None; loaded_slots.pop(rd, None)
            continue
        ar = re.match(r'(r\d+),\s*(r\d+),\s*#(0x[0-9a-fA-F]+|\d+)$', ops) \
             if m in ("sub", "sub.w", "subs", "add", "add.w", "adds") else None
        if ar:
            rd, rs, imm = _reg(ar.group(1)), _reg(ar.group(2)), int(ar.group(3), 0)
            src = origin.get(rs)
            if src and src[0] == "ptr":
                delta = src[3] + (imm if m.startswith("add") else -imm)
                origin[rd] = (src[0], src[1], src[2], delta, src[4])
            else: origin[rd] = None
            loaded_slots.pop(rd, None)
            continue
        cm = re.match(r'(r\d+),\s*#(0x[0-9a-fA-F]+|\d+)$', ops) if m == "cmp" else None
        if cm:
            rn, k = _reg(cm.group(1)), int(cm.group(2), 0)
            pending = (rn, k, origin.get(rn))
            continue
        tb = re.search(r'\[pc,\s*(r\d+)', ops) if m in ("tbb", "tbh") else None
        if tb and pending and pending[0] == _reg(tb.group(1)):
            expr, k = pending[2], pending[1]
            if expr and expr[0] == "ptr" and expr[4] == 1:
                for normalized in range(k + 1):
                    raw = normalized - expr[3]
                    if 0 <= raw <= 255:
                        cases.append((expr[1], expr[2], raw))
            skip_until = (ins.address + 4 + (k + 1) * (2 if m == "tbh" else 1) + 1) & ~1
        if m == "blx":
            rn = _reg(ops)
            if rn in loaded_slots: callback_slots.add(loaded_slots[rn])
        mem_base = re.search(r'\[(r\d+)', ops)
        if mem_base and m.startswith(("str", "ldr")):
            rb = _reg(mem_base.group(1))
            if rb in loaded_slots and loaded_slots[rb] not in callback_slots:
                slot = loaded_slots[rb]
                # Only compact object-header pointer fields are safe to
                # materialize generically. Large indexed offsets frequently
                # arise from scalar arithmetic that linear taint cannot prove
                # is a pointer (regression: net FUN_01023ad8 arg1+1236).
                if 0 <= slot[1] <= 0x100:
                    data_pointer_slots.add(slot)
    return cases, sorted(callback_slots), sorted(data_pointer_slots)

def verify(core, name, trials_random=40):
    ctx = core_ctx(core)
    p = ctx["srcdir"] + "/" + name + ".c"
    if not os.path.exists(p): return {"status": "missing"}
    txt = open(p).read()
    m = re.search(r'@\s+(0x[0-9a-fA-F]+)', txt.split("\n")[0])
    if not m: return {"status": "noaddr"}
    va = int(m.group(1), 16)
    size = ctx["sizes"].get(va) or ctx["sizes"].get(va & ~1)
    size = TRUE_SIZE_OVERRIDES.get((core, va), size)
    if not size: return {"status": "nosize"}
    # Do not apply true_extent() generically here: a noreturn call at the end
    # of a function can make a linear scanner decode the following literal
    # pool as fall-through code. Only CFG-reviewed extents belong above.
    selvals = selector_values(ctx["rawread"], va, size)
    ptr_cases, callback_slots, data_pointer_slots = pointer_control_inputs(ctx["rawread"], va, size)
    ovs = [{} for _ in ptr_cases] + build_overrides(selvals)
    body = txt[txt.index("*/") + 2:] if "*/" in txt[:400] else txt
    prefix_first = "CFG_VERIFY_PREFIX_FIRST" in txt[:400]
    comp, err = recon.compile_func(body, name, va)
    if err: return {"status": "compile-fail"}
    cb, ct, cs, cva = comp
    orig = ctx["read"](va, size, 64)
    rk = ctx["ret"](va)
    trials = len(ovs) + trials_random
    callback_setup = [(ai, off, (0x00080001).to_bytes(4, "little"))
                      for ai, off in callback_slots]
    pointer_setup = [(ai, off, (0x20030000 + 0x100 * n).to_bytes(4, "little"))
                     for n, (ai, off) in enumerate(data_pointer_slots)]
    common_setup = callback_setup + pointer_setup
    movs = []
    for ai, off, value in ptr_cases:
        movs.append([(ai, off, bytes((value,)))] + common_setup)
    for t in range(len(movs), trials):
        # A scalar selector override may reuse an argument that is a pointer
        # on another path. Never apply pointee setup through that scalar value
        # (especially zero, which would otherwise modify mapped code memory).
        overridden = set(ovs[t]) if t < len(ovs) else set()
        movs.append([item for item in common_setup if item[0] not in overridden])
    required_nptr = 1 + max([ai for ai, _, _ in ptr_cases] +
                            [ai for ai, _ in callback_slots] +
                            [ai for ai, _ in data_pointer_slots], default=-1)
    nptr_modes = tuple(n for n in (2, 1, 3, 4) if n >= required_nptr)
    for nptr in nptr_modes:
        if prefix_first:
            v = emu.compare(orig, va, size, cb + ct, cva, cs, code_base=ctx["cb"],
                            trials=trials, nptr=nptr, ret_kind=rk, no_return=True,
                            arg_overrides=ovs, memory_overrides=movs)
        else:
            v = emu.compare(orig, va, size, cb + ct, cva, cs, code_base=ctx["cb"],
                            trials=trials, nptr=nptr, ret_kind=rk, arg_overrides=ovs,
                            memory_overrides=movs)
            if not v.get("pass") and v.get("checked") == 0:
                v = emu.compare(orig, va, size, cb + ct, cva, cs, code_base=ctx["cb"],
                                trials=trials, nptr=nptr, ret_kind=rk, no_return=True,
                                arg_overrides=ovs, memory_overrides=movs)
        if v.get("pass"):
            return {"status": "PASS", "selectors": selvals, "pointer_cases": ptr_cases,
                    "callback_slots": callback_slots, "data_pointer_slots": data_pointer_slots,
                    "cover_cases": len(ovs),
                    "checked": v.get("checked")}
    return {"status": "FAIL", "selectors": selvals, "pointer_cases": ptr_cases,
            "callback_slots": callback_slots, "data_pointer_slots": data_pointer_slots,
            "cover_cases": len(ovs),
            "checked": v.get("checked"), "mismatches": v.get("mismatches"), "detail": v.get("detail")}

def self_test():
    """Regression gates for pointee setup and the recovered TBH selector."""
    # ldrb r0,[r0]; bx lr -- identical sides must see the injected byte.
    leaf = bytes.fromhex("0078" "7047")
    mem = [[(0, 0, b"\x5a")]]
    v = emu.compare(leaf, 0x50000, len(leaf), leaf, 0x50000, len(leaf),
                    trials=1, nptr=1, memory_overrides=mem)
    assert v["pass"], v
    # A different candidate remains a negative control: overrides do not
    # weaken return/trace comparison.
    const = bytes.fromhex("0020" "7047")
    v = emu.compare(leaf, 0x50000, len(leaf), const, 0x50000, len(const),
                    trials=1, nptr=1, memory_overrides=mem)
    assert not v["pass"], v
    # Argument 3 can itself be a pointer-controlled selector. Ensure the
    # four-pointer mode maps it before applying a relative memory override.
    leaf_arg3 = bytes.fromhex("1878" "7047")  # ldrb r0,[r3]; bx lr
    v = emu.compare(leaf_arg3, 0x50000, len(leaf_arg3),
                    leaf_arg3, 0x50000, len(leaf_arg3), trials=1, nptr=4,
                    memory_overrides=[[(3, 0, b"\xa5")]])
    assert v["pass"], v
    c = core_ctx("app")
    cases, slots, data_slots = pointer_control_inputs(c["rawread"], 0x1a064, 1764)
    assert cases == [(1, 0, x) for x in range(0x29, 0x3f)], cases
    assert (0, 0x0c) in slots, slots
    assert (0, 0x10) in data_slots, data_slots
    n = core_ctx("net")
    _, _, bad_slots = pointer_control_inputs(n["rawread"], 0x1023ad8,
                                             n["sizes"][0x1023ad8])
    assert (1, 1236) not in bad_slots, bad_slots
    assert 1 not in selector_values(n["rawread"], 0x1023ad8,
                                    n["sizes"][0x1023ad8])
    # FUN_0102f580 overwrites entry r3 with a PC-relative literal and later
    # with IPSR before CBZ. Neither branch is controlled by argument 3.
    assert selector_values(n["rawread"], 0x102f580, 36) == {}
    # FUN_0005fb8c's catalog ends at 0x5fc62, in the middle of its epilogue.
    # The reachable branch at 0x5fc64 proves the body extends through 0x5fc66.
    assert core_ctx("app")["sizes"][0x5fb8c] == 214
    assert true_extent(0x5fb8c, 214) == 218
    return True

if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] == "--self-test":
        print("cfg_verify self-test:", "PASS" if self_test() else "FAIL")
        raise SystemExit(0)
    core, name = sys.argv[1], sys.argv[2]
    r = verify(core, name)
    print(name, r["status"], "cases=%s" % r.get("cover_cases"), "sel=%s" % r.get("selectors"))
    print("mismatches=%r" % (r.get("mismatches"),))
    print("detail=%r" % (r.get("detail"),))
