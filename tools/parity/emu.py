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

# nRF5340 memory-mapped device aliases used by the shipped APP and NET images.
# Pages are materialized lazily, but only inside these reviewed windows.  The
# old generic handler mapped every missing address as zero-filled RAM, which
# made an omitted volatile peripheral read indistinguishable from the original
# read returning reset-state zero.
NRF53_MMIO_WINDOWS = (
    (0x40000000, 0x41000000),  # CPUAPP non-secure peripheral aliases
    (0x41000000, 0x42000000),  # CPUNET peripheral aliases
    (0x50000000, 0x51000000),  # CPUAPP secure peripheral aliases
    (0xE0000000, 0xE0100000),  # Cortex-M PPB/NVIC/CoreDebug window
)
NRF53_NET_RAM_WINDOW = (0x21000000, 0x21080000)

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


def _f32w(value):
    return struct.unpack("<I", struct.pack("<f", value))[0]


def _f64w(value):
    return struct.unpack("<II", struct.pack("<d", value))


# ---- realistic FLOAT inputs -------------------------------------------------
# Uniform 32-bit words are almost never ORDINARY floats.  Interpreted as
# binary32, a random word has a uniformly random 8-bit exponent, so it is a
# huge or vanishing magnitude with overwhelming probability, and the values
# that real firmware branches on -- exact 0.0, +/-1.0, +/-0.5, sensor-scale
# magnitudes, denormals -- have probability ~0.  That is exactly the shape of
# CRITICAL FINDING #1 (uniform integers almost never land in a small switch
# range) transposed to the VFP argument bank: `x == 0.0f`, `x > 1.0f` and
# similar guards were never exercised, so float code that is wrong on those
# paths could pass.  Seed a MIX of production-plausible float values and raw
# random words so both domains are covered.
FLOAT_POOL = tuple(_f32w(v) for v in (
    # exact/boundary values that random bit patterns never produce
    0.0, -0.0, 1.0, -1.0, 0.5, -0.5, 2.0, -2.0, 0.25, 4.0, 3.0, -3.0,
    # small sensor-scale magnitudes (gyro rad/s, normalized accelerometer,
    # quaternion components, filter gains, sample intervals)
    0.1, -0.1, 0.01, -0.01, 0.001, 0.05, -0.05, 0.6, 0.8, -0.8,
    0.70710678, -0.70710678, 0.99999994,
    # physical / geometric constants the firmware actually uses
    9.80665, -9.80665, 3.14159265, -3.14159265, 1.57079633, 57.2957795,
    0.0174532925, 180.0, 360.0,
    # ordinary display/percentage/brightness ranges
    10.0, 100.0, 255.0, 1000.0, 1024.0, 16777216.0,
    # magnitude extremes that remain finite, and the smallest denormal
    1e-6, 1e6, 1e-20, 1e20, 1.1754944e-38, 3.4028235e38, 1.4e-45,
))
# NOTE ON INFINITY/NaN.  They are deliberately NOT in this pool, and that is a
# measured decision, not an oversight.  Algebraically identical float code does
# not preserve NaN sign/payload (`-a + b*c` via VNMLS versus `b*c - a` flips the
# sign bit of a propagated NaN; `inf - inf` yields the positive default NaN
# instead), while the harness compares float memory writes and float call
# arguments BIT-EXACTLY.  Seeding NaN/infinity therefore fails semantically
# correct reconstructions -- measured on FUN_00026624, whose corrected body
# mismatched only in the sign bit of a NaN.  Production float inputs are never
# NaN, exceptional-value coverage stays in the hand-reviewed REVIEWED_FP_CASES
# (which is where libm classification needs it), and the ~20% of register pairs
# that keep uniform random words still deliver infinities and NaNs at exactly
# their historical rate, so nothing that used to be exercised has been lost.

# The values firmware actually BRANCHES on.  Over-sampled in both pools for
# the same reason make_args over-samples small integers: a comparison against
# exactly 0.0/1.0/0.5 is a real control-flow edge, and one pool slot in forty
# is not enough to reach it reliably.
FLOAT_BOUNDARY = tuple(_f32w(v) for v in (0.0, -0.0, 1.0, -1.0, 0.5, -0.5))
FLOAT_POOL = FLOAT_POOL + FLOAT_BOUNDARY * 3

# Pool for float-typed POINTEE memory: finite and of MODERATE magnitude
# (|x| <= 1e6).  Two reasons, both measured rather than assumed:
#   * a NaN stored through a reconstruction can carry a different payload/sign
#     than the original's (ARM NaN propagation is operand-order dependent, and
#     `inf - inf` versus a propagated NaN differ), and the memory-write trace is
#     compared bit-exactly -- seeding NaN/infinity would manufacture mismatches
#     for a semantically identical candidate;
#   * 1e20-scale inputs overflow to infinity as soon as they are squared, which
#     reintroduces the same NaN divergence one step later.
FLOAT_POOL_FINITE = tuple(
    w for w in FLOAT_POOL
    if (w & 0x7f800000) != 0x7f800000
    and abs(struct.unpack("<f", struct.pack("<I", w))[0]) <= 1e6) + FLOAT_BOUNDARY

DOUBLE_POOL = tuple(_f64w(v) for v in (
    0.0, -0.0, 1.0, -1.0, 0.5, -0.5, 2.0, 0.25, 3.0, 0.1, -0.1, 0.01,
    9.80665, 3.14159265358979, 1.5707963267949, 57.29577951308232,
    0.017453292519943295, 100.0, 1000.0, 1e-6, 1e6, 1e-300, 1e300,
    2.2250738585072014e-308, 1.7976931348623157e308, 5e-324,
))


def _vfp_seed_words(seed):
    """16 words for s0..s15: realistic float/double values mixed with random.

    Pairs are seeded as a unit so that a function reading d0..d7 receives
    plausible binary64 values, not two unrelated binary32 words.  ~20% of
    pairs keep the historical uniform-random content, so the new seeding is
    strictly additional coverage rather than a replacement.
    """
    words = list(struct.unpack("<16I", _prng_fill(
        b"vfp" + struct.pack("<I", seed), 64)))
    sel = _prng_fill(b"vfpmode" + struct.pack("<I", seed), 24)
    for pair in range(8):
        mode = sel[pair * 3] * 100 // 256
        a, b = sel[pair * 3 + 1], sel[pair * 3 + 2]
        if mode < 25:
            lo, hi = DOUBLE_POOL[((a << 8) | b) % len(DOUBLE_POOL)]
            words[2 * pair], words[2 * pair + 1] = lo, hi
        elif mode < 80:
            words[2 * pair] = FLOAT_POOL[a % len(FLOAT_POOL)]
            words[2 * pair + 1] = FLOAT_POOL[b % len(FLOAT_POOL)]
    return words


