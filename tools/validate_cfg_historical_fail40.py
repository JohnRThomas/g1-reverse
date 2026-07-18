#!/usr/bin/env python3
"""Validate the current-source closure of historical CFG discovery failures."""

import hashlib
import json
import os
import sys


BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HISTORICAL = os.path.join(BASE, "cfg_sweep_fails.json")
RECEIPT = os.path.join(
    BASE, "recon", "catalogs", "cfg_historical_fail40_closure.json")


def main():
    with open(HISTORICAL) as fp:
        historical = json.load(fp)
    with open(RECEIPT) as fp:
        receipt = json.load(fp)

    expected = {
        (core, name)
        for core in ("app", "net")
        for name in historical[core]["fail_list"]
    }
    entries = receipt.get("entries", [])
    actual = {(entry.get("core"), entry.get("raw_identity"))
              for entry in entries}
    errors = []
    if actual != expected:
        errors.append("receipt identity set differs from historical fail list")
    if len(actual) != len(entries):
        errors.append("receipt contains duplicate identities")

    for entry in entries:
        identity = "%s:%s" % (entry.get("core"), entry.get("raw_identity"))
        if entry.get("status") != "PASS":
            errors.append("%s is not PASS" % identity)
        path = os.path.join(BASE, entry.get("canonical_source", ""))
        if not os.path.isfile(path):
            errors.append("%s source is missing: %s" % (identity, path))
            continue
        with open(path, "rb") as fp:
            digest = hashlib.sha256(fp.read()).hexdigest()
        if digest != entry.get("source_sha256"):
            errors.append("%s source digest changed" % identity)

    summary = receipt.get("summary", {})
    if summary.get("function_count") != len(expected):
        errors.append("summary function_count is stale")
    if summary.get("cfg_pass") != len(expected) or summary.get("cfg_fail") != 0:
        errors.append("summary PASS/FAIL counts are stale")

    if errors:
        for error in errors:
            print(error, file=sys.stderr)
        return 1
    print("CFG historical fail40: PASS (%d current-source CFG proofs)" %
          len(expected))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
