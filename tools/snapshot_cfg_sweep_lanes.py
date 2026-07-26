#!/usr/bin/env python3
"""Snapshot volatile CFG lane receipts before an inventory-changing rerun."""

# Resolvable pipeline scratchpad (tools/g1_paths.py).  This used to be one
# literal /private/tmp path belonging to a finished agent session; see that
# module for the resolution order and the fail-closed catalog fallback.
import os as _g1_os, sys as _g1_sys
_G1_TOOLS = _g1_os.path.dirname(_g1_os.path.abspath(__file__))
if _g1_os.path.basename(_G1_TOOLS) != "tools":
    _G1_TOOLS = _g1_os.path.dirname(_G1_TOOLS)
if _G1_TOOLS not in _g1_sys.path:
    _g1_sys.path.insert(0, _G1_TOOLS)
import g1_paths as _g1_paths

import argparse
import hashlib
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SCRATCH = Path(
    _g1_paths.scratchpad()
)
BUCKETS = (
    "PASS", "FAIL", "compile_error", "other", "timeout",
    "source_changed",
)


def sha256_bytes(value):
    return hashlib.sha256(value).hexdigest()


def build(core):
    lanes = {}
    totals = {bucket: 0 for bucket in BUCKETS}
    inventory_counts = set()
    for lane in range(8):
        path = SCRATCH / ("reverify_%s_L%d.json" % (core, lane))
        raw = path.read_bytes()
        receipt = json.loads(raw)
        if (receipt.get("_shard_count") != 8 or
                receipt.get("_shard_index") != lane):
            raise ValueError("invalid lane identity: %s" % path)
        members = []
        for bucket in BUCKETS:
            values = receipt.get(bucket, [])
            totals[bucket] += len(values)
            members.extend(values)
        if len(members) != len(set(members)):
            raise ValueError("duplicate verdict in %s" % path)
        if set(receipt.get("_source_hashes", {})) != set(members):
            raise ValueError("source-hash coverage drift in %s" % path)
        inventory_counts.add(receipt.get("_inventory_count"))
        lanes[str(lane)] = {
            "scratch_path": str(path),
            "scratch_receipt_sha256": sha256_bytes(raw),
            "receipt": receipt,
        }
    if len(inventory_counts) != 1 or sum(totals.values()) != next(
            iter(inventory_counts)):
        raise ValueError("lane inventory is incomplete")
    return {
        "schema": 1,
        "kind": "cfg_sweep_lane_snapshot",
        "core": core,
        "inventory_count": next(iter(inventory_counts)),
        "counts": totals,
        "lanes": lanes,
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("core", choices=("app", "net"))
    parser.add_argument("output", type=Path)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    content = json.dumps(build(args.core), indent=1, sort_keys=True) + "\n"
    old = args.output.read_text() if args.output.exists() else None
    if args.check and old != content:
        raise ValueError("stale lane snapshot: %s" % args.output)
    if not args.check and old != content:
        args.output.write_text(content)
    print("%s snapshot valid: %s" % (args.core, args.output))


if __name__ == "__main__":
    main()
