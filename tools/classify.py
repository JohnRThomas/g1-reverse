"""
Classify every firmware function as LIBRARY or APPLICATION.

Evidence, in priority order:
  1. sig-match: normalized token signature equals a reference-ELF library
     function's signature  -> LIBRARY (strong; carries the matched name).
  2. name-match: the function's (IDA or Ghidra) name is a known library symbol
     present in the reference ELFs, or matches a library namespace prefix.
  3. otherwise APPLICATION.

Also merges the user's IDA symbol names (address->name from g1_rev_1.idc) onto
the Ghidra export so application functions carry their meaningful names.
"""

# Resolvable pipeline scratchpad (tools/g1_paths.py).  This used to be one
# literal /private/tmp path belonging to a finished agent session; see that
# module for the resolution order and the fail-closed catalog fallback.
import os as _g1_os, sys as _g1_sys
_G1_TOOLS = _g1_os.path.dirname(_g1_os.path.abspath(__file__))
if _g1_os.path.basename(_G1_TOOLS) != "tools":
    _G1_TOOLS = _g1_os.path.dirname(_G1_TOOLS)
if _G1_TOOLS not in _g1_sys.path:
    _g1_sys.path.insert(0, _G1_TOOLS)
import g1_paths as _g1_paths
import json, re, sys, hashlib
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
from ref_extract import sig_of

SCRATCH = _g1_paths.scratchpad()
IDC = "/Users/freedomcoder/Projects/G1disasm2/g1_rev_1.idc"

# library namespace prefixes / exact names (Zephyr, nrfx, BLE host, crypto, RTOS)
LIB_PREFIXES = (
    "z_", "k_", "arch_", "atomic_", "sys_", "cbprintf", "cbvprintf", "vsnprintk",
    "snprintk", "printk", "nrf_", "nrfx_", "nrfy_", "__nrfy", "bt_", "hci_",
    "gatt_", "att_", "smp_", "l2cap", "ecc_", "rpa_", "adv_", "scan_",
    "mbedtls_", "cc_mbedtls", "CC_", "LLF_", "RNG_", "nrf_cc3xx", "tc_",
    "entropy_", "ctr_drbg", "sha256", "sha_", "aes", "cmac", "hmac",
    "rpmsg_", "virtqueue_", "virtio_", "metal_", "ipc_", "mbox_", "ept_",
    "nvs_", "settings_", "flash_area_", "flash_page_", "flash_settings_",
    "qspi_", "nrf_qspi", "spim_", "twim_", "uarte_", "gpio_nrfx", "pinctrl_",
    "adc_", "saadc", "pwm_", "wdt_", "nvmc_", "net_buf", "log_", "z_log",
    "__aeabi", "__div", "__mul", "__float", "__fix", "__ext", "__trunc",
    "__udiv", "__ne", "_isr_wrapper", "region_init", "SystemInit",
    "nordicsemi_", "kmu_", "getTrngSource", "startTrngHW",
)
LIB_EXACT = set()

def load_idc_names():
    names = {}
    txt = open(IDC, errors="ignore").read()
    for m in re.finditer(r'set_name\((0x[0-9A-Fa-f]+),\s*"([^"]+)"\)', txt):
        addr = int(m.group(1), 16)
        names[addr] = m.group(2)
    return names

def is_lib_name(n):
    if not n:
        return False
    if n in LIB_EXACT:
        return True
    return n.startswith(LIB_PREFIXES)

def main():
    fw = json.load(open(SCRATCH + "/app_funcs.json"))
    ref = json.load(open(SCRATCH + "/ref_db.json"))
    by_sig = ref["by_sig"]
    lib_names = set(ref["names"].keys())
    idc = load_idc_names()

    out = []
    n_lib = n_app = n_sig = n_name = 0
    for f in fw["functions"]:
        addr = f["entry"]
        # thumb functions: entry may be odd in IDA; try both
        ida_name = idc.get(addr) or idc.get(addr & ~1) or idc.get(addr | 1)
        gname = f["name"]
        name = ida_name or (gname if not gname.startswith(("FUN_", "sub_")) else None)
        code = bytes.fromhex(f["bytes"]) if f["bytes"] else b""
        cls, ev, matched = "APPLICATION", "", None
        if code and not f["is_thunk"]:
            h, _ = sig_of(code, addr & ~1)
            if h and h in by_sig:
                cls, ev, matched = "LIBRARY", "sig", by_sig[h]
                n_sig += 1
        if cls == "APPLICATION":
            cand = name or gname
            if is_lib_name(cand) or (cand in lib_names):
                cls, ev = "LIBRARY", "name"
                n_name += 1
        if cls == "LIBRARY":
            n_lib += 1
        else:
            n_app += 1
        out.append({
            "entry": addr, "entry_hex": f["entry_hex"], "size": f["size"],
            "ghidra_name": gname, "ida_name": ida_name,
            "name": name or gname,
            "class": cls, "evidence": ev, "matched_lib": matched,
            "is_thunk": f["is_thunk"], "ncallees": len(f["callees"]),
            "has_decomp": bool(f["decompiled"]),
        })
    json.dump({"functions": out}, open(SCRATCH + "/classified.json", "w"))
    print("total:", len(out))
    print("LIBRARY:", n_lib, "  (by sig-match: %d, by name: %d)" % (n_sig, n_name))
    print("APPLICATION:", n_app)
    # app functions with decompilation and a real name, sorted by callee count
    app = [x for x in out if x["class"] == "APPLICATION" and not x["is_thunk"]]
    named_app = [x for x in app if x["ida_name"]]
    print("APPLICATION (non-thunk):", len(app), "| of which IDA-named:", len(named_app))

if __name__ == "__main__":
    main()
