#!/usr/bin/env python3
"""The PHASE-TOLERANT stream criterion, and its bound's derivation.

Full working: recon/analysis/phase_tolerant_criterion.md

The wall-anchored fields in the oracle (`peripherals/<bus>/phases/<phase>/
transaction_count` and `stream_sha256`) cut a stream at the 6 s phase boundary.
A periodic train that shifts in time therefore gains or loses a burst inside
the window, and every count and hash downstream of it moves with NO change to
what the firmware exchanged with the device.  Those fields are still published
and still compared strictly -- this tool ADDS a criterion that is anchored to
the train instead of to the wall.

WHAT IT STILL FAILS ON
    P1  a changed register, a changed write payload, a changed read length, a
        burst whose shape changed  -> the train key changes -> the train set
        differs -> FAIL(content)
    P2  a transaction or burst added to or dropped from the run, unless the
        observation wall clipped it and the train's own measured period
        predicts it back -> FAIL(population)
    P3  a train displaced in time by more than `--bound` -> FAIL(phase)
    P4  a changed period/cadence: gated THROUGH P3.  A per-period error e
        accumulates; after ceil(bound/e) bursts |delta| exceeds the bound.
        The per-train sensitivity is printed.
    P5  a reordering that is not a bounded phase shift: two bursts whose order
        swapped while being more than `--bound` apart -> FAIL(order)

WHAT IT DELIBERATELY STOPS FAILING ON
    a whole train moving in wall time by <= bound, and the burst-count changes
    at the observation wall that follow from it.

usage:
    phase_tolerant_compare.py derive-bound SHIPPED.json OURS.json [SHIPPED2 OURS2 ...]
    phase_tolerant_compare.py compare --bound-ms=N SHIPPED.json BASE.json STAGE.json [LABEL]
    phase_tolerant_compare.py pair    --bound-ms=N SHIPPED.json OURS.json  [LABEL]
"""
import json
import sys

WALL_NS = 20_000_000_000


# ---------------------------------------------------------------------------
def blocks(oracle):
    """(bus, device) -> train block, for every bus that carries one."""
    out = {}
    for bus, v in oracle.get("peripherals", {}).items():
        wrt = v.get("whole_run_trains")
        if not wrt:
            continue
        for dev, blk in (wrt.get("devices") or {}).items():
            if blk.get("transaction_count"):
                out[(bus, dev)] = blk
    return out


def trains_by_key(blk):
    return {t["key_sha256"]: t for t in blk["trains"]}


def measurable_mask(starts, deltas):
    """Per-index unambiguity: burst i's i-th-to-i-th match is unambiguous iff
    |delta_i| is less than half the LOCAL period around burst i in the shipped
    train.  Above that, burst i in one run is nearer to burst i+-1 of the other
    and the correspondence carries no information; below it, it is forced."""
    n = len(starts)
    mask = []
    for i in range(len(deltas)):
        gaps = []
        if i > 0:
            gaps.append(starts[i] - starts[i - 1])
        if i + 1 < n:
            gaps.append(starts[i + 1] - starts[i])
        local = min(gaps) if gaps else None
        mask.append(True if local is None else abs(deltas[i]) < local / 2.0)
    return mask


def measurable(train, deltas):
    """Whole-train form of the same test (used by the bound derivation)."""
    if len(deltas) < 2 or not train.get("period_ns"):
        return True
    return max(abs(d) for d in deltas) < train["period_ns"]["min"] / 2.0


def wall_explained(ts, to, bound_ns, wall_ns, period_ns):
    """A population difference is admissible only when the observation wall
    clipped the bursts, and the train's OWN measured period predicts them."""
    ns, no = len(ts), len(to)
    if ns == no:
        return True, ""
    if period_ns is None:
        return False, "population %d->%d and the train has no period" % (ns, no)
    p = period_ns["median"]
    if no > ns:
        for j in range(ns, no):
            predicted = ts[-1] + (j - (ns - 1)) * p
            if predicted <= wall_ns:
                return False, ("extra burst %d: shipped would have had one at "
                               "%.6f s, inside the wall" % (j, predicted / 1e9))
            if abs(to[j] - predicted) > bound_ns:
                return False, ("extra burst %d at %.6f s is %.3f ms from the "
                               "predicted %.6f s" % (j, to[j] / 1e9,
                                                     (to[j] - predicted) / 1e6,
                                                     predicted / 1e9))
        return True, "wall-clipped: %d extra burst(s) pulled inside %.3f s" % (no - ns, wall_ns / 1e9)
    for j in range(no, ns):
        if ts[j] <= wall_ns - bound_ns:
            return False, ("missing burst %d: shipped has one at %.6f s, more "
                           "than the bound inside the wall" % (j, ts[j] / 1e9))
    return True, "wall-clipped: %d burst(s) pushed past %.3f s" % (ns - no, wall_ns / 1e9)


