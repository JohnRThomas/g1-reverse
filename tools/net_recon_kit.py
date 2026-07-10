"""Net-core reconstruction kit — mirrors recon_kit but for the network core
(base 0x01008000, bytes from netcore_image.bin). Reuses the FROZEN harness
(parity/recon.compile_func + parity/emu.compare) unchanged; only the original
bytes come from net_extract and emulation uses code_base=NET_CODE_BASE."""
import sys, os, json, re
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import net_extract as nx
from parity import recon, emu
from capstone import *

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
NET_SRC = "/Users/freedomcoder/Projects/G1disasm2/recon/net/src"
LEDGER = os.environ.get("RECON_LEDGER", SCR + "/net_recon_ledger.json")
_md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
_fw = None
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
    size = f["size"]
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
    return {"name": f["name"], "entry": f["entry"], "entry_hex": f["entry_hex"],
            "size": size, "callees": f["callees"], "decompiled": f["decompiled"],
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
    rk = _ret_kind(va)
    orig = nx.func_bytes_padded(va, size, pad=64)
    comp, err = recon.compile_func(csrc, name, va)
    if err:
        rec = {"name": name, "entry_hex": hex(va), "size": size, "pass": False,
               "stage": "compile", "error": str(err)[:300]}
    else:
        body, tail, csize, cva = comp
        v = emu.compare(orig, va, size, body + tail, cva, csize,
                        code_base=emu.NET_CODE_BASE, trials=trials, nptr=nptr, ret_kind=rk)
        if not v.get("pass") and v.get("checked") == 0:
            v = emu.compare(orig, va, size, body + tail, cva, csize,
                            code_base=emu.NET_CODE_BASE, trials=trials, nptr=nptr,
                            ret_kind=rk, no_return=True)
        rec = {"name": name, "entry_hex": hex(va), "size": size,
               "pass": bool(v.get("pass")), "checked": v.get("checked"),
               "mismatches": v.get("mismatches")}
        if v.get("pass") and save_src:
            os.makedirs(NET_SRC, exist_ok=True)
            open(os.path.join(NET_SRC, name + ".c"), "w").write(
                "/* net-core %s @ %s  (parity %d trials PROVEN) */\n%s\n"
                % (name, hex(va), v.get("checked"), csrc))
    led = json.load(open(LEDGER)) if os.path.exists(LEDGER) else []
    led = [x for x in led if x["entry_hex"] != rec["entry_hex"]] + [rec]
    json.dump(led, open(LEDGER, "w"), indent=1)
    return rec

if __name__ == "__main__":
    cmd = sys.argv[1]
    if cmd == "info":
        d = info(int(sys.argv[2], 0))
        print("###", d["name"], d["entry_hex"], "size", d["size"], "callees", d["callees"])
        print(d["decompiled"]); print(d["disasm"])
