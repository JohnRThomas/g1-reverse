"""Finalize: aggregate the opus merge-wave journal into merged_app.json, run the
mechanistic verifier, and assemble the final catalog. Usage:
    finalize_structs.py <merge_journal.jsonl>
"""
import json, os, subprocess, sys

BASE = "/Users/freedomcoder/Projects/G1disasm2"
OUT = BASE + "/recon/structs"
CTYPE = {1: "uint8_t", 2: "uint16_t", 4: "uint32_t", 8: "uint64_t"}


def mechanical_fallback(cid, cl):
    """Ground-truth struct for a cluster no agent covered: fields at each
    observed offset, width clamped to the gap before the next offset so nothing
    overlaps. Flagged so it is never mistaken for a reviewed name."""
    offs = sorted(int(o, 16) for o in cl["accesses"])
    fields = []
    for i, off in enumerate(offs):
        a = cl["accesses"]["0x%x" % off]
        obs = max(a["sizes"])
        nxt = offs[i + 1] if i + 1 < len(offs) else off + obs
        gap = nxt - off
        w = min(obs, gap) if gap > 0 else obs
        fields.append({"offset": "0x%x" % off, "type": CTYPE.get(w, "uint8_t"),
                       "name": "field_0x%x" % off, "note": "mechanical (agent-dropped)"})
    return {"cid": cid, "struct_name": "%s_mechanical" % cid, "kind": cl["kind"],
            "purpose": "Agent output missing for this cluster; mechanical Ghidra layout retained.",
            "is_library": False, "library_name": "", "library_verified": False,
            "is_array": False, "is_union": False, "confidence": "low",
            "merged_cids": [cid], "review_note": "MECHANICAL FALLBACK (no agent proposal)",
            "fields": fields}


def main():
    journal = sys.argv[1]
    structs = []
    for line in open(journal):
        line = line.strip()
        if not line:
            continue
        r = json.loads(line)
        if r.get("type") == "result" and isinstance(r.get("result"), dict):
            for s in r["result"].get("structs", []):
                structs.append(s)
    # de-dup by cid (keep first; a cid should appear once)
    seen = set()
    uniq = []
    for s in structs:
        cid = s.get("cid")
        if cid in seen:
            continue
        seen.add(cid)
        uniq.append(s)
    # fill any cluster no agent covered with the mechanical ground-truth layout
    clusters = json.load(open(OUT + "/clusters_app.json"))["clusters"]
    target = {cid for cid, c in clusters.items() if c["n_offsets"] >= 2}
    covered = set()
    for s in uniq:
        covered |= set(s.get("merged_cids", [])) | {s.get("cid")}
    nfb = 0
    for cid in sorted(target - covered):
        uniq.append(mechanical_fallback(cid, clusters[cid]))
        nfb += 1

    json.dump({"schema": 1, "core": "app", "structs": uniq},
              open(OUT + "/merged_app.json", "w"), indent=1)
    print("merged structs:", len(uniq), "| mechanical fallbacks:", nfb)

    # mechanistic verification (writes struct_verification_report.json)
    subprocess.run([sys.executable, BASE + "/tools/verify_structs.py",
                    OUT + "/merged_app.json"],
                   env={**os.environ, "PYTHONSAFEPATH": "1"}, check=True)
    # assemble final catalog
    subprocess.run([sys.executable, BASE + "/tools/assemble_struct_catalog.py"],
                   env={**os.environ, "PYTHONSAFEPATH": "1"}, check=True)


if __name__ == "__main__":
    main()
