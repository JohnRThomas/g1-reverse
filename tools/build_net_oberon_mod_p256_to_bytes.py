#!/usr/bin/env python3
"""Build the fail-closed CPUNET Oberon P-256 serialization receipt."""

import argparse
import hashlib
import io
import json
import subprocess
from pathlib import Path

from elftools.elf.elffile import ELFFile

import net_extract


ROOT = Path(__file__).resolve().parents[1]
NCS = Path("/Users/freedomcoder/ncs251")
NRFXLIB = NCS / "nrfxlib"
ARCHIVE_REL = Path(
    "crypto/nrf_oberon/lib/cortex-m33+nodsp/soft-float/"
    "liboberon_3.0.13.a")
ARCHIVE = NRFXLIB / ARCHIVE_REL
MEMBER = "ocrypto_mod_p256.c.obj"
CURVE_MEMBER = "ocrypto_curve_p256.c.obj"
SECTION = ".text.ocrypto_mod_p256_to_bytes"
REJECTED_SECTION = ".text.ocrypto_mod_p256_from_bytes"
AR = Path(
    "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
    "arm-zephyr-eabi-ar")
OUTPUT = ROOT / "recon/ownership/net_oberon_mod_p256_to_bytes_exact.json"

ANALYSIS_VA = 0x01038FA4
RUNTIME_VA = 0x010397A4
ARCHIVE_SHA256 = "466f575748e64a8a170ed796a4edcd8a489517b5dd108b0f4295eea8ebb082f6"
MEMBER_SHA256 = "20411366c8705d23cc3244fe5d488015b55632a9cf385b33cdb1c8836f0e4c2f"
CURVE_MEMBER_SHA256 = "a7fdd1aeef4b583da563acec8a259c8a47deb5d32ffd3cbc6a70cfbaff96e1b6"
NRFXLIB_COMMIT = "ab72f33c86db7252dbf9a3ffec86c6b7fc6a9da7"
ARCHIVE_GIT_BLOB = "37fe825f2109ed72192b97dd12d5b21885e0a940"
IDENTICAL_TAGS = [
    "v2.4.0", "v2.4.0-rc1", "v2.4.0-rc2", "v2.4.1", "v2.4.2",
    "v2.4.3", "v2.4.4", "v2.5.0", "v2.5.0-NCSDK-29842",
    "v2.5.0-NCSDK-29842-1", "v2.5.0-rc1", "v2.5.0-rc2",
    "v2.5.1", "v2.5.1-rc1", "v2.5.2", "v2.5.3",
]


def sha(data):
    return hashlib.sha256(data).hexdigest()


def member_bytes(name=MEMBER):
    return subprocess.check_output([str(AR), "p", str(ARCHIVE), name])


def section_bytes(obj, name):
    elf = ELFFile(io.BytesIO(obj))
    section = elf.get_section_by_name(name)
    if section is None:
        raise ValueError("missing Oberon section " + name)
    reloc = elf.get_section_by_name(".rel" + name)
    offsets = ([] if reloc is None else
               [int(row["r_offset"]) for row in reloc.iter_relocations()])
    return section.data(), offsets


def git_blob(tag):
    spec = "%s:%s" % (tag, ARCHIVE_REL.as_posix())
    return subprocess.check_output(
        ["git", "-C", str(NRFXLIB), "rev-parse", spec], text=True).strip()


def curve_call_relocations(obj):
    elf = ELFFile(io.BytesIO(obj))
    result = []
    for section_name in (".text.ocrypto_curve_p256_to32bytes",
                         ".text.ocrypto_curve_p256_to64bytes"):
        reloc = elf.get_section_by_name(".rel" + section_name)
        symbols = elf.get_section(reloc["sh_link"])
        for row in reloc.iter_relocations():
            target = symbols.get_symbol(row["r_info_sym"]).name
            if target == "ocrypto_mod_p256_to_bytes":
                result.append({
                    "caller_section": section_name,
                    "offset": int(row["r_offset"]),
                    "relocation_type": int(row["r_info_type"]),
                    "target": target,
                })
    return result


