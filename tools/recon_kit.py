"""
Reconstruction kit used by reconstruction subagents.

Per function it resolves everything needed to write a faithful C reconstruction
whose recompilation can be PROVEN byte-for-behavior identical to the firmware:

  info(va)  -> {decompiled, disasm(annotated with literal-pool VALUES),
                callees, size, name}
  prove(va, size, name, csrc, nptr, trials) -> CFG-directed parity verdict,
                appended to a shared JSON ledger (recon_ledger.json).

CLI:
  python recon_kit.py info 0x327c4        # dump everything for one function
  python recon_kit.py list-app            # list application functions to do
  python recon_kit.py ledger              # summary of proven/failed
"""
import sys, os, json, re
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import extract
import function_names
from capstone import *

SCRATCH = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
RECON_SRC = "/Users/freedomcoder/Projects/G1disasm2/recon/app/src"
TRUE_SIZE_OVERRIDES = {
    # Catalog stops at the shared success island; include MOVS/BX LR.
    0x00085316: 0x62,
    # Independently callable SDK/application entries missed by the Ghidra
    # function catalog.  Each extent ends before its literal pool or the next
    # entry and is reviewed from the shipped Thumb CFG.
    0x00028964: 0x4c,  # enter_active_click_mode
    0x00052fbc: 0x4c,  # bt_settings_delete
    0x00066524: 0xf6,  # nrfx_qspi.c qspi_xfer
    # CINSTRDAT get switch owns fall-through stores through POP at 0x6671a;
    # its aligned peripheral-base literal begins independently at 0x6671c.
    0x000666e0: 0x3c,
    0x0007332c: 0xc2,  # k_work_schedule_for_queue
    0x00073424: 0xbe,  # k_work_reschedule_for_queue
    0x00076a88: 0x06,  # newlib nanf; literal begins at +0x08
    0x0007c058: 0x28,  # send_touch_click_event
    0x0007c084: 0x0a,  # gpio_pin_set_dt
    # zcbor_encode.c:str_encode is a real static entry omitted from the
    # exported function catalog.  It starts at its full callee-saved prologue
    # and returns at 0x8629e, where zcbor_int_encode begins independently.
    0x00086228: 0x76,
    0x0004c254: 0x18,  # delay_scaled_busy_wait; literals at 0x4c26c
    0x0004d44c: 0x14,  # z_log_notify_backend_enabled; literals at 0x4d460
    0x0004d468: 0x1e,  # z_log_dropped; alignment at 0x4d486
    0x0004d8b8: 0x1c,  # z_log_msg_commit; literals at 0x4d8d4
    0x0004e474: 0x0a,  # settings_store_init; alignment at 0x4e47e
    0x0004f500: 0x14,  # fixed three-word configuration setter
    0x000573c8: 0x24,  # allocation-failure logging helper
    0x00068298: 0x0c,  # libmetal Zephyr metal_sys_init
    0x00016574: 0x06,  # fixed-word setter
    0x00016834: 0x1a,  # state-normalizing tail adapter
    0x00017a04: 0x08,  # GPIO descriptor tail adapters
    0x00017a10: 0x08,
    0x00017a1c: 0x08,
    0x00017a28: 0x08,
    0x00017a34: 0x08,
    0x0002893c: 0x1e,  # click-event notification helper
    0x00032fdc: 0x06,  # fixed-byte getter
    0x0002538c: 0x98,  # transport state update; literals at 0x25424
    0x000258b4: 0x90,  # transport parameter reader; literals at 0x25944
    0x00025950: 0x78,  # transport parameter writer; literals at 0x259c8
    0x0002bdf0: 0x60,  # active-mode shutdown; literals at 0x2be50
    0x0003364c: 0x50,  # one-byte transport send; literal at 0x3369c
    0x00033a5c: 0x4c,  # notification-count response; literals at 0x33aa8
    0x00035744: 0x28,  # whitelist dump/init wrapper; literals at 0x3576c
    0x0003cebc: 0x72,  # do-not-disturb state setter; alignment at 0x3cf2e
    0x00024e60: 0xa0,  # framed transport write; literals begin at 0x24f00
    0x0004372c: 0xc8,  # display-mode globals dispatcher; literals begin at 0x437f4
    # lc3_tns_analyze continues through the final quantizer/order backedge at
    # 0x709c4; its trailing threshold literals begin at 0x709c8.
    0x0006ffd8: 0x9ee,
    # touch_key_thread's catalog ends at 0x2a332 inside its computed-switch
    # cases.  Owned cases resume after the 0x2a3a8 literal island and finish
    # at 0x2a4a0, where the trailing literal pool begins.
    0x0002a0d8: 0x3c8,
    # gui_utf_draw_truncate's catalog stops at 0x44ba2 inside its live
    # callback/logger tail.  The final branch ends at 0x44bc0; literals begin
    # at 0x44bc4 and the next independent prologue is at 0x44bd8.
    0x00044818: 0x3ac,
    # gui_utf_draw_align_right continues through its callback/logger tail;
    # live code ends at 0x451ce before alignment and the literal pool.
    0x00044ec4: 0x30a,
    # Final invalid-state return branch ends at the next entry 0x809f6.
    0x000809b0: 0x46,
    # clear_event_registrations' final reacquire tail ends at 0x7552c.
    0x000753ec: 0x140,
    # Final poll assertion tail and shared unlock/loop end before 0x753a0.
    0x000751d0: 0x1ce,
    # process_for_new_task's catalog extent ends at 0x2e038 inside the live
    # state-zero polling loop.  The remaining switch/default and shared
    # status-return tail run through the branch at 0x2e2be; literals begin at
    # 0x2e2c4 (0x2e2c2 is alignment) and 0x2e300 is a new prologue.
    0x0002c99c: 0x1924,
    # The unknown-address-type path rejoins the shared final formatter via the
    # branch at 0x18390; literals begin at 0x18394.
    0x00018334: 0x5e,
    # Final retry back-branch and read-exhaustion return end at 0x32e68;
    # literals begin at 0x32e6c.
    0x00032c28: 0x242,
    # The catalog ends immediately before the live default arm.  MVN.W/B
    # returns -128 through the shared epilogue; literals begin at 0x56ad0.
    0x00056a68: 0x68,
    # lc3_spec_encode's catalog stops at 0x6ffcc inside two branch-reachable
    # noise-estimation setup islands.  Both rejoin the shared body; the final
    # branch ends at 0x6ffd8, where the next independent prologue begins.
    0x0006f9c0: 0x618,
    # display_thread_handler's catalog stops at 0x495a2 inside its live
    # missing-message shutdown arm.  Logger and forced-display-reset islands
    # rejoin the worker through 0x49630; 0x49632 is alignment, 0x49634 is its
    # final literal, and FUN_00049638 is the next independent prologue.
    0x00049090: 0x5a2,
    # display_dispatch_thread's catalog stops at 0x29498 inside the final
    # mode-notification logger.  Its live notification/delay islands rejoin
    # through the branch at 0x29500; 0x29502 is alignment and literals occupy
    # 0x29504..0x2953b before FUN_0002953c.
    0x00028bec: 0x916,
    # The catalog stops at 0x285e4 inside the final inner switch.  Its four
    # live handlers end with the branch at 0x286c0..0x286c3; literals occupy
    # 0x286c4..0x286f7
    # and the next independent thread prologue is FUN_000286f8.
    0x00027cfe: 0x9fa,
    # proxy_thread_handler's catalog stops at 0x486f8 inside the language/
    # work-mode switch.  Live retry and atomic-flag tails continue through the
    # branch at 0x48812..0x48815; literals occupy 0x48818..0x4883f and the
    # independent requestAudioInfoToApp entry starts at 0x48840.
    0x00047c48: 0xbf8,
    # gui_utf_Wordwrap_draw's catalog stops at 0x45590 inside its live
    # callback/logger tail.  Executable ownership continues through 0x455b6;
    # its final literals occupy 0x455b8..0x455cb and gui_string_draw begins
    # independently at 0x455cc.
    0x000451e0: 0x3ec,
    # Live body/package formatting and word-wrap tail continue through
    # 0x35f1a; the catalog stops early at 0x35ef0 and literals start 0x35f1c.
    0x00035afc: 0x41e,
    # Refgraph stops at 0x2144c in the default status-response arm.  The live
    # tail ends after the branch at 0x21454; literals begin at 0x21458.
    0x00021334: 0x122,
    # Switch-owned continuations run through 0x429f2; 0x429f4 is a literal
    # and FUN_000429f8 is the next independent function.
    0x000417f8: 0x11fa,
    # Catalog ends before the ordinary shared return. POP is at 0x430aa and
    # the literal pool begins at 0x430ac.
    0x00042fb0: 0xfc,
    # Live calibration loop and final delay/return continue through 0x1080e;
    # the catalog stops at the loop's first VFP load at 0x10764.
    0x0000fe88: 0x988,
    0x00033384: 0x188,  # shared switch epilogue through 0x3350a
    # Response-kind 3 continues at 0x42c3e and returns at 0x42c4a; the
    # catalog stops at that live tail's entry.
    0x00042a64: 0x1ec,
    # Final short-payload branch rejoins completion at 0x1817e; literals start
    # immediately afterward at 0x18180.
    0x00017f70: 0x210,
    # UI refresh dispatch returns through 0x48e0e.  Its six-word literal pool
    # begins at 0x48e10; the catalog folds many independent handler bodies.
    0x00048b5c: 0x2b4,
    # Final mode-7 dispatch arm and its shared return.
    0x0001694c: 0x28c,
    # Late logger islands remain reachable through the branch at 0x17dee.
    0x00017a40: 0x3b0,
    # Shared epilogue and buffered logger island end before literals at 0x3e7b4.
    0x0003e05c: 0x758,
    # This atomic flag-clear wrapper returns at 0x810a8.  The independent
    # atomic/setter helpers beginning at 0x810aa were folded into its catalog.
    0x00081080: 0x2a,
    # Computed-switch default island continues through 0x4f40e; the catalog
    # stops at its entry 0x4f40a.
    0x0004f1d0: 0x23e,
    0x0000e53c: 0x3fc,
    0x0000fcf0: 0x178,
    0x000113a8: 0xecc,
    # local_esbs_ipc_service_recv's catalog stops inside the late command
    # switch.  Cases 0xf..default continue through 0x15dd4; literals begin at
    # 0x15dd8 and the next independent function starts at 0x15df4.
    0x00015960: 0x478,
    0x00016eb8: 0x7ac,
    0x0001a064: 0x6e4,
    0x0001a75c: 0x6bae,
    0x00021460: 0x59c,
    0x00023844: 0x1d0,
    # sync_to_slave's catalog ends at 0x273ee, before the final validation
    # branch/logger tail.  Live CFG continues through 0x2741a; literals begin
    # at 0x2741c and the next independent function starts at 0x27448.
    0x00026f74: 0x4a8,
    0x00028a1c: 0x198,
    # key_event_thread's catalog stops in the state-5 arm at 0x29fea.  The
    # complete state-5/state-6 tails and shared loopback continue through the
    # unconditional branch ending at 0x2a096; literals begin at 0x2a098.
    0x0002955c: 0xb3a,
    0x0002a8d8: 0x3f4,
    # The 0x4a..0x4f command islands live after the embedded literal pool at
    # 0x2baa0.  They rejoin the shared epilogue and end before literals at
    # 0x2bc0c; the catalog's 0xb54 bytes stop at the pool itself.
    0x0002af4c: 0xcc0,
    0x00030cd0: 0x3a,
    # Executable CFG ends at 0x338d8; 0x338dc..0x338e8 is the owned literal
    # pool and FUN_000338ec is the next independent catalog entry.
    0x0003384c: 0x8c,
    0x0003727c: 0x3bdc,
    0x0003af78: 0x7e6,
    0x0003b824: 0x5ba,
    0x0003bfe0: 0xb4c,
    0x0003e7f8: 0xc80,
    0x000442bc: 0x266,
    0x0004588c: 0x110c,
    0x00049acc: 0x634,
    0x0004abc0: 0x444,
    0x0004b4fc: 0x394,
    0x0004bc8c: 0x166,
    0x0004beb8: 0x110,
    # mpsc_pbuf_free tail-branches at 0x4c08c; its assertion literals begin
    # at 0x4c090 and the next independent function starts at 0x4c0a8.
    0x0004bfc8: 0xc8,
    0x0004d100: 0x70,
    0x0004d578: 0x0e,
    # Two-instruction scheduler-state tail wrapper.  The literal at 0x4d590
    # is data; FUN_0004d594 starts the next independent body.
    0x0004d588: 0x06,
    0x0004e98c: 0x10,
    0x00050b8c: 0x24,
    0x000531cc: 0x08,
    0x0005505c: 0x34,
    0x000566a4: 0x50,
    0x00056704: 0x1e0,
    0x00059690: 0x28,
    0x00059834: 0xe6,
    # att_op_get_type's classified extent stopped at 0x5831a, omitting the
    # confirmation and request return islands at 0x5831c..0x58322.
    0x000582b8: 0x6c,
    # Include the default-state arm's final branch at 0x599c0; literals start
    # at 0x599c4 after an alignment NOP.
    0x00059920: 0xa2,
    # Service Changed persistence diagnostic returns at 0x5a11e; its two-word
    # literal pool begins at 0x5a120 before FUN_0005a128.
    0x0005a0e8: 0x38,
    0x0005b9cc: 0x1e0,
    # Two CBZ arms enter the shared FUN_0005f638 call at 0x5f948 and rejoin
    # through the branch at 0x5f94e; literals begin at 0x5f950.
    0x0005f760: 0x1f0,
    0x0005fb8c: 0xda,
    # FUN_0005cff0 tail-branches at 0x5d09a; its branch completes at 0x5d09e.
    # The following NOP/literals precede an independent function at 0x5d0ac.
    0x0005cff0: 0xae,
    0x00068240: 0x3a,
    0x000698d0: 0xc82,
    0x0006b3c8: 0x5ea,
    0x0006bfc8: 0x7ae,
    0x0006c778: 0x2860,
    0x0006f4a0: 0x47c,
    0x00075d5c: 0x5e,
    0x0007712c: 0x466,
    0x00077594: 0x254,
    # Stream-format helper's final reachable branch is at 0x778c0.  The NOP
    # at 0x778c2 is alignment and literals occupy 0x778c4..0x778d4.
    0x00077820: 0xa2,
    # scanf conversion handlers and shared epilogue continue through 0x79272.
    0x00078f88: 0x2ea,
    0x000778d4: 0x0a,
    0x00078110: 0x45a,
    0x0007d1d6: 0x40,
    0x0007d3dc: 0x12,
    0x0007ee74: 0x32,
    0x00084e58: 0x0e,
    0x00085df6: 0x24,
    0x0008633e: 0x06,
    0x00086378: 0x08,
}
# Each reconstruction agent sets RECON_LEDGER to its own file to avoid races;
# merge later. Defaults to the shared ledger.
LEDGER = os.environ.get("RECON_LEDGER", SCRATCH + "/recon_ledger.json")

