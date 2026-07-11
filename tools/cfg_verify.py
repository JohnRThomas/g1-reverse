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
    ("net", 0x01013e98): 0x1cc,  # reviewed dispatcher code ends at 0x01014064
    ("net", 0x01038654): 0x100,  # loop continuation ends at branch 0x01038752
    ("app", 0x1a064): 1764,
    ("app", 0x5fb8c): 218,
    # Wrapper ends at the tail branch; catalog folded following utility code.
    ("app", 0x50b8c): 36,
    # Atomic release wrapper ends before the literal pool at 0x566f4.
    ("app", 0x566a4): 0x50,
    # The catalog stops inside the state-1 queue handler.  The default-state
    # logger tail at 0x568da branches back into the shared epilogue; executable
    # code therefore continues through the branch at 0x568e2.
    ("app", 0x56704): 0x1e0,
    # Four-argument dispatcher ends before literal data at 0x30d0a.
    ("app", 0x30cd0): 0x3a,
    # Privacy admission wrapper tail-branches at 0x5508a; next symbol starts 0x55094.
    ("app", 0x5505c): 0x34,
    ("app", 0x531cc): 0x8,
    # Ten bytes of executable wrapper plus alignment/literal ownership to 0x4d586.
    ("app", 0x4d578): 0xe,
    # TBH case handlers and three fatal tails continue past catalog end 0x101d810.
    ("net", 0x101d404): 0x478,
    # Ghidra folded nine following utility symbols into this wrapper.
    ("net", 0x103b1c4): 16,
    # Thin adapter ends at the next symbol; old 174-byte extent absorbed eight.
    ("net", 0x10294a2): 12,
    # Null-guarded tail wrapper; old extent included FUN_0103b0f0.
    ("net", 0x103b0e8): 8,
    # Alignment adapter ends before the independent range-check helper.
    ("net", 0x103b530): 8,
    # Readiness wrapper ends before alignment/literal data and FUN_01037f14.
    ("net", 0x1037f00): 14,
    ("net", 0x100cb10): 20,
    ("net", 0x101fc14): 22,
    ("net", 0x1021838): 30,
    ("net", 0x102e23c): 58,
    ("net", 0x10323cc): 38,
    ("net", 0x103a8d0): 22,
    # Parser wrapper ends before arithmetic helper at 0x103a056 / a076.
    ("net", 0x1039fe6): 112,
    # Atomic bit-test/set owns code through 0x1034398; following words are literals.
    ("net", 0x1034368): 48,
    # The outer switch default handler continues through the terminal BL at
    # 0x101b226; the catalog stops inside the preceding case body.
    ("net", 0x101b15c): 0xce,
    # NCS mpsc_pbuf_alloc is an internal entry omitted from the catalog.  Code
    # ends at 0x4bdf2 and its owned assertion literal pool extends to 0x4be0c.
    ("app", 0x4bc8c): 0x180,
    # NCS mpsc_pbuf_claim internal entry; code ends at 0x4bfae and the owned
    # checked-lock assertion literals end immediately before 0x4bfc8.
    ("app", 0x4beb8): 0x110,
}

