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
import sys, os, re, json, glob, time, subprocess, hashlib
sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import extract as ax, net_extract as nx
from parity import recon, emu
import recon_kit, net_recon_kit

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
BASE = "/Users/freedomcoder/Projects/G1disasm2"
_HDR = re.compile(r'@\s+(0x[0-9a-fA-F]+)')
_CACHE = {}


def _sha256_path(path):
    h = hashlib.sha256()
    with open(path, "rb") as fp:
        for chunk in iter(lambda: fp.read(1024 * 1024), b""):
            h.update(chunk)
    return h.hexdigest()


def _canonical_inventory():
    """Return the canonical function list and its exact source-byte hashes."""
    todo = {}
    source_hashes = {}
    for core in ("app", "net"):
        srcdir = (BASE + "/recon/app/src" if core == "app"
                  else BASE + "/recon/net/src")
        names = sorted(
            os.path.basename(path)[:-2]
            for path in glob.glob(srcdir + "/*.c")
        )
        todo[core] = names
        source_hashes[core] = {
            name: _sha256_path(os.path.join(srcdir, name + ".c"))
            for name in names
        }
    return todo, source_hashes


def _digest_json(value):
    return hashlib.sha256(
        json.dumps(value, sort_keys=True, separators=(",", ":")).encode()
    ).hexdigest()

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
    import cfg_verify
    idx = int(sys.argv[2])
    batch = json.load(open(SCR + "/reverify_agent_batches.json"))[idx]
    fails = []
    for it in batch:
        try:
            st = cfg_verify.verify(it["core"], it["name"])["status"]
        except Exception as e:
            st = "other-exc"
        print("%-30s %s" % (it["name"], st), flush=True)
        if st == "FAIL":
            fails.append("%s:%s" % (it["core"], it["name"]))
    print("\nFAILS(%d): %s" % (len(fails), " ".join(fails)), flush=True)