_md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
_fw = None; _cls = None

def _load():
    global _fw, _cls
    if _fw is None:
        _fw = {f["entry"]: f for f in json.load(open(SCRATCH + "/app_funcs.json"))["functions"]}
        _cls = {c["entry"]: c for c in json.load(open(SCRATCH + "/classified.json"))["functions"]}
        # overlay auto-derived names (from self-name logging strings) onto
        # functions the user never named, so info()/reconstructions use them.
        try:
            an = json.load(open(SCRATCH + "/autonames.json"))
            for a, d in an.items():
                e = int(a, 16)
                if e in _cls and not _cls[e].get("ida_name"):
                    _cls[e]["name"] = d["name"]
                    _cls[e]["auto_name"] = d["name"]
        except Exception:
            pass
    return _fw, _cls

def _litval(pc_addr, imm_str):
    """Resolve an ldr [pc,#imm] target address and the 32-bit value stored there."""
    m = re.search(r"#(0x[0-9a-fA-F]+|\d+)", imm_str)
    if not m:
        return None, None
    imm = int(m.group(1), 0)
    lit_addr = ((pc_addr + 4) & ~3) + imm
    try:
        return lit_addr, extract.read_u32(lit_addr)
    except Exception:
        return lit_addr, None

def info(va):
    fw, cls = _load()
    f = fw.get(va) or fw.get(va & ~1)
    if not f:
        return None
    c = cls.get(f["entry"], {})
    # correct Ghidra's occasionally-underestimated size (tail blocks past va+size)
    gsize = f["size"]
    try:
        from truesize import true_extent
        size = max(gsize, true_extent(f["entry"], gsize))
    except Exception:
        size = gsize
    size = TRUE_SIZE_OVERRIDES.get(f["entry"], size)
    code = extract.func_bytes_padded(f["entry"], size, pad=8)
    lines = []
    for i in _md.disasm(code, f["entry"]):
        ann = ""
        if "pc," in i.op_str and ("ldr" in i.mnemonic or "ldr.w" in i.mnemonic):
            la, lv = _litval(i.address, i.op_str)
            if lv is not None:
                ann = "   ; [0x%x] = 0x%08x" % (la, lv)
        if i.address >= f["entry"] + size:
            break
        lines.append("  %05x  %-9s %s%s" % (i.address, i.mnemonic, i.op_str, ann))
    identity_name = c.get("name") or f["name"]
    readable = (function_names.readable_name("app", f["entry"])
                if function_names.available("app") else identity_name)
    decompiled_raw = f["decompiled"]
    decompiled = (function_names.substitute(decompiled_raw, "app")
                  if function_names.available("app") else decompiled_raw)
    callee_records = []
    for callee in f["callees"]:
        match = re.fullmatch(r"(?:FUN_|sub_)0*([0-9a-fA-F]{3,8})", callee)
        address = (int(match.group(1), 16) & ~1) if match else (
            function_names.address_for_name("app", callee)
            if function_names.available("app") else None)
        callee_records.append({"identity": callee,
                               "address": hex(address) if address is not None else None,
                               "readable": (function_names.readable_name("app", address)
                                            if address is not None and function_names.available("app")
                                            else callee)})
    return {"name": identity_name, "readable_name": readable,
            "raw_name": function_names.raw_name("app", f["entry"]),
            "entry": f["entry"],
            "entry_hex": f["entry_hex"], "size": size,
            "class": c.get("class"),
            "callees": [record["readable"] for record in callee_records],
            "callee_records": callee_records,
            "decompiled": decompiled, "decompiled_raw": decompiled_raw,
            "function_name_map": function_names.MAP_PATH.get("app"),
            "disasm": "\n".join(lines)}