def build():
    archive = ARCHIVE.read_bytes()
    obj = member_bytes()
    curve_obj = member_bytes(CURVE_MEMBER)
    if sha(archive) != ARCHIVE_SHA256 or sha(obj) != MEMBER_SHA256:
        raise ValueError("pinned Oberon artifact changed")
    if sha(curve_obj) != CURVE_MEMBER_SHA256:
        raise ValueError("pinned Oberon curve caller changed")
    selected, relocations = section_bytes(obj, SECTION)
    rejected, rejected_relocations = section_bytes(obj, REJECTED_SECTION)
    firmware = net_extract.read_analysis(ANALYSIS_VA, len(selected))
    if relocations or rejected_relocations:
        raise ValueError("unexpected relocation in endian conversion section")
    if firmware != selected:
        raise ValueError("Oberon to_bytes section differs from firmware")
    if firmware == rejected:
        raise ValueError("from_bytes and to_bytes identities are ambiguous")
    for tag in IDENTICAL_TAGS:
        if git_blob(tag) != ARCHIVE_GIT_BLOB:
            raise ValueError("Oberon archive plateau changed at " + tag)

    return {
        "schema": 1,
        "core": "net",
        "component": "nrfxlib_oberon",
        "status": "exact_identity_correction",
        "decision": "name_as_ocrypto_mod_p256_to_bytes",
        "identity": {
            "analysis_va": "0x%08x" % ANALYSIS_VA,
            "runtime_va": "0x%08x" % RUNTIME_VA,
            "raw_symbol": "FUN_%08x" % ANALYSIS_VA,
            "upstream_symbol": "ocrypto_mod_p256_to_bytes",
            "abi": "void(uint8_t output[32], const ocrypto_mod_p256 *input)",
            "type_layout": "ocrypto_mod_p256 = uint32_t w[8] (32 bytes)",
        },
        "upstream": {
            "manifest_pin": "NCS/nrfxlib v2.5.1",
            "repository_commit": NRFXLIB_COMMIT,
            "oberon_version": "3.0.13",
            "archive": str(ARCHIVE),
            "archive_sha256": ARCHIVE_SHA256,
            "archive_git_blob": ARCHIVE_GIT_BLOB,
            "member": MEMBER,
            "member_sha256": MEMBER_SHA256,
            "section": SECTION,
            "section_size": len(selected),
            "section_sha256": sha(selected),
            "relocation_offsets": relocations,
            "selected_abi": "cortex-m33+nodsp soft-float",
        },
        "firmware_proof": {
            "match": "complete-section-byte-exact",
            "firmware_size": len(firmware),
            "firmware_sha256": sha(firmware),
            "load_store_direction": [
                "load input words at +0x1c,+0x18,...,+0x00",
                "REV each word",
                "store output words at +0x00,+0x04,...,+0x1c",
            ],
            "refgraph_callers": ["0x01038da0"],
            "code_callers": [
                {
                    "va": "0x01038d9c",
                    "identity": "ocrypto_curve_p256_to32bytes",
                    "site": "tail B.W 0x01038fa4",
                },
                {
                    "va": "0x01038da0",
                    "identity": "ocrypto_curve_p256_to64bytes",
                    "sites": ["BL 0x01038fa4 at 0x01038da6",
                              "tail B.W 0x01038fa4 at 0x01038db6"],
                },
            ],
            "archive_call_relocations": curve_call_relocations(curve_obj),
        },
        "rejected_identity": {
            "symbol": "ocrypto_mod_p256_from_bytes",
            "actual_analysis_va": "0x01038f70",
            "section": REJECTED_SECTION,
            "section_size": len(rejected),
            "section_sha256": sha(rejected),
            "reason": (
                "from_bytes loads input at ascending offsets and stores the "
                "reversed limbs at descending offsets; 0x01038fa4 does the inverse"),
        },
        "version_precision": {
            "archive_blob_identical_tags": IDENTICAL_TAGS,
            "earlier_family": "NCS v2.3.x carries Oberon 3.0.12",
            "later_family": "NCS v2.6.x carries Oberon 3.0.14",
            "limitation": (
                "The exact archive proves Oberon 3.0.13 / NCS 2.4.x-2.5.x; "
                "the function body cannot distinguish those tags. The west "
                "manifest pin establishes exact NCS v2.5.1 provenance."),
        },
        "policy": {
            "raw_backmap_preserved": True,
            "central_manifest_unchanged": True,
            "sdc_policy": "report_only_unchanged",
        },
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    text = json.dumps(build(), indent=1) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != text:
            raise ValueError("stale Oberon to_bytes receipt")
    else:
        OUTPUT.write_text(text)
    print("net Oberon to_bytes exact owner: 0x01038fa4")


if __name__ == "__main__":
    main()