def compare_block(ship, ours, bound_ns, wall_ns=WALL_NS):
    """Return a verdict dict for one (bus, device)."""
    ts, to = trains_by_key(ship), trains_by_key(ours)
    res = {"fails": [], "notes": [], "indeterminate": [], "max_abs_delta_ms": 0.0,
           "measurable_trains": 0, "total_trains": len(set(ts) | set(to))}
    only_ship = sorted(set(ts) - set(to))
    only_ours = sorted(set(to) - set(ts))

    # A shared bus can put two INDEPENDENT trains within burst_gap of each other
    # once one of them shifts in phase; the two bursts then segment as one and
    # a train appears that exists on neither side as a firmware programme.  That
    # is an artifact of the segmentation, not a content difference, so it gets
    # its own category rather than being counted as P1.
    #
    # The SPLIT direction is the same artifact seen from the other side: under a
    # TIGHTER gap the two halves of one shipped burst drift more than the
    # threshold apart in our run and segment as two.  The shipped train then has
    # the long key and ours has its prefix.  Iteration 46 section 46.9.1 measured
    # this on `twim1 npm1300` and it was charged as `P1 content` because this
    # tool had a category for the merge direction only.  It now has both.  Like
    # the merge test this is a prefix heuristic on `key_head` (96 chars), and
    # like the merge direction it is still REPORTED AS A FAILURE -- naming it
    # does not make it pass.
    def _prefixed_by_another(entry, key):
        head = entry["key_head"]
        for a in list(ts.values()) + list(to.values()):
            ha = a["key_head"]
            if a["key_sha256"] != key and len(ha) < len(head) and head.startswith(ha + "|"):
                return True
        return False

    def _prefixes_another(entry, key):
        head = entry["key_head"]
        for a in list(ts.values()) + list(to.values()):
            ha = a["key_head"]
            if a["key_sha256"] != key and len(ha) > len(head) and ha.startswith(head + "|"):
                return True
        return False

    merges = {k for k in only_ours if _prefixed_by_another(to[k], k)}
    splits = {k for k in only_ship if _prefixed_by_another(ts[k], k)}
    # the two HALVES a split produces on our side: each is a strict prefix of the
    # shipped train it came out of.  Same artifact, same category, still a FAIL.
    halves = {k for k in only_ours if _prefixes_another(to[k], k)}
    for k in only_ship:
        cat = ("P0 segmentation: a shipped train is absent from ours and its key "
               "BEGINS with another train's key -- one burst split in two under "
               "burst_gap_ns"
               if k in splits else "P1 content: shipped train absent from ours")
        res["fails"].append("%s (n=%d) %s"
                            % (cat, ts[k]["count"], ts[k]["key_head"][:60]))
    for k in only_ours:
        if k in merges:
            cat = ("P0 segmentation: a train appears only in ours and its key "
                   "BEGINS with another train's key -- two bursts on this shared "
                   "bus merged under burst_gap_ns")
        elif k in halves:
            cat = ("P0 segmentation: a train appears only in ours and another "
                   "train's key BEGINS with it -- one burst split in two under "
                   "burst_gap_ns")
        else:
            cat = "P1 content: train present only in ours"
        res["fails"].append("%s (n=%d) %s" % (cat, to[k]["count"], to[k]["key_head"][:60]))

    pairs = []           # (t_ship, t_ours) for the order gate
    for k in sorted(set(ts) & set(to)):
        a, b = ts[k], to[k]
        if a["burst_transactions"] != b["burst_transactions"]:
            res["fails"].append("P1 content: burst length %d -> %d on %s"
                                % (a["burst_transactions"], b["burst_transactions"],
                                   a["key_head"][:40]))
            continue
        sa, sb = a["starts_ns"], b["starts_ns"]
        ok, why = wall_explained(sa, sb, bound_ns, wall_ns, a.get("period_ns"))
        if not ok:
            res["fails"].append("P2 population %d -> %d on %s: %s"
                                % (len(sa), len(sb), a["key_head"][:40], why))
            continue
        if len(sa) != len(sb):
            res["notes"].append("P2 %s: %s" % (a["key_head"][:40], why))
        m = min(len(sa), len(sb))
        deltas = [sb[i] - sa[i] for i in range(m)]
        pairs.extend((sa[i], sb[i]) for i in range(m))
        if not deltas:
            continue
        mask = measurable_mask(sa, deltas)
        meas = [d for d, ok in zip(deltas, mask) if ok]
        ambi = [d for d, ok in zip(deltas, mask) if not ok]
        if meas:
            res["measurable_trains"] += 1
            mx = max(abs(d) for d in meas)
            res["max_abs_delta_ms"] = max(res["max_abs_delta_ms"], mx / 1e6)
            if mx > bound_ns:
                res["fails"].append(
                    "P3 phase: |delta| %.3f ms > bound on %d/%d bursts of the "
                    "n=%d train %s"
                    % (mx / 1e6, sum(1 for d in meas if abs(d) > bound_ns),
                       len(sa), len(sa), a["key_head"][:40]))
        if ambi:
            res["indeterminate"].append(
                "n=%d train: %d of %d bursts have |delta| above half the local "
                "period (max %.3f ms) -- their phase is NOT measured; content "
                "and population still gated -- %s"
                % (len(sa), len(ambi), len(deltas),
                   max(abs(d) for d in ambi) / 1e6, a["key_head"][:40]))

    # ---- P5 order: an inversion is admissible only inside the bound --------
    pairs.sort()
    worst = 0
    for i in range(len(pairs)):
        si, oi = pairs[i]
        for j in range(i + 1, len(pairs)):
            sj, oj = pairs[j]
            if sj - si > bound_ns and oj < oi:
                worst = max(worst, sj - si)
    if worst:
        res["fails"].append("P5 order: two bursts %.3f ms apart in the shipped "
                            "run swapped order" % (worst / 1e6))
    res["worst_admissible_inversion_ms"] = worst / 1e6
    res["verdict"] = "FAIL" if res["fails"] else (
        "PASS/INDETERMINATE-PHASE" if res["indeterminate"] else "PASS")
    # a compact, comparable profile of HOW it failed, so "pre-existing" can be
    # separated from "pre-existing AND WORSE"
    prof = {}
    for f in res["fails"]:
        cat = " ".join(f.split()[:2]).rstrip(":")
        prof[cat] = prof.get(cat, 0) + 1
    res["fail_profile"] = prof
    return res


