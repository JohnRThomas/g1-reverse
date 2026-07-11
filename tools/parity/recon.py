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
import os, subprocess, tempfile, sys
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
from elftools.elf.elffile import ELFFile
import extract
from parity import emu

GCC = "arm-none-eabi-gcc"
CFLAGS = ["-mcpu=cortex-m33", "-mthumb", "-Os", "-ffreestanding", "-nostdlib",
          # match the nRF5340 app core: single-precision hardware FPU, hard-float
          # ABI, so float arithmetic compiles to inline VFP (not __aeabi_* calls)
          "-mfpu=fpv5-sp-d16", "-mfloat-abi=hard",
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
        '__attribute__((noinline,used)) unsigned %s(void){return %du;}' % (s, i + 1)
        for i, s in enumerate(undef))
    spath = os.path.join(d, "stubs.c"); sopath = os.path.join(d, "stubs.o")
    open(spath, "w").write(stubs + "\n")
    subprocess.run([GCC] + CFLAGS + [spath, "-o", sopath], capture_output=True, text=True)
    # linker script: function first at link_va, stubs after
    lds = os.path.join(d, "link.ld")
    open(lds, "w").write(
        "ENTRY(%s)\nSECTIONS{ . = 0x%x; .text : { *(.text .text.*) *(.rodata .rodata.*) } }\n"
        % (func_name, link_va))
    epath = os.path.join(d, "f.elf")
    lr = subprocess.run([GCC, "-mcpu=cortex-m33", "-mthumb", "-nostdlib",
                         "-Wl,--build-id=none", "-T", lds,
                         opath, sopath, "-o", epath],
                        capture_output=True, text=True, cwd=d)
    if lr.returncode != 0:
        return None, "ld: " + lr.stderr
    with open(epath, "rb") as f:
        elf = ELFFile(f)
        st = elf.get_section_by_name(".symtab")
        sym = next((s for s in st.iter_symbols()
                    if s.name == func_name and s["st_info"]["type"] == "STT_FUNC"), None)
        if not sym:
            return None, "symbol %s not found after link" % func_name
        va = sym["st_value"] & ~1
        size = sym["st_size"]
        # read bytes from the ELF .text at the function's VA
        text = elf.get_section_by_name(".text")
        base = text["sh_addr"]; data = text.data()
        off = va - base
        body = data[off:off + size]
        tail = data[off + size: off + size + 64]
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
