"""Generate linker fragments that pin every named symbol to its ORIGINAL address,
so the symbolized code links and the referenced addresses byte-match the image.

Globals/kobjects/rodata externs become `PROVIDE(name = 0xADDR);` absolute-symbol
assignments (no storage allocated — they just make &name resolve to the real VA,
which is exactly what the whole-image byte-match of .text/.rodata needs).
Partition offsets and MMIO regs are #defines (already in the header), not symbols.
"""
import sys, os, json, collections

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
BASE = "/Users/freedomcoder/Projects/G1disasm2"
CORE = sys.argv[1] if len(sys.argv) > 1 else "app"
MAP = SCR + ("/symbol_map.json" if CORE == "app" else "/symbol_map_net.json")
OUT = BASE + "/recon/symbols/g1_%s_globals.ld" % CORE

def main():
    smap = json.load(open(MAP))
    seen = {}
    dup = 0
    for a, rec in smap.items():
        k = rec.get("kind")
        n = rec.get("name")
        if k not in ("ram_global", "kobject", "rodata_ref", "string") or not n:
            continue
        v = int(rec.get("symbol_base", a), 16)
        if n in seen:
            # same name, different addr already caught by merge dedupe; skip extras
            if seen[n] != v:
                dup += 1
            continue
        seen[n] = v
    lines = ["/* Auto-generated: pin reconstructed %s-core symbols to their original" % CORE,
             " * addresses so &name resolves to the real VA (whole-image byte-match)." ,
             " * %d symbols. Include via: INSERT or -T with the main linker script. */" % len(seen),
             ""]
    for n, v in sorted(seen.items(), key=lambda kv: kv[1]):
        lines.append("PROVIDE(%s = 0x%08x);" % (n, v))
    open(OUT, "w").write("\n".join(lines) + "\n")
    print("[%s] pinned %d symbols -> %s (%d name/addr dups skipped)" % (CORE, len(seen), OUT, dup))

if __name__ == "__main__":
    main()
