#!/usr/bin/env python3
"""Directed differential check for OUTGOING STACK ARGUMENTS at k_thread_create.

Why this exists
---------------
`tools/parity/emu.py` keys its side-effect trace on the ABI return register(s),
the ordered NON-STACK memory-write trace, and the call count/order with the
callee's arguments.  How many of those arguments are *stack* arguments is a
per-target decision: `emu.compare` only captures stack words for callees listed
in `call_stack_arity_by_target` (which `tools/cfg_verify.py` feeds from its
reviewed `REVIEWED_TARGET_CALL_STACK_ARITIES` table).  No reviewed entry existed
for `z_impl_k_thread_create` (original VA 0x00071eac), so every reconstruction
that silently dropped its stack arguments still produced an identical trace and
was reported "300/300 PROVEN".

With `CONFIG_TIMEOUT_64BIT=y` (this firmware) `z_impl_k_thread_create`'s tenth
parameter is a 64-bit `k_timeout_t delay`, 8-byte aligned at `sp+0x18`, so a
correct call site writes EIGHT stack words:

    sp+0x00 p1    sp+0x04 p2     sp+0x08 p3    sp+0x0c prio
    sp+0x10 opts  sp+0x14 (pad)  sp+0x18/0x1c  delay.ticks (64-bit)

This script pins `{0x00071eac: 8}` at the eight direct call sites and
`{0x0007cb66: 4}` at the dispatch veneer's caller, so a dropped `delay` -- or
any other dropped/reordered outgoing stack argument at these boundaries -- is a
hard FAIL.  It reads the canonical bodies from `recon/app/src` and changes
nothing under `tools/`; the one cfg_verify-routed site augments that module's
reviewed table in memory only, for the duration of the run.

Two guarded sites (`start_aging_mode_thread`, `start_ancs_work_thread`) never
reach their `k_thread_create` under random seeding, which would make a PASS
meaningless.  They carry reviewed path-forcing fixtures, and every
emu-routed site additionally asserts that the pinned callee really was called.

Usage
-----
    PYTHONSAFEPATH=1 .venv/bin/python \
        recon/emulator/scripts/check_thread_create_stack_args.py [--trials N]

Exit status is non-zero if any site fails.
"""
import os
import sys

BASE = "/Users/freedomcoder/Projects/G1disasm2"
sys.path.insert(0, os.path.join(BASE, "tools"))

import extract                       # noqa: E402
from parity import emu, recon        # noqa: E402

RECON_SRC = os.path.join(BASE, "recon/app/src")

K_THREAD_CREATE = 0x00071EAC         # z_impl_k_thread_create
DISPATCH_VENEER = 0x0007CB66         # main_dispatch_thread_tick

# Eight stack words == sp+0x00 .. sp+0x1c: p1,p2,p3,prio,options,pad,delay(2).
THREAD_CREATE_STACK_WORDS = 8
# The veneer takes four stack words of its own: p1, prio, delay(2).
VENEER_STACK_WORDS = 4

DEVICE_INFO_FIXTURE = emu.SCRATCH + 0x7000

