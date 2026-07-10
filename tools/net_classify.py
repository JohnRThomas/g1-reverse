"""Net-core self-naming + library classification, so reconstruction targets only
the net core's own APPLICATION logic (display/brightness/box/IPC glue) and skips
the Nordic radio controller + Zephyr (upstream). Same self-name-string trick as
the app core, plus namespace-based library exclusion tuned for the net core
(the controller/MPSL/ESB/kernel are library)."""
import json, re, string, sys
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import net_extract as nx

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]{3,63}$")
DAT = re.compile(r"DAT_([0-9a-fA-F]{4,8})")
PRINT = set(bytes(string.printable, "ascii")) - {0}
STOP = {"NULL", "true", "false", "size", "value", "data", "count", "state",
        "index", "status", "error", "result", "type", "name", "length"}
# net-core library namespaces: Zephyr kernel/drivers + Nordic radio stack
LIBP = ("z_", "k_", "arch_", "sys_", "nrf_", "nrfx_", "nrfy_", "sdc_", "SDC_",
        "mpsl_", "MPSL_", "esb_", "ll_", "lll_", "hci_", "hal_", "rpmsg_",
        "virtqueue_", "virtio_", "metal_", "ipc_", "mbox_", "ecb_", "ccm_",
        "radio_", "ram_", "__aeabi", "__div", "__udiv", "cbprintf", "printk",
        "log_", "z_log", "net_buf", "atomic_", "entropy_", "clock_control",
        "gpio_nrfx", "nrf5_", "spinlock")

def read_cstr(va, maxlen=80):
    b = nx.read(va, maxlen)
    out = bytearray()
    for ch in b:
        if ch == 0:
            break
        if ch not in PRINT:
            return None
        out.append(ch)
    return out.decode("ascii", "ignore") if out else None

def self_name(decomp):
    strs = []
    for m in DAT.finditer(decomp):
        try:
            ptr = nx.read_u32(int(m.group(1), 16))
        except Exception:
            continue
        if ptr is None:
            continue
        # string pointer is a real-firmware VA within the net image
        if nx.NET_REAL_BASE <= ptr < nx.NET_REAL_BASE + 0x40000:
            s = read_cstr(ptr)
            if s:
                strs.append(s)
    has_fmt = any("%s()" in s or "():" in s for s in strs)
    idents = [s for s in dict.fromkeys(strs)
              if IDENT.match(s) and s not in STOP and "%" not in s and "(" not in s]
    if has_fmt and idents:
        return idents[0]
    return None

def is_lib(name):
    return bool(name) and name.startswith(LIBP)

def main():
    fns = json.load(open(SCR + "/net_funcs.json"))["functions"]
    out = []
    n_lib = n_app = n_named = 0
    for f in fns:
        if f["is_thunk"]:
            continue
        nm = self_name(f["decompiled"]) if f["decompiled"] else None
        if nm:
            n_named += 1
        # classify: library if self-name or any callee is a library namespace
        lib = is_lib(nm) or any(is_lib(c) for c in f["callees"])
        cls = "LIBRARY" if lib else "APPLICATION"
        if cls == "LIBRARY":
            n_lib += 1
        else:
            n_app += 1
        out.append({"entry": f["entry"], "entry_hex": f["entry_hex"], "size": f["size"],
                    "name": nm or f["name"], "self_name": nm, "class": cls,
                    "ncallees": len(f["callees"]), "has_decomp": bool(f["decompiled"])})
    json.dump({"functions": out}, open(SCR + "/net_classified.json", "w"))
    app = [x for x in out if x["class"] == "APPLICATION"]
    appb = sum(x["size"] for x in app)
    print("net-core non-thunk functions:", len(out))
    print("  self-named (R1 strings):", n_named)
    print("  LIBRARY (controller/Zephyr, excluded):", n_lib)
    print("  APPLICATION (reconstruction target):", n_app, "(%d bytes)" % appb)
    print("  of which named:", sum(1 for x in app if x["self_name"]))
    # sample app functions
    for x in sorted(app, key=lambda z: -z["size"])[:12]:
        print("    %6d  %-30s %s" % (x["size"], x["name"], x["entry_hex"]))

if __name__ == "__main__":
    main()
