"""WS2 final: apply the naming master + symbol map to the parity-proven sources,
producing a readable recon/named/ tree. Renames each function and every
FUN_xxxx/sub_xxxx callee reference, and appends a global-name legend. Purely a
rename/annotate pass over the PROVEN code — logic is untouched (parity holds)."""
import json, glob, os, re
SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
SRC = "/Users/freedomcoder/Projects/G1disasm2/recon/verified/src"
OUT = "/Users/freedomcoder/Projects/G1disasm2/recon/named"

def load_map():
    m = {}   # addr -> name
    sym = json.load(open(SCR + "/symbol_map.json"))      # library + IDA + auto
    for a, n in sym.items():
        m[int(a, 16) & ~1] = n
    nm = json.load(open(SCR + "/naming_master.json"))    # 966 fresh semantic names
    for a, info in nm["functions"].items():
        addr = int(a, 16) & ~1
        m.setdefault(addr, info["name"])                 # don't override known names
    return m, nm["globals"]

def main():
    os.makedirs(OUT, exist_ok=True)
    fmap, gmap = load_map()
    gmap_int = {int(a, 16): g for a, g in gmap.items()}
    tok = re.compile(r"\b(?:FUN_|sub_)0*([0-9a-fA-F]{3,8})\b")
    def repl(mt):
        addr = int(mt.group(1), 16)
        return fmap.get(addr & ~1, mt.group(0))
    n_files = n_renamed = 0
    for cf in sorted(glob.glob(SRC + "/*.c")):
        src = open(cf).read()
        base = os.path.basename(cf)
        m = re.search(r"@ (0x[0-9a-fA-F]+)", src)
        va = int(m.group(1), 16) if m else None
        newname = fmap.get(va & ~1) if va else None
        # rename all FUN_/sub_ callee references + the defined symbol
        out = tok.sub(repl, src)
        # global legend: any 0x2000xxxx / 0x0008xxxx address with a known name
        legend = []
        for gaddr, g in gmap_int.items():
            if ("0x%08x" % gaddr) in out.lower() or ("0x%x" % gaddr) in out:
                fld = g.get("field")
                legend.append("//   0x%08x  %-28s %s" % (gaddr, g["name"],
                              ("[" + fld + "]") if fld else ""))
        header = "/* named: %s */\n" % (newname or base[:-2])
        if legend:
            header += "/* globals referenced:\n" + "\n".join(sorted(set(legend))) + "\n*/\n"
        outname = (newname or base[:-2]) + ".c"
        open(os.path.join(OUT, outname), "w").write(header + out)
        n_files += 1
        if newname:
            n_renamed += 1
    print("named source files written:", n_files, "| function renamed:", n_renamed)
    print("output:", OUT)

if __name__ == "__main__":
    main()