def _ret_kind(va):
    """Infer the ABI return kind from the Ghidra signature so the prover
    compares exactly the right return register(s): void / i32 / i64 / f32 / f64.
    """
    d = info(va)
    if not d or not d.get("decompiled"):
        return "i32"
    sig = ""
    for ln in d["decompiled"].splitlines():
        if "(" in ln and ln[:1] not in (" ", "\t", "{", ""):
            sig = ln.strip(); break
    low = sig.lower()
    rt = low.split("(")[0]
    # Disassembly is authoritative for float returns (Ghidra mislabels tiny VFP
    # leaves). If the last VFP-writing instruction targets s0/d0 before the
    # return, the ABI result is a float/double in that register.
    dis = d.get("disasm", "")
    last_vfp = None
    for ln in dis.splitlines():
        parts = ln.split()
        if len(parts) >= 3 and parts[1].startswith("v"):
            dst = parts[2].rstrip(",")
            if dst in ("s0", "d0"):
                last_vfp = dst
    if last_vfp == "s0":
        return "f32"
    if last_vfp == "d0":
        return "f64"
    if rt.startswith("void") and "*" not in rt:
        return "void"
    if "double" in rt:
        return "f64"
    if "float" in rt:
        return "f32"
    if any(t in rt for t in ("undefined8", "longlong", "long long", "uint64",
                             "int64", "ulonglong", "__int64")):
        return "i64"
    return "i32"

