"""Harness self-tests for the guards landed on 2026-07-29.

Run:
    PYTHONSAFEPATH=1 .venv/bin/python recon/tests/test_modtest_guards.py

These are the cheap, pure-Python halves of the mechanisms in
`recon/analysis/test_architecture.md` §29 -- the ones a future edit could
silently undo without any vector noticing.  Each one exists because the
property it asserts was ABSENT and cost something measurable:

  * `vector_staleness` FAILED OPEN on an unstamped vector, and 100 % of the net
    core's corpus took that branch (net_test_coverage.md §9.1);
  * it also skipped an env-switch check when the field was simply MISSING,
    which reopens the same hole one level down;
  * `_expose_target` walked over a preprocessor directive and manufactured FOUR
    of the seven tree disagreements in a 593-symbol fan-out (§28.6.2);
  * the out-parameter fill has to be deterministic in (ordinal, index, offset)
    or the two sides do not agree (§29.2).
"""

import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(REPO, "tools", "modtest"))
sys.path.insert(0, os.path.join(REPO, "tools"))

import core as mtcore          # noqa: E402

FAILURES = []


def check(name, condition, detail=""):
    print("%-58s %s%s" % (name, "ok" if condition else "FAIL",
                          ("  " + detail) if detail and not condition else ""))
    if not condition:
        FAILURES.append(name)


def stamped(**overrides):
    harness = {"rev": mtcore.harness_rev(), **mtcore.harness_env()}
    harness.update(overrides)
    return {"harness": harness}


# ---- vector_staleness --------------------------------------------------
check("unstamped vector is REFUSED (fails closed)",
      mtcore.vector_staleness({}) is not None)
check("vector with harness={} is REFUSED",
      mtcore.vector_staleness({"harness": {}}) is not None)
check("vector at the current rev + env is accepted",
      mtcore.vector_staleness(stamped()) is None)
check("vector at a different rev is REFUSED",
      mtcore.vector_staleness(stamped(rev="0" * 16)) is not None)
for field in sorted(mtcore.harness_env()):
    record = stamped()
    record["harness"].pop(field)
    check("vector MISSING %s is REFUSED" % field,
          mtcore.vector_staleness(record) is not None)
    record = stamped()
    value = record["harness"][field]
    record["harness"][field] = (not value) if isinstance(value, bool) else value + 1
    check("vector with a DIFFERENT %s is REFUSED" % field,
          mtcore.vector_staleness(record) is not None)

# ---- _expose_target over preprocessor directives ------------------------
CASES = {
    "after #include": '#include "g1_display.h"\nstatic void f(unsigned int);\n'
                      'static void f(unsigned int a) { (void)a; }\n',
    "after #define": '#define VC(a) (*(volatile char *)(a))\n\n'
                     'static int f(int p){ return p; }\n',
    "after a continued #define": '#define X(a) \\\n    ((a) + 1)\n'
                                 'static int f(int p){ return X(p); }\n',
    "after a comment": '/* banner */\nstatic int f(int p){ return p; }\n',
    "after a }": 'int g(void){ return 0; }\nstatic int f(int p){ return p; }\n',
}
for label, text in CASES.items():
    out, count = mtcore._expose_target(text, "f")
    check("_expose_target de-staticises %s" % label,
          count >= 1 and "static" not in out.replace("static_", ""),
          "count=%d out=%r" % (count, out))

# `static` must still be required to OPEN the declaration: a real statement
# before it means this is not a declaration head and must not be rewritten.
out, count = mtcore._expose_target("int g(void){ return 0; } int h = 1; x static "
                                   "int f(int p){ return p; }\n", "f")
check("_expose_target does NOT rewrite when real code precedes `static`",
      count == 0)

check("_only_directives rejects a trailing statement",
      not mtcore._only_directives("\n#include <x.h>\nint y;\n"))
check("_only_directives rejects code on the `static` line",
      not mtcore._only_directives("\n#include <x.h>\nint z = 1; "))

# ---- out-parameter fill ------------------------------------------------
a = mtcore.outparam_bytes(3, 1)
check("outparam_bytes is deterministic", a == mtcore.outparam_bytes(3, 1))
check("outparam_bytes differs per call ordinal", a != mtcore.outparam_bytes(4, 1))
check("outparam_bytes differs per argument index", a != mtcore.outparam_bytes(3, 2))
check("outparam_bytes covers the whole window", len(a) >= mtcore.OUTPARAM_WINDOW)
word = mtcore.outparam_bytes(0, 0, 0x01020304)
check("outparam_bytes(word) repeats the word",
      word[:8] == bytes.fromhex("04030201" * 2))

# ---- unit-boundary flags -----------------------------------------------
check("-fno-ipa-vrp is in UNIT_BOUNDARY_CFLAGS",
      "-fno-ipa-vrp" in mtcore.UNIT_BOUNDARY_CFLAGS)

print()
if FAILURES:
    print("FAILED %d: %s" % (len(FAILURES), ", ".join(FAILURES)))
    sys.exit(1)
print("all guard self-tests pass at harness_rev=%s" % mtcore.harness_rev())