def run_sweeplist():
    # sweeplist <core> <shard> <nShards>  -- CFG-directed sweep of sweep_todo.json[core]
    import cfg_verify
    core = sys.argv[2]; si = int(sys.argv[3]); ns = int(sys.argv[4])
    todo_path = SCR + "/sweep_todo.json"
    # The scratchpad can be both volatile *and stale*.  Rebuild the inventory
    # from canonical sources on every invocation, and replace the cached todo
    # whenever functions were added, removed, or renamed.  Merely checking for
    # file existence previously left 239 app and 193 net sources outside the
    # saved July-16 inventory.
    todo, inventory_source_hashes = _canonical_inventory()
    cached_todo = None
    if os.path.exists(todo_path):
        try:
            cached_todo = json.load(open(todo_path))
        except (OSError, ValueError):
            cached_todo = None
    if cached_todo != todo:
        os.makedirs(SCR, exist_ok=True)
        tmp = todo_path + ".tmp.%d" % os.getpid()
        with open(tmp, "w") as fp:
            json.dump(todo, fp, indent=2)
            fp.write("\n")
        os.replace(tmp, todo_path)
    todo_digest = _digest_json(todo)
    inventory_digest = _digest_json({
        todo_core: [
            [name, inventory_source_hashes[todo_core][name]]
            for name in todo[todo_core]
        ]
        for todo_core in ("app", "net")
    })
    core_inventory_digest = _digest_json([
        [name, inventory_source_hashes[core][name]] for name in todo[core]
    ])
    names = todo[core][si::ns]
    outp = SCR + "/reverify_%s_L%d.json" % (core, si)
    recheck = os.environ.get("CFG_VERIFY_RECHECK") == "1"
    if os.path.exists(outp) and not recheck:
        old = json.load(open(outp))
        if (old.get("_todo_digest") == todo_digest and
                old.get("_inventory_digest") == inventory_digest and
                old.get("_shard_count") == ns and
                old.get("_shard_index") == si):
            res = {k: list(old.get(k, []))
                   for k in ("PASS", "FAIL", "compile_error", "other",
                             "timeout", "source_changed")}
            res["_source_hashes"] = dict(old.get("_source_hashes", {}))
            res["_source_change_detail"] = dict(
                old.get("_source_change_detail", {}))
        else:
            # Lane membership changes when the sorted inventory changes.  A
            # receipt without the exact inventory/shard identity cannot prove
            # this lane and must be discarded fail-closed.
            res = {"PASS": [], "FAIL": [], "compile_error": [],
                   "other": [], "timeout": [], "source_changed": [],
                   "_source_hashes": {}, "_source_change_detail": {}}
    else:
        res = {"PASS": [], "FAIL": [], "compile_error": [],
               "other": [], "timeout": [], "source_changed": [],
               "_source_hashes": {}, "_source_change_detail": {}}
    res.update({"_todo_digest": todo_digest,
                "_inventory_digest": inventory_digest,
                "_core_inventory_digest": core_inventory_digest,
                "_inventory_count": len(todo[core]),
                "_shard_count": ns, "_shard_index": si,
                "_tool_hashes": {
                    "tools/reverify.py": _sha256_path(__file__),
                    "tools/cfg_verify.py": _sha256_path(
                        BASE + "/tools/cfg_verify.py"),
                    "tools/parity/emu.py": _sha256_path(
                        BASE + "/tools/parity/emu.py"),
                    "tools/parity/recon.py": _sha256_path(
                        BASE + "/tools/parity/recon.py"),
                }})
    done = set(sum((res[k] for k in (
        "PASS", "FAIL", "compile_error", "other", "timeout",
        "source_changed")), []))
    timeout_s = int(os.environ.get("CFG_VERIFY_TIMEOUT", "120"))
    t0 = time.time()
    processed = 0
    for i, nm in enumerate(names, 1):
        if nm in done:
            continue
        source_path = os.path.join(
            BASE, "recon", "app" if core == "app" else "net", "src",
            nm + ".c")
        before_hash = (_sha256_path(source_path)
                       if os.path.exists(source_path) else None)
        try:
            env = dict(os.environ, PYTHONSAFEPATH="1")
            cp = subprocess.run([sys.executable, BASE + "/tools/cfg_verify.py", core, nm],
                                cwd="/private/tmp", env=env, capture_output=True,
                                text=True, timeout=timeout_s)
            m = re.search(r'^\S+\s+(PASS|FAIL|\S+)', cp.stdout, re.M)
            st = m.group(1) if m else "other-exc"
        except subprocess.TimeoutExpired:
            st = "timeout"
        except Exception:
            st = "other-exc"
        after_hash = (_sha256_path(source_path)
                      if os.path.exists(source_path) else None)
        expected_hash = inventory_source_hashes[core][nm]
        if (before_hash != expected_hash or after_hash != expected_hash or
                before_hash is None):
            bucket = "source_changed"
            res["_source_change_detail"][nm] = {
                "inventory_sha256": expected_hash,
                "before_sha256": before_hash, "after_sha256": after_hash,
            }
        else:
            res["_source_hashes"][nm] = before_hash
            bucket = ("PASS" if st == "PASS" else
                      "FAIL" if st == "FAIL" else
                      "compile_error" if st == "compile-fail" else
                      "timeout" if st == "timeout" else "other")
        res[bucket].append(nm)
        done.add(nm)
        processed += 1
        if processed % 20 == 0:
            print("[%s L%d] %d/%d fail=%d compile=%d timeout=%d changed=%d (%.0fs)" % (
                  core, si, len(done), len(names), len(res["FAIL"]),
                  len(res["compile_error"]), len(res["timeout"]),
                  len(res["source_changed"]), time.time() - t0), flush=True)
        tmp = outp + ".tmp.%d" % os.getpid()
        with open(tmp, "w") as fp:
            json.dump(res, fp)
        os.replace(tmp, outp)
    print("[%s L%d] DONE pass=%d FAIL=%d compile=%d other=%d timeout=%d changed=%d" % (
          core, si, len(res["PASS"]), len(res["FAIL"]),
          len(res["compile_error"]), len(res["other"]),
          len(res["timeout"]), len(res["source_changed"])), flush=True)

if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else "sweep"
    if cmd == "sweeplist": run_sweeplist()
    elif cmd == "batch": run_batch()
    elif cmd == "check": print(sys.argv[3], verify(sys.argv[2],
        core_ctx(sys.argv[2])["srcdir"] + "/" + sys.argv[3] + ".c"))
    else: run_sweep()
