"""WS2 step 1: aggregate the unknown-global references and cluster contiguous
addresses into candidate struct/object instances. Each cluster = a base, an
extent, the set of accessed offsets, and the functions that touch it (which
often name the object, e.g. init_msgq_ancs -> that cluster is a k_msgq)."""
import glob, re, json
from collections import defaultdict

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
GAP = 0x40   # addresses within 64 bytes are treated as one object cluster

refs = defaultdict(lambda: {"fns": set(), "widths": set()})
for p in glob.glob(SCR + "/unknown_globals_*.txt"):
    for ln in open(p):
        m = re.search(r"(0x[0-9a-fA-F]{6,8})\s+referenced_by\s+(\S+?)(?:\.c)?\s+(\w+)", ln)
        if not m:
            continue
        a = int(m.group(1), 16)
        refs[a]["fns"].add(m.group(2))
        refs[a]["widths"].add(m.group(3))

addrs = sorted(refs)
clusters = []
cur = None
for a in addrs:
    if cur and a - cur["end"] <= GAP:
        cur["end"] = a
        cur["offsets"].append(a - cur["base"])
        cur["fns"] |= refs[a]["fns"]
        cur["n"] += 1
    else:
        cur = {"base": a, "end": a, "offsets": [0], "fns": set(refs[a]["fns"]), "n": 1}
        clusters.append(cur)

out = []
for c in clusters:
    out.append({"base": "0x%x" % c["base"], "size": c["end"] - c["base"] + 4,
                "naddr": c["n"], "offsets": c["offsets"],
                "fns": sorted(c["fns"])})
json.dump(out, open(SCR + "/ws2_clusters.json", "w"), indent=1)
print("distinct addrs:", len(addrs), "-> clusters:", len(out))
# biggest / most-referenced clusters first
out.sort(key=lambda c: -c["naddr"])
for c in out[:25]:
    print("  base %s size %-5d n=%-2d fns=%s" %
          (c["base"], c["size"], c["naddr"], ",".join(c["fns"][:3])))
