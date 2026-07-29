"""Coverage-guided golden-vector generation.

Fixtures are chosen by MEASURED COVERAGE of the shipped instructions, not by a
model of where the interesting inputs are.  That ordering is the whole point.
Every previous coverage model in this repository has had a blind spot that was
invisible from inside the model:

  * uniform random integers never land in a small switch range (AGENTS.md #1);
  * uniform random words are never ordinary floats (AGENTS.md #1b);
  * a branch whose selector comes from a GLOBAL is outside cfg_verify's
    argument taint model entirely (our_boot_bringup.md 51.1.1).

A measured coverage ratio has no such blind spot: an unreached basic block is
an unreached basic block whatever the reason.  It does not tell you the tests
are good; it tells you, honestly, how much of the function they touch.

Input dimensions searched, in order of cost:
  1. seeded argument vectors (emu.make_args, already boundary-biased)
  2. per-argument selector values recovered from the shipped CFG
  3. VFP argument words drawn from emu.FLOAT_POOL
  4. ABSOLUTE MEMORY -- every global the literal pool names -- swept over a
     small ladder of values.  This is the dimension cfg_verify does not have.
  5. architectural mode (thread / handler) when the body reads IPSR
"""

from __future__ import annotations

import os
import re
import struct
import sys

_HERE = os.path.dirname(os.path.abspath(__file__))
if _HERE not in sys.path:
    sys.path.insert(0, _HERE)
_TOOLS = os.path.dirname(_HERE)
if _TOOLS not in sys.path:
    sys.path.insert(0, _TOOLS)

from parity import emu                                       # noqa: E402
import core as mtcore                                        # noqa: E402
from core import Fixture, cfg_instructions, run_original      # noqa: E402

#: values a global is swept over.  Small and boundary, for the same reason
#: make_args over-samples small integers: real predicates test 0, 1, a small
#: enum, a level threshold, a bit mask, or a pointer being NULL.
GLOBAL_LADDER = (0, 1, 2, 3, 0xff, 0x7fffffff, 0xffffffff, emu.SCRATCH + 0x2000)

_LDR_PC = re.compile(r'^(?:r\d+|sb|sl|fp|ip),\s*\[pc,\s*#(?:0x)?([0-9a-fA-F]+)\]')


def literal_globals(core, va, size, limit=24):
    """Absolute addresses this function's literal pool names.

    A PC-relative load is how the shipped code reaches every global it uses
    (the reconstruction convention in AGENTS.md deliberately preserves those
    literal VALUES).  Reading the pool therefore enumerates the function's
    global dependencies without needing any symbol table.

    Kept: RAM and peripheral addresses.  Dropped: flash addresses, which are
    read-only string/table pointers, and are already exercised by the
    read-only-pointee machinery in emu.
    """
    ctx = mtcore.core_ctx(core)
    base = va & ~1
    blob = ctx["rawread"](base, size + 64)
    found = []
    for insn in mtcore._MD.disasm(blob[:size], base):
        if insn.mnemonic not in ("ldr", "ldr.w"):
            continue
        match = _LDR_PC.match(insn.op_str)
        if not match:
            continue
        literal = ((insn.address + 4) & ~3) + int(match.group(1), 16)
        offset = literal - base
        if not (0 <= offset + 4 <= len(blob)):
            continue
        word = int.from_bytes(blob[offset:offset + 4], "little")
        if word in found:
            continue
        # RAM (both cores) and the reviewed MMIO windows.  Everything else is
        # not a global this harness can meaningfully drive.
        ram = (emu.RAM_BASE <= word < emu.RAM_BASE + emu.RAM_SIZE or
               0x21000000 <= word < 0x21080000)
        if ram or emu._is_nrf53_mmio(word, 4):
            found.append(word)
        if len(found) >= limit:
            break
    return found


