"""
High-precision structural library detector.

The exact normalized-hash match found ~0 because the reference ELFs in elfs/ are
different NCS build configs than the shipped image. But the *opcode sequence*
(mnemonics only, ALL operands discarded) of a given library routine is highly
stable across build configs. So: an unnamed application `sub_` whose opcode
sequence is near-identical (high 3-gram Jaccard, matching length) to a NAMED
library function in the reference ELFs is almost certainly that library routine.

Strict thresholds (length within 12%, Jaccard >= 0.92, >= 12 opcodes) keep
precision high — we would rather leave a library function mis-labeled as
application (and waste some effort) than mislabel real application code as
library (and silently drop it from reconstruction).
"""
import sys, json, glob
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import extract
from capstone import *
from elftools.elf.elffile import ELFFile

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)

def opseq(code, addr):
    return [i.mnemonic.split(".")[0] for i in md.disasm(code, addr)]

def grams(seq, n=3):
    return set(tuple(seq[i:i+n]) for i in range(len(seq)-n+1))

def jacc(a, b):
    if not a or not b: return 0.0
    return len(a & b) / len(a | b)

def load_ref():
    refs = []  # (name, len, grams)
    for path in glob.glob("/Users/freedomcoder/Projects/G1disasm2/elfs/*.elf"):
        with open(path, "rb") as f:
            elf = ELFFile(f)
            st = elf.get_section_by_name(".symtab")
            if not st: continue
            secs = [(s["sh_addr"], s["sh_addr"]+s["sh_size"], s.data())
                    for s in elf.iter_sections() if s["sh_addr"] and s.data()]
            for sym in st.iter_symbols():
                if sym["st_info"]["type"] != "STT_FUNC": continue
                size = sym["st_size"]; addr = sym["st_value"] & ~1
                if size < 24 or not sym.name: continue
                code = None
                for lo, hi, data in secs:
                    if lo <= addr < hi:
                        code = data[addr-lo:addr-lo+size]; break
                if not code: continue
                seq = opseq(code, addr)
                if len(seq) < 12: continue
                refs.append((sym.name, len(seq), grams(seq)))
    return refs

def main():
    fw = {f["entry"]: f for f in json.load(open(SCR+"/app_funcs.json"))["functions"]}
    cls = {c["entry"]: c for c in json.load(open(SCR+"/classified.json"))["functions"]}
    refs = load_ref()
    print("reference library functions indexed:", len(refs))
    # bucket refs by opcode-length for speed
    from collections import defaultdict
    by_len = defaultdict(list)
    for nm, L, g in refs:
        by_len[L].append((nm, g))
    unnamed = [c for c in cls.values()
               if c["class"] == "APPLICATION" and not c["is_thunk"] and not c["ida_name"]]
    hits = []
    for c in unnamed:
        f = fw[c["entry"]]
        if f["size"] < 24: continue
        code = extract.func_bytes_padded(c["entry"], f["size"], pad=0)
        seq = opseq(code, c["entry"])
        if len(seq) < 12: continue
        g = grams(seq)
        best = (0.0, None)
        lo = int(len(seq)*0.88); hi = int(len(seq)*1.12)+1
        for L in range(lo, hi+1):
            for nm, rg in by_len.get(L, ()):
                s = jacc(g, rg)
                if s > best[0]:
                    best = (s, nm)
        if best[0] >= 0.92:
            hits.append((c["entry_hex"], f["size"], best[1], round(best[0], 3)))
    hits.sort(key=lambda x: -x[3])
    json.dump(hits, open(SCR+"/lib_fuzzy_hits.json", "w"), indent=1)
    print("RECLASSIFIED as LIBRARY (Jaccard>=0.92):", len(hits))
    for h in hits[:40]:
        print("  %s size=%-5d ~ %-30s J=%.3f" % h)

if __name__ == "__main__":
    main()
