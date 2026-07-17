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
    # Main display dispatcher is a deliberate nonreturning worker.  The
    # concrete display/buffer graphs below cover every mode selector; forty
    # ordered events include the selected arm and cross its iteration tail.
    ("app", 0x00028bec): 40,
    # Nonreturning proxy transport worker.  Concrete queue records below drive
    # one complete opcode dispatch and compare into the following loop head.
    ("app", 0x00047c48): 20,
    # The display worker is intentionally nonreturning.  Reviewed queue
    # records below cover one complete state/opcode dispatch and continue
    # through the service-abort poll into the following loop iteration.
    ("app", 0x00049090): 50,
    # Nonreturning flash worker: reviewed queue-result sequences below reach
    # the next semaphore wait after every selected drain loop completes.
    ("app", 0x00023480): 30,
    # The slave display worker is intentionally nonreturning.  Concrete
    # device/record fixtures below compare complete dispatch iterations; the
    # following iteration supplies a stable boundary beyond every handler's
    # writes and calls without pretending the production thread returns.
    ("app", 0x00027cfe): 50,
    # The key-event worker is likewise a deliberate nonreturning queue loop.
    # Each reviewed fixture drives one complete state dispatch, then supplies
    # quiescent polls; fifty ordered events cross the selected arm's writes
    # and calls and reach stable iterations of the following loop head.
    ("app", 0x0002955c): 50,
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
    # Controller assertion dispatch is deliberately noreturn after its fault
    # callback and AIRCR reset request.  Two events cover callback+reset; the
    # null-callback case has the single reset event before the terminal loop.
    ("net", 0x01008d00): 2,
}

# Direct callees absent from, or ambiguous in, the decompiler catalog.  These
# are reviewed AAPCS argument counts; registers above the true arity are caller
# scratch and must not create false mismatches merely because GCC leaves a
# different stale value in them.
CALL_ARITY_OVERRIDES = {
    # Zephyr sys_reboot consumes the reboot mode in r0 even though this arch
    # implementation ignores the value before its AIRCR reset request.
    ("net", 0x0102f4ec): 1,
    # Catalog-missing net entries and their internal transition helpers.
    ("net", 0x01020d1c): 2,  # radio transition consumes r0/r1
    ("net", 0x0102946c): 2,  # normalized handle and byte value
    ("net", 0x0101e090): 1,  # selected entry object
    ("net", 0x0101e15c): 3,  # context, entry, and byte value
    ("app", 0x00076ed4): 6,  # request tuple plus duplicated key/object pointer
    ("app", 0x000737d8): 1,  # boolean list-state update
    ("app", 0x00073cdc): 1,  # list head/object
    ("app", 0x0008664c): 0,  # post-unlock scheduler kick
    ("app", 0x0008641c): 1,  # initialized connection object
    ("app", 0x0008307a): 0,  # current connection accessor
    ("app", 0x00083204): 1,  # connection object finalizer
    ("app", 0x0005503c): 1,  # allocated pairing record
    ("app", 0x0005e6a8): 2,  # address byte plus address record
    ("app", 0x0005e9a0): 2,  # pairing record plus bit mask
    ("app", 0x00055cf0): 0,  # global connection-mode query
    ("app", 0x0005ce6c): 1,  # connection object
    # State-reset continuation takes no arguments; r0-r3 are merely residual
    # values after the two stores in FUN_0004e484.
    ("app", 0x0004e474): 0,
    # Diagnostic submission consumes domain, event code, and record pointer.
    ("app", 0x0007f406): 3,
    ("app", 0x0004bfc8): 2,  # mpsc buffer plus item being released
    ("app", 0x0004de68): 1,  # stream object
    ("app", 0x0004d588): 0,  # scheduler-state tail wrapper
    # Floating formatter helpers: the dtoa call uses r0-r3 plus four stacked
    # scalar arguments (the double itself is in d0); width setup has one
    # stacked callback; all comparison helpers consume both 64-bit operands.
    ("app", 0x00086cda): 4,
    ("app", 0x00086e1c): 4,
    ("app", 0x0000ddf0): 4,
    ("app", 0x0000dddc): 4,
    ("app", 0x0000ddc8): 4,
    ("app", 0x00052f18): 2,  # lookup consumes only key and zero-valued selector
    ("app", 0x000826e0): 1,  # notification helper consumes only its object pointer
    ("app", 0x0006446c): 0,  # parser fallback has no arguments
    ("app", 0x000655ec): 1,  # IRQ-register mapper consumes only the index
    ("app", 0x00074844): 0,  # timing continuation consumes no arguments
    ("app", 0x0007c0a4): 0,  # timing continuation entry veneer
    ("app", 0x00078d90): 3,  # writer, descriptor, and scalar value
    ("app", 0x00018e48): 1,  # event submission consumes one record pointer
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
    ("app", 0x00056908): 2,  # connection lookup: identifier and selector
    ("app", 0x00056c78): 2,  # connection plus eight-byte address record
    ("app", 0x00053cd4): 2,  # pool identifier and allocation size
    ("app", 0x000543d8): 2,  # queue identifier and allocated packet
    ("app", 0x000566a4): 1,  # release one connection reference
    ("app", 0x00080f56): 2,  # identifier and status code
    ("app", 0x00063654): 7,  # four register plus three stacked arguments
    ("app", 0x00084abe): 2,  # lock object and saved BASEPRI value
    ("app", 0x0008496c): 3,  # owner, byte destination, and byte count
    ("app", 0x00086406): 0,  # scheduler-state query
    ("app", 0x0008638c): 0,  # privilege/scheduler readiness query
    ("app", 0x0005010c): 3,  # interrupt configuration triplet
    ("app", 0x000500ac): 1,  # interrupt identifier
    ("app", 0x00062ad8): 2,  # owner and state destination
    ("app", 0x0006540c): 1,  # validate one address field
    ("app", 0x000850dc): 3,  # pin, set-register, clear-register
    ("app", 0x00064f30): 1,  # one-bit interrupt mask
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
    ("app", 0x0008669c): 1,  # output-window initializer consumes its pointer
    ("app", 0x00084602): 1,  # lookup consumes one selector
    ("app", 0x0004f770): 0,  # state query has no arguments
    ("app", 0x0006447c): 0,  # controller query has no arguments
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
    ("app", 0x00032c28): 0,  # exported flash-signature check has no arguments
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
    # Intrusive-list pop consumes only the list head.  Callers may retain an
    # event-type value in r1, but the callee never reads or forwards it.
    ("app", 0x0008688e): 1,
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
    ("net", 0x0103b442): 2,  # queue item and state bit consumed by finalizer
    ("net", 0x0103b3e0): 3,  # list, inserted record and comparison key
    # The conversion wrapper consumes the low/high words of one 64-bit value.
    # r2/r3 are caller scratch left by the preceding division helper.
    ("net", 0x01037c64): 2,
    # Sample lookup consumes owner and index; it installs its fixed lane in r2
    # before forwarding, and never consumes the caller's r2/r3 values.
    ("net", 0x01039768): 2,
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
    # Fusion update consumes seven hard-float values in s0-s6; its state
    # pointer is the sole integer-register argument.
    ("app", 0x00026624): 7,
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
    # gui_utf_draw_align_right's catalog ends immediately after the logger BL
    # at 0x451b4, truncating the callback invocation and fallback logger tail.
    # Live code ends with the branch at 0x451cc; alignment/literals follow and
    # gui_utf_Wordwrap_draw begins independently at 0x451e0.
    ("app", 0x00044ec4): 0x30a,
    # Complete four-mode SDC connection-event timing planner; the catalog's
    # 0x710-byte extent stops before its terminal assertion tails/literals.
    ("net", 0x01012f18): 0x738,
    # The catalog cuts the final invalid-state assertion BL in half.  That BL
    # ends at 0x0101ba4e; alignment/literals and FUN_0101ba58 follow.
    ("net", 0x0101b7e4): 0x26a,
    # img_mgmt_get_next_boot_slot owns the invalid-state return branch through
    # 0x809f4; the next independent function begins at 0x809f6.
    ("app", 0x000809b0): 0x46,
    # The catalog truncates the default TBB arm inside its MOVW.  The owned
    # noreturn controller-fault BL ends at 0x010164a6; alignment/literals follow.
    ("net", 0x01016430): 0x76,
    # clear_event_registrations owns the final lock-validation/set-owner tail
    # and backedge through 0x7552a; literals begin at 0x7552c.
    ("app", 0x000753ec): 0x140,
    # register_events owns the invalid-registration assertion tail and shared
    # BASEPRI restore/loop through 0x7539c; literals begin at 0x753a0.
    ("app", 0x000751d0): 0x1ce,
    # The final BL is the noreturn sys_reboot implementation.  The halfword
    # at 0x01031842 is alignment and the following words are literal data.
    ("net", 0x01031820): 0x22,
    # process_for_new_task's catalog extent ends at 0x2e038 inside the live
    # state-zero polling loop.  The remaining switch/default and shared
    # status-return tail run through the branch at 0x2e2be; literals begin at
    # 0x2e2c4 (0x2e2c2 is alignment) and 0x2e300 is a new prologue.
    ("app", 0x0002c99c): 0x1924,
    # The catalog ends at the unknown-type snprintk call.  Its ordinary branch
    # back into the shared final formatter is live code through 0x18390;
    # literals begin at 0x18394.
    ("app", 0x00018334): 0x5e,
    # The catalog stops at 0x01034346 inside the LDAEX/STLEX loop.  The
    # mismatch retry, claimed-index store, empty return, and shared epilogue
    # continue through 0x0103435c; alignment/literals begin at 0x0103435e.
    ("net", 0x01034328): 0x36,
    # The catalog stops at 0x32e64 on the final retry back-branch.  That branch
    # and the read-exhaustion return tail are owned code through 0x32e68;
    # literals begin at 0x32e6c.
    ("app", 0x00032c28): 0x242,
    # Large radio transition omitted from the catalog. Four independent
    # dispatch owners tail-branch here at 0x01012e36, 0x01013746,
    # 0x0101ab86, and 0x0101ba9e. Its contiguous ownership span includes the
    # embedded literal islands and ends before FUN_01021108.
    ("net", 0x01020d1c): 0x3ec,
    # The normalized handle/value updater is owned by FUN_010294a2's tail
    # branch at 0x010294aa and ends exactly where that wrapper begins.
    ("net", 0x0102946c): 0x36,
    # The packet-builder TBB owns six late fatal tails through 0x0100eeb0;
    # its literal pool begins at 0x0100eeb4.
    ("net", 0x0100ec88): 0x22c,
    # Complete RTC1 overflow/compare ISR; catalog 0x5c ends in its exclusive
    # loop, while executable ownership continues to the final loop backedge.
    ("net", 0x010315f0): 0xf4,
    # Complete scheduling snapshot builder, including every TBH-selected PHY
    # arm and the branch-owned assertion tails through 0x0101ab1e.
    ("net", 0x0101a38c): 0x794,
    # lc3_spec_encode owns late setup islands through 0x6ffd8; the catalog's
    # 0x60c extent cuts the second island before its shared-body branch.
    ("app", 0x0006f9c0): 0x618,
    # display_thread_handler continues beyond its catalog extent through the
    # final forced-reset branch at 0x49630.  Alignment is at 0x49632 and its
    # last literal is supplied by the verifier's padded immutable byte read.
    ("app", 0x00049090): 0x5a2,
    # display_dispatch_thread's live notification/delay tail ends with the
    # branch at 0x29500; alignment and its literal pool follow before the next
    # independent entry at 0x2953c.
    ("app", 0x00028bec): 0x916,
    # The catalog stops at 0x285e4 inside the final inner switch.  Its four
    # live handlers end with the branch at 0x286c0..0x286c3; literals occupy
    # 0x286c4..0x286f7 and FUN_000286f8 has an independent push prologue.
    ("app", 0x00027cfe): 0x9fa,
    # Catalog truncates the proxy switch inside case seven.  Include every
    # live retry/default/atomic tail plus its final literal pool up to the
    # independent requestAudioInfoToApp entry at 0x48840.
    ("app", 0x00047c48): 0xbf8,
    # Catalog truncates gui_utf_Wordwrap_draw inside the callback/logger tail.
    # Include live code through 0x455b6 and its literals through 0x455cb; the
    # independent gui_string_draw prologue begins exactly at 0x455cc.
    ("app", 0x000451e0): 0x3ec,
    # Five real net entry points omitted from Ghidra's function catalog.
    # Each has an exact direct owner branch: FUN_01013650 -> 0x01016144,
    # FUN_0102946c -> 0x0101e15c -> 0x0101e0a4, FUN_0100cb10 ->
    # 0x0101fd8c, and FUN_0101fc14 -> 0x0101fdc0.  These executable extents
    # stop before their alignment/literal pools or the next independent entry.
    ("net", 0x01016144): 0x16,
    ("net", 0x0101e0a4): 0x68,
    ("net", 0x0101e15c): 0x04,
    ("net", 0x0101fd8c): 0x2c,
    ("net", 0x0101fdc0): 0x0a,
    # Real net internal entries omitted from the catalog.  Exact direct tail
    # branches at 0x0101f98a, 0x01012e2c and 0x01021852 prove ownership; each
    # extent stops before its reviewed literal/alignment boundary.
    ("net", 0x0100eec8): 0x3c,
    ("net", 0x010127f8): 0xba,
    ("net", 0x010217cc): 0x30,
    # draw_message's catalog stops at 0x35ef0 in the live nonempty-body arm.
    # The body/package formatter, shared emptiness test, and word-wrap draw
    # continue through the back-branch at 0x35f18; literals begin at 0x35f1c.
    ("app", 0x00035afc): 0x41e,
    # Refgraph stops at 0x2144c in the middle of the default response arm.
    # STRB.W/STRB/B continue through 0x21456; 0x21458 and 0x2145c are the two
    # RAM-address literals and FUN_00021460 is the next independent prologue.
    ("app", 0x00021334): 0x122,
    # The dashboard/onboarding renderer's catalog stops at 0x4296c inside a
    # branch-reachable switch island.  Its three late case continuations span
    # 0x4296c..0x429f2 and branch back into the shared body; 0x429f2 is
    # alignment, 0x429f4 is a RAM-address literal, and FUN_000429f8 is the
    # next independent prologue.
    ("app", 0x000417f8): 0x11fa,
    # Both logger islands tail-call their sinks, but the ordinary no-log and
    # null-output paths continue past the catalog's 0x430a2 cutoff.  Their
    # shared POP return is at 0x430aa; literals start at 0x430ac.
    ("app", 0x00042fb0): 0xfc,
    # The catalog's 0x8dc extent ends exactly at 0x10764, the first VFP load
    # in the live three-axis calibration loop.  Its backedges, mode reset,
    # final attitude publication, delay call, and return continue through
    # 0x1080e; literals begin at 0x10810.
    ("app", 0x0000fe88): 0x988,
    # Catalog size 0x182 stops exactly at the shared switch epilogue.  The
    # six-byte stack restore/return through 0x3350a is still executable;
    # the literal pool begins at 0x3350c.
    ("app", 0x00033384): 0x188,
    # onboarding_ble_process response-kind 3 tail spans 0x42c3e..0x42c4a.
    # Treating the catalog boundary at 0x42c3e as external manufactured an
    # oracle loop and was the root cause of its generic-sweep timeout.
    ("app", 0x00042a64): 0x1ec,
    # The catalog ends before the final short-payload branch at 0x1817e.  It
    # rejoins the shared completion tail; literals begin at 0x18180.
    ("app", 0x00017f70): 0x210,
    # UI refresh dispatch returns through 0x48e0e.  Its literal pool begins at
    # 0x48e10; the catalog's 5.3 KiB tail belongs to independent handlers.
    ("app", 0x00048b5c): 0x2b4,
    ("app", 0x0001694c): 0x28c,  # final mode-7 arm and shared return
    ("app", 0x00017a40): 0x3b0,  # late diagnostic islands through 0x17dee
    ("app", 0x0003e05c): 0x758,  # shared epilogue and buffered logger island
    # This atomic flag-clear wrapper returns at 0x810a8.  The independent
    # atomic/setter helpers beginning at 0x810aa were folded into its catalog.
    ("app", 0x00081080): 0x2a,
    # FUN_0005cff0 ends with the tail branch through 0x5d09e.  The alignment
    # NOP/literals after it are data padding before FUN_0005d0ac.
    ("app", 0x0005cff0): 0xae,
    # Computed-switch default island continues through 0x4f40e; the catalog
    # stops at its entry 0x4f40a.
    ("app", 0x0004f1d0): 0x23e,
    # Default return island owns the back-branch at 0x01030ef6; the literal
    # starts at 0x01030ef8 and the next prologue at 0x01030efc.
    ("net", 0x01030e28): 0xd0,
    # Reachable arithmetic continues through the return at 0x0102dfde;
    # literals begin at 0x0102dfe0.
    ("net", 0x0102df2c): 0xb4,
    # Switch-owned cases/default continue through 0x01026646; the next
    # independent function begins at 0x01026648.
    ("net", 0x01026122): 0x526,
    # Catalog stops before the terminal diagnostic BL at 0x0100b108;
    # executable code ends immediately before literals at 0x0100b10c.
    ("net", 0x0100aff4): 0x118,
    # Both packet-description builders have late switch case-one islands
    # beyond Ghidra's catalog ends.  Each extent stops at the final return;
    # the following halfword is alignment before the next function.
    ("net", 0x01019f34): 0x68,
    ("net", 0x0101a070): 0x78,
    # The catalog stops at the default-tail setup.  Both fatal tails are
    # branch-reachable and end at 0x01012c04.  The literal word follows there;
    # FUN_01012c08 is the next independent entry.
    ("net", 0x01012ba4): 0x60,
    # Radio-event dispatch ends before its literal at 0x0101ad34 and the
    # independent FUN_0101ad38 prologue.  The catalog folds both into it.
    ("net", 0x0101ab20): 0x214,
    # The catalog stops before the BASEPRI restore, loop increment and
    # backedge at 0x01038638..0x01038642.  Literals start at 0x01038644 and
    # FUN_01038654 is the next independent entry.
    ("net", 0x010384a8): 0x19c,
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
    # Command validation returns/tail-branches by 0x338d8.  The words through
    # 0x338e8 are literals; FUN_000338ec begins the next function.
    ("app", 0x0003384c): 0x8c,
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
    # The serializer catalog stops at 0x0102c402 inside the deferred-string
    # callback loop.  Its reachable backedge/error joins end at 0x0102c420;
    # the literal pool begins there.
    ("net", 0x0102bfe4): 0x43c,
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
    # The MD5 transform's straight-line continuation runs through the final
    # stack restore at 0x4a100.  An embedded literal island makes the generic
    # reachability scan stop at 0x4a078 unless this reviewed extent is kept.
    ("app", 0x00049acc): 0x634,
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
    ("net", 0x0102d1c0): 0x7a,  # disable path rejoins return at 0x0102d238
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
    # The command-0x4a..0x4f dispatch islands follow the embedded literal pool
    # at 0x2baa0 and rejoin the shared epilogue.  Their final return path ends
    # at 0x2bc0c, where the trailing literals begin.
    ("app", 0x0002af4c): 0xcc0,
    ("app", 0x0000fcf0): 0x178,  # state machine code continues through 0xfe66; literals start 0xfe68
    # liblc3 detect_pitch tail extends twelve bytes past the catalog boundary.
    ("app", 0x000698d0): 0x0c82,
    # libLC3 fft owns its catalogued body through the late shared epilogues at
    # 0x6b990/0x6b99a.  0x6b9b8 is a distinct lc3_mdct_forward entry (full
    # prologue and a direct BL caller at 0x69318), not an FFT continuation.
    ("app", 0x0006b3c8): 0x05ea,
    # This initializer is only a ten-item loop followed by the tail call at
    # 0x596b4.  The catalog folds several unrelated functions after its two
    # literals; the next independent prologue begins at 0x596c2.
    ("app", 0x00059690): 0x28,
    # Function returns at 0x5991a; 0x5991c is its literal and the catalog's
    # 478-byte span incorrectly folds the distinct function at 0x59920.
    ("app", 0x00059834): 0xe6,
    # The default-state arm calls the formatter at 0x599bc and rejoins the
    # shared body through the owned branch at 0x599c0.  The catalog boundary
    # excluded that final two-byte branch and misclassified it as a callee.
    ("app", 0x00059920): 0xa2,
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
    # Complete late command-switch islands end at 0x15dd4; literal pool starts
    # at 0x15dd8 (catalog size 0x438 stopped in case 0xf).
    ("app", 0x00015960): 0x478,
    # sync_to_slave owns the validation/logger tail through 0x2741a.  Its
    # catalog stops at 0x273ee; literals begin at 0x2741c.
    ("app", 0x00026f74): 0x4a8,
    # key_event_thread's state-5/state-6 tails and shared loopback continue
    # through the branch ending at 0x2a096; literals begin at 0x2a098.
    ("app", 0x0002955c): 0xb3a,
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
    # Null-record branches share the FUN_0005f638 call at 0x5f948 and rejoin
    # through 0x5f94e; the literal pool starts at 0x5f950.
    ("app", 0x5f760): 0x1f0,
    # Four-argument dispatcher ends before literal data at 0x30d0a.
    ("app", 0x30cd0): 0x3a,
    # Privacy admission wrapper tail-branches at 0x5508a; next symbol starts 0x55094.
    ("app", 0x5505c): 0x34,
    ("app", 0x531cc): 0x8,
    # Catalog stops at 0x77790 immediately after the `%s` helper call, but the
    # reachable shared formatter/callback and padding tail continues through
    # 0x777e7.  Literal data begins at 0x777e8.
    ("app", 0x77594): 0x254,
    # Catalog stops inside `%n`; conversion handlers and shared return extend
    # through 0x79272.
    ("app", 0x78f88): 0x2ea,
    # Ten bytes of executable wrapper plus alignment/literal ownership to 0x4d586.
    ("app", 0x4d578): 0xe,
    # Three-instruction range check/tail wrapper; literal data begins at 0x4e99c.
    ("app", 0x4e98c): 0x10,
    # TBH case handlers and three fatal tails continue past catalog end 0x101d810.
    ("net", 0x101d404): 0x478,
    # LLCP receive dispatcher ends immediately before FUN_010187e0.
    ("net", 0x01018690): 0x150,
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
    # ipc_rpmsg_static_vrings.c:open; literal pool begins at 0x0102d8a0.
    ("net", 0x0102d708): 0x198,
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
    # mpsc_pbuf_free tail-branches at 0x4c08c; literals begin at 0x4c090 and
    # the next independent body begins at 0x4c0a8.
    ("app", 0x4bfc8): 0xc8,
    # Two-instruction scheduler-state tail wrapper; its literal starts at
    # 0x4d590 and FUN_0004d594 is the next body.
    ("app", 0x4d588): 0x06,
    # Service Changed persistence diagnostic returns at 0x5a11e; its literal
    # pool starts at 0x5a120 before FUN_0005a128.
    ("app", 0x5a0e8): 0x38,
    # Final reachable branch ends at 0x778c2; the following NOP and words are
    # alignment/literal data before the wrapper at 0x778d4.
    ("app", 0x77820): 0xa2,
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
    # libLC3 spectral encoding mutates the bitstream and has no ABI result;
    # r0 at return is merely loop/callee scratch.
    ("app", 0x0006f9c0): "void",
    # Tail-called from the void clock-release wrapper; r0 is calculation
    # scratch (or inherited on the zero-divisor arm), not an ABI result.
    ("net", 0x010217cc): "void",
    # Controller radio transition mutates fixed SDC/MMIO state only.  Any
    # r0/r1 values at its two return sites are helper/callback scratch.
    ("net", 0x01020d1c): "void",
    # Three-byte fixed radio-request state reset; r0/r1 are untouched scratch.
    ("net", 0x0101fdc0): "void",
    # Pure tail dispatcher; both selected handlers are void procedures.
    ("net", 0x01016144): "void",
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
    # Packetization consumes a caller-owned byte stream in 17-byte records.
    # The signed quotient directly controls the loop, so full-width fuzz only
    # manufactures millions of records.  These production lengths cover the
    # empty/tail cases, both sides of the record boundary, and two backedges.
    ("app", 0x00021a40): {1: (0, 1, 16, 17, 18, 34, 35)},
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
    # The fourth entry register is the direct record sink.  The original saves
    # r3 at entry-SP-44 and reloads it before BLX; it is not an object field.
    ("app", 0x00021a40): {3: 0x00080001},
    ("app", 0x00077594): {3: 0x00080001},
    # printf's floating formatter invokes the caller-supplied output function
    # from r3 after several fixed helper calls.
    ("app", 0x0007712c): {3: 0x00080001},
    ("app", 0x00055710): {0: 0x00080001},
}

# Narrow reviewed contracts for external callees that initialize caller-owned
# stack objects.  Entries are ordinal -> (argument register, offset, bytes).
REVIEWED_ORACLE_MEMORY_WRITES = {
    # Both reset spans are complete global objects.  Bind all possible call
    # ordinals because an optional diagnostic precedes the two memset calls.
    ("app", 0x00016738): {
        0: [(0, 0, bytes(0x25), 0x00086c78)],
        1: [(0, 0, bytes(0x25), 0x00086c78)],
        2: [(0, 0, bytes(0x25), 0x00086c78)],
    },
    # Successful burial reset and settings-load preclear completely initialize
    # their respective output spans before the reconstructed code consumes.
    ("app", 0x000230e0): {
        2: [(0, 0, bytes(0xbc), 0x00086c78)],
    },
    ("app", 0x00022bd0): {
        0: [(0, 0, bytes(0x84), 0x00086c78)],
    },
    # Translation formatting initializes the complete ten-byte local before
    # the first text-render call consumes it.
    ("app", 0x0003fd44): {
        2: [(0, 0, b"1/8 -> 8/1", 0x00077914)],
    },
    # The formatter owns the complete local message buffer after the initial
    # clear.  Give it a short nonuniform message so the submit helper observes
    # real initialized bytes rather than compiler-stack residue.
    ("app", 0x00019c70): {
        1: [(0, 0, bytes(200), 0x00086c78)],
        2: [(0, 0, b"debug-message\0", 0x00077c30)],
    },
    # Both floating converters publish one exact scale word through their
    # otherwise-uncaptured r1 output pointer.
    ("app", 0x000875e4): {
        0: [(1, 0, (2).to_bytes(4, "little", signed=True), 0x00078c44)],
        1: [(1, 0, (2).to_bytes(4, "little", signed=True), 0x00078c44)],
    },
    # The two key loaders and the transform fully initialize their local
    # outputs before the final decoder consumes them.  Nonuniform fixtures
    # make the recovered argument order and sixteen-byte reversal observable.
    ("app", 0x00081326): {
        0: [(0, 0, bytes((i * 17 + 3) & 0xff for i in range(16)),
             0x00055ba0)],
        1: [(0, 0, bytes((i * 29 + 5) & 0xff for i in range(180)),
             0x0004fa34)],
        2: [(0, 0, bytes((i * 23 + 7) & 0xff for i in range(16)),
             0x00055ba0)],
    },
    # The block decoder completely initializes the MD5 transform's local
    # sixteen-word input array.  Bind a nonuniform complete block to the exact
    # decoder target so every subsequently consumed word remains observable.
    ("app", 0x00049acc): {
        0: [(0, 0, bytes((i * 37 + 11) & 0xff for i in range(64)),
             0x0007d8c4)],
    },
    # Calendar conversion initializes all six uint16_t fields before the
    # wrapper logs and consumes year/month/day.  A valid nonuniform date keeps
    # every field observable and is bound to the exact conversion helper.
    ("app", 0x0004a2a4): {
        0: [(1, 0, (2025).to_bytes(2, "little") +
             (12).to_bytes(2, "little") + (31).to_bytes(2, "little") +
             (23).to_bytes(2, "little") + (58).to_bytes(2, "little") +
             (47).to_bytes(2, "little"), 0x0004a1b8)],
    },
    ("app", 0x0004a5b0): {
        1: [(1, 0, (2025).to_bytes(2, "little") +
             (12).to_bytes(2, "little") + (31).to_bytes(2, "little") +
             bytes(6), 0x0004a1b8)],
    },
    # The first call is memset(notification_scratch, 0, 16).
    ("app", 0x000338ec): {
        0: [(0, 0, bytes(16), 0x00086c78)],
    },
    # The serialization helpers initialize their complete caller-owned work
    # buffers and 28-byte encoded records.  Ordinal two is either the optional
    # secondary converter or the suffix encoder, so bind both possible effects
    # to the exact semantic target.  Nonuniform fixtures make truncation,
    # wrong-output selection, and reordered record copies observable.
    ("app", 0x000250f8): {
        0: [(0, 0, bytes((i * 13 + 3) & 0xff for i in range(32)),
             0x00025090)],
        1: [(1, 0, bytes((i * 17 + 5) & 0xff for i in range(28)),
             0x0007c3da)],
        2: [(0, 0, bytes((i * 19 + 7) & 0xff for i in range(32)),
             0x000250c4),
            (1, 0, bytes((i * 23 + 11) & 0xff for i in range(28)),
             0x0007c4f4)],
        3: [(1, 0, bytes((i * 29 + 13) & 0xff for i in range(28)),
             0x0007c3da)],
        4: [(1, 0, bytes((i * 23 + 11) & 0xff for i in range(28)),
             0x0007c4f4)],
    },
    # The external glyph-store query publishes two complete uint16_t
    # dimensions through its third argument.  Bind the write to the dynamic
    # callback target so the successful path consumes real reviewed data.
    ("app", 0x0004792c): {
        3: [(2, 0, (8).to_bytes(2, "little") +
                    (3).to_bytes(2, "little"), 0x00080000)],
    },
    # FUN_0102709e publishes the adjusted controller pointer through its third
    # argument before the caller classifies and forwards that word.
    ("net", 0x0100eaf0): {
        2: [(2, 0, (emu.SCRATCH + 0x2000).to_bytes(4, "little"),
             0x0102709e)],
    },
    # FUN_0100e018 copies a four-byte description and adjacent halfword into
    # the caller-owned record.  Use one valid tagged fixture so both codegens
    # consume the same complete six initialized bytes.
    ("net", 0x010166c0): {
        1: [(1, 0, b"\x01\x02\x03\x04\x00\x40", 0x0100e018)],
    },
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
    # These adjacent controller routines use the same two complete
    # FUN_0102714a output objects.  Bind each write to that semantic target;
    # their different ordinals account for the intervening readiness query.
    ("net", 0x010196e0): {
        1: [(1, 0, (emu.SCRATCH + 0x3000).to_bytes(4, "little"), 0x0102714a),
            (2, 0, bytes(2), 0x0102714a)],
    },
    ("net", 0x01019750): {
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
    ("app", 0x000497b0): {
        1: [(0, 1, 2, 0x00086c04)],
    },
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
    ("app", 0x00023400): {0: {0}, 1: {1}},
    # Panel suspend owns a one-byte command and settings load owns its complete
    # 132-byte persistence record.  Their compiler-dependent addresses are
    # normalized only at the exact consumer calls.
    ("app", 0x000475f0): {0: {1}, 1: {1}},
    ("app", 0x00022bd0): {0: {0}, 1: {1}},
    # The initializer receives command+1 before the remaining bytes are
    # defined; normalize only that interior address.  The subsequent queue
    # call is checked as the complete paired record below.
    ("app", 0x00049938): {0: {0}},
    # These initializers receive interior pointers before the containing
    # objects are complete.  Later calls compare the exact paired objects.
    ("app", 0x00022168): {0: {0}},
    ("app", 0x00022e78): {0: {0}},
    # The settings queue fills this five-byte compiler-local record.  Its
    # incoming bytes are output-buffer pre-state, so normalize only the exact
    # pointer argument; the reviewed oracle cases below publish all five bytes.
    ("app", 0x00023f04): {0: {1}},
    # The variadic cursor and 200-byte formatted message are compiler-owned.
    # Normalize only their addresses at the clear/format/submit boundaries.
    ("app", 0x00019c70): {
        1: {0}, 2: {0, 3}, 3: {0},
    },
    # Advertising requests and decode workspaces are compiler-owned records.
    # Normalize only their addresses at the exact helper boundaries; scalar
    # arguments and the externally visible output bytes remain exact.
    ("app", 0x000811ce): {
        0: {0}, 1: {1}, 2: {1}, 3: {1}, 4: {1},
    },
    ("app", 0x00081326): {
        0: {0}, 1: {0, 1}, 2: {0}, 3: {1, 2},
    },
    # Depending on whether a queued item is already present, the local item
    # slot reaches the decoder/timer call at one of these three ordinals.
    ("app", 0x000818dc): {0: {1}, 1: {1}, 2: {1}},
    # Exact compiler-owned command boundaries: opcode interior for the two
    # transport calls and response base for the three-byte comparator.
    ("app", 0x00060c00): {6: {1}, 10: {1}, 12: {1}},
    # Small compiler-owned request/descriptor frames.  Only the listed call
    # arguments are normalized; scalar registers and complete pointee bytes
    # remain part of the strengthened comparison.
    ("app", 0x00047ba8): {1: {0}, 2: {1}},
    # FUN_0004a4d0 completely initializes the local two-word statistics pair;
    # normalize only its compiler-dependent address at that exact boundary.
    ("app", 0x0002ed68): {10: {0}},
    # Register reads write through compiler-local halfword slots.  Normalize
    # only argument r1 at the first three possible read ordinals; target-bound
    # writes below make each returned register value exact.
    ("app", 0x0002e67c): {0: {1}, 1: {1}, 2: {1}, 3: {1}, 5: {1}},
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
    # The onboarding/status renderer clears its compiler-owned 1020-byte
    # scratch canvas before inspecting device state.  Only the destination
    # pointer's frame offset is compiler-specific; its zero fill and exact
    # 1020-byte extent remain fully compared.
    ("app", 0x000417f8): {
        0: {0}, **{i: {3} for i in range(1, 200)}},
}

# Narrow identities for uninitialized compiler-local words whose concrete
# entry-SP offsets differ across code generation.  Each pair is
# (original_offset, candidate_offset[, fixed_value]).  Without a third field
# the harness seeds the same symbolic full word at both locations; the optional
# scalar or per-case value sequence pins a reviewed incoming stack argument.
# All full-width effects remain compared.
REVIEWED_PAIRED_STACK_INITIAL_WORDS = {
    # lc3_spec_encode arguments five through eight are AAPCS stack words:
    # frame bytes, quantized spectrum, side data, and float spectrum.  Bind
    # the three pointer words to complete production-shaped objects; per-case
    # frame sizes select ordinary/high-rate table halves without unbounded
    # random loop counts.
    ("app", 0x0006f9c0): [
        (0, 0, (20, 20, 21, 60, 80, 100, 40, 120)),
        (4, 4, emu.SCRATCH + 0x3000),
        (8, 8, emu.SCRATCH + 0x4000),
        (12, 12, emu.SCRATCH + 0x5000),
    ],
    # Fifth/sixth AAPCS arguments are payload and output pointers.  Pin both
    # per production case; generic r0-r3 overrides cannot initialize incoming
    # stack arguments, and random output pointers would only manufacture
    # irrelevant faults.
    ("app", 0x000340c4): [
        (0, 0, tuple(
            0 if index == 2 else emu.SCRATCH + 0x6200
            for index in range(13))),
        (4, 4, tuple(
            0 if index == 1 else emu.SCRATCH + 0x6300
            for index in range(13))),
    ],
    # Fifth and sixth incoming words are forwarded by the seven-argument
    # wrapper and duplicated/repacked at the final call boundary.
    ("app", 0x00063778): [
        (0, 0, (0x11111111, 0x22222222, 0x33333333)),
        (4, 4, (0x44444444, 0x55555555, 0x66666666)),
    ],
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
    # Fifth/sixth arguments are the horizontal extent and final scanline.
    # The first two fixtures take the disabled-display diagnostics; the last
    # three execute exactly one bounded framebuffer row.
    ("app", 0x00047260): [
        (0, 0, (2, 2, 2, 2, 2)),
        (4, 4, (0, 0, 0, 0, 0)),
    ],
    # The shifted variant has the same two bounds plus a seventh row-offset
    # argument.  Keep the offset zero while still proving that it is consumed.
    ("app", 0x000473c8): [
        (0, 0, (2, 2, 2, 2, 2)),
        (4, 4, (0, 0, 0, 0, 0)),
        (8, 8, (0, 0, 0, 0, 0)),
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
    # calc_flash_crc accumulates into one two-byte local.  The readable table
    # loop saves two fewer registers, shifting the object by eight bytes.
    ("app", 0x00032c28): [
        ("flash-crc-accumulator", -34, -26, 2, None, None,
         (0x00022974,)),
    ],
    # The controller expands its compact module id into this complete local
    # string before passing it to the installed two-argument fault handler.
    # Both shipped and readable GCC use the saved r1-r3 area at entry-SP-20.
    ("net", 0x01008d00): [
        ("controller-fault-module-text", -20, -20, 12, None, (0,)),
    ],
    # draw_message owns four independent text workspaces.  The readable body
    # saves one additional callee register, shifting every object by eight
    # bytes while preserving each allocation, interior memset pointer, and
    # complete content.  Pairing the actual objects is stronger than broadly
    # ignoring stack-valued call arguments.
    ("app", 0x00035afc): [
        ("notification-heading", -0x18c, -0x194, 72),
        ("notification-relative-time", -0x1ac, -0x1b4, 32),
        ("notification-counter", -0x1b4, -0x1bc, 8),
        ("notification-body", -0x144, -0x14c, 292),
    ],
    # init_watchdog owns one complete Zephyr wdt_timeout_cfg.  The shipped
    # frame places it at entry-SP-48; readable GCC uses entry-SP-32.
    ("app", 0x0002ace0): [
        # memset owns the same destination identity but consumes none of its
        # pre-call bytes; its modeled sixteen-byte write is declared per case.
        ("watchdog-timeout-destination", -48, -32, 16, (), None,
         (0x00086c78,)),
        ("watchdog-timeout-config", -48, -32, 16, None, None,
         (0x00080010,)),
    ],
    # RTC synchronization publishes a three-word diagnostic descriptor to the
    # logger.  The shipped function constructs it in a temporary extension of
    # its frame; the readable struct occupies the ordinary GCC frame.
    ("app", 0x0004c2d4): [
        ("rtc-sync-channel-config", -28, -32, 4, (), None,
         (0x0006540c,)),
        ("rtc-sync-error-record", -48, -28, 12, None, None,
         (0x0004d944,)),
    ],
    # hci_vs_init reuses one caller-owned output slot for each synchronous HCI
    # command response.  The shipped frame keeps it at entry-SP-48 while the
    # readable reconstruction places the same four-byte slot at entry-SP-32.
    ("app", 0x00012080): [
        ("hci-response-slot", -48, -32, 4),
    ],
    # The file parser fills one complete 201-byte packet on the stack.  The
    # readable reconstruction uses a real array; GCC shifts it sixteen bytes
    # relative to the shipped frame, without changing its identity or extent.
    ("app", 0x00023634): [
        ("file-packet", -244, -228, 201),
    ],
    # Signal synchronization publishes one adjacent two-word record.  The
    # first word carries the normalized signal and the second the payload.
    ("app", 0x0002c224): [
        ("signal-message", -28, -24, 8),
    ],
    # Three independent compiler-owned records in the audio-request router.
    # Exact disassembly gives the shipped offsets; readable GCC reorders the
    # 257-byte forwarding packet below the two small formatter objects.
    ("app", 0x00017f70): [
        ("request-name", -344, -352, 20, None, (3, 6, 9),
         (0x00086fee, 0x0007ddbe, 0x00086c78, 0x00080000)),
        ("request-log-record", -324, -332, 30, None, None,
         (0x00086c78, 0x0007ddbe, 0x0007dda4, 0x00019c70)),
        ("forwarding-packet", -292, -300, 257, None, None,
         (0x00086c78, 0x00086c04, 0x00017eec)),
    ],
    ("app", 0x000276ec): [
        ("three-byte-event", -20, -12, 3, None, (1,), (0x00017eec,)),
    ],
    ("app", 0x00019ed4): [
        ("dmic-message", -228, -228, 203),
    ],
    ("app", 0x00023400): [
        ("user-settings-record", -48, -40, 32, None, None,
         (0x00086c78, 0x000225b4)),
    ],
    # Complete compiler-owned records: the suspend command is one initialized
    # byte and settings load owns the full 132-byte persisted structure.
    ("app", 0x000475f0): [
        ("panel-suspend-command", -9, -9, 1, None, None,
         (0x0007d82e,)),
    ],
    ("app", 0x00022bd0): [
        ("persisted-system-settings", -156, -156, 132, None, None,
         (0x00086c78, 0x000225b4)),
    ],
    ("app", 0x0003ce04): [
        ("not-disturb-message", -20, -20, 8, ((0, 4),)),
    ],
    ("app", 0x00042c8c): [
        ("onboarding-message", -20, -20, 8, ((0, 4),)),
    ],
    ("app", 0x00018bb4): [
        ("ancs-message", -444, -444, 436),
    ],
    ("app", 0x0002ec5c): [
        ("dmic-message", -216, -220, 200),
    ],
    ("app", 0x00023514): [
        ("file-message", -220, -220, 201),
    ],
    ("app", 0x00023d0c): [
        ("language-record", -20, -12, 4, None, None, (0x00080000,)),
    ],
    # Display transport wrappers publish the complete 24-byte command record.
    ("app", 0x000497b0): [
        ("display-close-packet", -40, -40, 24, None, None,
         (0x00086c78, 0x00086c04, 0x000720d0)),
    ],
    ("app", 0x00049a28): [
        ("display-power-packet", -40, -40, 24, None, None,
         (0x00086c78, 0x000720d0)),
    ],
    # The translation formatter owns exactly ten initialized output bytes.
    ("app", 0x0003fd44): [
        ("translation-text", -36, -36, 10, None, None,
         (0x00077914, 0x00043e90)),
    ],
    ("app", 0x0001a064): [
        ("get-response", -512, -472, 194),
        ("get-work-data", -296, -276, 244),
    ],
    ("app", 0x0001694c): [
        ("mode-change-message", -80, -96, 64, ((0, 2), (4, 64)), (10, 11),
         (0x00086c78, 0x00025b78)),
    ],
    # The CBOR decoder publishes one contiguous 64-bit argument to its width
    # reader.  Its explicit readable-C aggregate preserves the shipped frame
    # identity and prevents either 32-bit half from overlapping parser state.
    ("app", 0x00086064): [
        ("decoded-width", -56, -56, 8, None, (1,), (0x00085e1a,)),
    ],
    # Signed integer decoding publishes the complete eight-byte temporary.
    # Its untouched suffix deliberately retains the saved caller words.
    ("app", 0x0008629e): [
        ("signed-integer", -24, -24, 8, None, (0,), (0x00086208,)),
    ],
    ("app", 0x000183e4): [
        ("bond-description", -40, -44, 36, None, (0, 1),
         (0x00018334, 0x00019c70, 0x0007dda4)),
    ],
    # Compact protocol wrappers publish complete byte records, not unrelated
    # scalar temporaries.  Pair their exact initialized extents at the call.
    ("app", 0x00083dc8): [
        ("three-byte-request", -12, -12, 3, None, (0,), (0x00083d60,)),
    ],
    ("app", 0x00083e70): [
        ("five-byte-request", -16, -16, 5, None, (0,), (0x00083d60,)),
    ],
    # The mapper helper consumes one channel-index word.  GCC places the
    # readable-C object four bytes below the shipped frame.
    ("app", 0x00083ede): [
        ("channel-index", -44, -48, 4, None, None, (0x00061f64,)),
    ],
    # The bounds callback may inspect or replace the requested value in place.
    ("app", 0x000840cc): [
        ("requested-value", -28, -28, 4),
    ],
    # These wrappers publish exact one- and two-byte local payloads through
    # FUN_00082932. GCC shifts only their frame-relative addresses.
    ("app", 0x000829c0): [
        ("status-byte", -20, -24, 1, None, (1,), (0x00082932,)),
    ],
    ("app", 0x00082a1a): [
        ("status-halfword", -18, -24, 2, None, (1,), (0x00082932,)),
    ],
    # These forwarding wrappers expose slices of their saved incoming
    # argument records.  Normalize the complete records, not raw frame
    # offsets, at the six-argument request boundary.
    ("app", 0x00076cc8): [
        ("request-tail", -8, -12, 4, None, (0,), (0x00076ed4,)),
    ],
    ("app", 0x000777f0): [
        ("request-arguments", -12, -20, 4, None, None, (0x00076ed4,)),
    ],
    # Complete writer state consumed by the formatter. The shipped compiler's
    # entry-register save area moves the descriptor relative to readable GCC.
    ("app", 0x0007797c): [
        ("writer-descriptor", -120, -112, 24,
         ((0, 4), (8, 24))),
    ],
    # One three-word event descriptor; readable GCC places it four bytes
    # higher while preserving the complete contents consumed by FUN_18e48.
    ("app", 0x0007c0e2): [
        ("event-descriptor", -24, -20, 12),
    ],
    # The queue callback receives the one-byte control header immediately
    # preceding the 203-byte payload in the exact 208-byte frame.
    ("app", 0x0007c20a): [
        ("queue-control", -212, -212, 1, None, (3,)),
    ],
    # Queue records reconstructed with natural local arrays can move within
    # GCC's frame while remaining the same complete caller-owned object.
    ("app", 0x0002f878): [
        ("audio-delete-record", -220, -212, 204, None, (0, 1, 2)),
    ],
    # The natural header/payload structure is the same complete 204-byte
    # queue record as the shipped compiler's byte array.  Readable GCC saves
    # two additional words before it, shifting only its frame address.
    ("app", 0x0002f6b0): [
        ("audio-cache-record", -220, -212, 204, None, None,
         (0x00086c78, 0x00086c04, 0x000720d0)),
    ],
    ("app", 0x0002ed00): [
        ("dmic-record", -216, -220, 204, None, (0, 1, 2)),
    ],
    ("app", 0x00018ff8): [
        ("uid-record", -24, -24, 8, None, (0,)),
    ],
    ("app", 0x000499b8): [
        ("display-close-record", -32, -32, 24, ((0, 1),), (0, 1)),
    ],
    # The attitude worker owns two independent 24-byte sensor samples.  The
    # readable reconstruction saves one additional register, shifting both
    # arrays eight bytes upward without changing either complete object.
    ("app", 0x0000fe88): [
        ("imu-sample-3", -112, -104, 24, None, (0,)),
        ("imu-sample-7", -88, -80, 24, None, (1,)),
    ],
    # The integer conversion helper consumes one complete seven-word parser
    # state and the current output-list cursor. GCC's readable local ordering
    # places both much higher than the shipped 0x288-byte frame.
    ("app", 0x00078f88): [
        ("scan-conversion-state", -420, -324, 28, ((0, 20), (24, 28)), (1,),
         (0x0007932c,)),
        ("scan-output-cursor", -680, -328, 4, None, (1,),
         (0x0007932c,)),
    ],
    # FUN_00085130 consumes two adjacent one-byte outputs plus three stacked
    # optional arguments. GCC saves two extra registers, shifting only these
    # exact local byte identities eight bytes lower.
    ("app", 0x0006567c): [
        ("channel-low", -26, -34, 1, None, (2,), (0x00085130,)),
        ("channel-high", -25, -33, 1, None, (2,), (0x00085130,)),
    ],
    # The lookup helper receives one complete two-word key/result record.
    ("app", 0x00072f28): [
        ("lookup-key", -20, -32, 8, None, (2,), (0x00072cd4,)),
    ],
    # Failed address validation reports a complete two-word diagnostic.
    ("app", 0x00062d9c): [
        ("address-diagnostic", -40, -32, 8, None, (5,),
         (0x0004d944,)),
    ],
    # The JSON scalar formatter owns one complete 32-byte conversion
    # workspace. Readable GCC places it four bytes higher in its save frame.
    ("app", 0x000646c0): [
        ("scalar-format-workspace", -68, -64, 32),
    ],
    # The optional report contains exactly severity and message identity.
    ("app", 0x00061c40): [
        ("pin-diagnostic", -24, -24, 8, None, (0,), (0x0004d944,)),
    ],
    # Decoder failures publish a complete three-word diagnostic tuple.
    ("app", 0x0005ec18): [
        ("decode-diagnostic", -32, -20, 12, None, None,
         (0x0004d944,)),
    ],
    # Both capability probes reuse this complete four-byte selector record.
    # GCC's larger save set moves it twelve bytes lower in the frame.
    ("app", 0x000583d0): [
        ("capability-selector", -60, -72, 4, None, (0, 1),
         (0x00080d3e,)),
    ],
    # The formatter owns separate fixed-size name and message arrays.  Their
    # complete initialized bytes are consumed by the selected name helper and
    # by the variadic message formatter respectively.
    ("app", 0x00059920): [
        ("state-name", -68, -84, 12, None, (1,),
         (0x00086fee, 0x0007ddbe)),
        ("state-message", -56, -56, 32, None, (2,), (0x0007ddbe,)),
        ("state-log-record", -88, -72, 16, None, None, (0x00081ddc,)),
    ],
    ("app", 0x00059f04): [
        ("lookup-key", -64, -56, 24, None, (0, 2),
         (0x00080cf2, 0x00059bcc)),
        ("lookup-context", -68, -84, 4, None, (1,), (0x0007f1e8,)),
        ("missing-context-log", -40, -80, 8, None, None, (0x00082a42,)),
        ("initial-lookup-error-log", -88, -72, 14, None, (1,),
         (0x00082a42,)),
        ("lookup-conflict-log", -88, -72, 12, None, (3,),
         (0x00082a42,)),
    ],
    # The telemetry sender publishes one complete initialized 32-byte packet.
    # GCC's smaller save frame moves its base eight bytes upward.
    ("app", 0x0007c28e): [
        ("telemetry-packet", -48, -48, 32, None, (1,),
         (0x00022658,)),
    ],
    # Parser initialization owns a five-byte header workspace followed by an
    # independent eight-byte state pair.  Both are fully initialized before
    # the helpers consume them.
    ("app", 0x0007c4b6): [
        ("parser-header", -32, -32, 5, None, (0, 1),
         (0x0007c430, 0x0007c48a)),
        ("parser-state", -24, -24, 8, None, (2,), (0x0007c456,)),
    ],
    # The first attribute read writes a caller-owned uint16_t result.  GCC
    # places that scalar two bytes higher in its compact frame.
    ("app", 0x0007c968): [
        ("attribute-value", -20, -18, 2, None, (0,), (0x000257ec,)),
    ],
    # The BMP decoder fills width, height, and data offset as one contiguous
    # metadata record. Readable GCC places the aggregate eight bytes lower.
    ("app", 0x000435d4): [
        ("bitmap-metadata", -36, -44, 12, None, (0,), (0x0004588c,)),
    ],
    # FUN_00053d70 receives the five-word controller result workspace as an
    # output object. Readable GCC places the same object eight bytes higher;
    # no pre-call bytes are consumed, but its exact identity is call-visible.
    ("app", 0x00055350): [
        ("controller-result", -52, -44, 20, (), (0,), (0x00053d70,)),
    ],
    # The optional diagnostic contains severity, message identity, and the
    # nonzero lookup result.  GCC uses a smaller natural frame, but the logger
    # consumes the same complete twelve-byte record.
    ("app", 0x00052edc): [
        ("lookup-diagnostic", -32, -20, 12, None, (1,),
         (0x0004d944,)),
    ],
    # The validator consumes four adjacent uint16_t fields copied from the
    # caller's packet.  Pair the complete eight-byte value object only at that
    # exact semantic call.
    ("app", 0x00054528): [
        ("address-fields", -32, -36, 8, None, (1,),
         (0x00056c78,)),
        ("missing-connection-diagnostic", -48, -28, 12, None, (1,),
         (0x00080ea2,)),
    ],
    # Both I/O helpers exchange exactly the first eight bytes of one local
    # read buffer.  The shipped frame places it eight bytes below readable
    # GCC; bind the complete contract-sized object only to those two calls.
    ("app", 0x00055c64): [
        ("settings-buffer", -40, -32, 8, None, (0, 1),
         (0x00053e74, 0x00080652)),
        ("write-error", -16, -40, 8, None, (2,), (0x0004d944,)),
    ],
    # The transfer helper consumes one complete twelve-byte request.  The
    # shipped push frame places it eight bytes below readable GCC.
    ("app", 0x0008397e): [
        ("transfer-request", -20, -20, 12, None, (0,), (0x00060ab0,)),
    ],
    # The startup sender owns one complete 24-byte command.  GCC's smaller
    # save set moves it eight bytes upward while preserving every byte and the
    # +1 memset view.
    ("app", 0x00048a3c): [
        ("startup-mode-command", -40, -32, 24, None, (0, 1),
         (0x00086c78, 0x000720d0)),
    ],
    # The parser, optional timestamp writer, and object copy consume one
    # complete 15-byte operation record.  GCC's smaller save set moves the
    # record upward by 24 bytes while preserving every byte and interior view.
    ("app", 0x00055734): [
        ("operation-record", -80, -56, 15, None, None,
         (0x00055454, 0x00081196, 0x00083740)),
        ("attached-allocation", -84, -68, 4, None, None,
         (0x000556b0,)),
        ("enable-error", -48, -64, 8, None, None, (0x0004d944,)),
    ],
    # This three-word operation descriptor starts as the three entry
    # arguments and is then consumed by both processing helpers and the table
    # update.  Its frame placement alone differs across code generation.
    ("app", 0x00054d18): [
        ("operation-descriptor", -24, -28, 12),
    ],
    # The buffered-write path reports one compiler-local diagnostic tuple.
    # Every logger variant consumes its initialized severity/message/status
    # prefix; the optional fourth context word belongs only to severity four.
    # Pair the common consumed record at its exact preserved placement.
    ("app", 0x0004e1ac): [
        ("writer-diagnostic", -40, -40, 12, None, None,
         (0x0004d944,)),
    ],
    # Initializer validation reports a two-word severity/message record.  The
    # explicit readable record preserves the firmware's exact placement.
    ("app", 0x0004e2b4): [
        ("initializer-diagnostic", -40, -40, 8, None, None,
         (0x0004d944,)),
        ("device-geometry", -64, -48, 8, None, (1,),
         (0x00083ac2,)),
    ],
    # FUN_0007d8c4 owns the complete initialization, so there is no meaningful
    # pre-call content range.  Both codegens place the decoded block at the
    # same entry-SP offset; identity plus the target-bound write above proves
    # the exact 64-byte object consumed by the transform.
    ("app", 0x00049acc): [
        ("md5-input-block", -296, -300, 64, (), (0,), (0x0007d8c4,)),
    ],
    ("app", 0x0004a2a4): [
        ("calendar-fields", -36, -36, 12, (), (0,), (0x0004a1b8,)),
    ],
    ("app", 0x0004a5b0): [
        ("calendar-fields", -36, -44, 12, (), (1,), (0x0004a1b8,)),
    ],
    # FUN_000250f8 builds a compiler-owned serialization workspace: two input
    # descriptors and conversion buffers, three 28-byte records, a four-record
    # assembly array, and two pointer/length views.  Readable GCC saves one
    # extra callee-saved register and therefore moves every object eight bytes
    # lower without changing any semantic extent.  Pair each complete object;
    # the two identities sharing the descriptor slot have disjoint target
    # scopes, and embedded pointer words remain bound to the exact paired
    # serialization buffer rather than being treated as arbitrary addresses.
    ("app", 0x000250f8): [
        ("primary-spec", -340, -348, 10, None, None, (0x00025090,)),
        ("secondary-spec", -352, -360, 9, None, None, (0x000250c4,)),
        ("primary-work", -200, -208, 32, None, None,
         (0x00025090, 0x0007c3da)),
        ("secondary-work", -168, -176, 32, None, None,
         (0x000250c4, 0x0007c3da)),
        ("suffix-record", -288, -296, 28, None, (2, 4), (0x0007c4f4,)),
        ("record-array", -136, -144, 112, None, None, (0x0007c7de,)),
        ("serialization-buffer", -232, -240, 32),
        ("suffix-view", -328, -336, 8, None, None, (0x0007c4f4,), (0,)),
        ("record-builder", -328, -336, 12, None, None,
         (0x0007c7de, 0x0007c77e)),
        ("output-view", -360, -368, 8, None, None, (0x0007c77e,), (0,)),
    ],
    # Readable GCC selects different save sets around these fixed-size local
    # output records.  Pair the complete objects by semantic identity while
    # retaining their exact interior offsets and all bytes at call boundaries.
    ("net", 0x0100eaf0): [
        ("radio-result", -20, -24, 4, ()),
    ],
    ("net", 0x01010470): [
        ("controller-packet", -40, -44, 12),
    ],
    ("net", 0x010166c0): [
        ("connection-description", -24, -32, 6, ()),
    ],
    ("app", 0x000338ec): [
        ("notification-event", -180, -176, 4, None, (2,)),
        ("notification-scratch", -176, -172, 16, (), (0,),
         (0x00086c78,)),
    ],
    ("app", 0x000330ec): [
        ("pt-data-buffer", -32, -24, 4, (), (1,), (0x0007d0e8,)),
        ("pt-data-length", -36, -28, 4, (), (1,), (0x0007d0e8,)),
    ],
    # The glyph-list helper receives the address and end pointer of one
    # six-byte local UTF-16 list.  Readable GCC places that complete object
    # six bytes lower in its frame; pair the exact object, not arbitrary stack
    # addresses.
    ("app", 0x000362e8): [
        ("glyph-list-count", -42, -48, 6),
    ],
    # The flash opener's five-word output is uninitialized on entry; only its
    # identity is live at that call.  Each failure path completely initializes
    # the separate level/message diagnostic pair before logging it.
    ("app", 0x00052604): [
        ("flash-area-result", -44, -36, 20, (), (0,), (0x0004e048,)),
        ("flash-error", -24, -44, 8, None, (1, 2), (0x0004d944,)),
    ],
    # The selector helper owns one output byte and the flash lookup owns one
    # output handle.  Only object identity is live before either external
    # callee initializes it; readable block-local diagnostics enlarge the
    # candidate frame by sixteen bytes.
    ("app", 0x00051d8c): [
        ("selection-state", -37, -53, 1, (), None, (0x000809b0,)),
        ("area-handle", -36, -52, 4, (), None, (0x0004e048,)),
        ("failure-record", -64, -48, 24, None, None, (0x0004d944,)),
    ],
    # The parser initializes three caller-owned outputs: an eight-byte header,
    # a 36-byte workspace, and one flags word.  They are uninitialized before
    # the call, so compare exact semantic identity/extent rather than seed
    # bytes at compiler-dependent addresses.
    ("app", 0x00051ac0): [
        ("parsed-header", -92, -92, 8, (), (0,), (0x00052038,)),
        ("parse-workspace", -56, -60, 36, ()),
        ("parse-flags", -104, -100, 4, (), (0,), (0x00052038,)),
        ("formatted-token", -84, -84, 24, (), (7,), (0x00051f88,)),
        ("workspace-view", -100, -96, 4, None, (10,),
         (0x00086338,), (0,)),
    ],
    ("app", 0x0005f654): [
        ("validation-error", -24, -24, 8, None, None, (0x0004d944,)),
    ],
    ("app", 0x0005fb30): [
        ("activation-error", -32, -16, 8, None, None, (0x000837a2,)),
    ],
    ("app", 0x0005f760): [
        ("range-error", -32, -60, 8, None, None, (0x0004d944,)),
    ],
    # One three-word request/result tuple is passed both at byte offset three
    # and word offset one.  Preserve complete identity plus interior offsets.
    ("app", 0x00061624): [
        ("operation-record", -36, -36, 12),
    ],
    # CRC calculation owns one 1028-byte flash-read buffer.  The shipped frame
    # places its first byte at entry-SP-1064, while readable GCC places it four
    # bytes lower.  Calls may pass either the base or buffer+4; object identity,
    # interior offset, and every byte remain observable at each boundary.
    ("app", 0x00022974): [
        ("flash-crc-buffer", -0x428, -0x42c, 0x404),
    ],
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
    # The notification dispatcher publishes one contiguous opcode + ANCS
    # record to FUN_00021460.  Both the shipped frame and the readable typed
    # reconstruction place the complete initialized object at entry-SP-456.
    # Binding full contents to the consuming target makes the mode byte and
    # every dequeued/output field observable without normalizing unrelated
    # stack addresses at the earlier memset/dequeue calls.
    ("app", 0x0001965c): [
        ("ancs-command", -456, -456, 440, None, None, (0x00021460,)),
    ],
    # The transfer callback consumes the initialized register/configuration,
    # three-byte payload, embedded payload pointer, length, and type.  Reserved
    # padding bytes are outside the semantic ranges.
    ("app", 0x0002e67c): [
        ("option-init-frame", -44, -36, 20,
         ((0, 7), (8, 17)), None, (0x00080000,), (8,)),
    ],
    # The connection-description helper initializes the complete 36-byte
    # caller-owned buffer before the logger consumes it.  GCC's readable frame
    # is four bytes larger than the shipped frame, so compare object identity
    # and contents instead of raw stack addresses.
    ("app", 0x00018444): [
        ("connection-description", -48, -52, 36),
    ],
    # The queue receives the complete operation/slot/value request copied to
    # the entry frame.  The shipped prologue places it at entry-SP-48 while
    # readable GCC needs only 44 bytes; all twelve bytes remain observable at
    # the queue boundary and on the subsequent dispatch.
    ("app", 0x00024684): [
        ("slot-request", -48, -44, 12, None, (0,), (0x00072240,)),
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
        ("request-chain", -44, -36, 12, None, (1,), (0x00071358,)),
    ],
    ("app", 0x0004e83c): [
        ("configuration-arguments", -32, -32, 16),
    ],
    ("app", 0x0004ed8c): [
        ("submission-error-record", -40, -36, 12),
    ],
    ("app", 0x0004f418): [
        ("submission-error-log", -40, -28, 12, None, (1,), (0x0004d944,)),
    ],
    # These protocol wrappers publish complete initialized records.  Preserve
    # exact bytes and interior offsets while pairing GCC's frame placement to
    # the shipped frame at only the reviewed producer/consumer boundaries.
    ("app", 0x000488bc): [
        ("power-record", -48, -32, 24, None, (0, 1),
         (0x00086c78, 0x000720d0)),
    ],
    ("app", 0x00048998): [
        ("language-record", -40, -36, 24, None, (0, 1),
         (0x00086c78, 0x000720d0)),
    ],
    # ANCS diagnostics consume complete compiler-local connection strings.
    # No unrelated stack-looking value is normalized.
    ("app", 0x0001861c): [
        ("connection-description", -56, -64, 32),
    ],
    ("app", 0x00018adc): [
        ("connection-description", -48, -52, 36),
    ],
    ("app", 0x0004ff6c): [
        ("five-word-log", -64, -92, 20, None, (0, 1), (0x0004d944,)),
        ("three-word-log", -56, -104, 12, None, (2, 7, 8), (0x0004d944,)),
        ("ten-word-log", -80, -72, 40, None, (3, 4, 5, 6), (0x0004d944,)),
    ],
    ("app", 0x00057db0): [
        ("length-log", -96, -56, 16, None, (1,), (0x00081746,)),
    ],
    ("app", 0x00063ff8): [
        ("auth-block", -40, -36, 20, ((0, 16),), (1,), (0x0007efaa,)),
    ],
    ("app", 0x0006403c): [
        ("auth-block", -32, -36, 20, ((0, 16),), (0,), (0x0007ef80,)),
    ],
    ("app", 0x00064134): [
        ("mode-pair", -32, -40, 16, None, (0,), (0x0007ef04,)),
    ],
    ("app", 0x000641e4): [
        ("probe-result", -32, -36, 12, None, (0,), (0x0006403c,)),
    ],
    ("app", 0x000719f4): [
        ("wait-window", -48, -44, 8, None, (0,), (0x0008669c,)),
    ],
    ("app", 0x0007f4a0): [
        ("request-header", -20, -12, 4, None, (0,), (0x00080d3e,)),
    ],
    ("app", 0x00084300): [
        ("lookup-byte", -18, -22, 1, None, (0,), (0x00062070,)),
    ],
    ("app", 0x00085898): [
        ("request-buffer", -56, -48, 32, None, (0, 1),
         (0x0008705a, 0x00070f1c)),
    ],
    ("app", 0x000503d8): [
        ("fault-log-record", -32, -36, 8, None, (0,), (0x00080780,)),
    ],
    # Fault decoding reuses one exact two-word diagnostic and allocates a
    # separate three-word record only for the live BFAR report.
    ("app", 0x00050558): [
        ("fault-message", -32, -36, 8, None, None, (0x00080780,)),
        ("fault-message-with-value", -64, -28, 12, None, None,
         (0x00080780,)),
    ],
    ("app", 0x00050c24): [
        ("region-index-diagnostic", -24, -20, 12, None, (0,),
         (0x0004d944,)),
    ],
    # The partition walker owns an initialized diagnostic tuple and a sparse
    # descriptor whose reserved bytes are outside the helper's contract.
    ("app", 0x00050c54): [
        ("partition-diagnostic", -80, -68, 12, None, None,
         (0x0004d944,)),
        ("partition-descriptor", -56, -56, 16,
         ((0, 4), (8, 9), (12, 16)), None, (0x00050bf0,)),
    ],
    # The parser publishes this exact two-word error record.  Its decoded wire
    # words remain scalar locals until the deeper copy path, not a generic
    # addressable object at the error publisher boundary.
    ("app", 0x000513e8): [
        ("command-error", -48, -48, 8, None, None, (0x0008633e,)),
    ],
    # The lookup helper initializes the storage pointer; diagnostics and the
    # optional authorization workspace have distinct target-scoped lifetimes.
    ("app", 0x000518a8): [
        ("storage-pointer", -36, -44, 4, (), (4,), (0x0004e048,)),
        ("decoder-diagnostic", -56, -40, 16, None, None,
         (0x0008096a,)),
        ("authorization", -32, -40, 8, None, None,
         (0x00080a82, 0x00080970)),
    ],
    ("app", 0x0007f894): [
        ("callback-value", -12, -20, 4, None, (0,), (0x00080000,)),
    ],
    ("app", 0x00080798): [
        ("mpu-region", -32, -24, 16,
         ((0, 4), (8, 9), (12, 16)), None, (0x00050bf0,)),
    ],
    ("app", 0x00080872): [
        ("decoded-field-header", -48, -40, 8, (), None, (0x00085f9c,)),
    ],
    # The helper clears only the high byte of the caller's saved parameter;
    # the lower 24 bits and that byte form one exact addressable word.
    ("app", 0x000809f6): [
        ("lookup-byte", -20, -28, 4, None, None, (0x000809b0,)),
    ],
    ("app", 0x00080ca0): [
        ("decoded-key-record", -32, -32, 16, None, None,
         (0x00081326,)),
        ("comparison-key", -36, -36, 3, None, None, (0x00086be4,)),
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
    # FUN_0102714a completely initializes these compiler-owned outputs before
    # either caller consumes the handle.  Their pre-call ranges are therefore
    # deliberately empty; the exact target-bound 4+2 byte writes above remain
    # observable, while object identity accounts only for frame placement.
    ("net", 0x010196e0): [
        ("controller-handle", -28, -24, 4, ()),
        ("controller-selector", -30, -26, 2, ()),
    ],
    ("net", 0x01019750): [
        ("controller-handle", -44, -36, 4, ()),
        ("controller-selector", -46, -38, 2, ()),
    ],
    # Event zero publishes the initialized mode/exact-period bytes of a
    # sparse fourteen-byte timing request.  Events two/three instead use the
    # same frame base as a 32-byte callee-owned output snapshot, then pass its
    # identity to the exact consumer.  Target and ordinal scopes keep the two
    # non-overlapping lifetimes distinct despite their shared address.
    ("net", 0x0101ab20): [
        ("timing-request", -64, -56, 14, ((4, 5), (13, 14)), (2,),
         (0x01018dac,)),
        ("current-radio-state", -64, -56, 32, (), (2, 3),
         (0x0101a38c, 0x010231c8)),
    ],
    # The snapshot builder passes a complete 24-byte timing request to the
    # scheduler.  GCC's readable TU places it twenty bytes above the shipped
    # frame location; normalize identity while retaining every initialized
    # byte and both semantic call arguments.
    ("net", 0x0101a38c): [
        ("timing-request", -64, -64, 24,
         ((0, 1), (4, 12), (16, 24)), (5,), (0x0100d4d0,)),
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
        ("serializer-pair-or-descriptor", -144, -60, 20,
         ((0, 18),), None, (0x0004d944,)),
        ("serializer-pair-or-descriptor", -56, -60, 20,
         ((0, 18),), None, (0x00070000,)),
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
    # The display input command is a complete 24-byte queue record.  Its
    # original and readable-C frames coincide; restrict byte comparison to
    # the transport call because the preceding memset receives an interior
    # pointer before the record has been initialized.
    ("app", 0x00049938): [
        ("display-input-command", -40, -40, 24, None, (1,),
         (0x000720d0,)),
    ],
    # local_store_write owns one contiguous key workspace: a 28-byte prefix
    # followed by 100 cleared bytes available to the append helper.
    ("app", 0x00022168): [
        ("local-store-key", -152, -144, 128, None, (1, 2),
         (0x00086fbe, 0x0004e374)),
    ],
    # The flash reader publishes one packed 32-byte settings record.  GCC's
    # readable aggregate saves two fewer callee registers and shifts it by
    # eight bytes without changing its semantic identity or extent.
    ("app", 0x00022e78): [
        ("user-settings-record", -56, -48, 32, None, (1,),
         (0x000225b4,)),
    ],
    # The system-settings reader owns one contiguous persisted record.  The
    # readable aggregate shifts it eight bytes upward, but both memset and the
    # flash backend receive the same semantic 132-byte object.
    ("app", 0x000232f8): [
        ("persisted-system-settings", -148, -140, 132, None, (0, 1),
         (0x00086c78, 0x000225b4)),
    ],
    # Both upgrade helpers submit the same complete twelve-byte flash request.
    # Their readable arrays reserve four fewer bytes below the entry stack.
    ("app", 0x00023bfc): [
        ("dashboard-startup-request", -24, -20, 12, None, (0,),
         (0x000720d0,)),
    ],
    ("app", 0x00024420): [
        ("quick-note-request", -24, -28, 12, None, (0,),
         (0x000720d0,)),
    ],
    # The runtime synchronizer publishes one complete eight-byte wire record;
    # both compilers place it at the same entry-relative stack offset.
    ("app", 0x00016268): [
        ("runtime-sync-packet", -24, -24, 8, None, (0,),
         (0x00025b78,)),
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
    # Four logging calls share one fully initialized five-word record.  The
    # final two receive its two-word interior at +8; object identity differs
    # only because GCC chooses a smaller frame.
    ("net", 0x0102ea40): [
        ("logging-record", -56, -36, 20),
    ],
    # Lookup receives one fully initialized two-word caller-owned record;
    # GCC moves only the frame-relative base by four bytes.
    ("net", 0x01036c2c): [
        ("lookup-values", -20, -24, 8),
    ],
    # FUN_010345f4 receives one initialized selector word.  GCC's larger
    # frame shifts only this caller-owned object's address.
    ("net", 0x0103a924): [
        ("input-selector", -28, -36, 4),
    ],
    # Both glyph walkers pass one initialized uint16_t count object to their
    # callback; GCC shifts only that local by four bytes.
    ("app", 0x00044544): [
        ("glyph-count", -0x2da, -0x2de, 2),
    ],
    ("app", 0x00044bd8): [
        ("glyph-count", -0x2da, -0x2de, 2),
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
    # Installed sdc_fault_handler_t receives module text and source line.  The
    # controller's r2/r3 values are conversion scratch, not callback inputs.
    ("net", 0x01008d00): [2],
    # These wrappers call one zero-argument status/default helper; incoming
    # r0-r3 values at the boundary are residual caller scratch.
    ("app", 0x000560cc): [0],
    ("app", 0x00056a68): [0],
    # Six fixed no-argument helpers surround one binary callback; the final
    # FUN_00047ba8 flush is genuinely zero-argument and r0-r3 are scratch.
    ("app", 0x0003ae6c): [0, 0, 0, 0, 0, 2, 0],
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

# Target-scoped non-contiguous live register arguments.  These are used only
# where callee reconstruction proves an ABI hole; later live registers remain
# compared exactly rather than reducing the call to a shorter prefix.
REVIEWED_CALL_ARGUMENT_INDICES_BY_TARGET = {
    # The erase callback consumes owner/address/length only.  r3 retains the
    # prior 0x800 read length in the shipped mode-two path and is not ABI.
    ("app", 0x00024684): {0x00080008: (0, 1, 2)},
    ("app", 0x0003e05c): {0x0007d376: (0, 2, 3)},
    # FUN_00067138 consumes r0 and r2.  Its catalogued r1 parameter is unused,
    # and this caller intentionally leaves that register as scratch.
    ("app", 0x00067248): {0x00067138: (0, 2)},
    # even_ai_status_icon_render consumes only status (r0) and frame/context
    # (r3).  Its r1/r2 formals are unused; the final-page call intentionally
    # leaves publication temporaries there while passing r3=0.
    ("app", 0x0003bfe0): {0x0003be18: (0, 3)},
}

# FUN_00082a42 consumes the complete three-word log record.  The firmware's
# temporary frame places it at entry-SP-32; GCC's compact frame uses SP-20.
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x0005a0e8)] = [
    ("gatt-sc-store-log", -32, -20, 12, None, None, (0x00082a42,)),
]

# Both state helpers receive the same two-word local result object.  The
# shipped frame places local_2c at entry-SP-44; GCC's readable reconstruction
# places it at entry-SP-48.  Pair the complete object only at those semantic
# helper boundaries, so its contents and later use remain differential.
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x0002c99c)] = [
    ("task-state-result", -44, -48, 8, None, None,
     (0x0002c498, 0x0002c714)),
]

# Arguments beyond these widths are diagnostics-only stale registers on the
# reviewed caller path.  The source still spells all production arguments;
# differential call traces compare only the callee-consumed semantic prefix.
REVIEWED_TARGET_CALL_ARITIES = {
    ("app", 0x0002bef4): {
        0x0007cdf8: 0,  # bounded lock-wait delay
        0x00049858: 1,  # active screen/task selector
        0x0007dda4: 3,  # format, source, task id
        0x00019c70: 3,
    },
    # process_for_new_task is a large state dispatcher whose original keeps
    # loop/context temporaries live in r1-r3 around many unary/no-argument
    # helpers.  These widths come from the recovered callee bodies.  The
    # peer-address test is genuinely binary even though Ghidra omitted both
    # arguments at this call site; the readable source spells the live values.
    ("app", 0x0002c99c): {
        0x000167a8: 0, 0x00023eec: 0, 0x00026c28: 0,
        0x00026f74: 3, 0x0002bc2c: 3, 0x0002be64: 2,
        0x0002bef4: 3, 0x0002bffc: 3, 0x0002c0e8: 1,
        0x0002c180: 0, 0x0002c1fc: 0, 0x0002c214: 0,
        0x0002c224: 1, 0x0002c2b0: 0, 0x0002c498: 4,
        0x0002c714: 4, 0x0002eb40: 0, 0x0002efc0: 0,
        0x00032ee4: 0, 0x00033cdc: 0, 0x00033cf8: 0,
        0x00033d58: 1, 0x0003439c: 0, 0x00034410: 0,
        0x0003443c: 1, 0x0003444c: 0, 0x00034808: 0,
        0x00036030: 0, 0x0003cf34: 0, 0x00072880: 1,
        0x0007c132: 2, 0x0007ce5c: 2, 0x0007ce60: 1,
        0x00086c78: 3,
    },
    # Only the event id is consumed by the onboarding renderer's send-event
    # boundary; r1/r2 are explicitly unused by send_event and remain compiler
    # scratch in the shipped caller.
    ("app", 0x000417f8): {0x000276ec: 1},
    # ANCS initialization has many no-argument Zephyr helpers surrounded by
    # retry counters and object pointers that remain live in caller-scratch
    # registers.  Compare each boundary using the callee's reviewed ABI.
    ("app", 0x00019950): {
        0x000167a8: 0, 0x0007c0a8: 1, 0x00054a44: 1,
        0x00054b70: 0, 0x0005e6d4: 2, 0x0007f192: 0,
        0x0001905c: 1, 0x000191d8: 0, 0x000572fc: 1,
        0x00057330: 1, 0x0005a9d8: 1, 0x000181f0: 0,
        0x00019308: 0, 0x000198cc: 1, 0x0004c0a8: 1,
        0x00019c70: 0,
    },
    # The attitude worker's delay veneer consumes duration and flags only;
    # r2/r3 retain loop/calibration scratch values at the final delay.
    ("app", 0x0000fe88): {
        0x0007ca72: 2, 0x00026624: 1, 0x000276ec: 1,
    },
    # Production-shaped watchdog fixtures install three distinct indirect
    # callbacks.  Each consumes exactly device plus config/options/channel;
    # r2/r3 are address/record temporaries at those boundaries.
    ("app", 0x0002ace0): {
        0x00080000: 2, 0x00080010: 2, 0x00080020: 2,
    },
    ("app", 0x00042a64): {
        0x0007d382: 0, 0x00040708: 0, 0x0007d3be: 0,
        0x000167a8: 0, 0x0002eb40: 0, 0x0002bef4: 3,
    },
    # The default/disabled UART event tail is a zero-argument continuation;
    # descriptor registers at that boundary are caller scratch.
    # Every deferred diagnostic in the file saver is the zero-argument sink;
    # values left in r0-r3 are checksum/address temporaries.
    ("app", 0x00023634): {0x00019c70: 0},
    ("app", 0x000232f8): {
        0x00086c78: 3, 0x000225b4: 3,
    },
    ("app", 0x00023bfc): {0x000720d0: 4, 0x00072880: 1},
    ("app", 0x00024420): {0x000720d0: 4, 0x00072880: 1},
    ("app", 0x000477a0): {0x000778d4: 1, 0x000777f0: 1},
    ("app", 0x00028a1c): {
        0x00032fdc: 0, 0x0007cb48: 4, 0x000167a8: 0,
        0x0007cb8e: 1, 0x00086690: 0, 0x00030af0: 0,
        0x0007d0aa: 1, 0x0002893c: 0, 0x000289e4: 0,
        0x00028964: 0, 0x00032fd0: 1, 0x0004c0a8: 1,
        0x0007dda4: 1, 0x00019c70: 3,
    },
    ("app", 0x00023400): {0x0007dda4: 2, 0x00019c70: 2},
    # Both cache diagnostics consume exactly format and module. Queue count,
    # record size, and branch temporaries left in r2/r3 are caller scratch.
    ("app", 0x0002f6b0): {0x0007dda4: 2, 0x00019c70: 2},
    ("app", 0x00018444): {
        0x00081526: 0, 0x00018334: 2, 0x0007dda4: 3,
        0x00019c70: 2, 0x00056a68: 2,
    },
    ("app", 0x00047538): {
        0x0007dda4: 2, 0x00019c70: 2, 0x0007d74e: 0,
        0x0007d77c: 1, 0x0007d642: 2, 0x0007d6ae: 1,
        0x0007d658: 2, 0x0007d772: 1, 0x0007d67e: 1,
    },
    ("app", 0x00046d2c): {
        0x0007dda4: 2, 0x00019c70: 2, 0x0001655c: 0,
        0x0002e8b4: 0, 0x00080000: 1, 0x00015fdc: 0,
    },
    ("app", 0x000340c4): {
        0x0008705a: 3, 0x00034bd4: 1,
        0x0003384c: 1, 0x00033f54: 1,
    },
    ("app", 0x00024684): {
        0x00072240: 4, 0x0008638c: 1, 0x00086c78: 3,
        0x000167a8: 0, 0x00086be4: 3, 0x00086c04: 3,
        0x00037098: 0, 0x00080000: 4, 0x00080004: 4,
        0x00080008: 3,
    },
    ("app", 0x0003e05c): {0x0007d376: 4, 0x0007d37a: 1},
    # Timestamp publication consumes only the byte-swapped 32-bit timestamp.
    # r1/r2 are dispatch temporaries left live across this late command island.
    ("app", 0x0002af4c): {0x0007c0e2: 1},
    ("app", 0x000289e4): {
        0x0007dda4: 1, 0x00019c70: 1,
        0x00028964: 0, 0x000289b0: 0,
    },
    ("app", 0x0002e8b4): {
        0x0007dda4: 3, 0x00019c70: 3,
    },
    ("app", 0x0003ce04): {
        0x000167a8: 0, 0x00027448: 4, 0x00086c04: 3,
        0x00019c70: 2, 0x0007dda4: 2,
    },
    ("app", 0x00042c8c): {
        0x000167a8: 0, 0x00027448: 4, 0x00086c04: 3,
        0x00019c70: 2, 0x0007dda4: 2,
    },
    # These fixed diagnostic strings contain no substitutions; r2/r3 around
    # the calls are residual scratch, not logger arguments.
    ("app", 0x00046fc0): {0x0007dda4: 2, 0x00019c70: 2},
    ("app", 0x000230e0): {0x0007dda4: 2, 0x00019c70: 2},
    ("app", 0x00022bd0): {0x0007dda4: 2, 0x00019c70: 2},
    ("app", 0x00018bb4): {
        0x00086c78: 3, 0x00072240: 4, 0x00086c04: 3,
        0x000720d0: 4, 0x00019c70: 0,
    },
    ("app", 0x0002ec5c): {
        0x00086c04: 3, 0x00072240: 4, 0x000720d0: 4,
        0x00019c70: 0,
    },
    ("app", 0x00023514): {
        0x00072240: 4, 0x00086c1e: 4, 0x000720d0: 4,
        0x00019c70: 0,
    },
    ("app", 0x0002e4e8): {
        0x000864c2: 1, 0x0008638c: 1, 0x00083a9a: 1,
        0x000167a8: 0, 0x00019c70: 0,
    },
    ("app", 0x00023d0c): {
        0x0008638c: 1, 0x000167a8: 0, 0x00080000: 4,
        0x00019c70: 0,
    },
    ("app", 0x000183e4): {
        0x00018334: 2, 0x00019c70: 3, 0x0007dda4: 3,
    },
    ("app", 0x00023b78): {
        0x000720d0: 4, 0x00072880: 1, 0x00019c70: 2,
        0x0007e2fa: 2,
    },
    # The software double divider consumes all four IEEE-754 words in r0-r3.
    ("app", 0x000875e4): {0x0000db4c: 4},
    # The CBOR reader helpers consume the explicit width in r2.  The signed
    # integer decoder consumes only r0-r2; r3 merely retains the byte count in
    # the shipped build and is caller scratch under AAPCS.
    ("app", 0x00085ebc): {0x00085da2: 4, 0x00085e1a: 3,
                           0x00085dc4: 2},
    ("app", 0x00086064): {0x00085d36: 1, 0x00085d70: 2,
                           0x00085d82: 0, 0x00085dd2: 1,
                           0x00085e1a: 3, 0x0008603c: 2,
                           0x00086064: 2},
    ("app", 0x0008629e): {0x000861c2: 2, 0x00086208: 3},
    ("app", 0x0008688e): {0x000867da: 0},
    ("app", 0x00086b7e): {0x00077e4c: 3},
    ("app", 0x00083cfc): {
        0x00083cde: 4, 0x00067884: 1, 0x000678d0: 1,
    },
    ("app", 0x00083dc8): {0x00083d60: 4},
    ("app", 0x00083e70): {0x00083d60: 4, 0x00083dc8: 4},
    ("app", 0x00083ede): {0x00061f64: 1},
    ("app", 0x000840cc): {
        0x00084068: 2, 0x00084090: 0,
        0x00080000: 2,  # bounds callback: owner, in/out value pointer
        0x00080004: 1,  # activation callback: owner only
    },
    ("app", 0x000755f8): {
        0x000751d0: 4, 0x00072040: 1, 0x00072078: 1,
        0x000753ec: 3, 0x0007205c: 1, 0x00073f6c: 4,
    },
    # JSON text allocation/release hooks and tree resource release callbacks
    # each consume exactly the one pointer/length word supplied in r0.
    ("app", 0x00064290): {0x00080000: 1, 0x00080004: 1},
    ("app", 0x00064b1c): {0x00080000: 1},
    # The installed pin-controller callback consumes controller, pin index,
    # and the complete flag word; the readiness query is zero-argument.
    ("app", 0x000620cc): {0x0008638c: 0, 0x00080000: 3},
    ("app", 0x00059920): {
        0x00081526: 1, 0x00086fee: 2, 0x0007ddbe: 4,
        0x00081ddc: 3, 0x00059834: 1,
    },
    ("app", 0x00059f04): {
        0x00080cf2: 2, 0x0007f1e8: 2, 0x00077c1c: 3,
        0x00059bcc: 2, 0x000828da: 2, 0x00082a42: 3,
    },
    ("app", 0x0007c28e): {0x00032ee4: 0, 0x00022658: 3},
    ("app", 0x0007c3d0): {0x00024e60: 3},
    ("app", 0x0007c968): {0x000257ec: 4},
    ("app", 0x0007cb8e): {0x0000e244: 4, 0x0007cb8a: 4,
                           0x00074844: 4},
    ("app", 0x00033abc): {
        0x0007c1fe: 4, 0x0007dda4: 2, 0x00019c70: 0,
        0x00080000: 2,
    },
    ("app", 0x000431c0): {
        0x0007dda4: 2, 0x00019c70: 0, 0x0007d4ec: 0,
        0x0007d6f4: 1,
    },
    ("app", 0x00043228): {
        0x0007dda4: 2, 0x00019c70: 0, 0x0007d4ec: 0,
        0x000167a8: 0, 0x000471cc: 4, 0x00047260: 4,
    },
    ("app", 0x000435d4): {
        0x0007dda4: 2, 0x00019c70: 0, 0x0004588c: 4,
        0x00086c04: 3, 0x000431a8: 0, 0x000471cc: 4,
        0x0007d53a: 4, 0x000167a8: 0, 0x00047260: 4,
    },
    ("app", 0x00043bd8): {
        0x0007dda4: 2, 0x00019c70: 0, 0x000431a8: 0,
        0x000471cc: 4, 0x000167a8: 0, 0x00047260: 4,
    },
    # Exact decoder/helper prototypes; the original optimized call sites
    # deliberately leave unrelated address/status values in higher registers.
    ("app", 0x000518a8): {
        0x00086c78: 3, 0x00086be4: 2, 0x00080a46: 1,
        0x0007e2ec: 2, 0x000809f6: 1, 0x0005169c: 1,
        0x0004e048: 2, 0x0008096a: 3, 0x0007ef7e: 0,
        0x00080a82: 1, 0x00080970: 2,
    },
    ("app", 0x000513e8): {
        0x00051354: 2, 0x0005139c: 1, 0x0005f558: 2,
        0x000807f6: 3, 0x00080830: 2, 0x00080864: 1,
        0x000861aa: 4, 0x00080ae6: 2, 0x00080b0e: 2,
        0x0008630c: 2, 0x0008633e: 2, 0x0008634c: 2,
        0x0008635c: 2,
    },
    ("app", 0x0007f894): {0x00080000: 4},
    ("app", 0x00080798): {0x00050c24: 1, 0x00050bf0: 2},
    ("app", 0x00080872): {
        0x00085fa2: 0, 0x00085f9c: 2, 0x00085fce: 1,
        0x00086064: 2, 0x00086be4: 2, 0x00080000: 2,
    },
    ("app", 0x000809f6): {
        0x00051c68: 0, 0x00080a46: 1, 0x000809b0: 4,
    },
    ("app", 0x00080ca0): {
        0x00086c78: 3, 0x00081326: 2, 0x00086be4: 3,
    },
    # This tail continuation consumes only the identity pointer. The global
    # counters left in r1-r3 are implementation temporaries, not its ABI.
    ("app", 0x0005505c): {0x00054ea8: 1},
    # Both controller refresh helpers consume request plus descriptor only.
    # Their catalog prototypes are ambiguous; r2/r3 are branch temporaries.
    ("app", 0x00055454): {0x000810f2: 2, 0x00081102: 2},
    # The channel mapper mutates its single in/out integer pointer. Registers
    # r1-r3 contain address-construction temporaries after the preceding calls.
    ("app", 0x00065b18): {0x00065584: 1},
    # CRC-16 consumes exactly crc, buffer, and byte count.  r3 is stale from
    # the preceding byte-dump loop and is not part of the recovered ABI.
    ("app", 0x00022974): {0x0007da4a: 3},
    # The tail routine is a zero-argument state flush.  r0-r2 are scratch
    # values left by the preceding record formatter and are not its ABI.
    ("app", 0x0003439c): {0x00033b0c: 0},
    # These tree accessors have fixed recovered ABIs.  In particular, the
    # one-argument lookup leaves unrelated selector values in r1-r3.
    ("app", 0x00034dbc): {
        0x0008500c: 0, 0x00085020: 1, 0x00085030: 1,
        0x0008503c: 2, 0x000850c8: 0, 0x00064b1c: 1,
        0x00086c78: 3, 0x0008705a: 3,
    },
    # The indexed variant deliberately supplies a second lookup word.  The
    # diagnostic logger consumes at most its format word plus one value; r2
    # and r3 seen at shorter call sites are stale comparison temporaries.
    ("app", 0x00035050): {
        0x0008500c: 0, 0x00085020: 1, 0x00085030: 2,
        0x0008503c: 2, 0x000850c8: 0, 0x00034ff0: 2,
        0x00064b1c: 1, 0x0008705a: 3, 0x00019c70: 2,
    },
    # The glyph renderer consumes exactly the buffer pointer and the fixed
    # 0x120-byte capacity.  Later register values are caller scratch.
    ("app", 0x000362e8): {0x00047a4c: 2},
    # Firmware image reader and glyph-row renderer.  The device callback uses
    # context, address, destination, and length; the renderer consumes only
    # inverted byte and glyph width, leaving r2/r3 as loop scratch.
    ("app", 0x00036820): {
        0x00076d6c: 1, 0x00086c78: 3, 0x000167a8: 0,
        0x00080000: 4, 0x00087036: 3, 0x0007d1c8: 1,
        0x0003678c: 2, 0x00086c04: 3, 0x00076d7c: 1,
    },
    # Shutdown helpers consume no arguments, the work item remover consumes
    # object plus callback identity, and the embedded object destructor is
    # unary.  r2/r3 at the remover are caller scratch.
    ("app", 0x000526f4): {
        0x00080b28: 0, 0x00072e50: 2, 0x000864e8: 1,
    },
    # Property serialization helpers use fixed one-, two-, and three-word
    # ABIs.  The catalog's four-word guesses include stack-workspace residue
    # after the two integer emitters and final close operation.
    ("app", 0x00051ac0): {
        0x0008634c: 2, 0x0008099e: 3, 0x00086320: 2,
        0x00051f88: 2, 0x0000ef12: 1, 0x00086338: 2,
        0x00086378: 2, 0x0008635c: 2,
    },
    # The area handle is the sole argument to the close helper.
    ("app", 0x00051d8c): {0x0007ef7e: 1},
    ("app", 0x0005fb30): {0x000837a2: 3, 0x0004ba38: 1},
    ("app", 0x00061624): {
        0x000658e8: 4, 0x0006567c: 3, 0x000657e4: 3,
        0x00065b18: 1, 0x000659cc: 1,
    },
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
    # Net-core serializer uses the same recovered output-hook ABI.  The
    # production-shaped directed fixture below installs this external hook.
    ("net", 0x0102bfe4): {0x00070000: 3},
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
    ("app", 0x000497b0): {
        0x00086c78: 3, 0x00086c04: 3, 0x000720d0: 4,
    },
    ("app", 0x00049a28): {0x00086c78: 3, 0x000720d0: 4},
    ("app", 0x0003fd44): {
        0x000167a8: 0, 0x000431b4: 1, 0x00077914: 4,
        0x0007d224: 0, 0x0007d3ee: 0, 0x0007d446: 0,
        0x00043e90: 4, 0x000442bc: 4, 0x00043484: 4,
    },
    ("app", 0x00021c04): {
        0x00064ca4: 0, 0x0008509e: 3, 0x00085046: 3,
        0x00085014: 1, 0x0000ef12: 1, 0x00021a40: 4,
        0x00064b1c: 1,
    },
    ("app", 0x0003dff8): {
        0x0007d3ee: 0, 0x0007d446: 0, 0x00043484: 4,
    },
    ("app", 0x00019ed4): {
        0x00086c78: 3, 0x0002ecf4: 0, 0x0002ed00: 1,
        0x000167a8: 0, 0x0007cbfe: 2, 0x00086698: 0,
    },
    ("app", 0x000276ec): {
        0x000181fc: 0, 0x00017eec: 2,
        0x0007cb4c: 1, 0x0007cb8e: 1,
    },
    # Bounded-copy helpers: the runtime-constraint sink consumes no ABI
    # arguments and the successful tail copier consumes dst/src/length.
    ("app", 0x00086c1e): {0x00051164: 0, 0x00086c04: 3},
    ("app", 0x00087080): {0x00051164: 0, 0x0008705a: 3},
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
    ("app", 0x000340c4): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in {
            0x000a7ef6: 4, 0x000a7f12: 4, 0x000a7f41: 4,
            0x000a7f79: 4, 0x000a7fae: 2, 0x000a7fe3: 2,
        }.items()
    },
    ("app", 0x00024684): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in {
            0x0009ef15: 2, 0x0009ef3f: 2, 0x0009ee54: 2,
            0x0009ef67: 2, 0x0009efaf: 2,
            0x0009e9ea: 3, 0x0009ea0a: 3, 0x0009eba7: 3,
            0x0009ebc6: 3, 0x0009ef8e: 3, 0x0009f010: 3,
        }.items()
    },
}

# The endpoint table stores a three-argument callback and the receive routine
# tail-calls it with endpoint context, payload, and payload size.
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00025a48)] = {0x00080000: 3}

REVIEWED_TARGET_CALL_ARITIES[("app", 0x0005a0e8)] = {
    0x00053008: 4,
    0x00082a42: 3,
}


# Re-reviewed brightness/serialization helpers use fixed production ABIs.
# Keeping these widths target-scoped prevents caller-scratch registers from
# masquerading as semantic arguments at zero/one-argument helper boundaries.
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00047b1c)] = {
    0x000167a8: 0, 0x00086c78: 3, 0x00086c04: 3, 0x000720d0: 4,
}
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00025c54)] = {
    0x0004cb90: 1, 0x0004cbec: 3, 0x00072908: 4,
    0x0007dda4: 2, 0x00019c70: 2,
}
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00049000)] = {
    0x0007dda4: 3, 0x00019c70: 3,
}
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00031cbc)] = {
    0x000167a8: 0, 0x00022b00: 2, 0x000232f8: 1, 0x0007d14a: 1,
}
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00046e3c)] = {
    0x0007dda4: 3, 0x00019c70: 3, 0x000167a8: 0,
    0x0007d63e: 1, 0x0007d696: 1, 0x0007d67e: 1,
    0x0007d642: 2, 0x0007d772: 1,
}

# Additional AAPCS words consumed from the callee-entry stack. Register call
# arity remains independently reviewed above.
REVIEWED_TARGET_CALL_STACK_ARITIES = {
    # Newlib __assert_func passes line, optional-function prefix, and optional
    # function name after the four register arguments to fiprintf.
    ("app", 0x00076a94): {0x00076cc8: 3},
    ("app", 0x0003ce04): {0x00027448: 1},
    ("app", 0x00042c8c): {0x00027448: 1},
    ("app", 0x0003dff8): {0x00043484: 3},
    ("app", 0x0003fd44): {
        0x00077914: 1, 0x00043e90: 8,
        0x000442bc: 3, 0x00043484: 2,
    },
    # FUN_00083d60 receives the owning object as its fifth AAPCS argument.
    ("app", 0x00083dc8): {0x00083d60: 1},
    ("app", 0x000755f8): {0x000751d0: 3, 0x00073f6c: 2},
    # FUN_00082932 consumes its payload length as argument five.
    ("app", 0x000829c0): {0x00082932: 1},
    ("app", 0x00082a1a): {0x00082932: 1},
    ("app", 0x00076cc8): {0x00076ed4: 2},
    ("app", 0x000777f0): {0x00076ed4: 2},
    # The GPIO channel updater has seven integer/pointer arguments: four in
    # registers and three exact AAPCS stack words.
    ("app", 0x0006567c): {0x00085130: 3},
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
    # LC3 test encoder consumes four additional AAPCS words after r0-r3:
    # frame length, output offset, repeated state handle, and input pointer.
    ("app", 0x0002ed68): {0x00069238: 4},
    # Command publication passes its completion flag as AAPCS argument five.
    ("app", 0x000513e8): {0x000861aa: 1},
    ("app", 0x0007f894): {0x00080000: 1},
    ("app", 0x000809f6): {0x000809b0: 1},
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
    # FUN_0004d100 passes a locally-owned three-word request chain as argument
    # six to FUN_00071358. Capture both AAPCS stack words at that exact target
    # so the pointer in call-SP+4 is observable to paired-stack-object checks.
    ("app", 0x0004d100): {0x00071358: 2},
}

# Variadic diagnostics share two logger targets but consume a format-specific
# number of arguments.  Compare only the exact format ABI, not stale r2/r3
# values left live by surrounding dispatch code.
REVIEWED_CALL_ARITIES_BY_FORMAT = {
    ("app", 0x00019950): {
        (0x0007dda4, 0x0009af3b): 2,
        (0x0007dda4, 0x0009af75): 3,
        (0x0007dda4, 0x0009afa1): 2,
        (0x0007dda4, 0x0009b089): 1,
        (0x0007dda4, 0x0009b0ae): 2,
        (0x0007dda4, 0x0009afc3): 2,
        (0x0007dda4, 0x0009afed): 1,
        (0x0007dda4, 0x0009b019): 1,
        (0x0007dda4, 0x0009b04b): 1,
        (0x0007dda4, 0x0009b060): 3,
    },
    ("app", 0x00032c28): {
        (0x0007dda4, 0x000a74dc): 2,
        (0x0007dda4, 0x000a7500): 4,
        (0x0007dda4, 0x0009e2f1): 3,
        (0x00019c70, 0x000a74dc): 2,
        (0x00019c70, 0x000a7500): 4,
        (0x00019c70, 0x0009e2f1): 3,
    },
    # Watchdog diagnostics have exact fixed record widths.  The alternate
    # sink is a zero-argument backend even though the selected format remains
    # live in r0 at several call sites.
    ("app", 0x0002ace0): {
        **{(0x0007dda4, fmt): arity for fmt, arity in (
            (0x000a1b10, 2), (0x000a1b33, 3), (0x000a1b50, 2),
            (0x000a1b88, 2), (0x000a1bbc, 2), (0x000a1bda, 2),
            (0x000a1bf6, 3), (0x000a1c17, 2), (0x000a1c32, 2))},
        **{(0x00019c70, fmt): 0 for fmt in (
            0x000a1b10, 0x000a1b33, 0x000a1b50, 0x000a1b88,
            0x000a1bbc, 0x000a1bda, 0x000a1bf6, 0x000a1c17,
            0x000a1c32)},
    },
    # Retry diagnostics use the no-argument deferred sink even though the
    # selected format remains in r0.  The final result record has four fields.
    ("app", 0x00035608): {
        (0x00019c70, 0x000a896c): 0,
        (0x00019c70, 0x000a8994): 4,
    },
    # Both message-sync deferred diagnostics are zero-argument sink calls.
    ("app", 0x0002c224): {
        **{(0x00019c70, fmt): 0
           for fmt in (0x000a2690, 0x000a269c, 0x000a26ae)},
        (0x0007dda4, 0x000a2690): 2,
        (0x0007dda4, 0x000a269c): 2,
        (0x0007dda4, 0x000a26ae): 1,
    },
    # UART event diagnostics have fixed recovered format-specific widths.
    ("app", 0x00033384): {
        (0x0007e2fa, 0x00099cbd): 4,
        (0x0007e2fa, 0x000a7a19): 1,
        (0x0007e2fa, 0x000a7a33): 1,
        **{(0x0007dda4, fmt): arity for fmt, arity in (
            (0x000a797b, 5), (0x000a7993, 2), (0x000a7999, 2),
            (0x000a79ab, 5), (0x000a79bf, 1), (0x000a7a52, 1),
            (0x000f5400, 1))},
        **{(0x00019c70, fmt): arity for fmt, arity in (
            (0x000a797b, 0), (0x000a7999, 0))},
    },
    ("app", 0x00042a64): {
        (target, 0x000aa611): 3
        for target in (0x0007dda4, 0x00019c70)
    } | {
        (target, 0x000aa63d): 3
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x00019ed4): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in ((0x0009b45e, 3), (0x0009b482, 4))
    },
    ("app", 0x00022ddc): {
        (target, 0x0009e5f3): 2
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x00016268): {
        (target, 0x0009957c): 4
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x00022168): {
        (target, fmt): 4
        for target in (0x0007dda4, 0x00019c70)
        for fmt in (0x0009e161, 0x0009e187)
    },
    ("app", 0x00022e78): {
        (target, fmt): 2
        for target in (0x0007dda4, 0x00019c70)
        for fmt in (0x0009e60c, 0x0009e632)
    },
    # Queue initialization failures have exactly format and module arguments.
    # The preceding size/count values in r2/r3 are not logger ABI fields.
    ("app", 0x0002ebd8): {
        (target, 0x000a3ee4): 2
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x00018b6c): {
        (target, 0x0009a949): 2
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x00018e04): {
        (target, 0x0009a949): 2
        for target in (0x0007dda4, 0x00019c70)
    },
    # IPC packet diagnostics use all four argument registers plus nine
    # reviewed stack words declared in the companion table below.
    ("app", 0x00025a48): {
        (target, 0x0009f4a1): 4
        for target in (0x0007dda4, 0x00019c70)
    },
    # Whitelist diagnostics range from a format-only decision to a three-word
    # identifier/entry report.  Compare each exact format ABI for either sink.
    ("app", 0x00034bd4): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in {
            0x000a844e: 3, 0x000a846a: 3, 0x000a8491: 2,
            0x000a84a2: 1, 0x000a84c4: 1,
            0x000a84e7: 1, 0x000a850c: 1,
            0x000a8532: 1, 0x000a8558: 1,
            0x000a857f: 1, 0x000a85a1: 1,
            0x000a85c4: 2, 0x000a85d6: 3,
        }.items()
    },
    ("app", 0x00021c04): {
        (target, 0x0009d7ae): 3
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x0003dff8): {
        (target, 0x000a9e91): 2
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x00018bb4): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in ((0x0009a964, 1), (0x0009a981, 2))
    },
    ("app", 0x0002ec5c): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in ((0x000a3f17, 3), (0x000a3f45, 2))
    },
    ("app", 0x00023514): {
        (target, fmt): 2
        for target in (0x0007dda4, 0x00019c70)
        for fmt in (0x0009e824, 0x0009e840)
    },
    ("app", 0x0002e4e8): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in ((0x000a3a8b, 4), (0x000a3aa6, 2))
    },
    ("app", 0x00023d0c): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in {
            0x0009e9bf: 4, 0x0009e9ea: 4,
            0x0009ea0a: 3, 0x0009ea37: 3,
        }.items()
    },
    ("app", 0x000497b0): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in ((0x000ef01c, 3), (0x000ef058, 2),
                           (0x000f0044, 2))
    },
    ("app", 0x00049a28): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in ((0x000ef058, 2), (0x000f00ea, 3))
    },
    ("app", 0x0003fd44): {
        (target, 0x000aa487): 4
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x00049938): {
        (target, fmt): 2
        for target in (0x0007dda4, 0x00019c70)
        for fmt in (0x000ef058, 0x000f00bb)
    },
    # SettingStoreHandler reaches both logger implementations with two- and
    # three-word formats.  Registers above each format's actual ABI are stale
    # branch temporaries and must not become invented diagnostic arguments.
    ("app", 0x00023f04): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in {
            0x0009ead2: 2, 0x0009eaf4: 3,
            0x0009eb2e: 2, 0x0009eb66: 2, 0x0009e9ea: 3,
            0x0009eba7: 3, 0x0009ebc6: 3, 0x0009ebe5: 3,
            0x0009ea0a: 3, 0x0009ec11: 2, 0x0009ec34: 3,
            0x0009ec72: 2, 0x0009eca4: 3,
            0x0009ea7b: 2, 0x0009eaa5: 2,
        }.items()
    },
    ("app", 0x0003b78c): {
        (target, 0x0009d30b): 2
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x000518a8): {
        (0x0007e2fa, 0x00099cbd): 4,
        (0x0007e2fa, 0x000f25e2): 1,
    },
    ("app", 0x0002e67c): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in {
            0x000a3b3f: 2, 0x000a3af8: 2, 0x000a3c68: 2,
            0x000a3c0c: 2, 0x000a3c2d: 2,
            0x000a3b7a: 3, 0x000a3bd6: 3, 0x000a3b5a: 3,
            0x000a3bb6: 3, 0x000a3b8e: 3, 0x000a3bea: 3,
        }.items()
    },
    ("app", 0x00022974): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in {
            0x0009e484: 2, 0x0009e4a3: 2, 0x000a40ec: 2,
            0x0009e4c7: 3, 0x0009e4e3: 3, 0x0009e4f0: 2,
        }.items()
    },
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
    # Power-control and settings diagnostics all carry format plus module.
    # pull_message has one format-only notice, one count notice, and a
    # four-register invalid-output diagnostic.
    **{
        ("app", va): {
            (target, fmt): 2
            for target in (0x0007dda4, 0x00019c70)
            for fmt in formats
        }
        for va, formats in {
            0x00015f80: (0x0009945a, 0x00099476),
            0x000160b4: (0x0009945a, 0x000994f7),
            0x00015fdc: (0x0009949a, 0x0009940b, 0x000994b9,
                        0x00099329, 0x000994d3),
            0x000232f8: (0x0009e580, 0x0009e5a6),
        }.items()
    },
    ("app", 0x00023bfc): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in ((0x0009e98c, 3), (0x0009e903, 2))
    },
    ("app", 0x00024420): {
        (target, fmt): arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, arity in ((0x0009edf3, 3), (0x0009edc2, 2))
    },
    ("app", 0x000477a0): {
        (target, 0x000d7499): 2
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x00028a1c): {
        (0x0007dda4, fmt): arity
        for fmt, arity in {
            0x000a0b33: 1, 0x000a0b7c: 1, 0x000a6990: 2,
            0x000a0bc5: 1, 0x000a0c0f: 1, 0x000a0c21: 1,
            0x000a0c6c: 3,
        }.items()
    },
    ("app", 0x000342e0): {
        **{(target, 0x000a804b): 4
           for target in (0x0007dda4, 0x00019c70)},
        **{(target, 0x000a80bc): 1
           for target in (0x0007dda4, 0x00019c70)},
        **{(target, 0x000a806c): 2
           for target in (0x0007dda4, 0x00019c70)},
    },
}

# Stack-passed variadic words are likewise format-specific.  In particular,
# the ANCS worker's initial diagnostic consumes p4 as argument five while its
# later logger formats consume no stack words.
# These two callers mix format-only diagnostics with payload-bearing formats,
# so the logger ABI must be selected by the literal format rather than by the
# shared variadic sink address.
REVIEWED_CALL_ARITIES_BY_FORMAT[("app", 0x00047b1c)] = {
    **{(target, 0x000ef01c): 3
       for target in (0x0007dda4, 0x00019c70)},
    **{(target, 0x000ef058): 2
       for target in (0x0007dda4, 0x00019c70)},
}
REVIEWED_CALL_ARITIES_BY_FORMAT[("app", 0x00031cbc)] = {
    **{(target, fmt): 1
       for target in (0x0007dda4, 0x00019c70)
       for fmt in (0x000a70a0, 0x000a70c1, 0x000a672f)},
    **{(target, 0x000a70e7): 3
       for target in (0x0007dda4, 0x00019c70)},
}
REVIEWED_CALL_ARITIES_BY_FORMAT[("app", 0x0003b824)] = {
    **{(target, fmt): 2
       for target in (0x0007dda4, 0x00019c70)
       for fmt in (0x000a960d, 0x000a9654, 0x000a96e0,
                   0x000a9709, 0x000a9727, 0x000a974b,
                   0x000a9775, 0x000a9797, 0x000a97bb,
                   0x000a97e4)},
    **{(target, 0x000a9629): 3
       for target in (0x0007dda4, 0x00019c70)},
}

REVIEWED_CALL_STACK_ARITIES_BY_FORMAT = {
    ("app", 0x00019ed4): {
        (target, 0x0009b482): 2
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x000340c4): {
        (target, fmt): stack_arity
        for target in (0x0007dda4, 0x00019c70)
        for fmt, stack_arity in {
            0x000a7ef6: 3, 0x000a7f12: 3, 0x000a7f41: 2,
            0x000a7f79: 3, 0x000a7fae: 0, 0x000a7fe3: 0,
        }.items()
    },
    # role/mode occupy r2/r3; channel, result, and both addresses are the four
    # exact stacked variadic words for either runtime diagnostic sink.
    ("app", 0x00016268): {
        (target, 0x0009957c): 4
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x00025a48): {
        (target, 0x0009f4a1): 9
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x0002e4e8): {
        (target, 0x000a3a8b): 1
        for target in (0x0007dda4, 0x00019c70)
    },
    ("app", 0x00023d0c): {
        (target, fmt): 1
        for target in (0x0007dda4, 0x00019c70)
        for fmt in (0x0009e9bf, 0x0009e9ea)
    },
    ("app", 0x00019718): {
        (target, 0x00099969): 1
        for target in (0x0007dda4, 0x00019c70)
    },
    # Only the direct DEBUG_PRINT path forwards param_4 as a fifth,
    # stack-passed diagnostic word.  The buffered sink consumes r0-r3 only.
    ("app", 0x000342e0): {
        (0x0007dda4, 0x000a804b): 1,
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
                    deadline=(0, 0, 0), exit_flag=0, device_type=0,
                    uptime_ticks=None, language=None, sparse_pixels=False,
                    warning_offset=100):
    """Production-shaped QuickNote UI state with bounded shared raster rows."""
    ctx = bytearray(0x400)
    for row in range(199):
        struct.pack_into("<I", ctx, 0x24 + row * 4, _QN_ROW)
    global_state = bytearray(0x1100)
    global_state[0] = int(device_type) & 0xff
    struct.pack_into("<I", global_state, 0x1020, _QN_ENABLE)
    struct.pack_into("<I", global_state, 0xeb4, _QN_FB)
    struct.pack_into("<I", global_state, 0xeb8, _QN_FB + 0x400)
    row_image = bytearray(0x140)
    if sparse_pixels:
        # Three columns encounter distinct 0/0xf/0xf0/0xff mask values over
        # the four production frames without producing a 63k-write trace.
        row_image[2] = 0xff
        row_image[16] = 0xff
        row_image[29] = 0xff
    oracles = {i: {0: _QN_GLOBAL, 1: 0} for i in range(160)}
    if state == 0 and phase == 1 and language is not None:
        # Initial logging contributes four calls before the gate; without it,
        # memset/accessor/screen/reset place the language query at ordinal six.
        language_ordinal = 10 if level > 2 else 6
        oracles[language_ordinal] = {0: int(language), 1: 0}
    if state == 1 and phase == 3 and uptime_ticks is not None:
        uptime_ordinal = 4 + (2 if level > 2 else 0) + (1 if device_type == 1 else 0)
        oracles[uptime_ordinal] = {
            0: int(uptime_ticks) & 0xffffffff,
            1: (int(uptime_ticks) >> 32) & 0xffffffff,
        }
    if state == 2 and phase != 2 and uptime_ticks is not None:
        uptime_ordinal = 3 if level > 2 else 2
        oracles[uptime_ordinal] = {
            0: int(uptime_ticks) & 0xffffffff,
            1: (int(uptime_ticks) >> 32) & 0xffffffff,
        }
        if language is not None:
            # Within-warning display calls screen-clear, two icon metrics and
            # bitmap draw before the language selector.
            language_ordinal = 9 if level > 2 else 7
            oracles[language_ordinal] = {0: int(language), 1: 0}
    return (
        {0: _QN_CTX, 2: phase},
        [(_QN_CTX, bytes(ctx)), (_QN_GLOBAL, bytes(global_state)),
         (_QN_ENABLE, bytes((enable,))), (_QN_FB, bytes(0x800)),
         # Zero pixels exercise all 199x320 loop bounds without manufacturing
         # 63k non-stack write events per language pass.
         (_QN_ROW, bytes(row_image)),
         (0x20004978, bytes((state, 0, 0, 0)) +
          b"".join(x.to_bytes(4, "little") for x in deadline)),
         (0x2000230c, level.to_bytes(4, "little", signed=True)),
         (0x20007554, sink.to_bytes(4, "little")),
         (0x2001b817, bytes((exit_flag,))),
         (0x200024e8, int(warning_offset).to_bytes(4, "little", signed=True))],
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


def _app_61c40_case(pin, enabled, diagnostic=False):
    """One coherent pin-permission descriptor and selector."""
    owner = emu.SCRATCH + 0x1000
    device = emu.SCRATCH + 0x1100
    owner_data = bytearray(8)
    owner_data[4:8] = device.to_bytes(4, "little")
    device_data = bytearray(8)
    if enabled and pin < 32:
        device_data[4:8] = (1 << pin).to_bytes(4, "little")
    return ({0: owner, 1: pin, 2: int(diagnostic)},
            [(owner, bytes(owner_data)), (device, bytes(device_data))])


def _app_456fc_case(selector, index):
    """One table-dispatch fixture with a unique selected word."""
    bases = {
        1: 0x0008aa10, 3: 0x0008a4e8, 4: 0x0008a3e0,
        5: 0x0008a6f8, 6: 0x0008a908, 7: 0x0008a800,
        14: 0x0008a5f0,
    }
    base = bases.get(selector, 0x0008ab18)
    value = (0x456f0000 | (selector << 8) | index) & 0xffffffff
    return ({0: selector, 1: index},
            [(base + index * 4, value.to_bytes(4, "little"))])


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


def _net_record_array_case(mode=0, active=False, param4=0, count=1):
    """One bounded FUN_010384a8 descriptor iteration.

    The descriptor's low six mode bits select four distinct nested-list
    fields.  A nonzero selected field exercises the immediate completion arm;
    zero plus a nonempty output byte exercises the insertion helper.  Keeping
    count at zero/one prevents unconstrained 32-bit loop counts while retaining
    every recovered mode and both sides of the caller's param4 gate.
    """
    record = emu.SCRATCH + 0x1000
    nested = emu.SCRATCH + 0x1800
    output = emu.SCRATCH + 0x2000
    descriptor = bytearray(0x14)
    descriptor[0x0d] = int(mode) & 0x3f
    descriptor[0x10:0x14] = nested.to_bytes(4, "little")
    nested_record = bytearray(0x30)
    if active:
        selected_offset = {1: 8, 2: 8, 4: 0, 8: 0x24}.get(mode)
        if selected_offset is not None:
            nested_record[selected_offset:selected_offset + 4] = \
                (1).to_bytes(4, "little")
    return (
        {0: record, 1: count, 2: output, 3: param4},
        [(record, bytes(descriptor)), (nested, bytes(nested_record)),
         (output, b"X\0")],
    )


def _app_5505c_case(limit, count):
    identity = emu.SCRATCH + 0x1000
    state = bytearray(0x122)
    state[0x120] = limit
    state[0x121] = count
    return ({0: identity},
            [(identity, bytes(9)), (0x20002000, bytes(state))])


def _app_66ec0_case(frequency, radio_disabled=1):
    owner = emu.SCRATCH + 0x1000
    config = emu.SCRATCH + 0x1100
    device = emu.SCRATCH + 0x2000
    owner_data = bytearray(8)
    owner_data[0:4] = device.to_bytes(4, "little")
    owner_data[4] = 0
    config_data = bytearray(0x28)
    for offset, value in ((0, 0x11111111), (4, 0x22222222),
                          (8, 0x33333333), (0x0c, 0x44444444),
                          (0x14, frequency), (0x1c, 2)):
        config_data[offset:offset + 4] = value.to_bytes(4, "little")
    config_data[0x10] = 1
    config_data[0x12] = 7
    config_data[0x18] = 2
    config_data[0x19] = 1
    config_data[0x1a] = 3
    config_data[0x20] = 5
    config_data[0x21] = 0
    config_data[0x22] = 6
    config_data[0x23] = radio_disabled
    config_data[0x24] = 0
    return (
        {0: owner, 1: config},
        [(owner, bytes(owner_data)), (config, bytes(config_data)),
         (device, bytes(0x600)), (0x2000b384, bytes(0x24))],
    )


def _connection_init_case(owner, peer, options, option_enable=0,
                          option_callback=0, active_flags=0):
    owner_bytes = bytearray(0x200)
    owner_bytes[0xf0:0xf4] = int(active_flags).to_bytes(4, "little")
    absolute = [(emu.SCRATCH + 0x1000, bytes(owner_bytes))]
    if options:
        option_bytes = bytearray(8)
        option_bytes[0:4] = int(option_callback).to_bytes(4, "little")
        option_bytes[4] = option_enable
        absolute.append((emu.SCRATCH + 0x3000, bytes(option_bytes)))
    absolute.append((emu.STACK_TOP,
                     int(options).to_bytes(4, "little")))
    return ({0: owner, 1: peer, 2: 0x1234, 3: 0x5678}, absolute)


def _audio_fw_master_case(command, payload=b"", request_kind=0):
    """One bounded master-side audio/control request and its response buffer."""
    context = emu.SCRATCH + 0x1000
    request = emu.SCRATCH + 0x3000
    response = emu.SCRATCH + 0x3100
    context_image = bytearray(0x1100)
    request_image = bytearray(0x20)
    response_image = bytearray(0x120)
    request_image[0] = command
    request_image[1] = request_kind
    request_image[4:4 + len(payload)] = payload
    # Command 1's unchanged-mode arm is a real, bounded acknowledgement path.
    if command == 1 and len(payload) >= 2:
        context_image[0xed5] = payload[0]
        context_image[0xf98] = payload[1]
    return (
        {0: context, 1: request, 2: response, 3: 0x55667788},
        [(context, bytes(context_image)), (request, bytes(request_image)),
         (response, bytes(response_image)),
         (0x2000230c, bytes(4)), (0x20007554, bytes(4))],
    )


def _app_67248_case(index, record_present, release_enabled, active=True):
    owner = emu.SCRATCH + 0x1000
    context = emu.SCRATCH + 0x2000
    owner_bytes = bytearray(8)
    owner_bytes[0:4] = context.to_bytes(4, "little")
    owner_bytes[4] = index
    context_bytes = bytearray(0x600)
    for offset, value in ((0x508, 0x11111111), (0x50c, 0x22222222),
                          (0x510, 0x33333333), (0x514, 0x44444444),
                          (0x56c, 0x55555555)):
        context_bytes[offset:offset + 4] = value.to_bytes(4, "little")
    table = bytearray(0x100)
    entry = index * 0x24
    table[entry:entry + 4] = int(record_present).to_bytes(4, "little")
    table[entry + 0x1c] = int(active)
    table[entry + 0x1e] = 0 if release_enabled else 1
    table[entry + 0x20:entry + 0x24] = (0x66666666).to_bytes(4, "little")
    return ({0: owner, 1: 0x22222222, 2: 0x33333333, 3: 0x44444444},
            [(owner, bytes(owner_bytes)), (context, bytes(context_bytes)),
             (0x2000b384, bytes(table))])


def _net_controller_assert_case(module_id, line, callback=True):
    """One bounded internal-controller fault dispatch and reset request."""
    callback_address = 0x01040001 if callback else 0
    return (
        {0: module_id, 1: line, 2: 0x22222222, 3: 0x33333333},
        [(0x21000a58, callback_address.to_bytes(4, "little")),
         # Nonzero PRIGROUP proves the AIRCR read/mask/or reset write rather
         # than accepting a candidate that merely stores SYSRESETREQ.
         (0xe000ed0c, (0x00000300).to_bytes(4, "little"))],
    )


REVIEWED_STATE_CASES = {
    # The callback-null arm plus zero, ordinary, byte-boundary, and full-width
    # compact module ids.  Values >= 256 intentionally prove the shipped
    # low-byte remainder behavior instead of silently replacing it with an
    # ordinary decimal formatter.  Every callback case also preserves r1 as
    # the exact source-line argument.
    ("net", 0x01008d00): [
        _net_controller_assert_case(42, 0x4444, callback=False),
        _net_controller_assert_case(0, 0x1000),
        _net_controller_assert_case(3, 0x1001),
        _net_controller_assert_case(255, 0x1002),
        _net_controller_assert_case(256, 0x1003),
        _net_controller_assert_case(0xffffffff, 0x1004),
    ],
    # Production command families for the large master dispatcher.  Keep all
    # payloads bounded and logging disabled: these cover the firmware-load
    # length rejection, unchanged-mode acknowledgement, invalid audio mode,
    # status query, display flag dispatch, timestamp forwarding, and the
    # disabled device-status notification without depending on random bytes.
    ("app", 0x0002af4c): [
        _audio_fw_master_case(0x01, b"\x0b\x02"),
        _audio_fw_master_case(0x03, b"\x09\x00"),
        _audio_fw_master_case(0x29),
        _audio_fw_master_case(0x4a, b"\x00"),
        _audio_fw_master_case(0x4c, b"\x11\x22\x33\x44"),
        _audio_fw_master_case(0x25, b"\x00\x00\x00\x00\x01"),
        _audio_fw_master_case(0x00, b"\x00\x00\x00\x00\x00\x00\x00\x00" +
                              (18).to_bytes(4, "little"), request_kind=3),
    ],
    # Positive, zero, and negative exponent/scale deltas with valid operand
    # objects.  The converter's two scale outputs are supplied by the exact
    # target-bound producer contract above.
    ("app", 0x000875e4): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000},
         [(emu.SCRATCH + 0x1000, bytes(0x10) + (3).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000, bytes(0x10) + (1).to_bytes(4, "little"))]),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000},
         [(emu.SCRATCH + 0x1000, bytes(0x10) + (0).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000, bytes(0x10) + (0).to_bytes(4, "little"))]),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000},
         [(emu.SCRATCH + 0x1000, bytes(0x10) + (0).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000, bytes(0x10) + (3).to_bytes(4, "little"))]),
    ],
    # The fifth AAPCS word owns the callback record. Exercise both the direct
    # four-argument tail and the installed three-argument callback path with
    # a mapped production-shaped record.
    ("app", 0x00082e04): [
        ({0: 0x11, 1: 0, 2: 0x22, 3: 0x33},
         [(emu.STACK_TOP, (emu.SCRATCH + 0x1000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1000, (0x00080001).to_bytes(4, "little"))]),
        ({0: 0x11, 1: 1, 2: 0x22, 3: 0x33},
         [(emu.STACK_TOP, (emu.SCRATCH + 0x1000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1000, (0x00080001).to_bytes(4, "little"))]),
    ],
    # Atomic exchange values zero/nonzero plus distinct caller words.  There
    # are no argument-derived branches, so random fuzzing alone gave no
    # explicit production coverage accounting for this straight-line wrapper.
    ("app", 0x00083204): [
        ({0: emu.SCRATCH + 0x1000, 1: 0x11, 2: 0x22, 3: 0x33},
         [(emu.SCRATCH + 0x1000, bytes(0x220))]),
        ({0: emu.SCRATCH + 0x1000, 1: 0x44, 2: 0x55, 3: 0x66},
         [(emu.SCRATCH + 0x1000,
           (0x12345678).to_bytes(4, "little") +
           (0x89abcdef).to_bytes(4, "little") + b"\x7f" + bytes(0x217))]),
    ],
    # Existing/absent runtime records, release enabled/suppressed, and the
    # index-zero/index-nonzero cleanup suffixes.  These data-owned selectors
    # are invisible to argument-only CFG derivation.
    ("app", 0x00067248): [
        _app_67248_case(1, True, True),
        _app_67248_case(1, False, True),
        _app_67248_case(1, False, False),
        _app_67248_case(0, False, True),
    ],
    # Null owner, absent implementation, and a concrete installed callback.
    ("app", 0x000681cc): [
        ({0: 0}, []),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(8))]),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (emu.SCRATCH + 0x2000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000,
           bytes(0x0c) + (0x00080001).to_bytes(4, "little"))]),
    ],
    # Validate both required objects, reject an already-active owner, and
    # cover null/disabled/enabled optional callback records passed in r4's
    # fifth AAPCS stack slot.
    ("app", 0x000730e8): [
        _connection_init_case(0, emu.SCRATCH + 0x2000, 0),
        _connection_init_case(emu.SCRATCH + 0x1000, 0, 0),
        _connection_init_case(emu.SCRATCH + 0x1000,
                              emu.SCRATCH + 0x2000, 0, active_flags=1),
        _connection_init_case(emu.SCRATCH + 0x1000,
                              emu.SCRATCH + 0x2000, 0),
        _connection_init_case(emu.SCRATCH + 0x1000,
                              emu.SCRATCH + 0x2000,
                              emu.SCRATCH + 0x3000),
        _connection_init_case(emu.SCRATCH + 0x1000,
                              emu.SCRATCH + 0x2000,
                              emu.SCRATCH + 0x3000, 1, 0x00080001),
    ],
    # Both valid register boundaries, disabled permission, out-of-range pin,
    # and the optional diagnostic path over complete pointer state.
    ("app", 0x00061c40): [
        _app_61c40_case(0, True),
        _app_61c40_case(15, True, diagnostic=True),
        _app_61c40_case(0, False),
        _app_61c40_case(16, True),
    ],
    # Cover both increment arms and the exact equality boundary that selects
    # the tail continuation. Full-width random RAM almost never makes the two
    # adjacent counters equal.
    ("app", 0x0005505c): [
        _app_5505c_case(0, 3),
        _app_5505c_case(2, 3),
        _app_5505c_case(3, 3),
        _app_5505c_case(4, 3),
    ],
    # Every supported rate must publish its exact hardware encoding. One
    # enabled-radio case exercises all five five-argument channel updates;
    # the invalid rate reaches the exact fatal diagnostic prefix.
    ("app", 0x00066ec0): [
        *[_app_66ec0_case(rate) for rate in
          (0x1e8480, 0x7a120, 0x1e848, 0x3d090, 0xf4240,
           0xf42400, 0x3d0900, 0x7a1200, 0x1e84800)],
        _app_66ec0_case(0x1e8480, radio_disabled=0),
        _app_66ec0_case(12345),
    ],
    # The inline TBB table dispatches on argument zero while the generic
    # selector pass sees only the independent index bound in argument one.
    # Exercise every distinct table base, both default selector classes, the
    # final valid table index, and the out-of-range return explicitly.
    ("app", 0x000456fc): [
        _app_456fc_case(selector, index)
        for selector in (1, 2, 3, 4, 5, 6, 7, 14, 15)
        for index in (0, 65)
    ] + [({0: 1, 1: 66}, [])],
    # Empty input plus one bounded iteration for every recognized mode.  The
    # active/inactive nested fields cover immediate completion and callback
    # insertion; mode three reaches the default diagnostic, and param4=1
    # independently covers the callback-suppression gate.
    ("net", 0x010384a8): [
        _net_record_array_case(count=0),
        _net_record_array_case(mode=0),
        *[_net_record_array_case(mode=mode, active=True)
          for mode in (1, 2, 4, 8)],
        *[_net_record_array_case(mode=mode, active=False)
          for mode in (1, 2, 4, 8)],
        _net_record_array_case(mode=3),
        _net_record_array_case(mode=1, active=False, param4=1),
    ],
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

# Exact resource/query outcomes for the operation-record builder.  Its major
# selectors are external return values rather than entry arguments, so build
# each call ordinal from the production path instead of relying on fuzzing.
def _app_55734_case(*, configured=0, flags=0, kind=0, argument5=0,
                    lookup_status=4, validate=1, present=1,
                    field_status=0, parser=0, allocation=None,
                    registration=0, postprocess=0, attachment=None,
                    enable=0):
    output = emu.SCRATCH + 0x3000
    owner = emu.SCRATCH + 0x1000
    resource = emu.SCRATCH + 0x2000
    allocated = (emu.SCRATCH + 0x4000 if allocation is None else allocation)
    owner_bytes = bytearray(0x20)
    owner_bytes[0x10:0x14] = int(configured).to_bytes(4, "little")
    resource_bytes = bytearray(0x20)
    resource_bytes[0] = 7
    resource_bytes[4:8] = int(flags).to_bytes(4, "little")
    resource_bytes[8:10] = (0x1234).to_bytes(2, "little")
    resource_bytes[0x0c:0x0e] = (0x5678).to_bytes(2, "little")
    resource_bytes[0x10:0x14] = (0x10203040).to_bytes(4, "little")
    args = {0: output, 1: owner, 2: 0x22, 3: 0x33,
            4: argument5, 5: 0x44}
    memory = [(owner, bytes(owner_bytes)), (resource, bytes(resource_bytes)),
              (output, bytes(0x80))]
    oracles = {0: {0: lookup_status, 1: resource}}
    if (lookup_status & 4) == 0:
        return args, memory, oracles
    oracles[1] = {0: validate}
    if validate == 0:
        return args, memory, oracles
    oracles[2] = {0: present}
    if present == 0:
        return args, memory, oracles
    oracles[3] = {0: field_status}
    if field_status & 0x80:
        return args, memory, oracles
    oracles[4] = {0: 0x5a}
    oracles[6] = {0: parser}
    if parser != 0:
        return args, memory, oracles

    ordinal = 8  # timestamp is ordinal seven on both configuration arms
    oracles[ordinal] = {0: kind}
    ordinal += 1
    if configured and (flags & 1):
        ordinal += 1  # timestamp copied into operation_record.details[1]
    oracles[ordinal] = {0: allocated}
    if allocated == 0:
        return args, memory, oracles
    ordinal += 2  # record copy, then registration
    oracles[ordinal] = {0: registration}
    if registration != 0:
        return args, memory, oracles
    ordinal += 1
    if not configured:
        oracles[ordinal] = {0: postprocess}
        if postprocess != 0:
            return args, memory, oracles
        ordinal += 1
    if flags & 1:
        attachment = 0 if attachment is None else attachment
        oracles[ordinal] = {0: attachment}
        ordinal += 1
        if attachment != 0:
            if attachment != 0xfffffff4 or configured or (flags & 2):
                return args, memory, oracles
            return args, memory, oracles
    oracles[ordinal] = {0: enable}
    return args, memory, oracles

# Query-return cases for a packetizer whose loop bound is returned by its
# second callee. These cover allocation failure, empty data, exact and partial
# chunks without treating an arbitrary 32-bit oracle value as a buffer length.
ORACLE_STATE_CASES = {
    # The shipped decoder returns its destination pointer in the still-live
    # r0 register even though the source-level contract is void.  Pin that
    # residual register to the exact paired local block instead of allowing a
    # random scalar oracle to manufacture an invalid input pointer.
    ("app", 0x00049acc): [
        {0: {0: emu.STACK_TOP - 296}},
    ],
    ("app", 0x00019c44): [
        {0: {0: 0}},  # receive succeeds and copies 200 bytes
        {0: {0: 1}},  # receive fails and returns without copying
    ],
    # Initial read error, downstream write success, and downstream write
    # failure cover all three production outcomes.  Both branch selectors are
    # callee results, so argument-directed CFG cases cannot reach them.
    ("app", 0x00055c64): [
        {0: {0: 1}},
        {0: {0: 0}, 1: {0: 1}},
        {0: {0: 0}, 1: {0: 0}},
    ],
    # Transfer failure, zero success, and positive success drive both sides of
    # the callee-return sign test and the exact success delay.
    ("app", 0x0008397e): [
        {0: {0: 0xffffffff}},
        {0: {0: 0}},
        {0: {0: 1}},
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
                  frame=0, saved=0xffffffff, initialized=0, rendered=0,
                  hide_progress=1, sparse_pixels=False):
    app = emu.SCRATCH + 0x1000
    ctx = emu.SCRATCH + 0x4000
    row = emu.SCRATCH + 0x6000
    # The first accessor returns the absolute UI/application state object
    # whose fields drive this reviewed case.  Keep the pointer explicit so
    # importing the verifier cannot fall through to an undefined fixture.
    oracles = {0: {0: app}, 1: {0: 1}}
    if active == 0 and phase == 1 and not initialized and status == 0:
        # Common setup owns ordinals 0..9.  Each complete frame then calls
        # four metric getters, draws, obtains both framebuffer owners, and
        # publishes.  Pin only the two pointer-producing getters per frame.
        for frame_index in range(8):
            base = 10 + frame_index * 8
            for ordinal in range(base, base + 4):
                oracles[ordinal] = {0: 0}
            oracles[base + 5] = {0: app}
            oracles[base + 6] = {0: app}
    elif active == 0 and phase == 1 and not initialized and status == 14:
        oracles[9] = {0: app}
        oracles[10] = {0: app}
    elif active == 1 and phase == 1 and status == 7 and substate == 3:
        for frame_index in range(8):
            base = 8 + frame_index * 9
            for ordinal in range(base + 1, base + 5):
                oracles[ordinal] = {0: 0}
            oracles[base + 6] = {0: app}
            oracles[base + 7] = {0: app}
    elif active == 1 and phase == 1 and substate == 4:
        # A changing live layout may legitimately collapse either wipe pass.
        # Make each outer bound empty (initial top=200, live top=0), then run
        # all eight bounded text-region masks with stable zero coordinates.
        oracles.update({7: {0: app}, 8: {0: 200}, 9: {0: 0},
                        10: {0: app}, 11: {0: app},
                        12: {0: 0}, 13: {0: 0}, 14: {0: 0}, 15: {0: 0},
                        17: {0: 200}, 18: {0: 0},
                        19: {0: app}, 20: {0: app},
                        21: {0: 0}, 22: {0: 0}, 23: {0: 0}, 24: {0: 0}})
        # status 7 reaches the generic copied-text render at ordinals 29..34.
        for ordinal in range(30, 34):
            oracles[ordinal] = {0: 0}
        for frame_index in range(8):
            base = 35 + frame_index * 7
            for ordinal in range(base, base + 4):
                oracles[ordinal] = {0: 0}
            oracles[base + 4] = {0: app}
            oracles[base + 5] = {0: app}
        # Final canvas-flag publication remains live as r1 at the following
        # one-formal icon call; pin it rather than comparing target-seeded
        # random oracle returns from differently linked candidates.
        oracles[91] = {0: 0}
    elif active == 1 and phase == 1 and status == 14:
        oracles[7] = {0: app}
        oracles[8] = {0: app}
    state = bytearray(0x1000)
    state[0xef] = status
    state[0xf0] = substate
    state[0xf3] = 2
    state[0xf4] = hide_progress
    state[0xf5] = 3
    state[0xf6:0xf9] = b"AI!"
    state[0x286:0x288] = (3).to_bytes(2, "little")
    canvas = bytearray(0x1000)
    for y in range(199):
        canvas[0x24 + y * 4:0x28 + y * 4] = row.to_bytes(4, "little")
        state[0xb90 + y * 4:0xb94 + y * 4] = row.to_bytes(4, "little")
    state[0xeb4:0xeb8] = (emu.SCRATCH + 0x7000).to_bytes(4, "little")
    state[0xeb8:0xebc] = (emu.SCRATCH + 0x7100).to_bytes(4, "little")
    return (
        {0: ctx, 1: 0, 2: phase},
        [(app, bytes(state)), (ctx, bytes(canvas)),
         (row, (b"\xff" if sparse_pixels else b"\0") + bytes(0x13f)),
         (emu.SCRATCH + 0x7000, bytes(0x200)),
         (0x2000230c, level.to_bytes(4, "little", signed=True)),
         (0x20007554, sink.to_bytes(4, "little")),
         (0x20009fd8, frame.to_bytes(4, "little")),
         (0x20009fd4, rendered.to_bytes(4, "little")),
         (0x200024ec, saved.to_bytes(4, "little")),
         (0x20007b3c, bytes(0x40)),
         (0x2000a038, bytes(0x20)),
         (0x2001b818, bytes(0x200)),
         # The active bytes live inside the line-buffer allocation above and
         # therefore must be applied after its deterministic zero fixture.
         (0x2001b9a8, bytes((active, initialized)))],
        oracles,
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
    glyph_bytes = bytes((0xa5, 0x5a, 0x3c, 0xc3)) + bytes(60)
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


def _net_serializer_single_index_case():
    """One real descriptor reaching the net serializer's local index byte.

    Bits 0 and 1 enable deferred-index and encoded-pair processing.  The
    descriptor owns one deferred index followed by one pair; both select the
    same valid string pointer.  This reaches the callback at 0x0102c3dc with
    the one-byte local object, while also consuming both accumulation arrays.
    """
    data = _serializer_header(_SERIALIZER_STRING, deferred=1, records=1)
    data[8] = 1
    data[9:11] = bytes((0x33, 1))
    oracles = {0: {0: 0}}
    for ordinal in range(1, 9):
        oracles[ordinal] = {0: 1}
    return (
        {0: _SERIALIZER_INPUT, 1: len(data),
         2: _SERIALIZER_CALLBACK, 3: 0x13579bdf},
        [(_SERIALIZER_INPUT, bytes(data) + bytes(16)),
         (_SERIALIZER_STRING, b"production-string\0"),
         *_serializer_stack_args(3)],
        oracles,
    )


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


def _app_62d9c_case(kind):
    """Coherent device, state, and register blocks for initialization paths."""
    owner = emu.SCRATCH + 0x1000
    device = emu.SCRATCH + 0x1100
    state = emu.SCRATCH + 0x1200
    registers = emu.SCRATCH + 0x2000
    linked = emu.SCRATCH + 0x3000
    owner_data = bytearray(0x14)
    owner_data[4:8] = device.to_bytes(4, "little")
    owner_data[0x10:0x14] = state.to_bytes(4, "little")
    device_data = bytearray(0x10)
    device_data[0:4] = registers.to_bytes(4, "little")
    flags = 2 if kind in ("feature-invalid", "feature-valid") else 0
    if kind == "bit-four":
        flags = 0x10
    device_data[4:8] = flags.to_bytes(4, "little")
    device_data[8] = 0
    device_data[0x0c:0x10] = (0x44556677).to_bytes(4, "little")
    state_data = bytearray(0x20)
    state_data[0x14:0x18] = (0x11223344).to_bytes(4, "little")
    state_data[0x18:0x1c] = (0x55667788).to_bytes(4, "little")
    state_data[0x1c] = 3
    if kind == "linked":
        state_data[0x0c:0x10] = linked.to_bytes(4, "little")
    memory = [(owner, bytes(owner_data)), (device, bytes(device_data)),
              (state, bytes(state_data)), (registers, bytes(0x550)),
              (linked, bytes(0x100))]
    oracles = {2: {0: 0}, 3: {0: 0}}
    if kind == "toggle-error":
        oracles[2] = {0: 0xfffffffd}
    elif kind == "setup-error":
        oracles[3] = {0: 7}
    elif kind == "feature-invalid":
        oracles[4] = {0: 0}
    elif kind == "feature-valid":
        oracles[4] = {0: 0x0bad0000}
    return ({0: owner}, memory, oracles)


def _app_620cc_case(kind):
    """Five-slot pin configuration with at most one active controller."""
    owner = emu.SCRATCH + 0x1000
    slots = emu.SCRATCH + 0x1100
    controller = emu.SCRATCH + 0x2000
    valid_mask = emu.SCRATCH + 0x2100
    callback_slot = emu.SCRATCH + 0x2200
    output = emu.SCRATCH + 0x2300
    owner_data = bytearray(8)
    owner_data[4:8] = slots.to_bytes(4, "little")
    slot_data = bytearray(0x28)
    memory = [(owner, bytes(owner_data)), (slots, bytes(slot_data))]
    if kind == "empty":
        return ({0: owner}, memory, {})
    slot_data[4:8] = controller.to_bytes(4, "little")
    slot_data[8] = 3
    slot_data[10:12] = (1 if kind != "clear" else 0).to_bytes(2, "little")
    controller_data = bytearray(0x14)
    controller_data[4:8] = valid_mask.to_bytes(4, "little")
    controller_data[8:12] = callback_slot.to_bytes(4, "little")
    controller_data[0x10:0x14] = output.to_bytes(4, "little")
    memory = [
        (owner, bytes(owner_data)), (slots, bytes(slot_data)),
        (controller, bytes(controller_data)),
        (valid_mask, (1 << 3).to_bytes(4, "little")),
        (callback_slot, (0x00080001).to_bytes(4, "little")),
        (output, (0x55).to_bytes(4, "little")),
    ]
    oracles = {0: {0: int(kind != "not-ready")}}
    if kind not in ("not-ready",):
        oracles[1] = {0: (7 if kind == "callback-error" else 0)}
    return ({0: owner}, memory, oracles)


def _app_62f28_case(kind):
    """Bounded lock acquisition fixtures for both scheduler modes."""
    owner = emu.SCRATCH + 0x1000
    lock = emu.SCRATCH + 0x1100
    state = emu.SCRATCH + 0x1200
    destination = emu.SCRATCH + 0x1300
    nested = emu.SCRATCH + 0x1400
    lock_data = bytearray(0x550)
    lock_data[0x54c:0x550] = (0x12345678).to_bytes(4, "little")
    owner_data = bytearray(0x14)
    owner_data[4:8] = lock.to_bytes(4, "little")
    owner_data[0x10:0x14] = state.to_bytes(4, "little")
    state_data = bytearray(0x18)
    state_data[0x14:0x18] = destination.to_bytes(4, "little")
    memory = [(owner, bytes(owner_data)), (lock, bytes(lock_data)),
              (state, bytes(state_data)), (destination, b"\0"),
              (nested, bytes(0xc0)), (0x2001d564, b"\x01")]
    if kind == "fast":
        oracles = {0: {0: 1}, 1: {0: 1}}
    elif kind == "fast-nested":
        state_data[0x0c:0x10] = nested.to_bytes(4, "little")
        nested_data = bytearray(0xc0)
        nested_data[0x0c:0x10] = (1).to_bytes(4, "little")
        nested_data[0xbc:0xc0] = (0xffffffff).to_bytes(4, "little")
        memory[2] = (state, bytes(state_data))
        memory[4] = (nested, bytes(nested_data))
        oracles = {0: {0: 1}, 1: {0: 1}}
    elif kind == "slow":
        oracles = {0: {0: 0}, 1: {0: 1}, 2: {0: 1}}
    elif kind == "slow-retry":
        oracles = {0: {0: 0}, 1: {0: 0}, 3: {0: 1}, 4: {0: 1}}
    else:
        raise ValueError(kind)
    return ({0: owner, 1: 0x5a}, memory, oracles)


def _app_54528_case(kind):
    """Coherent connection-event fixtures for every recovered outcome."""
    event = emu.SCRATCH + 0x1000
    payload = emu.SCRATCH + 0x1100
    packet = emu.SCRATCH + 0x2000
    descriptor = bytearray(16)
    descriptor[12:16] = payload.to_bytes(4, "little")
    fields = bytes.fromhex("34127856bc9af0de5713")
    memory = [(event, bytes(descriptor)), (payload, fields),
              (packet, bytes(16))]
    if kind == "missing":
        oracles = {0: {0: 0}}
    elif kind == "invalid":
        oracles = {0: {0: 0x1234}, 1: {0: 0}}
    elif kind == "allocation-failure":
        oracles = {0: {0: 0x1234}, 1: {0: 1}, 2: {0: 0}}
    else:
        oracles = {0: {0: 0x1234}, 1: {0: 1},
                   2: {0: packet}, 3: {0: emu.SCRATCH + 0x2100}}
        memory.append((emu.SCRATCH + 0x2100, bytes(14)))
    return ({0: event}, memory, oracles)


def _app_54d18_case(kind):
    """Bounded table-update, rebuild-loop, and early-error fixtures."""
    args = {0: 3, 1: 0, 2: 0x55667788}
    if kind == "direct":
        args[1] = 0x1234
        return (args, [], {0: {0: 0}, 2: {0: 0}})
    if kind == "direct-flush":
        args[1] = 0x1234
        return (args, [], {0: {0: 0}, 2: {0: 4}})
    if kind == "early-error":
        return (args, [], {0: {0: 0xfffffff9}})
    if kind == "one-retry":
        return (args, [], {0: {0: 0}, 1: {0: 0}, 2: {0: 0},
                           3: {0: 0xffffffff}, 5: {0: 4}})
    raise ValueError(kind)


def _app_scanline_case(enabled, callback_status=0, buffered=False):
    """One coherent display-context fixture for the 0x47260/0x473c8 pair."""
    context = emu.SCRATCH + 0x1000
    owner = emu.SCRATCH + 0x2000
    framebuffer = emu.SCRATCH + 0x3000
    state = bytearray(0x378)
    state[0x344:0x348] = framebuffer.to_bytes(4, "little")
    state[0x35c:0x360] = int(enabled).to_bytes(4, "little")
    state[0x374:0x378] = owner.to_bytes(4, "little")
    memory = [
        (context, bytes(state)),
        (owner, bytes(8) + (0x00080001).to_bytes(4, "little")),
        (framebuffer, bytes((i * 29 + 7) & 0xff for i in range(0x20))),
        (0x2000230c, (1).to_bytes(4, "little")),
        (0x20007554, int(buffered).to_bytes(4, "little")),
    ]
    # r0/r1/r2/r3 choose a one-row, in-bounds update.  On the disabled path
    # only the first accessor result is consumed.  On the active path the
    # callback is ordinal two, after lock acquisition.
    oracles = {0: {0: context}}
    if enabled:
        oracles[2] = {0: int(callback_status)}
    return ({0: 2, 1: 3, 2: 10, 3: 0}, memory, oracles)


def _app_glyph_case(kind):
    """Bounded storage-callback fixtures for FUN_0004792c."""
    context = emu.SCRATCH + 0x1000
    state = bytearray(0x1034)
    if kind != "absent":
        state[0x1030:0x1034] = (0x00080001).to_bytes(4, "little")
    memory = [
        (context, bytes(state)),
        (0x2000230c, (1).to_bytes(4, "little")),
        (0x20007554, bytes(4)),
    ]
    if kind == "ascii":
        return ({0: 0x41, 1: 4, 2: 4}, [], {})
    oracles = {0: {0: context}}
    if kind == "absent":
        return ({0: 0x100, 1: 4, 2: 4}, memory, oracles)
    oracles.update({1: {0: context}, 2: {0: context}})
    if kind == "query-error":
        oracles[3] = {0: 1}
    else:
        oracles.update({3: {0: 0}, 6: {0: context}, 7: {0: context},
                        8: {0: int(kind == "read-error")}})
    return ({0: 0x100, 1: 4, 2: 4}, memory, oracles)


def _app_4a5b0_case(active_match):
    """A coherent valid calendar plus the complete seven-slot date state."""
    state_address = emu.SCRATCH + 0x5000
    state = bytearray(0x1200)
    if active_match:
        state[0x10de:0x10e0] = (2025).to_bytes(2, "little")
        state[0x10e0] = 12
        state[0x10e1] = 31
    oracles = {0: {0: 0x12345678}}
    oracles.update({ordinal: {0: state_address} for ordinal in range(2, 64)})
    return ({}, [(state_address, bytes(state))], oracles)


def _unlink_record_case(queued, current):
    record = emu.SCRATCH + 0x1000
    record_bytes = bytearray(0x100)
    record_bytes[0x0d] = 0x80 if queued else 0
    current_value = record if current else emu.SCRATCH + 0x2000
    return (
        {0: record},
        [(record, bytes(record_bytes)),
         (0x2000b450, int(current_value).to_bytes(4, "little"))],
        {1: {0: 1}, 3: {0: 1}, 4: {0: 1}},
    )


def _pairing_mode_case(mode):
    """Production-shaped connection, address, and allocated pairing record."""
    connection = emu.SCRATCH + 0x2000
    pairing = emu.SCRATCH + 0x3000
    owner = emu.SCRATCH + 0x1000
    connection_bytes = bytearray(0x100)
    connection_bytes[8] = mode
    connection_bytes[0x0d] = 2
    connection_bytes[0x14] = 5
    for offset in range(0x47, 0x57):
        connection_bytes[offset] = (offset * 3 + mode) & 0xff
    owner_bytes = bytearray(0x200)
    return (
        {0: owner},
        [(owner, bytes(owner_bytes)),
         (connection, bytes(connection_bytes)),
         (pairing, bytes(0x100))],
        {0: {0: connection}, 1: {0: 1}, 2: {0: pairing},
         3: {0: 1}, 4: {0: 1}, 5: {0: 1}},
    )


def _writer_init_case(writer, device, buffer, capacity, base, limit,
                      available):
    """Coherent seven-argument initializer fixture and geometry result."""
    absolute = [
        (emu.SCRATCH + 0x1000, bytes(0x100)),
        (emu.SCRATCH + 0x2000, bytes(0x100)),
        (emu.SCRATCH + 0x3000, bytes(0x100)),
        (emu.STACK_TOP + 0, int(base).to_bytes(4, "little")),
        (emu.STACK_TOP + 4, int(limit).to_bytes(4, "little")),
        (emu.STACK_TOP + 8, (0).to_bytes(4, "little")),
    ]
    oracles = {0: {0: 4}, 2: {0: 4}}
    writes = {1: [(2, 4, int(available).to_bytes(4, "little"),
                    0x00083ac2)]}
    return ({0: writer, 1: device, 2: buffer, 3: capacity},
            absolute, oracles, writes)


def _app_55350_case(record_count, requested_count):
    controller = emu.SCRATCH + 0x1000
    payload = emu.SCRATCH + 0x1800
    output = emu.SCRATCH + 0x3000
    owner = bytearray(0x10)
    owner[0x0c:0x10] = payload.to_bytes(4, "little")
    records = bytearray(2 + 22 * record_count)
    records[1] = record_count
    for index in range(record_count):
        for byte_index in range(22):
            records[2 + 22 * index + byte_index] = \
                (0x31 + index * 37 + byte_index * 5) & 0xff
    return (
        {0: output, 1: requested_count},
        [(0x200020c2, b"\x01"), (controller, bytes(owner)),
         (payload, bytes(records)), (output, bytes(66))],
        {0: {0: 0}},
        {0: [(2, 0, controller.to_bytes(4, "little"), 0x00053d70)]},
    )


def _app_55454_case(flags, mode, table_state=0, global_state=0,
                    oracle_result=None):
    request = emu.SCRATCH + 0x1000
    output = emu.SCRATCH + 0x1800
    table = bytearray(0xe0)
    table[2 * 7] = table_state
    table[0xd8] = global_state
    oracles = {} if oracle_result is None else {0: {0: oracle_result}}
    return (
        {0: request, 1: flags, 2: mode, 3: output},
        [(request, b"\x02"), (output, b"\xaa"),
         (0x20002000, bytes(table))],
        oracles,
    )


def _app_6567c_case(kind):
    parameters = emu.SCRATCH + 0x1000
    nested = emu.SCRATCH + 0x1100
    pair = emu.SCRATCH + 0x1200
    args = {0: 3, 1: 4, 2: 0, 3: 0}
    memory = [(0x20002bc0, bytes(0x80)),
              (0x5000d510, bytes(16))]
    if kind == "no-channel":
        return (args, memory, {0: {0: 2, 1: 0}})
    if kind == "invalid-channel":
        return (args, memory, {0: {0: 2, 1: 1}, 1: {0: 7}})
    if kind == "configure":
        return (args, memory, {0: {0: 2, 1: 1}, 1: {0: 0}})
    if kind in ("parameter", "parameter-error"):
        parameter_data = bytearray(8)
        parameter_data[0] = 1
        parameter_data[4:8] = nested.to_bytes(4, "little")
        args[2] = parameters
        memory += [(parameters, bytes(parameter_data)), (nested, b"\x02")]
        result = 0 if kind == "parameter" else 5
        return (args, memory,
                {0: {0: 2, 1: 0}, 1: {0: result, 1: 1}})
    pair_data = (0x11223344).to_bytes(4, "little") + \
                (0x55667788).to_bytes(4, "little")
    args[3] = pair
    memory[0] = (0x20002bc0, pair_data + bytes(0x78))
    memory.append((pair, pair_data))
    return (args, memory, {0: {0: 2, 1: 0}})


def _app_65b18_case(kind):
    args = {0: 0, 1: 7}
    memory = [(0x20002bc0, bytes(0x80)), (0x5000d510, bytes(4))]
    if kind == "inactive":
        return (args, memory, {0: {0: 0}})
    if kind == "active":
        return (args, memory,
                {0: {0: 1}, 2: {0: 0}, 4: {0: 2},
                 5: {0: 0x5000d310}})
    return (args, memory,
            {0: {0: 1}, 2: {0: 1}, 3: {0: 0}, 5: {0: 2},
             6: {0: 0x5000d310}})


def _app_83cfc_case(mode, setup_result=0):
    owner = emu.SCRATCH + 0x1000
    context = emu.SCRATCH + 0x1800
    context_data = bytearray(0x24)
    context_data[0x20:0x24] = (0x11223344).to_bytes(4, "little")
    owner_data = bytearray(8)
    owner_data[4:8] = context.to_bytes(4, "little")
    oracles = {}
    if mode == 0:
        oracles = {1: {0: setup_result}}
    elif mode == 1:
        oracles = {0: {0: setup_result}}
    return ({0: owner, 1: mode, 2: 0x55667788, 3: 0x99aabbcc},
            [(owner, bytes(owner_data)), (context, bytes(context_data))],
            oracles)


def _app_83e70_case(value, send_result=1):
    owner = emu.SCRATCH + 0x1000
    transport = emu.SCRATCH + 0x1800
    owner_data = bytearray(8)
    owner_data[4:8] = transport.to_bytes(4, "little")
    return ({0: owner, 1: value},
            [(owner, bytes(owner_data)), (transport, bytes(0x20))],
            ({0: {0: send_result}} if value < 0x10000000 else {}))


def _app_83ede_case(kind, channel=3, flags=0, submode=0):
    records = emu.SCRATCH + 0x1000
    device = emu.SCRATCH + 0x1800
    channel_table = emu.SCRATCH + 0x2200
    word = ((kind & 0xffff) << 16) | (channel & 0x7f) | \
           ((submode & 0xf) << 9) | flags
    return (
        {0: records, 1: 1, 2: device},
        [(records, word.to_bytes(4, "little")),
         (device, bytes(0x600)), (channel_table, bytes(0x400))],
        {0: {0: channel_table}, 1: {0: channel_table},
         2: {0: channel_table}},
    )


def _app_840cc_case(value, minimum=-0x80000000, maximum=0x7fffffff,
                     initial=-0x80000000, precheck=0xff, activation=0,
                     validate_callback=False, activate_callback=False,
                     oracle_results=()):
    owner = emu.SCRATCH + 0x1000
    limits = emu.SCRATCH + 0x1800
    operations = emu.SCRATCH + 0x2000
    statistics = emu.SCRATCH + 0x2800
    owner_data = bytearray(0x14)
    owner_data[4:8] = limits.to_bytes(4, "little")
    owner_data[8:12] = operations.to_bytes(4, "little")
    owner_data[0x10:0x14] = statistics.to_bytes(4, "little")
    limits_data = bytearray(0x1c)
    limits_data[0:4] = (minimum & 0xffffffff).to_bytes(4, "little")
    limits_data[4:8] = (maximum & 0xffffffff).to_bytes(4, "little")
    limits_data[8:12] = (initial & 0xffffffff).to_bytes(4, "little")
    limits_data[0x19] = precheck
    limits_data[0x1a] = activation
    operations_data = bytearray(0x18)
    if activate_callback:
        operations_data[0:4] = (0x00080005).to_bytes(4, "little")
    if validate_callback:
        operations_data[0x14:0x18] = (0x00080001).to_bytes(4, "little")
    oracles = {index: {0: result & 0xffffffff}
               for index, result in enumerate(oracle_results)}
    return (
        {0: owner, 1: value},
        [(owner, bytes(owner_data)), (limits, bytes(limits_data)),
         (operations, bytes(operations_data)), (statistics, bytes(0x20))],
        oracles,
    )


def _app_enqueue_ancs_case(initialized=True, full=False, enqueue_result=0,
                            log_level=0, deferred_logger=0):
    payload = emu.SCRATCH + 0x1000
    queue = bytearray(0x30)
    queue[0x10:0x14] = int(initialized).to_bytes(4, "little")
    queue[0x24:0x28] = (10 if full else 0).to_bytes(4, "little")
    memory = [(payload, bytes((index * 7 + 3) & 0xff for index in range(436))),
              (0x20006a6c, bytes(queue)),
              (0x2000230c, log_level.to_bytes(4, "little")),
              (0x20007554, deferred_logger.to_bytes(4, "little"))]
    if not initialized:
        return ({0: payload}, memory, {},
                {0: [(0, 0, bytes(436), 0x00086c78)]})
    copy_ordinal = 3 if full else 1
    enqueue_ordinal = copy_ordinal + 1
    oracles = {enqueue_ordinal: {0: enqueue_result}}
    writes = {
        0: [(0, 0, bytes(436), 0x00086c78)],
        copy_ordinal: [(0, 0, memory[0][1], 0x00086c04)],
    }
    return ({0: payload}, memory, oracles, writes)


def _app_enqueue_dmic_case(full=False, enqueue_result=0, log_level=0,
                            deferred_logger=0):
    payload = emu.SCRATCH + 0x1000
    queue = bytearray(0x30)
    queue[0x24:0x28] = (8 if full else 0).to_bytes(4, "little")
    payload_bytes = bytes((index * 11 + 5) & 0xff for index in range(200))
    memory = [(payload, payload_bytes), (0x20007b7c, bytes(queue)),
              (0x2000230c, log_level.to_bytes(4, "little")),
              (0x20007554, deferred_logger.to_bytes(4, "little"))]
    copy_ordinal = 3 if full and log_level > 0 else 2 if full else 1
    enqueue_ordinal = copy_ordinal + 1
    return (
        {0: payload}, memory, {enqueue_ordinal: {0: enqueue_result}},
        {0: [(0, 0, bytes([0x5a]) * 200, 0x00086c04)],
         copy_ordinal: [(0, 0, payload_bytes, 0x00086c04)]},
    )


def _app_enqueue_file_case(full=False, enqueue_result=0, log_level=0,
                            deferred_logger=0):
    queue = bytearray(0x30)
    queue[0x24:0x28] = (0x1e if full else 0).to_bytes(4, "little")
    serialized = bytes((index * 13 + 9) & 0xff for index in range(200))
    memory = [(0x200079a0, bytes(queue)),
              (0x2000230c, log_level.to_bytes(4, "little")),
              (0x20007554, deferred_logger.to_bytes(4, "little"))]
    serialize_ordinal = 2 if full and log_level > 0 else 1 if full else 0
    enqueue_ordinal = serialize_ordinal + 1
    return (
        {0: 0x11223344, 1: 0x56}, memory,
        {enqueue_ordinal: {0: enqueue_result}},
        {serialize_ordinal: [(0, 0, serialized, 0x00086c1e)]},
    )


def _audio_stream_cache_case(full=False, enqueue_result=0, log_level=0,
                             deferred_logger=0):
    audio_stream = emu.SCRATCH + 0x1000
    queue = bytearray(0x30)
    queue[0x24:0x28] = (0x12 if full else 0).to_bytes(4, "little")
    payload = bytes((index * 29 + 7) & 0xff for index in range(200))
    memory = [
        (audio_stream, payload), (0x20003890, bytes(queue)),
        (0x2000230c, int(log_level).to_bytes(4, "little")),
        (0x20007554, int(deferred_logger).to_bytes(4, "little")),
    ]
    oracles = {} if full else {2: {0: int(enqueue_result)}}
    return ({0: audio_stream}, memory, oracles)


def _audio_request_case(length, active=False, opcode=0x31,
                        descriptor_type=0):
    payload = emu.SCRATCH + 0x1000
    descriptor = emu.SCRATCH + 0x1200
    context = emu.SCRATCH + 0x2000
    short_buffer = emu.SCRATCH + 0x2500
    app_state = emu.SCRATCH + 0x2800
    payload_image = bytearray((index * 37 + 11) & 0xff
                              for index in range(0x101))
    payload_image[0] = opcode
    descriptor_image = bytearray(8)
    descriptor_image[0] = descriptor_type
    descriptor_image[1:7] = b"\x01\x02\x03\x04\x05\x06"
    context_image = bytearray(0x400)
    context_image[0x248] = int(active)
    context_image[0x254:0x258] = short_buffer.to_bytes(4, "little")
    context_image[0x0c:0x10] = (0x00080001).to_bytes(4, "little")
    memory = [
        (payload, bytes(payload_image)),
        (descriptor, bytes(descriptor_image)),
        (context, bytes(context_image)),
        (short_buffer, bytes(0x20)), (app_state, bytes(0x1100)),
        (0x20006a30, context.to_bytes(4, "little")),
        (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
    ]
    oracles = {2: {0: descriptor}, 5: {0: 0x1234, 1: 0}}
    if active and opcode == 0x18:
        oracles[6] = {0: app_state}
    return ({0: 2, 1: payload, 2: length}, memory, oracles)


def _app_ext_flash_case(ready, log_level=0, deferred_logger=0):
    outputs = [emu.SCRATCH + offset for offset in (0x1000, 0x1100, 0x1200)]
    state = emu.SCRATCH + 0x2000
    memory = [(address, bytes(4)) for address in outputs]
    memory += [(state, bytes(0x1100)),
               (0x2000230c, log_level.to_bytes(4, "little")),
               (0x20007554, deferred_logger.to_bytes(4, "little")),
               (0x20007b68, bytes(4))]
    oracles = {1: {0: int(ready)}}
    if ready:
        next_ordinal = 3 if log_level > 2 else 2
        oracles[next_ordinal] = {0: 0x1234}
        oracles[next_ordinal + 1] = {0: state}
    return ({0: outputs[0], 1: outputs[1], 2: outputs[2], 3: 0xa5a5a5a5},
            memory, oracles)


def _app_language_case(ready, callback_result=0, record=b"\xaa\x07\x00\x00",
                       log_level=0, deferred_logger=0):
    state = emu.SCRATCH + 0x2000
    state_bytes = bytearray(0x1040)
    state_bytes[0x1030:0x1034] = (0x00080001).to_bytes(4, "little")
    memory = [(state, bytes(state_bytes)),
              (0x2000230c, log_level.to_bytes(4, "little")),
              (0x20007554, deferred_logger.to_bytes(4, "little")),
              (0x20018462, bytes(4))]
    initial_log = 1 if log_level > 2 else 0
    ready_ordinal = initial_log
    oracles = {ready_ordinal: {0: int(ready)}}
    writes = {}
    if ready:
        first_state = ready_ordinal + 1
        callback_ordinal = first_state + 2
        oracles[first_state] = {0: state}
        oracles[first_state + 1] = {0: state}
        oracles[callback_ordinal] = {0: callback_result}
        # The paired object has reviewed but different frame offsets.  Replay
        # the callback's out-record into both mapped locations; each machine
        # reads its own address and the other write is inert frame padding.
        writes[callback_ordinal] = [
            (None, emu.STACK_TOP - 20, record),
            (None, emu.STACK_TOP - 12, record),
        ]
    return ({0: 0x11223344, 1: 0x55000000, 2: 0x66778899},
            memory, oracles, writes)


def _hci_vs_init_case(stop):
    """Bounded command/response prefixes for the no-argument HCI initializer.

    Every successful synchronous command publishes the same production-shaped
    net_buf through r2.  Prefix cases stop at a different real failure point,
    so command order, response ownership, copied controller fields, RNG gating,
    and the mandatory controller-feature diagnostic are all executed without
    inventing an unbounded external controller implementation.
    """
    controller = bytearray(0x180)
    config = emu.SCRATCH + 0x1800
    controller[0x168:0x16c] = config.to_bytes(4, "little")
    response = emu.SCRATCH + 0x1a00
    payload_address = emu.SCRATCH + 0x1b00
    net_buf = bytearray(16)
    net_buf[0xc:0x10] = payload_address.to_bytes(4, "little")
    payload = bytearray(80)
    # Read-local-supported-features stores payload[5:9] at controller+0x7c.
    # Bit six is the production prerequisite checked before LE initialization.
    payload[5] = 0x40
    config_bytes = bytearray(12)
    config_bytes[8:12] = (1).to_bytes(4, "little")
    memory = [
        (0x20002000, bytes(controller)),
        (config, bytes(config_bytes)),
        (response, bytes(net_buf)),
        (payload_address, bytes(payload)),
    ]
    # With the optional 0x0c03 probe disabled, these are the fixed ordinals of
    # 0x1003, unref, 0x1001, unref, 0x1002, unref, RNG, 0x2003, unref,
    # 0x2002, unref, and command allocation.
    failure_ordinal = {
        "features": 0,
        "version": 2,
        "commands": 4,
        "rng": 6,
        "le_features": 7,
        "le_states": 9,
        "allocate": 11,
    }[stop]
    success_ordinals = (0, 2, 4, 6, 7, 9)
    oracles = {ordinal: {0: 0} for ordinal in success_ordinals
               if ordinal < failure_ordinal}
    oracles[failure_ordinal] = {
        0: 0 if stop == "allocate" else 0xfffffff9
    }
    writes = {}
    for ordinal in (0, 2, 4, 7, 9):
        if ordinal < failure_ordinal:
            writes[ordinal] = [
                (2, 0, response.to_bytes(4, "little"), 0x00053d70)
            ]
    return ({}, memory, oracles, writes)


REVIEWED_ORACLE_CASES = {
    ("app", 0x00012080): [
        _hci_vs_init_case("features"),
        _hci_vs_init_case("version"),
        _hci_vs_init_case("commands"),
        _hci_vs_init_case("rng"),
        _hci_vs_init_case("le_features"),
        _hci_vs_init_case("le_states"),
        _hci_vs_init_case("allocate"),
    ],
    # Bounded production families: idle short/long/max/reject handling plus
    # active forwarding and its special 0x18 acknowledgement callback.
    ("app", 0x00017f70): [
        _audio_request_case(12),
        _audio_request_case(20),
        _audio_request_case(21),
        _audio_request_case(255),
        _audio_request_case(256),
        _audio_request_case(257),
        _audio_request_case(32, active=True),
        _audio_request_case(1, active=True, opcode=0x18),
    ],
    # Full, successful, failed, and both concrete logger-routing families.
    # The nonuniform complete stream makes payload source/extent observable.
    ("app", 0x0002f6b0): [
        _audio_stream_cache_case(full=True),
        _audio_stream_cache_case(full=True, log_level=1,
                                 deferred_logger=1),
        _audio_stream_cache_case(enqueue_result=0),
        _audio_stream_cache_case(enqueue_result=5),
        _audio_stream_cache_case(enqueue_result=5, log_level=1),
    ],
    ("app", 0x00018bb4): [
        _app_enqueue_ancs_case(initialized=False),
        _app_enqueue_ancs_case(),
        _app_enqueue_ancs_case(full=True, deferred_logger=1),
        _app_enqueue_ancs_case(enqueue_result=5, log_level=1),
    ],
    ("app", 0x0002ec5c): [
        _app_enqueue_dmic_case(),
        _app_enqueue_dmic_case(full=True, log_level=1),
        _app_enqueue_dmic_case(enqueue_result=5, log_level=1,
                               deferred_logger=1),
    ],
    ("app", 0x00023514): [
        _app_enqueue_file_case(),
        _app_enqueue_file_case(full=True, log_level=1),
        _app_enqueue_file_case(enqueue_result=5, log_level=1,
                               deferred_logger=1),
    ],
    ("app", 0x0002e4e8): [
        _app_ext_flash_case(False),
        _app_ext_flash_case(False, log_level=1, deferred_logger=1),
        _app_ext_flash_case(True),
        _app_ext_flash_case(True, log_level=3),
    ],
    ("app", 0x00023d0c): [
        _app_language_case(False, log_level=1),
        _app_language_case(True, callback_result=5, log_level=1,
                           deferred_logger=1),
        _app_language_case(True, record=b"\xaa\x07\x00\x00", log_level=4),
        _app_language_case(True, record=b"\x00\x09\x00\x00"),
    ],
    ("app", 0x00083cfc): [
        _app_83cfc_case(0, 7),
        _app_83cfc_case(1, -5),
        _app_83cfc_case(1, 0),
        _app_83cfc_case(2),
    ],
    ("app", 0x00083dc8): [
        ({0: emu.SCRATCH + 0x1000, 1: 0x12, 2: 0x34, 3: 0x56},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (0x11223344).to_bytes(4, "little"))], {}),
    ],
    ("app", 0x00083e70): [
        _app_83e70_case(0x0fffffff, 1),
        _app_83e70_case(0x10000000),
        _app_83e70_case(0x10000001),
        _app_83e70_case(0x01234567, 0),
    ],
    ("app", 0x00083ede): [
        *[_app_83ede_case(kind) for kind in range(0x23)],
        _app_83ede_case(0x0b, submode=2),
        _app_83ede_case(0x16, flags=0x4000),
        _app_83ede_case(0x1d, flags=0x2000),
        _app_83ede_case(0x1f, flags=0x180),
        _app_83ede_case(0x22, channel=0x7f),
    ],
    ("app", 0x000840cc): [
        _app_840cc_case(1, precheck=0, oracle_results=(-5,)),
        _app_840cc_case(1, initial=42, oracle_results=(-6,)),
        _app_840cc_case(1),
        _app_840cc_case(50, minimum=0, maximum=100),
        _app_840cc_case(50, minimum=0, maximum=100,
                        validate_callback=True, oracle_results=(-7,)),
        _app_840cc_case(5, minimum=10, maximum=100,
                        validate_callback=True, oracle_results=(0, -8)),
        _app_840cc_case(200, minimum=0, maximum=100,
                        validate_callback=True, oracle_results=(0, 0)),
        _app_840cc_case(0, activation=0),
        _app_840cc_case(0, activation=1, activate_callback=True,
                        oracle_results=(-9,)),
        _app_840cc_case(0, activation=1, activate_callback=True,
                        oracle_results=(0,)),
    ],
    ("app", 0x00048a3c): [
        ({0: mode},
         [(0x2000230c, int(level).to_bytes(4, "little")),
          (0x20007554, int(sink).to_bytes(4, "little"))],
         {1: {0: send_result}})
        for mode, level, sink, send_result in (
            (0, 0, 0, 1),       # transport failure diagnostic
            (0, 2, 0, 0),       # success below logging threshold
            (1, 3, 0, 0),       # mode-one debug logger text
            (0, 3, 1, 0),       # alternate logger and default text
        )
    ],
    # The optional status provider either yields no object or one concrete
    # status byte; the sink must consume that exact local byte and length one.
    ("app", 0x000829c0): [
        ({0: 0x10, 1: 0x20, 2: 0x30, 3: 0x40},
         [(emu.STACK_TOP, (0x1234).to_bytes(4, "little"))],
         {0: {0: 0}}),
        ({0: 0x10, 1: 0x20, 2: 0x30, 3: 0x40},
         [(emu.STACK_TOP, (0x1234).to_bytes(4, "little")),
          (emu.SCRATCH + 0x1000, bytes(8) + b"\x5a")],
         {0: {0: emu.SCRATCH + 0x1000}}),
    ],
    # Preserve representative complete 16-bit provider results in the local
    # payload passed with length two.
    ("app", 0x00082a1a): [
        ({0: 0x10, 1: 0x20, 2: 0x30, 3: 0x40},
         [(emu.STACK_TOP, (0x1234).to_bytes(4, "little"))],
         {0: {0: 0}}),
        ({0: 0x10, 1: 0x20, 2: 0x30, 3: 0x40},
         [(emu.STACK_TOP, (0x1234).to_bytes(4, "little"))],
         {0: {0: 0xabcd}}),
    ],
    # Queue removal has one hidden sign-bit selector and one global current
    # object comparison.  Cover both values of each with successful lock and
    # unlock oracles so every ordinary return/tail path is reached.
    ("app", 0x000741a4): [
        _unlink_record_case(queued, current)
        for queued in (False, True) for current in (False, True)
    ],
    # Early helper errors, ordinary unlinked setup, both flag-controlled
    # register modes, address validation, and the linked callback path.
    ("app", 0x00062d9c): [
        _app_62d9c_case("toggle-error"),
        _app_62d9c_case("setup-error"),
        _app_62d9c_case("simple"),
        _app_62d9c_case("bit-four"),
        _app_62d9c_case("feature-invalid"),
        _app_62d9c_case("feature-valid"),
        _app_62d9c_case("linked"),
    ],
    # Empty traversal, readiness failure, set/clear writes, callback success,
    # and callback error propagation over one active slot.
    ("app", 0x000620cc): [
        _app_620cc_case("empty"),
        _app_620cc_case("not-ready"),
        _app_620cc_case("set"),
        _app_620cc_case("clear"),
        _app_620cc_case("callback-error"),
    ],
    # Immediate and scheduler-gated acquisition, including a single bounded
    # retry and the conditional nested timestamp repair.
    ("app", 0x00062f28): [
        _app_62f28_case("fast"),
        _app_62f28_case("fast-nested"),
        _app_62f28_case("slow"),
        _app_62f28_case("slow-retry"),
    ],
    # The mode selector lives in the connection object returned by the first
    # accessor, so generic argument taint cannot see it.  Exercise ordinary,
    # flag-setting, high-mode, and default arms with coherent allocated state.
    ("app", 0x0005e47c): [
        _pairing_mode_case(mode) for mode in (0, 1, 5, 7)
    ],
    ("app", 0x00055734): [
        _app_55734_case(lookup_status=0),
        _app_55734_case(validate=0),
        _app_55734_case(present=0),
        _app_55734_case(field_status=0x80),
        _app_55734_case(flags=0, kind=0),
        _app_55734_case(flags=0x200, kind=1),
        _app_55734_case(flags=1, kind=2, attachment=0xfffffff4),
        _app_55734_case(flags=3, attachment=0xfffffff4),
        _app_55734_case(configured=1, flags=1, kind=1, attachment=0),
        _app_55734_case(configured=1, flags=0x11, kind=2, attachment=0),
        _app_55734_case(allocation=0),
        _app_55734_case(registration=7),
        _app_55734_case(postprocess=9),
        _app_55734_case(enable=5),
    ],
    # Successful controller completion publishes a concrete record list
    # through the paired five-word output workspace. Cover empty output,
    # caller truncation, and a complete two-record copy.
    ("app", 0x00055350): [
        _app_55350_case(0, 2),
        _app_55350_case(2, 1),
        _app_55350_case(2, 2),
    ],
    # Exercise every flag family with mapped request/output objects and a
    # concrete seven-byte table entry: invalid bit combinations, controller
    # success/error, direct state publication, the global bit-five gate, and
    # both explicit and implicit refresh helpers.
    ("app", 0x00055454): [
        _app_55454_case((1 << 19) | (1 << 2), 0),
        _app_55454_case(1 << 19, 0, oracle_result=0),
        _app_55454_case(1 << 19, 0, oracle_result=7),
        _app_55454_case(1 << 0, 0, table_state=1, oracle_result=0),
        _app_55454_case(1 << 0, 1, table_state=3),
        _app_55454_case((1 << 0) | (1 << 5), 1, table_state=0),
        _app_55454_case((1 << 0) | (1 << 5), 1, table_state=1,
                        global_state=0x40, oracle_result=0),
        _app_55454_case(1 << 2, 0, table_state=1, oracle_result=5),
        _app_55454_case(0, 0, oracle_result=0),
    ],
    # Pair null/non-null optional inputs with concrete 64-bit channel lookup
    # and validation results. This covers setup, parameter programming/error,
    # and the existing-address fast path without random oracle coincidences.
    ("app", 0x0006567c): [
        *[_app_6567c_case(kind) for kind in
          ("no-channel", "invalid-channel", "configure", "parameter",
           "parameter-error", "existing-pair")],
    ],
    # The top-level enable result and nested clear test are callee-owned.
    # Cover inactive, active-without-clear, and active-with-clear paths.
    ("app", 0x00065b18): [
        _app_65b18_case("inactive"),
        _app_65b18_case("active"),
        _app_65b18_case("clear"),
    ],
    # These two veneers have no internal branches: their complete semantics
    # are the fixed target and register transformation.  Deterministic return
    # values make the tail result independently observable.
    ("app", 0x00052b48): [
        ({}, [], {0: {0: 0x12345678}}),
    ],
    ("app", 0x00053184): [
        ({0: 0, 1: 0}, [], {0: {0: 0x12345678}}),
        ({0: emu.SCRATCH + 0x1000, 1: 1},
         [(emu.SCRATCH + 0x1000, b"DATA")],
         {0: {0: 0x87654321}}),
    ],
    # Zero skips the diagnostic; a nonzero lookup result proves all three
    # initialized diagnostic words and the exact logger call.
    ("app", 0x00052edc): [
        ({}, [], {0: {0: 0}}),
        ({}, [], {0: {0: 0x1234}}),
    ],
    # Missing connection, failed validation, allocation failure, and the
    # complete packet-copy/queue path.
    ("app", 0x00054528): [
        _app_54528_case("missing"),
        _app_54528_case("invalid"),
        _app_54528_case("allocation-failure"),
        _app_54528_case("success"),
    ],
    # Direct table update with and without the status-bit flush, early worker
    # error propagation, and one bounded parser retry/backedge.
    ("app", 0x00054d18): [
        _app_54d18_case("direct"),
        _app_54d18_case("direct-flush"),
        _app_54d18_case("early-error"),
        _app_54d18_case("one-retry"),
    ],
    # Null validation, alignment errors, empty/short geometry, and both
    # explicit- and implicit-limit success paths for the seven-argument
    # buffered-writer initializer.
    ("app", 0x0004e2b4): [
        _writer_init_case(0, emu.SCRATCH + 0x2000,
                          emu.SCRATCH + 0x3000, 16, 32, 16, 128),
        _writer_init_case(emu.SCRATCH + 0x1000, 0,
                          emu.SCRATCH + 0x3000, 16, 32, 16, 128),
        _writer_init_case(emu.SCRATCH + 0x1000, emu.SCRATCH + 0x2000,
                          0, 16, 32, 16, 128),
        _writer_init_case(emu.SCRATCH + 0x1000, emu.SCRATCH + 0x2000,
                          emu.SCRATCH + 0x3000, 15, 32, 16, 128),
        _writer_init_case(emu.SCRATCH + 0x1000, emu.SCRATCH + 0x2000,
                          emu.SCRATCH + 0x3000, 16, 32, 16, 0),
        _writer_init_case(emu.SCRATCH + 0x1000, emu.SCRATCH + 0x2000,
                          emu.SCRATCH + 0x3000, 16, 48, 32, 64),
        _writer_init_case(emu.SCRATCH + 0x1000, emu.SCRATCH + 0x2000,
                          emu.SCRATCH + 0x3000, 16, 3, 10, 128),
        _writer_init_case(emu.SCRATCH + 0x1000, emu.SCRATCH + 0x2000,
                          emu.SCRATCH + 0x3000, 16, 32, 16, 128),
        _writer_init_case(emu.SCRATCH + 0x1000, emu.SCRATCH + 0x2000,
                          emu.SCRATCH + 0x3000, 16, 32, 0, 128),
    ],
    # Same-day early return and a full seven-slot miss/rotation/publish path.
    ("app", 0x0004a5b0): [
        _app_4a5b0_case(True), _app_4a5b0_case(False),
    ],
    # The generic selector sweep cannot synthesize the serializer's coherent
    # descriptor plus its three AAPCS stack arguments.  This single reviewed
    # case reaches all three independently addressable local objects,
    # including the one-byte callback object at original 0x0102c3dc.
    ("net", 0x0102bfe4): [_net_serializer_single_index_case()],
    ("app", 0x0005f760): [
        # Invalid channel mask diagnostic.
        ({1: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(20))], {}),
        # One enabled channel, valid selector, sufficient capacity, and the
        # no-external-clock setup path through both mutex operations.
        ({1: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (1).to_bytes(4, "little") +
           (0x1234).to_bytes(4, "little") + (8).to_bytes(4, "little") +
           b"\x08\x00\x00\x00"),
          (0x20002230, b"\x05" + bytes(7))],
         {1: {0: 0, 1: 0x1234}, 2: {0: 0}}),
    ],
    ("app", 0x0005fb30): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(0x54))],
         {0: {0: 0x0bad0000}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           (0x20001234).to_bytes(4, "little") + bytes(0x4c) +
           b"\x01\x7f\x00\x00")],
         {0: {0: 0}}),
    ],
    ("app", 0x00061624): [
        ({0: emu.SCRATCH + 0x1000, 1: 3, 2: 0, 3: 0x55},
         [(emu.SCRATCH + 0x1000, bytes(4) +
           (emu.SCRATCH + 0x2000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000, bytes(0x20))],
         {0: {0: 0x0bad0000}, 2: {0: 0x0bad0000}}),
        ({0: emu.SCRATCH + 0x1000, 1: 3, 2: 0x10000, 3: 0x55},
         [(emu.SCRATCH + 0x1000, bytes(4) +
           (emu.SCRATCH + 0x2000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000, bytes(0x20))],
         {0: {0: 0x0bad0000}, 1: {0: 0x0bad0000},
          2: {0: 0x0bad0000}, 3: {0: 0x0bad0000}}),
    ],
    # Parser rejection plus a complete successful property serialization.
    # The success case drives every boolean field and the final close helper.
    ("app", 0x00051ac0): [
        ({0: emu.SCRATCH + 0x3000, 1: 3, 2: 8}, [], {0: {0: 1}}),
        ({0: emu.SCRATCH + 0x3000, 1: 3, 2: 8}, [],
         {0: {0: 0}, 1: {0: 1}, 2: {0: 1}, 3: {0: 1},
          4: {0: 1}, 5: {0: 1}, 6: {0: 1}, 7: {0: 0xffffffff},
          8: {0: 1}, 9: {0: 1}, 10: {0: 1}, 11: {0: 1},
          12: {0: 1}, 13: {0: 1}, 14: {0: 1}, 15: {0: 1},
          16: {0: 1}, 17: {0: 1}, 18: {0: 1}, 19: {0: 1},
          20: {0: 1}, 21: {0: 1}},
         {0: [(1, 0, b"ABCDEFGH", 0x00052038),
              (2, 0, bytes(range(36)), 0x00052038),
              (3, 0, (0x10).to_bytes(4, "little"), 0x00052038)]}),
    ],
    # Early classification and deep flash-operation/error-map cases.  Oracle
    # writes model the real one-byte state and four-byte handle outputs.
    ("app", 0x00051d8c): [
        ({0: 2, 1: 0}, [], {0: {0: 2}, 1: {0: 8}}),
        ({0: 2, 1: 0}, [],
         {0: {0: 9}, 1: {0: 8}, 2: {0: 7}, 3: {0: 0},
          4: {0: 4}},
         {1: [(1, 0, b"\x03", 0x000809b0)],
          3: [(1, 0, (0x1234).to_bytes(4, "little"), 0x0004e048)]}),
        ({0: 3, 1: 1}, [],
         {0: {0: 9}, 1: {0: 8}, 2: {0: 0}, 3: {0: 7},
          4: {0: 0}, 5: {0: 0}},
         {1: [(1, 0, b"\x03", 0x000809b0)],
          4: [(1, 0, (0x1234).to_bytes(4, "little"), 0x0004e048)]}),
    ],
    # Request parse rejection, direct status 9, and fallback status forwarding.
    ("app", 0x00052180): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (0x20002000).to_bytes(4, "little") +
           (0x20003000).to_bytes(4, "little"))], {0: {0: 1}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (0x20002000).to_bytes(4, "little") +
           (0x20003000).to_bytes(4, "little"))],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 1}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(4) + (0x20002000).to_bytes(4, "little") +
           (0x20003000).to_bytes(4, "little"))],
         {0: {0: 0}, 1: {0: 1}, 2: {0: 0x12345}}),
    ],
    # Flash-open failure, missing device, and successful erase.  The opener's
    # out-parameter receives one mapped flash-area object in success cases.
    ("app", 0x00052604): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(8) +
           (0x20004000).to_bytes(4, "little"))],
         {0: {0: 0xffffffff}, 2: {0: 0}}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(8) +
           (0x20004000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000, bytes(8) +
           (0x1000).to_bytes(4, "little"))],
         {0: {0: 0}, 1: {0: 0}, 4: {0: 0}},
         {0: [(1, 0, (emu.SCRATCH + 0x2000).to_bytes(4, "little"),
               0x0004e048)]}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(8) +
           (0x20004000).to_bytes(4, "little")),
          (emu.SCRATCH + 0x2000, bytes(8) +
           (0x1000).to_bytes(4, "little"))],
         {0: {0: 0}, 1: {0: 0x20005000}, 2: {0: 0}},
         {0: [(1, 0, (emu.SCRATCH + 0x2000).to_bytes(4, "little"),
               0x0004e048)]}),
    ],
    # Both sides of the optional registration prelude.
    ("app", 0x000526f4): [
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000, bytes(0x30))], {}),
        ({0: emu.SCRATCH + 0x1000},
         [(emu.SCRATCH + 0x1000,
           bytes(0x2c) + (1).to_bytes(4, "little"))], {}),
    ],
    # One coherent one-row glyph image reaches the allocator, device read
    # callback, header parser, all three metadata fields, byte renderer, and
    # final free.  Generic selector fuzz only reaches early callback faults.
    ("app", 0x00036820): [
        ({0: 2},
         [(emu.SCRATCH + 0x1000,
           bytes(28) + b"\x01\x00" + bytes(0x50 - 30)),
          (emu.SCRATCH + 0x2000,
           bytes(0x1030) + (0x00080001).to_bytes(4, "little")),
          (0x20009fcc, bytes(4))],
         {0: {0: emu.SCRATCH + 0x1000},
          2: {0: emu.SCRATCH + 0x2000},
          3: {0: emu.SCRATCH + 0x3000},
          4: {0: 0}, 5: {0: 0}, 6: {0: 0x20},
          7: {0: 8}, 8: {0: 1},
          10: {0: emu.SCRATCH + 0x2000},
         11: {0: emu.SCRATCH + 0x3000}, 12: {0: 0}}),
    ],
    # Both diagnostic backends and a real one-row callback transaction.  The
    # active cases make the temporary framebuffer mutation, callback ABI, and
    # exact restoration sequence observable.
    ("app", 0x00047260): [
        _app_scanline_case(False, buffered=False),
        _app_scanline_case(False, buffered=True),
        _app_scanline_case(True, callback_status=0),
        _app_scanline_case(True, callback_status=1, buffered=False),
        _app_scanline_case(True, callback_status=1, buffered=True),
    ],
    ("app", 0x000473c8): [
        _app_scanline_case(False, buffered=False),
        _app_scanline_case(False, buffered=True),
        _app_scanline_case(True, callback_status=0),
        _app_scanline_case(True, callback_status=1, buffered=False),
        _app_scanline_case(True, callback_status=1, buffered=True),
    ],
    # Cover the ASCII fast path, absent callback, query failure, complete
    # read, and read-error diagnostic.  The reviewed target-bound write above
    # initializes both dimension halfwords on successful queries.
    ("app", 0x0004792c): [
        _app_glyph_case("ascii"),
        _app_glyph_case("absent"),
        _app_glyph_case("query-error"),
        _app_glyph_case("success"),
        _app_glyph_case("read-error"),
    ],
    # Active record rotation, including the nonzero device index decrement.
    ("app", 0x0003439c): [
        ({},
         [(0x2001a22a, b"\x00"),
          (0x20007dac, (1).to_bytes(4, "little") + bytes(0x1b0)),
          (emu.SCRATCH + 0x1000, bytes(0x200))],
         {0: {0: emu.SCRATCH + 0x1000}, 1: {0: 2},
          2: {0: emu.SCRATCH + 0x1000},
          3: {0: emu.SCRATCH + 0x1000}, 4: {0: 0x12345678},
          5: {0: emu.SCRATCH + 0x1000}, 6: {0: 3}}),
    ],
    # Missing-first-property cases make the first recovered key and cleanup
    # path independently observable without requiring a full settings tree.
    ("app", 0x00034dbc): [
        ({0: 0x55},
         [(0x20007554, bytes(4)), (0x2001a22c, bytes(0x15e2))],
         {0: {0: emu.SCRATCH + 0x1000}, 2: {0: 0}}),
    ],
    ("app", 0x00035050): [
        ({}, [(0x20007554, bytes(4)), (0x2001a22c, bytes(2))],
         {0: {0: emu.SCRATCH + 0x1000}, 1: {0: 0}}),
    ],
    # Midnight observes the fixed 0x120-byte glyph-buffer capacity and passes
    # the complete six-byte local UTF-16 list to its reviewed helper.
    ("app", 0x000362e8): [
        ({0: emu.SCRATCH + 0x3000, 1: 0x11223344},
         [(emu.SCRATCH + 0x1000,
           bytes(0xef) + (0).to_bytes(4, "little") + b"\x00" +
           bytes(0x100 - 0xf4))],
         {0: {0: emu.SCRATCH + 0x1000},
          1: {0: emu.SCRATCH + 0x2000}}),
    ],
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
    # The two bounded-copy wrappers share the same contract: capacity and
    # overlap violations enter the fatal runtime-constraint handler, while a
    # valid disjoint range reaches the corresponding three-argument copier.
    ("app", 0x00086c1e): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000,
          2: 4, 3: 4},
         [(emu.SCRATCH + 0x1000, bytes(0x20)),
          (emu.SCRATCH + 0x2000, b"COPY" + bytes(0x1c))], {}),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000,
          2: 5, 3: 4},
         [(emu.SCRATCH + 0x1000, bytes(0x20)),
          (emu.SCRATCH + 0x2000, b"LIMIT" + bytes(0x1b))], {}),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1002,
          2: 4, 3: 4},
         [(emu.SCRATCH + 0x1000, b"OVERLAP" + bytes(0x19))], {}),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1000,
          2: 0, 3: 0},
         [(emu.SCRATCH + 0x1000, bytes(0x20))], {}),
    ],
    ("app", 0x00087080): [
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000,
          2: 4, 3: 4},
         [(emu.SCRATCH + 0x1000, bytes(0x20)),
          (emu.SCRATCH + 0x2000, b"TEXT" + bytes(0x1c))], {}),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x2000,
          2: 5, 3: 4},
         [(emu.SCRATCH + 0x1000, bytes(0x20)),
          (emu.SCRATCH + 0x2000, b"LIMIT" + bytes(0x1b))], {}),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1002,
          2: 4, 3: 4},
         [(emu.SCRATCH + 0x1000, b"OVERLAP" + bytes(0x19))], {}),
        ({0: emu.SCRATCH + 0x1000, 1: emu.SCRATCH + 0x1000,
          2: 0, 3: 0},
         [(emu.SCRATCH + 0x1000, bytes(0x20))], {}),
    ],
    # Floating normalization uses the first helper's d0 result, but derives
    # its optional scale from the original input exponent.  Exercise the flag
    # arm and both sides of the exact exponent 106/107 boundary.
    ("app", 0x000870ea): [
        ({0: 0x01020304, 1: 106 << 20, 2: 0}, [],
         {0: {0: 0x11223344, 1: 0x00012345}}),
        ({0: 0x01020304, 1: 107 << 20, 2: 1}, [],
         {0: {0: 0x11223344, 1: 0x00012345}}),
        ({0: 0x01020304, 1: 106 << 20, 2: 1}, [],
         {0: {0: 0x11223344, 1: 0x00012345},
          1: {0: 0xaabbccdd, 1: 0x40012345}}),
        ({0: 0x01020304, 1: 0, 2: 1}, [],
         {0: {0: 0x55667788, 1: 0x00054321},
          1: {0: 0x89abcdef, 1: 0x3ff23456}}),
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
        # Descriptor copy succeeds, then submission fails: this is the only
        # path that materializes and consumes the three-word error record.
        ({0: 1, 1: emu.SCRATCH, 2: 1, 3: 2},
         [(0x2000a28c, bytes(4)), (emu.SCRATCH, bytes(0x40))],
         {0: {0: 8}, 2: {0: 7}}),
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
        _even_ai_case(2, 1, 0),                    # unknown active state
        _even_ai_case(0, 0, 0),                    # inactive ignored phase
        _even_ai_case(0, 1, 0, initialized=1),     # one-time init latch
        _even_ai_case(0, 2, 0, level=3, sink=0),   # inactive direct logger + cleanup
        _even_ai_case(0, 2, 0, level=3, sink=1),   # inactive fallback logger
        _even_ai_case(0, 1, 0, sparse_pixels=True),# complete eight-frame init mask
        _even_ai_case(0, 1, 0xc),                  # status 12 immediate init return
        _even_ai_case(0, 1, 0xe),                  # status 14 full publish
        _even_ai_case(1, 0, 4),                    # active status-icon painter
        _even_ai_case(1, 2, 4, level=3, sink=0),   # active logger + teardown
        _even_ai_case(1, 2, 4, level=3, sink=1),   # active fallback logger
        _even_ai_case(1, 3, 4),                    # active ignored phase
        _even_ai_case(1, 1, 4, frame=1),           # low-status text render
        _even_ai_case(1, 1, 5, frame=1),           # blank transitional page
        _even_ai_case(1, 1, 6, frame=1),           # blank transitional page boundary
        _even_ai_case(1, 1, 7, substate=3,
                      sparse_pixels=True),         # page-change eight-frame mask
        _even_ai_case(1, 1, 7, substate=4,
                      sparse_pixels=True),         # completed-page transition
        _even_ai_case(1, 1, 0xb, frame=1),         # status 11 mic/header render
        _even_ai_case(1, 1, 0xc, frame=1),         # status 12 no-render return
        _even_ai_case(1, 1, 0xd, frame=1),         # status 13 no-render return
        _even_ai_case(1, 1, 0xe, frame=1),         # status 14 full-frame publish
        _even_ai_case(1, 1, 0xf, frame=1),         # status 15 no-render return
        _even_ai_case(1, 1, 0x10, frame=1),        # status 16 text render
        _even_ai_case(1, 1, 8, frame=0),           # streaming render first frame
        _even_ai_case(1, 1, 8, frame=1),           # streaming render update frame
        _even_ai_case(1, 1, 9, frame=1,
                      hide_progress=0),             # forced plain stream + progress
        _even_ai_case(1, 1, 10, frame=1,
                      rendered=1, hide_progress=0), # scrolling stream + progress
    ],
    # QuickNote is selected first by an absolute UI-state byte and only then
    # by the phase argument.  Random RAM almost never enters states 0/1/2, so
    # enumerate their production phase families explicitly.  Duplicate state
    # 0/2 cases cover both logger sinks, enable gates, recording transitions,
    # review warning/exit flags, and a bounded shared-row raster allocation.
    ("app", 0x0003b824): [
        # Unknown-state return plus every state-zero phase family and exact
        # logger threshold.  The two render cases complete all four masks,
        # both language layouts, and the primary-side DMIC start.
        _quicknote_case(3, 0),
        _quicknote_case(0, 0),
        _quicknote_case(0, 0, level=3, sink=0),
        _quicknote_case(0, 0, level=3, sink=1),
        _quicknote_case(0, 1, enable=0),
        _quicknote_case(0, 1, enable=1, language=5,
                        sparse_pixels=True),
        _quicknote_case(0, 1, level=3, sink=1, enable=1,
                        device_type=1, language=6, sparse_pixels=True),
        _quicknote_case(0, 2, level=1, device_type=1),
        _quicknote_case(0, 3),

        # Recording-state idle icon, no-op render phase, exit cleanup, and
        # release-to-review transition with/without the primary-side callback.
        _quicknote_case(1, 0),
        _quicknote_case(1, 1),
        _quicknote_case(1, 2, level=3, sink=1, device_type=1),
        _quicknote_case(1, 3, level=3, sink=0, device_type=1,
                        uptime_ticks=32768),
        _quicknote_case(1, 3, uptime_ticks=65536),

        # At one second of reviewed uptime: expired, pre-warning animation,
        # and inside-warning saved-message paths.  Duplicate hint/language/log
        # cases cover both skip arms, both strings, and both logger sinks.
        _quicknote_case(2, 2, level=3, device_type=1),
        _quicknote_case(2, 0, level=3, sink=1,
                        deadline=(0, 999, 0), uptime_ticks=32768),
        _quicknote_case(2, 0, deadline=(0, 2000, 0),
                        uptime_ticks=32768, exit_flag=0),
        _quicknote_case(2, 0, deadline=(0, 2000, 0),
                        uptime_ticks=32768, exit_flag=1),
        # Equality remains live: exact deadline is not expired, while exact
        # warning boundary remains in the pre-warning animation arm.
        _quicknote_case(2, 1, deadline=(0, 1000, 0),
                        uptime_ticks=32768, language=5),
        _quicknote_case(2, 1, deadline=(0, 1100, 0),
                        uptime_ticks=32768),
        _quicknote_case(2, 1, level=3, sink=0,
                        deadline=(0, 1050, 0), uptime_ticks=32768,
                        language=5, exit_flag=0),
        _quicknote_case(2, 3, deadline=(0, 1050, 0),
                        uptime_ticks=32768, language=6, exit_flag=0),
        _quicknote_case(2, 3, deadline=(0, 1050, 0),
                        uptime_ticks=32768, exit_flag=1),
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


def _gatt_sc_store_failure_case(error):
    entry = emu.SCRATCH + 0x1a00
    return ({0: entry},
            [(entry, bytes((1, 2, 3, 4, 5, 6, 7, 8,
                            0x34, 0x12, 0x78, 0x56)))],
            {0: {0: int(error) & 0xffffffff}})


REVIEWED_ORACLE_CASES[("app", 0x0005a0e8)] = [
    _gatt_sc_store_failure_case(0),
    _gatt_sc_store_failure_case(-5),
]


def _ancs_dispatch_case(dequeue_result=0, status=0, text_first=0,
                        kind=None, transport=0, sink=0, uid=5):
    """Production-shaped dequeue outcomes for FUN_0001965c.

    FUN_00018d94 owns both the success return and the 0x1b4-byte output
    record.  Random oracle returns almost never select success, and an oracle
    without its real out-write leaves the prior memset image permanently
    empty.  Drive the reviewed return and target-bound record write together.
    """
    record = bytearray(0x1b4)
    record[16] = int(text_first) & 0xff
    record[432:436] = int(status).to_bytes(4, "little")

    device = bytearray(8)
    device[0:4] = (0x11223344).to_bytes(4, "little")
    device[6] = int(transport) & 0xff
    memory = [
        (0x20006aac, bytes(device)),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]
    oracles = {1: {0: int(dequeue_result)}}
    writes = {}
    if dequeue_result == 0:
        writes[1] = [(0, 0, bytes(record), 0x00018d94)]
        # UID generation follows every nonempty successful dequeue.
        if status > 1 or text_first:
            oracles[2] = {0: int(uid)}
            if status < 2:
                oracles[4] = {0: int(kind)}
    return ({0: 0x12345678}, memory, oracles, writes)


# Cover dequeue failure/empty success, each classifier result, both logging
# implementations, the status>=2 bypass, and both transport-copy arms.  In
# particular kind 3 must publish mode byte 4 while kind 2/status>=2 publish 2.
REVIEWED_ORACLE_CASES[("app", 0x0001965c)] = [
    _ancs_dispatch_case(dequeue_result=1),
    _ancs_dispatch_case(),
    _ancs_dispatch_case(status=2, uid=0),
    _ancs_dispatch_case(text_first=ord("A"), kind=0),
    _ancs_dispatch_case(text_first=ord("A"), kind=1, sink=0),
    _ancs_dispatch_case(text_first=ord("A"), kind=1, sink=1),
    _ancs_dispatch_case(text_first=ord("A"), kind=2, transport=2),
    _ancs_dispatch_case(text_first=ord("A"), kind=3),
]


def _flash_crc_case(crc_pointer, byte_count, init_result=1,
                    callback_result=0):
    """Bounded flash-reader state for FUN_00022974's complete local buffer."""
    context = emu.SCRATCH + 0x3000
    context_image = bytearray(0x1034)
    context_image[0x1030:0x1034] = (0x00080001).to_bytes(4, "little")
    memory = [
        (emu.SCRATCH + 0x2000, b"\x34\x12"),
        (context, bytes(context_image)),
        (0x2000230c, bytes(4)),
        (0x20007554, bytes(4)),
        (0x2000302c, b"\x00"),
        (0x20018d90, b"\x00"),
    ]
    oracles = {1: {0: int(init_result)}}
    writes = {}
    if crc_pointer and byte_count and init_result:
        oracles.update({2: {0: context}, 3: {0: context},
                        4: {0: int(callback_result)}, 5: {0: 0x5678}})
        writes[4] = [(2, 0, b"\x5a", 0x00080000)]
    return ({0: crc_pointer, 1: 0x1000, 2: byte_count},
            memory, oracles, writes)


# Null/empty validation, initialization failure, and one successful one-byte
# read.  The success case reaches the buffer base (not merely buffer+4), makes
# its complete initialized contents observable, and exercises the exact
# target-bound callback write before CRC consumption.
REVIEWED_ORACLE_CASES[("app", 0x00022974)] = [
    _flash_crc_case(0, 1),
    _flash_crc_case(emu.SCRATCH + 0x2000, 0),
    _flash_crc_case(emu.SCRATCH + 0x2000, 1, init_result=0),
    _flash_crc_case(emu.SCRATCH + 0x2000, 1),
]


def _locked_driver_case(enabled, irq_flags, callback_result=0,
                        level=0, sink=0):
    """Concrete driver/vtable state for FUN_0002e398/FUN_0002e440."""
    device = emu.SCRATCH + 0x1000
    vtable = emu.SCRATCH + 0x1100
    config = emu.SCRATCH + 0x2000
    obj = bytearray(12)
    obj[8:12] = vtable.to_bytes(4, "little")
    methods = bytearray(8)
    methods[0:4] = (0x00080001).to_bytes(4, "little")
    methods[4:8] = (0x00080005).to_bytes(4, "little")
    memory = [
        (0x20007b68, (device if enabled else 0).to_bytes(4, "little")),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
        (device, bytes(obj)),
        (vtable, bytes(methods)),
        (config + 0x105c, int(irq_flags).to_bytes(2, "little")),
    ]
    oracles = {}
    if (irq_flags & 0x10) == 0:
        # FUN_0007c080 is a reviewed one-instruction `bx lr` veneer.  Preserve
        # the live r1 flags value exactly instead of letting the generic oracle
        # manufacture a caller-clobber that the real veneer cannot perform.
        oracles[0] = {1: (int(irq_flags) << 27) & 0xffffffff}
    if enabled:
        # With bit four clear the empty irq_lock veneer precedes the lock and
        # callback; with it set the callback is one ordinal earlier.
        callback_ordinal = 2 if (irq_flags & 0x10) == 0 else 1
        oracles[callback_ordinal] = {0: int(callback_result)}
    return ({0: config, 1: 0x11111111, 2: 0x22222222, 3: 0x33333333},
            memory, oracles)


# Both wrappers share the same locking and diagnostic control flow but select
# distinct adjacent vtable methods.  Stable mapped objects eliminate random
# indirect-call faults; nonzero callback results make both logger sinks live.
for _driver_va in (0x0002e398, 0x0002e440):
    REVIEWED_ORACLE_CASES[("app", _driver_va)] = [
        _locked_driver_case(False, 0),
        _locked_driver_case(False, 0x10),
        _locked_driver_case(True, 0, callback_result=0),
        _locked_driver_case(True, 0x10, callback_result=7, level=0),
        _locked_driver_case(True, 0x10, callback_result=7, level=1, sink=0),
        _locked_driver_case(True, 0x10, callback_result=7, level=1, sink=1),
    ]


def _option_init_case(stage, param=emu.SCRATCH + 0x2000,
                      transfer_result=0):
    """Register-read and transfer outcomes for FUN_0002e67c."""
    controller = emu.SCRATCH + 0x1000
    vtable = emu.SCRATCH + 0x1100
    device = bytearray(12)
    device[8:12] = vtable.to_bytes(4, "little")
    methods = bytearray(12)
    methods[8:12] = (0x00080001).to_bytes(4, "little")
    memory = [
        (0x2000230c, bytes(4)),
        (0x20007554, bytes(4)),
        (0x200023fc, controller.to_bytes(4, "little")),
        (0x20007b6c, bytes(4)),
        (0x20018da1, bytes(1)),
        (controller, bytes(device)),
        (vtable, bytes(methods)),
        (emu.SCRATCH + 0x2000, bytes(0x40)),
    ]
    prefix = int(param == 0)
    oracles = ({0: {0: emu.SCRATCH + 0x2000}} if prefix else {})
    writes = {}

    def register_read(index, value, result=0):
        ordinal = prefix + index
        oracles[ordinal] = {0: int(result)}
        if result == 0:
            writes[ordinal] = [(1, 0, int(value).to_bytes(2, "little"),
                                0x0002e594)]

    if stage == "first-error":
        register_read(0, 0, result=1)
    else:
        register_read(0, 0x5449 if stage != "wrong-chip" else 0x1234)
        if stage not in ("wrong-chip",):
            if stage == "second-error":
                register_read(1, 0, result=1)
            else:
                register_read(1, 0x3001 if stage != "wrong-option" else 0x1234)
                if stage not in ("wrong-option",):
                    if stage == "config-error":
                        register_read(2, 0, result=1)
                    else:
                        register_read(2, 0x1234)
                        ready_ordinal = prefix + 3
                        oracles[ready_ordinal] = {
                            0: 0 if stage == "not-ready" else 1
                        }
                        if stage not in ("not-ready",):
                            oracles[prefix + 4] = {0: int(transfer_result)}
    return ({0: int(param)}, memory, oracles, writes)


def _option_init_logged_success(sink):
    args, memory, _oracles, _writes = _option_init_case("success")
    memory.append((0x2000230c, (3).to_bytes(4, "little")))
    memory.append((0x20007554, int(sink).to_bytes(4, "little")))
    # Initial, chip-id, option-id, and final diagnostics occupy ordinals
    # 0/2/4/8.  Bind each register out-write to the intervening read target.
    oracles = {
        1: {0: 0}, 3: {0: 0}, 5: {0: 0},
        6: {0: 1}, 7: {0: 0},
    }
    writes = {
        1: [(1, 0, (0x5449).to_bytes(2, "little"), 0x0002e594)],
        3: [(1, 0, (0x3001).to_bytes(2, "little"), 0x0002e594)],
        5: [(1, 0, (0x1234).to_bytes(2, "little"), 0x0002e594)],
    }
    return args, memory, oracles, writes


REVIEWED_ORACLE_CASES[("app", 0x0002e67c)] = [
    _option_init_case("first-error", param=0),
    _option_init_case("wrong-chip"),
    _option_init_case("second-error"),
    _option_init_case("wrong-option"),
    _option_init_case("config-error"),
    _option_init_case("not-ready"),
    _option_init_case("success", transfer_result=-1),
    _option_init_case("success", transfer_result=0),
    _option_init_logged_success(0),
    _option_init_logged_success(1),
]


def _bt_addr_format_case(address_type, address_bytes):
    """Exercise one complete bt_addr_le_t formatting path.

    The two formatter callees are modeled with their reviewed caller-owned
    writes.  This makes the type-label stack buffer deterministic and exposes
    the final string as the real observable side effect.
    """
    source = emu.SCRATCH + 0x2400
    destination = emu.SCRATCH + 0x2800
    labels = {
        0: b"public\0",
        1: b"random\0",
        2: b"public-id\0",
        3: b"random-id\0",
    }
    label = labels.get(address_type, ("0x%02x" % address_type).encode() + b"\0")
    rendered = ("%02X:%02X:%02X:%02X:%02X:%02X (%s)" %
                (*reversed(address_bytes), label[:-1].decode())).encode() + b"\0"
    first_callee = 0x00086fee if address_type in labels else 0x0007ddbe
    writes = {
        0: [(0, 0, label, first_callee)],
        1: [(0, 0, rendered, 0x0007ddbe)],
    }
    return (
        {0: source, 1: destination},
        [(source, bytes([address_type]) + bytes(address_bytes)),
         (destination, b"\xa5" * 64)],
        {},
        writes,
    )


REVIEWED_ORACLE_CASES[("app", 0x00018334)] = [
    _bt_addr_format_case(0, bytes.fromhex("0123456789ab")),
    _bt_addr_format_case(1, bytes.fromhex("fedcba987654")),
    _bt_addr_format_case(2, bytes.fromhex("001122334455")),
    _bt_addr_format_case(3, bytes.fromhex("a0b1c2d3e4f5")),
    _bt_addr_format_case(4, bytes.fromhex("102030405060")),
    _bt_addr_format_case(0xff, bytes.fromhex("ffeeddccbbaa")),
]


def _poll_register_case(events, just_check=False, poller_active=True):
    """Build bounded production-shaped k_poll_event registration inputs.

    Event tuples are (type, condition_met, null_object).  Objects use exactly
    the fields read by poll.c's is_condition_met implementation.
    """
    event_address = emu.SCRATCH + 0x3000
    poller_address = emu.SCRATCH + 0x3800
    event_image = bytearray(max(20, 20 * len(events)))
    memory = [
        (0x2000b4a0, bytes(4)),
        (poller_address, bytes([int(bool(poller_active))]) + bytes(15)),
    ]
    for index, (event_type, condition_met, null_object) in enumerate(events):
        base = 20 * index
        object_address = emu.SCRATCH + 0x4000 + 0x80 * index
        object_image = bytearray(0x40)
        if condition_met:
            if event_type in (1, 2):
                object_image[8:12] = (1).to_bytes(4, "little")
            elif event_type == 4:
                object_image[0:4] = (emu.SCRATCH + 0x7000).to_bytes(4, "little")
            elif event_type == 8:
                object_image[0x24:0x28] = (1).to_bytes(4, "little")
        event_image[base + 8:base + 12] = (0x11223344).to_bytes(4, "little")
        # tag=0xa5, type in bits 8..13, state starts with bit 0x20 set so
        # state updates prove OR-not-assignment behavior.
        flags = 0xa5 | ((int(event_type) & 0x3f) << 8) | (0x20 << 14)
        event_image[base + 12:base + 16] = flags.to_bytes(4, "little")
        if not null_object:
            event_image[base + 16:base + 20] = object_address.to_bytes(4, "little")
            memory.append((object_address, bytes(object_image)))
    memory.append((event_address, bytes(event_image)))
    return ({0: event_address, 1: len(events), 2: poller_address,
             3: int(bool(just_check))}, memory, {})


REVIEWED_ORACLE_CASES[("app", 0x000751d0)] = [
    _poll_register_case([]),
    *[_poll_register_case([(kind, True, False)]) for kind in (1, 2, 4, 8)],
    *[_poll_register_case([(kind, False, False)]) for kind in (0, 1, 2, 4, 8)],
    _poll_register_case([(2, False, False)], just_check=True),
    _poll_register_case([(1, True, False), (2, False, False)]),
    _poll_register_case([(1, False, False), (2, False, False),
                         (4, False, False), (8, False, False)]),
    _poll_register_case([(3, False, False)]),
    *[_poll_register_case([(kind, False, True)]) for kind in (1, 2, 4, 8)],
]


def _poll_clear_case(events, interrupt_key=0, unlock_valid=True,
                     lock_valid=True):
    """Build reversed clear_event_registrations inputs.

    Event tuples are (type, null_object, linked).  Linked nodes receive real
    predecessor/successor storage so sys_dlist_remove effects are compared.
    """
    event_address = emu.SCRATCH + 0x3000
    event_image = bytearray(max(20, 20 * len(events)))
    memory = [(0x2000b4a0, bytes(4))]
    for index, (event_type, null_object, linked) in enumerate(events):
        base = 20 * index
        object_address = emu.SCRATCH + 0x4000 + 0x80 * index
        event_image[base + 8:base + 12] = (0x11223344).to_bytes(4, "little")
        event_image[base + 12:base + 16] = (
            0xa5 | ((int(event_type) & 0x3f) << 8)).to_bytes(4, "little")
        if not null_object:
            event_image[base + 16:base + 20] = object_address.to_bytes(4, "little")
            memory.append((object_address, bytes(0x40)))
        if linked:
            successor = emu.SCRATCH + 0x6000 + 0x40 * index
            predecessor = emu.SCRATCH + 0x7000 + 0x40 * index
            event_image[base:base + 4] = successor.to_bytes(4, "little")
            event_image[base + 4:base + 8] = predecessor.to_bytes(4, "little")
            memory.extend([(successor, b"\x11" * 8),
                           (predecessor, b"\x22" * 8)])
    memory.append((event_address, bytes(event_image)))
    oracles = {}
    for index in range(len(events)):
        oracles[2 * index] = {0: int(bool(unlock_valid))}
        oracles[2 * index + 1] = {0: int(bool(lock_valid))}
    return ({0: event_address, 1: len(events), 2: int(interrupt_key)},
            memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x000753ec)] = [
    _poll_clear_case([]),
    _poll_clear_case([(0, False, False)], interrupt_key=0x20),
    *[_poll_clear_case([(kind, False, False)]) for kind in (1, 2, 4, 8)],
    *[_poll_clear_case([(kind, False, True)]) for kind in (1, 2, 4, 8)],
    _poll_clear_case([(1, False, True), (2, False, False),
                      (4, False, True), (8, False, False)],
                     interrupt_key=0x40),
    _poll_clear_case([(3, False, False)]),
    *[_poll_clear_case([(kind, True, False)]) for kind in (1, 2, 4, 8)],
    _poll_clear_case([(0, False, False)], unlock_valid=False),
    _poll_clear_case([(0, False, False)], lock_valid=False),
]


def _pairing_failed_case(level=0, sink=0):
    active = emu.SCRATCH + 0x2400
    description = b"G1 production peer\0" + bytes(17)
    writes = {
        1: [(1, 0, description, 0x00018334)],
    }
    return (
        {0: 0x12345678, 1: 0x3e},
        [(0x2000230c, int(level).to_bytes(4, "little")),
         (0x20007554, int(sink).to_bytes(4, "little")),
         (active, bytes(64))],
        {0: {0: active}},
        writes,
    )


REVIEWED_ORACLE_CASES[("app", 0x00018444)] = [
    _pairing_failed_case(),
    _pairing_failed_case(level=1),
    _pairing_failed_case(level=1, sink=1),
]


REVIEWED_ORACLE_CASES[("app", 0x00047538)] = [
    ({}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4))], {}),
    ({}, [(0x2000230c, (4).to_bytes(4, "little")),
          (0x20007554, bytes(4))], {}),
    ({}, [(0x2000230c, (4).to_bytes(4, "little")),
          (0x20007554, (1).to_bytes(4, "little"))], {}),
]


def _panel_off_case(active=True, ready=1, level=0, sink=0):
    context = emu.SCRATCH + 0x6400
    base = context - 0x60
    image = bytearray(0x3dc)
    image[8:12] = (0x00080001).to_bytes(4, "little")
    image[0x18:0x1c] = int(bool(active)).to_bytes(4, "little")
    memory = [
        (base, bytes(image)),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]
    if not active:
        return ({0: context}, memory, {})
    query_ordinal = 1 if level > 2 else 0
    return ({0: context}, memory, {query_ordinal: {0: int(ready)}})


REVIEWED_ORACLE_CASES[("app", 0x00046d2c)] = [
    _panel_off_case(active=False),
    _panel_off_case(ready=1),
    _panel_off_case(ready=0),
    _panel_off_case(ready=1, level=3),
    _panel_off_case(ready=0, level=3, sink=1),
]


def _post_notification_case(command_opcode=4, command_length=0x1b4,
                            response_opcode=0, level=0, sink=0,
                            record_count=2, classifier=None,
                            null_argument=None):
    context = emu.SCRATCH + 0x1000
    state = emu.SCRATCH + 0x3000
    notification = emu.SCRATCH + 0x4000
    response = emu.SCRATCH + 0x6000
    command = emu.SCRATCH + 0x6100
    payload = emu.SCRATCH + 0x6200
    output = emu.SCRATCH + 0x6300

    context_image = bytearray(0x1000)
    context_image[0xff8:0xffc] = state.to_bytes(4, "little")
    notification_image = bytearray(0x1b8)
    notification_image[0x1b4:0x1b8] = int(record_count).to_bytes(4, "little")
    response_image = bytearray(4)
    response_image[1] = response_opcode
    command_image = bytearray(4)
    command_image[1] = command_opcode
    command_image[2:4] = int(command_length).to_bytes(2, "little")
    args = {0: context, 1: notification, 2: response, 3: command,
            4: payload, 5: output}
    if null_argument is not None:
        args[null_argument] = 0
    memory = [
        (context, bytes(context_image)),
        (state, bytes((i * 13 + 7) & 0xff for i in range(0xc0))),
        (notification, bytes(notification_image)),
        (response, bytes(response_image)),
        (command, bytes(command_image)),
        (payload, bytes(8)),
        (output, b"\xa5" * 8),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]
    oracles = {}
    if (command_opcode != 4 and command_length == 0x1b4 and record_count <= 1):
        # An initial level-three diagnostic precedes the classifier.
        ordinal = 1 if level > 2 else 0
        oracles[ordinal] = {0: int(classifier or 0)}
    return args, memory, oracles


REVIEWED_ORACLE_CASES[("app", 0x000340c4)] = [
    _post_notification_case(null_argument=0),
    _post_notification_case(null_argument=5, level=2),
    _post_notification_case(null_argument=4, level=2, sink=1),
    _post_notification_case(response_opcode=4),
    _post_notification_case(response_opcode=4, level=3),
    _post_notification_case(response_opcode=6, level=3, sink=1),
    _post_notification_case(command_opcode=3, command_length=7),
    _post_notification_case(command_opcode=3, command_length=7, level=1),
    _post_notification_case(command_opcode=3, command_length=7,
                            level=1, sink=1),
    _post_notification_case(command_opcode=3, record_count=2),
    _post_notification_case(command_opcode=3, record_count=1, classifier=1),
    _post_notification_case(command_opcode=3, record_count=1, classifier=2),
    _post_notification_case(command_opcode=3, record_count=1, classifier=0,
                            response_opcode=6, level=3),
]


def _slot_update_case(operation=1, slot=0, queue_result=0, ready=1,
                      read_result=0, erase_result=0, write_result=0,
                      marker=0, header_compare=0, tail_compare=0,
                      level=0, sink=0):
    runtime = emu.SCRATCH + 0x1000
    ops = runtime + 0x1000
    defaults = emu.SCRATCH + 0x4000
    ops_image = bytearray(0x3c)
    ops_image[0x20:0x24] = defaults.to_bytes(4, "little")
    ops_image[0x30:0x34] = (0x00080001).to_bytes(4, "little")
    ops_image[0x34:0x38] = (0x00080005).to_bytes(4, "little")
    ops_image[0x38:0x3c] = (0x00080009).to_bytes(4, "little")
    image = bytearray((index * 17 + 3) & 0xff for index in range(0x800))
    if slot < 4:
        image[slot * 0x200] = marker
    args = {0: operation, 1: slot, 2: 0x13579bdf}
    memory = [
        (runtime, bytes(0x1000)), (ops, bytes(ops_image)),
        (defaults, bytes((index * 29 + 5) & 0xff for index in range(0x600))),
        (0x00087bf0, (0x2468ace0).to_bytes(4, "little")),
        (0x20018465, bytes(image)),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]
    oracles = {0: {0: int(queue_result)}}
    writes = {}
    if queue_result != 0 or operation not in (1, 2) or slot > 3:
        return args, memory, oracles, writes

    ready_ordinal = 2 if operation == 2 else 1
    oracles[ready_ordinal] = {0: int(ready)}
    if not ready:
        return args, memory, oracles, writes

    if operation == 1:
        oracles.update({3: {0: runtime}, 4: {0: runtime},
                        5: {0: int(read_result)}})
        if read_result != 0:
            return args, memory, oracles, writes
        writes[5] = [(2, 0, bytes(image), 0x00080000)]
        if marker != 0xaa:
            oracles.update({6: {0: runtime}, 8: {0: runtime},
                            11: {0: runtime}, 12: {0: runtime},
                            13: {0: int(erase_result)}})
            if erase_result == 0:
                oracles.update({14: {0: runtime}, 15: {0: runtime},
                                16: {0: int(write_result)}})
        else:
            oracles.update({6: {0: runtime}, 7: {0: int(header_compare)},
                            8: {0: runtime}, 9: {0: int(tail_compare)}})
            if header_compare == 0 and tail_compare == 0:
                return args, memory, oracles, writes
    else:
        oracles.update({4: {0: runtime}, 5: {0: runtime},
                        6: {0: int(read_result)}})
        if read_result != 0:
            return args, memory, oracles, writes
        writes[6] = [(2, 0, bytes(image), 0x00080000)]
        oracles.update({8: {0: runtime}, 9: {0: runtime},
                        10: {0: int(erase_result)}})
        if erase_result == 0:
            oracles.update({11: {0: runtime}, 12: {0: runtime},
                            13: {0: int(write_result)}})
    return args, memory, oracles, writes


REVIEWED_ORACLE_CASES[("app", 0x00024684)] = [
    _slot_update_case(queue_result=-5),
    _slot_update_case(queue_result=-5, level=1),
    _slot_update_case(queue_result=-5, level=1, sink=1),
    _slot_update_case(operation=0),
    _slot_update_case(operation=1, slot=4),
    _slot_update_case(operation=2, slot=4, level=1),
    _slot_update_case(ready=0),
    _slot_update_case(read_result=-7),
    _slot_update_case(operation=1, slot=2, marker=0),
    _slot_update_case(operation=1, marker=0, erase_result=-8),
    _slot_update_case(operation=1, marker=0, write_result=-9),
    _slot_update_case(operation=1, slot=1, marker=0xaa),
    _slot_update_case(operation=2, erase_result=-8),
]


REVIEWED_ORACLE_CASES[("app", 0x0002eb40)] = [
    ({2: 0x11223344, 3: 0x55667788},
     [(0x20018da6, b"\x05"), (0x20018da5, b"\x05"),
      (0x20007554, bytes(4))], {}),
    ({2: 0x11223344, 3: 0x55667788},
     [(0x20018da6, b"\x06"), (0x20018da5, b"\x05"),
      (0x20007554, bytes(4))], {}),
    ({2: 0x11223344, 3: 0x55667788},
     [(0x20018da6, b"\x06"), (0x20018da5, b"\x05"),
      (0x20007554, (1).to_bytes(4, "little"))], {}),
]


def _codec_test_case(kind):
    """Reviewed allocator/encoder outcomes for the LC3 integration test."""
    input_buffer = emu.SCRATCH + 0x3000
    vtable = emu.SCRATCH + 0x1800
    codec = bytearray(12)
    codec[0:4] = (0x13579bdf).to_bytes(4, "little")
    codec[8:12] = vtable.to_bytes(4, "little")
    methods = bytearray(8)
    methods[4:8] = (0x00080001).to_bytes(4, "little")
    memory = [
        (0x00087bf0, bytes(codec)),
        (0x00087bf8, vtable.to_bytes(4, "little")),
        (vtable, bytes(methods)),
        (0x2000230c, (3).to_bytes(4, "little")),
        (0x20007554, bytes(4)),
        (0x20007b78, bytes(4)),
        (0x20002404, (0x1000).to_bytes(4, "little")),
        (input_buffer, bytes(0x100)),
    ]
    # Deterministic real helper results: frame bytes=2600, encoded samples=160.
    oracles = {0: {0: 2600}, 1: {0: 160}}
    writes = {}
    if kind == "alloc-failure":
        oracles.update({2: {0: 0}, 3: {0: 0x2222}, 4: {0: 0x3333}})
    else:
        oracles.update({2: {0: 0x1111}, 3: {0: 0x2222}, 4: {0: 0x3333}})
        if kind == "ready-shortcut":
            oracles.update({5: {0: 1}, 6: {0: 0}})
        else:
            oracles.update({5: {0: 0}, 6: {0: 0x2468},
                            7: {0: 0}, 8: {0: 0}})
            if kind == "direct-finish":
                oracles[9] = {0: 0}
            elif kind == "statistics-finish":
                oracles[9] = {0: 0}
                memory.append((0x20007b78, (1).to_bytes(4, "little")))
                writes[10] = [(0, 0, bytes.fromhex("3412000078560000"),
                               0x0004a4d0)]
            elif kind == "callback-success":
                oracles.update({9: {0: 1}, 10: {0: 0}})
            elif kind == "callback-error":
                oracles.update({9: {0: 1}, 10: {0: 7}})
            elif kind == "callback-edge":
                oracles.update({9: {0: 1}, 10: {0: 0}})
                memory.append((0x20002404, (0x40ffff).to_bytes(4, "little")))
            elif kind == "callback-threshold":
                oracles[9] = {0: 1}
                memory.append((0x20002404, (0x410000).to_bytes(4, "little")))
            else:
                raise AssertionError(kind)
    return ({0: input_buffer, 1: 640}, memory, oracles, writes)


# Drive allocation cleanup, the ready shortcut, two encoder-loop backedges,
# both completion modes, atomic fallback/statistics, callback success/error,
# and the exact 0x410000 output-address boundary.
REVIEWED_ORACLE_CASES[("app", 0x0002ed68)] = [
    _codec_test_case("alloc-failure"),
    _codec_test_case("ready-shortcut"),
    _codec_test_case("direct-finish"),
    _codec_test_case("statistics-finish"),
    _codec_test_case("callback-success"),
    _codec_test_case("callback-error"),
    _codec_test_case("callback-edge"),
    _codec_test_case("callback-threshold"),
]


def _fault_decode_case(status, clear_precise=False):
    """Concrete SCB fault state and caller-owned output byte."""
    output = emu.SCRATCH + 0x1000
    return (
        {0: int(clear_precise), 1: output},
        [(output, b"\xa5"),
         (0xe000ed28, int(status).to_bytes(4, "little")),
         (0xe000ed38, (0x12345678).to_bytes(4, "little"))],
        {},
    )


# One no-fault case plus every decoded CFSR bit.  The two precise-bus cases
# distinguish reporting BFAR from the caller-requested bit clear.
REVIEWED_ORACLE_CASES[("app", 0x00050558)] = [
    _fault_decode_case(0),
    _fault_decode_case(1 << 12),
    _fault_decode_case(1 << 11),
    _fault_decode_case(1 << 9),
    _fault_decode_case((1 << 9) | (1 << 15), False),
    _fault_decode_case((1 << 9) | (1 << 15), True),
    _fault_decode_case(1 << 10),
    _fault_decode_case(1 << 8),
    _fault_decode_case(1 << 13),
]


REVIEWED_ORACLE_CASES[("app", 0x00050c24)] = [
    ({0: 0x35}, [], {}),
]


def _partition_walk_case(kind, first=1, second=1, transfer=0):
    """One production partition entry and its MPU register state."""
    table = emu.SCRATCH + 0x1000
    start = 0x1000
    length = 0x20
    count = 1
    limit = 4
    s9c = start
    sa0 = start
    if kind == "empty-count":
        count = 0
    elif kind == "empty-entry":
        length = 0
    elif kind == "short-entry":
        length = 0x10
    elif kind == "misaligned-entry":
        start += 1
    elif kind in ("lookup-mismatch", "lookup-invalid", "lookup-high"):
        pass
    elif kind == "same-start-split":
        sa0 = 0x2000
    elif kind in ("new-start-join", "descriptor", "fallback"):
        s9c = 0x2000
        if kind in ("descriptor", "fallback"):
            sa0 = 0x2000
    elif kind != "same-region":
        raise AssertionError(kind)
    entry = (int(start).to_bytes(4, "little") +
             int(length).to_bytes(4, "little") + bytes(4))
    memory = [
        (table, entry),
        (0xe000ed98, bytes(4)),
        (0xe000ed9c, int(s9c).to_bytes(4, "little")),
        (0xe000eda0, int(sa0).to_bytes(4, "little")),
    ]
    oracles = {}
    if kind not in ("empty-count", "empty-entry", "short-entry",
                    "misaligned-entry"):
        oracles = {0: {0: int(first)}, 1: {0: int(second)}}
        if kind == "lookup-mismatch":
            oracles[1] = {0: int(second + 1)}
        elif kind == "lookup-invalid":
            oracles[0] = {0: -0x16}
            oracles[1] = {0: -0x16}
        elif kind == "lookup-high":
            oracles[0] = {0: limit}
            oracles[1] = {0: limit}
        else:
            oracles[2] = {0: int(transfer)}
            if kind in ("descriptor", "fallback") and transfer != -0x16:
                oracles[3] = {0: 5 if kind == "descriptor" else -0x16}
    return ({0: table, 1: count, 2: limit}, memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x00050c54)] = [
    _partition_walk_case("empty-count"),
    _partition_walk_case("empty-entry"),
    _partition_walk_case("short-entry"),
    _partition_walk_case("misaligned-entry"),
    _partition_walk_case("lookup-mismatch"),
    _partition_walk_case("lookup-invalid"),
    _partition_walk_case("lookup-high"),
    _partition_walk_case("same-region", transfer=2),
    _partition_walk_case("same-start-split", transfer=-0x16),
    _partition_walk_case("new-start-join", transfer=3),
    _partition_walk_case("descriptor", transfer=1),
    _partition_walk_case("fallback", transfer=7),
]


def _decoder_case(kind):
    """Production image request, output record, and storage lookup state."""
    request = emu.SCRATCH + 0x1000
    output = emu.SCRATCH + 0x1100
    image = emu.SCRATCH + 0x1200
    storage = emu.SCRATCH + 0x2000
    words = [0, 0, 0x100, image, 0x40, 0x55, 0, 0]
    global_words = [0xffffffff, 2, 0x200, 0]
    capacity = 0x200
    oracles = {}
    writes = {0: [(0, 0, bytes(24), 0x00086c78)]}

    if kind == "missing-mode":
        words[1] = -1
    elif kind in ("cached", "cached-short"):
        words[1] = 2
        if kind == "cached-short":
            global_words[2] = 0x20
    elif kind == "short-input":
        words[4] = 0x1f
    elif kind == "missing-address":
        words[2] = -1
    elif kind == "bad-magic":
        pass
    elif kind == "large-fragment":
        words[6] = 0x21
    elif kind == "resume":
        words[6] = 1
        global_words[0] = 1
        global_words[3] = 1
        oracles[1] = {0: 0}
    elif kind in ("fatal-channel", "open-failure", "allocation-failure",
                  "lookup-failure", "capacity-failure", "auth-failure",
                  "auth-present", "success"):
        oracles[1] = {0: 4 if kind == "fatal-channel" else 2}
        if kind != "fatal-channel":
            oracles[2] = {0: 1 if kind == "open-failure" else 0}
            if kind != "open-failure":
                oracles[3] = {0: -1 if kind == "allocation-failure" else 3}
                if kind != "allocation-failure":
                    oracles[4] = {0: 7 if kind == "lookup-failure" else 0}
                    writes[4] = [(1, 0, storage.to_bytes(4, "little"),
                                  0x0004e048)]
                    if kind == "capacity-failure":
                        capacity = 0x80
                    elif kind in ("auth-failure", "auth-present"):
                        words[7] = 1
                        oracles[6] = {0: 1 if kind == "auth-failure" else 0}
                        if kind == "auth-present":
                            oracles[7] = {0: 0}
    else:
        raise AssertionError(kind)

    request_bytes = b"".join(
        int(value & 0xffffffff).to_bytes(4, "little") for value in words)
    global_bytes = b"".join(
        int(value & 0xffffffff).to_bytes(4, "little")
        for value in global_words)
    image_bytes = bytearray(0x40)
    image_bytes[0:4] = ((0 if kind == "bad-magic" else 0x96f3b83d)
                        .to_bytes(4, "little"))
    storage_bytes = bytearray(0x20)
    storage_bytes[8:12] = int(capacity).to_bytes(4, "little")
    return (
        {0: request, 1: output},
        [(request, request_bytes), (output, bytes(24)),
         (image, bytes(image_bytes)), (storage, bytes(storage_bytes)),
         (0x2000ab7c, global_bytes)],
        oracles, writes,
    )


REVIEWED_ORACLE_CASES[("app", 0x000518a8)] = [
    _decoder_case("missing-mode"),
    _decoder_case("cached"),
    _decoder_case("cached-short"),
    _decoder_case("short-input"),
    _decoder_case("missing-address"),
    _decoder_case("bad-magic"),
    _decoder_case("large-fragment"),
    _decoder_case("resume"),
    _decoder_case("fatal-channel"),
    _decoder_case("open-failure"),
    _decoder_case("allocation-failure"),
    _decoder_case("lookup-failure"),
    _decoder_case("capacity-failure"),
    _decoder_case("auth-failure"),
    _decoder_case("auth-present"),
    _decoder_case("success"),
]


def _command_parser_case(kind):
    """Bounded wire command and queue/handler objects for FUN_000513e8."""
    context = emu.SCRATCH + 0x1000
    packet = emu.SCRATCH + 0x1100
    wire = emu.SCRATCH + 0x1200
    slot = emu.SCRATCH + 0x1300
    state = emu.SCRATCH + 0x1400
    owner = emu.SCRATCH + 0x1500
    handlers = emu.SCRATCH + 0x1600
    length = 16
    payload_length = 0
    flags = 0
    pending = 0
    oracles = {}

    if kind == "empty":
        length = 0
    elif kind == "short":
        length = 7
    elif kind == "payload-too-large":
        length = 8
        payload_length = 9
        oracles[0] = {0: 0}
        cleanup = 1
    elif kind == "flag-error":
        flags = 1
        oracles[0] = {0: 0}
        cleanup = 1
    elif kind == "allocation-failure":
        oracles.update({0: {0: 0}, 1: {0: 0}})
        cleanup = 2
    elif kind == "type-error":
        flags = 0x10
        oracles.update({0: {0: 0}, 1: {0: 0x2468}, 2: {0: 0}})
        cleanup = 4
    elif kind in ("lookup-null", "callback-missing", "lock-failure",
                  "callback-error", "unlock-failure", "handler-missing"):
        oracles.update({0: {0: 0}, 1: {0: 0x2468}, 2: {0: 0},
                        3: {0: 0}})
        if kind == "lookup-null":
            oracles[4] = {0: 0}
            cleanup = 5
        else:
            oracles[4] = {0: handlers}
            if kind == "callback-missing":
                cleanup = 5
            elif kind == "lock-failure":
                oracles[5] = {0: 0}
                cleanup = 6
            else:
                oracles[5] = {0: 1}
                oracles[6] = {0: 7 if kind == "callback-error" else 0}
                if kind == "callback-error":
                    oracles[7] = {0: 1}
                    cleanup = 8
                else:
                    oracles[7] = {0: 0 if kind == "unlock-failure" else 1}
                    if kind == "unlock-failure":
                        cleanup = 8
                    else:
                        pending = 0x20
                        oracles[8] = {0: 0}
                        cleanup = 9
    else:
        raise AssertionError(kind)

    if kind not in ("empty", "short"):
        # Entering the common error publisher: FUN_00080830 precedes the
        # state+4 lock, whose zero result selects the bounded fast cleanup.
        oracles[cleanup + 1] = {0: 0}
    if kind == "allocation-failure":
        # Exercise the real two-word error publication before releasing the
        # state lock; a zero publisher result selects the bounded fast exit.
        oracles[cleanup + 1] = {0: 1}
        oracles[cleanup + 2] = {0: 0}

    command = bytearray(8)
    command[0] = flags
    command[2:4] = int(payload_length).to_bytes(2, "big")
    command[4:6] = (0x1234).to_bytes(2, "big")
    command[7] = 0x56
    packet_bytes = bytearray(0x20)
    packet_bytes[0x0c:0x10] = wire.to_bytes(4, "little")
    packet_bytes[0x10:0x12] = int(length).to_bytes(2, "little")
    context_bytes = (owner.to_bytes(4, "little") +
                     slot.to_bytes(4, "little") +
                     state.to_bytes(4, "little"))
    state_bytes = bytearray(0x80)
    state_bytes[0x36:0x38] = int(pending).to_bytes(2, "little")
    handler_bytes = bytearray(8)
    if kind not in ("callback-missing", "lookup-null"):
        handler_bytes[0:4] = (0x00080001).to_bytes(4, "little")
    return (
        {0: context, 1: packet},
        [(context, context_bytes), (packet, bytes(packet_bytes)),
         (wire, bytes(command)), (slot, bytes(4)),
         (state, bytes(state_bytes)), (owner, bytes(0x40)),
         (handlers, bytes(handler_bytes))],
        oracles,
    )


REVIEWED_ORACLE_CASES[("app", 0x000513e8)] = [
    _command_parser_case("empty"),
    _command_parser_case("short"),
    _command_parser_case("payload-too-large"),
    _command_parser_case("flag-error"),
    _command_parser_case("allocation-failure"),
    _command_parser_case("type-error"),
    _command_parser_case("lookup-null"),
    _command_parser_case("callback-missing"),
    _command_parser_case("lock-failure"),
    _command_parser_case("callback-error"),
    _command_parser_case("unlock-failure"),
]


def _event_callback_case(length, installed=True):
    obj = emu.SCRATCH + 0x1000
    payload = emu.SCRATCH + 0x1100
    state = bytearray(0x20)
    if installed:
        state[0x1c:0x20] = (0x00080001).to_bytes(4, "little")
    return (
        {0: 0x35, 1: obj, 2: payload, 3: int(length)},
        [(obj, bytes(state)), (payload, bytes.fromhex("34127856"))],
        {},
    )


REVIEWED_ORACLE_CASES[("app", 0x0007f894)] = [
    _event_callback_case(4, installed=False),
    _event_callback_case(3),
    _event_callback_case(4),
    _event_callback_case(5),
]


def _mpu_region_case(index):
    region = emu.SCRATCH + 0x1000
    raw = bytearray(12)
    raw[0:4] = (0x1234).to_bytes(4, "little")
    raw[4:8] = (0x80).to_bytes(4, "little")
    raw[8:10] = (0x15).to_bytes(2, "little")
    raw[10:12] = (3).to_bytes(2, "little")
    return ({0: int(index), 1: region}, [(region, bytes(raw))], {})


REVIEWED_ORACLE_CASES[("app", 0x00080798)] = [
    _mpu_region_case(0), _mpu_region_case(7),
    _mpu_region_case(8), _mpu_region_case(0xff),
]


def _field_decode_case(kind):
    input_object = emu.SCRATCH + 0x1000
    fields = emu.SCRATCH + 0x1100
    destination = emu.SCRATCH + 0x1200
    count_output = emu.SCRATCH + 0x1300
    field_count = 1
    identifier = 0x11223344
    item_kind = 7
    field_kind = 7
    decoded = 0
    oracles = {0: {0: 1}}
    writes = {}

    if kind == "init-failure":
        oracles[0] = {0: 0}
    elif kind in ("end-success", "end-failure"):
        field_count = 0
        oracles.update({1: {0: 0}, 2: {0: 1 if kind == "end-success" else 0}})
        writes[1] = [(1, 0, bytes(8), 0x00085f9c)]
    else:
        item = identifier.to_bytes(4, "little") + item_kind.to_bytes(4, "little")
        oracles[1] = {0: 1}
        writes[1] = [(1, 0, item, 0x00085f9c)]
        if kind == "unknown-skip":
            field_kind = 8
            oracles.update({2: {0: 0}, 3: {0: 1}})
        else:
            oracles[2] = {0: 0}
            if kind == "duplicate":
                decoded = 1
            elif kind == "decoder-failure":
                oracles[3] = {0: 0}
            elif kind == "decoder-success":
                oracles.update({3: {0: 1}, 4: {0: 0}, 5: {0: 1}})
            else:
                raise AssertionError(kind)

    field = bytearray(20)
    field[0:4] = identifier.to_bytes(4, "little")
    field[4:8] = field_kind.to_bytes(4, "little")
    field[8:12] = (0x00080001).to_bytes(4, "little")
    field[12:16] = destination.to_bytes(4, "little")
    field[16] = decoded
    return (
        {0: input_object, 1: fields, 2: field_count, 3: count_output},
        [(input_object, bytes(0x40)), (fields, bytes(field)),
         (destination, bytes(0x20)), (count_output, bytes(4))],
        oracles, writes,
    )


REVIEWED_ORACLE_CASES[("app", 0x00080872)] = [
    _field_decode_case("init-failure"),
    _field_decode_case("end-success"),
    _field_decode_case("end-failure"),
    _field_decode_case("unknown-skip"),
    _field_decode_case("duplicate"),
    _field_decode_case("decoder-failure"),
    _field_decode_case("decoder-success"),
]


def _lookup_byte_case(selector, mapped, result, byte_value):
    oracles = {}
    index = 0
    base = int(selector)
    if selector > 3:
        oracles[0] = {0: 2}
        base = 2
        index = 1
    oracles[index] = {0: int(mapped)}
    oracles[index + 1] = {0: int(result)}
    writes = {index + 1: [(1, 0, bytes((int(byte_value) & 0xff,)),
                           0x000809b0)]}
    return ({0: int(selector), 1: 0x00abcdef, 2: 0x2468ace0},
            [], oracles, writes)


REVIEWED_ORACLE_CASES[("app", 0x000809f6)] = [
    _lookup_byte_case(2, 0, 2, 1),
    _lookup_byte_case(2, 3, 2, 3),
    _lookup_byte_case(2, 3, 4, 0),
    _lookup_byte_case(2, 2, 4, 1),
    _lookup_byte_case(2, 3, 4, 1),
    _lookup_byte_case(4, 2, 4, 2),
]

# Queue-empty, queued-item retry, terminal release, and deferred retry are all
# selected by memory/callee state rather than entry arguments.  Keep a valid
# item/resource graph in every executing case so the halfword dereference is a
# production-shaped input rather than random mapped RAM.
_dispatch_owner = emu.SCRATCH + 0x1000
_dispatch_item = emu.SCRATCH + 0x2000
_dispatch_resource = emu.SCRATCH + 0x3000
_dispatch_item_memory = [
    (_dispatch_item + 0x18, _dispatch_resource.to_bytes(4, "little")),
    (_dispatch_resource, (7).to_bytes(2, "little")),
]
REVIEWED_ORACLE_CASES[("app", 0x000818dc)] = [
    ({0: _dispatch_owner, 1: 0},
     [(_dispatch_owner - 4, (0).to_bytes(4, "little"))],
     {0: {0: 0}}),
    ({0: _dispatch_owner, 1: 0},
     [(_dispatch_owner - 4, (0).to_bytes(4, "little")),
      *_dispatch_item_memory],
     {0: {0: _dispatch_item}, 1: {0: 0xfffffff5}}),
    ({0: _dispatch_owner, 1: 0},
     [(_dispatch_owner - 4, _dispatch_item.to_bytes(4, "little")),
      *_dispatch_item_memory],
     {0: {0: 0xfffffff5}}),
    ({0: _dispatch_owner, 1: 0},
     [(_dispatch_owner - 4, _dispatch_item.to_bytes(4, "little")),
      *_dispatch_item_memory],
    {0: {0: 0xfffffff4}}),
]

# Pair the three public NULL guards with transform/decode failure and success.
# The helpers' complete local output fixtures are supplied by the reviewed
# target-bound writes above.
_key_a = emu.SCRATCH + 0x4100
_key_b = emu.SCRATCH + 0x4200
_decoded_key = emu.SCRATCH + 0x4300
REVIEWED_ORACLE_CASES[("app", 0x00081326)] = [
    ({0: 0, 1: _key_b, 2: _decoded_key}, [], {}),
    ({0: _key_a, 1: 0, 2: _decoded_key}, [], {}),
    ({0: _key_a, 1: _key_b, 2: 0}, [], {}),
    ({0: _key_a, 1: _key_b, 2: _decoded_key}, [], {1: {0: 0}}),
    ({0: _key_a, 1: _key_b, 2: _decoded_key}, [],
     {1: {0: 1}, 3: {0: 0}}),
    ({0: _key_a, 1: _key_b, 2: _decoded_key}, [],
     {1: {0: 1}, 3: {0: 1}}),
]

# Preserve the entry opcode guard alongside allocation failure and a complete
# successful four-byte payload publication.
REVIEWED_ORACLE_CASES[("app", 0x000821f4)] = [
    ({1: 0}, [], {}),
    ({1: 1}, [], {0: {0: 0}}),
    ({1: 1}, [],
     {0: {0: emu.SCRATCH + 0x4400},
      1: {0: emu.SCRATCH + 0x4500}}),
]

def _log_globals(level, sink):
    return [
        (0x2000230c, int(level).to_bytes(4, "little", signed=True)),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]


# Each index cleaner always performs its two byte clears, then independently
# gates the diagnostic by level and sink implementation.
for _clean_va in (0x00037154, 0x00037234):
    REVIEWED_ORACLE_CASES[("app", _clean_va)] = [
        ({}, _log_globals(2, 0), {}),
        ({}, _log_globals(3, 0), {}),
        ({}, _log_globals(3, 1), {}),
    ]

# Queue cleanup has a callee-owned success selector in addition to the two
# global logging gates.
REVIEWED_ORACLE_CASES[("app", 0x0002ec1c)] = [
    ({}, _log_globals(1, 0), {0: {0: 0}}),
    ({}, _log_globals(0, 0), {0: {0: 1}}),
    ({}, _log_globals(1, 0), {0: {0: 1}}),
    ({}, _log_globals(1, 1), {0: {0: 1}}),
]


def _whitelist_state(count, sink=0, flags=0x1f):
    data = bytearray(2 + 0x38 * max(count, 1))
    data[0] = flags
    data[1] = count
    for i in range(count):
        start = 2 + i * 0x38
        data[start:start + 0x38] = bytes(
            (i * 43 + j * 7 + 3) & 0xff for j in range(0x38))
    return [(0x20007554, int(sink).to_bytes(4, "little")),
            (0x2001a22c, bytes(data))]


# Allocation failures at every level, empty-list success, item failure, and a
# complete one-item success cover all callee-owned branch selectors without
# allowing a random whitelist count to manufacture an unbounded loop.
_wl_root = emu.SCRATCH + 0x5000
_wl_object = emu.SCRATCH + 0x5100
_wl_array = emu.SCRATCH + 0x5200
_wl_item = emu.SCRATCH + 0x5300
_wl_json = emu.SCRATCH + 0x5400
REVIEWED_ORACLE_CASES[("app", 0x000352e8)] = [
    ({0: 0, 1: 0x11223344, 2: 0x55667788, 3: 0x99aabbcc},
     _whitelist_state(0, 0), {}),
    ({0: 0, 1: 0x11223344, 2: 0x55667788, 3: 0x99aabbcc},
     _whitelist_state(0, 1), {}),
    ({0: 1}, _whitelist_state(0), {0: {0: 0}}),
    ({0: 1}, _whitelist_state(0),
     {0: {0: _wl_root}, 5: {0: 0}}),
    ({0: 1}, _whitelist_state(0),
     {0: {0: _wl_root}, 5: {0: _wl_object}, 7: {0: 0}}),
    ({0: 1}, _whitelist_state(0),
     {0: {0: _wl_root}, 5: {0: _wl_object}, 7: {0: _wl_array},
      10: {0: _wl_json}, 13: {0: 0x1234}}),
    ({0: 1}, _whitelist_state(1),
     {0: {0: _wl_root}, 5: {0: _wl_object}, 7: {0: _wl_array},
      8: {0: 0}}),
    ({0: 1}, _whitelist_state(1),
     {0: {0: _wl_root}, 5: {0: _wl_object}, 7: {0: _wl_array},
      8: {0: _wl_item}, 14: {0: _wl_json}, 17: {0: 0x1234}}),
]

# ANCS startup is a finite initializer in production, but random oracle
# returns manufacture either a 50-iteration readiness wait or the fatal reboot
# loop.  These cases bind every real initializer result and keep the device
# readiness byte at an explicit object address.  Error cases stop at the
# production-noreturn sys_reboot boundary below.
_ancs_device_info = emu.SCRATCH + 0x7000
_ancs_context = emu.SCRATCH + 0x9000


def _ancs_startup_state(log_level=0, alt_sink=0, ready=True):
    return [
        (0x2000230c, int(log_level).to_bytes(4, "little")),
        (0x20007554, int(alt_sink).to_bytes(4, "little")),
        (_ancs_device_info + 0x1058, bytes((bool(ready),))),
    ]


def _ancs_startup_case(fail_at=None, log_level=0, alt_sink=0):
    # With a ready device and no initial diagnostic the initializer calls are:
    # device-info, bt_send, foreach-bond, settings-load, ANCS client,
    # discovery params, auth callbacks, auth-info callbacks, GATT callbacks,
    # notify sync, bt_start, and work-thread start.
    shift = 1 if log_level else 0
    result_ordinals = {
        "send": 1, "client": 4, "discovery": 5, "auth": 6,
        "auth_info": 7, "notify": 9, "bt_start": 10,
    }
    oracles = {shift: {0: _ancs_device_info}}
    for stage, ordinal in result_ordinals.items():
        oracles[shift + ordinal] = {0: 7 if stage == fail_at else 0}
        if stage == fail_at:
            break
    return ({0: _ancs_context},
            _ancs_startup_state(log_level, alt_sink), oracles)


def _ancs_wait_then_start_case():
    # One wait iteration: the exact delay call publishes device readiness,
    # after which the same accessor returns the same object and initialization
    # continues normally.
    oracles = {
        0: {0: _ancs_device_info}, 2: {0: _ancs_device_info},
        3: {0: 0}, 6: {0: 0}, 7: {0: 0}, 8: {0: 0},
        9: {0: 0}, 11: {0: 0}, 12: {0: 0},
    }
    writes = {1: [(None, _ancs_device_info + 0x1058, b"\x01",
                   0x0007c0a8)]}
    return ({0: _ancs_context}, _ancs_startup_state(ready=False),
            oracles, writes)


def _ancs_send_exhaustion_case():
    # Five failed bt_send attempts each revisit the readiness accessor.  The
    # firmware intentionally proceeds to client initialization after the
    # retry budget is exhausted.
    oracles = {}
    for base in (0, 5, 10, 15, 20):
        oracles[base] = {0: _ancs_device_info}
        oracles[base + 1] = {0: -5}
    # foreach/settings are 25/26; client through bt_start occupy 27..33.
    for ordinal in (27, 28, 29, 30, 32, 33):
        oracles[ordinal] = {0: 0}
    return ({0: _ancs_context}, _ancs_startup_state(), oracles)


REVIEWED_ORACLE_CASES[("app", 0x00019950)] = [
    _ancs_startup_case(),
    _ancs_startup_case(log_level=1, alt_sink=0),
    _ancs_startup_case(log_level=1, alt_sink=1),
    _ancs_wait_then_start_case(),
    _ancs_send_exhaustion_case(),
    *[_ancs_startup_case(stage) for stage in
      ("client", "discovery", "auth", "auth_info", "notify", "bt_start")],
]


# The flash checker is driven by CRC values written through calc_flash_crc's
# first argument.  A return-only oracle leaves the seed at 0xffff and proves
# only the first mismatch exit.  These fixtures publish a distinct
# intermediate and final CRC for all seven production regions.
_flash_signature_crcs = (0x0d59, 0xdab9, 0x1265, 0xdab9,
                         0xd412, 0xdab9, 0x2632)


def _flash_crc_write(value):
    return [(0, 0, int(value).to_bytes(2, "little"), 0x00022974)]


def _flash_check_state(log_level=0, alt_sink=0):
    return [(0x2000230c, int(log_level).to_bytes(4, "little")),
            (0x20007554, int(alt_sink).to_bytes(4, "little"))]


def _flash_check_success_case(log_level=0, alt_sink=0):
    high_log = log_level > 2
    oracles = {}
    writes = {}
    for index, expected in enumerate(_flash_signature_crcs):
        first = (1 + 3 * index) if high_log else (2 * index)
        second = first + 1
        oracles[first] = {0: 0}
        oracles[second] = {0: 0}
        writes[first] = _flash_crc_write(expected ^ 0xffff)
        writes[second] = _flash_crc_write(expected)
    return ({}, _flash_check_state(log_level, alt_sink), oracles, writes)


def _flash_check_retry_case(first_call_fails):
    # Level one observes the retry diagnostic without enabling the entry or
    # per-region CRC logs.  Calls 0..2 are failed CRC, delay, diagnostic; the
    # retried region begins at call three.
    oracles = {0: {0: -5 if first_call_fails else 0}}
    writes = {}
    if not first_call_fails:
        writes[0] = _flash_crc_write(0x2468)
        oracles[1] = {0: -5}
        retry_first = 4
    else:
        retry_first = 3
    # A second-call failure inserts one extra call before the delay/logger.
    retry_second = retry_first + 1
    oracles[retry_first] = {0: 0}
    oracles[retry_second] = {0: 0}
    writes[retry_first] = _flash_crc_write(0xf2a6)
    writes[retry_second] = _flash_crc_write(_flash_signature_crcs[0])
    next_call = retry_second + 1
    for expected in _flash_signature_crcs[1:]:
        oracles[next_call] = {0: 0}
        oracles[next_call + 1] = {0: 0}
        writes[next_call] = _flash_crc_write(expected ^ 0xffff)
        writes[next_call + 1] = _flash_crc_write(expected)
        next_call += 2
    return ({}, _flash_check_state(log_level=1), oracles, writes)


def _flash_check_exhaustion_case():
    # Six failed first reads; only the first five are followed by a delay.
    return ({}, _flash_check_state(),
            {ordinal: {0: -5} for ordinal in (0, 2, 4, 6, 8, 10)})


def _flash_check_mismatch_case():
    return ({}, _flash_check_state(), {0: {0: 0}, 1: {0: 0}},
            {0: _flash_crc_write(0x2468),
             1: _flash_crc_write(_flash_signature_crcs[0] ^ 1)})


REVIEWED_ORACLE_CASES[("app", 0x00032c28)] = [
    _flash_check_success_case(),
    _flash_check_success_case(log_level=3, alt_sink=0),
    _flash_check_success_case(log_level=3, alt_sink=1),
    _flash_check_retry_case(first_call_fails=True),
    _flash_check_retry_case(first_call_fails=False),
    _flash_check_exhaustion_case(),
    _flash_check_mismatch_case(),
]


def _message_table_contains_case(slot_count, message_id, entries=()):
    image = bytearray(max(1, int(slot_count)) * 0x1b4)
    for index, occupied, entry_id in entries:
        offset = int(index) * 0x1b4
        image[offset + 8:offset + 12] = int(entry_id).to_bytes(4, "little")
        image[offset + 0x10] = int(occupied) & 0xff
    return ({0: int(slot_count), 1: int(message_id)},
            [(0x20007dac, bytes(image))], {})


# Empty bound, inactive and wrong-id records, first/last matches, mixed misses,
# and the full production twenty-slot bound.  Nonuniform ids make the occupied
# byte, id offset, stride, comparison direction, and loop bound observable.
REVIEWED_ORACLE_CASES[("app", 0x00033f24)] = [
    _message_table_contains_case(0, 0x11223344),
    _message_table_contains_case(1, 0x11223344,
                                 [(0, 0, 0x11223344)]),
    _message_table_contains_case(1, 0x11223344,
                                 [(0, 1, 0x55667788)]),
    _message_table_contains_case(1, 0x11223344,
                                 [(0, 1, 0x11223344)]),
    _message_table_contains_case(4, 0x89abcdef,
                                 [(0, 1, 7), (1, 0, 0x89abcdef),
                                  (2, 1, 9), (3, 1, 0x89abcdef)]),
    _message_table_contains_case(4, 0x89abcdef,
                                 [(0, 1, 7), (1, 0, 0x89abcdef),
                                  (2, 1, 9), (3, 1, 11)]),
    _message_table_contains_case(20, 0x2468ace0,
                                 [(0, 1, 1), (10, 1, 2),
                                  (19, 1, 0x2468ace0)]),
]


_persist_status_context = emu.SCRATCH + 0x1000
_persist_status_record = emu.SCRATCH + 0x3000


def _persist_status_case(active_task, task_id, requested_status,
                         current_task=0x31, current_status=0,
                         saved_status=0, log_level=0, alt_sink=0,
                         context=_persist_status_context, busy_lock=False):
    record = (int(current_task).to_bytes(4, "little") +
              bytes((int(current_status) & 0xff, 0, 0, 0)))
    memory = [
        (context + 0xd5, bytes((int(active_task) & 0xff,))),
        (context + 0xf98, bytes((int(saved_status) & 0xff,))),
        (context + 0x1054, _persist_status_record.to_bytes(4, "little")),
        (_persist_status_record, record),
        (0x20018d9c, bytes((1 if busy_lock else 0,))),
        (0x20018d9d, b"\x5a"),
        (0x2000230c, int(log_level).to_bytes(4, "little")),
        (0x20007554, int(alt_sink).to_bytes(4, "little")),
    ]
    writes = ({0: [(0, 0, b"\x00", 0x0007cdf8)]}
              if busy_lock else {})
    return ({0: context, 1: int(task_id), 2: int(requested_status)},
            memory, {}, writes)


# Same-record short circuits, both idle values, active-task replacement,
# whitelist accept/reject boundaries, every status/log family, both sinks,
# the task-16 saved-status transfer, and one finite busy-lock iteration.
REVIEWED_ORACLE_CASES[("app", 0x0002bef4)] = [
    _persist_status_case(0, 7, 2, current_task=7, current_status=1),
    _persist_status_case(0, 7, 3, current_task=7, current_status=3),
    _persist_status_case(0, 0x10, 2, saved_status=1,
                         log_level=1, alt_sink=0),
    _persist_status_case(1, 5, 2),
    _persist_status_case(4, 4, 2),
    _persist_status_case(4, 5, 2),
    _persist_status_case(4, 0x11, 2),
    _persist_status_case(0, 8, 3),
    _persist_status_case(0, 9, 0),
    _persist_status_case(4, 8, 3, log_level=1, alt_sink=1),
    _persist_status_case(0, 6, 2, context=0x20018d9c, busy_lock=True),
]


# process_for_new_task is a long-lived state dispatcher.  Random object bytes
# turn most selector arms into polling loops, while its old source collapsed
# every direct callee into one oracle.  Give each of the complete 0..17 TBH
# slots an owned context graph and select the production cancellation/ready
# boundary so every state body reaches a finite handoff.
_new_task_context = emu.SCRATCH + 0x1000
_new_task_worker = emu.SCRATCH + 0x3000
_new_task_record = emu.SCRATCH + 0x4000


def _new_task_state_case(selector):
    context = bytearray(0x1100)
    worker = bytearray(0xa0)
    context[1] = 1                 # cancellation/transport-complete boundary
    context[0xd5] = selector & 0xff
    context[0xfea] = 10            # finite state-eight wait predicate
    worker[0] = 1 if selector in (1, 8) else 2
    worker[0x98:0x9c] = (0x00080001).to_bytes(4, "little")
    pointer_offsets = (0xff0, 0xffc, 0x1000, 0x1004, 0x1008, 0x100c,
                       0x1010, 0x1014, 0x1018, 0x101c, 0x1020, 0x1054)
    memory = [(_new_task_context, bytes(context)),
              (_new_task_worker, bytes(worker)),
              # Keep the bounded state cases on the production quiet-log
              # path. Diagnostic argument fidelity is recovered in the C,
              # but random verbosity words must not dominate state coverage.
              (0x2000230c, (0).to_bytes(4, "little")),
              (0x20007554, (0).to_bytes(4, "little"))]
    for index, offset in enumerate(pointer_offsets):
        target = (_new_task_record if offset == 0x1054 else
                  emu.SCRATCH + 0x5000 + index * 0x100)
        memory.append((_new_task_context + offset,
                       int(target).to_bytes(4, "little")))
        memory.append((target, bytes(0x40)))
    oracles = {}
    if selector == 0:
        # memset, clear-timeout, wake-state, then now_has_persist_task.
        oracles[3] = {0: 1, 1: 0}
    elif selector == 1:
        # State one immediately normalizes to state zero; bind the second
        # pass's task lookup so it takes the finite cancellation boundary.
        oracles[6] = {0: 1, 1: 0}
    elif selector in (4, 5):
        oracles[2] = {0: 10}
    return ({0: _new_task_context, 1: _new_task_worker}, memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x0002c99c)] = [
    _new_task_state_case(selector) for selector in range(18)
] + [_new_task_state_case(0xff)]


# The context accessor owns both branches after formatting: disabled byte,
# nonempty pending word, and the empty state that submits the work item.
_debug_context = emu.SCRATCH + 0x6000
REVIEWED_ORACLE_CASES[("app", 0x00019c70)] = [
    ({0: 0x000a0000, 1: 11, 2: 22, 3: 33},
     [(_debug_context + 0x248, b"\x01")],
     {0: {0: _debug_context}}),
    ({0: 0x000a0000, 1: 11, 2: 22, 3: 33},
     [(_debug_context + 0x248, b"\x00"),
      (_debug_context + 0x220, (1).to_bytes(4, "little"))],
     {0: {0: _debug_context}}),
    ({0: 0x000a0000, 1: 11, 2: 22, 3: 33},
     [(_debug_context + 0x248, b"\x00"),
      (_debug_context + 0x220, (0).to_bytes(4, "little"))],
     {0: {0: _debug_context}}),
]

# Audio cache lookup success, silent failure, and both diagnostic sinks.  The
# fifth queue argument remains the caller's real stacked capacity value.
REVIEWED_ORACLE_CASES[("app", 0x0002f460)] = [
    ({0: emu.SCRATCH + 0x1000, 3: 16}, _log_globals(1, 0),
     {0: {0: 0}}),
    ({0: emu.SCRATCH + 0x1000, 3: 16}, _log_globals(0, 0),
     {0: {0: 1}}),
    ({0: emu.SCRATCH + 0x1000, 3: 16}, _log_globals(1, 0),
     {0: {0: 1}}),
    ({0: emu.SCRATCH + 0x1000, 3: 16}, _log_globals(1, 1),
     {0: {0: 1}}),
]


def _index_get_state(level, sink, cache_address, value):
    return [*_log_globals(level, sink), (cache_address, bytes([value]))]


# Cached-byte publication is always performed; level and sink only gate the
# diagnostic.  Nonuniform values make the stock/news destination offsets live.
REVIEWED_ORACLE_CASES[("app", 0x0003719c)] = [
    ({}, _index_get_state(2, 0, 0x2001b814, 0xa5), {}),
    ({}, _index_get_state(3, 0, 0x2001b814, 0x5a), {}),
    ({}, _index_get_state(3, 1, 0x2001b814, 0xc3), {}),
]
REVIEWED_ORACLE_CASES[("app", 0x000370bc)] = [
    ({}, _index_get_state(2, 0, 0x2001b815, 0x96), {}),
    ({}, _index_get_state(3, 0, 0x2001b815, 0x69), {}),
    ({}, _index_get_state(3, 1, 0x2001b815, 0x3c), {}),
]

# Clock conversion's 64-bit input and quotient are both callee-owned.  Pin a
# concrete tick pair and three distinct quotients around a nonzero boot base.
REVIEWED_ORACLE_CASES[("app", 0x0004a51c)] = [
    ({}, [*_log_globals(2, 0),
          (0x2000a0b0, (100).to_bytes(4, "little"))],
     {0: {0: 0x55667788, 1: 0x11223344}, 1: {0: 125}}),
    ({}, [*_log_globals(3, 0),
          (0x2000a0b0, (100).to_bytes(4, "little"))],
     {0: {0: 0x55667788, 1: 0x11223344}, 1: {0: 150}}),
    ({}, [*_log_globals(3, 1),
          (0x2000a0b0, (100).to_bytes(4, "little"))],
     {0: {0: 0x55667788, 1: 0x11223344}, 1: {0: 175}}),
]

# Charge-state logging deliberately changes the volatile byte in both logged
# cases.  The firmware must reload after the sink returns before publishing.
REVIEWED_ORACLE_CASES[("app", 0x00032784)] = [
    ({}, [*_log_globals(2, 0), (0x20019ef4, b"\x80")], {}, {}),
    ({}, [*_log_globals(3, 0), (0x20019ef4, b"\x80")], {},
     {0: [(None, 0x20019ef4, b"\x00", 0x0007dda4)]}),
    ({}, [*_log_globals(3, 1), (0x20019ef4, b"\x00")], {},
     {0: [(None, 0x20019ef4, b"\x80", 0x00019c70)]}),
]

_panel = emu.SCRATCH + 0x7000
_panel_memory = [(_panel + 0x369, b"\x07")]
REVIEWED_ORACLE_CASES[("app", 0x00047638)] = [
    ({0: _panel, 2: 0x33445566, 3: 0x778899aa},
     [*_log_globals(2, 0), *_panel_memory], {}),
    ({0: _panel, 2: 0x33445566, 3: 0x778899aa},
     [*_log_globals(3, 0), *_panel_memory], {}),
    ({0: _panel, 2: 0x33445566, 3: 0x778899aa},
     [*_log_globals(3, 1), *_panel_memory], {}),
]
REVIEWED_ORACLE_CASES[("app", 0x000475f0)] = [
    ({0: 0x11223344, 1: 0x55667788, 2: 0x99aabbcc},
     _log_globals(2, 0), {}),
    ({0: 0x11223344, 1: 0x55667788, 2: 0x99aabbcc},
     _log_globals(3, 0), {}),
    ({0: 0x11223344, 1: 0x55667788, 2: 0x99aabbcc},
     _log_globals(3, 1), {}),
]

# Panel initialization's controller-id result selects success, silent failure,
# and both fixed-string diagnostic sinks.
REVIEWED_ORACLE_CASES[("app", 0x00046fc0)] = [
    ({0: _panel}, [*_log_globals(2, 0), *_panel_memory],
     {2: {0: 0x4010}}),
    ({0: _panel}, [*_log_globals(2, 0), *_panel_memory],
     {2: {0: 0x400f}}),
    ({0: _panel}, [*_log_globals(3, 0), *_panel_memory],
     {2: {0: 0x400f}}),
    ({0: _panel}, [*_log_globals(3, 1), *_panel_memory],
     {2: {0: 0x400f}}),
]


def _burial_record(valid):
    record = bytearray((i * 13 + 5) & 0xff for i in range(0xc0))
    record[0x14:0x16] = ((3 if valid else 0xffff)
                         .to_bytes(2, "little"))
    record[0x16] = 1 if valid else 0
    return bytes(record)


_burial_app = emu.SCRATCH + 0x8000
REVIEWED_ORACLE_CASES[("app", 0x000230e0)] = [
    ({0: _burial_app, 3: 0x12345678}, _log_globals(1, 0),
     {0: {0: 1}}),
    ({0: _burial_app, 3: 0x12345678}, _log_globals(2, 0),
     {0: {0: 1}}),
    ({0: _burial_app, 3: 0x12345678}, _log_globals(2, 1),
     {0: {0: 1}}),
    ({0: _burial_app, 3: 0x12345678}, [], {0: {0: 0}},
     {0: [(1, 0, _burial_record(True), 0x000225b4)]}),
    ({0: _burial_app, 3: 0x12345678}, [],
     {0: {0: 0}, 1: {0: 0x55667788}},
     {0: [(1, 0, _burial_record(False), 0x000225b4)]}),
]


def _settings_record(version, tables=False, boundary=False):
    data = bytearray(0x84)
    data[0:4] = int(version).to_bytes(4, "little")
    data[8] = 2
    data[12:16] = (0x11223344).to_bytes(4, "little")
    data[16:20] = (0x55667788).to_bytes(4, "little")
    data[20] = 2
    if tables:
        data[21:53] = bytes((i * 7 + 3) & 0xff for i in range(32))
        data[53:85] = bytes((i * 11 + 5) & 0xff for i in range(32))
    else:
        data[21] = 0xff
        data[53] = 0xff
    data[85:87] = b"\x5a\xa5"
    data[96:98] = ((0 if boundary else 0x16).to_bytes(2, "little"))
    data[98:100] = ((0x41 if boundary else 4).to_bytes(2, "little"))
    for offset, value in ((100, 0x10111213), (104, 0x20212223),
                          (108, 0x30313233), (112, 0x40414243)):
        data[offset:offset + 4] = value.to_bytes(4, "little")
    data[116:118] = (0x20).to_bytes(2, "little")
    data[118:120] = (0x21).to_bytes(2, "little")
    data[120:122] = ((0 if boundary else 1).to_bytes(2, "little"))
    data[124:128] = ((0xffffffff if boundary else 5)
                     .to_bytes(4, "little"))
    data[128:132] = (0x51525354).to_bytes(4, "little")
    return bytes(data)


_settings_app = emu.SCRATCH + 0x9000
REVIEWED_ORACLE_CASES[("app", 0x00022bd0)] = [
    ({0: _settings_app}, _log_globals(2, 0), {1: {0: 1}}),
    ({0: _settings_app}, _log_globals(2, 1), {1: {0: 1}}),
    ({0: _settings_app}, _log_globals(1, 0), {1: {0: 0}},
     {1: [(1, 0, _settings_record(1), 0x000225b4)]}),
    ({0: _settings_app}, _log_globals(2, 0), {1: {0: 0}},
     {1: [(1, 0, _settings_record(1, True, True), 0x000225b4)]}),
    ({0: _settings_app}, _log_globals(2, 1), {1: {0: 0}},
     {1: [(1, 0, _settings_record(0), 0x000225b4)]}),
]

_user_settings = emu.SCRATCH + 0xa800
_user_record = bytes((i * 19 + 7) & 0xff for i in range(32))
REVIEWED_ORACLE_CASES[("app", 0x00023400)] = [
    ({0: _user_settings}, _log_globals(1, 0), {1: {0: 1}}),
    ({0: _user_settings}, _log_globals(2, 0), {1: {0: 1}}),
    ({0: _user_settings}, _log_globals(2, 1), {1: {0: 1}}),
    ({0: _user_settings}, _log_globals(1, 0), {1: {0: 0}},
     {1: [(1, 0, _user_record, 0x000225b4)]}),
    ({0: _user_settings}, _log_globals(2, 1), {1: {0: 0}},
     {1: [(1, 0, _user_record, 0x000225b4)]}),
]

# Registration always installs every callback/context pointer; only the
# diagnostic level and sink vary.
_imu_context = emu.SCRATCH + 0xb000
for _register_va in (0x00026250, 0x00025d40):
    REVIEWED_ORACLE_CASES[("app", _register_va)] = [
        ({0: _imu_context, 2: 0x33445566, 3: 0x778899aa},
         _log_globals(1, 0), {}),
        ({0: _imu_context, 2: 0x33445566, 3: 0x778899aa},
         _log_globals(2, 0), {}),
        ({0: _imu_context, 2: 0x33445566, 3: 0x778899aa},
         _log_globals(2, 1), {}),
    ]

# Static reset has the same three diagnostic states and must clear every
# complete fixed object regardless of logging.
REVIEWED_ORACLE_CASES[("app", 0x00016738)] = [
    ({2: 0x33445566, 3: 0x778899aa}, _log_globals(2, 0), {}),
    ({2: 0x33445566, 3: 0x778899aa}, _log_globals(3, 0), {}),
    ({2: 0x33445566, 3: 0x778899aa}, _log_globals(3, 1), {}),
]


def _ancs_state(ready, sink=0, level=0):
    context = emu.SCRATCH + 0xb800
    text_buffer = emu.SCRATCH + 0xb900
    record = bytearray(12)
    record[0:2] = ((0x1234 if ready else 0).to_bytes(2, "little"))
    record[4:8] = (0).to_bytes(4, "little")
    record[8:12] = text_buffer.to_bytes(4, "little")
    return context, [
        (0x20006aa0, bytes(record)),
        (text_buffer, b"ANCS\0"),
        (context + 0x44, b"\x01"),
        (0x2000230c, int(level).to_bytes(4, "little", signed=True)),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]


_ancs_context, _ancs_ready = _ancs_state(True)
_, _ancs_waiting = _ancs_state(False)
REVIEWED_ORACLE_CASES[("app", 0x000191e4)] = [
    ({0: 0x11111111, 1: 0x22222222, 2: 0x33333333},
     _ancs_ready, {0: {0: _ancs_context}, 1: {0: 77}, 3: {0: 0}}),
    ({0: 0x11111111, 1: 0x22222222, 2: 0x33333333},
     [*(x for x in _ancs_ready if x[0] != 0x20007554),
      (0x20007554, (1).to_bytes(4, "little"))],
     {0: {0: _ancs_context}, 1: {0: 77}, 3: {0: 1}, 5: {0: 0}}),
    # One initial wait call publishes the attribute id, then the request
    # succeeds. This covers the readiness-loop backedge without 1001 spins.
    ({0: 0x11111111, 1: 0x22222222, 2: 0x33333333},
     _ancs_waiting, {0: {0: _ancs_context}, 1: {0: 77}, 4: {0: 0}},
     {2: [(None, 0x20006aa0, (0x1234).to_bytes(2, "little"),
            0x0007c0a4)]}),
]


def _three_byte_key_case(producer, compare=0):
    source = emu.SCRATCH + 0x1000
    memory = bytearray(16)
    memory[3:6] = b"xyz"
    oracles = {1: {0: int(producer)}}
    writes = {0: [(0, 0, bytes(13), 0x00086c78)]}
    if producer == 0:
        oracles[2] = {0: int(compare)}
        writes[1] = [(1, 0, b"ABC", 0x00081326)]
    return ({0: 0x35, 1: source}, [(source, bytes(memory))], oracles, writes)


REVIEWED_ORACLE_CASES[("app", 0x00080ca0)] = [
    _three_byte_key_case(1),
    _three_byte_key_case(0, compare=1),
    _three_byte_key_case(0, compare=0),
]


def _cbor_window(address, first_byte, remaining=3, span=8):
    """Six-word decoder window used by the recovered CBOR readers."""
    end = address + span
    state = bytearray(24)
    state[0:4] = address.to_bytes(4, "little")
    state[4:8] = address.to_bytes(4, "little")
    state[8:12] = int(remaining).to_bytes(4, "little")
    state[12:16] = end.to_bytes(4, "little")
    state[16:20] = address.to_bytes(4, "little")
    state[20:24] = end.to_bytes(4, "little")
    return bytes(state), bytes([first_byte & 0xff]) + bytes(span - 1)


def _cbor_value_case(kind):
    state = emu.SCRATCH + 0x1000
    output = emu.SCRATCH + 0x1100
    cursor = emu.SCRATCH + 0x1200
    state_data = bytearray(16)
    state_data[0:4] = cursor.to_bytes(4, "little")
    state_data[12:16] = (cursor + 0x20).to_bytes(4, "little")
    output_data = bytearray(8)
    output_data[4:8] = (8 if kind != "overflow" else 0x30).to_bytes(4, "little")
    if kind == "first-error":
        oracles = {0: {0: 0}}
    elif kind == "width-error":
        oracles = {0: {0: 1}, 1: {0: 0}}
    else:
        oracles = {0: {0: 1}, 1: {0: 1}}
    return ({0: state, 1: output, 2: 1, 3: 2},
            [(state, bytes(state_data)), (output, bytes(output_data))],
            oracles)


REVIEWED_ORACLE_CASES[("app", 0x00085ebc)] = [
    _cbor_value_case("first-error"),
    _cbor_value_case("width-error"),
    _cbor_value_case("success"),
    _cbor_value_case("overflow"),
]


def _cbor_skip_case(kind):
    state = emu.SCRATCH + 0x1000
    cursor = emu.SCRATCH + 0x1200
    if kind == "rejected-mode":
        return ({0: state, 1: 1}, [(state, bytes(24))], {})
    if kind == "scalar":
        first = 0x01
    elif kind == "indefinite-scalar":
        first = 0x1f
    else:
        first = 0x42
    state_data, input_data = _cbor_window(cursor, first)
    if kind == "init-error":
        oracles = {0: {0: 0}}
    else:
        oracles = {0: {0: 1}, 1: {0: 1}}
    return ({0: state, 1: 0},
            [(state, state_data), (cursor, input_data)], oracles)


REVIEWED_ORACLE_CASES[("app", 0x00086064)] = [
    _cbor_skip_case("rejected-mode"),
    _cbor_skip_case("init-error"),
    _cbor_skip_case("scalar"),
    _cbor_skip_case("indefinite-scalar"),
    _cbor_skip_case("byte-string"),
]


def _signed_integer_case(length, negative=False):
    start = emu.SCRATCH + 0x1201
    image = bytearray(10)
    for index in range(max(1, min(int(length), 8))):
        image[index + 1] = (0x81 + index) if negative else (index + 1)
    return ({0: 7, 1: start, 2: int(length)},
            [(start - 1, bytes(image))],
            ({0: {0: 0x1234}} if 0 < length < 9 else {}))


REVIEWED_ORACLE_CASES[("app", 0x0008629e)] = [
    _signed_integer_case(0),
    _signed_integer_case(1, True), _signed_integer_case(8, True),
    _signed_integer_case(9),
]


def _list_pop_case(nonempty):
    head = emu.SCRATCH + 0x1000
    node = emu.SCRATCH + 0x1100
    if not nonempty:
        return ({0: head}, [(head, head.to_bytes(4, "little") * 2)], {})
    head_image = node.to_bytes(4, "little") * 2
    node_image = head.to_bytes(4, "little") * 2
    return ({0: head}, [(head, head_image), (node, node_image)], {})


REVIEWED_ORACLE_CASES[("app", 0x0008688e)] = [
    _list_pop_case(False), _list_pop_case(True),
]


def _descriptor_flags_case(index, object_flags=0, helper_result=0,
                           descriptor_flags=0):
    obj = emu.SCRATCH + 0x1000
    output_kind = emu.SCRATCH + 0x1100
    output_match = emu.SCRATCH + 0x1200
    raw = bytearray(16)
    raw[12:14] = int(object_flags).to_bytes(2, "little")
    raw[14:16] = int(index & 0xffff).to_bytes(2, "little")
    oracle_results = {} if index < 0 else {0: {0: int(helper_result)}}
    oracle_writes = {}
    if index >= 0 and helper_result >= 0:
        oracle_writes = {0: [
            (2, 4, int(descriptor_flags).to_bytes(4, "little"), 0x00077e4c),
        ]}
    return ({0: 3, 1: obj, 2: output_kind, 3: output_match},
            [(obj, bytes(raw)), (output_kind, bytes(4)),
             (output_match, bytes(4))], oracle_results, oracle_writes)


REVIEWED_ORACLE_CASES[("app", 0x00086b7e)] = [
    _descriptor_flags_case(-1),
    _descriptor_flags_case(-1, object_flags=0x80),
    _descriptor_flags_case(2, helper_result=-1),
    _descriptor_flags_case(2, descriptor_flags=0x1000),
    _descriptor_flags_case(2, descriptor_flags=0x2000),
]


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


def _json_string_case(encoded):
    """One complete JSON string decode through real allocation callbacks."""
    output = emu.SCRATCH + 0x0800
    parser = emu.SCRATCH + 0x1000
    text = emu.SCRATCH + 0x1800
    decoded = emu.SCRATCH + 0x2000
    descriptor = bytearray(24)
    descriptor[0:4] = text.to_bytes(4, "little")
    descriptor[4:8] = len(encoded).to_bytes(4, "little")
    descriptor[16:20] = (0x00080001).to_bytes(4, "little")
    descriptor[20:24] = (0x00080005).to_bytes(4, "little")
    return (
        {0: output, 1: parser},
        [(output, bytes(0x20)), (parser, bytes(descriptor)),
         (text, encoded), (decoded, bytes(0x20))],
        {0: {0: decoded}},
    )


def _tree_release_case():
    """One node with both optional resources and the node itself released."""
    node = emu.SCRATCH + 0x1000
    first_resource = emu.SCRATCH + 0x1800
    second_resource = emu.SCRATCH + 0x1c00
    record = bytearray(36)
    record[16:20] = first_resource.to_bytes(4, "little")
    record[32:36] = second_resource.to_bytes(4, "little")
    return (
        {0: node},
        [(node, bytes(record)),
         (0x20002bb0, (0x00080001).to_bytes(4, "little"))],
        {},
    )


def _irq_clear_case(mask, active, final_active=False):
    """Eight reviewed register mappings plus selected pending IRQ words."""
    memory = []
    for index in range(8):
        value = 1 if index in active else 0
        memory.append((0x5000d100 + 4 * index,
                       value.to_bytes(4, "little")))
    memory.append((0x5000d17c,
                   int(bool(final_active)).to_bytes(4, "little")))
    return (
        {0: mask}, memory,
        {index: {0: 0x100 + 4 * index} for index in range(8)},
    )


def _scan_case(format_bytes, input_bytes=b"", conversion_result=None):
    """Bounded scanf-style stream, format, and one output destination."""
    stream = emu.SCRATCH + 0x0800
    input_buffer = emu.SCRATCH + 0x1000
    format_buffer = emu.SCRATCH + 0x1800
    output_list = emu.SCRATCH + 0x2000
    output_value = emu.SCRATCH + 0x2400
    stream_record = bytearray(16)
    stream_record[0:4] = input_buffer.to_bytes(4, "little")
    stream_record[4:8] = len(input_bytes).to_bytes(4, "little")
    oracles = {}
    if b"%" in format_bytes:
        # Modifier lookup returns null for the plain conversion forms below.
        oracles[0] = {0: 0}
        if conversion_result is not None:
            oracles[1] = {0: conversion_result}
    return (
        {0: 0x13579bdf, 1: stream, 2: format_buffer, 3: output_list},
        [(stream, bytes(stream_record)), (input_buffer, input_bytes + b"\0"),
         (format_buffer, format_bytes),
         (output_list, output_value.to_bytes(4, "little")),
         (output_value, bytes(8))],
        oracles,
    )


REVIEWED_ORACLE_CASES[("app", 0x00064290)] = [
    _json_string_case(b'"a"'),
    _json_string_case(b'"\\n"'),
]
REVIEWED_ORACLE_CASES[("app", 0x00064b1c)] = [_tree_release_case()]
REVIEWED_ORACLE_CASES[("app", 0x00065324)] = [
    ({0: 2, 1: 0x55667788}, [(0x2000b320, b"\x01")], {}),
]
REVIEWED_ORACLE_CASES[("app", 0x00065620)] = [
    _irq_clear_case(0x05, {0, 2}, True),
    _irq_clear_case(0xff, {1, 3, 7}, False),
]
REVIEWED_ORACLE_CASES[("app", 0x00078f88)] = [
    _scan_case(b"abc\0", b"abc"),
    _scan_case(b"%n\0"),
    _scan_case(b"%d\0", b"7", conversion_result=1),
]

# Focused production-shaped calls for the formatter wrapper and the three
# neighboring event/queue helpers recovered in the same CFG-fail batch.
_writer_buffer = emu.SCRATCH + 0x2c00
REVIEWED_ORACLE_CASES[("app", 0x0007797c)] = [
    ({0: _writer_buffer, 1: 7, 2: 0, 3: 0},
     [(0x20002d20, (0x2468ace0).to_bytes(4, "little")),
      (_writer_buffer, bytes(8))], {}),
]
REVIEWED_ORACLE_CASES[("app", 0x0007c0a8)] = [
    ({0: value}, [], {}) for value in (0, 1, 0xffffffff)
]
REVIEWED_ORACLE_CASES[("app", 0x0007c0e2)] = [
    ({0: 0x11223344, 1: 0xa5a5a5a5, 2: 0x55667788}, [],
     {0: {0: 0x1234}, 1: {0: result}})
    for result in (0, 1)
]


def _queue_dispatch_case():
    receiver = emu.SCRATCH + 0x3000
    callback = 0x00080001
    return (
        {0: receiver},
        [(receiver, bytes(12) + callback.to_bytes(4, "little") + bytes(16))],
        {1: {0: 0}, 2: {0: 3}, 5: {0: 1}},
    )


REVIEWED_ORACLE_CASES[("app", 0x0007c20a)] = [_queue_dispatch_case()]


def _queue_globals(level=0, sink=0):
    return [
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]


def _audio_delete_case(result, level=0, sink=0):
    cleared = bytes(203)
    return (
        {0: 0x5a}, _queue_globals(level, sink), {1: {0: result}},
        {0: [(0, 0, cleared, 0x00086c78)]},
    )


REVIEWED_ORACLE_CASES[("app", 0x0002f878)] = [
    _audio_delete_case(0),
    _audio_delete_case(1, level=1),
]


def _ancs_case(active, result=0, level=0):
    output = emu.SCRATCH + 0x3400
    record = bytes((i * 29 + 7) & 0xff for i in range(0x1b4))
    memory = _queue_globals(level) + [
        (0x20006a6c + 0x10, int(active).to_bytes(4, "little")),
        (output, bytes(0x1b4)),
    ]
    oracles = {}
    writes = {0: [(0, 0, bytes(0x1b4), 0x00086c78)]}
    if active:
        oracles[1] = {0: result}
        if result == 0:
            writes[1] = [(1, 0, record, 0x00072240)]
            writes[2] = [(0, 0, record, 0x00086c04)]
    return ({0: output}, memory, oracles, writes)


REVIEWED_ORACLE_CASES[("app", 0x00018d94)] = [
    _ancs_case(False),
    _ancs_case(True, 0),
    _ancs_case(True, 1, level=1),
]


def _dmic_case(result, level=0):
    output = emu.SCRATCH + 0x3800
    initial = bytes((i * 17 + 3) & 0xff for i in range(200))
    dequeued = bytes((i * 31 + 5) & 0xff for i in range(200))
    writes = {0: [(0, 0, initial, 0x00086c04)]}
    if result == 0:
        writes[1] = [(1, 0, dequeued, 0x00072240)]
        writes[2] = [(0, 0, dequeued, 0x00086c04)]
    return (
        {0: output}, _queue_globals(level) + [(output, bytes(204))],
        {1: {0: result}}, writes,
    )


REVIEWED_ORACLE_CASES[("app", 0x0002ed00)] = [
    _dmic_case(0),
    _dmic_case(1, level=1),
]


def _uid_case(active, result=0, level=0):
    output = emu.SCRATCH + 0x3c00
    record = bytes.fromhex("4433221188776655")
    memory = _queue_globals(level) + [
        (0x20006a38 + 0x10, int(active).to_bytes(4, "little")),
        (output, bytes(8)),
    ]
    oracles = {0: {0: result}} if active else {}
    writes = ({0: [(1, 0, record, 0x00072240)]}
              if active and result == 0 else {})
    return ({0: output, 1: 8, 2: 0x2468ace0}, memory, oracles, writes)


REVIEWED_ORACLE_CASES[("app", 0x00018ff8)] = [
    _uid_case(False),
    _uid_case(True, 0),
    _uid_case(True, 1, level=1),
]


def _display_close_case(result, level=0, sink=0):
    return (
        {}, _queue_globals(level, sink), {1: {0: result}},
        {0: [(0, 0, bytes(23), 0x00086c78)]},
    )


REVIEWED_ORACLE_CASES[("app", 0x000499b8)] = [
    _display_close_case(0),
    _display_close_case(0, level=3),
    _display_close_case(1),
]


def _action_case(value, level=0, sink=0):
    return (
        {0: value, 1: 0x11223344, 2: 0x55667788, 3: 0x2468ace0},
        _queue_globals(level, sink), {},
    )


for _action_va in (0x00037108, 0x000371e8):
    REVIEWED_ORACLE_CASES[("app", _action_va)] = [
        _action_case(0),
        _action_case(0xff, level=3),
        _action_case(0x1234, level=3, sink=1),
    ]

REVIEWED_ORACLE_CASES[("app", 0x0003707c)] = [
    ({0: value}, [], {}) for value in (0, 0xff, 0x1234)
]


def _dashboard_init_case(initialized, outcomes):
    state = emu.SCRATCH + 0x4000
    initial_data = emu.SCRATCH + 0x5200
    rows = emu.SCRATCH + 0x6400
    state_bytes = bytearray(0x1100)
    state_bytes[0xfec:0xff0] = initial_data.to_bytes(4, "little")
    state_bytes[0x1020:0x1024] = rows.to_bytes(4, "little")
    memory = _queue_globals(0) + [
        (state, bytes(state_bytes)),
        (initial_data, bytes(0x40)),
        (rows, bytes(0x600)),
    ]
    oracles = {0: {0: int(initialized)}}
    if initialized:
        for ordinal in (1, 2, 3):
            oracles[ordinal] = {0: state}
        ordinal = 5  # ordinal four is FUN_0004a4b4
    else:
        ordinal = 2  # ordinal one is FUN_00016658
    for result in outcomes:
        oracles[ordinal] = {0: state}
        oracles[ordinal + 1] = {0: state}
        oracles[ordinal + 2] = {0: result}
        ordinal += 3
        if result in (-1, 0):
            oracles[ordinal] = {0: state}
            ordinal += 1
    return ({}, memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x00036ed8)] = [
    _dashboard_init_case(False, (-1, 0, 1, 1)),
    _dashboard_init_case(True, (1, 1, 1, 1)),
]


def _imu_thread_entry_case(already_running):
    state = emu.SCRATCH + 0x7800
    body = bytearray(0x300)
    body[0x14] = int(already_running)
    body[0x15] = 0
    return (
        {0: state}, _queue_globals(0) + [(state, bytes(body))], {},
        {0: [(0, 0, bytes(24), 0x00086c78)],
         1: [(0, 0, bytes(24), 0x00086c78)]},
    )


def _imu_thread_loop_case(mode, event=0):
    state = emu.SCRATCH + 0x9000
    base = state - 0xf00
    body = bytearray(0x1200)
    body[0xf00 + 0x14] = 0
    body[0xf00 + 0x15] = 1
    body[0xf00 + 0x106] = mode
    body[0xf00 - 0xe0f] = event
    stop_ordinal = 3 if mode == 0x0b else 4
    return (
        {0: state}, _queue_globals(0) + [(base, bytes(body))],
        {2: {0: 0}},
        {0: [(0, 0, bytes(24), 0x00086c78)],
         1: [(0, 0, bytes(24), 0x00086c78)],
         stop_ordinal: [(None, state + 0x15, b"\0", 0x0007ca72)]},
    )


def _imu_sensor_case(success, calibration=False, event_transition=False):
    state = emu.SCRATCH + 0x9000
    base = state - 0xf00
    device = emu.SCRATCH + 0xb000
    vtable = emu.SCRATCH + 0xc000
    callback = 0x00080001
    body = bytearray(0x1200)
    body[0xf00 + 0x15] = 1
    body[0xf00 + 0x1c:0xf00 + 0x20] = device.to_bytes(4, "little")
    # Keep the ordinary event-zero stabilization path finite; the transition
    # case uses an event that must publish status 2 and switch state to 2.
    body[0xf00 - 0xe0f] = 5 if event_transition else 0
    if event_transition:
        body[0xf00 + 8:0xf00 + 12] = (100).to_bytes(4, "little")
    device_bytes = bytearray(0x20)
    device_bytes[8:12] = vtable.to_bytes(4, "little")
    vtable_bytes = bytearray(0x20)
    vtable_bytes[0x0c:0x10] = callback.to_bytes(4, "little")
    vtable_bytes[0x10:0x14] = callback.to_bytes(4, "little")
    fusion_globals = bytearray(0x68)
    if calibration:
        fusion_globals[0x28] = 1  # established initial attitude
        fusion_globals[0x29] = 1  # calibration accumulation mode
        fusion_globals[0x34:0x38] = (4).to_bytes(4, "little")
        for offset, value in ((0x44, 0.5625), (0x48, 0.625),
                              (0x4c, 0.6875), (0x50, 0.0625),
                              (0x54, 0.125), (0x58, 0.1875),
                              (0x5c, 10.0), (0x60, 20.0), (0x64, 30.0)):
            fusion_globals[offset:offset + 4] = struct.pack("<f", value)
    elif event_transition:
        fusion_globals[0x04:0x08] = (1).to_bytes(4, "little")
        fusion_globals[0x28] = 1
    memory = _queue_globals(0) + [
        (base, bytes(body)), (device, bytes(device_bytes)),
        (vtable, bytes(vtable_bytes)),
        (0x20007a88, bytes(fusion_globals)),
    ]
    oracles = {2: {0: 1}, 3: {0: 0 if success else 0xffffffff}}
    writes = {
        0: [(0, 0, bytes(24), 0x00086c78)],
        1: [(0, 0, bytes(24), 0x00086c78)],
    }
    if not success:
        writes[4] = [(None, state + 0x15, b"\0", 0x0007ca72)]
        return ({0: state}, memory, oracles, writes)
    sample3 = bytes((i * 13 + 3) & 0xff for i in range(24))
    sample7 = bytes((i * 17 + 5) & 0xff for i in range(24))
    writes[4] = [(2, 0, sample3, callback)]
    writes[5] = [(2, 0, sample7, callback)]
    # All recovered numeric helpers return a coherent zero vector.  The
    # second mode query remains zero so the iteration reaches stabilization.
    for ordinal in range(6, 54):
        oracles[ordinal] = {0: 0, 1: 0}
    # Preserve distinct converted accelerometer/gyro lanes through the
    # hard-float fusion boundary instead of proving only an all-zero vector.
    for ordinal, value in ((11, 0x3dcccccd), (17, 0x3e4ccccd),
                           (23, 0x3e99999a), (41, 0x3f000000),
                           (44, 0xbf000000), (47, 0x3f400000)):
        oracles[ordinal] = {0: value}
    oracles[48] = {0: 0x00040000}
    # Distinct finite f32 oracle payloads make roll/pitch/yaw placement,
    # scaling, and calibration deltas independently observable.
    oracles[50] = {0: 0x00100000}
    oracles[51] = {0: 0x00200000}
    oracles[52] = {0: 0x00300000}
    if calibration:
        for ordinal in range(54, 57):
            oracles[ordinal] = {0: 0, 1: 0}
        writes[57] = [(None, state + 0x15, b"\0", 0x0007ca72)]
    elif event_transition:
        for ordinal in range(54, 59):
            oracles[ordinal] = {0: 0, 1: 0}
        oracles[56] = {0: state}
        writes[58] = [(None, state + 0x15, b"\0", 0x0007ca72)]
    else:
        writes[54] = [(None, state + 0x15, b"\0", 0x0007ca72)]
    return ({0: state}, memory, oracles, writes)


REVIEWED_ORACLE_CASES[("app", 0x0000fe88)] = [
    _imu_thread_entry_case(True),
    _imu_thread_entry_case(False),
    _imu_thread_loop_case(0x0b),
    _imu_thread_loop_case(0x0c, event=7),
    _imu_sensor_case(False),
    _imu_sensor_case(True),
    _imu_sensor_case(True, calibration=True),
    _imu_sensor_case(True, event_transition=True),
]


def _whitelist_store_case(results, sink=0):
    oracles = {}
    ordinal = 0
    for result in results:
        oracles[ordinal] = {0: result & 0xffffffff}
        ordinal += 1
        if result == 0:
            ordinal += 1  # persistent whitelist refresh
            break
        ordinal += 2      # retry delay and routed diagnostic
    return ({}, [(0x20007554, int(sink).to_bytes(4, "little"))], oracles)


REVIEWED_ORACLE_CASES[("app", 0x00035608)] = [
    _whitelist_store_case((0,)),
    _whitelist_store_case((-1, 0)),
    _whitelist_store_case((-1, -2, -3)),
    _whitelist_store_case((-1, -2, -3), sink=1),
]


def _signal_sync_case(mode, start, end, sink=0):
    state = emu.SCRATCH + 0x2000
    image = bytearray(0x1060)
    image[0x105a] = mode
    memory = [
        (state, bytes(image)),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]
    oracles = {
        0: {0: start & 0xffffffff, 1: (start >> 32) & 0xffffffff},
        1: {0: state},
        2: {0: 0x13579bdf},
        3: {0: state},
        5: {0: end & 0xffffffff, 1: (end >> 32) & 0xffffffff},
    }
    return ({0: 0x123400ab, 1: 0x89abcdef, 2: 0x76543210},
            memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x0002c224)] = [
    _signal_sync_case(1, 1000, 2000),
    _signal_sync_case(2, 1000, 2000),
    _signal_sync_case(2, 1000, 5000),
    _signal_sync_case(1, 1000, 5000, sink=1),
]


def _screen_state_case(current, requested, level=0, sink=0):
    owner = emu.SCRATCH + 0x3000
    image = bytearray(0x1000)
    image[0xfe8] = current
    memory = [
        (owner, bytes(image)),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]
    return ({0: 0x11223344, 1: owner, 2: requested, 3: 0x55667788},
            memory, {})


REVIEWED_ORACLE_CASES[("app", 0x0002bc2c)] = [
    _screen_state_case(0, 0),
    _screen_state_case(1, 1, level=2),
    _screen_state_case(1, 0, level=2, sink=1),
    _screen_state_case(0, 1, level=2),
]


def _file_save_case(packet, address=0, file_type=0, buffered=0,
                    checksum=0x10203040, level=0, sink=0):
    packet = bytes(packet)
    assert len(packet) == 201
    memory = [
        (0x200079dc, int(address).to_bytes(4, "little")),
        (0x200079d4, int(file_type).to_bytes(4, "little")),
        (0x200079d8, int(buffered).to_bytes(4, "little")),
        (0x200079e0, int(checksum).to_bytes(4, "little")),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
        (0x20017062, bytes(0x1400)),
    ]
    writes = {0: [(0, 0, packet, 0x000235a4)]}
    return ({0: emu.SCRATCH + 0x6000}, memory, {}, writes)


def _file_packet(length, prefix=b""):
    packet = bytearray(201)
    packet[:len(prefix)] = prefix
    packet[200] = length
    return packet


REVIEWED_ORACLE_CASES[("app", 0x00023634)] = [
    # Short completion marker, ordinary first/continuation chunks, threshold
    # flush, and protected firmware-address early return.
    _file_save_case(_file_packet(10, b"\x0d\x0e"), address=0x120000,
                    buffered=32, level=1),
    _file_save_case(_file_packet(9, b"\x00\x00\x12\x34\x56DATA")),
    _file_save_case(_file_packet(7, b"\x01abcdef"), address=0x123456,
                    buffered=12),
    _file_save_case(_file_packet(4, b"\x01abc"), address=0x123456,
                    buffered=0xffe, level=1, sink=1),
    _file_save_case(_file_packet(10, b"\x0d\x0e"), address=0x200000,
                    file_type=0x1c0000, buffered=16),
]


def _uart_case(kind, level=0, sink=0, queue_result=0,
               callback_result=0):
    descriptor = emu.SCRATCH + 0x5000
    payload = emu.SCRATCH + 0x5200
    device = emu.SCRATCH + 0x5400
    vtable = emu.SCRATCH + 0x5500
    desc = bytearray(16)
    desc[0] = kind
    desc[4:8] = payload.to_bytes(4, "little")
    data = bytearray(0x120)
    device_image = bytearray(12)
    vtable_image = bytearray(0x20)
    vtable_image[0x10:0x14] = (0x00080001).to_bytes(4, "little")
    device_image[8:12] = vtable.to_bytes(4, "little")
    oracles = {}
    if kind == 0:
        desc[8:12] = (2).to_bytes(4, "little")
        data[:2] = b"\x12\x34"
    elif kind == 2:
        frame = bytearray(b"\x5a\xa5\x7f\x01\x22\x00")
        frame[-1] = sum(frame[:-1]) & 0xff
        data[:len(frame)] = frame
    elif kind == 3:
        oracles[1] = {0: queue_result & 0xffffffff}
        if queue_result == 0:
            oracles[2] = {0: callback_result & 0xffffffff}
    memory = [
        (descriptor, bytes(desc)), (payload, bytes(data)),
        (device, bytes(device_image)), (vtable, bytes(vtable_image)),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
        (0x2001a128, bytes(0x102)),
    ]
    return ({0: 0x11223344, 1: descriptor, 2: device}, memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x00033384)] = [
    _uart_case(0), _uart_case(0, level=3),
    _uart_case(1), _uart_case(1, level=1),
    _uart_case(1, level=1, sink=1),
    _uart_case(2),
    _uart_case(3, queue_result=1),
    _uart_case(3, callback_result=1),
    _uart_case(3, callback_result=0),
    _uart_case(4),
]


def _watchdog_init_case(ready, install_results=(), setup_result=0,
                        feed_results=(), level=0, sink=0):
    device = bytearray(12)
    api_address = emu.SCRATCH + 0x7000
    device[8:12] = api_address.to_bytes(4, "little")
    api = bytearray(16)
    api[0:4] = (0x00080001).to_bytes(4, "little")
    api[8:12] = (0x00080011).to_bytes(4, "little")
    api[12:16] = (0x00080021).to_bytes(4, "little")
    memory = [
        (0x00087cc8, bytes(device)), (api_address, bytes(api)),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
        (0x20007b50, bytes(4)),
    ]
    oracles = {}
    ordinal = int(level > 3)  # optional entry diagnostic
    oracles[ordinal] = {0: int(bool(ready))}
    ordinal += 1
    if not ready:
        return ({0: 1, 1: 2, 2: 3, 3: 4}, memory, oracles)
    writes = {ordinal: [(0, 0, bytes(16), 0x00086c78)]}
    ordinal += 1  # memset timeout record
    if level > 3:
        ordinal += 1
    for index, result in enumerate(install_results):
        oracles[ordinal] = {0: result & 0xffffffff}
        ordinal += 1
        if index == 0 and result == -0x86:
            if level > 0:
                ordinal += 1
            continue
        break
    final_install = install_results[-1] if install_results else 0
    if final_install < 0:
        return ({0: 1, 1: 2, 2: 3, 3: 4}, memory, oracles, writes)
    oracles[ordinal] = {0: setup_result & 0xffffffff}
    ordinal += 1
    if setup_result < 0:
        return ({0: 1, 1: 2, 2: 3, 3: 4}, memory, oracles, writes)
    if level > 3:
        ordinal += 1
    for result in feed_results:
        if level > 3:
            ordinal += 1
        oracles[ordinal] = {0: result & 0xffffffff}
        ordinal += 1
        if result == 0:
            break
        ordinal += 1  # retry delay
    return ({0: 1, 1: 2, 2: 3, 3: 4}, memory, oracles, writes)


REVIEWED_ORACLE_CASES[("app", 0x0002ace0)] = [
    _watchdog_init_case(False),
    _watchdog_init_case(False, level=1),
    _watchdog_init_case(False, level=1, sink=1),
    _watchdog_init_case(True, (0,), 0, (0,)),
    _watchdog_init_case(True, (0,), 0, (0,), level=4),
    _watchdog_init_case(True, (0,), 0, (0,), level=4, sink=1),
    _watchdog_init_case(True, (-0x86, 0), 0, (1, 0), level=1),
    _watchdog_init_case(True, (-1,), level=1),
    _watchdog_init_case(True, (0,), -1, level=1),
    _watchdog_init_case(True, (0,), 0, (1, 1, 1, 1, 1), level=4),
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


def _app_59920_state_case(mode):
    """A real seven-byte state record and its owning application object."""
    state = emu.SCRATCH + 0x1200
    owner = emu.SCRATCH + 0x2200
    context = emu.SCRATCH + 0x4200
    state_image = bytes((mode, 0x21, 0x32, 0x43, 0x54, 0x65, 0x76))
    return (
        {0: context},
        [(context - 0x160, owner.to_bytes(4, "little")),
         (owner, (0x12345678).to_bytes(4, "little")),
         (state, state_image)],
        {0: {0: state}},
    )


def _app_59d24_case(kind):
    """Model disabled, existing, and each of the three allocation slots."""
    oracles = {0: {0: 1}, 1: {0: 1}}
    if kind == "disabled":
        oracles[0] = {0: 0}
    elif kind != "existing":
        oracles[1] = {0: 0}
        slot = int(kind[-1])
        for ordinal in range(slot):
            oracles[2 + ordinal] = {0: 1}
        oracles[2 + slot] = {0: 0}
    return ({0: 5, 1: 0x1234, 2: 3}, [], oracles)


def _app_583d0_case(kind):
    """Coherent owner, transfer state, and optional existing result record."""
    owner = emu.SCRATCH + 0x1000
    transfer = emu.SCRATCH + 0x2000
    limits = emu.SCRATCH + 0x3000
    cursor = emu.SCRATCH + 0x3800
    existing = emu.SCRATCH + 0x4000
    owner_image = bytearray(8)
    owner_image[0:4] = (0x1234).to_bytes(4, "little")
    transfer_image = bytearray(0x20)
    transfer_image[0:4] = limits.to_bytes(4, "little")
    transfer_image[4:8] = cursor.to_bytes(4, "little")
    if kind in ("existing", "update"):
        transfer_image[8:12] = existing.to_bytes(4, "little")
    limits_image = bytearray(0x40)
    limits_image[8:12] = (0x76543210).to_bytes(4, "little")
    limits_image[0x1e:0x20] = (2).to_bytes(2, "little")
    limits_image[0x2e:0x30] = (3).to_bytes(2, "little")
    existing_image = bytearray(8)
    existing_image[2:4] = (8).to_bytes(2, "little")
    if kind == "reset":
        oracles = {0: {0: 0}}
    elif kind in ("existing", "update"):
        oracles = {0: {0: 1}, 1: {0: 1}}
    else:
        oracles = {0: {0: 1}, 1: {0: 0}, 2: {0: 0, 1: 0}}
    requested = 9 if kind == "update" else 7
    return (
        {0: owner, 1: requested, 2: transfer},
        [(owner, bytes(owner_image)), (transfer, bytes(transfer_image)),
         (limits, bytes(limits_image)), (cursor, bytes(0x20)),
         (existing, bytes(existing_image))],
        oracles,
    )


def _app_59f04_case(kind):
    """Exercise initial lookup, missing/existing allocation, and conflict."""
    record = emu.SCRATCH + 0x4800
    oracles = {}
    effects = {}
    if kind == "null-context":
        return ({0: 0, 1: 0}, [(record, bytes(16))], {}, {})
    if kind == "initial-error":
        oracles = {0: {0: 1}}
    else:
        oracles = {0: {0: 0}, 1: {0: 0}}
        local_value = 7 if kind == "conflict" else 0
        effects = {1: [(1, 0, local_value.to_bytes(4, "little"),
                        0x0007f1e8)]}
        if kind == "conflict":
            oracles[2] = {0: 1}
        elif kind == "existing":
            oracles[2] = {0: record}
        else:
            oracles[2] = {0: 0}
    return ({0: 1, 1: 0}, [(record, bytes(16))], oracles, effects)


REVIEWED_ORACLE_CASES[("app", 0x000583d0)] = [
    _app_583d0_case(kind)
    for kind in ("reset", "existing", "update", "short")
]
REVIEWED_ORACLE_CASES[("app", 0x00059920)] = [
    _app_59920_state_case(mode) for mode in range(5)
]
REVIEWED_ORACLE_CASES[("app", 0x00059d24)] = [
    _app_59d24_case(kind)
    for kind in ("disabled", "existing", "slot0", "slot1", "slot2")
]
REVIEWED_ORACLE_CASES[("app", 0x00059f04)] = [
    _app_59f04_case(kind)
    for kind in ("null-context", "initial-error", "missing", "existing",
                 "conflict")
]


def _app_7c28e_packet_case():
    """A complete live settings image with nonuniform telemetry fields."""
    context = emu.SCRATCH + 0x5000
    image = bytearray(0x1100)
    for offset in (0x0fea, 0x0ed5, 0x0ef4, 0x0f60, 0x0f98,
                   0x1070, 0x108d, 0x0ec0, 0x106f, 0x0ef5,
                   0x108f, 0x1090, 0x1091, 0x0ec1):
        image[offset] = (offset * 37 + 0x5b) & 0xff
    image[0x0f6c:0x0f70] = (0x12345678).to_bytes(4, "little")
    image[0x1069:0x106d] = (0x89abcdef).to_bytes(4, "little")
    image[0x106d:0x106f] = (0x2468).to_bytes(2, "little")
    image[0x0f68:0x0f6c] = (0x0badc0de).to_bytes(4, "little")
    return ({0: context}, [(context, bytes(image))], {0: {0: 0xa5}})


def _app_7c968_attribute_case(kind):
    output = emu.SCRATCH + 0x6800
    if kind == "null":
        return ({0: 3, 1: 0, 2: 0}, [], {})
    if kind == "first-error":
        return ({0: 3, 1: output, 2: 0}, [(output, bytes(8))],
                {0: {0: 5}})
    return (
        {0: 3, 1: output, 2: 0},
        [(output, bytes(8))],
        {0: {0: 0}, 1: {0: 7}},
        {0: [(2, 0, (0x2468).to_bytes(2, "little"), 0x000257ec)]},
    )


REVIEWED_ORACLE_CASES[("app", 0x0007c28e)] = [
    _app_7c28e_packet_case()
]
REVIEWED_ORACLE_CASES[("app", 0x0007c968)] = [
    _app_7c968_attribute_case(kind)
    for kind in ("null", "first-error", "success")
]


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

# Small production-shaped contracts for the libm wrapper and the two request
# forwarding thunks.  These functions do not expose useful argument-derived
# CFG selectors, so generic random state alone would leave their global-state
# arms and stack-passed request words implicit.
ADDITIONAL_STATE_CASES[("app", 0x00075c2c)] = [
    ({}, [(0x200035af, b"\xff")]),
    ({}, [(0x200035af, b"\x00")]),
    ({}, [(0x200035af, b"\x00")]),
]
_request_context = emu.SCRATCH + 0x1400
_request_memory = [
    (0x2000b450, _request_context.to_bytes(4, "little")),
    (_request_context, bytes(0x80)),
]
REVIEWED_ORACLE_CASES[("app", 0x000755f8)] = [
    # Callee clears the completion byte: publish immediately, then unlock.
    ({0: 0x101, 1: 2, 2: 0, 3: 0}, _request_memory,
     {0: {0: 0x55}, 1: {0: 1}, 4: {0: 1}},
     {0: [(None, _request_context + 0x60, b"\x00", 0x000751d0)]}),
    # The same valid request in IRQ context must take the diagnostic exit.
    ({0: 0x101, 1: 2, 2: 0, 3: 0}, _request_memory, {}, {}),
    # No flags: clear the owned byte and return the firmware's -EAGAIN value.
    ({0: 0x202, 1: 3, 2: 0, 3: 0}, _request_memory,
     {0: {0: 0x66}, 1: {0: 1}, 3: {0: 1}}, {}),
    # Flagged request: queue the callback, reacquire, publish and unlock.
    ({0: 0x303, 1: 4, 2: 0x10, 3: 0x20}, _request_memory,
     {0: {0: 0x77}, 1: {0: 1}, 3: {0: 0x88},
      4: {0: 1}, 7: {0: 1}}, {}),
]
REVIEWED_ORACLE_CASES[("app", 0x0001694c)] = [
    ({0: mode},
     [(0x2000ff4b, b"\x00"),
      (0x200069fc, (emu.SCRATCH + 0x2000).to_bytes(4, "little")),
      (emu.SCRATCH + 0x2000, b"\x00\xff" + bytes(0x700 - 2)),
      (0x2000230c, bytes(4)), (0x20007554, bytes(4))],
     {})
    for mode in range(10)
]
REVIEWED_ORACLE_CASES[("app", 0x00017a40)] = [
    ({}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4))],
     {14: {0: 0}, 15: {0: 0}}),
    ({}, [(0x2000230c, (2).to_bytes(4, "little")),
          (0x20007554, bytes(4))],
     {14: {0: 0}, 16: {0: 0}}),
]
def _ble_get_case(command):
    context = emu.SCRATCH + 0x3000
    packet = emu.SCRATCH + 0x4200
    request = emu.SCRATCH + 0x4300
    output_word = emu.SCRATCH + 0x4400
    callback = 0x00080001
    context_data = bytearray(0xa00)
    context_data[0x0c:0x10] = callback.to_bytes(4, "little")
    context_data[0x10:0x14] = output_word.to_bytes(4, "little")
    packet_data = bytearray(16)
    packet_data[0] = command
    packet_data[2:4] = (6).to_bytes(2, "little")
    request_data = bytearray(32)
    request_data[1:3] = (6).to_bytes(2, "little")
    request_data[5] = 3
    oracle = {}
    if command == 0x39:
        oracle[1] = {0: 0}
    elif command == 0x3d:
        oracle[2] = {0: 0}
    elif command == 0x3e:
        oracle[0] = {0: emu.SCRATCH + 0x5000}
    return (
        {0: context, 1: packet, 2: request},
        [(context, bytes(context_data)), (packet, bytes(packet_data)),
         (request, bytes(request_data)), (output_word, bytes(4)),
         (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
         (0x20018462, b"\x00")],
        oracle)

REVIEWED_ORACLE_CASES[("app", 0x0001a064)] = [
    _ble_get_case(command)
    for command in tuple(range(0x29, 0x3f)) + (0x00, 0x2f)
]
REVIEWED_ORACLE_CASES[("app", 0x000183e4)] = [
    ({0: emu.SCRATCH + 0x2800},
     [(0x20007514, (7).to_bytes(4, "little")),
      (0x20006ab8, (emu.SCRATCH + 0x2900).to_bytes(4, "little")),
      (emu.SCRATCH + 0x2800, bytes(8)),
      (emu.SCRATCH + 0x2900, bytes(0x400)),
      (0x2000230c, level.to_bytes(4, "little")),
      (0x20007554, mode.to_bytes(4, "little"))], {})
    for level, mode in ((0, 0), (1, 0), (1, 1))
]
REVIEWED_ORACLE_CASES[("app", 0x00023b78)] = [
    ({}, [(0x2000230c, level.to_bytes(4, "little")),
          (0x20007554, mode.to_bytes(4, "little"))],
     {0: {0: status}})
    for status, level, mode in ((0, 0, 0), (0, 3, 0),
                                (0, 3, 1), (1, 1, 0), (1, 1, 1))
]

# The queue helper completely initializes command byte 0 and value byte 4.
# Drive the default arm plus every shipped command (1..4) with deterministic
# storage/logging state.  A failed storage probe keeps the cases finite while
# retaining each command's distinct dispatch and return behavior.
REVIEWED_ORACLE_CASES[("app", 0x00023f04)] = [
    ({},
     [(0x2000230c, (0).to_bytes(4, "little", signed=True)),
      (0x20007554, (0).to_bytes(4, "little")),
      (0x20018462, bytes((0, 2, 2)))],
     {0: {0: 0}, 1: {0: 0}},
     {0: [(1, 0, bytes((command, 0, 0, 0, value)), 0x00072240)]})
    for command, value in ((0, 0), (1, 5), (2, 0), (3, 1), (4, 0))
]

# Each queue initializer has four production outcomes: successful setup,
# failure below the log threshold, and failure through either diagnostic sink.
def _msgq_init_cases():
    return [
        ({},
         [(0x2000230c, int(level).to_bytes(4, "little", signed=True)),
          (0x20007554, int(sink).to_bytes(4, "little"))],
         {0: {0: status}})
        for status, level, sink in (
            (0, 0, 0), (1, 0, 0), (1, 1, 0), (1, 1, 1)
        )
    ]


for _msgq_init_va in (0x0002ebd8, 0x00018b6c, 0x00018e04):
    REVIEWED_ORACLE_CASES[("app", _msgq_init_va)] = _msgq_init_cases()


# IPC receive cases cover an empty endpoint table below logging, both complete
# packet diagnostics, and a matching endpoint's three-argument tail callback.
def _ipc0_receive_case(count, level, sink, match=False):
    owner = 0x20012000
    endpoint = 0x20012100
    packet = 0x20012200
    owner_bytes = bytearray(16)
    owner_bytes[4:8] = int(count).to_bytes(4, "little")
    endpoint_bytes = bytearray(16)
    endpoint_bytes[0] = 0x42
    endpoint_bytes[8:12] = (0x00080001).to_bytes(4, "little")
    if match:
        owner_bytes[8:12] = endpoint.to_bytes(4, "little")
    return (
        {0: packet, 1: 8},
        [(0x20007a84, owner.to_bytes(4, "little")),
         (owner, bytes(owner_bytes)),
         (endpoint, bytes(endpoint_bytes)),
         (packet, bytes((0x42, 1, 2, 3, 4, 5, 6, 7))),
         (0x2000230c, int(level).to_bytes(4, "little", signed=True)),
         (0x20007554, int(sink).to_bytes(4, "little"))],
        {},
    )


REVIEWED_ORACLE_CASES[("app", 0x00025a48)] = [
    _ipc0_receive_case(0, 0, 0),
    _ipc0_receive_case(0, 2, 0),
    _ipc0_receive_case(0, 2, 1),
    _ipc0_receive_case(1, 0, 0, match=True),
]


# Deterministic whitelist fixtures enter each built-in identifier family,
# exercise its disabled/enabled flag result, reach both final fallback results,
# and match one custom whitelist entry.  Oracle ordinals follow the concrete
# strlen/identifier-compare call order of the shipped CFG.
def _whitelist_case(argument, flags, count, returns, sink=0):
    identifier = 0x20013000
    return (
        {0: argument},
        [(identifier, b"sample-id\0"),
         (0x20007554, int(sink).to_bytes(4, "little")),
         (0x2001a22c, bytes((flags, count)) + bytes(0x3a))],
        {ordinal: {0: value} for ordinal, value in enumerate(returns)},
    )


_WHITELIST_IDENTIFIER = 0x20013000
REVIEWED_ORACLE_CASES[("app", 0x00034bd4)] = [
    _whitelist_case(0, 0, 0, (), sink=0),
    _whitelist_case(_WHITELIST_IDENTIFIER, 0, 0, (40,), sink=1),
    _whitelist_case(_WHITELIST_IDENTIFIER, 0, 0, (5, 0), sink=0),
    _whitelist_case(_WHITELIST_IDENTIFIER, 1, 0, (5, 0), sink=1),
    _whitelist_case(_WHITELIST_IDENTIFIER, 0, 0,
                    (5, 1, 1, 1, 1, 0), sink=0),
    _whitelist_case(_WHITELIST_IDENTIFIER, 2, 0,
                    (5, 1, 1, 1, 1, 0), sink=1),
    _whitelist_case(_WHITELIST_IDENTIFIER, 0, 0,
                    (5, 1, 1, 1, 1, 1, 1, 0), sink=0),
    _whitelist_case(_WHITELIST_IDENTIFIER, 8, 0,
                    (5, 1, 1, 1, 1, 1, 1, 0), sink=1),
    _whitelist_case(_WHITELIST_IDENTIFIER, 0, 0,
                    (5, 1, 1, 1, 1, 1, 1, 1, 1, 0), sink=0),
    _whitelist_case(_WHITELIST_IDENTIFIER, 4, 0,
                    (5, 1, 1, 1, 1, 1, 1, 1, 1, 0), sink=1),
    _whitelist_case(_WHITELIST_IDENTIFIER, 0, 0,
                    (5,) + (1,) * 9 + (0,), sink=0),
    _whitelist_case(_WHITELIST_IDENTIFIER, 0, 0,
                    (5,) + (1,) * 9 + (1,), sink=1),
    _whitelist_case(_WHITELIST_IDENTIFIER, 0x10, 1,
                    (5,) + (1,) * 9 + (4, 0), sink=0),
]
REVIEWED_ORACLE_CASES[("app", 0x000289e4)] = [
    ({}, [(0x20007554, mode.to_bytes(4, "little")),
          (0x20018d8b, bytes((flag,)))], {})
    for mode, flag in ((0, 0), (0, 1), (1, 0), (1, 1))
]
REVIEWED_ORACLE_CASES[("app", 0x0002e8b4)] = [
    ({0: 0x11, 1: 0x22, 2: 0x33, 3: 0x44},
     [(0x20007b6c, context.to_bytes(4, "little")),
      (0x2000230c, level.to_bytes(4, "little")),
      (0x20007554, mode.to_bytes(4, "little")),
      (0x20018da1, b"\x01")] +
     ([(context, bytes(0x20))] if context else []), {})
    for context, level, mode in (
        (0, 0, 0), (emu.SCRATCH + 0x2a00, 0, 0),
        (emu.SCRATCH + 0x2b00, 3, 0),
        (emu.SCRATCH + 0x2c00, 3, 1))
]

def _navigation_overview_case(active, sync_ready=0, cached=0):
    model = emu.SCRATCH + 0x3500
    model_data = bytearray(0x200)
    model_data[0xb1:0xb5] = (0x1210).to_bytes(4, "little")
    return (
        {0: 0, 1: model},
        [(model, bytes(model_data)),
         (0x20004bb8, bytes(5) + b"\x01" + bytes(0x20 - 6)),
         (0x20010323, bytes((active,))),
         (0x20010324, b"\x00"),
         (0x20010326, bytes((sync_ready,))),
         (0x2001ba2d, bytes((cached,))),
         (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
         (0x20007574, bytes(0x40)),
         (0x20015e52, bytes(0x1210)),
         (0x2001ba2e, bytes(0x1210))],
        {})

REVIEWED_ORACLE_CASES[("app", 0x0003e05c)] = [
    _navigation_overview_case(0),
    _navigation_overview_case(1),
    _navigation_overview_case(1, cached=1),
    _navigation_overview_case(1, sync_ready=1),
]

def _sync_data_cases():
    payload = emu.SCRATCH + 0x2d00
    state = emu.SCRATCH + 0x2e00
    context = emu.SCRATCH + 0x2f00
    base_memory = [(payload, b"\x5a\xa5\x3c\xc3"),
                   (context, bytes(0x20))]
    def memory(local, level=0, mode=0):
        return base_memory + [
            (state, bytes((1 if local else 0,)) + bytes(7)),
            (0x2000230c, level.to_bytes(4, "little")),
            (0x20007554, mode.to_bytes(4, "little"))]
    return [
        ({0: 0}, memory(False), {}),
        ({0: payload, 1: 1, 2: 0x1234}, memory(False),
         {0: {0: state}, 1: {0: context}, 2: {0: 100}}),
        ({0: payload, 1: 0, 2: 0x5678}, memory(False),
         {0: {0: state}, 1: {0: context}, 2: {0: 2000}}),
        ({0: payload, 1: 1, 2: 0x9abc}, memory(False, 1, 1),
         {0: {0: state}, 1: {0: context}, 2: {0: 2000}}),
        ({0: payload, 1: 0, 2: 0x1111}, memory(True),
         {0: {0: state}, 1: {0: context}, 2: {0: 100}}),
        ({0: payload, 1: 4, 2: 0x2222}, memory(True),
         {0: {0: state}, 2: {0: context}, 3: {0: 100}}),
        ({0: payload, 1: 2, 2: 0x3333}, memory(True, 1, 0),
         {0: {0: state}, 2: {0: context}, 3: {0: 5000}}),
    ]

REVIEWED_ORACLE_CASES[("app", 0x0003ce04)] = _sync_data_cases()
REVIEWED_ORACLE_CASES[("app", 0x00042c8c)] = _sync_data_cases()
REVIEWED_ORACLE_CASES[("app", 0x00076cc8)] = [
    ({0: 0x11, 1: 0x22, 2: 0x33, 3: 0x44},
     [(0x20002d20, (emu.SCRATCH + 0x1000).to_bytes(4, "little"))], {}),
    ({0: 0xa1, 1: 0xb2, 2: 0xc3, 3: 0xd4},
     [(0x20002d20, (emu.SCRATCH + 0x1100).to_bytes(4, "little"))], {}),
]
def _newlib_assert_case(has_function):
    reent = emu.SCRATCH + 0x1800
    stderr_stream = emu.SCRATCH + 0x1a00
    source_file = emu.SCRATCH + 0x2000
    function_name = emu.SCRATCH + 0x2100 if has_function else 0
    expression = emu.SCRATCH + 0x2200
    reent_image = bytearray(0x20)
    reent_image[0x0c:0x10] = stderr_stream.to_bytes(4, "little")
    memory = [
        (0x20002d20, reent.to_bytes(4, "little")),
        (reent, bytes(reent_image)),
        (stderr_stream, bytes(0x20)),
        (source_file, b"newlib_source.c\0"),
        (expression, b"allocation != NULL\0"),
    ]
    if has_function:
        memory.append((function_name, b"allocate_bigint\0"))
    return ({0: source_file, 1: 0x123, 2: function_name, 3: expression},
            memory, {})


REVIEWED_ORACLE_CASES[("app", 0x00076a94)] = [
    _newlib_assert_case(False),
    _newlib_assert_case(True),
]
def _img_next_boot_case(active_slot, swap_type, output=True):
    output_address = emu.SCRATCH + 0x2600 if output else 0
    memory = ([(output_address, b"\xa5")] if output else [])
    return ({0: 1, 1: output_address}, memory,
            {0: {0: int(active_slot)}, 1: {0: int(swap_type)}})


REVIEWED_ORACLE_CASES[("app", 0x000809b0)] = [
    _img_next_boot_case(0, 1),
    _img_next_boot_case(2, 1),
    _img_next_boot_case(0, 2),
    _img_next_boot_case(1, 2, output=False),
    _img_next_boot_case(2, 3),
    _img_next_boot_case(3, 4),
    _img_next_boot_case(0, 0),
    _img_next_boot_case(1, 5),
    _img_next_boot_case(4, 1),
    _img_next_boot_case(0xffffffff, 1),
]
def _smp_handle_requests_case(packet_count):
    transport = emu.SCRATCH + 0x2800
    oracles = {}
    for index in range(packet_count):
        packet = emu.SCRATCH + 0x3000 + 0x100 * index
        oracles[2 * index] = {0: packet}
        oracles[2 * index + 1] = {0: 0}
    oracles[2 * packet_count] = {0: 0}
    return ({0: transport}, [(transport, bytes(0x40))], oracles)


REVIEWED_ORACLE_CASES[("app", 0x00080ab4)] = [
    _smp_handle_requests_case(0),
    _smp_handle_requests_case(1),
    _smp_handle_requests_case(3),
]
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x00080ab4)] = [
    # GCC's readable body saves one extra register, shifting the complete
    # streamer and both CBOR adapters by eight bytes.  The adapters are
    # intentionally uninitialized here: smp_process_request_packet owns their
    # initialization, so only their object identities (not indeterminate
    # incoming bytes) are observable at this call boundary.
    ("smp-streamer", -184, -192, 12, None, None,
     (0x000513e8,), (4, 8)),
    ("smp-cbor-reader", -116, -124, 100, (), None,
     (0x000513e8,)),
    ("smp-cbor-writer", -172, -180, 56, (), None,
     (0x000513e8,)),
]


def _align_right_text_case(kind):
    source = emu.SCRATCH + 0x1800
    utf16 = emu.SCRATCH + 0x2800
    display = emu.SCRATCH + 0x3800
    memory = [
        (source, b"A\0"),
        (utf16, b"A\0\0\0"),
        (display, bytes(0xeb4) +
         (emu.SCRATCH + 0x4800).to_bytes(4, "little") +
         (emu.SCRATCH + 0x4900).to_bytes(4, "little") + bytes(0x48)),
        (emu.SCRATCH + 0x4800, bytes(0x200)),
    ]
    if kind == "skip":
        return ({0: 0, 1: source, 2: 0, 3: 10}, memory,
                {0: {0: utf16}})
    if kind == "callback":
        return ({0: 0, 1: source, 2: 0, 3: 10}, memory,
                {0: {0: utf16}, 1: {0: 0x12345678}})
    if kind == "empty-refresh":
        return ({0: 0, 1: source, 2: 0, 3: 10}, memory,
                {0: {0: utf16}, 1: {0: 2}, 2: {0: 0},
                 3: {0: 2}, 4: {0: display}, 5: {0: display},
                 6: {0: 0}})
    # One decoded glyph reaches both right-alignment measurement calls.
    writes = {
        0: [(1, 0, (1).to_bytes(2, "little"), 0x000478d8)],
        3: [(2, 0, (4).to_bytes(4, "little"), 0x0004588c),
            (3, 0, (8).to_bytes(4, "little"), 0x0004588c),
            (4, 0, (emu.SCRATCH + 0x4800).to_bytes(4, "little"),
             0x0004588c)],
    }
    if kind == "draw":
        writes[6] = list(writes[3])
        writes[7] = [
            (0, 0, bytes(range(16)), 0x00086c1e),
        ]
        return ({0: 0, 1: source, 2: 0, 3: 10}, memory,
                {0: {0: utf16}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0},
                 4: {0: 2}, 5: {0: 0}, 6: {0: 0}, 7: {0: 0},
                 8: {0: 2}, 9: {0: 0}, 10: {0: 2}, 11: {0: 0}},
                writes)
    # The bounded measurement-only case deliberately fails the second lookup
    # after the aligned origin has been calculated.
    return ({0: 0, 1: source, 2: 0, 3: 10}, memory,
            {0: {0: utf16}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0},
             4: {0: 2}, 5: {0: 0}, 6: {0: 0xffffffff},
             7: {0: 0}}, writes)


REVIEWED_ORACLE_CASES[("app", 0x00044ec4)] = [
    _align_right_text_case("skip"),
    _align_right_text_case("callback"),
    _align_right_text_case("empty-refresh"),
    _align_right_text_case("measure"),
    _align_right_text_case("draw"),
]
REVIEWED_PAIRED_STACK_INITIAL_WORDS[("app", 0x00044ec4)] = [
    (0, 0, (10, 10, 10, 10, 10)),       # top
    (4, 4, (100, 100, 100, 100, 100)),   # right
    (8, 8, (100, 100, 100, 100, 100)),   # bottom
    (12, 12, (2, 2, 2, 2, 2)),           # maximum lines
    (16, 16, (0, 0, 0, 0, 0)),           # masked-glyph prefix length
    (20, 20, (0, 1, 0, 0, 0)),           # callback mode
    (24, 24, (0, 0x00080001, 0, 0, 0)),  # callback
    (28, 28, (1, 0, 0, 0, 0)),           # skip built-in rendering
]
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00044ec4)] = {
    0x000167a8: 0,  # get_device_info
    0x00019c70: 0,  # alternate diagnostic sink
    0x000431a8: 0,  # display atomic state
    0x00043e58: 2,  # glyph pair spacing
    0x0004588c: 6,  # font, codepoint, width, height, bitmap, flags
    0x000471cc: 6,  # framebuffer clear rectangle
    0x00047260: 6,  # framebuffer refresh rectangle
    0x000478d8: 2,  # UTF-8 source and UTF-16 count output
    0x0007d53a: 6,  # glyph bitmap blit
    0x0007d860: 1,  # control-character classifier
    0x00086c1e: 4,  # checked bitmap copy
}
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x00044ec4)] = [
    # The readable frame places each small output slot four bytes lower than
    # the shipped frame.  Pair the exact objects rather than ignoring generic
    # stack-looking arguments; every written byte remains compared.
    ("align-right-utf16-count", -730, -734, 2, None, None,
     (0x000478d8,)),
    ("align-right-glyph-bitmap", -728, -732, 4, None, None,
     (0x0004588c,)),
    ("align-right-glyph-width", -724, -728, 4, None, None,
     (0x0004588c,)),
    ("align-right-glyph-height", -720, -724, 4, None, None,
     (0x0004588c,)),
    ("align-right-glyph-pixels", -716, -720, 680, None, None,
     (0x00086c1e, 0x0007d53a)),
]
REVIEWED_ORACLE_CASES[("app", 0x000777f0)] = [
    ({0: 0x11, 1: 0x22, 2: 0x33, 3: 0x44},
     [(0x20002d20, (emu.SCRATCH + 0x1200).to_bytes(4, "little")),
      (emu.SCRATCH + 0x1200, bytes(0x20))], {}),
    ({0: 0xa1, 1: 0xb2, 2: 0xc3, 3: 0xd4},
     [(0x20002d20, (emu.SCRATCH + 0x1300).to_bytes(4, "little")),
      (emu.SCRATCH + 0x1300, bytes(0x18) + (1).to_bytes(4, "little"))], {}),
]

# Complete queue and logger branch families for the six-byte display payload
# carried inside its fixed 24-byte transport record.
REVIEWED_ORACLE_CASES[("app", 0x00049938)] = [
    ({0: input_value, 1: input_state},
     [(0x2000230c, int(level).to_bytes(4, "little", signed=True)),
      (0x20007554, int(sink).to_bytes(4, "little"))],
     {1: {0: send_result}})
    for input_value, input_state, level, sink, send_result in (
        (0x12, 0x34, 0, 0, -5), # negative queue failure diagnostic
        (0x56, 0x78, 2, 0, 0),  # success below the logging threshold
        (0x9a, 0xbc, 3, 0, 0),  # direct logger success diagnostic
        (0xde, 0xf0, 3, 1, 0),  # alternate logger success diagnostic
    )
]


def _dmic_record_start_case(level, sink, old_flag):
    device = emu.SCRATCH + 0x4000
    memory = [
        (device, bytes(0x1100)),
        (0x2000230c, int(level).to_bytes(4, "little", signed=True)),
        (0x20007554, int(sink).to_bytes(4, "little")),
        (0x20007b78, int(old_flag).to_bytes(4, "little")),
    ]
    if level <= 2:
        getter_ordinals = (0, 3, 4)
    else:
        getter_ordinals = (0, 4, 5)
    return ({}, memory,
            {ordinal: {0: device} for ordinal in getter_ordinals})


REVIEWED_ORACLE_CASES[("app", 0x0003b78c)] = [
    _dmic_record_start_case(0, 0, 0),
    _dmic_record_start_case(3, 0, 0x11223344),
    _dmic_record_start_case(3, 1, 1),
]


def _local_store_write_case(suffix, result, level, sink, length):
    suffix_address = emu.SCRATCH + 0x1800
    value_address = emu.SCRATCH + 0x2000
    suffix_bytes = suffix.encode("ascii") + b"\0"
    return (
        {0: suffix_address, 1: value_address, 2: length},
        [(0x0009e145, b"ar_glass_userdata_settings/\0"),
         (suffix_address, suffix_bytes),
         (value_address, bytes((index * 19 + 7) & 0xff for index in range(64))),
         (0x2000230c, int(level).to_bytes(4, "little", signed=True)),
         (0x20007554, int(sink).to_bytes(4, "little"))],
        {2: {0: result}},
        {1: [(0, 27, suffix_bytes, 0x00086fbe)]},
    )


REVIEWED_ORACLE_CASES[("app", 0x00022168)] = [
    _local_store_write_case("brightness", 0, 2, 0, 16),
    _local_store_write_case("language", 0, 3, 0, 8),
    _local_store_write_case("gesture", 0, 3, 1, 4),
    _local_store_write_case("display", -5, 0, 0, 32),
    _local_store_write_case("timeout", -5, 1, 0, 4),
    _local_store_write_case("critical", -5, 1, 1, 1),
]


def _user_settings_record(display=10, interaction=1, primary=3,
                          secondary=3, boolean_mode=1, critical=0,
                          timeout=400, counter=7):
    record = bytearray(32)
    record[0] = display
    record[1] = 0x15
    record[2] = 0x14
    record[3] = interaction
    record[4:8] = int(timeout).to_bytes(4, "little")
    record[8] = 6
    record[9] = 1
    record[10] = 2
    record[11] = primary
    record[12:16] = (0x12345678).to_bytes(4, "little")
    record[16:18] = (0x3456).to_bytes(2, "little")
    record[18] = 0x9a
    record[19] = 0x11
    record[20] = boolean_mode
    record[21] = 0x22
    record[22] = 0x33
    record[23] = critical
    record[24] = secondary
    record[28:32] = (counter & 0xffffffff).to_bytes(4, "little")
    return bytes(record)


def _load_usr_setting_case(record, read_result, level, sink, critical_result=0):
    settings = emu.SCRATCH + 0x3000
    memory = [
        (settings, b"\xa5" * 0x1200),
        (0x2000230c, int(level).to_bytes(4, "little", signed=True)),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]
    oracles = {1: {0: read_result}}
    writes = {1: [(1, 0, record, 0x000225b4)]}
    if read_result == 0:
        ordinal = 2
        if level > 1:
            ordinal += 1
        if record[0] & record[3] == 0xff:
            ordinal += 1
        if record[0] == 11:
            ordinal += 1
        # FUN_00032ef0 precedes the zero-argument critical-state query.
        oracles[ordinal + 1] = {0: critical_result}
    return ({0: settings}, memory, oracles, writes)


REVIEWED_ORACLE_CASES[("app", 0x00022e78)] = [
    _load_usr_setting_case(_user_settings_record(), -5, 0, 0),
    _load_usr_setting_case(_user_settings_record(), -5, 2, 0),
    _load_usr_setting_case(_user_settings_record(), -5, 2, 1),
    _load_usr_setting_case(_user_settings_record(timeout=0), 0, 0, 0),
    _load_usr_setting_case(_user_settings_record(display=11), 0, 0, 0),
    _load_usr_setting_case(
        _user_settings_record(display=0xff, interaction=0xff, primary=12,
                              secondary=10, boolean_mode=3, critical=3,
                              counter=-1),
        0, 2, 0, critical_result=1),
    _load_usr_setting_case(_user_settings_record(critical=1), 0, 2, 1,
                           critical_result=0),
]


REVIEWED_ORACLE_CASES[("app", 0x00022ddc)] = [
    ({0: emu.SCRATCH + 0x3000},
     [(emu.SCRATCH + 0x3000, b"\xa5" * 0x1200),
      (0x2000230c, int(level).to_bytes(4, "little", signed=True)),
      (0x20007554, int(sink).to_bytes(4, "little"))], {})
    for level, sink in ((0, 0), (3, 0), (3, 1))
]


def _runtime_info_sync_case(payload, result, pending, level, sink):
    runtime = emu.SCRATCH + 0x1800
    return (
        {0: runtime},
        [(runtime, bytes(payload)),
         (0x20002fe0, bytes((pending,))),
         (0x2000230c, int(level).to_bytes(4, "little", signed=True)),
         (0x20007554, int(sink).to_bytes(4, "little"))],
        {0: {0: result}},
    )


REVIEWED_ORACLE_CASES[("app", 0x00016268)] = [
    _runtime_info_sync_case((0x12, 0x34, 0x56, 0x78, 0x9a), 0, 0, 0, 0),
    _runtime_info_sync_case((0xa1, 0xb2, 0xc3, 0xd4, 0xe5), -5, 1, 1, 0),
    _runtime_info_sync_case((1, 2, 3, 4, 5), 0x11223344, 1, 2, 0),
    _runtime_info_sync_case((0xfe, 0xdc, 0xba, 0x98, 0x76), 7, 1, 2, 1),
]


def _onboarding_ble_case(opcode, response_kind=2, level=0, sink=0,
                         persistence_state=14, persistence_result=1):
    device = emu.SCRATCH + 0x1000
    request = emu.SCRATCH + 0x2400
    command = emu.SCRATCH + 0x2500
    response = emu.SCRATCH + 0x2600
    context = emu.SCRATCH + 0x3000
    persisted_state = emu.SCRATCH + 0x3800

    device_data = bytearray(0x1100)
    device_data[0xed5] = 0x21
    device_data[0xee4] = 0x43
    device_data[0x1014:0x1018] = context.to_bytes(4, "little")
    device_data[0x1054:0x1058] = persisted_state.to_bytes(4, "little")
    request_data = bytearray(8)
    request_data[2:4] = int(response_kind).to_bytes(2, "little")
    command_data = bytes((0x5a, opcode & 0xff, 0xa6, 0, 0, 0, 0, 0))
    context_data = bytearray(0x40)
    context_data[0] = 1
    state_data = bytearray(8)
    state_data[0:4] = int(persistence_state).to_bytes(4, "little")
    memory = [
        (device, bytes(device_data)),
        (request, bytes(request_data)),
        (command, command_data),
        (response, b"\xcc" * 8),
        (context, bytes(context_data)),
        (persisted_state, bytes(state_data)),
        (0x20004bf0, bytes(16)),
        (0x2000230c, int(level).to_bytes(4, "little", signed=True)),
        (0x20007554, int(sink).to_bytes(4, "little")),
        (0x2001cdce, b"\x7e"), (0x2001cdcf, b"\x7d"),
        (0x2001cdd2, b"\x7c"),
        (0x000aa661, (0x11111111).to_bytes(4, "little")),
        (0x000aa665, (0x22222222).to_bytes(4, "little")),
        (0x000aa669, (0x33333333).to_bytes(4, "little")),
        (0x000aa66d, (0x44444444).to_bytes(4, "little")),
        (0x000aa671, (0x55555555).to_bytes(4, "little")),
        (0x000aa675, (0x66666666).to_bytes(4, "little")),
    ]
    oracles = {}
    if opcode > 0x17:
        return ({0: device, 1: request, 2: command, 3: response},
                memory, oracles)

    oracles[0] = {0: 0x55667788, 1: 0x11223344}
    if opcode == 0x12:
        return ({0: device, 1: request, 2: command, 3: response},
                memory, oracles)

    oracles[2] = {0: 0xddeeff00, 1: 0x99aabbcc}
    ordinal = 3
    if level > 2:
        ordinal += 1
    if opcode in (4, 5, 6):
        oracles[ordinal] = {0: device}
        ordinal += 1
    elif opcode in (15, 17):
        oracles[ordinal] = {0: device}
        oracles[ordinal + 1] = {0: device}
        ordinal += 2

    ordinal += 1  # post-switch onboarding continuation
    oracles[ordinal] = {0: device}
    ordinal += 1
    if persistence_state != 14:
        oracles[ordinal] = {0: persistence_result}
        ordinal += 1
        if persistence_result == 0:
            oracles[ordinal] = {0: device}
            oracles[ordinal + 2] = {0: device}
            oracles[ordinal + 3] = {0: device}
            oracles[ordinal + 4] = {0: device}
    return ({0: device, 1: request, 2: command, 3: response},
            memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x00042a64)] = [
    *[
        _onboarding_ble_case(
            opcode, response_kind=2 + opcode % 3,
            level=(3 if opcode in (3, 6) else 0),
            sink=(1 if opcode == 6 else 0),
            persistence_state=(0 if opcode in (3, 6) else 14),
            persistence_result=(0 if opcode == 6 else 1),
        )
        for opcode in range(24)
    ],
    _onboarding_ble_case(24, level=1, sink=0),
    _onboarding_ble_case(0xff, level=1, sink=1),
]


REVIEWED_ORACLE_CASES[("app", 0x000497b0)] = [
    # Maximum valid payload, null-payload record, direct/fallback success
    # diagnostics, transport failure, and the first rejected length.
    ({0: emu.SCRATCH + 0x1000, 1: 10},
     [(emu.SCRATCH + 0x1000, b"0123456789"),
      (0x2000230c, (1).to_bytes(4, "little")),
      (0x20007554, bytes(4))], {2: {0: 0}}),
    ({0: 0, 1: 5},
     [(0x2000230c, bytes(4)), (0x20007554, bytes(4))],
     {1: {0: 0}}),
    ({0: emu.SCRATCH + 0x1000, 1: 4},
     [(emu.SCRATCH + 0x1000, b"CLOS"),
      (0x2000230c, (1).to_bytes(4, "little")),
      (0x20007554, (1).to_bytes(4, "little"))], {2: {0: 0}}),
    ({0: emu.SCRATCH + 0x1000, 1: 4},
     [(emu.SCRATCH + 0x1000, b"FAIL"),
      (0x2000230c, (1).to_bytes(4, "little")),
      (0x20007554, bytes(4))], {2: {0: 1}}),
    ({0: emu.SCRATCH + 0x1000, 1: 11},
     [(emu.SCRATCH + 0x1000, b"TOO-LONG!!!"),
      (0x2000230c, (1).to_bytes(4, "little")),
      (0x20007554, bytes(4))], {}),
]

REVIEWED_ORACLE_CASES[("app", 0x00049a28)] = [
    ({0: 1}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4))],
     {1: {0: 0}}),
    ({0: 0}, [(0x2000230c, (3).to_bytes(4, "little")),
              (0x20007554, bytes(4))], {1: {0: 0}}),
    ({0: 2}, [(0x2000230c, (3).to_bytes(4, "little")),
              (0x20007554, (1).to_bytes(4, "little"))], {1: {0: 0}}),
    ({0: 1}, [(0x2000230c, (3).to_bytes(4, "little")),
              (0x20007554, bytes(4))], {1: {0: 1}}),
]


def _draw_translate_case(direction, screen, icon, level=0, sink=0):
    state = bytearray(0x110)
    state[0xef] = direction
    state[0xf0] = screen
    state[0xf1] = icon
    state[0xf5:0xfb] = b"LABEL\0"
    return (
        {0: emu.SCRATCH + 0x3000},
        [(emu.SCRATCH + 0x1000, bytes(state)),
         (0x2000230c, int(level).to_bytes(4, "little")),
         (0x20007554, int(sink).to_bytes(4, "little")),
         (0x200024f4, bytes.fromhex(
             "10000000200000003000000040000000"
             "50000000600000007000000080000000"))],
        {0: {0: emu.SCRATCH + 0x1000}},
    )


REVIEWED_ORACLE_CASES[("app", 0x0003fd44)] = [
    _draw_translate_case(1, 1, 1),
    _draw_translate_case(8, 8, 0),
    _draw_translate_case(1, 0, 1, 1, 0),
    _draw_translate_case(9, 9, 0, 1, 1),
]


def _mobile_notification_case(level, sink):
    payload = emu.SCRATCH + 0x3000
    ef12_ordinal = 11 if level > 2 else 10
    return (
        {0: emu.SCRATCH + 0x4000, 1: emu.SCRATCH + 0x5000,
         2: 0x0007c244},
        [(emu.SCRATCH + 0x1000, bytes(0x100)),
         (emu.SCRATCH + 0x2000, bytes(0x100)),
         (payload, b'{"notification":true}\0' + bytes(0x20)),
         (0x2000230c, int(level).to_bytes(4, "little")),
         (0x20007554, int(sink).to_bytes(4, "little"))],
        {0: {0: emu.SCRATCH + 0x1000},
         7: {0: emu.SCRATCH + 0x2000},
         9: {0: payload}, ef12_ordinal: {0: 21}},
    )


REVIEWED_ORACLE_CASES[("app", 0x00021c04)] = [
    _mobile_notification_case(0, 0),
    _mobile_notification_case(3, 0),
    _mobile_notification_case(3, 1),
]

REVIEWED_ORACLE_CASES[("app", 0x0003dff8)] = [
    ({0: direction, 1: 0x11223344, 2: 0x55667788},
     [(0x2000230c, bytes(4)), (0x20007554, bytes(4))],
     {0: {0: 100}, 1: {0: 200}})
    for direction in (1, 35)
] + [
    ({0: direction, 1: 0x11223344, 2: 0x55667788},
     [(0x2000230c, int(level).to_bytes(4, "little")),
      (0x20007554, int(sink).to_bytes(4, "little"))], {})
    for direction, level, sink in ((0, 0, 0), (0, 2, 0), (36, 2, 1))
]


def _dmic_send_case(sequence, prepared, decoded, callback_result=0,
                    failures=0, cadence=0, level=0, sink=0):
    transport = emu.SCRATCH + 0x1000
    memory = [
        (transport, bytes(0x0c) + (0x00080001).to_bytes(4, "little") +
         bytes(0x20)),
        (0x20010321, bytes((sequence,))),
        (0x20007558, int(failures).to_bytes(4, "little")),
        (0x2000755c, int(cadence).to_bytes(4, "little")),
        (0x20007560, (2).to_bytes(4, "little")),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
        (emu.SCRATCH + 0x2000, bytes(0x400)),
    ]
    oracles = {1: {0: prepared}}
    if prepared:
        oracles[2] = {0: decoded}
    if prepared and decoded == 0:
        oracles[3] = {0: callback_result}
        if callback_result & 0x80000000 and failures >= 9:
            oracles[4] = {0: emu.SCRATCH + 0x2000}
        elif cadence >= 99:
            oracles[4] = {0: 0x00008000, 1: 0}
    return ({0: transport}, memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x00019ed4)] = [
    _dmic_send_case(3, 0, 0),
    _dmic_send_case(3, 1, 0xfffffffb),
    _dmic_send_case(3, 1, 0, 0),
    _dmic_send_case(3, 1, 0, 0xffffffff, failures=9, level=1, sink=0),
    _dmic_send_case(3, 1, 0, 0xffffffff, failures=9, level=1, sink=1),
    _dmic_send_case(3, 1, 0, 0, cadence=99, level=1, sink=0),
    _dmic_send_case(3, 1, 0, 0, cadence=99, level=1, sink=1),
]


def _send_event_case(event_id, pending, active, work):
    state = bytearray(0x260)
    state[0x248] = active
    state[0x220:0x224] = int(work).to_bytes(4, "little")
    return (
        {0: event_id, 1: 0x11223344, 2: 0x55667788},
        [(emu.SCRATCH + 0x1000, bytes(state)),
         (0x2000302e, bytes((pending,)))],
        {0: {0: emu.SCRATCH + 0x1000}},
    )


REVIEWED_ORACLE_CASES[("app", 0x000276ec)] = [
    _send_event_case(0xf0, 0, 1, 0),
    _send_event_case(0xf0, 0xff, 1, 0),
    _send_event_case(0x20, 0, 0, 1),
    _send_event_case(0x20, 0, 0, 0),
]


# Optional inherited local-exclusive monitor state, one entry per reviewed
# production case.  This models callers that branch into a store-exclusive
# adapter after establishing the monitor outside the callee.
REVIEWED_INITIAL_EXCLUSIVE_MONITORS = {}

REVIEWED_FP_CASES = {
    # Preserve the incoming hard-float value across the default-value helper;
    # cover disabled conversion, unordered input, and an ordinary conversion.
    ("app", 0x00075c2c): [
        {0: 0x3f400000}, {0: 0x7fc00001}, {0: 0x40000000},
    ],
    # Binary64 classification and rounding boundaries: signed zeros, the
    # subnormal path, sub-unit finite values, fractional/integral normals,
    # wide mantissas, infinities, and NaN.
    ("app", 0x000767c8): [
        {0: 0x00000000, 1: 0x00000000},
        {0: 0x00000000, 1: 0x80000000},
        {0: 0x00000001, 1: 0x00000000},
        {0: 0x00000000, 1: 0x3fe00000},
        {0: 0x00000000, 1: 0xbfe00000},
        {0: 0x80000000, 1: 0x3ff80000},
        {0: 0x00000000, 1: 0x40000000},
        {0: 0x00000001, 1: 0x43300000},
        {0: 0x00000000, 1: 0x7ff00000},
        {0: 0x00000001, 1: 0x7ff80000},
    ],
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
    # Binary64 pow: signed zero, identity, domain-error, square-root,
    # ordinary positive/negative integer powers and infinities.
    ("app", 0x000133f8): [
        {0: 0x00000000, 1: 0x00000000, 2: 0x00000000, 3: 0x40000000},
        {0: 0x00000000, 1: 0x80000000, 2: 0x00000000, 3: 0x40080000},
        {0: 0x00000000, 1: 0x3ff00000, 2: 0x00000000, 3: 0x405ec000},
        {0: 0x00000000, 1: 0xbff00000, 2: 0x00000000, 3: 0x3fe00000},
        {0: 0x00000000, 1: 0x40100000, 2: 0x00000000, 3: 0x3fe00000},
        {0: 0x00000000, 1: 0x40000000, 2: 0x00000000, 3: 0x40080000},
        {0: 0x00000000, 1: 0x3fe00000, 2: 0x00000000, 3: 0xc0000000},
        {0: 0x00000000, 1: 0xc0000000, 2: 0x00000000, 3: 0x40080000},
        {0: 0x00000000, 1: 0xc0000000, 2: 0x00000000, 3: 0x40000000},
        {0: 0x00000000, 1: 0x7ff00000, 2: 0x00000000, 3: 0x40000000},
        {0: 0x00000000, 1: 0x40000000, 2: 0x00000000, 3: 0x7ff00000},
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

# FUN_000133f8 reaches the firmware's VFP sqrt tail helper, which takes its
# sole double argument in d0; the core-register arity is therefore zero.
REVIEWED_TARGET_CALL_ARITIES[("app", 0x000133f8)] = {0x00075e14: 0}

POINTER_READ_TRANSITION_CASES = {
    ("app", 0x00084a54): [
        [(0, 0, 0x110, 1, 1)],
        [(0, 0, 0x110, 1, 1)],
        [(0, 0, 0x110, 1, 1)],
        [(0, 0, 0x110, 1, 1), (0, 0, 0x53c, 2, 8)],
    ],
}


def _sdc_ecb_case(lock_result, sev_on_pend=False, retry_on_relax=False):
    """Complete nRF ECB ownership, MMIO and architectural wait state."""
    ecb = 0x4100d000
    ownership = 0x21000bf4
    oracles = {0: {0: int(lock_result) & 0xffffffff}}
    oracle_writes = {}
    if retry_on_relax:
        # A contending caller observes ownership and sets the adjacent retry
        # byte while this transaction is in the reviewed relax hook.
        oracles[3] = {0: (-35) & 0xffffffff}
        oracle_writes = {1: [
            (None, ownership + 1, b"\x01", 0x0102a21e),
        ]}
    return (
        {0: emu.SCRATCH + 0x1000},
        [(ownership, bytes(2)),
         # The transaction buffer is caller-owned and the peripheral only
         # consumes it; a nonuniform image catches pointer truncation/swaps.
         (emu.SCRATCH + 0x1000, bytes(range(48))),
         (ecb, bytes(0x600)),
         (0xe000ed10, (0x10 if sev_on_pend else 0).to_bytes(4, "little")),
         (0xe000e280, bytes(4))],
        oracles,
        oracle_writes,
    )


# The first completion read covers ordinary success and recursive ownership;
# ERROR on the first attempt followed by END on the second proves retry.  The
# two SEVONPEND cases wait through the weak relax hook and cover both incoming
# PRIMASK restoration outcomes.
REVIEWED_ORACLE_CASES[("net", 0x0100a7e8)] = [
    _sdc_ecb_case(0),
    _sdc_ecb_case(-35),
    _sdc_ecb_case(0),
    _sdc_ecb_case(0, sev_on_pend=True),
    _sdc_ecb_case(0, sev_on_pend=True),
    _sdc_ecb_case(0, sev_on_pend=True, retry_on_relax=True),
]

ABSOLUTE_READ_TRANSITION_CASES = {
    ("net", 0x0100a7e8): [
        [(0x4100d100, 1, 1)],
        [(0x4100d100, 1, 1)],
        [(0x4100d104, 1, 1), (0x4100d100, 2, 1)],
        [(0x4100d100, 3, 1)],
        [(0x4100d100, 3, 1)],
        [(0x4100d100, 3, 1), (0x4100d100, 4, 1)],
    ],
}

REVIEWED_INITIAL_PRIMASK_CASES = {
    ("net", 0x0100a7e8): [0, 0, 0, 0, 1, 0],
}


_CTRL_PACKET = emu.SCRATCH + 0x1000
_CTRL_NODE = emu.SCRATCH + 0x3000
_CTRL_SENTINEL = emu.SCRATCH + 0x3100
_CTRL_CONTEXT = emu.SCRATCH + 0x3200
_CTRL_CALLBACK = 0x00080001


def _controller_packet_case(state, *, current=True, head_state=1,
                            context=None, context_cb=0, release_cb=0,
                            handle_cb=0, flow_flag=0, flow_count=1,
                            packet=b"", oracle_returns=None,
                            oracle_writes=None, next_state=1):
    """One bounded controller queue/node and packet-production transaction."""
    queue = bytearray(0x2c)
    head = _CTRL_SENTINEL if current else _CTRL_NODE
    queue[8:12] = head.to_bytes(4, "little")
    queue[0x14:0x18] = (_CTRL_NODE if current else 0).to_bytes(4, "little")
    node = bytearray(0x20)
    node[0:4] = _CTRL_SENTINEL.to_bytes(4, "little")
    if context is None:
        context = _CTRL_CALLBACK
    node[4:8] = int(context).to_bytes(4, "little")
    node[8] = int(state) & 0xff
    node[9:13] = b"\x11\x22\x33\x44"
    sentinel = bytearray(0x20)
    sentinel[0:4] = _CTRL_SENTINEL.to_bytes(4, "little")
    sentinel[8] = int(head_state if current else next_state) & 0xff
    flow = bytearray(0x30)
    flow[0x17] = int(flow_flag) & 0xff
    flow[0x18:0x1a] = int(flow_count).to_bytes(2, "little")
    ctx = bytearray(0x20)
    ctx[0:2] = (0x1357).to_bytes(2, "little")
    ctx[8:10] = (0x2468).to_bytes(2, "little")
    callbacks = (int(handle_cb).to_bytes(4, "little") +
                 int(context_cb).to_bytes(4, "little") +
                 int(release_cb).to_bytes(4, "little"))
    packet_image = bytearray(0x40)
    packet_image[:len(packet)] = packet
    return (
        {0: _CTRL_PACKET},
        [(0x21000ec8, bytes(queue)),
         (0x21000eac, bytes(flow)),
         (0x21000054, callbacks),
         (_CTRL_NODE, bytes(node)),
         (_CTRL_SENTINEL, bytes(sentinel)),
         (_CTRL_CONTEXT, bytes(ctx)),
         (_CTRL_PACKET, bytes(packet_image))],
        dict(oracle_returns or {}),
        dict(oracle_writes or {}),
    )


def _packet_callback_write(data, offset=0, ordinal=0):
    return {ordinal: [(1, offset, bytes(data), _CTRL_CALLBACK & ~1)]}


_CONTROLLER_PACKET_CASES = [
    # Top-level flow gate, empty sentinel, and dequeue of a stale zero node.
    _controller_packet_case(16, head_state=16, flow_flag=1, flow_count=0),
    _controller_packet_case(2, head_state=16, flow_flag=0, flow_count=0),
    _controller_packet_case(2, head_state=16, flow_flag=1, flow_count=1),
    _controller_packet_case(1, current=False, next_state=1),
    _controller_packet_case(0, current=False, next_state=1),
    _controller_packet_case(0),
    # Dequeue a live callback node with interrupts initially enabled/disabled.
    _controller_packet_case(2, current=False, next_state=1),
    _controller_packet_case(2, current=False, next_state=1),
    # Callback changed the state concurrently: restart once, then complete.
    _controller_packet_case(
        2, oracle_writes={0: [(0, 8, b"\x02", _CTRL_CALLBACK & ~1)]}),
    _controller_packet_case(
        2, oracle_writes={0: [(0, 8, b"\x00", _CTRL_CALLBACK & ~1)]}),
    # Result callbacks: ordinary packet, direct deferred result, and retry.
    _controller_packet_case(3, oracle_returns={0: {0: 4}}),
    _controller_packet_case(3, oracle_returns={0: {0: 0x0107}}),
    _controller_packet_case(3, oracle_returns={0: {0: 0x0100}, 1: {0: 4}}),
    _controller_packet_case(4),
    # Radio packet completion: either activity flag, then the clear/restart arm.
    _controller_packet_case(6, oracle_returns={1: {0: 1}}),
    _controller_packet_case(6, oracle_returns={1: {0: 0}, 2: {0: 1}}),
    _controller_packet_case(6, oracle_returns={1: {0: 0}, 2: {0: 0}}),
    # Context callback family, including absent callback and type-13 completion.
    _controller_packet_case(7, context_cb=0),
    _controller_packet_case(7, context_cb=_CTRL_CALLBACK),
    _controller_packet_case(9, context_cb=_CTRL_CALLBACK),
    _controller_packet_case(12, context_cb=_CTRL_CALLBACK),
    _controller_packet_case(13, context_cb=_CTRL_CALLBACK),
    _controller_packet_case(14, context_cb=_CTRL_CALLBACK),
    # Handle lookup packet construction and both fatal validation arms.
    _controller_packet_case(8, context=_CTRL_CONTEXT,
                            oracle_returns={0: {0: 0x2468}}),
    _controller_packet_case(8, context=0),
    _controller_packet_case(8, context=_CTRL_CONTEXT,
                            oracle_returns={0: {0: 0}}),
    # Release callback absent, ordinary packet, and both release packet forms.
    _controller_packet_case(10, context=_CTRL_CONTEXT, release_cb=0),
    _controller_packet_case(
        10, context=_CTRL_CONTEXT, release_cb=_CTRL_CALLBACK,
        oracle_writes=_packet_callback_write(b"\x09")),
    _controller_packet_case(
        10, context=_CTRL_CONTEXT, release_cb=_CTRL_CALLBACK,
        oracle_returns={1: {0: 0}},
        oracle_writes=_packet_callback_write(b"\x1d")),
    _controller_packet_case(
        11, context=_CTRL_CONTEXT, release_cb=_CTRL_CALLBACK,
        oracle_returns={1: {0: 0}},
        oracle_writes=_packet_callback_write(b"\x1a\x00\x01")),
    _controller_packet_case(
        11, context=_CTRL_CONTEXT, release_cb=_CTRL_CALLBACK,
        oracle_returns={1: {0: 3}},
        oracle_writes=_packet_callback_write(b"\x1d")),
    _controller_packet_case(15),
    # Handle callback absent/present and null-context assertion.
    _controller_packet_case(16, handle_cb=0),
    _controller_packet_case(16, context=_CTRL_CONTEXT,
                            handle_cb=_CTRL_CALLBACK),
    _controller_packet_case(16, context=0, handle_cb=_CTRL_CALLBACK),
    # Every distinct callback-null assertion plus switch default.
    _controller_packet_case(2, context=0),
    _controller_packet_case(3, context=0),
    _controller_packet_case(4, context=0),
    _controller_packet_case(6, context=0),
    _controller_packet_case(5),
    _controller_packet_case(17),
]

REVIEWED_ORACLE_CASES[("net", 0x0100ec88)] = _CONTROLLER_PACKET_CASES
REVIEWED_INITIAL_PRIMASK_CASES[("net", 0x0100ec88)] = [
    1 if index == 7 else 0 for index in range(len(_CONTROLLER_PACKET_CASES))
]


_RTC1_CALLBACK = 0x00080001
_RTC_INVALID_TIME = (1 << 64) - 1


def _rtc_nrf_isr_case(intenset=0, overflow_event=0, overflow_count=7,
                      force_mask=0, compare_events=(0, 0),
                      current_times=(0, 0),
                      deadlines=(_RTC_INVALID_TIME, _RTC_INVALID_TIME),
                      callbacks=(0, 0),
                      contexts=(0x11223344, 0x55667788)):
    """One bounded Zephyr RTC1 overflow/compare interrupt transaction."""
    rtc = bytearray(0x550)
    rtc[0x104:0x108] = int(overflow_event).to_bytes(4, "little")
    rtc[0x140:0x144] = int(compare_events[0]).to_bytes(4, "little")
    rtc[0x144:0x148] = int(compare_events[1]).to_bytes(4, "little")
    rtc[0x304:0x308] = int(intenset).to_bytes(4, "little")
    channel_data = bytearray(0x20)
    for channel in range(2):
        offset = channel * 0x10
        channel_data[offset:offset + 4] = int(callbacks[channel]).to_bytes(
            4, "little")
        channel_data[offset + 4:offset + 8] = int(contexts[channel]).to_bytes(
            4, "little")
        channel_data[offset + 8:offset + 16] = int(deadlines[channel]).to_bytes(
            8, "little")

    oracles = {0: {}}
    ordinal = 1
    for channel in range(2):
        interrupt_mask = 0x10000 << channel
        channel_bit = 1 << channel
        if ((intenset & interrupt_mask) != 0 and
                ((force_mask & channel_bit) != 0 or
                 compare_events[channel] != 0)):
            oracles[ordinal] = {}  # rtc_compare_event_clear(channel)
            ordinal += 1
            now = int(current_times[channel])
            oracles[ordinal] = {
                0: now & 0xffffffff, 1: (now >> 32) & 0xffffffff,
            }
            ordinal += 1
            if now >= int(deadlines[channel]):
                # The real outlined leaf preserves r0/r1.  Model that concrete
                # implementation, because rtc_nrf_isr deliberately retains
                # channel and handler across this compiler-created boundary.
                oracles[ordinal] = {
                    0: channel, 1: int(callbacks[channel]),
                }
                ordinal += 1
                if callbacks[channel] != 0:
                    oracles[ordinal] = {}  # installed compare callback
                    ordinal += 1

    return (
        {},
        [(0x41016000, bytes(rtc)),
         (0x21004964, int(force_mask).to_bytes(4, "little")),
         (0x21004970, int(overflow_count).to_bytes(4, "little")),
         (0x21002b60, bytes(channel_data))],
        oracles,
    )


_RTC_NRF_ISR_CASES = [
    # Disabled and enabled-but-not-pending overflow, then real overflow.
    _rtc_nrf_isr_case(),
    _rtc_nrf_isr_case(intenset=0x2),
    _rtc_nrf_isr_case(intenset=0x2, overflow_event=1),
    # Compare zero: no trigger, forced future deadline, event-driven due/null,
    # and due callback with incoming interrupts already masked.
    _rtc_nrf_isr_case(intenset=0x10000),
    _rtc_nrf_isr_case(intenset=0x10000, force_mask=1,
                      current_times=(99, 0),
                      deadlines=(100, _RTC_INVALID_TIME)),
    _rtc_nrf_isr_case(intenset=0x10000, compare_events=(1, 0),
                      current_times=(100, 0),
                      deadlines=(100, _RTC_INVALID_TIME)),
    _rtc_nrf_isr_case(intenset=0x10000, compare_events=(1, 0),
                      current_times=(0x100000002, 0),
                      deadlines=(0x100000001, _RTC_INVALID_TIME),
                      callbacks=(_RTC1_CALLBACK, 0)),
    # Channel one proves the loop index, shifted masks, second data record,
    # callback channel value, and fifth (stacked) user-context argument.
    _rtc_nrf_isr_case(intenset=0x20000, compare_events=(0, 1),
                      current_times=(0, 0x200000003),
                      deadlines=(_RTC_INVALID_TIME, 0x200000002),
                      callbacks=(0, _RTC1_CALLBACK)),
    # Both channels in one IRQ prove ordered clear/read/callback boundaries.
    _rtc_nrf_isr_case(intenset=0x30002, overflow_event=1, force_mask=1,
                      compare_events=(0, 1),
                      current_times=(10, 21), deadlines=(11, 20),
                      callbacks=(0, _RTC1_CALLBACK)),
]

REVIEWED_ORACLE_CASES[("net", 0x010315f0)] = _RTC_NRF_ISR_CASES
REVIEWED_INITIAL_PRIMASK_CASES[("net", 0x010315f0)] = [
    1 if index == 6 else 0 for index in range(len(_RTC_NRF_ISR_CASES))
]
REVIEWED_TARGET_CALL_ARITIES[("net", 0x010315f0)] = {
    0x01039e4e: 0,
    0x0103a6ae: 1,
    0x010313a8: 0,
}
REVIEWED_CALL_ARGUMENT_INDICES_BY_TARGET[("net", 0x010315f0)] = {
    _RTC1_CALLBACK & ~1: (0, 2, 3),
}
REVIEWED_TARGET_CALL_STACK_ARITIES[("net", 0x010315f0)] = {
    _RTC1_CALLBACK & ~1: 1,
}


_TIMING_SNAPSHOT_OUT = emu.SCRATCH + 0x1000
_TIMING_RADIO_STATE = emu.SCRATCH + 0x3000


def _timing_snapshot_refresh_case(phy, timeout_units=0):
    """Refresh-path fixture with a one-slot schedule and empty ticker list."""
    state = bytearray(0x78)
    state[4:8] = (120).to_bytes(4, "little")
    state[8:12] = (100).to_bytes(4, "little")
    state[0x30:0x38] = (0x7fffffffffffffff).to_bytes(8, "little")
    state[0x50:0x58] = (9000).to_bytes(8, "little")
    state[0x74:0x76] = (10).to_bytes(2, "little", signed=True)
    radio = bytearray(0x20)
    radio[5] = int(phy) & 0xff
    # state pointer, 64-bit clock, slot overhead, lock, empty tail, insert,
    # unlock, PHY timing, drift clamp, and final radio overhead.
    oracles = {
        0: {0: _TIMING_RADIO_STATE},
        1: {0: 10000, 1: 0},
        2: {0: 20},
        3: {},
        4: {0: 0},
        5: {},
        6: {},
    }
    if phy in (1, 2, 4, 8):
        oracles.update({7: {0: 50}, 8: {0: 0}, 9: {0: 193}})
    return (
        {0: _TIMING_SNAPSHOT_OUT, 1: 1, 2: 1, 3: timeout_units},
        [(0x210010a0, bytes(state)),
         (_TIMING_RADIO_STATE, bytes(radio)),
         (_TIMING_SNAPSHOT_OUT, bytes(0x20)),
         (0x2100113c, bytes(0x30))],
        oracles,
    )


def _timing_snapshot_existing_case(phy):
    """Checksum-valid active schedule; no ticker-list refresh is required."""
    state = bytearray(0x78)
    state[4:8] = (120).to_bytes(4, "little")
    state[8:12] = (100).to_bytes(4, "little")
    state[0x30:0x38] = (0x7fffffffffffffff).to_bytes(8, "little")
    radio = bytearray(0x20)
    radio[5] = int(phy) & 0xff
    oracles = {
        0: {0: _TIMING_RADIO_STATE},
        1: {0: 10000, 1: 0},
        2: {0: 20},
    }
    if phy in (1, 2, 4, 8):
        oracles.update({3: {0: 50}, 4: {0: 50}, 5: {0: 193}})
    return (
        {0: _TIMING_SNAPSHOT_OUT, 1: 0, 2: 1, 3: 0},
        [(0x210010a0, bytes(state)),
         (_TIMING_RADIO_STATE, bytes(radio)),
         (_TIMING_SNAPSHOT_OUT, bytes(0x20))],
        oracles,
    )


def _timing_snapshot_advance_case(phy):
    """Checksum-stale ordinary advance through slot/PHY airtime selection."""
    state = bytearray(0x78)
    state[4:8] = (1000).to_bytes(4, "little")
    state[8:12] = (100).to_bytes(4, "little")
    state[0x18:0x20] = (9000).to_bytes(8, "little")
    state[0x20:0x28] = (9000).to_bytes(8, "little")
    state[0x30:0x38] = (20000).to_bytes(8, "little")
    state[0x50:0x58] = (9000).to_bytes(8, "little")
    state[0x74:0x76] = (10).to_bytes(2, "little", signed=True)
    radio = bytearray(0x20)
    radio[5] = int(phy) & 0xff
    oracles = {
        0: {0: _TIMING_RADIO_STATE},
        1: {0: 10000, 1: 0},
        2: {0: 20},
        3: {0: _TIMING_RADIO_STATE},
        4: {0: 193},
        5: {0: 20},
    }
    if phy in (1, 2, 4, 8):
        oracles.update({6: {0: 50}, 7: {0: 50},
                        8: {0: 0}, 9: {0: 193}})
    return (
        {0: _TIMING_SNAPSHOT_OUT, 1: 0, 2: 0, 3: 0},
        [(0x210010a0, bytes(state)),
         (_TIMING_RADIO_STATE, bytes(radio)),
         (_TIMING_SNAPSHOT_OUT, bytes(0x20))],
        oracles,
    )


def _timing_snapshot_schedule_case(mode, schedule_result):
    """Checksum-stale forced scheduling path and its request descriptor."""
    state = bytearray(0x78)
    state[0] = int(mode) & 0xff
    state[4:8] = (1000).to_bytes(4, "little")
    state[8:12] = (100).to_bytes(4, "little")
    state[0x18:0x20] = (9000).to_bytes(8, "little")
    state[0x20:0x28] = (9000).to_bytes(8, "little")
    state[0x30:0x38] = (20000).to_bytes(8, "little")
    state[0x3c:0x40] = (100).to_bytes(4, "little")
    state[0x50:0x58] = (9000).to_bytes(8, "little")
    state[0x74:0x76] = (10).to_bytes(2, "little", signed=True)
    radio = bytearray(0x20)
    radio[5] = 1
    oracles = {
        0: {0: _TIMING_RADIO_STATE},
        1: {0: 10000, 1: 0},
        2: {0: 20},
        3: {0: 193},
        4: {0: 193},
        5: {0: int(schedule_result)},
        6: {0: 50},
    }
    ordinal = 7
    if schedule_result:
        oracles[ordinal] = {0: 0}
        ordinal += 1
    oracles[ordinal] = {0: 193}
    return (
        {0: _TIMING_SNAPSHOT_OUT, 1: 0, 2: 1, 3: 0},
        [(0x210010a0, bytes(state)),
         (_TIMING_RADIO_STATE, bytes(radio)),
         (_TIMING_SNAPSHOT_OUT, bytes(0x20))],
        oracles,
    )


def _timing_snapshot_request_failure_case():
    """Finite active deadline reaches the one-shot request failure assert."""
    state = bytearray(0x78)
    state[4:8] = (120).to_bytes(4, "little")
    state[8:12] = (100).to_bytes(4, "little")
    state[0x30:0x38] = (20000).to_bytes(8, "little")
    radio = bytearray(0x20)
    radio[5] = 1
    return (
        {0: _TIMING_SNAPSHOT_OUT, 1: 0, 2: 1, 3: 0},
        [(0x210010a0, bytes(state)),
         (_TIMING_RADIO_STATE, bytes(radio)),
         (_TIMING_SNAPSHOT_OUT, bytes(0x20))],
        {0: {0: _TIMING_RADIO_STATE}, 1: {0: 10000, 1: 0},
         2: {0: 20}, 3: {0: 50}, 4: {0: 193}, 5: {0: 193},
         6: {0: 0}},
    )


def _timing_snapshot_mode5_empty_case():
    """Mode-five refresh with an empty schedule-node list."""
    owner = emu.SCRATCH + 0x5000
    state = bytearray(0x78)
    state[0] = 5
    state[4:8] = (120).to_bytes(4, "little")
    state[8:12] = (100).to_bytes(4, "little")
    state[0x28:0x2c] = owner.to_bytes(4, "little")
    state[0x30:0x38] = (0x7fffffffffffffff).to_bytes(8, "little")
    state[0x50:0x58] = (9000).to_bytes(8, "little")
    owner_image = bytearray(0x310)
    owner_image[0x2e0:0x2e4] = (200).to_bytes(4, "little")
    radio = bytearray(0x20)
    radio[5] = 1
    return (
        {0: _TIMING_SNAPSHOT_OUT, 1: 1, 2: 1, 3: 0},
        [(0x210010a0, bytes(state)),
         (_TIMING_RADIO_STATE, bytes(radio)),
         (_TIMING_SNAPSHOT_OUT, bytes(0x20)),
         (owner, bytes(owner_image)),
         (0x2100113c, bytes(0x30))],
        {0: {0: _TIMING_RADIO_STATE}, 1: {0: 10000, 1: 0},
         2: {0: 20}, 3: {}, 4: {0: 0}, 5: {0: 0}, 6: {}, 7: {},
         8: {0: 50}, 9: {0: 0}, 10: {0: 193}},
    )


_TIMING_SNAPSHOT_CASES = [
    _timing_snapshot_refresh_case(1, 0),
    _timing_snapshot_refresh_case(2, 3),
    _timing_snapshot_refresh_case(4, 0),
    _timing_snapshot_refresh_case(8, 3),
    _timing_snapshot_refresh_case(3, 0),  # invalid PHY assertion boundary
    # The first PHY dispatch (checksum-valid active schedule).
    _timing_snapshot_existing_case(1),
    _timing_snapshot_existing_case(2),
    _timing_snapshot_existing_case(4),
    _timing_snapshot_existing_case(8),
    _timing_snapshot_existing_case(3),
    # The second PHY dispatch and slot-advance arithmetic.
    _timing_snapshot_advance_case(1),
    _timing_snapshot_advance_case(2),
    _timing_snapshot_advance_case(4),
    _timing_snapshot_advance_case(8),
    _timing_snapshot_advance_case(3),
    # Request emission, including mode-four request kind and drift correction.
    _timing_snapshot_schedule_case(0, 0),
    _timing_snapshot_schedule_case(4, 3),
    _timing_snapshot_request_failure_case(),
    _timing_snapshot_mode5_empty_case(),
]

REVIEWED_ORACLE_CASES[("net", 0x0101a38c)] = _TIMING_SNAPSHOT_CASES
REVIEWED_TARGET_CALL_ARITIES[("net", 0x0101a38c)] = {
    0x01019204: 0,
    0x01022f08: 0,
    0x0101a130: 0,
    0x0101deac: 0,
    0x0101dda8: 0,
    0x0101dd48: 2,
    0x0101ddc0: 2,
    0x0101deb8: 0,
    0x010209f0: 1,
    0x0100f69c: 2,
    0x0101a0e8: 0,
    0x01022f3c: 1,
    0x0100d4d0: 2,
    0x01008d00: 2,
}


def _controller_radio_transition_case(*, mode=0, next_mode=0,
                                      pending_mode=0, last_mode=0,
                                      phy=1, previous_active=0,
                                      cleanup_pending=0,
                                      radio_cleanup=0,
                                      interval=100,
                                      cross_pending=0,
                                      descriptor_limit=8,
                                      transition_result=0,
                                      guard_result=1):
    """One complete production-shaped radio transition over fixed SDC state."""
    controller = bytearray(0x60)
    controller[7] = previous_active
    controller[8] = next_mode
    controller[9] = mode
    controller[0xc] = pending_mode
    controller[0x18] = phy
    controller[0x1c:0x1e] = interval.to_bytes(2, "little")
    controller[0x29] = last_mode
    controller[0x34] = 3
    controller[0x44] = radio_cleanup
    descriptor = emu.SCRATCH + 0x6e00
    controller[0x30:0x34] = descriptor.to_bytes(4, "little")
    for offset in (0x4c, 0x50, 0x54, 0x58):
        controller[offset:offset + 4] = (0x00080001).to_bytes(4, "little")

    peripheral = bytearray(0x1000)
    peripheral[0x104:0x108] = (1 if cleanup_pending else 0).to_bytes(4, "little")
    peripheral[0x10c:0x110] = (1 if pending_mode else 0).to_bytes(4, "little")
    peripheral[0x400:0x404] = (0).to_bytes(4, "little")
    peripheral[0x414:0x418] = (0).to_bytes(4, "little")
    peripheral[0x550:0x554] = (0).to_bytes(4, "little")
    radio = bytearray(0x1000)
    radio[0x144:0x148] = (1 if cross_pending else 0).to_bytes(4, "little")
    radio[0x544:0x548] = (1000).to_bytes(4, "little")
    radio[0x548:0x54c] = (2000).to_bytes(4, "little")
    radio[0x54c:0x550] = (900).to_bytes(4, "little")
    calls = {0: {0: 1100}}
    if interval > 0x95 and mode in (1, 2):
        calls[1] = {0: guard_result}
        calls[2] = {0: transition_result}
        calls[3] = {0: 1}
    else:
        calls[1] = {0: transition_result}
        calls[2] = {0: guard_result}
    return (
        {0: 0x12345678, 1: 0x89abcdef},
        [(0x210015f0, bytes(controller)),
         (descriptor, bytes((0, descriptor_limit, 0, 0))),
         (0x41008000, bytes(peripheral)),
         (0x4100c000, bytes(radio))],
        calls,
    )


# Fixed controller state, rather than incoming arguments, selects every arm.
# These cases deliberately include all three modes, the pending-mode path,
# zero/nonzero next state, and both transition/cleanup results.
REVIEWED_ORACLE_CASES[("net", 0x01020d1c)] = [
    _controller_radio_transition_case(),
    _controller_radio_transition_case(mode=1),
    _controller_radio_transition_case(mode=2),
    _controller_radio_transition_case(mode=1, pending_mode=1),
    _controller_radio_transition_case(mode=2, pending_mode=2),
    _controller_radio_transition_case(mode=1, next_mode=1),
    _controller_radio_transition_case(mode=2, next_mode=2),
    _controller_radio_transition_case(mode=1, next_mode=1,
                                      transition_result=1),
    _controller_radio_transition_case(mode=1, cleanup_pending=1,
                                      guard_result=0),
    # Callback-mask combinations: +0x58, +0x54, and the paired +0x4c/+0x50.
    _controller_radio_transition_case(transition_result=1),
    _controller_radio_transition_case(mode=1, pending_mode=1,
                                      transition_result=1),
    _controller_radio_transition_case(mode=2, pending_mode=1,
                                      cross_pending=1),
    _controller_radio_transition_case(mode=2, pending_mode=1,
                                      cross_pending=1, descriptor_limit=2),
    # RADIO cleanup register publication and both valid high-interval guards.
    _controller_radio_transition_case(radio_cleanup=1),
    _controller_radio_transition_case(mode=1, interval=200,
                                      guard_result=0),
    _controller_radio_transition_case(mode=2, interval=200,
                                      guard_result=-1),
    # Invalid validator result reaches the reviewed noreturn assertion sink.
    _controller_radio_transition_case(mode=1, interval=200,
                                      guard_result=1),
]
REVIEWED_TARGET_CALL_ARITIES[("net", 0x01020d1c)] = {
    0x01023de8: 0,
    0x010218d8: 0,
    0x010218e4: 0,
    0x01025cf0: 0,
    0x01021614: 2,
    0x010215d8: 2,
    0x010215f4: 2,
    0x01021634: 2,
    0x01020a6c: 3,
    0x01020500: 0,
    0x01025be0: 0,
    0x01008d00: 2,
    0x00080000: 2,
}


def _controller_radio_request_state_clear_case(initial):
    """Complete five-byte request state; only bytes 0..2 may be cleared."""
    assert len(initial) == 5
    return ({}, [(0x210014dc, bytes(initial))], {})


REVIEWED_ORACLE_CASES[("net", 0x0101fdc0)] = [
    _controller_radio_request_state_clear_case((1, 2, 3, 4, 5)),
    _controller_radio_request_state_clear_case((0xff, 0x80, 0x7f, 0xa5, 0x5a)),
]


def _controller_radio_event1_dispatch_case(active, context, event):
    """Fixed owner slot plus complete byte selecting either tail target."""
    owner = emu.SCRATCH + 0x7400
    global_words = bytearray(12)
    global_words[4:8] = owner.to_bytes(4, "little")
    owner_image = bytearray(0x300)
    owner_image[0x2ee] = active
    return (
        {0: context, 1: event},
        [(0x21000f68, bytes(global_words)), (owner, bytes(owner_image))],
        {},
    )


REVIEWED_ORACLE_CASES[("net", 0x01016144)] = [
    _controller_radio_event1_dispatch_case(0, emu.SCRATCH + 0x7000, 1),
    _controller_radio_event1_dispatch_case(0, emu.SCRATCH + 0x7100, 0xa5),
    _controller_radio_event1_dispatch_case(1, emu.SCRATCH + 0x7200, 1),
    _controller_radio_event1_dispatch_case(0xff, emu.SCRATCH + 0x7300, 0xa5),
]
REVIEWED_TARGET_CALL_ARITIES[("net", 0x01016144)] = {
    0x0100b594: 2,
    0x01014b18: 2,
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


def _power_imu_case(result, level=0, sink=0):
    """IMU/microphone rail result with both concrete logger routes."""
    return ({}, [
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ], {0: {0: result & 0xffffffff}})


def _panel_power_case(first_result, second_result=None, level=0, sink=0):
    """Two-stage panel shutdown, including each failure boundary."""
    memory = [
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]
    # With logging disabled, the first rail-control helper is ordinal 3 and
    # the optional second helper is ordinal 5.  The initial diagnostic shifts
    # those ordinals by one when level is enabled.
    first_ordinal = 4 if level else 3
    oracles = {first_ordinal: {0: first_result & 0xffffffff}}
    if first_result >= 0 and second_result is not None:
        second_ordinal = 7 if level else 5
        oracles[second_ordinal] = {0: second_result & 0xffffffff}
    return ({}, memory, oracles)


def _pull_message_case(kind, sink=0, slot=0):
    """NULL, available-message, and over-limit queue states."""
    output = emu.SCRATCH + 0x1000
    singleton = emu.SCRATCH + 0x1100
    memory = [
        (0x2000230c, (1 if kind.startswith("null-log") else 0).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
        (0x2001a22a, bytes((slot & 0xff,))),
    ]
    if kind == "null":
        return ({0: 0, 3: 0x55667788}, memory, {})
    if kind.startswith("null-log"):
        return ({0: 0, 1: 0x11223344, 2: 0x33445566,
                 3: 0x55667788}, memory, {})
    state = bytearray(0xde)
    state[0xdd] = 10 if kind == "available" else 11
    memory += [(output, bytes(4)), (singleton, bytes(state))]
    oracles = {0: {0: singleton}}
    if kind == "over-limit":
        oracles[1] = {0: singleton}
    return ({0: output}, memory, oracles)


def _system_settings_case(result, level=0, sink=0, skip_blocks=False):
    """Complete flash record with modeled memset/read backend writes."""
    output = emu.SCRATCH + 0x1000
    record = bytearray((index * 37 + 11) & 0xff for index in range(0x84))
    if skip_blocks:
        record[0x15] = 0xff
        record[0x35] = 0xff
    else:
        record[0x15] = 0x21
        record[0x35] = 0x43
    record[0x55] = 0x55
    record[0x56] = 0xa6
    memory = [
        (output, bytes(0x84)),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]
    oracles = {1: {0: result & 0xffffffff}}
    writes = {0: [(0, 0, bytes(0x84), 0x00086c78)]}
    if result == 0:
        writes[1] = [(1, 0, bytes(record), 0x000225b4)]
    return ({0: output}, memory, oracles, writes)


for _power_va in (0x00015f80, 0x000160b4):
    REVIEWED_ORACLE_CASES[("app", _power_va)] = [
        _power_imu_case(-5),
        _power_imu_case(-5, level=1),
        _power_imu_case(-5, level=1, sink=1),
        _power_imu_case(0),
        _power_imu_case(0, level=1),
        _power_imu_case(0, level=1, sink=1),
    ]

REVIEWED_ORACLE_CASES[("app", 0x00015fdc)] = [
    _panel_power_case(-5),
    _panel_power_case(0, -7),
    _panel_power_case(0, 0),
    _panel_power_case(-5, level=1),
    _panel_power_case(-5, level=1, sink=1),
    _panel_power_case(0, 0, level=1),
    _panel_power_case(0, 0, level=1, sink=1),
]

REVIEWED_ORACLE_CASES[("app", 0x000342e0)] = [
    _pull_message_case("null"),
    _pull_message_case("null-log"),
    _pull_message_case("null-log", sink=1),
    _pull_message_case("available", slot=0),
    _pull_message_case("available", sink=1, slot=1),
    _pull_message_case("over-limit"),
    _pull_message_case("over-limit", sink=1),
]

REVIEWED_ORACLE_CASES[("app", 0x000232f8)] = [
    _system_settings_case(-5),
    _system_settings_case(-5, level=2),
    _system_settings_case(-5, level=2, sink=1),
    _system_settings_case(0),
    _system_settings_case(0, level=2),
    _system_settings_case(0, level=2, sink=1),
    _system_settings_case(0, skip_blocks=True),
]


def _flash_upgrade_case(result, level=0, sink=0):
    """One complete upgrade request with success/failure logger routing."""
    return (
        {0: 0x112233a5, 1: 0x66778899, 2: 0xdeadbeef},
        [(0x2000230c, int(level).to_bytes(4, "little")),
         (0x20007554, int(sink).to_bytes(4, "little"))],
        {0: {0: result & 0xffffffff}},
    )


def _utf8_case(data, length, level=0, sink=0):
    """Concrete one-, two-, and three-byte input classes and boundaries."""
    source = emu.SCRATCH + 0x1000
    return (
        {0: source, 1: length},
        [(source, bytes(data) + bytes(max(0, 3 - len(data)))),
         (0x2000230c, int(level).to_bytes(4, "little")),
         (0x20007554, int(sink).to_bytes(4, "little"))],
        {},
    )


for _upgrade_va in (0x00023bfc, 0x00024420):
    REVIEWED_ORACLE_CASES[("app", _upgrade_va)] = [
        _flash_upgrade_case(0),
        _flash_upgrade_case(0, level=3),
        _flash_upgrade_case(0, level=3, sink=1),
        _flash_upgrade_case(-5),
        _flash_upgrade_case(-5, level=1),
        _flash_upgrade_case(-5, level=1, sink=1),
    ]

REVIEWED_ORACLE_CASES[("app", 0x000477a0)] = [
    _utf8_case(b"A", 1),
    _utf8_case(b"\xc2\xa9", 2),
    _utf8_case(b"\xc2\xa9", 1),
    _utf8_case(b"\xe3\x83\xa7", 3),
    _utf8_case(b"\xe3\x83\xa7", 2),
    _utf8_case(b"\xe3\x83\xa7", 2, level=4),
    _utf8_case(b"\xe3\x83\xa7", 2, level=4, sink=1),
]


def _click_dispatch_case(click_count, level=0, sink=0):
    """Bounded production click sequence followed by the release event."""
    context = emu.SCRATCH + 0x1000
    device = emu.SCRATCH + 0x3000
    key = 0x12345678
    context_bytes = bytearray(0x1080)
    context_bytes[0x105c:0x105e] = (1).to_bytes(2, "little")
    context_bytes[0x1078:0x107c] = (0x10203040).to_bytes(4, "little")
    device_bytes = bytearray(4)
    memory = [
        (context, bytes(context_bytes)), (device, bytes(device_bytes)),
        (0x20006a00, bytes(4)), (0x20019dac, b"\x01"),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]
    oracles = {}
    writes = {}
    ordinal = 0

    def begin_iteration(event):
        nonlocal ordinal
        state_ordinal = ordinal
        oracles[state_ordinal] = {0: 0, 1: key}
        if state_ordinal != 0:
            writes[state_ordinal] = [(None, 0x20019dac, bytes((event,)))]
        ordinal += 1                    # state query
        ordinal += 1                    # update_sync_buffer
        oracles[ordinal] = {0: device}
        ordinal += 1                    # get_device_info

    for index in range(click_count):
        begin_iteration(1)
        timestamp = 1000 * (index + 1)
        oracles[ordinal] = {0: timestamp}; ordinal += 1
        writes[ordinal] = [(0, 0, (0x10203040 + index).to_bytes(4, "little"),
                            0x0007d0aa)]
        ordinal += 1                    # read_rtc_counter_ms
        oracles[ordinal] = {0: timestamp + 100}; ordinal += 1
        oracles[ordinal] = {0: timestamp + 200}; ordinal += 1

    begin_iteration(2)
    release_time = 1000 * (click_count + 1)
    oracles[ordinal] = {0: release_time}; ordinal += 1
    oracles[ordinal] = {0: release_time + 10000}; ordinal += 1
    oracles[ordinal] = {0: release_time + 10001}; ordinal += 1

    if click_count == 1:
        ordinal += 1                    # single-click diagnostic
        writes[ordinal] = [(0, 0, (0x55667788).to_bytes(4, "little"),
                            0x0007d0aa)]
        ordinal += 1                    # read_rtc_counter_ms
        ordinal += 1                    # timestamp diagnostic
    elif click_count in (2, 3):
        ordinal += 1                    # selected click handler
    elif click_count >= 5:
        ordinal += 2                    # default handler plus state setter
    else:
        # Four clicks enter the deliberate reboot loop.  Prefix comparison
        # observes its selected logger route and repeated sleep/reboot calls.
        return ({0: context, 1: key, 2: 0x89abcdef}, memory, oracles, writes)

    oracles[ordinal] = {0: 1, 1: key}   # bounded thread exit
    return ({0: context, 1: key, 2: 0x89abcdef}, memory, oracles, writes)


def _click_idle_case(wait=False):
    """Idle queue processing and the context-busy sleep boundary."""
    context = emu.SCRATCH + 0x1000
    device = emu.SCRATCH + 0x3000
    state = bytearray(0x1080)
    state[1] = 1 if wait else 0
    state[0x105c:0x105e] = (1).to_bytes(2, "little")
    memory = [
        (context, bytes(state)), (device, bytes(4)),
        (0x20006a00, bytes(4)), (0x20019dac, b"\x00"),
        (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
    ]
    if wait:
        oracles = {0: {0: 0, 1: 0x12345678}, 3: {0: 1, 1: 0x12345678}}
    else:
        oracles = {0: {0: 0, 1: 0x12345678}, 2: {0: device},
                   3: {0: 1000}, 4: {0: 1100},
                   5: {0: 1, 1: 0x12345678}}
    return ({0: context, 1: 0x12345678, 2: 0x89abcdef}, memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x00028a1c)] = [
    ({0: emu.SCRATCH + 0x1000, 1: 0x12345678, 2: 0x89abcdef},
     [(emu.SCRATCH + 0x1000, bytes(0x1080))], {0: {0: 1}}),
    _click_idle_case(),
    _click_idle_case(wait=True),
    _click_dispatch_case(1),
    _click_dispatch_case(2),
    _click_dispatch_case(3),
    _click_dispatch_case(4, level=1),
    _click_dispatch_case(4, level=1, sink=1),
    _click_dispatch_case(5),
]

# Arithmetic leaves in this family return a 512-bit value through r0-r7,
# r11, and seven caller-reserved stack words.  An ordinary r0:r1 oracle loses
# most of that semantic result, so these reviewed wrappers execute the exact
# leaf/reducer bytes as one verification unit.  The candidate is free to
# express the same operation with ordinary C arrays.
REVIEWED_INTERNAL_CODE_REGIONS = {
    # The TBB dispatcher's case blocks follow its inline byte table.  The
    # generic reachable decoder deliberately stops at the computed branch;
    # execute the reviewed case-block extent as part of this function rather
    # than mistaking each selected case for an external oracle.
    ("app", 0x000456fc): ((0x00045732, 14),),
    # The TBB owns five late case islands plus its BHI -0x86 return island.
    # The generic switch decoder stops at the computed dispatch, so execute
    # this contiguous late extent and its joins as part of the function.
    ("app", 0x00083ede): ((0x00084044, 0x24),),
    ("net", 0x01008650): ((0x010083dc, 628),),
    ("net", 0x010087f0): ((0x01008670, 382),),
    ("net", 0x01008a28): ((0x01008670, 382), (0x01008940, 184)),
    ("net", 0x010089f8): ((0x010083dc, 628), (0x01008940, 184)),
}

# These arithmetic adapters consume fixed pointer ABIs.  Trying smaller nptr
# modes first can manufacture matching fault parity before their private
# multi-register workers execute, so require the production pointer count.
REVIEWED_NPTR_COUNTS = {
    # Work handler has exactly one transport pointer; queue results are fully
    # bounded by the reviewed oracle sequences above.
    ("app", 0x00080ab4): 1,
    # The optional type output is supplied explicitly by each fixture.
    ("app", 0x000809b0): 1,
    ("net", 0x0101a38c): 1,
    # IPC callback ABI is exactly (context pointer, packet pointer); both full
    # pointee graphs are supplied by the reviewed cases.
    ("app", 0x00015960): 2,
    # r0 is the persistent device context.  The optional r2 payload is
    # supplied explicitly because the intervening r1 command selector makes
    # generic contiguous nptr modes inapplicable.
    ("app", 0x00026f74): 1,
    # key_event_thread consumes only its r0 context pointer; r1/r2 are unused
    # scalar thread-entry arguments and every reviewed case supplies them.
    ("app", 0x0002955c): 1,
    # Fixtures supply the noncontiguous file/function/expression pointers.
    ("app", 0x00076a94): 1,
    # Complete fixtures provide the event buffer explicitly; one pointer mode
    # avoids replaying all terminal assertion paths under synthetic ABIs.
    ("app", 0x000753ec): 1,
    # Complete fixtures provide both noncontiguous pointer arguments (events
    # in r0 and poller in r2); one pointer ABI mode is sufficient and avoids
    # replaying every terminal assertion path under synthetic alternatives.
    ("app", 0x000751d0): 1,
    # Only r0 is a pointer (canvas owner); r1 is unused and r2 is the phase.
    # Repeating the million-instruction render under extra synthetic pointer
    # modes adds no coverage and makes negative controls unnecessarily costly.
    ("app", 0x0003b824): 1,
    # Even-AI likewise consumes only its r0 canvas pointer; r1 is unused and
    # r2 is the scalar phase.  Its three eight-frame render families are
    # already covered by explicit state fixtures and must not be replayed
    # under four synthetic pointer-count modes.
    ("app", 0x0003bfe0): 1,
    # Four pointer arguments with complete reviewed pointee graphs; additional
    # generic pointer modes only duplicate hundreds of expensive TBB runs.
    ("app", 0x00042a64): 4,
    # Exact wrapper contracts must run one substantive pointer mode; trying
    # later modes after a concrete mismatch can manufacture unrelated fault
    # parity and hide a deliberately wrong local payload.
    ("app", 0x0007d696): 0,
    ("app", 0x0007d82e): 2,
    ("app", 0x0008099e): 1,
    ("app", 0x000829f0): 1,
    ("app", 0x00085130): 1,
    ("app", 0x00028a1c): 1,
    ("net", 0x01008650): 3,  # result[16], left[8], right[8]
    ("net", 0x010087f0): 2,  # result[16], value[8]
    ("net", 0x01008a28): 2,  # result[8], value[8]
    ("net", 0x010089f8): 3,  # result[8], left[8], right[8]
    ("net", 0x0101a38c): 1,  # complete 24-byte scheduling snapshot output
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
    # Linear decoding mistakes the saved byte-valued record type in r8 for an
    # object owner and associates its offset zero with the later BLX.  The BLX
    # target is instead the direct fourth argument, saved at entry-SP-44.
    reviewed_non_callback_slots = {
        0x00021a40: {(2, 0)},
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
    callback_slots.difference_update(reviewed_non_callback_slots.get(va, ()))
    data_pointer_slots.update(reviewed_data_pointer_slots.get(va, ()))
    return cases, sorted(callback_slots), sorted(data_pointer_slots)

def _notification_count_case():
    request = emu.SCRATCH + 0x1000
    payload = emu.SCRATCH + 0x1100
    response = emu.SCRATCH + 0x1200
    request_image = bytearray(0x20)
    request_image[0x0c:0x10] = (0x00080001).to_bytes(4, "little")
    payload_image = bytearray(0x20)
    payload_image[0] = 7
    return (
        {0: request, 1: payload, 2: response},
        [(request, bytes(request_image)), (payload, bytes(payload_image)),
         (response, bytes(0x20)), (0x2000230c, bytes(4)),
         (0x20007554, bytes(4))],
        {},
    )


# Exact call contracts for the settings, simulator, SPI, and audio wrappers.
# Diagnostics with substitutions are refined by format immediately below.
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00022518)] = {
    0x0004e744: 0, 0x0004e494: 1,
}
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00021cd8)] = {
    0x000181fc: 0, 0x0007dda4: 2, 0x00019c70: 2,
    0x00086c78: 3, 0x0008705a: 3, 0x0004a3d0: 2, 0x0007c172: 1,
}
REVIEWED_TARGET_CALL_ARITIES[("app", 0x000262ac)] = {0x00067304: 3}
REVIEWED_TARGET_CALL_ARITIES[("app", 0x0002f764)] = {
    0x00086c78: 3, 0x000720d0: 4, 0x0007dda4: 2,
    0x00019c70: 2, 0x00072880: 1, 0x000167a8: 0,
    0x00026f74: 4, 0x000498c0: 1,
}
REVIEWED_TARGET_CALL_ARITIES[("app", 0x0002f80c)] = {
    0x00086c78: 3, 0x000720d0: 4, 0x0007dda4: 2,
    0x00019c70: 2, 0x00072880: 1,
}

REVIEWED_CALL_ARITIES_BY_FORMAT[("app", 0x00022518)] = {
    (target, fmt): arity
    for target in (0x0007dda4, 0x00019c70)
    for fmt, arity in ((0x0009e266, 3), (0x0009e2a0, 3),
                       (0x0009e2cb, 2))
}
REVIEWED_CALL_ARITIES_BY_FORMAT[("app", 0x000262ac)] = {
    (target, fmt): arity
    for target in (0x0007dda4, 0x00019c70)
    for fmt, arity in ((0x0009fb42, 2), (0x0009fb59, 4))
}
REVIEWED_CALL_STACK_ARITIES_BY_FORMAT[("app", 0x000262ac)] = {
    (target, 0x0009fb59): 1
    for target in (0x0007dda4, 0x00019c70)
}

# Complete caller-owned records consumed by the transfer/queue boundaries.
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x000262ac)] = [
    ("spi-transfer", -24, -24, 16, None, (0,), (0x00067304,)),
]
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x0002f764)] = [
    ("audio-start-record", -216, -216, 208, None, None,
     (0x00086c78, 0x000720d0, 0x00026f74)),
]
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x0002f80c)] = [
    ("audio-stop-record", -216, -216, 208, None, None,
     (0x00086c78, 0x000720d0)),
]
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x00047b1c)] = [
    # One complete 24-byte queue record.  GCC reserves four extra frame bytes
    # but passes the same record through clear/copy/enqueue boundaries.
    ("response-queue-record", -40, -44, 24, None, None,
     (0x00086c78, 0x00086c04, 0x000720d0)),
]
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x00031cbc)] = [
    # FUN_000232f8 fills a 116-byte panel-status snapshot.  The readable C
    # frame saves fewer registers and shifts only this complete object.
    ("panel-status-snapshot", -156, -140, 116, None, None,
     (0x000232f8,)),
]


def _panel_brightness_case(level, brightness, requested, sink=0):
    state = emu.SCRATCH + 0x5000
    image = bytearray(0xee0)
    image[0xed8:0xeda] = int(brightness).to_bytes(2, "little")
    logger = 1 if level > 2 else 0
    getter_ordinals = range(2 + logger, 5 + logger)
    return ({0: requested},
            [(state, bytes(image)),
             (0x2000230c, int(level).to_bytes(4, "little")),
             (0x20007554, int(sink).to_bytes(4, "little"))],
            {ordinal: {0: state} for ordinal in getter_ordinals})


REVIEWED_ORACLE_CASES[("app", 0x00046e3c)] = [
    _panel_brightness_case(0, 0, 0),
    _panel_brightness_case(0, 9, 5),
    _panel_brightness_case(0, 20, 6),
    _panel_brightness_case(3, 9, 5),
    _panel_brightness_case(3, 20, 6, sink=1),
]


def _serialization_case(level, sink, init_result, open_low=None,
                        open_high=0x12345678):
    initial_log = 1 if level > 2 else 0
    init_ordinal = initial_log
    oracles = {init_ordinal: {0: int(init_result)}}
    if init_result >= 0 or init_result == -0x78:
        # A successful/accepted initializer is followed by the two-register
        # serialization handle result from FUN_0004cbec.
        open_ordinal = init_ordinal + 1 + initial_log
        oracles[open_ordinal] = {
            0: int(0 if open_low is None else open_low),
            1: int(open_high),
        }
    return ({},
            [(0x2000230c, int(level).to_bytes(4, "little")),
             (0x20007554, int(sink).to_bytes(4, "little")),
             (0x20007a80, bytes(4))],
            oracles)


REVIEWED_ORACLE_CASES[("app", 0x00025c54)] = [
    _serialization_case(0, 0, -1),
    _serialization_case(1, 0, -1),
    _serialization_case(3, 0, -1),
    _serialization_case(3, 1, -1),
    _serialization_case(0, 0, 0, 0, 0x12345678),
    _serialization_case(0, 0, -0x78, -1, 0x12345678),
]

REVIEWED_ORACLE_CASES[("app", 0x00049000)] = [
    ({0: 0}, [(0x2000230c, bytes(4)),
              (0x20007554, bytes(4)), (0x2000a094, bytes(4))], {}),
    ({0: 0x12345678},
     [(0x2000230c, (3).to_bytes(4, "little")),
      (0x20007554, bytes(4)), (0x2000a094, bytes(4))], {}),
    ({0: 0xffffffff},
     [(0x2000230c, (3).to_bytes(4, "little")),
      (0x20007554, (1).to_bytes(4, "little")),
      (0x2000a094, bytes(4))], {}),
]


def _brightness_lum_case(mode=0, brightness=0, active=1,
                         null_response=False, level=0, sink=0):
    request = emu.SCRATCH + 0x1000
    response_holder = emu.SCRATCH + 0x2000
    response = emu.SCRATCH + 0x3000
    output_length = emu.SCRATCH + 0x4000
    state = emu.SCRATCH + 0x5000
    request_image = bytearray(7)
    request_image[4] = mode & 0xff
    request_image[5:7] = int(brightness).to_bytes(2, "little")
    args = {0: request, 1: 0x11223344,
            2: 0 if null_response else response_holder,
            3: output_length}
    memory = [
        (request, bytes(request_image)),
        (response_holder, response.to_bytes(4, "little")),
        (response, bytes(8)), (output_length, bytes(1)),
        (state, bytes(0xee0)),
        (0x20019ef3, bytes((active & 0xff,))),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]
    oracles = {}
    if active and not null_response:
        logger = 1 if level > 2 else 0
        getter_start = 1 + logger  # unconditional entry diagnostic is call 0
        getter_count = 3 if mode in (0, 1, 2) else 2
        for ordinal in range(getter_start, getter_start + getter_count):
            oracles[ordinal] = {0: state}
        first_read = getter_start + getter_count + 1
        for ordinal in range(first_read, first_read + 10, 2):
            oracles[ordinal] = {0: 1}  # force the reviewed five-try timeout
    return (args, memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x00031cbc)] = [
    _brightness_lum_case(null_response=True),
    _brightness_lum_case(active=0),
    _brightness_lum_case(mode=0, brightness=0x3f),
    _brightness_lum_case(mode=1, brightness=0x64),
    _brightness_lum_case(mode=2, brightness=10),
    _brightness_lum_case(mode=3, brightness=20),
]


def _sett_case(primary, secondary=0, level=0, sink=0):
    output = emu.SCRATCH + 0x8000
    memory = [(output, bytes(16)),
              (0x2000230c, int(level).to_bytes(4, "little")),
              (0x20007554, int(sink).to_bytes(4, "little"))]
    oracles = {0: {0: int(primary)}}
    if primary == 0:
        oracles[1] = {0: int(secondary)}
    return ({0: output}, memory, oracles)


def _simulator_calendar_case(level=0, sink=0):
    state = emu.SCRATCH + 0x9000
    return ({}, [(state, bytes(0x220)),
                 (0x2000230c, int(level).to_bytes(4, "little")),
                 (0x20007554, int(sink).to_bytes(4, "little"))],
            {0: {0: state}})


def _spi_transfer_case(active, result=0, level=0, sink=0):
    device = emu.SCRATCH + 0xa000
    image = bytearray(0x20)
    image[0x14:0x18] = int(active).to_bytes(4, "little")
    image[0x18] = 0x5a
    memory = [(device, bytes(image)),
              (0x2000230c, int(level).to_bytes(4, "little")),
              (0x20007554, int(sink).to_bytes(4, "little")),
              (emu.STACK_TOP, (0x55667788).to_bytes(4, "little"))]
    oracles = {0: {0: int(result)}} if active else {}
    return ({0: device, 1: 0x11223344, 2: 0x22334455, 3: 0x33445566},
            memory, oracles)


def _audio_case(result, level=0, sink=0):
    return ({}, [(0x2000230c, int(level).to_bytes(4, "little")),
                 (0x20007554, int(sink).to_bytes(4, "little"))],
            {1: {0: int(result)}})


REVIEWED_ORACLE_CASES[("app", 0x00022518)] = [
    _sett_case(5), _sett_case(5, level=2),
    _sett_case(5, level=2, sink=1),
    _sett_case(0, 7, level=2), _sett_case(0, 0, level=2),
]
REVIEWED_ORACLE_CASES[("app", 0x00021cd8)] = [
    _simulator_calendar_case(), _simulator_calendar_case(3),
    _simulator_calendar_case(3, sink=1),
]
REVIEWED_ORACLE_CASES[("app", 0x000262ac)] = [
    _spi_transfer_case(False), _spi_transfer_case(False, level=1),
    _spi_transfer_case(False, level=1, sink=1),
    _spi_transfer_case(True, 0x0bad0000),
    _spi_transfer_case(True, 7), _spi_transfer_case(True, 7, level=1),
    _spi_transfer_case(True, 7, level=1, sink=1),
]
REVIEWED_ORACLE_CASES[("app", 0x0002f764)] = [
    _audio_case(0), _audio_case(1), _audio_case(1, level=1),
    _audio_case(1, level=1, sink=1),
]
REVIEWED_ORACLE_CASES[("app", 0x0002f80c)] = [
    _audio_case(0), _audio_case(1), _audio_case(1, level=1),
    _audio_case(1, level=1, sink=1),
]


def _display_state(active, level=0, sink=0):
    state = emu.SCRATCH + 0x2000
    device = emu.SCRATCH + 0x3000
    state_image = bytearray(0x400)
    state_image[0x35c:0x360] = int(active).to_bytes(4, "little")
    device_image = bytearray(0x1000)
    device_image[0xeb4:0xeb8] = (emu.SCRATCH + 0x7000).to_bytes(4, "little")
    device_image[0xeb8:0xebc] = (0x1234).to_bytes(4, "little")
    memory = [(state, bytes(state_image)), (device, bytes(device_image)),
              (0x2000230c, int(level).to_bytes(4, "little")),
              (0x20007554, int(sink).to_bytes(4, "little"))]
    return state, device, memory


def _area_clear_case(active, level=0, sink=0):
    state, device, memory = _display_state(active, level, sink)
    prefix = 1 if level > 2 else 0
    oracles = ({prefix: {0: state}} if not active else
               {prefix: {0: state}, prefix + 1: {0: device},
                prefix + 3: {0: device}, prefix + 4: {0: device}})
    return ({0: 4, 1: 5, 2: 12, 3: 13}, memory, oracles)


def _screen_clear_case(active, level=0, sink=0):
    state, _, memory = _display_state(active, level, sink)
    prefix = 1 if level > 2 else 0
    return ({}, memory, {prefix: {0: state}})


def _merge_draw_case(kind):
    first = emu.SCRATCH + 0x4000
    second = emu.SCRATCH + 0x4100
    rows = emu.SCRATCH + 0x4200
    framebuffer = emu.SCRATCH + 0x4300
    x = 1 if kind == "odd" else 0
    x_end = 9 if kind == "odd" else (7 if kind == "invalid" else 8)
    memory = [
        (first, b"\xa5" + bytes(7)), (second, b"\x3c" + bytes(7)),
        (rows, framebuffer.to_bytes(4, "little")),
        (framebuffer, bytes(32)),
        (0x2000a034, rows.to_bytes(4, "little")),
        (0x2000230c, (2 if kind == "odd" else 0).to_bytes(4, "little")),
        (0x20007554, bytes(4)),
        (emu.STACK_TOP, first.to_bytes(4, "little")),
        (emu.STACK_TOP + 4, second.to_bytes(4, "little")),
        (emu.STACK_TOP + 8, (3).to_bytes(4, "little")),
        (emu.STACK_TOP + 12, (5).to_bytes(4, "little")),
    ]
    oracles = ({0: {0: 0, 1: 0}, 1: {0: 0, 1: 0}}
               if kind == "render" else {})
    return ({0: x, 1: 0, 2: x_end, 3: 1}, memory, oracles)


def _bmp_draw_case(kind):
    bitmap = emu.SCRATCH + 0x5000
    framebuffer = emu.SCRATCH + 0x6000
    memory = [(bitmap, b"\xf3\x5a" + bytes(30)),
              (framebuffer, bytes(64)),
              (0x2000a034, framebuffer.to_bytes(4, "little")),
              (0x2000230c, bytes(4)), (0x20007554, bytes(4))]
    mask = 0 if kind == "zero-mask" else 0x0f
    memory.append((emu.STACK_TOP, mask.to_bytes(4, "little")))
    if kind == "zero-mask":
        return ({0: 1, 1: 2, 2: 3, 3: bitmap}, memory, {})
    if kind == "decode-error":
        return ({0: 1, 1: 2, 2: 3, 3: bitmap}, memory,
                {0: {0: 0xffffffff}})
    effects = {0: [
        (2, 0, (4).to_bytes(4, "little"), 0x0004588c),
        (2, 4, (1).to_bytes(4, "little"), 0x0004588c),
        (2, 8, (0).to_bytes(4, "little"), 0x0004588c),
    ]}
    return ({0: 1, 1: 2, 2: 3, 3: bitmap}, memory,
            {0: {0: 0}, 2: {0: 0}, 4: {0: 0}}, effects)


REVIEWED_ORACLE_CASES[("app", 0x00033abc)] = [_notification_count_case()]
REVIEWED_ORACLE_CASES[("app", 0x000431c0)] = [
    _screen_clear_case(False), _screen_clear_case(True),
    _screen_clear_case(False, level=3),
]
REVIEWED_ORACLE_CASES[("app", 0x00043228)] = [
    _area_clear_case(False), _area_clear_case(True),
    _area_clear_case(False, level=3),
]
REVIEWED_ORACLE_CASES[("app", 0x00043bd8)] = [
    _merge_draw_case(kind) for kind in ("invalid", "odd", "render")
]
REVIEWED_ORACLE_CASES[("app", 0x000435d4)] = [
    _bmp_draw_case(kind) for kind in ("zero-mask", "decode-error", "success")
]

# Final display/persistence wrappers: reviewed ABI boundaries and complete
# compiler-owned records.  Logger formats in raster_height carry no
# substitutions; the refresh dispatcher and its handlers consume exactly
# their three semantic arguments.
REVIEWED_TARGET_CALL_ARITIES[("app", 0x000430c0)] = {
    0x0007dda4: 2, 0x00019c70: 2,
}
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00048b5c)] = {
    0x0003603c: 3, 0x00036b3c: 3, 0x0003f410: 3,
    0x0003fecc: 3, 0x0003af78: 3, 0x0003cb58: 3,
    0x0003cf44: 3, 0x0003b824: 3, 0x00042d44: 3,
    0x000430c0: 3, 0x0003bfe0: 3, 0x00046b80: 3,
    0x00080000: 3,
}
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00023014)] = {
    0x0007dda4: 2, 0x00019c70: 2,
}
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00023af0)] = {
    0x000720d0: 4, 0x00072880: 1,
}

REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x000430c0)] = [
    ("raster-dimensions", -32, -32, 8, None, None, (0x00042fb0,)),
]
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x00023014)] = [
    ("burial-flash-buffer", -208, -204, 192, None, None,
     (0x00086c78, 0x000225b4, 0x00086be4)),
]
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x00023af0)] = [
    ("language-update-record", -24, -20, 12, None, None, (0x000720d0,)),
]


def _panel_canvas_coord_case(canvas_gear=0, raster_gear=8,
                             device_type=0, current_x=0x1234,
                             current_y=0x5678, x_present=True,
                             y_present=True, level=0, sink=0):
    """Production-shaped calibration state for cal_panel_canvas_coord.

    The two output pointers are independently optional.  The device singleton
    supplies the handedness byte at +0 and both one-byte display gears at
    +0xec0/+0xec1.  Keeping that singleton concrete at every dynamic accessor
    call avoids the historical random-oracle timeout while the ordinary call
    trace still verifies accessor/logger identity, order, and arguments.
    """
    device = emu.SCRATCH + 0x2000
    x_out = emu.SCRATCH + 0x1000
    y_out = emu.SCRATCH + 0x1100
    image = bytearray(0xec2)
    image[0] = int(device_type) & 0xff
    image[0xec0] = int(raster_gear) & 0xff
    image[0xec1] = int(canvas_gear) & 0xff
    memory = [
        (device, bytes(image)),
        (x_out, int(current_x).to_bytes(4, "little", signed=True)),
        (y_out, int(current_y).to_bytes(4, "little", signed=True)),
        (0x2000230c, int(level).to_bytes(4, "little", signed=True)),
        (0x20007554, int(sink).to_bytes(4, "little", signed=True)),
    ]
    # At most six calls occur (four accessors plus two log sinks).  Publishing
    # the same singleton result at every ordinal is safe for void log calls and
    # makes each subsequent get_device_info dereference deterministic.
    oracles = {ordinal: {0: device} for ordinal in range(6)}
    return ({0: x_out if x_present else 0,
             1: y_out if y_present else 0}, memory, oracles)


_PANEL_CANVAS_X = {
    0: 0, 1: 22, 2: 8, 3: 0, 4: -4, 5: -8,
    6: -10, 7: -12, 8: -14, 9: -16, 10: 0,
}
REVIEWED_ORACLE_CASES[("app", 0x00042fb0)] = [
    # Null handling and every entry/default edge of the nine-way TBB.  The
    # alternating handedness byte covers both the direct and negated X paths.
    _panel_canvas_coord_case(x_present=False, y_present=False),
    *[_panel_canvas_coord_case(
        canvas_gear=gear, device_type=gear & 1,
        current_x=0x1234 + gear, y_present=False)
      for gear in range(11)],
    _panel_canvas_coord_case(
        canvas_gear=0xff, raster_gear=0xff, device_type=2,
        current_x=99, current_y=99, level=1),
    # Equality suppresses logging after the output write for both axes.
    _panel_canvas_coord_case(
        canvas_gear=1, device_type=0,
        current_x=_PANEL_CANVAS_X[1], y_present=False, level=3),
    _panel_canvas_coord_case(
        raster_gear=7, current_y=35, x_present=False, level=3),
    # Exact diagnostic threshold: a changed coordinate at level one remains
    # silent, distinguishing the shipped >1 condition from >=1.
    _panel_canvas_coord_case(
        canvas_gear=1, current_x=99, y_present=False, level=1),
    # Direct and buffered logger sinks for X and Y independently.
    _panel_canvas_coord_case(
        canvas_gear=4, current_x=99, y_present=False, level=3, sink=0),
    _panel_canvas_coord_case(
        canvas_gear=5, current_x=99, y_present=False, level=3, sink=1),
    _panel_canvas_coord_case(
        raster_gear=6, current_y=99, x_present=False, level=3, sink=0),
    _panel_canvas_coord_case(
        raster_gear=5, current_y=99, x_present=False, level=3, sink=1),
    # Both output paths and both logger targets in a single invocation verify
    # the accessor/log call ordering across the X-to-Y fallthrough boundary.
    _panel_canvas_coord_case(
        canvas_gear=9, raster_gear=4, device_type=1,
        current_x=99, current_y=99, level=3, sink=0),
    _panel_canvas_coord_case(
        canvas_gear=2, raster_gear=3, device_type=0,
        current_x=99, current_y=99, level=3, sink=1),
]
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00042fb0)] = {
    0x000167a8: 0,
    0x00019c70: 4,
    0x0007dda4: 4,
}


def _raster_case(current_height, current_offset, measured_height,
                 measured_offset, mode=0, level=0, sink=0):
    app = emu.SCRATCH + 0x2000
    memory = [
        (app, bytes(0x1200)),
        (0x20002540, int(current_height).to_bytes(4, "little", signed=True)),
        (0x2000253c, int(current_offset).to_bytes(4, "little", signed=True)),
        (0x2000230c, int(level).to_bytes(4, "little")),
        (0x20007554, int(sink).to_bytes(4, "little")),
    ]
    if mode == 2:
        return ({0: 0x11112222, 1: 0x33334444, 2: mode}, memory, {})
    effects = {0: [
        (0, 0, int(measured_height).to_bytes(4, "little", signed=True),
         0x00042fb0),
        (1, 0, int(measured_offset).to_bytes(4, "little", signed=True),
         0x00042fb0),
    ]}
    if (current_height, current_offset) == (measured_height, measured_offset):
        return ({0: 0x11112222, 1: 0x33334444, 2: mode}, memory, {}, effects)
    prefix = 1 if level > 2 else 0
    oracles = {prefix + 1: {0: app}, prefix + 2: {0: app},
               prefix + 4: {0: app}, prefix + 5: {0: app}}
    return ({0: 0x11112222, 1: 0x33334444, 2: mode}, memory, oracles, effects)


REVIEWED_ORACLE_CASES[("app", 0x000430c0)] = [
    _raster_case(12, 3, 12, 3),
    _raster_case(12, 3, 20, -2),
    _raster_case(12, 3, 20, -2, level=3),
    _raster_case(12, 3, 12, 3, level=3, sink=1),
    _raster_case(12, 3, 0, 0, mode=2),
    _raster_case(12, 3, 0, 0, mode=2, level=3, sink=1),
]


def _refresh_case(mode, ready=0, level=0, sink=0):
    owner = emu.SCRATCH + 0x4000
    image = bytearray(0xe00)
    image[0xb80:0xb84] = (0x00080001).to_bytes(4, "little")
    image[0xd4] = 0x35
    image[0xd5] = 0x5a
    memory = [(owner, bytes(image)),
              (0x2000230c, int(level).to_bytes(4, "little")),
              (0x20007554, int(sink).to_bytes(4, "little")),
              (0x2000a098, bytes(4))]
    return ({0: owner, 1: mode, 2: 0x11223344, 3: 0x55667788},
            memory, {0: {0: ready}})


REVIEWED_ORACLE_CASES[("app", 0x00048b5c)] = [
    _refresh_case(2, ready=1), _refresh_case(3, ready=1),
    *[_refresh_case(mode) for mode in
      (4, 5, 6, 7, 9, 10, 11, 12, 14, 15, 16, 17, 8)],
    _refresh_case(6, level=3), _refresh_case(8, level=3, sink=1),
]


def _little_endian_case(pointer, value=0x78563412, level=0, sink=0):
    memory = [(0x2000230c, int(level).to_bytes(4, "little")),
              (0x20007554, int(sink).to_bytes(4, "little"))]
    if pointer:
        memory.append((pointer, bytes(4)))
    return ({0: pointer, 1: value, 2: 0x10203040, 3: 0x50607080},
            memory, {})


REVIEWED_ORACLE_CASES[("app", 0x0004a568)] = [
    _little_endian_case(emu.SCRATCH + 0x7000),
    _little_endian_case(emu.SCRATCH + 0x7000, 0),
    _little_endian_case(0), _little_endian_case(0, level=2),
    _little_endian_case(0, level=2, sink=1),
]


def _burial_case(read_result, compare_result=0, write_result=0,
                 level=0, sink=0):
    app = emu.SCRATCH + 0x8000
    image = bytearray(0x1200)
    image[0x10c6:0x1186] = bytes((i * 17 + 9) & 0xff for i in range(192))
    prefix = 1 if level > 1 else 0
    oracles = {prefix + 1: {0: read_result}}
    if read_result == 0:
        oracles[prefix + 2] = {0: compare_result}
        if compare_result != 0:
            oracles[prefix + 3] = {0: write_result}
    effects = {prefix + 1: [
        (1, 0, bytes(image[0x10c6:0x1186]), 0x000225b4)
    ]}
    return ({0: app}, [(app, bytes(image)),
                       (0x2000230c, int(level).to_bytes(4, "little")),
                       (0x20007554, int(sink).to_bytes(4, "little"))],
            oracles, effects)


REVIEWED_ORACLE_CASES[("app", 0x00023014)] = [
    _burial_case(1), _burial_case(1, level=2),
    _burial_case(1, level=2, sink=1), _burial_case(0),
    _burial_case(0, compare_result=1),
    _burial_case(0, compare_result=1, write_result=1, level=2, sink=1),
]


def _language_upgrade_case(result, level=0, sink=0):
    return ({0: 0x5a, 1: 0x11223344, 2: 0x55667788},
            [(0x2000230c, int(level).to_bytes(4, "little")),
             (0x20007554, int(sink).to_bytes(4, "little"))],
            {0: {0: result}})


REVIEWED_ORACLE_CASES[("app", 0x00023af0)] = [
    _language_upgrade_case(1), _language_upgrade_case(1, level=1),
    _language_upgrade_case(1, level=1, sink=1),
    _language_upgrade_case(0), _language_upgrade_case(0, level=3),
    _language_upgrade_case(0, level=3, sink=1),
]


def _net_strexb_case(enabled, cursor=0, wrapped=0, timer_event=0,
                     first_now=100, second_now=200, recent_sample=0):
    samples = bytearray(20)
    next_cursor = (int(cursor) + 1) % 5
    samples[next_cursor * 4:next_cursor * 4 + 4] = int(
        recent_sample).to_bytes(4, "little")
    memory = [
        (0x21004fab, b"\xa5"),
        (0x21004faa, bytes((int(enabled) & 0xff,))),
        (0x21004fa8, bytes((int(cursor) & 0xff,))),
        (0x21004fa7, bytes((int(wrapped) & 0xff,))),
        (0x21004640, bytes(samples)),
        (0x41005114, int(timer_event).to_bytes(4, "little")),
        (0x410121ac, (0xdeadbeef).to_bytes(4, "little")),
        (0x4100b004, bytes(4)),
    ]
    oracles = {}
    if enabled:
        oracles[0] = {0: int(first_now)}
        if not wrapped or (int(first_now) - int(recent_sample)) & 0xffffffff > 7:
            oracles[1] = {0: int(second_now)}
    return ({}, memory, oracles)


REVIEWED_TARGET_CALL_ARITIES[("net", 0x0102d1c0)] = {0x0103a6c6: 0}
REVIEWED_ORACLE_CASES[("net", 0x0102d1c0)] = [
    _net_strexb_case(0),
    _net_strexb_case(0),
    _net_strexb_case(1, cursor=0, wrapped=1,
                     first_now=100, recent_sample=95),
    _net_strexb_case(1, cursor=2, wrapped=0, timer_event=0),
    _net_strexb_case(1, cursor=4, wrapped=0, timer_event=1),
]
REVIEWED_INITIAL_EXCLUSIVE_MONITORS[("net", 0x0102d1c0)] = [
    None,
    (0x21004fab, 1),
    (0x21004fab, 1),
    (0x21004fab, 1),
    (0x21004fab, 1),
]


def _rtc_sync_init_case(stage, channel=3, callback_result=0):
    """Concrete channel allocation and driver-vtable paths for FUN_0004c2d4."""
    api = emu.SCRATCH + 0x1800
    methods = bytearray(20)
    if stage not in ("missing-setup", "lookup-error", "channel-error"):
        methods[4:8] = (0x00080001).to_bytes(4, "little")
    if stage not in ("missing-enable", "missing-setup", "lookup-error",
                     "channel-error", "setup-error"):
        methods[16:20] = (0x00080005).to_bytes(4, "little")
    memory = [
        (0x00087be0, api.to_bytes(4, "little")),
        (api, bytes(methods)),
    ]
    if stage == "lookup-error":
        return ({}, memory, {0: {0: 0}}, {})
    oracles = {0: {0: 0x0bad0000}, 1: {0: int(channel)}}
    writes = {
        0: [(0, 0, int(channel & 0xff).to_bytes(4, "little"),
             0x0006540c)]
    }
    if stage == "channel-error":
        oracles[1] = {0: 0xffffffff}
    elif stage == "setup-error":
        oracles[2] = {0: 0xffffffff}
    elif stage not in ("missing-setup", "missing-enable"):
        oracles[2] = {0: 0}
        oracles[3] = {0: int(callback_result)}
    return ({}, memory, oracles, writes)


# Both indirect methods have stable semantic targets but distinct ABIs.  The
# enable callback consumes only r0-r2; r3 is its branch register in the shipped
# code and caller scratch in the readable reconstruction.
REVIEWED_TARGET_CALL_ARITIES[("app", 0x0004c2d4)] = {
    0x00080000: 4,
    0x00080004: 3,
}
REVIEWED_ORACLE_CASES[("app", 0x0004c2d4)] = [
    _rtc_sync_init_case("lookup-error"),
    _rtc_sync_init_case("channel-error"),
    _rtc_sync_init_case("missing-setup"),
    _rtc_sync_init_case("setup-error"),
    _rtc_sync_init_case("missing-enable"),
    _rtc_sync_init_case("enable-error", callback_result=0xffffffff),
    _rtc_sync_init_case("enable-nonzero", callback_result=7),
    _rtc_sync_init_case("success", callback_result=0),
]


def _net_u256_multiply_case(left, right):
    output = emu.SCRATCH + 0x1000
    left_address = emu.SCRATCH + 0x1100
    right_address = emu.SCRATCH + 0x1200
    words = lambda values: b"".join(
        (int(value) & 0xffffffff).to_bytes(4, "little") for value in values)
    return ({0: output, 1: left_address, 2: right_address},
            [(output, bytes(64)),
             (left_address, words(left)),
             (right_address, words(right))], {})


REVIEWED_ORACLE_CASES[("net", 0x01008650)] = [
    _net_u256_multiply_case([0] * 8, [0x13579bdf] * 8),
    _net_u256_multiply_case([1] + [0] * 7,
                            [0x89abcdef, 1, 2, 3, 4, 5, 6, 7]),
    _net_u256_multiply_case([0xffffffff] * 8, [0xffffffff] * 8),
    _net_u256_multiply_case(
        [0x01234567, 0x89abcdef, 0x0badc0de, 0xfeedface,
         0x80000000, 0x7fffffff, 0x11111111, 0xeeeeeeee],
        [0x76543210, 0xfedcba98, 0xc001d00d, 0x12345678,
         0xffffffff, 0x00000001, 0x55555555, 0xaaaaaaaa]),
]


def _net_random_state_finalize_case(*seeds):
    """Model successive eight-byte outputs from the installed RNG provider."""
    writes = {}
    for ordinal, (state_a, state_b) in enumerate(seeds):
        payload = ((int(state_a) & 0xffffffff).to_bytes(4, "little") +
                   (int(state_b) & 0xffffffff).to_bytes(4, "little"))
        writes[ordinal] = [(0, 0, payload, 0x01009204)]
    return ({}, [(0x21000ef4, bytes(16))], {}, writes)


# FUN_01009204 is the sys_rand_get veneer and consumes only buffer plus length.
# Include both seed-word asymmetries and a provider retry so the complete
# two-word transition, its split-source rotate, and the refill backedge are
# compared against writes made by the production-shaped provider oracle.
REVIEWED_TARGET_CALL_ARITIES[("net", 0x0100f5d8)] = {0x01009204: 2}
REVIEWED_ORACLE_CASES[("net", 0x0100f5d8)] = [
    _net_random_state_finalize_case((1, 0)),
    _net_random_state_finalize_case((0, 1)),
    _net_random_state_finalize_case((0x01234567, 0x89abcdef)),
    _net_random_state_finalize_case((0xffffffff, 0x80000000)),
    _net_random_state_finalize_case((0, 0), (0x13579bdf, 0x2468ace0)),
]


def _net_ccm_result_case(active, saved_result, end_keystream=0,
                         end_crypt=0, error=0, mic_status=0):
    status = bytes((int(active) & 0xff, 0x5a,
                    int(saved_result) & 0xff, 0xa5))
    return (
        {},
        [(0x210014d8, status),
         (0x4100e100, int(end_keystream).to_bytes(4, "little")),
         (0x4100e104, int(end_crypt).to_bytes(4, "little")),
         (0x4100e108, int(error).to_bytes(4, "little")),
         (0x4100e400, int(mic_status).to_bytes(4, "little"))],
    )


# Cached completion plus every short-circuit point of the live CCM register
# path.  Non-boolean event words and a wide MICSTATUS value prove the exact
# zero/nonzero tests and shipped low-byte result contract.
REVIEWED_STATE_CASES[("net", 0x0101fd8c)] = [
    _net_ccm_result_case(0, 0x00),
    _net_ccm_result_case(0, 0xa7, end_keystream=1, end_crypt=1,
                         mic_status=0x55),
    _net_ccm_result_case(1, 0x33, end_keystream=0),
    _net_ccm_result_case(1, 0x33, end_keystream=7, end_crypt=0),
    _net_ccm_result_case(1, 0x33, end_keystream=7, end_crypt=9, error=1,
                         mic_status=0x44),
    _net_ccm_result_case(1, 0x33, end_keystream=7, end_crypt=9, error=0,
                         mic_status=0x123456a9),
]


def _net_handle_update_case(controller_state, handle=0x1234, value=0x5a,
                            entry=None, context=None, transition_result=0):
    oracles = {0: {0: int(controller_state) & 0xffffffff,
                   1: 0x89abcdef}}
    if int(controller_state) & 0x20000000:
        oracles[1] = {0: int(entry or 0)}
        if entry:
            oracles[2] = {0: int(context or 0)}
            if context:
                oracles[3] = {0: int(transition_result) & 0xffffffff}
    return ({0: int(handle) & 0xffff, 1: int(value) & 0xff}, [], oracles)


# Bit 29 is the exact readiness gate.  The remaining cases stop at each real
# failure boundary, then exercise two complete context transitions with
# nonuniform handle/value/result data.  The explicit entry argument at ordinal
# two prevents a stale-r0 reconstruction from receiving a false proof.
REVIEWED_TARGET_CALL_ARITIES[("net", 0x0102946c)] = {
    0x0101f8cc: 0,
    0x01009d18: 2,
    0x0101e090: 1,
    0x0101e15c: 3,
}
REVIEWED_ORACLE_CASES[("net", 0x0102946c)] = [
    _net_handle_update_case(0),
    _net_handle_update_case(0x10000000),
    _net_handle_update_case(0x20000000, entry=0),
    _net_handle_update_case(0x20000000, entry=emu.SCRATCH + 0x1000,
                            context=0),
    _net_handle_update_case(0x20000000, handle=0x2468, value=0xa5,
                            entry=emu.SCRATCH + 0x1000,
                            context=emu.SCRATCH + 0x2000,
                            transition_result=0),
    _net_handle_update_case(0xe0000000, handle=0xffff, value=0xff,
                            entry=emu.SCRATCH + 0x3000,
                            context=emu.SCRATCH + 0x4000,
                            transition_result=0x6d),
]


_NET_RESOURCE_FREE_MASK = emu.SCRATCH + 0x5000
_NET_RESOURCE_CLAIMED_INDEX = emu.SCRATCH + 0x5100


def _net_resource_claim_case(free_mask, output_seed=0xa5):
    return (
        {0: _NET_RESOURCE_FREE_MASK, 1: _NET_RESOURCE_CLAIMED_INDEX},
        [(_NET_RESOURCE_FREE_MASK,
          (int(free_mask) & 0xffffffff).to_bytes(4, "little")),
         (_NET_RESOURCE_CLAIMED_INDEX,
          bytes((int(output_seed) & 0xff,)))],
    )


# Empty, boundary-bit, and nonuniform masks prove highest-bit selection and
# the exact remaining bitmap.  The last two cases change the word on the
# compare-exchange read: one retries with a new mask, the other observes that
# a competing claimant exhausted the pool.
REVIEWED_STATE_CASES[("net", 0x01034328)] = [
    _net_resource_claim_case(0),
    _net_resource_claim_case(1),
    _net_resource_claim_case(0x80000000),
    _net_resource_claim_case(0x80000005),
    _net_resource_claim_case(0x7fffffff),
    _net_resource_claim_case(0x00010001),
    _net_resource_claim_case(0x80000005),
    _net_resource_claim_case(0x80000000, output_seed=0x6c),
]
ABSOLUTE_READ_TRANSITION_CASES[("net", 0x01034328)] = [
    [], [], [], [], [], [],
    [(_NET_RESOURCE_FREE_MASK, 2, 0x00000006)],
    [(_NET_RESOURCE_FREE_MASK, 2, 0x00000000)],
]
REVIEWED_NPTR_COUNTS[("net", 0x01034328)] = 2


# run_main_dispatch_thread has several calls whose argument registers are
# intentionally inherited from earlier calls in the shipped code.  Record the
# semantic callee contracts so stale r0-r3 values are excluded, while each
# thread-creation boundary compares all four register and four stack arguments.
REVIEWED_TARGET_CALL_ARITIES[("app", 0x0002a65c)] = {
    0x0007dda4: 2, 0x00019c70: 2,
    0x000864c2: 1, 0x00023a54: 1, 0x0002ace0: 0,
    0x00032ee4: 0, 0x00032fe8: 0, 0x0003304c: 0,
    0x0007cb66: 8, 0x00047ad0: 1, 0x00049638: 1,
}
REVIEWED_TARGET_CALL_STACK_ARITIES[("app", 0x0002a65c)] = {
    0x0007cb66: 4,
}


def _main_dispatch_case(mode, first_battery, final_battery,
                        level=0, sink=0):
    dispatch = emu.SCRATCH + 0xa000
    prefix = 1 if level > 2 else 0
    first_ordinal = prefix + 3
    after_initial_threads = prefix + (7 if first_battery == 0 else 8)
    final_ordinal = after_initial_threads + (0 if mode == 0 else 4)
    return (
        {0: dispatch},
        [(dispatch, bytes((mode,)) + bytes(15)),
         (0x2000230c, int(level).to_bytes(4, "little")),
         (0x20007554, int(sink).to_bytes(4, "little"))],
        {first_ordinal: {0: int(first_battery)},
         final_ordinal: {0: int(final_battery)}},
    )


REVIEWED_ORACLE_CASES[("app", 0x0002a65c)] = [
    _main_dispatch_case(0, 0, 0),
    _main_dispatch_case(0, 1, 1),
    _main_dispatch_case(1, 0, 1),
    _main_dispatch_case(1, 1, 0),
    _main_dispatch_case(2, 0, 0),
    _main_dispatch_case(2, 1, 1),
    _main_dispatch_case(1, 0, 0, level=3),
    _main_dispatch_case(2, 1, 0, level=3, sink=1),
]


def _att_create_pdu_case(flags, first_byte, auth_result=None,
                         headroom=3, opcode=0, create_result=0):
    """Production-shaped nested connection/net_buf state for FUN_00058a54."""
    context = emu.SCRATCH + 0xb000
    connection_slot = emu.SCRATCH + 0xb200
    packet = emu.SCRATCH + 0xb400
    cursor = emu.SCRATCH + 0xb600
    owner_slot = emu.SCRATCH + 0xb800
    connection = emu.SCRATCH + 0xba00
    context_image = bytearray(0x124)
    context_image[0:4] = connection_slot.to_bytes(4, "little")
    context_image[0x120:0x124] = int(flags).to_bytes(4, "little")
    packet_image = bytearray(0x1c)
    packet_image[0x0c:0x10] = cursor.to_bytes(4, "little")
    packet_image[0x10:0x12] = (0x1357).to_bytes(2, "little")
    packet_image[0x14:0x18] = (cursor - headroom).to_bytes(4, "little")
    packet_image[0x18:0x1c] = owner_slot.to_bytes(4, "little")
    moves = [
        (context, bytes(context_image)),
        (connection_slot, connection.to_bytes(4, "little")),
        (packet, bytes(packet_image)),
        (cursor, bytes((first_byte,)) + bytes(15)),
        (owner_slot, (0x2468ace0).to_bytes(4, "little")),
    ]
    oracle_returns = {}
    if flags & 4:
        ordinal = 0
        if first_byte == 0xd2:
            oracle_returns[ordinal] = {0: int(auth_result or 0) & 0xffffffff}
            ordinal += 1
            if auth_result:
                return ({0: context, 1: packet}, moves, oracle_returns)
        oracle_returns[ordinal] = {0: int(headroom) & 0xffffffff}
        ordinal += 1
        oracle_returns[ordinal] = {0: int(opcode) & 0xffffffff}
        ordinal += 1
        if opcode <= 5:
            oracle_returns[ordinal] = {0: int(create_result) & 0xffffffff}
    return ({0: context, 1: packet}, moves, oracle_returns)


REVIEWED_ORACLE_CASES[("app", 0x00058a54)] = [
    _att_create_pdu_case(0, 0x02),
    _att_create_pdu_case(4, 0xd2, auth_result=7),
    _att_create_pdu_case(4, 0xd2, auth_result=0, opcode=0,
                         create_result=0),
    _att_create_pdu_case(4, 0x02, opcode=5, create_result=0),
    _att_create_pdu_case(4, 0x02, opcode=2, create_result=-105),
    _att_create_pdu_case(4, 0x02, opcode=3, create_result=-7),
    _att_create_pdu_case(4, 0x02, opcode=6),
]


def _status_notify_case(selector, box_state=0x42, variant=0,
                        accessor_result=None):
    """One complete BLE context/request for FUN_00021334.

    Generic pointer synthesis used to alias the request and context for some
    nptr modes.  It consequently replaced the context callback with bytes from
    the request and recursively entered 0x2144c until the instruction budget
    expired.  These bounded fixtures model the two distinct production
    objects and keep every byte consumed by the status encoder explicit.
    """
    context = emu.SCRATCH + 0xc000
    request = emu.SCRATCH + 0xe000
    request_image = bytearray(16)
    request_image[0] = 0xa5
    request_image[1] = int(selector) & 0xff
    request_image[2] = 0x3c
    memory = [
        (context + 0x000c, (0x00080001).to_bytes(4, "little")),
        (context - 0x06b0, b"\x72"),
        (context - 0x06af, b"\x39"),
        (context + 0x0759, b"\x2b"),
        (context + 0x0844, bytes((int(box_state) & 0xff,))),
        (context + 0x0846, bytes((int(variant) & 0xff,))),
        (request, bytes(request_image)),
        (0x20018d99, b"\x55"),
        (0x20018d9a, b"\x44"),
    ]
    oracles = {}
    if accessor_result is not None:
        # Ordinal zero is the explicit memset; the selected box accessor is
        # ordinal one and the two-argument transport callback is ordinal two.
        oracles[1] = {0: int(accessor_result) & 0xff}
    return ({0: context, 1: request}, memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x00021334)] = [
    # Every TBB selector, including all default entries.
    *[_status_notify_case(selector) for selector in range(0x09, 0x13)],
    # Both zero/out-of-range default families and all three high C9 replies.
    _status_notify_case(0x00),
    _status_notify_case(0x13),
    _status_notify_case(0xf0),
    _status_notify_case(0xf1),
    _status_notify_case(0xf2),
    # Every nested box-state conversion edge, including the variant splits.
    _status_notify_case(0x0a, box_state=0x5c),
    _status_notify_case(0x0a, box_state=0x5d, variant=0),
    _status_notify_case(0x0a, box_state=0x5d, variant=1),
    _status_notify_case(0x0a, box_state=0x5e, variant=0),
    _status_notify_case(0x0a, box_state=0x5e, variant=1),
    _status_notify_case(0x0a, box_state=0x5f),
    _status_notify_case(0x0a, box_state=0x60),
    _status_notify_case(0x0a, box_state=0x61),
    # Nonuniform accessor returns catch constant/substitution cheats.
    _status_notify_case(0x0e, accessor_result=0x6d),
    _status_notify_case(0x0f, accessor_result=0x83),
]
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00021334)] = {
    0x00086c78: 3,
    0x00032784: 0,
    0x000327c4: 0,
    0x00080000: 2,
}
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x00021334)] = [
    # Both compilers place the complete transmitted record at entry-SP-40.
    # Scope comparison to the transport callback: the preceding memset sees
    # only its +4 interior before those seventeen bytes have been initialized.
    ("status-notify-packet", -40, -40, 21, None, None, (0x00080000,)),
]


def _onboarding_render_case(mode, secondary=0, retry=0, attempt=0,
                            saved_time=0):
    """Concrete device/status objects for the callee-selected render modes."""
    device = emu.SCRATCH + 0xc000
    status = emu.SCRATCH + 0xe000
    device_image = bytearray(0x1020)
    status_image = bytearray(16)
    device_image[0xee4] = 0x5a
    device_image[0x1014:0x1018] = status.to_bytes(4, "little")
    status_image[2] = int(mode) & 0xff
    status_image[3] = 0
    saved_time = device if saved_time == "now" else int(saved_time)
    status_image[4:12] = saved_time.to_bytes(8, "little")
    memory = [
        (device, bytes(device_image)),
        (status, bytes(status_image)),
        (0x2001cdce, bytes((int(secondary) & 0xff,))),
        (0x2001cdd0, bytes((int(retry) & 0xff,))),
        (0x2001cdd1, bytes((int(retry) & 0xff,))),
        (0x2001cdd2, bytes((int(attempt) & 0xff,))),
    ]
    # get_device_info is called at different ordinals in every render arm.
    # Supplying the same concrete singleton at all boundaries is harmless for
    # scalar/layout oracles and makes every device-info dereference valid.
    oracles = {i: {0: device, 1: 0} for i in range(200)}
    return ({}, memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x000417f8)] = [
    # Every TBH entry (including aliases and default), plus the timed retry,
    # secondary-screen and one-shot redraw gates that choose the substantial
    # nested bodies for modes 5/6/19/20/21.
    *[_onboarding_render_case(mode) for mode in
      (0, 3, 4, 5, 6, 8, 15, 17, 19, 20, 21, 22, 23, 0xff)],
    _onboarding_render_case(0, saved_time="now"),
    _onboarding_render_case(3, retry=1, saved_time="now"),
    _onboarding_render_case(3, retry=6),
    _onboarding_render_case(5, secondary=1, saved_time="now"),
    _onboarding_render_case(5, secondary=2, retry=1),
    _onboarding_render_case(5, secondary=2, retry=1, attempt=1),
    _onboarding_render_case(20, secondary=1),
    _onboarding_render_case(21, secondary=1),
    _onboarding_render_case(6, secondary=1, saved_time="now"),
    _onboarding_render_case(6, secondary=2, retry=1),
    _onboarding_render_case(19, secondary=1),
    _onboarding_render_case(19, secondary=2, retry=1),
    _onboarding_render_case(23, retry=1, saved_time="now"),
    _onboarding_render_case(23, retry=6),
]


def _net_clock_batch_case(active_requests, pending_requests):
    context = bytearray(16)
    context[10] = int(active_requests) & 0xff
    context[11] = 0xa5  # stale published value must always be replaced
    context[12] = int(pending_requests) & 0xff
    return ({}, [(0x21001670, bytes(context))], {})


REVIEWED_ORACLE_CASES[("net", 0x010217cc)] = [
    # Disabled, minimum-one, exact division, rounded division and byte-limit
    # boundaries for the complete onoff-manager batch calculation.
    _net_clock_batch_case(0, 0),
    _net_clock_batch_case(0, 255),
    _net_clock_batch_case(1, 0),
    _net_clock_batch_case(2, 1),
    _net_clock_batch_case(2, 4),
    _net_clock_batch_case(3, 8),
    _net_clock_batch_case(10, 255),
    _net_clock_batch_case(255, 255),
]


_DISPLAY_THREAD_CONTEXT = emu.SCRATCH + 0xc000


def _display_thread_case(phase, opcode=None, parameter_kind=0,
                         selector=1, payload=7, parameter=0x12345678,
                         current_panel=3, runtime_state=0,
                         log_level=0, alternate_sink=0,
                         queue_status=None):
    """One complete display worker iteration with a concrete 24-byte record."""
    context = bytearray(0xc00)
    context[1] = int(runtime_state) & 0xff
    context[0xd5] = int(current_panel) & 0xff
    record = bytearray(24)
    if opcode is not None:
        record[0] = int(opcode) & 0xff
        struct.pack_into("<H", record, 2, int(parameter_kind) & 0xffff)
        encoded = (int(selector) | (int(payload) << 8)
                   if parameter_kind == 2 else int(parameter))
        struct.pack_into("<I", record, 4, encoded & 0xffffffff)

    memory = [
        (_DISPLAY_THREAD_CONTEXT, bytes(context)),
        (0x2000230c, int(log_level).to_bytes(4, "little", signed=True)),
        (0x20007554, int(alternate_sink).to_bytes(4, "little", signed=True)),
        (0x20002544, (2).to_bytes(4, "little", signed=True)),
        (0x200038c4, bytes(0x28)),
        (0x20004ce0, bytes(0x40)),
        (0x2001d446, b"\0"),
        (0x2001d447, bytes((int(phase) & 0xff, 0x5a))),
    ]

    # Without logging, queue receive is ordinal five: initial memset,
    # timer-init, canvas-select, per-iteration memset, 64-bit divide, receive.
    # Each initial logger adds one; a busy runtime adds sleep and, when
    # enabled, the wait logger too.
    queue_ordinal = 5 + (2 if log_level > 2 else 0)
    if runtime_state in (1, 8):
        queue_ordinal += 1 + (1 if log_level > 2 else 0)
    status = (0 if opcode is not None else -35) if queue_status is None else queue_status
    oracles = {queue_ordinal: {0: int(status) & 0xffffffff}}
    writes = ({queue_ordinal: [(1, 0, bytes(record), 0x00072240)]}
              if status == 0 else {})
    return ({0: _DISPLAY_THREAD_CONTEXT}, memory, oracles, writes)


_display_thread_cases = [
    # Idle start/stop parameter encodings, malformed records, and ignored op.
    _display_thread_case(0, 2, 0, current_panel=3),
    _display_thread_case(0, 2, 2, selector=1, payload=9),
    _display_thread_case(0, 2, 2, selector=0, payload=9),
    _display_thread_case(0, 3, 0, current_panel=4),
    _display_thread_case(0, 3, 2, selector=1, payload=6),
    _display_thread_case(0, 3, 2, selector=2, payload=6),
    _display_thread_case(0, 4, parameter=0x87654321),
    # Active queue timeout/retry and every live message opcode.
    _display_thread_case(1, None, current_panel=5),
    _display_thread_case(1, None, current_panel=0),
    _display_thread_case(1, 2, 0, current_panel=2),
    _display_thread_case(1, 3, 0, current_panel=2),
    _display_thread_case(1, 4, parameter=0x13579bdf, current_panel=2),
    _display_thread_case(1, 5, current_panel=2),
    _display_thread_case(1, 6, current_panel=2),
    _display_thread_case(1, 7, current_panel=2),
    _display_thread_case(1, 8, current_panel=2),
    # Stopping, corrupt phase, both logger sinks, and a finite busy wait.
    _display_thread_case(2, 5, current_panel=2),
    _display_thread_case(9, 5, current_panel=2),
    _display_thread_case(1, 4, parameter=17, current_panel=2,
                         log_level=4, alternate_sink=0),
    _display_thread_case(1, 5, current_panel=2,
                         log_level=4, alternate_sink=1),
    _display_thread_case(0, None, runtime_state=1),
]
REVIEWED_ORACLE_CASES[("app", 0x00049090)] = _display_thread_cases
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00049090)] = {
    0x0000e244: 4,
    0x000167a8: 0,
    0x00019c70: 0,
    0x000431b4: 1,
    0x00048e28: 4,
    0x00048ff4: 0,
    0x00049000: 1,
    0x0004906c: 0,
    0x00072240: 4,
    0x0007cb8a: 2,
    0x0007d6f4: 1,
    0x0007dda4: 3,
    0x00086726: 3,
    0x00086c78: 3,
}
REVIEWED_CALL_ARITIES_BY_FORMAT[("app", 0x00049090)] = {
    **{(0x0007dda4, fmt): 2 for fmt in (
        0x000efb2e, 0x000efb50, 0x000efb7a, 0x000efb9f,
        0x000efbb7, 0x000efc00, 0x000efc2d, 0x000efc62,
        0x000efcaf, 0x000efcdf, 0x000efd03, 0x000efd45,
        0x000efd6f, 0x000efef4, 0x000eff0e, 0x000eff2c,
        0x000eff5c, 0x000eff70, 0x000effaf,
    )},
    **{(0x0007dda4, fmt): 3 for fmt in (
        0x000efbe5, 0x000efc92, 0x000efd2d, 0x000efe74,
        0x000efebc,
    )},
}
REVIEWED_NPTR_COUNTS[("app", 0x00049090)] = 1
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x00049090)] = [
    # The complete 24-byte queue record is at entry-SP-64 in the shipped
    # register-rich loop and entry-SP-56 in the readable structured body.
    ("display-queue-record", -64, -56, 24, None, None,
     (0x00086c78, 0x00072240)),
]
ABSOLUTE_READ_TRANSITION_CASES[("app", 0x00049090)] = [
    *([[]] * (len(_display_thread_cases) - 1)),
    [(_DISPLAY_THREAD_CONTEXT + 1, 1, 0)],
]


def _lc3_spec_encode_case(dt, sample_rate, bandwidth, quantized,
                          significant_count, lsb_mode, accumulator_bits=0):
    bits = emu.SCRATCH + 0x1000
    output = emu.SCRATCH + 0x2000
    quantized_address = emu.SCRATCH + 0x3000
    side = emu.SCRATCH + 0x4000
    spectrum_address = emu.SCRATCH + 0x5000

    bits_image = bytearray(64)
    struct.pack_into("<I", bits_image, 8, 0x00ffffff)  # AC range
    struct.pack_into("<i", bits_image, 12, -1)         # AC cache
    struct.pack_into("<I", bits_image, 32, accumulator_bits)
    for offset, pointer in ((40, output), (44, output + 400),
                            (48, output), (52, output + 400)):
        struct.pack_into("<I", bits_image, offset, pointer)

    quantized_image = bytearray(800)
    for index, value in enumerate(quantized):
        struct.pack_into("<H", quantized_image, 2 * index,
                         int(value) & 0xffff)
    side_image = bytearray(12)
    struct.pack_into("<i", side_image, 4, int(significant_count))
    side_image[8] = bool(lsb_mode)
    spectrum_image = bytearray(500 * 4)
    for index in range(500):
        # Nonuniform bounded values exercise positive/negative residual and
        # noise-estimation comparisons without NaNs or infinities.
        value = ((index % 11) - 5) * 0.1875
        struct.pack_into("<f", spectrum_image, 4 * index, value)

    memory = [(bits, bytes(bits_image)), (output, bytes(400)),
              (quantized_address, bytes(quantized_image)),
              (side, bytes(side_image)),
              (spectrum_address, bytes(spectrum_image))]
    # Only lc3_get_bits_left has a scalar result.  The other two boundaries
    # are void accumulator/renormalization helpers, so the common bounded r0
    # value is ignored there while keeping the residual/LSB budget finite.
    oracles = {ordinal: {0: 8} for ordinal in range(200)}
    return ({0: bits, 1: dt, 2: sample_rate, 3: bandwidth},
            memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x0006f9c0)] = [
    _lc3_spec_encode_case(0, 0, 0, (), 0, False),
    _lc3_spec_encode_case(1, 0, 0, (0, 0), 2, False),
    _lc3_spec_encode_case(0, 0, 0, (2, 0), 2, False),
    _lc3_spec_encode_case(0, 0, 0, (8, 0), 2, True),
    _lc3_spec_encode_case(1, 1, 1, (3, 4, 0, 2), 4, False),
    _lc3_spec_encode_case(0, 2, 2, (17, 10, 4, 3, 0, 8), 6, True),
    _lc3_spec_encode_case(1, 0, 0, (2, 3), 2, False,
                          accumulator_bits=31),
    _lc3_spec_encode_case(1, 1, 2, (31, 16, 7, 2), 4, True),
]


def _draw_message_case(icon_type=None, sink=0, body=True, subtitle=True,
                       rendered_body=True):
    """Bounded notification-renderer state with exact formatter ownership.

    The icon selector is returned by the second application call after the
    three initial buffer clears.  Random oracle values previously selected
    only the default arm and, more importantly, the opaque snprintf wrapper
    never populated its output, so every body path returned early.  These
    fixtures cover the null routes, all five concrete icons, the fallback
    title/subtitle split, all body-format families, and both centered-message
    empty/nonempty exits.  Formatter writes are tied to both ordinal and the
    reviewed FUN_00077914 target.
    """
    level = [(0x20007554, int(sink).to_bytes(4, "little"))]
    if icon_type is None:
        return ({0: 7, 1: 0}, level, {})

    message = emu.SCRATCH + 0x4800
    record = bytearray(0xb0)
    record[0:4] = (0x10203040).to_bytes(4, "little")
    record[0x30:0x36] = b"TITLE\0"
    if body:
        record[0x50:0x55] = b"BODY\0"
    if subtitle:
        record[0x70:0x74] = b"SUB\0"
    record[0x90:0x98] = b"PACKAGE\0"
    memory = [(message, bytes(record))] + level
    oracles = {3: {0: 2}, 4: {0: int(icon_type)}}
    writes = {}
    if icon_type == 2:
        writes[7] = [(0, 0, b"PACKAGE\0", 0x00077914)]
        writes[17] = [(0, 0, (b"BODY\0" if rendered_body else b"\0"),
                       0x00077914)]
    else:
        writes[10] = [(0, 0, b"HEADING\0", 0x00077914)]
        writes[28] = [(0, 0, (b"BODY PACKAGE\0" if rendered_body else b"\0"),
                        0x00077914)]
    return ({0: 7, 1: message}, memory, oracles, writes)


REVIEWED_ORACLE_CASES[("app", 0x00035afc)] = [
    _draw_message_case(None, sink=0),
    _draw_message_case(None, sink=1),
    _draw_message_case(0, body=False, subtitle=False),
    _draw_message_case(1, body=True, subtitle=False),
    _draw_message_case(2, rendered_body=False),
    _draw_message_case(2, rendered_body=True),
    _draw_message_case(3, body=True, subtitle=True),
    _draw_message_case(4, body=True, subtitle=False),
    _draw_message_case(5, body=False, subtitle=False),
    _draw_message_case(5, body=True, subtitle=True),
]


def _slave_display_case(event, command=0, value=0, work_mode=0,
                        ready=1, aux=0, flag=0, system_event=0,
                        onboarding_mode=0, message_ready=0,
                        unread_mode=0):
    """One production-shaped iteration of the nonreturning slave worker.

    The worker, the device singleton, and its embedded dispatch state are the
    same object in firmware.  Separate pointed-to persistence/event records
    keep every indirect access concrete while the fifty-event reviewed prefix
    reaches the following iteration after each selected handler completes.
    """
    context = emu.SCRATCH + 0xc000
    dnd = emu.SCRATCH + 0xe000
    onboarding = emu.SCRATCH + 0xe100
    quick_note = emu.SCRATCH + 0xe200
    system_record = emu.SCRATCH + 0xe300
    image = bytearray(0x1100)
    image[0] = 2
    image[0xcb] = 0x2a
    image[0xd4] = int(event) & 0xff
    image[0xd5] = int(work_mode) & 0xff
    image[0xe5] = int(command) & 0xff
    image[0xe6] = int(value) & 0xff
    image[0xe7] = int(aux) & 0xff
    image[0xe8] = int(flag) & 0xff
    image[0xed5] = 0x2a
    image[0xed7] = 0x2a
    image[0xfe6] = int(ready) & 0xff
    image[0x1010:0x1014] = dnd.to_bytes(4, "little")
    image[0x1014:0x1018] = onboarding.to_bytes(4, "little")
    image[0x1020:0x1024] = quick_note.to_bytes(4, "little")
    image[0x1054:0x1058] = system_record.to_bytes(4, "little")
    image[0x108f] = int(message_ready) & 0xff
    image[0xdd] = 3
    image[0xd5] = int(unread_mode if event == 7 and command == 3
                      else work_mode) & 0xff
    onboarding_image = bytearray(0x30)
    onboarding_image[1] = 0
    onboarding_image[2] = int(onboarding_mode) & 0xff
    memory = [
        (context, bytes(image)),
        (dnd, bytes(16)),
        (onboarding, bytes(onboarding_image)),
        (quick_note, bytes(16)),
        (system_record, int(system_event).to_bytes(4, "little")),
        (0x2000230c, bytes(4)),       # logging disabled
        (0x20007554, bytes(4)),
        (0x20018d96, b"\0"),
        (0x20018d97, b"\0"),
        (0x20018d9f, b"\0"),
        (0x20018d8d, b"\0"),
        (0x20018462, b"\x03"),
        (0x2001cdce, b"\x12"),
        (0x2001b9ab, b"\0"),
        (0x20007b38, bytes(4)),
    ]
    # Every accessor observes the concrete singleton.  Other callees' return
    # values are harmless but deliberately nonzero, selecting the substantial
    # battery/message/onboarding arms instead of manufacturing null pointers.
    oracles = {i: {0: context, 1: 0x12345678} for i in range(160)}
    return ({0: context, 1: 0x11223344, 2: 0x55667788, 3: 0x7e},
            memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x00027cfe)] = [
    _slave_display_case(0, work_mode=6),
    _slave_display_case(1, ready=0),
    _slave_display_case(1, ready=1),
    _slave_display_case(2, command=0, work_mode=5),
    _slave_display_case(2, command=11, value=9, aux=8, work_mode=6),
    _slave_display_case(3),
    _slave_display_case(4),
    _slave_display_case(5),
    _slave_display_case(6, command=9, value=0x35),
    _slave_display_case(6, command=1, value=0, work_mode=12),
    _slave_display_case(6, command=1, value=1, work_mode=5),
    _slave_display_case(6, command=2, value=0x21, work_mode=6),
    _slave_display_case(6, command=2, value=0x21, work_mode=5),
    _slave_display_case(6, command=2, value=0x32, work_mode=5),
    _slave_display_case(6, command=2, value=0x43, work_mode=6),
    _slave_display_case(6, command=2, value=0x54, work_mode=5),
    _slave_display_case(6, command=2, value=0x65, work_mode=6),
    _slave_display_case(6, command=2, value=0x76, work_mode=5),
    _slave_display_case(6, command=2, value=0x80, work_mode=5),
    _slave_display_case(6, command=3, value=1, work_mode=9),
    _slave_display_case(6, command=3, value=0, work_mode=9),
    _slave_display_case(6, command=3, value=1, work_mode=8),
    _slave_display_case(6, command=4, value=3, aux=0x12, flag=1,
                        system_event=14, onboarding_mode=3),
    _slave_display_case(6, command=4, value=11, aux=1, flag=0,
                        onboarding_mode=11),
    _slave_display_case(6, command=5, value=1),
    _slave_display_case(6, command=6, value=1, work_mode=10),
    _slave_display_case(6, command=6, value=0, work_mode=10),
    _slave_display_case(6, command=7, value=0x44, work_mode=6),
    _slave_display_case(6, command=7, value=0x44, work_mode=5),
    _slave_display_case(6, command=8, value=2),
    _slave_display_case(6, command=8, value=3),
    _slave_display_case(6, command=10),
    _slave_display_case(7, command=0),
    _slave_display_case(7, command=1),
    _slave_display_case(7, command=2),
    _slave_display_case(7, command=3, message_ready=1, unread_mode=3),
    _slave_display_case(8, command=1, work_mode=4),
    _slave_display_case(8, command=0, work_mode=5),
]
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00027cfe)] = {
    0x000167a8: 0,  # get_device_info()
    0x0001694c: 1,  # change_work_mode_to(mode)
    0x00019c70: 2,  # debug_print(format, tag, ...); logs disabled in fixtures
    0x00023af0: 1,  # upgradeAppLanguageInfoToFlash(language)
    0x00023bfc: 1,  # upgradeDashboardStartupModeInfoToFlash(mode)
    0x00023eec: 0,  # get_pending_language_code()
    0x0002bc2c: 3,  # trigger_screen_state_change(reason, context, enabled)
    0x0002bed0: 1,  # check_battery_critical(context)
    0x0002bef4: 3,  # update_persist_task_status(context, task, state)
    0x0002bffc: 3,  # update_temp_task_status(context, task, state)
    0x0002c0e8: 1,  # update_persist_task_status_to_idle(context)
    0x0002c1fc: 0,  # check_pending_messages_flag()
    0x00032ee4: 0,  # is_battery_critical()
    0x00033cf8: 0,  # msg_content_recalc_unread()
    0x00033d58: 1,  # clear_timeout_message(reason)
    0x00034274: 0,  # msg_count_dec()
    0x0003439c: 0,  # push_message_3439c()
    0x0003441c: 0,  # msg_content_decrement_timer()
    0x0003443c: 1,  # set_message_indicator(value)
    0x0003707c: 1,  # handle_touch_single_click(side)
    0x00037108: 1,  # handle_dashboard_action(side)
    0x000371e8: 1,  # handle_stocks_action(side)
    0x0003cb4c: 0,  # update_not_disturb_settings()
    0x00040708: 0,  # onboarding_retry_watchdog_update()
    0x000429f8: 0,  # refresh_onboarding_retry_state()
    0x00042fb0: 2,  # cal_panel_canvas_coord(panel, canvas)
    0x00047058: 1,  # set_brightness_to_panel_reg_in_running(level)
    0x000498c0: 1,  # display_DelayClose(delay_ms)
    0x00049938: 2,  # display_inputEvent(event, pressed)
    0x000499b8: 0,  # display_MasterSendClose()
    0x00049a28: 1,  # display_powerEvent(event)
    0x0007cb4c: 1,  # process_sync_buffer(object)
    0x0007cb50: 0,  # process_touch_event()
    0x0007cb54: 1,  # set_atomic_flag_bits(flags)
    0x0007cb8a: 2,  # wait_for_event(timeout, flags)
    0x0007cb2c: 0,  # k_uptime_get_1()
    0x0007cbfe: 2,  # set_shutdown_flag(context, publish)
    0x0007c132: 2,  # peer_address_is_uninitialized(low, high)
    0x0007cdb6: 2,  # prepare_quick_note_mode(context, side)
    0x0007cce8: 2,  # update_display_status(context, status)
    0x0007d224: 0,  # get_timestamp()
    0x0007d3be: 0,  # reset_onboarding_bitmap_state()
}
REVIEWED_CALL_ARGUMENT_INDICES_BY_TARGET[("app", 0x00027cfe)] = {
    # The 64-bit timeout follows AAPCS even-register alignment: r1 is an
    # unused hole and the complete UINT64_MAX value occupies r2:r3.
    0x0007cb48: (0, 2, 3),
}


def _sync_to_slave_case(command, gate=None, current_mode=0, device_mode=0,
                        battery_critical=0, role=1, uptime=10000,
                        last_sync=0, active_command=0, dispatch=False,
                        payload_length=0, late_reject=False):
    """Concrete gate, throttle, dispatch, and late-validation paths."""
    context = emu.SCRATCH + 0x1000
    device = emu.SCRATCH + 0x3000
    snapshot = emu.SCRATCH + 0x4000
    mode_record = emu.SCRATCH + 0x4100
    payload = emu.SCRATCH + 0x5000
    image = bytearray(0x1080)
    image[0] = int(role) & 0xff
    image[0xd0:0xd4] = (0xaabbccdd).to_bytes(4, "little")
    image[0xd5] = 9 if late_reject else 5
    image[0xec] = 8 if late_reject else (0 if dispatch else 1)
    image[0xeb] = 8 if late_reject else 1
    image[0xee4] = 8 if late_reject else 2
    image[0xfec:0xff0] = snapshot.to_bytes(4, "little")
    image[0x1000:0x1004] = mode_record.to_bytes(4, "little")
    image[0x1060:0x1068] = int(last_sync).to_bytes(8, "little")
    # Reviewed data-derived callback target.  Both machines invoke the same
    # external Thumb sentinel after building their complete 0x21-byte packet.
    image[0x774:0x778] = (0x00080001).to_bytes(4, "little")
    device_image = bytearray(8)
    device_image[1] = int(device_mode) & 0xff
    memory = [
        (context, bytes(image)), (device, bytes(device_image)),
        (snapshot, (0x12345678).to_bytes(4, "little")),
        (mode_record, bytes(16)),
        (payload, bytes((0x31, 0x52, 0x73, 0x94, 0xb5, 0xd6, 0xf7, 0x18))),
        (0x2000f6e6, bytes(2)), (0x20018d8f, bytes(1)),
        (0x20018d9c, bytes(1)),
        (0x2000302b, bytes((int(active_command) & 0xff,))),
        (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
    ]
    oracles = {0: {0: 0}, 1: {0: int(current_mode)}}
    if gate != "work-mode":
        oracles[2] = {0: device}
        if gate != "device-mode":
            oracles[3] = {0: int(battery_critical)}
            if gate not in ("battery", "role"):
                oracles[4] = {
                    0: int(uptime) & 0xffffffff,
                    1: (int(uptime) >> 32) & 0xffffffff,
                }
    # The real memset owns all 248 packet bytes.  The dispatch callback then
    # acknowledges via context+0x105a, bounding the wait loop immediately.
    writes = {0: [(0, 0, bytes(248), 0x00086c78)]}
    if dispatch:
        writes[5] = [(None, context + 0x105a, b"\x02")]
    payload_arg = payload if payload_length else 0
    return ({0: context, 1: int(command), 2: payload_arg,
             3: int(payload_length)}, memory, oracles, writes)


REVIEWED_ORACLE_CASES[("app", 0x00026f74)] = [
    _sync_to_slave_case(3, gate="work-mode", current_mode=1),
    _sync_to_slave_case(3, gate="device-mode", device_mode=8),
    _sync_to_slave_case(3, gate="battery", battery_critical=1),
    _sync_to_slave_case(3, gate="role", role=2),
    _sync_to_slave_case(12, uptime=500),
    _sync_to_slave_case(3, dispatch=True, payload_length=8),
    _sync_to_slave_case(0, late_reject=True),
]
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00026f74)] = {
    0x000167a8: 0,  # get_device_info()
    0x00016940: 0,  # get_current_work_mode()
    0x00019c70: 2,  # debug_print(format, function, ...)
    0x00032ee4: 0,  # is_battery_critical()
    0x0007cb2c: 0,  # k_uptime_get_1()
    0x0007cb8e: 1,  # one-millisecond wait
    0x0007d230: 1,  # restore synchronization value
    0x0007dda4: 2,  # log_message(format, function, ...)
    0x00086c04: 3,  # memcpy
    0x00086c78: 3,  # memset
    0x00080000: 2,  # packet transport callback(packet, 0x21)
}
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x00026f74)] = [
    # Both frames place the 252-byte packet at entry-SP-292.  The first four
    # header bytes precede the memset's packet+4 argument; compare the whole
    # initialized transport object at its callback boundary.
    ("sync-packet", -292, -292, 252, None, (5,), (0x00080000,)),
]


def _local_esbs_recv_case(command, sequence=2, direction=0,
                          context_mode=5, received_mode=6,
                          suspend_state=0, receive_busy=False,
                          packet_status=4, packet_side=0,
                          message_state=0):
    """Production-shaped ESB IPC record and complete reachable object graph."""
    context = emu.SCRATCH + 0x1000
    packet = emu.SCRATCH + 0x3000
    master = emu.SCRATCH + 0x4000
    screen = emu.SCRATCH + 0x5200
    task = emu.SCRATCH + 0x5300
    timestamp_store = emu.SCRATCH + 0x5400
    mirror = emu.SCRATCH + 0x5500
    alternate_up = emu.SCRATCH + 0x5800
    alternate_down = emu.SCRATCH + 0x5b00
    message = emu.SCRATCH + 0x5e00
    image = bytearray(0x1100)
    image[0xc9] = 0x80
    image[0xd5] = int(context_mode) & 0xff
    image[0xda] = 1
    image[0xce] = 1 if receive_busy else 0
    image[0xcf] = 1 if receive_busy else 0
    image[0xfe6] = int(suspend_state) & 0xff
    image[0xfec:0xff0] = timestamp_store.to_bytes(4, "little")
    image[0xff4:0xff8] = mirror.to_bytes(4, "little")
    image[0x1024:0x1028] = alternate_up.to_bytes(4, "little")
    image[0x1028:0x102c] = alternate_down.to_bytes(4, "little")
    record = bytearray(21)
    record[0] = (int(command) | int(direction)) & 0xff
    record[1] = int(received_mode) & 0xff
    record[6] = int(sequence) & 0xff
    record[17:21] = (0x12345678).to_bytes(4, "little")
    packet_image = bytearray(32)
    packet_image[0] = int(packet_status) & 0xff
    packet_image[1] = int(packet_side) & 0xff
    packet_image[3] = 0x31
    packet_image[4] = 0x52
    packet_image[7:11] = (0x89abcdef).to_bytes(4, "little")
    packet_image[11:32] = record
    master_image = bytearray(0x1100)
    master_image[0x100c:0x1010] = screen.to_bytes(4, "little")
    master_image[0x1054:0x1058] = task.to_bytes(4, "little")
    message_image = bytearray(32)
    message_image[13] = int(message_state) & 0xff
    memory = [
        (context, bytes(image)), (packet, bytes(packet_image)),
        (master, bytes(master_image)), (screen, bytes(8)),
        (task, bytes(4)), (timestamp_store, bytes(4)),
        (mirror, bytes(0x180)),
        (alternate_up, bytes(0x210)), (alternate_down, bytes(0x210)),
        (message, bytes(message_image)),
        (0x200069fc, master.to_bytes(4, "little")),
        (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
        (0x20018d98, b"\x01"),
    ]
    # memset, timestamp publication, then optional message lookup.
    oracles = {0: {0: 0}, 1: {0: 0}, 2: {0: message}}
    writes = {0: [(0, 0, bytes(18), 0x00086c78)]}
    return ({0: context, 1: packet}, memory, oracles, writes)


REVIEWED_ORACLE_CASES[("app", 0x00015960)] = [
    _local_esbs_recv_case(3, sequence=1),
    _local_esbs_recv_case(1, suspend_state=1),
    _local_esbs_recv_case(2, suspend_state=0),
    _local_esbs_recv_case(3, direction=0x80, context_mode=9,
                          receive_busy=True),
    _local_esbs_recv_case(3, context_mode=16, receive_busy=True),
    _local_esbs_recv_case(0),
    _local_esbs_recv_case(10, message_state=0),
    _local_esbs_recv_case(11, message_state=2),
    _local_esbs_recv_case(12),
    _local_esbs_recv_case(13),
    _local_esbs_recv_case(14),
    _local_esbs_recv_case(15),
    _local_esbs_recv_case(16),
    _local_esbs_recv_case(17),
    _local_esbs_recv_case(18),
    _local_esbs_recv_case(12, packet_status=3, packet_side=1),
]
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00015960)] = {
    0x000158bc: 1,  # switch_to_dfu_mode(state)
    0x00019c70: 2,  # debug_print(format, function, ...)
    0x0002bef4: 2,  # update_persist_task_status(context, task)
    0x00033c18: 1,  # find_message_pool_entry_by_id(id)
    0x00033c5c: 0,  # msg_queue_init()
    0x00034524: 1,  # confirm_message(id)
    0x0007c010: 1,  # default packet handler(state)
    0x0007ce60: 1,  # reset_esb_sync_state(reason)
    0x0007d230: 1,  # set_device_sync_timestamp(timestamp)
    0x0007dda4: 2,  # log_message(format, function, ...)
    0x00086c78: 3,  # memset(record + 4, 0, 18)
}


def _key_event_case(state, role=0, work_mode=0,
                    onboarding_active=0, sc_sync_active=0):
    """One bounded key worker dispatch followed by quiescent queue polls."""
    context = emu.SCRATCH + 0xa000
    standby = emu.SCRATCH + 0xc000
    screen = emu.SCRATCH + 0xc100
    onboarding = emu.SCRATCH + 0xc200
    auxiliary = emu.SCRATCH + 0xc300
    quick_note = emu.SCRATCH + 0xc400
    image = bytearray(0x1100)
    image[0] = int(role) & 0xff
    image[0xd5] = int(work_mode) & 0xff
    image[0xffc:0x1000] = standby.to_bytes(4, "little")
    image[0x100c:0x1010] = screen.to_bytes(4, "little")
    image[0x1014:0x1018] = onboarding.to_bytes(4, "little")
    image[0x101c:0x1020] = auxiliary.to_bytes(4, "little")
    image[0x1020:0x1024] = quick_note.to_bytes(4, "little")
    onboarding_image = bytearray(8)
    onboarding_image[0] = int(onboarding_active) & 0xff
    memory = [
        (context, bytes(image)),
        (standby, bytes(8)), (screen, bytes(8)),
        (onboarding, bytes(onboarding_image)),
        (auxiliary, bytes(8)), (quick_note, bytes(8)),
        (0x2000230c, bytes(4)), (0x20007554, bytes(4)),
        (0x20007b18, int(state).to_bytes(4, "little")),
        (0x20007b1c, bytes(16)),
        (0x20018d89, bytes(1)), (0x20018d95, bytes(1)),
        (0x20018d96, bytes((int(sc_sync_active) & 0xff,))),
        (0x20018d98, bytes(1)),
    ]
    # init, two singleton reads, and one successful queue poll enter exactly
    # one selected state arm.  Every following poll reports no event, bounding
    # the nonreturning worker in its quiescent loop.
    oracles = {0: {0: 0}, 1: {0: context}, 2: {0: context}, 3: {0: 0}}
    ordinal = 4
    for _ in range(64):
        oracles[ordinal] = {0: context}
        oracles[ordinal + 1] = {0: context}
        oracles[ordinal + 2] = {0: 1}
        ordinal += 3
    return ({0: context, 1: 0x11223344, 2: 0x55667788}, memory, oracles)


REVIEWED_ORACLE_CASES[("app", 0x0002955c)] = [
    _key_event_case(0),
    _key_event_case(1),
    _key_event_case(2, work_mode=7),
    _key_event_case(3, onboarding_active=1),
    _key_event_case(4, role=1, work_mode=6, sc_sync_active=1),
    _key_event_case(5),
    _key_event_case(6),
]
REVIEWED_TARGET_CALL_ARITIES[("app", 0x0002955c)] = {
    0x0002953c: 0,
    0x000167a8: 0,
    0x0007cb8a: 2,
    0x000276ec: 1,
}
REVIEWED_CALL_ARGUMENT_INDICES_BY_TARGET[("app", 0x0002955c)] = {
    # AAPCS aligns the signed 64-bit timeout in r2:r3; r1 is a hole.
    0x0007cb48: (0, 2, 3),
}


def _flash_ops_case(nonzero_count_ordinals=()):
    """Bound one complete semaphore wake and ordered three-queue drain.

    Oracle ordinals are the actual external-call order.  Starting every call
    at zero makes later worker iterations quiescent; selected count-query
    ordinals become one and force the corresponding handler/backedge.
    """
    oracles = {i: {0: 0} for i in range(96)}
    for ordinal in nonzero_count_ordinals:
        oracles[int(ordinal)] = {0: 1}
    return ({}, [(0x2000230c, bytes(4)), (0x20007554, bytes(4))], oracles)


REVIEWED_ORACLE_CASES[("app", 0x00023480)] = [
    _flash_ops_case(),
    # wait=0, audio-count=1, handler, audio-count=0
    _flash_ops_case((1,)),
    # wait=0, audio-count=0, quicknote-count=1, handler, count=0
    _flash_ops_case((2,)),
    # wait=0, audio=0, quicknote=0, settings-count=1, handler, count=0
    _flash_ops_case((3,)),
    # Two audio requests prove the first while-loop backedge.
    _flash_ops_case((1, 3)),
    # One request in every queue proves the fixed audio->quicknote->settings
    # drain priority and all three handler identities in one iteration.
    _flash_ops_case((1, 4, 7)),
]
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00023480)] = {
    0x0002f758: 0,
    0x0002f94c: 0,
    0x00024678: 0,
    0x00024684: 0,
    0x00023ef8: 0,
    0x00023f04: 0,
}
REVIEWED_CALL_ARGUMENT_INDICES_BY_TARGET[("app", 0x00023480)] = {
    # k_sem_take-style wrapper uses r0 and aligned timeout r2:r3; r1 is the
    # AAPCS hole and is not read by the complete callee.
    0x00072908: (0, 2, 3),
}


def _proxy_thread_case(opcode=None, subtype=0, value=0, length=0,
                       pending_response=0):
    """Concrete proxy context and one complete 24-byte queue record."""
    context = emu.SCRATCH + 0xc000
    image = bytearray(0x1060)
    image[1] = 0
    image[0x788:0x78c] = (0x00080001).to_bytes(4, "little")
    image[0x105c] = 0 if opcode is None else 0x80
    memory = [
        (context, bytes(image)),
        (0x2000230c, bytes(4)),
        (0x20007554, bytes(4)),
        (0x2001d431, bytes((int(pending_response) & 0xff,))),
        (0x2001d432, bytes(0x20)),
        (0x2000ff04, bytes(4)),
        (0x2001d262, b"\0"),
        (0x2001d263, b"\0"),
        (0x2001d34a, b"\0"),
        (0x2001d34b, bytes(0xe6)),
        (0x20007b38, bytes(4)),
    ]
    oracles = {i: {0: 0} for i in range(96)}
    writes = {}
    if opcode is not None:
        record = bytearray(24)
        record[0] = int(opcode) & 0xff
        record[2:4] = int(length).to_bytes(2, "little")
        record[4] = int(subtype) & 0xff
        record[5] = int(value) & 0xff
        # Initial stack clear is ordinal zero, per-iteration clear ordinal one,
        # and k_msgq_get is ordinal two with its destination in r1.
        writes[2] = [(1, 0, bytes(record), 0x00072240)]
        oracles[2] = {0: 0}
        if opcode in (4, 5, 6):
            # get_device_info follows the queue receive for these compact
            # forwarding commands; sync_to_slave then succeeds immediately.
            oracles[3] = {0: context}
            oracles[4] = {0: 0}
    return ({0: context}, memory, oracles, writes)


REVIEWED_ORACLE_CASES[("app", 0x00047c48)] = [
    _proxy_thread_case(None),
    _proxy_thread_case(0, subtype=0x41, length=3),
    _proxy_thread_case(0, subtype=0x41, length=0x21),
    _proxy_thread_case(1, pending_response=0),
    _proxy_thread_case(1, pending_response=1),
    _proxy_thread_case(2, subtype=1, value=2),
    _proxy_thread_case(3, subtype=0, value=1),
    _proxy_thread_case(4, subtype=0x22),
    _proxy_thread_case(5, subtype=0x23),
    _proxy_thread_case(6, subtype=0x24),
    _proxy_thread_case(7),
    _proxy_thread_case(8),
]
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00047c48)] = {
    0x000167a8: 0,
    0x00023af0: 1,
    0x00023bfc: 1,
    0x00023eec: 0,
    0x0002f910: 1,
    0x0002f928: 0,
    0x00047bf8: 2,
    0x00049a28: 1,
    0x0004a4d0: 1,
    0x00072240: 4,
    0x000745c8: 0,
    0x00074844: 2,
    0x0008638c: 1,
    0x00086c04: 3,
    0x00086c1e: 4,
    0x00086c78: 3,
    0x0001694c: 1,
    0x00026f74: 4,
    0x00080000: 2,
}
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x00047c48)] = [
    # The clear and queue-receive calls are output boundaries: their incoming
    # bytes are not consumed, so normalize only the compiler-owned address.
    ("proxy-queue-output", -64, -64, 24, (), None,
     (0x00086c78, 0x00072240)),
    # Once received, copy consumers observe the complete populated record.
    ("proxy-queue-record", -64, -64, 24, None, None,
     (0x00086c04,)),
    # The timestamp helper consumes the complete initialized two-word result.
    # GCC reuses part of the now-dead receive-record slot for this local.
    ("proxy-timestamp-result", -72, -72, 8, None, None,
     (0x0004a4d0,)),
    # Opcodes four and five publish the low two initialized bytes of the same
    # local through sync_to_slave; opcode six uses its adjacent byte packet.
    ("proxy-forward-packet-4-5", -72, -72, 2, None, None,
     (0x00026f74,)),
    ("proxy-forward-packet-6", -76, -76, 2, None, None,
     (0x00026f74,)),
]


def _wordwrap_text_case(characters=(), classification=None,
                        resource_status=None, display_state=0,
                        callback=0, param10=0, param12=0,
                        level=0, sink=0):
    """One bounded UTF-16 layout family with explicit decoder ownership."""
    text = emu.SCRATCH + 0x2600
    device = emu.SCRATCH + 0x3000
    glyph = emu.SCRATCH + 0x3800
    glyph_bytes = bytes((0xa5, 0x5a, 0x3c, 0xc3)) + bytes(60)
    encoded = b"".join((int(ch) & 0xffff).to_bytes(2, "little")
                       for ch in characters) + b"\0\0"
    memory = [
        (text, encoded),
        (device, bytes(0x1000)),
        (glyph, glyph_bytes),
        (0x2000230c, int(level).to_bytes(4, "little", signed=True)),
        (0x20007554, int(sink).to_bytes(4, "little")),
        (0x200034f6, b"\xf0"),
        (0x2000a034, (emu.SCRATCH + 0x5000).to_bytes(4, "little")),
    ]
    oracles = {0: {0: text}}
    writes = {0: [(1, 0, len(characters).to_bytes(2, "little"),
                   0x000478d8)]}
    if callback:
        oracles[1] = {0: 0x2468ace0}
    elif not param10 and not param12:
        ordinal = 1
        oracles[ordinal] = {0: int(display_state)}
        ordinal += 1
        if int(display_state) & 2:
            # clear_framebuffer_region is a void boundary.
            oracles[ordinal] = {0: 0}
            ordinal += 1
        for ch in characters:
            result = (classification if classification is not None else 1)
            oracles[ordinal] = {0: int(result) & 0xffffffff}
            ordinal += 1
            if result == 0:
                status = int(resource_status if resource_status is not None
                             else -1)
                oracles[ordinal] = {0: status & 0xffffffff}
                writes[ordinal] = [
                    (2, 0, (8).to_bytes(4, "little"), 0x0004588c),
                    (3, 0, (4).to_bytes(4, "little"), 0x0004588c),
                    (4, 0, glyph.to_bytes(4, "little"), 0x0004588c),
                ]
                ordinal += 1
                if status >= 0:
                    # copy, spacing, draw, and the post-draw spacing query.
                    oracles[ordinal] = {0: 0}
                    writes[ordinal] = [
                        (0, 0, glyph_bytes[:16], 0x00086c1e),
                    ]
                    ordinal += 1
                    oracles[ordinal] = {0: 1}
                    ordinal += 1
                    oracles[ordinal] = {0: 0}
                    ordinal += 1
                    oracles[ordinal] = {0: 1}
                    ordinal += 1
        oracles[ordinal] = {0: int(display_state)}
        ordinal += 1
        if int(display_state) & 2:
            oracles[ordinal] = {0: device}
            oracles[ordinal + 1] = {0: device}
            oracles[ordinal + 2] = {0: 0}
    return ({0: 0, 1: emu.SCRATCH + 0x2500, 2: 0, 3: 10},
            memory, oracles, writes)


_WORDWRAP_CASE_SPECS = [
    # param10, callback, and param12 gates after the mandatory decoder call.
    ((), None, None, 0, 0, 0),
    ((), None, None, 1, 0, 0),
    ((), None, None, 1, 0x00080001, 0),
    ((), None, None, 0, 0, 1),
    # Empty/no-refresh and empty/clear-refresh production display modes.
    ((), None, None, 0, 0, 0),
    ((), None, None, 0, 0, 0),
    # Skipped classifier, newline, carriage return, and failed glyph lookup.
    ((0x41,), 1, None, 0, 0, 0),
    ((0x0a,), -1, None, 0, 0, 0),
    ((0x0d,), -1, None, 0, 0, 0),
    ((0x41,), 0, -1, 0, 0, 0),
]
REVIEWED_ORACLE_CASES[("app", 0x000451e0)] = [
    _wordwrap_text_case(chars, classification, resource_status,
                        display_state=(2 if index == 5 else 0),
                        param10=param10, callback=callback, param12=param12)
    for index, (chars, classification, resource_status,
                param10, callback, param12) in enumerate(_WORDWRAP_CASE_SPECS)
]
REVIEWED_ORACLE_CASES[("app", 0x000451e0)] += [
    _wordwrap_text_case((0x41,), 0, 0),
    _wordwrap_text_case((0x41,), 0, 0, display_state=2),
    _wordwrap_text_case((0x41,), 0, -1, level=2, sink=0),
    _wordwrap_text_case((0x41,), 0, -1, level=2, sink=1),
    _wordwrap_text_case((0x41,), 0, 0),
    # Narrow first glyph forces a line transition; the comma then enters the
    # punctuation table and bounded end-of-text lookahead arm.
    _wordwrap_text_case((0x41, 0x2c), 0, 0),
]
REVIEWED_PAIRED_STACK_INITIAL_WORDS[("app", 0x000451e0)] = [
    (0, 0, tuple(20 for _ in _WORDWRAP_CASE_SPECS)),      # top
    (4, 4, tuple([110] * 14 + [15, 15])),                  # right
    (8, 8, tuple([200] * 16)),                             # bottom
    (12, 12, tuple([3] * 16)),                             # max lines
    (16, 16, tuple([0] * 10 + [0, 1, 0, 0, 0, 0])),       # mask count
    (20, 20, tuple([spec[3] for spec in _WORDWRAP_CASE_SPECS] + [0] * 6)),
    (24, 24, tuple([spec[4] for spec in _WORDWRAP_CASE_SPECS] + [0] * 6)),
    (28, 28, tuple([spec[5] for spec in _WORDWRAP_CASE_SPECS] + [0] * 6)),
]
REVIEWED_TARGET_CALL_ARITIES[("app", 0x000451e0)] = {
    0x000167a8: 0,
    0x00019c70: 0,
    0x000431a8: 0,
    0x00043e58: 2,
    0x0004588c: 6,
    0x000471cc: 6,
    0x00047260: 6,
    0x000478d8: 2,
    0x0007d53a: 6,
    0x0007d860: 1,
    0x00086c1e: 4,
    0x00080000: 5,
}
REVIEWED_CALL_ARITIES_BY_FORMAT[("app", 0x000451e0)] = {
    (0x0007dda4, 0x000aaa58): 3,
    (0x0007dda4, 0x000aabe8): 2,
    (0x0007dda4, 0x000aac1e): 2,
    (0x0007dda4, 0x000aaa7f): 2,
}
REVIEWED_PAIRED_STACK_OBJECTS[("app", 0x000451e0)] = [
    # UTF decoder owns this two-byte output count.  Incoming bytes are not
    # consumed; the oracle's exact two-byte write and every later load remain
    # compared.  Readable GCC saves 24 fewer frame bytes than the firmware.
    ("wordwrap-decoded-length", -0x302, -0x2ea, 2, (), None,
     (0x000478d8,)),
    # resource_manger_get fills three independent words.  Their incoming
    # bytes are irrelevant, while exact oracle writes and later loads remain
    # fully differential.
    ("wordwrap-glyph-width", -0x2fc, -0x2e4, 4, (), None,
     (0x0004588c,)),
    ("wordwrap-glyph-height", -0x2f8, -0x2e0, 4, (), None,
     (0x0004588c,)),
    ("wordwrap-glyph-bitmap", -0x300, -0x2e8, 4, (), None,
     (0x0004588c,)),
    # The secure copy fills the first width/2*height bytes; drawing consumes
    # the complete compiler-owned canvas identity and therefore still checks
    # all initialized content rather than merely normalizing its address.
    ("wordwrap-glyph-canvas-output", -0x2cc, -0x2d0, 680, (), None,
     (0x00086c1e,)),
    ("wordwrap-glyph-canvas", -0x2cc, -0x2d0, 680, None, None,
     (0x0007d53a,)),
]


def _projector_pixel_transfer_case(byte_count, first_row=0x120,
                                   x=0x2345):
    """Bound one exact chunk family without weakening the signed ABI.

    The production loop is linear in byte_count.  Generic 32-bit fuzz values
    can request tens of thousands of SPI chunks and made the historical sweep
    time out; these cases retain both signed boundaries and three backedges,
    including the 16-bit row wrap performed after every full chunk.
    """
    return ({0: x, 1: first_row, 2: 0x89abcdef,
             3: byte_count & 0xffffffff}, [], {})


REVIEWED_ORACLE_CASES[("app", 0x0007d70a)] = [
    _projector_pixel_transfer_case(-1, first_row=0x1ffff, x=0x12345),
    _projector_pixel_transfer_case(0),
    _projector_pixel_transfer_case(0xefff),
    _projector_pixel_transfer_case(0xf000),
    _projector_pixel_transfer_case(0xf001),
    _projector_pixel_transfer_case(0x1e000),
    _projector_pixel_transfer_case(0x1e001),
    _projector_pixel_transfer_case(0x3c001, first_row=0xff80),
]


def _rle_byte_pair_case(runs, encoded_length=None):
    """One complete navigation RLE stream with exact expanded output writes."""
    encoded = emu.SCRATCH + 0x2400
    decoded = emu.SCRATCH + 0x2800
    stream = b"".join(bytes((count, value)) for count, value in runs)
    if encoded_length is None:
        encoded_length = len(stream)
    writes = {
        ordinal: [(0, 0, bytes((value,)) * count, 0x00086c78)]
        for ordinal, (count, value) in enumerate(runs)
    }
    return (
        {0: encoded, 1: encoded_length, 2: decoded},
        [(encoded, stream + bytes(2)), (decoded, b"\xa5" * 0x400)],
        {}, writes,
    )


REVIEWED_ORACLE_CASES[("app", 0x0007da70)] = [
    _rle_byte_pair_case([], encoded_length=0),
    _rle_byte_pair_case([(3, 0x5a)]),
    _rle_byte_pair_case([(0, 0x11), (2, 0x22)]),
    _rle_byte_pair_case([(1, 0x10), (4, 0x20), (2, 0x30), (7, 0x40)]),
    _rle_byte_pair_case([(0xff, 0x6d)]),
    # The loop owns this behavior even though production encoders emit pairs:
    # offsets 0 and 2 are both below three, so the second value at offset 3 is
    # consumed as the final run.
    _rle_byte_pair_case([(2, 0x31), (3, 0x42)], encoded_length=3),
]


def _net_controller_participants_init_case(initialized, active=False,
                                           process_results=(0,),
                                           start_result=0):
    """One finite linker-table initialization and pending-event drain."""
    if initialized:
        return ({}, [(0x21004fad, b"\x01")], {})

    ops = emu.SCRATCH + 0x1000
    state = emu.SCRATCH + 0x1100
    callback = 0x01040001
    entry_image = bytearray(16)
    entry_image[0:4] = ops.to_bytes(4, "little")
    entry_image[4:8] = state.to_bytes(4, "little")
    ops_image = bytearray(12)
    ops_image[8:12] = callback.to_bytes(4, "little")
    state_image = bytearray(8)
    state_image[5] = int(active)
    memory = [
        (0x21004fad, b"\x00"),
        (0x0103c0ec, bytes(entry_image)),
        (ops, bytes(ops_image)),
        (state, bytes(state_image)),
    ]

    oracles = {0: {0: int(start_result)}}
    process_ordinal = 2 if active else 1
    for result in process_results:
        oracles[process_ordinal] = {0: int(result)}
        process_ordinal += 1
    return ({}, memory, oracles)


# One already-initialized fast path, inactive/active participant forms, an
# ignored nonzero start result, and bounded one-/multi-event drain loops.  The
# installed callback is a unary participant initializer; its higher registers
# are conversion/table-walk scratch and are excluded only at this exact target.
REVIEWED_ORACLE_CASES[("net", 0x0102e000)] = [
    _net_controller_participants_init_case(True),
    _net_controller_participants_init_case(False, process_results=(0,)),
    _net_controller_participants_init_case(False, active=True,
                                           process_results=(0,)),
    _net_controller_participants_init_case(False, process_results=(2, 1, 0)),
    _net_controller_participants_init_case(False, active=True,
                                           process_results=(1, 0),
                                           start_result=0x55aa),
]
REVIEWED_TARGET_CALL_ARITIES[("net", 0x0102e000)] = {
    0x01040000: 1,
}


def _net_controller_supervisor_case(retry_mask=0, retry_results=(),
                                    event_results=(0,), wait_source_value=0,
                                    pending_count=0, drained_callback=True):
    """Bound the supervisor's retry, event-drain, callback, and wait cycle."""
    ops = emu.SCRATCH + 0x1000
    wait_source = emu.SCRATCH + 0x1200
    callback = 0x01040001 if drained_callback else 0
    entry_image = bytearray(16)
    entry_image[0:4] = ops.to_bytes(4, "little")
    ops_image = bytearray(28)
    ops_image[24:28] = callback.to_bytes(4, "little")
    wait_source_image = bytearray(12)
    wait_source_image[8:12] = int(wait_source_value).to_bytes(4, "little")
    memory = [
        (0x0103c0ec, bytes(entry_image)),
        (ops, bytes(ops_image)),
        (wait_source, bytes(wait_source_image)),
        (0x21004668, int(pending_count).to_bytes(4, "little", signed=True)),
        (0x21004660, bytes(4)),
        (0x21000944, bytes(0x20)),
    ]

    # Startup and wait-source lookup are always the first two calls.
    oracles = {0: {0: int(retry_mask)}, 1: {0: wait_source}}
    ordinal = 2
    if wait_source_value != 0 and pending_count > 9:
        ordinal += 1  # controller_wait_prepare; its return is ignored

    retry_values = iter(retry_results)
    event_values = iter(event_results)
    current_retry = int(retry_mask)
    previous_event = 0
    while ordinal < 28:
        if current_retry != 0:
            current_retry = int(next(retry_values, 0))
            oracles[ordinal] = {0: current_retry}
            ordinal += 1

        event = int(next(event_values, 0))
        oracles[ordinal] = {0: event}
        ordinal += 1
        if event == 0:
            if previous_event != 0 and drained_callback:
                ordinal += 1  # participant on_events_drained callback
            ordinal += 1      # controller_wait; return is ignored
        previous_event = event

    return ({}, memory, oracles)


# Six production-shaped supervisor families.  Prefix comparison is target-owned
# because this function is a deliberate noreturn service loop; sixteen ordered
# events cover startup publication plus retry, event, drained-callback and wait
# cycles without depending on instruction counts.
REVIEWED_PREFIX_PROOFS[("net", 0x0102e064)] = 16
REVIEWED_ORACLE_CASES[("net", 0x0102e064)] = [
    _net_controller_supervisor_case(),
    _net_controller_supervisor_case(wait_source_value=0x1234,
                                    pending_count=10),
    _net_controller_supervisor_case(retry_mask=1, retry_results=(0,)),
    _net_controller_supervisor_case(retry_mask=3, retry_results=(2, 0)),
    _net_controller_supervisor_case(event_results=(7, 0),
                                    drained_callback=True),
    _net_controller_supervisor_case(event_results=(7, 0),
                                    drained_callback=False),
]
REVIEWED_TARGET_CALL_ARITIES[("net", 0x0102e064)] = {
    0x01040000: 2,
}
REVIEWED_CALL_ARGUMENT_INDICES_BY_TARGET[("net", 0x0102e064)] = {
    # FUN_0103689c consumes the wait object and timeout pair.  Its physical r1
    # slot is never read (confirmed by the complete callee disassembly).
    0x0103689c: (0, 2, 3),
}


def _ipc_static_vrings_open_case(stage):
    """Complete one-device fixture for ipc_rpmsg_static_vrings_open.

    The generic allocator fills the atomic state with random nonzero data and
    therefore proves only -EALREADY.  These cases own every externally visible
    initialization boundary from descriptor sizing through READY/INITED state
    publication.
    """
    owner = emu.SCRATCH + 0x1000
    config = emu.SCRATCH + 0x2000
    mailbox = emu.SCRATCH + 0x3000
    mailbox_api = emu.SCRATCH + 0x3100
    data = emu.SCRATCH + 0x4000
    register_callback = 0x01040001
    set_enabled = 0x01040005

    owner_image = bytearray(0x14)
    owner_image[4:8] = config.to_bytes(4, "little")
    owner_image[0x10:0x14] = data.to_bytes(4, "little")
    config_image = bytearray(0x2c)
    config_image[0:4] = (1).to_bytes(4, "little")
    config_image[4:8] = (emu.SCRATCH + 0x7000).to_bytes(4, "little")
    config_image[8:12] = (104).to_bytes(4, "little")
    config_image[0x14:0x18] = mailbox.to_bytes(4, "little")
    config_image[0x18:0x1c] = (7).to_bytes(4, "little")
    config_image[0x1c:0x20] = (1).to_bytes(4, "little")
    config_image[0x20:0x24] = (3).to_bytes(4, "little")
    config_image[0x24:0x28] = (1).to_bytes(4, "little")
    config_image[0x28:0x2c] = (32).to_bytes(4, "little")
    mailbox_image = bytearray(12)
    mailbox_image[8:12] = mailbox_api.to_bytes(4, "little")
    api_image = bytearray(20)
    if stage != "missing_register":
        api_image[4:8] = register_callback.to_bytes(4, "little")
    if stage != "missing_enable":
        api_image[0x10:0x14] = set_enabled.to_bytes(4, "little")
    data_image = bytearray(0x384)
    data_image[0x37c:0x380] = (1 if stage == "busy" else 0).to_bytes(4, "little")
    data_image[0x208:0x20c] = (emu.SCRATCH + 0x7200).to_bytes(4, "little")
    data_image[0x210:0x214] = (0x800).to_bytes(4, "little")
    data_image[0x268:0x26c] = (emu.SCRATCH + 0x7300).to_bytes(4, "little")
    data_image[0x378:0x37c] = (1).to_bytes(4, "little")

    memory = [(owner, bytes(owner_image)), (config, bytes(config_image)),
              (mailbox, bytes(mailbox_image)), (mailbox_api, bytes(api_image)),
              (data, bytes(data_image))]
    if stage == "busy":
        return ({0: owner}, memory, {})

    # descriptor 1 fits, descriptor 2 does not; the rounded answer is one.
    oracles = {0: {0: 50}, 1: {0: 120}, 2: {0: 50}, 3: {0: 0}}
    if stage == "no_memory":
        config_image[8:12] = (4).to_bytes(4, "little")
        memory[1] = (config, bytes(config_image))
        return ({0: owner}, memory, {0: {0: 8}})
    if stage == "vrings_init_error":
        oracles[3] = {0: -5}
        return ({0: owner}, memory, oracles)

    # Queue setup occupies ordinals 4..6.  Mailbox callbacks then begin at 7.
    if stage == "missing_register":
        return ({0: owner}, memory, oracles)
    if stage == "register_error":
        oracles[7] = {0: -7}
        return ({0: owner}, memory, oracles)
    oracles[7] = {0: 0}
    if stage == "missing_enable":
        return ({0: owner}, memory, oracles)
    if stage == "enable_error":
        oracles[8] = {0: -9}
        return ({0: owner}, memory, oracles)
    oracles[8] = {0: 0}
    if stage == "rpmsg_init_error":
        oracles[9] = {0: -11}
        return ({0: owner}, memory, oracles)
    oracles[9] = {0: 0}
    oracles[10] = {0: -1 if stage == "buffer_size_error" else 256}
    return ({0: owner}, memory, oracles)


REVIEWED_ORACLE_CASES[("net", 0x0102d708)] = [
    _ipc_static_vrings_open_case("busy"),
    _ipc_static_vrings_open_case("no_memory"),
    _ipc_static_vrings_open_case("vrings_init_error"),
    _ipc_static_vrings_open_case("missing_register"),
    _ipc_static_vrings_open_case("register_error"),
    _ipc_static_vrings_open_case("missing_enable"),
    _ipc_static_vrings_open_case("enable_error"),
    _ipc_static_vrings_open_case("rpmsg_init_error"),
    _ipc_static_vrings_open_case("buffer_size_error"),
    _ipc_static_vrings_open_case("success"),
]
REVIEWED_NPTR_COUNTS[("net", 0x0102d708)] = 1
REVIEWED_TARGET_CALL_ARITIES[("net", 0x0102d708)] = {
    0x0103a056: 2, 0x0102db30: 2, 0x01036cb8: 1,
    0x01036ce4: 5, 0x01036bec: 2, 0x01040000: 4,
    0x01040004: 3, 0x0102dac0: 8, 0x010357ec: 1,
    0x01039fb6: 2,
}
REVIEWED_TARGET_CALL_STACK_ARITIES[("net", 0x0102d708)] = {
    0x01036ce4: 1,
    0x0102dac0: 4,
}
REVIEWED_CALL_ARGUMENT_INDICES_BY_TARGET[("net", 0x0102d708)] = {
    # ipc_static_vrings_shm_size is a compiler-outlined static inline helper.
    # Its complete body modifies r0/r3 only, so the original deliberately
    # carries buffer_size in caller-clobbered r1 across loop iterations.  The
    # separately compiled readable TU reloads the same semantic value; compare
    # the changing descriptor-count argument and ordinal-controlled result.
    0x0103a056: (0,),
}


def _sdc_llcp_rx_case(opcode, receive_state, response_type=0,
                      response_flags=0, cleanup=False,
                      transition_result=0, handler_result=9):
    """One complete decoded LL control PDU and controller-state fixture."""
    pdu = emu.SCRATCH + 0x1000
    state = bytearray(0xba)
    state[0x7c] = int(cleanup)
    state[0xb9] = receive_state
    decoded = bytearray(0x2c)
    decoded[0] = response_type
    decoded[1] = response_flags
    oracles = {0: {0: 3}, 2: {0: transition_result,
                               1: (transition_result << 4) & 0xffffffff}}
    if opcode != 7:
        if receive_state == 1 and (opcode == 6 or opcode <= 2):
            oracles[3] = {0: handler_result}
    writes = {1: [(1, 0, bytes(decoded), 0x0101a070)]}
    return ({0: pdu},
            [(pdu, bytes((opcode & 0x0f,))),
             (0x2100001c, b"\x00"),
             # The controller object crosses the emulator's 0x21001000 page
             # boundary; seed each mapped page independently.
             (0x21000f90, bytes(state[:0x70])),
             (0x21001000, bytes(state[0x70:]))],
            oracles, writes)


REVIEWED_ORACLE_CASES[("net", 0x01018690)] = [
    # Ordinary admitted opcode, with and without the cleanup tail.
    _sdc_llcp_rx_case(0, 1, cleanup=False, handler_result=9),
    _sdc_llcp_rx_case(6, 1, cleanup=True, handler_result=-4),
    # Unsupported and invalid receive-state paths.
    _sdc_llcp_rx_case(4, 2),
    _sdc_llcp_rx_case(3, 3),
    # LL_UNKNOWN_RSP preprocessing and each shared continuation class.
    _sdc_llcp_rx_case(7, 1, response_type=2,
                      response_flags=0xff, transition_result=2),
    _sdc_llcp_rx_case(7, 2, response_type=1,
                      response_flags=0xff, transition_result=3),
    _sdc_llcp_rx_case(7, 3, response_type=1,
                      response_flags=0xff, transition_result=4),
    _sdc_llcp_rx_case(7, 4, response_type=0,
                      response_flags=0x10, transition_result=5),
    _sdc_llcp_rx_case(7, 9, response_type=0,
                      response_flags=0, transition_result=6),
]
REVIEWED_NPTR_COUNTS[("net", 0x01018690)] = 1
REVIEWED_TARGET_CALL_ARITIES[("net", 0x01018690)] = {
    0x0100d760: 0, 0x0101a070: 2, 0x0101746c: 3,
    0x010168e4: 2, 0x010183e0: 1, 0x01020500: 0,
    0x010208b0: 0, 0x0101fca8: 0, 0x01008d00: 2,
    # Shared tails are ownership boundaries, not ordinary C callees.  Their
    # physical scratch-register contract is deliberately excluded here; all
    # writes and calls before the transfer remain strict.
    0x01018f1a: 0, 0x01018f22: 0, 0x01018fac: 0,
}

# Production-shaped fixtures for each of the planner's four timing modes.  The
# generic pointer seeder almost always chooses an invalid coefficient index and
# therefore proves only the 0x571 assertion tail.
def _sdc_conn_event_timing_case(mode, initial_attempt=1,
                                allow_reschedule=1):
    context = emu.SCRATCH + 0x5000
    state = bytearray(0x3d0)
    state[0x14:0x18] = (10000).to_bytes(4, "little")
    state[0x24:0x28] = (500).to_bytes(4, "little")
    state[0x28:0x2a] = (10).to_bytes(2, "little")
    state[0x6f] = 1
    state[0xbc:0xbe] = (10).to_bytes(2, "little")
    state[0x2d8] = 0
    state[0x2f6:0x2f8] = (1).to_bytes(2, "little")
    state[0x31c] = mode
    state[0x318:0x31c] = (0).to_bytes(4, "little")
    state[0x324:0x328] = (9000).to_bytes(4, "little")
    state[0x358:0x35c] = (0x2000).to_bytes(4, "little")
    state[0x35c:0x360] = (0).to_bytes(4, "little")
    state[0x360:0x362] = (10).to_bytes(2, "little")
    state[0x364] = 1
    state[0x368:0x36c] = (0).to_bytes(4, "little")
    state[0x36c:0x370] = (500).to_bytes(4, "little")

    # Every helper result is selected to keep arithmetic bounded while the
    # complete writes/call order remain differential.  The initial-mode MPSL
    # snapshot owns an 8-byte timestamp and adjacent 4-byte remainder.
    oracles = {0: {0: 0}}
    writes = {}
    if mode == 0:
        values = (0, 100, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 1)
        for ordinal, value in enumerate(values, 1):
            oracles[ordinal] = {0: value}
        writes[4] = [
            (0, 0, b"\x00" * 8, 0x010209c8),
            (1, 0, b"\x00" * 4, 0x010209c8),
        ]
    elif mode == 1:
        # base airtime, tail airtime, fixed time, guard, admission
        for ordinal, value in enumerate((0, 0, 0, 0, 1), 1):
            oracles[ordinal] = {0: value}
    elif mode == 2:
        # two scales, PHY timing pair(s), fixed time, guard, admission
        for ordinal, value in enumerate(
                (100, 1000, 0, 0, 0, 0, 0, 0, 1), 1):
            oracles[ordinal] = {0: value}
    else:
        # PHY timing pair, fixed time, guard, admission
        for ordinal, value in enumerate((0, 0, 0, 0, 1), 1):
            oracles[ordinal] = {0: value}
    return ({0: context, 1: 10, 2: initial_attempt,
             3: allow_reschedule},
            [(context, bytes(state)),
             (0x21000f54, b"\x00" * 8)],
            oracles, writes)


REVIEWED_ORACLE_CASES[("net", 0x01012f18)] = [
    _sdc_conn_event_timing_case(0),
    _sdc_conn_event_timing_case(1),
    _sdc_conn_event_timing_case(2),
    _sdc_conn_event_timing_case(3),
    # A distinct retry input proves the initial-attempt result byte.
    _sdc_conn_event_timing_case(1, initial_attempt=0),
]
REVIEWED_NPTR_COUNTS[("net", 0x01012f18)] = 1
REVIEWED_PAIRED_STACK_INITIAL_WORDS[("net", 0x01012f18)] = [
    (0, 0, (0, 0, 0, 0, 0)),  # optional fifth argument, event_skip_out
]
REVIEWED_PAIRED_STACK_OBJECTS[("net", 0x01012f18)] = [
    ("mpsl-window-timestamp", -48, -44, 8, None, (4,),
     (0x010209c8,)),
    ("mpsl-window-remainder", -52, -48, 4, None, (4,),
     (0x010209c8,)),
]


# The connection-event timing planner is an exact SDC archive match, but its
# large body leaves unrelated caller-clobbered registers live at many opaque
# helper boundaries.  Compare each helper's reviewed ABI arguments only.
REVIEWED_TARGET_CALL_ARITIES[("net", 0x01012f18)] = {
    0x01029638: 0,  # timing-compensation thunk
    0x01012c08: 0,  # no-return timing fault preamble
    0x01008d00: 2,  # controller assertion
    0x0101618c: 1,
    0x010247cc: 0,
    0x0100d58c: 2,
    0x01024678: 2,
    0x010209c8: 2,
    0x010243c0: 5,
    0x010209f0: 1,
    0x0100f48c: 2,
    0x010209e0: 1,
    0x0100d6e8: 4,
    0x0100f0fc: 1,
    0x01016160: 0,
    0x0100d4d0: 2,
    0x0100f63c: 0,
    0x010231c8: 2,
}
REVIEWED_PAIRED_STACK_OBJECTS[("net", 0x01018690)] = [
    ("decoded-ll-control-pdu", -56, -60, 0x2c, None, (1, 2, 3),
     (0x0101a070, 0x0101746c, 0x010168e4)),
]


# The fatal path has no ABI inputs: varied incoming scratch registers prove
# that only the fixed diagnostic record and reboot mode are observable.  The
# final sys_reboot call is an explicit terminal boundary, not a timed prefix.
REVIEWED_ORACLE_CASES[("net", 0x01031820)] = [
    ({}, [], {}),
    ({0: 0, 1: 1, 2: 2, 3: 3}, [], {}),
    ({0: 0xffffffff, 1: 0x80000000,
      2: 0x13579bdf, 3: 0x2468ace0}, [], {}),
]
REVIEWED_TARGET_CALL_ARITIES[("net", 0x01031820)] = {
    0x0102e000: 0,
    0x0102e284: 4,
    0x0102f4ec: 1,
}
REVIEWED_PAIRED_STACK_OBJECTS[("net", 0x01031820)] = [
    # Both translations place the complete two-word record at entry-SP-16;
    # compare its identity and all eight bytes at the logger boundary.
    ("controller-reset-diagnostic", -16, -16, 8, None, (1,),
     (0x0102e284,)),
]
REVIEWED_NPTR_COUNTS[("net", 0x01031820)] = 0


def _net_radio_operation_setup_case(operation_mode, return_finish_status,
                                    channel_result=0,
                                    finish_result=None):
    """One complete TBB mode/channel/finalizer path for FUN_01016430."""
    state = bytearray(0x200)
    lookup = bytearray(0x100)
    selector = 0x31
    slot = 7
    mapped_value = 0xa6
    state[0x7a] = selector
    state[0x98] = slot
    state[0xbd + slot] = int(operation_mode) & 0xff
    lookup[selector] = mapped_value

    dynamic_channel = operation_mode in (1, 4, 8)
    oracles = {}
    if dynamic_channel:
        # latch_mapped_radio_value is call zero; channel query is call one.
        oracles[1] = {0: int(channel_result) & 0xffffffff}
    if finish_result is not None:
        finalizer_ordinal = 4 if dynamic_channel else 3
        oracles[finalizer_ordinal] = {0: int(finish_result) & 0xffffffff}

    return (
        {0: int(return_finish_status), 1: 0x20014000},
        # The net state begins 0x70 bytes before a Unicorn page boundary;
        # split the identical image so fixture setup maps both RAM pages.
        [(0x21000f90, bytes(state[:0x70])),
         (0x21001000, bytes(state[0x70:])),
         (0x0103c24c, bytes(lookup))],
        oracles,
    )


# Every TBB class, both finalizers, the unsigned channel clamp boundaries, and
# zero/nonzero status normalization are finite and explicitly represented.
REVIEWED_ORACLE_CASES[("net", 0x01016430)] = [
    _net_radio_operation_setup_case(1, 0, channel_result=0),
    _net_radio_operation_setup_case(1, 1, channel_result=0x3f,
                                    finish_result=0),
    _net_radio_operation_setup_case(4, 1, channel_result=0x40,
                                    finish_result=7),
    _net_radio_operation_setup_case(8, 1, channel_result=0x41,
                                    finish_result=0xffffffff),
    _net_radio_operation_setup_case(8, 0, channel_result=0xff),
    _net_radio_operation_setup_case(2, 0),
    _net_radio_operation_setup_case(2, 1, finish_result=0),
    _net_radio_operation_setup_case(2, 1, finish_result=0x80000000),
    _net_radio_operation_setup_case(0, 0),
    _net_radio_operation_setup_case(3, 1),
    _net_radio_operation_setup_case(9, 0),
]
REVIEWED_TARGET_CALL_ARITIES[("net", 0x01016430)] = {
    0x01008d00: 2,
    0x0100a5b4: 0,
    0x010202fc: 2,
    0x010204f4: 1,
    0x01020764: 1,
    0x01021108: 2,
    0x010212ec: 2,
}
REVIEWED_NPTR_COUNTS[("net", 0x01016430)] = 0


def _net_timing_record_case(state_mode, initialize_state, update_state,
                            controller_mode, oracles, timeline_unit=7,
                            alternate_unit=11, budget=0x1234,
                            align=None):
    """One finite state-machine path through FUN_0101b7e4."""
    output = emu.SCRATCH + 0x5000
    context = emu.SCRATCH + 0x6000
    output_image = bytearray(b"\xa5" * 24)
    context_image = bytearray(0x320)
    table = bytearray(0x200)

    context_image[0xc5] = int(controller_mode) & 0xff
    context_image[0x300] = int(state_mode) & 0xff
    context_image[0x6e] = 2
    context_image[0x6f] = 0x0c
    context_image[0x14:0x18] = int(timeline_unit).to_bytes(4, "little")
    context_image[0x308:0x30c] = int(alternate_unit).to_bytes(4, "little")
    context_image[0x2d8:0x2dc] = (0x10203040).to_bytes(4, "little")
    context_image[0x2dc:0x2e0] = (0x50607080).to_bytes(4, "little")
    context_image[0x2fc:0x2fe] = (int(budget) & 0xffff).to_bytes(2, "little")
    table[4:6] = (100).to_bytes(2, "little")
    if align is not None:
        previous, current, quantum = align
        context_image[0x74:0x78] = (1).to_bytes(4, "little")
        context_image[0x78:0x7a] = int(quantum).to_bytes(2, "little")
        context_image[0xbc:0xbe] = int(current).to_bytes(2, "little")
        context_image[0xf2:0xf4] = int(previous).to_bytes(2, "little")

    complete_oracles = {0: {0: 0x12345678}}
    complete_oracles.update({int(k): {0: int(v) & 0xffffffff}
                             for k, v in oracles.items()})
    return (
        {0: output, 1: context, 2: int(initialize_state),
         3: int(update_state)},
        [(output, bytes(output_image)), (context, bytes(context_image)),
         (0x0103c290, bytes(table))],
        complete_oracles,
    )


# Exact state-0 initialization, all four state values, three assertion tails,
# both controller-mode record layouts, both early-return gates, the capacity
# correction path, doubled-count saturation, and final quantum alignment.
REVIEWED_ORACLE_CASES[("net", 0x0101b7e4)] = [
    # Invalid TBB state -> controller fault line 0x264.
    _net_timing_record_case(4, 1, 0, 0x10, {}),
    # State zero without initialization permission -> fault line 0x22c.
    _net_timing_record_case(0, 0, 0, 0x10, {}),
    # Complete state-zero setup; controller mode 0x0e returns at its age gate.
    _net_timing_record_case(0, 1, 0, 0x0e,
                            {1: -3, 3: 0, 4: 2, 6: 0x89abcdef}),
    # Existing state, ordinary empty/nonempty record forms and both gates.
    _net_timing_record_case(1, 1, 0, 0x0f,
                            {1: 1, 2: 0, 3: 0x11223344}),
    _net_timing_record_case(3, 1, 0, 0x10,
                            {1: 1, 2: 1, 3: 0x55667788}),
    # State two publishes state three and takes the full special-mode path.
    _net_timing_record_case(2, 1, 1, 0x0c,
                            {2: 1, 4: 0xaabbccdd, 5: 5,
                             8: 0, 9: 3}),
    # Ordinary full path where capacity exceeds the submitted count.
    _net_timing_record_case(1, 1, 1, 0x10,
                            {2: 0, 3: 1, 4: 0, 5: 0x01020304,
                             6: 2, 7: 5, 9: 1}),
    # Capacity correction, second count query, final adjustment, and alignment.
    _net_timing_record_case(2, 1, 1, 0x10,
                            {2: 1, 3: 1, 4: 0x10293847, 5: 8,
                             6: 3, 7: 4, 9: 0, 10: 2},
                            align=(3, 11, 4)),
    # Zero timeline unit at the capacity-correction boundary -> line 0x2a6.
    _net_timing_record_case(1, 1, 1, 0x10,
                            {2: 1, 3: 0, 4: 0x76543210, 5: 1, 6: 0},
                            timeline_unit=0),
    # Alternate special controller mode with update disabled.
    _net_timing_record_case(3, 1, 0, 0x26,
                            {1: 1, 3: 0x0badc0de}),
    # Exact 0x8000 count proves doubled-count saturation to 0xffff.
    _net_timing_record_case(1, 1, 1, 0x10,
                            {2: 1, 3: 0, 4: 0xc001d00d,
                             5: 0x8000, 6: 0xffff, 8: 0, 9: 7}),
]
REVIEWED_TARGET_CALL_ARITIES[("net", 0x0101b7e4)] = {
    0x01008d00: 2,
    0x0100d4d0: 2,
    0x0100f0fc: 1,
    0x0100f48c: 2,
    0x0100f69c: 2,
    0x0101a0e8: 0,
    0x0101da18: 2,
    0x0101dc50: 1,
    0x0101dec4: 0,
    0x010209f0: 1,
}
REVIEWED_NPTR_COUNTS[("net", 0x0101b7e4)] = 2


_DISPLAY_DISPATCH_CONTEXT = emu.SCRATCH + 0xc000


def _display_dispatch_case(mode, pending=0, mode16_tag=13):
    """One production-shaped display-dispatch iteration for a mode byte."""
    context = bytearray(0x1800)
    context[0] = 1                  # primary display owner
    context[1] = 0                  # worker is runnable
    context[0xfe6] = 0
    context[0xfea] = 0              # bypass critical-battery startup path
    context[0xcc] = 3
    context[0xcd] = 4
    context[0xed5] = 8
    context[0xee4] = 1

    descriptor = emu.SCRATCH + 0xe000
    buffers = emu.SCRATCH + 0x10000
    descriptor_image = bytes((0x11, 0x22, 0x33, 0x44, 0x55, 0, 0, 0))
    struct.pack_into("<I", context, 0x1054, descriptor)
    pointer_offsets = (0xfec, 0xff0, 0xff4, 0xffc, 0x1000, 0x1004,
                       0x1008, 0x100c, 0x1010, 0x1014, 0x101c, 0x1020,
                       0x1024, 0x1028)
    memory = [(_DISPLAY_DISPATCH_CONTEXT, bytes(context)),
              (descriptor, descriptor_image)]
    for index, offset in enumerate(pointer_offsets):
        address = buffers + index * 0x800
        struct.pack_into("<I", context, offset, address)
        image = bytearray(0x800)
        if offset == 0x100c:
            image[0] = int(mode16_tag) & 0xff
        memory.append((address, bytes(image)))
    # Re-emit the context after pointer installation; later overlapping maps
    # intentionally replace the preliminary image above.
    memory[0] = (_DISPLAY_DISPATCH_CONTEXT, bytes(context))
    memory.extend([
        (0x2000230c, (0).to_bytes(4, "little", signed=True)),
        (0x20007554, (0).to_bytes(4, "little", signed=True)),
        (0x20007af4, bytes(12)),
        (0x20007b3c, bytes(0x40)),
        (0x2000a098, int(mode).to_bytes(4, "little", signed=True)),
        (0x20018c6e, b"\0"),
        (0x20018d96, b"\0"),
        (0x20018d9b, bytes((int(pending) & 0xff,))),
        (0x20018d9c, b"\0"),
    ])

    # Calls 0/1 initialize geometry, call 3 is the loop-head device lookup,
    # and calls 4/5 are the two panel-owner gates.  Remaining generic returns
    # keep subsequent prefix iterations mapped and deterministic.
    oracles = {ordinal: {0: _DISPLAY_DISPATCH_CONTEXT, 1: 0}
               for ordinal in range(96)}
    oracles[4] = {0: 1}
    oracles[5] = {0: 1}
    writes = {3: [(None, _DISPLAY_DISPATCH_CONTEXT + 0xd5,
                   bytes((int(mode) & 0xff,)), 0x000167a8)]}

    # Force the first iteration's comparison to equality where that arm has
    # a buffer.  The selected call ordinal differs for the few setup-heavy
    # modes and is part of the reviewed call-order contract.
    compare_ordinal = 7
    if mode == 2:
        compare_ordinal = 8
    elif mode == 4:
        language = buffers + 0x7800
        memory.append((language, bytes(0x400)))
        oracles[7] = {0: 0}
        oracles[8] = {0: language}
        oracles[9] = {0: 0}
        oracles[10] = {0: _DISPLAY_DISPATCH_CONTEXT}
        compare_ordinal = None
    elif mode == 14:
        oracles[7] = {0: _DISPLAY_DISPATCH_CONTEXT}
        compare_ordinal = 8
    elif mode == 16 and mode16_tag in (13, 15):
        compare_ordinal = None       # valid tag exits immediately after unlock
    elif mode in (0, 1, 3, 13):
        compare_ordinal = None       # no buffer selected by the switch
    if compare_ordinal is not None:
        oracles[compare_ordinal] = {0: 0}
    return ({0: _DISPLAY_DISPATCH_CONTEXT}, memory, oracles, writes)


REVIEWED_ORACLE_CASES[("app", 0x00028bec)] = [
    # Every switch value, the unsigned default, all three event translations,
    # and both accepted/rejected mode-16 record families.
    *[_display_dispatch_case(mode) for mode in range(18)],
    _display_dispatch_case(5, pending=0x0f),
    _display_dispatch_case(5, pending=0x4e),
    _display_dispatch_case(5, pending=0x0d),
    _display_dispatch_case(16, mode16_tag=7),
    _display_dispatch_case(0xff),
]
REVIEWED_TARGET_CALL_ARITIES[("app", 0x00028bec)] = {
    0x0000e244: 4,
    0x00010840: 1,
    0x000167a8: 0,
    0x00016940: 0,
    0x0001694c: 1,
    0x00026850: 0,
    0x00026f74: 3,
    0x000276ec: 1,
    0x000289b0: 0,
    0x0002bed0: 1,
    0x0002c214: 0,
    0x00032ee4: 0,
    0x00033c4c: 1,
    0x00034390: 0,
    0x0003629c: 2,
    0x00042fb0: 2,
    0x00047058: 0,
    0x000723b8: 4,
    0x00072908: 4,
    0x0007cb8a: 2,
    0x0007cb2c: 0,
    0x0007cb8e: 1,
    0x0007d874: 1,
    0x00086be4: 3,
    0x00086c04: 3,
    0x00086c78: 3,
}
REVIEWED_NPTR_COUNTS[("app", 0x00028bec)] = 1


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
    if (core, va) == ("app", 0x00049acc):
        # FUN_0007d8c4 is a void block decoder.  The firmware deliberately
        # continues using its still-live r0 destination; an invented scalar
        # oracle return would replace that pointer and manufacture a fault.
        call_return_kinds = ["void"]
    if (core, va) == ("app", 0x000818dc):
        # The decoder's low word is the status selector while its live high
        # word is forwarded as the timer's second argument on -EAGAIN.
        # Queue lookup, when present, remains an ordinary pointer return.
        call_return_kinds = ["i64", "i64", "void"]
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
    absolute_read_transitions = ABSOLUTE_READ_TRANSITION_CASES.get((core, va))
    initial_primask_overrides = REVIEWED_INITIAL_PRIMASK_CASES.get((core, va))
    compare_primask = (core, va) in {
        ("net", 0x0100a7e8),
        ("net", 0x0100ec88),
        ("net", 0x010315f0),
    }
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
    initial_exclusive_monitors = REVIEWED_INITIAL_EXCLUSIVE_MONITORS.get(
        (core, va))
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
    # Canonical files retain their raw/address-derived filenames for reversible
    # provenance, while reviewed bodies may now define the readable symbol from
    # function_names_<core>.json.  Select the symbol actually defined by this
    # translation unit; do not require an asm-label that hides the readable C
    # identity from agents and source tooling.
    compile_name = name
    try:
        manifest_path = os.path.join(
            os.path.dirname(os.path.dirname(__file__)), "recon", "catalogs",
            "function_names_%s.json" % core)
        record = json.load(open(manifest_path))["by_address"]["0x%08x" % va]
        readable_name = record.get("name")
        definition = re.compile(
            r"\b%s\s*\([^;{}]*\)\s*\{" % re.escape(readable_name or ""),
            re.S)
        if readable_name and definition.search(body):
            compile_name = readable_name
    except (OSError, ValueError, KeyError, TypeError, re.error):
        pass
    comp, err = recon.compile_func(body, compile_name, va,
                                   extra_cflags=extra_cflags)
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
    terminal_targets = ({0x01008d00, 0x0100ebb8, 0x01014884, 0x01016828,
                         0x010256dc, 0x0102f4ec, 0x01039bb0}
                        if core == "net" else {0x00050af8, 0x0007e2ec})
    if (core, va) == ("net", 0x01018690):
        # LL_UNKNOWN_RSP leaves this ownership unit through a pointer-table
        # jump into one of three shared SoftDevice continuation entries.
        terminal_targets = set(terminal_targets) | {
            0x01018f1a, 0x01018f22, 0x01018fac,
        }
    if (core, va) == ("app", 0x00076a94):
        # Newlib abort is the required terminal action of __assert_func; the
        # catalog's old returning-oracle model manufactured an infinite loop.
        terminal_targets = set(terminal_targets) | {0x00051180}
    if (core, va) == ("app", 0x000809b0):
        # The impossible-slot assertion helper is specialized and noreturn;
        # treating it as an ordinary oracle falls into defensive switch code.
        terminal_targets = set(terminal_targets) | {0x00051c38}
    if (core, va) in (("app", 0x00086c1e), ("app", 0x00087080)):
        # The secure-copy constraint handler ends in ARCH_EXCEPT(3).  Its
        # post-BL instructions are unreachable defensive fallthrough.
        terminal_targets = set(terminal_targets) | {0x00051164}
    if (core, va) == ("app", 0x00078110):
        # Both allocation-failure islands branch to the firmware assertion
        # sink FUN_00076a94.  Instructions after that BL are defensive
        # compiler fallthrough and consume caller-clobbered r1; treating the
        # sink as an ordinary returning oracle manufactures a meaningless
        # retry size.  Compare the exact call prefix through the fatal helper.
        terminal_targets = set(terminal_targets) | {0x00076a94}
    if (core, va) == ("app", 0x00019950):
        # sys_reboot does not return in production.  Modeling it as an
        # ordinary oracle drops execution back into ANCS's deliberate fatal
        # retry loop and turns each initializer-error fixture into a timeout.
        terminal_targets = set(terminal_targets) | {0x0004c0a8}
    target_call_arities = dict(ctx["call_arity_by_target"])
    target_call_arities.update(REVIEWED_TARGET_CALL_ARITIES.get((core, va), {}))
    target_call_argument_indices = REVIEWED_CALL_ARGUMENT_INDICES_BY_TARGET.get(
        (core, va))
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
    if (core, va) == ("app", 0x0003b824):
        # A complete recording render owns four 199x320 pixel-mask passes.
        # The generic cap stopped during frame one and allowed the remaining
        # frames, final LCD publications, and DMIC transition to go unproved.
        compare_max_insns = 3000000
    if (core, va) == ("app", 0x0003bfe0):
        # Both initialization and page-change rendering own eight complete
        # 199x320 mask traversals; the old 200k cap stopped during frame one.
        compare_max_insns = 7000000
    for nptr in nptr_modes:
        if prefix_first:
            v = emu.compare(orig, va, size, cb + ct, cva, cs, code_base=ctx["cb"],
                            trials=trials, nptr=nptr, ret_kind=rk, no_return=True,
                            prefix_k=prefix_k,
                            arg_overrides=ovs, memory_overrides=movs,
                            absolute_memory_overrides=absolute_movs,
                            pointer_read_transitions=pointer_read_transitions,
                            absolute_read_transitions=absolute_read_transitions,
                            terminal_targets=terminal_targets,
                            oracle_overrides=oracle_overrides, call_arities=call_arities,
                            call_float_arities=call_float_arities,
                            call_return_kinds=call_return_kinds,
                            fp_arg_overrides=fp_arg_overrides,
                            call_arity_by_target=target_call_arities,
                            call_arity_by_format=format_call_arities,
                            call_argument_indices_by_target=target_call_argument_indices,
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
                            initial_primask_overrides=initial_primask_overrides,
                            compare_primask=compare_primask,
                            initial_exclusive_monitors=initial_exclusive_monitors,
                            orig_internal_code_regions=orig_internal_code_regions,
                            max_insns=compare_max_insns,
                            max_resumes=compare_max_resumes)
        else:
            v = emu.compare(orig, va, size, cb + ct, cva, cs, code_base=ctx["cb"],
                            trials=trials, nptr=nptr, ret_kind=rk, arg_overrides=ovs,
                            memory_overrides=movs, terminal_targets=terminal_targets,
                            absolute_memory_overrides=absolute_movs,
                            pointer_read_transitions=pointer_read_transitions,
                            absolute_read_transitions=absolute_read_transitions,
                            oracle_overrides=oracle_overrides, call_arities=call_arities,
                            call_float_arities=call_float_arities,
                            call_return_kinds=call_return_kinds,
                            fp_arg_overrides=fp_arg_overrides,
                            call_arity_by_target=target_call_arities,
                            call_arity_by_format=format_call_arities,
                            call_argument_indices_by_target=target_call_argument_indices,
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
                            initial_primask_overrides=initial_primask_overrides,
                            compare_primask=compare_primask,
                            initial_exclusive_monitors=initial_exclusive_monitors,
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
        # Every canvas-distance TBB arm is semantically live under the bounded
        # panel-state fixtures; changing one recovered gear offset must fail.
        "cal_panel_canvas_coord": (
            "case 2:\n            computed_x = 8;",
            "case 2:\n            computed_x = 9;"),
        # All four mask frames, LCD publications, and the final DMIC gate are
        # beyond the historical generic instruction cap and must stay live.
        "ui_QuickNote_task": (
            "frame != 4; ++frame",
            "frame != 3; ++frame"),
        # The reviewed command-prefix cases bind controller response objects
        # to the exact Read Local Supported Features opcode.
        "FUN_00012080": (
            "FUN_00053d70(0x1003,0,local_30)",
            "FUN_00053d70(0x1004,0,local_30)"),
        # Exact 20-byte boundary separates the short-buffer arm from the
        # context-resident long-payload arm.
        "FUN_00017f70": (
            "if (param_3 < 0x15) {",
            "if (param_3 < 0x14) {"),
        # The complete queue record exposes its protocol type at enqueue.
        "sendAudioStram2Cache": (
            "record.type = 2;",
            "record.type = 3;"),
        # The master dispatcher must retain its exact firmware-load rejection
        # marker under the bounded request-kind-three production fixture.
        "master_process_audio_fw_load_req": (
            "*param_3 = 0x6e;",
            "*param_3 = 0x6f;"),
        # Record padding is observable through the complete compiler-owned
        # 20-byte object passed to the formatter and direct callback.
        "FUN_00021a40": (
            "FUN_00086c78(record + 3, 17, 17);",
            "FUN_00086c78(record + 3, 16, 17);"),
        # The paired flash buffer compares all 1028 bytes, including the CRC
        # seed word before the memset-compatible helper initializes its tail.
        "FUN_00022974": (
            "*(uint32_t *)buffer = 0xff;",
            "*(uint32_t *)buffer = 0x100ff;"),
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
        # The classifier result is a callee-owned selector.  Its reviewed
        # dequeue/out-record cases must expose the distinct kind-three mode.
        "FUN_0001965c": (
            "mode = 4;",
            "mode = 2;"),
        # The paired driver fixtures distinguish the two adjacent vtable
        # callbacks; swapping either recovered slot must remain observable.
        "FUN_0002e398": (
            "fn_t f = *(volatile fn_t*)(r3v + 0);",
            "fn_t f = *(volatile fn_t*)(r3v + 4);"),
        "FUN_0002e440": (
            "fn_t f = *(volatile fn_t*)(r3v + 4);",
            "fn_t f = *(volatile fn_t*)(r3v + 0);"),
        # The transfer descriptor's byte type is part of the concrete stack
        # object consumed by the controller callback.
        "opt3007_chip_init": (
            "frame.transfer.type = 2;",
            "frame.transfer.type = 3;"),
        # The hook copies the complete 256-byte command window before parsing;
        # the call trace keeps that reviewed boundary observable.
        "spec_ble_command_hook": (
            "FUN_00086c1e((uintptr_t)&local_520,param_1,param_2,0x100);",
            "FUN_00086c1e((uintptr_t)&local_520,param_1,param_2,0xff);"),
        # A live direct logger sink compares the recovered format token.
        "FUN_0002eb40": (
            "DEBUG_PRINT(0xa3e80,",
            "DEBUG_PRINT(0xa3e81,"),
        # The reviewed exact-edge/threshold cases distinguish this bound.
        "FUN_0002ed68": (
            "0x40ffff < *puVar2v",
            "0x40fffe < *puVar2v"),
        # Exact fault diagnostics keep every selected CFSR message live.
        "FUN_00050558": (
            "message.message = 0x000f1e69;",
            "message.message = 0x000f1e68;"),
        "FUN_00050c24": (
            "local.c = param_1;",
            "local.c = param_1 + 1;"),
        # The fallback publishes the computed region number, not attributes
        # from the adjacent descriptor object.
        "FUN_00050c54": (
            "iVar3 = FUN_00050c24(uVar4);",
            "iVar3 = FUN_00050c24(uVar4 + 1);"),
        # Type-zero dispatch selects the first handler-table callback.
        "FUN_000513e8": (
            "pcVar12 = (codef)(uintptr_t)*puVar7;",
            "pcVar12 = (codef)(uintptr_t)puVar7[1];"),
        # The leading clear owns the complete 24-byte output contract.
        "FUN_000518a8": (
            "FUN_00086c78(param_2, 0, 0x18);",
            "FUN_00086c78(param_2, 0, 0x17);"),
        # A valid four-byte event forwards the decoded high halfword in r3.
        "FUN_0007f894": (
            "callback_value = payload[1];",
            "callback_value = length;"),
        "FUN_00080798": (
            "FUN_00050c24(param_1);",
            "FUN_00050c24(param_1 + 1);"),
        # A descriptor may be decoded only once.
        "FUN_00080872": (
            "if (field->decoded != 0)",
            "if (field->decoded == 0)"),
        # Both status bytes one and two are accepted on an exact lookup.
        "FUN_000809f6": (
            "(unsigned char)(byte3 - 1) < 2",
            "(unsigned char)(byte3 - 1) < 1"),
        # The three-byte prefix comes from source offsets three through five.
        "FUN_00080ca0": (
            "decoded[2] = *(volatile unsigned char *)(param_2 + 5);",
            "decoded[2] = *(volatile unsigned char *)(param_2 + 4);"),
        # Width literals are semantic inputs to the CBOR reader helpers, not
        # incidental live registers at their call sites.
        "FUN_00085ebc": (
            "FUN_00085e1a(param_1, param_2 + 1, 4);",
            "FUN_00085e1a(param_1, param_2 + 1, 8);"),
        "FUN_00086064": (
            "FUN_00085e1a(local_30, &local_38, 8);",
            "FUN_00085e1a(local_30, &local_38, 4);"),
        # Negative encoded integers are converted byte-for-byte before the
        # signed-value helper consumes the complete local record.
        "FUN_0008629e": (
            "*dst = (unsigned char)~(*src);",
            "*dst = *src;"),
        # Unlinking transfers both neighboring links before retiring the node.
        "FUN_0008688e": (
            "*(volatile int *)(iVar3 + 4) = (int)piVar2;",
            "*(volatile int *)(iVar3 + 4) = (int)piVar1;"),
        # The descriptor classification uses the complete high nibble.
        "FUN_00086b7e": (
            "(flags & 0xf000) == 0x2000",
            "(flags & 0xf000) == 0x1000"),
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
        # The sixth AAPCS argument at FUN_00071358 is a pointer to the complete
        # request chain. Its final initialized word must remain observable.
        "FUN_0004d100": (
            "struct { int *first; int *second; int zero; } request = { p3, p3, 0 };",
            "struct { int *first; int *second; int zero; } request = { p3, p3, 1 };"),
        # Equality selects the tail continuation, not the counter increment.
        "FUN_0005505c": (
            "if (b120 == 0 || b120 < b121) {",
            "if (b120 == 0 || b120 <= b121) {"),
        # The release consumes the controller handle published through the
        # five-word output workspace, not a post-copy cursor.
        "FUN_00055350": (
            "FUN_0005f24c((void *)(uintptr_t)local_34[0]);",
            "FUN_0005f24c((void *)(uintptr_t)(local_34[0] + 1));"),
        # FUN_00081102 consumes the exact bit-test value retained in r1.
        "FUN_00055454": (
            "FUN_00081102(param_1, (uint32_t)param_2 << 12);",
            "FUN_00081102(param_1, (uint32_t)param_2 << 11);"),
        # The channel lookup receives the live channel selector in r0.
        "FUN_0006567c": (
            "uVar12 = FUN_00065434(param_1);",
            "uVar12 = FUN_00065434(0);"),
        # The final register publication sets exactly bit one.
        "FUN_00065b18": (
            "(iVar2+0x200))|2;",
            "(iVar2+0x200))|4;"),
        # Fatal diagnostics retain the exact file/name literal ordering.
        "FUN_00066ec0": (
            "FUN_0007e2fa(0x00099cbdUL,0x000f7a30UL,0x000f6df0UL,0x15c);",
            "FUN_0007e2fa(0x000f7a30UL,0x00099cbdUL,0x000f6df0UL,0x15c);"),
        # The absent-provider payload is explicitly initialized to zero.
        "FUN_000829c0": (
            "local_14[0] = 0;",
            "local_14[0] = 1;"),
        # The sink consumes the complete two-byte provider result.
        "FUN_00082a1a": (
            "FUN_00082932(param_3, param_4, param_5, local_12, 2);",
            "FUN_00082932(param_3, param_4, param_5, local_12, 1);"),
        # The zero-selector tail retains entry argument four in r2.
        "FUN_00082e04": (
            "FUN_0005c310(param_1,param_3,param_4,param_5);",
            "FUN_0005c310(param_1,param_3,0,param_5);"),
        # Logged success cases make the recovered format/argument ABI live.
        "getDashboardStartUpModeInfofromFlash": (
            "FUN_00019c70(0x0009e9bfUL, 0x0009ed09UL, param_3,\n"
            "                         *(volatile unsigned int*)0x20007554UL);",
            "FUN_00019c70(0x0009e9bfUL, 0x0009ed09UL, param_3,\n"
            "                         0);"),
        # Equality is valid (including the zero-length same-address case);
        # only a capacity overflow enters the fatal constraint handler.
        "FUN_00086c1e": (
            "length > destination_size ||",
            "length >= destination_size ||"),
        "FUN_00087080": (
            "length > destination_size ||",
            "length >= destination_size ||"),
        # The normalization helper's d0 result is the value subsequently
        # scaled and returned; retaining the input recreates the false proof.
        "FUN_000870ea": (
            "u.d = FUN_00078bf8(u.d);",
            "FUN_00078bf8(u.d);"),
        # Complete paired transport records keep the selected command byte
        # observable at the queue boundary.
        "display_close": (
            "packet.type = 3;",
            "packet.type = 4;"),
        "display_powerEvent": (
            "packet[0] = powered_on == 1 ? 7 : 8;",
            "packet[0] = powered_on == 1 ? 8 : 7;"),
        # The translated-screen icon family uses distinct production IDs for
        # the two state-byte arms.
        "draw_template_translate_screen": (
            "uVar3 = 0x1b;",
            "uVar3 = 0x1c;"),
        # The notification command and final callback context are both live at
        # the publisher boundary; keep the recovered command ID exact.
        "mobile_send_notification_to_ble_device_test": (
            "FUN_00021a40(uVar1, uVar3, 0x4b, param_3);",
            "FUN_00021a40(uVar1, uVar3, 0x4c, param_3);"),
        # Direction 35 is the inclusive final production icon.
        "navigation_direction_img_display": (
            "(unsigned int)(param_1 - 1) < 0x23",
            "(unsigned int)(param_1 - 1) < 0x22"),
        # The transport callback consumes the complete 202-byte DMIC record.
        "send_dmic_msg": (
            "(&message, 202);",
            "(&message, 201);"),
        # Queued event records have the fixed F5/id/CB three-byte framing.
        "send_event": (
            "event[0] = 0xf5;",
            "event[0] = 0xf4;"),
    }
    for function_name, (correct, wrong) in negative_sources.items():
        source_path = (BASE + "/recon/app/src/" + function_name + ".c")
        source = open(source_path).read()
        assert correct in source, function_name
        verdict = verify("app", function_name, trials_random=8,
                         source_override=source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL", (function_name, verdict)

    # Two independent late-island contracts for the same large dispatcher:
    # its unchanged-mode acknowledgement byte and timestamp byte order.  A
    # tuple (rather than the dict above) intentionally permits repeated names.
    audio_fw_master_negative_sources = (
        ("param_3[2] = 0xc9;", "param_3[2] = 0xca;"),
        ("uVar20 >> 0x18);", "uVar20 >> 0x10);"),
    )
    audio_fw_master_source = open(
        BASE + "/recon/app/src/master_process_audio_fw_load_req.c").read()
    for correct, wrong in audio_fw_master_negative_sources:
        assert correct in audio_fw_master_source, correct
        verdict = verify(
            "app", "master_process_audio_fw_load_req", trials_random=0,
            source_override=audio_fw_master_source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL", (wrong, verdict)

    # Independent cache-capacity, record-length, and deferred-log contracts
    # for the same producer; repeated source names cannot live in the dict.
    audio_cache_negative_sources = (
        ("record.payload_length = sizeof(record.payload);",
         "record.payload_length = sizeof(record.payload) - 1;"),
        ("== 0x12)", "== 0x13)"),
        ("FUN_00019c70(LOG_CACHE_FULL, LOG_MODULE_AUDIO_CACHE);",
         "FUN_00019c70(LOG_CACHE_SEND_FAILED, LOG_MODULE_AUDIO_CACHE);"),
    )
    audio_cache_source = open(
        BASE + "/recon/app/src/sendAudioStram2Cache.c").read()
    for correct, wrong in audio_cache_negative_sources:
        assert correct in audio_cache_source, correct
        verdict = verify(
            "app", "sendAudioStram2Cache", trials_random=0,
            source_override=audio_cache_source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL", (wrong, verdict)

    # Independent deep-path contracts for the same audio request router.
    audio_request_negative_sources = (
        ("0, 0x14 - param_3);", "0, 0x15 - param_3);"),
        ("FUN_00017eec(forwarding.payload, param_3 & 0xff);",
         "FUN_00017eec(forwarding.payload, (param_3 + 1) & 0xff);"),
        ("[1] = 0xc9;", "[1] = 0xca;"),
        ("(void *)(iVar10 + 600)", "(void *)(iVar10 + 604)"),
    )
    audio_request_source = open(
        BASE + "/recon/app/src/FUN_00017f70.c").read()
    for correct, wrong in audio_request_negative_sources:
        assert correct in audio_request_source, correct
        verdict = verify(
            "app", "FUN_00017f70", trials_random=0,
            source_override=audio_request_source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL", (wrong, verdict)

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
        # An ECB hardware error retries the transaction; treating completion
        # as the retry condition silently returns after an aborted block.
        "FUN_0100a7e8": (
            "} while (ecb->EVENTS_ERRORECB != 0);",
            "} while (ecb->EVENTS_ENDECB != 0);"),
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

    # The net serializer fixture must genuinely consume the one-byte local
    # index object passed at 0x0102c3dc.  Corrupting only that byte changes the
    # callback payload and the selected string, while leaving outer flow and
    # both accumulation arrays intact.
    serializer_source = open(
        BASE + "/recon/net/src/FUN_0102bfe4.c").read()
    serializer_correct = "local_49 = abStack_48[uVar15];"
    serializer_wrong = "local_49 = (byte)(abStack_48[uVar15] ^ 1u);"
    assert serializer_correct in serializer_source
    serializer_verdict = verify(
        "net", "FUN_0102bfe4", trials_random=0,
        source_override=serializer_source.replace(
            serializer_correct, serializer_wrong, 1))
    assert serializer_verdict["status"] == "FAIL", serializer_verdict

    net_directed_negative_sources = (
        # The state-eight handle packet publishes a fixed ready flag after
        # its zero byte; all four volatile header stores are order/value live.
        ("FUN_0100ec88",
         "*(volatile uint8_t *)(packet + 5) = 1;",
         "*(volatile uint8_t *)(packet + 5) = 2;"),
        # Architectural interrupt masking and the adjacent contention byte
        # are independently live in the blocking ECB runner.
        ("FUN_0100a7e8",
         "if (saved_primask == 0) {",
         "if (1) {"),
        ("FUN_0100a7e8",
         "if (retry_requested == 0) {",
         "if (retry_requested != 0) {"),
        # The final state word uses the post-shift mix for its low 26 bits but
        # the pre-shift mix for its high six bits.  Moving that recovered
        # six-bit splice by one position must be observable.
        ("FUN_0100f5d8",
         "(pre_shift_mix << 26)",
         "(pre_shift_mix << 25)"),
        # A completed CCM operation is valid only when the hardware error
        # event remains clear; the live error fixture rejects polarity drift.
        ("FUN_0101fd8c",
         "CCM_REGISTER(CCM_EVENT_ERROR) == 0",
         "CCM_REGISTER(CCM_EVENT_ERROR) != 0"),
        # FUN_0101e090 consumes the selected entry explicitly.  Passing null
        # recreates the old stale-r0 shortcut and must change its call ABI.
        ("FUN_0102946c",
         "FUN_0101e090(entry)",
         "FUN_0101e090((void *)0)"),
        # Allocation is deliberately highest-numbered-first; mixed masks
        # distinguish the recovered CLZ selection from a lowest-bit claim.
        ("FUN_01034328",
         "31U - (unsigned int)__builtin_clz(observed)",
         "(unsigned int)__builtin_ctz(observed)"),
        ("FUN_01037a60",
         "if (exception != 0) {",
         "if (0) {"),
        ("FUN_010384a8",
         "{ uVar5 = 2; goto LAB_0103851c; }",
         "{ uVar5 = 1; goto LAB_0103851c; }"),
        # The fifth AAPCS argument is loaded with LDRB and passed to the
        # identity helper zero-extended; signed reconstruction corrupts values
        # 0x80..0xfe.  The timing request's exact-period flag lives at sparse
        # offset thirteen and is independently observable by FUN_01018dac.
        ("FUN_01019750",
         "extern int FUN_0100ca98(uint8_t, void *);",
         "extern int FUN_0100ca98(int8_t, void *);"),
        ("FUN_0101ab20",
         "request.exact_period = remainder == period * (remainder / period);",
         "request.exact_period = 1;"),
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

    # These straight-line wrappers have no CFG-derived selector cases, so
    # retain a small positive random budget for their focused ABI regressions.
    # Each mutation changes one recovered live argument while preserving call
    # order and control flow.
    net_random_negative_sources = (
        ("FUN_010388c8",
         "FUN_0103b442(piVar4, 1);",
         "FUN_0103b442(piVar4, 2);"),
        ("FUN_0103961c",
         "(int)(quotient >> 32));",
         "0);"),
        ("FUN_01039936",
         "int iVar2 = FUN_01039768(param_1, param_3);",
         "int iVar2 = FUN_01039768(param_1, param_2);"),
    )
    for function_name, correct, wrong in net_random_negative_sources:
        source_path = BASE + "/recon/net/src/" + function_name + ".c"
        source = open(source_path).read()
        assert correct in source, (function_name, correct)
        verdict = verify("net", function_name, trials_random=4,
                         source_override=source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL" and verdict.get("checked", 0) > 0, \
            (function_name, wrong, verdict)

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
        ("FUN_00024684", "if (record[0] != 0xaa)",
         "if (record[0] != 0xab)"),
        # onboarding_ble_process has a reviewed case for every opcode, both
        # invalid diagnostic sinks, each response kind, and the otherwise
        # rare persistence-result==0 tail.  Keep representative early, switch,
        # response, and deep-persistence effects live as permanent gates.
        ("onboarding_ble_process",
         "*(volatile u8*)(param_4+2) = 0xca;",
         "*(volatile u8*)(param_4+2) = 0xcb;"),
        ("onboarding_ble_process",
         "*(volatile u8*)(ctx + 0x1f) = 0;",
         "*(volatile u8*)(ctx + 0x1e) = 0;"),
        ("onboarding_ble_process",
         "*(volatile u8*)(param_4+3) = uVar2;",
         "*(volatile u8*)(param_4+4) = uVar2;"),
        ("onboarding_ble_process",
         "update_persist_task_status(t2, 0xe, 2);",
         "update_persist_task_status(t2, 0xe, 3);"),
        ("onboarding_ble_process",
         "*(volatile u8*)(ctx + 0x20) = *(volatile u8*)(t3 + 0xed5);",
         "*(volatile u8*)(ctx + 0x21) = *(volatile u8*)(t3 + 0xed5);"),
        ("onboarding_ble_process",
         "*(volatile u8*)(t5 + 0xed5) = 0x2a;",
         "*(volatile u8*)(t5 + 0xed5) = 0x2b;"),
        # The repaired response/serialization/brightness batch keeps queue
        # identity, published state, delay storage, clamp bound, and panel
        # command order independently observable under reviewed fixtures.
        ("send_response_data_to_msgqueue", "FUN_000720d0(0x2000392cUL,",
         "FUN_000720d0(0x20003930UL,"),
        ("serialization_init", "0x20007a80UL = 1;",
         "0x20007a80UL = 2;"),
        ("setDelayExitValue", "0x2000a094UL = param_1;",
         "0x2000a098UL = param_1;"),
        ("set_brightness_lum_base", "0x3f < uVar8",
         "0x3e < uVar8"),
        ("set_brightness_to_panel_reg", "FUN_0007d63e(6);",
         "FUN_0007d63e(7);"),
        ("opt3007_chip_init", "frame.transfer.length = 3;",
         "frame.transfer.length = 2;"),
        ("pairing_failed", "FUN_00056a68(connection, 0x13);",
         "FUN_00056a68(connection, 0x12);"),
        ("panel_init", "FUN_0007d642(0x31, 4);",
         "FUN_0007d642(0x31, 3);"),
        ("panel_off", "context + 0x35c", "context + 0x35d"),
        ("post_notification_cmd_response",
         "command->length != 0x1b4",
         "command->length != 0x1b5"),
        # User-setting field offset, installed callback, published IPC owner,
        # ANCS request queue, and second static-clear span are directly live.
        ("read_usr_settting_from_flash", "param_1[0x15] = buf[0x15]",
         "param_1[0x15] = buf[0x14]"),
        ("register_imu_funsion_context", "0x00025fadUL",
         "0x00025faeUL"),
        ("register_ipc_service_context", "0x20007a84UL",
         "0x20007a88UL"),
        ("request_ancs_attr_ext", "uVar1 = 0x20006ae8",
         "uVar1 = 0x20006aec"),
        ("reset_all_static_info", "base + 0x35", "base + 0x34"),
        ("navigation_overview_map_display",
         "*(volatile unsigned char*)(iVar3 + 0x15) = 0;",
         "*(volatile unsigned char*)(iVar3 + 0x15) = 1;"),
        ("not_disturb_sync_data", "| 5UL;", "| 4UL;"),
        ("on_triple_click", "0x20018d8bUL", "0x20018d8aUL"),
        ("onboarding_sync_data", "| 4UL;", "| 5UL;"),
        ("opt3007_chip_deinit", "(v + 0x10)", "(v + 0x14)"),
        # Panel state byte, suspend command, controller-id acceptance, burial
        # reset marker, and upper width bound are each independently live.
        ("jbd_panel_resume", "param_1+0x369", "param_1+0x368"),
        ("jbd_panel_suspend", "command = 0xff", "command = 0xfe"),
        ("jdb_panel_init", "iVar1 == 0x4010", "iVar1 == 0x4011"),
        ("load_burial_point", "base + 0xda) = 7",
         "base + 0xda) = 6"),
        ("load_sys_setting", "width_b > 0x40", "width_b > 0x41"),
        ("button_init", "FUN_00017688((uintptr_t)gpio_specs[0], 0x10000)",
         "FUN_00017688(0, 0x10000)"),
        ("ble_process_get_req",
         "(*(send_response_fn *)(context + 0x0c))(data, 0xc2);",
         "(*(send_response_fn *)(context + 0x0c))(response, 0xc2);"),
        ("change_work_mode_to", "{0,0,0,0,0,0,0,0,0,1},",
         "{0,0,0,0,0,0,0,0,0,0},"),
        ("check_bonded_addr", "+ 0x367u", "+ 0x366u"),
        ("cleanAppLanguageInfo",
         "FUN_00019c70(0x9e903, 0x9ed8f);",
         "FUN_00019c70(0x9e904, 0x9ed8f);"),
        # Queue identity, cached-index destinations, clock divisor, and final
        # volatile charge-bit extraction are live in the explicit cases above.
        ("getAudioMessageQueueCacheData", "0x20003890UL",
         "0x20003894UL"),
        ("getNewsIndex", "base[5] = b;", "base[4] = b;"),
        ("getStocksIndex", "base[3] = b;", "base[4] = b;"),
        ("get_boot_seconds", "1000,0);", "999,0);"),
        ("get_glassbox_charge_status", "return *pbVar1 >> 7;",
         "return *pbVar1 >> 6;"),
        # Index clearing, queue log gating, whitelist record layout, and the
        # debug work-state offset are all exercised by explicit production
        # states rather than relying on random globals or allocator results.
        ("cleanNewsIndex", "0x20004950UL+5", "0x20004950UL+4"),
        ("cleanStocksIndex", "0x20004950UL+3", "0x20004950UL+4"),
        ("clean_dmic_msgq", "0x2000230cUL > 0",
         "0x2000230cUL > 1"),
        ("convert_app_whitelist_to_json", "uVar8*0x38 + 0x2a",
         "uVar8*0x38 + 0x29"),
        ("debug_print", "context + 0x220", "context + 0x224"),
        # Atomic flag ownership, complete advertising request identity,
        # decoder reversal extent, retry classification, and payload capacity
        # are independently live in the repaired 0x81080..0x821f4 batch.
        ("FUN_00081080", "~0x8000u", "~0x4000u"),
        ("FUN_000811ce", "FUN_00055534(0x2008,",
         "FUN_00055534(0x2007,"),
        ("FUN_00081326", "param_3 + 7", "param_3 + 6"),
        ("FUN_000818dc", "result == -11", "result == -10"),
        ("FUN_000821f4", "FUN_000585f0(owner, 1, 4)",
         "FUN_000585f0(owner, 1, 3)"),
        ("FUN_000755f8", "uVar4=0x20", "uVar4=0"),
        ("FUN_00075c2c", "return fallback;", "return value;"),
        ("FUN_000767c8",
         "FUN_0000d58c(uVar7,uVar8,uVar4,normalized_high)",
         "FUN_0000d58c(uVar7,uVar8,uVar4,uVar5)"),
        ("FUN_00076cc8", "&uStack_8, param_1, &uStack_8",
         "&uStack_4, param_1, &uStack_8"),
        ("FUN_000777f0", "param_1, &uStack_c, uVar2, &uStack_c",
         "param_1, &uStack_8, uVar2, &uStack_c"),
        # JSON decoding, scalar serialization, recursive release, wrapper
        # forwarding, and all eight IRQ mapping iterations are covered by
        # production-shaped cases rather than pointer-fuzz fallthrough alone.
        ("FUN_00064290", "case 0x6e: bVar7 = 10;",
         "case 0x6e: bVar7 = 11;"),
        ("FUN_000646c0",
         "FUN_0008705a(iVar6,&local_44,",
         "FUN_0008705a(iVar6,local_40,"),
        ("FUN_00064b1c",
         "release((volatile int *)param_1[4]);",
         "release((volatile int *)param_1[8]);"),
        ("FUN_00065324", "FUN_00065000(param_1, param_2);",
         "FUN_00065000(param_2, param_1);"),
        ("FUN_00065620", "}while(uVar3!=8);", "}while(uVar3!=7);"),
        # Formatter/queue tail batch: preserve the recovered writer flags,
        # integer conversion base, fixed-point bias, event mode, and callback
        # control byte under the reviewed fixtures above.
        ("FUN_0007797c", "frame.writer.flags = 0xffff0208u;",
         "frame.writer.flags = 0xffff0209u;"),
        ("FUN_00078f88", "state.base = 10;", "state.base = 11;"),
        ("FUN_0007c0a8", "param_1 * 0x8000 + 999",
         "param_1 * 0x8000 + 998"),
        ("FUN_0007c0e2", "(param_2 & 0xffffff00u) | 2u",
         "(param_2 & 0xffffff00u) | 3u"),
        ("FUN_0007c20a", "frame.control = 0xf4;",
         "frame.control = 0xf5;"),
        # Queue-wrapper batch: keep packet opcode, exact copy extent/source,
        # UID field forwarding, and display close opcode observable through
        # bounded success/failure fixtures with modeled producer writes.
        ("delAudioStreamRecord", "buf[0] = 4;", "buf[0] = 5;"),
        ("dequeue_ancs", "FUN_00086c04(param_1, buf, 0x1b4);",
         "FUN_00086c04(param_1, buf, 0x1b3);"),
        ("dequeue_dmic", "(const void *)0x000885ccUL",
         "(const void *)0x000885cdUL"),
        ("dequeue_uid", "param_1[1] = record.second;",
         "param_1[1] = record.first;"),
        ("display_MasterSendClose", "record[0] = 6;", "record[0] = 7;"),
        # Dashboard/touch action bytes, the attitude worker's mode delay, and
        # initialized dashboard signature are each live under reviewed state
        # graphs rather than full-width pointer fuzzing.
        ("handle_dashboard_action", "0x20004950UL+3",
         "0x20004950UL+4"),
        ("handle_stocks_action", "0x20004950UL+5",
         "0x20004950UL+4"),
        ("handle_touch_single_click", "sub_1672c(action);",
         "sub_1672c(action + 1);"),
        ("imu_fusion_thread", "uVar7 = 0x8000;",
         "uVar7 = 0x8001;"),
        ("imu_fusion_thread", "I(buf1 + 4)",
         "I(buf1 + 8)"),
        ("imu_fusion_thread", "0x45a1cac1,0x3fadf3b6",
         "0x45a1cac2,0x3fadf3b6"),
        ("imu_fusion_thread", "as_f(d4),as_f(d5),as_f(d6)",
         "as_f(d5),as_f(d4),as_f(d6)"),
        ("imu_fusion_thread",
         "I(0x20007aa8) = (int)(roll * 100.0f);",
         "I(0x20007aa8) = (int)(pitch * 100.0f);"),
        ("imu_fusion_thread",
         "float la0 = roll, la1 = pitch, la2 = yaw;",
         "float la0 = pitch, la1 = roll, la2 = yaw;"),
        ("init_dashboard_info", "VB(pb+2) = 0x92;",
         "VB(pb+2) = 0x93;"),
        # Persistence/synchronization and UART/file fixtures must expose the
        # retry budget, complete two-word signal, state transition, packet
        # payload boundary, and frame preamble respectively.
        ("store_whitelist", "unsigned char cVar5 = 3;",
         "unsigned char cVar5 = 2;"),
        ("sync_message_signal_to_slave", "message.signal & 0xffff0000U",
         "message.signal & 0xff000000U"),
        ("trigger_screen_state_change",
         "*(volatile unsigned char*)(param_2 + 0xfe8) = 1;",
         "*(volatile unsigned char*)(param_2 + 0xfe8) = 0;"),
        ("try_to_save_file", "packet + 5, packet_length - 5",
         "packet + 4, packet_length - 5"),
        ("uart_callback", "param_3==0x5a",
         "param_3==0x5b"),
        ("FUN_0002ace0", "timeout.window.max = 30000;",
         "timeout.window.max = 30001;"),
        # Discovery and request validation: directed argument selectors must
        # retain the exact logger event and fatal-report argument ordering.
        ("FUN_0005a724",
         "FUN_00080cf2(param_1, frame.address)",
         "FUN_00080cf2(param_1, frame.decoded)"),
        ("FUN_0005b9cc",
         "0x00099cbdUL,0x000f3ebdUL,0x000f46b8UL,0x118f",
         "0x000f3ebdUL,0x00099cbdUL,0x000f46b8UL,0x118f"),
        # Settings serialization, selection, parse, flash, and shutdown paths
        # reconstructed in the CFG-fail redo sweep.
        ("FUN_00051ac0", "(param_3>>3)&1", "(param_3>>4)&1"),
        ("FUN_00051d8c", "status = 0x1d;", "status = 0x1c;"),
        ("FUN_00052180", "response = 9;", "response = 8;"),
        ("FUN_00052604", "iVar3+4, 0x3f, uVar2", "iVar3+4, 0x3e, uVar2"),
        ("FUN_000526f4", "0x00080ab5UL", "0x00080ab6UL"),
        # Recovered settings rotation/tree/glyph/image semantics from the
        # CFG-fail redo sweep.  Each has a coherent reviewed state case above.
        ("FUN_0003439c",
         "uVar7=(*(volatile uint8_t*)(iVar4+0xdd)-1)&0xff;",
         "uVar7=(*(volatile uint8_t*)(iVar4+0xdd)-2)&0xff;"),
        ("FUN_00034dbc", "FUN_0008503c(root, 0x000a862c)",
         "FUN_0008503c(root, 0x000a862d)"),
        ("FUN_00035050", "FUN_0008503c(iVar4, 0xa862c)",
         "FUN_0008503c(iVar4, 0xa862d)"),
        ("FUN_000362e8", "FUN_00047a4c(uVar3,0x120)",
         "FUN_00047a4c(uVar3,0x121)"),
        ("FUN_00036820", "mode * 0x3ebeu", "mode * 0x3ebfu"),
        # Recovered radio setup/activation/transport records.  These mutations
        # are deliberately aimed at reviewed stack objects or observable
        # status returns, so each gate is deterministic with random trials off.
        ("FUN_0005f654",
         "error.format = 0x000f5503", "error.format = 0x000f5504"),
        ("FUN_0005f760", "range_error[0] = 2;", "range_error[0] = 3;"),
        ("FUN_0005fb30", "+ 0x51) = 0;", "+ 0x52) = 0;"),
        ("FUN_00060c00", "return -0x13;", "return -0x12;"),
        ("FUN_00061624",
         "LAB_00061734:\n        uVar4 = 0;",
         "LAB_00061734:\n        uVar4 = 1;"),
        # Transport wrappers and value configuration use complete local
        # records plus production owner graphs; each mutation changes one
        # independently observed byte, register argument, or state update.
        ("FUN_00083cfc", "param_3, param_4);", "0, param_4);"),
        ("FUN_00083dc8",
         "request[2] = (unsigned char)param_4;",
         "request[2] = (unsigned char)(param_4 + 1);"),
        ("FUN_00083e70", "buf[0] = 0x07;", "buf[0] = 0x06;"),
        ("FUN_00083ede", "(submode << 8)", "(submode << 9)"),
        ("FUN_000840cc", "owner->statistics->updates++;",
         "owner->statistics->updates += 2;"),
        # Queue payload extents, flash API publication, and the signed 0xaa
        # language marker are all exercised by production-shaped fixtures.
        ("enqueue_ancs",
         "FUN_00086c78(buf, 0, 0x1b4);",
         "FUN_00086c78(buf, 0, 0x1b3);"),
        ("enqueue_dmic",
         "FUN_00086c04(buf, 0x885cc, 200);",
         "FUN_00086c04(buf, 0x885cd, 200);"),
        ("enqueue_file",
         "buf[200] = (unsigned char)param_2;",
         "buf[199] = (unsigned char)param_2;"),
        ("ext_flash_api_init",
         "*param_1 = 0x2e399;", "*param_1 = 0x2e398;"),
        ("getAppLanguageInfofromFlash",
         "(int8_t)0xaa ?", "(int8_t)0xab ?"),
        ("FUN_0004ed8c", "3, 0x000f1574, iVar3",
         "3, 0x000f1575, iVar3"),
        # Early diagnostic exits restore entry r3 before tail-calling the
        # logger.  Reusing the freshly loaded logger-mode word silently loses
        # the caller's fourth argument while preserving call order and CFG.
        ("FUN_0002f4a8",
         "(msg), (ctx), (v2), param_4); else FUN_00019c70((msg), (ctx), (v2), param_4);",
         "(msg), (ctx), (v2), mode_); else FUN_00019c70((msg), (ctx), (v2), mode_);"),
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
        # Display input publication and DMIC startup each have complete
        # production-shaped state families above.  Keep their recovered
        # record fields, queue result classification, device offsets, and
        # atomic flag value as independent permanent negative gates.
        ("display_inputEvent", "command[0] = 5;", "command[0] = 4;"),
        ("display_inputEvent",
         "*(uint16_t *)(command + 2) = 2;",
         "*(uint16_t *)(command + 2) = 3;"),
        ("display_inputEvent", "command[4] = input;", "command[4] = state;"),
        ("display_inputEvent",
         "FUN_000720d0(0x200038c4UL, command, 0, 0) != 0",
         "FUN_000720d0(0x200038c4UL, command, 0, 0) > 0"),
        ("dmic_record_start", "device[0x1059] = 4;",
         "device[0x1058] = 4;"),
        ("dmic_record_start", "0x20007b78UL, 1,",
         "0x20007b78UL, 2,"),
        ("dmic_record_start", "device + 0x104c", "device + 0x1048"),
        ("dmic_record_start", "device + 0x68", "device + 0x64"),
        # Persistence paths: exact key construction/capacity and flash-record
        # field normalization are observable in the complete stack objects
        # and production settings images above.
        ("local_store_write",
         "\"ar_glass_userdata_settings/\"",
         "\"ar_glass_userdata_settingx/\""),
        ("local_store_write", "key + 28, 0, 100",
         "key + 28, 0, 99"),
        ("local_store_write", "key, key_suffix, sizeof(key)",
         "key, key_suffix, sizeof(key) - 1"),
        ("local_store_write", "FUN_0004e374(key, value, length)",
         "FUN_0004e374(key, value, length + 1)"),
        ("load_usr_setting", "0x00134000UL, &record",
         "0x00134004UL, &record"),
        ("load_usr_setting", "record.timeout == 0 ? 400 : record.timeout",
         "record.timeout == 0 ? 399 : record.timeout"),
        ("load_usr_setting", "settings[0xec1] - 1) > 8",
         "settings[0xec1] - 1) > 9"),
        ("load_usr_setting", "record.critical_mode < 2",
         "record.critical_mode < 4"),
        # Reset defaults and runtime publication are stateful straight-line
        # contracts.  Each recovered field/argument is independently visible
        # in the mapped settings object or exact eight-byte wire record.
        ("reset_usr_setting", "settings + 0xfea) = 10;",
         "settings + 0xfea) = 9;"),
        ("reset_usr_setting", "settings + 0x1069) = UINT32_MAX;",
         "settings + 0x1069) = UINT32_MAX - 1;"),
        ("reset_usr_setting", "FUN_00032ef0(0);", "FUN_00032ef0(1);"),
        ("reset_usr_setting", "settings + 0xec1) = 3;",
         "settings + 0xec1) = 4;"),
        ("runtime_info_sync", ".marker = 1,", ".marker = 2,"),
        ("runtime_info_sync",
         "runtime[0], runtime[1], runtime[2], runtime[3], runtime[4]",
         "runtime[0], runtime[1], runtime[2], runtime[4], runtime[3]"),
        ("runtime_info_sync", "&packet, sizeof(packet)",
         "&packet, sizeof(packet) - 1"),
        ("runtime_info_sync", "0x20002fe0UL = 0;",
         "0x20002fe0UL = 1;"),
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
        # The explicit default command fixture must observe the handler's
        # recovered zero result; command-path effects alone are insufficient.
        ("SettingStoreHandler", "    uVar8 = 0;", "    uVar8 = 1;"),
        # Production cases above make each queue geometry, the IPC callback
        # payload length, and the first whitelist identifier length live.
        ("init_dmic_msgq", "0x20007b7cUL,200,8",
         "0x20007b7cUL,201,8"),
        ("init_msgq_ancs", "0x20006a6cUL,0x1b4,10",
         "0x20006a6cUL,0x1b5,10"),
        ("init_msgq_uid", "0x20006a38UL,8,10",
         "0x20006a38UL,9,10"),
        ("ipc0_ept_recv", "(int)(param_1+1), param_2-1",
         "(int)(param_1+1), param_2"),
        ("is_on_whitelist_by_identifier",
         "(const void *)0x000a81d0,param_1,0x15",
         "(const void *)0x000a81d0,param_1,0x14"),
        # Power rails, panel shutdown, queue-slot publication, and persisted
        # settings field selection are independently live in the complete
        # production state families above.
        ("power_for_imu_and_mic",
         "        8, 2, 1);", "        8, 3, 1);"),
        ("power_down_imu_and_mic",
         "        8, 3, 1);", "        8, 2, 1);"),
        ("power_down_panel", ", 8, 1, 1);", ", 8, 1, 0);"),
        ("pull_message", " * 0x1b4 +", " * 0x1b5 +"),
        ("read_sys_settting_from_flash",
         "output[0x56] = record[0x56];",
         "output[0x56] = record[0x55];"),
        # Flash upgrade records preserve param_2's upper half while replacing
        # only the low byte with param_1.  The three-byte UTF-8 decoder keeps
        # both low continuation bits in its middle-byte contribution.
        ("upgradeDashboardStartupModeInfoToFlash",
         "param_2 & 0xffff0000UL", "param_2 & 0xffff00ffUL"),
        ("upgradeQuickNoteDataToFlash",
         "param_2 & 0xffff0000U", "param_2 & 0xffff00ffU"),
        ("utf8_to_unicode",
         "(param_1[1] & 3) << 6", "(param_1[1] & 2) << 6"),
        # Completed click sequences dispatch at the exact 10,001 ms boundary;
        # increasing the threshold suppresses every selected switch arm.
        ("FUN_00028a1c",
         "iVar4 - iVar8 < 0x2711", "iVar4 - iVar8 < 0x2712"),
        # The RTC cases cover the dynamically placed logger record and both
        # register-indirect methods.  Changing either published descriptor
        # metadata or the three-argument enable ABI must remain observable.
        ("FUN_0004c2d4",
         "      3, (const void *)0xf0a68, iVar2",
         "      2, (const void *)0xf0a68, iVar2"),
        ("FUN_0004c2d4",
         "iVar2 = api->enable(puVar1, 8, 1);",
         "iVar2 = api->enable(puVar1, 8, 2);"),
    )
    for function_name, correct, wrong in directed_negative_sources:
        source_path = BASE + "/recon/app/src/" + function_name + ".c"
        source = open(source_path).read()
        assert correct in source, function_name
        verdict = verify("app", function_name, trials_random=0,
                         source_override=source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL", (function_name, verdict)

    # These functions are straight-line or loop-driven and have no CFG
    # selector cases.  Retain a small random budget so their ABI/layout
    # mutations are rejected by executed comparisons, not checked==0.
    app_random_negative_sources = (
        # Straight-line frame contracts: these mutations alter a pointer or
        # first-call scalar that every production invocation exposes.
        ("FUN_0005aba8",
         "FUN_0008016a(frame.work,frame.header,frame.scratch)",
         "FUN_0008016a(frame.header,frame.work,frame.scratch)"),
        ("FUN_0005af8c", "param_5, 0xf4a9e, &frame.object",
         "param_5, 0xf4a9f, &frame.object"),
        ("FUN_0005c80c", "0x5a329,&frame.input",
         "0x5a329,frame.data"),
        ("FUN_0004e484", "0x2000a10cUL", "0x2000a108UL"),
        ("FUN_0004e604",
         "FUN_0004e540(param_1, &local_24)",
         "FUN_0004e540(param_1, (void *)0)"),
        ("FUN_0004e780", "0x0007f211,", "0x0007f210,"),
        ("FUN_0004ee68",
         "FUN_00080d3e(*context, work.common + 4)",
         "FUN_00080d3e(*context, work.common)"),
        # Complete local records and ANCS state writes remain observable after
        # compiler-dependent stack addresses are paired above.
        ("SendPowerInfoToSlave", "request[0] = 4;", "request[0] = 5;"),
        ("SendSystemLanguageInfoToSlave", "local[0] = 5;", "local[0] = 6;"),
        ("ancs_connected",
         "*(volatile unsigned char*)(iVar5+0x367) = 1;",
         "*(volatile unsigned char*)(iVar5+0x367) = 0;"),
        ("ancs_disconnected",
         "*(volatile uint8_t *)(device_state + 0x365u) = 0;",
         "*(volatile uint8_t *)(device_state + 0x365u) = 1;"),
    )
    for function_name, correct, wrong in app_random_negative_sources:
        source_path = BASE + "/recon/app/src/" + function_name + ".c"
        source = open(source_path).read()
        assert correct in source, (function_name, correct)
        verdict = verify("app", function_name, trials_random=4,
                         source_override=source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL" and verdict.get("checked", 0) > 0, \
            (function_name, wrong, verdict)

    # Production display/notification fixtures must observe one concrete
    # output or boundary-ABI mutation in every newly reviewed reconstruction.
    display_negative_sources = (
        ("get_notification_counts_cmd_process",
         "param_3[1] = 0xc9;", "param_3[1] = 0xc8;"),
        ("gui_screen_clear",
         "FUN_0007d6f4(0);", "FUN_0007d6f4(1);"),
        ("gui_area_clear",
         "FUN_000471cc(iVar2 + 0xb90, 0, param_1, param_2, param_3, param_4);",
         "FUN_000471cc(iVar2 + 0xb90, 1, param_1, param_2, param_3, param_4);"),
        ("gui_bmp_bitmap_draw_ex",
         "            return 0;\n        }",
         "            return 1;\n        }"),
        ("gui_bitmps_merge_draw",
         "      return 0;\n    }",
         "      return 1;\n    }"),
        ("sett_init",
         "param_1[1] = 0x22169;", "param_1[1] = 0x22168;"),
        ("simulator_ancs_calendar_schedule_trigger",
         "FUN_00086c78(iVar1 + 0x34, 0, 0x1b4);",
         "FUN_00086c78(iVar1 + 0x34, 0, 0x1b3);"),
        ("spi_master_trans_data_tx_rx",
         "{ param_2, param_3, param_4, param_5 };",
         "{ param_2, param_3, param_4, param_4 };"),
        ("startAudioStreamRecord",
         "buf[4] = 1;", "buf[4] = 2;"),
        ("stopAudioStreamRecord",
         "record[4] = 3;", "record[4] = 2;"),
    )
    for function_name, correct, wrong in display_negative_sources:
        source_path = BASE + "/recon/app/src/" + function_name + ".c"
        source = open(source_path).read()
        assert source.count(correct) == 1, (function_name, correct)
        verdict = verify(
            "app", function_name, trials_random=0,
            source_override=source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL" and verdict.get("checked", 0) > 0, \
            (function_name, wrong, verdict)

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
    # Byte exclusives are an independent execution-model contract.  A paired
    # LDREXB/STREXB must perform one observable byte store; an unpaired STREXB
    # must fail with status one and leave memory unchanged.
    cmsis = ("/Users/freedomcoder/ncs251/modules/hal/cmsis/"
             "CMSIS/Core/Include/cmsis_gcc.h")
    def _byte_exclusive_fixture(value):
        src = ("#include <stdint.h>\n#include \"%s\"\n"
               "uint32_t byte_fixture(volatile uint8_t *p){"
               "uint32_t old=__LDREXB(p);"
               "return old+__STREXB(%du,p);}" % (cmsis, value))
        out, err = recon.compile_func(src, "byte_fixture", 0x61800)
        assert err is None, err
        body, _, size, va = out
        mnemonics = [ins.mnemonic for ins in _md.disasm(body[:size], va)]
        assert "ldrexb" in mnemonics and "strexb" in mnemonics, mnemonics
        return out
    ab, at, asz, ava = _byte_exclusive_fixture(0x5a)
    cb, ct, csz, cva = _byte_exclusive_fixture(0x5a)
    v = emu.compare(ab + at, ava, asz, cb + ct, cva, csz,
                    trials=1, nptr=1)
    assert v["pass"], v
    cb, ct, csz, cva = _byte_exclusive_fixture(0x5b)
    v = emu.compare(ab + at, ava, asz, cb + ct, cva, csz,
                    trials=1, nptr=1)
    assert not v["pass"], v
    unpaired = ("#include <stdint.h>\n#include \"%s\"\n"
                "uint32_t byte_fixture(volatile uint8_t *p){"
                "return __STREXB(0x5au,p);}" % cmsis)
    plain = ("#include <stdint.h>\n"
             "uint32_t byte_fixture(volatile uint8_t *p){"
             "(void)p;return 1;}")
    ao, ae = recon.compile_func(unpaired, "byte_fixture", 0x61800)
    bo, be = recon.compile_func(plain, "byte_fixture", 0x61800)
    assert ae is None and be is None, (ae, be)
    ab, at, asz, ava = ao; cb, ct, csz, cva = bo
    v = emu.compare(ab + at, ava, asz, cb + ct, cva, csz,
                    trials=1, nptr=1)
    assert v["pass"], v
    # The two former net blockers retain one production-case negative gate:
    # arithmetic must consume the multiplier, and the inherited-monitor lock
    # acquisition must store the recovered zero byte.
    blocker_negative_sources = (
        ("FUN_01008650",
         "(uint64_t)left[i] * right[j]",
         "(uint64_t)left[i] + right[j]"),
        ("FUN_0102d1c0",
         "__STREXB(0, lock)",
         "__STREXB(1, lock)"),
    )
    for function_name, correct, wrong in blocker_negative_sources:
        source_path = BASE + "/recon/net/src/" + function_name + ".c"
        source = open(source_path).read()
        assert source.count(correct) == 1, (function_name, correct)
        verdict = verify(
            "net", function_name, trials_random=0,
            source_override=source.replace(correct, wrong, 1))
        assert verdict["status"] == "FAIL" and verdict.get("checked", 0) > 0, \
            (function_name, wrong, verdict)
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
