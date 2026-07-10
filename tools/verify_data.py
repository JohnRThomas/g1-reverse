"""Whole-.rodata data byte-match verification. Compiles each recon/data/*.c table
with the Zephyr ARM toolchain, reads the emitted symbol bytes from the object, and
byte-compares them against the ORIGINAL image bytes at the table's VA. Reports total
bytes matched, per-file mismatches, and coverage of the app-core .rodata region.
"""
import sys, os, re, glob, subprocess, tempfile
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import extract as ax
from elftools.elf.elffile import ELFFile

CC = "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc"
CFLAGS = ["-c", "-Os", "-mcpu=cortex-m33", "-mthumb", "-ffreestanding", "-w"]
DATA = "/Users/freedomcoder/Projects/G1disasm2/recon/data"

def sym_bytes(obj, name):
    """Return the raw bytes of a defined symbol from an ELF object."""
    with open(obj, "rb") as f:
        elf = ELFFile(f)
        symtab = elf.get_section_by_name(".symtab")
        sym = None
        for s in symtab.iter_symbols():
            if s.name == name:
                sym = s; break
        if sym is None:
            return None
        shndx = sym["st_shndx"]
        if not isinstance(shndx, int):
            return None
        sec = elf.get_section(shndx)
        data = sec.data()
        off = sym["st_value"]
        size = sym["st_size"]
        return data[off:off + size]

def main():
    files = sorted(glob.glob(DATA + "/*.c"))
    total_bytes = matched_bytes = 0
    ok = mism = skip = 0
    mismatches = []
    covered = []
    with tempfile.TemporaryDirectory() as td:
        for f in files:
            m = re.search(r'rodata_(0x[0-9a-fA-F]+)', os.path.basename(f))
            if not m:
                skip += 1; continue
            base = int(m.group(1), 16)
            symname = "rodata_%x" % base
            # the file may name the symbol rodata_0xXXXX (with 0x) — read it
            txt = open(f).read()
            # the defined symbol is an identifier before `= {`, and its name always
            # contains the base-address hex; pick that match (handles rodata_0x.., litpool_..)
            bhex = "%x" % base
            cand = [g for g in re.findall(r'\b(\w+)\s*(?:\[\s*\d*\s*\])?\s*=\s*\{', txt)
                    if bhex in g.lower()]
            symname = cand[0] if cand else symname
            obj = os.path.join(td, "d.o")
            r = subprocess.run([CC] + CFLAGS + [f, "-o", obj], capture_output=True, text=True)
            if r.returncode != 0:
                skip += 1; mismatches.append((base, "compile-fail", r.stderr.strip()[:80])); continue
            emitted = sym_bytes(obj, symname)
            if emitted is None:
                # fall back: any single defined data symbol in the object
                skip += 1; mismatches.append((base, "sym-not-found", symname)); continue
            # compare only the table's real data length (drop trailing struct padding)
            dl = re.search(r'(\d+)\s*bytes', txt)
            n = int(dl.group(1)) if dl else len(emitted)
            n = min(n, len(emitted))
            emitted = emitted[:n]
            try:
                orig = ax.read(base, len(emitted))
            except Exception:
                skip += 1; continue
            total_bytes += len(emitted)
            if bytes(emitted) == bytes(orig):
                ok += 1; matched_bytes += len(emitted)
                covered.append((base, base + len(emitted)))
            else:
                mism += 1
                ndiff = sum(1 for a, b in zip(emitted, orig) if a != b)
                mismatches.append((base, "byte-diff", "%d/%d bytes differ" % (ndiff, len(emitted))))
    print("=== .rodata data byte-match ===")
    print("files: %d | byte-exact: %d | mismatched: %d | skipped: %d" % (len(files), ok, mism, skip))
    print("bytes compared: %d | matched: %d (%.2f%%)" % (
        total_bytes, matched_bytes, 100.0 * matched_bytes / max(total_bytes, 1)))
    if covered:
        lo = min(c[0] for c in covered); hi = max(c[1] for c in covered)
        print("rodata span covered: 0x%x .. 0x%x" % (lo, hi))
    if mismatches:
        print("--- issues (first 15) ---")
        for b, kind, det in mismatches[:15]:
            print("  0x%x  %s  %s" % (b, kind, det))

if __name__ == "__main__":
    main()