def worse_than(base, stage):
    """Did the stage add failures the base does not have?  Counted by CATEGORY
    (P1/P2/P3/P5), never by a raw millisecond difference -- a stream can move a
    few hundred microseconds without that meaning anything."""
    why = []
    for k, n in sorted(stage["fail_profile"].items()):
        b = base["fail_profile"].get(k, 0)
        if n > b:
            why.append("%s %d -> %d" % (k, b, n))
    return why


# ---------------------------------------------------------------------------
def cmd_derive(argv):
    """max |delta| over PHASE-MEASURABLE trains, per pair of oracles."""
    print("=== phase-bound derivation ===")
    print("Each pair is (reference, accepted-equivalent build).  Only trains "
          "whose i-th-to-i-th\ncorrespondence is unambiguous (max|d| < "
          "min(period)/2) contribute.\n")
    overall = 0.0
    for i in range(0, len(argv) - 1, 2):
        ship = json.load(open(argv[i]))
        ours = json.load(open(argv[i + 1]))
        bs, bo = blocks(ship), blocks(ours)
        pairmax, rows = 0.0, []
        for key in sorted(set(bs) & set(bo)):
            tsd, tod = trains_by_key(bs[key]), trains_by_key(bo[key])
            devmax, devwho = 0.0, ""
            nmeas = nambig = 0
            for k in sorted(set(tsd) & set(tod)):
                a, b = tsd[k], tod[k]
                m = min(len(a["starts_ns"]), len(b["starts_ns"]))
                d = [b["starts_ns"][x] - a["starts_ns"][x] for x in range(m)]
                if not d:
                    continue
                mx = max(abs(v) for v in d)
                if measurable(a, d):
                    nmeas += 1
                    if mx / 1e6 > devmax:
                        devmax, devwho = mx / 1e6, "n=%d %s" % (len(a["starts_ns"]),
                                                                a["key_head"][:34])
                else:
                    nambig += 1
            rows.append((key, devmax, nmeas, nambig, devwho))
            pairmax = max(pairmax, devmax)
        print("-- %s  vs  %s" % (argv[i], argv[i + 1]))
        for key, devmax, nmeas, nambig, who in rows:
            print("   %-8s %-28s measurable=%-3d ambiguous=%-3d  max|d| = %8.3f ms   %s"
                  % (key[0], key[1], nmeas, nambig, devmax, who))
        print("   PAIR MAX |delta| over measurable trains: %.3f ms\n" % pairmax)
        overall = max(overall, pairmax)
    print("DERIVED PHASE BOUND (max over every pair): %.3f ms" % overall)


