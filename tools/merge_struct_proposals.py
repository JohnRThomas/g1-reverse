"""Aggregate wave-1 (sonnet) struct proposals and pre-group them for the opus
merge/verify wave.

Reads the collect workflow journal -> recon/structs/proposals_sonnet.json.
Groups proposals whose Ghidra footprint SIGNATURE (sorted offset:width set) is
identical, since those are very likely the same underlying type that the
inter-procedural unification missed (or the same library struct reached by
different call paths). Each group becomes one opus review item; groups are
sharded across N opus agents. Output: recon/structs/merge_groups.json + shards.
"""
import json, os, sys, glob
from collections import defaultdict

BASE = "/Users/freedomcoder/Projects/G1disasm2"
OUT = BASE + "/recon/structs"
NSHARD = int(sys.argv[2]) if len(sys.argv) > 2 else 10


def load_journal(path):
    res = []
    for line in open(path):
        line = line.strip()
        if not line:
            continue
        r = json.loads(line)
        if r.get("type") == "result" and isinstance(r.get("result"), dict):
            res.append(r["result"])
    return res


def sig(cluster):
    parts = []
    for off, a in sorted(cluster["accesses"].items(), key=lambda kv: int(kv[0], 16)):
        parts.append("%s:%d" % (off, max(a["sizes"])))
    return "|".join(parts)


def main():
    journal = sys.argv[1]
    clusters = json.load(open(OUT + "/clusters_app.json"))["clusters"]
    results = load_journal(journal)
    props = []
    for r in results:
        for p in r.get("proposals", []):
            props.append(p)
    # de-dup proposals by cid (an agent could repeat); keep first
    bycid = {}
    for p in props:
        bycid.setdefault(p["cid"], p)
    json.dump(list(bycid.values()), open(OUT + "/proposals_sonnet.json", "w"), indent=1)

    # Group by footprint signature ONLY when the signature is DISTINCTIVE
    # (>=4 fields). Small/generic layouts (2-3 fields) collide by chance across
    # unrelated objects, so each such cluster stays its own group; Opus can still
    # merge or split within the review. Distinctive collisions are true dup
    # candidates worth presenting together.
    groups = defaultdict(list)
    for cid, p in bycid.items():
        cl = clusters.get(cid)
        if not cl:
            continue
        s = sig(cl)
        distinctive = cl["n_offsets"] >= 4
        key = s if distinctive else "solo::" + cid
        groups[key].append(cid)

    grouped = []
    for s, cids in groups.items():
        grouped.append({"signature": s[:120], "cids": sorted(cids),
                        "n": len(cids),
                        "kinds": sorted({clusters[c]["kind"] for c in cids}),
                        "any_library": any(bycid[c].get("is_library") for c in cids),
                        "names": sorted({bycid[c].get("struct_name", "") for c in cids})})
    grouped.sort(key=lambda g: (-g["n"], g["cids"][0]))
    json.dump(grouped, open(OUT + "/merge_groups.json", "w"), indent=1)

    # per-group review bundles (one file per group, so opus reads one file)
    rev = OUT + "/review"
    os.makedirs(rev, exist_ok=True)
    for g in grouped:
        rep = g["cids"][0]
        b = ["## review group %s  (%d cluster(s), kinds=%s)" %
             (rep, g["n"], ",".join(g["kinds"])), ""]
        if g["n"] > 1:
            b.append("These clusters share an IDENTICAL Ghidra footprint signature — "
                     "very likely the SAME type. Merge them into one canonical struct.")
            b.append("")
        for cid in g["cids"]:
            p = bycid[cid]
            b.append("### proposal for %s" % cid)
            b.append("struct_name: %s | is_library: %s | library_name: %s | is_array: %s | confidence: %s" %
                     (p.get("struct_name"), p.get("is_library"), p.get("library_name", ""),
                      p.get("is_array"), p.get("confidence")))
            b.append("purpose: %s" % p.get("purpose", ""))
            b.append("fields:")
            for f in p.get("fields", []):
                b.append("  %s  %-12s %s  %s" % (f.get("offset"), f.get("type"),
                                                 f.get("name"), f.get("note", "")))
            b.append("")
            # attach the ground-truth bundle (candidate layout + members)
            bp = OUT + "/bundles/%s.md" % cid
            if os.path.exists(bp):
                b.append("<ground-truth bundle for %s>" % cid)
                b.append(open(bp).read())
                b.append("")
        open(rev + "/%s.md" % rep, "w").write("\n".join(b))

    # shard = list of groups; each group carries ALL its cids so every cluster
    # is reviewed (Opus merges genuine dups, splits false ones).
    shards = defaultdict(list)
    for i, g in enumerate(grouped):
        shards[i % NSHARD].append({"rep": g["cids"][0], "cids": g["cids"]})
    for si, grps in shards.items():
        json.dump(grps, open(OUT + "/mgroup_shard_%02d.json" % si, "w"), indent=1)

    print("proposals:", len(bycid))
    print("merge groups:", len(grouped),
          "| multi-cid groups (real merges):", sum(1 for g in grouped if g["n"] > 1))
    print("library proposals:", sum(1 for p in bycid.values() if p.get("is_library")),
          "| array proposals:", sum(1 for p in bycid.values() if p.get("is_array")))


if __name__ == "__main__":
    main()
