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
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE  # noqa: E402

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


#: Bytes of a stack record examined at a call boundary.  **DEFAULT 48 --
#: ENABLED.**  Disable with MODTEST_STACK_ARG_WINDOW=0.
#:
#: HISTORY, because this setting has been turned on and off before and the
#: reasons matter more than the value.
#:
#: Corrections 1-4 (previous pass) made the capture work at all:
#:   1. a fixed window includes the frame's saved registers, whose position
#:      relative to a local differs between compilations
#:      (`ipc_read_u16_field`: 42/43 fixtures failed on BOTH trees);
#:   2. classifying the STORE (`push`/`vpush`/`stmdb sp!` = frame bookkeeping)
#:      fixed that case;
#:   3. a record may hold a pointer to another stack local, whose raw value is
#:      frame layout -- those aligned words are blanked;
#:   4. a capture must only be committed when the call actually happens, or a
#:      run that faults before the call compares a record nobody received.
#:
#: Correction 5 defeated it and the whole capture was disabled: the shipped
#: code may reserve a slot with `push {r1}` while the reconstruction uses
#: `str r1,[sp,#n]`, so `st25dv_read_area_size` captured nothing on the golden
#: side and four bytes on the candidate's -- 41/41 fixtures failed on both
#: trees.
#:
#: THAT DIAGNOSIS WAS INCOMPLETE, and the correction it implies is different.
#: Measured (`stackprobe`, all 47 `ipc` symbols, window 48, comparing ONLY the
#: capture and nothing else): **44 of 47 agree on every fixture, 8 of them with
#: a non-empty record.**  The three that disagree are not a `push`-versus-`str`
#: spelling problem at all:
#:
#:   * `st25dv_read_area_size` -- `push {r0,r1,r2,lr}` then `add r1,sp,#4`.
#:     The pushed words are not a record; they are a 12-byte SCRATCH
#:     ALLOCATION, and the buffer at sp+4 is an OUT parameter that the callee
#:     fills.  Its content at the call is garbage on both sides.
#:   * `st25dv_mailbox_poll_message` -- identical shape, `push {r0..r6,lr}`
#:     then `add r0,sp,#8`.
#:   * `st25dv_reg_modify_low5` -- reads the out-buffer back
#:     (`ldrb [sp,#7]`), keeps its top three bits (`bic r3,#0x1f`) and stores
#:     it again.  The compared byte is 0x30 golden / 0x50 candidate: the low
#:     five bits, which the function COMPUTES, agree exactly; the top three,
#:     which it INHERITED from uninitialised frame memory, do not.
#:
#: All three are the same defect class, and it is not the store spelling: the
#: capture was comparing bytes whose value the function never produced.  Two
#: rules follow, and both are checkable rather than heuristic:
#:
#:   6. **A byte READ from the stack before the run ever wrote it is
#:      inherited, not produced.**  Its value is the previous frame's
#:      contents, which differ between compilations by construction.  Any
#:      offset that is read-before-written is dropped
#:      (`inherited` in `_new_uc`).
#:   7. **The GOLDEN defines the extent.**  The shipped image is the oracle
#:      here, so the offsets IT wrote are what the record is; the candidate is
#:      read raw over the same window and compared only at those offsets
#:      (`stack_args_mismatch`).  An offset the shipped code never wrote is
#:      not part of the observable contract in this model, so a candidate that
#:      spills a register there is not a failure.
#:
#: Rule 7 is a deliberate ASYMMETRY and it is a weakening: a candidate that
#: writes an EXTRA field the shipped code does not write is invisible.  A
#: candidate that FAILS to write a field the shipped code writes is still
#: caught, because the golden offset is compared and the candidate's byte is
#: whatever its frame happened to hold.
#:
#: With 6 and 7 in place the measured disagreement count over all 139 piloted
#: symbols is ZERO, and `ipc_send_len_prefixed_packet` recovers from a 13 %
#: mutation kill rate to 100 %.  The numbers are in the architecture document.
STACK_ARG_WINDOW = int(os.environ.get("MODTEST_STACK_ARG_WINDOW", "48"))

#: How far above a stack pointer handed to an oracled call counts as "the
#: buffer the callee was supposed to fill".  512 is inherited from the detector
#: that measured the class (§28.5.2, `outparam_scope.py`, 6 of 376 app
#: symbols); it is a DETECTION window only -- nothing is compared over it -- so
#: making it generous costs fixtures, never correctness.
OUTPARAM_WINDOW = int(os.environ.get("MODTEST_OUTPARAM_WINDOW", "512"))

#: ★ FILL the out-parameter instead of dropping the fixture.  This is the
#: counterpart of the r0/r1 preservation of §28.1 -- there the oracle wrote too
#: MUCH, here it writes too LITTLE -- and it is the difference between
#: reporting these symbols as UNDECIDABLE and actually deciding them.
#:
#: The mechanism: a stack byte inside a buffer this run handed to an oracled
#: call, which nothing in the run has written, is given a deterministic value
#: keyed by (call ordinal, argument index, OFFSET FROM THE POINTER) at the
#: moment it is read -- on BOTH sides.  emu seeds all of RAM from a PRNG, so
#: those bytes were never "random": they were deterministic BY ADDRESS, which
#: is precisely the wrong key, because the shipped frame and the candidate's
#: frame put the same buffer at different addresses.  Keying on the offset from
#: the pointer the callee received makes the value frame-independent, which is
#: what the real callee's output is.
#:
#: It cannot manufacture a pass.  A candidate that reads a DIFFERENT offset of
#: the buffer gets a different byte; one that reads a different buffer, or the
#: wrong number of bytes, or in a different order, still diverges.  The only
#: comparisons it changes are those decided by which garbage a frame happened
#: to hold, which decide nothing.
OUTPARAM_FILL = os.environ.get("MODTEST_OUTPARAM_FILL", "1") == "1"
#: Fallback for OUTPARAM_FILL=0: drop the fixture instead (the net pass's own
#: "safe version", which cannot manufacture anything because it only removes
#: evidence -- measured cost: `md5_process_block` 41 fixtures -> 1, coverage
#: 0 %, i.e. the symbol becomes untested rather than falsely failing).
DROP_OUTPARAM_UNINIT = os.environ.get("MODTEST_DROP_OUTPARAM", "0") == "1"

_OUTPARAM_PATTERN = {}


