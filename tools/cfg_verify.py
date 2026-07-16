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

# Direct callees absent from, or ambiguous in, the decompiler catalog.  These
# are reviewed AAPCS argument counts; registers above the true arity are caller
# scratch and must not create false mismatches merely because GCC leaves a
# different stale value in them.
CALL_ARITY_OVERRIDES = {
    ("app", 0x0000db4c): 2,
    ("app", 0x00076d8c): 1,
    ("app", 0x00076cec): 2,
    ("app", 0x00058f34): 3,
    ("app", 0x0005f5d0): 2,
    ("app", 0x000821a4): 2,
    ("app", 0x0004a46c): 2,
    ("app", 0x00016574): 1,
    ("app", 0x00074d74): 1,  # work submission consumes queue node only
    ("app", 0x00086534): 2,  # object initializer consumes object and mode
    ("app", 0x000851ca): 2,  # pin-mode selector consumes pin and mode only
    ("app", 0x000850d8): 1,  # one-tick busy-wait; r1-r3 are stale caller scratch
    ("app", 0x00084b14): 2,  # controller toggle consumes handle and enable only
    ("net", 0x0102583c): 1,
    ("net", 0x01037e10): 2,
    ("net", 0x0102e460): 2,
    ("net", 0x010345f4): 1,
    ("net", 0x01034650): 1,  # channel-index mapper consumes only the index
    ("net", 0x0102e1fc): 1,  # notification consumes the updated object only
    ("net", 0x01032988): 0,
    ("net", 0x0103b224): 2,
    ("net", 0x010374dc): 0,
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
    ("app", 0x000638dc): 2,  # timer-head notification: timestamp and flags
    ("net", 0x01008d00): 2,  # assertion endpoint consumes module and line
    ("net", 0x010256dc): 2,  # fatal endpoint consumes module and line
    ("net", 0x010250d0): 1,  # scheduler operation selector
    ("net", 0x0100dfbc): 2,  # formatter body consumes only buffer and type
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
    ("app", 0x4bc8c): 0x180,
    # NCS mpsc_pbuf_claim internal entry; code ends at 0x4bfae and the owned
    # checked-lock assertion literals end immediately before 0x4bfc8.
    ("app", 0x4beb8): 0x110,
}

# Reviewed ABI returns where the generic "last s0/d0 writer" heuristic sees
# an internal floating-point temporary rather than the actual function result.
RETURN_KIND_OVERRIDES = {
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
    ("app", 0x00055710): {0: 0x00080001},
}

