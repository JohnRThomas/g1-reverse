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
from capstone import *

SCRATCH = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
RECON_SRC = "/Users/freedomcoder/Projects/G1disasm2/recon/app/src"
TRUE_SIZE_OVERRIDES = {
    0x0000e53c: 0x3fc,
    0x0000fcf0: 0x178,
    0x000113a8: 0xecc,
    0x00016eb8: 0x7ac,
    0x0001a064: 0x6e4,
    0x0001a75c: 0x6bae,
    0x00021460: 0x59c,
    0x00023844: 0x1d0,
    0x00028a1c: 0x198,
    0x0002a8d8: 0x3f4,
    0x00030cd0: 0x3a,
    0x0003727c: 0x3bdc,
    0x0003af78: 0x7e6,
    0x0003b824: 0x5ba,
    0x0003bfe0: 0xb4c,
    0x0003e7f8: 0xc80,
    0x000442bc: 0x266,
    0x0004588c: 0x110c,
    0x0004abc0: 0x444,
    0x0004b4fc: 0x394,
    0x0004bc8c: 0x166,
    0x0004beb8: 0x110,
    0x0004d100: 0x70,
    0x0004d578: 0x0e,
    0x0004e98c: 0x10,
    0x00050b8c: 0x24,
    0x000531cc: 0x08,
    0x0005505c: 0x34,
    0x000566a4: 0x50,
    0x00056704: 0x1e0,
    0x00059834: 0xe6,
    0x0005b9cc: 0x1e0,
    0x0005fb8c: 0xda,
    0x00068240: 0x3a,
    0x000698d0: 0xc82,
    0x0006b3c8: 0x5ea,
    0x0006bfc8: 0x7ae,
    0x0006c778: 0x2860,
    0x0006f4a0: 0x47c,
    0x00075d5c: 0x5e,
    0x0007712c: 0x466,
    0x00077594: 0x254,
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
    return {"name": c.get("name") or f["name"], "entry": f["entry"],
            "entry_hex": f["entry_hex"], "size": size,
            "class": c.get("class"), "callees": f["callees"],
            "decompiled": f["decompiled"], "disasm": "\n".join(lines)}

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
        print("### %s  %s  size=%d  class=%s" % (d["name"], d["entry_hex"], d["size"], d["class"]))
        print("callees:", d["callees"])
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
