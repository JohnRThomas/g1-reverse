"""Net-core library exclusion by opcode-sequence sig-match against the hci_rpmsg
reference build (BLE controller + MPSL + net-core Zephyr). Every net-core
function that matches upstream is LIBRARY -> excluded; the survivors are the net
core's own application logic (the reconstruction target)."""
import json, sys, difflib
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import net_extract as nx
import lib_sigmatch2 as L
from opt_sweep import build_index

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
NETREF = "/Users/freedomcoder/ncs251/netref_build"
THRESH = 0.90

def main():
    by_len = build_index(NETREF)
    print("net-core reference opcode-seqs:", sum(len(v) for v in by_len.values()))
    fns = json.load(open(SCR + "/net_funcs.json"))["functions"]
    lib = {}
    n_lib = n_app = 0
    app_bytes = 0
    for f in fns:
        if f["is_thunk"] or f["size"] < 16:
            continue
        code = nx.func_bytes_padded(f["entry"], f["size"], 0)
        if not code:
            continue
        seq = L.ops(code, f["entry"])
        if len(seq) < 6:
            continue
        best = (0.0, None)
        for dl in range(-2, 3):
            for nm, rseq in by_len.get(len(seq) + dl, ()):
                r = difflib.SequenceMatcher(None, seq, rseq).ratio()
                if r > best[0]:
                    best = (r, nm)
        if best[0] >= THRESH:
            lib[f["entry_hex"]] = {"name": best[1], "ratio": round(best[0], 3)}
            n_lib += 1
        else:
            n_app += 1
            app_bytes += f["size"]
    json.dump(lib, open(SCR + "/net_lib_hits.json", "w"), indent=1)
    print("LIBRARY (matched upstream, excluded):", n_lib)
    print("APPLICATION (reconstruction target):", n_app, "(%d bytes)" % app_bytes)
    # sample identified library
    import collections
    fam = collections.Counter()
    for h in lib.values():
        nm = h["name"]
        fam[nm.split("_")[0] if "_" in nm else nm[:6]] += 1
    print("  top library families:", dict(fam.most_common(10)))

if __name__ == "__main__":
    main()