def prove(va, size, name, csrc, nptr=2, trials=300, save_src=True):
    meta = None if va & 1 else info(va)
    if not meta or meta["entry"] != va or meta["name"] != name:
        rec = {"name": name, "entry_hex": hex(va), "size": size,
               "ghidra_size": None, "pass": False, "stage": "identity",
               "error": "name/address does not match app catalog"}
    else:
        eff = meta["size"]
        import cfg_verify
        canonical_header = "/* Reconstructed %s @ %s  (CFG-directed candidate) */" % (
            name, hex(va))
        first_line, separator, remainder = csrc.partition("\n")
        if re.search(r'@\s+0x[0-9a-fA-F]+', first_line) and "*/" in first_line:
            after_header = first_line.split("*/", 1)[1]
            candidate = (canonical_header + after_header +
                         (separator + remainder if separator else "\n"))
        else:
            candidate = canonical_header + "\n" + csrc.rstrip() + "\n"
        candidate = re.sub(r'\bCFG_VERIFY_PREFIX_FIRST\b', '', candidate)
        candidate = re.sub(r'\bCFG_VERIFY_PREFIX_K=\d+\b', '', candidate)
        verdict = cfg_verify.verify("app", name, trials_random=trials,
                                    source_override=candidate)
        checked = verdict.get("checked")
        passed = verdict.get("status") == "PASS" and type(checked) is int and checked > 0
        rec = {"name": name, "entry_hex": hex(va), "size": eff,
               "ghidra_size": meta["size"], "pass": passed,
               "checked": checked, "mismatches": verdict.get("mismatches"),
               "stage": "cfg_verify", "cfg_status": verdict.get("status"),
               "detail": verdict.get("detail")}
    led = []
    if os.path.exists(LEDGER):
        led = json.load(open(LEDGER))
    led = [x for x in led if x["entry_hex"] != rec["entry_hex"]]
    led.append(rec)
    json.dump(led, open(LEDGER, "w"), indent=1)
    if save_src and rec.get("pass"):
        os.makedirs(RECON_SRC, exist_ok=True)
        open(os.path.join(RECON_SRC, name + ".c"), "w").write(candidate)
    return rec

