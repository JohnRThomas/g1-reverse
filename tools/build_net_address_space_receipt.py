#!/usr/bin/env python3
"""Build the deterministic CPUNET analysis/runtime address receipt."""

import gzip
import hashlib
import json
import os
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

from net_address_space import (
    ANALYSIS_BASE,
    ANALYSIS_TO_RUNTIME_DELTA,
    RUNTIME_BASE,
    AnalysisAddress,
    RuntimeAddress,
)


IMAGE = os.path.join(ROOT, "netcore_image.bin")
NAMES = os.path.join(ROOT, "recon/catalogs/function_names_net.json")
REFGRAPH = os.path.join(ROOT, "recon/catalogs/refgraph_net.json.gz")
OUTPUT = os.path.join(ROOT, "recon/catalogs/net_address_spaces.json")


def _load(path):
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt") as stream:
        return json.load(stream)


def _hex(value):
    return "0x%08x" % value


def build():
    with open(IMAGE, "rb") as stream:
        image = stream.read()
    names = _load(NAMES)["by_address"]
    refgraph = _load(REFGRAPH)["functions"]

    functions = []
    analysis_entries = set()
    runtime_entries = set()
    for address, record in sorted(names.items(), key=lambda item: int(item[0], 16)):
        analysis = AnalysisAddress(int(address, 16))
        runtime = analysis.to_runtime()
        if record.get("address") != address:
            raise ValueError(
                "name-catalog address mismatch: key %s, record %r" %
                (address, record.get("address")))
        if analysis.value in analysis_entries:
            raise ValueError("duplicate analysis identity %s" % address)
        if runtime.value in runtime_entries:
            raise ValueError("duplicate runtime identity %s" % _hex(runtime.value))
        analysis_entries.add(analysis.value)
        runtime_entries.add(runtime.value)
        functions.append({
            "analysis_address": _hex(analysis.value),
            "runtime_address": _hex(runtime.value),
            "raw_name": record["raw_name"],
            "name": record["name"],
        })

    overlaps = []
    for analysis in sorted(analysis_entries):
        runtime = analysis + ANALYSIS_TO_RUNTIME_DELTA
        if runtime in analysis_entries:
            overlaps.append({
                "runtime_of_analysis_address": _hex(analysis),
                "runtime_address": _hex(runtime),
                "colliding_analysis_address": _hex(runtime),
                "runtime_owner": names[_hex(analysis)]["name"],
                "analysis_owner": names[_hex(runtime)]["name"],
            })

    pointer_referrers = {}
    for caller, record in refgraph.items():
        for raw in record.get("data_refs", ()):
            try:
                value = int(raw, 16)
                runtime = RuntimeAddress(value & ~1)
            except (TypeError, ValueError):
                continue
            analysis = runtime.to_analysis().value
            if analysis not in analysis_entries:
                continue
            key = (value & ~1, bool(value & 1), analysis)
            pointer_referrers.setdefault(key, set()).add(int(caller, 16))

    function_pointers = []
    for (runtime, thumb, analysis), callers in sorted(pointer_referrers.items()):
        record = names[_hex(analysis)]
        function_pointers.append({
            "runtime_address": _hex(runtime | int(thumb)),
            "analysis_address": _hex(analysis),
            "thumb": thumb,
            "raw_name": record["raw_name"],
            "name": record["name"],
            "referring_analysis_functions": [_hex(value) for value in sorted(callers)],
        })

    reset_vector = int.from_bytes(image[4:8], "little")
    reset_runtime = RuntimeAddress(reset_vector & ~1)
    reset_analysis = reset_runtime.to_analysis()
    receipt = {
        "schema": 1,
        "core": "net",
        "image": "netcore_image.bin",
        "image_sha256": hashlib.sha256(image).hexdigest(),
        "coordinate_spaces": {
            "analysis": {
                "base": _hex(ANALYSIS_BASE),
                "usage": "function identities, CFG positions, direct relative targets",
            },
            "runtime": {
                "base": _hex(RUNTIME_BASE),
                "usage": "linked execution addresses and stored absolute flash pointers",
            },
            "analysis_to_runtime_delta": "0x%03x" % ANALYSIS_TO_RUNTIME_DELTA,
            "untyped_numeric_lookup_allowed": False,
        },
        "oracles": {
            "reset_vector": {
                "stored_runtime_thumb_address": _hex(reset_vector),
                "runtime_address": _hex(reset_runtime.value),
                "analysis_address": _hex(reset_analysis.value),
            },
            "assertion_string": {
                "runtime_address": "0x0103d2a7",
                "prefix": "ASSERTION FAIL @",
            },
            "packet_length_table": {
                "runtime_address": "0x0103c190",
                "length": 43,
                "sha256": hashlib.sha256(
                    image[0x0103c190 - RUNTIME_BASE:
                          0x0103c190 - RUNTIME_BASE + 43]).hexdigest(),
            },
        },
        "summary": {
            "function_identities": len(functions),
            "analysis_runtime_numeric_overlaps": len(overlaps),
            "runtime_function_pointer_references": len(function_pointers),
        },
        "functions": functions,
        "analysis_runtime_numeric_overlaps": overlaps,
        "runtime_function_pointer_references": function_pointers,
    }
    return receipt


def write(receipt, path=OUTPUT):
    text = json.dumps(receipt, indent=2, sort_keys=False) + "\n"
    descriptor, temporary = tempfile.mkstemp(
        prefix=os.path.basename(path) + ".", dir=os.path.dirname(path), text=True)
    try:
        with os.fdopen(descriptor, "w") as stream:
            stream.write(text)
        os.replace(temporary, path)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)


def main():
    receipt = build()
    write(receipt)
    print("functions=%d overlaps=%d runtime_function_pointers=%d -> %s" % (
        receipt["summary"]["function_identities"],
        receipt["summary"]["analysis_runtime_numeric_overlaps"],
        receipt["summary"]["runtime_function_pointer_references"], OUTPUT))


if __name__ == "__main__":
    main()
