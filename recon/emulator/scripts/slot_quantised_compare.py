#!/usr/bin/env python3
"""The SLOT-QUANTISED phase gate — a bound that does not depend on our own
build's error.

Full working, every constant's derivation, and what it stops catching:
`recon/analysis/criterion_bound_redesign.md`.

WHY THIS EXISTS
    The published phase-tolerant criterion derives its bound as

        Delta = max |delta| over phase-measurable trains, shipped vs OUR OWN
                in-tree base, over both stimuli

    which has three measured defects:

    A   it is a function of our own error, so a firmware REPAIR loosens it
        (iteration 45's repair moved Delta 145.440 -> 262.200 ms);
    B   it is flippable by 204 bytes of unreferenced, `retain`-kept .rodata that
        move zero .text addresses (iteration 46 sections 46.9 / 46.10);
    C   `max|delta|` is not a displacement.  On `spim_a` navigation the per-burst
        delta distribution is ~154 ms wide AT ZERO slot offset, so the statistic
        the bound was derived from is dominated by within-train spread.

    And, measured in this pass: applying the published derivation rule to a pair
    that contains no build of ours at all -- the SHIPPED firmware against ITSELF
    at a different emulator seed -- reproduces Delta to within 3 % (141.170 ms
    against 145.440 ms).  The published bound was the stimulus noise floor.

THE RULE
    Per stream (bus, device), over the trains common to both oracles, using the
    existing decomposition in phase_tolerant_compare (no second segmentation
    rule is introduced):

        D = median(delta)                   the DISPLACEMENT   (not the maximum)
        S = P95(delta) - P5(delta)          the SPREAD
        k = round(D / W)                    the integer slot index
        r = D - k*W                         the SUB-SLOT RESIDUAL

    W is the DUT BLE connection-event response slot width -- a property of the
    stimulus and the emulated link, not of any firmware.

    Q1  |r| <= R          on every gated stream          <- THE GATE
    Q2  k is REPORTED, never gated
    Q3  S <= Sigma[device]                               <- shape
    Q4  P1 content / P2 population / P5 order            <- unchanged, in
                                                            phase_tolerant_compare.py

    The refactor gate is computed on the DIRECT base->stage pairing, because
    median(X - Z) is not median(X - Y) - median(Y - Z) on the wide, bimodal
    distributions these streams carry (measured: `st25dv_nfc` moves 5.68 ms by
    that arithmetic and 0.06 ms when paired directly).

    Against SHIPPED the same quantities are published as context.  `k` differing
    between base and stage is reported as `SLOT MOVED`, which marks every
    slot-sensitive strict field (the p1_boot counts and hashes, RADIO_TX's BLE
    component, JBD_FRAMECOUNTER) as slot-attributable rather than a regression.

CONSTANTS -- and where they may NOT come from
    Forbidden: "how far our build sits from shipped".  Every default below is
    measured, and `constants` re-derives all of them from captures on disk.

usage:
    slot_quantised_compare.py gate  [--w-ms=] [--r-ms=] [--r-seed-ms=]
                                    BASE.json STAGE.json [SHIPPED.json] [LABEL]
    slot_quantised_compare.py pair  [--w-ms=] A.json B.json [LABEL]
"""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import phase_tolerant_compare as ptc          # noqa: E402

#: Slot width.  Measured in this pass from five CLEAN one-slot hops between our
#: own images -- clean meaning both slot-locked devices (`spim_a jbd_display`
#: and `twim1 opt3001`) move by 90..110 ms and agree with each other within
#: 1 ms.  Ten measurements, mean 100.513 ms, full range 99.950 .. 101.010 ms.
#: The images are only probes here: W is a property of the link, and the same
#: value falls out of hops between images that share no source change.
SLOT_MS = 100.513

