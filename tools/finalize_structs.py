"""Finalize: aggregate the opus merge-wave journal into merged_app.json, run the
mechanistic verifier, and assemble the final catalog. Usage:
    finalize_structs.py <merge_journal.jsonl>
"""
import json, os, subprocess, sys

BASE = "/Users/freedomcoder/Projects/G1disasm2"
OUT = BASE + "/recon/structs"


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
    json.dump({"schema": 1, "core": "app", "structs": uniq},
              open(OUT + "/merged_app.json", "w"), indent=1)
    print("merged structs:", len(uniq))

    # mechanistic verification (writes struct_verification_report.json)
    subprocess.run([sys.executable, BASE + "/tools/verify_structs.py",
                    OUT + "/merged_app.json"],
                   env={**os.environ, "PYTHONSAFEPATH": "1"}, check=True)
    # assemble final catalog
    subprocess.run([sys.executable, BASE + "/tools/assemble_struct_catalog.py"],
                   env={**os.environ, "PYTHONSAFEPATH": "1"}, check=True)


if __name__ == "__main__":
    main()