# Reviewed fixtures that force a guarded k_thread_create to be reached.
PATH_FORCING = {
    # start_aging_mode_thread: `if (*(u8*)0x20019ef1 != 0) return;`
    0x00032FE8: {"absolute_memory_overrides": [(0x20019EF1, b"\x00")]},
    # start_ancs_work_thread: get_device_info()[0] must be 2 and
    # is_battery_critical() must not return 1.
    # The three non-thread callees here take 0/0/2 register arguments; without
    # saying so, the default arity of 4 compares scratch registers and the site
    # mismatches for a reason unrelated to stack arguments.  (cfg_verify infers
    # the same thing from the extern declarations in the source.)
    0x000198CC: {"absolute_memory_overrides": [(DEVICE_INFO_FIXTURE, b"\x02")],
                 "oracle_overrides": {0: {0: DEVICE_INFO_FIXTURE},
                                      1: {0: 0}},
                 "call_arity_by_target": {0x000167A8: 0,   # get_device_info
                                          0x00032EE4: 0,   # is_battery_critical
                                          0x00019C70: 0,   # debug_print
                                          0x0007DDA4: 2,   # log_message
                                          K_THREAD_CREATE: 4}},
    # imu_fusion_init (iteration 13): the 13th k_thread_create site, recovered
    # from the Ghidra catalog gap [0x25f90, 0x26100).  It only reaches the call
    # when context[0x14] == 0 and both dev_api_call_slot0 results are >= 0.
    # The argument-pointer scratch half is therefore zero-filled (identically for
    # original and candidate) and the two driver results are forced on call
    # ordinals 2 and 4.
    #
    # The stack window below STACK_TOP is poison-filled for the same reason the
    # scratch is zeroed, and it is the one place this site differs from the other
    # nine: the original prologue is `push {r4,r5,r6,r7,lr} ; sub sp,#0x24` while
    # GCC needs only four callee-saved registers for the reconstruction
    # (`push {r4,r5,r6,lr} ; sub sp,#32`).  Both frames therefore leave the
    # architecturally dead AAPCS pad word at sp+0x14 uninitialised, but at
    # DIFFERENT absolute addresses, so without a constant fill the eight-word
    # window would differ on that dead word alone.  All eight outgoing words are
    # still compared; the live seven plus the 64-bit delay match exactly.
    #
    # g_log_level (0x2000230c) is pinned to 0 so the five guarded log branches
    # stay out of the call sequence and the two forced ordinals are stable.
    #
    # Mutation battery actually run on this site (60 trials each):
    #   prio -11 -> -12          FAIL (60/60)   <- discriminating
    #   delay 0ULL -> 5ULL       FAIL (60/60)   <- discriminating
    #   p2 0 -> 1                FAIL (60/60)   <- discriminating
    #   delay argument removed   PASS           <- NOT discriminating HERE, and
    #     the reason is specific and known: dropping the argument shrinks the
    #     frame from `sub sp,#32` to `sub sp,#24`, exactly 8 bytes, so sp+0x18
    #     and sp+0x1c land on the pushed r4/r5 slots -- and the harness enters
    #     the function with r4 = r5 = 0, which is byte-identical to the correct
    #     K_NO_WAIT delay.  (The other eight sites lost more than 8 bytes and hit
    #     the pushed lr = RETURN_MAGIC, which is why they did fail pre-fix.)
    #     The authority for that mutation at this site is therefore the
    #     instruction-level frame comparison recorded in
    #     reports/our_boot_bringup.md Iteration 13: the emitted
    #     `str r4,[sp,#0] / strd r5,r5,[sp,#4] / strd r3,r5,[sp,#12] /
    #     strd r2,r3,[sp,#24]` block matches the original word for word.  Register arities: get_device_type 0, dev_api_call_slot0 3,
    # imu_fusion_state_init 1, panel_level_calc_cached 1.
    0x00025FAC: {"absolute_memory_overrides": [(emu.SCRATCH, b"\x00" * 0x4000),
                                              (emu.STACK_TOP - 0x100,
                                               b"\xa5" * 0x100),
                                              (0x2000230C, b"\x00" * 4)],
                 "oracle_overrides": {2: {0: 0}, 4: {0: 0}},
                 "call_arity_by_target": {0x00016568: 0,   # get_device_type
                                          0x0007CA54: 3,   # dev_api_call_slot0
                                          0x000265B8: 1,   # imu_fusion_state_init
                                          0x00025ECC: 1,   # panel_level_calc_cached
                                          0x00019C70: 4,   # debug_print
                                          0x0007DDA4: 4,   # log_message
                                          K_THREAD_CREATE: 4}},
}

# (source basenames, va, size, ret_kind, {callee_va: stack_words}, method)
# The canonical tree stores some bodies under their FUN_ identity and some
# under the readable name, so each site lists every basename it may live under.
#
# method "emu": standalone emu.compare, sound here because these bodies have no
#               variadic/oracle context beyond what the default harness models.
# method "cfg": routed through cfg_verify, which owns the reviewed variadic
#               arities and CFG-derived branch inputs this body needs; a bare
#               emu.compare mismatches it even when it is correct.
SITES = [
    (("FUN_0002201c", "init_ble_work_thread"), 0x0002201C, 66, "i32",
     {K_THREAD_CREATE: THREAD_CREATE_STACK_WORDS}, "emu"),
    (("FUN_00049638", "spawn_display_thread"), 0x00049638, 52, "i32",
     {K_THREAD_CREATE: THREAD_CREATE_STACK_WORDS}, "emu"),
    (("FUN_00047ad0", "spawn_proxy_thread"), 0x00047AD0, 76, "i32",
     {K_THREAD_CREATE: THREAD_CREATE_STACK_WORDS}, "emu"),
    (("FUN_0003304c", "spawn_aging_mode_aux_thread"), 0x0003304C, 60, "void",
     {K_THREAD_CREATE: THREAD_CREATE_STACK_WORDS}, "emu"),
    (("FUN_000198cc", "start_ancs_work_thread"), 0x000198CC, 104, "void",
     {K_THREAD_CREATE: THREAD_CREATE_STACK_WORDS}, "emu"),
    (("FUN_00032fe8", "start_aging_mode_thread"), 0x00032FE8, 74, "void",
     {K_THREAD_CREATE: THREAD_CREATE_STACK_WORDS}, "emu"),
    (("FUN_00023a54", "spawn_flash_ops_and_brightness_threads"), 0x00023A54, 90,
     "void", {K_THREAD_CREATE: THREAD_CREATE_STACK_WORDS}, "emu"),
    (("FUN_0007cb66", "main_dispatch_thread_tick"), 0x0007CB66, 36, "void",
     {K_THREAD_CREATE: THREAD_CREATE_STACK_WORDS}, "emu"),
    (("FUN_0002a65c", "run_main_dispatch_thread"), 0x0002A65C, 398, "void",
     {DISPATCH_VENEER: VENEER_STACK_WORDS}, "cfg"),
    (("imu_fusion_init",), 0x00025FAC, 0x124, "i32",
     {K_THREAD_CREATE: THREAD_CREATE_STACK_WORDS}, "emu"),
]


