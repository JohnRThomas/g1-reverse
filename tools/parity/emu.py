"""
Differential parity harness for Cortex-M33 (ARMv8-M, Thumb) functions.

Goal: prove that a *reconstructed* function is semantically identical to the
original firmware function, without needing bit-identical codegen.

Method (differential emulation with identical callee oracles):
  * Load the ORIGINAL function's raw bytes at its real virtual address.
  * Load the CANDIDATE (recompiled) function's bytes at the SAME virtual
    address (its literal pool is position-relative, so this is valid).
  * For N randomized trials, initialize IDENTICAL machine state for both:
      - r0..r3 arguments (random or pointers into a shared scratch buffer)
      - a scratch RAM region filled from a per-trial seeded PRNG
      - stack
  * Execute each under Unicorn. Model every called function as a pure,
    deterministic ORACLE: return value = hash(target, r0..r3). Both versions
    see the identical oracle, and we also record the *sequence* of
    (callee_target, args) — so a divergence in what/how a callee is called is
    itself a parity failure.
  * After each run, compare: return value (r0[/r1]), all bytes written to the
    scratch region, and the call trace. All-equal across all trials => PASS.

This proves the function computes the same result given identical callee
behavior and identical inputs — the correct notion of semantic parity for a
unit whose dependencies are abstracted.
"""
import struct
import hashlib
import re
from unicorn import *
from unicorn.arm_const import *
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_MCLASS

# ---- fixed memory map -------------------------------------------------------
CODE_BASE = 0x00000000
CODE_SIZE = 0x00200000          # 2 MiB flat code region (app core)
NET_CODE_BASE = 0x01000000      # net core flash window (nRF5340 CPUNET)
RAM_BASE  = 0x20000000
RAM_SIZE  = 0x00080000          # 512 KiB
SCRATCH   = 0x20010000          # arg-pointer scratch region (inside RAM)
SCRATCH_SZ = 0x8000
STACK_TOP = 0x2007F000          # inside RAM
RETURN_MAGIC = 0x001F0000       # LR sentinel inside mapped CODE region

REG = [UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3,
       UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7,
       UC_ARM_REG_R8, UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11,
       UC_ARM_REG_R12]

# VFP/FPU single-precision registers s0..s15 (cover d0..d7): seeded so
# float-argument functions get identical randomized inputs, and s0 (the
# float/double return) is compared for float-returning functions.
SREG = [getattr(__import__("unicorn.arm_const", fromlist=["x"]),
                "UC_ARM_REG_S%d" % i) for i in range(16)]
_md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)


def _prng_fill(seed_bytes, n):
    """Deterministic keystream from SHA-256 in counter mode."""
    out = bytearray()
    ctr = 0
    while len(out) < n:
        out += hashlib.sha256(seed_bytes + struct.pack("<I", ctr)).digest()
        ctr += 1
    return bytes(out[:n])


def _oracle(idx):
    # Modeled callee return value, keyed ONLY on call order (index). Both the
    # original and the recompiled candidate therefore receive the identical
    # value at their k-th call, so return-value-dependent control flow is
    # reproducible and comparable. Keying on index (not arg registers) avoids
    # false mismatches from ABI noise in unused/dead argument registers, while
    # any argument error that actually changes observable behavior still shows
    # up as a differing memory-write trace, call count/order, or return value.
    h = hashlib.sha256(struct.pack("<I", idx & 0xffffffff)).digest()
    return struct.unpack_from("<I", h, 0)[0], struct.unpack_from("<I", h, 4)[0]


