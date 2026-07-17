"""Net-core reconstruction kit for the network-core firmware image.

Candidate persistence is gated by cfg_verify's CFG-directed side-effect proof;
this helper only supplies catalog/disassembly metadata and the proof ledger.
"""
import sys, os, json, re
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import net_extract as nx
import function_names
from capstone import *

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
NET_SRC = "/Users/freedomcoder/Projects/G1disasm2/recon/net/src"
LEDGER = os.environ.get("RECON_LEDGER", SCR + "/net_recon_ledger.json")
_md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
_fw = None
TRUE_SIZE_OVERRIDES = {
    # The controller connection-event timing planner owns all four TBH arms,
    # three terminal assertion tails, and its interleaved literal pools through
    # 0x0101364f.  FUN_01013650 is the next independent entry.
    0x01012f18: 0x738,
    # The catalog cuts the final invalid-state assertion BL in half.  That BL
    # ends at 0x0101ba4e; alignment/literals and FUN_0101ba58 follow.
    0x0101b7e4: 0x26a,
    # The catalog truncates the default TBB arm inside its MOVW.  The owned
    # noreturn controller-fault BL ends at 0x010164a6; alignment/literals follow.
    0x01016430: 0x76,
    # The final BL is the noreturn sys_reboot implementation.  The halfword
    # at 0x01031842 is alignment and the following words are literal data.
    0x01031820: 0x22,
    # Catalog 0x1e-byte extent truncates the acquire/release exclusive loop;
    # executable ownership continues through the shared return at 0x103435c.
    0x01034328: 0x36,
    # Catalog-missing radio transition and normalized handle/value updater.
    # The former is tail-owned by four dispatchers and spans its embedded
    # literals through the boundary before FUN_01021108; FUN_010294a2 owns the
    # latter through its exact tail branch at 0x010294aa.
    0x01020d1c: 0x3ec,
    0x0102946c: 0x36,
    # The TBB default/null-callback assertion tails continue through the BL at
    # 0x0100eeb0.  The five aligned literal words begin at 0x0100eeb4.
    0x0100ec88: 0x22c,
    # Ghidra stopped inside the force-ISR atomic loop.  The RTC1 ISR owns the
    # complete channel-processing tail through 0x010316ce; its five-word
    # literal pool then occupies 0x010316d0..0x010316e3.
    0x010315f0: 0xf4,
    # Three PHY-type TBH dispatches and seven branch-owned fatal tails are all
    # part of the scheduling snapshot builder.  The last tail BL ends at
    # 0x0101ab1e; FUN_0101ab20 is the next independent entry.
    0x0101a38c: 0x794,
    # Catalog-missing entry points with exact executable ownership proven by
    # direct branches from FUN_01013650, FUN_0102946c/FUN_0101e15c,
    # FUN_0100cb10, and FUN_0101fc14 respectively.
    0x01016144: 0x16,
    0x0101e0a4: 0x68,
    0x0101e15c: 0x04,
    0x0101fd8c: 0x2c,
    0x0101fdc0: 0x0a,
    # Three real internal entry points omitted from the Ghidra catalog.  Each
    # is reached by an exact direct tail branch from a catalogued caller.
    # 0x0100eec8 ends at its fatal assertion BL; its queue literal is ef04.
    0x0100eec8: 0x3c,
    # Retry/descriptor completion tails through 0x010128ae; 128b2 is
    # alignment and its two literals occupy 128b4..128bc.
    0x010127f8: 0xba,
    # Scheduler division/round-up helper ends before its 217fc literal.
    0x010217cc: 0x30,
    0x0102d1c0: 0x7a,  # disable path rejoins return at 0x0102d238
    # Catalog-missing rpmsg endpoint delivery adapter.  Its final ordinary
    # return ends at 0x0102d6da; the aligned callback literal follows.
    0x0102d69c: 0x3e,
    # Default return island owns the back-branch at 0x01030ef6; the literal
    # starts at 0x01030ef8 and the next prologue at 0x01030efc.
    0x01030e28: 0xd0,
    # Both branch-reachable fatal tails end at 0x01012c04; a literal follows
    # and FUN_01012c08 is the next independent entry.
    0x01012ba4: 0x60,
    # Reachable arithmetic continues through the return at 0x0102dfde;
    # literals begin at 0x0102dfe0.
    0x0102df2c: 0xb4,
    # Switch-owned cases/default continue through 0x01026646; the next
    # independent function begins at 0x01026648.
    0x01026122: 0x526,
    # Catalog stops before the terminal diagnostic BL at 0x0100b108;
    # executable code ends immediately before literals at 0x0100b10c.
    0x0100aff4: 0x118,
    # Late case-one islands end at the final returns immediately before the
    # following alignment/independent functions.
    0x01019f34: 0x68,
    0x0101a070: 0x78,
    # Event dispatcher ends before the 0x0101ad34 literal and FUN_0101ad38.
    0x0101ab20: 0x214,
    # Final BASEPRI restore/loop backedge ends before literals at 0x01038644.
    0x010384a8: 0x19c,
    0x0100ac98: 0x202,
    0x0100b180: 0x402,
    0x0100cb10: 0x14,
    0x0100dfbc: 0x4c,
    0x01013e98: 0x1cc,
    0x0101b15c: 0xce,
    0x0101e2cc: 0x30,
    0x0101fc14: 0x16,
    0x0102bbec: 0x3f0,  # late copy loop and aligned-error return precede literals
    # Deferred-string callback loop and its error joins end immediately
    # before the literal pool at 0x0102c420.
    0x0102bfe4: 0x43c,
    0x0101ba58: 0x13c,  # renderer diagnostics end before independent helpers
    # LLCP RX dispatcher owns its complete jump-table setup and literal pool
    # boundary through 0x010187e0; catalog stopped inside its pointer table.
    0x01018690: 0x150,
    0x01021838: 30,     # wrapper ends at tail call; following code is separate
    0x0101bdd4: 0x10e,  # owned default diagnostic ends before literals
    0x01020a00: 0x60,   # owned default diagnostic ends before literals
    # printf-like late formatting islands rejoin through 0x01039618; the
    # catalog's 0x448-byte extent stops inside the sign-emission path.
    0x01039190: 0x48a,
    0x01020168: 0xc2,
    0x01021cec: 0xf8,
    0x01031248: 0x38,
    0x010312d0: 0x3c,
    0x010122fc: 0x30,
    0x0102d1c0: 0x7a,
    # ipc_rpmsg_static_vrings.c:open; Ghidra stopped after its prologue.
    # The complete function returns at 0x0102d8a0, where its literal pool starts.
    0x0102d708: 0x198,
    0x0102d938: 0xdc,
    0x0103a076: 0xb6,
    0x01028464: 0x22,
    0x01028486: 0x22,
    0x01032764: 0x2e,
    0x0100d58c: 0x3c,
    0x010333b4: 0x22c,
    0x010294a2: 0x0c,
    0x0102de38: 0x14,
    0x0102e23c: 0x3a,
    0x0103038c: 0x10c,
    0x010323cc: 0x26,
    0x01034368: 0x30,
    0x0103601c: 0xda,
    # Catalog-missing kernel ownership-release body.  Its final error return
    # ends at 0x0103664a; aligned logging/kernel-object literals follow.
    0x0103657c: 0xce,
    0x01037f00: 0x0e,
    0x01038654: 0x100,
    0x01039fb6: 0x0e,
    0x01039fe6: 0x70,
    0x0103a294: 0x12,
    0x0103a3ce: 0x08,
    # Ten-byte nested-limit adapter; the catalog incorrectly follows its
    # 0x0102fdd0 tail target and attributes that callee's body to this entry.
    0x0103a44c: 0x0a,
    0x0103a8d0: 0x16,
    0x0103b0e8: 0x08,
    0x0103b1c4: 0x10,
    0x0103b530: 0x08,
    0x010119ac: 0x1d8,
    # CFG-reviewed TBH handlers and fatal tails through 0x101d87c.
    0x0101d404: 0x478,
}
def _load():
    global _fw
    if _fw is None:
        _fw = {f["entry"]: f for f in json.load(open(SCR + "/net_funcs.json"))["functions"]}
    return _fw