# Narrow reviewed contracts for external callees that initialize caller-owned
# stack objects.  Entries are ordinal -> (argument register, offset, bytes).
REVIEWED_ORACLE_MEMORY_WRITES = {
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
    ("app", 0x000545f0): {1: [(0, 12, bytes(4))]},
    # Matrix conversion writes four result words through its second argument.
    ("app", 0x0007d968): {2: [(1, 0, bytes(16))]},
    # Formatter advances a caller-owned cursor in the descriptor.  Anchor it
    # to the reviewed output buffer for both stack layouts.
    ("app", 0x00077914): {0: [(1, 0, (emu.SCRATCH + 0x2400).to_bytes(4, "little"))]},
}
REVIEWED_STACK_POINTER_CALLS = {
    # Small compiler-owned request/descriptor frames.  Only the listed call
    # arguments are normalized; scalar registers and complete pointee bytes
    # remain part of the strengthened comparison.
    ("app", 0x00047ba8): {1: {0}, 2: {1}},
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
# (original_offset, candidate_offset).  The harness seeds the same symbolic
# full word at both locations, then still compares all full-width effects.
REVIEWED_PAIRED_STACK_INITIAL_WORDS = {
    # Two mapping.tag words: original frame is eight bytes deeper because it
    # saves r8/r9.  Each path overwrites only the low byte before publishing
    # the complete word to event+0x10.
    ("app", 0x00026338): [(-44, -36), (-36, -28)],
}

# Reviewed addressable stack objects.  Each tuple is
# (semantic identity, original entry-SP offset, candidate entry-SP offset,
# byte size).  Unlike the older argument-position normalization, this maps
# only the declared half-open regions and compares identity, interior offset,
# declared size, and complete bytes at every external call boundary.
REVIEWED_PAIRED_STACK_OBJECTS = {
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
}

# Arguments beyond these widths are diagnostics-only stale registers on the
# reviewed caller path.  The source still spells all production arguments;
# differential call traces compare only the callee-consumed semantic prefix.
REVIEWED_TARGET_CALL_ARITIES = {
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
    # ble_process_put_req post_to_host callback (ctx+0x0c).
    ("app", 0x0001a75c): {0x00080000: 2, 0x0007c1dc: 2},
    ("net", 0x01035830): {0x00080000: 1},
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
    ("app", 0x0003af78): _dashboard_directed_states(),
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

REVIEWED_STATE_CASES = {
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


REVIEWED_ORACLE_CASES = {
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
    # Persistent ANCS worker, production mode 1: after five initialization
    # calls, accessor and delay alternate forever. Every accessor returns the
    # same stable global object rather than a changing fuzz pointer.
    ("app", 0x00019718): [
        ({0: emu.SCRATCH + 0x0200},
         [(emu.SCRATCH + 0x0200, bytes(0x240)),
          (emu.SCRATCH + 0x1000, b"\x00\x01" + bytes(0x105c)),
          (0x2000230c, bytes(4)), (0x20007554, bytes(4))],
         {i: {0: emu.SCRATCH + 0x1000} for i in range(5, 205, 2)})
        ,({0: emu.SCRATCH + 0x0200},
          [(emu.SCRATCH + 0x0200, bytes(0x240)),
           (emu.SCRATCH + 0x1000, b"\x00\x08" + bytes(0x105c)),
           (0x2000230c, bytes(4)), (0x20007554, bytes(4))],
          {i: {0: emu.SCRATCH + 0x1000}
           for base in range(5, 205, 3) for i in (base, base + 1)})
        ,({0: emu.SCRATCH + 0x0200},
          [(emu.SCRATCH + 0x0200, bytes(0x240)),
           (emu.SCRATCH + 0x1000, bytes(0x1060)),
           (0x2000230c, bytes(4)), (0x20007554, bytes(4))],
          {i: {0: emu.SCRATCH + 0x1000}
           for base in range(5, 205, 4) for i in (base, base + 1, base + 2)})
        ,*[
          ({0: emu.SCRATCH + 0x0200},
           [(emu.SCRATCH + 0x0200, bytes(0x240)),
            (emu.SCRATCH + 0x1000, bytes(0x105c) + b"\x80\x00"),
            (0x20006aac, (0x12345678).to_bytes(4, "little") + bytes([event_count]) + bytes(3)),
            (0x2000230c, bytes(4)), (0x20007554, bytes(4))],
           {**{i: {0: emu.SCRATCH + 0x1000}
               for base in range(5, 205, 8) for i in (base, base + 1, base + 2)},
            **{base + 4: {0: 0} for base in range(5, 205, 8)}})
          for event_count in (1, 2)
        ]
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
        ({}, [], {0: {0: 0}, 1: {0: 0}}),
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

# Reviewed hard-float arguments, expressed as raw IEEE-754 words keyed by
# s-register index.  These accompany the state/oracle cases above.
REVIEWED_FP_CASES = {
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
    prefix_first = "CFG_VERIFY_PREFIX_FIRST" in txt[:400]
    extra_cflags = []
    if "CFG_VERIFY_NO_IF_CONVERSION" in txt[:400]:
        extra_cflags += ["-fno-if-conversion", "-fno-if-conversion2"]
    extra_cflags = extra_cflags or None
    am = re.search(r'CFG_VERIFY_CALL_ARITIES=([0-4](?:,[0-4])*)', txt[:1000])
    call_arities = [int(x) for x in am.group(1).split(',')] if am else None
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
    if (core, va) == ("app", 0x0006c778):
        call_arities = [3] + [1] * 64 + [4, 4]
        call_float_arities = [0] + [1] * 64 + [0, 0]
        call_return_kinds = ["void"] + ["f32"] * 64 + ["void", "void"]
    pm = re.search(r'CFG_VERIFY_PREFIX_K=(\d+)', txt[:1000])
    prefix_k = int(pm.group(1)) if pm else 200
    oracle_memory_writes = REVIEWED_ORACLE_MEMORY_WRITES.get((core, va))
    oracle_memory_copies = ({0: [(0, 1, 2)]}
                            if (core, va) == ("app", 0x0006c778) else None)
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
    nptr_modes = tuple(dict.fromkeys(
        n for n in (max(1, required_nptr), 2, 1, 3, 4) if n >= required_nptr))
    # Both cores use Zephyr's ARCH_EXCEPT(4): clear BASEPRI, load reason 4,
    # SVC #2. The SVC is a production-noreturn runtime exception even though
    # the compiler emits a defensive BX LR after it.
    terminal_targets = ({0x01008d00, 0x0100ebb8, 0x01014884, 0x01016828, 0x010256dc, 0x01039bb0}
                        if core == "net" else {0x00050af8, 0x0007e2ec})
    target_call_arities = dict(ctx["call_arity_by_target"])
    target_call_arities.update(REVIEWED_TARGET_CALL_ARITIES.get((core, va), {}))
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
                            call_float_arity_by_target=ctx["call_float_arity_by_target"],
                            call_return_kind_by_target=ctx["call_return_kind_by_target"],
                            oracle_memory_writes=oracle_memory_writes,
                            oracle_memory_copies=oracle_memory_copies,
                            normalized_stack_pointer_calls=normalized_stack_pointer_calls,
                            candidate_direct_target_map=candidate_direct_target_map,
                            paired_stack_initial_words=paired_stack_initial_words,
                            paired_stack_objects=paired_stack_objects,
                            initial_xpsr_overrides=initial_xpsr_overrides)
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
                            call_float_arity_by_target=ctx["call_float_arity_by_target"],
                            call_return_kind_by_target=ctx["call_return_kind_by_target"],
                            oracle_memory_writes=oracle_memory_writes,
                            oracle_memory_copies=oracle_memory_copies,
                            normalized_stack_pointer_calls=normalized_stack_pointer_calls,
                            candidate_direct_target_map=candidate_direct_target_map,
                            paired_stack_initial_words=paired_stack_initial_words,
                            paired_stack_objects=paired_stack_objects,
                            initial_xpsr_overrides=initial_xpsr_overrides)
            # A no-return retry is only an inconclusive-run recovery.  Never
            # replace a concrete primary mismatch with a prefix-mode result;
            # doing so discards the most useful diagnostic and can hide faults.
            if (not v.get("pass") and v.get("checked") == 0 and
                    not v.get("mismatches")):
                v = emu.compare(orig, va, size, cb + ct, cva, cs, code_base=ctx["cb"],
                                trials=trials, nptr=nptr, ret_kind=rk, no_return=True,
                                arg_overrides=ovs, memory_overrides=movs,
                                absolute_memory_overrides=absolute_movs,
                                pointer_read_transitions=pointer_read_transitions,
                                terminal_targets=terminal_targets,
                                oracle_overrides=oracle_overrides, call_arities=call_arities,
                                call_float_arities=call_float_arities,
                                call_return_kinds=call_return_kinds,
                                fp_arg_overrides=fp_arg_overrides,
                                call_arity_by_target=target_call_arities,
                                call_float_arity_by_target=ctx["call_float_arity_by_target"],
                                call_return_kind_by_target=ctx["call_return_kind_by_target"],
                                oracle_memory_writes=oracle_memory_writes,
                                oracle_memory_copies=oracle_memory_copies,
                                normalized_stack_pointer_calls=normalized_stack_pointer_calls,
                                candidate_direct_target_map=candidate_direct_target_map,
                                paired_stack_initial_words=paired_stack_initial_words,
                                paired_stack_objects=paired_stack_objects,
                                initial_xpsr_overrides=initial_xpsr_overrides)
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
    def _stack_object_fixture(pad_size, second=7, pointer_offset=0):
        src = ("extern void sink(void*); void fixture(void){"
               "volatile unsigned char pad[%d]; volatile unsigned char object[4];"
               "object[0]=42; object[1]=%d; object[2]=9; object[3]=11;"
               "sink((void*)(object+%d));"
               "pad[0]=0;}" % (pad_size, second, pointer_offset))
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
    # A too-small reviewed extent cannot normalize a pointer at its boundary.
    ob, ot, osz, ova = _stack_object_fixture(1, pointer_offset=3)
    cb, ct, csz, cva = _stack_object_fixture(64, pointer_offset=3)
    v = emu.compare(ob + ot, ova, osz, cb + ct, cva, csz, trials=1,
                    nptr=0, ret_kind="void", call_arities=[1],
                    paired_stack_objects=[("fixture-object", -12, -76, 3)])
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
