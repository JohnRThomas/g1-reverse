"""Merge opus field-name proposals into the struct catalog. Only field_0x*
placeholders are renamed; offsets are never touched. Names are validated as C
identifiers and forced unique within each struct. Optional type refinements and
struct renames are applied when valid. Usage:
    merge_field_names.py <field_journal.jsonl>
Writes recon/structs/merged_app.json (re-derived from the catalog + renames);
run verify_structs.py + assemble_struct_catalog.py afterwards.
"""
import json, os, re, sys

BASE = "/Users/freedomcoder/Projects/G1disasm2"
OUT = BASE + "/recon/structs"
IDENT = re.compile(r"^[A-Za-z_]\w*$")
PLACE = re.compile(r"^field_0x[0-9a-fA-F]+$")
KW = set("auto break case char const continue default do double else enum extern "
         "float for goto if inline int long register restrict return short signed "
         "sizeof static struct switch typedef union unsigned void volatile while".split())


def main():
    journal = sys.argv[1]
    prop = {}
    for line in open(journal):
        line = line.strip()
        if not line:
            continue
        r = json.loads(line)
        if r.get("type") == "result" and isinstance(r.get("result"), dict):
            for p in r["result"].get("proposals", []):
                prop[p["cid"]] = p

    cat = json.load(open(OUT + "/struct_catalog_app.json"))["structs"]
    renamed_fields = 0
    retyped = 0
    struct_renames = 0
    kept = 0
    for s in cat:
        p = prop.get(s["cid"])
        if not p:
            continue
        byoff = {f["offset"]: f for f in p.get("fields", [])}
        used = {f["name"] for f in s["fields"] if not PLACE.match(f["name"])}
        for f in s["fields"]:
            if not PLACE.match(f["name"]):
                continue
            pf = byoff.get(f["offset"])
            if not pf:
                kept += 1
                continue
            name = (pf.get("name") or "").strip()
            if not name or PLACE.match(name) or not IDENT.match(name) or name in KW:
                kept += 1
                continue
            if name in used:  # de-collide within struct
                name = "%s_%s" % (name, f["offset"][2:])
                if name in used:
                    kept += 1
                    continue
            used.add(name)
            f["name"] = name
            renamed_fields += 1
            nt = (pf.get("type") or "").strip()
            if nt and IDENT.match(nt.replace(" ", "").replace("*", "")) and nt != f["type"]:
                f["type"] = nt
                retyped += 1
        sr = (p.get("struct_rename") or "").strip()
        if sr and IDENT.match(sr) and sr != s["struct_name"] and not sr.endswith("_mechanical"):
            s["struct_name"] = sr
            struct_renames += 1

    json.dump({"schema": 1, "core": "app", "structs": cat},
              open(OUT + "/merged_app.json", "w"), indent=1)
    remaining = sum(1 for s in cat for f in s["fields"] if PLACE.match(f["name"]))
    print("fields renamed:", renamed_fields, "| retyped:", retyped,
          "| struct renames:", struct_renames, "| kept placeholder:", kept)
    print("placeholder fields remaining:", remaining)


if __name__ == "__main__":
    main()