# Full-width fuzz values are not useful for caller-supplied iteration counts:
# they only spend the instruction budget repeating an already-covered body.
# Keep these reviewed loop counts small while the remaining arguments and RAM
# state retain their normal randomized coverage.
BOUNDED_RANDOM_ARGS = {
    ("net", 0x01038654): {1: (0, 1, 2, 3)},
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
    aliases = {"sb": 9, "sl": 10, "fp": 11, "ip": 12}
    if tok.strip() in aliases: return aliases[tok.strip()]
    m = re.match(r'r(\d+)$', tok.strip())
    return int(m.group(1)) if m else None

_RT = r'(?:r\d+|sb|sl|fp|ip)'

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
    stack_taint = {}                              # fixed SP spill slot -> arg taint
    for ins in _md.disasm(code, va):
        if ins.address < skip_until:
            continue
        m, ops = ins.mnemonic, ins.op_str
        if m in ("bl", "blx"):
            # ABI return registers are defined by the callee, not derived from
            # the incoming pointer/scalar argument previously held in r0/r1.
            taint[0] = set(); taint[1] = set()
            continue
        # Preserve argument provenance through the compiler's fixed stack
        # spills (for example `str r1,[sp,#8]` followed by `ldr r3,[sp,#8]`).
        # This is value flow, unlike the stale pointee taint intentionally
        # cleared below when a register is overwritten by an arbitrary load.
        stsp = re.match(r'(' + _RT + r'),\s*\[sp(?:,\s*#(0x[0-9a-fA-F]+|\d+))?\]$', ops) \
               if m in ("str", "str.w") else None
        if stsp:
            rs, off = _reg(stsp.group(1)), int(stsp.group(2), 0) if stsp.group(2) else 0
            stack_taint[off] = set(taint.get(rs, ()))
            continue
        ldsp = re.match(r'(' + _RT + r'),\s*\[sp(?:,\s*#(0x[0-9a-fA-F]+|\d+))?\]$', ops) \
               if m in ("ldr", "ldr.w") else None
        if ldsp:
            rd, off = _reg(ldsp.group(1)), int(ldsp.group(2), 0) if ldsp.group(2) else 0
            taint[rd] = set(stack_taint.get(off, ()))
            continue
        # switch on a register
        tb = re.search(r'\[pc,\s*(' + _RT + r')', ops) if m in ("tbb", "tbh") else None
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
        cm = re.match(r'(' + _RT + r'),\s*#(0x[0-9a-fA-F]+|\d+)$', ops) if m in ("cmp", "cmp.w") else None
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
        mv = re.match(r'(' + _RT + r'),\s*(' + _RT + r')$', ops) if m in ("mov", "movs", "mov.w") else None
        if mv:
            rd, rs = _reg(mv.group(1)), _reg(mv.group(2))
            if rd is not None: taint[rd] = set(taint.get(rs, ()))
        else:
            # any instruction writing a low reg (first operand) clears its taint,
            # except the compares/branches handled above
            if m not in ("cmp", "cmp.w", "cmn", "tst", "teq", "tbb", "tbh", "cbz", "cbnz",
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
    # A small reviewed exception list covers functions whose literal islands
    # stop linear decoding before the later BLX. Do not infer callbacks merely
    # from a conventional-looking offset: +0x0c is rd_idx in mpsc_pbuf_free.
    reviewed_callback_slots = {
        0x1a064: {(0, 0x0c)},  # ble_process_get_req send callback
    }
    callback_slots.update(reviewed_callback_slots.get(va, ()))
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
    bounded = BOUNDED_RANDOM_ARGS.get((core, va))
    if bounded:
        while len(ovs) < trials:
            n = len(ovs)
            ovs.append({ai: vals[n % len(vals)] for ai, vals in bounded.items()})
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
    nptr_modes = tuple(dict.fromkeys(
        n for n in (max(1, required_nptr), 2, 1, 3, 4) if n >= required_nptr))
    # Both cores use Zephyr's ARCH_EXCEPT(4): clear BASEPRI, load reason 4,
    # SVC #2. The SVC is a production-noreturn runtime exception even though
    # the compiler emits a defensive BX LR after it.
    terminal_targets = ({0x01008d00, 0x0100ebb8, 0x01016828, 0x010256dc, 0x01039bb0}
                        if core == "net" else {0x0007e2ec})
    for nptr in nptr_modes:
        if prefix_first:
            v = emu.compare(orig, va, size, cb + ct, cva, cs, code_base=ctx["cb"],
                            trials=trials, nptr=nptr, ret_kind=rk, no_return=True,
                            arg_overrides=ovs, memory_overrides=movs,
                            terminal_targets=terminal_targets)
        else:
            v = emu.compare(orig, va, size, cb + ct, cva, cs, code_base=ctx["cb"],
                            trials=trials, nptr=nptr, ret_kind=rk, arg_overrides=ovs,
                            memory_overrides=movs, terminal_targets=terminal_targets)
            if not v.get("pass") and v.get("checked") == 0:
                v = emu.compare(orig, va, size, cb + ct, cva, cs, code_base=ctx["cb"],
                                trials=trials, nptr=nptr, ret_kind=rk, no_return=True,
                                arg_overrides=ovs, memory_overrides=movs,
                                terminal_targets=terminal_targets)
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
    # mpsc_pbuf_free has a real get_wlen callback at +0x1c. Its +0x0c member
    # is the scalar rd_idx and must never be seeded as executable code.
    _, free_slots, _ = pointer_control_inputs(c["rawread"], 0x4bfc8, 224)
    assert free_slots == [(0, 0x1c)], free_slots
    n = core_ctx("net")
    _, _, bad_slots = pointer_control_inputs(n["rawread"], 0x1023ad8,
                                             n["sizes"][0x1023ad8])
    assert (1, 1236) not in bad_slots, bad_slots
    assert 1 not in selector_values(n["rawread"], 0x1023ad8,
                                    n["sizes"][0x1023ad8])
    # FUN_0102f580 overwrites entry r3 with a PC-relative literal and later
    # with IPSR before CBZ. Neither branch is controlled by argument 3.
    assert selector_values(n["rawread"], 0x102f580, 36) == {}
    # Capstone spells r10 as `sl`; the event switch in FUN_0101ab20 moves
    # argument 1 there before CMP/TBB, so aliases must retain provenance.
    assert set(range(10)) <= set(selector_values(n["rawread"], 0x101ab20, 532)[1])
    # FUN_0005fb8c's catalog ends at 0x5fc62, in the middle of its epilogue.
    # The reachable branch at 0x5fc64 proves the body extends through 0x5fc66.
    assert core_ctx("app")["sizes"][0x5fb8c] == 214
    assert true_extent(0x5fb8c, 214) == 218
    # FUN_0102b900's production fatal path must remain reason 3 followed by
    # runtime-exception SVC 2; this anchors the readable platform boundary to
    # the exact shipped opcode sequence.
    fatal = core_ctx("net")["rawread"](0x0102b926, 12)
    assert fatal == bytes.fromhex("404080f311884ff0030002df"), fatal.hex()
    # Net timing reconstruction spills arg1 to [sp,#8] before branching on
    # the restored value. Directed coverage must retain that dependency.
    nctx = core_ctx("net")
    assert selector_values(nctx["rawread"], 0x101a38c, 1940).get(1) == [0, 1]

    # Strict terminal-key regressions. Post-terminal state is absent by design;
    # only the complete prefix hash, event count and call ordinal participate.
    base = {"terminal": True, "terminal_call_ordinal": 2,
            "terminal_event_count": 5, "terminal_prefix_hash": "abc"}
    assert emu._terminal_key(base) == (2, 5, "abc")
    assert emu._terminal_key({**base, "terminal_prefix_hash": "changed-write"}) != emu._terminal_key(base)
    assert emu._terminal_key({**base, "terminal_call_ordinal": 3,
                              "terminal_event_count": 6}) != emu._terminal_key(base)
    assert emu._terminal_key({"terminal": False, "returned": True}) is None
    # App assert_post_action is byte-for-byte the same Zephyr runtime-exception
    # sequence as the net panic endpoint: BASEPRI=0; reason=4; SVC #2; BX LR.
    assert ax.read(0x7e2ec, 14) == bytes.fromhex(
        "404080f311884ff0040002df7047")
    # Net fatal logger begins by saving the complete call context and disabling
    # interrupts before entering its diagnostic output loop.
    assert nx.read(0x010256dc, 6) == bytes.fromhex("1fb572b6134b")
    # Prefix verification for a genuine reset loop must still reject a
    # changed pre-loop write even though neither side returns.
    loop_ok = bytes.fromhex("0121" "0160" "fee7")
    loop_bad = bytes.fromhex("0221" "0160" "fee7")
    v = emu.compare(loop_ok, 0x50000, len(loop_ok), loop_ok, 0x50000,
                    len(loop_ok), trials=1, nptr=1, no_return=True)
    assert v["pass"], v
    v = emu.compare(loop_ok, 0x50000, len(loop_ok), loop_bad, 0x50000,
                    len(loop_bad), trials=1, nptr=1, no_return=True)
    assert not v["pass"], v
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
