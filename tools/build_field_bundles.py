"""Field-naming bundles: for every recovered struct that still has field_0x*
placeholders, emit a bundle pointing the agent at the member functions' fully
named source (recon/readable_sources/app) so it can read how each field is used
and name it. Sharded into N for parallel opus agents.
Output: recon/structs/field_bundles/**
"""
import json, os, re, sys

BASE = "/Users/freedomcoder/Projects/G1disasm2"
RS = BASE + "/recon/readable_sources/app"
OUT = BASE + "/recon/structs/field_bundles"
NSHARD = int(sys.argv[1]) if len(sys.argv) > 1 else 20


def main():
    os.makedirs(OUT, exist_ok=True)
    cat = json.load(open(BASE + "/recon/structs/struct_catalog_app.json"))["structs"]
    clusters = json.load(open(BASE + "/recon/structs/clusters_app.json"))["clusters"]
    amap = json.load(open(BASE + "/recon/catalogs/function_names_app.json"))["by_address"]

    # index readable-source files by basename (without .c)
    srcindex = {}
    for sub in ("g1", "library"):
        d = os.path.join(RS, sub)
        if os.path.isdir(d):
            for f in os.listdir(d):
                if f.endswith(".c"):
                    srcindex.setdefault(f[:-2], os.path.join("recon/readable_sources/app", sub, f))

    def human(entry):
        rec = amap.get("0x%08x" % (int(entry, 16) & ~1))
        return rec["name"] if rec else None

    items = []
    for s in cat:
        ph = [f for f in s["fields"] if re.match(r'^field_0x[0-9a-fA-F]+$', f["name"])]
        if ph:
            items.append((s, ph))

    manifest = []
    for i, (s, ph) in enumerate(sorted(items, key=lambda x: x[0]["cid"])):
        cid = s["cid"]
        cl = clusters.get(cid, {})
        acc = cl.get("accesses", {})
        # member source files (dedup, resolve readable name -> path)
        srcs = []
        seen = set()
        for cc in s.get("merged_cids", [cid]):
            for m in clusters.get(cc, {}).get("members", []):
                hn = human(m["entry"])
                if hn and hn not in seen:
                    seen.add(hn)
                    p = srcindex.get(hn)
                    srcs.append((hn, m.get("base", "?"), p))

        b = []
        b.append("### struct %s  (%s)  cid=%s" % (s["struct_name"], "library:" + s["library_name"] if s.get("is_library") else "G1-original", cid))
        b.append("")
        b.append("purpose: %s" % s.get("purpose", ""))
        b.append("")
        b.append("This object is accessed by these functions (read their fully-named source):")
        for hn, base, p in srcs[:30]:
            b.append("  - %s  (as %s)%s" % (hn, base, "  ->  " + p if p else "  [no source file]"))
        b.append("")
        b.append("Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:")
        b.append("```c")
        b.append("struct %s {" % s["struct_name"])
        for f in sorted(s["fields"], key=lambda f: int(f["offset"], 16)):
            a = acc.get(f["offset"], {})
            meta = "rw=%s sz=%s" % ("".join(a.get("rw", [])), ",".join(map(str, a.get("sizes", []))))
            todo = "   <-- NAME ME" if re.match(r'^field_0x[0-9a-fA-F]+$', f["name"]) else ""
            b.append("    %-12s %s;  /* +%s  %s */%s" % (f["type"], f["name"], f["offset"], meta, todo))
        b.append("};")
        b.append("```")
        bundle = "\n".join(b)
        with open(OUT + "/%s.md" % cid, "w") as fh:
            fh.write(bundle)
        manifest.append({"cid": cid, "struct_name": s["struct_name"],
                         "n_placeholders": len(ph), "shard": i % NSHARD})

    shards = {}
    for m in manifest:
        shards.setdefault(m["shard"], []).append(m["cid"])
    for si, cids in shards.items():
        json.dump(cids, open(OUT + "/shard_%02d.json" % si, "w"), indent=1)
    json.dump(manifest, open(OUT + "/manifest.json", "w"), indent=1)
    print("structs needing field names:", len(manifest),
          "| placeholder fields:", sum(m["n_placeholders"] for m in manifest),
          "| shards:", len(shards))


if __name__ == "__main__":
    main()
