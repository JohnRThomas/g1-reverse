"""Merge agent naming proposals into function_name_overrides.json (app core).

Input: recon/naming_bundles/proposals/all_proposals.json — a list of
{address, name, confidence, evidence, batch} records produced by the naming
workflow. This script:
  * validates each name is a legal C identifier and not a C keyword;
  * refuses to overwrite an address that already has a human name;
  * de-collides names against existing human names and among proposals,
    preferring higher confidence and appending a short _<addrtag> only when a
    name is otherwise taken (keeps every name unique and traceable);
  * writes accepted entries into recon/catalogs/function_name_overrides.json.

Run tools/build_function_names.py and tools/validate_name_maps.py afterwards.
"""
import json, os, re, sys

BASE = "/Users/freedomcoder/Projects/G1disasm2"
PROP = BASE + "/recon/naming_bundles/proposals/all_proposals.json"
OVER = BASE + "/recon/catalogs/function_name_overrides.json"
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
KW = set("auto break case char const continue default do double else enum extern "
         "float for goto if inline int long register restrict return short signed "
         "sizeof static struct switch typedef union unsigned void volatile while "
         "_Bool _Complex _Imaginary".split())
RANK = {"high": 3, "medium": 2, "low": 1}


def main():
    amap = json.load(open(BASE + "/recon/catalogs/function_names_app.json"))["by_address"]
    existing = {v["name"] for v in amap.values() if not v["name"].startswith("FUN_")}
    props = json.load(open(PROP))

    # normalize + validate; drop entries whose address already has a human name
    clean = []
    skipped = {"badname": 0, "already_named": 0, "unknown_addr": 0}
    for p in props:
        addr = p["address"].strip().lower()
        if not addr.startswith("0x"):
            addr = "0x" + addr
        key = "0x%08x" % (int(addr, 16) & ~1)
        rec = amap.get(key)
        if rec is None:
            skipped["unknown_addr"] += 1
            continue
        if not rec["name"].startswith("FUN_"):
            skipped["already_named"] += 1
            continue
        name = p["name"].strip()
        if not IDENT.match(name) or name in KW or name.startswith("FUN_"):
            skipped["badname"] += 1
            continue
        clean.append({"key": key, "name": name,
                      "conf": RANK.get(p.get("confidence", "low"), 1),
                      "confidence": p.get("confidence", "low"),
                      "evidence": p.get("evidence", "").strip()})

    # de-collide: process highest confidence first; a name already taken gets a
    # short address tag suffix so it stays unique and reversible.
    clean.sort(key=lambda c: (-c["conf"], c["key"]))
    taken = set(existing)
    accepted = {}
    tagged = 0
    for c in clean:
        name = c["name"]
        if name in taken:
            tag = c["key"][-6:].lstrip("0") or "0"
            cand = "%s_%s" % (name, tag)
            if cand in taken:
                continue  # give up rather than fabricate further
            name = cand
            tagged += 1
        taken.add(name)
        ev = "[agent-name conf=%s] %s Raw identity remains %s." % (
            c["confidence"], c["evidence"], "FUN_" + c["key"][2:])
        accepted[c["key"]] = {"name": name, "evidence": ev}

    over = json.load(open(OVER)) if os.path.exists(OVER) else {"schema": 1, "app": {}, "net": {}}
    over.setdefault("app", {})
    added = 0
    for key, rec in accepted.items():
        if key not in over["app"]:
            added += 1
        over["app"][key] = rec
    json.dump(over, open(OVER, "w"), indent=1)

    print("proposals in:", len(props))
    print("skipped:", skipped)
    print("accepted:", len(accepted), "| collision-tagged:", tagged,
          "| newly added to overrides:", added)


if __name__ == "__main__":
    main()
