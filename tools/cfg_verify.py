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
import sys, os, re, json, glob, struct, math
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

# Prefix-only comparison is a narrowly reviewed property of known firmware
# loops, never a capability supplied by candidate source text.  Values are the
# exact ordered-event prefix lengths compared for each reviewed entry point.
REVIEWED_PREFIX_PROOFS = {
    ("app", 0x00016eb8): 500,
    ("app", 0x00019718): 200,
    ("app", 0x00021da8): 80,
    ("app", 0x00023844): 20,
    ("app", 0x0002685c): 150,
    ("app", 0x000286f8): 200,
    ("app", 0x00028a1c): 200,
    ("app", 0x0002a4f4): 200,
    ("app", 0x0002a8d8): 240,
    ("app", 0x000324bc): 200,
    ("app", 0x000438d0): 200,
    ("app", 0x0004c4d0): 200,
    ("app", 0x00050170): 200,
    ("app", 0x00056704): 200,
    ("app", 0x000729fc): 200,
    ("app", 0x0007e526): 200,
    ("net", 0x01022774): 200,
    ("net", 0x010255a4): 200,
    ("net", 0x0102b5bc): 200,
    ("net", 0x0102f4ec): 200,
}

# Direct callees absent from, or ambiguous in, the decompiler catalog.  These
# are reviewed AAPCS argument counts; registers above the true arity are caller
# scratch and must not create false mismatches merely because GCC leaves a
# different stale value in them.
CALL_ARITY_OVERRIDES = {
    # Floating formatter helpers: the dtoa call uses r0-r3 plus four stacked
    # scalar arguments (the double itself is in d0); width setup has one
    # stacked callback; all comparison helpers consume both 64-bit operands.
    ("app", 0x00086cda): 4,
    ("app", 0x00086e1c): 4,
    ("app", 0x0000ddf0): 4,
    ("app", 0x0000dddc): 4,
    ("app", 0x0000ddc8): 4,
    ("app", 0x00052f18): 2,  # lookup consumes only key and zero-valued selector
    # Inlined fatal SVC boundary in the event worker consumes only r0=reason.
    ("app", 0x0005463e): 1,
    ("app", 0x00054688): 1,
    ("net", 0x0102524c): 1,  # state selector consumes only the mode value
    ("net", 0x0103b304): 1,  # snapshot helper consumes its output pair only
    # ARCH_EXCEPT's SVC boundary consumes only r0 (the reason code).  r1-r3
    # remain caller scratch and differ when CMSIS chooses a temporary register
    # for the preceding BASEPRI write.
    ("net", 0x01039bba): 1,
    ("app", 0x0000db4c): 2,
    ("app", 0x00076d8c): 1,
    ("app", 0x00076cec): 2,
    ("app", 0x00058f34): 3,
    ("app", 0x0005f5d0): 2,
    ("app", 0x000821a4): 2,
    ("app", 0x0004a46c): 2,
    # Byte-to-length mapper consumes only its byte selector; r1-r3 around the
    # call are scheduler temporaries, not part of its semantic ABI.
    ("app", 0x0004e98c): 1,
    # Wrap marker consumes the buffer and contiguous-word count; its body uses
    # only r0/r1, while r2/r3 are lock temporaries at the allocator call site.
    ("app", 0x0007e390): 2,
    ("app", 0x00016574): 1,
    ("app", 0x00074d74): 1,  # work submission consumes queue node only
    ("app", 0x00086534): 2,  # object initializer consumes object and mode
    ("app", 0x000851ca): 2,  # pin-mode selector consumes pin and mode only
    ("app", 0x000850d8): 1,  # one-tick busy-wait; r1-r3 are stale caller scratch
    # Four-byte veneer forwards the request object to its unary cleanup body.
    ("app", 0x00080ae2): 1,
    ("app", 0x00084b14): 2,  # controller toggle consumes handle and enable only
    ("net", 0x0102583c): 1,
    ("net", 0x01037e10): 2,
    ("net", 0x0102e460): 2,
    ("net", 0x010345f4): 1,
    ("net", 0x01034650): 1,  # channel-index mapper consumes only the index
    ("net", 0x0102e1fc): 1,  # notification consumes the updated object only
    ("net", 0x01032988): 0,
    ("net", 0x0103b224): 2,
    ("net", 0x010374dc): 1,
    ("net", 0x0101e660): 1,
    ("net", 0x01029638): 0,
    ("net", 0x010218cc): 2,  # request object and immutable descriptor
    ("net", 0x010218c0): 2,  # request object and type selector
    ("app", 0x00019950): 1,  # BLE worker initializer consumes context only
    ("app", 0x0007c172): 1,  # k_sem_give thunk consumes only the semaphore
    ("app", 0x00086698): 0,  # 64-bit clock query returns r1:r0; no arguments
    ("app", 0x000835ae): 3,  # block transform consumes dst, src, and byte count
    ("app", 0x000826b2): 2,  # byte-sequence comparator consumes pointer and key
    ("app", 0x000814e6): 2,  # slot comparator consumes selector and tag byte
    ("app", 0x000735cc): 1,  # subsystem initializer consumes its object only
    # Wrapper immediately moves incoming r0 to r1, replaces r0 with its fixed
    # object, and tail-calls 0x73424; incoming r1-r3 are provably dead.
    ("app", 0x000531d8): 1,
    ("app", 0x00030178): 2,  # register write: address and value
    ("app", 0x0004b908): 1,  # one-time scheduler initializer consumes object only
    ("app", 0x0005caa4): 1,  # bit-pool lookup consumes only the kind selector
    # Event-buffer ownership helpers are unary.  The pending-payload fixture
    # shifts them to later call ordinals where r1-r3 retain different stack
    # temporaries across code generation; those registers are not their ABI.
    ("app", 0x0005f24c): 1,
    ("app", 0x0005f2d4): 1,
    ("app", 0x000543c8): 1,
    # Structured logger consumes source, level and the diagnostic-record
    # pointer.  Its decompiled body is an assembly/varargs boundary and the
    # generic catalog incorrectly reports zero register arguments.
    ("app", 0x00080ea2): 3,
    # Tail cleanup consumes only the initialization request in r0.  The byte
    # and list-link temporaries left in r1-r3 are caller scratch.
    ("app", 0x00068298): 1,
    ("app", 0x0008688e): 2,  # event object and event type
    ("app", 0x000738d4): 0,  # scheduler wakeup has no arguments
    ("app", 0x00072880): 1,  # event release consumes its event object only
    ("app", 0x000538f8): 3,  # handle, reason and failed buffer
    ("app", 0x00063b7c): 2,  # event selector and optional context
    # The queue handoff consumes the first three register arguments; its r3
    # formal is unused.  Two additional semantic fields are stacked and were
    # recovered directly from the caller/callee disassembly.
    ("app", 0x00073f6c): 3,
    ("app", 0x00065434): 1,  # channel lookup consumes the channel selector
    ("app", 0x00065478): 1,  # mode lookup consumes the channel selector
    ("app", 0x000257ec): 3,  # object, operation selector, request pointer
    ("app", 0x00083dc8): 4,  # object plus all three bytes stored by the callee
    ("app", 0x000638dc): 2,  # timer-head notification: timestamp and flags
    ("net", 0x01008d00): 2,  # assertion endpoint consumes module and line
    # These two four-byte veneers branch to zero-argument state initializers;
    # all live caller-scratch registers at the veneer call sites are stale.
    ("net", 0x010294ba): 0,
    ("net", 0x010294be): 0,
    # Radio state update consumes only the channel and mode.  Its remaining
    # live registers are forwarded solely to the two-argument assertion sink.
    ("net", 0x010202fc): 2,
    # The clock veneer and time-window helper consume zero and two arguments;
    # their higher live registers are caller scratch or assertion diagnostics.
    ("net", 0x01022f08): 0,  # four-byte veneer for FUN_01025034
    ("net", 0x01025034): 0,
    ("net", 0x0100d4d0): 2,
    # The scheduler record helper consumes start, end and the 16-bit span.
    # r3 is used only as stale diagnostic material on its fatal-only branch.
    ("net", 0x010217ac): 3,
    ("net", 0x01020270): 1,  # controller timing selector; higher regs are stale
    ("net", 0x010212ec): 2,  # direction and PHY selector
    ("net", 0x01025c44): 1,  # controller mode selector
    ("net", 0x010256dc): 2,  # fatal endpoint consumes module and line
    ("net", 0x010250d0): 1,  # scheduler operation selector
    ("net", 0x0100dfbc): 2,  # formatter body consumes only buffer and type
    ("net", 0x0103aec2): 1,  # lock-release tail consumes only the lock object
    ("net", 0x01020764): 1,  # packet submission consumes only its packet pointer
    ("net", 0x010129e8): 1,  # controller subobject initializer is unary
    ("net", 0x010129f4): 1,  # controller subobject finalizer is unary
    ("net", 0x0100f368): 3,  # bounded renderer consumes object, offset and span
    ("net", 0x0100f5d8): 0,  # radio finalizer has no arguments
    ("net", 0x010217cc): 0,  # scheduler unlock/notify helper has no arguments
    ("net", 0x0100ca98): 2,  # selector and one-byte output pointer
    ("net", 0x0100d14c): 2,  # object lock/unlock consumes object and state
    ("net", 0x0101bbc0): 1,  # radio object finalization is unary
    ("net", 0x0103a44c): 1,  # allocator lookup consumes its fixed pool only
    ("net", 0x01034d8c): 2,  # logger setup consumes selector and format
    ("net", 0x0103aec6): 1,  # lock acquisition consumes the lock object only
    ("net", 0x01034dd8): 1,  # controller-log consumer takes the buffer only
    ("net", 0x01036f74): 1,  # scheduler-head notification consumes one boolean
    ("net", 0x0103735c): 2,  # ready-list removal takes list head and node
    ("net", 0x0103719c): 1,  # zero-delay activation takes the owner only
    ("net", 0x010372b4): 0,  # scheduler handoff tail takes no arguments
    ("net", 0x0102eb8c): 3,  # subsystem, operation and value
    ("net", 0x01030014): 2,  # allocated object and enable flag
    ("net", 0x0103b2b4): 0,  # scheduler reschedule tail has no arguments
    ("app", 0x0004372c): 1,
    ("app", 0x0004d468): 3,
    ("app", 0x0004d8b8): 1,
    ("app", 0x0007c85e): 4,  # forwarding wrapper preserves transfer ABI
    # Zephyr syscall veneer consumes the complete r0-r3 register ABI.  Several
    # callers pass timeout/status words in r1-r3; treating it as unary masks
    # stale-register reconstructions (notably ble_work_thread).
    ("app", 0x00072908): 4,
    ("app", 0x00018ff8): 1,  # event dequeue takes the event object
    ("app", 0x000191e4): 0,  # notification reset has no arguments
    ("app", 0x00075f88): 0,  # hard-float s0 argument; no GPR arguments
    ("app", 0x00075d5c): 0,  # libLC3 log10f helper consumes s0 only
    ("app", 0x000868ee): 0,  # hard-float s0 argument; no GPR arguments
    ("app", 0x000807f2): 0,
    ("app", 0x00076a88): 1,
    ("app", 0x00086976): 1,  # scaling exponent in r0; sample is hard-float s0
    ("app", 0x00084fd4): 0,
    ("app", 0x0007ef3e): 0,
    ("app", 0x00081746): 3,  # structured logger: sink, level, record pointer
    ("app", 0x00081b30): 1,
    ("app", 0x00074844): 2,  # timestamp helper consumes selector and mode
    ("app", 0x000250f8): 3,  # encoder consumes three byte-array pointers
    ("app", 0x00080000): 2,  # printf_like output callback: byte and context
    ("app", 0x0007d37a): 1,  # panoramic-map completion consumes buffer only
    ("app", 0x00075174): 1,  # startup object registration consumes object only
    ("app", 0x00025d40): 1,  # startup transport initializer consumes descriptor
    ("app", 0x0002e4e8): 3,  # hardware-id reader writes three output words
    ("app", 0x000622a0): 1,  # display startup consumes its device descriptor
    ("app", 0x00026250): 1,  # display vtable initializer consumes object only
    ("app", 0x00023df4): 0,
    ("app", 0x00023d0c): 0,
    ("app", 0x00023acc): 0,
    ("app", 0x000243fc): 0,
    ("app", 0x0000e954): 1, ("app", 0x0000e9b4): 1,
    ("app", 0x0008693c): 0, ("app", 0x00086902): 0,
    ("app", 0x0000ea18): 3, ("app", 0x0000eb7c): 2,
    ("app", 0x0000ea70): 3, ("app", 0x00075c90): 0,
    ("app", 0x0000d848): 1, ("app", 0x0000de18): 4,
    ("app", 0x00086c78): 3, ("app", 0x0000e938): 0,
    ("app", 0x0000e3a0): 3, ("app", 0x0000ea4c): 2,
    ("app", 0x000868fc): 0, ("app", 0x00075dc8): 0,
}

CALL_FLOAT_ARITY_OVERRIDES = {
    ("app", 0x00086cda): 2,  # one hard-float double in d0 (s0:s1)
    ("app", 0x000265e8): 1,  # reciprocal-square-root helper consumes s0
    # Interpolator consumes five hard-float arguments in s0-s4; its four
    # remaining arguments occupy r0-r3.
    ("app", 0x0000e53c): 5,
    ("app", 0x00075f88): 1,
    ("app", 0x00075d5c): 1,
    ("app", 0x000868ee): 1,
    ("app", 0x00086976): 1,
    ("app", 0x0008693c): 2, ("app", 0x00086902): 2,
    ("app", 0x0000eb7c): 1, ("app", 0x0000ea70): 1,
    ("app", 0x00075c90): 1, ("app", 0x0000e938): 1,
    ("app", 0x0000e3a0): 2, ("app", 0x000868fc): 1,
    ("app", 0x00075dc8): 1,
}

def _decompiled_arity(func):
    """Best-effort direct-call arity from Ghidra's decompiled declaration."""
    text = func.get("decompiled") or ""
    name = func.get("ghidra_name") or func.get("name") or ""
    m = re.search(r'\b' + re.escape(name) + r'\s*\(([^)]*)\)', text)
    if not m:
        return None
    params = m.group(1).strip()
    if not params or params == "void":
        return 0
    if "..." in params:
        return 4  # varargs: r0-r3 may all be semantically live
    return min(4, len([p for p in params.split(",") if p.strip()]))
# Ghidra/classification under-reports these resolved jump-table bodies. Values
# are CFG-confirmed executable extents, not trailing data-table inflation.
TRUE_SIZE_OVERRIDES = {
    # The catalog cuts the formatter inside its final width-padding loop at
    # 0x77578.  The loop backedge and return join continue through 0x7758a;
    # 0x77592 is alignment and FUN_00077594 starts the next function.
    ("app", 0x0007712c): 0x466,
    # The catalog stops in the final unknown-command diagnostic island.  The
    # owned callback tail returns at 0x219fc; the following word is a literal.
    ("app", 0x00021460): 0x59c,
    # The final mode-two glyph-spacing backedge at 0x44520 is executable.
    # Catalog size 0x262 stops before that branch; literals begin at 0x44524.
    ("app", 0x000442bc): 0x266,
    # Ghidra folds 3.2 KiB of following libm helpers into this 94-byte VFP
    # domain wrapper.  Its tail branch completes at 0x75dba; literals follow.
    ("app", 0x00075d5c): 0x5e,
    # The catalog stops at 0x7855c in the middle of the rounding tail.  The
    # reachable load, BL FUN_00087510, comparison, and return join continue
    # through 0x7856a; 0x7856c is the following literal pool.
    ("app", 0x00078110): 0x45a,
    # Two-argument context wrapper ends at its tail branch at 0x778de.  The
    # catalog's remaining bytes are distinct wrappers/functions.
    ("app", 0x000778d4): 0x0a,
    ("app", 0x00085df6): 0x24,  # next decoder routine starts at 0x85e1a
    ("app", 0x0008633e): 0x06,  # unary wrapper tail ends at 0x86344
    ("app", 0x00086378): 0x08,  # following independent thunk starts 0x86380
    # Event renderer ends after its three owned diagnostic islands; the old
    # catalog size folds several independent helpers beginning at 0x101bb94.
    ("net", 0x0101ba58): 0x13c,
    # Final copy loop and misalignment return end at 0x0102bfdc; literals
    # follow before the next independent function at 0x0102bfe4.
    ("net", 0x0102bbec): 0x3f0,
    # The catalog folds the literal pool and three following lock helpers into
    # this scheduler-table initializer.  Its final owned tail branch ends at
    # 0x010360f6; literals begin at 0x010360f8.
    ("net", 0x0103601c): 0xda,
    # This wrapper ends in a tail branch at 0x84e62.  Ghidra folded the next
    # two entry points into the 34-byte catalog range.
    ("app", 0x00084e58): 0x0e,
    # Default switch diagnostics live just beyond the catalog ends.  Each
    # extent stops after its owned noreturn BL, before the following literals.
    ("net", 0x0101bdd4): 0x10e,
    ("net", 0x01020a00): 0x60,
    # printf-like's catalog end cuts the final sign/digit/padding islands at
    # 0x010395d8.  All remain CFG-reachable and rejoin the parser loop through
    # 0x01039618; 0x0103961a begins alignment before the next function.
    ("net", 0x01039190): 0x48a,
    # Ghidra folded two following init/cleanup routines into this symbol.
    # FUN_00068240 itself tail-branches at 0x68276; 0x6827a is padding and
    # the next routine starts at 0x6827c.
    ("app", 0x00068240): 0x3a,
    # The catalog stops at 0x6c75c, cutting the final interpolation arm.
    # Reachable code continues through the return at 0x6c774.
    ("app", 0x0006bfc8): 0x7ae,
    # Serializer catalog end 0x4afe2 cuts the deferred-index emission path in
    # half. Reachable code returns/terminates through 0x4b002; literals begin
    # at 0x4b004 and the next function starts at 0x4b01c.
    ("app", 0x0004abc0): 0x444,
    ("net", 0x01020168): 0xc2,  # default noreturn call completes at 0x0102022a
    ("net", 0x01021cec): 0xf8,  # selector panic call completes at 0x01021de2
    # Net catalog entries below stop at the first instruction after an
    # exclusive-access opcode.  Their straight-line CFGs continue to the
    # reviewed returns shown here; the following words/prologues are separate.
    ("net", 0x01031248): 0x38,  # return at 0x0103127e
    ("net", 0x010312d0): 0x3c,  # return at 0x0103130a
    ("net", 0x010122fc): 0x30,  # shared slow path returns at 0x0101232c
    ("net", 0x0102d938): 0xdc,  # final error return branches through 0x0102da12
    ("net", 0x0103a076): 0xb6,  # all init/error arms return by 0x0103a12a
    ("net", 0x01028464): 0x22,  # TBB call/return tail ends at 0x01028486
    ("net", 0x01028486): 0x22,  # duplicate wrapper tail ends at 0x010284a8
    ("net", 0x01032764): 0x2e,  # final switch arm/default return end at 0x01032792
    ("net", 0x0100d58c): 0x3c,  # default arm owns noreturn diagnostic BL at 0x0100d5c4
    ("net", 0x010333b4): 0x22c, # radio-owner init returns before literals at 0x010335e0
    ("app", 0x0007d1d6): 0x40,  # tail branch ends at 0x7d216; next prologue is separate
    # 39-entry PUT TBH dispatcher. Ghidra stores 25,616 executable bytes as
    # disjoint ranges separated by literal islands; the last handler returns
    # at 0x2130a, so verification must retain the complete address extent.
    ("app", 0x0001a75c): 0x6bae,
    # Even-AI's catalog end at 0x3cac4 cuts off the phase-0/2 dispatch islands
    # and final streaming renderer.  CFG-reachable code continues through the
    # return at 0x3cb2a; the literal pool starts at 0x3cb2c.
    ("app", 0x0003bfe0): 0x0b4c,
    # QuickNote's catalog end at 0x3bd9c cuts the state-2 deadline arithmetic
    # in half.  Executable timeout/warning/exit blocks continue through the
    # return at 0x3bdde; the first trailing literal follows that boundary.
    ("app", 0x0003b824): 0x05ba,
    # Dashboard action branches 4/6/7 live after the catalog's 0x3b6c4 end
    # and rejoin the shared update/return tail through 0x3b75c.  The following
    # word is the first literal; treating these blocks as callees hides the
    # late selector arms and manufactures FUN_000167a8 target mismatches.
    ("app", 0x0003af78): 0x07e6,
    # printf_like's catalog size stopped at 0x11fca, but its float/integer
    # formatting tails remain CFG-reachable through 0x12272.  Literal words
    # begin at 0x12274; treating the late blocks as callees masked formatter
    # semantics and manufactured false target mismatches.
    ("app", 0x000113a8): 0x0ecc,
    # Panoramic-map display's catalog end (0x3f208) cuts off numerous branch
    # islands.  CFG-reachable code continues through 0x3f476; its literal pool
    # begins at 0x3f478.
    ("app", 0x0003e7f8): 0x0c80,
    # Dashboard refresh has a literal island at 0x3aba0 followed by
    # CFG-reachable late branch islands (including 0x3acc6) through 0x3ae48.
    # The final island's literal pool begins at 0x3ae58.
    ("app", 0x0003727c): 0x3bdc,
    # main has late initialization/error branch islands through 0x17660; its
    # final literal pool begins at 0x17664.
    ("app", 0x00016eb8): 0x07ac,
    # The entry TBH case 5 lands at 0x467e2 and owns a nested TBB through
    # 0x46994.  The catalog stopped at the case target and misclassified the
    # complete tail as an external boundary; literals begin at 0x46998.
    ("app", 0x0004588c): 0x110c,
    # Final interpolation fallback at 0xe910 rejoins the shared result tail at
    # 0xe928; catalog truncation made that in-body branch look like an external
    # recursive oracle boundary.  Return is at 0xe936.
    ("app", 0x0000e53c): 0x3fc,
    # Full libLC3 SNS analyzer owns embedded literal islands and branch tails
    # through 0x6efd7; 1002 bytes is only its first code island.
    ("app", 0x0006c778): 0x2860,
    # libLC3 spectrum analyzer includes late gain-adjust branch islands through
    # 0x6f91b; the classified 1098-byte span truncates them at 0x6f8ea.
    ("app", 0x0006f4a0): 0x47c,
    # TBB cases 0x19/0x1a land at 0x23a0c; catalog 456 truncates their final
    # MOV/B before the literal pool at 0x23a14.
    ("app", 0x00023844): 0x1d0,
    ("app", 0x0002a8d8): 0x3f4,  # live thread tail ends at 0x2acca; literals start 0x2accc
    ("app", 0x0000fcf0): 0x178,  # state machine code continues through 0xfe66; literals start 0xfe68
    # liblc3 detect_pitch tail extends twelve bytes past the catalog boundary.
    ("app", 0x000698d0): 0x0c82,
    # libLC3 fft owns its catalogued body through the late shared epilogues at
    # 0x6b990/0x6b99a.  0x6b9b8 is a distinct lc3_mdct_forward entry (full
    # prologue and a direct BL caller at 0x69318), not an FFT continuation.
    ("app", 0x0006b3c8): 0x05ea,
    # Function returns at 0x5991a; 0x5991c is its literal and the catalog's
    # 478-byte span incorrectly folds the distinct function at 0x59920.
    ("app", 0x00059834): 0xe6,
    # Transition engine returns at 0x4b88c; the classified 0x35a-byte span
    # truncates its callback-drain and lock-reacquire epilogue.
    ("app", 0x0004b4fc): 0x394,
    ("net", 0x010119ac): 0x1d8,
    # The catalog stops at 0x100b568 even though the entry validation branches
    # to its owned fatal-reporting island at 0x100b578.  Retain that BL through
    # its noreturn boundary at 0x100b582 instead of inventing an external
    # FUN_0100b578 call.
    ("net", 0x0100b180): 0x402,
    # The catalog drops the final POP at 0x100dffe and the switch default's
    # fatal-reporting island at 0x100e000.  Both are CFG-reachable body code;
    # the noreturn BL completes at 0x100e008.
    ("net", 0x0100dfbc): 0x4c,
    # Catalog ends after the default arm's argument setup at 0x100ae94.  The
    # owned noreturn BL at 0x100ae96 completes the global-state TBB default;
    # the literal pool starts at 0x100ae9c.
    ("net", 0x0100ac98): 0x202,
    # The catalog's 0x26-byte extent ends in the middle of `mov.w r1,#0x2a8`.
    # The default arm owns the following module load and noreturn assertion BL;
    # the next independent prologue starts at 0x101e2fc.
    ("net", 0x0101e2cc): 0x30,
    # Thin wrapper ends at the tail branch; catalog folds FUN_0007d3ee.
    ("app", 0x0007d3dc): 0x12,
    # Constructor wrapper ends at 0x7eea6; catalog folds several following
    # library helpers through 0x7ef90.
    ("app", 0x0007ee74): 0x32,
    # Fatal mode tail branches back to the shared noreturn call at 0x10303c6;
    # catalog size 266 stopped immediately before this final instruction.
    ("net", 0x0103038c): 0x10c,
    ("app", 0x00028a1c): 0x198,  # reviewed persistent-input thread body
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
    # Catalog ends at 0x5bba4, inside the default/state-gate tails.  The shared
    # return completes at 0x5bbaa; literals begin at 0x5bbac.
    ("app", 0x5b9cc): 0x1e0,
    # Four-argument dispatcher ends before literal data at 0x30d0a.
    ("app", 0x30cd0): 0x3a,
    # Privacy admission wrapper tail-branches at 0x5508a; next symbol starts 0x55094.
    ("app", 0x5505c): 0x34,
    ("app", 0x531cc): 0x8,
    # Catalog stops at 0x77790 immediately after the `%s` helper call, but the
    # reachable shared formatter/callback and padding tail continues through
    # 0x777e7.  Literal data begins at 0x777e8.
    ("app", 0x77594): 0x254,
    # Ten bytes of executable wrapper plus alignment/literal ownership to 0x4d586.
    ("app", 0x4d578): 0xe,
    # Three-instruction range check/tail wrapper; literal data begins at 0x4e99c.
    ("app", 0x4e98c): 0x10,
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
    # Catalog entries stop after their first instruction(s); each reviewed
    # body continues to the next symbol boundary shown here.
    ("net", 0x0102de38): 0x14,  # atomic exchange; literal follows at +0x14
    ("net", 0x01039fb6): 0x0e,  # atomic exchange retry loop
    ("net", 0x0103a294): 0x12,  # atomic fetch-add retry loop
    ("net", 0x0103a3ce): 0x08,  # load saved PSPLIM and restore it
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
    # Allocator CFG ends at 0x4bdf2.  Bytes 0x4bdf4..0x4be0a are its literal
    # pool and 0x4be0c begins the next function; neither belongs to this body.
    ("app", 0x4bc8c): 0x166,
    # This wrapper ends at 0x4d16a; 0x4d16c is its literal and 0x4d170 is the
    # next function, previously folded into the catalog extent.
    ("app", 0x4d100): 0x70,
    # NCS mpsc_pbuf_claim internal entry; code ends at 0x4bfae and the owned
    # checked-lock assertion literals end immediately before 0x4bfc8.
    ("app", 0x4beb8): 0x110,
}

# net_recon_kit is used by reconstruction workers before this verifier runs.
# Keep its disassembly/proof extents exactly synchronized with the authoritative
# CFG-reviewed net entries above; fail import loudly if either registry drifts.
_NET_TRUE_SIZE_OVERRIDES = {
    va: size for (core, va), size in TRUE_SIZE_OVERRIDES.items() if core == "net"
}
if net_recon_kit.TRUE_SIZE_OVERRIDES != _NET_TRUE_SIZE_OVERRIDES:
    missing = sorted(_NET_TRUE_SIZE_OVERRIDES.keys() -
                     net_recon_kit.TRUE_SIZE_OVERRIDES.keys())
    extra = sorted(net_recon_kit.TRUE_SIZE_OVERRIDES.keys() -
                   _NET_TRUE_SIZE_OVERRIDES.keys())
    wrong = sorted(va for va in (_NET_TRUE_SIZE_OVERRIDES.keys() &
                                 net_recon_kit.TRUE_SIZE_OVERRIDES.keys())
                   if _NET_TRUE_SIZE_OVERRIDES[va] !=
                   net_recon_kit.TRUE_SIZE_OVERRIDES[va])
    raise RuntimeError("net TRUE_SIZE_OVERRIDES drift: missing=%r extra=%r wrong=%r" %
                       (missing, extra, wrong))

_APP_TRUE_SIZE_OVERRIDES = {
    va: size for (core, va), size in TRUE_SIZE_OVERRIDES.items() if core == "app"
}
if recon_kit.TRUE_SIZE_OVERRIDES != _APP_TRUE_SIZE_OVERRIDES:
    missing = sorted(_APP_TRUE_SIZE_OVERRIDES.keys() -
                     recon_kit.TRUE_SIZE_OVERRIDES.keys())
    extra = sorted(recon_kit.TRUE_SIZE_OVERRIDES.keys() -
                   _APP_TRUE_SIZE_OVERRIDES.keys())
    wrong = sorted(va for va in (_APP_TRUE_SIZE_OVERRIDES.keys() &
                                 recon_kit.TRUE_SIZE_OVERRIDES.keys())
                   if _APP_TRUE_SIZE_OVERRIDES[va] !=
                   recon_kit.TRUE_SIZE_OVERRIDES[va])
    raise RuntimeError("app TRUE_SIZE_OVERRIDES drift: missing=%r extra=%r wrong=%r" %
                       (missing, extra, wrong))

# Reviewed ABI returns where the generic "last s0/d0 writer" heuristic sees
# an internal floating-point temporary rather than the actual function result.
RETURN_KIND_OVERRIDES = {
    ("app", 0x00086cda): "i32",  # digit-buffer pointer in r0
    # Signed double-to-integer conversion returns the complete r1:r0 pair.
    # Its catalog signature loses the high word, which previously let callers
    # manufacture that word from unrelated caller scratch.
    ("app", 0x0000ec34): "i64",
    # The catalog marks this status-returning field update as void, but its
    # caller immediately branches on signed r0.
    ("app", 0x00083dc8): "i32",
    ("app", 0x0001a75c): "void",
    ("net", 0x0103a2f8): "void",  # notification procedure has no ABI result
    ("app", 0x0000c358): "void",
    ("app", 0x0006ab80): "i32",  # bool result is returned in r0, not stale s0
    ("app", 0x00086c44): "i32",  # memmove returns its destination in r0
    ("app", 0x0000e2b4): "void",  # wrapper stores result through its fourth pointer
    ("app", 0x0000e2b4): "void",  # interpolation wrapper publishes through r3
    ("app", 0x0006b3c8): "i32",  # liblc3 fft returns a complex-buffer pointer
    ("app", 0x0006b9b8): "void",  # libLC3 forward MDCT publishes through d/y
    ("app", 0x0006c778): "void",  # libLC3 SNS analysis publishes through data/y
    ("app", 0x0006bfc8): "void",  # interpolation worker publishes through output
    # libLC3 analysis/quantization procedures have no ABI return value.  In
    # particular s0 remains caller-scratch after their hard-float helper call.
    ("app", 0x0006f164): "void",
    ("app", 0x0006f4a0): "void",
}

# Original firmware bytes are immutable evidence.  Emulator workarounds must
# be generic execution-model fixes with independent regression tests; they may
# never rewrite selected input functions merely to obtain a passing verdict.
ORIGINAL_BYTE_PATCHES = {}

# Full-width fuzz values are not useful for caller-supplied iteration counts:
# they only spend the instruction budget repeating an already-covered body.
# Keep these reviewed loop counts small while the remaining arguments and RAM
# state retain their normal randomized coverage.
BOUNDED_RANDOM_ARGS = {
    # Radio-mode TBB domain plus invalid/default neighbors.
    ("net", 0x01020168): {0: (0, 1, 2, 3, 4, 5, 8, 9)},
    # Timeline update's unsigned validity interval and byte threshold input.
    ("net", 0x01023ea8): {
        0: (0x75, 0x76, 0x77, 0x0f423fff, 0x0f424000, 0x0f424001),
        1: (0, 1, 2, 0x7f, 0xff),
    },
    ("net", 0x01038654): {1: (0, 1, 2, 3)},
    # Bluetooth connection setup accepts only these four PHY/rate selectors;
    # other full-width values deliberately enter the fatal exception path and
    # do not exercise the long setup body.
    ("net", 0x01019aa0): {3: (1, 2, 4, 8)},
    # The second argument is an iteration count, not an unconstrained scalar.
    # Zero, one and two cover the skip, single-body and back-edge paths.
    ("net", 0x0101da18): {1: (0, 1, 2)},
    # Scheduler queue index; the firmware table has a small fixed domain.
    ("net", 0x01022774): {0: (0, 1, 2)},
    # Bitmap compositor dimensions: cover empty, one-element and backedge
    # paths without interpreting arbitrary 32-bit fuzz as image dimensions.
    ("app", 0x0007d586): {2: (0, 2, 4), 3: (0, 1, 2)},
    # Count of fixed-stride records in the first validation array.
    ("app", 0x000811ce): {2: (0, 1, 2)},
    # Big-integer exponent walker.  Argument 2 is consumed two bits first and
    # then one bit per list node with an arithmetic shift; arbitrary negative
    # fuzz values intentionally never converge.  These values cover the
    # low-bit prelude, skipped loop, both loop branches and multiple backedges.
    ("app", 0x0007893c): {2: (0, 1, 2, 3, 4, 5, 8, 12, 0x1c)},
    # Big-integer left shift. Argument 2 is a bit count; its quotient by 32
    # directly controls two limb-copy loops. Full-width fuzz values turn a
    # finite caller-sized operation into billions of iterations. These values
    # cover zero/nonzero remainders, the 31/32 boundary, and multiple limbs.
    ("app", 0x000789f0): {2: (0, 1, 31, 32, 33, 63, 64, 65)},
    # Checksum input and padded byte length; cover empty, one word, padding,
    # and two loop backedges without manufacturing billion-iteration buffers.
    ("app", 0x0007cf34): {1: (0, 4, 8), 2: (0, 4, 8)},
}

# Raw entry-register callback: FUN_00077594 saves r3 in r10 at 0x775a2 and
# invokes it at 0x777aa/0x777ca. Keep it at a deterministic external Thumb VA.
FIXED_EXTERNAL_CALLBACK_ARGS = {
    ("app", 0x00077594): {3: 0x00080001},
    # printf's floating formatter invokes the caller-supplied output function
    # from r3 after several fixed helper calls.
    ("app", 0x0007712c): {3: 0x00080001},
    ("app", 0x00055710): {0: 0x00080001},
}

# Narrow reviewed contracts for external callees that initialize caller-owned
# stack objects.  Entries are ordinal -> (argument register, offset, bytes).
REVIEWED_ORACLE_MEMORY_WRITES = {
    # dtoa publishes sign, decimal position, and digit count through one core
    # and two AAPCS stack-passed output pointers (arguments 3, 4, and 6).
    ("app", 0x0007712c): {
        4: [(3, 0, b"\x00", 0x00086cda),
            (4, 0, (1).to_bytes(4, "little"), 0x00086cda),
            (6, 0, (1).to_bytes(4, "little"), 0x00086cda)],
    },
    ("net", 0x010195f8): {
        1: [(1, 0, (emu.SCRATCH + 0x3000).to_bytes(4, "little"), 0x0102714a),
            (2, 0, bytes(2), 0x0102714a)],
    },
    ("net", 0x010198cc): {
        2: [(1, 0, (emu.SCRATCH + 0x3000).to_bytes(4, "little"), 0x0102714a),
            (2, 0, bytes(2), 0x0102714a)],
    },
    # The first call is the firmware's memset-compatible buffer initializer.
    ("app", 0x00064a88): {0: [(0, 0, bytes(36))]},
    # Queue receive fills the caller-owned 200-byte payload on success before
    # the wrapper copies it to its destination.  A nonuniform fixture catches
    # truncation, offset, and ordering errors in the success branch.
    ("app", 0x00019c44): {
        0: [(1, 0, bytes((i * 37 + 11) & 0xff for i in range(200)))],
    },
    # Position lookup publishes the available byte count through r1.
    ("net", 0x0103576c): {0: [(1, 0, (32).to_bytes(4, "little"))]},
    # Timeline conversion fills an eight-byte time pair and one-byte status.
    ("net", 0x01023ea8): {0: [(1, 0, bytes(8)), (2, 0, bytes(1))]},
    # State initializer receives handle and auxiliary values through two
    # compiler-local output slots before consuming the handle.
    ("net", 0x01019588): {
        1: [(1, 0, (emu.SCRATCH + 0x1000).to_bytes(4, "little")),
            (2, 0, (0).to_bytes(2, "little"))],
    },
    ("app", 0x0000c358): [{
        4: [(2, 0, (1).to_bytes(4, "little")), (2, 4, bytes(4))],
        8: [(2, 0, (1).to_bytes(4, "little")), (2, 4, bytes(4))],
        9: [(2, 0, struct.pack("<f", .2)), (2, 4, struct.pack("<f", .3))],
        16: [(2, 0, (1).to_bytes(4, "little")), (2, 4, bytes(4))],
        17: [(2, 0, struct.pack("<f", .2)), (2, 4, struct.pack("<f", .3))],
        20: [(2, 0, (1).to_bytes(4, "little")), (2, 4, bytes(4))],
        28: [(0, 0, bytes(64))],
    } for _ in range(2)] + [{
        4: [(2, 0, (1).to_bytes(4, "little")), (2, 4, bytes(4))],
        8: [(2, 0, (1).to_bytes(4, "little")), (2, 4, bytes(4))],
        9: [(2, 0, struct.pack("<f", .2)), (2, 4, struct.pack("<f", .3))],
        16: [(2, 0, (1).to_bytes(4, "little")), (2, 4, bytes(4))],
        17: [(2, 0, struct.pack("<f", .2)), (2, 4, struct.pack("<f", .3))],
        20: [(2, 0, (1).to_bytes(4, "little")), (2, 4, bytes(4))],
        29: [(0, 0, bytes(64))],
    }],
    # LTPF pitch detector returns tc through its fourth argument.  A bounded
    # production lag keeps refine_pitch's correlation window finite.
    ("app", 0x0006ab80): {
        3: [(3, 0, (50).to_bytes(4, "little"))],
        4: [(3, 0, b"\x00\x00\x80\x3f" * 17)],
        5: [(3, 0, bytes(256))],
        6: [(3, 0, bytes(256))],
    },
    # frexpf writes the extracted exponent through its integer pointer on each
    # of the 64 fast_log2f calls.  Model that real callee side effect so the
    # two compiler-specific local-stack offsets do not retain unrelated seed
    # bytes and contaminate the polynomial result.
    ("app", 0x0006c778): {
        i: [(0, 0, (0).to_bytes(4, "little"))] for i in range(1, 65)},
    ("app", 0x00021da8): [
        {4: [(0, 0, payload)]} if payload is not None else {}
        for payload in (
            b"\x03\xf5\x09\xcb", b"\x15" + bytes(range(1, 22)),
            None, None, None, None, None, None, None, None,
        )
    ] + [{6: [(0, 0, b"\x03\xf5\x09\xcb")]}] + [{} for _ in range(6)] +
    [{4: [(0, 0, b"\x03\xf5\x09\xcb")]}],
    # find(matches) writes count through its third argument; zero selects the
    # interpolation fallback without consuming randomized caller stack data.
    ("app", 0x0000e53c): {6: [(2, 4, bytes(4))]},
    # The interpolator returns its float through the caller-owned r3 out-slot.
    # Give both binaries the same nonzero payload so the wrapper's optional
    # copy is compared semantically instead of reading uninitialized stack.
    ("app", 0x0000e2b4): {1: [(3, 0, b"\x00\x00\x48\x41")]},
    # Parser initializer is exactly memset(local_state, 0, 28).
    ("app", 0x00064b64): {0: [(0, 0, bytes(28))]},
    # printf_like begins every conversion by clearing its 24-byte parser
    # descriptor.  Model the reviewed memset side effect; otherwise the oracle
    # returns without clearing stack memory and both binaries parse random
    # flags/layout-dependent conversion kinds.
    ("app", 0x000113a8): {0: [(0, 0, bytes(24))]},
    ("net", 0x01012438): {0: [(0, 0, b"\x01\x01\x00\x00\x00\x00")]},
    # FUN_0100ca98 returns a controller type through its second argument.
    # Replaying that real out-parameter write prevents the caller from reading
    # unrelated compiler-local stack bytes.  One valid nonzero type exercises
    # propagation through FUN_01010890 on every selector/random trial.
    # This function has several possible first callees.  Bind the modeled
    # out-byte to FUN_0100ca98 itself so another call at ordinal zero cannot
    # accidentally receive its side effect.
    ("net", 0x0101746c): {
        0: [(1, 0, b"\x01", 0x0100ca98)],
    },
    # FUN_0102714a publishes the controller handle and auxiliary selector
    # through its second and third arguments.  The caller immediately feeds
    # the handle to FUN_010270d2, so replay both real out-parameter writes.
    ("net", 0x01019660): {
        1: [(1, 0, (emu.SCRATCH + 0x3000).to_bytes(4, "little"), 0x0102714a),
            (2, 0, bytes(2), 0x0102714a)],
    },
    # The connection builder queries the same controller handle repeatedly;
    # each FUN_0102714a call refreshes its two caller-owned output slots before
    # the handle is consumed by FUN_010270d2.
    ("net", 0x01019aa0): {
        ordinal: [
            (1, 0, (emu.SCRATCH + 0x3000).to_bytes(4, "little"), 0x0102714a),
            (2, 0, bytes(2), 0x0102714a),
        ]
        for ordinal in (2, 5, 8, 12, 16, 23)
    },
    ("app", 0x000545f0): {1: [(0, 12, bytes(4))]},
    # Matrix conversion writes four result words through its second argument.
    ("app", 0x0007d968): {2: [(1, 0, bytes(16))]},
    # Formatter advances a caller-owned cursor in the descriptor.  Anchor it
    # to the reviewed output buffer for both stack layouts.
    ("app", 0x00077914): {0: [(1, 0, (emu.SCRATCH + 0x2400).to_bytes(4, "little"))]},
}

# Target-bound caller-owned copies.  The optional fourth tuple field is the
# semantic callee identity; an ordinal occupied by another helper must not
# receive the effect.
REVIEWED_ORACLE_MEMORY_COPIES = {
    # The interpolation worker consumes the overlap-safe move immediately in
    # its polynomial/output loops.  Replay the exact memmove boundary instead
    # of comparing only its compiler-local pointer arguments.
    ("app", 0x0006bfc8): {
        0: [(0, 1, 2, 0x00086c44)],
    },
    ("app", 0x0007d82e): {
        0: [(0, 1, 2, 0x00086c1e)],
    },
}
REVIEWED_STACK_POINTER_CALLS = {
    # Small compiler-owned request/descriptor frames.  Only the listed call
    # arguments are normalized; scalar registers and complete pointee bytes
    # remain part of the strengthened comparison.
    ("app", 0x00047ba8): {1: {0}, 2: {1}},
    # The overlap-safe copy moves samples between two offsets in the
    # compiler-owned interpolation workspace.
    ("app", 0x0006bfc8): {0: {0, 1}},
    ("app", 0x0004e540): {i: {2} for i in range(32)},
    ("app", 0x00052000): {0: {1}},
    ("app", 0x00052c40): {i: {0} for i in range(8)},
    ("app", 0x000553f8): {0: {0}, 1: {0, 1}, 2: {1}},
    ("app", 0x00055d08): {i: {2} for i in range(32)},
    ("app", 0x00057a04): {i: {2} for i in range(32)},
    ("app", 0x00058c34): {0: {0, 3}, 1: {0, 3}, 2: {0, 3},
                              3: {0, 3}, 4: {0, 3}, 5: {0, 3},
                              6: {0, 3}, 7: {0, 3}},
    ("net", 0x0102fa4c): {0: {0}, 1: {0}},
    ("net", 0x01039138): {0: {0}, 1: {0, 2, 4}},
    ("net", 0x01019588): {1: {1, 2}},
    # Scheduler update publishes a compiler-local result record at call 13.
    ("net", 0x0101b230): {13: {1}},
    # Decoder request/result descriptors are distinct compiler-local objects.
    ("app", 0x00051e9c): {0: {1, 3}},
    # Entropy buffer, timestamp pair, and diagnostic tuple are stack-owned.
    ("app", 0x00055bf8): {0: {0}, 2: {1, 3}, 3: {2}},
    ("app", 0x0007f542): {1: {0}},
    # Allocator publishes its result through a compiler-local pointer slot.
    ("app", 0x00058930): {0: {1}},
    ("app", 0x00071358): {3: {3, 4}},
    ("app", 0x00062930): {1: {2}, 2: {2}, 3: {2}, 4: {1, 2}},
    # Controller registration passes a compiler-local descriptor in r1.
    ("net", 0x010187e0): {0: {1}},
    ("net", 0x0102b5bc): {1: {1}},
    # Retry packet is compiler-local and is passed to memset plus each
    # register-indirect transport callback.
    ("net", 0x0102a394): {i: {0} for i in range(32)},
    ("net", 0x01035830): {3: {3}},
    # Time conversion owns two result words and a one-byte carry on stack.
    ("net", 0x010225ac): {0: {1}, 1: {1, 2}, 8: {2, 3}},
    ("app", 0x0008295a): {1: {3}},
    # Queue submission owns a two-word item on its stack.  The internal submit
    # helper and the final unlock tail both receive that same local in r1.
    ("app", 0x00085a9c): {2: {1}},
    # Eight-byte radio packet is a compiler-owned stack record.  Depending on
    # mode, its send is call ordinal two or three.
    ("app", 0x0003af04): {2: {0}, 3: {0}},
    # The hook's parser/result records are compiler-local stack objects.
    # Normalize only the pointer argument at each boundary; command lengths,
    # constants, call identities, pointee effects, and return values remain
    # exact.
    ("app", 0x0000ef28): {1: {0}, 2: {0}, 3: {0}, 4: {0}, 5: {0}},
    # Forward MDCT passes its compiler-local complex work buffer as FFT input
    # and first scratch buffer.  Their offsets differ with frame layout/codegen.
    ("app", 0x0006b9b8): {0: {0, 2}},
    ("app", 0x0000c358): {
        4: {0, 1, 2}, 8: {0, 1, 2}, 9: {2}, 16: {0, 1, 2},
        17: {2}, 20: {0, 1, 2}, 28: {0, 1}, 29: {0, 1},
        38: {0, 1}, 39: {0, 1}, 43: {0, 1}, 44: {0, 1},
    },
    # LTPF owns tc, correlation, and interpolation work arrays on its stack.
    ("app", 0x0006ab80): {3: {3}, 4: {3}, 5: {3}, 6: {3}},
    # resource_manger_get passes its two addressable selector words through
    # r1/r2 to the per-resource lookup helper.  GCC may materialize them as
    # local words or reuse the pushed r0/r1 parameter homes.
    ("app", 0x0004588c): {0: {1, 2}},
    # Timer setup passes its compiler-local command/result bytes to helpers.
    ("net", 0x01020a6c): {1: {0}, 3: {3}, 4: {0}, 5: {0}, 6: {0}},
    # SNS uses compiler-local energy/scale-factor arrays at its three external
    # buffer boundaries; compare ownership/argument position, not stack offset.
    ("app", 0x0006c778): {
        0: {0}, **{i: {0} for i in range(1, 65)}, 65: {2}, 66: {2}},
    # Match collection uses three compiler-local stack arrays; the fallback
    # interpolator subsequently receives the local result array as r2.
    ("app", 0x0000e53c): {6: {0, 1, 2}, 7: {2}},
    ("app", 0x00021da8): {
        **{i: {0} for i in range(4, 200, 4)},
        **{i: {1} for i in range(5, 200, 4)},
        6: {0}, 7: {0, 1},
    },
    # Persistent flash worker owns a compiler-local message object. Normalize
    # its initializer and each send/reset use by stack-relative identity.
    ("app", 0x000324bc): {
        0: {0},
        **{i: {0} for base in range(5, 200, 5) for i in (base, base + 1)},
    },
    # The interpolation table and result out-slot are compiler-local objects.
    ("app", 0x0000e2b4): {1: {0, 3}},
    ("app", 0x000644f8): {1: {1}},  # local three-byte formatter descriptor
    ("app", 0x00064b64): {0: {0}, 3: {0}, 5: {0}},
    ("app", 0x000710b4): {0: {2}, 4: {2}},
    ("app", 0x00057b60): {1: {2}},
    ("net", 0x01012438): {0: {0}, 1: {0}, 2: {0}, 3: {0}, 9: {1}},
    ("app", 0x00043e90): {0: {1}},
    ("app", 0x000476b4): {2: {3}},
    # This routine builds its two-byte status descriptor in a compiler-local
    # stack slot before passing it to the transport helper.
    ("app", 0x0005a8bc): {2: {2}},
    # The decoder's first helper initializes a compiler-local 16-byte frame.
    ("app", 0x0005d0ac): {0: {0}},
    ("app", 0x0005eeb4): {0: {0}},
    ("app", 0x00047724): {2: {1, 3}},
    # Synchronous command completion passes its 28-byte stack event to the
    # initializer and later to the wait primitive.  Candidate stack placement
    # is code-generation-specific, so compare each pointer as a stack offset.
    ("app", 0x00053d70): {0: {0}, 4: {0}},
    ("app", 0x00077914): {0: {1, 3}},
    ("app", 0x0007d968): {0: {0}, 2: {0, 1}},
    # The formatter descriptor is a compiler-local stack object on both sides.
    ("app", 0x0008712e): {0: {1}},
    # printf_like owns several compiler-local parser/number descriptors.  GCC
    # places them at different frame offsets; normalize only arguments that
    # actually point into the respective stacks, retaining pointee bytes,
    # ordering, non-stack pointers, and every scalar argument comparison.
    ("app", 0x000113a8): {i: {0, 1, 2, 3} for i in range(200)},
    # Dashboard refresh owns several temporary date/text/layout descriptors;
    # compare their symbolic stack ownership rather than compiler frame offset.
    ("app", 0x0003727c): {i: {0, 1, 2, 3} for i in range(200)},
}

# Narrow identities for uninitialized compiler-local words whose concrete
# entry-SP offsets differ across code generation.  Each pair is
# (original_offset, candidate_offset[, fixed_value]).  Without a third field
# the harness seeds the same symbolic full word at both locations; the optional
# scalar or per-case value sequence pins a reviewed incoming stack argument.
# All full-width effects remain compared.
REVIEWED_PAIRED_STACK_INITIAL_WORDS = {
    # Incoming arguments five, six, and seven.  The sixth word selects all
    # four renderer modes; the seventh selects 12/24-hour formatting.
    ("app", 0x000442bc): [
        (0, 0, (0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55)),
        (4, 4, (0, 3, 1, 2, 1, 2, 2, 0)),
        (8, 8, (1, 0, 1, 0, 1, 0, 0, 0)),
    ],
    # Bitmap source and four-bit color are the fifth/sixth AAPCS arguments.
    # Pin both so validation cases remain bounded and the production cases
    # consume a complete four-byte, two-row bitmap.
    ("app", 0x00043a68): [
        (0, 0, emu.SCRATCH + 0x1000),
        (4, 4, (1, 2, 3, 4, 5, 0x0a, 0x0b)),
    ],
    # clean_fb_data receives its clamped x/y bounds as the fifth and sixth
    # AAPCS arguments.  These bounded cases cover both validation failures and
    # a two-row production clear without turning random words into huge loops.
    ("app", 0x000471cc): [
        # invalid-x, invalid-y, small clear, x clamp, y clamp, signed
        # division boundary, and a four-row loop with three backedges.
        (0, 0, (4, 10, 2, 700, 2, 3, 8)),
        (4, 4, (10, 4, 1, 1, 250, 1, 3)),
    ],
    # Exercise the fifth/sixth optional byte fields of the register updater.
    # These arguments are AAPCS stack-passed and therefore invisible to the
    # register-only selector extractor.
    ("app", 0x00085130): [
        (0, 0, (0, emu.SCRATCH + 0x1800, emu.SCRATCH + 0x1800,
                0, emu.SCRATCH + 0x1800, 0)),
        (4, 4, (0, 0, emu.SCRATCH + 0x1900,
                emu.SCRATCH + 0x1900, 0, emu.SCRATCH + 0x1900)),
    ],
    # Two mapping.tag words: original frame is eight bytes deeper because it
    # saves r8/r9.  Each path overwrites only the low byte before publishing
    # the complete word to event+0x10.
    ("app", 0x00026338): [(-44, -36), (-36, -28)],
    # Fifth and sixth AAPCS arguments enter at entry-SP+0/+4.  Pin the output
    # length pointer and callback context so the dispatch fixtures own complete
    # mapped objects rather than relying on random stack words.
    ("app", 0x00032b24): [
        (0, 0, emu.SCRATCH + 0x2200),
        (4, 4, 0x12345678),
    ],
    # Fifth argument is the second-copy length.  Values align with the five
    # reviewed cases below and cover both sides of the 0x11a clamp.
    ("app", 0x00024534): [
        (0, 0, (0x100, 0x11a, 0, 0x10, 0x10, 0, 0, 0, 0)),
    ],
}

# Reviewed addressable stack objects.  Each tuple is
# (semantic identity, original entry-SP offset, candidate entry-SP offset,
# byte size), optionally followed by content ranges, exact call ordinals,
# semantic call targets, embedded-pointer offsets, and a semantic argument
# index that explicitly declares the content byte length.  With neither a
# range nor length relation, the complete declared byte size is compared.
# Unlike the older argument-position normalization, this maps
# only the declared half-open regions and compares identity, interior offset,
# declared size, and complete bytes at every external call boundary.
REVIEWED_PAIRED_STACK_OBJECTS = {
    ("net", 0x0101132c): [
        ("controller-init-descriptor", -40, -40, 16),
        ("controller-iterator", -48, -48, 8, None, None,
         (0x01009dd8,)),
    ],
    # FUN_00085130 consumes this one-byte enable flag by pointer.  The object
    # remains at entry-SP-25 in both codegens; compare its initialized content
    # at the exact fourth call boundary rather than only its numeric address.
    ("app", 0x000657e4): [
        ("gpio-enable", -25, -25, 1, None, (3,), (0x00085130,)),
    ],
    # The cursor passed to either formatter branch points at the caller-owned
    # remaining varargs, beginning exactly at entry SP.  Compare both cursor
    # identity and the complete words available to the callee.
    ("app", 0x00086f00): [
        ("remaining-varargs", 0, 0, 16),
    ],
    # Complete locally-owned event/request records.  These replace the old
    # pointer-only normalization so opcode and every initialized byte remain
    # observable at the consuming call.
    ("app", 0x00048ad4): [
        ("double-click-event", -32, -32, 24),
    ],
    ("app", 0x00023c88): [
        ("startup-request", -16, -16, 6),
    ],
    # Both queue wrappers publish a complete three-word caller-owned record.
    # The shipped push layout places it four bytes below GCC's local array.
    ("app", 0x00018e48): [
        ("uid-queue-record", -24, -20, 12),
    ],
    ("app", 0x000244a8): [
        ("quick-note-delete-record", -24, -20, 12),
    ],
    # The flash callback receives exactly the first three initialized bytes of
    # this result record; the fourth local byte is outside its length contract.
    ("app", 0x00023df4): [
        ("dashboard-flash-record", -20, -12, 3),
    ],
    # The display transport consumes exactly opcode byte 1 and the screen id.
    # Bytes saved beside them on the original stack are outside length two.
    ("app", 0x00049858): [
        ("display-close-request", -12, -12, 2),
    ],
    ("app", 0x00065b9c): [
        ("irq-channel", -52, -52, 4),
    ],
    # REV16 publishes one exact two-byte payload.  The original stores at
    # entry-SP-12 while readable GCC uses the aligned halfword at SP-10.
    ("app", 0x0007d696): [
        ("big-endian-value", -12, -10, 2),
    ],
    # The bounded copy initializes bytes 1..7 after opcode byte 0.  At the
    # producer call bytes 1..7 have identical symbolic pre-state; at the send
    # call the target-bound copy has initialized them.  Both boundaries compare
    # exact bytes and therefore catch opcode, copy, and length mistakes.
    ("app", 0x0007d82e): [
        ("command", -16, -16, 8),
    ],
    # Queue submission consumes the complete two-word work item.
    ("app", 0x0008099e): [
        ("work-item", -16, -16, 8),
    ],
    # FUN_00065584 consumes and updates the caller-owned channel word before
    # the wrapper uses the reduced index for its register address.
    ("app", 0x00085130): [
        ("channel-index", -28, -44, 4),
    ],
    # The dispatch response and helper-owned transfer buffer are adjacent in
    # the original frame.  GCC moves both four bytes lower in the readable C;
    # compare their identities, interior offsets, and complete contents.
    ("app", 0x00021460): [
        ("dispatch-response", -0xb4, -0xb8, 20),
        ("dispatch-transfer", -0xa0, -0xa4, 0x84),
    ],
    # Exact serializer/log records.  The compiler reuses its SP+4 slot for the
    # queued and compact-handle records; call ordinals distinguish their
    # non-overlapping lifetimes without normalizing arbitrary stack pointers.
    ("app", 0x00071684): [
        ("event-log-record", -80, -56, 24, ((0, 22),), (1,), (0x0004d944,)),
        ("queued-log-argument", -40, -76, 8, ((0, 8),), (2,), (0x0004d944,)),
        ("compact-handle-record", -80, -76, 20, ((0, 18),), (3, 4),
         (0x0004d944,)),
    ],
    # The callback payload has two reserved holes.  Every initialized field is
    # compared exactly at either callback ordinal; no generic stack identity.
    ("app", 0x00067600): [
        ("callback-payload", -40, -40, 24,
         ((0, 1), (4, 6), (8, 24)), (2, 3), None),
    ],
    ("app", 0x0004d100): [
        ("request-chain", -44, -36, 12),
    ],
    ("app", 0x0004e83c): [
        ("configuration-arguments", -32, -32, 16),
    ],
    ("app", 0x0004ed8c): [
        ("submission-error-record", -40, -36, 12),
    ],
    ("app", 0x00052880): [
        ("stream-request", -104, -104, 24),
    ],
    ("net", 0x0102fbd0): [
        ("diagnostic-record", -32, -28, 12),
    ],
    ("net", 0x010359b8): [
        ("primary-log-record", -80, -48, 24),
        ("queued-log-record", -40, -72, 8, ((0, 8),), (2,),
         (0x0102e284,)),
    ],
    ("net", 0x01030bac): [
        ("controller-log-buffer", -140, -148, 132),
        ("controller-diagnostic", -152, -156, 8, ((0, 8),), (3, 4),
         (0x0102e284,)),
    ],
    ("net", 0x0103566c): [
        ("queue-selector", -30, -38, 2),
        ("queue-context", -28, -36, 4),
    ],
    ("app", 0x0007712c): [
        ("dtoa-sign", -53, -57, 1, ((0, 1),)),
        ("dtoa-decimal-position", -52, -56, 4, ()),
        ("dtoa-digit-count", -48, -52, 4, ()),
        ("float-width-result", -44, -48, 8, ()),
    ],
    ("net", 0x010195f8): [
        ("controller-handle", -12, -16, 4, ()),
        ("controller-selector", -14, -18, 2, ()),
    ],
    ("net", 0x010198cc): [
        ("controller-handle", -36, -32, 4, ()),
        ("controller-selector", -38, -36, 2, ()),
    ],
    ("net", 0x0101ba58): [
        ("render-request", -48, -36, 12),
    ],
    # Optional radio initialization passes an eight-byte descriptor to
    # FUN_0101e274.  The callee reads the owner pointer at +4; the original
    # also initializes the mode byte at +0, while bytes 1:4 are alignment and
    # are neither initialized nor consumed.
    ("net", 0x0101e6ac): [
        ("radio-init-descriptor", -32, -40, 8, ((0, 1), (4, 8))),
    ],
    # Formatting wrapper owns a 0x4c-byte descriptor and a separate two-word
    # argument vector.  The original reuses incoming argument save slots for
    # the vector; the canonical struct/array source places both in its frame.
    ("app", 0x000779bc): [
        ("format-record", -128, -84, 76),
        ("format-arguments", -8, -92, 8),
    ],
    # Serializer local arrays and the dynamically constructed diagnostic
    # descriptor. GCC reuses the pair slot for the descriptor; the original
    # uses separate locations. Their common id represents disjoint lifetimes.
    # Descriptor padding bytes 18:20 are neither initialized nor consumed.
    ("app", 0x0004abc0): [
        ("serializer-pair-or-descriptor", -144, -60, 20, ((0, 18),)),
        ("serializer-pair-or-descriptor", -56, -60, 20, ((0, 18),)),
        ("serializer-deferred-indices", -72, -76, 16),
        ("serializer-index-byte", -73, -77, 1),
    ],
    ("app", 0x0005c8d8): [
        ("operation-context", -32, -36, 12),
    ],
    # The event worker reuses one GCC local slot for three diagnostics.  The
    # shipped frame has a distinct two-word pending record and a later
    # three-word record reused by the error/unknown branches.  Bind each
    # lifetime to the exact logger call so count, format and value bytes remain
    # observable without treating unrelated stack pointers as equivalent.
    ("app", 0x000545f0): [
        ("pending-buffer-log", -48, -44, 8, None, (4,), (0x00080ea2,)),
        ("processing-error-log", -80, -44, 12, None, (6,), (0x00080ea2,)),
        ("unknown-event-log", -80, -44, 12, None, (2,), (0x00080ea2,)),
    ],
    ("app", 0x00064a88): [
        ("encoded-buffer", -52, -60, 36),
    ],
    # HCI status handling owns a sixteen-byte decoded response.  The producer
    # initializes it before the first word is consumed by the status decoder.
    ("app", 0x0005ffa4): [
        ("decoded-status", -48, -32, 16),
    ],
    ("app", 0x00060c00): [
        ("command-frame", -48, -88, 24, ((0, 4), (8, 16)), None,
         (0x00060ab0, 0x00086be4)),
        ("status-log", -64, -64, 12, None, (6,), (0x000838d6,)),
        ("transition-log", -72, -64, 18, ((0, 18),), (7, 8),
         (0x000838d6,)),
        ("mismatch-log", -80, -64, 32, None, (13,), (0x000838d6,)),
    ],
    # The queue lookup publishes one removed-entry index byte through its
    # third argument.  This is an output-only object; its entry contents are
    # indeterminate and are not consumed before the producer writes it.
    ("net", 0x01010834): [
        ("removed-entry-index", -9, -17, 1, ()),
    ],
    # The frame parser fills this compact nineteen-byte record.  The original
    # reserves a forty-byte frame after six saved registers; GCC's readable C
    # places the same object twenty bytes higher in its smaller frame.
    ("net", 0x01017344): [
        ("parsed-radio-record", -64, -44, 19),
    ],
    # Flash recovery owns one contiguous four-byte decoded-length word followed
    # by its 4096-byte I/O buffer.  GCC's frame is twelve bytes smaller, but
    # every callback and decoder observes the same object identity and bytes.
    ("app", 0x00022834): [
        ("flash-length-and-buffer", -4136, -4124, 4100),
    ],
    # These two log adapters fully initialize twelve-byte formatter records;
    # only compiler register allocation changes their entry-SP placement.
    ("app", 0x00052f68): [
        ("log-record", -32, -20, 12),
    ],
    ("app", 0x00057438): [
        ("log-record", -24, -20, 12),
    ],
    # Long-duration formatting owns one fully initialized twelve-byte calendar
    # record.  Both reviewed frames pass entry-SP-44; preserve identity, extent, interior
    # offsets, and all twelve content bytes at every boundary.
    ("app", 0x000357dc): [
        ("calendar-record", -44, -44, 12),
    ],
    # The parser receives the complete four-byte command header object.  The
    # shipped frame places it at entry-SP-24; GCC saves two extra registers and
    # places the same object at entry-SP-32.
    ("app", 0x00024dac): [
        ("command-header", -24, -32, 4),
    ],
    # One contiguous local record owns the eight-byte event payload followed
    # by three four-byte result words.  GCC leaves one alignment word before
    # the record, shifting the whole semantic object by four bytes.
    ("app", 0x0002ea28): [
        ("event-and-results", -40, -36, 20),
    ],
    # The three device-query result buffers are distinct caller-owned output
    # objects.  FUN_000302f8 receives their identity/extent but does not consume
    # their indeterminate pre-call bytes, so the observable content range is
    # deliberately empty.
    ("app", 0x00030b3c): [
        ("query-1c00-result", -28, -24, 4, ()),
        ("query-4444-result", -24, -20, 4, ()),
        ("query-4744-result", -20, -16, 8, ()),
    ],
    # The mode-change poller owns one 21-byte controller status record.  The
    # original reserves its decompiler-sized 140-byte frame while the rebuilt
    # function needs only 32 local bytes, so pair their different exact bases
    # and make all content explicit at FUN_000232f8.
    ("app", 0x00032308): [
        ("controller-status-record", -156, -48, 21),
    ],
    # One initialized 257-byte transmit record: selector byte followed by the
    # exact 256-byte payload copied from the caller.
    ("app", 0x00017eec): [
        ("transport-record", -276, -276, 257),
    ],
    # The date/time formatter owns a twelve-byte decoded-time record followed
    # by a twenty-byte text buffer.  GCC preserves both complete objects but
    # reserves four additional frame bytes, shifting each base by four.
    ("app", 0x000442bc): [
        ("decoded-time", -68, -72, 12),
        ("formatted-time", -56, -60, 20),
        ("glyph-handle", -80, -84, 4),
        ("glyph-width", -76, -80, 4),
        ("glyph-data", -72, -76, 4),
    ],
    ("app", 0x0004967c): [
        ("display-reflash-packet", -48, -48, 24),
    ],
    # Property lookup writes selected/context into a twelve-byte local result
    # and publishes a separate, fully initialized twelve-byte diagnostic.
    # The lookup result pointer is identical in both builds; only the dynamic
    # diagnostic record needs pairing.
    ("app", 0x0004e124): [
        ("property-result", -36, -28, 12, ()),
        ("property-diagnostic", -56, -44, 12),
    ],
    # Configuration parsing owns two output-only result objects plus a complete
    # three-word diagnostic.  The reconstructed parser result is now a real
    # contiguous 32-byte struct, matching the original memset/field accesses.
    ("app", 0x000521fc): [
        ("parser-status", -244, -248, 4, ()),
        ("decoded-values", -240, -232, 24, ()),
        ("configuration-diagnostic", -264, -244, 12),
        ("completion-buffer", -184, -176, 32, ()),
        # FUN_00080872 consumes all six twenty-byte descriptors.  Normalize
        # each embedded output pointer to the exact field within the paired
        # parsed-result object while retaining every other table byte.
        ("parsed-configuration", -216, -208, 32, ()),
        ("parser-field-table", -152, -144, 120, None, (1,),
         (0x00080872,), (12, 32, 52, 72, 92, 112)),
    ],
    # The parser's twenty-byte output scratch is uninitialized at its producer
    # boundary.  The short diagnostic calls consume exactly two initialized
    # words (0x1040/0x1080 encode eight payload bytes).
    ("app", 0x00052d58): [
        ("parser-scratch", -60, -44, 20, (), None, (0x0007f1e8,)),
        ("short-diagnostic-null", -40, -44, 8, None, (0,),
         (0x0004d944,)),
        ("short-diagnostic-runtime", -40, -56, 8, None, (2, 3),
         (0x0004d944,)),
        ("full-diagnostic", -80, -56, 12, None, (4,), (0x0004d944,)),
    ],
    # Queue receive owns one 204-byte message object.  The original places it
    # at entry-SP-216; GCC saves one additional register and uses entry-SP-220.
    # The complete object is paired, not a generic stack-pointer sentinel.
    ("app", 0x00019c44): [
        ("queue-message", -216, -220, 204),
    ],
    # The mode-zero allocation path passes the address of its fully initialized
    # four-byte input value to FUN_01027258.  The original and GCC frames place
    # that same object four bytes apart; compare identity and complete content.
    ("net", 0x0100a664): [
        ("allocation-input-value", -24, -20, 4),
    ],
    # Both record-submission entries build the same 14-byte semantic
    # descriptor at different compiler-frame offsets.  FUN_01011d14 reads
    # payload[0:4], flags[4:6], context[8:12], and type[12:14]; bytes 6:8 are
    # ABI alignment and are never initialized or consumed.  Pair one object
    # identity while comparing every initialized/observable byte range.
    ("net", 0x010122fc): [
        ("record-description", -32, -24, 14, ((0, 6), (8, 14))),
    ],
    ("net", 0x01012308): [
        ("record-description", -32, -24, 14, ((0, 6), (8, 14))),
    ],
    # This builder passes a fully initialized twelve-byte controller descriptor
    # to FUN_010098d8.  The original places it at entry-SP-44, while GCC's
    # additional saved registers put the candidate at entry-SP-52.  Pair the
    # exact object so call comparison includes its identity and all 12 bytes.
    ("net", 0x01008a58): [
        ("controller-option-descriptor", -44, -52, 12),
    ],
    # ble_process_put_req: original pushes 36 bytes and reserves 340; its
    # response base starts at post-frame SP+60 => entry-SP-316 (the first
    # memset receives response+4 at -312).  The integrated C places the
    # same response base at entry-SP-60 (memset argument -56). Runtime call
    # tracing confirms the candidate frame is 0x100 bytes shallower.
    ("app", 0x0001a75c): [
        ("response", -316, -60, 20),
        # Opcodes 1/2/3/5 pass their initialized eight-byte synchronization
        # record to FUN_00019b54. Runtime traces place it at these exact bases.
        ("copy-ack-sync", -296, -72, 8),
        # Opcode 9 action-1 timestamp query owns an eight-byte result object.
        ("op9-system-time", -328, -80, 8),
    ],
    # Recursive controller-option setup owns one nine-byte semantic record per
    # active frame plus the outer call's four-byte mode word.  Runtime call
    # traces place the fully initialized records at these exact entry-SP
    # offsets.  Pairing the objects preserves recursion/frame identity and
    # compares every byte passed to FUN_01009708; it does not collapse generic
    # stack pointers to argument-position sentinels.
    ("net", 0x010098d8): [
        # FUN_01009708 reads offsets 0..8; bytes 9..11 are alignment padding
        # and are deliberately outside the compared half-open object.
        ("outer-option-record", -28, -36, 9),
        ("recursive-option-record", -196, -76, 9),
        ("outer-mode-word", -16, -40, 4),
    ],
    # FUN_0102714a writes a four-byte controller handle and an adjacent
    # two-byte auxiliary selector through caller-owned locals.  GCC places the
    # two objects at different frame offsets but both executions pass and
    # consume their complete initialized contents repeatedly.
    ("net", 0x01019aa0): [
        ("controller-handle", -44, -48, 4),
        ("auxiliary-selector", -46, -52, 2),
    ],
    # Timeline conversion gives FUN_010244cc two caller-owned output objects.
    # The original frame places the eight-byte time pair at entry-SP-44 and
    # the adjacent status byte at entry-SP-45; GCC places them four bytes
    # lower.  Neither object's pre-call bytes are consumed, so their reviewed
    # observable ranges are empty.  The callee's exact 8+1 byte writes remain
    # modeled separately in REVIEWED_ORACLE_MEMORY_WRITES.
    ("net", 0x01023ea8): [
        ("timeline-time-pair", -44, -48, 8, ()),
        ("timeline-status", -45, -49, 1, ()),
    ],
    # The encoder owns two independently addressable accumulation arrays and
    # a one-byte callback object.  Original r7 is entry-SP-120, giving bases
    # r7+0x30, r7+0x40, and r7+0x2f; GCC's entry-SP-144 frame uses SP+0x30,
    # SP+0x40, and SP+0x54 respectively.  Keep each identity and full declared
    # extent distinct rather than treating arbitrary stack arguments alike.
    ("net", 0x0102bfe4): [
        ("deferred-index-array", -72, -96, 16),
        ("encoded-pair-array", -56, -80, 20),
        ("single-index-byte", -73, -60, 1),
    ],
    # The invalid-mode path builds one fully initialized three-word diagnostic
    # record.  FUN_0102e284 derives a 12-byte payload length from 0x1840 and
    # passes the complete record through FUN_0102bfe4.  The shipped dynamic
    # frame places it at entry-SP-48; GCC's real struct is at entry-SP-36.
    ("net", 0x0102fc30): [
        ("invalid-mode-diagnostic", -48, -36, 12),
    ],
    # The scheduler snapshot helper receives one eight-byte output pair.
    # Its pre-call bytes are not consumed; subsequent loads/calls preserve the
    # produced pair's scalar semantics.  GCC shifts only this object by four
    # bytes (original entry-SP-48, candidate entry-SP-44).
    ("net", 0x01035d18): [
        ("scheduler-snapshot", -48, -44, 8, ()),
    ],
}

# Exact per-ordinal ABI widths for callers of data-derived functions.  Unlike
# target-address overrides, these remain valid when the callback address is
# supplied by runtime state rather than fixed firmware text.
REVIEWED_CALL_ARITIES = {
    # Initialization calls, the true four-register field update, then a
    # conversion-free diagnostic whose only semantic argument is its format.
    ("app", 0x000167f4): [0, 0, 1, 4, 1],
    # The first notification supplies its copied context word; the tail
    # notification is the unary completion form of the same installed hook.
    ("app", 0x00079780): [2, 1],
    # Two fixed helpers followed by slot_callback_fn(uint16_t, uint32_t).
    ("net", 0x01009d64): [2, 2, 2],
    # Two fixed flag queries, an optional third query, then a two-argument
    # data-derived callback.  All calls in the normal dispatcher path are
    # binary; callback r2/r3 values are caller scratch.
    ("app", 0x00067600): [2, 2, 2, 2],
    # These reviewed minute/hour cases have one fixed 18-call shape.  The
    # formatter consumes four arguments at the initial elapsed-time message
    # and three at the final completion message; r3 at the latter is stale.
    ("app", 0x000357dc): [0, 0, 3, 4, 0, 3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 0, 3],
}

# Arguments beyond these widths are diagnostics-only stale registers on the
# reviewed caller path.  The source still spells all production arguments;
# differential call traces compare only the callee-consumed semantic prefix.
REVIEWED_TARGET_CALL_ARITIES = {
    # Bitmap conversion uses a 64-bit clock result, two six-argument
    # framebuffer helpers, and zero-argument display accessors.
    ("app", 0x00043a68): {
        0x000431a8: 0, 0x000471cc: 4, 0x000167a8: 0,
        0x00047260: 4,
    },
    # This formatter's installed output callback consumes all four register
    # arguments: owner, context, byte/string pointer, and length.
    ("app", 0x0007712c): {0x00080000: 4},
    # The dashboard activation path passes four register words and two zero
    # stack words to FUN_00075174.  Its unrelated startup callers are unary,
    # so keep this complete ABI scoped to the dispatcher call site.
    ("app", 0x00021460): {0x00075174: 4},
    # Date/time renderer: fixed formatter/glyph/draw ABIs include additional
    # AAPCS stack words recorded separately below.
    ("app", 0x000442bc): {
        0x0004a1b8: 2, 0x00086f00: 4, 0x0000ef12: 1,
        0x00043e90: 4, 0x000431a8: 0, 0x000471cc: 4,
        0x0004588c: 4, 0x0007d53a: 4, 0x000167a8: 0,
        0x00047260: 4, 0x0007dda4: 4, 0x00019c70: 4,
    },
    ("app", 0x0004967c): {
        0x00086c78: 3, 0x00086698: 0, 0x0007dda4: 4,
        0x00019c70: 4, 0x00086c04: 3, 0x000720d0: 4,
        0x0004904c: 0,
    },
    # Installed property/settings callbacks consume all three explicit words;
    # treating these data-derived targets as two-argument functions would hide
    # the context word and requested byte count from the semantic trace.
    ("app", 0x0004e124): {0x00080000: 3},
    ("app", 0x00052d58): {0x00080000: 3},
    # Dispatch-table handlers consume request, size, output pointer, output
    # length pointer, and the caller's fifth callback context word.
    ("app", 0x00032b24): {0x00080000: 4},
    # Runtime device callbacks recovered from their production vtables.
    ("app", 0x00023df4): {0x00080000: 4},
    ("app", 0x0002aeb4): {0x00080000: 1},
    ("app", 0x00065b9c): {0x00065584: 1, 0x000654c4: 2},
    # Recovered fixed ABIs; the catalog either omits these small helpers or
    # carries decompiler-only stale register parameters.
    ("app", 0x000829f0): {0x00082932: 5},
    ("app", 0x00084e58): {0x00084e44: 3},
    ("app", 0x00085130): {0x00065584: 1},
    ("app", 0x0004e83c): {0x0007f344: 1},
    # Serializer output hooks have the recovered ABI
    # callback(bytes, length, context).  The fourth register is caller scratch
    # and differs with ordinary register allocation, so do not admit it into
    # the semantic call trace for deterministic callback fixtures.
    ("app", 0x0004abc0): {0x00070000: 3},
    # Scheduler insertion finishes through a unary ready-queue update.
    ("app", 0x00073d1c): {0x00073cdc: 2, 0x000737d8: 1},
    # This wrapper forwards exactly the global context and caller value.
    ("app", 0x000778d4): {0x00077820: 2},
    # Runtime allocator table: allocate(size), release(ptr), resize(ptr,size).
    ("app", 0x00064a88): {
        0x00080000: 1, 0x00081000: 1, 0x00082000: 2,
    },
    # r2 is unused caller scratch; the wrapper consumes r0/r1 and the owner
    # carried in r3, which remains explicit in the canonical source.
    ("app", 0x00060c00): {0x000838dc: 2, 0x00060a10: 1},
    ("app", 0x0005ffa4): {0x0004ba38: 1},
    # FUN_0003444c is a state query.  Its decompiler-only r1/r2 parameters are
    # referenced solely by a dormant diagnostic formatter; the production
    # caller performs a bare BL and deliberately supplies no arguments.
    ("app", 0x0002c714): {0x0003444c: 0, 0x0007ce5c: 2},
    # Exact recovered prototypes.  The catalog's conservative four-register
    # defaults include caller-scratch values that none of these callees read.
    ("app", 0x00024dac): {0x00024d74: 1, 0x00025788: 4},
    ("app", 0x0002ea28): {
        0x0002e988: 4, 0x0007cef6: 3, 0x0000e2b4: 2,
        0x0007ceda: 0,
    },
    ("app", 0x00030b3c): {
        0x00030178: 2, 0x000301bc: 0, 0x00030224: 0,
        0x000302f8: 2, 0x000304f0: 0, 0x00030710: 0,
        0x00030754: 1, 0x0007cf70: 0,
    },
    # Raw call sites deliberately leave caller-scratch registers live, but
    # these fixed-signature callees consume only the reviewed prefixes.
    ("app", 0x0004c278): {
        0x000635a4: 1, 0x00064f78: 0, 0x00064fd4: 2,
        0x0007e2fa: 4, 0x0007e2ec: 2,
    },
    ("app", 0x00052000): {0x0008633e: 2, 0x00086334: 2},
    ("app", 0x00052c40): {0x0008638c: 1, 0x00052bf8: 1,
                              0x00084c76: 0, 0x0007e2fa: 4,
                              0x0007e2ec: 2},
    ("app", 0x000553f8): {0x00055350: 2, 0x00055204: 1,
                              0x00080fba: 2, 0x00054d18: 2},
    ("app", 0x00057a04): {0x0005f450: 3},
    # The persistent ANCS worker clears two ten-byte records.  The catalog's
    # conservative prototype omitted the length register, so bind the exact
    # three-word memset-like ABI at this caller.
    ("app", 0x00019718): {0x00086534: 3},
    # ble_process_put_req post_to_host callback (ctx+0x0c).
    ("app", 0x0001a75c): {0x00080000: 2, 0x0007c1dc: 2},
    ("net", 0x01035830): {0x00080000: 1},
    ("net", 0x01039190): {0x00080000: 2},
    # The option builder's cursor-only helper and its three installed callback
    # prototypes consume one, three, one, and five arguments respectively.
    # The harness compares the four register arguments of the five-argument
    # callback; its fifth scalar is passed on the stack by both binaries.
    ("net", 0x01008a58): {
        0x0101077c: 1,
        0x01030000: 3,
        0x01030004: 1,
        0x01030008: 4,
    },
    # FUN_01020764 stores only param_1; r1-r3 at its raw call sites are stale
    # caller scratch (confirmed by its complete decompile/disassembly).
    ("net", 0x0100ac98): {0x01020764: 1},
    ("net", 0x010333b4): {
        # Reviewed external callback installed in the production fixture.
        # Only r0 (the saved channel byte) is consumed.
        0x00080000: 1,
    },
    ("app", 0x0003b824): {
        0x0004382c: 0,
    },
    ("app", 0x0003af78): {
        0x0001672c: 0, 0x000167a8: 0, 0x00019c70: 4,
        0x00033cf8: 0, 0x00037060: 0, 0x000370bc: 0,
        0x0003719c: 0, 0x0003727c: 4, 0x0003ae6c: 0,
        0x0003af04: 0, 0x000431b4: 1, 0x000431c0: 0,
        0x000432d0: 0, 0x000432ec: 0, 0x0004382c: 0,
        0x00047260: 4, 0x00047b1c: 2, 0x00047ba8: 0,
        0x000488bc: 1, 0x00048b44: 1, 0x0004a9ec: 0,
        0x0004aab0: 0, 0x0007d1d0: 1, 0x0007d224: 0,
        0x0007d248: 0, 0x00086c78: 3, 0x00086698: 0,
        0x000276ec: 1, 0x00026f74: 4, 0x0007dda4: 4,
    },
    ("net", 0x01023ad8): {0x00080000: 2},
    ("app", 0x00023844): {0x00072908: 1},
    # low_speed_peripheral_dispatch_thread is persistent, so a call-ordinal
    # arity vector becomes stale as soon as a branch adds/removes one call.
    # Use the reviewed callee ABIs by target for every boundary in its CFG.
    ("app", 0x0002a8d8): {
        0x0001694c: 1, 0x0002c0e8: 1,
        0x0007dda4: 4, 0x00019c70: 4,
        0x00026f74: 3, 0x00019b2c: 0, 0x0008149a: 2,
        0x00010b18: 2, 0x0002eb40: 0, 0x0002eb78: 0,
        0x00026b88: 3, 0x00016268: 1,
        # 0x27448 is a two-byte entry veneer; execution crosses the oracle
        # boundary at its 0x2744a implementation body.
        0x00027448: 3, 0x0002744a: 3,
        0x00033c5c: 0, 0x00025528: 0, 0x0002aeb4: 0,
        0x0002ae84: 0, 0x0007d1d6: 2, 0x0007cb2c: 0,
        0x0007cb8e: 1, 0x0004c0a8: 1, 0x0007cb8a: 2,
        0x00016580: 0, 0x000167b4: 0, 0x0001658c: 1,
        0x00026c28: 0, 0x00026c8c: 0, 0x00027758: 3,
        0x00026a08: 1, 0x00056a68: 2, 0x000167a8: 0,
        0x0007cbfe: 2, 0x0002316c: 2, 0x0002a868: 0,
        0x0007cbae: 0,
    },
}

# Additional AAPCS words consumed from the callee-entry stack. Register call
# arity remains independently reviewed above.
REVIEWED_TARGET_CALL_STACK_ARITIES = {
    ("app", 0x00043a68): {0x000471cc: 2, 0x00047260: 2},
    ("app", 0x00021460): {0x00075174: 2},
    ("app", 0x000442bc): {
        0x00086f00: 5, 0x00043e90: 8, 0x000471cc: 2,
        0x0004588c: 2, 0x0007d53a: 2, 0x00047260: 2,
    },
    # printf floating conversion passes four scalar words after r0-r3 to dtoa
    # and the output callback as width-helper argument five.  The dtoa double
    # is independently compared in d0 via CALL_FLOAT_ARITY_OVERRIDES.
    ("app", 0x0007712c): {0x00086cda: 4, 0x00086e1c: 1},
    # GPIO updater arguments five/six are the mapping base and null optional
    # field.  Both are semantically consumed and must remain in the call event.
    ("app", 0x000657e4): {0x00085130: 2},
    ("app", 0x00032b24): {0x00080000: 1},
    # The table dump forwards value0 and both caller words after the four
    # register arguments to either logging implementation.
    ("app", 0x00033b0c): {0x0007dda4: 3, 0x00019c70: 3},
    ("app", 0x000723b8): {0x00073f6c: 2},
    # FUN_01035edc consumes ten integer arguments.  r0-r3 carry descriptor
    # fields 0..3 and the remaining six fields are exact AAPCS stack words.
    ("net", 0x0103601c): {0x01035edc: 6},
    # The installed packet callback consumes its context as argument five.
    ("net", 0x0103566c): {0x00080000: 1},
    # Scheduler wait consumes ticks_low/ticks_high after its four register
    # arguments.  These are semantic timeout words, not caller-stack noise.
    ("net", 0x01038764): {0x010375b8: 2},
    # After format/name/screen-id in r0-r2, AAPCS aligns each converted gyro
    # value on the caller stack.  Compare all three uint64_t payloads exactly
    # for either logging implementation (six complete words).
    ("app", 0x00036164): {0x0007dda4: 6, 0x00019c70: 6},
}

# Variadic diagnostics share two logger targets but consume a format-specific
# number of arguments.  Compare only the exact format ABI, not stale r2/r3
# values left live by surrounding dispatch code.
REVIEWED_CALL_ARITIES_BY_FORMAT = {
    ("app", 0x00021460): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in {
            0x0009d4e4: 2, 0x0009d518: 2, 0x0009d546: 2,
            0x0009d587: 2, 0x0009d5af: 2, 0x0009d5da: 2,
            0x0009d60f: 2, 0x0009b8fd: 4,
            0x0009d64e: 3, 0x0009d681: 3,
        }.items()
    },
    ("app", 0x000442bc): {
        (target, 0x000aaad4): 4
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x0004967c): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in ((0x000effd2, 2), (0x000efff4, 2),
                           (0x000f001c, 4), (0x000ef058, 2),
                           (0x000ef01c, 3))
    },
}

# Stack-passed variadic words are likewise format-specific.  In particular,
# the ANCS worker's initial diagnostic consumes p4 as argument five while its
# later logger formats consume no stack words.
REVIEWED_CALL_STACK_ARITIES_BY_FORMAT = {
    ("app", 0x00019718): {
        (target, 0x00099969): 1
        for target in (0x0007dda4, 0x00019c70)
    },
}

def _dashboard_directed_states():
    """Late action arms and independent dashboard RAM branch families."""
    cases = []
    def add(action, state=1, mode=0, latch=0, level=0, sink=0,
            once=0, count0=2, count1=2, count2=2):
        dash = bytearray(0x28)
        screen = bytearray(0x5000)
        row = emu.SCRATCH + 0x7000
        for i in range(199):
            screen[0x24 + i * 4:0x28 + i * 4] = row.to_bytes(4, "little")
        dash[0] = state; dash[2] = count0; dash[4] = count1
        dash[6] = count2; dash[9] = latch; dash[0xb] = once
        dash[0x1a] = mode
        cases.append(({0: emu.SCRATCH + 0x2000, 2: action}, [
            (emu.SCRATCH + 0x2000, bytes(screen)),
            (row, b"\xff" * 0x140),
            (0x20004950, bytes(dash)),
            (0x2000230c, level.to_bytes(4, "little", signed=True)),
            (0x20007554, sink.to_bytes(4, "little")),
            (0x20007570, (2).to_bytes(4, "little")),
            (0x2000756c, (0).to_bytes(4, "little")),
            (0x2001b814, b"\x00\x00\x00"),
        ]))
    # Complete action selector, including the raw late islands and default.
    for action in (4, 6, 7, 8): add(action)
    # State byte, logger threshold/sink, latch, and all mode/count guards.
    for state in (0, 1, 2): add(3, state=state)
    for level, sink in ((0, 0), (3, 0), (3, 1)): add(4, level=level, sink=sink)
    for mode in (0, 1, 2, 3): add(4, mode=mode)
    add(1, state=0, latch=0); add(1, state=0, latch=1)
    add(4, mode=0, count0=1); add(4, mode=1, count1=1)
    add(4, mode=2, count2=1); add(4, mode=2, count2=2)
    # One-shot/timing gate families (the seeded deadlines supply both sides of
    # the unsigned 64-bit elapsed comparison across the deterministic trials).
    add(0, once=0); add(0, once=1)
    return cases

ADDITIONAL_STATE_CASES = {
    ("net", 0x0101f818): [
        ({0: 0x11, 1: 0x22},
         [(0x21001334, bytes(4)), (0x2100143c, (0x1234).to_bytes(4, "little")),
          (0x21001448, b"\x00")]),
    ],
    # Every supported radio mode plus the diagnostic default.  The DPPI source
    # words and destination registers are real mapped MMIO addresses.
    ("net", 0x01020a00): [
        ({0: mode, 1: 0, 2: 0, 3: 0x44},
         [(0x41008510, bytes(4)), (0x41008588, bytes(4)),
          (0x01ff0080, (0x11111111).to_bytes(4, "little") +
           (0x22222222).to_bytes(4, "little")),
          (0x21001608, b"\x00")])
        for mode in (1, 2, 4, 8, 3)
    ],
    ("net", 0x01021838): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1080, b"\x01"), (0x2100167a, b"\x03")]),
    ],
    # Channel teardown with and without the active-controller callback.  The
    # record pointer retains its real eight-byte negative header ownership.
    ("net", 0x0103afac): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2008},
         [(emu.SCRATCH + 0x1000 + 0xa0,
           (emu.SCRATCH + 0x3000).to_bytes(4, "little") +
           (emu.SCRATCH + 0x4000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000, (0x1234).to_bytes(4, "little") + bytes(4)),
          (emu.SCRATCH + 0x3000 + 0x18, active.to_bytes(4, "little"))])
        for active in (0, 1)
    ],
    ("app", 0x0003af78): _dashboard_directed_states(),
    # Scheduler unlink: one production-shaped queue node for every valid
    # selector class.  The link advances to 0x20 so each case executes one
    # callback and terminates without manufacturing a synthetic loop.
    ("net", 0x01021cec): [
        ({}, [(0x210016f0 + 0x49, b"\x00"),
              (0x210016f0 + 0x31, b"\x01"),
              (0x210016f0 + 0x32, b"\x01"),
              (0x210016f0 + 0x52, bytes((selector, 0x20))),
              (0x210016f0 + 0xf0, (0x00080001).to_bytes(4, "little")),
              (0x210016f0 + 0xf4, (0x1234).to_bytes(4, "little"))])
        for selector in (1, 4, 5, 6)
    ],
    # Exercise both callback descriptor variants selected by owner[-0xb0].
    ("net", 0x0102b2ac): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000 - 0xb0, state.to_bytes(4, "little")),
          (emu.SCRATCH + 0x1000 - 4, (0x00080001).to_bytes(4, "little"))])
        for state in (0, 1)
    ],
}

# Explicit reviewed-state cases for routines whose control flow waits on MMIO
# or on a production-owned queue/list invariant.
# Each case is (argument overrides, absolute setup writes).  These fixtures are
# local to the reviewed function; the harness does not seed hardware globally.
def _c358_state():
    state = bytearray(0x6000)
    def sf(index, value):
        state[index * 4:index * 4 + 4] = struct.pack("<f", value)
    for index in range(0x5de): sf(index, 0.125)
    for index, value in ((0, 1), (1, 2), (0x5d4, 3), (0x5d5, 4),
                         (0x5d1, -10), (0x5d2, 10), (0x11a, 0),
                         (0x11b, 1), (0x11c, 2), (0x51, 0), (0x52, 1),
                         (0x119, 2), (0x15, .2), (0x17, .1), (0x4a, 0),
                         (0x4b, .1), (0x12, 1), (0x13, 1), (0x14, 1)):
        sf(index, value)
    return bytes(state)

_C358_P = emu.SCRATCH + 0x1000
_C358_SETUP = [(_C358_P, _c358_state()),
               (_C358_P + 0x7000, bytes(0x100)),
               (0x20002d1c, struct.pack("<f", 0.0))]

_QN_CTX = emu.SCRATCH + 0x1000
_QN_GLOBAL = emu.SCRATCH + 0x5000
_QN_ENABLE = emu.SCRATCH + 0x7000
_QN_FB = emu.SCRATCH + 0x8000
_QN_ROW = emu.SCRATCH + 0x12000

def _quicknote_case(state, phase, level=0, sink=0, enable=1,
                    deadline=(0, 0, 0), exit_flag=0):
    """Production-shaped QuickNote UI state with bounded shared raster rows."""
    ctx = bytearray(0x400)
    for row in range(199):
        struct.pack_into("<I", ctx, 0x24 + row * 4, _QN_ROW)
    global_state = bytearray(0x1100)
    struct.pack_into("<I", global_state, 0x1020, _QN_ENABLE)
    struct.pack_into("<I", global_state, 0xeb4, _QN_FB)
    struct.pack_into("<I", global_state, 0xeb8, _QN_FB + 0x400)
    oracles = {i: {0: _QN_GLOBAL, 1: 0} for i in range(160)}
    if state == 0 and phase == 1:
        # With verbose production logging enabled, ordinal 10 is the language
        # query (the earlier accessor calls supply the enable byte/pointers).
        oracles[10] = {0: 6 if sink == 0 else 5, 1: 0}
    return (
        {0: _QN_CTX, 2: phase},
        [(_QN_CTX, bytes(ctx)), (_QN_GLOBAL, bytes(global_state)),
         (_QN_ENABLE, bytes((enable,))), (_QN_FB, bytes(0x800)),
         # Zero pixels exercise all 199x320 loop bounds without manufacturing
         # 63k non-stack write events per language pass.
         (_QN_ROW, bytes(0x140)),
         (0x20004978, bytes((state, 0, 0, 0)) +
          b"".join(x.to_bytes(4, "little") for x in deadline)),
         (0x2000230c, level.to_bytes(4, "little", signed=True)),
         (0x20007554, sink.to_bytes(4, "little")),
         (0x2001b817, bytes((exit_flag,))),
         (0x200024e8, (100).to_bytes(4, "little"))],
        # All global-accessor calls return the reviewed object.  Individual
        # language and uptime results are refined after the first smoke run.
        oracles,
    )

def _irq_queue_case(flags, pending, tail_word, produced, consumed, threshold):
    """One valid queue-control object for FUN_000857e0.

    The three pointers and callback are real object ownership, while the six
    scalar fields select each callback/skip arm and the final counter clear.
    """
    owner = emu.SCRATCH + 0x1000
    producer = emu.SCRATCH + 0x1200
    consumer = emu.SCRATCH + 0x1400
    control = bytearray(0x30)
    control[0:4] = owner.to_bytes(4, "little")
    control[16:20] = (0x00080001).to_bytes(4, "little")
    control[20:24] = bytes(4)  # ring index used by consumer + index*8
    control[28:32] = producer.to_bytes(4, "little")
    control[32:36] = consumer.to_bytes(4, "little")
    control[38:40] = threshold.to_bytes(2, "little")
    owner_state = bytearray(0x20)
    owner_state[16:20] = flags.to_bytes(4, "little")
    owner_state[24:28] = pending.to_bytes(4, "little")
    producer_state = bytearray(8)
    producer_state[2:4] = produced.to_bytes(2, "little")
    consumer_state = bytearray(8)
    consumer_state[0:2] = tail_word.to_bytes(2, "little")
    consumer_state[4:6] = consumed.to_bytes(2, "little")
    return ({0: emu.SCRATCH + 0x1800},
            [(emu.SCRATCH + 0x1800, bytes(control)),
             (owner, bytes(owner_state)), (producer, bytes(producer_state)),
             (consumer, bytes(consumer_state))])

def _op10_guidance_payload(lengths, unterminated_index=None):
    data = bytearray((0xa0, 0, 0, 1, 1, 2, 4, 0, 8, 0))
    for i, length in enumerate(lengths):
        data.extend(bytes((0x41 + i,)) * length)
        if unterminated_index != i:
            data.append(0)
        else:
            data.extend(bytes((0x61 + i,)) * 8)
            break
    data[1:3] = len(data).to_bytes(2, "little")
    return bytes(data)

def _op10_nav_case(subcmd, *, active=0, oversize=False):
    """One production-shaped navigation sync/exit/arrived command."""
    ctx = emu.SCRATCH + 0x2000
    packet = emu.SCRATCH + 0x3000
    request = emu.SCRATCH + 0x4000
    transfer = emu.SCRATCH + 0x5000
    nav = emu.SCRATCH + 0x7000
    root = 0x20018000
    advertised = 70 if oversize else (12 if subcmd == 6 else 6)
    body = bytearray(256)
    body[:6] = bytes((0xa0, advertised, 0, 1, subcmd, 7))
    body[6:12] = b"TURN\x00\x00"
    ctx_state = bytearray(0x1000)
    ctx_state[0x70c:0x710] = (0x00080001).to_bytes(4, "little")
    ctx_state[0x710:0x714] = transfer.to_bytes(4, "little")
    nav_state = bytearray(0x200)
    nav_state[0] = active
    return (
        {0: ctx, 1: packet, 2: request},
        [(ctx - 0x700, bytes(ctx_state)),
         (packet, bytes((10, 0, advertised, 0)) + bytes(252)),
         (request, bytes(body)), (transfer, bytes(0x300)),
         (root + 0x1000, nav.to_bytes(4, "little")),
         (nav, bytes(nav_state)),
         (0x20007568, (7).to_bytes(4, "little")),
         (0x20010323, bytes(4)),
         (0x2000230c, (0).to_bytes(4, "little")),
         (0x20007554, (0).to_bytes(4, "little"))],
    )

def _ble_put_outer_cfg_case(command):
    """Production-shaped base state for one CFG-derived PUT opcode.

    The outer selector is packet[0], so scalar argument overrides cannot drive
    it.  Reviewed nested fixtures exercise opcodes 1..10 in depth, while these
    cases preserve a valid context/callback/buffer graph for every value from
    the original 39-entry TBH table.  Keeping the selector in the absolute
    packet image is important: absolute fixture writes are applied after the
    generic argument-relative pointee writes.
    """
    ctx = emu.SCRATCH + 0x2000
    packet = emu.SCRATCH + 0x4000
    request = emu.SCRATCH + 0x5000
    transfer = emu.SCRATCH + 0x6000
    left = emu.SCRATCH + 0x7000
    right = emu.SCRATCH + 0x8000
    state = bytearray(0x1000)
    state[0x0c:0x10] = (0x00080001).to_bytes(4, "little")
    state[0x10:0x14] = transfer.to_bytes(4, "little")
    state[0x870:0x874] = left.to_bytes(4, "little")
    state[0x880:0x884] = right.to_bytes(4, "little")
    state[0x888:0x88c] = left.to_bytes(4, "little")
    state[0x88c:0x890] = right.to_bytes(4, "little")
    body = bytearray(256)
    body[:12] = bytes((0xa0, 20, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0))
    return (
        {0: ctx, 1: packet, 2: request},
        [(ctx, bytes(state)),
         (packet, bytes((command, 0, 20, 0)) + bytes(252)),
         (request, bytes(body)), (transfer, bytes(0x400)),
         (left, bytes(0x600)), (right, bytes(0x600)),
         (0x20018fec, left.to_bytes(4, "little")),
         (0x20019000, left.to_bytes(4, "little")),
         (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
         (0x20007564, bytes(8)), (0x200079e0, bytes(4)),
         (0x20007aac, bytes(4)), (0x20002fe2, bytes(1)),
         (0x20018d99, bytes(3))],
    )

def _net_08a58_reviewed_case(kind, sizing_only=0):
    """Production-shaped controller option state for the encoder builder."""
    state = bytearray(0x40)
    callbacks = bytes(12)
    if kind == "enabled":
        # Exercise every fixed optional encoder, both aligned timeline records,
        # the paired allocation path, state publication and the final record.
        for offset in (2, 3, 4, 9, 12, 15, 20, 25, 26, 27, 28, 29, 30, 31, 32):
            state[offset] = 1
        state[10:12] = (0x1234).to_bytes(2, "little")
        state[16:19] = b"\x02\x03\x04"
        state[21:25] = b"\x05\x06\x07\x08"
        state[36:40] = (emu.SCRATCH + 0x2800).to_bytes(4, "little")
        # Distinct installed Thumb callbacks let the reviewed target contracts
        # preserve their different one-, three-, and five-argument prototypes.
        callbacks = b"".join(address.to_bytes(4, "little") for address in
                             (0x01030001, 0x01030005, 0x01030009))
        state[13] = 9
        state[14] = 1
    elif kind == "partial-pairs":
        # Reach the second halves of the two short-circuit option pairs:
        # S[31] != 0 with S[9] == 0, and S[27] != 0 with S[28] == 0.
        state[31] = 1
        state[27] = 1
    elif kind != "empty":
        raise ValueError(kind)
    return (
        {0: emu.SCRATCH + 0x1000, 1: int(sizing_only)},
        [(0x21000a30, bytes(state)),
         (0x21000044, callbacks[0:4]),
         (0x2100004c, callbacks[4:8]),
         (0x21000048, callbacks[8:12])],
    )


def _app_33b0c_dump_case(buffered):
    """Ten distinct diagnostic records and the complete logger payload."""
    table = bytearray(10 * 0x1b4)
    for index in range(10):
        base = index * 0x1b4
        for word, value in enumerate((0x1000 + index, 0x2000 + index,
                                      0x3000 + index)):
            table[base + 4 * word:base + 4 * word + 4] = \
                value.to_bytes(4, "little")
    return (
        {1: 0x44556677, 2: 0x8899aabb},
        [(0x20007554, int(buffered).to_bytes(4, "little")),
         (0x20007dac, bytes(table))],
    )


REVIEWED_STATE_CASES = {
    # REV16 consumes a scalar, not a pointer.  Exercise both low-bit values and
    # representative halfword boundaries while the exact two-byte local object
    # remains compared at the downstream command call.
    ("app", 0x0007d696): [
        ({0: value}, []) for value in (0, 1, 0x1234, 0xffff, 0x00120034)
    ],
    # The opcode is scalar while only payload is a pointer.  Override both so
    # the harness does not obtain pointer alignment for r0 from nptr=2, and
    # cover empty, single-byte, and maximum seven-byte command payloads for
    # even and odd opcodes.  The target-bound copy below supplies exact bytes.
    ("app", 0x0007d82e): [
        ({0: opcode, 1: emu.SCRATCH + 0x1200, 2: length},
         [(emu.SCRATCH + 0x1200, bytes.fromhex("10213243546576"))])
        for opcode in (0x36, 0x37) for length in (0, 1, 7)
    ],
    # Fixed framebuffer bounds replace unconstrained stack words.  The first
    # two cases exercise x/y validation through both log sinks; the last walks
    # two mapped row pointers and checks both clear calls.
    ("app", 0x000471cc): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1800,
          2: 5, 3: 0},
         [(emu.SCRATCH + 0x1000,
           (emu.SCRATCH + 0x2000).to_bytes(4, "little") * 201),
          (0x2000230c, (1).to_bytes(4, "little")),
          (0x20007554, bytes(4))]),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1800,
          2: 0, 3: 5},
         [(emu.SCRATCH + 0x1000,
           (emu.SCRATCH + 0x2000).to_bytes(4, "little") * 201),
          (0x2000230c, (1).to_bytes(4, "little")),
          (0x20007554, (1).to_bytes(4, "little"))]),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1800,
          2: 0, 3: 0},
         [(emu.SCRATCH + 0x1000,
           (emu.SCRATCH + 0x2000).to_bytes(4, "little") * 201),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4))]),
        # x end 700 clamps to the inclusive panel boundary 640.
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1800,
          2: 638, 3: 0},
         [(emu.SCRATCH + 0x1000,
           (emu.SCRATCH + 0x2000).to_bytes(4, "little") * 201),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4))]),
        # y end 250 clamps to the inclusive panel boundary 200.
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1800,
          2: 0, 3: 199},
         [(emu.SCRATCH + 0x1000,
           (emu.SCRATCH + 0x2000).to_bytes(4, "little") * 201),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4))]),
        # Negative odd x checks signed division truncation toward zero.
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1800,
          2: 0xfffffffd, 3: 0},
         [(emu.SCRATCH + 0x1000,
           (emu.SCRATCH + 0x2000).to_bytes(4, "little") * 201),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4))]),
        # Four rows make the loop body/backedge repetition observable.
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1800,
          2: 0, 3: 0},
         [(emu.SCRATCH + 0x1000,
           (emu.SCRATCH + 0x2000).to_bytes(4, "little") * 201),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4))]),
    ],
    # No-log return plus normal/special screen close arms through both sinks.
    ("app", 0x00049858): [
        ({0: 0}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4))]),
        ({0: 3}, [(0x2000230c, (1).to_bytes(4, "little")),
                   (0x20007554, bytes(4))]),
        ({0: 4}, [(0x2000230c, (1).to_bytes(4, "little")),
                   (0x20007554, (1).to_bytes(4, "little"))]),
    ],
    # Single-precision domain handling depends on the process-wide errno gate.
    # Pair enabled and disabled states with the directed FP inputs below.
    ("app", 0x00075d5c): [
        ({}, [(0x200035af, bytes((gate,)))])
        for gate in (0xff, 0, 0, 0, 0, 0xff, 0, 0)
    ],
    # Atomic slot reservation: immediate exhaustion, first-slot acquisition,
    # and acquisition after one occupied record.
    ("app", 0x000562a4): [
        ({0: emu.SCRATCH + 0x1000, 1: 0}, []),
        ({0: emu.SCRATCH + 0x1000, 1: 1, 3: 0x1234},
         [(emu.SCRATCH + 0x1000 + 0xd0, bytes(4))]),
        ({0: emu.SCRATCH + 0x1000, 1: 2, 3: 0x1234},
         [(emu.SCRATCH + 0x1000 + 0xd0, (1).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1000 + 0xd8 + 0xd0, bytes(4))]),
    ],
    # The builder's selectors live in persistent controller state rather than
    # argument registers.  Cover the all-absent shape, every major enabled
    # gate in both emit/sizing modes, and the two paired-gate partial states.
    ("net", 0x01008a58): [
        _net_08a58_reviewed_case("empty"),
        _net_08a58_reviewed_case("enabled"),
        _net_08a58_reviewed_case("enabled", sizing_only=1),
        _net_08a58_reviewed_case("partial-pairs"),
    ],
    # Diagnostic table dump selects between the direct and buffered logger
    # from one global flag; exercise both complete ten-record traversals.
    ("app", 0x00033b0c): [
        _app_33b0c_dump_case(buffered=False),
        _app_33b0c_dump_case(buffered=True),
    ],
    # Two global gate bytes.  Cover the call arm and both short-circuit exits;
    # random RAM almost never makes both bytes zero in the same trial.
    ("net", 0x01009184): [
        ({}, [(0x21000a5c, b"\x00\x00")]),
        ({}, [(0x21000a5c, b"\x01\x00")]),
        ({}, [(0x21000a5c, b"\x00\x01")]),
    ],
    ("net", 0x010091a8): [
        ({}, [(0x21000a5c, b"\x00\x00")]),
        ({}, [(0x21000a5c, b"\x01\x00")]),
        ({}, [(0x21000a5c, b"\x00\x01")]),
    ],
    # Null skips publication; non-null exercises the five-argument initializer
    # and all three persistent state writes with byte-truncated selectors.
    ("net", 0x0100a50c): [
        ({0: 0, 1: 0x12, 2: 0x34}, []),
        ({0: emu.SCRATCH + 0x1000, 1: 0x12, 2: 0x34},
         [(emu.SCRATCH + 0x1000, bytes(0x40))]),
    ],
    # Invalid alignment reaches the assertion boundary.  Valid input covers
    # mode zero's local pointer, mode one's publish suppression, and the
    # nonzero/non-one null-pointer path that still publishes state.
    ("net", 0x0100a664): [
        ({0: 3, 1: 5, 2: 0, 3: 0}, []),
        ({0: 3, 1: 5, 2: 2, 3: 0}, []),
        ({0: 3, 1: 5, 2: 4, 3: 0}, []),
        ({0: 3, 1: 5, 2: 4, 3: 1}, []),
        ({0: 3, 1: 5, 2: 4, 3: 2}, []),
    ],
    # These compact TBB dispatchers were not taint-derived because their
    # selectors are transformed before the table branch.  Pin every valid
    # public value plus one invalid/default value explicitly.
    ("net", 0x0101e2cc): [({0: value}, []) for value in (1, 2, 4, 8, 3)],
    ("net", 0x01028464): [({0: value}, []) for value in (1, 2, 4, 8, 3)],
    ("net", 0x01028486): [({0: value}, []) for value in (1, 2, 4, 8, 3)],
    # The radio buffer mode is read from global controller state.  Modes zero
    # through four cover both successful result families and the in-range
    # default; five covers the unsigned range-check default.
    ("net", 0x01032764): [
        ({}, [(0x21004a9c, bytes((mode,)))]) for mode in range(6)
    ],
    # BLE PUT opcodes 1-5. Model the real three-buffer ownership graph instead
    # of allowing random ctx+0x10/callback words to become nested pointers.
    # For each opcode cover the minimum production payload and a longer or
    # length-error-shaped packet. Opcode 4 forwards both advertised packet[2]
    # and the request's independently controlled length to its parser helper.
    ("app", 0x0001a75c): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000,
          2: emu.SCRATCH + 0x3000},
         [(emu.SCRATCH + 0x1000,
           bytes(0x0c) + (0x00080001).to_bytes(4, "little") +
           (emu.SCRATCH + 0x4000).to_bytes(4, "little") + bytes(0x20)),
          (emu.SCRATCH + 0x2000,
           bytes((command, 0, advertised & 0xff, advertised >> 8)) +
           bytes((0x40 + i) & 0xff for i in range(60))),
          (emu.SCRATCH + 0x3000,
           bytes((0xa0, actual & 0xff, actual >> 8)) +
           bytes((0x60 + i) & 0xff for i in range(61))),
          (emu.SCRATCH + 0x4000, bytes(0x100)),
          (0x2000230c, (0).to_bytes(4, "little")),
          (0x20007554, (0).to_bytes(4, "little"))])
        for command, advertised, actual in (
            (1, 1, 1), (1, 5, 4),
            (2, 1, 1), (2, 8, 7),
            (3, 1, 1), (3, 4, 9),
            (4, 4, 4), (4, 7, 3),
            (5, 1, 1), (5, 6, 2),
        )
    ] + [
        ({0: emu.SCRATCH + 0x2000, 1: emu.SCRATCH + 0x3000,
          2: emu.SCRATCH + 0x4000},
         [(emu.SCRATCH + 0x2000,
           bytes(0x0c) + (0x00080001).to_bytes(4, "little") +
           (emu.SCRATCH + 0x5000).to_bytes(4, "little") + bytes(0x85c) +
           (emu.SCRATCH + 0x6000).to_bytes(4, "little") + bytes(0x30) +
           (emu.SCRATCH + 0x7000).to_bytes(4, "little") + bytes(0x80)),
          (emu.SCRATCH + 0x3000,
           bytes((6, 0, advertised & 0xff, advertised >> 8)) + bytes(60)),
          (emu.SCRATCH + 0x4000,
           bytes((0xa0, actual & 0xff, actual >> 8, 1, subop,
                  total & 0xff, total >> 8, current & 0xff, current >> 8,
                  1, present, 0)) + bytes(range(12, 64))),
          (emu.SCRATCH + 0x5000, bytes(0x100)),
          (emu.SCRATCH + 0x6000, bytes(0x200)),
          (emu.SCRATCH + 0x7000, bytes(0x600)),
          (0x20018000 + 0xfec,
           (emu.SCRATCH + 0x6000).to_bytes(4, "little")),
          (0x2000230c, (0).to_bytes(4, "little")),
          (0x20007554, (0).to_bytes(4, "little")),
          (0x2000d6f6, state), (0x2000d70a, state),
          (0x2000d710, state),
          (0x2000f6de, state),
          (0x20010327, b"\x01" + bytes(0x17ff))])
        for subop, advertised, actual, total, current, present, state in (
            # length mismatch, simple configuration actions 1/2/6
            (1, 20, 19, 1, 1, 0, bytes(12)),
            (1, 21, 21, 1, 1, 0, bytes(12)),
            (2, 5, 5, 1, 1, 0, bytes(12)),
            (6, 7, 7, 1, 1, 0, bytes(12)),
            # note: single, first, middle, final, and order error
            (3, 12, 12, 1, 1, 0, bytes(12)),
            (3, 16, 16, 3, 1, 1, bytes(12)),
            (3, 12, 12, 3, 2, 1, b"\x04\x00\x03\x00\x01\x00" + bytes(6)),
            (3, 12, 12, 3, 3, 1, b"\x07\x00\x03\x00\x02\x00" + bytes(6)),
            (3, 12, 12, 3, 2, 1, bytes(12)),
            # stock/news multipart first, middle, final-order-error, order error
            (4, 12, 12, 3, 1, 0, bytes(12)),
            (4, 12, 12, 3, 2, 0, b"\x03\x00\x03\x00\x01\x00" + bytes(6)),
            (4, 12, 12, 3, 3, 0, bytes(12)),
            (4, 12, 12, 3, 2, 0, bytes(12)),
            (5, 12, 12, 3, 1, 0, bytes(12)),
            (5, 12, 12, 3, 2, 0, b"\x03\x00\x03\x00\x01\x00" + bytes(6)),
            (5, 12, 12, 3, 3, 0, bytes(12)),
            (5, 12, 12, 3, 2, 0, bytes(12)),
            # Successful stock/news single and multipart-final parsing.
            (4, 16, 16, 1, 1, 0, bytes(12)),
            (4, 12, 12, 3, 3, 0, b"\x06\x00\x03\x00\x02\x00" + bytes(6)),
            (5, 16, 16, 1, 1, 0, bytes(12)),
            (5, 12, 12, 3, 3, 0, b"\x06\x00\x03\x00\x02\x00" + bytes(6)),
        )
    ] + [
        ({0: emu.SCRATCH + 0x2000, 1: emu.SCRATCH + 0x3000,
          2: emu.SCRATCH + 0x4000},
         [(emu.SCRATCH + 0x2000,
           bytes(0x0c) + (0x00080001).to_bytes(4, "little") +
           (emu.SCRATCH + 0x5000).to_bytes(4, "little") + bytes(0x900)),
          (emu.SCRATCH + 0x3000,
           bytes((command, 0, advertised & 0xff, advertised >> 8)) + bytes(60)),
          (emu.SCRATCH + 0x4000,
           bytes((0xa0, actual & 0xff, actual >> 8, 1, mode, value)) + bytes(58)),
          (emu.SCRATCH + 0x5000, bytes(0x100)),
          (0x2000230c, (0).to_bytes(4, "little")),
          (0x20007554, (0).to_bytes(4, "little"))])
        for command, advertised, actual, mode, value in (
            (7, 5, 5, 0, 2),
            (8, 7, 6, 3, 1),
            (8, 7, 7, 3, 1),
            (8, 7, 7, 3, 2),
            (8, 7, 7, 4, 0),
        )
    ] + [
        ({0: emu.SCRATCH + 0x2000, 1: emu.SCRATCH + 0x3000,
          2: emu.SCRATCH + 0x4000},
         [(emu.SCRATCH + 0x2000,
           bytes(0x0c) + (0x00080001).to_bytes(4, "little") +
           (emu.SCRATCH + 0x5000).to_bytes(4, "little") + bytes(0x85c) +
           (emu.SCRATCH + 0x6000).to_bytes(4, "little") + bytes(0x0c) +
           (emu.SCRATCH + 0x7000).to_bytes(4, "little") + bytes(0x40)),
          (emu.SCRATCH + 0x3000,
           bytes((9, 0, actual & 0xff, actual >> 8)) + bytes(60)),
          (emu.SCRATCH + 0x4000,
           bytes((0xa0, advertised & 0xff, advertised >> 8, 1, action, 2,
                  4, 0)) + bytes(range(8, 64))),
          (emu.SCRATCH + 0x5000, bytes(0x300)),
          (emu.SCRATCH + 0x6000, bytes(0x100)),
          (emu.SCRATCH + 0x7000, bytes(0x300)),
          (0x2000230c, (0).to_bytes(4, "little")),
          (0x20007554, (0).to_bytes(4, "little"))])
        for advertised, actual, action in (
            (16, 15, 2),
            (16, 16, 2), (16, 16, 2),
            (8, 8, 5), (8, 8, 5),
        )
    ] + [
        ({0: emu.SCRATCH + 0x2000, 1: emu.SCRATCH + 0x3000,
          2: emu.SCRATCH + 0x4000},
         [(emu.SCRATCH + 0x2000,
           bytes(0x0c) + (0x00080001).to_bytes(4, "little") +
           (emu.SCRATCH + 0x5000).to_bytes(4, "little") + bytes(0x85c) +
           (emu.SCRATCH + 0x6000).to_bytes(4, "little") + bytes(0x0c) +
           (emu.SCRATCH + 0x7000).to_bytes(4, "little") + bytes(0x40)),
          (emu.SCRATCH + 0x3000, bytes((9, 0, 24, 0)) + bytes(60)),
          (emu.SCRATCH + 0x4000,
           bytes((0xa0, 24, 0, 1, 1, 1, 0, 1, 0, 1, 2, 3,
                  0x41, 0x42, 0x43, 0x44, 1, 2, 3, 4, 5, 6, 7, 8)) +
           bytes(40)),
          (emu.SCRATCH + 0x5000, bytes(0x300)),
          (emu.SCRATCH + 0x6000, bytes(0x100)),
          (emu.SCRATCH + 0x7000, bytes(0x300)),
          (0x2000230c, (0).to_bytes(4, "little")),
          (0x20007554, (0).to_bytes(4, "little"))])
        for _local in (1, 0)
    ] + [
        ({0: emu.SCRATCH + 0x2000, 1: emu.SCRATCH + 0x3000,
          2: emu.SCRATCH + 0x4000},
         [(emu.SCRATCH + 0x2000,
           bytes(0x0c) + (0x00080001).to_bytes(4, "little") +
           (emu.SCRATCH + 0x5000).to_bytes(4, "little") + bytes(0x85c) +
           (emu.SCRATCH + 0x6000).to_bytes(4, "little") + bytes(0x0c) +
           (emu.SCRATCH + 0x7000).to_bytes(4, "little") + bytes(0x40)),
          (emu.SCRATCH + 0x3000, bytes((9, 0, 24, 0)) + bytes(60)),
          (emu.SCRATCH + 0x4000,
           bytes((0xa0, 24, 0, 1, 1, 3, 0, sequence, 0, 1, 2, 3,
                  0x41, 0x42, 0x43, 0x44, 1, 2, 3, 4, 5, 6, 7, 8)) +
           bytes(40)),
          (emu.SCRATCH + 0x5000, bytes(0x300)),
          (emu.SCRATCH + 0x6000, bytes(0x100)),
          (emu.SCRATCH + 0x7000, bytes(0x300)),
          (0x2000d702, text_size.to_bytes(2, "little") +
           total_state.to_bytes(2, "little") + packet_state.to_bytes(2, "little") +
           bytes(2)),
          (0x2001046b, bytes(0x217)),
          (0x20018000 + 0xffc, (0x20019000).to_bytes(4, "little")),
          (0x20019000, bytes(0x300)),
          (0x2000230c, (0).to_bytes(4, "little")),
          (0x20007554, (0).to_bytes(4, "little"))])
        for sequence, text_size, total_state, packet_state in (
            (1, 0, 0, 0),
            (2, 12, 3, 1),
            (3, 24, 3, 2),
            (3, 24, 3, 2),
            (2, 0, 3, 0),
        )
    ] + [
        ({0: emu.SCRATCH + 0x2000, 1: emu.SCRATCH + 0x3000,
          2: emu.SCRATCH + 0x4000},
         [(emu.SCRATCH + 0x2000,
           bytes(0x0c) + (0x00080001).to_bytes(4, "little") +
           (emu.SCRATCH + 0x5000).to_bytes(4, "little") + bytes(0x85c) +
           (emu.SCRATCH + 0x6000).to_bytes(4, "little") + bytes(0x0c) +
           (emu.SCRATCH + 0x7000).to_bytes(4, "little") + bytes(0x40)),
          (emu.SCRATCH + 0x3000, bytes((9, 0, 24, 0)) + bytes(60)),
          (emu.SCRATCH + 0x4000,
           bytes((0xa0, 24, 0, 1, action, 1, 0, 1, 0, 2, 4, 0,
                  0x41, 0x42, 0x43, 0x44, 1, 2, 3, 4, 5, 6, 7, 8)) +
           bytes(40)),
          (emu.SCRATCH + 0x5000, bytes(0x300)),
          (emu.SCRATCH + 0x6000, bytes(0x100)),
          (emu.SCRATCH + 0x7000, bytes(0x300)),
          (0x2001046a, bytes((0,))),
          (0x2000230c, (0).to_bytes(4, "little")),
          (0x20007554, (0).to_bytes(4, "little"))])
        for action, _local in ((3, 1), (3, 0), (7, 1), (7, 0))
    ] + [
        ({0: emu.SCRATCH + 0x2000, 1: emu.SCRATCH + 0x3000,
          2: emu.SCRATCH + 0x4000},
         [(emu.SCRATCH + 0x2000,
           bytes(0x0c) + (0x00080001).to_bytes(4, "little") +
           (emu.SCRATCH + 0x5000).to_bytes(4, "little") + bytes(0x85c) +
           (emu.SCRATCH + 0x6000).to_bytes(4, "little") + bytes(0x0c) +
           (emu.SCRATCH + 0x7000).to_bytes(4, "little") + bytes(0x40)),
          (emu.SCRATCH + 0x3000, bytes((9, 0, 24, 0)) + bytes(60)),
          (emu.SCRATCH + 0x4000,
           bytes((0xa0, 24, 0, 1, action, 3, 0, sequence, 0, 2, 4, 0,
                  0x41, 0x42, 0x43, 0x44, 1, 2, 3, 4, 5, 6, 7, 8)) +
           bytes(40)),
          (emu.SCRATCH + 0x5000, bytes(0x300)),
          (emu.SCRATCH + 0x6000, bytes(0x100)),
          (emu.SCRATCH + 0x7000, bytes(0x300)),
          (0x2000d704, total_state.to_bytes(2, "little") +
           packet_state.to_bytes(2, "little") + size_state.to_bytes(2, "little")),
          (0x2001046a, bytes(0x218)),
          (0x2000230c, (0).to_bytes(4, "little")),
          (0x20007554, (0).to_bytes(4, "little"))])
        for action, sequence, total_state, packet_state, size_state in (
            (3, 1, 0, 0, 0),
            (3, 2, 3, 1, 12),
            (3, 3, 3, 2, 24),
            (3, 3, 3, 2, 24),
            (3, 2, 3, 0, 0),
            (7, 3, 3, 2, 24),
        )
    ] + [
        ({0: emu.SCRATCH + 0x2000, 1: emu.SCRATCH + 0x3000,
          2: emu.SCRATCH + 0x4000},
         [(emu.SCRATCH + 0x2000,
           bytes(0x0c) + (0x00080001).to_bytes(4, "little") +
           (emu.SCRATCH + 0x5000).to_bytes(4, "little") + bytes(0x900)),
          (emu.SCRATCH + 0x3000,
           bytes((10, 0, packet_length & 0xff, packet_length >> 8)) + bytes(252)),
          (emu.SCRATCH + 0x4000, payload + bytes(256 - len(payload))),
          (emu.SCRATCH + 0x5000, bytes(0x300)),
          (0x20018000 + 0x1000, (emu.SCRATCH + 0x7000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x7000, bytes(0x200)),
          (0x20010323, bytes(4)),
          (0x2000230c, (0).to_bytes(4, "little")),
          (0x20007554, (0).to_bytes(4, "little"))])
        for payload, packet_length in (
            (_op10_guidance_payload((1, 1, 1, 1, 1)),
             len(_op10_guidance_payload((1, 1, 1, 1, 1))) - 1),
            (bytes((0xa0, 6, 0, 1, 0, 0)), 6),
            (bytes((0xa0, 6, 0, 1, 0, 0)), 6),
            (_op10_guidance_payload((1, 1, 1, 1, 1)),
             len(_op10_guidance_payload((1, 1, 1, 1, 1)))),
            (_op10_guidance_payload((1, 1, 1, 1, 1)),
             len(_op10_guidance_payload((1, 1, 1, 1, 1)))),
            *[(p, len(p)) for p in (
                _op10_guidance_payload((25, 1, 1, 1, 1)),
                _op10_guidance_payload((1, 25, 1, 1, 1)),
                _op10_guidance_payload((1, 1, 65, 1, 1)),
                _op10_guidance_payload((1, 1, 1, 25, 1)),
                _op10_guidance_payload((1, 1, 1, 1, 25)),
                *(_op10_guidance_payload((1, 1, 1, 1, 1), i)
                  for i in range(5)),
            )],
        )
    ] + [
        ({0: emu.SCRATCH + 0x2000, 1: emu.SCRATCH + 0x3000,
          2: emu.SCRATCH + 0x4000},
         [(emu.SCRATCH + 0x2000,
           bytes(0x0c) + (0x00080001).to_bytes(4, "little") +
           (emu.SCRATCH + 0x5000).to_bytes(4, "little") + bytes(0x900)),
          (emu.SCRATCH + 0x3000, bytes((10, 0, 20, 0)) + bytes(60)),
          (emu.SCRATCH + 0x4000,
           bytes((0xa0, 20, 0, 1, 2, total, 0, sequence, 0)) +
           bytes(range(9, 64))),
          (emu.SCRATCH + 0x5000, bytes(0x300)),
          (0x20018000 + 0x1000, (emu.SCRATCH + 0x7000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x7000, bytes(0x200)),
          (0x2000d704, total_state.to_bytes(2, "little") +
           packet_state.to_bytes(2, "little") + size_state.to_bytes(2, "little")),
          (0x20015e52, bytes(0x1210)),
          (0x20010323, bytes(4)),
          (0x2000230c, (0).to_bytes(4, "little")),
          (0x20007554, (0).to_bytes(4, "little"))])
        for total, sequence, total_state, packet_state, size_state in (
            (1, 1, 0, 0, 0),       # single
            (3, 1, 0, 0, 0),       # first
            (3, 2, 3, 1, 11),      # middle
            (3, 3, 3, 2, 22),      # final local
            (3, 3, 3, 2, 22),      # final non-local
            (3, 2, 3, 0, 0),       # order error
            (3, 3, 3, 1, 11),      # final-order error
            (3, 2, 3, 1, 0x120f),  # middle capacity
            (3, 3, 3, 2, 0x1210),  # final capacity
        )
    ] + [
        ({0: 0x2001a000, 1: 0x2001b000, 2: 0x2001c000},
         [(0x2001a000,
           bytes(0x0c) + (0x00080001).to_bytes(4, "little") +
           (0x2001d000).to_bytes(4, "little") + bytes(0x900)),
          (0x2001b000, bytes((10, 0, 20, 0)) + bytes(60)),
          (0x2001c000,
           bytes((0xa0, 20, 0, 1, 3, total, 0, sequence, 0, 2)) +
           bytes(range(10, 64))),
          (0x2001d000, bytes(0x300)),
          (0x2001f000 + 0x1000, (0x2001e000).to_bytes(4, "little")),
          (0x2001e000, bytes(0x200)),
          (0x2000d6fc, total_state.to_bytes(2, "little") +
           packet_state.to_bytes(2, "little") + size_state.to_bytes(2, "little")),
          (0x20011d82, bytes(0x40d0)),
          (0x20010322, bytes(5)),
          (0x2000230c, (0).to_bytes(4, "little")),
          (0x20007554, (0).to_bytes(4, "little"))])
        for total, sequence, total_state, packet_state, size_state in (
            (1, 1, 0, 0, 0),
            (3, 1, 0, 0, 0),
            (3, 2, 3, 1, 10),
            (3, 3, 3, 2, 20),
            (3, 3, 3, 2, 20),
            (3, 2, 3, 0, 0),
            (3, 3, 3, 1, 10),
            (3, 2, 3, 1, 0x40cf),
            (3, 3, 3, 2, 0x40d0),
        )
    ] + [
        _op10_nav_case(4, active=active)
        for active in (0, 1)
    ] + [
        _op10_nav_case(5)
    ] + [
        _op10_nav_case(6, oversize=oversize)
        for oversize in (False, False, True, True)
    ],
    # Ten fixed diagnostic rows.  Seed the production table explicitly so the
    # two runs observe identical row words instead of unrelated randomized RAM.
    ("app", 0x00033b4c): [
        ({}, [(0x20008eb4,
               b"".join((i * 0x10001 + j).to_bytes(4, "little")
                         for i in range(10) for j in range(109))),
              (0x20007554, sink.to_bytes(4, "little"))])
        for sink in (0, 1)
    ],
    # IRQ queue completion: callback on both flag families plus every skip
    # predicate (pending, tail bit, and producer/consumer threshold).
    ("app", 0x000857e0): [
        _irq_queue_case(0, 0, 0, 2, 0, 0),
        _irq_queue_case(0, 1, 0, 2, 0, 7),
        _irq_queue_case(0, 0, 1, 2, 0, 7),
        _irq_queue_case(0x20000000, 1, 0, 2, 0, 7),
        _irq_queue_case(0x20000000, 0, 0, 2, 0, 1),
        _irq_queue_case(0x20000000, 0, 0, 2, 0, 2),
    ],
    # Panoramic-map UI state is a mutually exclusive event/refresh state
    # machine.  Fully random absolute RAM can assert several one-shot flags at
    # once, which firmware never produces.  Hold the expensive initial refresh
    # complete, trigger only the 0x1210 payload event, and cover logger disabled,
    # direct sink, and fallback sink with the exact signed 32-bit level global.
    ("app", 0x0003e7f8): [
        ({0: 0, 1: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(0x200)),
          (emu.SCRATCH + 0x10b1, (0x1210).to_bytes(4, "little")),
          (0x20004bbc, b"\x01"),
          (0x20010322, b"\x00\x01\x00\x00"),
          (0x2000230c, level.to_bytes(4, "little", signed=True)),
          (0x20007554, sink.to_bytes(4, "little"))])
        for level, sink in ((0, 0), (3, 0), (3, 1))
    ],
    # Four-state generated battery estimator.  Both cases traverse the complete
    # finite production update (48 calls / 105 events) with distinct sensor
    # inputs while keeping every one-based state index and matrix bound valid.
    ("app", 0x0000c358): [
        ({0: _C358_P, 1: _C358_P + 0x7000,
          2: _C358_P + 0x7100, 3: _C358_P + 0x7200}, _C358_SETUP),
        ({0: _C358_P, 1: _C358_P + 0x7000,
          2: _C358_P + 0x7100, 3: _C358_P + 0x7200}, _C358_SETUP),
        ({0: _C358_P, 1: _C358_P + 0x7000,
          2: _C358_P + 0x7100, 3: _C358_P + 0x7200}, _C358_SETUP),
    ],
    # libLC3 LTPF analysis: the fifth argument is stack-passed.  Exercise both
    # frame durations, endpoint samplerates, inactive/active history, and
    # silence/non-zero PCM.  The state allocation includes both resampler
    # histories through tc at +0x484.
    ("app", 0x0006ab80): [
        ({0: dt, 1: sr, 2: emu.SCRATCH + 0x1000,
          3: emu.SCRATCH + 0x2200},
         [(emu.STACK_TOP, (emu.SCRATCH + 0x3000).to_bytes(4, "little")),
          (0x0008c938 + 4 * sr, (0x00080001).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1000,
           bytes((active, 0, 0, 0)) + pitch.to_bytes(4, "little") +
           nc0.to_bytes(4, "little") + nc1.to_bytes(4, "little") +
           bytes(0x478)),
          (emu.SCRATCH + 0x2000, sample.to_bytes(2, "little", signed=True) * 0x400),
          (emu.SCRATCH + 0x3000, bytes(8))])
        for dt, sr, active, pitch, nc0, nc1, sample in (
            (0, 0, 0, 0, 0x00000000, 0x00000000, 0),
            (1, 4, 0, 320, 0x3f70a3d7, 0x3f70a3d7, 1200),
            (0, 2, 1, 256, 0x3f666666, 0x3f570a3d, -900),
            (1, 3, 1, 400, 0x3f000000, 0x3f400000, 300),
        )
    ],
    # Radio-event dispatcher: its selected client callback lives in the
    # absolute scheduler object rather than in an argument-owned structure.
    # Materialize slot zero so callback-taking selector arms are compared as
    # calls instead of as unrelated random-pointer faults.
    ("net", 0x01023ad8): [
        ({0: selector},
         [(0x210016f0 + 0x4a, b"\x00"),
          (0x210016f0 + 0xd0, (0x00080001).to_bytes(4, "little")),
          (0x210016f0 + 0xd4, (0x1234).to_bytes(4, "little"))])
        for selector in range(8)
    ],
    ("app", 0x00026338): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(0x14) + active.to_bytes(4, "little") +
           bytes((mode, 1, 2, 3, 4, 5)) + bytes(2)),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4))])
        for active, mode in ((0, 3), (1, 3), (1, 4), (1, 5))
    ],
    ("app", 0x0002685c): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes((0, branch)) + bytes(0x1100)),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
          (0x2000302c, b"\x01"), (0x20018d90, b"\x00")])
        for branch in (0, 1)
    ],
    # libLC3 SNS analyzer: data/x/y are stack-passed after the four register
    # arguments. Use valid enum domains and production-sized zeroed buffers.
    ("app", 0x0006c778): [
        ({0: dt, 1: sr, 2: emu.SCRATCH + 0x1000, 3: att},
         [(emu.STACK_TOP,
           b"".join((emu.SCRATCH + off).to_bytes(4, "little")
                    for off in (0x1200, 0x1400, 0x1c00))),
          (emu.SCRATCH + 0x1000, bytes(0x100)),
          (emu.SCRATCH + 0x1200, bytes(0x100)),
          (emu.SCRATCH + 0x1400, bytes(0x800)),
          (emu.SCRATCH + 0x1c00, bytes(0x800))])
        for dt, sr, att in ((0, 0, 0), (1, 4, 1))
    ],
    ("app", 0x0000e53c): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000,
          2: emu.SCRATCH + 0x4000, 3: emu.SCRATCH + 0x6000},
         [(emu.SCRATCH + 0x1000, bytes(0x40)),
          (emu.SCRATCH + 0x2000, bytes(0x1600)),
          (emu.SCRATCH + 0x4000, bytes(0x1778)),
          (emu.SCRATCH + 0x6000, bytes(4))]),
    ],
    # libLC3 spectrum analyzer: all five pointer arguments after `pitch` are
    # stack-passed. Pin production-sized frames and zeroed analysis state;
    # arbitrary stack RAM otherwise becomes multi-billion loop bounds.
    ("app", 0x0006f4a0): [
        ({0: dt, 1: sr, 2: nbytes, 3: pitch},
         [(emu.STACK_TOP,
           b"".join((emu.SCRATCH + off).to_bytes(4, "little")
                    for off in (0x2800, 0x2900, 0x2a00, 0x3200, 0x3800))),
          (emu.SCRATCH + 0x2800, bytes(0x100)),
          (emu.SCRATCH + 0x2900,
           spec_words[0].to_bytes(4, "little") +
           (spec_words[1] & 0xffffffff).to_bytes(4, "little") + bytes(0xf8)),
          (emu.SCRATCH + 0x2a00,
           sample_word.to_bytes(4, "little") * (0x800 // 4)),
          (emu.SCRATCH + 0x3200, bytes(0x600)),
          (emu.SCRATCH + 0x3800, bytes(0x100))])
        for dt, sr, nbytes, pitch, spec_words, sample_word in (
            # Production endpoints plus the 320-byte AC-side-information
            # boundary.  Non-zero spectra and history state prevent the
            # gain estimator/reset path from being proved only on silence.
            (0, 0, 20, 0, (0x00000000, 0), 0x00000000),
            (1, 4, 100, 1, (0x41200000, 7), 0x3f800000),
            (0, 2, 319, 0, (0xc1200000, -5), 0xbf000000),
            (0, 2, 320, 1, (0x41c80000, 20), 0x40000000),
            (1, 4, 321, 1, (0xc1c80000, -20), 0x40400000),
        )
        for _ in (0,)
    ],
    # Pure hard-float sample encoder. Arguments five and six are stack-passed
    # output/count pointers; pin them to dynamic scratch and cover reciprocal,
    # direct-scale, zero and signed-nonzero sample paths.
    ("app", 0x0006f164): [
        ({0: width, 1: rows, 2: exponent, 3: emu.SCRATCH + 0x2000},
         [(emu.STACK_TOP, (emu.SCRATCH + 0x2200).to_bytes(4, "little") +
                          (emu.SCRATCH + 0x2300).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000,
           (sample_word.to_bytes(4, "little") +
            ((sample_word ^ 0x80000000) & 0xffffffff).to_bytes(4, "little")) * 200),
          (emu.SCRATCH + 0x2200, bytes(0x400)),
          (emu.SCRATCH + 0x2300, bytes(4))])
        # +/-65 crosses the scale-table block loop; large samples exercise
        # saturation, while zero/nonzero pairs cover nq trimming/reset.
        for width, rows, exponent, sample_word in (
            (0, 0, -65, 0x00000000), (0, 0, -1, 0x3f800000),
            (0, 0, 0, 0x47000000), (0, 0, 1, 0x3f800000),
            (1, 4, 65, 0x40000000))
    ],
    # Google liblc3 mixed-radix FFT.  Valid production transform lengths keep
    # every loop bounded; the three disjoint regions cover input and both
    # scratch/output buffers. Cover every production transform length.
    ("app", 0x0006b3c8): [
        ({0: emu.SCRATCH + 0x0200, 1: n,
          2: emu.SCRATCH + 0x0c00, 3: emu.SCRATCH + 0x1600},
         [(emu.SCRATCH + 0x0200, bytes(0x800)),
          (emu.SCRATCH + 0x0c00, bytes(0x800)),
          (emu.SCRATCH + 0x1600, bytes(0x800))])
        for n in (30, 40, 60, 80, 90, 120, 160, 180, 240)
    ],
    # libLC3 forward MDCT: duration is 7.5/10 ms and source/destination sample
    # rates span the five production enum values.  Arguments five and six are
    # stack-passed delay/output pointers; cover every valid selector tuple and
    # provide disjoint maximum-sized sample, delay and output regions.
    ("app", 0x0006b9b8): [
        ({0: dt, 1: sr, 2: sr_dst, 3: emu.SCRATCH + 0x0200},
         [(emu.STACK_TOP,
           (emu.SCRATCH + 0x0c00).to_bytes(4, "little") +
           (emu.SCRATCH + 0x1600).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0200,
           (struct.pack("<f", 1.0) + struct.pack("<f", -0.5)) * 256),
          (emu.SCRATCH + 0x0c00,
           (struct.pack("<f", 0.25) + struct.pack("<f", -0.75)) * 256),
          (emu.SCRATCH + 0x1600, bytes(0x800))])
        for dt in (0, 1) for sr in range(5) for sr_dst in range(5)
    ],
    # liblc3 pitch detection production bounds: 16-sample aligned minimum,
    # mid-frame, and 128-sample maximum with low/mid/high previous lag.
    ("app", 0x000698d0): [
        ({0: emu.SCRATCH + 0x0800, 1: emu.SCRATCH + 0x1200,
          2: n, 3: emu.SCRATCH + 0x0d00},
         [(emu.SCRATCH + 0x0c84, tc.to_bytes(4, "little")),
          (emu.SCRATCH + 0x1000, bytes(0x400))])
        for n, tc in ((16, 0), (64, 50), (128, 97))
    ],
    # Pool allocator: materialize the global root and one free slot so the
    # callback-owned grow loop reaches its initialization/return path.
    ("app", 0x00076c3c): [
        ({0: emu.SCRATCH + 0x0800},
         [(0x0009873c, (emu.SCRATCH + 0x1000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1000, bytes(0x18) + (1).to_bytes(4, "little") +
           bytes(0x2c) + (0).to_bytes(4, "little") + (1).to_bytes(4, "little") +
           (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1200, bytes(0x68))]),
    ],
    # Arithmetic-coder finalizer: random pointer differences and pending-byte
    # counts can manufacture unbounded loops.  These valid bounded states cover
    # empty output, buffered-bit backfill, and pending-0xff/carry emission.
    ("app", 0x000685f4): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (0x00123456).to_bytes(4, "little") +
           (0x00010000).to_bytes(4, "little") + (-1).to_bytes(4, "little", signed=True) +
           bytes(28) + (emu.SCRATCH + 0x1820).to_bytes(4, "little") +
           (emu.SCRATCH + 0x1800).to_bytes(4, "little") +
           (emu.SCRATCH + 0x1800).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1800, bytes(0x20))]),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (0x0000abcd).to_bytes(4, "little") +
           (0x00000100).to_bytes(4, "little") + (0x42).to_bytes(4, "little") +
           bytes(12) + (0x44332211).to_bytes(4, "little") +
           (5).to_bytes(4, "little") + bytes(8) +
           (emu.SCRATCH + 0x1820).to_bytes(4, "little") +
           (emu.SCRATCH + 0x1800).to_bytes(4, "little") +
           (emu.SCRATCH + 0x1804).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1800, b"ABCD" + bytes(0x1c))]),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (0x00ff1000).to_bytes(4, "little") +
           (0).to_bytes(4, "little") + (0x7e).to_bytes(4, "little") +
           (1).to_bytes(4, "little") + (2).to_bytes(4, "little") +
           bytes(20) + (emu.SCRATCH + 0x1820).to_bytes(4, "little") +
           (emu.SCRATCH + 0x1800).to_bytes(4, "little") +
           (emu.SCRATCH + 0x1800).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1800, bytes(0x20))]),
    ],
    # Channel-start state: one initialized channel with an already-created
    # backend avoids the production wait-for-worker spin while exercising the
    # descriptor installation and asynchronous start path.
    ("app", 0x00067304): [
        ({0: emu.SCRATCH + 0x0200, 1: emu.SCRATCH + 0x0300, 2: 8, 3: 0},
         [(emu.SCRATCH + 0x0200, (emu.SCRATCH + 0x1000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0204, b"\x00"),
          (emu.SCRATCH + 0x0300, bytes(16)),
          (0x2000b384, (1).to_bytes(4, "little") + bytes(0x18) + b"\x01\x00\x00\x00" +
           (0xffffffff).to_bytes(4, "little"))]),
    ],
    # Pool/free validator: null, valid external self-owned, valid pool-owned,
    # and the two ownership assertion boundaries.
    ("app", 0x0005833c): [
        ({0: 0}, []),
        ({0: emu.SCRATCH + 0x0d00},
         [(emu.SCRATCH + 0x0d00,
           (emu.SCRATCH + 0x0d00 - 0x148).to_bytes(4, "little"))]),
        ({0: 0x2000add4}, [(0x2000add4, (emu.SCRATCH + 0x0100).to_bytes(4, "little"))]),
        ({0: 0x2000add4}, [(0x2000add4, (0x2000add4 - 0x148).to_bytes(4, "little"))]),
        ({0: emu.SCRATCH + 0x0d00}, [(emu.SCRATCH + 0x0d00, (0).to_bytes(4, "little"))]),
    ],
    # Reverse-copy helper: caller guarantees disjoint non-empty ranges; cover
    # one/multi-byte copies plus the overlap assertion boundary.
    ("app", 0x0005ec84): [
        ({0: emu.SCRATCH + 0x0800, 1: emu.SCRATCH + 0x0900, 2: 1},
         [(emu.SCRATCH + 0x0900, b"A")]),
        ({0: emu.SCRATCH + 0x0800, 1: emu.SCRATCH + 0x0900, 2: 4},
         [(emu.SCRATCH + 0x0900, b"ABCD")]),
        ({0: emu.SCRATCH + 0x0800, 1: emu.SCRATCH + 0x0801, 2: 4}, []),
    ],
    # Intrusive-list unlink: head removal, linked removal, and null assertion.
    ("app", 0x0005f3d8): [
        ({0: 0, 1: emu.SCRATCH + 0x0a00},
         [(emu.SCRATCH + 0x0a04, (emu.SCRATCH + 0x0b00).to_bytes(4, "little"))]),
        ({0: emu.SCRATCH + 0x0c00, 1: emu.SCRATCH + 0x0a00},
         [(emu.SCRATCH + 0x0c04, (emu.SCRATCH + 0x0a00).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0a04, (emu.SCRATCH + 0x0b00).to_bytes(4, "little"))]),
        ({0: 0, 1: 0}, []),
    ],
    ("net", 0x01012438): [
        ({0: emu.SCRATCH + 0x0200, 1: emu.SCRATCH + 0x0300},
         [(emu.SCRATCH + 0x0200, bytes(0x70)),
          (emu.SCRATCH + 0x0300, bytes([0x11, flags]) + bytes(0x12) +
           bytes([mode, 1, secondary, 0, 1, 0, 1, 0, 1, 0, 1, 0]))])
        for mode in (1, 2, 3)
        for secondary, flags in ((1, 0x20), (3, 0x00), (2, 0x18))
    ],
    # Fixed-size mask compositor: its 8*199*320 traversal necessarily exceeds
    # the generic emulator instruction cap. Seed a nonzero first pixel so the
    # prefix comparison reaches an externally visible semantic write.
    ("app", 0x000438d0): [
        ({}, [(0x2000a034, (emu.SCRATCH + 0x2000).to_bytes(4, "little")),
              (emu.SCRATCH + 0x2000, (emu.SCRATCH + 0x3000).to_bytes(4, "little")),
              (emu.SCRATCH + 0x3000, b"\xff"),
              (0x000ab6e0, b"\x7f")]),
    ],
    # Global object/vtable tail dispatcher.
    ("app", 0x000543c8): [
        ({}, [(0x20002168, (emu.SCRATCH + 0x0700).to_bytes(4, "little")),
              (emu.SCRATCH + 0x0714, (0x00080001).to_bytes(4, "little"))]),
    ],
    ("net", 0x010119ac): [
        ({0: emu.SCRATCH + 0x0200, 1: active},
         [(emu.SCRATCH + 0x0200, bytes(0x120)),
          (emu.SCRATCH + 0x0202, kind.to_bytes(2, "little")),
          (0x21000f20, (emu.SCRATCH + 0x0800).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0800, bytes(0x100))])
        for active in (0, 1)
        for kind in (0x10, 0x12, 0x13, 0x15, 0x1d)
    ] + [
        ({0: emu.SCRATCH + 0x0200, 1: 0},
         [(emu.SCRATCH + 0x0200, bytes(0x120)),
          (emu.SCRATCH + 0x0202, (0x11).to_bytes(2, "little")),
          (0x21000f20, (emu.SCRATCH + 0x0800).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0800, bytes(0x100))])
    ],
    # Transition engine: its object contains intrusive lists and callback
    # tables. Random RAM creates cyclic lists and non-Thumb callbacks, neither
    # of which is a valid production state. Exercise each public request while
    # the engine is already dispatching; this is the concurrency/defer path
    # selected before any list dereference.
    ("app", 0x0004b4fc): [
        ({0: emu.SCRATCH + 0x1000, 1: request, 2: 0x20, 3: 0x12345678},
         [(emu.SCRATCH + 0x1000, bytes(0x24)),
          (emu.SCRATCH + 0x1000 + 0x1c, (0x0008).to_bytes(2, "little"))])
        for request in (1, 2, 3)
    ],
    # Atomic notifier: cover both the absent-listener return and the indirect
    # callback tail through the two-level global callback slot.
    ("app", 0x0004e964): [
        ({}, [(0x2000a2b0, (0).to_bytes(4, "little"))]),
        ({}, [(0x2000a2b0, (emu.SCRATCH + 0x0600).to_bytes(4, "little")),
              (emu.SCRATCH + 0x0600, (0x00080001).to_bytes(4, "little")),
              (0x2000a158, (0x12345678).to_bytes(4, "little"))]),
    ],
    # Text-cursor trim: bound the owned length/position fields and cover null,
    # null-data, early non-space, and all-space end/decrement paths.
    ("app", 0x00084ed8): [
        ({0: 0}, []),
        ({0: emu.SCRATCH + 0x0a00},
         [(emu.SCRATCH + 0x0a00, (0).to_bytes(4, "little"))]),
        ({0: emu.SCRATCH + 0x0a00},
         [(emu.SCRATCH + 0x0a00, (emu.SCRATCH + 0x0b00).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0a04, (2).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0a08, (0).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0b00, b" A")]),
        ({0: emu.SCRATCH + 0x0a00},
         [(emu.SCRATCH + 0x0a00, (emu.SCRATCH + 0x0b00).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0a04, (2).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0a08, (0).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0b00, b"  ")]),
    ],
    # Formatter worker: argument five is an argv cursor passed on the entry
    # stack (loaded from post-push sp+0x30).  Random stack RAM manufactures an
    # invalid cursor and makes original/candidate compiler stack layouts read
    # different values.  Pin the full ABI state while varying representative
    # conversions through the shared formatter/callback tail.
    ("app", 0x00077594): [
        ({0: 0x1234, 1: emu.SCRATCH + 0x0200, 2: 0x5678,
          3: 0x00080001},
         [(emu.STACK_TOP, (emu.SCRATCH + 0x0300).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0200, bytes(0x50)),
          (emu.SCRATCH + 0x0200 + 0x18, bytes((conversion,))),
          (emu.SCRATCH + 0x0300, (emu.SCRATCH + 0x0400).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0400, (emu.SCRATCH + 0x0500).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0500, b"format-string\0")])
        for conversion in (0, ord('c'), ord('d'), ord('s'), ord('x'))
    ],
    # printf_like: random pointers do not reach the parser.  Supply a valid
    # callback, format string, and va-list cursor so every conversion family,
    # flag parser, dynamic/static width and precision, and length modifier is
    # exercised.  The argv area includes scalar, 64-bit, pointer, string, and
    # %n destinations; unused words are harmless for shorter formats.
    ("app", 0x000113a8): [
        ({0: 0x00080001, 1: 0x13579bdf, 2: emu.SCRATCH + 0x0200,
          3: emu.SCRATCH + 0x0300},
         [(emu.SCRATCH + 0x0200, fmt),
          (emu.SCRATCH + 0x0300, argv + bytes(0x40 - len(argv))),
          (emu.SCRATCH + 0x0400, b"formatter-string\0"),
          (emu.SCRATCH + 0x0500, bytes(0x20))])
        for fmt, argv in (
            (b"plain text\0", bytes(4)), (b"%%\0", bytes(4)),
            (b"%+ #0-12.5d\0", (12345).to_bytes(4, "little")),
            (b"%*.*u\0", (9).to_bytes(4, "little") +
                          (4).to_bytes(4, "little") +
                          (12345).to_bytes(4, "little")),
            (b"%hhd\0", (0x7f).to_bytes(4, "little")),
            (b"%hd\0", (0x1234).to_bytes(4, "little")),
            (b"%ld\0", (123456).to_bytes(4, "little")),
            (b"%lld\0", (0x89abcdef).to_bytes(4, "little") +
                         (0x01234567).to_bytes(4, "little")),
            (b"%c\0", (ord('Z')).to_bytes(4, "little")),
            (b"%s %.0s\0", (emu.SCRATCH + 0x0400).to_bytes(4, "little") * 2),
            (b"%o %x %X %p\0", (0x1234).to_bytes(4, "little") * 3 +
                                (emu.SCRATCH + 0x0400).to_bytes(4, "little")),
            # Four independently valid finite doubles (1.0), naturally
            # 8-byte aligned at the va-list base.
            (b"%.0f\0", bytes.fromhex("000000000000f03f")),
            (b"%e\0", bytes.fromhex("000000000000f03f")),
            (b"%E\0", bytes.fromhex("000000000000f03f")),
            (b"%.0g\0", bytes.fromhex("000000000000f03f")),
            (b"%.0G\0", bytes.fromhex("000000000000f03f")),
            (b"%n %hn %hhn %ln\0", (emu.SCRATCH + 0x0500).to_bytes(4, "little") * 4),
            (b"%q trailing\0", bytes(4)),
        )
    ],
    # Big-integer left shift: constrain the operand header to valid compact
    # objects. Random 32-bit `used` fields manufacture multi-billion iteration
    # loops that no production object can contain. Exercise empty through
    # three-limb shapes, both exact and spare allocation capacity, and all
    # important shift/limb boundaries.
    ("app", 0x000789f0): [
        ({1: emu.SCRATCH + 0x0300, 2: bits},
         [(emu.SCRATCH + 0x0304, (0).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0308, capacity.to_bytes(4, "little")),
          (emu.SCRATCH + 0x0310, used.to_bytes(4, "little")),
          (emu.SCRATCH + 0x0314, (0x89abcdef).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0318, (0x01234567).to_bytes(4, "little")),
          (emu.SCRATCH + 0x031c, (0xfedcba98).to_bytes(4, "little"))])
        for used in (0, 1, 2, 3)
        for bits in (0, 1, 31, 32, 33, 63, 64, 65)
        for capacity in (used + (bits >> 5) + 1,
                         used + (bits >> 5) + 4)
    ],
    # Quaternion-to-Euler conversion: use finite, normalized representative
    # inputs rather than arbitrary RAM bit patterns dominated by NaNs.  Values
    # are q0..q3 at offsets 0x0c..0x18.
    ("app", 0x0007cab4): [
        ({0: emu.SCRATCH + 0x2000},
         [(emu.SCRATCH + 0x200c, q0.to_bytes(4, "little")),
          (emu.SCRATCH + 0x2010, q1.to_bytes(4, "little")),
          (emu.SCRATCH + 0x2014, q2.to_bytes(4, "little")),
          (emu.SCRATCH + 0x2018, q3.to_bytes(4, "little"))])
        for q0,q1,q2,q3 in (
            (0x3f800000,0,0,0),
            (0x3f3504f3,0x3f3504f3,0,0),
            (0x3f000000,0x3f000000,0x3f000000,0x3f000000))
    ],
    ("app", 0x00077914): [
        ({0: emu.SCRATCH + 0x2400, 1: length, 2: 0, 3: 0},
         [(emu.SCRATCH + 0x2400, b"A\0")])
        for length in (0xffffffff, 1)
    ],
    ("app", 0x0007d120): [
        ({0: emu.SCRATCH + 0x2800},
         [(emu.SCRATCH + 0x2804, (emu.SCRATCH + 0x2820).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2808, (emu.SCRATCH + 0x2830).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2820, (0x00080011).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2830, (0x00080001).to_bytes(4, "little"))]),
    ],
    # Seven-argument record validator: arguments 5..7 are passed on the
    # initial stack. Pin their counts/flags to valid small cases while keeping
    # both record-array pointers in deterministic scratch memory.
    ("app", 0x000811ce): [
        ({2: 0, 3: emu.SCRATCH + 0x0300},
         [(emu.STACK_TOP + 0, (0).to_bytes(4, "little")),
          (emu.STACK_TOP + 4, (0).to_bytes(4, "little")),
          (emu.STACK_TOP + 8, (0).to_bytes(4, "little"))]),
        ({2: 1, 3: emu.SCRATCH + 0x0300},
         [(emu.STACK_TOP + 0, (1).to_bytes(4, "little")),
          (emu.STACK_TOP + 4, (1).to_bytes(4, "little")),
          (emu.STACK_TOP + 8, (1).to_bytes(4, "little"))]),
        ({2: 2, 3: emu.SCRATCH + 0x0300},
         [(emu.STACK_TOP + 0, (2).to_bytes(4, "little")),
          (emu.STACK_TOP + 4, (1).to_bytes(4, "little")),
          (emu.STACK_TOP + 8, (2).to_bytes(4, "little"))]),
    ],
    # Terminated one-node list cases for this callback walker. Random RAM can
    # form cycles or full-width entry counts, neither a valid owned list.
    ("app", 0x00086b40): [
        ({0: emu.SCRATCH + 0x0800, 1: 0x00080001},
         [(emu.SCRATCH + 0x0848, (0).to_bytes(4, "little")),
          (emu.SCRATCH + 0x084c, (0).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0850, (emu.SCRATCH + 0x0900).to_bytes(4, "little"))]),
        ({0: emu.SCRATCH + 0x0800, 1: 0x00080001},
         [(emu.SCRATCH + 0x0848, (0).to_bytes(4, "little")),
          (emu.SCRATCH + 0x084c, (1).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0850, (emu.SCRATCH + 0x0900).to_bytes(4, "little")),
          (emu.SCRATCH + 0x090c, (2).to_bytes(2, "little")),
          (emu.SCRATCH + 0x090e, (0).to_bytes(2, "little"))]),
    ],
    ("net", 0x0103038c): [
        ({0: 0}, [(0x21004810, (0).to_bytes(4, "little"))]),
        ({0: 1}, [(0x21004810, (1).to_bytes(4, "little")),
                  (0x4100541c, (2).to_bytes(4, "little"))]),
        ({0: 1}, [(0x21004810, (1).to_bytes(4, "little")),
                  (0x4100541c, (0).to_bytes(4, "little")),
                  (0x41005418, (0x00010002).to_bytes(4, "little"))]),
        ({0: 2}, [(0x21004810, (1).to_bytes(4, "little")),
                  (0x41005418, (0x00010002).to_bytes(4, "little"))]),
        ({0: 3}, [(0x21004810, (1).to_bytes(4, "little"))]),
    ],
    # Queue-drain routine.  Its production outer loop terminates only after
    # the owned queue at context+0x28 becomes empty; unconstrained randomized
    # RAM makes that list cyclic.  Anchor the context pointer and empty queue
    # explicitly.  The second argument still receives ordinary pointer fuzz.
    ("app", 0x00058f80): [
        ({0: emu.SCRATCH + 0x1800},
         [(emu.SCRATCH + 0x1800, (0x20030000).to_bytes(4, "little")),
          (0x20030028, (0).to_bytes(4, "little"))]),
    ],
}

# libLC3 SNS analysis: seven-argument hard-float ABI.  The final three pointers
# are stack-passed.  Map the separately-owned LC3 constant tables and exercise
# every duration/rate/attack combination with finite non-silent spectra.
_sns_tables = [(a, ax.read(a, n)) for a, n in (
    (0x0008c94c, 1280), (0x0008ce4c, 1024),
    (0x00090128, 704), (0x000903e8, 104),
    (0x00090450, 1024), (0x00090850, 1024), (0x00090c50, 2600))]
REVIEWED_STATE_CASES[("app", 0x0006c778)] = [
    ({0: dt, 1: sr, 2: emu.SCRATCH + 0x1000, 3: att},
     _sns_tables + [
         (emu.STACK_TOP + 0, (emu.SCRATCH + 0x2000).to_bytes(4, "little")),
         (emu.STACK_TOP + 4, (emu.SCRATCH + 0x3000).to_bytes(4, "little")),
         (emu.STACK_TOP + 8, (emu.SCRATCH + 0x4000).to_bytes(4, "little")),
         (emu.SCRATCH + 0x1000, struct.pack("<64f", *[
             0.01 + (i + 1) * (sr + 1) * 0.003 for i in range(64)])),
         (emu.SCRATCH + 0x2000, bytes(64)),
         (emu.SCRATCH + 0x3000, struct.pack("<480f", *[
             math.sin(i * 0.11) + 0.01 * i for i in range(480)])),
         (emu.SCRATCH + 0x4000, bytes(1920))])
    for dt in (0, 1) for sr in range(5) for att in (0, 1)
]

# Query-return cases for a packetizer whose loop bound is returned by its
# second callee. These cover allocation failure, empty data, exact and partial
# chunks without treating an arbitrary 32-bit oracle value as a buffer length.
ORACLE_STATE_CASES = {
    ("app", 0x00019c44): [
        {0: {0: 0}},  # receive succeeds and copies 200 bytes
        {0: {0: 1}},  # receive fails and returns without copying
    ],
    ("app", 0x00035498): [
        {0: {0: 0}},
        {0: {0: emu.SCRATCH + 0x1000}, 1: {0: 0}},
        {0: {0: emu.SCRATCH + 0x1000}, 1: {0: 1}},
        {0: {0: emu.SCRATCH + 0x1000}, 1: {0: 17}},
        {0: {0: emu.SCRATCH + 0x1000}, 1: {0: 18}},
    ],
}

# Combined argument/state/oracle cases for parsers whose termination is owned
# by callee return values.  Keeping these three inputs together avoids turning
# arbitrary fuzz-oracle values into an unbounded synthetic input stream.
def _even_ai_case(active, phase, status, substate=0, level=0, sink=0,
                  frame=0, saved=0xffffffff):
    app = emu.SCRATCH + 0x1000
    ctx = emu.SCRATCH + 0x4000
    state = bytearray(0x1000)
    state[0xef] = status
    state[0xf0] = substate
    state[0xf3] = 2
    state[0xf4] = 1
    state[0xf5] = 3
    state[0x286:0x288] = (0).to_bytes(2, "little")
    return (
        {0: ctx, 1: 0, 2: phase},
        [(app, bytes(state)), (ctx, bytes(0x1000)),
         (0x2000230c, level.to_bytes(4, "little", signed=True)),
         (0x20007554, sink.to_bytes(4, "little")),
         (0x20009fd8, frame.to_bytes(4, "little")),
         (0x20009fd4, (0).to_bytes(4, "little")),
         (0x200024ec, saved.to_bytes(4, "little")),
         (0x20007b3c, bytes(0x40)),
         (0x2000a038, bytes(0x20)),
         (0x2001b818, bytes(0x200)),
         # The active bytes live inside the line-buffer allocation above and
         # therefore must be applied after its deterministic zero fixture.
         (0x2001b9a8, bytes((active, 0)))],
        {0: {0: app}, 1: {0: 1}},
    )


_AC98_GLOBAL = 0x21000c48
_AC98_STATE = emu.SCRATCH + 0x1000
_AC98_PACKET = _AC98_GLOBAL + 0x48

def _ac98_reviewed_case(mode):
    """One stable radio-buffer state for each global switch arm.

    Modes 0-3 all reach the common packet-finalization tail.  Mode 4 selects
    the default assertion.  Packet byte 2 deliberately differs from byte 1 so
    the final copy to 0x21000cfe detects the recovered +2 byte access.
    """
    global_state = bytearray(0xb8)
    global_state[0x28:0x2c] = _AC98_STATE.to_bytes(4, "little")
    global_state[0x48:0x4c] = bytes((3, 1, 0x5a, 2))
    global_state[0x7a] = 0xff
    global_state[0x7b] = 3
    global_state[0x7c:0x80] = _AC98_PACKET.to_bytes(4, "little")
    global_state[0x80:0x84] = (emu.SCRATCH + 0x4000).to_bytes(4, "little")

    controller = bytearray(0x130)
    controller[0x6e] = controller[0x6f] = 0x22
    controller[0xbe] = mode
    # ca=0 selects the ordinary finalize calls; cb=0 keeps the initial
    # channel comparison on its no-log path; 105=0 permits mode-0 allocation.
    controller[0xca] = 0
    controller[0xcb] = 0
    controller[0x105] = 0

    if mode == 0:
        # pool busy=0, then allocator returns the reviewed packet buffer
        oracles = {0: {0: 0}, 1: {0: _AC98_PACKET}}
    elif mode == 2:
        oracles = {0: {0: _AC98_PACKET}}
    elif mode == 3:
        oracles = {0: {0: 1}}
    else:
        oracles = {}
    return ({0: 0},
            [(_AC98_GLOBAL, bytes(global_state)),
             (_AC98_STATE, bytes(controller)),
             (emu.SCRATCH + 0x4000, bytes(0x100))],
            oracles)


def _mpsc_alloc_case(kind):
    """Bounded production-shaped allocator paths for the MPSC buffer."""
    obj = emu.SCRATCH + 0x0800
    backing = emu.SCRATCH + 0x1000
    state = bytearray(0x80)
    state[0x0c:0x10] = (8).to_bytes(4, "little")
    state[0x20:0x24] = backing.to_bytes(4, "little")
    state[0x24:0x28] = (16).to_bytes(4, "little")
    memory = [(obj, bytes(state)), (backing, bytes(0x100))]
    if kind == "reject":
        return ({0: obj, 1: 17, 2: 0, 3: 0}, memory, {})
    if kind == "allocate":
        return ({0: obj, 1: 4, 2: 0, 3: 0}, memory,
                {0: {0: 1}, 2: {0: 0}, 3: {0: 1}, 4: {0: 1}},
                {2: [(1, 0, (16).to_bytes(4, "little"), 0x0007e314)]})
    if kind == "wrap":
        return ({0: obj, 1: 4, 2: 0, 3: 0}, memory,
                {0: {0: 1}, 2: {0: 1}, 4: {0: 1},
                 5: {0: 1}, 7: {0: 0}, 8: {0: 1}, 9: {0: 1}},
                {2: [(1, 0, (2).to_bytes(4, "little"), 0x0007e314)],
                 7: [(1, 0, (16).to_bytes(4, "little"), 0x0007e314)]})
    if kind == "timeout":
        # Wait once, reacquire the lock, then observe newly available space.
        return ({0: obj, 1: 4, 2: 1, 3: 0}, memory,
                {0: {0: 1}, 2: {0: 0}, 3: {0: 0}, 4: {0: 1},
                 5: {0: 0}, 6: {0: 1}, 8: {0: 1}, 9: {0: 1},
                 11: {0: 0}, 12: {0: 1}, 13: {0: 1}},
                {2: [(1, 0, (2).to_bytes(4, "little"), 0x0007e314)],
                 11: [(1, 0, (16).to_bytes(4, "little"), 0x0007e314)]})
    if kind == "timeout-error":
        # A failed wait terminates after reacquiring/releasing the lock; it
        # must not be treated as newly available space.
        return ({0: obj, 1: 4, 2: 1, 3: 0}, memory,
                {0: {0: 1}, 2: {0: 0}, 3: {0: 0}, 4: {0: 1},
                 5: {0: 7}, 6: {0: 1}, 8: {0: 1}},
                {2: [(1, 0, (2).to_bytes(4, "little"), 0x0007e314)]})
    if kind == "mode-drop":
        # In restricted execution mode a nonzero timeout must bypass waiting
        # and use the drop selector instead.
        return ({0: obj, 1: 4, 2: 1, 3: 0}, memory,
                {0: {0: 1}, 2: {0: 0}, 3: {0: 1},
                 4: {0: 0}, 5: {0: 1}},
                {2: [(1, 0, (2).to_bytes(4, "little"), 0x0007e314)]})
    if kind == "drop-publish":
        state[0x18:0x1c] = (0x00080001).to_bytes(4, "little")
        memory[0] = (obj, bytes(state))
        return ({0: obj, 1: 4, 2: 0, 3: 0}, memory,
                {0: {0: 1}, 2: {0: 0}, 3: {0: 1}, 4: {0: 1},
                 6: {0: 1}, 9: {0: 0}, 10: {0: 1}, 11: {0: 1}},
                {2: [(1, 0, (2).to_bytes(4, "little"), 0x0007e314)],
                 3: [(2, 0, (emu.SCRATCH + 0x3000).to_bytes(4, "little"), 0x0007e3ce),
                     (3, 0, (2).to_bytes(4, "little"), 0x0007e3ce)],
                 9: [(1, 0, (16).to_bytes(4, "little"), 0x0007e314)]})
    # No contiguous space and no wrap: the drop selector terminates cleanly.
    return ({0: obj, 1: 4, 2: 0, 3: 0}, memory,
            {0: {0: 1}, 2: {0: 0}, 3: {0: 0}, 4: {0: 1}},
            {2: [(1, 0, (2).to_bytes(4, "little"), 0x0007e314)]})


def _net_queue_remove_case(result, removed_index):
    request = emu.SCRATCH + 0x1000
    backing = emu.SCRATCH + 0x2000
    queue = bytearray(8)
    queue[0] = 4
    queue[4:8] = backing.to_bytes(4, "little")
    writes = ({0: [(2, 0, bytes((removed_index,)), 0x010106dc)]}
              if result else {})
    return ({0: 1, 1: request},
            [(request, b"\x78\x56\x34\x12\x34\x12\x00\x00"),
             (0x21000f14, bytes(queue)), (backing, bytes(range(32)))],
            {0: {0: result}}, writes)


def _net_list_insert_case(kind):
    owner = emu.SCRATCH + 0x1000
    node = emu.SCRATCH + 0x2000
    state = bytearray(0x30)
    state[8:12] = (0x8000 if kind == "early" else 0).to_bytes(4, "little")
    if kind == "occupied":
        state[0x10:0x14] = (emu.SCRATCH + 0x3000).to_bytes(4, "little")
    oracles = {0: {0: 1 if kind == "early" else 0}}
    if kind != "early":
        oracles[1] = {0: 0}
    if kind == "occupied":
        oracles[2] = {0: emu.SCRATCH + 0x3100}
    return ({0: owner, 1: node}, [(owner, bytes(state))], oracles)


def _net_init_case(kind):
    config = emu.SCRATCH + 0x1000
    controller = emu.SCRATCH + 0x3000
    existing = emu.SCRATCH + 0x4000
    found = emu.SCRATCH + 0x5000
    config_image = bytearray(0x100)
    globals_image = bytearray(0x60)
    controller_image = bytearray(16)
    # The fourth descriptor word is loaded from controller+4.  Keep the
    # adjacent controller+8 word mapped but distinct so the exact descriptor
    # object passed to FUN_01020738 detects a wrong field offset.
    controller_image[4:8] = (0x13579bdf).to_bytes(4, "little")
    controller_image[8:12] = (0x2468ace0).to_bytes(4, "little")
    globals_image[0x28:0x2c] = controller.to_bytes(4, "little")
    memory = [(config, bytes(config_image)),
              (0x21000f20, bytes(globals_image)),
              (controller, bytes(controller_image)), (existing, bytes(32)),
              (found, b"\x00\x00\x5a" + b"ABCD" + b"EF" + b"\x07" +
               bytes(22))]
    if kind == "early":
        return ({0: config}, memory, {12: {0: 0}})
    oracles = {12: {0: 1}, 13: {0: 0}, 14: {0: 0}}
    writes = {}
    if kind == "baseline":
        pass
    elif kind == "timestamp":
        config_image[0x1a] = 1
        config_image[0x20] = 1
        config_image[2:4] = (0x10).to_bytes(2, "little")
        config_image[0x58:0x5c] = (0xffffffff).to_bytes(4, "little")
        config_image[0x5c:0x60] = (0x7fffffff).to_bytes(4, "little")
        memory[0] = (config, bytes(config_image))
        oracles.update({13: {0: 1}, 15: {0: 2},
                        16: {0: 5, 1: 0}, 17: {0: 0}, 18: {0: 0}})
    elif kind == "random":
        config_image[0x20] = 1
        config_image[0x3c:0x40] = (0x100).to_bytes(4, "little")
        memory[0] = (config, bytes(config_image))
        oracles.update({13: {0: 1}, 15: {0: 2}, 16: {0: 0}})
    else:
        config_image[2:4] = (1).to_bytes(2, "little")
        config_image[0x1c:0x20] = existing.to_bytes(4, "little")
        memory[0] = (config, bytes(config_image))
        oracles[15] = {0: 0}
        if kind == "iterator-retry":
            oracles.update({16: {0: 0}, 17: {0: 0}, 18: {0: 1}})
            writes = {
                16: [(0, 0, existing.to_bytes(4, "little"), 0x01009dd8)],
                17: [(0, 0, found.to_bytes(4, "little"), 0x01009dd8)],
            }
        else:
            oracles.update({16: {0: 0}, 17: {0: 1}})
            writes = {
                16: [(0, 0, found.to_bytes(4, "little"), 0x01009dd8)],
            }
    return ({0: config}, memory, oracles, writes)


def _net_printf_case(fmt, words=(), string_data=None, first_return=0):
    context = emu.SCRATCH + 0x1000
    format_address = emu.SCRATCH + 0x1100
    arguments = emu.SCRATCH + 0x1200
    context_data = bytearray(8)
    context_data[2] = 2
    context_data[4:8] = (0x00080001).to_bytes(4, "little")
    argv = bytearray(32)
    for index, value in enumerate(words):
        argv[index * 4:index * 4 + 4] = value.to_bytes(4, "little")
    memory = [(context, bytes(context_data)),
              (format_address, fmt + b"\x00"), (arguments, bytes(argv))]
    if string_data is not None:
        memory.append((emu.SCRATCH + 0x1300, string_data + b"\x00"))
    oracles = {ordinal: {0: 0} for ordinal in range(64)}
    oracles[0] = {0: first_return}
    return ({0: context, 1: format_address, 2: arguments}, memory, oracles)


def _net_packet_case(kind, alternate=False, fallback=False):
    packet = emu.SCRATCH + 0x1000
    radio = emu.SCRATCH + 0x2000
    alternate_address = emu.SCRATCH + 0x3000
    state = bytearray(0xc4)
    state[0x50:0x54] = radio.to_bytes(4, "little")
    state[0xc0:0xc4] = packet.to_bytes(4, "little")
    radio_data = bytearray(0x200)
    # Distinguish every byte participating in the packed source load and the
    # five-bit packet field.  Zero-filled radio state allowed +0xce/+0xcf and
    # masks 0x1f/0x0f to collapse to the same trace.
    radio_data[0xce:0xd3] = b"\x11\x22\x33\x44\x55"
    radio_data[0xd9] = 0x1b
    if alternate:
        state[0x4d] = 1
        state[0x54] = 3
        state[0x7b] = 7
        state[0x7d] = 1
    elif fallback:
        state[0x78] = 2
        state[0x7b] = 7
        state[0x7d] = 1
    memory = [(0x21000f90, bytes(state[:0x70])),
              (0x21001000, bytes(state[0x70:])), (packet, bytes(64)),
              (radio, bytes(radio_data)),
              (alternate_address, bytes(range(8)))]
    oracle_ordinal = 2 if kind not in (3, 5) else (3 if kind == 3 else 7)
    oracles = ({oracle_ordinal: {0: alternate_address}}
               if (alternate or fallback) else {})
    return ({0: kind, 2: 0x11223344, 3: 0x55667788}, memory, oracles)


def _net_record_case(kind):
    packet = emu.SCRATCH + 0x1000
    header = emu.SCRATCH + 0x3000
    payload = emu.SCRATCH + 0x4000
    alternate = emu.SCRATCH + 0x5000
    state = bytearray(0x100)
    state[0x45] = 1
    state[0x78] = 2
    state[0x7b] = 7
    state[0x90] = 1
    record = bytearray(19)
    record[0] = 0
    record[1] = 3
    record[4:8] = payload.to_bytes(4, "little")
    record[8:12] = header.to_bytes(4, "little")
    record[17] = 1
    if kind == "simple":
        return ({0: packet}, [(packet, b"\x00")], {0: {0: 0x22}})
    oracles = {0: {0: 0x22}}
    header_image = bytearray(32)
    if kind == "reject":
        oracles[2] = {0: 0}
    elif kind == "cleanup":
        oracles.update({2: {0: 1}, 3: {0: 1}})
    elif kind == "cleanup-reset":
        state[0x7c] = 1
        oracles.update({2: {0: 0xff}, 3: {0: 1}, 4: {0: 1}})
    elif kind == "cb-equal":
        state[0x7c] = 1
        oracles.update({2: {0: 2}, 3: {0: 0}, 4: {0: 0}})
    elif kind == "cb-ff":
        state[0x7c] = 1
        oracles.update({2: {0: 0xff}, 3: {0: 0}})
    elif kind == "radio":
        state[0x7d] = 1
        state[0x54] = 3
        state[0x4d] = 1
        oracles.update({2: {0: 1}, 3: {0: alternate}, 4: {0: 0}})
    else:
        record[18] = 1
        if kind != "special-header-false":
            header_image[5] = 0x40
        oracles[2] = {0: 1}
        if kind == "special-header-false":
            oracles[3] = {0: 0}
        else:
            oracles[3] = {0: 0}
            if kind == "special-ca-zero":
                oracles[4] = {0: 0}
            elif kind == "special-ff":
                state[0x78] = 0xff
            else:
                oracles[4] = {0: emu.SCRATCH + 0x6000}
                oracles[5] = {0: 1 if kind == "special-aaac-fail" else 0}
    return ({0: packet},
            [(packet, b"\x08"), (0x21000f90, bytes(state[:0x70])),
             (0x21001000, bytes(state[0x70:])),
             (header, bytes(header_image)), (payload, bytes(32)),
             (alternate, bytes(8)), (emu.SCRATCH + 0x6000, bytes(32))],
            oracles,
            {1: [(1, 0, bytes(record), 0x01019f9c)]})


def _net_scheduler_case(kind):
    work = emu.SCRATCH + 0x1000
    runtime = emu.SCRATCH + 0x3000
    globals_memory = [(0x21004b28 + 8, runtime.to_bytes(4, "little")),
                      (runtime + 0x60, bytes(2))]
    if kind == "irq":
        return ({0: work, 1: 1, 2: 1, 3: 0}, globals_memory, {})
    if kind == "null":
        return ({0: 0, 1: 1, 2: 1, 3: 0}, globals_memory, {})
    if kind == "priority":
        return ({0: work, 1: 0xffffffff, 2: 1, 3: 0}, globals_memory, {})
    if kind == "completed":
        return ({0: work, 1: 1, 2: 1, 3: 0}, globals_memory,
                {0: {0: 0x1234}, 1: {0: 1}, 4: {0: 1}},
                {0: [(2, 0, b"\x00", 0x010384a8)]})
    if kind == "lock-fail":
        return ({0: work, 1: 1, 2: 1, 3: 0}, globals_memory,
                {0: {0: 0x1234}, 1: {0: 0}})
    if kind == "completed-release-fail":
        return ({0: work, 1: 1, 2: 1, 3: 0}, globals_memory,
                {0: {0: 0x1234}, 1: {0: 1}, 4: {0: 0}},
                {0: [(2, 0, b"\x00", 0x010384a8)]})
    if kind == "immediate":
        return ({0: work, 1: 1, 2: 0, 3: 0}, globals_memory,
                {0: {0: 0x1234}, 1: {0: 1}, 3: {0: 1}})
    if kind == "immediate-release-fail":
        return ({0: work, 1: 1, 2: 0, 3: 0}, globals_memory,
                {0: {0: 0x1234}, 1: {0: 1}, 3: {0: 0}})
    if kind == "wait-relock-fail":
        return ({0: work, 1: 1, 2: 1, 3: 2}, globals_memory,
                {0: {0: 0x1234}, 1: {0: 1}, 3: {0: 7},
                 4: {0: 0}})
    if kind == "wait-release-fail":
        return ({0: work, 1: 1, 2: 1, 3: 2}, globals_memory,
                {0: {0: 0x1234}, 1: {0: 1}, 3: {0: 7},
                 4: {0: 1}, 7: {0: 0}})
    if kind == "high-only":
        return ({0: work, 1: 1, 2: 0, 3: 2}, globals_memory,
                {0: {0: 0x1234}, 1: {0: 1}, 3: {0: 7},
                 4: {0: 1}, 7: {0: 1}})
    return ({0: work, 1: 1, 2: 1, 3: 0}, globals_memory,
            {0: {0: 0x1234}, 1: {0: 1}, 3: {0: 7},
             4: {0: 1}, 7: {0: 1}})


def _net_radio_init_case(timestamp=False, descriptor=False, error=False,
                         threshold=False, callback=False, final_time=7,
                         alternate_mode=False):
    output = emu.SCRATCH + 0x1000
    config = emu.SCRATCH + 0x5000
    output_data = bytearray(0x400)
    config_data = bytearray(0x100)
    config_data[0x24:0x26] = (10).to_bytes(2, "little")
    config_data[0x2a:0x2c] = (20).to_bytes(2, "little")
    config_data[0x30:0x32] = (30).to_bytes(2, "little")
    config_data[0x36:0x38] = (40).to_bytes(2, "little")
    table2 = bytearray(16)
    table2[2:4] = (2).to_bytes(2, "little")
    table2[4:6] = (3).to_bytes(2, "little")
    table2[8:12] = (0x1234).to_bytes(4, "little")
    table3 = bytearray(0x30)
    table3[4] = 1
    if callback:
        table3[0x24:0x28] = (0x00080001).to_bytes(4, "little")
    # The first status word selects the table/default mode family; the second
    # call's high r1 bits select the local descriptor path.
    oracles = {1: {0: 0x20 if alternate_mode else 0, 1: 0}}
    ordinal = 2
    oracles[ordinal] = {0: 0, 1: 2 if descriptor else 0}
    ordinal += 1
    if descriptor:
        # FUN_0101e274 consumes the complete local descriptor.
        oracles[ordinal] = {0: 0}
        ordinal += 1
    oracles[ordinal] = {0: 1 if error else 0}  # FUN_01009f58
    ordinal += 1
    if error:
        return ({0: output, 1: 9, 2: config, 3: int(timestamp)},
                [(output, bytes(output_data)), (config, bytes(config_data)),
                 (0x0103ec0a, b"\x11\x22\x33\x44\x55"),
                 (0x21000eac, bytes(table2)),
                 (0x21001208, bytes(table3))], oracles)
    oracles[ordinal] = {0: 0x55}  # FUN_01028256
    ordinal += 1
    if timestamp:
        oracles[ordinal] = {0: 0x123456}
        ordinal += 1
    oracles[ordinal] = {0: 100}
    ordinal += 1
    oracles[ordinal] = {0: 8000 if threshold else 1000}
    ordinal += 1
    if threshold:
        oracles[ordinal] = {0: 0x2345}
        ordinal += 1
    oracles[ordinal] = {0: 0}  # FUN_0101bbc0
    ordinal += 1
    if callback:
        oracles[ordinal] = {0: 0}
        ordinal += 1
    oracles[ordinal] = {0: 0x66}  # FUN_0101e660
    ordinal += 1
    oracles[ordinal] = {0: final_time}  # final FUN_0100f66c
    return ({0: output, 1: 9, 2: config, 3: int(timestamp)},
            [(output, bytes(output_data)), (config, bytes(config_data)),
             (0x0103ec0a, b"\x11\x22\x33\x44\x55"),
             (0x21000eac, bytes(table2)), (0x21001208, bytes(table3))],
            oracles)


def _net_controller_reset_case():
    controller = emu.SCRATCH + 0x4000
    return ({}, [(controller, bytes(0x40)), (0x21001098, bytes(6))],
            {0: {0: 7}, 2: {0: controller}})


def _net_controller_log_case(controller_mask=0, radio_mask=0):
    owner = emu.SCRATCH + 0x1000
    outer = emu.SCRATCH + 0x2000
    limits = emu.SCRATCH + 0x3000
    state = bytearray(0x20)
    state[4:8] = limits.to_bytes(4, "little")
    state[0x10:0x14] = outer.to_bytes(4, "little")
    limits_data = (int(controller_mask).to_bytes(4, "little") +
                   int(radio_mask).to_bytes(4, "little"))
    return ({0: owner}, [(owner, bytes(state)), (outer, bytes(0x100)),
                         (limits, limits_data)], {},
            {2: [(0, 0, bytes(132), 0x0103b62e)]})


def _net_packet_drain_case(kind):
    """Inactive, empty, callback, retry, and fatal controller queue states."""
    owner = emu.SCRATCH + 0x1000
    root = emu.SCRATCH + 0x1800
    controller = emu.SCRATCH + 0x2000
    state = emu.SCRATCH + 0x3000
    owner_data = root.to_bytes(4, "little")
    root_data = bytearray(0x40)
    root_data[0x24:0x28] = controller.to_bytes(4, "little")
    controller_data = bytearray(0xb0)
    controller_data[0xa0:0xa4] = state.to_bytes(4, "little")
    controller_data[0xa4:0xa8] = (0x13579bdf).to_bytes(4, "little")
    state_data = bytearray(0x20)
    active = kind != "inactive"
    state_data[0x18:0x1c] = int(active).to_bytes(4, "little")
    oracles = {}
    memory = [(owner, owner_data), (root, bytes(root_data)),
              (controller, bytes(controller_data)), (state, bytes(state_data))]
    if kind == "inactive":
        pass
    elif kind == "empty":
        oracles[1] = {0: 0}
    else:
        packet = emu.SCRATCH + 0x4000
        target = emu.SCRATCH + 0x5000
        packet_data = bytearray(0x30)
        packet_data[0:4] = (0x11223344).to_bytes(4, "little")
        packet_data[4:8] = (0x55667788).to_bytes(4, "little")
        packet_data[12:14] = (0x8001 if kind == "unsigned-halfword" else 7
                              ).to_bytes(2, "little")
        target_data = bytearray(0x40)
        target_data[0x28:0x2c] = (
            0xffffffff if kind == "wrap-state" else 0
        ).to_bytes(4, "little")
        target_data[0x2c:0x30] = (0x00080001).to_bytes(4, "little")
        target_data[0x3c:0x40] = (0x89abcdef).to_bytes(4, "little")
        memory.extend([(packet, bytes(packet_data)), (target, bytes(target_data))])
        callback_result = (0xffffffff if kind == "fatal" else
                           1 if kind == "callback-positive" else 0)
        oracles.update({1: {0: packet}, 4: {0: target},
                        6: {0: callback_result}})
        if kind == "retry":
            packet2 = emu.SCRATCH + 0x6000
            packet2_data = bytearray(packet_data)
            packet2_data[0:4] = (0x99aabbcc).to_bytes(4, "little")
            packet2_data[4:8] = (0x10203040).to_bytes(4, "little")
            memory.append((packet2, bytes(packet2_data)))
            oracles.update({9: {0: packet2}, 12: {0: 0}, 16: {0: 0}})
        elif kind != "fatal":
            oracles[9] = {0: 0}
    return ({0: owner, 1: 7, 2: 0x12340000, 3: 0x2468ace0},
            memory, oracles)


def _net_ready_list_case(kind):
    """Circular Zephyr ready-list with empty and ordered insertion shapes."""
    node = (0x210043a8 if kind == "reserved" else
            emu.SCRATCH + 0x1000)
    existing = emu.SCRATCH + 0x2000
    base = 0x21004b28
    sentinel = base + 0x18
    node_data = bytearray(0x20)
    globals_data = bytearray(0x40)
    if kind in ("empty", "reserved"):
        globals_data[8:12] = node.to_bytes(4, "little")
        globals_data[0x18:0x1c] = sentinel.to_bytes(4, "little")
        globals_data[0x1c:0x20] = sentinel.to_bytes(4, "little")
        memory = [(node, bytes(node_data)), (base, bytes(globals_data))]
    else:
        node_data[0x0e] = {"ordered": 1, "remove-insert": 1,
                           "equal": 5, "append": 9, "multi": 5,
                           "negative": 0xfe}[kind]
        if kind == "remove-insert":
            node_data[0x0d] = 0x80
        existing_data = bytearray(0x20)
        existing_data[0:4] = sentinel.to_bytes(4, "little")
        existing_data[4:8] = sentinel.to_bytes(4, "little")
        existing_data[0x0e] = 1 if kind == "multi" else 5
        globals_data[8:12] = existing.to_bytes(4, "little")
        globals_data[0x18:0x1c] = existing.to_bytes(4, "little")
        globals_data[0x1c:0x20] = existing.to_bytes(4, "little")
        memory = [(node, bytes(node_data)), (existing, bytes(existing_data)),
                  (base, bytes(globals_data))]
        if kind == "multi":
            second = emu.SCRATCH + 0x2800
            second_data = bytearray(0x20)
            existing_data[0:4] = second.to_bytes(4, "little")
            existing_data[4:8] = sentinel.to_bytes(4, "little")
            second_data[0:4] = sentinel.to_bytes(4, "little")
            second_data[4:8] = existing.to_bytes(4, "little")
            second_data[0x0e] = 9
            globals_data[0x1c:0x20] = second.to_bytes(4, "little")
            memory = [(node, bytes(node_data)), (existing, bytes(existing_data)),
                      (second, bytes(second_data)), (base, bytes(globals_data))]
    return ({0: node}, memory, {})


def _net_ready_enqueue_case(kind):
    """Owned work item and success/failure spinlock lifecycle."""
    node = emu.SCRATCH + 0x1000
    base = 0x21004b28
    globals_data = bytearray(0x80)
    current = kind in ("current", "linked")
    globals_data[8:12] = (node if current else emu.SCRATCH + 0x2000).to_bytes(4, "little")
    node_data = bytearray(0x40)
    if kind in ("linked", "linked-other"):
        node_data[0x0d] = 0x81
    if kind == "lock-fail":
        oracles = {1: {0: 0}}
    elif kind == "unlock-fail":
        oracles = {1: {0: 1}, 4: {0: 0}}
    elif kind in ("linked", "linked-other"):
        oracles = {1: {0: 1}, 5: {0: 1}}
    else:
        oracles = {1: {0: 1}, 4: {0: 1}}
    return ({0: node}, [(node, bytes(node_data)), (base, bytes(globals_data))],
            oracles)


def _net_runtime_table_case(duration):
    """Single fixed runtime descriptor with a mapped owning object."""
    owner = emu.SCRATCH + 0x1000
    record = bytearray(0x2c)
    record[0:4] = owner.to_bytes(4, "little")
    for index in range(1, 11):
        record[index * 4:index * 4 + 4] = (0x11000000 + index).to_bytes(4, "little")
    record[0x24:0x28] = int(duration & 0xffffffff).to_bytes(4, "little")
    return ({}, [(owner, bytes(0x100)), (0x0103bfc0, bytes(record))], {})


def _net_format_layout_case(format_bytes, misaligned=False, flags=0):
    """Bounded format layout input and explicit AAPCS fifth argument."""
    output = emu.SCRATCH + 0x1000 + int(misaligned)
    fmt = emu.SCRATCH + 0x3000
    arguments = emu.SCRATCH + 0x4000
    memory = [(emu.SCRATCH + 0x1000, bytes(0x800)),
              (fmt, format_bytes),
              (arguments, (0x12345678).to_bytes(4, "little") + bytes(28)),
              (emu.STACK_TOP, arguments.to_bytes(4, "little"))]
    return ({0: output, 1: 0x400, 2: flags, 3: fmt}, memory, {})


def _net_format_sizing_case(format_bytes, alignment=0, flags=0):
    """NULL-output sizing mode with an exact caller varargs cursor."""
    fmt = emu.SCRATCH + 0x3000
    arguments = emu.SCRATCH + 0x4000
    return (
        {0: 0, 1: alignment & 7, 2: flags, 3: fmt},
        [(fmt, format_bytes),
         (arguments, (0x12345678).to_bytes(4, "little") + bytes(28)),
         (emu.STACK_TOP, arguments.to_bytes(4, "little"))],
        {},
    )


def _net_format_capacity_case(capacity):
    """Initial non-NULL output-capacity boundary (7 rejects, 8 proceeds)."""
    output = emu.SCRATCH + 0x1000
    fmt = emu.SCRATCH + 0x3000
    arguments = emu.SCRATCH + 0x4000
    return (
        {0: output, 1: capacity, 2: 0, 3: fmt},
        [(output, bytes(0x20)), (fmt, b"\0"),
         (arguments, (0x12345678).to_bytes(4, "little") + bytes(28)),
         (emu.STACK_TOP, arguments.to_bytes(4, "little"))],
        {},
    )


def _app_442bc_case(mode, glyph="success", flush=True, buffered=False,
                    hour=12, rendered_text=b"A\0"):
    """One production-shaped time-rendering mode with exact out-objects."""
    decoded = bytearray(12)
    decoded[6:8] = int(hour).to_bytes(2, "little")
    decoded[8:12] = (34).to_bytes(4, "little")
    rendered = rendered_text + bytes(20 - len(rendered_text))
    accessor = emu.SCRATCH + 0x3000
    accessor_image = bytearray(0xf00)
    accessor_image[0xeb4:0xeb8] = (0x11223344).to_bytes(4, "little")
    accessor_image[0xeb8:0xebc] = (0x55667788).to_bytes(4, "little")
    memory = [
        (accessor, bytes(accessor_image)),
        (0x2000a034, (0x2000d000).to_bytes(4, "little")),
        (0x2000230c, (2 if glyph == "failure" else 0).to_bytes(4, "little")),
        (0x20007554, int(buffered).to_bytes(4, "little")),
    ]
    glyph_count = rendered_text.find(b"\0")
    oracles = {2: {0: glyph_count}}
    writes = {
        0: [(1, 0, bytes(decoded), 0x0004a1b8)],
        1: [(0, 0, rendered, 0x00086f00)],
    }
    if mode in (1, 2):
        # First query requests the clear; one glyph is then resolved/drawn or
        # rejected, and the final query independently selects the flush.
        oracles[3] = {0: 2}
        for index in range(glyph_count):
            glyph_ordinal = 5 + 2 * index
            if glyph == "success":
                oracles[glyph_ordinal] = {0: 0}
                writes[glyph_ordinal] = [
                    (2, 0, (10).to_bytes(4, "little"), 0x0004588c),
                    (3, 0, (0x12345678).to_bytes(4, "little"), 0x0004588c),
                    (4, 0, (0x2000abcd).to_bytes(4, "little"), 0x0004588c),
                ]
            else:
                oracles[glyph_ordinal] = {0: 1}
        final_query = 5 + 2 * glyph_count
        oracles[final_query] = {0: 2 if flush else 0}
        if flush:
            oracles[8] = {0: accessor}
            oracles[9] = {0: accessor}
    return ({0: 0x1234, 1: 20, 2: 30, 3: 40}, memory, oracles, writes)


def _app_4967c_success_case(buffered=False, logged=False, length=4,
                            start_time=100, end_time=140):
    """Successful reflash submission with exact packet producer effects."""
    payload = emu.SCRATCH + 0x1800
    payload_bytes = b"ABCDEFGHIJ"[:length]
    level = 3 if logged else 0
    # memset, timestamp, optional logger, tail memset, copy, queue
    time_ordinal = 1
    tail_memset = 3 if logged else 2
    copy_ordinal = tail_memset + 1
    queue_ordinal = copy_ordinal + 1
    success_logger = queue_ordinal + 1 if logged else None
    second_time = queue_ordinal + 2 if logged else queue_ordinal + 1
    writes = {
        0: [(0, 0, bytes(24), 0x00086c78)],
        tail_memset: [(0, 0, bytes(23), 0x00086c78)],
        copy_ordinal: [(0, 0, payload_bytes, 0x00086c04)],
    }
    oracles = {
        time_ordinal: {0: start_time & 0xffffffff,
                       1: (start_time >> 32) & 0xffffffff},
        queue_ordinal: {0: 0},
        second_time: {0: end_time & 0xffffffff,
                      1: (end_time >> 32) & 0xffffffff},
    }
    return (
        {0: payload, 1: length},
        [(payload, payload_bytes),
         (0x2000230c, level.to_bytes(4, "little")),
         (0x20007554, int(buffered).to_bytes(4, "little"))],
        oracles, writes,
    )


def _app_4967c_queue_failure_case():
    payload = emu.SCRATCH + 0x1800
    return (
        {0: payload, 1: 4},
        [(payload, b"ABCD"), (0x2000230c, bytes(4)),
         (0x20007554, bytes(4))],
        {1: {0: 100, 1: 0}, 4: {0: 0xfffffffb}},
        {0: [(0, 0, bytes(24), 0x00086c78)],
         2: [(0, 0, bytes(23), 0x00086c78)],
         3: [(0, 0, b"ABCD", 0x00086c04)]},
    )


def _app_4967c_null_success_case():
    return (
        {0: 0, 1: 4},
        [(0x2000230c, bytes(4)), (0x20007554, bytes(4))],
        {1: {0: 100, 1: 0}, 3: {0: 0}, 4: {0: 140, 1: 0}},
        {0: [(0, 0, bytes(24), 0x00086c78)],
         2: [(0, 0, bytes(23), 0x00086c78)]},
    )


def _app_4967c_invalid_length_case(level, buffered):
    payload = emu.SCRATCH + 0x1800
    return (
        {0: payload, 1: 11},
        [(payload, b"0123456789A"),
         (0x2000230c, int(level).to_bytes(4, "little")),
         (0x20007554, int(buffered).to_bytes(4, "little"))],
        {},
        {0: [(0, 0, bytes(24), 0x00086c78)]},
    )


def _app_357dc_calendar_case(mode, elapsed, fields=None, twelve_hour=False,
                              sink=0):
    """Production-shaped long-duration display state.

    ``fields`` is the exact six-halfword result produced by FUN_0004a1b8:
    year, month, day, hour, minute and second.  The producer owns the complete
    twelve-byte local record; binding its write to both call ordinal and target
    makes every calendar field and the two-argument ABI observable.
    """
    timestamp = 0x10203040
    app_state = emu.SCRATCH + 0x3000
    settings = emu.SCRATCH + 0x5000
    memory = [
        (0x20007554, int(sink).to_bytes(4, "little")),
        (app_state + 0xfec, settings.to_bytes(4, "little")),
        (settings + 0x5e, bytes((int(bool(twelve_hour)),))),
    ]
    oracles = {
        0: {0: app_state},
        1: {0: (timestamp + elapsed) & 0xffffffff},
        4: {0: mode},
    }
    if mode != 6 and fields is not None and elapsed < 86400:
        # The detailed-time arm queries the same application singleton twice
        # more: first for the diagnostic byte and then for the actual 12/24h
        # selector.  Leaving either result random silently disables this nest.
        oracles[7] = {0: app_state}
        oracles[9] = {0: app_state}
    effects = {}
    if fields is not None:
        record = struct.pack("<6H", *fields)
        effects[5] = [(1, 0, record, 0x0004a1b8)]
    return ({0: emu.SCRATCH, 1: timestamp}, memory, oracles, effects)


def _net_mode_update_case(mode, allocated=True):
    obj = emu.SCRATCH + 0x1800
    valid = mode in (1, 3, 5)
    memory = [(obj, bytes(0x40))] if valid and allocated else []
    oracles = ({0: {0: obj if allocated else 0}} if valid else {})
    return ({0: mode}, memory, oracles)


def _net_event_dispatch_case(mode, handle=0, name_kind="fallback", queued=False,
                             context_zero=False, slot_offset=0):
    names = [emu.SCRATCH + 0x5000 + 0x20 * i for i in range(5)]
    table = b"".join(pointer.to_bytes(4, "little") for pointer in names)
    memory = [(8 + slot_offset, int(handle).to_bytes(4, "little")),
              (0x0103cb34, table)]
    memory.extend((pointer, ("mode-%d" % i).encode() + b"\0")
                  for i, pointer in enumerate(names))
    context = 0
    if queued or context_zero:
        context = emu.SCRATCH + 0x2000
        context_data = bytearray(0x30)
        context_data[0x1c:0x20] = int(queued).to_bytes(4, "little")
        memory.append((context, bytes(context_data)))
    oracles = {0: {0: slot_offset}}
    if handle:
        name = emu.SCRATCH + 0x7000
        if name_kind == "valid":
            memory.append((name, b"runtime-name\0"))
            oracles[2 + int(queued)] = {0: name}
        elif name_kind == "empty":
            memory.append((name, b"\0"))
            oracles[2 + int(queued)] = {0: name}
        else:
            oracles[2 + int(queued)] = {0: 0}
    return ({0: mode, 1: context}, memory, oracles)


def _flash_read_case(recover=False):
    """Production-shaped flash callback table and bounded success paths.

    FUN_000167a8 returns the runtime API object; its read, erase, and write
    entries live at +0x1030/+0x1038/+0x1034.  Random oracle pointers make the
    indirect calls fault before any recovered control flow can be compared.
    """
    api = emu.SCRATCH + 0x1000
    state = bytearray(0x1040)
    for offset in (0x1030, 0x1034, 0x1038):
        state[offset:offset + 4] = (0x00080001).to_bytes(4, "little")
    memory = [(api, bytes(state))]
    if not recover:
        # memset, device-ready, API lookup x2, read, decode, success log.
        oracles = {
            1: {0: 1}, 2: {0: api}, 3: {0: api},
            4: {0: 0}, 5: {0: 0},
        }
    else:
        # Decode failure drives erase, write, reread, and final decode.
        oracles = {
            1: {0: 1}, 2: {0: api}, 3: {0: api}, 4: {0: 0},
            5: {0: 1}, 6: {0: api}, 7: {0: api}, 8: {0: 0},
            9: {0: api}, 10: {0: api}, 11: {0: 0},
            12: {0: api}, 13: {0: api}, 14: {0: 0}, 15: {0: 0},
        }
    return ({}, memory, oracles)


def _app_43a68_bitmap_case(flush=False):
    """Two rows by two source bytes with exact row and display ownership."""
    bitmap = emu.SCRATCH + 0x1000
    table = emu.SCRATCH + 0x3000
    rows = [emu.SCRATCH + 0x4000 + 0x100 * index for index in range(4)]
    accessor = emu.SCRATCH + 0x6000
    table_image = b"".join(row.to_bytes(4, "little") for row in rows)
    accessor_image = bytearray(0xec0)
    accessor_image[0xeb4:0xeb8] = (0x11223344).to_bytes(4, "little")
    accessor_image[0xeb8:0xebc] = (0x55667788).to_bytes(4, "little")
    memory = [
        (bitmap, bytes.fromhex("813ca55a")),
        (0x2000a034, table.to_bytes(4, "little")),
        (table, table_image),
        *((row, bytes(0x40)) for row in rows),
        (accessor, bytes(accessor_image)),
        (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
    ]
    if not flush:
        return ({0: 2, 1: 1, 2: 18, 3: 3}, memory,
                {0: {0: 0, 1: 1}, 1: {0: 0, 1: 1}})
    return ({0: 2, 1: 1, 2: 18, 3: 3}, memory,
            {0: {0: 2, 1: 1}, 2: {0: 2, 1: 1},
             3: {0: accessor}, 4: {0: accessor}})


def _float_format_special_case(low, high, nan_case=False, conversion="g"):
    """Bounded printf floating conversion for NaN/infinity classification."""
    descriptor = bytearray(0x100)
    descriptor[4:8] = (6).to_bytes(4, "little")
    descriptor[24] = ord(conversion)
    table = emu.SCRATCH + 0x3000
    decimal_point = emu.SCRATCH + 0x3100
    va_cursor = emu.SCRATCH + 0x4000
    value = emu.SCRATCH + 0x5000
    if nan_case:
        # FUN_0000de2c is the NaN predicate.  The first call rejects the
        # finite/infinity comparison and the self-comparison selects NaN.
        # Width setup is therefore the next call at ordinal four.
        oracles = {
            0: {0: table}, 1: {0: 1}, 2: {0: 1}, 3: {0: 1},
            4: {0: 0}, 5: {0: 0},
        }
        width_ordinal = 4
    else:
        # Infinity is non-NaN but greater than DBL_MAX: the NaN predicate and
        # FUN_0000ddf0 comparison both return zero.  FUN_0000dddc then tests
        # the original signed value against zero and publishes the sign.
        sign_result = 1 if high & 0x80000000 else 0
        oracles = {
            0: {0: table}, 1: {0: 1}, 2: {0: 0}, 3: {0: 0},
            4: {0: sign_result}, 5: {0: 0}, 6: {0: 0},
        }
        width_ordinal = 5
    case = (
        {0: emu.SCRATCH + 0x2000, 1: emu.SCRATCH + 0x1000,
         2: 0x55, 3: 0x00080001},
        [(emu.SCRATCH + 0x1000, bytes(descriptor)),
         (table, decimal_point.to_bytes(4, "little")),
         (decimal_point, b".\0"),
         (emu.STACK_TOP, va_cursor.to_bytes(4, "little")),
         (va_cursor, value.to_bytes(4, "little")),
         (value, low.to_bytes(4, "little") + high.to_bytes(4, "little"))],
        oracles,
    )
    return case + ({
        width_ordinal: [
            (2, 0, (3).to_bytes(4, "little") + bytes(4), 0x00086e1c),
        ],
    },)


def _property_update_case(lookup_result, selected=4, current=4,
                          callback_result=0):
    """Property lookup plus the installed device callback and diagnostics."""
    owner = emu.SCRATCH + 0x1000
    handle = emu.SCRATCH + 0x2000
    vtable = emu.SCRATCH + 0x3000
    owner_bytes = bytearray(0x80)
    owner_bytes[0x0c:0x10] = handle.to_bytes(4, "little")
    owner_bytes[0x20:0x24] = int(current).to_bytes(4, "little", signed=True)
    handle_bytes = bytearray(0x20)
    handle_bytes[8:12] = vtable.to_bytes(4, "little")
    vtable_bytes = bytearray(0x20)
    vtable_bytes[8:12] = (0x00080001).to_bytes(4, "little")
    oracles = {0: {0: lookup_result}}
    if lookup_result != 0:
        oracles[1] = {0: 0}
    elif selected != current:
        oracles[1] = {0: callback_result}
        if callback_result != 0:
            oracles[2] = {0: 0}
    result = (int(selected).to_bytes(4, "little", signed=True) +
              (0x13579bdf).to_bytes(4, "little") +
              (2).to_bytes(4, "little"))
    return (
        {0: owner, 1: 7},
        [(owner, bytes(owner_bytes)), (handle, bytes(handle_bytes)),
         (vtable, bytes(vtable_bytes))],
        oracles,
        {0: [(2, 0, result, 0x00083a92)]},
    )


def _configuration_case(parser_result=0, decode_result=0, present=0,
                        parsed_kind=1, parsed_count=0, amount=0,
                        total=0, progress=0, transfer_result=0,
                        cleanup_result=0):
    """Configuration parser outputs with exact 32-byte and 24-byte records."""
    owner = emu.SCRATCH + 0x0800
    parser_input = emu.SCRATCH + 0x1000
    control = emu.SCRATCH + 0x1200
    parsed = bytearray(32)
    parsed[0:4] = b"cfg\0"
    parsed[4:8] = int(parsed_kind).to_bytes(4, "little", signed=True)
    parsed[8:12] = (-1).to_bytes(4, "little", signed=True)
    parsed[12:16] = (7).to_bytes(4, "little", signed=True)
    parsed[16:20] = int(parsed_count).to_bytes(4, "little", signed=True)
    parsed[20:24] = (4).to_bytes(4, "little")
    parsed[24:28] = (2).to_bytes(4, "little", signed=True)
    parsed[28:32] = b"end\0"
    decoded = bytearray(24)
    decoded[0:4] = int(total).to_bytes(4, "little")
    decoded[8:12] = int(amount).to_bytes(4, "little", signed=True)
    decoded[12:16] = (0x2468ace0).to_bytes(4, "little")
    decoded[16] = int(present)
    state = bytearray(0x40)
    state[4:8] = int(progress).to_bytes(4, "little")
    state[8:12] = int(total).to_bytes(4, "little")
    oracles = {0: {0: 0}, 1: {0: parser_result}}
    writes = {
        0: [(0, 0, bytes(32), 0x00086c78)],
        1: [(3, 0, bytes(4), 0x00080872),
            (1, -0x40, bytes(parsed), 0x00080872)],
    }
    if parser_result == 0:
        oracles[2] = {0: decode_result}
        writes[2] = [(1, 0, bytes(decoded), 0x000518a8)]
        if decode_result == 0:
            if not present:
                oracles[3] = {0: 9}
            elif parsed_count == 0:
                # Copy, clear, optional completion read, then release.
                oracles[6 if total == progress else 3] = {0: 0}
            else:
                oracles[3] = {0: transfer_result}
                if transfer_result != 0:
                    oracles[5] = {0: cleanup_result}
                elif progress + amount != total:
                    oracles[4] = {0: 0}
        else:
            oracles[4] = {0: cleanup_result}
    return (
        {0: owner},
        [(owner, bytes(4) + parser_input.to_bytes(4, "little") +
          control.to_bytes(4, "little")),
         (parser_input, bytes(0x100)), (control, bytes(0x100)),
         (0x2000ab7c, bytes(state))],
        oracles, writes,
    )


def _settings_dispatch_case(global_word, primary=0, secondary=0,
                            callback_result=None, null_input=False):
    """Settings-name dispatch across both name families and callback exits."""
    inp = 0 if null_input else emu.SCRATCH + 0x1000
    oracles = {}
    if inp:
        oracles[0] = {0: 4}
        oracles[1] = {0: primary}
        if primary != 0:
            oracles[2] = {0: secondary}
            if secondary == 0 and callback_result is not None:
                oracles[3] = {0: callback_result}
                if callback_result < 0:
                    oracles[4] = {0: 0}
        elif not (global_word & 8) and callback_result is not None:
            oracles[2] = {0: callback_result}
            if callback_result < 7:
                oracles[3] = {0: 0}
    elif global_word & 1:
        oracles[0] = {0: 0}
    memory = [(0x200020d4, int(global_word).to_bytes(4, "little"))]
    if inp:
        memory.append((inp, bytes(0x100)))
    return ({0: inp, 1: 0, 2: 0x00080001, 3: 0x55}, memory, oracles)


def _float_format_finite_case(conversion, precision, decimal_position, digits,
                              width=0, flags=0, fail_callback=False,
                              fail_callback_offset=0, value_low=0,
                              value_high=0x3ff40000, sign=0,
                              zero_result=0, value_cursor_offset=0,
                              width_result=0):
    """Finite printf conversion with bounded dtoa results and output calls."""
    descriptor = bytearray(0x100)
    descriptor[0:4] = int(flags).to_bytes(4, "little")
    descriptor[4:8] = int(precision).to_bytes(4, "little")
    descriptor[12:16] = int(width).to_bytes(4, "little")
    descriptor[24] = ord(conversion)
    table = emu.SCRATCH + 0x3000
    decimal_point = emu.SCRATCH + 0x3100
    dtoa_digits = emu.SCRATCH + 0x3200
    va_cursor = emu.SCRATCH + 0x4000
    value = emu.SCRATCH + 0x5000
    owner = emu.SCRATCH + 0x2000
    scientific = (conversion in "eE" or
                  (conversion in "gG" and
                   (decimal_position < -3 or decimal_position > precision)))
    oracles = {
        0: {0: table}, 1: {0: 1},
        2: {0: 1}, 3: {0: 0}, 4: {0: dtoa_digits}, 5: {0: 0},
    }
    width_ordinal = 5
    if scientific:
        # Exponent formatter precedes width setup on e/E and scientific g/G.
        oracles[5] = {0: 4}
        width_ordinal = 6
        oracles[width_ordinal] = {0: width_result & 0xffffffff}
    else:
        oracles[width_ordinal] = {0: width_result & 0xffffffff}
    direct_callback_ordinal = 7
    for ordinal in range(direct_callback_ordinal,
                         direct_callback_ordinal + 24):
        oracles[ordinal] = {0: 0}
    ddc8_ordinal = 9 if scientific else 6
    oracles[ddc8_ordinal] = {0: zero_result}
    if fail_callback:
        oracles[direct_callback_ordinal + fail_callback_offset] = {
            0: 0xffffffff}
    writes = {
        4: [(3, 0, bytes((sign & 0xff,)), 0x00086cda),
            (4, 0, int(decimal_position & 0xffffffff).to_bytes(4, "little"),
             0x00086cda),
            (6, 0, len(digits).to_bytes(4, "little"), 0x00086cda)],
        width_ordinal: [
            (2, 0, (min(width, len(digits)) if width else len(digits)).to_bytes(
             4, "little") + bytes(4), 0x00086e1c)],
    }
    return (
        {0: owner, 1: emu.SCRATCH + 0x1000,
         2: 0x55, 3: 0x00080001},
        [(emu.SCRATCH + 0x1000, bytes(descriptor)),
         (table, decimal_point.to_bytes(4, "little")),
         (decimal_point, b".\0"),
         (dtoa_digits, digits.encode("ascii") + b"\0"),
         (emu.STACK_TOP, va_cursor.to_bytes(4, "little")),
         (va_cursor, (value + value_cursor_offset).to_bytes(4, "little")),
         (value, (bytes(8) if value_cursor_offset else b"") +
          int(value_low).to_bytes(4, "little") +
          int(value_high).to_bytes(4, "little"))],
        oracles, writes,
    )


def _numeric_parse_case(kind):
    """Production-shaped hexadecimal parser state and ordinal helper results.

    The parser consumes a string after its caller-owned ``0x`` prefix.  Its
    digit helper returns hexadecimal nibbles for A-F and 0x10..0x19 for the
    decimal characters used by a P exponent.  Keep repeated classifications
    deterministic: an earlier version returned different values for the same
    ``A`` byte merely to steer branches, which was useful as a smoke test but
    was not a defensible parser fixture.

    Every result below is attached to the exact dynamic call ordinal.  The
    ordinary differential call trace additionally checks the semantic target
    at that ordinal.  Shift writes are separately target-bound to FUN_0008729e
    by REVIEWED_ORACLE_CASES' fourth element.
    """
    cursor = emu.SCRATCH + 0x1000
    outputs = emu.SCRATCH + 0x1100
    constraints = emu.SCRATCH + 0x1200
    text_address = emu.SCRATCH + 0x2000
    number = emu.SCRATCH + 0x3000
    shifted_number = emu.SCRATCH + 0x3200
    expanded_number = emu.SCRATCH + 0x3400
    owner = emu.SCRATCH + 0x4000
    locale = emu.SCRATCH + 0x5000
    if kind == "early-six":
        text_data = b"00x\0"
        oracles = {0: {0: 1}, 1: {0: 0}, 2: {0: 1}}
        limits = (0, 0, 100, 0)
        param6 = 0
        writes = {}
    elif kind == "early-zero":
        text_data = b"000x\0"
        oracles = {0: {0: 1}, 1: {0: 0}, 2: {0: 1}}
        limits = (0, 0, 100, 0)
        param6 = 0
        writes = {}
    else:
        specs = {
            # Decimal-point transition plus both signs of a binary exponent.
            # AB has bit length eight; target precision 20 requires a
            # four-bit right shift and exposes guard/sticky classification.
            "decimal-exp-positive": ("A.Bp+2", (20, -100, 100, 0), 0,
                                     (1, 0), False, "."),
            "decimal-exp-negative": ("A.Bp-2", (20, -100, 100, 0), 0,
                                     (0,), False, "."),
            "uppercase-exponent": ("A.BP+2", (20, -100, 100, 0), 0,
                                   (1, 0), False, "."),
            "unsigned-exponent": ("Ap2", (28, -100, 100, 0), 0,
                                  (), False, "."),
            "multidigit-exponent": ("Ap12", (28, -100, 100, 0), 0,
                                    (), False, "."),
            "multibyte-locale": ("A::BP+2", (20, -100, 100, 0), 0,
                                 (1, 0), False, "::"),
            # Nine nibbles cross the 32-bit limb boundary.
            "multi-limb": ("123456789", (31, -100, 100, 0), 0, (), False, "."),
            # Precision larger than the natural leading-zero count invokes
            # the left-shift/relocation helper and returns its new object.
            "left-shift": ("A", (32, -100, 100, 0), 0, (), False, "."),
            # The first allocation failure reaches the assertion sink.
            "initial-allocation-fatal": ("A", (28, -100, 100, 0), 0,
                                         (), True, "."),
            # Exponent limits drive the two terminal range results.
            "overflow": ("Ap+9", (28, -100, 4, 0), 0, (), False, "."),
            "underflow-reject": ("Ap-9", (28, 30, 100, 0), 0, (), False, "."),
            "underflow-minimum": ("Ap-9", (28, 30, 100, 2), 0, (), False, "."),
            # Round-to-even below/above the retained-word parity boundary and
            # a directed rounding mode controlled by the sixth AAPCS arg.
            "round-even-down": ("AB", (20, -100, 100, 1), 0,
                                (1, 0), False, "."),
            "round-even-up": ("BB", (20, -100, 100, 1), 0,
                              (1, 0), False, "."),
            "round-directed": ("AB", (20, -100, 100, 3), 1,
                               (1, 1), False, "."),
            "round-mode2-zero": ("AB", (20, -100, 100, 2), 0,
                                 (1, 1), False, "."),
            "round-mode2-one": ("AB", (20, -100, 100, 2), 1,
                                (1, 1), False, "."),
            # Shifting nine all-one nibbles by four leaves one active
            # 0xffffffff limb.  Rounding carries through it and forces the
            # capacity-expansion island, followed by scale normalization.
            "carry-expand-success": ("FFFFFFFFF", (24, -100, 100, 1), 0,
                                     (1, 1), False, "."),
            "carry-expand-fatal": ("FFFFFFFFF", (24, -100, 100, 1), 0,
                                   (1, 1), False, "."),
        }
        (text, limits, param6, remainder_results, allocation_retry,
         separator) = specs[kind]
        text_data = b"00" + text.encode("ascii") + b"\0"

        def digit_value(ch):
            if "0" <= ch <= "9":
                return 0x10 + ord(ch) - ord("0")
            if "A" <= ch <= "F":
                return 10 + ord(ch) - ord("A")
            if "a" <= ch <= "f":
                return 10 + ord(ch) - ord("a")
            return 0

        oracles = {}
        targets = []

        def result(target, value, preserved=None):
            ordinal = len(targets)
            targets.append(target)
            registers = {0: value}
            if preserved:
                registers.update(preserved)
            oracles[ordinal] = registers
            return ordinal

        result(0x0000ef12, len(separator))
        significand = text
        exponent = ""
        exponent_sign = 1
        exponent_offset = 0
        for marker in ("p", "P"):
            if marker in significand:
                significand, exponent = significand.split(marker, 1)
                exponent_offset = len(significand) + 1
                if exponent.startswith(("+", "-")):
                    if exponent[0] == "-":
                        exponent_sign = -1
                    exponent = exponent[1:]
                    exponent_offset += 1
                break
        before, found_separator, after = significand.partition(separator)
        digits = before + after
        assert digits and all(digit_value(ch) for ch in digits)

        # Initial digit test and forward scan through the integer portion.
        result(0x00087340, digit_value(before[0]))
        for ch in before:
            result(0x00087340, digit_value(ch))
        result(0x00087340, 0)  # decimal point, P, or NUL
        if found_separator:
            result(0x00087036, 0)  # exact locale separator
            for ch in after:
                result(0x00087340, digit_value(ch))
            result(0x00087340, 0)  # P or NUL
        else:
            result(0x00087036, 1)  # delimiter is not the locale separator

        if exponent:
            for index, ch in enumerate(exponent):
                # The original keeps the scan pointer in caller-scratch r1
                # across every digit-helper call.  Model the concrete shipped
                # helper's preservation, not abstract AAPCS clobbering.
                result(0x00087340, digit_value(ch),
                       {1: text_address + 2 + exponent_offset + index})
            # The shipped digit helper preserves the scan pointer in r1 even
            # though r1 is caller-scratch under base AAPCS.  Original code
            # intentionally consumes that concrete implementation property at
            # 0x78218, so model it rather than injecting a random oracle r1.
            result(0x00087340, 0,
                   {1: text_address + 2 + len(text)})

        if allocation_retry:
            result(0x000785d4, 0)
            # The diagnostic helper preserves the failed size in r1; original
            # code increments it directly at 0x78272 before retrying.
            result(0x00076a94, 0, {1: 0})
        result(0x000785d4, number)

        # The firmware packs least-significant nibbles first, skipping the
        # locale separator only after an exact FUN_00087036 comparison.
        for ch in reversed(after):
            result(0x00087340, digit_value(ch))
        if found_separator:
            result(0x00087036, 0)
        for ch in reversed(before):
            result(0x00087340, digit_value(ch))

        numeric_value = int(digits, 16)
        limb_count = (len(digits) + 7) // 8
        bit_length = numeric_value.bit_length()
        result(0x00087510, bit_length)
        natural_zeroes = limb_count * 32 - bit_length
        target_precision = limits[0]
        writes = {}
        active_number = number
        scale = (-4 * len(after) if found_separator else 0)
        if exponent:
            scale += exponent_sign * int(exponent, 10)

        if target_precision < natural_zeroes:
            shift = natural_zeroes - target_precision
            first = remainder_results[0] if remainder_results else 0
            result(0x0008768e, first)
            guard_index = shift - 1
            guard_set = bool(numeric_value & (1 << guard_index))
            if first and guard_set and guard_index >= 2:
                second = remainder_results[1] if len(remainder_results) > 1 else 0
                result(0x0008768e, second)
            shift_ordinal = result(0x0008729e, 0)
            shifted_value = numeric_value >> shift
            shifted_bytes = b"".join(
                ((shifted_value >> (32 * i)) & 0xffffffff).to_bytes(4, "little")
                for i in range(limb_count))
            writes[shift_ordinal] = [
                (0, 0x14, shifted_bytes, 0x0008729e),
            ]
            if kind.startswith("carry-expand-"):
                # The shift helper normalizes away the zero high limb.  The
                # parser later reloads this count before propagating carry.
                writes[shift_ordinal].append(
                    (0, 0x10, (1).to_bytes(4, "little"), 0x0008729e))
            scale += shift
        elif target_precision > natural_zeroes:
            shift = target_precision - natural_zeroes
            active_number = shifted_number
            result(0x000789f0, shifted_number)
            scale -= shift

        if scale > limits[2]:
            result(0x00078654, 0)
        elif scale < limits[1]:
            distance = limits[1] - scale
            if target_precision <= distance:
                # Mode 2 with param6==0 returns the minimum quantum; all
                # other configured cases reject and free the allocation.
                if not (limits[3] == 2 and param6 == 0):
                    result(0x00078654, 0)

        if kind.startswith("carry-expand-"):
            if kind == "carry-expand-fatal":
                result(0x000785d4, 0)
                result(0x00076a94, 0)
            else:
                result(0x000785d4, expanded_number)
                result(0x00086c04, 0)
                result(0x00078654, 0)
                # The new high limb increases the active word count, so the
                # parser renormalizes once and increments the binary scale.
                result(0x0008729e, 0)

        # Pin the returned left-shift allocation as a complete helper-owned
        # object.  Its scalar fields and limbs are subsequently read/written
        # by both implementations and therefore remain fully observable.
        shifted_value = numeric_value << max(0, target_precision - natural_zeroes)
        shifted_object = bytearray(0x100)
        shifted_object[4:8] = (limb_count).to_bytes(4, "little")
        shifted_object[8:12] = (8).to_bytes(4, "little")
        shifted_object[16:20] = (limb_count).to_bytes(4, "little")
        for i in range(limb_count):
            shifted_object[20 + 4*i:24 + 4*i] = (
                (shifted_value >> (32*i)) & 0xffffffff).to_bytes(4, "little")

    limit_bytes = b"".join((value & 0xffffffff).to_bytes(4, "little")
                           for value in limits)
    number_state = bytearray(0x100)
    number_state[4:8] = (1).to_bytes(4, "little")
    number_state[8:12] = ((1 if kind.startswith("carry-expand-") else 8)
                          ).to_bytes(4, "little")
    expanded_state = bytearray(0x100)
    expanded_state[4:8] = (2).to_bytes(4, "little")
    expanded_state[8:12] = (8).to_bytes(4, "little")
    expanded_state[16:20] = (1).to_bytes(4, "little")
    return (
        {0: owner, 1: cursor, 2: constraints, 3: outputs, 5: param6},
        [(cursor, text_address.to_bytes(4, "little")), (outputs, bytes(8)),
         (constraints, limit_bytes), (text_address, text_data),
         (number, bytes(number_state)), (shifted_number, bytes(shifted_object)
          if kind not in ("early-six", "early-zero") else bytes(0x100)),
         (expanded_number, bytes(expanded_state)),
         (owner, bytes(0x100)), (0x00098768, locale.to_bytes(4, "little")),
         (locale, (separator.encode("ascii") + b"\0")
          if kind not in ("early-six", "early-zero") else b".\0"),
         # Fifth and sixth AAPCS arguments are caller stack words.  The fifth
         # points to a complete four-byte result object; the sixth is also
         # pinned in arg overrides for documentation and stack setup below.
         (emu.STACK_TOP, (outputs + 4).to_bytes(4, "little") +
          param6.to_bytes(4, "little"))],
        oracles, writes,
    )


def _app_32308_case(kind, buffered=False):
    """Production validation, current-mode and unsupported-mode paths."""
    request = emu.SCRATCH + 0x1000
    out_pointer = emu.SCRATCH + 0x2000
    output = emu.SCRATCH + 0x2100
    status_length = emu.SCRATCH + 0x2200
    controller = emu.SCRATCH + 0x3000
    request_bytes = bytearray(8)
    controller_bytes = bytearray(0xf00)
    memory = [
        (request, bytes(request_bytes)),
        (out_pointer, output.to_bytes(4, "little")),
        (output, bytes(16)),
        (status_length, bytes(4)),
        (controller, bytes(controller_bytes)),
        (0x20007554, int(buffered).to_bytes(4, "little")),
    ]
    if kind == "invalid-length":
        return ({0: request, 1: 4, 2: out_pointer, 3: status_length},
                memory, {})
    if kind == "current":
        request_bytes[4] = 1
        controller_bytes[0xed4] = 1
        memory[0] = (request, bytes(request_bytes))
        memory[4] = (controller, bytes(controller_bytes))
        return ({0: request, 1: 5, 2: out_pointer, 3: status_length},
                memory, {1: {0: controller}})
    if kind == "unsupported":
        request_bytes[4] = 2
        memory[0] = (request, bytes(request_bytes))
        return ({0: request, 1: 5, 2: out_pointer, 3: status_length},
                memory, {})
    raise ValueError(kind)


def _app_32308_poll_case(success):
    """Coherent mode-change request with a reviewed 21-byte poll result."""
    request = emu.SCRATCH + 0x1000
    out_pointer = emu.SCRATCH + 0x2000
    output = emu.SCRATCH + 0x2100
    status_length = emu.SCRATCH + 0x2200
    controller = emu.SCRATCH + 0x3000
    request_bytes = bytearray(8)
    request_bytes[4] = 1
    controller_bytes = bytearray(0xf00)
    controller_bytes[0xed4] = 0  # force the mode-change/poll path
    memory = [
        (request, bytes(request_bytes)),
        (out_pointer, output.to_bytes(4, "little")),
        (output, bytes(16)),
        (status_length, bytes(4)),
        (controller, bytes(controller_bytes)),
    ]
    oracles = {1: {0: controller}, 2: {0: controller}, 3: {0: controller}}
    writes = {}
    poll_ordinals = (5,) if success else (5, 7, 9, 11, 13)
    for ordinal in poll_ordinals:
        oracles[ordinal] = {0: 0}
        record = bytearray(21)
        record[20] = 1 if success else 0
        writes[ordinal] = [
            (0, 0, bytes(record), 0x000232f8),
        ]
    return ({0: request, 1: 5, 2: out_pointer, 3: status_length},
            memory, oracles, writes)


def _app_32b24_dispatch_case(hit, mode=0, callback_result=0,
                             final_result=0, null_request=False):
    """Production dispatcher, including framing and failure propagation."""
    selector = 0x42
    request = emu.SCRATCH + 0x1000
    out_pointer = emu.SCRATCH + 0x2000
    output = emu.SCRATCH + 0x2100
    output_length = emu.SCRATCH + 0x2200
    table = bytearray(45 * 8)
    if hit:
        table[0] = selector
        table[4:8] = (0x00080001).to_bytes(4, "little")
    # In the fallback fixture every selector and callback remains zero, so the
    # requested nonzero selector traverses all 45 records deterministically.
    oracles = {}
    if hit:
        oracles[0] = {0: callback_result}
        oracles[1] = {0: final_result}
    else:
        oracles[0] = {0: final_result}
    return (
        {0: mode, 1: 0 if null_request else request, 2: 1, 3: out_pointer},
        [(request, bytes((selector,)) + bytes(15)),
         (out_pointer, output.to_bytes(4, "little")),
         (output, bytes((0x11, 0x22, 0x33, 0x44, 0x55)) + bytes(27)),
         (output_length, b"\x05" + bytes(3)),
         (0x0008a208, bytes(table)),
         (0x20019ef5, bytes(32))],
        oracles,
    )


def _app_32b24_invalid_case(mode=2):
    """Invalid selector reaches only the diagnostic and -1 return."""
    request = emu.SCRATCH + 0x1000
    out_pointer = emu.SCRATCH + 0x2000
    output = emu.SCRATCH + 0x2100
    output_length = emu.SCRATCH + 0x2200
    return (
        {0: mode, 1: request, 2: 1, 3: out_pointer},
        [(request, b"\x42" + bytes(15)),
         (out_pointer, output.to_bytes(4, "little")),
         (output, bytes(32)), (output_length, b"\x05" + bytes(3))],
        {0: {0: 0}},
    )


def _app_2c714_case(kind, buffered=False):
    """Production-shaped startup wait and synchronization state paths."""
    context = emu.SCRATCH + 0x0800
    state = emu.SCRATCH + 0x2000
    selector = emu.SCRATCH + 0x2100
    result = emu.SCRATCH + 0x2200
    nested = emu.SCRATCH + 0x2300
    waiting = emu.SCRATCH + 0x4000
    ready = emu.SCRATCH + 0x5200
    ctx = bytearray(0x1100)
    status = bytearray(0x20)
    waiting_bytes = bytearray(0x1100)
    ready_bytes = bytearray(0x1100)
    ctx[0xfea] = 10
    ctx[0xff0:0xff4] = nested.to_bytes(4, "little")
    memory = [
        (context, bytes(ctx)), (state, bytes(status)),
        (selector, bytes(4)), (result, bytes(4)),
        (nested, (0x89abcdef).to_bytes(4, "little")),
        (waiting, bytes(waiting_bytes)), (ready, bytes(ready_bytes)),
        (0x2000230c, (3).to_bytes(4, "little")),
        (0x20007554, int(buffered).to_bytes(4, "little")),
    ]
    if kind in ("wait-break", "wait-delay"):
        waiting_bytes[0xdd] = 2
        memory[5] = (waiting, bytes(waiting_bytes))
        memory[6] = (ready, bytes(ready_bytes))
        status[1] = 6
        memory[1] = (state, bytes(status))
        memory[2] = (selector, b"\x01" + bytes(3))
        if kind == "wait-break":
            # The startup state helper reports ready immediately.
            oracles = {0: {0: waiting}, 1: {0: waiting}, 2: {0: 4},
                       4: {0: 0}, 5: {0: context}, 7: {0: context}}
        else:
            # One bounded wait/delay iteration, followed by a ready accessor.
            oracles = {0: {0: waiting}, 1: {0: waiting}, 2: {0: 0},
                       4: {0: ready}, 6: {0: 0},
                       7: {0: context}, 9: {0: context}}
    elif kind in ("state-0", "state-1"):
        status[1] = int(kind[-1])
        status[7] = 1
        status[0xb:0xf] = (0x12345678).to_bytes(4, "little")
        memory[1] = (state, bytes(status))
        # Initial accessor/state query, two accessors used by the abort/state
        # checks, then the selected direct or buffered diagnostic call.
        oracles = {0: {0: context}, 2: {0: 1},
                   3: {0: context}, 4: {0: context}}
    elif kind in ("state-2", "state-6", "state-6-decrement"):
        status[1] = 6 if kind == "state-6-decrement" else int(kind[-1])
        memory[1] = (state, bytes(status))
        memory[2] = (selector, (2 if kind in ("state-2", "state-6-decrement")
                                else 1).to_bytes(4, "little"))
        # A zero countdown byte enters the late synchronization arm.  State 6
        # selects it directly; state 2 selects it through the caller selector.
        if kind == "state-6-decrement":
            # The live controller gates select the 64-bit timestamp update.
            # A low word below 1000 makes subtraction borrow from the distinct
            # high word, proving both halves of the shipped STRD result.
            ctx[0] = 1
            ctx[0x108f] = 1
            ctx[0x1060:0x1064] = (500).to_bytes(4, "little")
            ctx[0x1064:0x1068] = (0x12345678).to_bytes(4, "little")
            memory[0] = (context, bytes(ctx))
            oracles = {0: {0: context}, 2: {0: 0}, 3: {0: 2},
                       4: {0: context}, 5: {0: context}, 6: {0: context},
                       8: {0: context}}
        else:
            oracles = {0: {0: context}, 2: {0: 0},
                       3: {0: context}, 5: {0: context}}
    elif kind == "late-sync":
        ctx[0x108f] = 0
        status[1] = 6
        memory[0] = (context, bytes(ctx))
        memory[1] = (state, bytes(status))
        memory[2] = (selector, b"\x01" + bytes(3))
        # Initial accessor/state query, then the pre-sync and post-sync
        # accessors both return the same production controller object.
        oracles = {0: {0: context}, 2: {0: 0},
                   3: {0: context}, 5: {0: context}}
    elif kind == "timeout":
        ctx[0] = 1
        ctx[0x108f] = 1
        status[1] = 4
        status[7] = 1
        status[0xb:0xf] = (0x12345678).to_bytes(4, "little")
        memory[0] = (context, bytes(ctx))
        memory[1] = (state, bytes(status))
        # Sixteen unsuccessful state queries, each followed by two accessors
        # and a delay.  The sixteenth iteration emits the periodic logger; the
        # following query succeeds and reaches the late synchronization tail.
        oracles = {0: {0: context}, 2: {0: 1}}
        for iteration in range(16):
            base = 3 + 4 * iteration
            oracles[base] = {0: 0}
            oracles[base + 1] = {0: context}
            oracles[base + 2] = {0: context}
        oracles[68] = {0: 2}
        oracles[73] = {0: 0}
    else:
        raise ValueError(kind)
    return ({0: context, 1: state, 2: selector, 3: result}, memory, oracles)


_SERIALIZER_INPUT = emu.SCRATCH + 0x1000
_SERIALIZER_STRING = emu.SCRATCH + 0x3000
_SERIALIZER_LENGTHS = emu.SCRATCH + 0x3800
_SERIALIZER_CALLBACK = 0x00070001


def _serializer_stack_args(flags, lengths=0, capacity=0):
    """Exact AAPCS stack arguments 5..7 for FUN_0004abc0."""
    return [
        (emu.STACK_TOP, int(flags).to_bytes(4, "little")),
        (emu.STACK_TOP + 4, int(lengths).to_bytes(4, "little")),
        (emu.STACK_TOP + 8, int(capacity).to_bytes(4, "little")),
    ]


def _serializer_header(pointer, deferred=0, records=0, strings=0):
    """Two-word production descriptor followed by deferred/record bytes."""
    data = bytearray(8 + deferred + records * 2)
    data[0:4] = bytes((2, strings, deferred, records))
    data[4:8] = int(pointer).to_bytes(4, "little")
    return data


def _serializer_callback_case(length, failure=None):
    """One deferred string and every ordered output-callback position.

    Call 0 is the production memcpy into the local deferred-index array;
    calls 1..6 are header, encoded-pair bytes, body, index, string, and final
    flush respectively.  The final flush return is intentionally ignored.
    """
    data = _serializer_header(_SERIALIZER_STRING, deferred=1)
    data[8] = 1
    oracles = {0: {0: 0}}
    for ordinal in range(1, 7):
        oracles[ordinal] = {0: 1}
    if failure is not None:
        oracles[failure] = {0: 0xfffffff5}
    memory = [
        (_SERIALIZER_INPUT, bytes(data) + bytes(16)),
        (_SERIALIZER_STRING, b"production-string\0"),
        (_SERIALIZER_LENGTHS, int(length).to_bytes(2, "little") + bytes(30)),
        *_serializer_stack_args(1, _SERIALIZER_LENGTHS, 16),
    ]
    return ({0: _SERIALIZER_INPUT, 1: 16,
             2: _SERIALIZER_CALLBACK, 3: 0x13579bdf}, memory, oracles)


def _serializer_classification_case(pointer, resolver=None):
    """One record, with the pointed value inside or outside the flash range."""
    data = _serializer_header(pointer, records=1)
    data[8:10] = bytes((0x33, 1))
    # Bit 1 admits record processing; bit 3 enables the resolver.  Using bit 3
    # alone would take the early return and never exercise FUN_0007dc00.
    flags = 2 if resolver is None else 10
    oracles = {}
    if resolver is None and not (0x879b0 <= pointer < 0xf8d64):
        oracles[0] = {0: 3}  # strlen only on the outside-range, bit-1 path
    elif resolver is not None:
        low, high = resolver
        oracles[0] = {0: low, 1: high}
        if low:
            oracles[1] = {0: 0}  # descriptor submission
    return ({0: _SERIALIZER_INPUT, 1: 10, 2: 0, 3: 0},
            [(_SERIALIZER_INPUT, bytes(data) + bytes(16)),
             (_SERIALIZER_STRING, b"abc\0"),
             *_serializer_stack_args(flags)], oracles)


def _serializer_resolver_callback_case(low, high):
    """Resolver result controls pair retention; high r1 becomes its key byte."""
    data = _serializer_header(_SERIALIZER_STRING, records=1)
    data[8:10] = bytes((0x33, 1))
    return (
        {0: _SERIALIZER_INPUT, 1: 10,
         2: _SERIALIZER_CALLBACK, 3: 0x2468ace0},
        [(_SERIALIZER_INPUT, bytes(data) + bytes(16)),
         (_SERIALIZER_STRING, b"abc\0"), *_serializer_stack_args(10)],
        {0: {0: low, 1: high}, 1: {0: 1}, 2: {0: 1},
         3: {0: 0xfffffff5}},
    )


def _serializer_index_boundary_case(count):
    """Accumulate exactly 16 deferred indices or assert on the 17th."""
    data = _serializer_header(0x00090000, records=count)
    for index in range(count):
        data[8 + index * 2:10 + index * 2] = bytes((index + 1, 1))
    oracles = ({0: {0: 0xfffffff5}} if count == 16 else
               {0: {0: 0}, 1: {0: 0}})
    return ({0: _SERIALIZER_INPUT, 1: len(data),
             2: _SERIALIZER_CALLBACK, 3: 0},
            [(_SERIALIZER_INPUT, bytes(data) + bytes(16)),
             *_serializer_stack_args(3)], oracles)


def _serializer_flag_case(flags):
    """One outside-range record under every low-nibble flag combination."""
    data = _serializer_header(_SERIALIZER_STRING, records=1)
    data[8:10] = bytes((0x33, 1))
    oracles = {}
    if flags & 2:
        ordinal = 0
        if flags & 8:
            oracles[ordinal] = {0: 0, 1: 0xa1b2c35a}
            ordinal += 1
        oracles[ordinal] = {0: 3}
    return (
        {0: _SERIALIZER_INPUT, 1: 10, 2: 0, 3: 0},
        [(_SERIALIZER_INPUT, bytes(data) + bytes(16)),
         (_SERIALIZER_STRING, b"abc\0"), *_serializer_stack_args(flags)],
        oracles,
    )


def _serializer_multi_length_case():
    """Two deferred strings publish independent unsigned 16-bit lengths."""
    second = _SERIALIZER_STRING + 0x100
    data = bytearray(14)
    data[0:4] = bytes((3, 0, 2, 0))
    data[4:8] = _SERIALIZER_STRING.to_bytes(4, "little")
    data[8:12] = second.to_bytes(4, "little")
    data[12:14] = bytes((1, 2))
    return (
        {0: _SERIALIZER_INPUT, 1: len(data), 2: 0, 3: 0},
        [(_SERIALIZER_INPUT, bytes(data) + bytes(16)),
         (_SERIALIZER_STRING, b"first\0"), (second, b"second\0"),
         (_SERIALIZER_LENGTHS, bytes(32)),
         *_serializer_stack_args(1, _SERIALIZER_LENGTHS, 2)],
        {0: {0: 0x7fff}, 1: {0: 0xfffe}},
    )


def _app_167f4_status_case(result):
    """Production owner object with both signs of FUN_00083dc8 status."""
    owner = emu.SCRATCH + 0x1100
    owner_bytes = bytearray(0x40)
    owner_bytes[0x1c:0x20] = (0x12345678).to_bytes(4, "little")
    return (
        {},
        [(0x00087d14, owner.to_bytes(4, "little")),
         (owner, bytes(owner_bytes))],
        {3: {0: result & 0xffffffff, 1: 0x55667788}},
    )


def _app_17eec_case(state_ready, buffered, send_result):
    """Complete 257-byte transport object through idle/ready/send paths."""
    source = emu.SCRATCH + 0x1000
    payload = bytes(((index * 37 + 11) & 0xff) for index in range(0x100))
    transport = bytearray(0x28)
    transport[0x24:0x28] = (0x30 if state_ready else 0).to_bytes(4, "little")
    copy_ordinal = 3 if state_ready else 1
    send_ordinal = copy_ordinal + 1
    return (
        {0: source, 1: 0x5a},
        [(source, payload),
         (0x200038f8, bytes(transport)),
         (0x20007554, int(bool(buffered)).to_bytes(4, "little"))],
        {send_ordinal: {0: send_result & 0xffffffff}},
        {
            0: [(0, 0, bytes(0x101), 0x00086c78)],
            copy_ordinal: [(0, 0, payload, 0x00086c04)],
        },
    )


def _app_24534_case(mode, first_length, log_level, buffered,
                     callback_result, payload_kind):
    """Full API/vtable/flash fixture for the loader's production paths."""
    api = emu.SCRATCH + 0x1000
    dst_a = emu.SCRATCH + 0x3000
    dst_b = emu.SCRATCH + 0x4000
    api_bytes = bytearray(0x1040)
    api_bytes[0x1030:0x1034] = (0x00080001).to_bytes(4, "little")
    flash = bytearray(0x800)
    if payload_kind == "valid":
        base = mode * 0x200
        flash[base] = 0xaa
        for index in range(1, 0x200):
            flash[base + index] = (index * 29 + mode * 17) & 0xff

    initial_logger = log_level > 2
    readiness_ordinal = 1 if initial_logger else 0
    memset_ordinal = readiness_ordinal + 1
    first_accessor = memset_ordinal + 1
    second_accessor = first_accessor + 1
    callback_ordinal = second_accessor + 1
    oracles = {
        readiness_ordinal: {0: 1},
        first_accessor: {0: api},
        second_accessor: {0: api},
        callback_ordinal: {0: callback_result},
    }
    writes = {
        memset_ordinal: [(0, 0, bytes(0x800), 0x00086c78)],
        callback_ordinal: [(2, 0, bytes(flash), 0x00080000)],
    }
    return (
        {0: mode, 1: dst_a, 2: first_length, 3: dst_b},
        [(api, bytes(api_bytes)),
         (dst_a, bytes(0x300)),
         (dst_b, bytes(0x300)),
         (0x20018465, bytes(0x800)),
         (0x2000230c, int(log_level).to_bytes(4, "little")),
         (0x20007554, int(bool(buffered)).to_bytes(4, "little")),
         (0x00087bf0, (0x13579bdf).to_bytes(4, "little"))],
        oracles,
        writes,
    )


def _app_24534_range_case(buffered):
    """Out-of-range mode through each production diagnostic sink."""
    return (
        {0: 4, 1: emu.SCRATCH + 0x3000, 2: 0x28,
         3: emu.SCRATCH + 0x4000},
        [(emu.SCRATCH + 0x3000, bytes(0x300)),
         (emu.SCRATCH + 0x4000, bytes(0x300)),
         (0x2000230c, (1).to_bytes(4, "little")),
         (0x20007554, int(bool(buffered)).to_bytes(4, "little"))],
        {},
    )


def _app_24534_not_ready_case(buffered):
    """Unavailable flash device with its name consumed by the diagnostic."""
    dst_a = emu.SCRATCH + 0x3000
    dst_b = emu.SCRATCH + 0x4000
    device_name = emu.SCRATCH + 0x5000
    return (
        {0: 0, 1: dst_a, 2: 0x28, 3: dst_b},
        [(dst_a, bytes(0x300)), (dst_b, bytes(0x300)),
         (device_name, b"g1-flash\0"),
         (0x00087bf0, device_name.to_bytes(4, "little")),
         (0x2000230c, (1).to_bytes(4, "little")),
         (0x20007554, int(bool(buffered)).to_bytes(4, "little"))],
        {0: {0: 0}},
    )


def _app_73d1c_case(kind):
    queue = 0x2000b448
    sentinel = queue + 0x1c
    node = 0x20006720 if kind == "forbidden" else emu.SCRATCH + 0x1000
    first = emu.SCRATCH + 0x1100
    second = emu.SCRATCH + 0x1200
    q = bytearray(0x24)
    q[8:12] = (node if kind in ("empty-ready", "middle") else 0).to_bytes(4, "little")
    work = bytearray(0x20)
    work[0x0d] = 0x80 if kind == "already" else 0
    priorities = {
        "already": 5, "forbidden": 3, "empty": 4, "empty-ready": 4,
        "head": 1, "middle": 5, "equal": 5, "append": 9,
    }
    work[0x0e] = priorities[kind]
    writes = [(queue, bytes(q)), (node, bytes(work))]
    oracle_writes = {}
    if kind in ("empty", "empty-ready", "forbidden", "already"):
        q[0x1c:0x20] = sentinel.to_bytes(4, "little")
        q[0x20:0x24] = sentinel.to_bytes(4, "little")
        writes[0] = (queue, bytes(q))
    else:
        first_image = bytearray(0x20)
        first_image[0:4] = sentinel.to_bytes(4, "little")
        first_image[4:8] = sentinel.to_bytes(4, "little")
        first_image[0x0e] = {"head": 9, "append": 1, "equal": 5,
                             "middle": 1}[kind]
        q[0x1c:0x20] = first.to_bytes(4, "little")
        q[0x20:0x24] = first.to_bytes(4, "little")
        if kind == "middle":
            second_image = bytearray(0x20)
            first_image[0:4] = second.to_bytes(4, "little")
            second_image[0:4] = sentinel.to_bytes(4, "little")
            second_image[4:8] = first.to_bytes(4, "little")
            second_image[0x0e] = 9
            q[0x20:0x24] = second.to_bytes(4, "little")
            writes.append((second, bytes(second_image)))
        writes[0] = (queue, bytes(q))
        writes.append((first, bytes(first_image)))
    if kind == "already":
        # Production unlink leaves the queue empty before this routine marks
        # and reinserts the same work item.  Bind every effect to both ordinal
        # zero and the exact FUN_00073cdc target.
        linked = bytearray(work)
        linked[0:4] = sentinel.to_bytes(4, "little")
        linked[4:8] = sentinel.to_bytes(4, "little")
        writes[1] = (node, bytes(linked))
        q[0x1c:0x20] = node.to_bytes(4, "little")
        q[0x20:0x24] = node.to_bytes(4, "little")
        writes[0] = (queue, bytes(q))
        oracle_writes = {0: [
            (0, 0, sentinel.to_bytes(4, "little"), 0x00073cdc),
            (0, 4, sentinel.to_bytes(4, "little"), 0x00073cdc),
            (1, 0, bytes(4), 0x00073cdc),
            (1, 4, bytes(4), 0x00073cdc),
        ]}
    return ({0: node}, writes, {}, oracle_writes)


def _app_757b0_case(kind):
    request = emu.SCRATCH + 0x1000
    work = emu.SCRATCH + 0x1100
    previous = emu.SCRATCH + 0x1200
    following = emu.SCRATCH + 0x1300
    request_image = bytearray(0x20)
    writes = []
    if kind.startswith("self"):
        request_image[0:4] = request.to_bytes(4, "little")
    else:
        request_image[0:4] = work.to_bytes(4, "little")
        work_image = bytearray(0x20)
        work_image[0:4] = following.to_bytes(4, "little")
        work_image[4:8] = previous.to_bytes(4, "little")
        previous_image = bytearray(0x10)
        previous_image[0:4] = work.to_bytes(4, "little")
        following_image = bytearray(0x10)
        following_image[4:8] = work.to_bytes(4, "little")
        writes.extend([(work, bytes(work_image)),
                       (previous, bytes(previous_image)),
                       (following, bytes(following_image))])
    writes.insert(0, (request, bytes(request_image)))
    if kind == "lock-fail":
        oracles = {0: {0: 0}}
    elif kind == "self-unlock-fail":
        oracles = {0: {0: 1}, 2: {0: 0}}
    elif kind == "self-success":
        oracles = {0: {0: 1}, 2: {0: 1}}
    else:
        oracles = {0: {0: 1}, 2: {0: 0x12345678}}
    return ({0: request, 1: 0x55667788}, writes, oracles)


def _app_79780_case(active):
    first = bytearray(16)
    first[0:4] = (0x00080001).to_bytes(4, "little")
    first[4:16] = bytes.fromhex("112233445566778899aabbcc")
    second = bytes.fromhex("102030405060708090a0b0c0d0e0f00001020304")
    state = bytearray(0x1c0)
    if active:
        state[0x118:0x11c] = (0x02000000).to_bytes(4, "little")
    return (
        {0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1100},
        [(emu.SCRATCH + 0x1000, bytes(first)),
         (emu.SCRATCH + 0x1100, second),
         (0x2000cc30, bytes(state)),
         (0x20002ef8, bytes(20)), (0x20002f0c, bytes(16))],
        {},
    )


def _ble_dispatch_case(command, length=0, state=b"", log_level=0, backend=0):
    context = bytearray(0x40)
    context[0x0c:0x10] = (0x00080001).to_bytes(4, "little")
    context[0x10:0x14] = (emu.SCRATCH + 0x1300).to_bytes(4, "little")
    packet = bytearray(0x40)
    packet[0] = command
    packet[2:4] = int(length).to_bytes(2, "little")
    request_state = bytearray(0x40)
    request_state[:len(state)] = state
    accessor = emu.SCRATCH + 0x1400
    owned = emu.SCRATCH + 0x2600
    return (
        {0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1100,
         2: emu.SCRATCH + 0x1200},
        [(emu.SCRATCH + 0x1000, bytes(context)),
         (emu.SCRATCH + 0x1100, bytes(packet)),
         (emu.SCRATCH + 0x1200, bytes(request_state)),
         (emu.SCRATCH + 0x1300, bytes(0x100)),
         (accessor + 0x100c, owned.to_bytes(4, "little")),
         (owned, bytes(0x300)),
         (0x2000230c, int(log_level).to_bytes(4, "little")),
         (0x20007554, int(backend).to_bytes(4, "little"))],
        {ordinal: {0: accessor} for ordinal in range(32)},
    )


def _ble_dispatch_copy_case(command, length, log_level=0, backend=0):
    """Exercise the real bounded payloads for the three copy-style commands."""
    args, memory, _ = _ble_dispatch_case(
        command, length, log_level=log_level, backend=backend)
    payload = bytes((0x31 + i * 17) & 0xff for i in range(length - 1))
    state = bytearray(0x40)
    state[1:1 + len(payload)] = payload
    memory = [(address, bytes(state) if address == emu.SCRATCH + 0x1200 else data)
              for address, data in memory]
    # response memset, payload copy, producer, callback
    writes = {
        0: [(0, 0, bytes(16), 0x00086c78)],
        1: [(0, 0, payload, 0x00086c04)],
        2: [(1, 0, bytes.fromhex("c9a55a3cc37e1896"), 0x00019b54)],
    }
    return args, memory, {}, writes


def _ble_dispatch_4e_case(count, index, mode, publication, owned_state=8):
    """Exact segmented-transfer state, nested mode, and publication fixture."""
    context = bytearray(0x40)
    context[0x0c:0x10] = (0x00080001).to_bytes(4, "little")
    context[0x10:0x14] = (emu.SCRATCH + 0x1300).to_bytes(4, "little")
    length = 13
    packet = bytearray(0x40)
    packet[0] = 0x4e
    packet[2:4] = length.to_bytes(2, "little")
    state = bytearray(0x40)
    state[1:9] = bytes((0x5a, count, index, mode, 0x12, 0x34, 0x56, 0x78))
    payload = bytes.fromhex("91a2b3c4")
    state[9:13] = payload
    accessor = emu.SCRATCH + 0x1400
    owned = emu.SCRATCH + 0x2600
    accessor_image = bytearray(0x1100)
    accessor_image[0xcc] = 0x6d
    accessor_image[0x100c:0x1010] = owned.to_bytes(4, "little")
    owned_image = bytearray(0x300)
    owned_image[0] = owned_state
    owned_image[0x197:0x199] = (3).to_bytes(2, "little")
    complete = index == ((count - 1) & 0xff)
    ordinal = 0
    oracles = {}
    writes = {ordinal: [(0, 0, bytes(16), 0x00086c78)]}
    ordinal += 1
    writes[ordinal] = [(0, 0, bytes(0x158), 0x00086c78)]
    ordinal += 1
    if not complete:
        oracles[ordinal] = {0: accessor}; ordinal += 1
        oracles[ordinal] = {0: accessor}; ordinal += 1
        ordinal += 2  # FUN_0007c1aa and incomplete-segment publication
    writes[ordinal] = [(0, 0, payload, 0x00086c1e)]
    ordinal += 1
    if index == 0:
        oracles[ordinal] = {0: accessor}; ordinal += 1
        writes[ordinal] = [(0, 0, bytes(0x190), 0x00086c78)]; ordinal += 1
        for _ in range(5):
            oracles[ordinal] = {0: accessor}; ordinal += 1
    oracles[ordinal] = {0: accessor}; ordinal += 1
    oracles[ordinal] = {0: accessor}; ordinal += 1
    writes[ordinal] = [(0, 0, payload, 0x00086c04)]; ordinal += 1
    oracles[ordinal] = {0: accessor}; ordinal += 1
    if complete:
        writes[ordinal] = [(1, 0, bytes.fromhex("1122334455667788"),
                            0x00019b54)]
        ordinal += 1
        if mode == 0x60:
            ordinal += 1
            oracles[ordinal] = {0: accessor}; ordinal += 1
        elif mode == 0x70:
            oracles[ordinal] = {0: accessor}; ordinal += 1
            oracles[ordinal] = {0: accessor}; ordinal += 1
        elif mode in (0x30, 0x40):
            oracles[ordinal] = {0: accessor}; ordinal += 1
            oracles[ordinal] = {0: accessor}; ordinal += 1
            oracles[ordinal] = {0: accessor}; ordinal += 1
        elif mode == 0x50:
            oracles[ordinal] = {0: accessor}; ordinal += 1
            oracles[ordinal] = {0: accessor}; ordinal += 1
            oracles[ordinal] = {0: accessor}; ordinal += 1
            oracles[ordinal] = {0: accessor}; ordinal += 1
    oracles[ordinal] = {0: publication}; ordinal += 1
    # Complete transfers publish status through FUN_0007c176.  A return of one
    # also publishes the three exact global status bytes and returns early.
    if complete:
        ordinal += 1
    return (
        {0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1100,
         2: emu.SCRATCH + 0x1200},
        [(emu.SCRATCH + 0x1000, bytes(context)),
         (emu.SCRATCH + 0x1100, bytes(packet)),
         (emu.SCRATCH + 0x1200, bytes(state)),
         (emu.SCRATCH + 0x1300, bytes(0x100)),
         (accessor, bytes(accessor_image)),
         (owned, bytes(owned_image)),
         (0x2000ffa7, bytes(0x158)),
         (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
         (0x20018d99, bytes(3))],
        oracles, writes,
    )


def _ble_dispatch_50_case(kind, backend):
    """Dashboard-lock diagnostics through both logger implementations."""
    packet_length = 5 if kind == "length-mismatch" else 0
    args, memory, oracles = _ble_dispatch_case(
        0x50, packet_length, log_level=3, backend=backend)
    state = bytearray(0x40)
    accessor_first = 0
    if kind == "length-mismatch":
        state[1:3] = (3).to_bytes(2, "little")
    elif kind == "master":
        state[4] = 1
        accessor_first = 1
    elif kind == "action-error":
        state[4] = 2
        accessor_first = 1
    elif kind != "slave-error":
        raise ValueError(kind)
    accessor = emu.SCRATCH + 0x1400
    replaced = []
    for address, data in memory:
        if address == emu.SCRATCH + 0x1200:
            data = bytes(state)
        replaced.append((address, data))
    replaced.extend([
        (accessor, bytes((accessor_first,))),
        (0x20007570, bytes(4)),
        (0x2000756c, (3).to_bytes(4, "little")),
    ])
    return args, replaced, oracles


REVIEWED_ORACLE_CASES = {
    ("app", 0x00085df6): [
        # Direct decode, restart rejected by the preparatory helper, and a
        # successful restart which clears the pending byte and forces -1/0.
        ({0: emu.SCRATCH + 0x1000, 3: 0x12345678},
         [(emu.SCRATCH + 0x1000, bytes(0x20))], {}),
        ({0: emu.SCRATCH + 0x1000, 3: 0x12345678},
         [(emu.SCRATCH + 0x1000, bytes(0x10) + b"\x01" + bytes(0x0f))],
         {0: {0: 0}}),
        ({0: emu.SCRATCH + 0x1000, 3: 0x12345678},
         [(emu.SCRATCH + 0x1000, bytes(0x10) + b"\x01" + bytes(0x0f))],
         {0: {0: 1}}),
    ],
    ("app", 0x00086f00): [
        # First unnamed argument is in r3; the paired object at entry SP owns
        # the exact remaining va-list words passed to either formatter.
        ({0: emu.SCRATCH + 0x1000, 2: 0xffffffff, 3: 0x11223344},
         [(emu.STACK_TOP, bytes.fromhex("01000000020000000300000004000000"))], {}),
        ({0: emu.SCRATCH + 0x1000, 2: 4, 3: 0x11223344},
         [(emu.STACK_TOP, bytes.fromhex("01000000020000000300000004000000"))],
         {0: {0: 0xffffffff}}),
        ({0: emu.SCRATCH + 0x1000, 2: 4, 3: 0x11223344},
         [(emu.STACK_TOP, bytes.fromhex("01000000020000000300000004000000"))],
         {0: {0: 3}}),
        ({0: emu.SCRATCH + 0x1000, 2: 4, 3: 0x11223344},
         [(emu.STACK_TOP, bytes.fromhex("01000000020000000300000004000000")),
          (emu.SCRATCH + 0x2000, bytes(0x54) + (10).to_bytes(4, "little") + bytes(0x28))],
         {0: {0: 4}, 1: {0: 0x55667788, 1: emu.SCRATCH + 0x2000,
                          "lr": (emu.RETURN_MAGIC | 1, 0x00051164)},
          2: {0: 3}}),
        # Zero is part of the nonnegative adjustment arm.  Distinct sentinels
        # at both destinations catch a >0 mutation which would clear bit 12.
        ({0: emu.SCRATCH + 0x1000, 2: 4, 3: 0x11223344},
         [(emu.STACK_TOP, bytes.fromhex("01000000020000000300000004000000")),
          (emu.SCRATCH + 0x2000,
           bytes(0x0c) + (0x1000).to_bytes(2, "little") +
           (7).to_bytes(2, "little", signed=True) + bytes(0x44) +
           (10).to_bytes(4, "little") + bytes(0x28))],
         {0: {0: 4}, 1: {0: 0x55667788, 1: emu.SCRATCH + 0x2000,
                          "lr": (emu.RETURN_MAGIC | 1, 0x00051164)},
          2: {0: 0}}),
        ({0: emu.SCRATCH + 0x1000, 2: 4, 3: 0x11223344},
         [(emu.STACK_TOP, bytes.fromhex("01000000020000000300000004000000")),
          (emu.SCRATCH + 0x2000, bytes(0x0c) + (0xffff).to_bytes(2, "little") +
           (7).to_bytes(2, "little", signed=True) + bytes(0x70))],
         {0: {0: 4}, 1: {0: 0x55667788, 1: emu.SCRATCH + 0x2000,
                          "lr": (emu.RETURN_MAGIC | 1, 0x00051164)},
          2: {0: 0xffffffff}}),
    ],
    ("app", 0x00048ad4): [
        ({}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4))],
         {1: {0: 7}}, {0: [(0, 0, bytes(23), 0x00086c78)]}),
        ({}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4))],
         {1: {0: 0xffffffdd}},
         {0: [(0, 0, bytes(23), 0x00086c78)]}),
        ({}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4))],
         {1: {0: 0}}, {0: [(0, 0, bytes(23), 0x00086c78)]}),
        ({}, [(0x2000230c, (2).to_bytes(4, "little")),
              (0x20007554, bytes(4))],
         {1: {0: 0}}, {0: [(0, 0, bytes(23), 0x00086c78)]}),
        ({}, [(0x2000230c, (3).to_bytes(4, "little")),
              (0x20007554, bytes(4))],
         {1: {0: 0}}, {0: [(0, 0, bytes(23), 0x00086c78)]}),
        ({}, [(0x2000230c, (3).to_bytes(4, "little")),
              (0x20007554, (1).to_bytes(4, "little"))],
         {1: {0: 0}}, {0: [(0, 0, bytes(23), 0x00086c78)]}),
    ],
    ("app", 0x0004ab3c): [
        ({}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4)),
              (emu.SCRATCH + 0x2000, bytes(0x1200))],
         {0: {0: emu.SCRATCH + 0x2000}, 2: {0: emu.SCRATCH + 0x2000}}),
        ({}, [(0x2000230c, (2).to_bytes(4, "little")),
              (0x20007554, bytes(4)),
              (emu.SCRATCH + 0x2000, bytes(0x1200))],
         {0: {0: emu.SCRATCH + 0x2000}, 2: {0: emu.SCRATCH + 0x2000}}),
        ({}, [(0x2000230c, (3).to_bytes(4, "little")),
              (0x20007554, bytes(4)), (emu.SCRATCH + 0x2000, bytes(0x1200))],
         {1: {0: emu.SCRATCH + 0x2000}, 3: {0: emu.SCRATCH + 0x2000}}),
        ({}, [(0x2000230c, (3).to_bytes(4, "little")),
              (0x20007554, (1).to_bytes(4, "little")),
              (emu.SCRATCH + 0x2000, bytes(0x1200))],
         {1: {0: emu.SCRATCH + 0x2000}, 3: {0: emu.SCRATCH + 0x2000}}),
    ],
    ("app", 0x00023c88): [
        ({}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4))], {0: {0: 7}}),
        ({}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4))],
         {0: {0: 0xffffffdd}}),
        ({}, [(0x2000230c, (1).to_bytes(4, "little")),
              (0x20007554, bytes(4))], {0: {0: 7}}),
        ({}, [(0x2000230c, (1).to_bytes(4, "little")),
              (0x20007554, (1).to_bytes(4, "little"))], {0: {0: 7}}),
        ({}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4))], {0: {0: 0}}),
        ({}, [(0x2000230c, (2).to_bytes(4, "little")),
              (0x20007554, bytes(4))], {0: {0: 0}}),
        ({}, [(0x2000230c, (3).to_bytes(4, "little")),
              (0x20007554, bytes(4))], {0: {0: 0}}),
        ({}, [(0x2000230c, (3).to_bytes(4, "little")),
              (0x20007554, (1).to_bytes(4, "little"))], {0: {0: 0}}),
    ],
    ("app", 0x00073d1c): [
        _app_73d1c_case(kind) for kind in (
            "already", "forbidden", "empty", "empty-ready",
            "head", "append", "middle", "equal",
        )
    ],
    ("app", 0x000757b0): [
        _app_757b0_case(kind) for kind in (
            "lock-fail", "self-unlock-fail", "self-success", "linked",
        )
    ],
    ("app", 0x00079780): [
        _app_79780_case(False),
        _app_79780_case(True),
    ],
    # One real group-0 IRQ bit.  The reviewed W1C controller transition is
    # applied only when the second FUN_00065620 boundary is reached.
    ("app", 0x00065b9c): [
        ({},
         [(0x50842520, (1).to_bytes(4, "little")),
          (0x50842820, bytes(4)),
          (0x20002bd0, (0x1c).to_bytes(2, "little")),
          (emu.SCRATCH + 0x2200, bytes(0x300))],
         {0: {0: 0x80000001}, 1: {0: 0, 1: 0},
          2: {0: emu.SCRATCH + 0x2200}, 3: {0: 0},
          4: {0: emu.SCRATCH + 0x2200}, 5: {0: 0}, 6: {0: 0},
          7: {0: emu.SCRATCH + 0x2200}, 8: {0: 0}},
         {8: [(None, 0x50842520, bytes(4), 0x00065620),
              (None, 0x50842820, bytes(4), 0x00065620)]}),
        # Non-IRQ mask path independently exercises the peripheral-slot loop.
        ({}, [(0x5000d304, bytes(4))], {0: {0: 3}}),
    ],
    # Coherent callback state for all event-query families and callback/no-call
    # publication decisions.
    ("app", 0x00067600): [
        ({0: emu.SCRATCH + 0x3000, 1: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           (0x00070001).to_bytes(4, "little") +
           (0x11223344).to_bytes(4, "little") + bytes(4) * 5 +
           bytes(4) + bytes((0, 0, 0, 0, 0, 1))),
          (emu.SCRATCH + 0x3000, bytes(0x600))],
         oracles)
        for oracles in (
            {0: {0: 0}, 1: {0: 1}, 2: {0: 0}},
            {0: {0: 0}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0}},
            {0: {0: 1}, 1: {0: 0}, 2: {0: 0}},
            {0: {0: 1}, 1: {0: 1}, 2: {0: 0}},
        )
    ] + [
        # IRQ field 0x80 sign-extends negative, so clear-state must not touch
        # NVIC ICPR. This independently guards the defined unsigned-then-signed
        # extraction used by the readable C.
        ({0: 0x20080000, 1: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           (0x00070001).to_bytes(4, "little") +
           (0x11223344).to_bytes(4, "little") + bytes(4) * 6 +
           bytes((0, 0, 0, 0, 0, 0))),
          (0x20080000, bytes(0x600))],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0}}),
    ],
    # Nonzero interpolation count: 16-sample collapse, overlap-safe copy, 48
    # polynomial iterations, and one bounded output sample.
    ("app", 0x0006bfc8): [
        ({0: 0, 1: 0, 2: emu.SCRATCH + 0x1000, 3: mode},
         [(emu.SCRATCH + 0x1000,
           b"".join(struct.pack("<f", float(i) / 32.0) for i in range(16))),
          (emu.SCRATCH + 0x3000, struct.pack("<f", 0.75) + bytes(0xfc)),
          (emu.SCRATCH + 0x4000, bytes(0x100)),
          (0x00090c50, (b"\x01\x00\x00\x00" * 48) + bytes(0x40) +
           (48).to_bytes(4, "little")),
          (emu.STACK_TOP, (emu.SCRATCH + 0x3000).to_bytes(4, "little")),
          (emu.STACK_TOP + 4, (emu.SCRATCH + 0x4000).to_bytes(4, "little"))],
         {0: {0: 0}})
        for mode in (0, 1)
    ],
    # Exact event, queued, and compact-handle record forms, including fatal 4.
    ("app", 0x00071684): [
        ({0: event, 1: context},
         [(emu.SCRATCH + 0x1000, bytes(0x1c) +
           ((1).to_bytes(4, "little") if context else bytes(4))),
          (emu.SCRATCH + 0x3000, b"worker-name\0")],
         ({0: {0: 7}, 2 + (1 if context else 0): {0: emu.SCRATCH + 0x3000}}))
        for event, context in ((0, 0), (1, emu.SCRATCH + 0x1000), (4, 0))
    ],
    # Production queue handoff.  FUN_00073f6c's two stack words are now part
    # of the call event, so successor/value corruption is directly observable.
    ("app", 0x000723b8): [
        ({0: emu.SCRATCH + 0x1000, 1: 0,
          2: emu.SCRATCH + 0x4000, 3: 0x12345678},
         [(emu.SCRATCH + 0x1000,
           (emu.SCRATCH + 0x1800).to_bytes(4, "little") + bytes(4) +
           (emu.SCRATCH + 0x3000).to_bytes(4, "little") +
           (1).to_bytes(4, "little") + (5).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1800, bytes(14) + b"\x04" + bytes(17)),
          (emu.SCRATCH + 0x2000, bytes(14) + b"\x03" + bytes(17)),
          (emu.SCRATCH + 0x3000, bytes(14) + b"\x05" + bytes(17)),
          (0x2000b450, (emu.SCRATCH + 0x2000).to_bytes(4, "little"))],
         {0: {0: 1}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0}}),
    ],
    # Lock assertion, lookup miss, and lookup hit are all distinct outcomes.
    ("app", 0x00072880): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(0x30))], {0: {0: 0}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(8) + (2).to_bytes(4, "little") +
           (3).to_bytes(4, "little") + bytes(0x20))],
         {0: {0: 1}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0}, 4: {0: 0}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(0x30)),
          (emu.SCRATCH + 0x3000, bytes(0xa0))],
         {0: {0: 1}, 1: {0: 0}, 2: {0: emu.SCRATCH + 0x3000},
          3: {0: 0}, 4: {0: 0}}),
    ],
    ("app", 0x00021460): [
        _ble_dispatch_case(command) for command in (
            0x01, 0x20, 0x27, 0x28, 0x29, 0x35, 0x45, 0x46, 0x00,
            0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50,
            0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
        )
    ] + [
        _ble_dispatch_copy_case(command, length)
        for command, length in ((0x4a, 6), (0x4c, 9), (0x4f, 12))
    ] + [
        _ble_dispatch_4e_case(count, index, mode, publication)
        for count, index, mode, publication in (
            (3, 1, 0x30, 0),       # incomplete, response status 0xcb
            (2, 1, 0x30, 0),       # complete, mode 0x30, publish false
            (2, 1, 0x40, 1),       # complete, mode 0x40 + global publication
            (2, 1, 0x50, 0),       # complete, mode 0x50
            (2, 1, 0x60, 0),       # complete, mode 0x60
            (2, 1, 0x70, 0),       # complete, mode 0x70
            (1, 0, 0x30, 0),       # first/final segment initialization
        )
    ] + [
        # State six takes a separate nested mode arm from the existing
        # state-eight fixtures. Modes 30/40 cover its normal transitions;
        # mode 50 distinguishes the state==6 predicate from the >6 arm.
        _ble_dispatch_4e_case(2, 1, mode, 0, owned_state=6)
        for mode in (0x30, 0x40, 0x50)
    ] + [
        # Every in-range diagnostic site through direct and buffered sinks.
        _ble_dispatch_case(command, log_level=level, backend=backend)
        for command, level in ((0x47, 2), (0x48, 2))
        for backend in (0, 1)
    ] + [
        _ble_dispatch_copy_case(0x4c, 9, log_level=3, backend=backend)
        for backend in (0, 1)
    ] + [
        # Level two is the exact suppression boundary for the 0x4c diagnostic.
        _ble_dispatch_copy_case(0x4c, 9, log_level=2, backend=0)
    ] + [
        _ble_dispatch_50_case(kind, backend)
        for kind in ("length-mismatch", "master", "action-error",
                     "slave-error")
        for backend in (0, 1)
    ] + [
        _ble_dispatch_case(0xf1, log_level=2, backend=0),
        _ble_dispatch_case(0xf1, log_level=2, backend=1),
        _ble_dispatch_case(0x00, log_level=1, backend=0),
        _ble_dispatch_case(0x00, log_level=1, backend=1),
    ],
    ("net", 0x0102fbd0): [
        _net_mode_update_case(mode, allocated)
        for mode, allocated in ((1, True), (3, True), (5, True),
                                (1, False), (0, False), (2, False),
                                (4, False), (6, False))
    ],
    ("net", 0x01030bac): [
        _net_controller_log_case(),
        _net_controller_log_case(0x0004, 0x8000),
        _net_controller_log_case(0x10002, 0x20001),
        _net_controller_log_case(0xffff, 0x10000),
        _net_controller_log_case(0x10000, 0xffff),
    ],
    ("net", 0x0103566c): [
        _net_packet_drain_case(kind)
        for kind in ("inactive", "empty", "positive", "unsigned-halfword",
                     "wrap-state", "callback-positive", "retry", "fatal")
    ],
    ("net", 0x010359b8): [
        *[_net_event_dispatch_case(mode) for mode in range(5)],
        _net_event_dispatch_case(5),
        _net_event_dispatch_case(2, queued=True),
        _net_event_dispatch_case(2, context_zero=True),
        _net_event_dispatch_case(2, handle=0x1234, name_kind="valid"),
        _net_event_dispatch_case(2, handle=0x1234, name_kind="empty"),
        _net_event_dispatch_case(2, handle=0x1234, name_kind="fallback"),
        _net_event_dispatch_case(2, handle=0x4321, name_kind="valid",
                                 slot_offset=4),
    ],
    ("net", 0x01037398): [_net_ready_list_case("empty"),
                           _net_ready_list_case("ordered"),
                           _net_ready_list_case("remove-insert"),
                           _net_ready_list_case("equal"),
                           _net_ready_list_case("append"),
                           _net_ready_list_case("multi"),
                           _net_ready_list_case("negative"),
                           _net_ready_list_case("reserved")],
    ("net", 0x01037768): [
        _net_ready_enqueue_case(kind)
        for kind in ("other", "current", "linked", "linked-other",
                     "lock-fail", "unlock-fail")
    ],
    ("net", 0x0103601c): [_net_runtime_table_case(0xffffffff),
                           _net_runtime_table_case(0),
                           _net_runtime_table_case(1),
                           _net_runtime_table_case(0xfffffffe),
                           _net_runtime_table_case(0x20000)],
    ("net", 0x0102bbec): [_net_format_layout_case(b"\0"),
                           _net_format_layout_case(b"%d\0"),
                           _net_format_layout_case(b"%a\0"),
                           _net_format_layout_case(b"%e\0"),
                           _net_format_layout_case(b"%f\0"),
                           _net_format_layout_case(b"%g\0"),
                           _net_format_layout_case(b"%lld\0"),
                           _net_format_layout_case(b"%s\0"),
                           _net_format_layout_case(b"%p\0"),
                           _net_format_layout_case(b"%#08x\0"),
                           _net_format_layout_case(b"%d\0", flags=4),
                           _net_format_layout_case(b"\0", True),
                           _net_format_sizing_case(b"\0"),
                           _net_format_sizing_case(b"%d\0", alignment=7),
                           _net_format_sizing_case(b"%e\0", alignment=7),
                           _net_format_capacity_case(7),
                           _net_format_capacity_case(8)],
    ("app", 0x00012db0): [
        # Exact adjacent positive/negative reducer tables.  Without mapped
        # data, both runners lazily read zeros and a wrong base/index can pass.
        ({}, [(0x00088848, bytes.fromhex(
            "763c7935ef39ea3d763c7935ef39eabd"
            "0000e0fe422ee63f0000e0fe422ee6bf"
            "000000000000e03f000000000000e0bf"))], {})
        for _ in range(13)
    ],
    ("app", 0x00060c00): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(4) + (emu.SCRATCH + 0x1100).to_bytes(4, "little") + bytes(8) + (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1100, bytes(0x40))], {0: {0: 0xffffffff}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(4) + (emu.SCRATCH + 0x1100).to_bytes(4, "little") + bytes(8) + (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1100, bytes(0x40))],
         {0: {0: 0}, 2: {0: 0x0bad3000}, 3: {0: 0xffffffef}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(4) + (emu.SCRATCH + 0x1100).to_bytes(4, "little") + bytes(8) + (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1100, bytes(0x40))],
         {0: {0: 0}, 2: {0: 0x0bad3000}, 3: {0: 0}, 4: {0: 0}, 5: {0: 0xfffffff5}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(4) + (emu.SCRATCH + 0x1100).to_bytes(4, "little") + bytes(8) + (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1100, bytes(0x40))],
         {0: {0: 0}, 2: {0: 0x0bad3000}, 3: {0: 0}, 4: {0: 0}, 5: {0: 0}, 7: {0: 1}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(4) + (emu.SCRATCH + 0x1100).to_bytes(4, "little") + bytes(8) + (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1100, bytes(0x30) + b"\x11\x22\x33" + bytes(0x0d))],
         {0: {0: 0}, 2: {0: 0x0bad3000}, 3: {0: 0}, 4: {0: 0}, 5: {0: 0x40}, 6: {0: 0}, 7: {0: 0}, 9: {0: 0}, 10: {0: 0}, 12: {0: 0}},
         {10: [(1, -12, b"\x11\x22\x33", 0x00060ab0)]}),
        # Exact mismatch path: the response producer writes three differing
        # bytes, memcmp reports nonzero, and logger ordinal thirteen consumes
        # the fully initialized eight-field diagnostic.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(4) + (emu.SCRATCH + 0x1100).to_bytes(4, "little") + bytes(8) + (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1100, bytes(0x30) + b"\x11\x22\x33" + bytes(0x0d))],
         {0: {0: 0}, 2: {0: 0x0bad3000}, 3: {0: 0}, 4: {0: 0}, 5: {0: 0x40}, 6: {0: 0}, 7: {0: 0}, 9: {0: 0}, 10: {0: 0}, 12: {0: 1}},
         {10: [(1, -12, b"\xaa\xbb\xcc", 0x00060ab0)]}),
        # Expected-state true (configuration mode 2) with a clear status bit
        # forces the transition command; its failure selects the true-state
        # diagnostic string in the exact eighteen-byte record.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (emu.SCRATCH + 0x1100).to_bytes(4, "little") +
           bytes(8) + (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1100, bytes(0x1d) + b"\x02" + bytes(0x22))],
         {0: {0: 0}, 2: {0: 0x0bad3000}, 3: {0: 0}, 4: {0: 0},
          5: {0: 0}, 6: {0: 0xfffffffb}}),
        # The alternate configuration selector at +0x1c independently drives
        # the same true-state transition and diagnostic family.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (emu.SCRATCH + 0x1100).to_bytes(4, "little") +
           bytes(8) + (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1100, bytes(0x1c) + b"\x03" + bytes(0x23))],
         {0: {0: 0}, 2: {0: 0x0bad3000}, 3: {0: 0}, 4: {0: 0},
          5: {0: 0}, 6: {0: 0xfffffffb}}),
    ],
    ("app", 0x000167f4): [
        _app_167f4_status_case(-1),
        _app_167f4_status_case(0),
    ],
    ("app", 0x00017eec): [
        _app_17eec_case(False, False, 0),
        _app_17eec_case(True, False, 0),
        _app_17eec_case(True, True, 7),
    ],
    ("app", 0x00024534): [
        # Unclamped and boundary-clamped successful copies, callback failure,
        # and invalid headers through both logger implementations.  The fifth
        # stack argument is paired with these cases above.
        _app_24534_case(0, 0x28, 1, False, 0, "valid"),
        _app_24534_case(3, 0x2a, 1, False, 0, "valid"),
        _app_24534_case(0, 0x10, 1, False, 1, "callback-fail"),
        _app_24534_case(1, 0x10, 3, False, 0, "invalid"),
        _app_24534_case(2, 0x10, 3, True, 0, "invalid"),
        _app_24534_range_case(False),
        _app_24534_range_case(True),
        _app_24534_not_ready_case(False),
        _app_24534_not_ready_case(True),
    ],
    ("app", 0x00078110): [
        _numeric_parse_case("early-six"),
        _numeric_parse_case("early-zero"),
        _numeric_parse_case("decimal-exp-positive"),
        _numeric_parse_case("decimal-exp-negative"),
        _numeric_parse_case("uppercase-exponent"),
        _numeric_parse_case("unsigned-exponent"),
        _numeric_parse_case("multidigit-exponent"),
        _numeric_parse_case("multibyte-locale"),
        _numeric_parse_case("multi-limb"),
        _numeric_parse_case("left-shift"),
        _numeric_parse_case("initial-allocation-fatal"),
        _numeric_parse_case("overflow"),
        _numeric_parse_case("underflow-reject"),
        _numeric_parse_case("underflow-minimum"),
        _numeric_parse_case("round-even-down"),
        _numeric_parse_case("round-even-up"),
        _numeric_parse_case("round-directed"),
        _numeric_parse_case("round-mode2-zero"),
        _numeric_parse_case("round-mode2-one"),
        _numeric_parse_case("carry-expand-success"),
        _numeric_parse_case("carry-expand-fatal"),
    ],
    ("app", 0x00084c94): [
        # Negative status leaves the completion byte unchanged.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (emu.SCRATCH + 0x1100).to_bytes(4, "little") +
           bytes(8) + (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1100, (0x12345678).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1200, b"\xa5")],
         {0: {0: 0xffffffff}}),
        # Nonnegative status publishes completion by clearing the target byte.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (emu.SCRATCH + 0x1100).to_bytes(4, "little") +
           bytes(8) + (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1100, (0x12345678).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1200, b"\xa5")],
         {0: {0: 0}}),
    ],
    ("net", 0x010195f8): [_net_controller_reset_case()],
    ("app", 0x0004e124): [
        _property_update_case(5),
        _property_update_case(0, selected=4, current=4),
        _property_update_case(0, selected=6, current=4, callback_result=0),
        _property_update_case(0, selected=6, current=4, callback_result=7),
    ],
    # Disabled/null, both primary result arms, both callback length families,
    # secondary mismatch, and both secondary callback outcomes.
    ("app", 0x00052d58): [
        _settings_dispatch_case(0),
        _settings_dispatch_case(1, null_input=True),
        _settings_dispatch_case(9, primary=0),
        _settings_dispatch_case(1, primary=0, callback_result=5),
        _settings_dispatch_case(1, primary=0, callback_result=14),
        _settings_dispatch_case(1, primary=1, secondary=1),
        _settings_dispatch_case(1, primary=1, secondary=0,
                                callback_result=-1),
        _settings_dispatch_case(1, primary=1, secondary=0,
                                callback_result=3),
    ],
    ("app", 0x0007712c): [
        _float_format_special_case(0, 0x7ff00000),
        _float_format_special_case(0, 0xfff00000),
        _float_format_special_case(1, 0x7ff80000, nan_case=True),
        _float_format_special_case(0, 0x7ff00000, conversion="G"),
        _float_format_special_case(1, 0x7ff80000, nan_case=True,
                                   conversion="G"),
        _float_format_finite_case("e", 2, 3, "125"),
        _float_format_finite_case("E", 3, 2, "1250"),
        _float_format_finite_case("f", 2, 1, "125"),
        _float_format_finite_case("g", 4, 1, "1250"),
        _float_format_finite_case("G", 4, 8, "1250"),
        # Negative decimal position drives leading-zero digit loops; width and
        # left/right padding are exercised with and without alternate form.
        _float_format_finite_case("f", 3, -2, "125", width=9, flags=2),
        _float_format_finite_case("g", 3, -1, "125", width=8, flags=1),
        # The first direct output callback fails after successful dtoa/width
        # setup, proving the immediate -1 propagation exit.
        _float_format_finite_case("e", 2, 2, "125", fail_callback=True),
        # Actual hard-float values and dtoa sign output: positive/negative
        # zero exercise the zero comparator, while -1.25 proves finite sign.
        _float_format_finite_case(
            "f", 2, 1, "0", value_low=0, value_high=0, zero_result=1),
        _float_format_finite_case(
            "f", 2, 1, "0", value_low=0, value_high=0x80000000,
            sign=1, zero_result=1),
        _float_format_finite_case(
            "f", 2, 1, "125", value_low=0, value_high=0xbff40000,
            sign=1),
        # Precision normalization occurs before dtoa: unspecified becomes six,
        # and g/G precision zero becomes one.
        _float_format_finite_case("f", 0xffffffff, 1, "125000"),
        _float_format_finite_case("g", 0, 1, "1"),
        # Exact g thresholds: -3 stays fixed, -4 becomes scientific; decimal
        # position equal to precision stays fixed, one greater is scientific.
        _float_format_finite_case("g", 4, -3, "1250"),
        _float_format_finite_case("g", 4, -4, "1250"),
        _float_format_finite_case("g", 4, 4, "1250"),
        _float_format_finite_case("g", 4, 5, "1250"),
        # Ordinary width policy complements the flag-2 right-padding case.
        _float_format_finite_case("f", 3, -2, "125", width=9, flags=0),
        # Fail inside the leading-zero work and late in the final padding run,
        # rather than only at the first direct callback.
        _float_format_finite_case(
            "f", 3, -2, "125", width=9, flags=2,
            fail_callback=True, fail_callback_offset=4),
        _float_format_finite_case(
            "f", 3, -2, "125", width=9, flags=2,
            fail_callback=True, fail_callback_offset=9),
        # AAPCS double cursor alignment is observable: the cursor begins four
        # bytes off an eight-byte boundary, skips sentinels, consumes the
        # double at +8, and advances to +16.
        _float_format_finite_case(
            "f", 2, 1, "125", value_cursor_offset=4),
        # Width setup failure returns immediately without any output callback.
        _float_format_finite_case(
            "f", 2, 1, "125", width_result=0xffffffff),
    ],
    ("app", 0x0005ffa4): [
        # Empty notification with no pending payload exits without helpers.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(8)), (0x2000b008, bytes(0x60))], {}),
        # A valid response is decoded to the expected controller magic and
        # needs no recovery transition when there is no pending payload.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, b"\x01\0\0\0" + bytes(4)),
          (0x2000b008, bytes(0x60))],
         {0: {0: 0}, 1: {0: 0x0bad0000}},
         {0: [(1, 0, (0x1234).to_bytes(4, "little"))]}),
        # Decode failure exercises the structured diagnostic and the
        # production recovery flag/wakeup path.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, b"\x01\0\0\0" + bytes(4)),
          (0x2000b008, bytes(0x60))],
         {0: {0: 0xffffffff}}),
        # A pending payload with no active state runs the four-argument
        # transfer helper; its failure logs, releases the controller using the
        # payload value, and raises the recovery event.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (0x44556677).to_bytes(4, "little")),
          (0x2000b008, bytes(0x60))],
         {0: {0: 0xffffffff}}),
        # Active state with no payload clears the pending marker and releases
        # the owning handle when bit zero requests that cleanup.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(8)),
          (0x2000b008,
           (0x11223344).to_bytes(4, "little") + bytes(0x4c) +
           b"\x01\x01\x01" + bytes(0x0d))], {}),
        # Transfer success leaves recovery inactive and does not release the
        # controller or emit a diagnostic.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (0x44556677).to_bytes(4, "little")),
          (0x2000b008, bytes(0x60))], {0: {0: 0}}),
        # Active response failure with no payload performs pending cleanup and
        # then wakes recovery.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, b"\x01\0\0\0" + bytes(4)),
          (0x2000b008,
           (0x11223344).to_bytes(4, "little") + bytes(0x4c) +
           b"\x01\x01\x01" + bytes(0x0d))], {0: {0: 0xffffffff}}),
    ],
    ("app", 0x0005c8d8): [
        # Failure at each of the two admission gates.
        ({0: 1, 1: 0x22, 2: 0x33}, [], {1: {0: 0xffffffff}}),
        ({0: 1, 1: 0x22, 2: 0x33}, [],
         {1: {0: 0}, 2: {0: 0xffffffff}}),
        # Successful setup with no matching owner among all three slots.
        ({0: 1, 1: 0x22, 2: 0x33},
         [(0x2000af18, bytes(0x30))],
         {1: {0: 0}, 2: {0: 0}, 3: {0: 1}, 5: {0: 0}}),
        # First-slot match and a one-element queued chain exercise both cleanup
        # calls and the halfword state clears.
        ({0: 1, 1: 0x22, 2: 0x33},
         [(0x2000af18,
           bytes((1,)) + bytes(7) +
           (emu.SCRATCH + 0x5000).to_bytes(4, "little") + bytes(0x24)),
          (emu.SCRATCH + 0x5000,
           (emu.SCRATCH + 0x5118).to_bytes(4, "little") + bytes(0x40)),
         (emu.SCRATCH + 0x5100, bytes(0x40))],
         {1: {0: 0}, 2: {0: 0}, 3: {0: 1}, 5: {0: 0}, 6: {0: 1}}),
        # A zero return from FUN_00059b5c must skip FUN_0005a39c; the second
        # admission check becomes ordinal four and all slots miss.
        ({0: 1, 1: 0x22, 2: 0x33},
         [(0x2000af18, bytes(0x30))],
         {1: {0: 0}, 2: {0: 0}, 3: {0: 0}, 4: {0: 0}}),
        # Matching owners in the second and third slots prove the scan is not
        # accidentally truncated to slot zero.  Their null chains exercise the
        # clean break after a successful comparator without cleanup calls.
        ({0: 1, 1: 0x22, 2: 0x33},
         [(0x2000af18, bytes(0x10) + b"\x01" + bytes(0x1f))],
         {1: {0: 0}, 2: {0: 0}, 3: {0: 0}, 4: {0: 0}, 5: {0: 1}}),
        ({0: 1, 1: 0x22, 2: 0x33},
         [(0x2000af18, bytes(0x20) + b"\x01" + bytes(0x0f))],
         {1: {0: 0}, 2: {0: 0}, 3: {0: 0}, 4: {0: 0}, 5: {0: 1}}),
        # First-slot owner with three linked queued nodes.  Each +0x18 link
        # points to the next node's embedded-list address; the third node makes
        # repeated traversal distinguishable from a single conditional step.
        ({0: 1, 1: 0x22, 2: 0x33},
         [(0x2000af18,
           bytes((1,)) + bytes(7) +
           (emu.SCRATCH + 0x5000).to_bytes(4, "little") + bytes(0x24)),
          (emu.SCRATCH + 0x5000,
           (emu.SCRATCH + 0x5118).to_bytes(4, "little") + bytes(0x40)),
          (emu.SCRATCH + 0x5100,
           bytes(0x18) + (emu.SCRATCH + 0x5218).to_bytes(4, "little") +
           bytes(0x24)),
          (emu.SCRATCH + 0x5200,
           bytes(0x18) + (emu.SCRATCH + 0x5318).to_bytes(4, "little") +
           bytes(0x24)),
          (emu.SCRATCH + 0x5300, bytes(0x40))],
         {1: {0: 0}, 2: {0: 0}, 3: {0: 1}, 5: {0: 0}, 6: {0: 1}}),
    ],
    ("net", 0x01010834): [
        _net_queue_remove_case(0, 0),
        _net_queue_remove_case(1, 1),
        _net_queue_remove_case(1, 3),
    ],
    ("net", 0x01039972): [
        _net_list_insert_case(kind) for kind in ("early", "empty", "occupied")
    ],
    ("net", 0x0101132c): [
        _net_init_case(kind) for kind in
        ("early", "baseline", "timestamp", "random", "iterator",
         "iterator-retry")
    ],
    ("net", 0x01039190): [
        _net_printf_case(b"abc"),
        _net_printf_case(b"%%"),
        _net_printf_case(b"%-5s", (emu.SCRATCH + 0x1300,), b"hi", 2),
        _net_printf_case(b"%c", (ord("Z"),)),
        _net_printf_case(b"%.3s", (emu.SCRATCH + 0x1300,), b"hello", 3),
        _net_printf_case(b"%q"),
    ],
    ("net", 0x010162e0): [
        _net_packet_case(2), _net_packet_case(3), _net_packet_case(5),
        _net_packet_case(2, alternate=True),
        _net_packet_case(5, alternate=True),
        _net_packet_case(2, fallback=True),
    ],
    ("net", 0x01017344): [
        _net_record_case(kind) for kind in
        ("simple", "reject", "cleanup", "cleanup-reset", "cb-equal",
         "cb-ff", "radio", "special-header-false", "special-ff",
         "special-ca-zero", "special-aaac-ok", "special-aaac-fail")
    ],
    # The first two fixtures are deliberately thread/IRQ respectively because
    # verify() applies [0,16] xPSR to the first two MRS-IPSR cases.  Remaining
    # cases cover argument panics, completed work, zero timeout and wait/relock.
    ("net", 0x01038764): [
        _net_scheduler_case(kind) for kind in
        ("completed", "irq", "null", "priority", "immediate", "wait",
         "high-only",
         "lock-fail", "completed-release-fail",
         "immediate-release-fail", "wait-relock-fail",
         "wait-release-fail")
    ],
    ("net", 0x0101e6ac): [
        _net_radio_init_case(),
        _net_radio_init_case(timestamp=True),
        _net_radio_init_case(descriptor=True),
        _net_radio_init_case(error=True),
        _net_radio_init_case(threshold=True),
        _net_radio_init_case(callback=True, final_time=1),
        _net_radio_init_case(alternate_mode=True),
    ],
    ("app", 0x0002c714): [
        _app_2c714_case("wait-break", buffered=False),
        _app_2c714_case("wait-delay", buffered=False),
        _app_2c714_case("state-0", buffered=False),
        _app_2c714_case("state-1", buffered=True),
        _app_2c714_case("state-2", buffered=False),
        _app_2c714_case("timeout", buffered=False),
        _app_2c714_case("state-6", buffered=True),
        _app_2c714_case("state-6-decrement", buffered=False),
    ],
    ("app", 0x00032308): [
        _app_32308_case("invalid-length"),
        _app_32308_case("current"),
        _app_32308_case("unsupported", buffered=False),
        _app_32308_case("unsupported", buffered=True),
        _app_32308_poll_case(success=True),
        _app_32308_poll_case(success=False),
    ],
    ("app", 0x00032b24): [
        _app_32b24_dispatch_case(hit=True),
        _app_32b24_dispatch_case(hit=False),
        _app_32b24_dispatch_case(hit=True, mode=1),
        _app_32b24_dispatch_case(hit=False, mode=1),
        # Callback failure is deliberately ignored; final publication still
        # determines the function result.  The last case proves -4 mapping.
        _app_32b24_dispatch_case(hit=True, callback_result=-1),
        _app_32b24_dispatch_case(hit=True, final_result=1),
        _app_32b24_invalid_case(mode=2),
        _app_32b24_dispatch_case(hit=False, null_request=True),
    ],
    ("app", 0x00064a88): [
        # Initial allocation failure.
        ({0: 0x1234, 1: 0x5678},
         [(0x20002bac,
           (0x00080001).to_bytes(4, "little") +
           (0x00081001).to_bytes(4, "little") + bytes(4))],
         {1: {0: 0}}),
        # No resize callback: allocate/copy/terminate/release fallback.
        ({0: 0x1234, 1: 0x5678},
         [(0x20002bac,
           (0x00080001).to_bytes(4, "little") +
           (0x00081001).to_bytes(4, "little") + bytes(4))],
         {1: {0: emu.SCRATCH + 0x6000}, 2: {0: 1},
          4: {0: emu.SCRATCH + 0x7000}}),
        # Resize callback owns successful result publication.
        ({0: 0x1234, 1: 0x5678},
         [(0x20002bac,
           (0x00080001).to_bytes(4, "little") +
           (0x00081001).to_bytes(4, "little") +
           (0x00082001).to_bytes(4, "little"))],
         {1: {0: emu.SCRATCH + 0x6000}, 2: {0: 1},
          4: {0: emu.SCRATCH + 0x7000}}),
        # Encoder rejection releases the initial allocation without finalize,
        # resize, fallback allocation, or publication.
        ({0: 0x1234, 1: 0x5678},
         [(0x20002bac,
           (0x00080001).to_bytes(4, "little") +
           (0x00081001).to_bytes(4, "little") + bytes(4))],
         {1: {0: emu.SCRATCH + 0x6000}, 2: {0: 0}}),
        # Resize failure falls through to release of the original allocation.
        ({0: 0x1234, 1: 0x5678},
         [(0x20002bac,
           (0x00080001).to_bytes(4, "little") +
           (0x00081001).to_bytes(4, "little") +
           (0x00082001).to_bytes(4, "little"))],
         {1: {0: emu.SCRATCH + 0x6000}, 2: {0: 1}, 4: {0: 0}}),
        # Nonzero length below capacity: copy length+1 bytes and terminate at
        # the exact encoded length, independently of the copied NUL byte.
        ({0: 0x1234, 1: 0x5678},
         [(0x20002bac,
           (0x00080001).to_bytes(4, "little") +
           (0x00081001).to_bytes(4, "little") + bytes(4))],
         {1: {0: emu.SCRATCH + 0x6000}, 2: {0: 1},
          4: {0: emu.SCRATCH + 0x7000}},
         {2: [(1, 8, (10).to_bytes(4, "little"), 0x000646c0)]}),
        # Length above capacity clamps the copy to 0x100 while retaining the
        # exact terminator position at result+length.
        ({0: 0x1234, 1: 0x5678},
         [(0x20002bac,
           (0x00080001).to_bytes(4, "little") +
           (0x00081001).to_bytes(4, "little") + bytes(4))],
         {1: {0: emu.SCRATCH + 0x6000}, 2: {0: 1},
          4: {0: emu.SCRATCH + 0x7000}},
         {2: [(1, 8, (300).to_bytes(4, "little"), 0x000646c0)]}),
        # Without resize support, fallback allocation failure likewise releases
        # the original buffer and returns null.
        ({0: 0x1234, 1: 0x5678},
         [(0x20002bac,
           (0x00080001).to_bytes(4, "little") +
           (0x00081001).to_bytes(4, "little") + bytes(4))],
         {1: {0: emu.SCRATCH + 0x6000}, 2: {0: 1}, 4: {0: 0}}),
    ],
    # Cover both the absent lookup result and the fully initialized log-record
    # publication path.
    ("app", 0x00052f68): [
        ({}, [], {0: {0: 0}}),
        ({}, [], {0: {0: 1}}),
    ],
    ("app", 0x00022834): [
        _flash_read_case(False),
        _flash_read_case(True),
    ],
    ("app", 0x0004bc8c): [
        _mpsc_alloc_case(kind)
        for kind in ("reject", "allocate", "wrap", "drop", "timeout",
                     "timeout-error", "mode-drop", "drop-publish")
    ],
    ("app", 0x0004d100): [
        ({0: 0, 1: 0, 2: emu.SCRATCH, 3: 0},
         [(emu.STACK_TOP, bytes(16))], {}),
        # The two mandatory inputs are independent guards.  Keeping the other
        # nonzero prevents either check from being hidden by short-circuiting.
        ({0: 0, 1: 0, 2: emu.SCRATCH, 3: 0},
         [(emu.STACK_TOP, (11).to_bytes(4, "little") +
          (emu.SCRATCH + 0x2000).to_bytes(4, "little") +
          (13).to_bytes(4, "little") + bytes(4))], {}),
        ({0: emu.SCRATCH, 1: 0, 2: emu.SCRATCH + 0x1000, 3: 7},
         [(emu.SCRATCH, bytes(0x300)),
          (emu.STACK_TOP, (11).to_bytes(4, "little") + bytes(4) +
           (13).to_bytes(4, "little") + bytes(4))], {}),
        ({0: emu.SCRATCH, 1: 0, 2: emu.SCRATCH + 0x1000, 3: 7},
         [(emu.SCRATCH, bytes(0x300)), (emu.STACK_TOP, bytes(16))], {}),
        ({0: emu.SCRATCH, 1: 1, 2: emu.SCRATCH + 0x1000, 3: 7},
         [(emu.SCRATCH, bytes(0x300)),
          (emu.STACK_TOP, (11).to_bytes(4, "little") +
           (emu.SCRATCH + 0x2000).to_bytes(4, "little") +
           (13).to_bytes(4, "little") + bytes(4))], {}),
        ({0: emu.SCRATCH, 1: 0, 2: emu.SCRATCH + 0x1000, 3: 7},
         [(emu.SCRATCH, bytes(0x300)),
          (emu.STACK_TOP, (11).to_bytes(4, "little") +
           (emu.SCRATCH + 0x2000).to_bytes(4, "little") +
           (13).to_bytes(4, "little") + (0x00080001).to_bytes(4, "little"))], {}),
    ],
    ("app", 0x0004e83c): [
        ({0: emu.SCRATCH, 1: 0, 2: 3, 3: 4},
         [(emu.SCRATCH, bytes(4) + (9).to_bytes(4, "little") + bytes(8))],
         {0: {0: 1}}),
        ({0: emu.SCRATCH, 1: 0, 2: 3, 3: 4},
         [(emu.SCRATCH, bytes(4) + (9).to_bytes(4, "little") + bytes(8))],
         {0: {0: 0}, 1: {0: 0xffffffff}}),
        ({0: emu.SCRATCH, 1: 0, 2: 3, 3: 0x10000},
         [(emu.SCRATCH, bytes(4) + (9).to_bytes(4, "little") + bytes(8))],
         {0: {0: 0}, 1: {0: 0xfffffff4}}),
        ({0: emu.SCRATCH, 1: 0, 2: 3, 3: 4},
         [(emu.SCRATCH, bytes(8) + (9).to_bytes(4, "little") + bytes(4))],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 7}}),
        ({0: emu.SCRATCH, 1: 0, 2: 3, 3: 4},
         [(emu.SCRATCH, bytes(8) + (100).to_bytes(4, "little") + bytes(4))],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 0}}),
    ],
    ("app", 0x0004ed8c): [
        ({0: 1, 1: 0, 2: 0, 3: 2}, [], {}),
        # Non-null descriptors may carry only bit 1; prove both rejection of
        # another bit and acceptance of the permitted bit itself.
        ({0: 1, 1: emu.SCRATCH, 2: 1, 3: 2},
         [(emu.SCRATCH, b"\x01" + bytes(0x3f))], {}),
        ({0: 1, 1: emu.SCRATCH, 2: 1, 3: 2},
         [(0x2000a28c, bytes(4)),
          (emu.SCRATCH, b"\x02" + bytes(0x3f))],
         {0: {0: 8}, 2: {0: 0}}),
        ({0: 1, 1: 0, 2: 1, 3: 2},
         [(0x2000a28c, (1).to_bytes(4, "little"))], {}),
        ({0: 1, 1: 0, 2: 1, 3: 2},
         [(0x2000a28c, bytes(4))], {0: {0: 0}}),
        ({0: 1, 1: 0, 2: 1, 3: 2},
         [(0x2000a28c, bytes(4))], {0: {0: 7}}),
        ({0: 1, 1: emu.SCRATCH, 2: 1, 3: 2},
         [(0x2000a28c, bytes(4)), (emu.SCRATCH, bytes(0x40))],
         {0: {0: 8}, 2: {0: 0}}),
    ],
    ("app", 0x00052880): [
        ({0: emu.SCRATCH}, [(emu.SCRATCH, bytes(0x80))], {}),
        ({0: emu.SCRATCH},
         [(emu.SCRATCH, bytes(0x18) + (emu.SCRATCH + 0x1000).to_bytes(4, "little") + bytes(0x64))],
         {1: {0: 0}, 2: {0: 0}},
         {1: [(1, 0x24, b"\x02", 0x00056f4c)]}),
        ({0: emu.SCRATCH},
         [(emu.SCRATCH, bytes(0x0c) + (emu.SCRATCH + 0x3000).to_bytes(4, "little") +
           (20).to_bytes(2, "little") + bytes(0x0a) +
           (emu.SCRATCH + 0x1000).to_bytes(4, "little") + bytes(3) + b"\x05" + bytes(0x63)),
          (emu.SCRATCH + 0x2000, bytes(0x69) + b"\x05" + bytes(0x80))],
         {1: {0: 0}, 2: {0: 20}, 3: {0: emu.SCRATCH + 0x2000},
          5: {0: 0}},
         {1: [(1, 0x24, b"\x02", 0x00056f4c)]}),
        ({0: emu.SCRATCH},
         [(emu.SCRATCH, bytes(0x0c) + (emu.SCRATCH + 0x3000).to_bytes(4, "little") +
           (10).to_bytes(2, "little") + bytes(0x0a) +
           (emu.SCRATCH + 0x1000).to_bytes(4, "little") + bytes(3) + b"\x05" + bytes(0x63)),
          (emu.SCRATCH + 0x2000, bytes(0x69) + b"\x05" + bytes(0x80))],
         {1: {0: 0}, 2: {0: 10}, 3: {0: emu.SCRATCH + 0x2000},
          5: {0: 0xfffffff4}},
         {1: [(1, 0x24, b"\x02", 0x00056f4c)]}),
        ({0: emu.SCRATCH},
         [(emu.SCRATCH, bytes(0x0c) + (emu.SCRATCH + 0x3000).to_bytes(4, "little") +
           (20).to_bytes(2, "little") + bytes(0x0a) +
           (emu.SCRATCH + 0x1000).to_bytes(4, "little") + bytes(3) + b"\x05" + bytes(0x63)),
          (emu.SCRATCH + 0x2000, bytes(0x69) + b"\x05" + bytes(0x80))],
         {1: {0: 0}, 2: {0: 20}, 3: {0: emu.SCRATCH + 0x2000},
          5: {0: 7}},
         {1: [(1, 0x24, b"\x02", 0x00056f4c)]}),
        # A large -ENOMEM halves the chunk, yields, and retries.  Two exact
        # successful half-size chunks then complete the 40-byte transfer.
        ({0: emu.SCRATCH},
         [(emu.SCRATCH, bytes(0x0c) + (emu.SCRATCH + 0x3000).to_bytes(4, "little") +
           (40).to_bytes(2, "little") + bytes(0x0a) +
           (emu.SCRATCH + 0x1000).to_bytes(4, "little") + bytes(3) + b"\x05" + bytes(0x63)),
          (emu.SCRATCH + 0x2000, bytes(0x69) + b"\x05" + bytes(0x80))],
         {1: {0: 0}, 2: {0: 40}, 3: {0: emu.SCRATCH + 0x2000},
          5: {0: 0xfffffff4}, 7: {0: 0}, 9: {0: 0}},
         {1: [(1, 0x24, b"\x02", 0x00056f4c)]}),
        # Once one chunk has succeeded, a later -ENOMEM yields without
        # shrinking, then retries the same ten-byte chunk successfully.
        ({0: emu.SCRATCH},
         [(emu.SCRATCH, bytes(0x0c) + (emu.SCRATCH + 0x3000).to_bytes(4, "little") +
           (20).to_bytes(2, "little") + bytes(0x0a) +
           (emu.SCRATCH + 0x1000).to_bytes(4, "little") + bytes(3) + b"\x05" + bytes(0x63)),
          (emu.SCRATCH + 0x2000, bytes(0x69) + b"\x05" + bytes(0x80))],
         {1: {0: 0}, 2: {0: 10}, 3: {0: emu.SCRATCH + 0x2000},
          5: {0: 0}, 7: {0: 0xfffffff4}, 9: {0: 0}},
         {1: [(1, 0x24, b"\x02", 0x00056f4c)]}),
    ],
    # Setup/decode errors plus absent, empty, transfer-error, progress and
    # completion success families.  Parser/decode outputs are exact producer
    # effects rather than unrelated compiler-stack seeds.
    ("app", 0x000521fc): [
        _configuration_case(parser_result=1),
        _configuration_case(decode_result=5),
        _configuration_case(present=0),
        _configuration_case(present=1, parsed_kind=0, total=0, progress=0),
        _configuration_case(present=1, parsed_count=0, total=5, progress=2),
        _configuration_case(decode_result=5, cleanup_result=6),
        _configuration_case(present=1, parsed_count=2, amount=2, total=5,
                            progress=0, transfer_result=4),
        _configuration_case(present=1, parsed_count=2, amount=2, total=5,
                            progress=0, transfer_result=0),
        _configuration_case(present=1, parsed_count=2, amount=2, total=5,
                            progress=3, transfer_result=0),
    ],
    # Cover both operating-mode format families, minute/hour scaling, and both
    # logger sinks with valid timestamp-oracle results.  Random oracle values
    # manufacture invalid calendar pointers on the long-duration paths.
    ("app", 0x000357dc): [
        ({0: emu.SCRATCH, 1: 100}, [(0x20007554, sink.to_bytes(4, "little"))],
         {0: {0: emu.SCRATCH}, 1: {0: 100 + elapsed}, 4: {0: mode}})
        for mode, elapsed, sink in ((6, 60, 0), (6, 3600, 1),
                                    (5, 60, 1), (5, 3600, 0))
    ] + [
        # Calendar-backed hour/minute formatting in 24-hour mode, then all
        # three semantically distinct 12-hour conversions: 00 -> 12 AM,
        # 12 remains 12 PM, and 13 -> 1 PM.
        _app_357dc_calendar_case(5, 10800,
                                 (2026, 7, 17, 23, 41, 52), False, 0),
        _app_357dc_calendar_case(5, 10800,
                                 (2026, 7, 17, 0, 11, 22), True, 1),
        _app_357dc_calendar_case(5, 10800,
                                 (2026, 7, 17, 12, 22, 33), True, 0),
        _app_357dc_calendar_case(5, 10800,
                                 (2026, 7, 17, 13, 33, 44), True, 1),
        # Alternate operating mode consumes the same exact producer record
        # without the diagnostic/12-hour conversion subgraph.
        _app_357dc_calendar_case(6, 10800,
                                 (2026, 7, 17, 21, 45, 56), False, 0),
        # Exact boundary representatives for day text, weekday/date lookup,
        # and the first month/day calendar-backed path on both mode families.
        _app_357dc_calendar_case(5, 86400, None, False, 0),
        _app_357dc_calendar_case(5, 172800, None, False, 1),
        _app_357dc_calendar_case(5, 604800,
                                 (2027, 1, 2, 3, 4, 5), False, 0),
        _app_357dc_calendar_case(6, 86400, None, False, 1),
        _app_357dc_calendar_case(6, 172800, None, False, 0),
        _app_357dc_calendar_case(6, 604800,
                                 (2028, 11, 29, 19, 58, 57), False, 1),
    ],
    # Window lookup: null/error, exact write, and short-write panic.  Parameter
    # five is stack-passed; the lookup's r1 out-word is modeled explicitly.
    ("net", 0x0103576c): [
        ({0: emu.SCRATCH + 0x1000, 1: 0x11, 2: 0x22, 3: 0x33},
         [(emu.STACK_TOP, (16).to_bytes(4, "little") + (7).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1000 + 0xac,
           (emu.SCRATCH + 0x2000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000,
           (emu.SCRATCH + 0x3000).to_bytes(4, "little") +
           bytes(4) + (0x100).to_bytes(4, "little")),
          (emu.SCRATCH + 0x3000, bytes(0x100))],
         {0: {0: position}, 1: {0: written}},
         {0: [(1, 0, (32).to_bytes(4, "little"))]})
        for position, written in (
            (0, 0),
            (emu.SCRATCH + 0x3004, 16),
            (emu.SCRATCH + 0x3004, 15),
        )
    ],
    # Parser output selects every header-validation arm and the response loop's
    # terminal/continuation records.  Writes are bound to the exact producing
    # callee so an ordinal shift cannot replay them through another helper.
    ("app", 0x00024dac): [
        ({}, [], {0: {0: 0xfffffffe}}, {}),
        ({}, [], {0: {0: 0}},
         {0: [(0, 0, bytes((0x10, 0x40, 8, 0)), 0x00024d74)]}),
        ({}, [], {0: {0: 0}, 1: {0: 1}},
         {0: [(0, 0, bytes((0xe1, 0x40, 8, 0)), 0x00024d74)]}),
        ({}, [], {0: {0: 0}, 1: {0: 0}},
         {0: [(0, 0, bytes((0xe1, 0x40, 8, 0)), 0x00024d74)],
          1: [(2, 0, bytes((3, 0, 0, 0)), 0x00025788)]}),
        ({}, [], {0: {0: 0}, 1: {0: 0}},
         {0: [(0, 0, bytes((0xe1, 0x40, 8, 0)), 0x00024d74)],
          1: [(2, 0, bytes((3, 1, 0, 0)), 0x00025788)]}),
        ({}, [], {0: {0: 0}, 1: {0: 0}},
         {0: [(0, 0, bytes((0xe1, 0x41, 8, 0)), 0x00024d74)],
          1: [(2, 0, bytes((3, 1, 0, 0)), 0x00025788)]}),
        ({}, [], {0: {0: 0}, 1: {0: 0}},
         {0: [(0, 0, bytes((0xe1, 0x40, 8, 0)), 0x00024d74)],
          1: [(2, 0, bytes((0xfd, 1, 0, 0)), 0x00025788)]}),
    ],
    ("app", 0x00024fe8): [
        ({}, [], {0: {0: 0}}),
        ({}, [], {0: {0: 0xffffffff}, 1: {0: 0x12345678}, 2: {0: 0}}),
    ],
    ("app", 0x0002ea28): [
        ({}, [], {0: {0: 0xffffffff}}),
        ({}, [], {0: {0: 0}, 2: {0: 0xffffffff}}),
        ({}, [], {0: {0: 0}, 2: {0: 0},
                  3: {0: 0x89abcdef, 1: 0x01234567}}),
    ],
    # Enumerate the initialization failures, special -2 setup path, direct
    # success path, and the full recovery chain with a real four-word config.
    ("app", 0x00030b3c): [
        ({0: 0}, [], {}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, (1).to_bytes(4, "little") * 4)],
         {0: {0: 0xffffffff}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, (1).to_bytes(4, "little") * 4)],
         {0: {0: 0}, 1: {0: 1}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, (1).to_bytes(4, "little") * 4)],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 0xffffffff}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, (1).to_bytes(4, "little") * 4)],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 0xfffffffe},
          8: {0: 0}, 9: {0: 0}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, (1).to_bytes(4, "little") * 4)],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 0xfffffffe},
          8: {0: 1}, 9: {0: 0}, 10: {0: 0}, 11: {0: 0},
          12: {0: 0}, 13: {0: 1}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, (1).to_bytes(4, "little") * 4)],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0}, 4: {0: 1}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, (1).to_bytes(4, "little") * 4)],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 0}, 3: {0: 1}, 4: {0: 1}}),
    ],
    # Validation covers horizontal and vertical inversion plus odd x.  The two
    # production cases walk two rows and two source bytes per row; the latter
    # also exercises pre-clear and post-write display flush with complete
    # six-argument helper ABIs.
    ("app", 0x00043a68): [
        ({0: 2, 1: 0, 2: 0, 3: 0},
         [(0x2000230c, level.to_bytes(4, "little")),
          (0x20007554, sink.to_bytes(4, "little"))], {})
        for level, sink in ((0, 0), (2, 0), (2, 1))
    ] + [
        ({0: 0, 1: 3, 2: 8, 3: 2},
         [(0x2000230c, bytes(4)), (0x20007554, bytes(4))], {}),
        ({0: 1, 1: 0, 2: 9, 3: 1},
         [(0x2000230c, (2).to_bytes(4, "little")),
          (0x20007554, bytes(4))], {}),
        _app_43a68_bitmap_case(False),
        _app_43a68_bitmap_case(True),
    ],
    # Exercise both transport outcomes for the fully initialized 24-byte
    # command record; random oracle returns almost never select success zero.
    ("app", 0x00047bf8): [
        ({0: 0x12, 1: 0x34}, [], {1: {0: result}})
        for result in (0, 1, 0xfffffffb)
    ],
    ("app", 0x000442bc): [
        _app_442bc_case(0),
        _app_442bc_case(3),
        _app_442bc_case(1, glyph="success", flush=True),
        _app_442bc_case(2, glyph="success", flush=False),
        _app_442bc_case(1, glyph="failure", flush=False, buffered=False),
        _app_442bc_case(2, glyph="failure", flush=False, buffered=True),
        _app_442bc_case(2, glyph="success", flush=False,
                        rendered_text=b"A:B\0"),
        _app_442bc_case(0, hour=13),
    ],
    ("app", 0x0004967c): [
        _app_4967c_success_case(False, False),
        _app_4967c_success_case(False, True),
        _app_4967c_success_case(True, True),
        _app_4967c_success_case(False, False, 10),
        _app_4967c_null_success_case(),
        _app_4967c_queue_failure_case(),
        _app_4967c_invalid_length_case(0, False),
        _app_4967c_invalid_length_case(1, False),
        _app_4967c_invalid_length_case(1, True),
        # Exact uint64_t modulo multiplication and shifted subtraction.  These
        # pairs force low-word carry, nonzero high splices, the signed bit, and
        # complete counter wrap through both logger implementations.
        _app_4967c_success_case(
            False, True, 4, 0x00000000fffffff0, 0x0000000100000030),
        _app_4967c_success_case(
            True, True, 4, 0x00012345fffffff0, 0x0001234600000070),
        _app_4967c_success_case(
            False, True, 4, 0x00012345fffffff0, 0x0001234600000070),
        _app_4967c_success_case(
            False, True, 4, 0x7ffffffffffffff0, 0x8000000000000050),
        _app_4967c_success_case(
            True, True, 4, 0xfffffffffffffff0, 0x0000000000000050),
    ],
    # Serializer coverage uses coherent two-word descriptors and exact AAPCS
    # stack arguments.  It covers both early exits, multi-string discovery,
    # every checked callback failure, the ignored flush result, unsigned
    # 16-bit lengths, range classification, both halves of the resolver's
    # r1:r0 result, descriptor construction, and the 16/17 index boundary.
    ("app", 0x0004abc0): [
        ({0: emu.SCRATCH + 0x1000, 1: 0, 2: 0, 3: 0},
         [(emu.SCRATCH + 0x1000, bytes(32))], {}),
        ({0: emu.SCRATCH + 0x1000, 1: 8, 2: 0, 3: 0},
         [(emu.SCRATCH + 0x1000, bytes(32))], {}),
        ({0: emu.SCRATCH + 0x1000, 1: 8,
          2: emu.ORACLE_TRAMPOLINE | 1, 3: 0},
         [(emu.SCRATCH + 0x1000, bytes(32))], {0: {0: 0}}),
        # param_2==0 walks two [tag, NUL-terminated string] records.
        ({0: _SERIALIZER_INPUT, 1: 0, 2: 0, 3: 0},
         [(_SERIALIZER_INPUT,
           bytes((2, 2, 0, 0)) + _SERIALIZER_STRING.to_bytes(4, "little") +
           b"\x11abc\0\x22hello\0"), *_serializer_stack_args(0)],
         {0: {0: 3}, 1: {0: 5}}),
        # Two deferred strings populate separate unsigned length slots at the
        # 0x7fff/0xfffe boundaries (stored as 0x8000/0xffff after NUL).
        _serializer_multi_length_case(),
        # Five checked callback exits plus the deliberately ignored flush rc.
        *[_serializer_callback_case(7, failure=ordinal)
          for ordinal in range(1, 7)],
        # The callback's string length is the original unsigned LDRH value.
        *[_serializer_callback_case(length)
          for length in (0x7fff, 0x8000, 0xffff)],
        # Same record index, on either side of [0x879b0,0xf8d64).
        _serializer_classification_case(0x00090000),
        _serializer_classification_case(_SERIALIZER_STRING),
        # Resolver miss vs hit; the hit publishes an exact 18-byte descriptor.
        _serializer_classification_case(
            _SERIALIZER_STRING, resolver=(0, 0xa1b2c35a)),
        _serializer_classification_case(
            _SERIALIZER_STRING, resolver=(1, 0xa1b2c35a)),
        # Callback mode proves resolver high-r1 is retained as pair key 0x5a.
        _serializer_resolver_callback_case(0, 0xa1b2c35a),
        _serializer_resolver_callback_case(1, 0xa1b2c35a),
        # Enumerate every combination of the four recovered behavior flags;
        # resolver-enabled cases use an explicit miss before length handling.
        *[_serializer_flag_case(flags) for flags in range(16)],
        _serializer_index_boundary_case(16),
        _serializer_index_boundary_case(17),
    ],
    # Six fixed record-prefix comparisons are followed by two bounded row
    # tables selected through the application state accessor.  Random absolute
    # RAM makes those NUL-terminated tables effectively unbounded, so enumerate
    # each comparison exit, both table selectors, successful row advancement,
    # and the two row-mismatch returns with one-row production-shaped tables.
    ("app", 0x0003483c): [
        ({0: 1}, [], {0: {0: 0}}),
        ({0: 1}, [], {0: {0: 1}, 1: {0: 0}}),
        ({0: 1}, [], {0: {0: 1}, 1: {0: 1}, 2: {0: 0}}),
        ({0: 1}, [], {0: {0: 1}, 1: {0: 1}, 2: {0: 1}, 3: {0: 0}}),
        ({0: 1}, [], {0: {0: 1}, 1: {0: 1}, 2: {0: 1}, 3: {0: 1},
                       4: {0: 0}}),
        ({0: 1}, [], {0: {0: 1}, 1: {0: 1}, 2: {0: 1}, 3: {0: 1},
                       4: {0: 1}, 5: {0: 0}}),
        *[
            ({0: 1},
             [(emu.SCRATCH + 0x1068, bytes((selector,))),
              (0x20003152, bytes(0x21)), (0x20003292, bytes(0x21)),
              (0x20003032, bytes(0x21)), (0x200030d2, bytes(0x21))],
             {0: {0: 1}, 1: {0: 1}, 2: {0: 1}, 3: {0: 1},
              4: {0: 1}, 5: {0: 1}, 6: {0: emu.SCRATCH},
              7: {0: emu.SCRATCH}})
            for selector in (0, 1)
        ],
        ({0: 1},
         [(emu.SCRATCH + 0x1068, b"\0"),
          (0x20003152, b"A" + bytes(0x20)), (0x20003032, bytes(0x21))],
         {0: {0: 1}, 1: {0: 1}, 2: {0: 1}, 3: {0: 1}, 4: {0: 1},
          5: {0: 1}, 6: {0: emu.SCRATCH}, 7: {0: 5}, 8: {0: 0}}),
        ({0: 1},
         [(emu.SCRATCH + 0x1068, b"\0"), (0x20003152, bytes(0x21)),
          (0x20003032, b"B" + bytes(0x20))],
         {0: {0: 1}, 1: {0: 1}, 2: {0: 1}, 3: {0: 1}, 4: {0: 1},
          5: {0: 1}, 6: {0: emu.SCRATCH}, 7: {0: emu.SCRATCH},
          8: {0: 7}, 9: {0: 0}}),
        # The first selected row is nonempty and its recovered string length
        # straddles the 31-byte comparison clamp.  The compare oracle's third
        # argument therefore distinguishes 30, 31, and 32 -> 31 exactly.
        *[
            ({0: 1},
             [(emu.SCRATCH + 0x1068, b"\0"),
              (0x20003152, b"R" * row_length + b"\0" +
               bytes(0x20 - row_length)),
              (0x20003032, bytes(0x21))],
             {0: {0: 1}, 1: {0: 1}, 2: {0: 1}, 3: {0: 1},
              4: {0: 1}, 5: {0: 1}, 6: {0: emu.SCRATCH},
              7: {0: row_length}, 8: {0: 0}})
            for row_length in (30, 31, 32)
        ],
    ],
    # The table count is a byte in absolute controller state.  Random RAM can
    # request hundreds of 56-byte records, which is not a coherent initialized
    # table.  Cover both invalid-input logger routes, empty table, first-field
    # mismatch, second-field mismatch, and a complete match.
    ("app", 0x00034ff0): [
        ({0: 0, 1: 1}, [(0x20007554, bytes(4))], {}),
        ({0: 1, 1: 0}, [(0x20007554, (1).to_bytes(4, "little"))], {}),
        ({0: emu.SCRATCH, 1: emu.SCRATCH + 0x1000},
         [(0x2001a22c, bytes(0x40))], {}),
        ({0: emu.SCRATCH, 1: emu.SCRATCH + 0x1000},
         [(0x2001a22c, b"\0\1" + bytes(0x3e))], {0: {0: 1}}),
        ({0: emu.SCRATCH, 1: emu.SCRATCH + 0x1000},
         [(0x2001a22c, b"\0\1" + bytes(0x3e))],
         {0: {0: 0}, 1: {0: 1}}),
        ({0: emu.SCRATCH, 1: emu.SCRATCH + 0x1000},
         [(0x2001a22c, b"\0\1" + bytes(0x3e))],
         {0: {0: 0}, 1: {0: 0}}),
    ],
    # Global controller state, not an argument, selects this TBB.  Cover all
    # four valid buffer modes and the default assertion with complete owned
    # objects instead of relying on randomized RAM to happen to be coherent.
    ("net", 0x0100ac98): [_ac98_reviewed_case(mode) for mode in range(5)],
    # Slot lookup has an oracle-controlled not-found result and otherwise calls
    # a callback assembled from two object halfwords.  Use one mapped object
    # and explicit oracle results to cover both exits without random pointers.
    ("net", 0x01009d64): [
        ({0: 0x1234, 1: 0},
         [(0x21000b7c, (emu.SCRATCH + 0x1000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1000,
           bytes(6) + (0x0103).to_bytes(2, "little") +
           (0x0001).to_bytes(2, "little") + bytes(0x36))],
         {0: {0: 0xff}}),
        ({0: 0x1234, 1: 0},
         [(0x21000b7c, (emu.SCRATCH + 0x1000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1000,
           bytes(6) + (0x0103).to_bytes(2, "little") +
           (0x0001).to_bytes(2, "little") + bytes(0x36))],
         {0: {0: 2}, 1: {0: 0x55667788}}),
    ],
    # Queue allocator: random objects manufacture invalid intrusive-list and
    # callback pointers.  Cover the null assertion, empty-queue return, and a
    # one-record dequeue using bounded production-shaped queue state.  The
    # void unlock leaves r1 caller-scratch; pin it to the semantic null link
    # consumed by the following list lookup.
    ("app", 0x0005eeb4): [
        ({0: 0, 1: 0, 2: 0, 3: 0}, [], {}),
        ({0: emu.SCRATCH + 0x1000, 1: 0, 2: 0, 3: 0},
         [(emu.SCRATCH + 0x1000, bytes(0x80))],
         {1: {0: 1}, 2: {1: 0}, 3: {0: 1, 1: 0}, 4: {0: 0}}),
        ({0: emu.SCRATCH + 0x1000, 1: 0, 2: 0, 3: 0},
         [(emu.SCRATCH + 0x1000, bytes(0x80)),
          (emu.SCRATCH + 0x1020, (2).to_bytes(2, "little") +
           (1).to_bytes(2, "little") + bytes(12) +
           (emu.SCRATCH + 0x2000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000, bytes(0x40))],
         {1: {0: 1}, 2: {1: 0}, 3: {0: 0}, 4: {0: 1}}),
    ],
    # Queue-state reentrancy gate: all three public operation selectors on an
    # already-active owner.  This is the production fast path; it proves the
    # selector-specific pending bit (0x10 vs 0x20), owner mutation, lock query,
    # and clean return without manufacturing cyclic randomized lists.
    ("net", 0x0102c6f8): [
        ({0: emu.SCRATCH + 0x1000, 1: op, 2: 0, 3: 0},
         [(emu.SCRATCH + 0x1000, bytes(0x1c) + b"\x08\x00" + bytes(0x20))],
         {0: {0: 1}})
        for op in (1, 2, 3)
    ],
    ("app", 0x00075acc): [
        ({}, [(0x200035af, bytes((mode,)))], oracles)
        for mode, oracles in (
            (0xff, {}),
            (0, {1:{0:1}}),
            (0, {1:{0:0},2:{0:1},3:{0:1}}),
            (0, {1:{0:0},2:{0:1},3:{0:0}}),
            (0, {1:{0:0},2:{0:0},3:{0:0},4:{0:0}}),
            (0, {1:{0:0},2:{0:0},3:{0:1},4:{0:1},5:{0:1},6:{0:1}}),
        )
    ],
    ("app", 0x00077d54): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000},
         [(0x20002d20, bytes(4)),
          (emu.SCRATCH + 0x1000, bytes(4)),
          (emu.SCRATCH + 0x2000,
           (0x11111111).to_bytes(4,"little") + bytes(4) + bytes(4) +
           flags.to_bytes(2,"little") + bytes(2) + field4.to_bytes(4,"little") +
           (5).to_bytes(4,"little") + bytes(0x1c) + owner.to_bytes(4,"little") +
           bytes(0x10))], {})
        for flags, field4, owner in (
            (0, 0, 0), (8, 1, 0), (0x88, 0, 0),
            (9, 0, 0), (0x14, 0, emu.SCRATCH + 0x3000),
        )
    ],
    ("app", 0x00082396): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000},
         [(emu.SCRATCH + 0x2000 + 0xc, (emu.SCRATCH + 0x3000).to_bytes(4,"little")),
          (emu.SCRATCH + 0x3000, length.to_bytes(2,"little")),
          (emu.SCRATCH + 0x1000, (emu.SCRATCH + 0x4000).to_bytes(4,"little")),
          (emu.SCRATCH + 0x4000, (emu.SCRATCH + 0x5000).to_bytes(4,"little")),
          (emu.SCRATCH + 0x5004, bytes(4)),
          (emu.SCRATCH + 0x7000, bytes(8))], oracles)
        for length, oracles in (
            (22, {}),
            (23, {0: {0: 0}}),
            (23, {0: {0: emu.SCRATCH + 0x6000},
                  1: {0: emu.SCRATCH + 0x7000}}),
        )
    ],
    ("app", 0x0007f542): [
        ({0: 0x11, 1: 0xabcd, 2: 0x22}, [], {0: {0: 0}}),
    ] + [
        ({0: 0x11, 1: 0xabcd, 2: 0x22},
         [(emu.SCRATCH + 0x3000, (0x12345678).to_bytes(4,"little"))],
         {0: {0: emu.SCRATCH + 0x3000}, 1: {0: result}})
        for result in (0, 1)
    ],
    ("app", 0x0007d1d6): [
        ({0: emu.SCRATCH + 0x1000, 1: 0x55},
         [(emu.SCRATCH + 0x1000 + 0xff4, (emu.SCRATCH + 0x3000).to_bytes(4,"little")),
          (emu.SCRATCH + 0x1000 + 0xfec, (emu.SCRATCH + 0x4000).to_bytes(4,"little")),
          (emu.SCRATCH + 0x3000 + 0x164, value.to_bytes(4,"little")),
          (emu.SCRATCH + 0x4000, (0x11223344).to_bytes(4,"little"))], {})
        for value in (0, 0xaabbccdd)
    ],
    ("app", 0x0003af04): [
        ({}, [(emu.SCRATCH + 0x1000, bytes(0xfec) +
               (emu.SCRATCH + 0x3000).to_bytes(4, "little") + bytes(0x20)),
              (emu.SCRATCH + 0x3000, bytes(0x64) + bytes((0x5a,)) + bytes(0x20)),
              (0x2000496a, bytes((mode,)))],
         {0: {0: emu.SCRATCH + 0x1000},
          1: {0: emu.SCRATCH + 0x1000},
          2: {0: 6}})
        for mode in (0, 1, 2)
    ],
    ("app", 0x000742b4): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(0x40))], {0: {0: 0}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(0x40))],
         {0: {0: 1}, 2: {0: 0}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(0x40))],
         {0: {0: 1}, 2: {0: 1}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(8)+(1).to_bytes(4,"little")+bytes(0x34))],
         {0: {0: 1}, 3: {0: 1}}),
    ],
    # Pool formatter's two legal header-width families.  Valid aligned storage
    # and bounded arithmetic results avoid assertion-only inputs while still
    # exercising the complete split/link initialization sequence.
    ("net", 0x0102c5ec): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000, 2: size},
         [(emu.SCRATCH + 0x1000, bytes(4)),
          (emu.SCRATCH + 0x2000, bytes(0x200))],
         {0: {0: 0}, 1: {0: 0},
          **{i: {0: emu.SCRATCH + 0x2000} for i in range(2, 12)}})
        for size in (0x40, 0x40000)
    ],
    # Radio transport object construction: three null-contract returns and a
    # fully-owned object/vtable case.  The latter stops on the constructor's
    # documented nonzero status after proving all field/vtable mutations.
    ("net", 0x01035830): [
        ({0: 0, 1: emu.SCRATCH + 0x2000, 3: emu.SCRATCH + 0x3000}, [], {}),
        ({0: emu.SCRATCH + 0x1000, 1: 0, 3: emu.SCRATCH + 0x3000}, [], {}),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000, 3: 0}, [], {}),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000,
          2: 0x12345678, 3: emu.SCRATCH + 0x3000},
         [(emu.SCRATCH + 0x1000, bytes(0xc0)),
          (emu.SCRATCH + 0x2000,
           bytes(0x18) + (0).to_bytes(4, "little") +
           bytes(4) + (emu.SCRATCH + 0x4000).to_bytes(4, "little") + bytes(8) +
           (emu.SCRATCH + 0x5000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x4000, bytes(0x10) +
           (0x00080001).to_bytes(4, "little")),
          (emu.SCRATCH + 0x5000, bytes(0x20))],
         {2: {0: 0}, 3: {0: 0xffffffff}}),
    ],
    ("app", 0x00071358): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000,
          2: 0x55, 3: emu.SCRATCH + 0x3000},
         [(emu.STACK_TOP, (emu.SCRATCH + 0x4000).to_bytes(4, "little") +
                          (emu.SCRATCH + 0x5000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000 + 0x18, (1).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000 + 0x20, (emu.SCRATCH + 0x6000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x6000 + 0x10, (0x00080001).to_bytes(4, "little")),
          (emu.SCRATCH + 0x6000 + 0x0c, (0x00080001).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000 + 0x2c, (emu.SCRATCH + 0x7000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x7000, (emu.SCRATCH + 0x8000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x7000 + 0x18, (emu.SCRATCH + 0x9000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x3000, bytes(12))],
         {2: {0: flag}, 3: {0: 0}})
        for flag in (0, 1)
    ],
    ("app", 0x00062930): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000 + 4, (emu.SCRATCH + 0x2000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000, (emu.SCRATCH + 0x3000).to_bytes(4, "little") +
           (0x1234).to_bytes(4, "little")),
          (emu.SCRATCH + 0x3000 + 8, (emu.SCRATCH + 0x4000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x4000 + 8, (0x00080001).to_bytes(4, "little"))],
         oracles, writes)
        for oracles, writes in (
            ({0: {0: 0}}, {}),
            ({0: {0: 1}, 1: {0: 1}}, {}),
            ({0: {0: 1}, 1: {0: 0}}, {1: [(2, 0, b"IT")]}),
            ({0: {0: 1}, 1: {0: 0}, 2: {0: 0}},
             {1: [(2, 0, b"IT")], 2: [(2, 0, b"\x01\x30")]}),
            ({0: {0: 1}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0}, 4: {0: 0}},
             {1: [(2, 0, b"IT")], 2: [(2, 0, b"\x01\x30")],
              3: [(2, 0, b"\x34\x12")]}),
        )
    ],
    # Radio-owner initialization.  Configuration kind 2 is the production
    # externally-installed callback family; kinds 0/1 install firmware-local
    # entry points (0x10333a4 and the overlapping loop instruction 0x10333e4)
    # and are covered by the immutable ownership/disassembly assertions below.
    # These cases cover all three radio mask modes and the complete successful
    # initialization tail without making a candidate jump into an unrelated
    # same-address instruction after recompilation.
    ("net", 0x010333b4): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           (b"\x02\x00\x00\x00" + bytes(4) + bytes((0, mode)) +
            bytes(7) + b"\x11" + bytes(2))),
          (0x2100499c, (0x00080001).to_bytes(4, "little")),
          (0x21006458, bytes(2)),
          (0x21004a90, bytes(0x30))],
         {3: {0: emu.SCRATCH + 0x3000},
          5: {0: 0x0bad0000}, 6: {0: 0}, 7: {0: 1}})
        for mode in (0, 1, 2)
    ],
    # Vendor BLE hook: ordinary fuzzing gives every string/parser oracle a
    # random return value and can strand the audio-transfer retry loop.  Use
    # the real, bounded POST_BT_UNPAIR command family to prove the early
    # command mutation and both production diagnostic sinks.  Ordinals are
    # stable semantic calls: context, clear, bounded copy, command compare,
    # optional logger, and response append.
    ("app", 0x0000ef28): [
        ({0: emu.SCRATCH + 0x1000, 1: len(b"POST_BT_UNPAIR")},
         [(emu.SCRATCH + 0x1000, b"POST_BT_UNPAIR"),
          (0x2000230c, level.to_bytes(4, "little")),
          (0x20007554, sink.to_bytes(4, "little"))],
         ({0: {0: emu.SCRATCH + 0x3000}, 3: {0: 0}}))
        for level, sink in ((0, 0), (3, 0), (3, 1))
    ],
    # Boot starts with a one-time allocator.  Keep ordinary status-returning
    # initializers successful (zero), while giving the allocation call owned
    # writable storage.  Additional pointer-producing getters are overridden
    # below as their production contracts are reached.
    ("app", 0x00016eb8): [
        ({}, [(emu.SCRATCH + 0x1000, bytes(0x7000)),
              (emu.SCRATCH + 0x2778, (0x00080001).to_bytes(4, "little")),
              (emu.SCRATCH + 0x277c, (0x00080001).to_bytes(4, "little")),
              (emu.SCRATCH + 0x2f70, (0x00080001).to_bytes(4, "little")),
              (emu.SCRATCH + 0x2f80, (0x00080001).to_bytes(4, "little")),
              (emu.SCRATCH + 0x2b10, (0x00080001).to_bytes(4, "little")),
              (emu.SCRATCH + 0x2b6c, (0x00080001).to_bytes(4, "little")),
              (0x2000230c, bytes(4)), (0x20007554, bytes(4))],
         ({i: {0: 0} for i in range(128)} |
          {1: {0: emu.SCRATCH + 0x1000},
           5: {0: emu.SCRATCH + 0x2000}})),
    ],
    # Even-AI is selected by an argument phase, an absolute active state, and
    # several fields in the global UI object returned by its first accessor.
    # Enumerate the deep logger/cleanup/icon/render families explicitly; raw
    # random state otherwise almost never produces active=0/1 and valid status.
    ("app", 0x0003bfe0): [
        _even_ai_case(0, 2, 0, level=3, sink=0),   # inactive direct logger + cleanup
        _even_ai_case(0, 2, 0, level=3, sink=1),   # inactive fallback logger
        _even_ai_case(1, 0, 4),                    # active status-icon painter
        _even_ai_case(1, 2, 4, level=3, sink=0),   # active logger + teardown
        _even_ai_case(1, 2, 4, level=3, sink=1),   # active fallback logger
        _even_ai_case(1, 1, 4, frame=1),           # low-status text render
        _even_ai_case(1, 1, 0xb, frame=1),         # status 11 mic/header render
        _even_ai_case(1, 1, 0xe, frame=1),         # status 14 full-frame publish
        _even_ai_case(1, 1, 0x10, frame=1),        # status 16 text render
        _even_ai_case(1, 1, 8, frame=0),           # streaming render first frame
        _even_ai_case(1, 1, 8, frame=1),           # streaming render update frame
    ],
    # QuickNote is selected first by an absolute UI-state byte and only then
    # by the phase argument.  Random RAM almost never enters states 0/1/2, so
    # enumerate their production phase families explicitly.  Duplicate state
    # 0/2 cases cover both logger sinks, enable gates, recording transitions,
    # review warning/exit flags, and a bounded shared-row raster allocation.
    ("app", 0x0003b824): [
        _quicknote_case(state, phase, level, sink, enable, deadline, exit_flag)
        for state, phase, level, sink, enable, deadline, exit_flag in (
            (0, 0, 0, 0, 1, (0, 0, 0), 0),
            (0, 1, 3, 0, 1, (0, 0, 0), 0),
            (0, 1, 3, 1, 1, (0, 0, 0), 0),
            (0, 1, 0, 0, 0, (0, 0, 0), 0),
            (0, 2, 3, 0, 1, (0, 0, 0), 0),
            (0, 3, 0, 0, 1, (0, 0, 0), 0),
            (1, 0, 3, 0, 1, (0, 0, 0), 0),
            (1, 2, 3, 1, 1, (0, 0, 0), 0),
            (1, 3, 3, 0, 1, (0, 0, 0), 0),
            (2, 0, 0, 0, 1, (0, 0, 0), 0),
            (2, 1, 0, 1, 1, (0, 0, 0), 0),
            (2, 2, 0, 0, 1, (0, 0, 0), 0),
            (2, 3, 0, 1, 1, (0xffffffff, 0, 0), 0),
            (2, 3, 0, 0, 1, (0xffffffff, 0, 0), 1),
        )
    ],
    # Persistent low-speed supervisor.  These are production state families,
    # not random padding: external query results are pinned to valid bounded
    # outcomes so a 500-event semantic prefix crosses multiple five-tick
    # cycles.  Together they cover both roles, both log sinks, peer escalation,
    # phase hold/set/clear, sync cleanup, worker wait/fatal cadence, disconnect
    # notification, watchdog feed/disable, and the +0x108e recovery request.
    ("app", 0x0002a8d8): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(0x1100)),
          (emu.SCRATCH + 0x1000, bytes((mode, worker))),
          (emu.SCRATCH + 0x1ae2, bytes((peer_ready, peer_phase))),
          (emu.SCRATCH + 0x19b4, peer_ptr.to_bytes(4, "little")),
          (emu.SCRATCH + 0x16de, bytes((side_bits,))),
          (emu.SCRATCH + 0x10e4, bytes((display_bits,))),
          (emu.SCRATCH + 0x1fea, b"\x0c"),
          (emu.SCRATCH + 0x2060, timestamp.to_bytes(8, "little")),
          (emu.SCRATCH + 0x1ae4, disconnect_base.to_bytes(4, "little")),
          (emu.SCRATCH + 0x2068, bytes((disconnect_blocked,))),
          (emu.SCRATCH + 0x208e, bytes((recover,))),
          (0x2000230c, log_level.to_bytes(4, "little")),
          (0x20007554, sink.to_bytes(4, "little")),
          (0x20018d90, bytes((watchdog_blocked,))),
          (0x20018d91, bytes((hold,))),
          (0x2000302c, bytes((watchdog_ready,)))],
         ({i: {0: oracle_r0, 1: oracle_r1} for i in range(160)} |
          extra_oracles))
        for (mode, worker, peer_ready, peer_phase, peer_ptr,
             side_bits, display_bits, timestamp, disconnect_base,
             disconnect_blocked, recover, log_level, sink,
             watchdog_blocked, hold, watchdog_ready,
             oracle_r0, oracle_r1, extra_oracles) in (
            # Quiet master/slave baselines and both watchdog branches.
            (0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, {}),
            (1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, {}),
            # Flash-CRC watchdog suppression flag: neither feed nor disable.
            (0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, {}),
            # Active master side: bit propagation and <500 sync cleanup.
            (1, 0, 0, 0, 0x20030000, 0x05, 0x04, 0, 0, 1, 0,
             2, 0, 0, 0, 1, 1, 0, {}),
            # Active peer on alternate sink: escalation after five polls,
            # side transition, verbose status/error logs, disconnect timer,
            # and explicit recovery request.
            (1, 0, 1, 1, 0x20030000, 0x04, 0x05, 0, 0, 0, 1,
             3, 1, 0, 255, 1, 1, 0,
             {}),
            # Hold countdown and subsequent side clear (master/slave roles).
            (1, 0, 0, 1, 0, 1, 3, 0, 0, 1, 0, 0, 0, 0, 2, 1, 0, 0, {}),
            # Active slave-side peer assertion and status-bit cleanup.
            (0, 0, 0, 0, 0x20030000, 4, 5, 0, 0, 1, 0,
             0, 0, 0, 0, 1, 1, 0, {}),
            # Connected peer whose last notification is older than 30s.
            (0, 0, 0, 1, 0x20030000, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 1, 1, 0,
             {22: {0: 0, 1: 0}, 26: {0: 60001, 1: 0},
              27: {0: 60001, 1: 0}}),
            # Worker loop, bounded nonfatal cadence. All query returns zero.
            (0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
             0, 0, {}),
            # Worker timeout at call 18: signed elapsed 600000us enters the
            # production fatal reporting cadence (delay/query/log forever).
            (0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
             0, 0, {18: {0: 600000, 1: 0}}),
            # Same fatal family with master-only sync and alternate log sink;
            # its worker clock is call 20 because sync/update precede it.
            (1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1,
             0, 0, {20: {0: 600000, 1: 0}}),
        )
    ],
    # Radio timer arming: exercise both production clock modes and the
    # high-duration request path.  The last case forces the 0x6f6 assertion
    # fallthrough, whose result bit is derived from deadline+0x29.
    ("net", 0x01020a6c): [
        ({0: 0, 1: 1000, 2: 3},
         [(0x210015f7, b"\x00"), (0x2100160c, (0x40).to_bytes(2, "little")),
          (0x4100c54c, (2000).to_bytes(4, "little")),
          (0x0103c5b6, (10).to_bytes(2, "little"))],
         {0: {0: 1}, 1: {0: 0}, 5: {0: 0, 1: 0}}),
        ({0: 0, 1: 1000, 2: 3},
         [(0x210015f7, b"\x01"), (0x2100160c, (0x40).to_bytes(2, "little")),
          (0x4100c54c, (2000).to_bytes(4, "little")),
          (0x0103c5b6, (10).to_bytes(2, "little"))],
         {0: {0: 1}, 1: {0: 0}, 5: {0: 0, 1: 0}}),
        ({0: 1, 1: 1000, 2: 3},
         [(0x210015f7, b"\x00"), (0x2100160c, (0x96).to_bytes(2, "little")),
          (0x4100c54c, (0).to_bytes(4, "little"))],
         {0: {0: 1}, 1: {0: 0}, 2: {0: 0, 1: 0}, 5: {0: 1}}),
    ],
    ("app", 0x00026418): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(0x14) + active.to_bytes(4, "little") +
           bytes((mode, 1, 2, 3, 4, 5)) + bytes(2)),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
          (0x20018c6c, b"\x00"), (0x20018c6d, b"\x00")],
         {1: {0: 0x0bad0000}})
        for active, mode in ((1, 3), (0, 3), (0, 4), (0, 5))
    ],
    ("app", 0x00021da8): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(0x250) + (emu.SCRATCH + 0x4000).to_bytes(4, "little") * 2 +
           bytes(0x10c) + bytes((send_state,)) + bytes(3)),
          (emu.SCRATCH + 0x5000 + 0x105c, b"\x80\x00"),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
          (0x2000302e, bytes((pending,))),
          (0x20018da9, bytes((f1,))),
          (0x20007550, f4.to_bytes(4, "little"))],
         {0: {0: init_rc}, 2: {0: emu.SCRATCH + 0x6000},
          3: {0: emu.SCRATCH + 0x5000}, 4: ({0: receive, 1: receive_hi} if receive_hi else {0: receive}),
          6: {0: state}, 7: {0: error}})
        for receive, receive_hi, pending, f1, f4, send_state, state, error, init_rc in (
            # receive: short boundary, long boundary
            (0, 0, 0xff, 0, 0, 0, 1, 0, 0),
            (0, 0, 0xff, 0, 0, 0, 1, 0, 0),
            # receive miss: F5 ordinary/special, F1, F4, and idle
            (1, 0x12345678, 8, 0, 0, 0, 1, 0, 0),
            (1, 0x12345678, 9, 0, 0, 0, 1, 0, 0),
            (1, 0x12345678, 0xff, 1, 0, 0, 1, 0, 0),
            (1, 0x12345678, 0xff, 0, 1, 0, 1, 0, 0),
            (1, 0x12345678, 0xff, 0, 0, 0, 1, 0, 0),
            # send-state terminal arms: controller error and nonzero state
            (1, 0x12345678, 8, 0, 0, 1, 0, 0, 0),
            (1, 0x12345678, 8, 0, 0, 1, 0, 7, 0),
            (1, 0x12345678, 8, 0, 0, 1, 5, 0, -5),
        )
    ] + [
        # Controller-not-ready once, then ready: exercise the wait/backedge
        # before receiving and sending a short packet.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(0x250) + (emu.SCRATCH + 0x4000).to_bytes(4, "little") * 2 + bytes(0x10c)),
          (emu.SCRATCH + 0x5000 + 0x105c, b"\x00\x00"),
          (emu.SCRATCH + 0x7000 + 0x105c, b"\x80\x00"),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4)), (0x2000302e, b"\xff")],
         {0: {0: 0}, 2: {0: emu.SCRATCH + 0x6000},
          3: {0: emu.SCRATCH + 0x5000}, 5: {0: emu.SCRATCH + 0x7000}, 6: {0: 0}}),
    ] + [
        # Enabled diagnostics, once per sink.  The first case reaches every
        # level-3 site (startup, init failure, allocation, ready, and the
        # direct controller error); the second uses level 2 to prove the
        # level-3 sites stay off while the level-2 state error stays on.
        ({0: emu.SCRATCH + 0x1000, 2: 0xa5a55a5a},
         [(emu.SCRATCH + 0x1000,
           bytes(0x250) + (emu.SCRATCH + 0x4000).to_bytes(4, "little") * 2 +
           bytes(0x10c) + b"\x01" + bytes(3)),
          (emu.SCRATCH + 0x5000 + 0x105c, b"\x80\x00"),
          (0x2000230c, (3).to_bytes(4, "little")),
          (0x20007554, sink.to_bytes(4, "little")),
          (0x2000302e, b"\x08"), (0x20018da9, b"\x00"),
          (0x20007550, bytes(4))],
         {1: {0: 0xfffffffb}, 4: {0: emu.SCRATCH + 0x6000},
          6: {0: emu.SCRATCH + 0x5000},
          7: {0: 1, 1: 0x12345678}, 9: {0: 0}, 11: {0: 7}})
        for sink in (0, 7)
    ] + [
        ({0: emu.SCRATCH + 0x1000, 2: 0x11223344},
         [(emu.SCRATCH + 0x1000,
           bytes(0x250) + (emu.SCRATCH + 0x4000).to_bytes(4, "little") * 2 +
           bytes(0x10c) + b"\x01" + bytes(3)),
          (emu.SCRATCH + 0x5000 + 0x105c, b"\x80\x00"),
          (0x2000230c, (2).to_bytes(4, "little")),
          (0x20007554, sink.to_bytes(4, "little")),
          (0x2000302e, b"\x08"), (0x20018da9, b"\x00"),
          (0x20007550, bytes(4))],
         {0: {0: 0}, 2: {0: emu.SCRATCH + 0x6000},
          3: {0: emu.SCRATCH + 0x5000},
          4: {0: 1, 1: 0x12345678}, 6: {0: 5}})
        for sink in (0, 7)
    ] + [
        # A receive miss must bypass all pending-global synthesis when work is
        # already queued.  Cover both the short-slot and long-buffer states.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(0x250) + (emu.SCRATCH + 0x4000).to_bytes(4, "little") * 2 +
           bytes(0x100) + long_len.to_bytes(4, "little") +
           slot.to_bytes(4, "little") + (3).to_bytes(4, "little") + bytes(4)),
          (emu.SCRATCH + 0x5000 + 0x105c, b"\x80\x00"),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
          (0x2000302e, b"\x09"), (0x20018da9, b"\x01"),
          (0x20007550, (1).to_bytes(4, "little"))],
         {0: {0: 0}, 2: {0: emu.SCRATCH + 0x6000},
          3: {0: emu.SCRATCH + 0x5000},
          4: {0: 1, 1: 0x12345678}})
        for long_len, slot in ((0, 1), (5, 0))
    ] + [
        # Allocation failure is retained in context+0x10 but does not prevent
        # the worker from servicing its caller-owned packet buffers.
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(0x250) + (emu.SCRATCH + 0x4000).to_bytes(4, "little") * 2 +
           bytes(0x10c)),
          (emu.SCRATCH + 0x5000 + 0x105c, b"\x80\x00"),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
          (0x2000302e, b"\xff")],
         {0: {0: 0}, 2: {0: 0}, 3: {0: emu.SCRATCH + 0x5000},
          4: {0: 0}}),
    ],
    # Firmware transport: bound the heap and driver callbacks explicitly.
    # Cover allocation failure and one successful zero-payload transmit that
    # exits at the first register-write failure, without allowing random
    # callback words to become retry counts or heap pointers.
    ("app", 0x00030340): [
        ({0: 1, 1: 2, 2: 0, 3: 0}, [], {0: {0: 0}}),
        ({0: 1, 1: 2, 2: 0, 3: 0},
         [(0x20007bc0, (emu.SCRATCH + 0x1800).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1800, (0x00080001).to_bytes(4, "little") * 2),
          (emu.SCRATCH + 0x1000, bytes(0x40))],
         {0: {0: emu.SCRATCH + 0x1000}, 1: {0: 0}, 2: {0: 0},
          3: {0: 1}}),
    ],
    # Persistent flash-export worker: keep logging quiet and force the
    # connection check into the short path.  Stable gate/oracle values bound
    # the production thread while prefix comparison validates repeated state.
    ("app", 0x000324bc): [
        ({}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4)),
              (0x00087bf0, bytes(0x20)),
              (emu.SCRATCH + 0x1000, bytes(0x788) +
               (0x00080001).to_bytes(4, "little") + bytes(0x8a4))],
         {0: {0: 0, 1: 0}, 1: {0: 0, 1: 0},
          **{i: ({0: emu.SCRATCH + 0x1000, 1: 0}
                  if i >= 4 and (i - 4) % 5 == 0 else {0: 0, 1: 0})
             for i in range(2, 202)}}),
    ],
    # Permanent brightness worker.  Its selector lives in the queue-owned
    # context, not an ABI argument, so CFG argument taint cannot discover it.
    # Drive every semantic switch arm plus boundary/default values explicitly.
    # The callback slot is a deterministic external Thumb target.  Clock
    # ordinals differ for callback and pre-action arms; force the second clock
    # beyond five seconds so each selected arm reaches completion.  Prefix
    # comparison then bounds the production thread without a callee write that
    # would conceal later modes.
    ("app", 0x00023844): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(0x1040) +
           (0x00080001).to_bytes(4, "little") + bytes(8) +
           mode.to_bytes(4, "little") + bytes(0xb0)),
          (0x200079c4, bytes(4)), (0x2000230c, bytes(4)),
          (0x200079d4, ((0x1c0000 if mode == 0x16 else 0)).to_bytes(4, "little"))],
         ({4: {0: 0, 1: 0}, 6: {0: 0x10000000, 1: 0}}
          if mode in (1, 2, 3, 6, 7, 8, 0xb) else
          {5: {0: 0, 1: 0}, 7: {0: 0x10000000, 1: 0}}
          if mode in (0x11, 0x3e) else
          {3: {0: 0, 1: 0}, 5: {0: 0x10000000, 1: 0}}))
        for mode in (0, 1, 2, 3, 4, 6, 7, 8, 0xb, 0x11, 0x16, 0x17,
                     0x19, 0x1a, 0x1b, 0x3e)
    ],
    ("app", 0x0002a4f4): [
        ({0: 0x11223344, 1: 0xaabbccdd, 2: 0x55667788, 3: 0x99aabbcc},
         [(emu.SCRATCH + 0x1000, b"\x00\x08"),
          (0x20018d88, b"\x00"), (0x20018d94, b"\x00"),
          (0x200040c8, bytes(8))],
         {0: {0: 0}, 2: {0: emu.SCRATCH + 0x1000}, 6: {0: 0xfffffff0}}),
        ({0: 0x11223344, 1: 0xaabbccdd, 2: 0x55667788, 3: 0x99aabbcc},
         [(emu.SCRATCH + 0x1000, b"\x00\x01"),
          (0x20018d88, b"\x00"), (0x20018d94, b"\x00"),
          (0x200040c8, bytes(8))],
         {0: {0: 1}, 2: {0: emu.SCRATCH + 0x1000}, 4: {0: 0xfffffff0}}),
    ],
    # Hard-float fusion update: the reciprocal-square-root helper returns its
    # float in s0 while preserving the state object in r0.  Random oracle r0
    # values turn that production ABI into unrelated writes, so pin both
    # helper returns to the reviewed state object and cover disabled/enabled
    # integral feedback with a finite unit quaternion.
    ("app", 0x00026624): [
        ({0: emu.SCRATCH + 0x1800},
         [(emu.SCRATCH + 0x1800,
           bytes(4) + (0x3f000000).to_bytes(4, "little") +
           gain.to_bytes(4, "little") +
           (0x3f800000).to_bytes(4, "little") + bytes(0x18))],
         {0: {0: emu.SCRATCH + 0x1800},
          1: {0: emu.SCRATCH + 0x1800}})
        for gain in (0x00000000, 0x3dcccccd)
    ],
    # Timer insertion with an empty delta queue.  Exercise the real insertion
    # and head-notification path while keeping lock/query oracles successful.
    ("app", 0x00074bf4): [
        ({0: emu.SCRATCH + 0x2c00, 1: 0x1234, 2: 0, 3: 0},
         [(emu.SCRATCH + 0x2c00, bytes(24)),
          (0x20002cfc, (0x20002cfc).to_bytes(4, "little") * 2),
          (0x200069e0, (0).to_bytes(8, "little"))],
         {0: {0: 1}, 2: {0: 0}, 3: {0: 1}}),
    ],
    # Scheduler handoff: the hardware status word owns loop termination.  These
    # production-shaped states cover one-time initialization, the mode-1 fast
    # exit, privileged and unprivileged completed waits, and invalid mode.
    ("app", 0x00060788): [
        ({0: 0}, [(0x2000b094, (0).to_bytes(4, "little"))],
         {0: {0: 0}}),
        ({0: 1}, [(0x2000b094, (1).to_bytes(4, "little")),
                  (0x5000541c, (2).to_bytes(4, "little"))], {}),
        ({0: 2}, [(0x2000b094, (1).to_bytes(4, "little")),
                  (0x50005418, (0x10002).to_bytes(4, "little"))],
         {0: {0: 1}}),
        ({0: 2}, [(0x2000b094, (1).to_bytes(4, "little")),
                  (0x2001d564, b"\x01"),
                  (0x50005418, (0x10002).to_bytes(4, "little"))],
         {0: {0: 0}}),
        ({0: 3}, [(0x2000b094, (1).to_bytes(4, "little"))], {}),
    ],
    # JSON string writer: valid output cursors plus bounded NUL-terminated
    # strings cover direct copy, short escapes and the unicode escape helper.
    ("app", 0x000644f8): [
        ({0: 0, 1: 0}, [], {}),
        ({0: 0, 1: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, (emu.SCRATCH + 0x2000).to_bytes(4, "little") +
           (emu.SCRATCH + 0x2000).to_bytes(4, "little") +
           (emu.SCRATCH + 0x2100).to_bytes(4, "little"))],
         {0: {0: emu.SCRATCH + 0x2000}}),
        ({0: emu.SCRATCH + 0x1100, 1: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1100, b"json\0"),
          (emu.SCRATCH + 0x1000, (emu.SCRATCH + 0x2000).to_bytes(4, "little") +
           (emu.SCRATCH + 0x2000).to_bytes(4, "little") +
           (emu.SCRATCH + 0x2100).to_bytes(4, "little"))],
         {0: {0: emu.SCRATCH + 0x2000}}),
        ({0: emu.SCRATCH + 0x1100, 1: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1100, b"a\n\x01\\\"\0"),
          (emu.SCRATCH + 0x1000, (emu.SCRATCH + 0x2000).to_bytes(4, "little") +
           (emu.SCRATCH + 0x2000).to_bytes(4, "little") +
           (emu.SCRATCH + 0x2100).to_bytes(4, "little"))],
         {0: {0: emu.SCRATCH + 0x2000}}),
    ],
    # Cross-thread producer request.  The consumer publishes its buffer and
    # waits for state+0x110; pointer-derived read transitions below model the
    # producer acknowledgement without fixed emulator addresses.
    ("app", 0x00084a54): [
        ({0: emu.SCRATCH + 0x1100, 1: 0, 2: 9},
         [(emu.SCRATCH + 0x1100, (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x173c, (7).to_bytes(4, "little"))], {}),
        ({0: emu.SCRATCH + 0x1100, 1: emu.SCRATCH + 0x1300, 2: 4},
         [(emu.SCRATCH + 0x1100, (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x173c, (7).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1300, bytes(4))],
         {0: {0: emu.SCRATCH + 0x1300}}),
        ({0: emu.SCRATCH + 0x1100, 1: emu.SCRATCH + 0x1300, 2: 4},
         [(emu.SCRATCH + 0x1100, (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x173c, (7).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1300, b"\0\1\0\0")],
         {0: {0: emu.SCRATCH + 0x1300}}),
        ({0: emu.SCRATCH + 0x1100, 1: emu.SCRATCH + 0x1300, 2: 4},
         [(emu.SCRATCH + 0x1100, (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x173c, (7).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1300, bytes(4))],
         {0: {0: emu.SCRATCH + 0x1300}}),
    ],
    # Object setup followed by a callee-owned cleanup walk.  Keep allocation
    # results in mapped scratch memory and terminate every cleanup sequence
    # explicitly instead of treating arbitrary oracle words as list nodes.
    ("app", 0x0008349c): [
        ({0: 0}, [], {0: {0: 0}, 1: {0: 0}}),
        ({0: 0}, [],
         {0: {0: emu.SCRATCH + 0x1000},
          1: {0: emu.SCRATCH + 0x1004}, 2: {0: 0},
          3: {0: 0}}),
        ({0: emu.SCRATCH + 0x0200}, [],
         {0: {0: emu.SCRATCH + 0x1000},
          1: {0: emu.SCRATCH + 0x1004}, 2: {0: 0},
          3: {0: 1}, 4: {0: 0}, 5: {0: 0}}),
        ({0: emu.SCRATCH + 0x0200}, [],
         {0: {0: emu.SCRATCH + 0x1000},
          1: {0: emu.SCRATCH + 0x1004}, 2: {0: 0},
          3: {0: 0}, 4: {0: 0}, 5: {0: 0}, 6: {0: 0}}),
        ({0: emu.SCRATCH + 0x0200}, [],
         {0: {0: emu.SCRATCH + 0x1000},
          1: {0: emu.SCRATCH + 0x1004}, 2: {0: 0},
          3: {0: 0}, 4: {0: 0}, 5: {0: 1}, 6: {0: 5},
          7: {0: 0}, 8: {0: 0}}),
        ({0: 0}, [],
         {0: {0: 0}, 1: {0: emu.SCRATCH + 0x1200}, 2: {0: 3},
          3: {0: 0}, 4: {0: 0}}),
    ],
    # Signed scale conversion.  Boundary products exercise the modular
    # high-word correction; distinct i64 results at each oracle prove the
    # complete d8f8 -> ec34 -> ldivmod dataflow and both quotient/remainder
    # output words.
    ("app", 0x000125c0): [
        ({0: emu.SCRATCH + 0x0200, 1: p2, 2: p3},
         [(emu.SCRATCH + 0x0200, bytes(8))],
         {0: {0: 0x11223344, 1: 0x3ff12345},
          1: {0: 0x55667788, 1: 0x40023456},
          2: {0: scaled & 0xffffffff, 1: (scaled >> 32) & 0xffffffff},
          3: {0: quotient & 0xffffffff, 1: (quotient >> 32) & 0xffffffff,
              2: remainder & 0xffffffff, 3: (remainder >> 32) & 0xffffffff}})
        for p2, p3, scaled, quotient, remainder in (
            (0x7fffffff, 2, 2500001, 2, 500001),
            (0x80000000, 0xffffffff, -2500001, -2, -500001),
            (0xffffffff, 0x80000000, 0x100000001, 4294, 967297),
        )
    ],
    # Persistent ANCS worker. Direct and buffered level-three diagnostics,
    # level-one post-start diagnostics, and level-zero suppression are kept as
    # distinct production paths.  Every timeout register pair is therefore
    # defined by the original path rather than caller-scratch normalization.
    ("app", 0x00019718): [
        ({0: emu.SCRATCH + 0x0200},
         [(emu.SCRATCH + 0x0200, bytes(0x240)),
          (emu.SCRATCH + 0x1000, b"\x00\x01" + bytes(0x105c)),
          (0x2000230c, (3).to_bytes(4, "little")), (0x20007554, bytes(4))],
         {i: {0: emu.SCRATCH + 0x1000} for i in range(6, 206, 2)})
        ,({0: emu.SCRATCH + 0x0200},
          [(emu.SCRATCH + 0x0200, bytes(0x240)),
           (emu.SCRATCH + 0x1000, b"\x00\x08" + bytes(0x105c)),
           (0x2000230c, (3).to_bytes(4, "little")), (0x20007554, bytes(4))],
          {i: {0: emu.SCRATCH + 0x1000}
           for base in range(6, 206, 3) for i in (base, base + 1)})
        ,({0: emu.SCRATCH + 0x0200},
          [(emu.SCRATCH + 0x0200, bytes(0x240)),
           (emu.SCRATCH + 0x1000, bytes(0x1060)),
           (0x2000230c, (3).to_bytes(4, "little")), (0x20007554, bytes(4))],
          {i: {0: emu.SCRATCH + 0x1000}
           for base in range(6, 206, 4) for i in (base, base + 1, base + 2)})
        ,*[
          ({0: emu.SCRATCH + 0x0200},
           [(emu.SCRATCH + 0x0200, bytes(0x240)),
            (emu.SCRATCH + 0x1000, bytes(0x105c) + b"\x80\x00"),
            (0x20006aac, (0x12345678).to_bytes(4, "little") + bytes([event_count]) + bytes(3)),
            (0x2000230c, (3).to_bytes(4, "little")),
            (0x20007554, sink.to_bytes(4, "little"))],
           {**{i: {0: emu.SCRATCH + 0x1000}
               for base in range(6, 206, 12) for i in (base, base + 1, base + 2)},
            **{base + 5: {0: 0} for base in range(6, 206, 12)}})
          for event_count, sink in ((1, 0), (2, 0), (1, 1), (2, 1))
        ],
        # Level one suppresses only the initial >2 diagnostic.  Every later
        # >0 diagnostic remains, shifting each twelve-call iteration by one.
        ({0: emu.SCRATCH + 0x0200},
         [(emu.SCRATCH + 0x0200, bytes(0x240)),
          (emu.SCRATCH + 0x1000, bytes(0x105c) + b"\x80\x00"),
          (0x20006aac, (0x12345678).to_bytes(4, "little") + b"\x01\0\0\0"),
          (0x2000230c, (1).to_bytes(4, "little")),
          (0x20007554, bytes(4))],
         {**{i: {0: emu.SCRATCH + 0x1000}
              for base in range(5, 205, 12)
              for i in (base, base + 1, base + 2)},
          **{base + 5: {0: 0} for base in range(5, 205, 12)}}),
        # Level zero suppresses all diagnostics.  The event-count-one path has
        # eight calls per completed worker iteration after the five-call setup.
        ({0: emu.SCRATCH + 0x0200},
         [(emu.SCRATCH + 0x0200, bytes(0x240)),
          (emu.SCRATCH + 0x1000, bytes(0x105c) + b"\x80\x00"),
          (0x20006aac, (0x12345678).to_bytes(4, "little") + b"\x01\0\0\0"),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4))],
         {**{i: {0: emu.SCRATCH + 0x1000}
              for base in range(5, 205, 8)
              for i in (base, base + 1, base + 2)},
          **{base + 4: {0: 0} for base in range(5, 205, 8)}}),
    ],
    # Queue insertion: model a valid owner/pool/item relation and force the
    # lookup oracle to return the required 16-byte key size.  The busy state
    # then exercises the lookup/unlock return path without a synthetic panic.
    ("app", 0x000710b4): [
        ({0: emu.SCRATCH + 0x1000, 1: 0x11223344, 2: 0x55667788,
          3: emu.SCRATCH + 0x1300},
         [(emu.SCRATCH + 0x10ac, (emu.SCRATCH + 0x1500).to_bytes(4, "little")),
          (emu.SCRATCH + 0x10a0, (emu.SCRATCH + 0x1600).to_bytes(4, "little")),
          (emu.SCRATCH + 0x10a8, (emu.SCRATCH + 0x1700).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1500, (emu.SCRATCH + 0x12f0).to_bytes(4, "little") +
           bytes(4) + (0x100).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1618, (1).to_bytes(4, "little")),
          (emu.SCRATCH + 0x12f8, (0x1234).to_bytes(4, "little"))],
         {0: {0: 16}}),
    ],
    ("app", 0x0005774c): [
        ({0: emu.SCRATCH + 0x1000, 1: 7},
         [(emu.SCRATCH + 0x10b4, b"\x02")], {}),
        ({0: emu.SCRATCH + 0x1000, 1: 7},
         [(emu.SCRATCH + 0x10b4, b"\x03"),
          (emu.SCRATCH + 0x101c, (1).to_bytes(4, "little"))],
         {0: {0: 0}, 1: {0: 5}, 2: {0: 1}}),
        ({0: emu.SCRATCH + 0x1000, 1: 7},
         [(emu.SCRATCH + 0x10b4, b"\x03"),
          (emu.SCRATCH + 0x104c, (0).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1080, (0).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1004, (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x121c, (0).to_bytes(4, "little"))],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0}}),
    ],
    ("app", 0x00057b60): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1200},
         [(emu.SCRATCH + 0x101c, (0).to_bytes(4, "little"))], {0: {0: 0}}),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1200},
         [(emu.SCRATCH + 0x101c, (1).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1018, (8).to_bytes(2, "little")),
          (emu.SCRATCH + 0x1210, (9).to_bytes(2, "little"))], {0: {0: 1}}),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1200},
         [(emu.SCRATCH + 0x101c, (1).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1018, (8).to_bytes(2, "little")),
          (emu.SCRATCH + 0x1210, (1).to_bytes(2, "little"))], {0: {0: 1}}),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1200},
         [(emu.SCRATCH + 0x101c, (1).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1016, (4).to_bytes(2, "little")),
          (emu.SCRATCH + 0x1018, (8).to_bytes(2, "little")),
          (emu.SCRATCH + 0x1210, (3).to_bytes(2, "little"))],
         {0: {0: 1}, 1: {0: 5}}),
    ],
    # Packed-nibble adapter: the diagnostic helper returns the next bounded
    # low nibble in r1. Cover direct success, one diagnostic recovery, and a
    # repeated diagnostic before recovery without allowing a synthetic
    # unbounded assertion loop.
    ("app", 0x000640e8): [
        ({0: emu.SCRATCH + 0x0100, 1: 3, 2: 4}, [], {}),
        ({0: emu.SCRATCH + 0x0100, 1: 3, 2: 15}, [],
         {0: {1: 14}}),
        ({0: emu.SCRATCH + 0x0100, 1: 3, 2: 15}, [],
         {0: {1: 15}, 1: {1: 14}}),
    ],
    # Audio converters operate on caller-owned production buffers. Random
    # state bytes manufacture very large loops; seed the minimum layout, a
    # two-lane layout, and the special six-lane boundary instead.
    **{
        ("app", va): [
            ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000, 2: 1},
             [(emu.SCRATCH + 0x1000, bytes([channels, 0, mode]) + bytes(0x49d)),
              (emu.SCRATCH + 0x14a0, (emu.SCRATCH + 0x3000).to_bytes(4, "little")),
              (emu.SCRATCH + 0x14a4, (emu.SCRATCH + 0x4000).to_bytes(4, "little")),
              (emu.SCRATCH + 0x2000, bytes(range(1, 65)))], {})
            for channels, mode in ((0, 0), (0, 1), (0, 4))
        ] for va in (0x00068d2c, 0x00068d90, 0x00068de8)
    },
    # Packet submission owns a credit CAS loop. The acquire helper's return
    # must describe the same reviewed counter state; an unrelated random word
    # makes the real firmware retry forever. Cover empty credits plus direct
    # packet-clone failure for both reserve selectors. The latter also proves
    # the compensating atomic credit increment.
    ("app", 0x0005757c): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1100, 2: 0},
         [(emu.SCRATCH + 0x102c, (0).to_bytes(4, "little"))],
         {0: {0: 0}}),
    ] + [
    ] + [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1100, 2: reserve},
         [(emu.SCRATCH + 0x1028, (0x40).to_bytes(2, "little")),
          (emu.SCRATCH + 0x102c, (1).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1104, (0).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1110, (8).to_bytes(2, "little"))],
         {0: {0: 1}, 1: {0: 16}, 2: {0: 16}, 3: {0: 0}})
        for reserve in (0, 1)
    ],
    # ATT teardown owns several queue-drain loops whose dequeue helpers decide
    # termination. Cover the null-owner exit and a non-null/busy owner while
    # forcing the first queue empty; unconstrained oracle words never empty.
    ("app", 0x00059834): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x0ff8, (0).to_bytes(4, "little"))], {}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x0ff8, (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x111c, (0).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1230, (1).to_bytes(4, "little"))],
         {1: {0: 0}}),
    ],
    # The ATT parser's first lookup is allowed to report no handler group.
    # Pin that explicit exit instead of interpreting a random oracle word as
    # a traversable intrusive-list base.
    ("app", 0x0005c5f0): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1100, 2: 0}, [],
         {0: {0: 0}}),
    ],
    # Connection-complete handler: seed its packet pointer and bound the
    # allocator/oracle decisions. This avoids copying unconstrained stack
    # output that the address-validation helper owns.
    ("app", 0x00054444): [
        ({0: emu.SCRATCH + 0x0600},
         [(emu.SCRATCH + 0x060c, (emu.SCRATCH + 0x0700).to_bytes(4, "little")),
          (emu.SCRATCH + 0x0700, (0x0042).to_bytes(2, "little")),
          (emu.SCRATCH + 0x070a, (0x0010).to_bytes(2, "little"))],
         {0: {0: emu.SCRATCH + 0x0900}, 1: {0: 0}, 2: {0: 0}}),
    ],
    # Queue drain terminates only when its dequeue oracle reports empty.
    ("app", 0x00056300): [
        ({0: emu.SCRATCH + 0x0800, 1: 0},
         [(emu.SCRATCH + 0x0814, (0).to_bytes(4, "little")),
          (emu.SCRATCH + 0x081c, (0).to_bytes(4, "little"))],
         {0: {0: 0}}),
    ],
    # Synchronous HCI completion: bound the command-index helpers and make the
    # wait complete normally. Random oracle returns otherwise force every run
    # into the production SVC fatal path and never exercise status handling.
    ("app", 0x00053d70): [
        ({0: 0x201a, 1: emu.SCRATCH + 0x0200, 2: 0},
         [(0x2000abf4, (0).to_bytes(1, "little"))],
         {1: {0: 0}, 4: {0: 0}, 5: {0: 0}}),
        ({0: 0x201a, 1: emu.SCRATCH + 0x0200, 2: emu.SCRATCH + 0x0300},
         [(0x2000abf4, (9).to_bytes(1, "little"))],
        {1: {0: 0}, 4: {0: 0}, 5: {0: 0}}),
    ],
    # One bounded event and a successful first poll.  k_poll's reviewed write
    # contract above initializes the event state consumed by this thread.
    ("app", 0x000545f0): [
        # Poll failure reaches the first inlined SVC at 0x5463e.
        ({}, [], {0: {0: 0}, 1: {0: 1}, 2: {0: 0}}, {}),
        # Type-4/state-0 with an empty dequeue reaches the second inlined SVC
        # site at 0x54688.  k_poll owns the event-state write, so fixtures model
        # it as that oracle's exact output rather than pre-seeding stale state.
        ({}, [], {0: {0: 0}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0}},
         {1: [(0, 12, (4 << 14).to_bytes(4, "little"), 0x000755f8)]}),
        # Ignored event type, connection event, unknown event, and successful
        # buffer event cover every production dispatch family before looping.
        ({}, [], {0: {0: 0}, 1: {0: 0}},
         {1: [(0, 12, (2 << 14).to_bytes(4, "little"), 0x000755f8)]}),
        ({}, [(0x20002944 + 16, (emu.SCRATCH + 0x2038).to_bytes(4, "little"))],
         {0: {0: 0}, 1: {0: 0}},
         {1: [(0, 12, ((4 << 14) | 1).to_bytes(4, "little"), 0x000755f8)]}),
        ({}, [], {0: {0: 0}, 1: {0: 0}},
         {1: [(0, 12, (5 << 14).to_bytes(4, "little"), 0x000755f8)]}),
        ({}, [(emu.SCRATCH + 0x2000, bytes(0x80)),
              (0x20002140, bytes(4))],
         {0: {0: 0}, 1: {0: 0}, 2: {0: emu.SCRATCH + 0x2000},
          3: {0: 0}, 4: {0: emu.SCRATCH + 0x2100}, 5: {0: 0}},
         {1: [(0, 12, (4 << 14).to_bytes(4, "little"), 0x000755f8)]}),
        # A pre-existing pending payload publishes the exact two-word
        # diagnostic before release, then installs and processes the dequeued
        # buffer normally.  This is the only production path that consumes the
        # 0xf313c record, so keep its logger at exact ordinal four.
        ({}, [(emu.SCRATCH + 0x2000, bytes(0x80)),
              (emu.SCRATCH + 0x2200, bytes(0x40)),
              (0x20002140,
               (emu.SCRATCH + 0x2200).to_bytes(4, "little"))],
         {0: {0: 0}, 1: {0: 0}, 2: {0: emu.SCRATCH + 0x2000},
          3: {0: 0}, 6: {0: emu.SCRATCH + 0x2100}, 7: {0: 0}},
         {1: [(0, 12, (4 << 14).to_bytes(4, "little"), 0x000755f8)]}),
        # Buffer processing failure publishes its exact diagnostic, releases
        # the wait event, resolves the controller slot/handle, reports the
        # failed buffer and frees it before the event loop advances.
        ({}, [(emu.SCRATCH + 0x2000, bytes(0x80)),
              (0x20002140, bytes(4)),
              (0x2000abf4 + 14, (0x1234).to_bytes(2, "little"))],
         {0: {0: 0}, 1: {0: 0}, 2: {0: emu.SCRATCH + 0x2000},
          3: {0: 0}, 4: {0: emu.SCRATCH + 0x2100}, 5: {0: 7},
          8: {0: 1}},
         {1: [(0, 12, (4 << 14).to_bytes(4, "little"), 0x000755f8)]}),
    ],
    # The formatter's first helper return is a bounded encoded length (11 bits),
    # not an arbitrary fuzz word.  Cover the unformatted path plus formatted
    # allocation failure/success without manufacturing recursive overflow logs.
    ("app", 0x0004d944): [
        ({0: 0x1111, 1: 0, 2: emu.SCRATCH + 0x200, 3: 0x2222}, [],
         {0: {0: emu.SCRATCH + 0x1000}}),
        ({0: 0x1111, 1: 0x200, 2: emu.SCRATCH + 0x200, 3: 0x2222}, [],
         {0: {0: 4}, 1: {0: 0}}),
        ({0: 0x1111, 1: 0x200, 2: emu.SCRATCH + 0x200, 3: 0x2222}, [],
         {0: {0: 4}, 1: {0: emu.SCRATCH + 0x1000}, 2: {0: 0}}),
    ],
    # Iterator termination and lookup results are callee-owned. Cover empty,
    # immediate match, one rejected candidate, and allocation-failure fatal.
    ("app", 0x0004ed3c): [
        ({0: 0x1111, 1: emu.SCRATCH + 0x0200}, [], {0: {0: 0}}),
        ({0: 0x1111, 1: emu.SCRATCH + 0x0200},
         [(emu.SCRATCH + 0x0300, (0xa5a5a5a5).to_bytes(4, "little"))],
         {0: {0: 0x2222}, 1: {0: emu.SCRATCH + 0x0300}, 2: {0: 0}}),
        ({0: 0x1111, 1: emu.SCRATCH + 0x0200},
         [(emu.SCRATCH + 0x0300, (0xa5a5a5a5).to_bytes(4, "little"))],
         {0: {0: 0x2222}, 1: {0: emu.SCRATCH + 0x0300},
          2: {0: 1}, 3: {0: 0}}),
        ({0: 0x1111, 1: emu.SCRATCH + 0x0200}, [],
         {0: {0: 0x2222}, 1: {0: 0}}),
    ],
    # SPI helpers obtain their private state from the first oracle and then
    # dispatch through the device vtable at state+0x374.  Seed exactly that
    # production object shape and use the standard external callback target.
    ("app", 0x000476b4): [
        ({}, [(emu.SCRATCH + 0x0744, (emu.SCRATCH + 0x1000).to_bytes(4, "little")),
              (emu.SCRATCH + 0x0774, (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
              (emu.SCRATCH + 0x1208, (0x00080001).to_bytes(4, "little"))],
         {0: {0: emu.SCRATCH + 0x0400}}),
    ],
    ("app", 0x00047724): [
        ({1: 0x13579bdf},
         [(emu.SCRATCH + 0x0774, (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1208, (0x00080001).to_bytes(4, "little"))],
         {0: {0: emu.SCRATCH + 0x0400}}),
    ],
    ("app", 0x00080872): [
        ({0: emu.SCRATCH + 0x1200, 1: emu.SCRATCH + 0x1300,
          2: 0, 3: emu.SCRATCH + 0x1400}, [], {0: {0: 0}}),
        ({0: emu.SCRATCH + 0x1200, 1: emu.SCRATCH + 0x1300,
          2: 0, 3: emu.SCRATCH + 0x1400}, [],
         {0: {0: 1}, 1: {0: 0}, 2: {0: 0}}),
        ({0: emu.SCRATCH + 0x1200, 1: emu.SCRATCH + 0x1300,
          2: 0, 3: emu.SCRATCH + 0x1400}, [],
         {0: {0: 1}, 1: {0: 0}, 2: {0: 1}}),
        ({0: emu.SCRATCH + 0x1200, 1: emu.SCRATCH + 0x1300,
          2: 0, 3: emu.SCRATCH + 0x1400}, [],
         {0: {0: 1}, 1: {0: 1}, 2: {0: 0}, 3: {0: 1}}),
        ({0: emu.SCRATCH + 0x1200, 1: emu.SCRATCH + 0x1300,
          2: 0, 3: emu.SCRATCH + 0x1400}, [],
         {0: {0: 1}, 1: {0: 1}, 2: {0: 1}, 3: {0: 0}, 4: {0: 1}}),
    ],
}


def _queue_globals(level, sink):
    return [(0x2000230c, int(level).to_bytes(4, "little")),
            (0x20007554, int(sink).to_bytes(4, "little"))]


# The logger can run long enough for the volatile charge byte to change.  The
# original reloads after the call; make that ordering observable with an exact,
# target-bound absolute write from each logging implementation.
REVIEWED_ORACLE_CASES[("app", 0x000327c4)] = [
    ({}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4)),
          # Bit six and bit seven are independently live in the no-log path.
          # This distinguishes the recovered 0x7f mask from a weaker 0x3f.
          (0x20019ef4, b"\xc0")], {}, {}),
    ({}, [(0x2000230c, (3).to_bytes(4, "little")),
          (0x20007554, bytes(4)), (0x20019ef4, b"\x7f")], {},
     # The logger changes both the high/status bit and leaves bit six set.
     # The return must therefore reload, clear bit seven, and preserve bit six.
     {0: [(None, 0x20019ef4, b"\xc1", 0x0007dda4)]}),
    ({}, [(0x2000230c, (3).to_bytes(4, "little")),
          (0x20007554, (1).to_bytes(4, "little")),
          (0x20019ef4, b"\xff")], {},
     {0: [(None, 0x20019ef4, b"\x02", 0x00019c70)]}),
]


# The queue result is a real branch selector but random oracle values almost
# never exercise success.  Pair each result with both logging implementations.
REVIEWED_ORACLE_CASES[("app", 0x000244a8)] = [
    ({0: 7, 2: 0x11223344}, _queue_globals(3, sink), {0: {0: 0}})
    for sink in (0, 1)
] + [
    ({0: 7, 2: 0x11223344}, _queue_globals(1, sink), {0: {0: 1}})
    for sink in (0, 1)
]


def _enqueue_case(active, count, level, sink, enqueue_result=0):
    queue = bytearray(0x28)
    queue[0x10:0x14] = int(active).to_bytes(4, "little")
    queue[0x24:0x28] = int(count).to_bytes(4, "little")
    calls = {}
    if active:
        # Full queues first dequeue and log; otherwise the enqueue is call 1
        # after the level-gated uid diagnostic (or call 0 with logging off).
        enqueue_ordinal = (2 if count == 10 else (1 if level else 0))
        calls[enqueue_ordinal] = {0: enqueue_result}
    return (
        {0: emu.SCRATCH + 0x1000, 2: 0x55667788},
        [(emu.SCRATCH + 0x1000, bytes.fromhex("78563412f0debc9a")),
         (0x20006a38, bytes(queue)), *_queue_globals(level, sink)],
        calls,
    )


REVIEWED_ORACLE_CASES[("app", 0x00018e48)] = [
    _enqueue_case(0, 0, 0, 0),
    _enqueue_case(1, 0, 1, 0, 0),
    _enqueue_case(1, 0, 1, 1, 1),
    _enqueue_case(1, 10, 0, 0, 0),
    _enqueue_case(1, 10, 0, 1, 0),
]


def _dashboard_flash_case(ready, callback_result=0, record=None,
                          level=0, sink=0):
    api = bytearray(0x1034)
    api[0x1030:0x1034] = (0x00080001).to_bytes(4, "little")
    memory = [
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
        (0x00087bf0, (0x13579bdf).to_bytes(4, "little")),
        (emu.SCRATCH + 0x1000, bytes(api)),
        (emu.SCRATCH + 0x2400, bytes(0x40)),
    ]
    # At level three the initial "read setting" diagnostic precedes the flash
    # readiness/accessor/callback sequence.  Keep every callee-owned result and
    # output write attached to its actual shifted ordinal; otherwise the valid
    # record silently lands on an accessor rather than the callback.
    prefix = int(level > 2)
    oracles = {prefix: {0: int(bool(ready))}}
    writes = {}
    if ready:
        oracles.update({prefix + 1: {0: emu.SCRATCH + 0x1000},
                        prefix + 2: {0: emu.SCRATCH + 0x2400},
                        prefix + 3: {0: callback_result}})
        if record is not None:
            callback_ordinal = prefix + 3
            # Bind the three-byte output effect to the installed flash-read
            # callback identity at its exact (possibly log-shifted) ordinal.
            writes[callback_ordinal] = [
                (2, 0, bytes(record), 0x00080000)]
    return ({0: 0x10203040, 1: 0xa5000000, 2: 0x50607080},
            memory, oracles, writes)


REVIEWED_ORACLE_CASES[("app", 0x00023df4)] = [
    # Not-ready, read-failure, and successful reads through both log sinks.
    _dashboard_flash_case(False, level=1, sink=0),
    _dashboard_flash_case(False, level=1, sink=1),
    _dashboard_flash_case(True, 1, level=1, sink=0),
    _dashboard_flash_case(True, 1, level=1, sink=1),
    # Level three also covers the initial "read setting" diagnostic.
    _dashboard_flash_case(True, 0, b"\xaa\x00\x05", level=3, sink=0),
    _dashboard_flash_case(True, 0, b"\xaa\x00\x05", level=3, sink=1),
    # Invalid magic and reserved 0xff mode remain separate record semantics.
    _dashboard_flash_case(True, 0, b"\x00\x00\x05"),
    _dashboard_flash_case(True, 0, b"\xaa\x00\xff"),
]


def _watchdog_case(state, level=0, sink=0, callback_results=()):
    device = bytearray(12)
    device[8:12] = (emu.SCRATCH + 0x1000).to_bytes(4, "little")
    vtable = bytearray(8)
    vtable[4:8] = (0x00080001).to_bytes(4, "little")
    memory = [
        (0x20007b50, int(state & 0xffffffff).to_bytes(4, "little")),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
        (0x00087cc8, bytes(device)), (emu.SCRATCH + 0x1000, bytes(vtable)),
    ]
    # Each failed callback is followed by the fixed sleep helper.
    stride = 3 if level > 3 else 2
    first_callback = 1 if level > 3 else 0
    oracles = {first_callback + index * stride: {0: result}
               for index, result in enumerate(callback_results)}
    return ({}, memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x0002aeb4)] = [
    _watchdog_case(-16, 4, 0),
    _watchdog_case(-16, 4, 1),
    _watchdog_case(0, callback_results=(0,)),
    _watchdog_case(0, callback_results=(1, 0)),
    _watchdog_case(0, callback_results=(1, 1, 1, 1, 1)),
    _watchdog_case(0, 4, 0, callback_results=(0,)),
    _watchdog_case(0, 4, 1, callback_results=(0,)),
]


def _gyro_case(level, sink):
    state = bytearray(0x100)
    state[0xef:0xf3] = bytes.fromhex("0000803f")
    state[0xf3:0xf7] = bytes.fromhex("000000c0")
    state[0xf7:0xfb] = bytes.fromhex("00006040")
    return (
        {0: emu.SCRATCH + 0x2000},
        [(emu.SCRATCH + 0x1000, bytes(state)),
         (emu.SCRATCH + 0x2000, b"\x00\x2a"),
         (0x2000230c, int(level).to_bytes(4, "little")),
         (0x20007554, int(sink).to_bytes(4, "little"))],
        {0: {0: emu.SCRATCH + 0x1000},
         1: {0: 0x11111111, 1: 0x22222222},
         2: {0: 0x33333333, 1: 0x44444444},
         3: {0: 0x55555555, 1: 0x66666666}},
    )


REVIEWED_ORACLE_CASES[("app", 0x00036164)] = [
    _gyro_case(0, 0), _gyro_case(3, 0), _gyro_case(3, 1),
]

# Reviewed hard-float arguments, expressed as raw IEEE-754 words keyed by
# s-register index.  These accompany the state/oracle cases above.
def _app_657e4_case(kind):
    mapping = emu.SCRATCH + 0x2000
    config = emu.SCRATCH + 0x1000
    mapping_image = bytearray(0x40)
    config_image = bytearray((2, 0, 1, 0))
    common = {0: {0: 0, 1: mapping}}
    if kind == "helper-fail":
        oracles = {**common, 1: {0: 0}, 2: {0: 1}}
        arg3 = 0
    elif kind == "active-reject":
        mapping_image[1] = 1
        oracles = {**common, 1: {0: 1},
                   2: {0: 1, 1: mapping}}
        arg3 = 0
    else:
        oracles = {**common, 1: {0: 1},
                   2: {0: 0, 1: mapping}}
        arg3 = 0 if kind == "success-null" else config
        if arg3:
            oracles[4] = {0: 0 if kind == "config-reject" else 1}
        if kind == "config-zero":
            config_image[1] = 0
        elif kind == "config-enabled":
            config_image[1] = 2
            config_image[2] = 1
    return ({0: 3, 1: 0, 2: arg3},
            [(mapping, bytes(mapping_image)), (config, bytes(config_image))],
            oracles)


def _app_65b9c_mode_case(group, old_mode, settings):
    table = emu.SCRATCH + 0x2200
    channel = group << 5
    image = bytearray(0x300)
    image[(channel + 0x80) * 4:(channel + 0x80) * 4 + 4] = (
        old_mode << 16).to_bytes(4, "little")
    pending0 = 1 if group == 0 else 0
    pending1 = 1 if group == 1 else 0
    writes = [
        (0x000f6bb7, b"\x00\x01"),
        (0x50842520, pending0.to_bytes(4, "little")),
        (0x50842820, pending1.to_bytes(4, "little")),
        (0x20002bd0, int(settings).to_bytes(2, "little")),
        (table, bytes(image)),
    ]
    requested = (settings >> 2) & 7
    oracles = {0: {0: 0x80000001},
               1: {0: 0, 1: 0},
               2: {0: table}}
    if settings & 0x10:
        oracles.update({3: {0: 0}, 4: {0: table},
                        5: {0: 0}, 6: {0: 0}, 7: {0: table},
                        8: {0: 0}})
        final_ordinal = 8
    else:
        next_ordinal = 3
        # Every non-forced arm first applies one pin mode.
        oracles[next_ordinal] = {0: 0}; next_ordinal += 1
        if ((old_mode == 2 and (requested & 5) == 1) or
                (old_mode != 2 and
                 (requested == 3 or (old_mode == 3 and requested == 2)))):
            oracles[next_ordinal] = {0: 0}; next_ordinal += 1
        oracles[next_ordinal] = {0: table}; next_ordinal += 1
        oracles[next_ordinal] = {0: 0}
        final_ordinal = next_ordinal
    # The exact ordinal varies with the selected mode arm, but the effect is
    # still bound to FUN_00065620 itself.  Only the post-dispatch status query
    # can match any of these ordinals; unrelated helpers receive no write.
    effects = {ordinal: [
        (None, 0x50842520, bytes(4), 0x00065620),
        (None, 0x50842820, bytes(4), 0x00065620),
    ] for ordinal in range(3, 12)}
    return ({}, writes, oracles, effects)


def _app_67600_state(handler=True, status=0, event_flags=0, flags=0,
                     active=0, enabled=1):
    peripheral = emu.SCRATCH + 0x3000
    callback = emu.SCRATCH + 0x1000
    state = bytearray(0x28)
    state[0:4] = ((0x00070001 if handler else 0).to_bytes(4, "little"))
    state[4:8] = (0x11223344).to_bytes(4, "little")
    state[0x1c:0x20] = int(flags).to_bytes(4, "little")
    state[0x20:0x22] = int(status).to_bytes(2, "little")
    state[0x23] = int(active)
    state[0x25] = int(enabled)
    registers = bytearray(0x600)
    registers[0x4c4:0x4c8] = int(event_flags).to_bytes(4, "little")
    return callback, peripheral, state, registers


def _app_6bfc8_count_case(count):
    samples = emu.SCRATCH + 0x1000
    source = emu.SCRATCH + 0x3000
    output = emu.SCRATCH + 0x4000
    table = bytearray(0x104)
    for i in range(min(count, 64)):
        table[i * 4:(i + 1) * 4] = (1).to_bytes(4, "little")
    table[0x100:0x104] = int(count).to_bytes(4, "little")
    return (
        {0: 0, 1: 0, 2: samples, 3: 0},
        [(samples, b"".join(struct.pack("<f", float(i) / 64.0)
                            for i in range(64))),
         (source, b"".join(struct.pack("<f", 0.5 + i / 128.0)
                           for i in range(64))),
         (output, bytes(0x200)), (0x00090c50, bytes(table)),
         (emu.STACK_TOP, source.to_bytes(4, "little")),
         (emu.STACK_TOP + 4, output.to_bytes(4, "little"))],
        ({0: {0: 0}} if 0 < count < 64 else {}),
    )


def _app_71684_fallback_case(kind):
    string = emu.SCRATCH + 0x3000
    context = 0
    writes = [(string, b"unused\0")]
    if kind == "handle-zero":
        oracles = {0: {0: 0}}
        context = emu.SCRATCH + 0x1000
        writes.append((context, bytes(0x1c) + (1).to_bytes(4, "little")))
    elif kind == "name-null":
        oracles = {0: {0: 7}, 2: {0: 0}}
    else:
        oracles = {0: {0: 7}, 2: {0: string}}
        writes[0] = (string, b"\0")
    return ({0: 5, 1: context}, writes, oracles)


def _app_71684_event_case(event):
    """Map the real event-name table so indices two and three are semantic."""
    name = emu.SCRATCH + 0x3200 + event * 0x20
    table = bytearray(20)
    table[event * 4:event * 4 + 4] = name.to_bytes(4, "little")
    return ({0: event, 1: 0},
            [(0x00098658, bytes(table)),
             (name, ("event-%d" % event).encode() + b"\0")],
            {0: {0: 7}, 2: {0: name}})


def _app_723b8_case(kind):
    entry = emu.SCRATCH + 0x1000
    next_entry = emu.SCRATCH + 0x1800
    head = emu.SCRATCH + 0x2000
    item = emu.SCRATCH + 0x3000
    successor = emu.SCRATCH + 0x4000
    entry_image = bytearray(0x20)
    entry_image[0:4] = next_entry.to_bytes(4, "little")
    entry_image[8:12] = item.to_bytes(4, "little")
    entry_image[12:16] = (0 if kind.startswith("acquire") else 1).to_bytes(4, "little")
    entry_image[16:20] = (5).to_bytes(4, "little", signed=True)
    next_image = bytearray(0x20); next_image[0x0e] = 4
    head_image = bytearray(0x20); head_image[0x0e] = 3
    item_image = bytearray(0x20); item_image[0x0e] = 5
    writes = [(entry, bytes(entry_image)), (next_entry, bytes(next_image)),
              (head, bytes(head_image)), (item, bytes(item_image)),
              (successor, bytes(0x20)),
              (0x2000b450, head.to_bytes(4, "little"))]
    overrides = {0: entry, 1: 0, 2: successor, 3: 0x12345678}
    effects = {}
    if kind == "acquire-existing-head":
        entry_image[8:12] = head.to_bytes(4, "little")
        entry_image[12:16] = (2).to_bytes(4, "little")
        writes[0] = (entry, bytes(entry_image))
    if kind == "irq":
        oracles = {}
    elif kind == "lock-fail":
        oracles = {0: {0: 0}}
    elif kind in ("acquire-success", "acquire-existing-head"):
        oracles = {0: {0: 1}, 1: {0: 0}, 2: {0: 1}}
    elif kind == "acquire-unlock-fail":
        oracles = {0: {0: 1}, 1: {0: 0}, 2: {0: 0}}
    elif kind == "successor-zero":
        entry_image[12:16] = (1).to_bytes(4, "little")
        entry_image[16:20] = (3).to_bytes(4, "little", signed=True)
        item_image[0x0e] = 3
        writes[0] = (entry, bytes(entry_image)); writes[3] = (item, bytes(item_image))
        overrides[2] = 0; overrides[3] = 0
        oracles = {0: {0: 1}, 1: {0: 0}, 2: {0: 1}}
    else:
        previous_update = 1 if kind == "previous-update-fail" else 0
        oracles = {0: {0: 1}, 1: {0: 0}, 2: {0: previous_update},
                   3: {0: 1},
                   4: {0: 0 if kind == "reacquire-fail" else 1},
                   5: {0: 0}}
        if kind != "reacquire-fail":
            oracles[6] = {0: 1 if kind == "next-update-fail" else 0}
            if kind not in ("next-update-fail", "previous-update-fail"):
                oracles[7] = {0: 0 if kind == "final-unlock-fail" else 1}
        produced_next = next_entry
        if kind == "next-self":
            produced_next = entry
        elif kind == "next-null":
            produced_next = 0
        elif kind == "next-high-priority":
            next_image[0x0e] = 7
            writes[1] = (next_entry, bytes(next_image))
        elif kind == "next-clamp":
            next_image[0x0e] = 0x80
            writes[1] = (next_entry, bytes(next_image))
        effects = {3: [
            (2, 0, produced_next.to_bytes(4, "little"), 0x00073f6c),
            (2, 8, item.to_bytes(4, "little"), 0x00073f6c),
            (2, 16, (5).to_bytes(4, "little", signed=True), 0x00073f6c),
        ]}
    return (overrides, writes, oracles, effects)


# These reviewed cases supplement the earlier primary-path fixtures.  Keeping
# them separate makes every newly covered semantic family explicit.
REVIEWED_ORACLE_CASES[("app", 0x000657e4)] = [
    _app_657e4_case(kind) for kind in (
        "helper-fail", "active-reject", "success-null", "config-reject",
        "config-zero", "config-enabled",
    )
]
REVIEWED_ORACLE_CASES[("app", 0x00065b9c)] += [
    _app_65b9c_mode_case(1, 0, 0x10 | (7 << 2)),
    _app_65b9c_mode_case(0, 2, 1 << 2),
    _app_65b9c_mode_case(0, 0, 3 << 2),
    _app_65b9c_mode_case(0, 3, 2 << 2),
]
for event_flags in (2, 4, 1):
    callback, peripheral, state, registers = _app_67600_state(
        event_flags=event_flags)
    REVIEWED_ORACLE_CASES[("app", 0x00067600)].append(
        ({0: peripheral, 1: callback},
         [(callback, bytes(state)), (peripheral, bytes(registers))],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0}}))
callback, peripheral, state, registers = _app_67600_state(handler=False)
REVIEWED_ORACLE_CASES[("app", 0x00067600)].append(
    ({0: peripheral, 1: callback},
     [(callback, bytes(state)), (peripheral, bytes(registers))], {}))
callback, peripheral, state, registers = _app_67600_state(status=1)
REVIEWED_ORACLE_CASES[("app", 0x00067600)].append(
    ({0: peripheral, 1: callback},
     [(callback, bytes(state)), (peripheral, bytes(registers))],
     {0: {0: 0}, 1: {0: 0}, 2: {0: 0}}))
# Enter the event-present arm with flag four set: publication must bypass the
# register-clear path and suppress the callback while inactive.
callback, peripheral, state, registers = _app_67600_state(flags=4)
REVIEWED_ORACLE_CASES[("app", 0x00067600)].append(
    ({0: peripheral, 1: callback},
     [(callback, bytes(state)), (peripheral, bytes(registers))],
     {0: {0: 1}, 1: {0: 0}, 2: {0: 1}}))
# Enabled-zero is a distinct clear-state/publication contract.
callback, peripheral, state, registers = _app_67600_state(enabled=0)
REVIEWED_ORACLE_CASES[("app", 0x00067600)].append(
    ({0: peripheral, 1: callback},
     [(callback, bytes(state)), (peripheral, bytes(registers))],
     {0: {0: 0}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0}}))
REVIEWED_ORACLE_CASES[("app", 0x0006bfc8)] += [
    _app_6bfc8_count_case(0), _app_6bfc8_count_case(63),
    _app_6bfc8_count_case(64),
]
REVIEWED_ORACLE_CASES[("app", 0x00071684)] += [
    _app_71684_fallback_case(kind)
    for kind in ("handle-zero", "name-null", "name-empty")
]
REVIEWED_ORACLE_CASES[("app", 0x00071684)] += [
    _app_71684_event_case(2), _app_71684_event_case(3),
]
REVIEWED_ORACLE_CASES[("app", 0x00072880)].append(
    ({0: emu.SCRATCH + 0x1000},
     [(emu.SCRATCH + 0x1000, bytes(8) + (3).to_bytes(4, "little") * 2 +
       bytes(0x20))],
     {0: {0: 1}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0}, 4: {0: 0}}))

# MRS IPSR coverage alternates thread/IRQ state in the generic verifier.  Keep
# every substantive queue case at an even index and place an explicit IRQ
# fatal fixture at each odd index, so no queue outcome is accidentally run in
# exception context.
for kind in (
        "lock-fail", "acquire-success", "acquire-existing-head",
        "acquire-unlock-fail",
        "successor-zero", "reacquire-fail", "next-update-fail",
        "next-self", "next-null", "next-high-priority", "next-clamp",
        "previous-update-fail", "final-unlock-success",
        "final-unlock-fail"):
    REVIEWED_ORACLE_CASES[("app", 0x000723b8)].append(
        _app_723b8_case("irq"))
    REVIEWED_ORACLE_CASES[("app", 0x000723b8)].append(
        _app_723b8_case(kind))


REVIEWED_FP_CASES = {
    # Positive/negative zero, finite values, infinities and NaN cover the
    # ordered/unordered VFP comparisons and both domain-error returns.
    ("app", 0x00075d5c): [
        {0: bits} for bits in (
            0x00000000, 0x80000000, 0x3f000000, 0xbf000000,
            0x7f800000, 0xff800000, 0x7fc00001, 0x00000001)
    ],
    # Double-precision libm reducer: zeros, tiny/medium/unit magnitudes,
    # reduction threshold, infinity and NaN exercise its major exponent arms.
    ("app", 0x00012db0): [
        {0: 0x00000000, 1: 0x00000000},
        {0: 0x00000000, 1: 0x80000000},
        {0: 0xd9d7bdbb, 1: 0x3ddb7cdf},
        {0: 0x00000000, 1: 0x3fe00000},
        {0: 0x66666666, 1: 0x3fe66666},
        {0: 0x00000000, 1: 0x3ff00000},
        {0: 0x00000000, 1: 0x40000000},  # +2.0: positive reduction table
        {0: 0x00000000, 1: 0xc0000000},  # -2.0: negative reduction table
        {0: 0x9999999a, 1: 0x3ff19999},  # +1.1 near reduction threshold
        {0: 0x9999999a, 1: 0xbff19999},  # -1.1 near reduction threshold
        {0: 0x00000000, 1: 0x40862e42},
        {0: 0x00000000, 1: 0x7ff00000},
        {0: 0x00000001, 1: 0x7ff80000},
    ],
    ("app", 0x00075acc): [
        {0:0x00000000,1:0x40000000,2:0x00000000,3:0x40080000}
        for _ in range(6)
    ],
    ("app", 0x0000c358): [
        {0: 0x3f000000, 1: 0x3e800000, 2: 0xbf800000, 3: 0x3dcccccd},
        {0: 0x3f800000, 1: 0xbf000000, 2: 0xbf800000, 3: 0x3e4ccccd},
        {0: 0xbf000000, 1: 0x3f000000, 2: 0x00000000, 3: 0x3d4ccccd},
    ],
    ("app", 0x0000e53c): [
        {0: 0x3f000000, 1: 0x3f800000, 2: 0x3f000000,
         3: 0x42c80000, 4: 0x00000000},
    ],
    ("app", 0x00026624): [
        {0: 0x3dcccccd, 1: 0x3e4ccccd, 2: 0xbd4ccccd,
         3: 0x00000000, 4: 0x00000000, 5: 0x00000000,
         6: 0x3c23d70a},
        {0: 0x3dcccccd, 1: 0x3e4ccccd, 2: 0xbd4ccccd,
         3: 0x3f000000, 4: 0x3f19999a, 5: 0x3f4ccccd,
         6: 0x3c23d70a},
    ],
}

POINTER_READ_TRANSITION_CASES = {
    ("app", 0x00084a54): [
        [(0, 0, 0x110, 1, 1)],
        [(0, 0, 0x110, 1, 1)],
        [(0, 0, 0x110, 1, 1)],
        [(0, 0, 0x110, 1, 1), (0, 0, 0x53c, 2, 8)],
    ],
}

_CHANNEL_OPTION_BYTES = (
    emu.SCRATCH + 0x1600,
    emu.SCRATCH + 0x1604,
    emu.SCRATCH + 0x1608,
)


def _app_85130_case(channel, enabled_fields):
    """Production GPIO channel reduction plus selected optional fields."""
    group = channel >> 5
    assert group in (0, 1)
    base = 0x50842500 if group == 0 else 0x50842800
    reduced = channel & 0x1f
    register = base + reduced * 4 + 0x200
    overrides = {0: channel}
    for argument, address in zip((1, 2, 3), _CHANNEL_OPTION_BYTES):
        overrides[argument] = address if argument in enabled_fields else 0
    memory = [
        (_CHANNEL_OPTION_BYTES[0], b"\x01"),
        (_CHANNEL_OPTION_BYTES[1], b"\x01"),
        (_CHANNEL_OPTION_BYTES[2], b"\x03"),
        (emu.SCRATCH + 0x1800, b"\x02"),
        (emu.SCRATCH + 0x1900, b"\x03"),
        (register, (0xa5a5a5a5).to_bytes(4, "little")),
    ]
    oracles = {0: {0: base}}
    writes = {0: [(0, 0, reduced.to_bytes(4, "little"), 0x00065584)]}
    return overrides, memory, oracles, writes


# Six cases align with the reviewed fifth/sixth stack-argument sequence above:
# none; pull; pull+sense; sense; pull; sense.  Together with r1-r3 they cover
# every optional field independently and in combination on both channel banks.
REVIEWED_ORACLE_CASES[("app", 0x00085130)] = [
    _app_85130_case(3, set()),
    _app_85130_case(35, {1}),
    _app_85130_case(3, {2, 3}),
    _app_85130_case(35, {1, 2, 3}),
    _app_85130_case(3, {1, 2, 3}),
    _app_85130_case(35, {1, 2, 3}),
]

# Arithmetic leaves in this family return a 512-bit value through r0-r7,
# r11, and seven caller-reserved stack words.  An ordinary r0:r1 oracle loses
# most of that semantic result, so these reviewed wrappers execute the exact
# leaf/reducer bytes as one verification unit.  The candidate is free to
# express the same operation with ordinary C arrays.
REVIEWED_INTERNAL_CODE_REGIONS = {
    ("net", 0x010087f0): ((0x01008670, 382),),
    ("net", 0x01008a28): ((0x01008670, 382), (0x01008940, 184)),
    ("net", 0x010089f8): ((0x010083dc, 628), (0x01008940, 184)),
}

# These arithmetic adapters consume fixed pointer ABIs.  Trying smaller nptr
# modes first can manufacture matching fault parity before their private
# multi-register workers execute, so require the production pointer count.
REVIEWED_NPTR_COUNTS = {
    # Exact wrapper contracts must run one substantive pointer mode; trying
    # later modes after a concrete mismatch can manufacture unrelated fault
    # parity and hide a deliberately wrong local payload.
    ("app", 0x0007d696): 0,
    ("app", 0x0007d82e): 2,
    ("app", 0x0008099e): 1,
    ("app", 0x000829f0): 1,
    ("app", 0x00085130): 1,
    ("net", 0x010087f0): 2,  # result[16], value[8]
    ("net", 0x01008a28): 2,  # result[8], value[8]
    ("net", 0x010089f8): 3,  # result[8], left[8], right[8]
}

def core_ctx(core):
    if core in _CACHE: return _CACHE[core]
    if core == "app":
        funcs = json.load(open(SCR + "/app_funcs.json"))["functions"]
        c = dict(srcdir=BASE + "/recon/app/src", read=ax.func_bytes_padded,
                 rawread=ax.read, cb=emu.CODE_BASE, ret=recon_kit._ret_kind,
                 sizes={f["entry"]: f["size"] for f in json.load(open(SCR + "/classified.json"))["functions"]})
    else:
        funcs = json.load(open(SCR + "/net_funcs.json"))["functions"]
        c = dict(srcdir=BASE + "/recon/net/src", read=nx.func_bytes_padded,
                 rawread=nx.read, cb=emu.NET_CODE_BASE, ret=net_recon_kit._ret_kind,
                 sizes={f["entry"]: f["size"] for f in json.load(open(SCR + "/net_funcs.json"))["functions"]})
    c["call_arity_by_target"] = {
        f["entry"]: arity for f in funcs
        if (arity := _decompiled_arity(f)) is not None
    }
    c["call_arity_by_target"].update({
        va: arity for (which, va), arity in CALL_ARITY_OVERRIDES.items()
        if which == core
    })
    c["call_float_arity_by_target"] = {
        va: arity for (which, va), arity in CALL_FLOAT_ARITY_OVERRIDES.items()
        if which == core
    }
    c["call_return_kind_by_target"] = {
        f["entry"]: RETURN_KIND_OVERRIDES.get((core, f["entry"]), c["ret"](f["entry"]))
        for f in funcs
    }
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
        # printf-like loads the two-argument output callback from context+4;
        # a literal island separates the load from later BLX sites.
        0x01039190: {(0, 0x04)},
    }
    # Atomic flag helpers load an object member pointer in-place (`ldr rN,
    # [rN,#0x14]`) and then use the two-operand `adds rN,#4` form.  The linear
    # tracker deliberately handles only explicit three-operand arithmetic, so
    # preserve these reviewed nested-pointer fields explicitly.
    reviewed_data_pointer_slots = {
        0x7ef2e: {(0, 0x14)},
        0x7ef3e: {(0, 0x14)},
    }
    callback_slots.update(reviewed_callback_slots.get(va, ()))
    data_pointer_slots.update(reviewed_data_pointer_slots.get(va, ()))
    return cases, sorted(callback_slots), sorted(data_pointer_slots)

def verify(core, name, trials_random=40, source_override=None):
    ctx = core_ctx(core)
    p = ctx["srcdir"] + "/" + name + ".c"
    if source_override is None and not os.path.exists(p):
        return {"status": "missing"}
    txt = source_override if source_override is not None else open(p).read()
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
    # MRS IPSR selectors are architectural-state controlled rather than
    # argument controlled. Exercise both thread mode and a real external IRQ.
    insns = list(_md.disasm(ctx["rawread"](va, size), va))
    initial_xpsr_overrides = ([0, 16] if any(
        ins.mnemonic == "mrs" and "ipsr" in ins.op_str.lower() for ins in insns) else None)
    if initial_xpsr_overrides:
        ovs = [{}, {}] + ovs
    reviewed_state_cases = REVIEWED_STATE_CASES.get((core, va))
    absolute_movs = None
    if reviewed_state_cases:
        ovs = [case[0] for case in reviewed_state_cases]
        absolute_movs = [case[1] for case in reviewed_state_cases]
    ble_outer_cfg_cases = ()
    if (core, va) == ("app", 0x0001a75c):
        # REVIEWED_STATE_CASES used to replace the generic overrides while the
        # argument-relative selector writes were then overwritten by those
        # cases' absolute packet images.  Materialize the original TBH values
        # as complete production-shaped cases so nested fixtures augment,
        # rather than erase, CFG-derived outer-opcode coverage.
        outer_values = sorted({value for ai, off, value in ptr_cases
                               if ai == 1 and off == 0})
        ble_outer_cfg_cases = tuple(_ble_put_outer_cfg_case(value)
                                    for value in outer_values)
        if absolute_movs is None:
            absolute_movs = [[] for _ in ovs]
        ovs.extend(case[0] for case in ble_outer_cfg_cases)
        absolute_movs.extend(case[1] for case in ble_outer_cfg_cases)
    additional_state_cases = ADDITIONAL_STATE_CASES.get((core, va), ())
    if additional_state_cases:
        if absolute_movs is None:
            absolute_movs = [[] for _ in ovs]
        ovs.extend(case[0] for case in additional_state_cases)
        absolute_movs.extend(case[1] for case in additional_state_cases)
    body = txt[txt.index("*/") + 2:] if "*/" in txt[:400] else txt
    prefix_k = REVIEWED_PREFIX_PROOFS.get((core, va))
    prefix_first = prefix_k is not None
    extra_cflags = []
    if "CFG_VERIFY_NO_IF_CONVERSION" in txt[:400]:
        extra_cflags += ["-fno-if-conversion", "-fno-if-conversion2"]
    extra_cflags = extra_cflags or None
    am = re.search(r'CFG_VERIFY_CALL_ARITIES=([0-4](?:,[0-4])*)', txt[:1000])
    call_arities = ([int(x) for x in am.group(1).split(',')] if am else
                    REVIEWED_CALL_ARITIES.get((core, va)))
    if (core, va) == ("app", 0x0003af04):
        # Two accessors, selected zero-argument mode query, two-argument send,
        # and zero-argument flush.  Registers above those reviewed ABIs are
        # caller scratch and intentionally excluded from the trace.
        call_arities = [0, 0, 0, 2, 0]
    call_float_arities = None
    call_return_kinds = None
    if (core, va) == ("app", 0x00085a9c):
        # FUN_000857e0 leaves an inherited/oracle r1 value which the firmware
        # forwards through the final tail call.  Model the concrete r1:r0 ABI.
        call_return_kinds = ["void", "i32", "i32", "i64", "i32"]
    if (core, va) == ("app", 0x00086f00):
        # FUN_00079528 is catalogued as void, but its final nested conversion
        # leaves the signed result in r0 and this wrapper branches on it.
        # Preserve that caller-visible residual ABI so reviewed +/-/zero
        # adjustment outcomes genuinely select both update arms.
        call_return_kinds = ["i32", "i64", "i32"]
    if (core, va) == ("app", 0x0006c778):
        call_arities = [3] + [1] * 64 + [4, 4]
        call_float_arities = [0] + [1] * 64 + [0, 0]
        call_return_kinds = ["void"] + ["f32"] * 64 + ["void", "void"]
    oracle_memory_writes = REVIEWED_ORACLE_MEMORY_WRITES.get((core, va))
    oracle_memory_copies = REVIEWED_ORACLE_MEMORY_COPIES.get((core, va))
    if (core, va) == ("app", 0x0006c778):
        oracle_memory_copies = {0: [(0, 1, 2)]}
    normalized_stack_pointer_calls = REVIEWED_STACK_POINTER_CALLS.get((core, va))
    paired_stack_initial_words = REVIEWED_PAIRED_STACK_INITIAL_WORDS.get((core, va))
    paired_stack_objects = REVIEWED_PAIRED_STACK_OBJECTS.get((core, va))
    pointer_read_transitions = POINTER_READ_TRANSITION_CASES.get((core, va))
    oracle_overrides = ({0: {0: emu.SCRATCH + 0x1000}}
                        if "CFG_VERIFY_ORACLE0_R0_POINTER" in txt[:400] else None)
    reviewed_oracles = ORACLE_STATE_CASES.get((core, va))
    if (core, va) == ("app", 0x0006ab80):
        # Two pitch-absent and two pitch-present production frames.  The
        # detector's boolean is a callee result, not random test state.
        oracle_overrides = [
            {0: {0: emu.SCRATCH + 0x1020},
             2: {0: emu.SCRATCH + 0x1320},
             3: {0: present}}
            for present in (0, 1, 0, 0)]
    if reviewed_oracles:
        oracle_overrides = reviewed_oracles
        ovs = [{} for _ in reviewed_oracles]
        absolute_movs = [[] for _ in reviewed_oracles]
    if (core, va) == ("app", 0x0001a75c) and reviewed_state_cases:
        # Opcode 6/subop 3 single-packet path calls FUN_000167a8 exactly four
        # times (three stores and the mode test), at call ordinals 1..4 after
        # the initial response memset. Preserve all other oracle results.
        oracle_overrides = [{} for _ in reviewed_state_cases]
        if len(oracle_overrides) > 14:
            oracle_overrides[14] = {
                i: {0: 0x20018000} for i in range(1, 5)
            }
        if len(oracle_overrides) > 17:
            oracle_overrides[17] = {
                i: {0: 0x20018000} for i in range(2, 6)
            }
        for case_index in (27, 29):
            if len(oracle_overrides) > case_index:
                oracle_overrides[case_index] = {
                    i: {0: 0x20018000} for i in range(1, 5)
                }
        for case_index in (28, 30):
            if len(oracle_overrides) > case_index:
                oracle_overrides[case_index] = {
                    i: {0: 0x20018000} for i in range(2, 6)
                }
        if len(oracle_overrides) > 34:
            oracle_overrides[33] = {1: {0: 1}}
            oracle_overrides[34] = {1: {0: 0}}
        if len(oracle_overrides) > 40:
            oracle_overrides[37] = {3: {0: 1}}
            oracle_overrides[38] = {3: {0: 0}}
            oracle_overrides[39] = {1: {0: 1}}
            oracle_overrides[40] = {1: {0: 0}}
        if len(oracle_overrides) > 42:
            oracle_overrides[41] = {6: {0: 1}}
            oracle_overrides[42] = {6: {0: 0}}
        if len(oracle_overrides) > 47:
            oracle_overrides[45] = {5: {0: 0x20018000}, 8: {0: 1}}
            oracle_overrides[46] = {5: {0: 0x20018000}, 8: {0: 0}}
        if len(oracle_overrides) > 51:
            oracle_overrides[48] = {5: {0: 1}}
            oracle_overrides[49] = {5: {0: 0}}
            oracle_overrides[50] = {5: {0: 1}}
            oracle_overrides[51] = {5: {0: 0}}
        if len(oracle_overrides) > 57:
            oracle_overrides[54] = {6: {0: 1}}
            oracle_overrides[55] = {6: {0: 0}}
            oracle_overrides[57] = {6: {0: 1}}
        if len(oracle_overrides) > 72:
            oracle_overrides[59] = {
                1: {0: 0x20018000}, 3: {0: 0x20018000},
                5: {0: 0x20018000}, 8: {0: 1},
            }
            oracle_overrides[60] = {
                1: {0: 0x20018000}, 3: {0: 0x20018000},
                5: {0: 0x20018000}, 8: {0: 0},
            }
            oracle_overrides[61] = {1: {0: 0x20018000}, 2: {0: 0x20018000},
                                    14: {0: 1}}
            oracle_overrides[62] = {1: {0: 0x20018000}, 2: {0: 0x20018000},
                                    14: {0: 0}}
            for case_index in range(63, 73):
                oracle_overrides[case_index] = {
                    1: {0: 0x20018000}, 2: {0: 0x20018000}
                }
        if len(oracle_overrides) > 81:
            for case_index in (73, 74, 75):
                oracle_overrides[case_index] = {1: {0: 0x20018000}}
            oracle_overrides[76] = {1: {0: 0x20018000}, 5: {0: 1}}
            oracle_overrides[77] = {1: {0: 0x20018000}, 5: {0: 0}}
            oracle_overrides[78] = {4: {0: 0x20018000}}
            oracle_overrides[79] = {4: {0: 0x20018000}}
        if len(oracle_overrides) > 90:
            for case_index in range(82, 91):
                oracle_overrides[case_index] = {1: {0: 0x2001f000}}
            oracle_overrides[85][3] = {0: 1}
            oracle_overrides[86][3] = {0: 0}
        if len(oracle_overrides) > 97:
            for case_index in range(91, 98):
                oracle_overrides[case_index] = {1: {0: 0x20018000}}
            oracle_overrides[94][5] = {0: 1}
            oracle_overrides[95][5] = {0: 0}
            oracle_overrides[96][4] = {0: 1}
            oracle_overrides[97][4] = {0: 0}
    combined_cases = REVIEWED_ORACLE_CASES.get((core, va))
    fp_arg_overrides = REVIEWED_FP_CASES.get((core, va))
    if combined_cases:
        ovs = [case[0] for case in combined_cases]
        absolute_movs = [case[1] for case in combined_cases]
        oracle_overrides = [case[2] for case in combined_cases]
        if any(len(case) > 3 for case in combined_cases):
            oracle_memory_writes = [case[3] if len(case) > 3 else {}
                                    for case in combined_cases]
    if (core, va) == ("app", 0x00023844):
        # Per-case completion ordinal.  Modes 0x16/0x17 deliberately continue
        # through their own loop arms and need no synthetic completion write.
        brightness_modes = (0, 1, 2, 3, 4, 6, 7, 8, 0xb, 0x11, 0x16, 0x17,
                            0x19, 0x1a, 0x1b, 0x3e)
        completion_ordinals = (6, 7, 7, 7, 6, 7, 7, 7, 7, 8, None, None,
                               6, 6, 6, 8)
        assert len(combined_cases or ()) == len(brightness_modes)
        oracle_memory_writes = [
            ({ordinal: [(0, 0x104c, (0x15).to_bytes(4, "little"))]}
             if ordinal is not None else {})
            for ordinal in completion_ordinals]
    comp, err = recon.compile_func(body, name, va, extra_cflags=extra_cflags)
    if err: return {"status": "compile-fail"}
    candidate_direct_target_map = dict(recon.LAST_DIRECT_TARGET_MAP)
    if (core, va) == ("app", 0x0001a75c) and os.environ.get("BLE_TRACE_DIAG"):
        candidate_direct_target_map = {}
    cb, ct, cs, cva = comp
    # PC-relative Thumb literal loads can reach 1020 bytes beyond the current
    # instruction (LDR.W/VLDR immediate).  The executable extent deliberately
    # excludes trailing literal pools, but the emulator must still map those
    # input bytes.  Candidates already include their generated literal pool in
    # cb+ct; giving the original only 64 trailing bytes made the two machines'
    # flash state asymmetric (notably expf/atanf, whose pools begin at/after
    # the catalog boundary).
    orig = bytearray(ctx["read"](va, size, 1024))
    for off, replacement in ORIGINAL_BYTE_PATCHES.get((core, va), ()):
        orig[off:off + len(replacement)] = replacement
    orig = bytes(orig)
    rk = RETURN_KIND_OVERRIDES.get((core, va), ctx["ret"](va))
    trials = len(ovs) if (reviewed_state_cases or reviewed_oracles or combined_cases) else len(ovs) + trials_random
    bounded = BOUNDED_RANDOM_ARGS.get((core, va))
    if bounded:
        while len(ovs) < trials:
            n = len(ovs)
            ovs.append({ai: vals[n % len(vals)] for ai, vals in bounded.items()})
    fixed_callbacks = FIXED_EXTERNAL_CALLBACK_ARGS.get((core, va), {})
    if fixed_callbacks:
        while len(ovs) < trials:
            ovs.append({})
        for ov in ovs:
            ov.update(fixed_callbacks)
    callback_setup = [(ai, off, (0x00080001).to_bytes(4, "little"))
                      for ai, off in callback_slots]
    pointer_setup = [(ai, off, (0x20030000 + 0x100 * n).to_bytes(4, "little"))
                     for n, (ai, off) in enumerate(data_pointer_slots)]
    common_setup = callback_setup + pointer_setup
    movs = []
    relative_ptr_cases = (() if ble_outer_cfg_cases else ptr_cases)
    for ai, off, value in relative_ptr_cases:
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
    reviewed_nptr = REVIEWED_NPTR_COUNTS.get((core, va))
    if reviewed_nptr is not None:
        assert reviewed_nptr >= required_nptr
        nptr_modes = (reviewed_nptr,)
    else:
        nptr_modes = tuple(dict.fromkeys(
            n for n in (max(1, required_nptr), 2, 1, 3, 4)
            if n >= required_nptr))
    # Both cores use Zephyr's ARCH_EXCEPT(4): clear BASEPRI, load reason 4,
    # SVC #2. The SVC is a production-noreturn runtime exception even though
    # the compiler emits a defensive BX LR after it.
    terminal_targets = ({0x01008d00, 0x0100ebb8, 0x01014884, 0x01016828, 0x010256dc, 0x01039bb0}
                        if core == "net" else {0x00050af8, 0x0007e2ec})
    if (core, va) == ("app", 0x00078110):
        # Both allocation-failure islands branch to the firmware assertion
        # sink FUN_00076a94.  Instructions after that BL are defensive
        # compiler fallthrough and consume caller-clobbered r1; treating the
        # sink as an ordinary returning oracle manufactures a meaningless
        # retry size.  Compare the exact call prefix through the fatal helper.
        terminal_targets = set(terminal_targets) | {0x00076a94}
    target_call_arities = dict(ctx["call_arity_by_target"])
    target_call_arities.update(REVIEWED_TARGET_CALL_ARITIES.get((core, va), {}))
    format_call_arities = REVIEWED_CALL_ARITIES_BY_FORMAT.get((core, va))
    format_call_stack_arities = REVIEWED_CALL_STACK_ARITIES_BY_FORMAT.get(
        (core, va))
    target_call_stack_arities = REVIEWED_TARGET_CALL_STACK_ARITIES.get(
        (core, va), {})
    orig_internal_code_regions = [
        (address, ctx["rawread"](address, region_size))
        for address, region_size in REVIEWED_INTERNAL_CODE_REGIONS.get((core, va), ())
    ]
    compare_max_insns = 1000000 if orig_internal_code_regions else 200000
    compare_max_resumes = 20000 if orig_internal_code_regions else 5000
    for nptr in nptr_modes:
        if prefix_first:
            v = emu.compare(orig, va, size, cb + ct, cva, cs, code_base=ctx["cb"],
                            trials=trials, nptr=nptr, ret_kind=rk, no_return=True,
                            prefix_k=prefix_k,
                            arg_overrides=ovs, memory_overrides=movs,
                            absolute_memory_overrides=absolute_movs,
                            pointer_read_transitions=pointer_read_transitions,
                            terminal_targets=terminal_targets,
                            oracle_overrides=oracle_overrides, call_arities=call_arities,
                            call_float_arities=call_float_arities,
                            call_return_kinds=call_return_kinds,
                            fp_arg_overrides=fp_arg_overrides,
                            call_arity_by_target=target_call_arities,
                            call_arity_by_format=format_call_arities,
                            call_float_arity_by_target=ctx["call_float_arity_by_target"],
                            call_return_kind_by_target=ctx["call_return_kind_by_target"],
                            call_stack_arity_by_target=target_call_stack_arities,
                            call_stack_arity_by_format=format_call_stack_arities,
                            oracle_memory_writes=oracle_memory_writes,
                            oracle_memory_copies=oracle_memory_copies,
                            normalized_stack_pointer_calls=normalized_stack_pointer_calls,
                            candidate_direct_target_map=candidate_direct_target_map,
                            paired_stack_initial_words=paired_stack_initial_words,
                            paired_stack_objects=paired_stack_objects,
                            initial_xpsr_overrides=initial_xpsr_overrides,
                            orig_internal_code_regions=orig_internal_code_regions,
                            max_insns=compare_max_insns,
                            max_resumes=compare_max_resumes)
        else:
            v = emu.compare(orig, va, size, cb + ct, cva, cs, code_base=ctx["cb"],
                            trials=trials, nptr=nptr, ret_kind=rk, arg_overrides=ovs,
                            memory_overrides=movs, terminal_targets=terminal_targets,
                            absolute_memory_overrides=absolute_movs,
                            pointer_read_transitions=pointer_read_transitions,
                            oracle_overrides=oracle_overrides, call_arities=call_arities,
                            call_float_arities=call_float_arities,
                            call_return_kinds=call_return_kinds,
                            fp_arg_overrides=fp_arg_overrides,
                            call_arity_by_target=target_call_arities,
                            call_arity_by_format=format_call_arities,
                            call_float_arity_by_target=ctx["call_float_arity_by_target"],
                            call_return_kind_by_target=ctx["call_return_kind_by_target"],
                            call_stack_arity_by_target=target_call_stack_arities,
                            call_stack_arity_by_format=format_call_stack_arities,
                            oracle_memory_writes=oracle_memory_writes,
                            oracle_memory_copies=oracle_memory_copies,
                            normalized_stack_pointer_calls=normalized_stack_pointer_calls,
                            candidate_direct_target_map=candidate_direct_target_map,
                            paired_stack_initial_words=paired_stack_initial_words,
                            paired_stack_objects=paired_stack_objects,
                            initial_xpsr_overrides=initial_xpsr_overrides,
                            orig_internal_code_regions=orig_internal_code_regions,
                            max_insns=compare_max_insns,
                            max_resumes=compare_max_resumes)
        if v.get("pass") and type(v.get("checked")) is int and v["checked"] > 0:
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
    # Candidate comments must not grant prefix-only proof authority or choose
    # its comparison length. Conversely, removing all legacy marker text from
    # a reviewed loop must not revoke its table-owned policy.
    ordinary_name = "FUN_01028464"
    ordinary_source = open(BASE + "/recon/net/src/" + ordinary_name + ".c").read()
    ordinary_first = ordinary_source.split("\n", 1)[0]
    injected_source = ordinary_source.replace(
        ordinary_first,
        ordinary_first[:-2] +
        " CFG_VERIFY_PREFIX_FIRST CFG_VERIFY_PREFIX_K=1 */", 1)
    reviewed_name = "FUN_010255a4"
    reviewed_source = open(BASE + "/recon/net/src/" + reviewed_name + ".c").read()
    reviewed_source = re.sub(r'\bCFG_VERIFY_PREFIX_FIRST\b', '', reviewed_source)
    reviewed_source = re.sub(r'\bCFG_VERIFY_PREFIX_K=\d+\b', '', reviewed_source)
    saved_compare = emu.compare
    policy_calls = []
    def _inconclusive_policy_compare(*args, **kwargs):
        policy_calls.append(kwargs)
        return {"pass": False, "checked": 0, "mismatches": 0,
                "detail": "policy fixture"}
    try:
        emu.compare = _inconclusive_policy_compare
        verdict = verify("net", ordinary_name, trials_random=0,
                         source_override=injected_source)
        assert verdict["status"] == "FAIL", verdict
        assert policy_calls and all(
            not call.get("no_return", False) and "prefix_k" not in call
            for call in policy_calls), policy_calls
        policy_calls.clear()
        verdict = verify("net", reviewed_name, trials_random=0,
                         source_override=reviewed_source)
        assert verdict["status"] == "FAIL", verdict
        assert policy_calls and all(
            call.get("no_return") is True and call.get("prefix_k") == 200
            for call in policy_calls), policy_calls
    finally:
        emu.compare = saved_compare

    # These compact wrappers previously passed through pointer-only stack
    # normalization even when their local payload bytes were wrong.  Keep one
    # readable negative source for every repaired contract, including the
    # fifth AAPCS stack argument and the channel helper's input object.
    negative_sources = {
        "FUN_0007d696": (
            "(unsigned short)((value << 8) | ((value >> 8) & 0xffu))",
            "(unsigned short)((value << 8) | (value >> 8))"),
        "FUN_0007d82e": (
            "command[0] = (unsigned char)opcode;",
            "command[0] = (unsigned char)(opcode + 1);"),
        "FUN_0008099e": (
            "struct work_item item = { value, context };",
            "struct work_item item = { context, value };"),
        "FUN_000829f0": (
            "FUN_00082932(param_3, param_4, param_5, text, length);",
            "FUN_00082932(param_3, param_4, param_5, text, "
            "(unsigned short)(length + 1));"),
        "FUN_00085130": (
            "uint32_t index = channel;\n  uintptr_t table = FUN_00065584(&index);",
            "uint32_t index = channel ^ 1u;\n  uintptr_t table = "
            "FUN_00065584(&index);\n  index = channel & 0x1fu;"),
        # FUN_00083dc8 stores all three byte arguments.  Its fourth register
        # used to be hidden by an incorrect arity-three normalization.
        "FUN_000167f4": (
            "FUN_00083dc8(arg0, 0xb, 2, 1)",
            "FUN_00083dc8(arg0, 0xb, 2, 0)"),
        "FUN_000545f0": (
            "if (error != 0) {",
            "if (0) {"),
        "FUN_0005c8d8": (
            "while ((iVar2 = *(volatile int*)(iVar1+0x18)) != 0){",
            "if ((iVar2 = *(volatile int*)(iVar1+0x18)) != 0){"),
        "FUN_00060c00": (
            "((uint32_t)configuration[0x1c] - 3u) < 2u",
            "((uint32_t)configuration[0x1c] - 5u) < 2u"),
        "FUN_00064a88": (
            "result + buffer.length",
            "result + 0"),
        # Positive and negative P exponents must affect the binary scale in
        # the recovered direction.  The production-shaped parser cases catch
        # this one-token semantic reversal before later range/rounding code.
        "FUN_00078110": (
            "scale += exponent_delta;",
            "scale -= exponent_delta;"),
        # Clamp/equality fixtures must reject an off-by-one panel endpoint.
        "clean_fb_data": (
            "if (0x27f < param_5) param_5 = 0x280;",
            "if (0x27f < param_5) param_5 = 0x27f;"),
        # Logged active watchdog attempts compare the complete diagnostic ABI.
        "disable_watchdog": (
            "DEBUG_PRINT(0xa1c6a, 0xa1c85, 0,",
            "DEBUG_PRINT(0xa1c6b, 0xa1c85, 0,"),
        # The post-logger reload is observable through target-bound writes.
        "get_glassbox_charge_percent": (
            "return *(volatile uint8_t *)0x20019ef4UL & 0x7f;",
            "return percent;"),
        # Exact six-word variadic payload rejects reordered converted axes.
        "dump_template_gyro_info": (
            "uVar2,uVar3,uVar4);",
            "uVar4,uVar3,uVar2);"),
        # Exact two-byte transport object catches a wrong screen selector.
        "display_close_screen": (
            "loc[1] = (uint8_t)param_1;",
            "loc[1] = 0;"),
        # Logged success cases make the recovered format/argument ABI live.
        "getDashboardStartUpModeInfofromFlash": (
            "FUN_00019c70(0x0009e9bfUL, 0x0009ed09UL, param_3,\n"
            "                         *(volatile unsigned int*)0x20007554UL);",
            "FUN_00019c70(0x0009e9bfUL, 0x0009ed09UL, param_3,\n"
            "                         0);"),
    }
    for function_name, (correct, wrong) in negative_sources.items():
        source_path = (BASE + "/recon/app/src/" + function_name + ".c")
        source = open(source_path).read()
        assert correct in source, function_name
        verdict = verify("app", function_name, trials_random=8,
                         source_override=source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL", (function_name, verdict)

    # Long-duration display coverage must keep the exact calendar producer
    # ABI, the 604800-second transition into month/day formatting, and every
    # semantically distinct 12-hour conversion arm live.  These were all
    # invisible when only minute/hour cases drove this function.
    calendar_negative_sources = (
        ("FUN_0004a1b8(param_2,calendar);",
         "FUN_0004a1b8(param_2 + 1,calendar);"),
        ("if (0x6977fu < uVar9 - 0x2a300) {",
         "if (0x69780u < uVar9 - 0x2a300) {"),
        ("if ((ushort)(calendar[1] >> 16) < 0xd) {",
         "if ((ushort)(calendar[1] >> 16) < 0xc) {"),
        ("== 0) { calendar[1] = (0xc << 16)",
         "== 1) { calendar[1] = (0xc << 16)"),
        ("(ushort)(calendar[1] >> 16) - 0xc;",
         "(ushort)(calendar[1] >> 16) - 0xb;"),
    )
    calendar_source = open(BASE + "/recon/app/src/FUN_000357dc.c").read()
    for correct, wrong in calendar_negative_sources:
        assert correct in calendar_source, correct
        verdict = verify(
            "app", "FUN_000357dc", trials_random=0,
            source_override=calendar_source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL", (correct, verdict)

    # Net production fixtures must reject the concrete false reconstructions
    # found by the independent cross-audit.  These mutations isolate format
    # families, sparse mode masks, populated controller bits, callback stack
    # argument five, event-name modes, six stacked descriptor fields, ordered
    # multi-node insertion, and the already-linked flag transition.
    net_negative_sources = {
        "FUN_0102bbec": ("case 0x61:", "case 0x62:"),
        "FUN_0102fbd0": ("0x2aU >>", "0x20U >>"),
        "FUN_01030bac": ("unsigned int mask = 1u << bit;",
                           "unsigned int mask = 2u << bit;"),
        "FUN_0103566c": (
            "*(unsigned int *)(uintptr_t)(iVar2 + 0x3c));", "0);"),
        "FUN_010359b8": ("if (param_1 < 5) {",
                           "if ((param_1 >= 3) && (param_1 < 5)) {"),
        "FUN_0103601c": (
            "piVar9[5], piVar9[6], piVar9[7], piVar9[8], piVar9[10]);",
            "0, 0, 0, 0, 0);"),
        "FUN_01037398": (
            "if ((*(signed char *)((int)param_1 + 0xe) != "
            "*(signed char *)((int)puVar4 + 0xe)) &&\n"
            "        (*(signed char *)((int)param_1 + 0xe) < "
            "*(signed char *)((int)puVar4 + 0xe))) {",
            "if (1) {"),
        "FUN_01037768": ("& 0x7f;", "& 0x7e;"),
    }
    for function_name, (correct, wrong) in net_negative_sources.items():
        source_path = BASE + "/recon/net/src/" + function_name + ".c"
        source = open(source_path).read()
        assert correct in source, function_name
        verdict = verify("net", function_name, trials_random=0,
                         source_override=source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL", (function_name, verdict)

    net_directed_negative_sources = (
        ("FUN_0101132c",
         "controller_init.words[0] = 0x01012439u;",
         "controller_init.words[0] = 0x0101243du;"),
        ("FUN_0101132c",
         "PW(0x28) + 4u",
         "PW(0x28) + 8u"),
        ("FUN_010162e0",
         "(volatile void *)(iVar10 + 0x1f)",
         "(volatile void *)(iVar10 + 0x20)"),
        ("FUN_010162e0",
         "(volatile void *)(iVar7 + 0xce)",
         "(volatile void *)(iVar7 + 0xcf)"),
        ("FUN_010162e0",
         "load_packed_u32((volatile void *)puVar9)",
         "load_packed_u32((volatile void *)(puVar9 + 1))"),
        ("FUN_010162e0",
         "uVar1 = *(volatile u8*)(iVar2+0x78);",
         "uVar1 = *(volatile u8*)(iVar2+0x7b);"),
        ("FUN_010162e0", "& 0x1f) |", "& 0x0f) |"),
        ("FUN_01017344",
         "if ((L.local_2e == 1)",
         "if ((L.local_2e == 2)"),
        ("FUN_01038764",
         "ticks_low, ticks_high);",
         "ticks_high, ticks_low);"),
        ("FUN_01038764",
         "(ticks_low | ticks_high) == 0);",
         "ticks_low == 0);"),
        ("FUN_01038764",
         "state[0] = 0;\n    if ((ticks_low | ticks_high) == 0) {",
         "state[0] = 0;\n    if (ticks_low == 0) {"),
        ("FUN_0102fbd0", "0x2aU >>", "0x2eU >>"),
        ("FUN_01030bac", "puVar4[1] > 0xffff", "puVar4[1] > 0x10000"),
        ("FUN_01030bac", "puVar4[0] > 0xffff", "puVar4[0] > 0x10000"),
        ("FUN_0103566c",
         "typedef int (*fnptr)(int, void *, unsigned short, int, unsigned int);",
         "typedef int (*fnptr)(int, void *, short, int, unsigned int);"),
        ("FUN_0103566c", "if (bVar6) {\n        next_state =",
         "if (0) {\n        next_state ="),
        ("FUN_0103566c", "if (iVar2 < 0) {",
         "if (iVar2 != 0) {"),
        ("FUN_0102bbec", "case 0x65:", "case 0x62:"),
        ("FUN_0102bbec", "case 0x67:", "case 0x62:"),
        ("FUN_010359b8", "if (param_1 < 5) {",
         "if (param_1 < 6) {"),
        ("FUN_010359b8",
         "if ((param_2 != 0) && ((*(unsigned int *)(param_2 + 0x1c) & 0x1ff) != 0)) {",
         "if (param_2 != 0) {"),
        ("FUN_010359b8", "DAT_01035aa8 + (unsigned int)iVar3",
         "DAT_01035aa8"),
        ("FUN_0103601c", "uVar6 = uVar6 & ~((int)uVar6 >> 31);",
         "uVar6 = uVar6;"),
        ("FUN_0103601c", "(long long)(int)uVar6 * 0x8000 + 999",
         "(unsigned int)(uVar6 * 0x8000u) + 999"),
        ("FUN_01037398",
         "if ((*(signed char *)((int)param_1 + 0xe) != "
         "*(signed char *)((int)puVar4 + 0xe)) &&\n"
         "        (*(signed char *)((int)param_1 + 0xe) < "
         "*(signed char *)((int)puVar4 + 0xe))) {",
         "if ((*(unsigned char *)((int)param_1 + 0xe) != "
         "*(unsigned char *)((int)puVar4 + 0xe)) &&\n"
         "        (*(unsigned char *)((int)param_1 + 0xe) < "
         "*(unsigned char *)((int)puVar4 + 0xe))) {"),
        ("FUN_01037398", "if (param_1 == (int *)P_01037428) {",
         "if (0) {"),
        ("FUN_01037768", "if (pb[0xd] < 0) {",
         "if ((pb[0xd] < 0) && "
         "(param_1 == *(volatile int *)0x21004b30)) {"),
    )
    for function_name, correct, wrong in net_directed_negative_sources:
        source_path = BASE + "/recon/net/src/" + function_name + ".c"
        source = open(source_path).read()
        assert correct in source, function_name
        verdict = verify("net", function_name, trials_random=0,
                         source_override=source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL", (function_name, verdict)

    # NULL sizing mode and the initial seven/eight-byte output-capacity
    # boundary are independent contracts.  Keep each as a permanent negative
    # gate rather than letting the format-family switch gate stand in for it.
    net_directed_negative_sources = (
        ("FUN_0102bbec",
         "if (param_1 == (undefined4 *)0x0) {",
         "if (0) {"),
        ("FUN_0102bbec",
         "if ((uintptr_t)param_2 < 8u) {",
         "if (0) {"),
        ("FUN_0102bbec",
         "if ((uintptr_t)param_2 < 8u) {",
         "if ((uintptr_t)param_2 <= 8u) {"),
    )
    for function_name, correct, wrong in net_directed_negative_sources:
        source_path = BASE + "/recon/net/src/" + function_name + ".c"
        source = open(source_path).read()
        assert correct in source, (function_name, correct)
        verdict = verify("net", function_name, trials_random=0,
                         source_override=source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL", (function_name, wrong, verdict)

    # These mutations differ only on scalar/length values that aligned-pointer
    # fuzzing used to omit.  Keep the new directed cases as permanent gates.
    directed_negative_sources = (
        # All four stack-selected renderer modes plus formatter, glyph mode,
        # and final flush arguments are independently live.
        ("FUN_000442bc", "case 0:", "case 4:"),
        ("FUN_000442bc", "case 1:", "case 4:"),
        ("FUN_000442bc", "case 2:", "case 4:"),
        ("FUN_000442bc", "case 3:", "case 4:"),
        ("FUN_000442bc",
         "FUN_00086f00((int)display.text_12,0,0x10,",
         "FUN_00086f00((int)display.text_12,0,0x0f,"),
        ("FUN_000442bc", "FUN_0004588c(1,*pbVar9",
         "FUN_0004588c(3,*pbVar9"),
        ("FUN_000442bc", "FUN_0004588c(2,*pbVar9",
         "FUN_0004588c(3,*pbVar9"),
        ("FUN_000442bc",
         "param_2,param_3,param_4,param_5);\n    return 0;",
         "param_2,param_3,param_4,param_4);\n    return 0;"),
        ("FUN_000442bc", "if (param_7 == '\\0') {", "if (0) {"),
        ("FUN_000442bc", "if (pbVar9[1] == 0x3a)", "if (0)"),
        ("FUN_000442bc", "if (*pbVar9 == 0x3a)", "if (0)"),
        # Deterministic packet, queue, timing, and completion contracts.
        ("FUN_0004967c", "if(iVar2 == 0){", "if(iVar2 != 0){"),
        ("FUN_0004967c", "if(iVar2 == 0){", "if(iVar2 <= 0){"),
        ("FUN_0004967c", "if(param_2 < 0xb){", "if(param_2 < 0xa){"),
        ("FUN_0004967c", "packet[0] = 2;", "packet[0] = 3;"),
        ("FUN_0004967c", "packet[2] = (uint8_t)param_2;",
         "packet[2] = (uint8_t)(param_2 + 1);"),
        ("FUN_0004967c", "long long lVar8 = thunk_FUN_00074f68();",
         "long long lVar8 = lVar7;"),
        ("FUN_0004967c", "UINT64_C(1000)", "UINT64_C(999)"),
        ("FUN_0004967c", " | uVar5*0x20000", " | 0"),
        ("FUN_0004967c", " | uVar3*0x20000", " | 0"),
        ("FUN_0004967c", "(uVar5>>0xf)-(uVar3>>0xf)",
         "(uVar5>>0x10)-(uVar3>>0xf)"),
        ("FUN_0004967c", "(unsigned)(uVar4<uVar6)", "0u"),
        ("FUN_0004967c",
         "FUN_00019c70(0x000f001c,0x000f019a, uVar4-uVar6,\n"
         "                       ((uVar5>>0xf)-(uVar3>>0xf)) -",
         "FUN_00019c70(0x000f001c,0x000f019a, uVar4-uVar6,\n"
         "                       ((uVar5>>0x10)-(uVar3>>0xf)) -"),
        ("FUN_0004967c",
         "((uVar5>>0xf)-(uVar3>>0xf)) -\n"
         "                           (unsigned)(uVar4<uVar6));",
         "((uVar5>>0xf)-(uVar3>>0xf)) -\n"
         "                           (unsigned)(uVar4>=uVar6));"),
        ("FUN_0004967c", "FUN_0004904c();", "(void)0;"),
        # The row comparison is capped at 31 bytes: lengths 30/31/32 make
        # both neighboring clamp mutations observable in the compare ABI.
        ("FUN_0003483c",
         "return length < 31U ? length : 31U;",
         "return length < 30U ? length : 30U;"),
        ("FUN_0003483c",
         "return length < 31U ? length : 31U;",
         "return length < 32U ? length : 32U;"),
        # Transport failures are any nonzero errno, including negative ones.
        ("FUN_00047bf8",
         "if (iVar1 != 0) {",
         "if (iVar1 > 0) {"),
        ("FUN_00043a68",
         "if((param_1 & 1) == 0){",
         "if((param_1 & 1) != 0){"),
        ("FUN_00043a68",
         "if((uVar6 & 1U) != 0)",
         "if((uVar6 & 1U) == 0)"),
        ("FUN_00043a68",
         "iVar8 < param_4 - param_2",
         "iVar8 < 1"),
        ("FUN_00043a68",
         "if((uVar14 & 2) != 0)",
         "if((uVar14 & 4) != 0)"),
        ("FUN_00043a68",
         "if(((uint32_t)iVar7 & 2U) != 0)",
         "if(((uint32_t)iVar7 & 4U) != 0)"),
        ("get_glassbox_charge_percent",
         "return *(volatile uint8_t *)0x20019ef4UL & 0x7f;",
         "return *(volatile uint8_t *)0x20019ef4UL & 0x3f;"),
        ("getDashboardStartUpModeInfofromFlash",
         "((unsigned char)local_14 == 0xaa)",
         "(0)"),
        ("FUN_0004e124",
         "*(int*)(param_1+0x20)=local.result.selected;",
         "*(int*)(param_1+0x20)=local.result.selected + 1;"),
        ("FUN_000521fc",
         "puVar1[0] = decoded.value;",
         "puVar1[0] = decoded.value + 1;"),
        ("FUN_000521fc",
         "0x000f349f, 5, 0x00085f8d, parsed.text",
         "0x000f349e, 5, 0x00085f8d, parsed.text"),
        ("FUN_000521fc",
         "0x000f3b6f, 4, 0x00085f97, &parsed.values[2]",
         "0x000f3b6f, 5, 0x00085f97, &parsed.values[2]"),
        ("FUN_000521fc",
         "0x000f3b6f, 4, 0x00085f97, &parsed.values[2]",
         "0x000f3b6f, 4, 0x00085f97, &parsed.values[1]"),
        ("FUN_000521fc",
         "if (puVar1[2] == puVar1[1]) {",
         "if (1) {"),
        ("FUN_000521fc",
         "if (iVar3 == 0) {\n            uVar4 = 7;",
         "if (1) {\n            uVar4 = 7;"),
        ("FUN_00052d58",
         "(unsigned char)(uVar4 / 7);",
         "(unsigned char)(uVar4 / 8);"),
        ("FUN_00065b9c",
         "channel_prefix << 5",
         "channel_prefix << 4"),
        ("FUN_00067600",
         "if ((callback->flags & 4) != 0) {",
         "if (0) {"),
        ("FUN_00067600",
         "irq_field < 0x80u",
         "irq_field < 0x81u"),
        ("FUN_0006bfc8",
         "if (0x3f < iVar8) {",
         "if (0x3e < iVar8) {"),
        ("FUN_00071684",
         "if (event < 5) {",
         "if (event < 2 || event == 4) {"),
        ("FUN_000723b8",
         "entry->acquisitions == 0 || entry->item == head",
         "entry->acquisitions == 0"),
        ("FUN_000723b8",
         "next != entry && next != 0",
         "next != 0"),
        ("FUN_000723b8",
         "if (next_priority <= priority) {",
         "if (1) {"),
        ("FUN_000723b8",
         "if (priority < -127) {\n        priority = -127;",
         "if (priority < -127) {\n        priority = -126;"),
        ("FUN_0002c714",
         "FUN_00033c04(*(byte *)(iVar4 + 0xdd) - 1);",
         "FUN_00033c04(*(byte *)(iVar4 + 0xdd));"),
        ("FUN_0002c714",
         "if ((*(char *)(param_2 + 1) == '\\x06') ||",
         "if ((*(char *)(param_2 + 1) == '\\x05') ||"),
        ("FUN_0002c714",
         "load_u32_le((const void *)(uintptr_t)load_u32_le(param_1 + 0xff0)),",
         "0,"),
        ("FUN_0002c714",
         "uVar9 - 1000",
         "uVar9 - 999"),
        ("FUN_0002c714",
         "sync_to_slave(param_1,0xc,0,0);",
         "sync_to_slave(param_1,0xc,0);"),
        ("FUN_0002c714",
         "sync_to_slave(param_1,8,0,0);",
         "sync_to_slave(param_1,8,0,1);"),
        ("FUN_00032308",
         "param_2 < 5",
         "param_2 < 4"),
        ("FUN_00032308",
         "uVar4 = 4;",
         "uVar4 = 2;"),
        ("FUN_00032308",
         "uVar4 = 3;",
         "uVar4 = 2;"),
        ("FUN_00032308",
         "DEBUG_PRINT(0x000a676d, 0x000a7712, 0x3c1);",
         "DEBUG_PRINT(0x000a676e, 0x000a7712, 0x3c1);"),
        ("FUN_00032308",
         "if (*(int*)0x20007554 == 0)",
         "if (*(int*)0x20007554 != 0)"),
        ("FUN_00032b24",
         "if(param_1!=0){",
         "if(0){"),
        ("FUN_00032b24",
         "param_1==2",
         "param_1==3"),
        ("FUN_00032b24",
         "0x00ffa55aU",
         "0x00ffa55bU"),
        ("FUN_00033b0c",
         "DEBUG_PRINT(format_string, iVar2, value2, value1, value0, param_2, param_3);",
         "DEBUG_PRINT(format_string, iVar2, value2, value1, value0, param_2, param_3 + 1);"),
        ("FUN_00033b0c",
         "FUN_00019c70(format_string, iVar2, value2, value1,\n"
         "                         value0, param_2, param_3);",
         "FUN_00019c70(format_string, iVar2, value2, value1,\n"
         "                         value0, param_2, param_3 + 1);"),
        ("FUN_0007d696",
         "FUN_0007d82e(0x36, &big_endian, sizeof(big_endian));",
         "if (value & 1u) big_endian ^= 1u;\n    "
         "FUN_0007d82e(0x36, &big_endian, sizeof(big_endian));"),
        ("FUN_0007d82e",
         "command[0] = (unsigned char)opcode;",
         "command[0] = (unsigned char)opcode;\n  "
         "if (opcode & 1u) command[0] ^= 1u;"),
        ("FUN_0007d82e",
         "command[0] = (unsigned char)opcode;",
         "command[0] = (unsigned char)opcode;\n  "
         "if (payload_length == 0) command[0] ^= 1u;"),
        ("FUN_000125c0",
         "param_3 * (0u - (param_2 >> 31))",
         "param_3 * (0u + (param_2 >> 31))"),
        ("FUN_000125c0",
         "FUN_0000ec34((uint32_t)multiplied,",
         "FUN_0000ec34(0,"),
        ("FUN_000125c0",
         "(uint32_t)((uint64_t)multiplied >> 32)",
         "0"),
        ("FUN_000125c0",
         "int64_t scaled = FUN_0000ec34",
         "int64_t scaled = (int32_t)FUN_0000ec34"),
        ("FUN_000125c0",
         "(uint32_t)(scaled % 1000000)",
         "(uint32_t)(scaled % 1000001)"),
        ("FUN_00019718",
         "if(*lv>2)",
         "if(*lv>3)"),
        ("FUN_00019718",
         "if(*lv>0)",
         "if(*lv>2)"),
        ("FUN_00019718",
         "if(*lv>0)",
         "if(1)"),
        ("FUN_00019718",
         "FUN_00072908(c+0x200,-1LL)",
         "FUN_00072908(c+0x200,0LL)"),
        ("FUN_00019718",
         "FUN_00086534(c+0x200,0,10)",
         "FUN_00086534(c+0x200,0,9)"),
        ("FUN_00019718",
         "FUN_00086534(c+0x1e8,0,10)",
         "FUN_00086534(c+0x1e8,0,9)"),
        ("FUN_00019718",
         "DEBUG_PRINT(0x99969,0x9b0d8,p3,0,p4)",
         "DEBUG_PRINT(0x99969,0x9b0d8,p3,0,p4+1)"),
        ("FUN_00019718",
         "FUN_00019c70(0x99969,0x9b0d8,p3,*sink,p4)",
         "FUN_00019c70(0x99969,0x9b0d8,p3,*sink,p4+1)"),
        ("FUN_00019718",
         "DEBUG_PRINT(0x9adc7,0x9b0d8)",
         "DEBUG_PRINT(0x9adc8,0x9b0d8)"),
        ("FUN_00019718",
         "FUN_00019c70(0x9adc7,0x9b0d8)",
         "FUN_00019c70(0x9adc8,0x9b0d8)"),
        ("ble_process_req_dispatch",
         "DEBUG_PRINT(0x0009d4e4u, 0x0009e04eu);",
         "DEBUG_PRINT(0x0009d4e5u, 0x0009e04eu);"),
        ("ble_process_req_dispatch",
         "== 6) {",
         "== 5) {"),
        ("ble_process_req_dispatch",
         "load_u16(packet + 2), load_u16(param_3 + 1));",
         "load_u16(param_3 + 1), load_u16(packet + 2));"),
        ("ble_process_req_dispatch",
         "0x8000u,\n                                     0, 0, 0);",
         "0x8001u,\n                                     0, 0, 0);"),
        ("ble_process_req_dispatch",
         "0x8000u,\n                                     0, 0, 0);",
         "0x8000u,\n                                     0, 1, 0);"),
        ("ble_process_req_dispatch",
         "(uint32_t)(command_id - 1) < 0x27u",
         "(uint32_t)(command_id - 1) < 0x28u"),
        ("ble_process_req_dispatch",
         "(uint32_t)(command_id - 0x29u) < 0x1du",
         "(uint32_t)(command_id - 0x29u) < 0x1eu"),
        ("ble_process_req_dispatch",
         "((command_id + 0xfu) & 0xffu) > 5u",
         "((command_id + 0xfu) & 0xffu) > 6u"),
        ("ble_process_req_dispatch",
         "case 0x4c:\n        if (2 < LVL_A) {",
         "case 0x4c:\n        if (1 < LVL_A) {"),
        ("ble_process_req_dispatch",
         "__atomic_fetch_or(P_20007570, 2,",
         "__atomic_fetch_or(P_20007570, 4,"),
        ("ble_process_req_dispatch",
         "P_2000756c, 0xfffffffdu, __ATOMIC_ACQ_REL);",
         "P_2000756c, 0xfffffffbu, __ATOMIC_ACQ_REL);"),
        ("FUN_00078110",
         "if ((*pbVar18 & 0xdf) == 0x50) {",
         "if (*pbVar18 == 0x70) {"),
        ("FUN_00078110",
         "iVar6 = FUN_0000ef12(iVar13);",
         "iVar6 = FUN_0000ef12(iVar13);\n  iVar6 = 1;"),
        ("FUN_00078110",
         "param_6 = 1 - param_6;",
         "param_6 = param_6;"),
        ("FUN_00078110",
         "if (*(volatile int*)(iVar7 + 8) <= iVar17) {",
         "if (0) {"),
    )
    for function_name, correct, wrong in directed_negative_sources:
        source_path = BASE + "/recon/app/src/" + function_name + ".c"
        source = open(source_path).read()
        assert correct in source, function_name
        verdict = verify("app", function_name, trials_random=0,
                         source_override=source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL", (function_name, verdict)

    # The dispatcher uses an acquire load followed by two acquire/release
    # exclusive RMW loops. Side-effect parity alone cannot distinguish an
    # ordinary volatile RMW in a single-thread run, so permanently inspect the
    # generated M33 instruction contract as well.
    dispatch_source = open(
        BASE + "/recon/app/src/ble_process_req_dispatch.c").read()
    dispatch_out, dispatch_err = recon.compile_func(
        dispatch_source, "ble_process_req_dispatch", 0x00021460)
    assert dispatch_err is None, dispatch_err
    dispatch_body, _, dispatch_size, dispatch_va = dispatch_out
    atomic_mnemonics = [
        insn.mnemonic for insn in _md.disasm(
            dispatch_body[:dispatch_size], dispatch_va)
        if insn.mnemonic in ("lda", "ldaex", "stlex", "ldrex", "strex")
    ]
    assert atomic_mnemonics == [
        "lda", "ldaex", "stlex", "ldaex", "stlex"
    ], atomic_mnemonics

    # Volatile reads are not part of the side-effect trace.  Keep the table
    # dump's recovered ordering as a compile-time inspection gate: value0 is
    # fetched first, then the logger selector, then value1/value2.  This is the
    # exact order at 0x33b16..0x33b1a in the shipped image.
    dump_path = BASE + "/recon/app/src/FUN_00033b0c.c"
    dump_source = open(dump_path).read()
    dump_markers = (
        "unsigned int value0 = puVar3[0];",
        "unsigned int buffered = *piVar1;",
        "unsigned int value1 = puVar3[1];",
        "unsigned int value2 = puVar3[2];",
    )
    dump_positions = [dump_source.index(marker) for marker in dump_markers]
    assert dump_positions == sorted(dump_positions), dump_positions
    dump_out, dump_err = recon.compile_func(
        dump_source, "FUN_00033b0c", 0x00033b0c)
    assert dump_err is None, dump_err
    dump_body, _, dump_size, dump_va = dump_out
    dump_insns = list(_md.disasm(dump_body[:dump_size], dump_va))
    multiply = next(index for index, ins in enumerate(dump_insns)
                    if ins.mnemonic.startswith("mul"))
    first_store = next(index for index in range(multiply + 1, len(dump_insns))
                       if dump_insns[index].mnemonic.startswith("str"))
    ordered_loads = [ins for ins in dump_insns[multiply + 1:first_store]
                     if ins.mnemonic.startswith("ldr")]
    assert len(ordered_loads) == 4, [ins.op_str for ins in ordered_loads]
    assert "#4" in ordered_loads[2].op_str, ordered_loads[2].op_str
    assert "#8" in ordered_loads[3].op_str, ordered_loads[3].op_str

    # The floating formatter's hard-float and stacked ABI fields were once
    # absent from the trace.  Each mutation keeps call order/control fixtures
    # intact while corrupting one independently recovered semantic input.
    float_source_path = BASE + "/recon/app/src/FUN_0007712c.c"
    float_source = open(float_source_path).read()
    float_mutations = (
        ("_u.d,\n                            &local_34",
         "0.0,\n                            &local_34"),
        ("FUN_00086e1c(param_1, param_2, local_2c, param_3, param_4)",
         "FUN_00086e1c(param_1, param_2, local_2c, param_3, (outfn)0)"),
        ("FUN_0000dddc(uVar10, uVar11, 0, 0)",
         "FUN_0000dddc(0, 0, 0, 0)"),
        ("FUN_0000ddc8(param_2[0x12], param_2[0x13], 0, 0)",
         "FUN_0000ddc8(0, 0, 0, 0)"),
        ("if (0x47 < bVar12) {", "if (0x47 <= bVar12) {"),
        ("(param_1, param_3, (u32)puVar8, uVar10);",
         "(param_1, param_3, 0, uVar10);"),
        ("(param_1, param_3, (u32)puVar8, uVar10);",
         "(param_1, param_3, (u32)puVar8, 1);"),
        ("(*param_5 + 7U) & 0xfffffff8",
         "(*param_5 + 0U) & 0xfffffff8"),
        ("iVar4 = FUN_00086e1c(param_1, param_2, local_2c, param_3, param_4);\n"
         "  uVar13 = local_30;\n  if (iVar4 == -1) {",
         "iVar4 = FUN_00086e1c(param_1, param_2, local_2c, param_3, param_4);\n"
         "  uVar13 = local_30;\n  if (0) {"),
    )
    for correct, wrong in float_mutations:
        assert correct in float_source, correct
        verdict = verify(
            "app", "FUN_0007712c", trials_random=0,
            source_override=float_source.replace(correct, wrong))
        assert verdict["status"] == "FAIL", (wrong, verdict)

    # A candidate ending after width setup recreates the historical truncated
    # proof: helper calls match, but the formatter's output loops and return
    # policy are absent.  Full-body verification must reject that prefix.
    tail_marker = "  if ((int)(*param_2 << 0x15) < 0) {"
    assert tail_marker in float_source
    truncated_float = (float_source[:float_source.index(tail_marker)] +
                       "  return 0;\n}\n")
    verdict = verify("app", "FUN_0007712c", trials_random=0,
                     source_override=truncated_float)
    assert verdict["status"] == "FAIL", verdict

    # FUN_0100ac98 dispatches on controller RAM rather than an argument, so
    # generic selector taint cannot discover its TBB cases.  Prove that the
    # five reviewed fixtures select modes 0..4, that every valid mode reaches
    # the final packet-copy write, and that the default reaches the real fatal
    # target.  Byte 1 is 0x01 while byte 2 is 0x5a in the preserved-buffer
    # cases, making the recovered +2 access independently observable.
    ac98_va = 0x0100ac98
    ac98_size = TRUE_SIZE_OVERRIDES[("net", ac98_va)]
    ac98_ctx = core_ctx("net")
    ac98_runner = emu.Runner(
        ac98_va, ac98_size, ac98_ctx["read"](ac98_va, ac98_size, 1024),
        code_base=ac98_ctx["cb"])
    ac98_arities = dict(ac98_ctx["call_arity_by_target"])
    ac98_arities.update(REVIEWED_TARGET_CALL_ARITIES[("net", ac98_va)])
    ac98_cases = REVIEWED_ORACLE_CASES[("net", ac98_va)]
    assert len(ac98_cases) == 5, len(ac98_cases)
    for mode, (overrides, writes, oracles) in enumerate(ac98_cases):
        controller_images = [data for address, data in writes
                             if address == _AC98_STATE]
        assert len(controller_images) == 1, (mode, controller_images)
        assert controller_images[0][0xbe] == mode, (mode, controller_images[0][0xbe])
        args = [overrides.get(i, 0) for i in range(4)]
        state = ac98_runner.run(
            mode, args, mode, absolute_memory_overrides=writes,
            terminal_targets={0x01008d00}, oracle_overrides=oracles,
            call_arity_by_target=ac98_arities,
            call_float_arity_by_target=ac98_ctx["call_float_arity_by_target"],
            call_return_kind_by_target=ac98_ctx["call_return_kind_by_target"])
        if mode < 4:
            assert state.get("returned") and not state.get("terminal"), (mode, state)
            expected_byte = 0 if mode == 0 else 0x5a
            assert ("W", 0x21000cfe, 1, expected_byte) in state["events"], (
                mode, state["events"])
        else:
            assert state.get("terminal") and state["call_targets"] == [0x01008d00], state
    ac98_verdict = verify("net", "FUN_0100ac98", trials_random=0)
    assert ac98_verdict["status"] == "PASS", ac98_verdict
    assert ac98_verdict["cover_cases"] == 5, ac98_verdict

    # ble_process_put_req owns a 39-entry pointer-loaded TBH selector.  Its
    # production fixtures must not overwrite the CFG-derived opcode byte, as
    # happened when absolute packet images replaced generic pointee writes.
    ble_ctx = core_ctx("app")
    ble_va = 0x0001a75c
    ble_size = TRUE_SIZE_OVERRIDES[("app", ble_va)]
    ble_ptr_cases, _, _ = pointer_control_inputs(
        ble_ctx["rawread"], ble_va, ble_size)
    ble_commands = sorted({value for ai, off, value in ble_ptr_cases
                           if ai == 1 and off == 0})
    assert ble_commands == list(range(1, 0x28)), ble_commands
    generated_commands = []
    for command in ble_commands:
        overrides, writes = _ble_put_outer_cfg_case(command)
        packet = overrides[1]
        packet_images = [data for address, data in writes if address == packet]
        assert len(packet_images) == 1, (command, packet_images)
        generated_commands.append(packet_images[0][0])
    assert generated_commands == list(range(1, 0x28)), generated_commands
    # A function's executable extent does not include its trailing literal
    # pool.  Mapping only that extent must not be mistaken for a valid
    # differential environment: it turns original PC-relative loads into
    # zero while the compiled candidate still sees its constants.
    # vldr s0,[pc,#4]; bx lr; nop; .float 1.234567
    lit_va = 0x62000
    lit_size = 6
    lit_code = bytes.fromhex("9fed010a" "7047")
    lit_tail = bytes.fromhex("00bf" "4b069e3f")
    v = emu.compare(lit_code, lit_va, lit_size,
                    lit_code + lit_tail, lit_va, lit_size,
                    trials=2, nptr=0, ret_kind="f32")
    assert not v["pass"], v
    v = emu.compare(lit_code + lit_tail, lit_va, lit_size,
                    lit_code + lit_tail, lit_va, lit_size,
                    trials=2, nptr=0, ret_kind="f32")
    assert v["pass"], v
    bad_tail = bytearray(lit_tail)
    bad_tail[-4] ^= 1
    v = emu.compare(lit_code + lit_tail, lit_va, lit_size,
                    lit_code + bytes(bad_tail), lit_va, lit_size,
                    trials=2, nptr=0, ret_kind="f32")
    assert not v["pass"], v
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
    # A callee-owned out-slot must participate in subsequent semantics.  This
    # models wrappers such as FUN_0000e2b4, whose interpolator writes a float
    # to caller stack and whose next action conditionally copies that value.
    def _out_slot_fixture(ret_expr):
        src = ("extern void fill(unsigned *); "
               "unsigned fixture(void){unsigned out; fill(&out); return %s;}"
               % ret_expr)
        out, err = recon.compile_func(src, "fixture", 0x61000)
        assert err is None, err
        return out
    oob, oot, oosz, oova = _out_slot_fixture("out")
    ocb, oct, ocsz, ocva = _out_slot_fixture("out")
    writes = {0: [(0, 0, b"\x78\x56\x34\x12")]}
    v = emu.compare(oob + oot, oova, oosz, ocb + oct, ocva, ocsz,
                    trials=1, nptr=0, oracle_memory_writes=writes,
                    call_arities=[1], normalized_stack_pointer_calls={0: {0}})
    assert v["pass"], v
    # Returning a constant instead of the callee-written word must fail even
    # though the external target, call count, and normalized pointer ABI match.
    ocb, oct, ocsz, ocva = _out_slot_fixture("0")
    v = emu.compare(oob + oot, oova, oosz, ocb + oct, ocva, ocsz,
                    trials=1, nptr=0, oracle_memory_writes=writes,
                    call_arities=[1], normalized_stack_pointer_calls={0: {0}})
    assert not v["pass"], v
    # Hard-float call arguments live in s0-s3, not r0-r3.  A changed s0
    # argument must be observable even when the external call order matches.
    def _float_arity_fixture(expr):
        src = "extern void sink(float); void fixture(float x){sink(%s);}" % expr
        out, err = recon.compile_func(src, "fixture", 0x60000)
        assert err is None, err
        return out
    fob, fot, fosz, fova = _float_arity_fixture("x")
    fcb, fct, fcsz, fcva = _float_arity_fixture("x")
    v = emu.compare(fob + fot, fova, fosz, fcb + fct, fcva, fcsz,
                    trials=2, nptr=0, ret_kind="void", call_arities=[0],
                    call_float_arities=[1])
    assert v["pass"], v
    fcb, fct, fcsz, fcva = _float_arity_fixture("x + 1.0f")
    v = emu.compare(fob + fot, fova, fosz, fcb + fct, fcva, fcsz,
                    trials=2, nptr=0, ret_kind="void", call_arities=[0],
                    call_float_arities=[1])
    assert not v["pass"], v
    # Void ABI has no floating-point return register.  Different dead s0
    # temporaries at return must not become a false result mismatch.
    def _void_return_fixture(value):
        src = ("void fixture(float x){volatile float y=x+%s; (void)y;}" % value)
        out, err = recon.compile_func(src, "fixture", 0x60a00)
        assert err is None, err
        return out
    vob, vot, vosz, vova = _void_return_fixture("0.0f")
    vcb, vct, vcsz, vcva = _void_return_fixture("1.0f")
    v = emu.compare(vob + vot, vova, vosz, vcb + vct, vcva, vcsz,
                    trials=2, nptr=0, ret_kind="void")
    assert v["pass"], v
    v = emu.compare(vob + vot, vova, vosz, vcb + vct, vcva, vcsz,
                    trials=2, nptr=0, ret_kind="f32")
    assert not v["pass"], v
    # External hard-float return values must replace stale pre-call s0 state.
    # The two callers intentionally leave different temporaries in s0 before
    # invoking the same zero-argument oracle.  They are equivalent when its
    # reviewed f32 ABI is modeled, and observably different under the old GPR-
    # only oracle behavior.  Changing the consumer remains a negative control.
    def _float_return_fixture(pre, result):
        src = ("extern float get_value(void); "
               "float fixture(float x){volatile float y=x+%s; (void)y; "
               "return %s;}" % (pre, result))
        out, err = recon.compile_func(src, "fixture", 0x60800)
        assert err is None, err
        return out
    rob, rot, rosz, rova = _float_return_fixture("0.0f", "get_value()")
    rcb, rct, rcsz, rcva = _float_return_fixture("1.0f", "get_value()")
    v = emu.compare(rob + rot, rova, rosz, rcb + rct, rcva, rcsz,
                    trials=2, nptr=0, ret_kind="f32", call_arities=[0],
                    call_float_arities=[0], call_return_kinds=["f32"])
    assert v["pass"], v
    v = emu.compare(rob + rot, rova, rosz, rcb + rct, rcva, rcsz,
                    trials=2, nptr=0, ret_kind="f32", call_arities=[0],
                    call_float_arities=[0])
    assert not v["pass"], v
    rcb, rct, rcsz, rcva = _float_return_fixture("1.0f", "get_value()+1.0f")
    v = emu.compare(rob + rot, rova, rosz, rcb + rct, rcva, rcsz,
                    trials=2, nptr=0, ret_kind="f32", call_arities=[0],
                    call_float_arities=[0], call_return_kinds=["f32"])
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
    # Architectural-state coverage: an IPSR predicate agrees with itself in
    # thread and handler modes, while the historical constant-zero stand-in is
    # rejected specifically by the handler-mode case.
    ipsr_predicate = bytes.fromhex("eff30580" "0038" "18bf" "0120" "7047")
    constant_zero = bytes.fromhex("0020" "7047")
    v = emu.compare(ipsr_predicate, 0x50000, len(ipsr_predicate),
                    ipsr_predicate, 0x50000, len(ipsr_predicate), trials=2,
                    nptr=0, initial_xpsr_overrides=[0, 16])
    assert v["pass"], v
    v = emu.compare(ipsr_predicate, 0x50000, len(ipsr_predicate),
                    constant_zero, 0x50000, len(constant_zero), trials=2,
                    nptr=0, initial_xpsr_overrides=[0, 16])
    assert not v["pass"] and v["mismatches"] == 1, v
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
    # System-reset helper: DSB; SCB AIRCR read/modify/write; DSB; idle loop.
    assert nx.read(0x0102f4ec, 26) == bytes.fromhex(
        "bff34f8f0549064bca6802f4e0621343cb60bff34f8f00bffde7")
    # Guard the sole IT-state workaround against silently drifting to another
    # instruction sequence or address.
    assert ax.read(0x00087172, 6) == bytes.fromhex("bcbf8b232b60")
    # 0x10333e4 is the ADDS inside FUN_010333b4's configuration-copy loop,
    # not a callable entry: two loads precede it and BNE at 0x10333ec targets
    # 0x10333de.  This immutable owner evidence prevents a mid-function catalog
    # split from manufacturing a second ABI/function.
    assert nx.read(0x010333de, 16) == bytes.fromhex(
        "144618685968083303c4ab422246f7d1")
    # Stabilizing an oracle-return pointer must preserve differential strength:
    # identical dereferences pass, while a changed loaded result still fails.
    def _oracle_ptr_fixture(expr):
        src = "extern unsigned *getp(void); unsigned fixture(void){return %s;}" % expr
        out, err = recon.compile_func(src, "fixture", 0x60000)
        assert err is None, err
        return out
    ob, ot, osz, ova = _oracle_ptr_fixture("*getp()")
    cb, ct, csz, cva = _oracle_ptr_fixture("*getp()")
    ov = {0: {0: emu.SCRATCH + 0x1000}}
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz,
                    trials=1, nptr=0, oracle_overrides=ov)
    assert v["pass"], v
    cb, ct, csz, cva = _oracle_ptr_fixture("*getp() + 1")
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz,
                    trials=1, nptr=0, oracle_overrides=ov)
    assert not v["pass"], v
    # Reviewed call arity ignores only non-argument stale registers and still
    # rejects any changed true argument.
    def _arity_fixture(expr):
        src = "extern void sink(unsigned); void fixture(unsigned x){sink(%s);}" % expr
        out, err = recon.compile_func(src, "fixture", 0x60000)
        assert err is None, err
        return out
    ob, ot, osz, ova = _arity_fixture("x")
    cb, ct, csz, cva = _arity_fixture("x")
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz,
                    trials=2, nptr=0, ret_kind="void", call_arities=[1])
    assert v["pass"], v
    cb, ct, csz, cva = _arity_fixture("x + 1")
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz,
                    trials=2, nptr=0, ret_kind="void", call_arities=[1])
    assert not v["pass"], v
    # Reviewed local-pointer normalization equates only two genuine stack
    # addresses. Changing the last true argument to NULL must still fail.
    def _local_pointer_fixture(use_null):
        last = "(void*)0" if use_null else "&local"
        src = ("extern void sink(unsigned,unsigned,unsigned,void*);"
               "void local_fixture(void){unsigned local=0;"
               "sink(1,2,3,%s);}" % last)
        out, err = recon.compile_func(src, "local_fixture", 0x62000)
        assert err is None, err
        return out
    ob, ot, osz, ova = _local_pointer_fixture(False)
    cb, ct, csz, cva = _local_pointer_fixture(False)
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz,
                    trials=1, nptr=0, ret_kind="void", call_arities=[4],
                    normalized_stack_pointer_calls={0: {3}})
    assert v["pass"], v
    cb, ct, csz, cva = _local_pointer_fixture(True)
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz,
                    trials=1, nptr=0, ret_kind="void", call_arities=[4],
                    normalized_stack_pointer_calls={0: {3}})
    assert not v["pass"], v
    # Reviewed stack-object identity is stricter than arbitrary stack-pointer
    # elision: compiler-shifted objects compare by identity+interior offset,
    # declared extent, and complete call-boundary contents.
    def _stack_object_fixture(pad_size, second=7, third=9, pointer_offset=0):
        src = ("extern void sink(void*); void fixture(void){"
               "volatile unsigned char pad[%d]; volatile unsigned char object[4];"
               "object[0]=42; object[1]=%d; object[2]=%d; object[3]=11;"
               "sink((void*)(object+%d));"
               "pad[0]=0;}" % (pad_size, second, third, pointer_offset))
        out, err = recon.compile_func(src, "fixture", 0x62000)
        assert err is None, err
        return out
    # GCC 12.2 layouts verified by the emitted prologues: object is entry-SP-12
    # without the pad and entry-SP-76 with the 64-byte pad.
    ob, ot, osz, ova = _stack_object_fixture(1)
    cb, ct, csz, cva = _stack_object_fixture(64)
    objects = [("fixture-object", -12, -76, 4)]
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=objects)
    assert v["pass"], v
    cb, ct, csz, cva = _stack_object_fixture(64, second=8)
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=objects)
    assert not v["pass"], v
    cb, ct, csz, cva = _stack_object_fixture(64, pointer_offset=1)
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=objects)
    assert not v["pass"], v
    # Complete reviewed input records may themselves contain compiler-local
    # pointers.  Normalize each such word to its paired object identity while
    # keeping every surrounding byte exact; redirecting the embedded pointer
    # to another interior offset must still fail.
    def _embedded_stack_pointer_fixture(pad_size, pointer_offset=0):
        src = ("extern void sink(void*); void fixture(void){"
               "volatile unsigned char pad[%d]; void *object[1];"
               "object[0]=(void*)((unsigned char*)object+%d);sink(object);"
               "pad[0]=0;}" % (pad_size, pointer_offset))
        out, err = recon.compile_func(src, "fixture", 0x62000)
        assert err is None, err
        return out
    ob, ot, osz, ova = _embedded_stack_pointer_fixture(1)
    cb, ct, csz, cva = _embedded_stack_pointer_fixture(64)
    embedded_objects = [
        ("embedded-pointer-object", -12, -76, 4, None, None, None, (0,))]
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=embedded_objects)
    assert v["pass"], v
    cb, ct, csz, cva = _embedded_stack_pointer_fixture(64, pointer_offset=1)
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=embedded_objects)
    assert not v["pass"], v
    # A too-small reviewed extent cannot normalize a pointer at its boundary.
    ob, ot, osz, ova = _stack_object_fixture(1, pointer_offset=3)
    cb, ct, csz, cva = _stack_object_fixture(64, pointer_offset=3)
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=[("fixture-object", -12, -76, 3)])
    assert not v["pass"], v
    # Content-aware objects may contain a reviewed alignment hole.  A change
    # in that unobservable hole does not manufacture a mismatch, while every
    # byte in either declared semantic range remains strict.
    ranged_objects = [("ranged-object", -12, -76, 4, ((0, 1), (2, 4)))]
    ob, ot, osz, ova = _stack_object_fixture(1)
    cb, ct, csz, cva = _stack_object_fixture(64, second=8)
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=ranged_objects)
    assert v["pass"], v
    cb, ct, csz, cva = _stack_object_fixture(64, third=10)
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=ranged_objects)
    assert not v["pass"], v
    # An output-only object legitimately has no observable pre-call content,
    # but its identity, pointer interior offset, and declared boundary remain
    # strict.  Different indeterminate bytes are accepted; shifting the passed
    # pointer or shrinking the reviewed extent past that pointer is rejected.
    output_objects = [("output-object", -12, -76, 4, ())]
    ob, ot, osz, ova = _stack_object_fixture(1)
    cb, ct, csz, cva = _stack_object_fixture(64, second=8, third=10)
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=output_objects)
    assert v["pass"], v
    cb, ct, csz, cva = _stack_object_fixture(64, pointer_offset=1)
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=output_objects)
    assert not v["pass"], v
    ob, ot, osz, ova = _stack_object_fixture(1, pointer_offset=3)
    cb, ct, csz, cva = _stack_object_fixture(64, pointer_offset=3)
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=[("output-object", -12, -76, 3, ())])
    assert not v["pass"], v
    # Call-scoped identities are exact: the same object pair is recognized at
    # its reviewed ordinal and remains an ordinary unequal stack pointer at a
    # different ordinal.  This prevents temporal stack-slot reuse from making
    # unrelated records interchangeable.
    ob, ot, osz, ova = _stack_object_fixture(1)
    cb, ct, csz, cva = _stack_object_fixture(64)
    scoped = [("scoped-object", -12, -76, 4, None, (0,))]
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=scoped)
    assert v["pass"], v
    wrong_scope = [("scoped-object", -12, -76, 4, None, (1,))]
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=wrong_scope)
    assert not v["pass"], v
    def _first_bl_target(body, va, size):
        ins = next(i for i in _md.disasm(body[:size], va)
                   if i.mnemonic == "bl")
        return int(ins.op_str.lstrip("#"), 0) & ~1
    original_target = _first_bl_target(ob, ova, osz)
    candidate_target = _first_bl_target(cb, cva, csz)
    target_scoped = [("target-object", -12, -76, 4, None, None,
                      (original_target,))]
    v = emu.compare(
        ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
        nptr=0, ret_kind="void", call_arities=[1],
        paired_stack_objects=target_scoped,
        candidate_direct_target_map={candidate_target: original_target})
    assert v["pass"], v
    wrong_target = [("target-object", -12, -76, 4, None, None,
                     (original_target + 4,))]
    v = emu.compare(
        ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
        nptr=0, ret_kind="void", call_arities=[1],
        paired_stack_objects=wrong_target,
        candidate_direct_target_map={candidate_target: original_target})
    assert not v["pass"], v
    # Manual STLEX/STREX emulation must expose its successful store exactly as
    # UC_HOOK_MEM_WRITE would.  A changed atomic mask on a void helper is the
    # regression that previously passed because neither return values nor
    # exclusive stores appeared in the trace.
    def _atomic_or_fixture(mask):
        src = ("void atomic_fixture(unsigned *p){"
               "(void)__atomic_fetch_or(p,%du,__ATOMIC_ACQ_REL);}" % mask)
        out, err = recon.compile_func(src, "atomic_fixture", 0x61000)
        assert err is None, err
        return out
    ab, at, asz, ava = _atomic_or_fixture(1)
    cb, ct, csz, cva = _atomic_or_fixture(1)
    v = emu.compare(ab + at, ava, asz, cb + ct, cva, csz,
                    trials=1, nptr=1, ret_kind="void")
    assert v["pass"], v
    cb, ct, csz, cva = _atomic_or_fixture(2)
    v = emu.compare(ab + at, ava, asz, cb + ct, cva, csz,
                    trials=1, nptr=1, ret_kind="void")
    assert not v["pass"], v
    # Register-indirect callback identity is semantic even when call order and
    # r0-r3 arguments match. Direct linked stub addresses remain normalized.
    def _indirect_fixture(slot):
        src = ("typedef unsigned(*fn)(void*);"
               "unsigned fixture(unsigned **p){return ((fn)p[%d])(p);}" % slot)
        out, err = recon.compile_func(src, "fixture", 0x62000)
        assert err is None, err
        return out
    ib, it, isz, iva = _indirect_fixture(2)
    cb, ct, csz, cva = _indirect_fixture(2)
    mem = [[(0, 4, (0x00080011).to_bytes(4, "little")),
            (0, 8, (0x00080001).to_bytes(4, "little"))]]
    v = emu.compare(ib + it, iva, isz, cb + ct, cva, csz,
                    trials=1, nptr=1, memory_overrides=mem)
    assert v["pass"], v
    cb, ct, csz, cva = _indirect_fixture(1)
    v = emu.compare(ib + it, iva, isz, cb + ct, cva, csz,
                    trials=1, nptr=1, memory_overrides=mem)
    assert not v["pass"], v
    # Trial-indexed oracle cases must remain symmetric and differential: this
    # is the mechanism used to bound the reviewed packet-length query.
    ov_trials = [{0: {0: emu.SCRATCH + 0x1000}},
                 {0: {0: emu.SCRATCH + 0x1004}}]
    # Rebuild both sides here: the arity regression above deliberately reuses
    # its own `ob/ot` temporaries with a different fixture body.
    ob, ot, osz, ova = _oracle_ptr_fixture("*getp()")
    cb, ct, csz, cva = _oracle_ptr_fixture("*getp()")
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz,
                    trials=2, nptr=0, oracle_overrides=ov_trials)
    assert v["pass"], v
    cb, ct, csz, cva = _oracle_ptr_fixture("*getp() + 1")
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz,
                    trials=2, nptr=0, oracle_overrides=ov_trials)
    assert not v["pass"], v
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
    # Argument-owned read transitions model an external producer without a
    # fixed target address. The reviewed ordinal and value are both material:
    # moving the transition later or changing its value changes the result.
    read_twice = bytes.fromhex("0168" "0a68" "0868" "7047")
    runner = emu.Runner(0x50000, len(read_twice), read_twice)
    args = [emu.SCRATCH + 0x200, 0, 0, 0]
    setup = [(0, 0, (emu.SCRATCH + 0x300).to_bytes(4, "little"))]
    absolute = [(emu.SCRATCH + 0x300, (0).to_bytes(4, "little"))]
    good = runner.run(0, args, 0, memory_overrides=setup,
                      absolute_memory_overrides=absolute,
                      pointer_read_transitions=[(0, 0, 0, 2, 7)])
    assert good["r0"] == 7, good
    wrong_ordinal = runner.run(0, args, 0, memory_overrides=setup,
                               absolute_memory_overrides=absolute,
                               pointer_read_transitions=[(0, 0, 0, 3, 7)])
    assert wrong_ordinal["r0"] == 0, wrong_ordinal
    wrong_value = runner.run(0, args, 0, memory_overrides=setup,
                             absolute_memory_overrides=absolute,
                             pointer_read_transitions=[(0, 0, 0, 2, 8)])
    assert wrong_value["r0"] == 8, wrong_value
    # Direct external calls retain semantic identity independently of their
    # generated stub layout.  An identical same-arity mapping passes; mapping
    # that exact call ordinal to a different target must fail.
    direct_src = "extern int FUN_00070000(int); int fixture(int x){return FUN_00070000(x);}"
    direct_out, direct_err = recon.compile_func(direct_src, "fixture", 0x63000)
    assert not direct_err, direct_err
    db, dt, dsz, dva = direct_out
    dr = emu.Runner(dva, dsz, db + dt).run(0, [7, 0, 0, 0], 0)
    stub = dr["call_targets"][0]
    v = emu.compare(db + dt, dva, dsz, db + dt, dva, dsz, trials=1, nptr=0,
                    candidate_direct_target_map={stub: stub})
    assert v["pass"], v
    v = emu.compare(db + dt, dva, dsz, db + dt, dva, dsz, trials=1, nptr=0,
                    candidate_direct_target_map={stub: stub + 4})
    assert not v["pass"] and v["detail"][0][1] == "direct-target", v
    assert recon.LAST_DIRECT_TARGET_MAP.get(stub) == 0x70000
    # A format-specific arity belongs to one semantic logger target.  The same
    # format address at an unrelated callee must retain that callee's complete
    # ABI rather than inheriting a shorter logger prefix.
    format_a = ("extern int FUN_00070000(const char*,int,int);"
                "int fixture(void){return FUN_00070000((void*)0x12340,1,2);}")
    format_b = ("extern int FUN_00070000(const char*,int,int);"
                "int fixture(void){return FUN_00070000((void*)0x12340,1,3);}")
    fa, fe = recon.compile_func(format_a, "fixture", 0x63000)
    assert not fe, fe
    fb, fe = recon.compile_func(format_b, "fixture", 0x63000)
    assert not fe, fe
    fab, fat, fas, fva = fa; fbb, fbt, fbs, _ = fb
    fr = emu.Runner(fva, fas, fab + fat).run(0, [0, 0, 0, 0], 0)
    format_stub = fr["call_targets"][0]
    format_value = fr["events"][0][2]
    v = emu.compare(
        fab + fat, fva, fas, fbb + fbt, fva, fbs, trials=1, nptr=0,
        call_arity_by_target={format_stub: 3},
        call_arity_by_format={(format_stub + 4, format_value): 2})
    assert not v["pass"], v
    # A stack pointer followed by scalar value one is not evidence that its
    # pointee is one byte long.  The complete reviewed four-byte object must
    # expose a mutation in byte one unless an explicit range/length relation
    # says otherwise.
    stack_a = ("extern void FUN_00070000(int,int,int,int,unsigned char*,unsigned);"
               "void fixture(void){unsigned char x[4]={1,2,3,4};"
               "x[1]=2;FUN_00070000(0,0,0,0,x,1);}")
    stack_b = ("extern void FUN_00070000(int,int,int,int,unsigned char*,unsigned);"
               "void fixture(void){unsigned char x[4]={1,2,3,4};"
               "x[1]=9;FUN_00070000(0,0,0,0,x,1);}")
    sa, se = recon.compile_func(stack_a, "fixture", 0x63000)
    assert not se, se
    sb, se = recon.compile_func(stack_b, "fixture", 0x63000)
    assert not se, se
    sab, sat, sas, sva = sa; sbb, sbt, sbs, _ = sb
    sr_a = emu.Runner(sva, sas, sab + sat).run(
        0, [0, 0, 0, 0], 0, call_stack_arity_by_target={})
    stack_stub = sr_a["call_targets"][0]
    sr_a = emu.Runner(sva, sas, sab + sat).run(
        0, [0, 0, 0, 0], 0,
        call_stack_arity_by_target={stack_stub: 2})
    sr_b_probe = emu.Runner(sva, sbs, sbb + sbt).run(
        0, [0, 0, 0, 0], 0)
    candidate_stack_stub = sr_b_probe["call_targets"][0]
    candidate_stack_map = {candidate_stack_stub: stack_stub}
    sr_b = emu.Runner(sva, sbs, sbb + sbt).run(
        0, [0, 0, 0, 0], 0,
        call_stack_arity_by_target={stack_stub: 2},
        oracle_target_map=candidate_stack_map)
    a_event = next(event for event in sr_a["events"] if event[0] == "C")
    b_event = next(event for event in sr_b["events"] if event[0] == "C")
    a_offset = a_event[a_event.index("S") + 1] - emu.STACK_TOP
    b_offset = b_event[b_event.index("S") + 1] - emu.STACK_TOP
    v = emu.compare(
        sab + sat, sva, sas, sbb + sbt, sva, sbs, trials=1, nptr=0,
        candidate_direct_target_map=candidate_stack_map,
        paired_stack_objects=[("uncaptured-fifth-argument",
                               a_offset, b_offset, 4)])
    assert (not v["pass"] and
            any(item[0] == "stack-object-coverage" for item in v["detail"])), v
    v = emu.compare(
        sab + sat, sva, sas, sbb + sbt, sva, sbs, trials=1, nptr=0,
        call_stack_arity_by_target={stack_stub: 2},
        candidate_direct_target_map=candidate_stack_map,
        paired_stack_objects=[("next-scalar-is-not-length",
                               a_offset, b_offset, 4)])
    assert not v["pass"], v
    v = emu.compare(
        sab + sat, sva, sas, sbb + sbt, sva, sbs, trials=1, nptr=0,
        call_stack_arity_by_target={stack_stub: 2},
        candidate_direct_target_map=candidate_stack_map,
        paired_stack_objects=[("explicit-length-relation",
                               a_offset, b_offset, 4,
                               None, None, None, None, 5)])
    assert v["pass"], v
    # Target-bound oracle writes must follow that same semantic mapping.  A
    # generated candidate stub is not numerically equal to the original
    # firmware target, but an out-parameter effect reviewed for FUN_00070000
    # applies only when the mapping identifies that exact callee.
    write_src = ("extern void FUN_00070000(unsigned*);"
                 "unsigned fixture(unsigned*p){FUN_00070000(p);return *p;}")
    write_out, write_err = recon.compile_func(write_src, "fixture", 0x63000)
    assert not write_err, write_err
    wb, wt, wsz, wva = write_out
    write_map = dict(recon.LAST_DIRECT_TARGET_MAP)
    write_stub = next(k for k, value in write_map.items() if value == 0x70000)
    write_effect = {0: [(0, 0, (0x12345678).to_bytes(4, "little"), 0x70000)]}
    write_runner = emu.Runner(wva, wsz, wb + wt)
    common_write_args = dict(
        seed=0, args=[emu.SCRATCH, 0, 0, 0], scratch_seed=0,
        absolute_memory_overrides=[(emu.SCRATCH, bytes(4))],
        oracle_memory_writes=write_effect)
    unbound = write_runner.run(**common_write_args)
    assert unbound["r0"] == 0, unbound
    bound = write_runner.run(**common_write_args,
                             oracle_target_map={write_stub: 0x70000})
    assert bound["r0"] == 0x12345678, bound
    # Readable SDK aliases retain identity too.  Same-arity lock/unlock stubs
    # must not collapse to an order-only oracle, including after a trap and
    # beyond the bounded 64-entry diagnostic target list.
    named_a = "extern int k_mutex_lock(void*); int fixture(void*x){return k_mutex_lock(x);}"
    named_b = "extern int k_mutex_unlock(void*); int fixture(void*x){return k_mutex_unlock(x);}"
    ao, ae = recon.compile_func(named_a, "fixture", 0x63000)
    assert not ae, ae
    amap = dict(recon.LAST_DIRECT_TARGET_MAP)
    bo, be = recon.compile_func(named_b, "fixture", 0x63000)
    assert not be, be
    bmap = dict(recon.LAST_DIRECT_TARGET_MAP)
    assert 0x000723b8 in amap.values() and 0x00072558 in bmap.values(), (amap, bmap)
    ab, at, asz, ava = ao; bb, bt, bsz, bva = bo
    v = emu.compare(ab + at, ava, asz, bb + bt, bva, bsz, trials=1,
                    nptr=1, candidate_direct_target_map=bmap)
    assert not v["pass"] and v["detail"][0][1] == "direct-target", v
    trap_a = ("extern int k_mutex_lock(void*); int fixture(void*x){"
              "k_mutex_lock(x);__builtin_trap();}")
    trap_b = ("extern int k_mutex_unlock(void*); int fixture(void*x){"
              "k_mutex_unlock(x);__builtin_trap();}")
    ao, ae = recon.compile_func(trap_a, "fixture", 0x63000)
    assert not ae, ae
    bo, be = recon.compile_func(trap_b, "fixture", 0x63000)
    assert not be, be
    bmap = dict(recon.LAST_DIRECT_TARGET_MAP)
    ab, at, asz, ava = ao; bb, bt, bsz, bva = bo
    v = emu.compare(ab + at, ava, asz, bb + bt, bva, bsz, trials=1,
                    nptr=1, candidate_direct_target_map=bmap)
    assert not v["pass"] and v["detail"][0][1] == "direct-target", v
    calls_a = ";".join("k_mutex_lock(x)" for _ in range(65))
    calls_b = ";".join((["k_mutex_lock(x)"] * 64) + ["k_mutex_unlock(x)"])
    prefix = "extern int k_mutex_lock(void*);extern int k_mutex_unlock(void*);int fixture(void*x){"
    ao, ae = recon.compile_func(prefix + calls_a + ";return 0;}", "fixture", 0x63000)
    assert not ae, ae
    bo, be = recon.compile_func(prefix + calls_b + ";return 0;}", "fixture", 0x63000)
    assert not be, be
    bmap = dict(recon.LAST_DIRECT_TARGET_MAP)
    ab, at, asz, ava = ao; bb, bt, bsz, bva = bo
    v = emu.compare(ab + at, ava, asz, bb + bt, bva, bsz, trials=1,
                    nptr=1, candidate_direct_target_map=bmap)
    assert not v["pass"] and v["detail"][0][1] == "direct-target", v
    # Full regressions for the Unicorn ITSTATE leak.  These use immutable,
    # unpatched original bytes and must pass through the generic IT-end
    # execution boundary only.
    for it_name in ("FUN_0008712e", "FUN_00077914"):
        it_verdict = verify("app", it_name, trials_random=0)
        assert it_verdict["status"] == "PASS", (it_name, it_verdict)
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