def list_app(named_only=True, max_size=100000):
    fw, cls = _load()
    out = []
    for e, c in cls.items():
        if c["class"] != "APPLICATION" or c["is_thunk"]:
            continue
        if named_only and not c["ida_name"]:
            continue
        f = fw[e]
        out.append((f["size"], len(f["callees"]), c["name"], f["entry_hex"]))
    out.sort()
    return out

if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else "help"
    if cmd == "info":
        d = info(int(sys.argv[2], 0))
        print("### %s  [%s @ %s]  size=%d  class=%s" %
              (d["readable_name"], d["raw_name"], d["entry_hex"], d["size"], d["class"]))
        print("callees:", d["callee_records"])
        print("--- decompiled ---\n" + d["decompiled"])
        print("--- disasm (literal-pool values annotated) ---\n" + d["disasm"])
    elif cmd == "list-app":
        for s, nc, n, a in list_app():
            print("%5d  callees=%2d  %-34s %s" % (s, nc, n, a))
    elif cmd == "ledger":
        led = json.load(open(LEDGER)) if os.path.exists(LEDGER) else []
        p = sum(1 for x in led if x["pass"]); tot = len(led)
        print("PROVEN %d / %d" % (p, tot))
        for x in led:
            if not x["pass"]:
                print("  FAIL", x["name"], x["entry_hex"], x["stage"], (x["error"] or "")[:80])