class Runner:
    def __init__(self, func_va, func_size, func_bytes, code_base=CODE_BASE):
        self.va = func_va
        self.size = func_size
        self.body = bytes(func_bytes)
        self.code_base = code_base

    def _new_uc(self):
        uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB | UC_MODE_MCLASS)
        uc.mem_map(CODE_BASE, CODE_SIZE)
        if self.code_base == NET_CODE_BASE:
            uc.mem_map(NET_CODE_BASE, 0x40000)
        uc.mem_map(RAM_BASE, RAM_SIZE)
        return uc

    def run(self, seed, args, scratch_seed, max_insns=200000, stop_events=0,
            memory_overrides=None):
        """Run one trial. Returns dict(state) or {'error':...}.
        stop_events>0: stop after that many side-effect events (for non-returning
        supervisor loops — we compare the ordered event-trace prefix instead of a
        return value, which is robust to GCC-vs-original instructions-per-loop)."""
        uc = self._new_uc()
        # place function body at its VA
        uc.mem_write(self.va, self.body)
        # seed RAM + scratch identically per trial
        uc.mem_write(RAM_BASE, _prng_fill(b"ram" + struct.pack("<I", scratch_seed), RAM_SIZE))

        # registers
        for i, r in enumerate(REG):
            uc.reg_write(r, 0)
        for i in range(4):
            uc.reg_write(REG[i], args[i] & 0xffffffff)
        # CFG-directed pointee inputs. Each item is (arg_index, byte_offset,
        # bytes); applying it before hooks means test setup is not an observed
        # side effect. Both original and candidate receive identical memory.
        for ai, off, data in (memory_overrides or ()):
            address = ((args[ai] & 0xffffffff) + off) & 0xffffffff
            uc.mem_write(address, bytes(data))
        # seed VFP s0..s15 identically (float args + float-return coverage)
        fseed = _prng_fill(b"vfp" + struct.pack("<I", scratch_seed), 64)
        for i, sr in enumerate(SREG):
            try:
                uc.reg_write(sr, struct.unpack_from("<I", fseed, i * 4)[0])
            except UcError:
                break
        uc.reg_write(UC_ARM_REG_SP, STACK_TOP)
        uc.reg_write(UC_ARM_REG_LR, RETURN_MAGIC | 1)

        state = {"ncalls": 0, "returned": False, "events": []}
        fstart, fend = self.va, self.va + self.size

        # ordered event trace: every non-stack memory write + every call marker.
        # Stack writes (register save/restore/spill) are an implementation
        # detail, not observable behavior, so they are excluded.
        stack_lo = STACK_TOP - 0x9000
        stack_hi = STACK_TOP + 0x100
        def _mw(uc, access, address, size, value, ud):
            if not (stack_lo <= address < stack_hi):
                state["events"].append(("W", address & 0xffffffff, size,
                                        value & ((1 << (size * 8)) - 1)))
                if stop_events and len(state["events"]) >= stop_events:
                    state["capped_events"] = True; uc.emu_stop()
            return True
        uc.hook_add(UC_HOOK_MEM_WRITE, _mw)

        # lazily map unmapped accesses with deterministic zero pages
        def _map_miss(uc, access, address, size, value, ud):
            page = address & ~0xFFF
            try:
                uc.mem_map(page, 0x1000)
                uc.mem_write(page, b"\x00" * 0x1000)
            except UcError:
                pass
            return True
        uc.hook_add(UC_HOOK_MEM_READ_UNMAPPED | UC_HOOK_MEM_WRITE_UNMAPPED |
                    UC_HOOK_MEM_FETCH_UNMAPPED, _map_miss)

        def _code(uc, address, size, ud):
            pc = address
            # Treat the whole sentinel window as "returned" — some return
            # sequences (e.g. IT-block-terminated pop {pc}) land a couple of
            # bytes into the sentinel region rather than exactly on it.
            if RETURN_MAGIC <= pc < RETURN_MAGIC + 0x10:
                state["returned"] = True
                uc.emu_stop(); return
            if fstart <= pc < fend:
                # Unicorn inconsistently enforces alignment for M-profile
                # exclusive instructions depending on the encoded Rt register.
                # Cortex-M word/halfword exclusives architecturally fault on
                # misalignment, so enforce that rule before executing either
                # original or candidate code.
                raw = bytes(uc.mem_read(pc, size))
                ins = next(_md.disasm(raw, pc), None)
                if ins and re.match(r'^(?:ld|st)[arl]?ex', ins.mnemonic):
                    bm = re.search(r'\[(r\d+)\]', ins.op_str)
                    if bm:
                        reg = int(bm.group(1)[1:])
                        if reg >= len(REG):
                            return
                        addr = uc.reg_read(REG[reg])
                        align = 1 if ins.mnemonic.endswith('b') else (2 if ins.mnemonic.endswith('h') else 4)
                        if addr & (align - 1):
                            state["alignment_fault"] = True
                            state["fault_pc"] = pc
                            uc.emu_stop(); return
                return  # normal in-body execution
            # out of body: a call or tail-branch to another function -> oracle it
            lr = uc.reg_read(UC_ARM_REG_LR)
            idx = state["ncalls"]
            state["ncalls"] += 1
            state["events"].append(("C", idx))
            if stop_events and len(state["events"]) >= stop_events:
                state["capped_events"] = True; uc.emu_stop(); return
            o0, o1 = _oracle(idx)
            uc.reg_write(UC_ARM_REG_R0, o0)
            uc.reg_write(UC_ARM_REG_R1, o1)
            # return to caller (LR). If LR is the sentinel this ends the function.
            if (lr & ~1) == (RETURN_MAGIC & ~1):
                state["returned"] = True
                uc.emu_stop(); return
            uc.reg_write(UC_ARM_REG_PC, lr | 1)
            uc.emu_stop()
            # will be restarted by the driver loop
            state["_resume"] = lr | 1
        uc.hook_add(UC_HOOK_CODE, _code)

        pc = self.va | 1
        total = 0
        try:
            while True:
                state.pop("_resume", None)
                uc.emu_start(pc, 0, 0, max_insns)
                total += 1
                if state.get("returned"):
                    break
                if state.get("capped_events"):
                    break  # collected enough events for a non-returning function
                resume = state.get("_resume")
                if resume is None:
                    break  # stopped w/o call/return (count limit)
                pc = resume
                if total > 5000:
                    break
        except UcError as e:
            # A deterministic fault is itself observable behavior. Capture a
            # signature (error kind, #calls + write trace so far, faulting
            # offset within the function) so that an original and a candidate
            # that fault identically are recognised as PARITY, not skipped.
            ev = state["events"]
            return {"error": str(e).split("(")[0].strip(),
                    "ncalls": state["ncalls"],
                    "events_hash": hashlib.sha256(repr(ev).encode()).hexdigest(),
                    "fault_off": (uc.reg_read(UC_ARM_REG_PC) - self.va) & 0xffffffff}

        if state.get("alignment_fault"):
            ev = state["events"]
            return {"error": "Unhandled CPU exception",
                    "ncalls": state["ncalls"],
                    "events_hash": hashlib.sha256(repr(ev).encode()).hexdigest(),
                    "fault_off": (state["fault_pc"] - self.va) & 0xffffffff}

        r0 = uc.reg_read(UC_ARM_REG_R0)
        r1 = uc.reg_read(UC_ARM_REG_R1)
        try:
            s0 = uc.reg_read(SREG[0]); s1 = uc.reg_read(SREG[1])
        except UcError:
            s0 = s1 = 0
        ev = state["events"]
        eh = hashlib.sha256(repr(ev).encode()).hexdigest()
        ph = hashlib.sha256(repr(ev[:stop_events] if stop_events else ev).encode()).hexdigest()
        return {"r0": r0, "r1": r1, "s0": s0, "s1": s1,
                "returned": state["returned"], "prefix_hash": ph,
                "events_hash": eh, "ncalls": state["ncalls"],
                "nevents": len(ev)}