#: registers that may hold an argument on entry, in AAPCS order
_ARG_REGS = ("r0", "r1", "r2", "r3")
_MOVE = ("mov", "movs", "mov.w")
_ADDSUB = ("add", "add.w", "adds", "sub", "sub.w", "subs", "addw", "subw")
_DEREF = ("ldr", "ldrb", "ldrh", "ldrsb", "ldrsh", "ldrd", "ldm", "ldmia",
          "ldmdb", "str", "strb", "strh", "strd", "stm", "stmia", "stmdb",
          "ldrex", "ldrexb", "ldrexh", "strex", "strexb", "strexh", "vldr",
          "vstr", "vldm", "vstm", "tbb", "tbh")
_BASE = re.compile(r'\[\s*(r\d+|sb|sl|fp|ip|sp|pc)\b')
_DEST = re.compile(r'^\s*(r\d+|sb|sl|fp|ip)\s*,')
_SRC2 = re.compile(r'^\s*(r\d+|sb|sl|fp|ip)\s*,\s*(r\d+|sb|sl|fp|ip)\s*(?:,\s*#|$)')


def pointer_arg_mask(core, va, size):
    """Which of r0-r3 the SHIPPED code actually DEREFERENCES.

    THE DEFECT THIS FIXES, measured in the pilot (§18.5): every fixture was
    built by `emu.make_args(seed, nptr=2)`, so exactly the first two argument
    registers pointed into scratch and r2/r3 held seeded integers.  A function
    whose THIRD or FOURTH parameter is a pointer therefore received a small
    integer or a random word there, the shipped code faulted dereferencing it,
    and the reconstruction faulted at a different point or not at all.  The
    result is a FAIL that says nothing about the reconstruction --
    `imu_mahony_ahrs_update` failed 44 of 44 fixtures this way, on a function
    AGENTS.md records as repaired and passing.

    A fixed prefix count is wrong in both directions, which is the part worth
    stating: it also makes r0 a pointer for a function whose first parameter is
    a `uint8_t` command code, which is how a pointer-shaped value gets fed to a
    switch selector.  So the count is not the thing to derive -- the MASK is.

    Derivation is from the shipped instructions only, and it is deliberately
    conservative: track which registers still hold a value derived from an
    argument register (through register moves and immediate adds/subs), and
    mark argument `i` a pointer when a load or store uses such a register as
    its base.  A register written by anything else loses its origin, and every
    argument register loses its origin at a `bl` (the callee clobbers r0-r3).

    Walked in address order over the CFG-REACHABLE set rather than by linear
    disassembly, so a literal pool cannot be decoded as instructions -- the
    data-inflation problem of AGENTS.md finding #2 in miniature.
    """
    ctx = mtcore.core_ctx(core)
    base = va & ~1
    reachable, _unresolved = cfg_instructions(core, va, size)
    blob = ctx["rawread"](base, size + 8)
    origin = {name: index for index, name in enumerate(_ARG_REGS)}
    mask = set()
    for address in sorted(reachable):
        offset = address - base
        if not (0 <= offset < size):
            continue
        insn = next(mtcore._MD.disasm(blob[offset:offset + 4], address), None)
        if insn is None:
            continue
        head = insn.mnemonic.split(".")[0]
        operands = insn.op_str
        if head in ("bl", "blx"):
            for name in _ARG_REGS:
                origin.pop(name, None)
            continue
        if insn.mnemonic in _DEREF or head in _DEREF:
            found = _BASE.search(operands)
            if found and found.group(1) in origin:
                mask.add(origin[found.group(1)])
            # `str rX, [rY]` also WRITES rY's pointee, not rX -- the
            # destination register of a store is a source.  Nothing to clear.
            if head.startswith(("ldr", "vldr", "ldm", "vldm")):
                dest = _DEST.match(operands)
                if dest:
                    origin.pop(dest.group(1), None)
            continue
        if insn.mnemonic in _MOVE or head in _MOVE:
            pair = _SRC2.match(operands)
            dest = _DEST.match(operands)
            if pair and pair.group(2) in origin:
                origin[pair.group(1)] = origin[pair.group(2)]
            elif dest:
                origin.pop(dest.group(1), None)
            continue
        if insn.mnemonic in _ADDSUB or head in _ADDSUB:
            pair = _SRC2.match(operands)
            dest = _DEST.match(operands)
            if pair and "#" in operands and pair.group(2) in origin:
                origin[pair.group(1)] = origin[pair.group(2)]
            elif dest:
                origin.pop(dest.group(1), None)
            continue
        dest = _DEST.match(operands)
        if dest and head not in ("cmp", "cmn", "tst", "teq", "push", "b",
                                 "it", "ite", "itt"):
            origin.pop(dest.group(1), None)
    return mask


