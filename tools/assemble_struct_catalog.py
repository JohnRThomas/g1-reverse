"""Part E: assemble the final verified struct catalog.

Combines the opus-merged canonical structs (recon/structs/merged_app.json) with
the mechanistic verification report (verify_structs.py) into the durable
deliverable recon/structs/struct_catalog_app.json. Each record carries its
Ghidra provenance (cluster + members), the field layout, library ownership +
verification status, and the D1/D2 verdict. Structs that fail the mechanistic
gate are kept but marked rejected with the reason (never silently dropped).
"""
import json, os, sys

BASE = "/Users/freedomcoder/Projects/G1disasm2"
OUT = BASE + "/recon/structs"


def main():
    merged = json.load(open(OUT + "/merged_app.json"))
    if isinstance(merged, dict):
        merged = merged.get("structs", [])
    clusters = json.load(open(OUT + "/clusters_app.json"))["clusters"]
    report = {r["cid"]: r for r in
              json.load(open(OUT + "/struct_verification_report.json"))["results"]}

    catalog = []
    for s in merged:
        cid = s.get("cid")
        cl = clusters.get(cid, {})
        vr = report.get(cid, {})
        rec = {
            "cid": cid,
            "struct_name": s.get("struct_name"),
            "kind": cl.get("kind"),
            "purpose": s.get("purpose"),
            "is_library": s.get("is_library", False),
            "library_name": s.get("library_name", ""),
            "library_header": s.get("library_header", ""),
            "library_verified": s.get("library_verified", False),
            "is_array": s.get("is_array", False),
            "is_union": s.get("is_union", False),
            "confidence": s.get("confidence"),
            "merged_cids": s.get("merged_cids", [cid]),
            "size_lower_bound": cl.get("min_size_bytes"),
            "n_members": cl.get("n_members_total"),
            "members": cl.get("members", [])[:24],
            "fields": s.get("fields", []),
            "review_note": s.get("review_note", ""),
            "verified": vr.get("pass", False),
            "verify_errors": vr.get("errors", []),
            "verify_warnings": vr.get("warnings", []),
        }
        catalog.append(rec)

    catalog.sort(key=lambda r: (not r["verified"], r["cid"]))
    # split library vs original into companion files for convenience
    lib = [r for r in catalog if r["is_library"]]
    orig = [r for r in catalog if not r["is_library"]]
    json.dump({"schema": 1, "core": "app", "count": len(catalog), "structs": catalog},
              open(OUT + "/struct_catalog_app.json", "w"), indent=1)
    json.dump({"schema": 1, "core": "app", "structs": lib},
              open(OUT + "/struct_library_app.json", "w"), indent=1)
    json.dump({"schema": 1, "core": "app", "structs": orig},
              open(OUT + "/struct_original_app.json", "w"), indent=1)

    # coverage: every cluster with >=2 offsets must be covered exactly once
    target = {cid for cid, c in clusters.items() if c["n_offsets"] >= 2}
    covered = {}
    for r in catalog:
        for cid in set(r["merged_cids"]) | {r["cid"]}:
            covered.setdefault(cid, []).append(r["struct_name"])
    missing = sorted(target - set(covered))
    dup = {cid: names for cid, names in covered.items() if len(names) > 1 and cid in target}
    json.dump({"target": len(target), "covered": len(set(covered) & target),
               "missing": missing, "double_covered": dup},
              open(OUT + "/struct_coverage_app.json", "w"), indent=1)

    npass = sum(1 for r in catalog if r["verified"])
    print("coverage: %d/%d clusters covered | missing: %d | double-covered: %d" %
          (len(set(covered) & target), len(target), len(missing), len(dup)))
    print("catalog structs:", len(catalog))
    print("  mechanistically verified (D1+D2):", npass, "| rejected:", len(catalog) - npass)
    print("  library:", len(lib), "(offset-verified:",
          sum(1 for r in lib if r["library_verified"]), ") | G1-original:", len(orig))
    print("  unions:", sum(1 for r in catalog if r["is_union"]),
          "| arrays:", sum(1 for r in catalog if r["is_array"]))
    if len(catalog) - npass:
        print("  --- rejected (first 12) ---")
        for r in catalog:
            if not r["verified"]:
                print("   ", r["cid"], r["struct_name"], "::", "; ".join(r["verify_errors"])[:140])
                if sum(1 for x in catalog if not x["verified"]) > 12:
                    break


if __name__ == "__main__":
    main()
