#!/usr/bin/env python3
"""Measured improvements to the phase-tolerant criterion, kept OUT of the
emulator scripts on purpose.

`recon/emulator/scripts/phase_tolerant_compare.py` and
`build_display_sensor_oracle.py` are owned by the concurrent parity agent.  This
module holds the parts of the criterion this pass measured and, where the
evidence supports it, the parts it ADOPTS -- so that the numbers in
`recon/analysis/refactor_consolidated_verdict.md` can be recomputed from any
pair of oracle JSONs without editing another agent's tool.

Full working and every number: `recon/analysis/refactor_consolidated_verdict.md`
sections 5, 6 and 7.

--------------------------------------------------------------------------
1.  RADIO_TX COMPONENTS -- ADOPTED
--------------------------------------------------------------------------

`our_boot_bringup.md` 44.4 proved from four instrumented Renode captures that

    RADIO_TX  ==  ESB_MASTER_FRAMES  +  BLE_link_layer_TX      exactly

because the G1 shares one net-core RADIO between the ESB L<->R sync and the BLE
peripheral link.  It then declined to publish the missing component "because it
changes the oracle's field set".

It does not have to.  Both terms of the sum are ALREADY oracle fields, so the
component is arithmetic:

    BLE_link_TX  :=  RADIO_TX - ESB_MASTER_FRAMES

and gating the two components separately is strictly harder than gating the sum.
It has to be, and the reason is the whole point: on the in-tree base the sum
reads 0x232 == shipped while BOTH components are wrong by one in OPPOSITE
directions (374+188 against 373+189).  Every record since iteration 43.11
carried `RADIO_TX 0x232` as a criterion our build MEETS.  It never did.

A gate on a derived aggregate is a gate that can pass for the wrong reason.

--------------------------------------------------------------------------
2.  THE EQUAL-POPULATION AMBIGUITY RULE -- implemented, NOT adopted alone
--------------------------------------------------------------------------

The shipped rule excludes burst i from the phase gate when |delta_i| exceeds
half the local period, on the ground that the i-to-i correspondence is then
ambiguous.  `our_boot_bringup.md` 44.7.1 observes that with EQUAL burst
populations `starts_ns` is sorted on both sides, so i<->i is the unique
ORDER-PRESERVING bijection and there is nothing to be ambiguous with -- and
concludes the exclusion can be dropped "at zero cost".

Measured here: at the SHIPPED 5 ms burst gap that change moves the derived bound
from **145.440 ms to 7,498.630 ms**, because the 44.3.1 train-membership swap on
`twim1 npm1300` moves a burst between two trains while BOTH keep their
populations (9 and 6).  The correspondence really is unique; it is the TRAIN
ASSIGNMENT that is wrong.

At a burst gap in the 0.700-2.300 ms band the same change re-derives the bound
to 145.440 ms unchanged and closes the exclusion hole completely.  The two
changes are COUPLED, so this one is implemented and gated behind an explicit
argument rather than switched on.
"""
from __future__ import annotations

import json
import sys


# ---------------------------------------------------------------------------
# 1. RADIO_TX components
# ---------------------------------------------------------------------------
def _counter(oracle: dict, name: str) -> int | None:
    """Read a hex-string counter out of an oracle, tolerating its width.

    The oracle spells these as `"0x0000000000000232"` and `"0x00000175"` -- the
    same value at two widths -- so the parse must not key on length.
    """
    raw = (oracle.get("counters") or {}).get(name)
    if raw is None:
        return None
    if isinstance(raw, int):
        return raw
    try:
        return int(str(raw), 16)
    except ValueError:
        return None


def radio_tx_components(oracle: dict) -> dict:
    """Split `counters/RADIO_TX` into its two independent subsystems.

    Returns `{"RADIO_TX", "ESB_MASTER_FRAMES", "BLE_link_TX"}`, or a dict with
    `"available": False` when either term is missing -- never a guess.
    """
    total = _counter(oracle, "RADIO_TX")
    esb = _counter(oracle, "ESB_MASTER_FRAMES")
    if total is None or esb is None:
        return {"available": False,
                "why": "RADIO_TX=%r ESB_MASTER_FRAMES=%r" % (total, esb)}
    return {"available": True, "RADIO_TX": total,
            "ESB_MASTER_FRAMES": esb, "BLE_link_TX": total - esb}


def compare_radio_tx(shipped: dict, ours: dict) -> dict:
    """Per-component verdict against the shipped reference."""
    s, o = radio_tx_components(shipped), radio_tx_components(ours)
    if not (s["available"] and o["available"]):
        return {"verdict": "NOT_MEASURED", "shipped": s, "ours": o}
    out = {"shipped": s, "ours": o, "fields": {}}
    for k in ("ESB_MASTER_FRAMES", "BLE_link_TX"):
        out["fields"][k] = {"shipped": s[k], "ours": o[k], "delta": o[k] - s[k],
                            "verdict": "EQ" if o[k] == s[k] else "NE"}
    out["sum_verdict"] = "EQ" if s["RADIO_TX"] == o["RADIO_TX"] else "NE"
    out["verdict"] = ("EQ" if all(f["verdict"] == "EQ" for f in out["fields"].values())
                      else "NE")
    # the finding that motivates the whole field: the SUM can agree while both
    # components disagree, in opposite directions.
    out["cancellation"] = (out["sum_verdict"] == "EQ" and out["verdict"] == "NE")
    return out


# ---------------------------------------------------------------------------
# 2. the equal-population ambiguity rule
# ---------------------------------------------------------------------------
def measurable_mask(starts: list[int], deltas: list[int],
                    equal_population: bool = False,
                    equal_population_rule: bool = False) -> list[bool]:
    """Per-burst phase-measurability.

    With `equal_population_rule` and equal populations the exclusion is dropped:
    `starts_ns` is sorted on both sides, so i<->i is the unique order-preserving
    bijection and P5 already fails any run whose order changed.  With UNEQUAL
    populations the common-prefix pairing is a genuine choice, so the exclusion
    is retained -- that half is not optional, and dropping it is what moves the
    bound to 7,498.630 ms (see the module docstring).
    """
    if equal_population_rule and equal_population:
        return [True] * len(deltas)
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


# ---------------------------------------------------------------------------
def main(argv: list[str]) -> int:
    if len(argv) < 2:
        sys.exit("usage: criterion_probe.py radio-tx SHIPPED.json OURS.json [OURS2.json ...]")
    if argv[0] != "radio-tx":
        sys.exit("unknown command %r" % argv[0])
    shipped = json.load(open(argv[1]))
    print("%-46s %9s %9s %9s  %s" % ("oracle", "RADIO_TX", "ESB", "BLE", "verdict"))
    s = radio_tx_components(shipped)
    print("%-46s %9d %9d %9d  (shipped reference)"
          % (argv[1][-46:], s["RADIO_TX"], s["ESB_MASTER_FRAMES"], s["BLE_link_TX"]))
    bad = 0
    for p in argv[2:]:
        r = compare_radio_tx(shipped, json.load(open(p)))
        o = r["ours"]
        note = "  <- CANCELLATION: sum EQ, both components NE" if r.get("cancellation") else ""
        print("%-46s %9d %9d %9d  %s%s"
              % (p[-46:], o["RADIO_TX"], o["ESB_MASTER_FRAMES"], o["BLE_link_TX"],
                 r["verdict"], note))
        bad += r["verdict"] != "EQ"
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