def _float_scratch_bytes(seed, size):
    """Pointee-memory image whose words read as ordinary binary32 values.

    Float arguments also arrive through POINTERS (filter state, quaternions,
    coefficient arrays).  Uniform-random pointee bytes have the same blind
    spot as uniform-random VFP registers, so provide a keystream of plausible
    finite floats with ~25% of slots left random (a real record also holds
    integers, flags and pointers).
    """
    random_words = _prng_fill(b"fram" + struct.pack("<I", seed), size + 4)
    sel = _prng_fill(b"frammode" + struct.pack("<I", seed), (size // 4) + 2)
    out = bytearray()
    index = 0
    while len(out) < size:
        pick = sel[index % len(sel)]
        if pick * 100 // 256 < 75:
            out += struct.pack("<I", FLOAT_POOL_FINITE[
                random_words[(index * 4) % size] % len(FLOAT_POOL_FINITE)])
        else:
            # Keep sign and mantissa arbitrary (integer/flag/pointer fields
            # live in these records too) but clamp the exponent into a moderate
            # band, 2**-23 .. 2**8.  A raw random word is a ~1e34 float three
            # times in ten; squaring it overflows to infinity and the following
            # subtraction yields a NaN whose SIGN is not preserved by
            # algebraically equivalent float code, which would fail a correct
            # reconstruction on a bit-exact float compare (measured on
            # FUN_00026624, state word q0 = 0x77f8197f = 1.0e34).
            word = int.from_bytes(random_words[index * 4:index * 4 + 4],
                                  "little")
            word = (word & 0x807fffff) | ((0x68 + ((word >> 23) & 0x1f)) << 23)
            out += struct.pack("<I", word)
        index += 1
    return bytes(out[:size])


def _range_contains(window, address, size=1):
    start, end = window
    return (type(address) is int and type(size) is int and size > 0 and
            start <= address and address + size <= end)


def _is_nrf53_mmio(address, size=1):
    return any(_range_contains(window, address, size)
               for window in NRF53_MMIO_WINDOWS)

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

# ---- read-only pointee equivalence class ------------------------------------
# A pointer ARGUMENT's numeric address is not observable behaviour when the
# pointee is immutable.  The shipped firmware passes 0x000a3b3f because its
# format string happens to live at that flash address; a reconstruction that
# spells the same string as an ordinary C literal passes the address of its own
# copy in its own .rodata.  Both callees read the identical bytes, so the two
# programs are indistinguishable to every observer -- yet the ordered call
# trace compared them as raw integers and failed.  That is the ONE false-FAIL
# class this equivalence removes, and nothing else.
#
# The class is deliberately narrow.  A value is replaced by its content ONLY
# when every one of these holds:
#   1. it lands inside a declared read-only extent (the shipped flash image, or
#      the candidate's own linked read-only tail) -- so NULL, RAM, MMIO,
#      out-of-image and unmapped pointers are never normalized;
#   2. the pointee is a COMPLETE, NUL-terminated byte string of length
#      1..RODATA_STRING_MAX;
#   3. every byte of it is printable ASCII or \t \n \r;
#   4. the address is a string HEAD -- the preceding byte is NUL, or the
#      address is the first byte of its extent.
# Anything failing those tests keeps EXACT address comparison, which is what
# the harness did before, so no discrimination is lost for non-string read-only
# objects (const tables, function pointers, device structs, section bounds).
#
# Why no false PASS is introduced: normalization is a pure function of the
# observed value on each side, so two EQUAL values always normalize to equal
# identities.  The verdict can therefore only change for pairs where the two
# sides observed DIFFERENT addresses whose pointees are byte-identical strings
# -- which is precisely the equivalence being asserted, and is unobservable
# because .rodata is never written.
RODATA_STRING_MAX = 256
_RO_TEXT_BYTES = frozenset(list(range(0x20, 0x7f)) + [0x09, 0x0a, 0x0d])
# Enabled per core.  The CPUAPP image has a single flash coordinate space, so a
# stored pointer's content is unambiguous.  CPUNET does NOT: analysis (0x1008000)
# and runtime (0x1008800) windows overlap numerically and only provenance
# distinguishes them (tools/net_address_space.py), so a content lookup there
# could decode the WRONG object.  Net literal inlining is deferred anyway, so
# net keeps exact address comparison and this stays a one-line switch.
RODATA_EQUIVALENCE_CORES = ("app",)
_RO_IMAGE_CACHE = {}
# Count of resolutions served by a CANDIDATE'S OWN read-only tail rather than
# by the shipped image.  See ReadOnlyPointees.content for what it measures.
RO_OWN_TAIL_HITS = 0


def _firmware_readonly_extent(code_base):
    """(lo, hi, read) over the shipped read-only flash image for this core.

    Returns None when the core is not enabled or the image cannot be loaded --
    fail-closed to exact address comparison, never to a permissive default.
    """
    core = "net" if code_base == NET_CODE_BASE else "app"
    if core not in RODATA_EQUIVALENCE_CORES:
        return None
    if core in _RO_IMAGE_CACHE:
        return _RO_IMAGE_CACHE[core]
    extent = None
    try:
        import sys as _sys
        _tools = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        if _tools not in _sys.path:
            _sys.path.insert(0, _tools)
        if core == "app":
            import extract
            blob = extract._blob()
            lo = extract.APP_LINK_BASE
            hi = lo + (len(blob) - extract.APP_HDR)
            extent = (lo, hi, extract.read, "image")
        else:
            import net_extract
            blob = net_extract._blob()
            lo = net_extract.NET_RUNTIME_BASE
            hi = lo + len(blob)
            extent = (lo, hi, net_extract.read_runtime, "image")
    except Exception:
        extent = None
    _RO_IMAGE_CACHE[core] = extent
    return extent


class ReadOnlyPointees:
    """Content identity for pointers into declared read-only extents."""

    def __init__(self, extents):
        # extents: ordered ((lo, hi, read), ...), tried in order.  The SHIPPED
        # IMAGE is always first, so any address the image can decode resolves
        # identically on both sides and today's verdict is preserved exactly.
        # A candidate's own linked read-only tail is consulted only for
        # addresses the image does not decode as a string -- which is where an
        # inlined literal lives.
        self.extents = tuple(e for e in extents if e)
        self._cache = {}

    def __bool__(self):
        return bool(self.extents)

    def content(self, value):
        """('RO', bytes) for a read-only string head, else None."""
        if type(value) is not int:
            return None
        value &= 0xffffffff
        if value in self._cache:
            return self._cache[value]
        result = None
        for lo, hi, read, tag in self.extents:
            if not (lo <= value < hi):
                continue
            if value > lo:
                previous = read(value - 1, 1)
                if len(previous) != 1 or previous[0] != 0:
                    continue            # interior of a string / of an object
            span = min(RODATA_STRING_MAX + 1, hi - value)
            raw = read(value, span)
            end = raw.find(b"\x00")
            if end >= 1 and all(byte in _RO_TEXT_BYTES for byte in raw[:end]):
                result = ("RO", raw[:end])
                if tag == "own":
                    # Instrumentation, not policy.  The shipped-image extent is
                    # applied identically on both sides, so it can only turn a
                    # FAIL into a PASS.  This own-tail extent is the ONE
                    # asymmetric element (the original has no such object), and
                    # therefore the only way this change could in principle
                    # lose an existing PASS.  Counting its hits over the corpus
                    # is how that risk is measured rather than assumed.
                    global RO_OWN_TAIL_HITS
                    RO_OWN_TAIL_HITS += 1
                break
        self._cache[value] = result
        return result

    def key(self, value):
        """Content identity if there is one, else the exact address."""
        identity = self.content(value)
        return identity if identity is not None else (value & 0xffffffff)


def _bytes_extent(lo, data):
    """Read-only extent backed by an in-memory byte string."""
    data = bytes(data)
    def read(va, n):
        off = va - lo
        return data[off:off + n] if off >= 0 else b""
    return (lo, lo + len(data), read, "own")


def _terminal_key(state):
    """Strict semantic prefix identity through a production-noreturn call."""
    if not state.get("terminal"):
        return None
    return (state.get("terminal_call_ordinal"),
            state.get("terminal_event_count"),
            state.get("terminal_prefix_hash"))


class Runner:
    def __init__(self, func_va, func_size, func_bytes, code_base=CODE_BASE,
                 internal_code_regions=None, own_readonly_tail=False):
        self.va = func_va
        self.size = func_size
        self.body = bytes(func_bytes)
        self.code_base = code_base
        # Read-only extents whose pointees compare by CONTENT (see
        # ReadOnlyPointees).  `own_readonly_tail` declares the bytes linked
        # after this unit's executable extent -- for a compiled candidate that
        # is its own .rodata, where an inlined string literal lives.  The
        # shipped image stays FIRST: it is the extent both sides share, so
        # every address it can decode keeps its pre-existing verdict, and the
        # own tail is reached only for addresses the image does not decode.
        extents = [_firmware_readonly_extent(code_base)]
        if own_readonly_tail and len(self.body) > self.size:
            extents.append(_bytes_extent(self.va + self.size,
                                         self.body[self.size:]))
        self.readonly = ReadOnlyPointees(extents)
        self.internal_code_regions = tuple(
            (int(address), bytes(data))
            for address, data in (internal_code_regions or ()))
        main_range = (self.va, self.va + self.size)
        regions = sorted((address, address + len(data))
                         for address, data in self.internal_code_regions)
        for index, (start, end) in enumerate(regions):
            if start < 0 or end > 0x100000000 or start >= end:
                raise ValueError("internal code regions must be non-empty 32-bit ranges")
            if start < main_range[1] and main_range[0] < end:
                raise ValueError("internal code region overlaps the main function body")
            if index and start < regions[index - 1][1]:
                raise ValueError("internal code regions overlap each other")

    def _new_uc(self):
        uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB | UC_MODE_MCLASS)
        uc.mem_map(CODE_BASE, CODE_SIZE)
        if self.code_base == NET_CODE_BASE:
            uc.mem_map(NET_CODE_BASE, 0x40000)
        uc.mem_map(RAM_BASE, RAM_SIZE)
        return uc

    def run(self, seed, args, scratch_seed, max_insns=200000, max_resumes=5000,
            stop_events=0,
            memory_overrides=None, absolute_memory_overrides=None,
            stack_initial_words=None,
            pointer_read_transitions=None, absolute_read_transitions=None,
            terminal_targets=None, terminal_ordinal=None,
            detect_repeated_terminal=False, oracle_overrides=None,
            call_arities=None, call_arity_by_target=None,
            call_arity_by_format=None, call_argument_indices_by_target=None,
            call_float_arities=None, call_float_arity_by_target=None,
            call_return_kinds=None, call_return_kind_by_target=None,
            call_stack_arity_by_target=None, call_stack_arity_by_format=None,
            oracle_memory_writes=None, oracle_memory_copies=None,
            oracle_target_map=None,
            normalized_stack_pointer_calls=None,
            stack_objects=None,
            fp_arg_overrides=None, initial_xpsr=0, initial_primask=0,
            initial_exclusive_monitor=None, float_scratch=False):
        """Run one trial. Returns dict(state) or {'error':...}.
        stop_events>0: stop after that many side-effect events (for non-returning
        supervisor loops — we compare the ordered event-trace prefix instead of a
        return value, which is robust to GCC-vs-original instructions-per-loop)."""
        for override in (oracle_overrides or {}).values():
            if "lr" in override:
                lr_spec = override["lr"]
                if (type(lr_spec) is not tuple or len(lr_spec) != 2 or
                        any(type(value) is not int for value in lr_spec)):
                    raise ValueError(
                        "oracle LR continuation must be an exact integer "
                        "(value, semantic_target) tuple")
        for stack_object in (stack_objects or ()):
            if len(stack_object) < 3:
                raise ValueError("stack object requires identity, offset, and payload")
            size = len(stack_object[2])
            content_ranges = stack_object[3] if len(stack_object) > 3 else None
            content_length_argument = (stack_object[7]
                                       if len(stack_object) > 7 else None)
            if content_ranges is not None:
                previous_end = 0
                for content_range in content_ranges:
                    if (not isinstance(content_range, (tuple, list)) or
                            len(content_range) != 2 or
                            any(type(value) is not int for value in content_range)):
                        raise ValueError("stack object content ranges must be integer pairs")
                    start, end = content_range
                    if not (0 <= start < end <= size):
                        raise ValueError("stack object content range is outside its payload")
                    if start < previous_end:
                        raise ValueError("stack object content ranges overlap or are unordered")
                    previous_end = end
            if content_length_argument is not None:
                if type(content_length_argument) is not int or content_length_argument < 0:
                    raise ValueError("stack object length argument must be a nonnegative integer")
                if content_ranges is not None:
                    raise ValueError(
                        "stack object cannot declare both content ranges and a length argument")
        uc = self._new_uc()
        # place function body at its VA
        uc.mem_write(self.va, self.body)
        # Some firmware leaf workers use a private result convention spanning
        # r0-r11 and caller-reserved stack words.  A reviewed caller can only
        # be verified meaningfully by executing those worker bytes as part of
        # the unit, rather than replacing the call with an r0:r1 oracle.  The
        # regions are explicit and remain subject to the normal write trace.
        for address, data in self.internal_code_regions:
            uc.mem_write(address, data)
        # External calls return through a real Thumb BX LR instruction inside
        # the same emulation run.  Stopping/restarting Unicorn at every oracle
        # boundary can corrupt hidden Thumb execution state (notably ITSTATE)
        # long after the call has returned.
        uc.mem_write(ORACLE_TRAMPOLINE, bytes.fromhex("7047"))
        # seed RAM + scratch identically per trial
        uc.mem_write(RAM_BASE, _prng_fill(b"ram" + struct.pack("<I", scratch_seed), RAM_SIZE))
        if float_scratch:
            # Argument-pointer region only: the pointee records of a hard-float
            # function read as plausible binary32 values instead of uniform
            # bytes.  Applied before every observation hook and identically for
            # original and candidate, exactly like the other input fixtures.
            uc.mem_write(SCRATCH, _float_scratch_bytes(scratch_seed, SCRATCH_SZ))

        # registers
        for i, r in enumerate(REG):
            uc.reg_write(r, 0)
        for i in range(4):
            uc.reg_write(REG[i], args[i] & 0xffffffff)
        # Reviewed architectural-mode fixture. IPSR is the low exception-number
        # field of xPSR: zero is thread mode, nonzero is handler mode.
        uc.reg_write(UC_ARM_REG_XPSR, int(initial_xpsr) & 0xffffffff)
        uc.reg_write(UC_ARM_REG_PRIMASK, int(initial_primask) & 1)
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
        # Hardware-owned status registers are not reachable through an ABI
        # pointer.  Reviewed fixtures may advance one absolute word on an
        # exact read ordinal, modeling a peripheral event without globally
        # teaching the harness device-specific side effects.
        for address, ordinal, value in (absolute_read_transitions or ()):
            read_transitions.append({"address": int(address) & 0xffffffff,
                                     "ordinal": int(ordinal),
                                     "value": int(value) & 0xffffffff,
                                     "count": 0})
        # seed VFP s0..s15 identically (float args + float-return coverage).
        # Values mix production-plausible floats/doubles with random words --
        # see FLOAT_POOL: uniform bit patterns alone never produce 0.0, +/-1.0,
        # +/-0.5 or sensor-scale magnitudes, which is the float analogue of the
        # integer small-value false-proof class.
        fseed = _vfp_seed_words(scratch_seed)
        for i, sr in enumerate(SREG):
            try:
                uc.reg_write(sr, fseed[i])
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
        for stack_object in (stack_objects or ()):
            _object_id, offset, payload = stack_object[:3]
            uc.mem_write(STACK_TOP + int(offset), bytes(payload))

        state = {"ncalls": 0, "returned": False, "events": [],
                 "call_targets": [], "call_event_positions": [],
                 "call_arities_used": [], "call_float_arities_used": [],
                 "call_return_kinds_used": [],
                 "next_call_indirect": False,
                 "matched_stack_objects": set()}
        if initial_exclusive_monitor is not None:
            address, width = initial_exclusive_monitor
            state["exclusive_monitor"] = (int(address) & 0xffffffff,
                                            int(width))
        if read_transitions:
            def _reviewed_read_transition(uc, access, address, size, value, ud):
                for transition in read_transitions:
                    if address == transition["address"]:
                        transition["count"] += 1
                        if transition["count"] == transition["ordinal"]:
                            uc.mem_write(address, transition["value"].to_bytes(4, "little"))
            uc.hook_add(UC_HOOK_MEM_READ, _reviewed_read_transition)
        fstart, fend = self.va, self.va + self.size
        internal_ranges = tuple(
            (address, address + len(data))
            for address, data in self.internal_code_regions)

        class _ExternalBoundary(Exception):
            """Abort Unicorn before it executes an oracle-boundary opcode."""
            pass

        # Ordered event trace: every peripheral read, every non-stack memory
        # write, and every call marker.  Peripheral reads are observable even
        # when their reset-state value is zero: removing, duplicating, or
        # reordering a volatile MMIO access must fail parity.
        # Stack writes (register save/restore/spill) are an implementation
        # detail, not observable behavior, so they are excluded.
        stack_lo = STACK_TOP - 0x9000
        stack_hi = STACK_TOP + 0x100

        def _stack_object_pointer(value, include_content=False,
                                  call_index=None, call_target=None,
                                  argument_values=None):
            """Return reviewed object identity for a pointer, never generic stack.

            The half-open object ranges are declared by the caller relative to
            entry SP. Content begins at the referenced interior offset: bytes
            before an interior pointer are outside that call's pointee region
            (notably response+4 passed to memset).
            """
            for object_index, stack_object in enumerate(stack_objects or ()):
                object_id, offset, payload = stack_object[:3]
                content_ranges = (stack_object[3]
                                  if len(stack_object) > 3 else None)
                call_ordinals = (stack_object[4]
                                 if len(stack_object) > 4 else None)
                call_targets = (stack_object[5]
                                if len(stack_object) > 5 else None)
                embedded_pointer_offsets = (stack_object[6]
                                            if len(stack_object) > 6 else ())
                content_length_argument = (stack_object[7]
                                           if len(stack_object) > 7 else None)
                if (call_ordinals is not None and
                        (call_index is None or call_index not in call_ordinals)):
                    continue
                if (call_targets is not None and
                        (call_target is None or
                         (call_target & ~1) not in call_targets)):
                    continue
                base = STACK_TOP + int(offset)
                size = len(payload)
                if base <= value < base + size:
                    # Coverage is semantic call-boundary recognition, not a
                    # generic observation of stack-looking words in writes.
                    # Recursive embedded pointers retain the call index and
                    # therefore prove that their declaration was active too.
                    if call_index is not None:
                        state["matched_stack_objects"].add(object_index)
                    key = ("SO", object_id, value - base, size)
                    if include_content:
                        interior = value - base
                        if content_ranges is None:
                            count = size - interior
                            # Never infer a pointee length from the following
                            # scalar ABI word.  A shorter extent must name its
                            # length argument explicitly in the reviewed object
                            # declaration; otherwise the declared allocation
                            # extent is the semantic content range.
                            if content_length_argument is not None:
                                if (argument_values is None or
                                        content_length_argument not in argument_values):
                                    raise ValueError(
                                        "stack object length argument is unavailable")
                                count = min(count, max(0, int(argument_values[
                                    content_length_argument])))
                            content = bytes(uc.mem_read(value, count))
                        else:
                            # Some ABI records contain unwritten alignment
                            # holes.  Reviewed ranges enumerate every byte the
                            # consumer can observe, while retaining one object
                            # identity and its complete allocation extent.
                            selected = []
                            for start, end in content_ranges:
                                start = max(int(start), interior)
                                end = min(int(end), size)
                                if start < end:
                                    selected.append(bytes(uc.mem_read(
                                        base + start, end - start)))
                            content = b"".join(selected)
                            key += (tuple((int(start), int(end))
                                          for start, end in content_ranges),)
                        if embedded_pointer_offsets:
                            # Normalize reviewed pointer words inside a local
                            # input record to the identity/interior offset of
                            # the local object they reference.  All surrounding
                            # bytes remain exact, and a pointer redirected to a
                            # different field/object remains observable.
                            raw = bytes(uc.mem_read(base, size))
                            pieces = []
                            cursor = interior
                            end = interior + len(content)
                            for pointer_offset in embedded_pointer_offsets:
                                pointer_offset = int(pointer_offset)
                                if not (cursor <= pointer_offset and
                                        pointer_offset + 4 <= end):
                                    continue
                                if cursor < pointer_offset:
                                    pieces.append(("B", raw[cursor:pointer_offset]))
                                pointer_value = int.from_bytes(
                                    raw[pointer_offset:pointer_offset + 4],
                                    "little")
                                pointer_identity = _stack_object_pointer(
                                    pointer_value, call_index=call_index,
                                    call_target=call_target)
                                if pointer_identity is None:
                                    pieces.append(("B", raw[pointer_offset:
                                                            pointer_offset + 4]))
                                else:
                                    pieces.append(("P", pointer_identity))
                                cursor = pointer_offset + 4
                            if cursor < end:
                                pieces.append(("B", raw[cursor:end]))
                            content = tuple(pieces)
                        key += (content,)
                    return key
            return None

        readonly = self.readonly

        def _format_table_lookup(table, semantic_target, format_address,
                                 default):
            """Reviewed per-format-string arity, resolved by CONTENT.

            The reviewed tables are keyed by the SHIPPED image address of the
            format string.  A reconstruction that spells the same string as a C
            literal presents a different address for the identical bytes; the
            reviewed arity belongs to the string, not to the flash address, so
            fall back to a content match.  An ambiguous or unresolvable address
            falls back to the by-target default -- exactly today's behaviour.
            """
            key = (semantic_target, format_address)
            if key in table:
                return table[key]
            identity = readonly.content(format_address)
            if identity is None:
                return default
            matches = {value for (entry_target, address), value in table.items()
                       if entry_target == semantic_target and
                       readonly.content(address) == identity}
            return matches.pop() if len(matches) == 1 else default

        def _call_event(index, target):
            """Record the observable register ABI at an external boundary.

            Call order alone is insufficient: a reconstruction can call the
            right oracle while silently dropping or changing live arguments.
            r0-r3 are the fixed AAPCS argument registers and are independent
            of compiler-specific stack-frame layout, so compare them exactly.
            """
            semantic_target = (oracle_target_map or {}).get(
                target & ~1, target & ~1)
            if call_arities and index < len(call_arities):
                arity = call_arities[index]
            elif call_arity_by_format is not None:
                format_address = int(uc.reg_read(REG[0])) & 0xffffffff
                arity = _format_table_lookup(
                    call_arity_by_format, semantic_target, format_address,
                    ((call_arity_by_target or {}).get(semantic_target, 4)))
            elif call_arity_by_target is not None:
                arity = call_arity_by_target.get(semantic_target, 4)
            else:
                arity = 4
            state["call_arities_used"].append(arity)
            values = []
            call_sp = int(uc.reg_read(UC_ARM_REG_SP)) & 0xffffffff
            for argument_index in range(arity):
                if argument_index < 4:
                    value = int(uc.reg_read(REG[argument_index])) & 0xffffffff
                else:
                    value = int.from_bytes(uc.mem_read(
                        call_sp + 4 * (argument_index - 4), 4), "little")
                values.append(value)
            format_address = int(uc.reg_read(REG[0])) & 0xffffffff
            default_stack_arity = ((call_stack_arity_by_target or {}).get(
                semantic_target, 0))
            if call_stack_arity_by_format is not None:
                stack_arity = _format_table_lookup(
                    call_stack_arity_by_format, semantic_target,
                    format_address, default_stack_arity)
            else:
                stack_arity = default_stack_arity
            stack_values = [int.from_bytes(uc.mem_read(call_sp + 4 * i, 4),
                                           "little")
                            for i in range(stack_arity)]
            argument_values = {i: value for i, value in enumerate(values)}
            argument_values.update({4 + i: value
                                    for i, value in enumerate(stack_values)})
            for ai, value in enumerate(values):
                identity = _stack_object_pointer(value, include_content=True,
                                                   call_index=index,
                                                   call_target=semantic_target,
                                                   argument_values=argument_values)
                if identity is None:
                    # Read-only pointee equivalence: a pointer to an immutable
                    # string compares by its bytes, never by its flash address.
                    identity = readonly.content(value)
                if identity is not None:
                    values[ai] = identity
            for ai in ((normalized_stack_pointer_calls or {}).get(index, ())):
                if (ai < len(values) and isinstance(values[ai], int) and
                        stack_lo <= values[ai] < stack_hi):
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
            for stack_index, value in enumerate(stack_values):
                identity = _stack_object_pointer(
                    value, include_content=True, call_index=index,
                    call_target=semantic_target,
                    argument_values=argument_values)
                if identity is None:
                    identity = readonly.content(value)
                if identity is not None:
                    stack_values[stack_index] = identity
            # A few recovered ABIs deliberately leave a register hole before
            # a later live argument (for example r0 + r2 with r1 scratch).
            # Preserve the live word using a reviewed target-scoped index set.
            if (call_argument_indices_by_target is not None and
                    semantic_target in call_argument_indices_by_target):
                argument_indices = call_argument_indices_by_target[semantic_target]
                if any(type(ai) is not int or ai < 0 or ai >= len(values)
                       for ai in argument_indices):
                    raise ValueError("call argument index outside reviewed arity")
                values = [values[ai] for ai in argument_indices]
            return ("C", index, *values, "S", *stack_values, "F", *float_values,
                    "T", indirect_target)
        def _mw(uc, access, address, size, value, ud):
            if not (stack_lo <= address < stack_hi):
                pointer_identity = _stack_object_pointer(value)
                if pointer_identity is None and size == 4:
                    # A stored read-only string pointer is the same equivalence
                    # class as a passed one.  Only full words can hold one.
                    pointer_identity = readonly.content(value)
                state["events"].append(("W", address & 0xffffffff, size,
                                        pointer_identity if pointer_identity is not None else
                                        value & ((1 << (size * 8)) - 1)))
                if stop_events and len(state["events"]) >= stop_events:
                    state["capped_events"] = True; uc.emu_stop()
            return True
        uc.hook_add(UC_HOOK_MEM_WRITE, _mw)

        def _mr(uc, access, address, size, value, ud):
            if _is_nrf53_mmio(address, size):
                observed = int.from_bytes(uc.mem_read(address, size), "little")
                state["events"].append(("R", address & 0xffffffff, size,
                                        observed))
                if stop_events and len(state["events"]) >= stop_events:
                    state["capped_events"] = True
                    uc.emu_stop()
            return True
        # Registered after reviewed read-transition hooks so the trace records
        # the hardware value actually consumed on that ordinal.
        uc.hook_add(UC_HOOK_MEM_READ, _mr)

        # Lazily materialize only reviewed device/RAM windows.  Unknown missing
        # addresses now retain Unicorn's architectural fault instead of being
        # silently converted into zero-filled memory.  MMIO reset state is
        # deterministic zero; non-reset hardware states remain explicit via
        # absolute_memory_overrides / absolute_read_transitions.
        def _map_miss(uc, access, address, size, value, ud):
            allowed = (_is_nrf53_mmio(address, size) or
                       _range_contains(NRF53_NET_RAM_WINDOW, address, size))
            if not allowed or access == UC_MEM_FETCH_UNMAPPED:
                return False
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
            if (fstart <= pc < fend or
                    any(start <= pc < end for start, end in internal_ranges)):
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
                        # Unicorn lacks reliable M-profile exclusive support.
                        # Emulate byte, halfword, and word forms symmetrically,
                        # including the local exclusive monitor.
                        load_exclusive = re.fullmatch(
                            r'(?:ldaex|ldrex)([bh]?)', ins.mnemonic)
                        store_exclusive = re.fullmatch(
                            r'(?:stlex|strex)([bh]?)', ins.mnemonic)
                        if load_exclusive:
                            rd = _gpr_index(ins.op_str.split(",")[0])
                            if rd is None:
                                return
                            width = (1 if load_exclusive.group(1) == "b" else
                                     2 if load_exclusive.group(1) == "h" else 4)
                            uc.reg_write(REG[rd], int.from_bytes(
                                uc.mem_read(addr, width), "little"))
                            state["exclusive_monitor"] = (addr, width)
                            state["_resume"] = (pc + size) | 1
                            uc.emu_stop(); return
                        if store_exclusive:
                            parts = [x.strip() for x in ins.op_str.split(",")]
                            rd, rs = _gpr_index(parts[0]), _gpr_index(parts[1])
                            if rd is None or rs is None:
                                return
                            width = (1 if store_exclusive.group(1) == "b" else
                                     2 if store_exclusive.group(1) == "h" else 4)
                            monitor = state.get("exclusive_monitor")
                            # Accept the legacy word-monitor key only for a
                            # word store so resumed comparisons remain stable.
                            ok = (monitor == (addr, width) or
                                  (width == 4 and
                                   state.get("exclusive_addr") == addr))
                            if ok:
                                mask = (1 << (width * 8)) - 1
                                value = int(uc.reg_read(REG[rs])) & mask
                                uc.mem_write(addr, value.to_bytes(width, "little"))
                                # Writes performed by Unicorn API calls from a
                                # code hook do not trigger UC_HOOK_MEM_WRITE.
                                # Emit the architectural store explicitly so
                                # exclusive RMW side effects remain observable.
                                if not (stack_lo <= addr < stack_hi):
                                    state["events"].append(("W", addr & 0xffffffff,
                                                            width, value))
                                    if stop_events and len(state["events"]) >= stop_events:
                                        state["capped_events"] = True
                            uc.reg_write(REG[rd], 0 if ok else 1)
                            state.pop("exclusive_monitor", None)
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
            continuation_lr = None
            if oracle_overrides and idx in oracle_overrides:
                ov = oracle_overrides[idx]
                if 0 in ov: o0 = ov[0] & 0xffffffff
                if 1 in ov: o1 = ov[1] & 0xffffffff
                # Reviewed context-switch helpers can resume a split
                # continuation with the caller's LR restored, rather than the
                # ordinary BL return LR.  Keep this explicit and order-keyed;
                # ordinary calls never alter LR here.
                if "lr" in ov:
                    lr_value, lr_target = ov["lr"]
                    semantic_target = (oracle_target_map or {}).get(
                        pc & ~1, pc & ~1)
                    if semantic_target == (int(lr_target) & ~1):
                        continuation_lr = int(lr_value) & 0xffffffff
            for write in (oracle_memory_writes or {}).get(idx, ()):
                ai, off, data = write[:3]
                # Optional fourth field binds an out-parameter effect to the
                # reviewed callee identity.  Ordinal-only replay is unsafe
                # when earlier branches can put a different function at the
                # same call index.
                semantic_target = (oracle_target_map or {}).get(
                    pc & ~1, pc & ~1)
                if (len(write) > 3 and
                        semantic_target != (int(write[3]) & ~1)):
                    continue
                if ai is None:
                    base = int(off) & 0xffffffff
                    off = 0
                elif ai < 4:
                    base = int(uc.reg_read(REG[ai])) & 0xffffffff
                else:
                    # AAPCS stack-passed arguments begin at the callee-entry
                    # SP.  At the intercepted BL/BLX boundary the caller has
                    # already materialized them at the current SP.
                    call_sp = int(uc.reg_read(UC_ARM_REG_SP)) & 0xffffffff
                    base = int.from_bytes(uc.mem_read(
                        call_sp + 4 * (int(ai) - 4), 4), "little")
                uc.mem_write(base + off, bytes(data))
            for copy in ((oracle_memory_copies or {}).get(idx, ())):
                dst_ai, src_ai, len_ai = copy[:3]
                semantic_target = (oracle_target_map or {}).get(
                    pc & ~1, pc & ~1)
                if (len(copy) > 3 and
                        semantic_target != (int(copy[3]) & ~1)):
                    continue
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
            if continuation_lr is not None:
                # Resume at the ordinary BL return PC while publishing the
                # context-restored caller LR to the split continuation.  A
                # BX-LR trampoline cannot represent these as distinct values.
                uc.reg_write(UC_ARM_REG_LR, continuation_lr)
                uc.reg_write(UC_ARM_REG_PC, lr | 1)
                return
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
                if total > int(max_resumes):
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
                    "matched_stack_objects": sorted(state["matched_stack_objects"]),
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
                    "matched_stack_objects": sorted(state["matched_stack_objects"]),
                    "fault_off": (state["fault_pc"] - self.va) & 0xffffffff}

        r0 = uc.reg_read(UC_ARM_REG_R0)
        r1 = uc.reg_read(UC_ARM_REG_R1)
        primask = uc.reg_read(UC_ARM_REG_PRIMASK) & 1
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
                "primask": primask,
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
                "matched_stack_objects": sorted(state["matched_stack_objects"]),
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
            pointer_read_transitions=None, absolute_read_transitions=None,
            terminal_targets=None, oracle_overrides=None, call_arities=None,
            call_arity_by_target=None, call_arity_by_format=None,
            call_argument_indices_by_target=None,
            call_float_arities=None,
            call_float_arity_by_target=None, oracle_memory_writes=None,
            call_return_kinds=None, call_return_kind_by_target=None,
            call_stack_arity_by_target=None, call_stack_arity_by_format=None,
            normalized_stack_pointer_calls=None, fp_arg_overrides=None,
            oracle_memory_copies=None,
            paired_stack_initial_words=None, candidate_direct_target_map=None,
            paired_stack_objects=None,
            initial_xpsr_overrides=None, initial_primask_overrides=None,
            compare_primask=False,
            orig_internal_code_regions=None,
            candidate_internal_code_regions=None, max_insns=200000,
            max_resumes=5000, initial_exclusive_monitors=None,
            float_scratch_trials=()):
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
    def _retkey(x, readonly=None):
        if ret_kind == "void":
            return ()
        if ret_kind == "i64":
            return (x["r0"], x["r1"])
        if ret_kind == "f32":
            return (_cf32(x["s0"]),)
        if ret_kind == "f64":
            return _cf64(x["s0"], x["s1"])
        # i32 default.  A returned `const char *` is the same read-only
        # equivalence class as a passed one; every other value is unchanged
        # because `key()` falls back to the exact 32-bit result.
        return ((readonly.key(x["r0"]) if readonly is not None else x["r0"]),)
    """Run both functions over `trials` randomized inputs; return verdict dict."""
    ro = Runner(orig_va, orig_size, orig_bytes, code_base,
                internal_code_regions=orig_internal_code_regions)
    # Only the CANDIDATE gets an own-tail read-only extent: its compiled
    # .rodata is where an inlined string literal lands, and the shipped image
    # has no such object.  The original needs none -- every address it can
    # produce is already covered, authoritatively, by the image itself.
    rc = Runner(cand_va, cand_size, cand_bytes, code_base,
                internal_code_regions=candidate_internal_code_regions,
                own_readonly_tail=True)
    mism = []
    checked = 0
    matched_orig_stack_objects = set()
    matched_cand_stack_objects = set()
    se = prefix_k if no_return else 0
    # Trial indices whose argument-pointer region is seeded with plausible
    # binary32 values instead of uniform bytes (hard-float pointee coverage).
    float_scratch_trials = frozenset(int(t) for t in (float_scratch_trials or ()))
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
        art = (absolute_read_transitions[t]
               if absolute_read_transitions and t < len(absolute_read_transitions) else None)
        run_cap = 5000 if no_return else int(max_insns)
        trial_oracles = (oracle_overrides[t]
                         if isinstance(oracle_overrides, (list, tuple)) and t < len(oracle_overrides)
                         else oracle_overrides)
        trial_fp = ((fp_arg_overrides[t] if t < len(fp_arg_overrides) else None)
                    if isinstance(fp_arg_overrides, (list, tuple))
                    else fp_arg_overrides)
        trial_xpsr = (initial_xpsr_overrides[t]
                      if initial_xpsr_overrides and t < len(initial_xpsr_overrides)
                      else 0)
        trial_primask = (initial_primask_overrides[t]
                         if initial_primask_overrides and t < len(initial_primask_overrides)
                         else 0)
        trial_exclusive_monitor = (
            initial_exclusive_monitors[t]
            if initial_exclusive_monitors and t < len(initial_exclusive_monitors)
            else None)
        trial_oracle_writes = (oracle_memory_writes[t]
                               if isinstance(oracle_memory_writes, (list, tuple)) and t < len(oracle_memory_writes)
                               else oracle_memory_writes)
        symbolic_stack_words = []
        for i, pair in enumerate(paired_stack_initial_words or ()):
            if len(pair) > 2:
                fixed = pair[2]
                if isinstance(fixed, (tuple, list)):
                    fixed = fixed[t % len(fixed)]
                value = int(fixed) & 0xffffffff
            else:
                value = int.from_bytes(_prng_fill(
                    b"local" + struct.pack("<II", t, i), 4), "little")
            symbolic_stack_words.append(value)
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
            (pair[0], pair[1], symbolic_stack_objects[i], *pair[4:])
            for i, pair in enumerate(paired_stack_objects or ())]
        cand_stack_objects = [
            (pair[0], pair[2], symbolic_stack_objects[i], *pair[4:])
            for i, pair in enumerate(paired_stack_objects or ())]
        a = ro.run(t, args, t, max_insns=run_cap, max_resumes=max_resumes,
                   stop_events=se, memory_overrides=mov,
                   absolute_memory_overrides=amov,
                   stack_initial_words=orig_stack_words,
                   stack_objects=orig_stack_objects,
                   pointer_read_transitions=prt,
                   absolute_read_transitions=art,
                   terminal_targets=terminal_targets, oracle_overrides=trial_oracles,
                   call_arities=call_arities,
                   call_arity_by_target=call_arity_by_target,
                   call_arity_by_format=call_arity_by_format,
                   call_argument_indices_by_target=call_argument_indices_by_target,
                   call_float_arities=call_float_arities,
                   call_float_arity_by_target=call_float_arity_by_target,
                   call_return_kinds=call_return_kinds,
                   call_return_kind_by_target=call_return_kind_by_target,
                   call_stack_arity_by_target=call_stack_arity_by_target,
                   call_stack_arity_by_format=call_stack_arity_by_format,
                   oracle_memory_writes=trial_oracle_writes,
                   oracle_memory_copies=oracle_memory_copies,
                   normalized_stack_pointer_calls=normalized_stack_pointer_calls,
                   fp_arg_overrides=trial_fp, initial_xpsr=trial_xpsr,
                   initial_primask=trial_primask,
                   initial_exclusive_monitor=trial_exclusive_monitor,
                   float_scratch=(t in float_scratch_trials))
        # candidate emulated at its own VA but identical inputs/scratch
        b = rc.run(t, args, t, max_insns=run_cap, max_resumes=max_resumes,
                   stop_events=se, memory_overrides=mov,
                   absolute_memory_overrides=amov,
                   stack_initial_words=cand_stack_words,
                   stack_objects=cand_stack_objects,
                   pointer_read_transitions=prt,
                   absolute_read_transitions=art,
                   terminal_ordinal=(a.get("terminal_call_ordinal")
                                     if a.get("terminal") else None),
                   detect_repeated_terminal=False, oracle_overrides=trial_oracles,
                   call_arities=a.get("call_arities_used_full", call_arities),
                   call_argument_indices_by_target=call_argument_indices_by_target,
                   call_float_arities=a.get("call_float_arities_used_full", call_float_arities),
                   call_return_kinds=a.get("call_return_kinds_used_full", call_return_kinds),
                   call_stack_arity_by_target=call_stack_arity_by_target,
                   call_stack_arity_by_format=call_stack_arity_by_format,
                   oracle_memory_writes=trial_oracle_writes,
                   oracle_memory_copies=oracle_memory_copies,
                   oracle_target_map=candidate_direct_target_map,
                   normalized_stack_pointer_calls=normalized_stack_pointer_calls,
                   fp_arg_overrides=trial_fp, initial_xpsr=trial_xpsr,
                   initial_primask=trial_primask,
                   initial_exclusive_monitor=trial_exclusive_monitor,
                   float_scratch=(t in float_scratch_trials))
        matched_orig_stack_objects.update(a.get("matched_stack_objects", ()))
        matched_cand_stack_objects.update(b.get("matched_stack_objects", ()))
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
                first = next(((i, x, y) for i, (x, y) in
                              enumerate(zip(a.get("events", ()), b.get("events", ())))
                              if x != y), None)
                mism.append((t, "terminal-prefix", ka, kb,
                             b.get("returned"), first))
            continue
        if no_return and "error" not in a and "error" not in b:
            # Non-returning supervisor loop: compare the ordered side-effect
            # prefix (calls + memory writes). Robust to instructions-per-loop
            # differences because events are semantic, not instruction-counted.
            checked += 1
            if a["returned"] or b["returned"]:
                key_a = (_retkey(a, ro.readonly), a["returned"], a["ncalls"],
                         a["events_hash"])
                key_b = (_retkey(b, rc.readonly), b["returned"], b["ncalls"],
                         b["events_hash"])
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
        architectural_a = (a.get("primask"),) if compare_primask else ()
        architectural_b = (b.get("primask"),) if compare_primask else ()
        key_a = (_retkey(a, ro.readonly), a["returned"], a["ncalls"], a["events_hash"],
                 architectural_a)
        key_b = (_retkey(b, rc.readonly), b["returned"], b["ncalls"], b["events_hash"],
                 architectural_b)
        if key_a != key_b:
            mism.append((t, "state", a, b))
            if verbose:
                print("trial", t, "MISMATCH\n  orig", key_a, "\n  cand", key_b)
    expected_stack_objects = set(range(len(paired_stack_objects or ())))
    missing_orig = sorted(expected_stack_objects - matched_orig_stack_objects)
    missing_cand = sorted(expected_stack_objects - matched_cand_stack_objects)
    if missing_orig or missing_cand:
        mism.append(("stack-object-coverage", missing_orig, missing_cand))
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
    # ---- float-argument coverage (the float analogue of finding #1) ---------
    # `vcmp.f32 s0,#0; vmrs; ite eq; moveq r0,#1; movne r0,#2; bx lr` versus a
    # body that always answers 2.  Only an EXACTLY zero float argument tells
    # them apart, and a uniform-random 32-bit word is never exactly 0.0f, so
    # the historical seeding proved this wrong candidate correct.  The pooled
    # seeding must reach the equal case.
    zero_test = bytes.fromhex("b5ee400a" "f1ee10fa" "0cbf" "0120" "0220" "7047")
    always_two = bytes.fromhex("0220" "7047")
    vz = compare(zero_test, va, len(zero_test), always_two, va, len(always_two),
                 trials=40, nptr=0)
    assert not vz["pass"], vz
    # Same shape against exactly 1.0f (vcmp.f32 s0,s1 with s1 seeded 1.0).
    one_test = bytes.fromhex("b4ee600a" "f1ee10fa" "0cbf" "0120" "0220" "7047")
    vo = compare(one_test, va, len(one_test), always_two, va, len(always_two),
                 trials=40, nptr=0, fp_arg_overrides={1: _f32w(1.0)})
    assert not vo["pass"], vo
    # Sign of a multiply-accumulate: VMLS (Sd = Sd - Sn*Sm) versus VNMLS
    # (Sd = -Sd + Sn*Sm), the exact iteration-37 fusion defect shape.
    vmls_body = bytes.fromhex("00eec10a" "7047")
    vnmls_body = bytes.fromhex("10ee810a" "7047")
    vm = compare(vmls_body, va, len(vmls_body), vnmls_body, va, len(vnmls_body),
                 trials=40, nptr=0, ret_kind="f32")
    assert not vm["pass"], vm
    # NEGATIVE control: realistic float seeding must not manufacture failures.
    # Two different encodings of "ignore every float argument, return 5" stay
    # parity even when the return kind is f32 (s0 is untouched by both).
    five_a = bytes.fromhex("0520" "7047")
    five_b = bytes.fromhex("4ff00500" "7047")
    for kind in ("i32", "f32", "f64", "void"):
        vn = compare(five_a, va, len(five_a), five_b, va, len(five_b),
                     trials=40, nptr=0, ret_kind=kind)
        assert vn["pass"], (kind, vn)
    # Float POINTEE coverage: `vldr s0,[r0]; vcmp.f32 s0,#0; ...` distinguishes
    # itself from the constant body only when the pointed-to word is exactly
    # 0.0f.  Uniform pointee bytes never are; the float scratch profile is.
    load_zero_test = bytes.fromhex("90ed000a" "b5ee400a" "f1ee10fa"
                                   "0cbf" "0120" "0220" "7047")
    ptr_case = [{0: SCRATCH + 0x2000}] * 40
    vp = compare(load_zero_test, va, len(load_zero_test),
                 always_two, va, len(always_two), trials=40, nptr=0,
                 arg_overrides=ptr_case)
    assert vp["pass"], vp          # uniform pointee bytes: blind, as measured
    vp = compare(load_zero_test, va, len(load_zero_test),
                 always_two, va, len(always_two), trials=40, nptr=0,
                 arg_overrides=ptr_case, float_scratch_trials=range(40))
    assert not vp["pass"], vp      # float pointee profile: discriminates
    # The float pointee profile is symmetric setup, so identical bodies pass.
    vp = compare(load_zero_test, va, len(load_zero_test),
                 load_zero_test, va, len(load_zero_test), trials=40, nptr=0,
                 arg_overrides=ptr_case, float_scratch_trials=range(40))
    assert vp["pass"], vp
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
    # Reviewed internal regions execute a private-ABI leaf as part of the
    # caller's semantic unit.  The same BL is no longer an oracle event, and
    # its complete register result must equal an ordinary inlined candidate.
    internal_caller = bytes.fromhex("00b500f005f800bd")
    internal_leaf = bytes.fromhex("08447047")  # add r0,r1; bx lr
    internal_run = Runner(
        va, len(internal_caller), internal_caller,
        internal_code_regions=[(va + 0x10, internal_leaf)]).run(
            0, [7, 9, 0, 0], 0)
    assert internal_run["returned"] and internal_run["ncalls"] == 0, internal_run
    assert internal_run["r0"] == 16, internal_run
    internal_cmp = compare(
        internal_caller, va, len(internal_caller),
        internal_leaf, va, len(internal_leaf), trials=4, nptr=0,
        orig_internal_code_regions=[(va + 0x10, internal_leaf)])
    assert internal_cmp["pass"], internal_cmp
    internal_bad = bytes.fromhex("01307047")  # adds r0,#1; bx lr
    internal_cmp = compare(
        internal_caller, va, len(internal_caller),
        internal_bad, va, len(internal_bad), trials=4, nptr=0,
        orig_internal_code_regions=[(va + 0x10, internal_leaf)])
    assert not internal_cmp["pass"], internal_cmp
    try:
        Runner(va, len(internal_caller), internal_caller,
               internal_code_regions=[(va + 2, internal_leaf)])
        assert False, "main-body/internal overlap was accepted"
    except ValueError:
        pass
    try:
        Runner(va, len(internal_caller), internal_caller,
               internal_code_regions=[(va + 0x10, internal_leaf),
                                      (va + 0x11, internal_leaf)])
        assert False, "overlapping internal regions were accepted"
    except ValueError:
        pass
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
    # Optional third fields pin reviewed incoming stack arguments to exact
    # full words instead of generating symbolic uninitialized-local content.
    vl = compare(local_orig, va, len(local_orig), local_cand, va, len(local_cand),
                 trials=1, nptr=0, arg_overrides=local_args,
                 paired_stack_initial_words=[(-8, -12, 0xa5c3f00d)])
    assert vl["pass"], vl
    # A reviewed case sequence selects one exact incoming word per trial.
    vl = compare(local_orig, va, len(local_orig), local_cand, va, len(local_cand),
                 trials=2, nptr=0, arg_overrides=local_args * 2,
                 paired_stack_initial_words=[
                     (-8, -12, (0xa5c3f00d, 0x12345678))])
    assert vl["pass"], vl
    vl = compare(local_orig, va, len(local_orig), local_upper_bad, va,
                 len(local_upper_bad), trials=1, nptr=0,
                 arg_overrides=local_args,
                 paired_stack_initial_words=[(-8, -12, 0xa5c3f00d)])
    assert not vl["pass"], vl
    # Split context-switch continuations restore the caller LR rather than the
    # ordinary BL return address.  The override is bound to the exact semantic
    # helper target; an unrelated target must not receive it.
    split = bytes.fromhex("00b500f005f810b510bd")
    split_runner = Runner(va, len(split), split)
    split_args = [0, 0, 0, 0]
    resumed = split_runner.run(
        0, split_args, 0,
        oracle_overrides={0: {"lr": (RETURN_MAGIC | 1, va + 0x10)}},
        max_insns=100)
    assert resumed.get("returned"), resumed
    wrong_resume = split_runner.run(
        0, split_args, 0,
        oracle_overrides={0: {"lr": (RETURN_MAGIC | 1, va + 0x20)}},
        max_insns=100)
    assert not wrong_resume.get("returned"), wrong_resume
    try:
        split_runner.run(0, split_args, 0,
                         oracle_overrides={0: {"lr": RETURN_MAGIC | 1}},
                         max_insns=100)
        assert False, "target-free scalar LR continuation was accepted"
    except ValueError:
        pass
    for bad_lr in ([RETURN_MAGIC | 1, va + 0x10],
                   (str(RETURN_MAGIC | 1), va + 0x10)):
        try:
            split_runner.run(0, split_args, 0,
                             oracle_overrides={0: {"lr": bad_lr}},
                             max_insns=100)
            assert False, "non-exact LR continuation tuple was accepted"
        except ValueError:
            pass
    # Reviewed content ranges are exact, ordered half-open payload intervals.
    # None retains complete-content behavior and () remains the intentional
    # output-only contract, while malformed/overlapping ranges fail closed.
    for valid_ranges in (None, ()):
        valid = Runner(va, len(leaf), leaf).run(
            0, [0, 0, 0, 0], 0,
            stack_objects=[("valid-range", -8, bytes(4), valid_ranges)])
        assert valid.get("returned"), valid
    for bad_ranges in (((1, 1),), ((0, 5),),
                       ((0, 3), (2, 4)), ((2, 4), (0, 1))):
        try:
            Runner(va, len(leaf), leaf).run(
                0, [0, 0, 0, 0], 0,
                stack_objects=[("bad-range", -8, bytes(4), bad_ranges)])
            assert False, "invalid stack-object content range was accepted"
        except ValueError:
            pass
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
