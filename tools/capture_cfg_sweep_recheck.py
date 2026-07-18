#!/usr/bin/env python3
"""Capture exact-hash CFG rechecks for sources changed after a full lane sweep."""

import argparse
import hashlib
import json
from pathlib import Path

import cfg_verify


ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "recon/analysis/cfg_sweep_target_rechecks.json"
TOOL_PATHS = (
    "tools/cfg_verify.py",
    "tools/parity/emu.py",
    "tools/parity/recon.py",
)


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def json_safe(value):
    if value is None or isinstance(value, (bool, int, float, str)):
        return value
    if isinstance(value, bytes):
        return {"bytes_hex": value.hex()}
    if isinstance(value, (list, tuple)):
        return [json_safe(item) for item in value]
    if isinstance(value, dict):
        return {str(key): json_safe(item) for key, item in value.items()}
    return {"repr": repr(value)}


def capture(core, name):
    source = ROOT / "recon" / core / "src" / (name + ".c")
    if not source.exists():
        raise ValueError("missing canonical source: %s" % source)
    before = sha256(source)
    result = cfg_verify.verify(core, name)
    after = sha256(source)
    if before != after:
        raise ValueError("source changed during CFG recheck: %s:%s" %
                         (core, name))
    tools = {path: sha256(ROOT / path) for path in TOOL_PATHS}
    return {
        "core": core,
        "name": name,
        "source_sha256": before,
        "tool_hashes": tools,
        "status": result.get("status"),
        "result": json_safe(result),
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("core", choices=("app", "net"))
    parser.add_argument("names", nargs="+")
    parser.add_argument("--output", type=Path, default=OUT)
    args = parser.parse_args()
    if args.output.exists():
        data = json.loads(args.output.read_text())
    else:
        data = {"schema": 1, "kind": "cfg_sweep_target_rechecks",
                "rechecks": {}}
    if data.get("schema") != 1 or not isinstance(data.get("rechecks"), dict):
        raise ValueError("unsupported target-recheck receipt")
    for name in args.names:
        receipt = capture(args.core, name)
        data["rechecks"][args.core + ":" + name] = receipt
        print("%s:%s %s source=%s" %
              (args.core, name, receipt["status"],
               receipt["source_sha256"]), flush=True)
    args.output.write_text(json.dumps(data, indent=1, sort_keys=True) + "\n")


if __name__ == "__main__":
    main()
