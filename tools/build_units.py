"""Build graph-driven work units for the Fable waves.
 A) module_units.json — per module: functions, the public API (functions called
    from OTHER modules), internal call structure, owned data addrs, entry points.
 B) data_units.json — rodata/data objects (clustered contiguous addresses that
    functions read) split into batches for data-recovery agents.
Uses the authoritative Ghidra reference graph (refgraph_app.json)."""
import json
from collections import defaultdict
SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"

g = json.load(open(SCR + "/refgraph_app.json"))["functions"]
groups = json.load(open(SCR + "/topic_groups.json"))
# addr(int) -> module
mod_of = {}
for m, fns in groups.items():
    for f in fns:
        mod_of[int(f["addr"], 16)] = m

def gi(h):
    try:
        v = int(h, 16)
        return v if v >= 0 else None
    except Exception:
        return None

# ---- A) module units ----
units = {}
for m, fns in groups.items():
    addrs = [int(f["addr"], 16) for f in fns]
    aset = set(addrs)
    api = []          # funcs in this module called from a DIFFERENT module
    owned_data = set()
    entry = []        # funcs with no in-module caller (thread mains / callbacks)
    for a in addrs:
        node = g.get("0x%x" % a)
        if not node:
            continue
        callers = [c for c in (gi(x) for x in node["callers"]) if c is not None]
        ext_callers = [c for c in callers if mod_of.get(c) not in (m, None)]
        if ext_callers or not callers:
            api.append("0x%x" % a)
        if not any(c in aset for c in callers):
            entry.append("0x%x" % a)
        for d in node["data_refs"]:
            di = gi(d)
            if di is not None:
                owned_data.add(di)
    units[m] = {"nfuncs": len(addrs), "api": api[:60], "entry_points": entry[:30],
                "n_owned_data": len(owned_data)}
json.dump(units, open(SCR + "/module_units.json", "w"), indent=1)

# ---- B) data objects: cluster flash-rodata addresses functions read ----
FLASH_LO, FLASH_HI = 0xC200, 0xE7000      # image rodata window (below code end)
data_hits = defaultdict(set)              # addr -> funcs that read it
for a, node in g.items():
    for d in node["data_refs"]:
        di = gi(d)
        if di is not None and FLASH_LO <= di < FLASH_HI:
            data_hits[di].add(a)
addrs = sorted(data_hits)
clusters = []
cur = None
for a in addrs:
    if cur and a - cur["end"] <= 0x40:
        cur["end"] = a; cur["n"] += 1
    else:
        cur = {"base": a, "end": a, "n": 1}; clusters.append(cur)
data_objs = [{"base": "0x%x" % c["base"], "span": c["end"] - c["base"] + 4, "naddr": c["n"]}
             for c in clusters if c["end"] - c["base"] >= 4 or c["n"] >= 2]
# batch into ~12 groups
NB = 12
per = (len(data_objs) + NB - 1) // NB
data_batches = [data_objs[i*per:(i+1)*per] for i in range(NB)]
data_batches = [b for b in data_batches if b]
json.dump(data_batches, open(SCR + "/data_units.json", "w"), indent=1)

print("module units:", len(units))
for m in sorted(units, key=lambda k: -units[k]["nfuncs"])[:8]:
    u = units[m]
    print("  %-13s funcs=%-4d api=%-3d entry=%-2d owned_data=%d" %
          (m, u["nfuncs"], len(u["api"]), len(u["entry_points"]), u["n_owned_data"]))
print("data objects (rodata clusters):", len(data_objs), "-> %d batches" % len(data_batches))
