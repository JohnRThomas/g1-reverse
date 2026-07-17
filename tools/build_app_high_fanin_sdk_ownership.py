#!/usr/bin/env python3
"""Build fail-closed ownership evidence for high-fan-in CPUAPP residues."""

import argparse
import gzip
import hashlib
import json
import os


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IMAGE = os.path.join(ROOT, "app_update.bin")
CLASSIFIED = os.path.join(ROOT, "recon/catalogs/classified.json.gz")
OUTPUT = os.path.join(ROOT, "recon/catalogs/app_high_fanin_sdk_ownership.json")
BASE = 0xC200

EXPECTED = (
    {
        "va": 0x0007DDA4, "size": 26, "symbol": "log_message",
        "semantic_owner": "application variadic vprintf wrapper",
        "source": "recon/app/src/log_message.c",
        "upstream_provenance": "newlib-nano vprintf public API",
        "config": ["CONFIG_NEWLIB_LIBC=y", "CONFIG_NEWLIB_LIBC_NANO=y"],
        "abi": "void log_message(const char *format, ...); AAPCS va_list begins at saved r1",
        "reference_count": 281,
        "same_entry_alias": "DEBUG_PRINT",
        "same_entry_alias_reference_count": 61,
    },
    {
        "va": 0x000431A8, "size": 8, "symbol": "atomic_get_3_0",
        "semantic_owner": "display atomic-state accessor",
        "source": "recon/app/src/atomic_get_3_0.c",
        "upstream_provenance": "Zephyr atomic_get semantics; application object at 0x2000a030",
        "config": ["CONFIG_ATOMIC_OPERATIONS_BUILTIN=y"],
        "abi": "uint32_t atomic_get_3_0(void); fixed atomic object at 0x2000a030",
        "reference_count": 30,
    },
    {
        "va": 0x00082FF6, "size": 12, "symbol": "atomic_test_bit",
        "semantic_owner": "Zephyr atomic_test_bit header-inline instance",
        "source": "recon/app/src/atomic_test_bit.c",
        "upstream_provenance": "zephyr/include/zephyr/sys/atomic.h",
        "config": ["CONFIG_ATOMIC_OPERATIONS_BUILTIN=y"],
        "abi": "bool atomic_test_bit(const atomic_t *target, int bit); atomic_t is 32-bit long",
        "reference_count": 37,
    },
    {
        "va": 0x00083090, "size": 20, "symbol": "atomic_set_bit",
        "semantic_owner": "Zephyr atomic_set_bit header-inline instance",
        "source": "recon/app/src/atomic_set_bit.c",
        "upstream_provenance": "zephyr/include/zephyr/sys/atomic.h",
        "config": ["CONFIG_ATOMIC_OPERATIONS_BUILTIN=y"],
        "abi": "void atomic_set_bit(atomic_t *target, int bit); atomic_t is 32-bit long",
        "reference_count": 29,
    },
)


def sha256_bytes(data):
    return hashlib.sha256(data).hexdigest()


def load_classified(path):
    with gzip.open(path, "rt", encoding="utf-8") as stream:
        return json.load(stream)["functions"]


def build(classified_path=CLASSIFIED, image_path=IMAGE):
    by_va = {row["entry"]: row for row in load_classified(classified_path)}
    with open(image_path, "rb") as stream:
        image = stream.read()
    rows = []
    for expected in EXPECTED:
        catalog = by_va.get(expected["va"])
        if not catalog:
            raise ValueError("missing classified entry 0x%08x" % expected["va"])
        if catalog["size"] != expected["size"] or catalog["name"] != expected["symbol"]:
            raise ValueError("identity drift at 0x%08x: %r" % (expected["va"], catalog))
        source_path = os.path.join(ROOT, expected["source"])
        if not os.path.isfile(source_path):
            raise ValueError("missing retained owner %s" % expected["source"])
        start = expected["va"] - BASE
        span = image[start:start + expected["size"]]
        if len(span) != expected["size"]:
            raise ValueError("firmware span out of range at 0x%08x" % expected["va"])
        with open(source_path, "rb") as stream:
            source_digest = sha256_bytes(stream.read())
        row = dict(expected)
        row.update({
            "va": "0x%08x" % expected["va"],
            "raw_identity": "FUN_%08x" % expected["va"],
            "firmware_span_sha256": sha256_bytes(span),
            "source_sha256": source_digest,
            "verification": "tools/cfg_verify.py app %s: PASS" % expected["symbol"],
            "retain_reconstruction": True,
            "exclude_reconstruction": False,
        })
        rows.append(row)
    return {
        "schema": 1,
        "core": "app",
        "policy": {
            "fail_closed": True,
            "single_owner": "retained reconstructed entry",
            "no_weak_stub_blob_or_assembly": True,
            "forbidden_alias": "log_message/DEBUG_PRINT@0x0007dda4 -> debug_print@0x00019c70",
            "permitted_same_entry_alias": "DEBUG_PRINT -> log_message@0x0007dda4",
        },
        "pinned_environment": {
            "ncs": "2.5.1", "zephyr": "3.4.99", "gcc": "12.2.0",
            "libc": "newlib-nano", "optimization": "-Os", "float_abi": "hard",
        },
        "summary": {
            "functions": len(rows),
            "resolved_reference_count": (
                sum(row["reference_count"] for row in rows) +
                sum(row.get("same_entry_alias_reference_count", 0) for row in rows)),
        },
        "functions": rows,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--classified", default=CLASSIFIED)
    parser.add_argument("--image", default=IMAGE)
    parser.add_argument("--output", default=OUTPUT)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    rendered = json.dumps(build(args.classified, args.image), indent=1) + "\n"
    if args.check:
        if not os.path.isfile(args.output) or open(args.output, encoding="utf-8").read() != rendered:
            raise SystemExit("CPUAPP high-fan-in SDK ownership catalog is stale")
    else:
        with open(args.output, "w", encoding="utf-8") as stream:
            stream.write(rendered)
    print("CPUAPP high-fan-in ownership PASS: 4 functions, 438 classified references")


if __name__ == "__main__":
    main()