def _masked_args(seed, mask):
    """`emu.make_args` with an arbitrary POINTER MASK rather than a prefix."""
    scalars = emu.make_args(seed, 0)
    pointers = emu.make_args(seed, 4)
    return [pointers[i] if i in mask else scalars[i] for i in range(4)]


#: A self-referential pointee region: every word in it is an address INSIDE it.
#:
#: WHY.  `make_args` points an argument at scratch and `emu` seeds scratch with
#: random bytes, so a POINTER FIELD read out of a pointee is a random 32-bit
#: word and dereferencing it faults.  Firmware written against a driver model
#: chases two or three of those before it does anything:
#:
#:     ((vfn)(*(int *)(*(int *)(*param_1 + 8) + 8)))(*param_1, &local_28, ...)
#:
#: `i2c_read_reg16_be` is exactly that shape.  Measured: it faulted on the
#: SECOND load in every one of 113 candidate fixtures, kept 3, reached 74 % of
#: its instructions and NEVER REACHED ITS OWN CALL -- so the 20-byte descriptor
#: record it builds in stack locals was never passed to anybody and every
#: perturbation of every field survived (19 % kill rate).  That is not a
#: pointee-capture blind spot; the capture was working and there was nothing to
#: capture.
#:
#: A chain region makes every dereference land back inside the region, so the
#: chase terminates in an ordinary oracled call instead of a fault.  Written
#: through the fixture's `abs` dimension, so `tools/parity/emu.py` is not
#: touched -- it is FROZEN (AGENTS.md) and the net core shares it.
CHAIN_BASE = emu.SCRATCH + 0x1000
CHAIN_LEN = 512


