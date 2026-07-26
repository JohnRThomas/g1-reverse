"""Full-link driver (phase 4). Compiles every symbolized source + data table +
blob for a core, links them at the ORIGINAL memory layout with the global-pin and
function-alias fragments, and reports what resolves vs what remains undefined.
Undefined should reduce to genuine external library symbols (Zephyr/newlib/libgcc/
CryptoCell) once reconstruction is complete. Emits build/<core>_full.elf.
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
if CORE == "app":
    # Match the cohesive CPUAPP CMake build: reviewed local SDK helpers are
    # inlined only into their retained owning callers.
    CF.append("-DG1_APP_SDK_INLINE_COHESION=1")
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
    # Reviewed veneer aliases are directional: their source VA is an exact
    # tail branch to a different function entry.  Unlike readable/raw identity
    # aliases, reversing one would change ownership and is never valid.
    reviewed_veneers = BASE + "/recon/symbols/g1_%s_veneer_aliases.ld" % CORE
    public_sdk_aliases = BASE + "/recon/symbols/g1_%s_public_sdk_aliases.ld" % CORE
    readable_aliases = BASE + "/recon/symbols/g1_%s_readable_aliases.ld" % CORE
    for directional_fragment in (reviewed_veneers, public_sdk_aliases,
                                 readable_aliases):
        if not os.path.exists(directional_fragment):
            continue
        for line in open(directional_fragment):
            match = re.search(r'PROVIDE\(([^\s=]+)\s*=\s*([^\s;)]+)', line)
            if not match:
                continue
            alias, target = match.groups()
            if target in defined and alias not in defined:
                defsym += ["--defsym", "%s=%s" % (alias, target)]
    r = subprocess.run([LD, "-r", "-o", out] + defsym + objs,
                       capture_output=True, text=True)
    undef = [l.split()[-1] for l in subprocess.run([NM, "-u", out], capture_output=True, text=True).stdout.splitlines() if l.strip()]
    provided = set()
    for frag in ("g1_%s_globals.ld" % CORE, "g1_%s_aliases.ld" % CORE,
                 "g1_%s_function_aliases.ld" % CORE,
                 "g1_%s_veneer_aliases.ld" % CORE,
                 "g1_%s_public_sdk_aliases.ld" % CORE,
                 "g1_%s_readable_aliases.ld" % CORE,
                 "g1_%s_sdk_state.ld" % CORE):
        p = BASE + "/recon/symbols/" + frag
        if os.path.exists(p):
            for l in open(p):
                m = re.search(r'PROVIDE\((\w+)', l)
                if m:
                    provided.add(m.group(1))
                    continue
                # Cohesive state aliases use strong linker assignments so a
                # selected SDK object's storage wins over fixed-address
                # reconstruction fallbacks.  The standalone partial link has
                # no SDK objects, but these names are still reviewed/resolved
                # by the production linker fragment rather than unknowns.
                m = re.match(r'\s*([A-Za-z_$][\w$]*)\s*=', l)
                if m:
                    provided.add(m.group(1))
    real = [s for s in undef if s not in provided]
    lib = [s for s in real if LIBPAT.match(s)]
    unknown = [s for s in real if not LIBPAT.match(s)]
    reviewed = []
    reviewed_by_category = {}
    unknown_by_disposition = {}
    # Pattern classification deliberately stays conservative.  CPUAPP's
    # non-pattern residue has a generated fail-closed audit: only symbols in
    # the exact current full-link set, with retained-caller/owner evidence,
    # may leave UNKNOWN.  Genuine SDK externals join the library bucket;
    # excluded-owner byproducts and compiler pseudo spellings remain visible
    # as reviewed report-only residue.
    if CORE == "app":
        audit_path = BASE + "/recon/catalogs/app_full_link_unknown_audit.json"
        if os.path.exists(audit_path):
            audit = json.load(open(audit_path))
            rows = {row["symbol"]: row for row in audit.get("entries", [])}
            if set(rows) != set(unknown):
                missing = sorted(set(unknown) - set(rows))
                stale = sorted(set(rows) - set(unknown))
                raise RuntimeError(
                    "CPUAPP UNKNOWN audit drift (missing=%s stale=%s)" %
                    (missing, stale))
            for symbol in unknown:
                row = rows[symbol]
                category = row.get("category")
                if row.get("action") != "report_only":
                    raise RuntimeError("non-report-only UNKNOWN audit row: " + symbol)
                if category == "genuine_sdk_library_external":
                    lib.append(symbol)
                elif category in ("duplicate_owner_byproduct",
                                  "ghidra_compiler_pseudo"):
                    reviewed.append(symbol)
                    reviewed_by_category[category] = (
                        reviewed_by_category.get(category, 0) + 1)
                else:
                    raise RuntimeError("unsupported UNKNOWN audit category for %s: %r" %
                                       (symbol, category))
            unknown = []
    elif CORE == "net":
        audit_path = BASE + "/recon/catalogs/net_link_function_residue.json"
        if not os.path.exists(audit_path):
            raise RuntimeError("missing fail-closed CPUNET link-residue audit")
        audit = json.load(open(audit_path))
        rows = {row["symbol"]: row for row in audit.get("entries", [])}
        audited_nonpattern = {
            symbol for symbol in rows if not LIBPAT.match(symbol)
        }
        if audited_nonpattern != set(unknown):
            missing = sorted(set(unknown) - audited_nonpattern)
            stale = sorted(audited_nonpattern - set(unknown))
            raise RuntimeError(
                "CPUNET UNKNOWN audit drift (missing=%s stale=%s)" %
                (missing, stale))
        unresolved = []
        for symbol in unknown:
            row = rows[symbol]
            category = row.get("category")
            if category == "sdk_or_config_symbol":
                lib.append(symbol)
            elif category == "compiler_or_ghidra_pseudo":
                reviewed.append(symbol)
                reviewed_by_category[category] = (
                    reviewed_by_category.get(category, 0) + 1)
            elif category == "true_missing_reconstructed_entry":
                disposition = row.get("closeout_disposition")
                if not disposition or row.get("closeout_actionable") is None:
                    raise RuntimeError(
                        "CPUNET missing entry lacks explicit closeout: " + symbol)
                unresolved.append(symbol)
                unknown_by_disposition[disposition] = (
                    unknown_by_disposition.get(disposition, 0) + 1)
            else:
                raise RuntimeError(
                    "unsupported CPUNET UNKNOWN audit category for %s: %r" %
                    (symbol, category))
        unknown = unresolved
    return {"link_rc": r.returncode, "link_err": r.stderr.strip()[:150],
            "undef_total": len(undef), "provided": len(undef) - len(real),
            "library": len(lib), "reviewed": sorted(reviewed),
            "reviewed_by_category": reviewed_by_category,
            "unknown_by_disposition": unknown_by_disposition,
            "unknown": sorted(unknown)}

if __name__ == "__main__":
    ok, fail, tot, failures = compile_all()
    print("[%s] compiled %d/%d objects (%d fail)" % (CORE, ok, tot, fail))
    for path, error in failures[:50]:
        print("COMPILE_FAIL", os.path.relpath(path, BASE))
        print(error[:1200])
    rep = link_and_report()
    print("link rc=%d %s" % (rep["link_rc"], rep["link_err"]))
    print("undefined: %d total | %d pinned/aliased | %d library-external | "
          "%d reviewed-report-only | %d UNKNOWN"
          % (rep["undef_total"], rep["provided"], rep["library"],
             len(rep["reviewed"]), len(rep["unknown"])))
    if rep["reviewed"]:
        print("reviewed residue:", json.dumps(rep["reviewed_by_category"], sort_keys=True))
    if rep["unknown_by_disposition"]:
        print("UNKNOWN dispositions:",
              json.dumps(rep["unknown_by_disposition"], sort_keys=True))
    if rep["unknown"]:
        print("UNKNOWN (must be resolved/inspected):")
        for s in rep["unknown"][:50]:
            print("   ", s)
    json.dump(rep, open(_g1_paths.scratchpad() + '/fulllink_%s.json' % CORE, "w"), indent=1)
