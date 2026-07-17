"""Full-link driver (phase 4). Compiles every symbolized source + data table +
blob for a core, links them at the ORIGINAL memory layout with the global-pin and
function-alias fragments, and reports what resolves vs what remains undefined.
Undefined should reduce to genuine external library symbols (Zephyr/newlib/libgcc/
CryptoCell) once reconstruction is complete. Emits build/<core>_full.elf.
"""
import sys, os, glob, subprocess, re, json, concurrent.futures, tempfile

BASE = "/Users/freedomcoder/Projects/G1disasm2"
SDK = "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin"
CC = SDK + "/arm-zephyr-eabi-gcc"; AS = SDK + "/arm-zephyr-eabi-as"
LD = SDK + "/arm-zephyr-eabi-ld"; NM = SDK + "/arm-zephyr-eabi-nm"
CORE = sys.argv[1] if len(sys.argv) > 1 else "app"
CF = ["-c", "-Os", "-mcpu=cortex-m33", "-mthumb", "-ffreestanding", "-w",
      "-ffunction-sections", "-fdata-sections", "-I", BASE + "/recon/symbols",
      "-I", BASE + "/recon/app/src", "-I", BASE + "/recon/net/src",
      "-I", "/Users/freedomcoder/ncs251/modules/lib/liblc3/include",
      "-I", "/Users/freedomcoder/ncs251/modules/lib/liblc3/src",
      "-I", "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include"]
OBJD = BASE + "/build/%s_full_obj" % CORE

LIBPAT = re.compile(r'^(k_|z_|sys_|bt_|net_buf|nrf|nrfx|hci|log_|logging|settings|nvs|'
    r'flash_|gpio|spim?|twim?|pwm|uarte?|adc|__aeabi|__div|__mul|__fix|__float|__extend|'
    r'__trunc|__udiv|__umod|mem(cpy|set|move|cmp)|str|q_|atomic|ring_|CC_|Instruction|'
    r'arch_|arm_|_impl|__gnu|snprintf|v?s?n?printf|malloc|free|abort|assert|k_is_in_isr|'
    r'z_impl|mpsl|sdc_|ecb|rng|entropy|clock_control|device_|__device|__init)')

def compile_all():
    os.makedirs(OBJD, exist_ok=True)
    # A renamed/generated source must not leave an old object participating in
    # the next partial link; that previously manufactured duplicate symbols.
    for stale in glob.glob(OBJD + "/*.o"):
        os.unlink(stale)
    srcs = glob.glob(BASE + "/recon/symbolized/%s/*.c" % CORE)
    if CORE == "app":
        srcs += glob.glob(BASE + "/recon/data/*.c")
    else:
        srcs += glob.glob(BASE + "/recon/net/data/*.c")
    blobs = glob.glob(BASE + "/recon/blobs/%s/*.S" % CORE)
    def cc(f):
        o = os.path.join(OBJD, os.path.basename(f).rsplit(".", 1)[0] + ".o")
        tool = AS if f.endswith(".S") else CC
        flags = ["-mcpu=cortex-m33", "-mthumb"] if f.endswith(".S") else CF
        r = subprocess.run([tool] + flags + [f, "-o", o], capture_output=True, text=True)
        return f, r.returncode, r.stderr
    ok = fail = 0
    failures = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as ex:
        for f, rc, stderr in ex.map(cc, srcs + blobs):
            ok += rc == 0; fail += rc != 0
            if rc != 0:
                failures.append((f, stderr.strip()))
    return ok, fail, len(srcs + blobs), failures

def link_and_report():
    objs = sorted(glob.glob(OBJD + "/*.o"))
    out = BASE + "/build/%s_full.elf" % CORE
    # Generated raw/readable aliases are safe to apply during the real partial
    # link because their target was observed defined in the previous clean ELF.
    defsym = []
    # Read the freshly compiled objects before trusting the direction of a
    # durable alias fragment.  Switching a core from raw to readable generated
    # sources reverses which side is defined; stale direction must not make the
    # otherwise valid partial link fail.
    defined = set()
    for obj in objs:
        for line in subprocess.run([NM, "-g", obj], capture_output=True,
                                   text=True).stdout.splitlines():
            fields = line.split()
            if len(fields) >= 3 and fields[-2] != "U":
                defined.add(fields[-1])
    generated_aliases = BASE + "/recon/symbols/g1_%s_function_aliases.ld" % CORE
    if os.path.exists(generated_aliases):
        for line in open(generated_aliases):
            match = re.search(r'PROVIDE\(([^\s=]+)\s*=\s*([^\s;)]+)', line)
            if match:
                alias, target = match.groups()
                if target in defined and alias not in defined:
                    defsym += ["--defsym", "%s=%s" % (alias, target)]
                elif alias in defined and target not in defined:
                    defsym += ["--defsym", "%s=%s" % (target, alias)]
    r = subprocess.run([LD, "-r", "-o", out] + defsym + objs,
                       capture_output=True, text=True)
    undef = [l.split()[-1] for l in subprocess.run([NM, "-u", out], capture_output=True, text=True).stdout.splitlines() if l.strip()]
    provided = set()
    for frag in ("g1_%s_globals.ld" % CORE, "g1_%s_aliases.ld" % CORE,
                 "g1_%s_function_aliases.ld" % CORE):
        p = BASE + "/recon/symbols/" + frag
        if os.path.exists(p):
            for l in open(p):
                m = re.search(r'PROVIDE\((\w+)', l)
                if m: provided.add(m.group(1))
    real = [s for s in undef if s not in provided]
    lib = [s for s in real if LIBPAT.match(s)]
    unknown = [s for s in real if not LIBPAT.match(s)]
    return {"link_rc": r.returncode, "link_err": r.stderr.strip()[:150],
            "undef_total": len(undef), "provided": len(undef) - len(real),
            "library": len(lib), "unknown": sorted(unknown)}

if __name__ == "__main__":
    ok, fail, tot, failures = compile_all()
    print("[%s] compiled %d/%d objects (%d fail)" % (CORE, ok, tot, fail))
    for path, error in failures[:50]:
        print("COMPILE_FAIL", os.path.relpath(path, BASE))
        print(error[:1200])
    rep = link_and_report()
    print("link rc=%d %s" % (rep["link_rc"], rep["link_err"]))
    print("undefined: %d total | %d pinned/aliased | %d library-external | %d UNKNOWN"
          % (rep["undef_total"], rep["provided"], rep["library"], len(rep["unknown"])))
    if rep["unknown"]:
        print("UNKNOWN (must be resolved/inspected):")
        for s in rep["unknown"][:50]:
            print("   ", s)
    json.dump(rep, open("/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad/fulllink_%s.json" % CORE, "w"), indent=1)
