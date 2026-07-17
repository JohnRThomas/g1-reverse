#!/usr/bin/env python3
"""Prove the classified CPUAPP naming residue is absent after regeneration."""

import argparse
import hashlib
import json
import os
import re


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
UNDEFINED = re.compile(r"undefined reference to [`']([^`']+)[`']")
MULTIPLE = re.compile(r"multiple definition of [`']([^`']+)[`']")


def digest(path):
    value = hashlib.sha256()
    with open(path, "rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            value.update(block)
    return value.hexdigest()


def symbols(path, pattern):
    with open(path, encoding="utf-8", errors="replace") as stream:
        return set(pattern.findall(stream.read()))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--before", required=True)
    parser.add_argument("--after", required=True)
    parser.add_argument("--report", default=os.path.join(
        ROOT, "recon/analysis/app_link_residue.json"))
    parser.add_argument("--json", default=os.path.join(
        ROOT, "recon/analysis/app_identity_repair_proof.json"))
    parser.add_argument("--markdown", default=os.path.join(
        ROOT, "recon/analysis/app_identity_repair_proof.md"))
    args = parser.parse_args()

    with open(args.report) as stream:
        report = json.load(stream)
    queue = {row["symbol"] for row in report["entries"]
             if row["category"] == "naming_or_symbolization_defect"}
    before = symbols(args.before, UNDEFINED)
    after = symbols(args.after, UNDEFINED)
    duplicates = symbols(args.after, MULTIPLE)
    missing_before = sorted(queue - before)
    remaining = sorted(queue & after)
    duplicate_queue = sorted(queue & duplicates)
    result = {
        "schema": 1,
        "core": "app",
        "scope": "61 identity-safe naming/symbolization repairs",
        "inputs": {
            "before": {"path": os.path.abspath(args.before),
                       "sha256": digest(args.before)},
            "after": {"path": os.path.abspath(args.after),
                      "sha256": digest(args.after)},
            "classification": {"path": os.path.relpath(args.report, ROOT),
                               "sha256": digest(args.report)},
        },
        "queue_count": len(queue),
        "present_before": len(queue & before),
        "removed_after": len(queue - after),
        "missing_from_before": missing_before,
        "remaining_after": remaining,
        "duplicate_queue_symbols": duplicate_queue,
        "pass": not missing_before and not remaining and not duplicate_queue,
        "excluded_correction": {
            "symbol": "DEBUG_PRINT",
            "va": "0x0007dda4",
            "category": "sdk_or_config_symbol",
            "reason": "distinct variadic vprintf wrapper; never aliased to debug_print@0x00019c70",
        },
    }
    if not result["pass"]:
        raise SystemExit("identity repair proof failed: %s" % result)
    with open(args.json, "w") as stream:
        json.dump(result, stream, indent=1)
        stream.write("\n")
    lines = [
        "# CPUAPP identity repair proof", "",
        "The corrected naming/symbolization queue contains **%d** symbols. All"
        % len(queue),
        "were present in the pre-repair retain-all log and none remain in the",
        "post-repair retain-all log. No queue spelling appears in a duplicate-",
        "definition diagnostic.", "",
        "`DEBUG_PRINT` is deliberately excluded: disassembly identifies it as the",
        "distinct variadic wrapper at `0x0007dda4`, not `debug_print` at",
        "`0x00019c70`; it now belongs to SDK/library ownership remediation.", "",
    ]
    with open(args.markdown, "w") as stream:
        stream.write("\n".join(lines))
    print("CPUAPP identity proof PASS: %d/%d removed, 0 duplicate owners" %
          (len(queue - after), len(queue)))


if __name__ == "__main__":
    main()
