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
import os
import hashlib
import os
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
ORACLE_TRAMPOLINE = RETURN_MAGIC + 0x100

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

def _gpr_index(name):
    """Map Capstone's ARM aliases to the r0-r12 indices used by REG."""
    name = name.strip().lower()
    aliases = {"sb": 9, "sl": 10, "fp": 11, "ip": 12}
    if name in aliases:
        return aliases[name]
    if name.startswith("r") and name[1:].isdigit():
        value = int(name[1:])
        return value if 0 <= value < len(REG) else None
    return None


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

def _terminal_key(state):
    """Strict semantic prefix identity through a production-noreturn call."""
    if not state.get("terminal"):
        return None
    return (state.get("terminal_call_ordinal"),
            state.get("terminal_event_count"),
            state.get("terminal_prefix_hash"))


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
            memory_overrides=None, absolute_memory_overrides=None,
            stack_initial_words=None,
            pointer_read_transitions=None,
            terminal_targets=None, terminal_ordinal=None,
            detect_repeated_terminal=False, oracle_overrides=None,
            call_arities=None, call_arity_by_target=None,
            call_float_arities=None, call_float_arity_by_target=None,
            call_return_kinds=None, call_return_kind_by_target=None,
            oracle_memory_writes=None, oracle_memory_copies=None,
            normalized_stack_pointer_calls=None,
            stack_objects=None,
            fp_arg_overrides=None, initial_xpsr=0):
        """Run one trial. Returns dict(state) or {'error':...}.
        stop_events>0: stop after that many side-effect events (for non-returning
        supervisor loops — we compare the ordered event-trace prefix instead of a
        return value, which is robust to GCC-vs-original instructions-per-loop)."""
        uc = self._new_uc()
        # place function body at its VA
        uc.mem_write(self.va, self.body)
        # External calls return through a real Thumb BX LR instruction inside
        # the same emulation run.  Stopping/restarting Unicorn at every oracle
        # boundary can corrupt hidden Thumb execution state (notably ITSTATE)
        # long after the call has returned.
        uc.mem_write(ORACLE_TRAMPOLINE, bytes.fromhex("7047"))
        # seed RAM + scratch identically per trial
        uc.mem_write(RAM_BASE, _prng_fill(b"ram" + struct.pack("<I", scratch_seed), RAM_SIZE))

        # registers
        for i, r in enumerate(REG):
            uc.reg_write(r, 0)
        for i in range(4):
            uc.reg_write(REG[i], args[i] & 0xffffffff)
        # Reviewed architectural-mode fixture. IPSR is the low exception-number
        # field of xPSR: zero is thread mode, nonzero is handler mode.
        uc.reg_write(UC_ARM_REG_XPSR, int(initial_xpsr) & 0xffffffff)
        # CFG-directed pointee inputs. Each item is (arg_index, byte_offset,
        # bytes); applying it before hooks means test setup is not an observed
        # side effect. Both original and candidate receive identical memory.
        for ai, off, data in (memory_overrides or ()):
            address = ((args[ai] & 0xffffffff) + off) & 0xffffffff
            uc.mem_write(address, bytes(data))
        # Function-specific MMIO/PPB fixtures.  These are setup state, applied
        # before observation hooks exactly like argument-relative overrides.
        for address, data in (absolute_memory_overrides or ()):
            page = address & ~0xFFF
            try:
                uc.mem_map(page, 0x1000)
            except UcError:
                pass
            uc.mem_write(address, bytes(data))
        read_transitions = []
        for ai, pointer_off, target_off, ordinal, value in (pointer_read_transitions or ()):
            owner = int.from_bytes(uc.mem_read(
                ((args[ai] & 0xffffffff) + pointer_off) & 0xffffffff, 4), "little")
            read_transitions.append({"address": (owner + target_off) & 0xffffffff,
                                     "ordinal": ordinal, "value": value & 0xffffffff,
                                     "count": 0})
        # seed VFP s0..s15 identically (float args + float-return coverage)
        fseed = _prng_fill(b"vfp" + struct.pack("<I", scratch_seed), 64)
        for i, sr in enumerate(SREG):
            try:
                uc.reg_write(sr, struct.unpack_from("<I", fseed, i * 4)[0])
            except UcError:
                break
        for i, value in (fp_arg_overrides or {}).items():
            if 0 <= i < len(SREG):
                uc.reg_write(SREG[i], int(value) & 0xffffffff)
        uc.reg_write(UC_ARM_REG_SP, STACK_TOP)
        uc.reg_write(UC_ARM_REG_LR, RETURN_MAGIC | 1)
        # Reviewed compiler-local pre-state.  An uninitialized C object has a
        # symbolic incoming value, but its concrete address changes when the
        # compiler chooses a different frame layout.  Seed that value before
        # observation; subsequent byte/word mutations and every emitted
        # non-stack side effect remain compared at full width.
        for offset, value in (stack_initial_words or ()):
            uc.mem_write(STACK_TOP + offset,
                         (int(value) & 0xffffffff).to_bytes(4, "little"))
        for _object_id, offset, payload in (stack_objects or ()):
            uc.mem_write(STACK_TOP + int(offset), bytes(payload))

        state = {"ncalls": 0, "returned": False, "events": [],
                 "call_targets": [], "call_event_positions": [],
                 "call_arities_used": [], "call_float_arities_used": [],
                 "call_return_kinds_used": [],
                 "next_call_indirect": False}
        if read_transitions:
            def _reviewed_read_transition(uc, access, address, size, value, ud):
                for transition in read_transitions:
                    if address == transition["address"]:
                        transition["count"] += 1
                        if transition["count"] == transition["ordinal"]:
                            uc.mem_write(address, transition["value"].to_bytes(4, "little"))
            uc.hook_add(UC_HOOK_MEM_READ, _reviewed_read_transition)
        fstart, fend = self.va, self.va + self.size

        class _ExternalBoundary(Exception):
            """Abort Unicorn before it executes an oracle-boundary opcode."""
            pass

        # ordered event trace: every non-stack memory write + every call marker.
        # Stack writes (register save/restore/spill) are an implementation
        # detail, not observable behavior, so they are excluded.
        stack_lo = STACK_TOP - 0x9000
        stack_hi = STACK_TOP + 0x100

        def _stack_object_pointer(value, include_content=False, content_limit=None):
            """Return reviewed object identity for a pointer, never generic stack.

            The half-open object ranges are declared by the caller relative to
            entry SP. Content begins at the referenced interior offset: bytes
            before an interior pointer are outside that call's pointee region
            (notably response+4 passed to memset).
            """
            for object_id, offset, payload in (stack_objects or ()):
                base = STACK_TOP + int(offset)
                size = len(payload)
                if base <= value < base + size:
                    key = ("SO", object_id, value - base, size)
                    if include_content:
                        count = size - (value - base)
                        if content_limit is not None and 0 < content_limit < count:
                            count = content_limit
                        key += (bytes(uc.mem_read(value, count)),)
                    return key
            return None

        def _call_event(index, target):
            """Record the observable register ABI at an external boundary.

            Call order alone is insufficient: a reconstruction can call the
            right oracle while silently dropping or changing live arguments.
            r0-r3 are the fixed AAPCS argument registers and are independent
            of compiler-specific stack-frame layout, so compare them exactly.
            """
            if call_arities and index < len(call_arities):
                arity = call_arities[index]
            elif call_arity_by_target is not None:
                arity = call_arity_by_target.get(target & ~1, 4)
            else:
                arity = 4
            state["call_arities_used"].append(arity)
            values = [int(uc.reg_read(REG[i])) & 0xffffffff for i in range(arity)]
            for ai, value in enumerate(values):
                limit = values[ai + 1] if ai + 1 < len(values) else None
                identity = _stack_object_pointer(value, include_content=True,
                                                   content_limit=limit)
                if identity is not None:
                    values[ai] = identity
            for ai in ((normalized_stack_pointer_calls or {}).get(index, ())):
                if ai < len(values) and stack_lo <= values[ai] < stack_hi:
                    values[ai] = 0xffff0000 | ai
            if call_float_arities and index < len(call_float_arities):
                float_arity = call_float_arities[index]
            elif call_float_arity_by_target is not None:
                float_arity = call_float_arity_by_target.get(target & ~1, 0)
            else:
                float_arity = 0
            state["call_float_arities_used"].append(float_arity)
            if call_return_kinds and index < len(call_return_kinds):
                return_kind = call_return_kinds[index]
            elif call_return_kind_by_target is not None:
                return_kind = call_return_kind_by_target.get(target & ~1, "i32")
            else:
                return_kind = "i32"
            state["call_return_kinds_used"].append(return_kind)
            float_values = [int(uc.reg_read(SREG[i])) & 0xffffffff
                            for i in range(float_arity)]
            indirect_target = ((target & ~1) if state.pop("next_call_indirect", False)
                               else None)
            return ("C", index, *values, "F", *float_values,
                    "T", indirect_target)
        def _mw(uc, access, address, size, value, ud):
            if not (stack_lo <= address < stack_hi):
                pointer_identity = _stack_object_pointer(value)
                state["events"].append(("W", address & 0xffffffff, size,
                                        pointer_identity if pointer_identity is not None else
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
            if pc == ORACLE_TRAMPOLINE:
                return  # execute the mapped BX LR normally
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
                # Unicorn 2.x can leak ITSTATE past a completed IT block when
                # the next basic block contains a conditional branch (minimal
                # reproducer: ITT LT; MOVLT; STRLT; CMP; BEQ; LDR).  End the
                # translation block exactly at the architectural end of every
                # IT block.  Restarting there is generic and sound: ITSTATE is
                # required to be empty at this boundary, while APSR/registers
                # remain intact.
                if state.get("it_end_pc") == pc:
                    state.pop("it_end_pc", None)
                    state["_resume"] = pc | 1
                    uc.emu_stop(); return
                if (ins and ins.mnemonic.startswith("it") and
                        all(c in "te" for c in ins.mnemonic[2:])):
                    end = pc + size
                    for _ in range(len(ins.mnemonic) - 1):
                        nxt = next(_md.disasm(bytes(uc.mem_read(end, 4)), end), None)
                        if nxt is None:
                            break
                        end += nxt.size
                    state["it_end_pc"] = end
                if ins and ins.mnemonic in ("bl", "blx", "bx"):
                    state["next_call_indirect"] = bool(
                        ins.mnemonic in ("blx", "bx") and
                        re.fullmatch(r'(?:r\d+|sb|sl|fp|ip)', ins.op_str.strip()))
                # Zephyr's ARCH_EXCEPT(reason) is an in-body `svc #2` in the
                # shipped image and a named platform-boundary call in readable
                # reconstruction C. Represent both as the same terminal call
                # event, preserving every preceding call/write in the prefix.
                if ins and ins.mnemonic == "svc" and int(ins.op_str.lstrip("#"), 0) == 2:
                    idx = state["ncalls"]
                    state["ncalls"] += 1
                    state["events"].append(_call_event(idx, pc))
                    state["call_targets"].append(pc & ~1)
                    state["call_event_positions"].append(len(state["events"]) - 1)
                    state["terminal"] = True
                    state["terminal_call_ordinal"] = idx
                    state["terminal_event_count"] = len(state["events"])
                    uc.emu_stop(); return
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
                        # Unicorn lacks reliable ARMv8-M LDAEX/STLEX support.
                        # Emulate the architectural word forms symmetrically,
                        # including the local exclusive monitor.
                        if ins.mnemonic in ("ldaex", "ldrex"):
                            rd = _gpr_index(ins.op_str.split(",")[0])
                            if rd is None:
                                return
                            uc.reg_write(REG[rd], int.from_bytes(uc.mem_read(addr, 4), "little"))
                            state["exclusive_addr"] = addr
                            state["_resume"] = (pc + size) | 1
                            uc.emu_stop(); return
                        if ins.mnemonic in ("stlex", "strex"):
                            parts = [x.strip() for x in ins.op_str.split(",")]
                            rd, rs = _gpr_index(parts[0]), _gpr_index(parts[1])
                            if rd is None or rs is None:
                                return
                            ok = state.get("exclusive_addr") == addr
                            if ok:
                                value = int(uc.reg_read(REG[rs])) & 0xffffffff
                                uc.mem_write(addr, value.to_bytes(4, "little"))
                                # Writes performed by Unicorn API calls from a
                                # code hook do not trigger UC_HOOK_MEM_WRITE.
                                # Emit the architectural store explicitly so
                                # exclusive RMW side effects remain observable.
                                if not (stack_lo <= addr < stack_hi):
                                    state["events"].append(("W", addr & 0xffffffff,
                                                            4, value))
                                    if stop_events and len(state["events"]) >= stop_events:
                                        state["capped_events"] = True
                            uc.reg_write(REG[rd], 0 if ok else 1)
                            state.pop("exclusive_addr", None)
                            state["_resume"] = (pc + size) | 1
                            uc.emu_stop(); return
                if ins and ins.mnemonic in ("lda", "ldr") and ins.mnemonic == "lda":
                    mm = re.match(r'r(\d+),\s*\[r(\d+)\]', ins.op_str)
                    if mm:
                        rd, rb = int(mm.group(1)), int(mm.group(2)); addr = uc.reg_read(REG[rb])
                        uc.reg_write(REG[rd], int.from_bytes(uc.mem_read(addr, 4), "little"))
                        state["_resume"] = (pc + size) | 1
                        uc.emu_stop(); return
                # Preserve target identity for data-derived calls/tail jumps.
                # Direct BL/B.W targets differ between original and generated
                # stub layouts and remain order-normalized; register-indirect
                # boundaries are semantic callback/vtable selections.
                if ins and ins.mnemonic in ("bx", "blx") and re.fullmatch(
                        r'(?:r\d+|ip|sb|sl|fp)', ins.op_str.strip()):
                    state["next_boundary_indirect"] = True
                return  # normal in-body execution
            # out of body: a call or tail-branch to another function -> oracle it
            lr = uc.reg_read(UC_ARM_REG_LR)
            idx = state["ncalls"]
            state["ncalls"] += 1
            event = _call_event(idx, pc)
            if state.pop("next_boundary_indirect", False):
                event = (*event, "T", pc & ~1)
            state["events"].append(event)
            state["call_targets"].append(pc & ~1)
            state["call_event_positions"].append(len(state["events"]) - 1)
            if ((terminal_targets and (pc & ~1) in terminal_targets) or
                    (terminal_ordinal is not None and idx == terminal_ordinal)):
                state["terminal"] = True
                state["terminal_call_ordinal"] = idx
                state["terminal_event_count"] = len(state["events"])
                uc.emu_stop(); return
            if (detect_repeated_terminal and len(state["call_targets"]) >= 2 and
                    state["call_targets"][-1] == state["call_targets"][-2]):
                # Candidate panic loops call the same generated stub forever.
                # The first of the repeated pair is the semantic terminal event.
                state["terminal"] = True
                state["terminal_call_ordinal"] = idx - 1
                state["terminal_event_count"] = state["call_event_positions"][-2] + 1
                uc.emu_stop(); return
            if stop_events and len(state["events"]) >= stop_events:
                state["capped_events"] = True; uc.emu_stop(); return
            o0, o1 = _oracle(idx)
            if oracle_overrides and idx in oracle_overrides:
                ov = oracle_overrides[idx]
                if 0 in ov: o0 = ov[0] & 0xffffffff
                if 1 in ov: o1 = ov[1] & 0xffffffff
            for ai, off, data in ((oracle_memory_writes or {}).get(idx, ())):
                base = int(uc.reg_read(REG[ai])) & 0xffffffff
                uc.mem_write(base + off, bytes(data))
            for dst_ai, src_ai, len_ai in ((oracle_memory_copies or {}).get(idx, ())):
                dst = int(uc.reg_read(REG[dst_ai])) & 0xffffffff
                src = int(uc.reg_read(REG[src_ai])) & 0xffffffff
                length = int(uc.reg_read(REG[len_ai])) & 0xffffffff
                uc.mem_write(dst, bytes(uc.mem_read(src, length)))
            uc.reg_write(UC_ARM_REG_R0, o0)
            uc.reg_write(UC_ARM_REG_R1, o1)
            # AAPCS hard-float results are returned in s0/d0, independently of
            # the GPR result registers.  Populate the ABI-selected bank from
            # the same order-keyed oracle.  The candidate receives the return
            # kind observed for the corresponding original call ordinal, so
            # generated stub addresses cannot change oracle semantics.
            return_kind = state["call_return_kinds_used"][-1]
            if return_kind in ("f32", "f64"):
                # Arbitrary hash bits overwhelmingly denote extreme values,
                # NaNs, or infinities and manufacture invalid domains/loop
                # counts that a real floating-point callee would not return.
                # Keep the oracle deterministic while choosing an ordinary
                # finite positive value in [0.5, 1.0).
                f0 = 0x3f000000 | (o0 & 0x007fffff)
                uc.reg_write(SREG[0], f0)
                if return_kind == "f64":
                    # Finite positive double in [0.5, 1.0), using both oracle
                    # words as payload so d0 remains order-dependent.
                    uc.reg_write(SREG[0], o0)
                    uc.reg_write(SREG[1], 0x3fe00000 | (o1 & 0x000fffff))
            # return to caller (LR). If LR is the sentinel this ends the function.
            if (lr & ~1) == (RETURN_MAGIC & ~1):
                state["returned"] = True
                uc.emu_stop(); return
            # Redirect before the external opcode executes.  The mapped BX LR
            # performs an architectural return without leaving this emu_start;
            # target and target+2 instructions are never executed.
            uc.reg_write(UC_ARM_REG_PC, ORACLE_TRAMPOLINE | 1)
            return
        uc.hook_add(UC_HOOK_CODE, _code)

        pc = self.va | 1
        total = 0
        try:
            while True:
                state.pop("_resume", None)
                try:
                    uc.emu_start(pc, 0, 0, max_insns)
                except _ExternalBoundary:
                    pass
                total += 1
                if state.get("returned"):
                    break
                if state.get("capped_events"):
                    break  # collected enough events for a non-returning function
                if state.get("terminal"):
                    break
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
                    # Semantic target identity must survive a later fault.  A
                    # candidate must not be allowed to call the wrong named
                    # dependency merely because both paths subsequently trap.
                    "call_targets_full": list(state["call_targets"]),
                    "call_arities_used": state["call_arities_used"],
                    "call_float_arities_used": state["call_float_arities_used"],
                    "call_return_kinds_used_full": list(state["call_return_kinds_used"]),
                    "call_arities_used_full": list(state["call_arities_used"]),
                    "call_float_arities_used_full": list(state["call_float_arities_used"]),
                    "events_hash": hashlib.sha256(repr(ev).encode()).hexdigest(),
                    "events": list(ev),
                    "fault_off": (uc.reg_read(UC_ARM_REG_PC) - self.va) & 0xffffffff}

        if state.get("alignment_fault"):
            ev = state["events"]
            return {"error": "Unhandled CPU exception",
                    "ncalls": state["ncalls"],
                    "call_targets_full": list(state["call_targets"]),
                    "call_arities_used": state["call_arities_used"],
                    "call_float_arities_used": state["call_float_arities_used"],
                    "call_return_kinds_used_full": list(state["call_return_kinds_used"]),
                    "call_arities_used_full": list(state["call_arities_used"]),
                    "call_float_arities_used_full": list(state["call_float_arities_used"]),
                    "events_hash": hashlib.sha256(repr(ev).encode()).hexdigest(),
                    "events": list(ev),
                    "fault_off": (state["fault_pc"] - self.va) & 0xffffffff}

        r0 = uc.reg_read(UC_ARM_REG_R0)
        r1 = uc.reg_read(UC_ARM_REG_R1)
        try:
            s0 = uc.reg_read(SREG[0]); s1 = uc.reg_read(SREG[1])
        except UcError:
            s0 = s1 = 0
        ev = state["events"]
        terminal_count = state.get("terminal_event_count")
        terminal_events = ev[:terminal_count] if terminal_count else ev
        eh = hashlib.sha256(repr(ev).encode()).hexdigest()
        ph = hashlib.sha256(repr(ev[:stop_events] if stop_events else ev).encode()).hexdigest()
        return {"r0": r0, "r1": r1, "s0": s0, "s1": s1,
                "returned": state["returned"], "prefix_hash": ph,
                "events_hash": eh, "ncalls": state["ncalls"],
                # Keep diagnostics bounded for runaway oracle loops; complete
                # comparison still uses the full hashes/count above.
                "events": ev[:int(os.environ.get("EMU_DIAGNOSTIC_EVENTS", "128"))],
                "call_targets": state["call_targets"][:64],
                # Kept separately from bounded diagnostics: direct-target
                # verification is part of the verdict and therefore may not
                # silently stop after the 64th call.
                "call_targets_full": list(state["call_targets"]),
                "call_return_kinds_used": state["call_return_kinds_used"][:64],
                "call_arities_used": state["call_arities_used"][:64],
                "call_float_arities_used": state["call_float_arities_used"][:64],
                "call_return_kinds_used_full": list(state["call_return_kinds_used"]),
                "call_arities_used_full": list(state["call_arities_used"]),
                "call_float_arities_used_full": list(state["call_float_arities_used"]),
                "nevents": len(ev), "terminal": bool(state.get("terminal")),
                "terminal_call_ordinal": state.get("terminal_call_ordinal"),
                "terminal_event_count": terminal_count,
                "terminal_prefix_hash": hashlib.sha256(repr(terminal_events).encode()).hexdigest(),
                "last_call_event_count": (state["call_event_positions"][-1] + 1
                                          if state["call_event_positions"] else None),
                "last_call_prefix_hash": (hashlib.sha256(
                    repr(ev[:state["call_event_positions"][-1] + 1]).encode()).hexdigest()
                    if state["call_event_positions"] else None)}


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
            memory_overrides=None, absolute_memory_overrides=None,
            pointer_read_transitions=None,
            terminal_targets=None, oracle_overrides=None, call_arities=None,
            call_arity_by_target=None, call_float_arities=None,
            call_float_arity_by_target=None, oracle_memory_writes=None,
            call_return_kinds=None, call_return_kind_by_target=None,
            normalized_stack_pointer_calls=None, fp_arg_overrides=None,
            oracle_memory_copies=None,
            paired_stack_initial_words=None, candidate_direct_target_map=None,
            paired_stack_objects=None,
            initial_xpsr_overrides=None):
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
        amov = (absolute_memory_overrides[t]
                if absolute_memory_overrides and t < len(absolute_memory_overrides) else None)
        prt = (pointer_read_transitions[t]
               if pointer_read_transitions and t < len(pointer_read_transitions) else None)
        run_cap = 5000 if no_return else 200000
        trial_oracles = (oracle_overrides[t]
                         if isinstance(oracle_overrides, (list, tuple)) and t < len(oracle_overrides)
                         else oracle_overrides)
        trial_fp = (fp_arg_overrides[t]
                    if isinstance(fp_arg_overrides, (list, tuple)) and t < len(fp_arg_overrides)
                    else fp_arg_overrides)
        trial_xpsr = (initial_xpsr_overrides[t]
                      if initial_xpsr_overrides and t < len(initial_xpsr_overrides)
                      else 0)
        trial_oracle_writes = (oracle_memory_writes[t]
                               if isinstance(oracle_memory_writes, (list, tuple)) and t < len(oracle_memory_writes)
                               else oracle_memory_writes)
        symbolic_stack_words = [
            int.from_bytes(_prng_fill(
                b"local" + struct.pack("<II", t, i), 4), "little")
            for i in range(len(paired_stack_initial_words or ()))
        ]
        orig_stack_words = [
            (pair[0], symbolic_stack_words[i])
            for i, pair in enumerate(paired_stack_initial_words or ())]
        cand_stack_words = [
            (pair[1], symbolic_stack_words[i])
            for i, pair in enumerate(paired_stack_initial_words or ())]
        symbolic_stack_objects = [
            _prng_fill(b"stack-object" + struct.pack("<II", t, i), int(pair[3]))
            for i, pair in enumerate(paired_stack_objects or ())]
        orig_stack_objects = [
            (pair[0], pair[1], symbolic_stack_objects[i])
            for i, pair in enumerate(paired_stack_objects or ())]
        cand_stack_objects = [
            (pair[0], pair[2], symbolic_stack_objects[i])
            for i, pair in enumerate(paired_stack_objects or ())]
        a = ro.run(t, args, t, max_insns=run_cap, stop_events=se, memory_overrides=mov,
                   absolute_memory_overrides=amov,
                   stack_initial_words=orig_stack_words,
                   stack_objects=orig_stack_objects,
                   pointer_read_transitions=prt,
                   terminal_targets=terminal_targets, oracle_overrides=trial_oracles,
                   call_arities=call_arities,
                   call_arity_by_target=call_arity_by_target,
                   call_float_arities=call_float_arities,
                   call_float_arity_by_target=call_float_arity_by_target,
                   call_return_kinds=call_return_kinds,
                   call_return_kind_by_target=call_return_kind_by_target,
                   oracle_memory_writes=trial_oracle_writes,
                   oracle_memory_copies=oracle_memory_copies,
                   normalized_stack_pointer_calls=normalized_stack_pointer_calls,
                   fp_arg_overrides=trial_fp, initial_xpsr=trial_xpsr)
        # candidate emulated at its own VA but identical inputs/scratch
        b = rc.run(t, args, t, max_insns=run_cap, stop_events=se, memory_overrides=mov,
                   absolute_memory_overrides=amov,
                   stack_initial_words=cand_stack_words,
                   stack_objects=cand_stack_objects,
                   pointer_read_transitions=prt,
                   terminal_ordinal=(a.get("terminal_call_ordinal")
                                     if a.get("terminal") else None),
                   detect_repeated_terminal=False, oracle_overrides=trial_oracles,
                   call_arities=a.get("call_arities_used_full", call_arities),
                   call_float_arities=a.get("call_float_arities_used_full", call_float_arities),
                   call_return_kinds=a.get("call_return_kinds_used_full", call_return_kinds),
                   oracle_memory_writes=trial_oracle_writes,
                   oracle_memory_copies=oracle_memory_copies,
                   normalized_stack_pointer_calls=normalized_stack_pointer_calls,
                   fp_arg_overrides=trial_fp, initial_xpsr=trial_xpsr)
        # Generated direct-call stubs move with candidate code layout.  When
        # the compiler exposed an original-VA symbol, compare that semantic
        # identity by call ordinal so swapping same-ABI callees is observable.
        identity_bad = None
        for ci, cand_target in enumerate(b.get("call_targets_full", ())):
            semantic = (candidate_direct_target_map or {}).get(cand_target & ~1)
            if semantic is not None:
                actuals = a.get("call_targets_full", ())
                actual = actuals[ci] if ci < len(actuals) else None
                if actual is None or (actual & ~1) != semantic:
                    identity_bad = (ci, actual, semantic)
                    break
        if identity_bad is not None:
            checked += 1
            mism.append((t, "direct-target", identity_bad))
            continue
        if a.get("terminal"):
            # A readable noreturn declaration can still compile as BL followed
            # by an epilogue instead of a tail branch. If the matching ordinal
            # is the candidate's final call and it immediately returns without
            # another side effect, that call is the semantic terminal.
            ordinal = a.get("terminal_call_ordinal")
            if (not b.get("terminal") and b.get("returned") and
                    ordinal is not None and b.get("ncalls") == ordinal + 1 and
                    b.get("last_call_event_count") == b.get("nevents")):
                b["terminal"] = True
                b["terminal_call_ordinal"] = ordinal
                b["terminal_event_count"] = b.get("last_call_event_count")
                b["terminal_prefix_hash"] = b.get("last_call_prefix_hash")
            checked += 1
            ka = _terminal_key(a)
            kb = _terminal_key(b)
            if not b.get("terminal") or ka != kb:
                mism.append((t, "terminal-prefix", ka, kb, b.get("returned")))
            continue
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
                first = next(((i, x, y) for i, (x, y) in
                              enumerate(zip(a.get("events", ()), b.get("events", ())))
                              if x != y), None)
                mism.append((t, "prefix", a["nevents"], b["nevents"], first))
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
                    mism.append((t, "fault", a if os.environ.get("BLE_TRACE_DIAG") else sa,
                                 b if os.environ.get("BLE_TRACE_DIAG") else sb))
            else:
                mism.append((t, "one-sided-fault",
                             (a.get("error"), a.get("fault_off"), a.get("ncalls"),
                              a.get("call_targets_full")),
                             (b.get("error"), b.get("fault_off"), b.get("ncalls"),
                              b.get("call_targets_full"))))
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
    assert [_gpr_index(x) for x in ("r9", "sb", "sl", "fp", "ip")] == [9, 9, 10, 11, 12]
    va = 0x50000
    # leaf: movs r0,#5 ; bx lr   -> returns constant 5
    leaf = bytes.fromhex("0520" "7047")
    v = compare(leaf, va, len(leaf), leaf, va, len(leaf), trials=8, nptr=0)
    print("self-test identical-leaf:", v["pass"], {k: v[k] for k in ("checked", "mismatches")})
    # Absolute setup is symmetric and occurs before write tracing.  Identical
    # loads must pass, while changing only the fixture must change the result.
    load = bytes.fromhex("0068" "7047")              # ldr r0,[r0]; bx lr
    fixture_addr = SCRATCH + 0x7000
    abs11 = [[(fixture_addr, (11).to_bytes(4, "little"))]]
    v = compare(load, va, len(load), load, va, len(load), trials=1, nptr=0,
                arg_overrides=[{0: fixture_addr}], absolute_memory_overrides=abs11)
    assert v["pass"], v
    runner = Runner(va, len(load), load)
    common = dict(seed=0, args=[fixture_addr, 0, 0, 0], scratch_seed=0)
    got11 = runner.run(**common, absolute_memory_overrides=abs11[0])
    got22 = runner.run(**common, absolute_memory_overrides=[
        (fixture_addr, (22).to_bytes(4, "little"))])
    assert got11["r0"] == 11 and got22["r0"] == 22, (got11, got22)
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
    # External-call arguments are semantic side effects too.  Both functions
    # call the same target in the same order, but r0=1 versus r0=2 must fail.
    call_r0_1 = bytes.fromhex("00b5" "0120" "fff7feff" "00bd")
    call_r0_2 = bytes.fromhex("00b5" "0220" "fff7feff" "00bd")
    vc = compare(call_r0_1, va, len(call_r0_1), call_r0_2, va, len(call_r0_2),
                 trials=1, nptr=0)
    assert not vc["pass"], vc
    # Target identity remains observable when both implementations fault after
    # the call.  Previously fault result dictionaries discarded call targets,
    # allowing this wrong-dependency candidate to pass.
    call_then_fault_a = bytes.fromhex("00b5" "00f005f8" "00de" "00bd")
    call_then_fault_b = bytes.fromhex("00b5" "00f007f8" "00de" "00bd")
    vf = compare(call_then_fault_a, va, len(call_then_fault_a),
                 call_then_fault_b, va, len(call_then_fault_b), trials=1,
                 nptr=0, candidate_direct_target_map={va + 0x14: va + 0x14})
    assert not vf["pass"], vf
    # An external helper may begin with ordinary load/store instructions.  A
    # code hook must stop before executing any of them; otherwise Unicorn can
    # advance through the helper and report each halfword as another boundary.
    # The 8-byte caller below BLs to an adjacent 8-byte store helper.
    ext_blob = bytes.fromhex(
        "00b500f005f800bd" "0000000000000000"
        "014b186000207047" "34a00020")
    ext_run = Runner(va, 8, ext_blob).run(0, [0x12345678, 0, 0, 0], 0)
    assert ext_run["returned"] and ext_run["ncalls"] == 1, ext_run
    assert ext_run["call_targets"] == [va + 0x10], ext_run
    assert not any(e[0] == "W" for e in ext_run["events"]), ext_run
    # Negative control for continuation folding: two legitimate BL sites call
    # distinct adjacent two-byte helpers.  Their caller LRs differ, so both
    # boundaries must remain observable even though targets are only +2 apart.
    adjacent_blob = bytes.fromhex(
        "00b500f005f800f004f800bd" "00000000" "70477047")
    adjacent_run = Runner(va, 12, adjacent_blob).run(0, [0, 0, 0, 0], 0)
    assert adjacent_run["returned"] and adjacent_run["ncalls"] == 2, adjacent_run
    assert adjacent_run["call_targets"] == [va + 0x10, va + 0x12], adjacent_run
    # Minimal form of the Unicorn ITSTATE leak from FUN_0008712e/77914, after
    # an external oracle return.  ITT LT; MOV; STR followed by CMP; BEQ caused
    # Unicorn to predicate the later LDR too.  The generic IT-end TB boundary
    # must make the byte store use the saved pointer, not stale r3=0x8b.
    it_resume = bytes.fromhex(
        "02b5054600f010f8" "0124431c" "bcbf8b232b60"
        "002c00d0009b00221a70" "02bd") + bytes(8)
    it_run = Runner(va, 0x1e, it_resume).run(
        0, [SCRATCH + 0x100, SCRATCH + 0x200, 0, 0], 0)
    assert it_run["returned"] and it_run["ncalls"] == 1, it_run
    assert ("W", SCRATCH + 0x100, 4, 0x8b) in it_run["events"], it_run
    assert ("W", SCRATCH + 0x200, 1, 0) in it_run["events"], it_run
    assert not any(e[0] == "W" and e[1] == 0x8b for e in it_run["events"]), it_run
    # Indirect callback identity is semantic.  Equal BX targets pass, while a
    # wrapper that loads the callback from the wrong argument must fail even
    # when call count and register arguments otherwise match.
    bx_r0 = bytes.fromhex("0047")
    bx_r1 = bytes.fromhex("0847")
    ind_ovs = [{0: 0x00080001, 1: 0x00081001}]
    vi = compare(bx_r0, va, len(bx_r0), bx_r0, va, len(bx_r0),
                 trials=1, nptr=0, arg_overrides=ind_ovs)
    assert vi["pass"], vi
    vi = compare(bx_r0, va, len(bx_r0), bx_r1, va, len(bx_r1),
                 trials=1, nptr=0, arg_overrides=ind_ovs)
    assert not vi["pass"], vi
    # An uninitialized word local may move when saved-register choices change.
    # Seed one symbolic word at the reviewed offsets and compare the complete
    # word that each function publishes.  This is identity, not padding
    # masking: changing the initialized low byte or explicitly clearing the
    # upper bytes must still fail.
    local_orig = bytes.fromhex(
        "00b5" "81b0" "0021" "8df80010" "0099" "0160" "01b0" "00bd")
    local_cand = bytes.fromhex(
        "10b5" "81b0" "0021" "8df80010" "0099" "0160" "01b0" "10bd")
    local_low_bad = bytes.fromhex(
        "10b5" "81b0" "0121" "8df80010" "0099" "0160" "01b0" "10bd")
    local_upper_bad = bytes.fromhex(
        "10b5" "81b0" "0021" "0091" "8df80010" "0099" "0160" "01b0" "10bd")
    local_args = [{0: SCRATCH + 0x1000}]
    local_contract = [(-8, -12)]
    vl = compare(local_orig, va, len(local_orig), local_cand, va, len(local_cand),
                 trials=1, nptr=0, arg_overrides=local_args,
                 paired_stack_initial_words=local_contract)
    assert vl["pass"], vl
    vl = compare(local_orig, va, len(local_orig), local_low_bad, va,
                 len(local_low_bad), trials=1, nptr=0,
                 arg_overrides=local_args,
                 paired_stack_initial_words=local_contract)
    assert not vl["pass"], vl
    vl = compare(local_orig, va, len(local_orig), local_upper_bad, va,
                 len(local_upper_bad), trials=1, nptr=0,
                 arg_overrides=local_args,
                 paired_stack_initial_words=local_contract)
    assert not vl["pass"], vl