def _resolve(names):
    for cand_name in names:
        p = os.path.join(RECON_SRC, cand_name + ".c")
        if os.path.exists(p):
            return cand_name, p
    return None, None


def _call_reached(orig, va, size, stack_arities, kwargs):
    """Run the ORIGINAL once and report whether the pinned callee was called."""
    target = next(iter(stack_arities)) & ~1
    runner = emu.Runner(va, size, orig)
    amov = kwargs.get("absolute_memory_overrides")
    out = runner.run(0, emu.make_args(0, 2), 0,
                     absolute_memory_overrides=(amov[0] if amov else None),
                     oracle_overrides=kwargs.get("oracle_overrides"),
                     call_stack_arity_by_target=stack_arities)
    return target in [t & ~1 for t in out.get("call_targets_full", ())]


def _run_emu(name, src_path, va, size, ret_kind, stack_arities, trials):
    csrc = open(src_path).read()
    orig = extract.func_bytes_padded(va, size, pad=64)
    comp, err = recon.compile_func(csrc, name, va)
    if err:
        return {"name": name, "status": "COMPILE-FAIL", "error": err[-400:]}
    body, tail, csize, cva = comp
    # The candidate's direct-call stubs move with its own code layout, so the
    # per-target stack arity can only be looked up through the semantic map the
    # compile step recorded.  Without it the candidate captures zero stack words
    # for every call and the run fails for a bookkeeping reason, not a real one.
    direct_map = dict(recon.LAST_DIRECT_TARGET_MAP)
    force = PATH_FORCING.get(va, {})
    kwargs = {}
    if "absolute_memory_overrides" in force:
        kwargs["absolute_memory_overrides"] = [
            force["absolute_memory_overrides"]] * trials
    if "oracle_overrides" in force:
        kwargs["oracle_overrides"] = force["oracle_overrides"]
    if "call_arity_by_target" in force:
        kwargs["call_arity_by_target"] = force["call_arity_by_target"]
    v = emu.compare(orig, va, size, body + tail, cva, csize,
                    trials=trials, nptr=2, ret_kind=ret_kind,
                    call_stack_arity_by_target=stack_arities,
                    candidate_direct_target_map=direct_map, **kwargs)
    reached = _call_reached(orig, va, size, stack_arities, kwargs)
    status = "PASS" if v.get("pass") else "FAIL"
    if status == "PASS" and not reached:
        status = "NOT-REACHED"
    return {"name": name, "status": status, "checked": v.get("checked"),
            "mismatches": v.get("mismatches"), "reached": reached}


def _run_cfg(name, va, stack_arities, trials):
    import cfg_verify
    # Runtime-only augmentation of the reviewed table (tools/ is not modified).
    table = cfg_verify.REVIEWED_TARGET_CALL_STACK_ARITIES.setdefault(
        ("app", va), {})
    table.update(stack_arities)
    v = cfg_verify.verify("app", name, trials_random=trials)
    return {"name": name,
            "status": "PASS" if v.get("status") == "PASS" else "FAIL",
            "checked": v.get("checked"), "mismatches": v.get("mismatches"),
            "reached": True}


def run_site(names, va, size, ret_kind, stack_arities, method, trials):
    name, src_path = _resolve(names)
    if src_path is None:
        return {"name": names[0], "status": "MISSING-SRC", "reached": None}
    if method == "cfg":
        r = _run_cfg(name, va, stack_arities, trials)
    else:
        r = _run_emu(name, src_path, va, size, ret_kind, stack_arities, trials)
    r["va"] = hex(va)
    r["method"] = method
    r["stack_arities"] = {hex(k): w for k, w in stack_arities.items()}
    return r


def main(argv):
    trials = 120
    for i, a in enumerate(argv):
        if a == "--trials":
            trials = int(argv[i + 1])
    bad = 0
    print("directed outgoing-stack-argument check @ k_thread_create "
          "(CONFIG_TIMEOUT_64BIT: 64-bit k_timeout_t delay at sp+0x18)")
    print("%-40s %-10s %-6s %-12s %-8s %-8s %s" % (
        "function", "va", "via", "status", "checked", "reached",
        "pinned stack words"))
    for names, va, size, rk, sa, method in SITES:
        r = run_site(names, va, size, rk, sa, method, trials)
        if r["status"] != "PASS":
            bad += 1
        print("%-40s %-10s %-6s %-12s %-8s %-8s %s" % (
            r["name"], r.get("va", "-"), r.get("method", "-"), r["status"],
            r.get("checked", "-"), r.get("reached", "-"),
            r.get("stack_arities", "-")))
        if r["status"] == "COMPILE-FAIL":
            print("    error: %s" % r["error"])
        elif r["status"] == "FAIL":
            print("    mismatches=%s" % r.get("mismatches"))
    print("EXIT=%d  (%d/%d sites pass)" % (1 if bad else 0, len(SITES) - bad,
                                           len(SITES)))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