def _print_pair(label, res):
    print("   %-8s %-28s %-24s max|d|=%8.3f ms  measurable=%d/%d"
          % (label[0], label[1], res["verdict"], res["max_abs_delta_ms"],
             res["measurable_trains"], res["total_trains"]))
    for f in res["fails"]:
        print("        FAIL  %s" % f)
    for n in res["notes"]:
        print("        note  %s" % n)
    for n in res["indeterminate"]:
        print("        ????  %s" % n)


def cmd_pair(argv, bound_ns):
    ship, ours = json.load(open(argv[0])), json.load(open(argv[1]))
    label = argv[2] if len(argv) > 2 else "OURS"
    bs, bo = blocks(ship), blocks(ours)
    print("=== phase-tolerant criterion: shipped vs %s, bound %.3f ms ==="
          % (label, bound_ns / 1e6))
    bad = 0
    for key in sorted(set(bs) | set(bo)):
        if key not in bs or key not in bo:
            print("   %-8s %-28s MISSING on one side" % key)
            bad += 1
            continue
        r = compare_block(bs[key], bo[key], bound_ns)
        _print_pair(key, r)
        bad += bool(r["fails"])
    print("streams failing: %d" % bad)
    return bad


def cmd_compare(argv, bound_ns):
    ship = json.load(open(argv[0]))
    base = json.load(open(argv[1]))
    stage = json.load(open(argv[2]))
    label = argv[3] if len(argv) > 3 else "STAGE"
    bs, bb, bt = blocks(ship), blocks(base), blocks(stage)
    print("=== phase-tolerant three-way, bound %.3f ms : shipped | base | %s ==="
          % (bound_ns / 1e6, label))
    order = ("BOTH_PASS", "PRE_EXISTING_SAME", "PRE_EXISTING_WORSE",
             "REGRESSION", "IMPROVED")
    buckets = {k: [] for k in order}
    detail = {}
    for key in sorted(set(bs) & set(bb) & set(bt)):
        rb = compare_block(bs[key], bb[key], bound_ns)
        rt = compare_block(bs[key], bt[key], bound_ns)
        why = worse_than(rb, rt)
        detail[key] = (rb, rt, why)
        pb, pt = not rb["fails"], not rt["fails"]
        if pb and pt:
            buckets["BOTH_PASS"].append(key)
        elif not pb and not pt:
            buckets["PRE_EXISTING_WORSE" if why else "PRE_EXISTING_SAME"].append(key)
        elif pb and not pt:
            buckets["REGRESSION"].append(key)
        else:
            buckets["IMPROVED"].append(key)
    for name in order:
        print("\n-- %s : %d" % (name, len(buckets[name])))
        for key in buckets[name]:
            rb, rt, why = detail[key]
            print("   %-8s %-28s base=%-24s %s=%s" % (key[0], key[1],
                                                      rb["verdict"], label, rt["verdict"]))
            print("        base max|d| %8.3f ms  profile %s" %
                  (rb["max_abs_delta_ms"], rb["fail_profile"] or "{}"))
            print("        %-4s max|d| %8.3f ms  profile %s" %
                  (label, rt["max_abs_delta_ms"], rt["fail_profile"] or "{}"))
            if why:
                print("        WORSE THAN BASE: %s" % "; ".join(why))
            for f in rt["fails"][:6]:
                print("        %s FAIL  %s" % (label, f))
            if len(rt["fails"]) > 6:
                print("        %s FAIL  ... %d more" % (label, len(rt["fails"]) - 6))
            for n in rt["indeterminate"]:
                print("        %s ????  %s" % (label, n))
    bad = len(buckets["REGRESSION"]) + len(buckets["PRE_EXISTING_WORSE"])
    print("\nREFACTOR REGRESSIONS: %d   PRE-EXISTING-BUT-WORSE: %d"
          % (len(buckets["REGRESSION"]), len(buckets["PRE_EXISTING_WORSE"])))
    return bad


def main():
    argv = sys.argv[1:]
    if not argv:
        sys.exit(__doc__)
    bound_ns = None
    rest = []
    for a in argv:
        if a.startswith("--bound-ms="):
            bound_ns = int(round(float(a.split("=", 1)[1]) * 1e6))
        else:
            rest.append(a)
    cmd, rest = rest[0], rest[1:]
    if cmd == "derive-bound":
        cmd_derive(rest)
        return 0
    if bound_ns is None:
        sys.exit("--bound-ms=N is required for '%s'" % cmd)
    if cmd == "pair":
        return 1 if cmd_pair(rest, bound_ns) else 0
    if cmd == "compare":
        return 1 if cmd_compare(rest, bound_ns) else 0
    sys.exit("unknown command %r" % cmd)


if __name__ == "__main__":
    sys.exit(main())
