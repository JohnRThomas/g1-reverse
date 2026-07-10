"""Compile all symbolized sources + data tables for a core to objects, then
link-probe: partial-link them with the global pin script and report which symbols
resolve internally vs remain undefined (the latter should be library/Zephyr APIs).
This is the integration test the per-function parity proofs cannot give.
"""
import sys, os, glob, subprocess, concurrent.futures, collections, re

BASE = "/Users/freedomcoder/Projects/G1disasm2"
SDK = "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin"
CC = SDK + "/arm-zephyr-eabi-gcc"
LD = SDK + "/arm-zephyr-eabi-ld"
NM = SDK + "/arm-zephyr-eabi-nm"
CORE = sys.argv[1] if len(sys.argv) > 1 else "app"
FLAGS = ["-c", "-Os", "-mcpu=cortex-m33", "-mthumb", "-ffreestanding", "-w",
         "-ffunction-sections", "-fdata-sections", "-I", BASE + "/recon/symbols"]
OBJD = BASE + "/build/%s_obj" % CORE

def compile_all():
    os.makedirs(OBJD, exist_ok=True)
    srcs = sorted(glob.glob(BASE + "/recon/symbolized/%s/*.c" % CORE))
    if CORE == "app":
        srcs += sorted(glob.glob(BASE + "/recon/data/*.c"))
    def cc(f):
        o = os.path.join(OBJD, os.path.basename(f)[:-2] + ".o")
        r = subprocess.run([CC] + FLAGS + [f, "-o", o], capture_output=True, text=True)
        return (f, r.returncode, r.stderr)
    ok = fail = 0; ferr = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as ex:
        for f, rc, err in ex.map(cc, srcs):
            if rc == 0: ok += 1
            else: fail += 1; ferr.append((os.path.basename(f), err.strip().split("\n")[-1][:80]))
    print("compile: ok=%d fail=%d of %d" % (ok, fail, len(srcs)))
    for f, e in ferr[:8]: print("   FAIL", f, e)
    return ok

def link_probe():
    objs = sorted(glob.glob(OBJD + "/*.o"))
    out = BASE + "/build/%s_linked.elf" % CORE
    pin = BASE + "/recon/symbols/g1_%s_globals.ld" % CORE
    # partial link, ignore unresolved (they are library APIs); apply pin defs
    cmd = [LD, "-r", "-o", out] + objs
    r = subprocess.run(cmd, capture_output=True, text=True)
    print("partial-link rc=%d %s" % (r.returncode, r.stderr.strip()[:200]))
    # collect undefined symbols from the merged object
    u = subprocess.run([NM, "-u", out], capture_output=True, text=True)
    undef = [l.split()[-1] for l in u.stdout.splitlines() if l.strip()]
    # subtract pinned symbols (they're PROVIDEd at final link)
    pinned = set()
    for l in open(pin):
        m = re.search(r'PROVIDE\((\w+)', l)
        if m: pinned.add(m.group(1))
    real_undef = [s for s in undef if s not in pinned]
    # categorize
    LIBPAT = re.compile(r'^(k_|z_|sys_|bt_|net_|nrf|nrfx|hci|log|settings|nvs|flash_|gpio|spi|i2c|pwm|uart|adc|__|mem|str|_|q_|atomic|printf|snprintf|malloc|free|abort|assert)')
    lib = [s for s in real_undef if LIBPAT.match(s)]
    unknown = [s for s in real_undef if not LIBPAT.match(s)]
    print("undefined symbols: %d total | %d pinned-globals(resolved at final link) | %d library-like | %d UNKNOWN"
          % (len(undef), len(undef) - len(real_undef), len(lib), len(unknown)))
    print("--- UNKNOWN undefined (should be near-zero if reconstruction is internally complete) ---")
    for s in sorted(unknown)[:40]:
        print("  ", s)
    print("--- sample library-provided externs (expected) ---")
    for s in sorted(lib)[:15]:
        print("  ", s)

if __name__ == "__main__":
    if compile_all():
        link_probe()
