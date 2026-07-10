"""Merge all per-agent ledgers, de-dupe by address, and independently RE-VERIFY
every 'proven' reconstruction from its saved recon/app/src/*.c (trust nothing —
re-run the parity harness here). Prints a status table."""
import sys, os, glob, json, re
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import recon_kit
from parity import recon

SCRATCH = recon_kit.SCRATCH
SRC = recon_kit.RECON_SRC

def merge():
    best = {}
    for f in glob.glob(SCRATCH + "/ledger_*.json"):
        try:
            for x in json.load(open(f)):
                k = x["entry_hex"]
                if k not in best or (x.get("pass") and not best[k].get("pass")):
                    best[k] = x
        except Exception:
            pass
    return best

def reverify():
    """Re-prove each saved .c independently."""
    results = []
    for cf in sorted(glob.glob(SRC + "/*.c")):
        src = open(cf).read()
        name = os.path.basename(cf)[:-2]
        m = re.search(r"@ (0x[0-9a-fA-F]+)", src)
        if not m:
            results.append((name, None, "no-addr-comment")); continue
        va = int(m.group(1), 16)
        info = recon_kit.info(va)
        if not info:
            results.append((name, va, "no-info")); continue
        rk = recon_kit._ret_kind(va)
        ok = False
        for nptr in (2, 1, 0):
            v = recon.prove(va, info["size"], src, name, trials=200, nptr=nptr,
                            ret_kind=rk)
            if v.get("pass"):
                ok = True; break
        results.append((name, va, "VERIFIED" if ok else "REVERIFY-FAIL(%s)" % rk))
    return results

if __name__ == "__main__":
    best = merge()
    p = sum(1 for x in best.values() if x.get("pass"))
    print("merged ledger: %d proven / %d attempted" % (p, len(best)))
    json.dump(list(best.values()), open(SCRATCH + "/ledger_merged.json", "w"), indent=1)
    if len(sys.argv) > 1 and sys.argv[1] == "verify":
        print("--- independent re-verification of saved sources ---")
        for name, va, st in reverify():
            print("  %-40s %-10s %s" % (name, hex(va) if va else "?", st))
