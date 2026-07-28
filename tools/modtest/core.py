"""Golden-vector test core.

THE ORACLE IS THE SHIPPED IMAGE.  Every expectation in this harness is produced
by emulating the ORIGINAL firmware bytes, read out of app_update.bin /
netcore_image.bin at the function's real VA, under a fully-specified fixture.
No expectation is ever taken from a reconstruction, so a test cannot pass by
agreeing with our own mistake.

The unit of comparison is the SIDE-EFFECT KEY produced by tools/parity/emu.py:

    (ABI return value, returned flag, call count, ordered event-trace hash)

where the event trace contains, in order, every nRF5340 MMIO read, every
non-stack memory write, and every external call together with its AAPCS
argument registers.  Stack traffic is excluded because register spill layout is
not observable behaviour.

WHAT IS DIFFERENT FROM tools/cfg_verify.py, and why this exists:

  * cfg_verify derives its cases by taint-tracking which ARGUMENT a branch
    selector derives from.  our_boot_bringup.md section 51.1.1 measured the
    consequence: `update_imu_mode` shipped a transposed log-format pointer, and
    cfg_verify returned `PASS cases=4` before AND after the repair, and PASSed
    again with EVERY log pointer in the file replaced by garbage -- because
    every log call is guarded by a GLOBAL (`LOG_LEVEL` at 0x2000230c), and a
    predicate that derives from memory is outside cfg_verify's model.  The
    blind spot is not "small integers" and not "floats"; it is
    ANY BRANCH WHOSE SELECTOR IS NOT DERIVED FROM AN ARGUMENT.
  * This harness therefore (a) treats absolute memory -- globals and MMIO --
    as a first-class fixture dimension, and (b) MEASURES instruction coverage
    on the shipped bytes, so an unreached subtree is visible as a number
    instead of being invisible by construction.

A green result here is worth exactly as much as its coverage figure and its
mutation kill rate.  Both are reported with every run, and neither is optional.
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import struct
import subprocess
import sys
import tempfile
from contextlib import contextmanager

_TOOLS = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _TOOLS not in sys.path:
    sys.path.insert(0, _TOOLS)
REPO = os.path.dirname(_TOOLS)

from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_MCLASS  # noqa: E402
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE  # noqa: E402

import extract as app_extract          # noqa: E402
import net_extract                     # noqa: E402
from parity import emu                 # noqa: E402
from parity import recon               # noqa: E402

_MD = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
_MD.detail = True

VECTOR_DIR = os.path.join(REPO, "recon", "tests", "vectors")


# --------------------------------------------------------------------------
# core context: how to read the shipped image, and what size a function is
# --------------------------------------------------------------------------

_CTX = {}


def core_ctx(core):
    if core in _CTX:
        return _CTX[core]
    import g1_paths
    if core == "app":
        sizes = {f["entry"]: f["size"]
                 for f in g1_paths.load_catalog("classified.json")["functions"]}
        ctx = dict(read=app_extract.func_bytes_padded, rawread=app_extract.read,
                   code_base=emu.CODE_BASE, sizes=sizes)
    else:
        funcs = g1_paths.load_catalog("net_funcs.json")["functions"]
        ctx = dict(read=net_extract.func_bytes_padded, rawread=net_extract.read,
                   code_base=emu.NET_CODE_BASE,
                   sizes={f["entry"]: f["size"] for f in funcs})
    # Function entry addresses, needed by the CFG walker to know where the
    # NEXT function begins so a linear scan cannot bleed into it.
    catalog = "app_funcs.json" if core == "app" else "net_funcs.json"
    ctx["entries"] = {f["entry"] & ~1
                      for f in g1_paths.load_catalog(catalog)["functions"]}
    _CTX[core] = ctx
    return ctx


def image_digest(core):
    """sha256 of the shipped image the expectations came from."""
    blob = app_extract._blob() if core == "app" else net_extract._blob()
    return hashlib.sha256(blob).hexdigest()


# --------------------------------------------------------------------------
# coverage: which instructions of the SHIPPED function actually ran
# --------------------------------------------------------------------------

_TERMINAL = ("bx",)
_UNCOND = {"b", "b.w"}
_COND = {"bne", "beq", "bcs", "bcc", "bmi", "bpl", "bvs", "bvc", "bhi", "bls",
         "bge", "blt", "bgt", "ble", "cbz", "cbnz"}


def cfg_instructions(core, va, size):
    """CFG-reachable instruction addresses of the original function.

    This is the coverage DENOMINATOR.  It is a BFS from the entry that follows
    branches and stops at returns, at the next function's entry, and at an
    unresolved computed branch.  AGENTS.md finding #2 is the reason a linear
    scan is not used: Ghidra folds trailing rodata tables into the function
    symbol, and disassembling a data table produces phantom instructions that
    would DEFLATE the coverage ratio into meaninglessness.

    Returns (addresses, unresolved_indirect) so the caller can report how much
    of the function the denominator itself could not see.  A `tbb`/`tbh` or a
    register branch ends a path; its targets are counted only if some fixture
    actually reaches them, and they are then added to the denominator by
    `Coverage.merge`, never silently dropped.
    """
    ctx = core_ctx(core)
    blob = ctx["rawread"](va & ~1, size + 64)
    base = va & ~1
    seen = set()
    work = [0]
    unresolved = 0
    while work:
        off = work.pop()
        if off in seen or off < 0 or off >= size:
            continue
        for insn in _MD.disasm(blob[off:size], base + off):
            offset = insn.address - base
            if offset > 0 and (base + offset) in ctx["entries"]:
                break
            if offset in seen:
                break
            seen.add(offset)
            mnemonic = insn.mnemonic
            if mnemonic in _TERMINAL or (mnemonic == "pop" and "pc" in insn.op_str):
                break
            # `startswith("bl")` is WRONG here: it also matches `blt`, `bls`
            # and `ble`, the signed/unsigned conditional branches.  Treating
            # them as calls made the walker fall through instead of following
            # the branch, which both deflated the coverage denominator and (in
            # true_extent) stopped the extent one instruction short of the
            # function's own tail block.  Measured on `fuel_gauge_update`.
            if mnemonic.split(".")[0] in ("bl", "blx"):
                continue                        # call: falls through
            target = None
            if "#" in insn.op_str:
                try:
                    target = int(insn.op_str.split("#")[-1], 0) - base
                except ValueError:
                    target = None
            head = mnemonic.split(".")[0]
            if head in _UNCOND or mnemonic in _UNCOND:
                if target is not None and 0 <= target < size:
                    work.append(target)
                elif target is None:
                    unresolved += 1
                break
            if head in _COND:
                if target is not None and 0 <= target < size:
                    work.append(target)
                elif target is None:
                    unresolved += 1
                continue
            if mnemonic in ("tbb", "tbh") or (
                    mnemonic in ("mov", "add") and insn.op_str.startswith("pc")):
                unresolved += 1
                break
    return {base + o for o in seen}, unresolved


def true_extent(core, va, ghidra_size, max_scan=0x2000):
    """Extend an UNDER-reported Ghidra size to cover the function's own tail.

    Ghidra ends some function symbols before a shared tail block or a switch
    handler the function branches into (tools/truesize.py exists for exactly
    this).  The emulator treats any PC outside [va, va+size) as an external
    call, so an under-reported size turns the function's own basic block into
    a phantom callee -- and the golden vector then records that phantom.

    MEASURED: `fuel_gauge_update` is catalogued at 1,064 bytes, ending at
    0x10F40, but branches `blt.w #0x10fbe` -- 126 bytes past the end.  Under
    the catalogued size the golden run recorded 60 "calls" to 0x10FBE and a
    fault, and the reconstruction (which has that block inline) returned after
    5 calls.  That reads as a reconstruction defect and is not one.

    The walk NEVER crosses the next catalogued function entry, and it only
    ever EXTENDS.  An over-reported size is a different problem (AGENTS.md
    finding #2, Ghidra data inflation) and is handled by the coverage
    denominator, not here: trailing rodata is simply never executed.
    """
    ctx = core_ctx(core)
    base = va & ~1
    following = sorted(e for e in ctx["entries"] if e > base)
    limit = min(following[0] - base, max_scan) if following else max_scan
    if limit <= ghidra_size:
        return ghidra_size
    blob = ctx["rawread"](base, limit)
    end = ghidra_size
    seen = set()
    work = [0]
    while work:
        off = work.pop()
        if off in seen or off < 0 or off >= limit:
            continue
        for insn in _MD.disasm(blob[off:limit], base + off):
            offset = insn.address - base
            if offset > 0 and (base + offset) in ctx["entries"]:
                break
            if offset in seen:
                break
            seen.add(offset)
            end = max(end, offset + insn.size)
            mnemonic = insn.mnemonic
            if mnemonic in _TERMINAL or (mnemonic == "pop" and "pc" in insn.op_str):
                break
            if mnemonic.split(".")[0] in ("bl", "blx"):
                continue
            target = None
            if "#" in insn.op_str:
                try:
                    target = int(insn.op_str.split("#")[-1], 0) - base
                except ValueError:
                    target = None
            head = mnemonic.split(".")[0]
            if head in _UNCOND or mnemonic in _UNCOND:
                if target is not None and 0 <= target < limit:
                    work.append(target)
                break
            if head in _COND:
                if target is not None and 0 <= target < limit:
                    work.append(target)
                continue
            if mnemonic in ("tbb", "tbh"):
                break
    return end


#: Bytes of a stack record captured at a call boundary.  **DEFAULT 0 --
#: DISABLED.**  Enable with MODTEST_STACK_ARG_WINDOW=48.
#:
#: This is a measured retreat, recorded rather than hidden.  The capture closes
#: a large real blind spot -- `ipc_send_len_prefixed_packet` went from a 13 %
#: mutation kill rate at 100 % coverage to 100 % -- but making it SOUND needs
#: an object-extent model, and four successive corrections were not enough:
#:
#:   1. a fixed window includes the frame's saved registers, whose position
#:      relative to a local differs between compilations
#:      (`ipc_read_u16_field`: 42/43 fixtures failed on BOTH trees);
#:   2. classifying the STORE (`push`/`vpush`/`stmdb sp!` = frame bookkeeping)
#:      fixed that case;
#:   3. a record may hold a pointer to another stack local, whose raw value is
#:      frame layout -- those aligned words are blanked;
#:   4. a capture must only be committed when the call actually happens, or a
#:      run that faults before the call compares a record nobody received;
#:   5. AND STILL: the shipped code may reserve a slot with `push {r1}` while
#:      the reconstruction uses `str r1,[sp,#n]`.  Rule 2 classifies the first
#:      as bookkeeping and the second as content, so `st25dv_read_area_size`
#:      captured nothing on the golden side and four bytes on the candidate's
#:      -- 41/41 fixtures failed, identically on both trees, with byte-identical
#:      event traces.
#:
#: A suite that emits a FALSE FAIL is worse than one with a known blind spot,
#: because it invites a "fix" to correct code.  So this is off by default, the
#: blind spot is restated in the architecture document, and the machinery stays
#: in the tree for whoever builds the extent model.
STACK_ARG_WINDOW = int(os.environ.get("MODTEST_STACK_ARG_WINDOW", "0"))


class _CoverageRunner(emu.Runner):
    """emu.Runner + executed-PC coverage + STACK-RECORD CONTENT at calls.

    THE STACK-RECORD PROBLEM, measured.  A great deal of this firmware builds a
    small record in a stack local and passes its ADDRESS to a callee:

        struct {...} local_20;  local_20.a = 2; ... local_20.e = 7;
        ipc_transport_ops_dispatch(param_1, &local_20, 2, param_2);

    `emu` records the call's argument registers, so the trace contains the
    POINTER; `normalise_events` then replaces it with a frame-origin-independent
    offset. Nothing anywhere observes what is IN the record. Consequence,
    measured on `ipc_send_len_prefixed_packet` -- 100 % instruction coverage,
    41 fixtures, and a mutation kill rate of **13 %**: every perturbation of
    every field constant survived. A suite in that state licenses exactly the
    restructuring it cannot see, which is the failure mode this whole design is
    supposed to prevent.

    THE FIX, and why it is sound.  At every `bl`/`blx` inside the unit, for each
    of r0-r3 that points into the stack window, capture the bytes of
    [ptr, ptr + STACK_ARG_WINDOW) **that this run actually WROTE**. Content is
    keyed by offset from the pointer, so it is independent of frame layout,
    of the order the fields were stored in, and of the widths used to store
    them. Bytes the run never wrote are excluded, which is what keeps
    uninitialised frame padding -- the one thing that legitimately differs
    between two compilations -- out of the comparison.
    """

    def __init__(self, *args, **kwargs):
        # A per-INSTRUCTION Python callback costs more than the emulation it
        # observes.  Coverage is only needed while GENERATING vectors (it is
        # measured on the shipped bytes); replaying a candidate does not use
        # it, so `track_coverage=False` drops the whole-body hook and leaves
        # only the per-call-site hooks, which fire a handful of times per run.
        self.track_coverage = kwargs.pop("track_coverage", True)
        super().__init__(*args, **kwargs)
        self.covered = set()
        self.stack_arg_trace = []
        self.call_sites = set()
        for insn in _MD.disasm(self.body[:self.size], self.va):
            if insn.mnemonic.split(".")[0] in ("bl", "blx"):
                self.call_sites.add(insn.address)

    def _new_uc(self):
        uc = super()._new_uc()
        low, high = self.va, self.va + self.size
        stack_low = emu.STACK_TOP - 0x9000
        stack_high = emu.STACK_TOP + 0x100
        written = set()

        pushed = set()
        classified = {}

        def _write(_uc, _access, address, size, _value, _ud):
            if not (stack_low <= address < stack_high):
                return True
            # REGISTER SAVES ARE NOT POINTEE CONTENT.  A stack pointer argument
            # is captured over a fixed window, and that window runs past the
            # object into the frame's own saved registers -- whose position
            # relative to a local differs between the shipped code and any
            # recompilation.  Measured on `ipc_read_u16_field`: `&local_14` is
            # a 2-byte local, and offsets 2..19 of the window were r4-r7/lr in
            # the shipped frame and something else in the candidate's, which
            # failed 42 of 43 fixtures on BOTH trees.  Classify the store by
            # the instruction performing it: `push` / `stmdb sp!` / `vpush`
            # bytes are frame bookkeeping and never object content.
            pc = int(_uc.reg_read(emu.UC_ARM_REG_PC)) & 0xffffffff
            prologue = classified.get(pc)
            if prologue is None:
                prologue = False
                if low <= pc < high:
                    insn = next(_MD.disasm(bytes(_uc.mem_read(pc, 4)), pc),
                                None)
                    if insn is not None:
                        head = insn.mnemonic.split(".")[0]
                        prologue = (head in ("push", "vpush") or
                                    (head in ("stmdb", "stm", "stmfd") and
                                     "sp!" in insn.op_str))
                # Memoised: code does not change during a run, and a stack
                # write happens on every register spill, so disassembling per
                # write would dominate the emulation cost.
                classified[pc] = prologue
            for offset in range(size):
                if prologue:
                    pushed.add(address + offset)
                else:
                    written.add(address + offset)
                    pushed.discard(address + offset)
            return True
        uc.hook_add(UC_HOOK_MEM_WRITE, _write)

        def _coverage(_uc, address, _size, _ud):
            self.covered.add(address)
        if self.track_coverage:
            uc.hook_add(UC_HOOK_CODE, _coverage, begin=low, end=high - 1)

        def _hook(_uc, address, _size, _ud):
            # Only registered on the function's OWN call sites, so this fires a
            # handful of times per run rather than once per instruction.
            insn = next(_MD.disasm(bytes(_uc.mem_read(address, 4)), address),
                        None)
            # The call-site set comes from a LINEAR disassembly, which can
            # misalign inside a literal pool and name an address that is not a
            # call.  Confirm against the bytes actually being executed.
            # (Measured: without this, `i2c_read_reg16_be` recorded a stack
            # record on a run whose call count was zero, failing 2 of 3
            # fixtures on both trees.)
            if insn is None or insn.mnemonic.split(".")[0] not in ("bl", "blx"):
                return
            ordinal = self._call_seq
            self._call_seq += 1
            record = []
            for index in range(4):
                value = int(_uc.reg_read(emu.REG[index])) & 0xffffffff
                if not (stack_low <= value < stack_high):
                    continue
                present = {offset for offset in range(STACK_ARG_WINDOW)
                           if value + offset in written}
                # A record may hold a POINTER TO ANOTHER STACK LOCAL
                # (`local_20.p = &local_24`).  Its raw value is the frame
                # layout, which differs between the shipped code and any
                # recompilation, so comparing those four bytes manufactures a
                # failure for a correct candidate -- measured: this made
                # `ipc_send_len_prefixed_packet` fail 41/41 on BOTH trees.
                # Blank the word and keep every other field exact.
                pointer_words = set()
                for offset in range(0, STACK_ARG_WINDOW - 3):
                    if (value + offset) & 3:
                        continue
                    if not all((offset + k) in present for k in range(4)):
                        continue
                    word = int.from_bytes(_uc.mem_read(value + offset, 4),
                                          "little")
                    if stack_low <= word < stack_high:
                        pointer_words.update(offset + k for k in range(4))
                content = []
                for offset in sorted(present):
                    if offset in pointer_words:
                        content.append((offset, "P"))
                    else:
                        content.append((offset,
                                        _uc.mem_read(value + offset, 1)[0]))
                if content:
                    record.append((index, tuple(content)))
            if record:
                self.stack_arg_trace.append((ordinal, tuple(record)))
        if STACK_ARG_WINDOW:
            for site in sorted(self.call_sites):
                uc.hook_add(UC_HOOK_CODE, _hook, begin=site, end=site)
        return uc

    def run(self, *args, **kwargs):
        self.stack_arg_trace = []
        self._call_seq = 0
        state = super().run(*args, **kwargs)
        # A capture is taken AT the `bl`, before it executes.  A run that
        # builds a record and then FAULTS at the call has passed that record to
        # nobody, so its content is not observable -- and the shipped code and
        # the reconstruction legitimately fill the record at different points
        # relative to the faulting load.  Keep only captures whose call
        # actually happened, which `ncalls` counts.  (Measured: without this,
        # `i2c_read_reg16_be` failed 2 of 3 fixtures on both trees.)
        calls = int(state.get("ncalls", 0))
        state["stack_args"] = [record for ordinal, record
                               in self.stack_arg_trace if ordinal < calls]
        return state


# --------------------------------------------------------------------------
# fixtures
# --------------------------------------------------------------------------

class Fixture(dict):
    """A completely specified input state.  JSON-serialisable by construction.

    Keys:
      id             human label, stable across regenerations
      args           4 words for r0..r3
      nptr           how many of them make_args would have pointed at SCRATCH
      scratch_seed   seeds RAM and the VFP bank deterministically
      fp             {sN: word} overrides on the VFP argument bank
      abs            [[addr, hex]] absolute memory writes applied BEFORE hooks
                     -- this is the GLOBAL/MMIO dimension cfg_verify has none of
      mem            [[arg_index, offset, hex]] pointee writes
      xpsr           architectural mode (0 = thread, nonzero = handler)
      float_scratch  seed the argument-pointer region with plausible binary32
    """

    @staticmethod
    def make(fid, args, nptr=2, scratch_seed=0, fp=None, abs_mem=None,
             mem=None, xpsr=0, float_scratch=False, oracle=None):
        return Fixture(id=fid, args=[int(a) & 0xffffffff for a in args],
                       nptr=int(nptr), scratch_seed=int(scratch_seed),
                       fp={str(k): int(v) & 0xffffffff
                           for k, v in (fp or {}).items()},
                       abs=[[int(a) & 0xffffffff,
                             bytes(b).hex() if not isinstance(b, str) else b]
                            for a, b in (abs_mem or [])],
                       mem=[[int(i), int(o),
                             bytes(b).hex() if not isinstance(b, str) else b]
                           for i, o, b in (mem or [])],
                       xpsr=int(xpsr), float_scratch=bool(float_scratch),
                       oracle=[[int(i), int(r), int(v) & 0xffffffff]
                               for i, r, v in (oracle or [])])

    def run_kwargs(self):
        oracle = {}
        for index, register, value in self.get("oracle", ()):
            oracle.setdefault(int(index), {})[int(register)] = int(value)
        return dict(
            seed=0,
            args=list(self["args"]),
            scratch_seed=self["scratch_seed"],
            memory_overrides=[(i, o, bytes.fromhex(h))
                              for i, o, h in self.get("mem", ())],
            absolute_memory_overrides=[(a, bytes.fromhex(h))
                                       for a, h in self.get("abs", ())],
            fp_arg_overrides={int(k): v for k, v in self.get("fp", {}).items()},
            oracle_overrides=oracle or None,
            initial_xpsr=self.get("xpsr", 0),
            float_scratch=self.get("float_scratch", False))


# --------------------------------------------------------------------------
# key extraction
# --------------------------------------------------------------------------

def _canon_float32(word):
    if (word & 0x7f800000) == 0x7f800000 and (word & 0x007fffff):
        return 0x7fc00000
    return word


#: emu bounds `state["events"]` for diagnostics; this harness needs the WHOLE
#: list because it recomputes the trace hash after normalising stack pointers.
#: Set before any Runner.run() call.  Traces longer than this fall back to
#: emu's own (unnormalised) hash, and `observable_key` says so in the key.
EVENT_LIMIT = 100000
os.environ.setdefault("EMU_DIAGNOSTIC_EVENTS", str(EVENT_LIMIT))

#: emu's stack window (Runner.run: STACK_TOP - 0x9000 .. STACK_TOP + 0x100).
_STACK_LO = emu.STACK_TOP - 0x9000
_STACK_HI = emu.STACK_TOP + 0x100


def normalise_events(events):
    """Replace stack-frame addresses with offsets from the first one seen.

    WHY.  A pointer to a stack LOCAL passed to a callee is recorded in the
    trace as a raw integer.  Its numeric value is the compiler's frame layout,
    which is codegen, not behaviour -- and it differs between the shipped
    firmware and any recompilation.  Measured on `fuel_gauge_update`: the
    original passes (0x2007EF3C, +4, +8) at call ordinal 2 and the candidate
    passes (0x2007EF48, +4, +8).  Same three consecutive words of the same
    record; different frame origin.

    WHAT IS PRESERVED.  Only the ORIGIN is normalised away.  Each stack address
    becomes its signed delta from the first stack address in the trace, so the
    *relative* structure is compared exactly: passing a different local, or the
    same two locals in the opposite order, or a pointer into the middle of a
    record instead of its head, all still differ.

    WHAT THIS COULD MISS, stated plainly: a candidate whose frame lays out the
    same locals at different RELATIVE offsets while otherwise behaving
    identically will still fail (a false failure, not a false pass), and a
    candidate that happens to reproduce the same relative structure with
    semantically different objects would pass.  The second requires the deltas
    to coincide exactly and is not a class this project has seen.
    """
    anchor = [None]

    def walk(node):
        if isinstance(node, tuple):
            return tuple(walk(x) for x in node)
        if isinstance(node, list):
            return [walk(x) for x in node]
        if isinstance(node, int) and not isinstance(node, bool):
            if _STACK_LO <= node < _STACK_HI:
                if anchor[0] is None:
                    anchor[0] = node
                return ("SP", node - anchor[0])
        return node

    return _sort_independent_write_runs([walk(event) for event in events])


def _sort_independent_write_runs(events):
    """Order-normalise a run of writes to DISTINCT non-MMIO addresses.

    Within this model the only observers are external calls and MMIO accesses.
    Between two of them, the order in which two *different* RAM locations are
    stored is unobservable -- it is instruction scheduling.  Measured on
    `fuel_gauge_update` under the `combo-2-0` fixture: the shipped code stores
    0x20007B70 then 0x20007B74; the reconstruction stores 0x20007B74 then
    0x20007B70. Same addresses, same widths, same values, opposite order.

    STRICT CONDITIONS, so this cannot hide a defect:
      * the run must contain only writes -- any call or MMIO read ends it;
      * every address in the run must be DISTINCT, so no write-after-write to
        the same location is ever reordered;
      * no address may be inside an MMIO window, where ordering IS semantics.
    A wrong value, a wrong address, a missing write or an extra one all still
    change the multiset and therefore still fail.
    """
    out = []
    run = []

    def flush():
        if len(run) > 1:
            addresses = [e[1] for e in run]
            if (len(set(addresses)) == len(addresses) and
                    not any(_is_mmio_address(a) for a in addresses)):
                run.sort(key=repr)
        out.extend(run)
        run.clear()

    for event in events:
        if (isinstance(event, tuple) and event and event[0] == "W" and
                isinstance(event[1], int)):
            run.append(event)
            continue
        flush()
        out.append(event)
    flush()
    return out


def _is_mmio_address(address):
    return isinstance(address, int) and emu._is_nrf53_mmio(address, 1)


def observable_key(state, ret_kind):
    """The pass criterion, in one place.

    Equality of this tuple is what "the reconstruction behaves like the
    shipped firmware on this input" means in this harness.  It is:

      * the ABI return value, and ONLY the registers the ABI defines as the
        result (`void` compares nothing, `i64` compares r0:r1, `f32` compares
        s0 with NaN payload canonicalised);
      * whether the function returned at all;
      * how many external calls it made;
      * the sha256 of the COMPLETE ordered event trace -- every MMIO read,
        every non-stack write with its width and value, every call with its
        AAPCS argument registers, in order.

    Deliberately NOT compared: instruction count, cycle count, code size,
    stack layout, register allocation, the text offset at which a fault
    occurred, and NaN payloads.  Those are codegen, not behaviour.
    """
    events = state.get("events", ())
    if state.get("nevents", len(events)) > len(events):
        # The trace was truncated for diagnostics; normalisation would compare
        # a prefix against a whole, so fall back to emu's own hash and SAY SO
        # in the key, rather than silently comparing less.
        digest = "raw:" + state["events_hash"]
    else:
        digest = hashlib.sha256(
            repr(normalise_events(events)).encode()).hexdigest()
    # Stack-record content observed at call boundaries (see _CoverageRunner).
    # Folded into the same field so an older vector without it still compares
    # equal to itself, and any vector regenerated after this change carries it.
    stack_args = state.get("stack_args")
    if stack_args:
        digest = hashlib.sha256(
            (digest + "|" + repr(stack_args)).encode()).hexdigest()
    if "error" in state:
        return {"kind": "fault", "error": state["error"],
                "ncalls": state["ncalls"], "events": digest}
    if ret_kind == "void":
        ret = []
    elif ret_kind == "i64":
        ret = [state["r0"], state["r1"]]
    elif ret_kind == "f32":
        ret = [_canon_float32(state["s0"])]
    elif ret_kind == "f64":
        high = state["s1"]
        ret = ([0, 0x7ff80000]
               if (high & 0x7ff00000) == 0x7ff00000 and
               ((high & 0x000fffff) or state["s0"])
               else [state["s0"], high])
    else:
        ret = [state["r0"]]
    return {"kind": "return", "ret": ret, "returned": bool(state["returned"]),
            "ncalls": state["ncalls"], "events": digest}


# --------------------------------------------------------------------------
# running the original (golden) side
# --------------------------------------------------------------------------

_ABI = {}


def callee_abi(core):
    """Per-callee arity / float arity / return kind, keyed by ORIGINAL VA.

    Without this, `emu` compares FOUR argument registers at every call site
    regardless of the callee's real arity, so r1..r3 holding caller scratch
    make a semantically identical candidate fail.  Measured: every one of
    `opt3001_read_lux_raw`'s 42 cases failed at event 0 -- a call event whose
    return value, call count and everything downstream matched -- purely on
    argument registers above the callee's arity.

    Sourced from tools/cfg_verify.py's `core_ctx`, which derives arity from the
    Ghidra decompilation of the CALLEE plus a reviewed override table.  It is
    imported lazily because it costs the whole catalog stack, and its absence
    degrades to arity 4 rather than failing.
    """
    if core in _ABI:
        return _ABI[core]
    try:
        import cfg_verify
        ctx = cfg_verify.core_ctx(core)
        abi = {"call_arity_by_target": ctx["call_arity_by_target"],
               "call_float_arity_by_target": ctx["call_float_arity_by_target"],
               "call_return_kind_by_target": ctx["call_return_kind_by_target"]}
    except Exception:                                   # noqa: BLE001
        abi = {}
    _ABI[core] = abi
    return abi


def run_original(core, va, size, fixture, ret_kind="i32", max_insns=200000):
    ctx = core_ctx(core)
    body = ctx["read"](va, size, pad=64)
    runner = _CoverageRunner(va & ~1, size, body, ctx["code_base"])
    kwargs = fixture.run_kwargs()
    state = runner.run(max_insns=max_insns, **callee_abi(core), **kwargs)
    return state, runner.covered


# --------------------------------------------------------------------------
# compiling a candidate out of an arbitrary tree
# --------------------------------------------------------------------------

@contextmanager
def _tree_cflags(tree, unit):
    """Point parity/recon.py's include search at THIS tree, not the repo.

    recon.CFLAGS hardcodes two repo-absolute -I entries.  A stage tree carries
    its own generated module headers (stage 03 hoists module-wide externs into
    them), so compiling a stage-09 unit against the repo's headers would be
    testing a chimera.  Swap them for the duration of the compile.
    """
    saved = list(recon.CFLAGS)
    kept = [flag for flag in saved
            if not (flag.startswith("-I") and "/recon/" in flag)]
    dirs = [os.path.dirname(unit.path)] + tree.include_dirs()
    recon.CFLAGS = kept + ["-I" + d for d in dirs]
    try:
        yield
    finally:
        recon.CFLAGS = saved


#: THE UNIT BOUNDARY IS THE FUNCTION, in both trees.
#:
#: This is forced, not chosen.  The golden expectation comes from emulating the
#: shipped bytes of ONE function; every control transfer that leaves those
#: bytes is oracled.  For the candidate to be comparable, exactly the same set
#: of transfers must leave it.  Two failure modes have to be prevented:
#:
#:   * a merged stage-09 TU holds up to 39 functions, and at -Os GCC inlines a
#:     single-caller `static` sibling -- the candidate would then perform inline
#:     what the shipped function does with a `bl`, and the traces cannot align;
#:   * a plain `-fno-inline` is NOT the fix.  Measured on `__ieee754_asinf`:
#:     the reconstruction spells its bit-casts as `static inline float F(...)`,
#:     which are notation, not functions; `-fno-inline` turned all sixteen of
#:     them into real calls (golden ncalls=0, candidate ncalls=16, FAIL 0/5 on
#:     BOTH trees).
#:
#: So: disable the SIZE/CALL-COUNT HEURISTICS, which are what pull a `static`
#: sibling in, and leave `-finline` alone, which is what honours the `inline`
#: keyword.
#: CORRECTION.  Blanket inlining suppression was too broad.  It also stops the
#: compiler inlining a file-local helper that has NO provenance banner -- which
#: is notation, not a shipped function -- so the candidate called helpers the
#: shipped body has inline.  Measured: `__ieee754_atan2f` golden `ncalls = 0`,
#: candidate `ncalls = 5`, FAIL 0/48 on BOTH trees; `__ieee754_expf` 25/37.
#:
#: The precise rule is a property of the SOURCE, not of a compiler flag:
#:   * a BANNER-NAMED function is a separate function in the shipped image and
#:     must remain a call boundary -> `__attribute__((noinline))`, injected by
#:     `_mark_members_noinline`;
#:   * an unbannered file-local helper is spelling and may inline freely.
#: Only the interprocedural transforms that would MERGE or RESHAPE a
#: banner-named function stay as flags.
UNIT_BOUNDARY_CFLAGS = ["-fno-ipa-icf", "-fno-ipa-sra", "-fno-ipa-cp",
                        "-fno-partial-inlining"]


def _definition_span(text, name, start=0):
    """Offset of `name`'s DEFINITION head, or None.  No regex: see
    `_expose_target` for why (154 s of catastrophic backtracking)."""
    cursor = start
    while True:
        index = text.find(name, cursor)
        if index < 0:
            return None
        cursor = index + len(name)
        if index and (text[index - 1].isalnum() or text[index - 1] in "_$"):
            continue
        rest = text[cursor:]
        if not rest.lstrip().startswith("("):
            continue
        # MATCHING close paren, not the first one.  `if (getNewsIndex(a)) {`
        # satisfies "name ( ... ) {" and is not a definition; taking the first
        # `)` matched it and injected an attribute into the middle of another
        # function's body, which broke the whole TU (measured: CCFAIL on
        # `ipc_read_u16_field` and `register_ipc_service_context`).
        open_at = cursor + len(rest) - len(rest.lstrip())
        depth = 0
        close = -1
        for position in range(open_at, min(len(text), open_at + 4000)):
            if text[position] == "(":
                depth += 1
            elif text[position] == ")":
                depth -= 1
                if depth == 0:
                    close = position
                    break
        if close < 0:
            continue
        if not text[close + 1:close + 200].lstrip().startswith("{"):
            continue
        comment_end = text.rfind("*/", 0, index)
        head = max(text.rfind(";", 0, index) + 1,
                   text.rfind("}", 0, index) + 1,
                   text.rfind("{", 0, index) + 1,
                   # `*/` is TWO characters: +1 lands between them and splits
                   # the comment terminator.  Measured: it produced
                   # `*__attribute__((noinline)) /` and broke the whole TU.
                   (comment_end + 2) if comment_end >= 0 else 0)
        declaration = text[head:index].strip()
        # A definition head is a RETURN TYPE.  Anything that opens a statement
        # or an expression is not one.
        # A return type contains no punctuation beyond `*` and `const`.  A
        # head carrying `(`, `)` or `,` is a parameter list, a cast or a
        # continuation -- injecting there produced
        # `__attribute__((noinline)) )` and broke `check_sw0_status`'s TU.
        if (not declaration or
                any(ch in declaration for ch in "=;(),") or
                declaration.split()[0] in ("if", "while", "for", "switch",
                                           "return", "else", "do", "case")):
            continue
        return head, index


_NOINLINE = "__attribute__((noinline)) "


def _mark_members_noinline(text, members, skip):
    """Force every OTHER banner-named function in this TU out of line."""
    count = 0
    for name, _raw, _va in members:
        if name == skip or _NOINLINE in text:
            pass
        span = _definition_span(text, name)
        if span is None:
            continue
        head, _index = span
        if name == skip:
            continue
        if text[head:head + len(_NOINLINE) + 40].lstrip().startswith(
                "__attribute__((noinline))"):
            continue
        text = text[:head] + "\n" + _NOINLINE + text[head:]
        count += 1
    return text, count

#: The firmware was built with arm-zephyr-eabi GCC 12.2.  The host GCC in this
#: environment promotes several C constraint violations to hard errors that
#: GCC 12 reported as warnings, so a source the real build compiles is rejected
#: here.  Measured: `mark_master_or_low_battery_flag` fails to compile in BOTH
#: trees with `error: assignment to 'char *' from 'int'`.  Demoting them is
#: correct -- the question this harness asks is what the code DOES, and the
#: real build already answered whether it compiles.
#: The application TUs include Zephyr headers (`<zephyr/sys_clock.h>`), which
#: the real build supplies and `parity/recon.py`'s freestanding flag set does
#: not.  Measured: `send_response_data_to_ble` and `send_response_data_to_msgqueue`
#: fail to COMPILE without these, on both trees.  The generated `autoconf.h`
#: comes from the reference build named in AGENTS.md.
_NCS = os.path.expanduser("~/ncs251")
ZEPHYR_CFLAGS = [flag for flag in (
    "-I" + os.path.join(_NCS, "zephyr", "include"),
    "-I" + os.path.join(_NCS, "nrf", "include"),
    "-I" + os.path.join(_NCS, "refapp", "build", "zephyr", "include",
                        "generated"),
) if os.path.isdir(flag[2:])]
#: The generated `autoconf.h` is BUILD-SPECIFIC.  Zephyr headers need it
#: (`CONFIG_SYS_CLOCK_TICKS_PER_SEC` and friends), but force-including a
#: FOREIGN build's autoconf would change the codegen of inline Zephyr helpers
#: and could manufacture divergences.  So it is opt-in: set
#: G1_AUTOCONF=<path to the G1 build's autoconf.h>.  Without it, the handful of
#: TUs that include Zephyr headers report CCFAIL, which is visible and honest.
_AUTOCONF = os.environ.get("G1_AUTOCONF")
if _AUTOCONF and os.path.exists(_AUTOCONF):
    ZEPHYR_CFLAGS = ZEPHYR_CFLAGS + ["-imacros", _AUTOCONF]

PERMISSIVE_CFLAGS = ["-Wno-error=int-conversion",
                     "-Wno-error=incompatible-pointer-types",
                     "-Wno-error=implicit-function-declaration",
                     "-Wno-error=implicit-int",
                     "-Wno-error=return-mismatch",
                     "-Wno-error=declaration-missing-parameter-type",
                     "-w"]

_UNDEF_STUB = ('__attribute__((noinline,used,section(".oracle_stubs"))) '
               'unsigned %s(void){return %du;}')


#: Linker fragments that pin DATA symbols to their original addresses.
#:
#: This is not optional and it is not cosmetic.  The symbolized trees spell a
#: global as a NAME (`g_opt3007_chip_ready`), and `recon/symbols/g1_app_globals.ld`
#: is what binds that name to 0x20018da1.  Without the fragment the name is an
#: undefined symbol, the harness's own stub generator turns it into a FUNCTION,
#: and the reconstruction reads a byte out of a stub instead of out of the
#: global -- so a fixture that drives the global has no effect at all.
#: Measured: `opt3001_read_lux_raw`'s `glob-0-0` case expected an early return
#: with zero calls (`g_opt3007_chip_ready == 0`) and the candidate called
#: `opt3001_reg_read` anyway, on BOTH trees.
#:
#: FUNCTION alias fragments are deliberately NOT included: pinning a callee to
#: its original flash address would place it outside the linked image, and the
#: harness needs callees to remain external boundaries so they are oracled.
PIN_FRAGMENTS = ("g1_app_globals.ld", "g1_app_sdk_state.ld",
                 "g1_net_globals.ld")
#: Base of the reconstructed RAM arena the data pins are expressed against
#: (recon/application/gen_app_data_image.py:ARENA_ORIGIN).
RAM_ARENA_ORIGIN = 0x20002000
_PROVIDE = re.compile(r'PROVIDE\(\s*([A-Za-z_$][\w$]*)\s*=\s*([^)]+?)\s*\)\s*;')


#: `extern volatile int g_log_use_alt_sink; /* @0x20007554 */` -- the address
#: comment tools/symbolize.py writes next to every declaration.
_HEADER_ADDRESS = re.compile(
    r'\b([A-Za-z_$][\w$]*)\s*(?:\[[^\]]*\])?\s*;\s*/\*\s*@\s*(0x[0-9a-fA-F]+)')


def header_addresses(tree, core):
    path = os.path.join(tree.root, "recon", "symbols",
                        "g1_%s_symbols.h" % core)
    if not os.path.exists(path):
        return {}
    with open(path, errors="replace") as handle:
        return {m.group(1): m.group(2)
                for m in _HEADER_ADDRESS.finditer(handle.read())}


def linker_pins(tree, core):
    """{symbol: expression} from the TREE's own pin fragments.

    A pin expression may name a symbol that is DEFINED IN C by one of the
    hand-written integration TUs the harness does not link
    (`PROVIDE(g_log_use_alt_sink = g1_log_use_alt_sink)`, defined in
    recon/application/app/src/g1_app_ram_relocs.c).  Those are resolved from
    the address comment `tools/symbolize.py` writes into
    `recon/symbols/g1_<core>_symbols.h`, which is the same provenance the pin
    itself has.  Without this, `opt3007_get_max_lux` and `fuel_gauge_update`
    fail to LINK -- measured, on both trees.
    """
    pins = {}
    for name in PIN_FRAGMENTS:
        if core == "app" and name.startswith("g1_net"):
            continue
        if core == "net" and name.startswith("g1_app"):
            continue
        path = os.path.join(tree.root, "recon", "symbols", name)
        if not os.path.exists(path):
            continue
        with open(path, errors="replace") as handle:
            for match in _PROVIDE.finditer(handle.read()):
                pins.setdefault(match.group(1), match.group(2))
    headers = header_addresses(tree, core)
    for name, expression in list(pins.items()):
        for token in re.findall(r'[A-Za-z_$][\w$]*', expression):
            if token in pins or token == "g1_ram_arena":
                continue
            # The pin's own right-hand side names an object whose address the
            # header knows; anchoring it there keeps every pin resolvable.
            if name in headers:
                pins[name] = headers[name]
            elif token in headers:
                pins[token] = headers[token]
    return pins


def _expose_target(text, symbol):
    """Drop `static` from the TARGET function's own definition, and only that.

    Stage 07 gives TU-private symbols internal linkage.  A `static` function
    that no other member of its TU calls is then simply NOT EMITTED by GCC
    ("defined but not used"), so the harness cannot find it after the link and
    the symbol becomes untestable in the refactored tree while remaining
    testable in the canonical one -- a difference in TESTABILITY that would
    read as a difference in behaviour.  Measured on
    `ipc_rpmsg_backend_register`: canonical FAIL(3/5), refactored
    "symbol not found after link".

    This changes LINKAGE, not code: the body, the constants and the calls are
    untouched, and linkage is not part of the pass criterion (§4).  The
    substitution is anchored on the definition -- `static` … `<symbol>` `(`
    followed by `{` rather than `;` -- so a declaration, a static VARIABLE, or
    a sibling's `static` is never touched.  It is applied at most once and the
    count is returned, so a silent no-match is visible.
    """
    # NO REGEX HERE.  The obvious pattern -- `static\s+((?:\w+|\*|\s)*?\bNAME\s*\(` --
    # backtracks catastrophically on a merged TU: measured at 154 SECONDS for
    # one symbol of `g1_ipc_06.c`, which made a 10-member unit cost 25 minutes
    # of pure regex.  Scan instead.
    count = 0
    cursor = 0
    while True:
        index = text.find(symbol, cursor)
        if index < 0:
            break
        cursor = index + len(symbol)
        after = text[cursor:cursor + 400].lstrip()
        if not after.startswith("("):
            continue
        # a DEFINITION ends its parameter list with `{`, a declaration with `;`
        close = text.find(")", cursor)
        if close < 0:
            continue
        following = text[close + 1:close + 200].lstrip()
        # BOTH forms.  A forward DECLARATION `static void f(void);` left behind
        # after the definition is de-staticised is a hard error ("static
        # declaration follows non-static declaration") -- measured on
        # `trigger_touch_key_hw_reset`.
        if not following[:1] in ("{", ";"):
            continue
        # walk back to the start of the declaration: the previous `;`, `}` or
        # start of file, whichever is closest
        comment_end = text.rfind("*/", 0, index)
        start = max(text.rfind(";", 0, index) + 1,
                    text.rfind("}", 0, index) + 1,
                    (comment_end + 2) if comment_end >= 0 else 0)
        head = text[start:index]
        position = head.find("static")
        if position < 0:
            continue
        before = head[:position]
        after_kw = head[position + 6:]
        if before.strip() or not after_kw[:1].isspace():
            continue                     # `static` must open the declaration
        text = text[:start + position] + after_kw + text[index:]
        count += 1
        cursor = start + position + len(after_kw)
    return text, count


def _undefined_symbols(path):
    from elftools.elf.elffile import ELFFile
    with open(path, "rb") as handle:
        table = ELFFile(handle).get_section_by_name(".symtab")
        return sorted({s.name for s in table.iter_symbols()
                       if s.name and s["st_shndx"] == "SHN_UNDEF"})


def fp_contract_flags(core, va, size):
    """`-ffp-contract` is a per-TU build contract RECOVERED FROM THE IMAGE.

    `VMLA/VMLS/VNMLA/VNMLS` multiply-accumulate with an intermediate rounding
    (two roundings, exactly C's `a + b*c`); `VFMA/VFMS/VFNMA/VFNMS` are fused
    (one rounding).  They differ by up to 1 ULP.  Compiling a candidate under
    the wrong contract manufactures spurious last-bit mismatches AND hides real
    ones.  The census in AGENTS.md finding #1b: 24 app functions use MAC ops
    and NONE mixes the two forms; the five G1 application bodies (0x26624,
    0x265e8, 0x26828, 0x7cab4, fuel_gauge_update) are unfused and every
    liblc3/libm body is fused.  Derived here, not assumed, exactly as
    tools/cfg_verify.py derives it.
    """
    ctx = core_ctx(core)
    unfused = fused = False
    for insn in _MD.disasm(ctx["rawread"](va & ~1, size), va & ~1):
        if insn.mnemonic.startswith(("vmla", "vmls", "vnmla", "vnmls")):
            unfused = True
        elif insn.mnemonic.startswith(("vfma", "vfms", "vfnma", "vfnms")):
            fused = True
    return ["-ffp-contract=off"] if unfused and not fused else []


#: (tree.root, symbol, va, flags, text-digest) -> compile result.
#: `_replay` calls run_candidate once per FIXTURE, and without this the same
#: translation unit is recompiled and relinked for every one of them -- 47
#: symbols x ~40 fixtures x 2 trees = 3,760 compiles for one module, which is
#: the difference between a module taking minutes and taking an hour.
_COMPILE_CACHE = {}


def compile_candidate(tree, symbol, va, extra_cflags=None, text_override=None):
    key = (tree.root, symbol, va & ~1, tuple(extra_cflags or ()),
           hashlib.sha256((text_override or "").encode()).hexdigest()
           if text_override is not None else None)
    if key in _COMPILE_CACHE:
        result = _COMPILE_CACHE[key]
        if isinstance(result, Exception):
            raise result
        return result
    try:
        result = _compile_candidate(tree, symbol, va, extra_cflags, text_override)
    except RuntimeError as error:
        _COMPILE_CACHE[key] = error
        raise
    _COMPILE_CACHE[key] = result
    return result


def _compile_candidate(tree, symbol, va, extra_cflags=None, text_override=None):
    """Compile the TU that defines `symbol` and link it at the original VA.

    Placement is explicit rather than inherited from section order, because a
    merged TU has no natural "first" function.  With `-ffunction-sections` the
    target's own section is linked FIRST, at the original VA, so the executable
    extent handed to the emulator is exactly the target function (plus any
    `.part`/`.cold` fragment the compiler outlined FROM it).  Every sibling of
    a merged unit is linked after `.rodata`, which makes it an external
    boundary -- oracled, exactly as the shipped image's `bl` to that sibling is.

    Returns (body, tail, size, linked_va, direct_target_map).
    """
    unit = tree.unit_for(symbol)
    if unit is None:
        raise RuntimeError("symbol %s not present in tree %s" % (symbol, tree.name))
    # `text_override` lets the mutation engine compile a MUTANT without ever
    # writing to the repository.  Nothing in this harness modifies a tree.
    text = unit.text if text_override is None else text_override
    text, destaticised = _expose_target(text, symbol)
    text, _marked = _mark_members_noinline(text, unit.members, symbol)
    from elftools.elf.elffile import ELFFile

    with _tree_cflags(tree, unit):
        flags = (list(recon.CFLAGS) + ["-ffunction-sections", "-fdata-sections"]
                 + UNIT_BOUNDARY_CFLAGS + PERMISSIVE_CFLAGS + ZEPHYR_CFLAGS
                 + list(extra_cflags or []))
        workdir = tempfile.mkdtemp(prefix="modtest_")
        csource = os.path.join(workdir, "unit.c")
        cobject = os.path.join(workdir, "unit.o")
        with open(csource, "w") as handle:
            handle.write(text)
        result = subprocess.run([recon.GCC] + flags + [csource, "-o", cobject],
                                capture_output=True, text=True)
        if result.returncode != 0:
            raise RuntimeError("cc: " + result.stderr[-2000:])
        pins = linker_pins(tree, tree.core)
        undefined = [s for s in _undefined_symbols(cobject)
                     if s != symbol and s not in pins]
        # A pin expression can name another pinned symbol
        # (`PROVIDE(x = g1_log_use_alt_sink + 4)`), so emit the transitive
        # closure, not just the directly-referenced set.
        pinned_used = set(_undefined_symbols(cobject)) & set(pins)
        frontier = set(pinned_used)
        while frontier:
            nxt = set()
            for name in frontier:
                for token in re.findall(r'[A-Za-z_$][\w$]*', pins[name]):
                    if token in pins and token not in pinned_used:
                        nxt.add(token)
            pinned_used |= nxt
            frontier = nxt
        pinned_used = sorted(pinned_used)
        stub_source = os.path.join(workdir, "stubs.c")
        stub_object = os.path.join(workdir, "stubs.o")
        with open(stub_source, "w") as handle:
            handle.write("\n".join(_UNDEF_STUB % (name, i + 1)
                                   for i, name in enumerate(undefined)) + "\n")
        subprocess.run([recon.GCC] + list(recon.CFLAGS) + [stub_source, "-o", stub_object],
                       capture_output=True, text=True)

    script = os.path.join(workdir, "link.ld")
    with open(script, "w") as handle:
        handle.write("g1_ram_arena = 0x%x;\n" % RAM_ARENA_ORIGIN)
        # Only the pins this unit actually references, so an unrelated pin
        # expression cannot fail the link.
        for name in pinned_used:
            handle.write("PROVIDE(%s = %s);\n" % (name, pins[name]))
        handle.write(
            "ENTRY(%s)\nSECTIONS{ . = 0x%x;\n"
            "  .text : { *(.text.%s) *(.text.%s.*) }\n"
            "  .rodata : { *(.rodata .rodata.*) }\n"
            "  .siblings : { *(.text .text.*) }\n"
            "  .oracle_stubs : { *(.oracle_stubs) }\n}\n"
            % (symbol, va & ~1, symbol, symbol))
    elf_path = os.path.join(workdir, "unit.elf")
    link = subprocess.run(
        [recon.GCC, "-mcpu=cortex-m33", "-mthumb", "-nostdlib",
         "-Wl,--build-id=none", "-T", script, cobject, stub_object,
         "-o", elf_path], capture_output=True, text=True, cwd=workdir)
    if link.returncode != 0:
        raise RuntimeError("ld: " + link.stderr[-2000:])

    target_map = {}
    with open(elf_path, "rb") as handle:
        elf = ELFFile(handle)
        table = elf.get_section_by_name(".symtab")
        semantic = recon._semantic_name_map(
            "net" if (va & ~1) >= 0x01000000 else "app")
        for name in undefined:
            match = re.fullmatch(r"FUN_([0-9a-fA-F]{8})", name)
            original = (int(match.group(1), 16) if match
                        else semantic.get(name))
            if original is None:
                continue
            entry = next((s for s in table.iter_symbols() if s.name == name), None)
            if entry:
                target_map[int(entry["st_value"]) & ~1] = original & ~1
        # A merged TU's SIBLINGS are DEFINED, so they are not undefined stubs
        # and were missing from the map -- a stored pointer to a sibling then
        # compared as its linked address against the shipped VA.  Measured:
        # `register_ipc_service_context` passed on the canonical tree (where
        # the callee is an `extern` stub) and failed 42/42 on the refactored
        # one (where it is a sibling in `g1_ipc_cc03.c`).
        banner_va = {name: va for name, _raw, va in unit.members}
        for entry in table.iter_symbols():
            if (entry.name in banner_va and
                    entry["st_info"]["type"] == "STT_FUNC" and
                    entry.name != symbol):
                target_map[int(entry["st_value"]) & ~1] = banner_va[entry.name] & ~1
        target = next((s for s in table.iter_symbols()
                       if s.name == symbol and s["st_info"]["type"] == "STT_FUNC"),
                      None)
        if target is None:
            raise RuntimeError("symbol %s not found after link" % symbol)
        text_section = elf.get_section_by_name(".text")
        base = text_section["sh_addr"]
        size = text_section["sh_size"]
        end = max(s["sh_addr"] + s["sh_size"] for s in elf.iter_sections()
                  if s["sh_type"] != "SHT_NOBITS" and s["sh_addr"] >= base)
        image = bytearray(end - base)
        for section in elf.iter_sections():
            if (section["sh_type"] != "SHT_NOBITS" and section["sh_size"] and
                    base <= section["sh_addr"] < end):
                offset = section["sh_addr"] - base
                image[offset:offset + section["sh_size"]] = section.data()
        linked_va = int(target["st_value"]) & ~1
        if linked_va != base:
            raise RuntimeError(
                "target %s did not land first (%#x vs .text %#x)"
                % (symbol, linked_va, base))
        return bytes(image[:size]), bytes(image[size:]), size, linked_va, target_map


def run_candidate(core, symbol, tree, va, fixture, golden, ret_kind="i32",
                  extra_cflags=None, max_insns=200000, text_override=None):
    """Run the candidate under `fixture` and return (key, coverage, meta).

    The candidate is fed the ORIGINAL run's positional call metadata
    (arity / float arity / return kind per call ordinal), exactly as
    emu.compare does: those properties belong to the callee being modelled,
    and the candidate's stub addresses cannot be looked up in a
    VA-keyed table.
    """
    contract = fp_contract_flags(core, va, golden.get("orig_size") or 0)
    body, tail, size, linked_va, target_map = compile_candidate(
        tree, symbol, va, list(extra_cflags or []) + contract,
        text_override=text_override)
    runner = _CoverageRunner(linked_va, size, body + tail,
                             core_ctx(core)["code_base"], own_readonly_tail=True,
                             track_coverage=False)
    # THE CANDIDATE'S OWN .rodata MUST WIN over the shipped image at the same
    # addresses.  The candidate is linked at the ORIGINAL VA, so its .rodata
    # lands a few hundred bytes into the shipped flash image's own address
    # space.  emu.Runner tries the shipped image FIRST -- correct for its
    # differential use, wrong here -- so an inlined C string literal resolved
    # to whatever the shipped image happens to hold at that address.
    # Measured: `ipc0_ept_recv` passed a format string that decoded as
    # b'%s(): NOT MATCH(cmd=%x)! ...' in the golden and as b'Tu' in the
    # candidate, and `global_ipc_service_send`'s tag decoded as b' Tu'.
    # Two of the three tree disagreements in the ipc pilot were this, not code.
    if len(runner.body) > runner.size:
        runner.readonly = emu.ReadOnlyPointees([
            emu._bytes_extent(linked_va + size, runner.body[size:]),
            emu._firmware_readonly_extent(core_ctx(core)["code_base"])])
    kwargs = fixture.run_kwargs()
    state = runner.run(
        max_insns=max_insns,
        call_arities=golden.get("call_arities"),
        call_float_arities=golden.get("call_float_arities"),
        call_return_kinds=golden.get("call_return_kinds"),
        oracle_target_map=target_map, **kwargs)
    # A STORED FUNCTION POINTER is the candidate's stub address, never the
    # shipped VA.  `register_ipc_service_context` writes 0x25B39 (a Thumb
    # function address) into a global; the candidate wrote its own stub's
    # address, and all 42 fixtures failed on BOTH trees.  emu already resolves
    # this identity for CALL TARGETS (`oracle_target_map`); apply the same map
    # to values that appear in the event trace, preserving the Thumb bit.
    if target_map:
        remap = {}
        for stub, original in target_map.items():
            remap[stub] = original
            remap[stub | 1] = original | 1
        def _remap(node):
            if isinstance(node, tuple):
                return tuple(_remap(x) for x in node)
            if isinstance(node, list):
                return [_remap(x) for x in node]
            if isinstance(node, int) and not isinstance(node, bool):
                return remap.get(node, node)
            return node
        state["events"] = [_remap(event) for event in state.get("events", ())]
    key = observable_key(state, ret_kind)
    # Semantic call-target identity: whenever the compiler exposed a callee
    # whose original VA we know, the ordinal-matched original call must have
    # gone to that same VA.  Without this a candidate could call the wrong
    # same-ABI dependency and still match the trace.
    identity = None
    for ordinal, target in enumerate(state.get("call_targets_full", ())):
        semantic = target_map.get(target & ~1)
        if semantic is None:
            continue
        actual = golden.get("call_targets", [])
        got = actual[ordinal] if ordinal < len(actual) else None
        if got is None or (got & ~1) != semantic:
            identity = {"ordinal": ordinal, "expected_original_target": got,
                        "candidate_semantic_target": semantic}
            break
    return key, runner.covered, {"size": size, "target_identity": identity,
                                 "state": state}


# --------------------------------------------------------------------------
# vector files
# --------------------------------------------------------------------------

def vector_path(core, module, symbol):
    return os.path.join(VECTOR_DIR, core, module, symbol + ".json")


def save_vectors(record):
    path = vector_path(record["core"], record["module"], record["symbol"])
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as handle:
        json.dump(record, handle, indent=1, sort_keys=True)
    return path


def load_vectors(core, module, symbol):
    with open(vector_path(core, module, symbol)) as handle:
        return json.load(handle)
