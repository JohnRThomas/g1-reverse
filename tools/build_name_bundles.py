"""Build per-function naming evidence bundles for unnamed CPUAPP functions.

For every reconstructed CPUAPP function whose committed name is still FUN_*,
emit a compact markdown bundle: readable source (callee names already
substituted in recon/named/), caller/callee name context, and referenced
C-strings read from the original image. Bundles are split into N batches so
independent naming agents can work in parallel without overlap.
"""
import gzip, json, os, re, sys, string

sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import extract
import function_names

BASE = "/Users/freedomcoder/Projects/G1disasm2"
OUT = sys.argv[1] if len(sys.argv) > 1 else BASE + "/recon/naming_bundles"
NBATCH = int(sys.argv[2]) if len(sys.argv) > 2 else 20
PRINT = set(bytes(string.printable, "ascii")) - set(b"\t\n\r\x0b\x0c")


def read_cstr(va, maxlen=120):
    try:
        b = extract.read(va, maxlen)
    except Exception:
        return None
    out = bytearray()
    for ch in b:
        if ch == 0:
            break
        if ch not in PRINT:
            return None
        out.append(ch)
    if len(out) < 4:
        return None
    return out.decode("ascii", "replace")


def main():
    os.makedirs(OUT, exist_ok=True)
    fn = function_names
    amap = json.load(open(BASE + "/recon/catalogs/function_names_app.json"))["by_address"]
    rg = json.load(gzip.open(BASE + "/recon/catalogs/refgraph_app.json.gz"))["functions"]

    def nm(addr_hex):
        # addr_hex like '0x3f2a8' -> normalized '0x0003f2a8'
        try:
            a = int(addr_hex, 16)
        except ValueError:
            return addr_hex
        key = "0x%08x" % (a & ~1)
        rec = amap.get(key)
        return rec["name"] if rec else "FUN_%08x" % (a & ~1)

    # unnamed reconstructed functions
    srcaddrs = {}
    for f in os.listdir(BASE + "/recon/app/src"):
        if f.endswith(".c"):
            srcaddrs[f[:-2]] = f
    unnamed = []
    for key, rec in amap.items():
        if not rec["name"].startswith("FUN_"):
            continue
        raw = rec["raw_name"]
        if raw in srcaddrs:
            unnamed.append((int(key, 16), raw))
    unnamed.sort()
    print("unnamed reconstructed CPUAPP functions:", len(unnamed))

    manifest = []
    for i, (addr, raw) in enumerate(unnamed):
        named_path = BASE + "/recon/named/%s.c" % raw
        src_path = named_path if os.path.exists(named_path) else BASE + "/recon/app/src/%s.c" % raw
        try:
            src = open(src_path).read()
        except OSError:
            continue
        node = rg.get("0x%x" % addr) or rg.get("0x%x" % (addr & ~1)) or {}
        callers = [nm(c) for c in node.get("callers", [])]
        calls = [nm(c) for c in node.get("calls", [])]
        strings = []
        seen = set()
        for dref in node.get("data_refs", []):
            try:
                v = int(dref, 16)
            except ValueError:
                continue
            if v < 0:
                continue
            s = read_cstr(v)
            if s and s not in seen:
                seen.add(s)
                strings.append(s)
        # strings referenced textually in the source (DAT-resolved literals)
        for m in re.findall(r'"((?:\\.|[^"\\]){3,})"', src):
            if m not in seen:
                seen.add(m)
                strings.append(m)

        b = []
        b.append("### %s  @ 0x%08x  (size=%s)" % (raw, addr, node.get("size", "?")))
        b.append("")
        b.append("callers (%d): %s" % (len(callers), ", ".join(callers[:24]) or "(none / root or address-taken)"))
        b.append("callees (%d): %s" % (len(calls), ", ".join(calls[:40]) or "(none)"))
        if strings:
            b.append("strings: %s" % " | ".join('"%s"' % s[:80] for s in strings[:30]))
        b.append("")
        b.append("```c")
        b.append(src.strip())
        b.append("```")
        bundle = "\n".join(b)
        manifest.append({"i": i, "addr": "0x%08x" % addr, "raw": raw,
                         "batch": i % NBATCH, "chars": len(bundle)})
        with open(OUT + "/%s.md" % raw, "w") as fh:
            fh.write(bundle)

    # write batch groupings
    batches = {}
    for m in manifest:
        batches.setdefault(m["batch"], []).append(m["raw"])
    for bi, raws in batches.items():
        json.dump(raws, open(OUT + "/batch_%02d.json" % bi, "w"), indent=1)
    json.dump(manifest, open(OUT + "/manifest.json", "w"), indent=1)
    print("bundles:", len(manifest), "batches:", len(batches),
          "avg chars:", sum(m["chars"] for m in manifest) // max(len(manifest), 1))


if __name__ == "__main__":
    main()
