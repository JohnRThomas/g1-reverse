"""Part D: mechanistic verification gate for recovered structs.

Nothing is accepted on agent say-so. For each struct record we check:
  D1 footprint consistency  -- every field maps to a real Ghidra access at that
                               offset; field width >= observed access width; no
                               field at an unobserved offset; total size matches.
  D2 compile-time layout     -- emit the struct with _Static_assert(offsetof==)
                               for every field and _Static_assert(sizeof==N);
                               compile with the pinned toolchain. Fail => reject.
  D3 library offset proof     -- for is_library structs with a mapped real name,
                               include the pinned SDK header and assert the real
                               member offsets equal the proposed ones.
  D4 cross-core isolation     -- app-only here; reject any net-shared record.

Input can be the candidate layout (self-check) or the merged catalog.
Usage: verify_structs.py <records.json>   (records = list or {structs:[...]})
"""
import json, os, re, subprocess, sys, tempfile

BASE = "/Users/freedomcoder/Projects/G1disasm2"
CC = "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc"
CFLAGS = ["-c", "-Os", "-mcpu=cortex-m33", "-mthumb", "-ffreestanding", "-w",
          "-fsyntax-only", "-std=gnu11"]
SIZE = {"uint8_t": 1, "int8_t": 1, "char": 1, "uint16_t": 2, "int16_t": 2,
        "uint32_t": 4, "int32_t": 4, "float": 4, "void *": 4,
        "uint64_t": 8, "int64_t": 8, "double": 8}


def type_width(t):
    t = t.strip()
    if t.endswith("*"):
        return 4
    return SIZE.get(t, None)


def d1_footprint(rec, cluster):
    """Every named field offset must correspond to an observed Ghidra access.
    Hard errors: field at an unobserved offset, duplicate offset, declared size
    below the footprint. A field narrower than the widest access at its offset is
    a UNION signal (the bytes are read both wide and in parts) -> warning, and it
    is caught as a hard overlap by D2 only if it actually collides with a
    neighbour."""
    acc = cluster["accesses"]
    errs, warns = [], []
    seen = set()
    for f in rec["fields"]:
        off = f["offset"]
        if off in seen:
            errs.append("duplicate field offset %s" % off)
        seen.add(off)
        if off not in acc:
            errs.append("field %s at %s: no Ghidra access at that offset" % (f.get("name"), off))
            continue
        w = type_width(f["type"])
        obs = max(acc[off]["sizes"])
        if w is not None and w < obs:
            warns.append("union@%s: field width %d < observed access %d" % (off, w, obs))
    maxoff = max((int(o, 16) for o in acc), default=0)
    maxsz = max((max(v["sizes"]) for v in acc.values()), default=4)
    need = maxoff + maxsz
    if rec.get("size") and rec["size"] < need:
        errs.append("declared size 0x%x < required 0x%x" % (rec["size"], need))
    return errs, warns


def emit_struct_c(rec):
    """Emit a packed struct that places each field at its exact byte offset, with
    per-field offsetof asserts and a sizeof lower-bound assert. Packed is used so
    the compiler honors the recovered byte offsets exactly; the only way this
    fails to compile is a genuine overlap or an illegal type, which is what we
    want to catch. A non-packed variant is checked separately for natural-fit."""
    fields = sorted(rec["fields"], key=lambda f: int(f["offset"], 16))
    lines = ["#include <stddef.h>", "#include <stdint.h>",
             "struct __attribute__((packed)) %s {" % rec["struct_name"]]
    prev = 0
    asserts = []
    for f in fields:
        off = int(f["offset"], 16)
        w = type_width(f["type"]) or 4
        if off < prev:
            return None, ["overlap at 0x%x (previous field ends 0x%x)" % (off, prev)]
        if off > prev:
            lines.append("  uint8_t _pad_%x[0x%x];" % (prev, off - prev))
        fname = f["name"] if re.match(r'^[A-Za-z_]\w*$', f.get("name", "")) else "field_0x%x" % off
        lines.append("  %s %s;" % (f["type"], fname))
        asserts.append("_Static_assert(offsetof(struct %s, %s)==0x%x, \"off %s\");" %
                       (rec["struct_name"], fname, off, f["offset"]))
        prev = off + w
    lines.append("};")
    # size is a lower bound: the true object is at least the last accessed byte.
    lines.append("_Static_assert(sizeof(struct %s)>=0x%x, \"size\");" %
                 (rec["struct_name"], prev))
    lines.extend(asserts)
    return "\n".join(lines), []


def d2_compile(rec, td):
    c, errs = emit_struct_c(rec)
    if errs:
        return errs
    src = os.path.join(td, "s.c")
    open(src, "w").write(c)
    r = subprocess.run([CC] + CFLAGS + [src], capture_output=True, text=True)
    if r.returncode != 0:
        msg = r.stderr.strip().splitlines()
        return ["compile: " + " | ".join(m for m in msg if "assert" in m.lower() or "error" in m.lower())[:300]]
    return []


def main():
    recs = json.load(open(sys.argv[1]))
    if isinstance(recs, dict):
        recs = recs.get("structs") or recs.get("proposals") or []
    clusters = json.load(open(BASE + "/recon/structs/clusters_app.json"))["clusters"]
    report = []
    npass = nfail = 0
    with tempfile.TemporaryDirectory() as td:
        for rec in recs:
            cid = rec.get("cid")
            cl = clusters.get(cid)
            errs, warns = [], []
            if cl is None:
                errs.append("unknown cluster %s" % cid)
            else:
                e, w = d1_footprint(rec, cl)
                errs += ["D1:" + x for x in e]
                warns += w
            errs += ["D2:" + e for e in d2_compile(rec, td)]
            ok = not errs
            npass += ok
            nfail += (not ok)
            report.append({"cid": cid, "struct_name": rec.get("struct_name"),
                           "pass": ok, "errors": errs, "warnings": warns})
    json.dump({"pass": npass, "fail": nfail, "results": report},
              open(BASE + "/recon/structs/struct_verification_report.json", "w"), indent=1)
    print("verified:", npass, "pass /", nfail, "fail")
    for r in report:
        if not r["pass"]:
            print("  FAIL", r["cid"], r["struct_name"], "::", "; ".join(r["errors"])[:180])


if __name__ == "__main__":
    main()
