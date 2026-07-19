"""Part A/A2: inter-procedural unification of struct bases into canonical clusters.

Param structs are collapsed with union-find over call-argument flow: if a caller
passes its own `param_N` as the i-th argument to a callee, then the caller's
param_N and the callee's param_(i+1) describe the same object -> union them.
Global bases are unified by address (already shared). Stack bases stay per
function (a frame local is not shared across functions).

Each resulting cluster merges the access footprints of its members, so agents
work on a small number of canonical types instead of hundreds of call sites.
Output: recon/structs/clusters_app.json.
"""
import gzip, json, os, re, sys
from collections import defaultdict

BASE = "/Users/freedomcoder/Projects/G1disasm2"
OUT = BASE + "/recon/structs"
SRC = BASE + "/recon/catalogs/app_funcs.json.gz"

CALL = None  # compiled per run once we know the name set


class UF:
    def __init__(self):
        self.p = {}

    def find(self, x):
        self.p.setdefault(x, x)
        while self.p[x] != x:
            self.p[x] = self.p[self.p[x]]
            x = self.p[x]
        return x

    def union(self, a, b):
        ra, rb = self.find(a), self.find(b)
        if ra != rb:
            self.p[ra] = rb


def split_args(s):
    """Split a call argument list on top-level commas."""
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip()); cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def main():
    data = json.load(gzip.open(SRC))
    foot = json.load(open(OUT + "/footprints_app.json"))["footprints"]
    name2entry = {}
    for fn in data["functions"]:
        e = fn.get("entry_hex") or ("0x%x" % fn.get("entry", 0))
        name2entry[fn["name"]] = e
    names = sorted(name2entry, key=len, reverse=True)
    callre = re.compile(r'\b(' + "|".join(re.escape(n) for n in names) + r')\s*\(([^;{}]*)\)')

    uf = UF()
    # seed every param node
    for key, rec in foot.items():
        if rec["kind"] == "param":
            uf.find(key)

    edges = 0
    for fn in data["functions"]:
        if fn.get("is_thunk") or fn.get("is_external"):
            continue
        dc = fn.get("decompiled") or ""
        if not dc:
            continue
        entry = fn.get("entry_hex") or ("0x%x" % fn.get("entry", 0))
        for m in callre.finditer(dc):
            callee, arglist = m.group(1), m.group(2)
            callee_entry = name2entry.get(callee)
            if not callee_entry:
                continue
            for i, arg in enumerate(split_args(arglist)):
                pm = re.fullmatch(r'param_(\d+)', arg)
                if not pm:
                    continue
                caller_node = "param:%s:param_%s" % (entry, pm.group(1))
                callee_node = "param:%s:param_%d" % (callee_entry, i + 1)
                if caller_node in foot or callee_node in foot:
                    uf.union(caller_node, callee_node)
                    edges += 1

    # build clusters
    clusters = defaultdict(lambda: {"members": [], "kind": "param",
                                    "accesses": defaultdict(lambda: {"sizes": set(), "rw": set(), "types": set()})})
    # param clusters via UF
    for key, rec in foot.items():
        if rec["kind"] != "param":
            continue
        root = uf.find(key)
        cl = clusters[("param", root)]
        cl["members"].append({"func": rec["func"], "entry": rec["entry"], "base": rec["base"]})
        for off, a in rec["accesses"].items():
            t = cl["accesses"][off]
            t["sizes"].update(a["sizes"]); t["rw"].update(a["rw"]); t["types"].update(a["types"])
    # global clusters by address; stack clusters per base
    for key, rec in foot.items():
        if rec["kind"] == "param":
            continue
        cid = ("global", rec["base"]) if rec["kind"] == "global" else ("stack", key)
        cl = clusters[cid]
        cl["kind"] = rec["kind"]
        cl["members"].append({"func": rec["func"], "entry": rec["entry"], "base": rec["base"]})
        for off, a in rec["accesses"].items():
            t = cl["accesses"][off]
            t["sizes"].update(a["sizes"]); t["rw"].update(a["rw"]); t["types"].update(a["types"])

    out = {}
    n = 0
    for (kind, cid), cl in clusters.items():
        acc = {}
        for off, a in cl["accesses"].items():
            acc[off] = {"sizes": sorted(a["sizes"]), "rw": sorted(a["rw"]), "types": sorted(a["types"])}
        acc = dict(sorted(acc.items(), key=lambda kv: int(kv[0], 16)))
        maxoff = max((int(o, 16) for o in acc), default=0)
        maxsz = max((max(v["sizes"]) for v in acc.values()), default=4)
        cid_str = "%s_%04d" % (kind, n)
        out[cid_str] = {
            "kind": kind,
            "n_members": len(cl["members"]),
            "n_offsets": len(acc),
            "min_size_bytes": maxoff + maxsz,
            "members": sorted(cl["members"], key=lambda m: m["entry"])[:40],
            "n_members_total": len(cl["members"]),
            "accesses": acc,
        }
        n += 1

    json.dump({"clusters": out}, open(OUT + "/clusters_app.json", "w"), indent=1)

    real = {k: 0 for k in ("param", "global", "stack")}
    for c in out.values():
        if c["n_offsets"] >= 2:
            real[c["kind"]] += 1
    print("call-arg flow edges:", edges)
    print("clusters total:", len(out))
    print("clusters with >=2 offsets (agent work items):", real, "= ", sum(real.values()))
    # distribution of param cluster fan-in
    fan = sorted((c["n_members_total"] for k, c in out.items() if c["kind"] == "param"), reverse=True)[:10]
    print("largest param-cluster member counts:", fan)


if __name__ == "__main__":
    main()