def outparam_bytes(ordinal, index, word=None):
    """Deterministic content an opaque callee is modelled as writing.

    `word` (the fixture's `outparam` dimension) replaces the hash pattern with
    one repeated 32-bit value, which is how a message-loop's command selector
    gets driven -- see `generate.POINTEE_LADDER`.
    """
    if word is not None:
        return (int(word) & 0xffffffff).to_bytes(4, "little") * \
            (OUTPARAM_WINDOW // 4 + 1)
    key = (int(ordinal), int(index))
    if key not in _OUTPARAM_PATTERN:
        blob = b""
        counter = 0
        while len(blob) < OUTPARAM_WINDOW:
            blob += hashlib.sha256(b"modtest-outparam|%d|%d|%d"
                                   % (key[0], key[1], counter)).digest()
            counter += 1
        _OUTPARAM_PATTERN[key] = blob[:OUTPARAM_WINDOW]
    return _OUTPARAM_PATTERN[key]


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
        # CONTENT capture (which offsets this run produced) is only meaningful
        # on the GOLDEN side -- rule 7, the golden defines the extent.  The
        # candidate only needs the RAW window, which costs no write hook and no
        # read hook at all.
        self.stack_content = kwargs.pop("stack_content", True)
        # Which core's image to interrogate for `callee_gpr_defs` (§22.3).
        # None disables oracle register preservation entirely.
        self.preserve_core = kwargs.pop("preserve_core", None)
        if not ORACLE_PRESERVE:
            self.preserve_core = None
        super().__init__(*args, **kwargs)
        self.covered = set()
        self.stack_arg_trace = []
        self.stack_raw_trace = []
        self.stack_ro_trace = []
        self._outparam_regions = []
        self.outparam_uninit = []
        self.outparam_filled = 0
        self.uninit_stack_reads = 0
        #: fixture dimension; set by run_original / run_candidate
        self.outparam_word = None
        self._pending_preserve = None
        self._preserve_cache = {}
        self._otm = None
        self.preserved_calls = []
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
        #: RULE 6.  A stack byte the run READ before it ever wrote is
        #: INHERITED -- its value is the previous frame's, which differs
        #: between the shipped code and any recompilation by construction.
        #: `st25dv_reg_modify_low5` reads the out-buffer back, keeps its top
        #: three bits with `bic r3,#0x1f` and stores it again: the five bits
        #: it COMPUTES agree exactly and the three it INHERITED do not.
        #: Comparing an inherited byte is comparing frame layout.
        inherited = set()

        pushed = set()
        classified = {}

        #: ★ THE UNMODELLED OUT-PARAMETER (§28.5.2; net_test_coverage.md §12.1).
        #: `emu` models a callee as opaque and writes r0/r1 only, so a callee
        #: whose JOB is to fill a caller-supplied buffer fills NOTHING, and the
        #: caller then reads a stack byte that nothing in the run ever wrote.
        #: Both sides read garbage; the two frames are not the same frame; the
        #: comparison decides nothing about the reconstruction.  It is detected
        #: EXACTLY -- a read of a never-written byte inside a region this run
        #: passed by pointer to an oracled call -- and the fixture is DROPPED at
        #: `gen` (`generate.select`).  Dropping can only remove evidence, never
        #: manufacture it.
        #:
        #: `written` alone is the WRONG set to test against here, and using it
        #: would have flagged nearly everything: a byte the PROLOGUE pushed is
        #: classified into `pushed`, so the epilogue's `pop` reads a byte not in
        #: `written`, and a 512-byte window from a stack local reaches the
        #: frame's own saved registers on most functions.  A pushed byte is
        #: initialised.  Rule 6's `inherited` keeps its existing meaning
        #: untouched -- it defines what a stored record contains and is a
        #: different question.
        def _read(_uc, _access, address, size, _value, _ud):
            if not (stack_low <= address < stack_high):
                return True
            for offset in range(size):
                byte_address = address + offset
                if byte_address not in written:
                    inherited.add(byte_address)
                if byte_address in written or byte_address in pushed:
                    continue
                self.uninit_stack_reads += 1
                # WHICH buffer a byte belongs to, when several pointer
                # arguments' windows overlap: the CLOSEST PRECEDING pointer,
                # then the most recent call.  Picking "the last region
                # registered" instead would be decided by the order two
                # arguments happened to be classified and by how far apart the
                # frame put them -- i.e. by frame layout, which is the very
                # thing this fill exists to be independent of.  The RELATIVE
                # layout of the pointers actually passed is compared in the
                # trace, so this choice agrees on both sides whenever the trace
                # does.
                best = None
                for region in self._outparam_regions:
                    low_bound, high_bound, ordinal, index = region
                    if low_bound <= byte_address < high_bound:
                        if best is None or (low_bound, ordinal) > (best[0],
                                                                   best[2]):
                            best = region
                if best is None:
                    continue
                low_bound, _high, ordinal, index = best
                self.outparam_uninit.append((byte_address, low_bound))
                if OUTPARAM_FILL:
                    # Writing inside a UC_HOOK_MEM_READ callback DOES change the
                    # value the access returns (verified directly against
                    # unicorn before relying on it).
                    pattern = outparam_bytes(ordinal, index,
                                             self.outparam_word)
                    _uc.mem_write(byte_address,
                                  pattern[byte_address - low_bound:
                                          byte_address - low_bound + 1])
                    self.outparam_filled += 1
            return True
        if (self.stack_content and STACK_ARG_WINDOW) or (OUTPARAM_FILL and
                                                         self.call_sites):
            uc.hook_add(UC_HOOK_MEM_READ, _read)

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
        if (self.stack_content and STACK_ARG_WINDOW) or (OUTPARAM_FILL and
                                                         self.call_sites):
            # The write hook is what distinguishes an INITIALISED stack byte
            # from an unwritten one, so the out-parameter fill needs it on the
            # CANDIDATE side too -- not only on the golden, where the record
            # content is captured.
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
            # THE r0-CLOBBER CLASS (§22.3).  Snapshot, BEFORE the call, every
            # one of r0/r1 the real callee provably never writes; `_restore`
            # puts them back after `emu`'s oracle has overwritten them.  The
            # snapshot is bound to THIS call's return address so a `bl` into
            # the function's own body -- which `emu` never oracles, and which a
            # linear call-site scan can also invent -- cannot leak a stale
            # restore into some later call.
            self._pending_preserve = None
            if self.preserve_core is not None:
                keep = self._preserve_for(_uc, insn)
                if keep:
                    self._pending_preserve = (
                        ((address + insn.size) | 1) & 0xffffffff,
                        {index: int(_uc.reg_read(emu.REG[index])) & 0xffffffff
                         for index in keep})
            record = []
            raw = []
            readonly_words = []
            for index in range(4):
                value = int(_uc.reg_read(emu.REG[index])) & 0xffffffff
                if not (stack_low <= value < stack_high):
                    continue
                # The out-parameter region for this argument: whatever the
                # callee was handed a pointer to.  Registered on BOTH sides.
                # Capped at STACK_TOP so a shallow frame's region can never
                # reach the stack-argument area emu writes above it.
                self._outparam_regions.append(
                    (value, min(value + OUTPARAM_WINDOW, emu.STACK_TOP),
                     ordinal, index))
                span = min(STACK_ARG_WINDOW, stack_high - value)
                window = b""
                if span > 0:
                    window = bytes(_uc.mem_read(value, span))
                    raw.append((index, window.hex()))
                    # ★ READ-ONLY POINTER INSIDE A STACK RECORD (§28.6.1).
                    # Computed on BOTH sides, from the same function of the
                    # observed word, so the golden stores WHICH string and the
                    # candidate is asked the same question about its own word.
                    markers = self._readonly_markers(value, window)
                    if markers:
                        readonly_words.append(
                            (index, tuple(sorted(markers.items()))))
                if not self.stack_content:
                    continue
                # RULE 6: an offset the run read before writing is inherited
                # frame content, not something this function produced.
                present = {offset for offset in range(span)
                           if value + offset in written
                           and value + offset not in inherited}
                # A record may hold a POINTER TO ANOTHER STACK LOCAL
                # (`local_20.p = &local_24`).  Its raw value is the frame
                # layout, which differs between the shipped code and any
                # recompilation, so comparing those four bytes manufactures a
                # failure for a correct candidate -- measured: this made
                # `ipc_send_len_prefixed_packet` fail 41/41 on BOTH trees.
                # Blank the word and keep every other field exact.
                pointer_words = set()
                for offset in range(0, max(span - 3, 0)):
                    if (value + offset) & 3:
                        continue
                    if not all((offset + k) in present for k in range(4)):
                        continue
                    word = int.from_bytes(_uc.mem_read(value + offset, 4),
                                          "little")
                    if stack_low <= word < stack_high:
                        pointer_words.update(offset + k for k in range(4))
                # ★ A POINTER TO A STRING LITERAL IS THE SAME KIND OF NUMBER AS
                # A POINTER TO A STACK LOCAL, and it was being compared
                # EXACTLY.  Measured: four of the six `stack-record` failures in
                # §28.6 mismatch at arg 2 offset 4 with a golden word that
                # decodes as a `printf` format string in the shipped image's
                # pool and a candidate word that is the SAME STRING in its own
                # `.rodata`.  `bt_dev_show_info` failed 41 of 41 fixtures at
                # 100 % coverage on that alone.
                # It is NOT blanked -- that would let a candidate pass the wrong
                # string.  The CONTENT is recorded instead, so *which* string is
                # compared and *where it lives* is not.  (§28.6.1)
                readonly_offsets = dict(readonly_words[-1][1]) \
                    if (readonly_words and readonly_words[-1][0] == index) else {}
                # A word only counts as a stored read-only pointer when the run
                # wrote ALL FOUR of its bytes; a partially-written word is not a
                # pointer this function produced.
                readonly_span = {}
                for base_offset in readonly_offsets:
                    if all(base_offset + k in present for k in range(4)):
                        for k in range(4):
                            readonly_span[base_offset + k] = base_offset
                content = []
                for offset in sorted(present):
                    if offset in pointer_words:
                        content.append((offset, "P"))
                    elif offset in readonly_span:
                        base_offset = readonly_span[offset]
                        content.append(
                            (offset, ["RO", readonly_offsets[base_offset]]
                             if offset == base_offset else "-"))
                    else:
                        content.append((offset,
                                        _uc.mem_read(value + offset, 1)[0]))
                if content:
                    record.append((index, tuple(content)))
            if record:
                self.stack_arg_trace.append((ordinal, tuple(record)))
            if raw:
                self.stack_raw_trace.append((ordinal, tuple(raw)))
            if readonly_words:
                self.stack_ro_trace.append((ordinal, tuple(readonly_words)))
        if STACK_ARG_WINDOW or OUTPARAM_FILL or self.preserve_core is not None:
            for site in sorted(self.call_sites):
                uc.hook_add(UC_HOOK_CODE, _hook, begin=site, end=site)

        def _restore(_uc, _address, _size, _ud):
            # `emu` returns from every oracled call by redirecting PC to
            # ORACLE_TRAMPOLINE, a mapped `bx lr`, AFTER it has written r0/r1.
            # That address is executed exactly once per oracled call and by
            # nothing else, so it is the one place a post-call fixup can live
            # without touching `emu`, which is frozen and shared with the net
            # core.  LR still holds this call's return address, which is what
            # binds the fixup to the call that took the snapshot.
            pending = self._pending_preserve
            if not pending:
                return
            self._pending_preserve = None
            expected_lr, values = pending
            if (int(_uc.reg_read(emu.UC_ARM_REG_LR)) & 0xffffffff) != expected_lr:
                return
            for index, value in values.items():
                _uc.reg_write(emu.REG[index], value)
            self.preserved_calls.append((expected_lr, tuple(sorted(values))))
        if self.preserve_core is not None:
            uc.hook_add(UC_HOOK_CODE, _restore,
                        begin=emu.ORACLE_TRAMPOLINE,
                        end=emu.ORACLE_TRAMPOLINE)
        return uc

    def _readonly_markers(self, base, window):
        """{offset: content-digest} for words of `window` that point at a
        read-only STRING, by `emu.ReadOnlyPointees`' own narrow test.

        The same function of the same observed word is applied on both sides,
        so two equal words always produce equal markers and the verdict can
        only change for a pair whose two addresses hold byte-identical strings
        -- which is exactly the equivalence being asserted.  `emu`'s test is
        already deliberately narrow (a complete NUL-terminated printable string
        whose head the address is); anything failing it keeps EXACT byte
        comparison, so no discrimination is lost for const tables, device
        structs or function pointers.

        Disabled wherever `emu.RODATA_EQUIVALENCE_CORES` is (i.e. on net, where
        the analysis and runtime windows overlap numerically and a content
        lookup could decode the wrong object) -- there `self.readonly` is
        falsy and this returns nothing, leaving today's byte comparison.
        """
        readonly = getattr(self, "readonly", None)
        if not readonly:
            return {}
        markers = {}
        for offset in range(0, max(len(window) - 3, 0)):
            if (base + offset) & 3:
                continue
            word = int.from_bytes(window[offset:offset + 4], "little")
            identity = readonly.content(word)
            if identity is not None:
                markers[offset] = hashlib.sha256(
                    identity[1]).hexdigest()[:16]
        return markers

    _REG_INDEX = {**{"r%d" % i: i for i in range(13)},
                  "ip": 12, "sb": 9, "sl": 10, "fp": 11}

    def _preserve_for(self, uc, insn):
        """Regs of r0/r1 to carry across THIS call, or None.

        The target is resolved the same way `emu` resolves it -- the branch
        immediate, or the register for a `blx rN` -- and then mapped through
        `oracle_target_map`, so a candidate's generated stub is interrogated as
        the ORIGINAL callee it stands for.  A target with no map entry (the
        compiler did not expose it) simply preserves nothing on the candidate
        side; that asymmetry is harmless because a candidate compiled against
        an `extern` never reads a caller-saved register across a call, so
        preservation can change the GOLDEN's trace and never the candidate's.
        """
        head = insn.mnemonic.split(".")[0]
        target = None
        if "#" in insn.op_str:
            try:
                target = int(insn.op_str.split("#")[-1], 0)
            except ValueError:
                target = None
        elif head == "blx":
            index = self._REG_INDEX.get(insn.op_str.strip())
            if index is not None:
                target = int(uc.reg_read(emu.REG[index]))
        if target is None:
            return None
        target &= ~1
        target = (self._otm or {}).get(target, target)
        if target in self._preserve_cache:
            return self._preserve_cache[target]
        written = callee_gpr_defs(self.preserve_core, target)
        keep = None
        if written is not None:
            keep = tuple(r for r in _ORACLE_CLOBBERED if r not in written) or None
        self._preserve_cache[target] = keep
        return keep

    def run(self, *args, **kwargs):
        self.stack_arg_trace = []
        self.stack_raw_trace = []
        self.stack_ro_trace = []
        self._outparam_regions = []
        self.outparam_uninit = []
        self.outparam_filled = 0
        self.uninit_stack_reads = 0
        self._call_seq = 0
        self._pending_preserve = None
        self.preserved_calls = []
        self._otm = kwargs.get("oracle_target_map")
        state = super().run(*args, **kwargs)
        # A capture is taken AT the `bl`, before it executes.  A run that
        # builds a record and then FAULTS at the call has passed that record to
        # nobody, so its content is not observable -- and the shipped code and
        # the reconstruction legitimately fill the record at different points
        # relative to the faulting load.  Keep only captures whose call
        # actually happened, which `ncalls` counts.  (Measured: without this,
        # `i2c_read_reg16_be` failed 2 of 3 fixtures on both trees.)
        calls = int(state.get("ncalls", 0))
        state["stack_args"] = [[ordinal, [[index, list(content)]
                                          for index, content in record]]
                               for ordinal, record in self.stack_arg_trace
                               if ordinal < calls]
        state["stack_raw"] = {ordinal: dict(record)
                              for ordinal, record in self.stack_raw_trace
                              if ordinal < calls}
        state["stack_ro"] = {ordinal: {index: dict(markers)
                                       for index, markers in record}
                             for ordinal, record in self.stack_ro_trace
                             if ordinal < calls}
        # Reported, not acted on, from here: `generate.select` decides what to
        # do with it and the vector file records the count, so the class stays
        # visible instead of becoming an invisible filter.
        state["outparam_uninit"] = len(self.outparam_uninit)
        state["outparam_filled"] = self.outparam_filled
        state["uninit_stack_reads"] = self.uninit_stack_reads
        return state


def stack_args_mismatch(golden, candidate_raw, candidate_ro=None):
    """RULE 7: the GOLDEN defines the extent of a stack record.

    `golden` is what the SHIPPED bytes produced -- a list of
    `[call_ordinal, [[arg_index, [[offset, byte|"P"], ...]], ...]]`.
    `candidate_raw` is `{call_ordinal: {arg_index: hex-window}}`, read raw.

    Only the offsets the shipped code WROTE (and did not inherit, rule 6) are
    compared.  Returns None on agreement, else a small diagnostic dict.

    Why asymmetric, restated where it is implemented: the shipped image is the
    oracle, so what it wrote is what the record IS.  A candidate that spills a
    register into a slot the shipped code never wrote is not a behaviour
    difference -- and treating it as one is precisely what produced 41/41 false
    failures on `st25dv_read_area_size` and disabled this whole mechanism last
    pass.  The cost is stated in `STACK_ARG_WINDOW`: an EXTRA write is
    invisible.  A MISSING one is not.
    """
    for entry in golden or ():
        ordinal, record = entry[0], entry[1]
        window = (candidate_raw or {}).get(ordinal)
        if window is None:
            window = (candidate_raw or {}).get(str(ordinal))
        for pair in record:
            index, content = pair[0], pair[1]
            blob = None if window is None else window.get(index,
                                                          window.get(str(index)))
            if blob is None:
                return {"call_ordinal": ordinal, "arg": index,
                        "reason": "candidate passed no stack pointer here"}
            data = bytes.fromhex(blob)
            markers = ((candidate_ro or {}).get(ordinal)
                       or (candidate_ro or {}).get(str(ordinal)) or {})
            markers = markers.get(index, markers.get(str(index))) or {}
            for item in content:
                offset, expected = item[0], item[1]
                if expected == "P":
                    continue            # frame-layout word, blanked on both
                if expected == "-":
                    continue            # 2nd..4th byte of a read-only pointer
                if isinstance(expected, (list, tuple)) and expected[0] == "RO":
                    # WHICH STRING, not where it lives (§28.6.1).  The
                    # candidate's word must resolve, by the same test, to a
                    # read-only string with the same content.  A candidate that
                    # stores a DIFFERENT string still fails, and one that stores
                    # a non-pointer fails with `reason` saying so -- this is not
                    # a blanking rule.
                    got = markers.get(offset, markers.get(str(offset)))
                    if got != expected[1]:
                        return {"call_ordinal": ordinal, "arg": index,
                                "offset": offset,
                                "expected_readonly_content": expected[1],
                                "got_readonly_content": got,
                                "reason": ("candidate word is not a read-only "
                                           "string with the same content")}
                    continue
                if offset >= len(data):
                    return {"call_ordinal": ordinal, "arg": index,
                            "offset": offset, "reason": "window short"}
                if data[offset] != expected:
                    return {"call_ordinal": ordinal, "arg": index,
                            "offset": offset, "expected": expected,
                            "got": data[offset]}
    return None


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
      outparam       word an oracled callee is modelled as writing through a
                     stack pointer argument (core.OUTPARAM_FILL); None = the
                     default hash pattern
    """

    @staticmethod
    def make(fid, args, nptr=2, scratch_seed=0, fp=None, abs_mem=None,
             mem=None, xpsr=0, float_scratch=False, oracle=None,
             outparam=None):
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
                               for i, r, v in (oracle or [])],
                       outparam=(None if outparam is None
                                 else int(outparam) & 0xffffffff))

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
    # Stack-record content is NOT folded into this digest.  It used to be, and
    # that is why it could only ever be an all-or-nothing equality: the golden
    # and the candidate produce different REPRESENTATIONS of it now (the golden
    # records which offsets it wrote, the candidate is read raw), and rule 7
    # compares them asymmetrically in `stack_args_mismatch`.  Folding a
    # one-sided hash in here would compare a record the candidate never had.
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
    if DERIVED_ARITY and abi.get("call_arity_by_target"):
        table = dict(abi["call_arity_by_target"])
        for target in list(table):
            derived = live_in_arity(core, target)
            if derived is not None and derived < table[target]:
                table[target] = derived
        abi["call_arity_by_target"] = table
    _ABI[core] = abi
    return abi


#: Derive callee arity from the CALLEE'S OWN BYTES rather than from Ghidra, and
#: use it whenever it is NARROWER.  ON by default: swept over all 2,383 app
#: callees that have a Ghidra arity, **310 of them (13 %) are over-wide**, so
#: leaving it off means 13 % of call sites compare dead argument registers and
#: can fail a correct candidate.  Disable with MODTEST_DERIVED_ARITY=0.
DERIVED_ARITY = os.environ.get("MODTEST_DERIVED_ARITY", "1") == "1"

_ARITY_CACHE = {}
_DEST_REG = re.compile(r'^\s*(r[0-3])\s*,')


def live_in_arity(core, va, cap=4):
    """How many of r0-r3 the callee READS BEFORE WRITING.  None if unknown.

    WHY THIS EXISTS.  §11 defect 2 fixed the harness comparing four argument
    registers at every call site whatever the callee's arity, by taking the
    arity from `cfg_verify.core_ctx`.  That source is Ghidra's decompiled
    signature, and it can be too WIDE -- which reintroduces the same false
    failure it was meant to remove.

    Measured on §18.3 item 4.  `st25dv_mailbox_send_message` fails exactly one
    fixture, at call ordinal 0, on argument registers.  The callee is
    `st25dv_write_reg_pair` at 0x24f08, whose entire body is:

        push {r3,r4,r5,lr} / mov r4,r0 / ldr r5,[pc,#0x2c] / movs r3,#4
        mov r2,r0 / movs r1,#0 / ldr r0,[r5] / bl 0x256dc / ...

    It reads **r0 and nothing else** -- r1, r2 and r3 are all overwritten
    before any use.  Its true arity is 1.  Ghidra says 4, so the harness
    compares three DEAD registers whose values are whatever the caller happened
    to leave there, and reports a divergence in them as a defect.

    The derivation is a live-in analysis over the CFG-reachable set in address
    order: a register is live-in if it is read before this walk sees it
    written.  It is conservative in the safe direction -- anything it cannot
    classify leaves the register live-in, so the arity can only ever come out
    too WIDE, never too narrow, and a too-wide arity is the status quo.
    """
    key = (core, va & ~1)
    if key in _ARITY_CACHE:
        return _ARITY_CACHE[key]
    ctx = core_ctx(core)
    base = va & ~1
    size = ctx["sizes"].get(va) or ctx["sizes"].get(base)
    if not size:
        _ARITY_CACHE[key] = None
        return None
    size = min(size, 0x1000)
    try:
        reachable, _unresolved = cfg_instructions(core, base, size)
        blob = ctx["rawread"](base, size)
    except Exception:                                   # noqa: BLE001
        _ARITY_CACHE[key] = None
        return None
    live_in = set()
    written = set()
    for address in sorted(reachable):
        offset = address - base
        if not (0 <= offset < size):
            continue
        insn = next(_MD.disasm(blob[offset:offset + 4], address), None)
        if insn is None:
            continue
        head = insn.mnemonic.split(".")[0]
        if head in ("bl", "blx"):
            # The callee's own call passes r0-r3; anything not yet written is
            # being forwarded and is therefore live-in.
            for index in range(cap):
                if index not in written:
                    live_in.add(index)
            break
        try:
            reads, writes = insn.regs_access()
        except Exception:                               # noqa: BLE001
            _ARITY_CACHE[key] = None
            return None
        names_read = {insn.reg_name(r) for r in reads}
        names_written = {insn.reg_name(w) for w in writes}
        # `push {r3, r4, r5, lr}` READS r3, and Thumb code uses exactly that
        # to reserve four bytes of stack -- the pushed value is dead.  Counting
        # it as a use is what made `st25dv_write_reg_pair` derive arity 4
        # instead of 1 on the first attempt, i.e. it reproduced the very
        # over-wide arity this function exists to narrow.  A stack save is only
        # a real use if the value is reloaded, and the walk stops at the first
        # `bl` before any reload could matter.
        if head in ("push", "vpush") or (head in ("stmdb", "stmfd") and
                                         "sp!" in insn.op_str):
            names_read = set()
        for index in range(cap):
            name = "r%d" % index
            if name in names_read and index not in written:
                live_in.add(index)
        for index in range(cap):
            name = "r%d" % index
            if name in names_written and index not in live_in:
                written.add(index)
    arity = (max(live_in) + 1) if live_in else 0
    _ARITY_CACHE[key] = arity
    return arity


# --------------------------------------------------------------------------
# THE r0-CLOBBER FALSE-FAILURE CLASS (§22.3) -- derived from the callee's bytes
# --------------------------------------------------------------------------

#: `emu.Runner.run`'s order-keyed call oracle writes **r0 and r1 only**
#: (`uc.reg_write(UC_ARM_REG_R0, o0)` / `R1, o1`); r2, r3 and r12 are left
#: untouched.  So r0 and r1 are the ONLY registers whose unconditional clobber
#: can manufacture a false failure, and this module never needs to reason about
#: the rest of the caller-saved bank.
_ORACLE_CLOBBERED = (0, 1)

#: Preserve, across an oracled call, every one of r0/r1 that the REAL CALLEE
#: provably never writes.  ON by default.  Disable with
#: MODTEST_ORACLE_PRESERVE=0 (which restores the pre-2026-07-29 semantics).
ORACLE_PRESERVE = os.environ.get("MODTEST_ORACLE_PRESERVE", "1") == "1"

_CALLEE_DEF_CACHE = {}


def callee_gpr_defs(core, va, depth=3):
    """Which of r0/r1 the callee at `va` CAN WRITE, from its OWN SHIPPED BYTES.

    Returns a frozenset subset of `{0, 1}`, or **None** when it cannot be
    established -- in which case the caller must assume both, which is exactly
    today's behaviour.

    WHY THIS EXISTS.  §22.3.  The shipped firmware was built at `-Os` with
    `-fipa-ra` on, so a caller may keep a value live in r0-r3 ACROSS a call
    when the compiler could see that the callee does not clobber it:

        00026636  vldr s7,  [r0, #0x18]     <-- r0 = state
        0002666c  bl   #0x265e8             <-- fast_inverse_sqrt: float in/out
        000266b4  vldr s13, [r0, #8]        <-- r0 STILL the state pointer

    `emu`'s oracle writes `sha256(ordinal)` into r0:r1 at EVERY call whatever
    the callee is, so the shipped body faults on the second `vldr` and the
    frozen golden records a fault the real hardware never takes.  The
    candidate, compiled against an `extern`, reloads the pointer from a
    callee-saved register and does not fault: a guaranteed FAIL for a CORRECT
    reconstruction.  `imu_mahony_ahrs_update` is the identified instance.

    The evidence that fixes it is the same evidence that found 310 of 2,383
    Ghidra callee arities over-wide (§22.7): the callee's own instructions.
    `fast_inverse_sqrt` is a leaf that takes and returns a float and never
    names r0, so preserving r0 across the call reproduces the hardware.

    DIRECTION OF CONSERVATISM.  Anything unclassifiable -- an unresolved
    computed branch, a `blx` through a register, a callee with no catalogued
    size, a call cycle, recursion past `depth` -- returns None and the register
    is clobbered as before.  The analysis can therefore only ever say "this
    register IS written" too often, never too rarely, so turning it on can only
    remove false failures, never manufacture them.

    It is NOT a live-range analysis of the caller.  It does not need to be: if
    the callee writes the register the oracle clobbers it exactly as before,
    and if the callee does not, preserving it is what the silicon does.
    """
    key = (core, va & ~1)
    if key in _CALLEE_DEF_CACHE:
        return _CALLEE_DEF_CACHE[key]
    # Cycle guard: while this callee is in flight it answers "unknown", so a
    # recursive or mutually recursive call graph degrades to the status quo
    # instead of looping or inventing an answer.
    _CALLEE_DEF_CACHE[key] = None
    result = _callee_gpr_defs(core, va, depth)
    _CALLEE_DEF_CACHE[key] = result
    return result


def _callee_gpr_defs(core, va, depth):
    ctx = core_ctx(core)
    base = va & ~1
    size = ctx["sizes"].get(va) or ctx["sizes"].get(base)
    if not size or size > 0x2000:
        return None
    try:
        blob = ctx["rawread"](base, size + 64)
    except Exception:                                   # noqa: BLE001
        return None
    defs = set()
    seen = set()
    work = [0]

    def _sub(target):
        """Merge a nested callee's writes; None propagates as 'unknown'."""
        if depth <= 0:
            return False
        inner = callee_gpr_defs(core, target, depth - 1)
        if inner is None:
            return False
        defs.update(inner)
        return True

    while work:
        off = work.pop()
        if off in seen or off < 0 or off >= size:
            continue
        for insn in _MD.disasm(blob[off:size], base + off):
            offset = insn.address - base
            if offset > 0 and (base + offset) in ctx["entries"]:
                # FALLS THROUGH INTO THE NEXT CATALOGUED FUNCTION.  Whatever
                # that one writes, this path writes; it is not analysed here.
                return None
            if offset in seen:
                break                                   # path already covered
            seen.add(offset)
            head = insn.mnemonic.split(".")[0]
            target = None
            if "#" in insn.op_str:
                try:
                    target = int(insn.op_str.split("#")[-1], 0)
                except ValueError:
                    target = None
            if head in ("bl", "blx"):
                # A nested call: whatever IT writes, this callee writes.
                if target is None or not _sub(target):
                    return None
                if defs.issuperset(_ORACLE_CLOBBERED):
                    return frozenset(defs)
                continue
            if head in _TERMINAL or (head == "pop" and "pc" in insn.op_str):
                break                                   # return
            if head in _UNCOND or insn.mnemonic in _UNCOND:
                if target is None:
                    return None
                if base <= target < base + size:
                    work.append(target - base)
                elif not _sub(target):
                    return None                         # tail call, unknown
                break
            if head in _COND:
                if target is None:
                    return None
                if base <= target < base + size:
                    work.append(target - base)
                elif not _sub(target):
                    return None                         # conditional tail call
                continue                                # and fall through
            if insn.mnemonic in ("tbb", "tbh") or (
                    insn.mnemonic in ("mov", "add") and
                    insn.op_str.startswith("pc")):
                return None                             # computed branch
            try:
                _reads, writes = insn.regs_access()
            except Exception:                           # noqa: BLE001
                return None
            names = {insn.reg_name(w) for w in writes}
            for index in _ORACLE_CLOBBERED:
                if ("r%d" % index) in names:
                    defs.add(index)
            if defs.issuperset(_ORACLE_CLOBBERED):
                return frozenset(defs)
        else:
            # THE WALK RAN OUT OF BYTES WITHOUT REACHING A TERMINAL.  The path
            # continues into whatever is linked next and this analysis has NOT
            # seen it.  Returning `frozenset()` here would assert "writes
            # nothing" about a function it did not finish reading.
            #
            # MEASURED, and it is why this branch exists: `0x0000d588` is
            # catalogued as FOUR BYTES holding `eor r3, r3, #0x80000000` -- a
            # double-negation fragment with no return instruction at all.  The
            # first version of this function answered "writes neither r0 nor
            # r1" for it, and a cross-check against Ghidra's return kinds
            # caught it as the ONE contradiction in 128 (Ghidra calls it
            # `i64`, i.e. a result in r0:r1).  128 -> 127, and the remaining
            # 127 all agree with Ghidra.
            return None
    return frozenset(defs)


def oracle_preserve_map(core, targets):
    """{callee_va: frozenset(regs to PRESERVE)} for the targets worth it.

    Only entries that actually preserve something are returned, so an empty
    map means the run is bit-for-bit what it was before this feature existed.
    """
    out = {}
    if not ORACLE_PRESERVE:
        return out
    for target in targets:
        written = callee_gpr_defs(core, target)
        if written is None:
            continue
        keep = frozenset(r for r in _ORACLE_CLOBBERED if r not in written)
        if keep:
            out[target & ~1] = keep
    return out


_PC_RELATIVE = re.compile(r'\[pc,\s*#(?:0x)?([0-9a-fA-F]+)\]')


def literal_pad(core, va, size, minimum=64, cap=0x800):
    """How many bytes past `size` this function's LITERAL POOL reaches.

    THE DEFECT THIS FIXES, and it is the worst kind -- it made the harness
    accuse a CORRECT reconstruction.

    The golden body was read as `func_bytes_padded(va, size, pad=64)`.  Reads
    outside the mapped body land on `emu`'s unmapped-access hook, which maps a
    page of ZEROS and continues, so a literal beyond `va + size + 64` is
    silently read as 0.

    `__ieee754_expf` is 344 bytes at 0x76290, so the padded body ends at
    0x76428 -- and its pool holds exactly two more words:

        0x76428  0x3717f7d1  = 9.0580006e-06   ln2LO
        0x7642c  0x0d800000  = 2**-100         subnormal rescale

    Losing `ln2LO` drops the low half of the argument reduction
    `x - k*ln2HI - k*ln2LO`, so the golden's answer is wrong by `k * 9.058e-6`
    relative.  Measured against `math.exp`, over the three fixtures named in
    §18.3 item 2:

        x = 9.8066502  k=14   golden err +1.27e-4   candidate err 2.0e-8
        x = 1.5707964  k= 2   golden err +1.82e-5   candidate err 3.0e-8
        x =-3.0        k=-4   golden err -3.62e-5   candidate err 3.0e-8

    `k * 9.058e-6` is 1.268e-4, 1.81e-5 and -3.62e-5.  The reconstruction is
    accurate to one float32 ULP and the ORACLE was wrong.

    So the pad is derived instead of assumed: every PC-relative load in the
    function names its literal, and the body is mapped far enough to cover the
    furthest one.  Padding only extends the MAPPED region -- `emu`'s executable
    extent is `[va, va+size)` and is unchanged -- so the extra bytes are simply
    the real image bytes at their real addresses, which is what a PC-relative
    load is entitled to see.
    """
    ctx = core_ctx(core)
    base = va & ~1
    end = base + size + minimum
    limit = base + size + cap
    for insn in _MD.disasm(ctx["rawread"](base, size), base):
        match = _PC_RELATIVE.search(insn.op_str)
        if not match:
            continue
        # `ldrd`/`vldr` of a double is 8 bytes; take the wider one always.
        literal = ((insn.address + 4) & ~3) + int(match.group(1), 16) + 8
        if base <= literal <= limit:
            end = max(end, literal)
    return end - (base + size)


def run_original(core, va, size, fixture, ret_kind="i32", max_insns=200000):
    ctx = core_ctx(core)
    body = ctx["read"](va, size, pad=literal_pad(core, va, size))
    runner = _CoverageRunner(va & ~1, size, body, ctx["code_base"],
                             preserve_core=core)
    runner.outparam_word = fixture.get("outparam")
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
#: `-fno-ipa-vrp` ADDED 2026-07-29 (§28.6.3).  INTERPROCEDURAL VALUE-RANGE
#: PROPAGATION is not covered by `-fno-ipa-cp` and leaks the unit boundary in a
#: MERGED TU only: when the TU also defines a callee whose return value GCC can
#: pin (`ble_appearance_value` is `{ return 0x341; }`), the compiler substitutes
#: the constant and DELETES the call the shipped code makes.
#: `__attribute__((noinline))` does not stop it, because this is not inlining.
#: It can only happen in the refactored tree, so it presents as a TREE
#: DISAGREEMENT -- the headline metric of this whole design.  Bisected against
#: the whole flag set: this one flag restores `read_appearance` to 2 calls and
#: no other flag changes it.
UNIT_BOUNDARY_CFLAGS = ["-fno-ipa-icf", "-fno-ipa-sra", "-fno-ipa-cp",
                        "-fno-ipa-vrp", "-fno-partial-inlining"]


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


def _only_directives(before):
    """True when `before` is whitespace and COMPLETE preprocessor lines only.

    Used by `_expose_target` to decide whether `static` opens its declaration.
    The LAST fragment (everything after the final newline, i.e. what sits on
    the same line as `static`) must be blank; every earlier line must be blank
    or a `#`-directive, and a directive continued with a trailing backslash is
    followed to its end so that its continuation body is not read as code.
    """
    parts = before.split("\n")
    if parts[-1].strip():
        return False
    continued = False
    for line in parts[:-1]:
        stripped = line.strip()
        if continued:
            continued = stripped.endswith("\\")
            continue
        if not stripped:
            continue
        if not stripped.startswith("#"):
            return False
        continued = stripped.endswith("\\")
    return not continued


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
        # A PREPROCESSOR DIRECTIVE IS NOT A STATEMENT, and the walk-back above
        # cannot see one: a directive ends with a NEWLINE, not with `;`, `}` or
        # `*/`, so `start` steps straight over it and `before` is
        # '\n#include "g1_display.h"\n' -- non-empty, so the declaration was
        # SKIPPED.  Measured cost: `get_demo_image_source`,
        # `refresh_box_field_timer`, `set_misc_286c_value` and `uarte_nrfx_init`
        # -- FOUR of the SEVEN tree disagreements in the 593-symbol fan-out of
        # §28.8, i.e. the harness manufacturing the metric it exists to report.
        # Accept a `before` made only of whitespace and COMPLETE directive
        # lines; anything else still means `static` did not open the
        # declaration.  (§28.6.2)
        if not _only_directives(before) or not after_kw[:1].isspace():
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
        if text_section is None:
            # `main` is the one symbol of the 634-symbol fan-out with NO result
            # at all: this returned None, the subscript raised TypeError, and
            # because `cli.cmd_run` had no per-symbol guard the exception took
            # the whole batch with it -- 23 further symbols silently lost
            # (§28.8.4).  A link that produced no `.text` is an ordinary
            # compile-side failure and must be reported as CCFAIL, not as a
            # crash.
            raise RuntimeError(
                "linked object for %s has no .text section (sections: %s)"
                % (symbol, ", ".join(s.name for s in elf.iter_sections()
                                     if s.name)[:200]))
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
                             track_coverage=False, stack_content=False,
                             preserve_core=core)
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
    runner.outparam_word = fixture.get("outparam")
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

#: Source files whose content DEFINES what a frozen expectation means.
#: `index.py` is deliberately excluded: it maps symbols to files and does not
#: participate in producing or comparing an expectation.
_SEMANTIC_SOURCES = ("core.py", "generate.py", "cli.py", "mutate.py")

_HARNESS_REV = None


def harness_rev():
    """Fingerprint of the harness code that DEFINES a golden expectation.

    WHY THIS EXISTS, and it is not hypothetical.  This harness was changed four
    times during a single session while a concurrent pass was sweeping the net
    core with it -- including flipping `STACK_ARG_WINDOW` from 0 to 48, which
    changes what `observable_key` contains and therefore what a stored vector
    MEANS.  **168 of that pass's vectors were invalidated mid-sweep.**  It
    recovered by pinning the harness to a `git show HEAD` snapshot and
    regenerating, and deleted 81 more whose harness version it could not
    establish rather than publish numbers it could not stand behind.

    A prose warning in an architecture document does not reach a process that
    is already running.  A stamp does: `gen` records this fingerprint in every
    vector file and `run` refuses a vector whose fingerprint differs, so the
    whole class becomes a hard error at the point of use instead of a silent
    comparison against a different definition of "expected".

    It is a content hash rather than a git rev on purpose -- the working tree
    is dirty by design here (the owner's rule is to leave it so), and a git rev
    would say "HEAD" for four materially different harnesses in one session.
    """
    global _HARNESS_REV
    if _HARNESS_REV is None:
        digest = hashlib.sha256()
        here = os.path.dirname(os.path.abspath(__file__))
        for name in _SEMANTIC_SOURCES:
            path = os.path.join(here, name)
            digest.update(name.encode())
            if os.path.exists(path):
                with open(path, "rb") as handle:
                    digest.update(handle.read())
        _HARNESS_REV = digest.hexdigest()[:16]
    return _HARNESS_REV


def vector_staleness(record):
    """None if this vector may be replayed, else why not.

    ⚠ THIS USED TO FAIL OPEN AND THAT WAS THE WHOLE HOLE.  The previous version
    returned None -- *replay permitted, silently* -- for an UNSTAMPED vector,
    on the reasoning that refusing every pre-stamp vector "would turn a safety
    feature into a wall", and claimed in this docstring that `cli.cmd_run`
    reported the count.  It did not (`grep -n unstamped cli.py` returned
    nothing), so the guard's ONE escape hatch was also its only invisible path.
    The net pass measured the consequence: all 233 of its inherited vectors
    were unstamped, i.e. **100 % of the corpus took the permissive branch**,
    replaying against a harness that had since changed in four ways that each
    redefine the stored expectation (net_test_coverage.md §9.1).

    It now FAILS CLOSED: no stamp, no replay.  The wall is the point -- `gen`
    is cheap, a wrong verdict is not -- and it is one regeneration deep.

    The env-var switches are checked the same way: a vector that does not
    RECORD one is refused rather than assumed to match, because "the field is
    missing" and "the field agrees" are not the same statement and only the
    second one licenses a comparison.  (Written this way deliberately: the
    obvious `if field in harness` spelling reopens the identical hole one level
    down -- an old vector simply omits the field and sails through.)
    """
    harness = record.get("harness") or {}
    stamped = harness.get("rev")
    if stamped is None:
        return ("vector is UNSTAMPED -- it was frozen by an unknown harness "
                "version, and what it stores as 'expected' may not be what "
                "this harness (%s) compares against; regenerate it "
                "(`cli.py gen`)" % harness_rev())
    if stamped != harness_rev():
        return ("vector was generated by harness %s, this is %s -- regenerate "
                "it (`cli.py gen`); the expectation it stores may not mean "
                "what this harness compares against"
                % (stamped, harness_rev()))
    # THE ENV-VAR HOLE.  `harness_rev` fingerprints SOURCE, and the two
    # semantics switches that matter are environment variables, so two runs of
    # byte-identical harness code can freeze two different definitions of
    # "expected" under one fingerprint.  Both are recorded at `gen`; compare
    # them.  (Found while A/B-measuring the r0-clobber class -- the control arm
    # and the treatment arm produced indistinguishable vector files.)
    for field, current in sorted(harness_env().items()):
        if field not in harness:
            return ("vector does not record %s, so it cannot be shown to mean "
                    "what this run compares against -- regenerate it "
                    "(`cli.py gen`)" % field)
        if harness[field] != current:
            return ("vector was generated with %s=%s, this run has %s -- "
                    "regenerate it (`cli.py gen`)"
                    % (field, harness[field], current))
    return None


def harness_env():
    """Every ENVIRONMENT switch that changes what a golden expectation MEANS.

    One place, so the next switch is covered by construction.  `harness_rev()`
    fingerprints SOURCE and is blind to all of these: two runs of byte-identical
    code with different values here freeze two different definitions of
    "expected" under one fingerprint.  `gen` records this dict and
    `vector_staleness` refuses a vector that does not match it -- including one
    that simply OMITS a key, which is how the same hole would otherwise reopen
    one level down.
    """
    return {"outparam_fill": bool(OUTPARAM_FILL),
            "derived_arity": bool(DERIVED_ARITY),
            "oracle_preserve": bool(ORACLE_PRESERVE),
            "stack_arg_window": int(STACK_ARG_WINDOW),
            "outparam_window": int(OUTPARAM_WINDOW),
            "drop_outparam_uninit": bool(DROP_OUTPARAM_UNINIT)}


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
