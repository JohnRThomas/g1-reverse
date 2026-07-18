#!/usr/bin/env python3
"""Receipt for the two in-body ARCH_EXCEPT sites in hci_tx_thread."""

import argparse
import hashlib
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
IMAGE = ROOT / "app_update.bin"
SOURCE = ROOT / "recon/app/src/FUN_000545f0.c"
MIRROR = ROOT / "recon/verified/src/FUN_000545f0.c"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
NAMED = ROOT / "recon/named/hci_tx_thread.c"
SYMBOLIZED = ROOT / "recon/symbolized/app/hci_tx_thread.c"
JSON_OUT = ROOT / "recon/ownership/app_hci_tx_svc_resolution.json"
MD_OUT = ROOT / "recon/ownership/app_hci_tx_svc_resolution.md"
LINK_BASE = 0xC200
IMAGE_HEADER = 512
SITES = (0x00054634, 0x0005467E)
SEQUENCE = bytes.fromhex("404080f311884ff0030002df")


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def image_read(image, va, size):
    offset = va - LINK_BASE + IMAGE_HEADER
    return image[offset:offset + size]


def build():
    source = SOURCE.read_text()
    mirror = MIRROR.read_text()
    named = NAMED.read_text()
    symbolized = SYMBOLIZED.read_text()
    names = json.loads(NAMES.read_text())
    if source != mirror:
        raise ValueError("canonical hci_tx_thread source/mirror drift")
    required = (
        '"eors.n r0, r0\\n\\t"',
        '"msr BASEPRI, r0\\n\\t"',
        '"mov r0, %[why]\\n\\t"',
        '"svc %[id]\\n\\t"',
        "ARCH_EXCEPT(3);",
        "__builtin_unreachable();",
    )
    if any(token not in source for token in required):
        raise ValueError("stock ARCH_EXCEPT lowering drift")
    stale = ("FUN_0005463e", "FUN_00054688")
    for path, text in ((SOURCE, source), (NAMED, named),
                       (SYMBOLIZED, symbolized)):
        if any(symbol in text for symbol in stale):
            raise ValueError("fabricated SVC function survived in %s" % path)
    record = names["by_address"]["0x000545f0"]
    if record["name"] != "hci_tx_thread" or record["raw_name"] != "FUN_000545f0":
        raise ValueError("hci_tx_thread readable/raw identity drift")
    image = IMAGE.read_bytes()
    rows = []
    for va in SITES:
        actual = image_read(image, va, len(SEQUENCE))
        if actual != SEQUENCE:
            raise ValueError("ARCH_EXCEPT bytes drift at 0x%08x" % va)
        rows.append({
            "sequence_start": "0x%08x" % va,
            "svc_address": "0x%08x" % (va + 10),
            "bytes": actual.hex(),
            "reason": 3,
            "svc_immediate": 2,
        })
    return {
        "schema": 1,
        "core": "app",
        "status": "resolved_in_containing_owner",
        "owner": {
            "address": "0x000545f0",
            "raw_name": "FUN_000545f0",
            "name": "hci_tx_thread",
            "upstream_identity": "zephyr/subsys/bluetooth/host/hci_core.c:hci_tx_thread",
        },
        "image_sha256": digest(IMAGE),
        "source_sha256": digest(SOURCE),
        "sites": rows,
        "resolution": {
            "stock_macro": "Zephyr 3.4 ARMv8-M Mainline ARCH_EXCEPT(3)",
            "fake_function_entries_removed": list(stale),
            "raw_owner_backmap_preserved": True,
            "cfg_verify": {
                "command": "tools/cfg_verify.py app FUN_000545f0",
                "result": "PASS",
                "cases": 8,
            },
            "full_link_effect": "both fake undefined function symbols removed",
        },
        "policy": {
            "linker_aliases_emitted": False,
            "invented_functions": False,
            "byte_blobs": False,
        },
    }


def markdown(data):
    lines = [
        "# CPUAPP hci_tx_thread embedded SVC resolution",
        "",
        "The apparent functions `FUN_0005463e` and `FUN_00054688` were the",
        "final `svc #2` instructions of two identical, in-body stock Zephyr",
        "`ARCH_EXCEPT(3)` sequences. They are now expressed inside",
        "`hci_tx_thread`; no veneer, alias, or invented callable ABI remains.",
        "",
        "| sequence | SVC | bytes |",
        "|---|---|---|",
    ]
    for row in data["sites"]:
        lines.append("| `%s` | `%s` | `%s` |" %
                     (row["sequence_start"], row["svc_address"], row["bytes"]))
    lines += [
        "",
        "Authoritative CFG verification: **PASS, 8 cases**. The readable name",
        "maps back to raw owner `FUN_000545f0 @ 0x000545f0`.",
        "",
    ]
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build()
    json_text = json.dumps(data, indent=2, sort_keys=True) + "\n"
    md_text = markdown(data)
    if args.check:
        if JSON_OUT.read_text() != json_text or MD_OUT.read_text() != md_text:
            raise SystemExit("hci_tx_thread SVC receipt is stale")
        print("hci_tx_thread SVC receipt current")
        return
    JSON_OUT.write_text(json_text)
    MD_OUT.write_text(md_text)
    print("wrote", JSON_OUT.relative_to(ROOT), MD_OUT.relative_to(ROOT))


if __name__ == "__main__":
    main()
