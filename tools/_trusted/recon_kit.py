"""
Reconstruction kit used by reconstruction subagents.

Per function it resolves everything needed to write a faithful C reconstruction
whose recompilation can be PROVEN byte-for-behavior identical to the firmware:

  info(va)  -> {decompiled, disasm(annotated with literal-pool VALUES),
                callees, size, name}
  prove(va, size, name, csrc, nptr, trials) -> parity verdict, appended to a
                shared JSON ledger (recon_ledger.json).

CLI:
  python recon_kit.py info 0x327c4        # dump everything for one function
  python recon_kit.py list-app            # list application functions to do
  python recon_kit.py ledger              # summary of proven/failed
"""
import sys, os, json, re
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import extract
from parity import recon
from capstone import *

SCRATCH = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
RECON_SRC = "/Users/freedomcoder/Projects/G1disasm2/recon/app/src"
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
    rk = _ret_kind(va)
    # Correct Ghidra's occasionally-underestimated size so the harness's in-body
    # range [va, va+size) covers tail blocks / switch handlers the function
    # branches into (otherwise they look like spurious external calls).
    try:
        from truesize import true_extent
        eff = max(size, true_extent(va, size))
    except Exception:
        eff = size
    v = recon.prove(va, eff, csrc, name, trials=trials, nptr=nptr, ret_kind=rk)
    # Non-returning supervisor loop (main / *_thread): every trial ran to the
    # cap without returning, so nothing was checked. Retry comparing the ordered
    # side-effect prefix instead of a return value.
    if not v.get("pass") and v.get("checked") == 0:
        v2 = recon.prove(va, eff, csrc, name, trials=trials, nptr=nptr,
                         ret_kind=rk, no_return=True)
        if v2.get("checked"):
            v = v2
    rec = {"name": name, "entry_hex": hex(va), "size": eff, "ghidra_size": size,
           "pass": bool(v.get("pass")), "checked": v.get("checked"),
           "mismatches": v.get("mismatches"), "cand_size": v.get("cand_size"),
           "stage": v.get("stage"), "error": str(v.get("error"))[:300] if v.get("error") else None}
    led = []
    if os.path.exists(LEDGER):
        led = json.load(open(LEDGER))
    led = [x for x in led if x["entry_hex"] != rec["entry_hex"]]
    led.append(rec)
    json.dump(led, open(LEDGER, "w"), indent=1)
    if save_src and v.get("pass"):
        os.makedirs(RECON_SRC, exist_ok=True)
        open(os.path.join(RECON_SRC, name + ".c"), "w").write(
            "/* Reconstructed %s @ %s  (parity: %d/%d trials, PROVEN) */\n%s\n"
            % (name, hex(va), v.get("checked"), trials, csrc))
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
