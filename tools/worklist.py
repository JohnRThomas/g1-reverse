"""
Durable work-queue for the breadth reconstruction.

Emits the next N application functions that still need a parity proof, smallest
first (highest hit-rate). Excludes: thunks, already-proven (any ledger), and
functions confirmed to be library code by the fuzzy structural matcher.

Usage:
  python worklist.py stats                 # remaining scope summary
  python worklist.py next 120              # print next 120 addresses (hex)
  python worklist.py next 120 --named      # only named functions
  python worklist.py batches 8 15          # 8 batches of 15, space-joined lines
"""

# Resolvable pipeline scratchpad (tools/g1_paths.py).  This used to be one
# literal /private/tmp path belonging to a finished agent session; see that
# module for the resolution order and the fail-closed catalog fallback.
import os as _g1_os, sys as _g1_sys
_G1_TOOLS = _g1_os.path.dirname(_g1_os.path.abspath(__file__))
if _g1_os.path.basename(_G1_TOOLS) != "tools":
    _G1_TOOLS = _g1_os.path.dirname(_G1_TOOLS)
if _G1_TOOLS not in _g1_sys.path:
    _g1_sys.path.insert(0, _G1_TOOLS)
import g1_paths as _g1_paths
import sys, json, glob
SCR = _g1_paths.scratchpad()

def proven_set():
    s = set()
    for f in glob.glob(SCR + "/ledger_*.json") + [SCR + "/recon_ledger.json"]:
        try:
            for x in json.load(open(f)):
                if x.get("pass"):
                    s.add(int(x["entry_hex"], 16))
        except Exception:
            pass
    return s

def attempted_failed_set():
    """Addresses with a ledger entry but never proven -> deferred to the
    hard-tail pass so breadth waves stop recycling them."""
    proven = proven_set()
    s = set()
    for f in glob.glob(SCR + "/ledger_*.json") + [SCR + "/recon_ledger.json"]:
        try:
            for x in json.load(open(f)):
                a = int(x["entry_hex"], 16)
                if not x.get("pass") and a not in proven:
                    s.add(a)
        except Exception:
            pass
    return s

def fuzzy_lib():
    s = set()
    try:
        s |= set(int(h[0], 16) for h in json.load(open(SCR + "/lib_fuzzy_hits.json")))
    except Exception:
        pass
    try:  # v2 ordered-sequence library matches (NCS 2.5.1, ratio>=0.90)
        s |= set(int(a, 16) for a in json.load(open(SCR + "/lib_sig2_hits.json")))
    except Exception:
        pass
    return s

def defer_list():
    """Explicit hard-tail addresses (idle loops, indirect vtable tail-calls,
    float/64-bit ABI) deferred out of breadth waves. One hex addr per line."""
    s = set()
    try:
        for ln in open(SCR + "/defer_list.txt"):
            ln = ln.strip()
            if ln and not ln.startswith("#"):
                s.add(int(ln.split()[0], 16))
    except Exception:
        pass
    return s

def load():
    fw = {f["entry"]: f for f in json.load(open(SCR + "/app_funcs.json"))["functions"]}
    cls = {c["entry"]: c for c in json.load(open(SCR + "/classified.json"))["functions"]}
    return fw, cls

def remaining(named=None, max_size=100000, min_size=1):
    fw, cls = load()
    done = proven_set(); lib = fuzzy_lib()
    deferred = attempted_failed_set() | defer_list()
    out = []
    for e, c in cls.items():
        if c["class"] != "APPLICATION" or c["is_thunk"]:
            continue
        if e in done or e in lib or e in deferred:
            continue
        sz = fw[e]["size"]
        if sz < min_size or sz > max_size:
            continue
        isn = bool(c["ida_name"])
        if named is True and not isn:
            continue
        if named is False and isn:
            continue
        out.append((sz, e, c["name"]))
    out.sort()
    return out

if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else "stats"
    named = None
    if "--named" in sys.argv: named = True
    if "--unnamed" in sys.argv: named = False
    if cmd == "stats":
        r = remaining()
        rn = [x for x in r if True]
        fw, cls = load()
        print("remaining application funcs to prove:", len(r),
              "(%d bytes)" % sum(x[0] for x in r))
        nn = sum(1 for x in r if cls[x[1]]["ida_name"])
        print("  named:", nn, " unnamed:", len(r) - nn)
        print("  proven so far:", len(proven_set()), " fuzzy-library excluded:", len(fuzzy_lib()))
    elif cmd == "next":
        n = int(sys.argv[2])
        for sz, e, nm in remaining(named=named)[:n]:
            print("0x%x" % e)
    elif cmd == "batches":
        nb = int(sys.argv[2]); per = int(sys.argv[3])
        r = remaining(named=named)[:nb * per]
        for i in range(nb):
            chunk = r[i*per:(i+1)*per]
            if chunk:
                print(" ".join("0x%x" % e for _, e, _ in chunk))