def _litval(pc, imm):
    m = re.search(r"#(0x[0-9a-fA-F]+|\d+)", imm)
    if not m:
        return None, None
    la = ((pc + 4) & ~3) + int(m.group(1), 0)
    return la, nx.read_u32(la)

def info(va):
    fw = _load()
    f = fw.get(va) or fw.get(va & ~1)
    if not f:
        return None
    size = TRUE_SIZE_OVERRIDES.get(f["entry"], f["size"])
    code = nx.func_bytes_padded(f["entry"], size, 8)
    lines = []
    for i in _md.disasm(code, f["entry"]):
        ann = ""
        if "pc," in i.op_str and "ldr" in i.mnemonic:
            la, lv = _litval(i.address, i.op_str)
            if lv is not None:
                ann = "   ; [0x%x] = 0x%08x" % (la, lv)
        if i.address >= f["entry"] + size:
            break
        lines.append("  %05x  %-9s %s%s" % (i.address, i.mnemonic, i.op_str, ann))
    readable = (function_names.readable_name("net", f["entry"])
                if function_names.available("net") else f["name"])
    decompiled_raw = f["decompiled"]
    decompiled = (function_names.substitute(decompiled_raw, "net")
                  if function_names.available("net") else decompiled_raw)
    callee_records = []
    for callee in f["callees"]:
        match = re.fullmatch(r"(?:FUN_|sub_)0*([0-9a-fA-F]{3,8})", callee)
        address = (int(match.group(1), 16) & ~1) if match else (
            function_names.address_for_name("net", callee)
            if function_names.available("net") else None)
        callee_records.append({"identity": callee,
                               "address": hex(address) if address is not None else None,
                               "readable": (function_names.readable_name("net", address)
                                            if address is not None and function_names.available("net")
                                            else callee)})
    return {"name": f["name"], "readable_name": readable,
            "raw_name": function_names.raw_name("net", f["entry"]),
            "entry": f["entry"], "entry_hex": f["entry_hex"],
            "size": size,
            "callees": [record["readable"] for record in callee_records],
            "callee_records": callee_records,
            "decompiled": decompiled, "decompiled_raw": decompiled_raw,
            "function_name_map": function_names.MAP_PATH.get("net"),
            "disasm": "\n".join(lines)}

