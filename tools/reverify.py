"""Re-verify saved reconstructions with the input-aware (fixed) harness.
A reconstruction that still passes was a real proof; one that now fails was a
FALSE proof (only its default path was ever fuzzed) and must be redone.

Modes:
  reverify.py sweep <core> <trials> [shardIdx nShards]  -- full/shard sweep
  reverify.py batch <idx>                               -- re-verify one agent batch
  reverify.py check <core> <name|addr>                  -- one function
READ-ONLY. Fast path: nptr=2 first (false proofs are arg-VALUE bugs, nptr-agnostic),
escalate nptr only on fail; trials default 40.
"""
import sys, os, re, json, glob, time
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import extract as ax, net_extract as nx
from parity import recon, emu
import recon_kit, net_recon_kit

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
BASE = "/Users/freedomcoder/Projects/G1disasm2"
_HDR = re.compile(r'@\s+(0x[0-9a-fA-F]+)')
_CACHE = {}

def core_ctx(core):
    if core in _CACHE:
        return _CACHE[core]
    if core == "app":
        ctx = dict(srcdir=BASE + "/recon/verified/src", read=ax.func_bytes_padded,
                   cb=emu.CODE_BASE, ret=recon_kit._ret_kind,
                   sizes={f["entry"]: f["size"] for f in json.load(open(SCR + "/classified.json"))["functions"]})
    else:
        ctx = dict(srcdir=BASE + "/recon/net/src", read=nx.func_bytes_padded,
                   cb=emu.NET_CODE_BASE, ret=net_recon_kit._ret_kind,
                   sizes={f["entry"]: f["size"] for f in json.load(open(SCR + "/net_funcs.json"))["functions"]})
    _CACHE[core] = ctx
    return ctx

def verify(core, path, trials=40):
    """Return 'PASS' / 'FAIL' / 'other-<reason>' for a saved reconstruction."""
    ctx = core_ctx(core)
    name = os.path.basename(path)[:-2]
    txt = open(path).read()
    m = _HDR.search(txt.split("\n")[0])
    if not m:
        return "other-noaddr"
    va = int(m.group(1), 16)
    size = ctx["sizes"].get(va) or ctx["sizes"].get(va & ~1)
    if not size:
        return "other-nosize"
    body = txt[txt.index("*/") + 2:] if "*/" in txt[:400] else txt
    try:
        comp, err = recon.compile_func(body, name, va)
    except Exception as e:
        return "other-compile"
    if err:
        return "other-compile"
    cbody, ctail, csize, cva = comp
    orig = ctx["read"](va, size, 64)
    rk = ctx["ret"](va)
    for nptr in (2, 1, 3):
        try:
            v = emu.compare(orig, va, size, cbody + ctail, cva, csize,
                            code_base=ctx["cb"], trials=trials, nptr=nptr, ret_kind=rk)
            if not v.get("pass") and v.get("checked") == 0:
                v = emu.compare(orig, va, size, cbody + ctail, cva, csize,
                                code_base=ctx["cb"], trials=trials, nptr=nptr,
                                ret_kind=rk, no_return=True)
            if v.get("pass"):
                return "PASS"
        except Exception:
            continue
    return "FAIL"

def run_sweep():
    core = sys.argv[2]; trials = int(sys.argv[3]) if len(sys.argv) > 3 else 40
    files = sorted(glob.glob(core_ctx(core)["srcdir"] + "/*.c"))
    shard = None
    if len(sys.argv) > 5:
        si, ns = int(sys.argv[4]), int(sys.argv[5]); files = files[si::ns]; shard = si
    res = {"PASS": [], "FAIL": [], "other": []}
    sfx = ("_s%d" % shard) if shard is not None else ""
    outp = SCR + "/reverify_%s%s.json" % (core, sfx)
    t0 = time.time()
    for i, f in enumerate(files, 1):
        st = verify(core, f, trials)
        nm = os.path.basename(f)[:-2]
        (res["PASS"] if st == "PASS" else res["FAIL"] if st == "FAIL" else res["other"]).append(nm)
        if i % 50 == 0:
            print("[%s%s] %d/%d pass=%d fail=%d (%.0fs)" % (core, sfx, i, len(files),
                  len(res["PASS"]), len(res["FAIL"]), time.time() - t0), flush=True)
        json.dump(res, open(outp, "w"))
    print("[%s%s] DONE pass=%d FAIL=%d other=%d" % (core, sfx, len(res["PASS"]),
          len(res["FAIL"]), len(res["other"])), flush=True)

def run_batch():
    idx = int(sys.argv[2])
    batch = json.load(open(SCR + "/reverify_agent_batches.json"))[idx]
    fails = []
    for it in batch:
        p = core_ctx(it["core"])["srcdir"] + "/" + it["name"] + ".c"
        if not os.path.exists(p):
            print("%-30s MISSING" % it["name"], flush=True); continue
        st = verify(it["core"], p, 50)
        print("%-30s %s" % (it["name"], st), flush=True)
        if st == "FAIL":
            fails.append("%s:%s" % (it["core"], it["name"]))
    print("\nFAILS(%d): %s" % (len(fails), " ".join(fails)), flush=True)

if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else "sweep"
    if cmd == "batch": run_batch()
    elif cmd == "check": print(sys.argv[3], verify(sys.argv[2],
        core_ctx(sys.argv[2])["srcdir"] + "/" + sys.argv[3] + ".c"))
    else: run_sweep()