#: The gate.  R = max(R_slot, R_pad), both measured, NEITHER from our error:
#:   R_slot = 0.563 ms  the largest deviation of an observed one-slot hop from W
#:                      -- the lattice's own width is not constant, so a residual
#:                      below this is indistinguishable from "exactly one slot";
#:   R_pad  = 1.160 ms  the largest |r| produced by adding 204 bytes of
#:                      unreferenced, unexecutable, `retain`-kept .rodata to a
#:                      build (0 .text addresses moved), over four image pairs
#:                      and both stimuli.  The criterion MUST be insensitive to
#:                      at least this, or it is flippable by inert bytes.
BOUND_MS = 1.160

#: NOT a gate.  The largest |r| the SHIPPED firmware produces against ITSELF
#: when only the emulator seed changes (four seeds, both stimuli).  A Q1 failure
#: below this is real at a fixed seed but is NOT reproducible as a claim about
#: the firmware across stimulus realisations, and is labelled so.
SEED_NOISE_MS = 50.110

#: Q3 ceilings, per device, from the shipped-vs-shipped seed pairs only.
#: Published, and honestly: at these values Q3 catches nothing in the current
#: ladder (criterion_bound_redesign.md section 5.3).
SIGMA_MS = {
    ("spim_a", "jbd_display"): 68.240,
    ("twim1", "npm1300_charger_fuelgauge"): 1069.469,
    ("twim1", "opt3001_ambient_light"): 37.387,
    ("twim1", "st25dv_nfc_eeprom"): 76.299,
    ("twim1", "st25dv_system_port"): 76.260,
    ("twim2", "lsm6dso_imu"): 34.393,
}


def pct(v, p):
    s = sorted(v)
    if not s:
        return 0.0
    if len(s) == 1:
        return s[0]
    i = p / 100.0 * (len(s) - 1)
    lo = int(i)
    hi = min(lo + 1, len(s) - 1)
    return s[lo] + (s[hi] - s[lo]) * (i - lo)


def deltas_by_device(A, B):
    """(bus, dev) -> per-burst delta in ms over the trains common to both."""
    ba, bb = ptc.blocks(A), ptc.blocks(B)
    out = {}
    for key in sorted(set(ba) & set(bb)):
        ta, tb = ptc.trains_by_key(ba[key]), ptc.trains_by_key(bb[key])
        d = []
        for k in sorted(set(ta) & set(tb)):
            sa, sb = ta[k]["starts_ns"], tb[k]["starts_ns"]
            m = min(len(sa), len(sb))
            d.extend((sb[i] - sa[i]) / 1e6 for i in range(m))
        if d:
            out[key] = d
    return out


def stats(d, slot=SLOT_MS):
    D = pct(d, 50)
    k = int(round(D / slot))
    return {"n": len(d), "D_ms": D, "S_ms": pct(d, 95) - pct(d, 5),
            "min_ms": min(d), "max_ms": max(d), "k": k, "slots": D / slot,
            "r_ms": D - k * slot, "max_abs_delta_ms": max(abs(x) for x in d)}


HDR = ("%-38s %5s %10s %6s %9s %10s %10s"
       % ("bus/device", "n", "D med ms", "k", "r ms", "S p95-p5", "max|d|"))


def _row(name, s):
    return ("%-38s %5d %10.3f %6d %9.3f %10.3f %10.3f"
            % (name, s["n"], s["D_ms"], s["k"], s["r_ms"], s["S_ms"],
               s["max_abs_delta_ms"]))


def cmd_pair(argv, slot):
    A, B = json.load(open(argv[0])), json.load(open(argv[1]))
    label = argv[2] if len(argv) > 2 else "B"
    print("=== slot-quantised statistics  (%s - A)   W = %.3f ms" % (label, slot))
    print(HDR)
    for key, d in deltas_by_device(A, B).items():
        print(_row("%s/%s" % key, stats(d, slot)))
    return 0