def _ret_kind(va):
    d = info(va)
    dis = d.get("disasm", "") if d else ""
    last = None
    for ln in dis.splitlines():
        p = ln.split()
        if len(p) >= 3 and p[1].startswith("v"):
            dst = p[2].rstrip(",")
            if dst in ("s0", "d0"):
                last = dst
    if last == "s0":
        return "f32"
    if last == "d0":
        return "f64"
    sig = (d.get("decompiled", "") if d else "").strip().split("(")[0].lower() if d else ""
    if sig.startswith("void") and "*" not in sig:
        return "void"
    if any(t in sig for t in ("undefined8", "longlong", "uint64", "int64")):
        return "i64"
    return "i32"

def prove(va, size, name, csrc, nptr=2, trials=300, save_src=True):
    # Entry points in the catalogs are canonical even Thumb addresses.  An odd
    # alias must not select a different override/ledger key while verification
    # silently normalizes it to the same code.
    meta = None if va & 1 else info(va)
    if not meta or meta["entry"] != va or meta["name"] != name:
        rec = {"name": name, "entry_hex": hex(va), "size": size, "pass": False,
               "stage": "identity", "error": "name/address does not match net catalog"}
    else:
        # Ignore caller-supplied bounds. info() applies the synchronized,
        # CFG-reviewed override when one exists and catalog metadata otherwise.
        size = meta["size"]
        # Import lazily: cfg_verify imports this module for net-core metadata.
        # The source override lets CFG verification gate a candidate before it
        # is persisted, rather than re-reading the previous on-disk source.
        import cfg_verify
        canonical_header = "/* net-core %s @ %s  (CFG-directed candidate) */" % (
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
        verdict = cfg_verify.verify("net", name, trials_random=trials,
                                    source_override=candidate)
        checked = verdict.get("checked")
        passed = verdict.get("status") == "PASS" and type(checked) is int and checked > 0
        rec = {"name": name, "entry_hex": hex(va), "size": size,
               "pass": passed, "stage": "cfg_verify",
               "checked": checked,
               "mismatches": verdict.get("mismatches"),
               "cfg_status": verdict.get("status"),
               "detail": verdict.get("detail")}
        if passed and save_src:
            os.makedirs(NET_SRC, exist_ok=True)
            open(os.path.join(NET_SRC, name + ".c"), "w").write(candidate)
    led = json.load(open(LEDGER)) if os.path.exists(LEDGER) else []
    led = [x for x in led if x["entry_hex"] != rec["entry_hex"]] + [rec]
    json.dump(led, open(LEDGER, "w"), indent=1)
    return rec

if __name__ == "__main__":
    cmd = sys.argv[1]
    if cmd == "info":
        d = info(int(sys.argv[2], 0))
        print("###", d["readable_name"], "[%s @ %s]" % (d["raw_name"], d["entry_hex"]),
              "size", d["size"], "callees", d["callee_records"])
        print(d["decompiled"]); print(d["disasm"])
