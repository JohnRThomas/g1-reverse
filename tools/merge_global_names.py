"""Stage D: consolidate agent-proposed global names (from a naming workflow's
journal.jsonl) + the rule-based auto-names into a canonical global_names.json,
dedupe identifiers, and report. This canonical table is then consumed by
build_symbol_map.py (via harvest) so the names flow into the symbol map.
NON-DESTRUCTIVE except writing global_names_<core>.json.
"""
import sys, os, re, json, glob, collections

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
CORE = "app"
JOURNAL = None
for a in sys.argv[1:]:
    if a.endswith(".jsonl") or "/" in a: JOURNAL = a
    else: CORE = a

def load_agent_names(journal):
    """Each line {'type':'result', ...} carries an agent return with .names."""
    out = []
    if not journal or not os.path.exists(journal):
        return out
    for ln in open(journal):
        ln = ln.strip()
        if not ln: continue
        try: obj = json.loads(ln)
        except Exception: continue
        # the agent return may be nested under result/value/output depending on shape
        cand = obj
        for k in ("result", "value", "output", "data"):
            if isinstance(cand, dict) and k in cand and isinstance(cand[k], (dict, list)):
                cand = cand[k]
        # find a dict with 'names' anywhere shallow
        def find_names(x, depth=0):
            if depth > 4: return None
            if isinstance(x, dict):
                if isinstance(x.get("names"), list): return x["names"]
                for v in x.values():
                    r = find_names(v, depth+1)
                    if r is not None: return r
            if isinstance(x, list):
                for v in x:
                    r = find_names(v, depth+1)
                    if r is not None: return r
            return None
        nm = find_names(obj)
        if nm: out.extend(nm)
    return out

def valid_ident(n):
    return bool(re.match(r'^[A-Za-z_][A-Za-z0-9_]*$', n or "")) and len(n) <= 48

def main():
    agent_names = load_agent_names(JOURNAL)
    # rule-based auto names (Stage B)
    auto = {}
    ap = SCR + "/global_auto_%s.json" % CORE
    if os.path.exists(ap):
        for a, d in json.load(open(ap)).items():
            auto[a] = {"addr": a, "name": d["name"], "confidence": d.get("conf", "high"),
                       "rationale": d.get("reason", "rule"), "source": "rule"}

    canon = dict(auto)
    conflict = 0
    for n in agent_names:
        a = n.get("addr")
        if not a: continue
        try: a = hex(int(a, 16))
        except Exception: continue
        nm = n.get("name")
        if not valid_ident(nm):
            continue
        # prefer higher confidence / agent over rule when both exist
        prev = canon.get(a)
        if prev and prev.get("source") == "rule" and n.get("confidence") == "low":
            continue
        canon[a] = {"addr": a, "name": nm, "ctype": n.get("ctype"),
                    "confidence": n.get("confidence"), "is_library": n.get("is_library"),
                    "upstream_file": n.get("upstream_file"),
                    "rationale": n.get("rationale"), "source": "agent"}

    # dedupe identifiers: same name on different addrs -> suffix with addr tail
    byname = collections.defaultdict(list)
    for a, d in canon.items():
        byname[d["name"]].append(a)
    for nm, addrs in byname.items():
        if len(addrs) > 1:
            for a in sorted(addrs):
                # keep library statics' canonical name only once (first addr); suffix the rest
                if a != sorted(addrs)[0]:
                    canon[a]["name"] = "%s_%s" % (nm, a[-4:])
                    conflict += 1

    out = SCR + "/global_names_%s.json" % CORE
    json.dump(canon, open(out, "w"), indent=1)
    conf = collections.Counter(d.get("confidence") for d in canon.values())
    lib = sum(1 for d in canon.values() if d.get("is_library"))
    print("[%s] canonical global names: %d" % (CORE, len(canon)))
    print("  from agents: %d | from rules: %d" % (
        sum(1 for d in canon.values() if d.get("source")=="agent"),
        sum(1 for d in canon.values() if d.get("source")=="rule")))
    print("  confidence:", dict(conf))
    print("  library statics: %d | app globals: %d" % (lib, len(canon)-lib))
    print("  identifier collisions auto-suffixed:", conflict)
    print("  ->", out)

if __name__ == "__main__":
    main()