def _chain_bytes(stride, residue):
    """Chain image; words at index % 4 == `residue` carry the THUMB BIT.

    A word in this region is used two ways and the two are incompatible: as a
    LOAD BASE it must be 4-aligned (Unicorn rejects the unaligned `ldr`), and
    as a FUNCTION POINTER it must be odd or the `blx` switches to ARM state and
    dies with "Invalid instruction".  No single value is both.

    So which words are odd is swept instead of guessed: 3 strides x 4 residues.
    A function's own hop sequence lands on whichever combination fits it, and
    the coverage-greedy selector keeps only the ones that reach new code.
    Measured on `i2c_read_reg16_be`: 11 of the 12 combinations still fault, and
    `stride 0x04 / residue 2` returns cleanly with `ncalls = 1` and a captured
    20-byte descriptor record -- the first time any fixture has reached that
    function's call at all.
    """
    out = bytearray()
    for index in range(CHAIN_LEN // 4):
        word = CHAIN_BASE + ((index * 4 + stride) % CHAIN_LEN)
        if index % 4 == residue:
            word |= 1
        out += struct.pack("<I", word)
    return bytes(out)


def _cfg_selector_overrides(core, va, size, cap=48):
    """Per-argument branch values recovered from the shipped instructions.

    Reuses tools/cfg_verify.py's selector recovery.  It is imported lazily and
    inside a try: cfg_verify is 27k lines and pulls in the whole catalog stack,
    and this harness must degrade to pure coverage-guided search rather than
    fail when a catalog is missing.
    """
    try:
        import cfg_verify
        ctx = mtcore.core_ctx(core)
        values = cfg_verify.selector_values(ctx["rawread"], va & ~1, size)
        return cfg_verify.build_overrides(values, cap=cap)
    except Exception as exc:                       # noqa: BLE001
        return [{"__error__": str(exc)}] if False else []


#: conditional-branch mnemonic heads (no `b`, no `bl`, no `blx`)
_COND_HEADS = frozenset(mtcore._COND)


def tail_branch_entries(core, va, size):
    """Catalogued entries the function BRANCHES to (not `bl`s) from inside.

    A `blt.w #0x10fbe` out of `fuel_gauge_update` is the function's own
    `return -1` block: Ghidra registered it as a separate function entry, so
    `core.true_extent` -- which must never cross an entry -- stops just before
    it, and the emulator then records 60 phantom "calls" to it while the
    reconstruction, which spells that block inline, simply returns.  Neither
    side is wrong; the CATALOG's function boundary and the RECONSTRUCTION's
    disagree, and no fixture that reaches such a block can decide anything.

    Those fixtures are DROPPED, with the reason recorded in the vector file,
    rather than being reported as a failure -- a suite that emits a false FAIL
    is worse than one that emits none, because it invites a "fix" to correct
    code.  Fixtures that never reach the block are unaffected.
    """
    ctx = mtcore.core_ctx(core)
    base = va & ~1
    out = set()
    for insn in mtcore._MD.disasm(ctx["rawread"](base, size), base):
        head = insn.mnemonic.split(".")[0]
        # NOT `head.startswith("bl")` -- that also matches `blt`, the
        # signed-less-than CONDITIONAL branch, which is exactly the
        # instruction this function exists to find.  (`blt.w #0x10fbe` in
        # `fuel_gauge_update` was silently skipped by that spelling.)
        #
        # CONDITIONAL branches only.  An UNCONDITIONAL `b`/`b.w` to a
        # catalogued entry is an ordinary TAIL CALL and must be compared, not
        # dropped: `ipc_log_forward`, `ipc_send_packet_ch2005`,
        # `send_box_event_ipc` and `sleep_fixed_33_ticks` are 6-12 byte thunks
        # whose entire body is that branch, and treating it as a boundary
        # dispute discarded 113 of 113 fixtures for each -- 0 cases, 0 %
        # coverage, four functions silently untested.
        if head not in _COND_HEADS:
            continue
        if "#" not in insn.op_str:
            continue
        try:
            target = int(insn.op_str.split("#")[-1], 0)
        except ValueError:
            continue
        if base <= target < base + size:
            continue
        if (target & ~1) in ctx["entries"]:
            out.add(target & ~1)
    return out


def _call_count(core, va, size):
    """How many `bl`/`blx` sites the shipped function has."""
    ctx = mtcore.core_ctx(core)
    return sum(1 for insn in mtcore._MD.disasm(ctx["rawread"](va & ~1, size),
                                               va & ~1)
               if insn.mnemonic in ("bl", "blx", "bl.w"))


def _reads_ipsr(core, va, size):
    ctx = mtcore.core_ctx(core)
    for insn in mtcore._MD.disasm(ctx["rawread"](va & ~1, size), va & ~1):
        if insn.mnemonic == "mrs" and "ipsr" in insn.op_str.lower():
            return True
    return False


def candidate_fixtures(core, va, size, nptr=None, seeds=48, float_words=None):
    """Enumerate candidate fixtures, cheapest dimension first.

    `nptr=None` (the default now) DERIVES the pointer mask from the shipped
    instructions; an explicit integer reproduces the old fixed-prefix
    behaviour, which is kept only so the two can be compared.
    """
    out = []
    mask = (pointer_arg_mask(core, va, size) if nptr is None
            else set(range(max(0, min(4, int(nptr))))))
    nptr_meta = len(mask) if nptr is None else int(nptr)
    for t in range(seeds):
        out.append(Fixture.make("seed-%d" % t, _masked_args(t, mask),
                                nptr=nptr_meta, scratch_seed=t,
                                float_scratch=(t % 4 == 3)))
    # THE DERIVED MASK IS ADDED TO THE OLD CONFIGURATION, NEVER SUBSTITUTED
    # FOR IT.  Measured, on `battery_soc_curve_model_init`: the derivation
    # returns {1,2,3} (r0 is only ever PASSED to a callee, as the source
    # argument of an inlined `memcpy`, and this function never dereferences
    # it), and replacing the old prefix-2 configuration took the symbol from
    # FAIL(28/47) to FAIL(0/49).  Both verdicts are legitimate -- the trees
    # agree in both -- but a fixture set that loses inputs is a worse fixture
    # set, and the greedy selector discards anything that adds neither
    # coverage nor a new outcome, so extra bands cost only generation time.
    for label, extra in (("ptr4", {0, 1, 2, 3}), ("ptr2", {0, 1}),
                         ("ptr0", set())):
        if extra == mask:
            continue
        for t in range(4):
            out.append(Fixture.make("%s-%d" % (label, t),
                                    _masked_args(700 + t, extra),
                                    nptr=len(extra), scratch_seed=700 + t))
    # POINTER-CHAIN fixtures (see CHAIN_BASE).  Every pointer argument aims
    # into a region whose every word is another address inside it, so a
    # driver-model dereference chain resolves instead of faulting.  Both with
    # the default oracle and with all callees returning 0, because the shape
    # this unlocks is `if (ops->xfer(...) == 0)`.
    if mask:
        t = 0
        for stride in (0x40, 0x04, 0x100):
            for residue in range(4):
                chain = [(CHAIN_BASE, _chain_bytes(stride, residue))]
                args = _masked_args(800 + t, mask)
                for slot in mask:
                    args[slot] = CHAIN_BASE + 4 * (slot % 4)
                out.append(Fixture.make("chain-%d" % t, args, nptr=len(mask),
                                        scratch_seed=800 + t, abs_mem=chain))
                out.append(Fixture.make(
                    "chain0-%d" % t, list(args), nptr=len(mask),
                    scratch_seed=830 + t, abs_mem=chain,
                    oracle=[(k, r, 0) for k in range(12) for r in (0, 1)]))
                t += 1
    for index, override in enumerate(_cfg_selector_overrides(core, va, size)):
        args = _masked_args(index, mask)
        for slot, value in override.items():
            if isinstance(slot, int) and 0 <= slot < 4:
                args[slot] = value & 0xffffffff
        out.append(Fixture.make("cfgsel-%d" % index, args, nptr=nptr_meta,
                                scratch_seed=index))
    # Sweep the WHOLE float pool through s0, not a sample of it.  This is the
    # float analogue of the CFG selector sweep: a hard-float leaf's control
    # flow and its numeric result both depend on where the argument sits
    # relative to a handful of exact thresholds, and eight samples of a
    # 66-entry pool leave most branch domains visited exactly once.
    pool = emu.FLOAT_POOL if float_words is None else emu.FLOAT_POOL[:float_words]
    for index, word in enumerate(pool):
        out.append(Fixture.make(
            "fp-%d" % index, _masked_args(index, mask), nptr=nptr_meta,
            scratch_seed=index, float_scratch=True,
            fp={0: word, 1: emu.FLOAT_POOL[(index * 13) % len(emu.FLOAT_POOL)]}))
    globals_ = literal_globals(core, va, size)
    for gi, address in enumerate(globals_):
        for vi, value in enumerate(GLOBAL_LADDER):
            out.append(Fixture.make(
                "glob-%d-%d" % (gi, vi), _masked_args(gi * 4 + vi, mask),
                nptr=nptr_meta, scratch_seed=gi * 8 + vi,
                abs_mem=[(address, int(value).to_bytes(4, "little"))]))
    # All globals at once, both extremes: catches a predicate that needs two
    # globals set together (a level AND an enable flag), which the one-at-a-time
    # sweep above structurally cannot reach.
    for vi, value in enumerate((0, 1, 2, 0xffffffff)):
        if globals_:
            out.append(Fixture.make(
                "globall-%d" % vi, _masked_args(100 + vi, mask), nptr=nptr_meta,
                scratch_seed=200 + vi,
                abs_mem=[(a, int(value).to_bytes(4, "little"))
                         for a in globals_]))
    # CALLEE RESULTS.  In call-heavy application code this is the DOMINANT
    # branch selector -- `if (k_msgq_put(...) != 0)`, `if (dev == NULL)`,
    # `switch (parse(...))`.  emu's default oracle returns sha256(ordinal),
    # which is a large arbitrary word, so every `== 0` / `< 0` / small-enum
    # test on a callee result goes exactly ONE way for every fixture.  That is
    # the same defect as AGENTS.md finding #1, one level out: the blind spot is
    # no longer the argument bank but the return bank.
    # Measured before this dimension existed: `fuel_gauge_update` (1,064 bytes,
    # 319 CFG instructions) reached 20 instructions -- 6 % -- across 41
    # fixtures.
    calls = _call_count(core, va, size)
    if calls:
        span = min(max(calls, 1), 48)
        for vi, value in enumerate((0, 1, 2, 0xffffffff, 0xfffffff5, 0x7fffffff)):
            out.append(Fixture.make(
                "orc-all-%d" % vi, _masked_args(400 + vi, mask), nptr=nptr_meta,
                scratch_seed=400 + vi,
                oracle=[(k, 0, value) for k in range(span)] +
                       [(k, 1, value) for k in range(span)]))
        # One call at a time returns 0 while the rest keep the default hash:
        # this separates "the k-th dependency failed" from "all of them did".
        for k in range(min(span, 12)):
            for vi, value in enumerate((0, 1)):
                out.append(Fixture.make(
                    "orc-%d-%d" % (k, vi), _masked_args(500 + k * 2 + vi, mask),
                    nptr=nptr_meta, scratch_seed=500 + k * 2 + vi,
                    oracle=[(k, 0, value), (k, 1, value)]))
    # GLOBAL x CALLEE-RESULT combinations.  Neither sweep alone reaches a
    # predicate that needs both -- `fuel_gauge_update` compares a 64-bit uptime
    # (a callee result) against a stored timestamp (a global), and every
    # one-dimensional fixture leaves the other operand at a random value, so
    # the comparison went the same way every time.  Measured: without these,
    # coverage was 39/338 (12 %).
    if globals_ and calls:
        span = min(max(calls, 1), 48)
        for gi, gvalue in enumerate((0, 1, 0xffffffff)):
            for oi, ovalue in enumerate((0, 1, 0xffffffff, 0x000186a0)):
                out.append(Fixture.make(
                    "combo-%d-%d" % (gi, oi),
                    _masked_args(600 + gi * 4 + oi, mask), nptr=nptr_meta,
                    scratch_seed=600 + gi * 4 + oi,
                    abs_mem=[(a, int(gvalue).to_bytes(4, "little"))
                             for a in globals_],
                    oracle=[(k, r, ovalue)
                            for k in range(span) for r in (0, 1)]))
    if _reads_ipsr(core, va, size):
        for vi, mode in enumerate((0, 16)):
            out.append(Fixture.make("ipsr-%d" % vi, _masked_args(300 + vi, mask),
                                    nptr=nptr_meta, scratch_seed=300 + vi, xpsr=mode))
    return out, globals_


#: Fixtures kept for OUTCOME variety on top of the coverage-greedy set.
#:
#: MEASURED, not assumed.  Pure coverage-greedy selection kept 5 fixtures for
#: `__ieee754_asinf` at 103/103 instructions -- 100% coverage -- and killed only
#: 12 of 20 mutants (60%).  Every survivor was a 1-ULP perturbation of a
#: polynomial coefficient on a path the 5 fixtures DID execute.  Two of those
#: eight are EQUIVALENT MUTANTS, measured: over 200,000 float32 inputs drawn
#: from the branch's reachable domain [2**-27, 0.5), `0x3811ef08+1` and
#: `0x3a4f7f04+1` change the polynomial's float32 result on ZERO of them, so no
#: test can kill them.  The other three coefficients differ on 0.09%, 2.0% and
#: 24% of that domain -- those are real test weaknesses, and their cause is that
#: only ONE kept fixture ever reached the branch.
#:
#: The general lesson, and the fourth distinct way this project has produced a
#: vacuous pass: COVERAGE IS NECESSARY AND NOT SUFFICIENT.  Executing an
#: instruction does not make its result observable.  So a fixture is kept when
#: it produces a NEW OBSERVABLE OUTCOME as well as when it reaches new code --
#: distinct outcomes are precisely what discriminates a mutant.
OUTCOME_CAP = 40


def select(core, va, size, ret_kind="i32", nptr=None, budget=400, max_insns=200000,
           outcome_cap=OUTCOME_CAP):
    """Greedy coverage-maximising subset of the candidate fixtures.

    Returns (kept, coverage, denominator, unresolved, globals, stats).
    A fixture is KEPT only when it executes at least one shipped instruction
    no kept fixture has executed.  A run that faults or does not return is
    still kept if it adds coverage: a deterministic fault is observable
    behaviour and is compared like any other outcome.
    """
    denominator, unresolved = cfg_instructions(core, va, size)
    mask = (pointer_arg_mask(core, va, size) if nptr is None
            else set(range(max(0, min(4, int(nptr))))))
    fixtures, globals_ = candidate_fixtures(core, va, size, nptr=nptr)
    covered = set()
    kept = []
    errors = 0
    outcomes = set()
    outcome_kept = 0
    disputed = tail_branch_entries(core, va, size)
    dropped = 0
    capped = 0
    from core import observable_key
    for fixture in fixtures[:budget]:
        try:
            state, hit = run_original(core, va, size, fixture,
                                      ret_kind=ret_kind, max_insns=max_insns)
        except Exception:                                   # noqa: BLE001
            errors += 1
            continue
        if disputed and any((t & ~1) in disputed
                            for t in state.get("call_targets_full", ())):
            dropped += 1
            continue
        if not state.get("returned") and "error" not in state:
            # The ORIGINAL hit the instruction cap without returning.  emu
            # calls that trial inconclusive for exactly this reason, and so
            # must a frozen vector: the "expectation" would be a snapshot of an
            # unbounded loop truncated at an arbitrary instruction budget, and
            # any candidate whose loop costs a different number of
            # instructions per iteration fails it.  Measured on
            # `ipc_rpmsg_backend_register`: golden ncalls=25000 / returned
            # false, candidate 22222 -- FAIL on BOTH trees, meaning nothing.
            capped += 1
            continue
        new = hit - covered
        # The stack RECORD is part of the outcome.  Without this a fixture that
        # builds a different record but reaches no new instruction and returns
        # the same value is discarded, and the record's field constants are
        # then constrained by whichever single fixture happened to survive
        # coverage-greedy selection.  That is the same "coverage is necessary
        # and not sufficient" trap OUTCOME_CAP exists for, one level in.
        key = repr((observable_key(state, ret_kind), state.get("stack_args")))
        fresh_outcome = key not in outcomes and outcome_kept < outcome_cap
        if new or fresh_outcome or not kept:
            covered |= hit
            outcomes.add(key)
            kept.append((fixture, state, hit))
            if not new:
                outcome_kept += 1
    # Instructions executed that the CFG walker did not predict are real code
    # (they ran).  Fold them into the denominator so the ratio can never be
    # inflated by an incomplete static walk.
    denominator = denominator | covered
    stats = {"candidates": len(fixtures), "kept": len(kept),
             "harness_errors": errors,
             "pointer_arg_mask": sorted(mask),
             "pointer_arg_mask_derived": nptr is None,
             "dropped_extent_dispute": dropped,
             "dropped_instruction_cap": capped,
             "extent_dispute_targets": ["0x%08x" % t for t in sorted(disputed)]}
    return kept, covered, denominator, unresolved, globals_, stats