def cmd_gate(argv, slot, bound, seed_noise):
    base = json.load(open(argv[0]))
    stage = json.load(open(argv[1]))
    ship = json.load(open(argv[2])) if len(argv) > 2 and argv[2].endswith(".json") else None
    label = argv[-1] if not argv[-1].endswith(".json") else "STAGE"

    print("=== SLOT-QUANTISED GATE : base | %s" % label)
    print("    W = %.3f ms   R = %.3f ms   (seed-noise annotation floor %.3f ms)"
          % (slot, bound, seed_noise))
    print("\n-- Q1/Q3, the refactor gate: DIRECT base -> %s pairing" % label)
    print(HDR + "   verdict")
    direct = deltas_by_device(base, stage)
    fails, notes = [], []
    for key, d in direct.items():
        s = stats(d, slot)
        v = "PASS"
        if abs(s["r_ms"]) > bound:
            v = "FAIL Q1"
            if abs(s["r_ms"]) < seed_noise:
                v += " (BELOW-STIMULUS-NOISE)"
            fails.append((key, "Q1", s))
        sig = SIGMA_MS.get(key)
        if sig is not None and s["S_ms"] > sig:
            v += " FAIL Q3"
            fails.append((key, "Q3", s))
        if s["k"] and not v.startswith("FAIL Q1"):
            notes.append("%s/%s moved %+d slot(s) relative to the base"
                         % (key[0], key[1], s["k"]))
        elif s["k"]:
            notes.append("%s/%s: k = %+d is NOT MEANINGFUL -- D = %.3f ms is "
                         "%.3f slots, which the lattice does not explain"
                         % (key[0], key[1], s["k"], s["D_ms"], s["slots"]))
        print(_row("%s/%s" % key, s) + "   " + v)

    if ship is not None:
        print("\n-- context vs SHIPPED (published, NOT gated: this is the "
              "pre-existing structural offset)")
        print("%-38s %10s %6s %9s | %10s %6s %9s"
              % ("bus/device", "base D", "k", "base r", "%s D" % label[:8], "k", "r"))
        db, ds = deltas_by_device(ship, base), deltas_by_device(ship, stage)
        for key in sorted(set(db) & set(ds)):
            sb, ss = stats(db[key], slot), stats(ds[key], slot)
            flag = "   <== SLOT MOVED" if sb["k"] != ss["k"] else ""
            print("%-38s %10.3f %6d %9.3f | %10.3f %6d %9.3f%s"
                  % ("%s/%s" % key, sb["D_ms"], sb["k"], sb["r_ms"],
                     ss["D_ms"], ss["k"], ss["r_ms"], flag))
            if sb["k"] != ss["k"]:
                notes.append(
                    "%s/%s: k %+d -> %+d vs shipped. Every SLOT-SENSITIVE strict "
                    "field on this bus (p1_boot transaction_count and "
                    "stream_sha256, RADIO_TX's BLE component, JBD_FRAMECOUNTER) "
                    "is slot-attributable and is NOT evidence of a regression "
                    "or an improvement." % (key[0], key[1], sb["k"], ss["k"]))

    for n in notes:
        print("    note  %s" % n)
    print("\nQ1/Q3 FAILURES: %d" % len(fails))
    for key, q, s in fails:
        print("    %-8s %-28s %s  |r| = %.3f ms  (D = %.3f = %.3f slots)"
              % (key[0], key[1], q, abs(s["r_ms"]), s["D_ms"], s["slots"]))
    return 1 if fails else 0


def main():
    argv, slot, bound, seed = sys.argv[1:], SLOT_MS, BOUND_MS, SEED_NOISE_MS
    rest = []
    for a in argv:
        if a.startswith("--w-ms="):
            slot = float(a.split("=", 1)[1])
        elif a.startswith("--r-ms="):
            bound = float(a.split("=", 1)[1])
        elif a.startswith("--r-seed-ms="):
            seed = float(a.split("=", 1)[1])
        else:
            rest.append(a)
    if not rest:
        sys.exit(__doc__)
    cmd, rest = rest[0], rest[1:]
    if cmd == "pair":
        return cmd_pair(rest, slot)
    if cmd == "gate":
        return cmd_gate(rest, slot, bound, seed)
    sys.exit("unknown command %r" % cmd)


if __name__ == "__main__":
    sys.exit(main())