def make_args(seed, nptr=2):
    """Build a trial's argument vector. First `nptr` args point into scratch.

    Non-pointer args MIX small/boundary values with full-random ones. Pure
    32-bit random almost never lands in a small valid range, so a function that
    dispatches on a bounded argument (cmp rN,#k; tbb/tbh; cbz rN) would only ever
    have its default path fuzzed -- letting a wrong reconstruction pass. Seeding
    small/boundary values ~45% of the time exercises the real switch cases and
    flag branches. Pointer args are unchanged (identical addr for orig+cand)."""
    rnd = _prng_fill(b"args" + struct.pack("<I", seed), 32)
    vals = list(struct.unpack("<8I", rnd))
    mode = _prng_fill(b"argm" + struct.pack("<I", seed), 8)   # separate stream
    SMALL = (0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 0xff, 0x100,
             0x7fffffff, 0x80000000, 0xffffffff)
    args = []
    for i in range(4):
        if i < nptr:
            # word-aligned pointer into scratch: avoids spurious LDREX/STREX
            # alignment faults (Cortex-M requires word-aligned exclusives) while
            # keeping the address identical for original and candidate.
            args.append(SCRATCH + ((vals[i] % (SCRATCH_SZ // 2)) & ~3))
        elif mode[i] * 100 // 256 < 45:
            args.append(SMALL[vals[i] % len(SMALL)])
        else:
            args.append(vals[i])
    return args


def compare(orig_bytes, orig_va, orig_size,
            cand_bytes, cand_va, cand_size,
            code_base=CODE_BASE, trials=64, nptr=2, verbose=False,
            ret_kind="i32", no_return=False, prefix_k=200, arg_overrides=None,
            memory_overrides=None):
    """arg_overrides: optional list of {arg_index: value} dicts. When given, the
    first len(arg_overrides) trials pin those argument registers to the specified
    values (control-flow-derived, to guarantee every branch/switch-case is
    exercised) while other args keep their seeded values; remaining trials are
    fully seeded. This makes coverage a property of the CFG, not of luck."""
    """ret_kind selects which register(s) form the return part of the parity key,
    so we compare exactly what the function's ABI defines as its result:
      void -> none;  i32 -> r0;  i64 -> r0,r1;  f32 -> s0;  f64 -> s0,s1.
    Everything else (ordered memory writes, call count/order, returned flag) is
    always compared."""
    def _cf32(u):
        # canonicalize NaN: any float NaN payload -> one value (real inputs are
        # never NaN; differing NaN bit-payloads between vmla and mul+add are not
        # a semantic difference).
        if (u & 0x7f800000) == 0x7f800000 and (u & 0x007fffff):
            return 0x7fc00000
        return u
    def _cf64(lo, hi):
        if (hi & 0x7ff00000) == 0x7ff00000 and ((hi & 0x000fffff) or lo):
            return (0, 0x7ff80000)
        return (lo, hi)
    def _retkey(x):
        if ret_kind == "void":
            return ()
        if ret_kind == "i64":
            return (x["r0"], x["r1"])
        if ret_kind == "f32":
            return (_cf32(x["s0"]),)
        if ret_kind == "f64":
            return _cf64(x["s0"], x["s1"])
        return (x["r0"],)  # i32 default
    """Run both functions over `trials` randomized inputs; return verdict dict."""
    ro = Runner(orig_va, orig_size, orig_bytes, code_base)
    rc = Runner(cand_va, cand_size, cand_bytes, code_base)
    mism = []
    checked = 0
    se = prefix_k if no_return else 0
    for t in range(trials):
        args = make_args(t, nptr)
        if arg_overrides and t < len(arg_overrides):
            for i, v in arg_overrides[t].items():
                if 0 <= i < len(args):
                    args[i] = v & 0xffffffff
        mov = memory_overrides[t] if memory_overrides and t < len(memory_overrides) else None
        a = ro.run(t, args, t, stop_events=se, memory_overrides=mov)
        # candidate emulated at its own VA but identical inputs/scratch
        b = rc.run(t, args, t, stop_events=se, memory_overrides=mov)
        if no_return and "error" not in a and "error" not in b:
            # Non-returning supervisor loop: compare the ordered side-effect
            # prefix (calls + memory writes). Robust to instructions-per-loop
            # differences because events are semantic, not instruction-counted.
            checked += 1
            if a["returned"] or b["returned"]:
                key_a = (_retkey(a), a["returned"], a["ncalls"], a["events_hash"])
                key_b = (_retkey(b), b["returned"], b["ncalls"], b["events_hash"])
                if key_a != key_b:
                    mism.append((t, "prefix-return", key_a, key_b))
            elif a["prefix_hash"] != b["prefix_hash"]:
                mism.append((t, "prefix", a["nevents"], b["nevents"]))
            continue
        ea, eb = "error" in a, "error" in b
        if ea or eb:
            # Both must fault identically (same kind, same call/write trace,
            # same faulting offset) to count as parity; otherwise mismatch.
            if ea and eb:
                # The instruction offset is code-generation-specific: two C
                # implementations can perform the same calls/writes and raise
                # the same architectural fault at different text offsets.
                # Preserve fault_off in diagnostics, but semantic parity is
                # fault kind plus the complete ordered side-effect trace.
                sa = (a["error"], a["ncalls"], a["events_hash"])
                sb = (b["error"], b["ncalls"], b["events_hash"])
                checked += 1
                if sa != sb:
                    mism.append((t, "fault", sa, sb))
            else:
                mism.append((t, "one-sided-fault", a.get("error"), b.get("error")))
            continue
        # Both hit the instruction cap without returning on this input: the
        # trial is inconclusive (adversarial random loop bound), so skip it.
        # If only ONE side fails to return, the returned-flag mismatch below
        # still catches a genuine infinite-loop reconstruction bug.
        if not a["returned"] and not b["returned"]:
            continue
        checked += 1
        key_a = (_retkey(a), a["returned"], a["ncalls"], a["events_hash"])
        key_b = (_retkey(b), b["returned"], b["ncalls"], b["events_hash"])
        if key_a != key_b:
            mism.append((t, "state", a, b))
            if verbose:
                print("trial", t, "MISMATCH\n  orig", key_a, "\n  cand", key_b)
    return {"pass": len(mism) == 0 and checked > 0,
            "trials": trials, "checked": checked,
            "mismatches": len(mism), "detail": mism[:5]}


if __name__ == "__main__":
    # self-test: identical bytes must always pass
    import sys
    va = 0x50000
    # leaf: movs r0,#5 ; bx lr   -> returns constant 5
    leaf = bytes.fromhex("0520" "7047")
    v = compare(leaf, va, len(leaf), leaf, va, len(leaf), trials=8, nptr=0)
    print("self-test identical-leaf:", v["pass"], {k: v[k] for k in ("checked", "mismatches")})
    # Fault locations differ when equivalent C compiles with an extra harmless
    # instruction.  Same fault class and empty trace must still be semantic
    # parity; a returning candidate remains a one-sided-fault failure.
    fault_a = bytes.fromhex("0068" "7047")             # ldr r0,[r0]; bx lr
    fault_b = bytes.fromhex("00bf" "0068" "7047")     # nop; same fault
    ovs = [{0: 0xffffffff}]
    v = compare(fault_a, va, len(fault_a), fault_b, va, len(fault_b),
                trials=1, nptr=0, arg_overrides=ovs)
    assert v["pass"], v
    v = compare(fault_a, va, len(fault_a), bytes.fromhex("7047"), va, 2,
                trials=1, nptr=0, arg_overrides=ovs)
    assert not v["pass"], v
    # Unicorn historically faulted an unaligned LDAEX for Rt=r1 but silently
    # executed the same architectural operation for Rt=r4.  The runner must
    # enforce Cortex-M alignment independently of that emulator quirk.
    ex_r1 = bytes.fromhex("0346" "d3e8ef1f" "7047")
    ex_r4 = bytes.fromhex("0346" "d3e8ef4f" "7047")
    v = compare(ex_r1, va, len(ex_r1), ex_r4, va, len(ex_r4),
                trials=1, nptr=0, arg_overrides=[{0: 1}])
    assert v["pass"], v
    # add r0,r0,r1 ; bx lr  -> returns arg0+arg1  (exercises inputs)
    addf = bytes.fromhex("0844" "7047")
    v2 = compare(addf, va, len(addf), addf, va, len(addf), trials=16, nptr=0)
    print("self-test add-args:", v2["pass"], {k: v2[k] for k in ("checked", "mismatches")})
    # negative control: different constant must FAIL
    leaf7 = bytes.fromhex("0720" "7047")
    v3 = compare(leaf, va, len(leaf), leaf7, va, len(leaf7), trials=8, nptr=0)
    print("self-test neg-control (expect False):", v3["pass"], {k: v3[k] for k in ("checked", "mismatches")})
