"""
Compile a reconstructed C function for Cortex-M33 and prove semantic parity
against the original firmware bytes using the differential emulator.

Reconstruction convention (makes parity exact):
  * Globals are expressed as fixed absolute-address pointers, using the literal
    values found in the original function's literal pool. So the recompiled
    code dereferences the SAME addresses -> reads the SAME (seeded) memory.
  * Callees are opaque; the emulator models them as identical order/arg-keyed
    oracles for both original and candidate.
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
import os, re, json, subprocess, tempfile, sys
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
from elftools.elf.elffile import ELFFile
import extract
from parity import emu

GCC = "arm-none-eabi-gcc"
LAST_DIRECT_TARGET_MAP = {}
_SEMANTIC_NAME_MAPS = {}
_BASE = "/Users/freedomcoder/Projects/G1disasm2"
_SCR = (_g1_paths.scratchpad())

def _semantic_name_map(core):
    """Return unambiguous external symbol name -> original firmware VA.

    Raw FUN names are sufficient for early reconstructions, but readable C
    calls SDK/library and renamed application symbols.  Those identities are
    equally semantic and must not collapse to call ordinal merely because the
    generated oracle stubs move at link time.
    """
    if core in _SEMANTIC_NAME_MAPS:
        return _SEMANTIC_NAME_MAPS[core]
    candidates = {}
    def add(name, va):
        if not name:
            return
        candidates.setdefault(name, set()).add(int(va) & ~1)
    catalog = "net_funcs.json" if core == "net" else "app_funcs.json"
    try:
        obj = _g1_paths.load_catalog(catalog)
        funcs = obj.get("functions", obj) if isinstance(obj, dict) else obj
        for f in funcs:
            va = f.get("entry", f.get("address"))
            if va is None:
                continue
            for key in ("name", "ida_name", "ghidra_name"):
                add(f.get(key), va)
            for name in (f.get("matched_lib") or ()):
                add(name, va)
    except (OSError, ValueError, TypeError):
        pass
    # Durable readable aliases survive scratchpad loss and include semantic
    # names recovered after the original Ghidra/IDA catalogs were exported.
    manifest = os.path.join(
        _BASE, "recon/catalogs/function_names_%s.json" % core)
    try:
        for address, record in json.load(open(manifest))["by_address"].items():
            va = int(address, 16)
            add(record.get("name"), va)
            add(record.get("raw_name"), va)
            for name in record.get("aliases", ()):
                add(name, va)
    except (OSError, ValueError, KeyError, TypeError):
        pass
    # Alias linker entries preserve the raw address on the left while naming
    # the readable implementation on the right.
    alias = os.path.join(_BASE, "recon/symbols/g1_%s_aliases.ld" % core)
    try:
        for line in open(alias):
            m = re.search(r'PROVIDE\(FUN_([0-9a-fA-F]{8})[^=]*=\s*([A-Za-z_$][\w$]*)\s*\)', line)
            if m:
                add(m.group(2), int(m.group(1), 16))
    except OSError:
        pass
    result = {name: next(iter(values)) for name, values in candidates.items()
              if len(values) == 1}
    _SEMANTIC_NAME_MAPS[core] = result
    return result
CFLAGS = ["-mcpu=cortex-m33", "-mthumb", "-Os", "-ffreestanding", "-nostdlib",
          # Preserve the firmware-era C rule that an empty parameter list is
          # unprototyped. Newer host GCC defaults to gnu23 where `f()` means
          # `f(void)`, rejecting recovered callees whose exact arity varies.
          "-std=gnu11",
          # match the nRF5340 app core: single-precision hardware FPU, hard-float
          # ABI, so float arithmetic compiles to inline VFP (not __aeabi_* calls)
          "-mfpu=fpv5-sp-d16", "-mfloat-abi=hard",
          # The shipped image uses the hardware VSQRT instruction directly;
          # errno-setting libm fallbacks are not part of this freestanding ABI.
          "-fno-math-errno",
          "-I/Users/freedomcoder/ncs251/modules/lib/liblc3/include",
          "-I/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include",
          # Reconstructed functions may be split into readable, always-inlined
          # family includes.  The temporary parity TU keeps only the canonical
          # .c text, so expose both reconstruction source roots explicitly.
          "-I/Users/freedomcoder/Projects/G1disasm2/recon/app/src",
          "-I/Users/freedomcoder/Projects/G1disasm2/recon/net/src",
          "-isystem/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/include",
          "-fno-jump-tables", "-fomit-frame-pointer", "-c"]

def _undef_syms(opath):
    with open(opath, "rb") as f:
        elf = ELFFile(f)
        st = elf.get_section_by_name(".symtab")
        out = []
        for s in st.iter_symbols():
            if s.name and s["st_shndx"] == "SHN_UNDEF":
                out.append(s.name)
    return sorted(set(out))

def compile_func(csrc, func_name, link_va, extra_cflags=None):
    """Compile the reconstructed function AND link it at its real VA with a
    generated stub for every external callee, so that `bl <callee>` targets an
    address OUTSIDE the function body (detectable as a call by the emulator)."""
    # A readable reconstruction may name a callee semantically while retaining
    # its raw identity in the declaration comment:
    #
    #   extern int process_task_state_four(...); /* FUN_0002c714 */
    #
    # Treat that explicit back-map as first-class identity.  The durable
    # catalog remains the fallback, but newly recovered names no longer lose
    # call-target strictness while waiting for a catalog regeneration.
    source_backmaps = {}
    source_backmap_pattern = re.compile(
        r'\bextern\b[^;\n]*?\b([A-Za-z_$][\w$]*)\s*\([^;\n]*\)\s*;'
        r'\s*/\*\s*(?:=\s*)?FUN_([0-9a-fA-F]{3,8})\b')
    for match in source_backmap_pattern.finditer(csrc):
        name = match.group(1)
        address = int(match.group(2), 16) & ~1
        previous = source_backmaps.setdefault(name, address)
        if previous != address:
            return None, ("ambiguous source back-map for %s: 0x%x vs 0x%x" %
                          (name, previous, address))

    d = tempfile.mkdtemp(prefix="parity_")
    cpath = os.path.join(d, "f.c"); opath = os.path.join(d, "f.o")
    open(cpath, "w").write(csrc)
    r = subprocess.run([GCC] + CFLAGS + (extra_cflags or []) + [cpath, "-o", opath],
                       capture_output=True, text=True)
    if r.returncode != 0:
        return None, "cc: " + r.stderr
    undef = [s for s in _undef_syms(opath) if s != func_name]
    # generate distinct stub bodies (each 8 bytes so they occupy separate addrs)
    # Keep every callee at a distinct address. Identical empty stubs can be
    # folded by GCC/linker, which makes a logger followed by panic look like a
    # repeated call to the same target and breaks terminal-call recognition.
    stubs = "\n".join(
        '__attribute__((noinline,used,section(".oracle_stubs"))) unsigned %s(void){return %du;}' % (s, i + 1)
        for i, s in enumerate(undef))
    spath = os.path.join(d, "stubs.c"); sopath = os.path.join(d, "stubs.o")
    open(spath, "w").write(stubs + "\n")
    subprocess.run([GCC] + CFLAGS + [spath, "-o", sopath], capture_output=True, text=True)
    # linker script: function first at link_va, stubs after
    lds = os.path.join(d, "link.ld")
    open(lds, "w").write(
        "ENTRY(%s)\nSECTIONS{ . = 0x%x; .text : { *(.text .text.*) } "
        ".rodata : { *(.rodata .rodata.*) } "
        ".oracle_stubs : { *(.oracle_stubs) } }\n"
        % (func_name, link_va))
    epath = os.path.join(d, "f.elf")
    lr = subprocess.run([GCC, "-mcpu=cortex-m33", "-mthumb", "-nostdlib",
                         "-Wl,--build-id=none", "-T", lds,
                         opath, sopath, "-o", epath],
                        capture_output=True, text=True, cwd=d)
    if lr.returncode != 0:
        return None, "ld: " + lr.stderr
    global LAST_DIRECT_TARGET_MAP
    LAST_DIRECT_TARGET_MAP = {}
    with open(epath, "rb") as f:
        elf = ELFFile(f)
        st = elf.get_section_by_name(".symtab")
        semantic_names = _semantic_name_map("net" if link_va >= 0x01000000 else "app")
        for name in undef:
            mm = re.fullmatch(r"FUN_([0-9a-fA-F]{8})", name)
            semantic_va = (int(mm.group(1), 16) if mm else
                           source_backmaps.get(name, semantic_names.get(name)))
            if semantic_va is None:
                continue
            ss = next((s for s in st.iter_symbols() if s.name == name), None)
            if ss:
                LAST_DIRECT_TARGET_MAP[int(ss["st_value"]) & ~1] = semantic_va & ~1
        sym = next((s for s in st.iter_symbols()
                    if s.name == func_name and s["st_info"]["type"] == "STT_FUNC"), None)
        if not sym:
            return None, "symbol %s not found after link" % func_name
        va = sym["st_value"] & ~1
        # The executable candidate boundary includes every local helper emitted
        # from the reconstruction TU, not just the public symbol's STT_FUNC
        # range.  Oracle stubs live in their own later section and therefore
        # remain external boundaries.  This distinction is essential for
        # compiler-outlined helpers in large functions.
        text = elf.get_section_by_name(".text")
        base = text["sh_addr"]; size = text["sh_size"]
        end = max(s["sh_addr"] + s["sh_size"] for s in elf.iter_sections()
                  if s["sh_type"] != "SHT_NOBITS" and s["sh_addr"] >= base)
        data = bytearray(end - base)
        for sec in elf.iter_sections():
            if (sec["sh_type"] != "SHT_NOBITS" and sec["sh_size"] and
                    base <= sec["sh_addr"] < end):
                so = sec["sh_addr"] - base
                data[so:so + sec["sh_size"]] = sec.data()
        off = va - base
        body = data[off:off + size]
        # Keep the complete linked tail, not merely the first literal-pool
        # window.  Large reconstructed functions can own readable static const
        # tables after their STT_FUNC extent; truncating those bytes makes
        # otherwise-valid PC-relative loads read zero/unrelated flash and can
        # even manufacture stack corruption in the differential run.  The
        # executable boundary remains `size`: Runner still oracles control flow
        # outside the function, while ordinary data reads can see every byte
        # emitted by the candidate translation unit.
        tail = data[off + size:]
        return (bytes(body), bytes(tail), size, va), None

def prove(orig_va, orig_size, csrc, func_name, code_base=emu.CODE_BASE,
          trials=200, nptr=2, extra_cflags=None, ret_kind="i32", no_return=False):
    # original bytes incl. trailing literal pool
    orig = extract.func_bytes_padded(orig_va, orig_size, pad=64)
    comp, err = compile_func(csrc, func_name, orig_va, extra_cflags)
    if err:
        return {"pass": False, "stage": "compile", "error": err}
    body, tail, csize, cva = comp
    cand = body + tail
    v = emu.compare(orig, orig_va, orig_size,
                    cand, cva, csize,
                    code_base=code_base, trials=trials, nptr=nptr, ret_kind=ret_kind,
                    no_return=no_return)
    v["cand_size"] = csize
    v["orig_size"] = orig_size
    return v
