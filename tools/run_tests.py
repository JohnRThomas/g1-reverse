#!/usr/bin/env python3
"""Run every tools/test_*.py and report an honest pass/fail baseline.

There are 159 of these files and, until now, nothing that ran them: no
pytest.ini, no Makefile, no CI entry point.  "Green" had no definition.

Why a subprocess per file rather than `unittest discover`:
  * these are proof scripts, not unit tests -- several boot Unicorn, compile
    with arm-none-eabi-gcc, or sweep hundreds of functions, and a single one
    that hangs or calls sys.exit() would take the whole discovery run with it;
  * they share a flat module namespace and mutate sys.path at import time, so
    importing all 159 into one interpreter is not the environment any of them
    was written for;
  * per-file isolation is what makes a per-file baseline meaningful.

Every file gets a wall-clock timeout and its own verdict.  A timeout is
reported as a timeout, never as a pass.

Usage:
    python tools/run_tests.py [-j N] [--timeout S] [--pattern GLOB]
                              [--json OUT] [--list]
Exit status is 0 only when every selected file passes.
"""

import argparse
import concurrent.futures
import glob
import json
import os
import subprocess
import sys
import time

TOOLS = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(TOOLS)


def discover(pattern):
    return sorted(glob.glob(os.path.join(TOOLS, pattern)))


def run_one(path, timeout):
    env = dict(os.environ)
    env.setdefault("PYTHONSAFEPATH", "1")
    # The scripts assume they can `import extract`, `import cfg_verify`, ...
    # An EMPTY PYTHONPATH entry means "the current directory", and the repo
    # root contains struct.py -- which shadows the stdlib `struct` module and
    # breaks half the corpus with an ImportError that has nothing to do with
    # the test.  Never emit a trailing separator.
    inherited = env.get("PYTHONPATH", "")
    env["PYTHONPATH"] = (TOOLS + os.pathsep + inherited) if inherited else TOOLS
    started = time.time()
    try:
        proc = subprocess.run([sys.executable, path], cwd=REPO, env=env,
                              capture_output=True, text=True, timeout=timeout)
        status = "pass" if proc.returncode == 0 else "fail"
        code = proc.returncode
        out, err = proc.stdout, proc.stderr
    except subprocess.TimeoutExpired as exc:
        status, code = "timeout", None
        out = exc.stdout.decode() if isinstance(exc.stdout, bytes) else (exc.stdout or "")
        err = exc.stderr.decode() if isinstance(exc.stderr, bytes) else (exc.stderr or "")
    return {"file": os.path.basename(path), "status": status,
            "returncode": code, "seconds": round(time.time() - started, 1),
            "stdout_tail": out[-2000:], "stderr_tail": err[-4000:]}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("-j", "--jobs", type=int, default=max(1, (os.cpu_count() or 4) // 2))
    ap.add_argument("--timeout", type=float, default=900.0)
    ap.add_argument("--pattern", default="test_*.py")
    ap.add_argument("--json", default=None)
    ap.add_argument("--list", action="store_true")
    args = ap.parse_args()

    paths = discover(args.pattern)
    if args.list:
        for p in paths:
            print(os.path.basename(p))
        return 0
    if not paths:
        print("no test files matched %r" % args.pattern)
        return 2

    print("running %d files, %d jobs, %.0fs timeout" %
          (len(paths), args.jobs, args.timeout), flush=True)
    results = []
    started = time.time()
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures = {pool.submit(run_one, p, args.timeout): p for p in paths}
        for done in concurrent.futures.as_completed(futures):
            row = done.result()
            results.append(row)
            print("%-8s %6.1fs  %s" % (row["status"].upper(), row["seconds"],
                                       row["file"]), flush=True)

    results.sort(key=lambda r: r["file"])
    counts = {}
    for row in results:
        counts[row["status"]] = counts.get(row["status"], 0) + 1
    print("\n=== baseline ===")
    print("total %d  %s  (%.0fs wall)" %
          (len(results), "  ".join("%s=%d" % kv for kv in sorted(counts.items())),
           time.time() - started))
    for row in results:
        if row["status"] != "pass":
            first = next((l for l in reversed(row["stderr_tail"].splitlines())
                          if l.strip()), "")
            print("  %-8s %-58s %s" % (row["status"], row["file"], first[:110]))
    if args.json:
        with open(args.json, "w") as stream:
            json.dump({"counts": counts, "results": results}, stream, indent=1)
        print("wrote %s" % args.json)
    return 0 if counts.get("pass", 0) == len(results) else 1


if __name__ == "__main__":
    raise SystemExit(main())
