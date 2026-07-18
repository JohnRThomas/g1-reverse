#!/usr/bin/env python3
"""Build a non-authorizing receipt for exact GCC/Newlib-nano image matches."""

import argparse
import hashlib
import io
import json
import subprocess
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
SDK = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi")
AR = SDK / "bin/arm-zephyr-eabi-ar"
MULTILIB = "thumb/v8-m.main+fp/hard"
LIBDIR = SDK / "arm-zephyr-eabi/lib" / MULTILIB
GCCDIR = SDK / "lib/gcc/arm-zephyr-eabi/12.2.0" / MULTILIB
ARCHIVES = {
    "libc_nano": LIBDIR / "libc_nano.a",
    "libm_nano": LIBDIR / "libm_nano.a",
    "libgcc": GCCDIR / "libgcc.a",
}
ARCHIVE_SHA256 = {
    "libc_nano": "c6a3f8bf0d33e395061c64e8f523e7fb11aaf7fb679c25ff0124e5cd77eaa5cc",
    "libm_nano": "9a5f5ed0de96d00ad1b0a4b3ad04ac9734484ebd3b4baa2c6f4db78f53745ffd",
    "libgcc": "ef533e786e630d558648c53887eedc0d8aacd92f48d24dfc60745df388db5f1e",
}
NANO_SPECS = SDK / "arm-zephyr-eabi/lib/nano.specs"
NANO_SPECS_SHA256 = "45c2b58cf99963cba6e8498f3234131e7868deae67d5a9c0a3852ea84bc18329"
IMAGE = ROOT / "app_update.bin"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
OUTPUT = ROOT / "recon/catalogs/app_toolchain_exact_matches.json"
VA_START = 0xC200
VA_END = 0x879B0
IMAGE_FLASH_BASE = 0xC000

# Exact section ownership established by the complete archive sweep.  Unlike
# libc_nano, these compact families are intentionally pinned: scanning every
# tiny compiler helper creates unhelpful matches against literal/data bytes.
LIBGCC = [
    (0xD580, "_arm_addsubdf3.o", ".text"),
    (0xD8F8, "_arm_muldivdf3.o", ".text"),
    (0xDD1C, "_arm_cmpdf2.o", ".text"),
    (0xDE58, "_arm_fixdfsi.o", ".text"),
    (0xDEA8, "_arm_fixunsdfsi.o", ".text"),
    (0xDEE8, "_arm_truncdfsf2.o", ".text"),
    (0xDF88, "_arm_addsubsf3.o", ".text"),
    (0xE1A4, "_aeabi_ldivmod.o", ".text"),
    (0xE244, "_aeabi_uldivmod.o", ".text"),
    (0xE274, "_fixunsdfdi.o", ".text"),
    (0xEC34, "_fixdfdi.o", ".text"),
    (0xEC62, "_udivmoddi4.o", ".text"),
]

LIBM = [
    (0x12C80, "lib_a-w_exp.o", ".text.exp"),
    (0x12D20, "lib_a-w_log.o", ".text.log"),
    (0x12DB0, "lib_a-e_exp.o", ".text.__ieee754_exp"),
    (0x13090, "lib_a-e_log.o", ".text.__ieee754_log"),
    (0x133F8, "lib_a-e_pow.o", ".text.__ieee754_pow"),
    (0x13E50, "lib_a-s_nan.o", ".text.nan"),
    (0x13E60, "lib_a-s_scalbn.o", ".text.scalbn"),
    (0x75980, "lib_a-sf_fpclassify.o", ".text.__fpclassifyf"),
    (0x759B8, "lib_a-sf_frexp.o", ".text.frexpf"),
    (0x75A0C, "lib_a-sf_scalbn.o", ".text.scalbnf"),
    (0x75ACC, "lib_a-w_pow.o", ".text.pow"),
    (0x75C2C, "lib_a-wf_asin.o", ".text.asinf"),
    (0x75C90, "lib_a-wf_exp.o", ".text.expf"),
    (0x75D0C, "lib_a-wf_fmod.o", ".text.fmodf"),
    (0x75D5C, "lib_a-wf_log10.o", ".text.log10f"),
    (0x75DC8, "lib_a-wf_sqrt.o", ".text.sqrtf"),
    (0x75E14, "lib_a-e_sqrt.o", ".text.__ieee754_sqrt"),
    (0x75F88, "lib_a-ef_asin.o", ".text.__ieee754_asinf"),
    (0x76154, "lib_a-ef_atan2.o", ".text.__ieee754_atan2f"),
    (0x76290, "lib_a-ef_exp.o", ".text.__ieee754_expf"),
    (0x76430, "lib_a-ef_fmod.o", ".text.__ieee754_fmodf"),
    (0x76538, "lib_a-ef_log.o", ".text.__ieee754_logf"),
    (0x76718, "lib_a-ef_log10.o", ".text.__ieee754_log10f"),
    (0x767C8, "lib_a-s_rint.o", ".text.rint"),
    (0x768E0, "lib_a-sf_atan.o", ".text.atanf"),
    (0x76A88, "lib_a-sf_nan.o", ".text.nanf"),
    (0x868EE, "lib_a-sf_fabs.o", ".text.fabsf"),
    (0x86902, "lib_a-sf_fmax.o", ".text.fmaxf"),
    (0x8693C, "lib_a-sf_fmin.o", ".text.fminf"),
    (0x86976, "lib_a-sf_ldexp.o", ".text.ldexpf"),
    (0x869CC, "lib_a-s_fabs.o", ".text.fabs"),
    (0x869DC, "lib_a-s_finite.o", ".text.finite"),
    (0x869F2, "lib_a-sf_finite.o", ".text.finitef"),
]
LIBM_ALTERNATIVES = {
    0x75C2C: [("lib_a-wf_acos.o", ".text.acosf")],
}


def sha256_bytes(data):
    return hashlib.sha256(data).hexdigest()


def sha256_file(path):
    return sha256_bytes(Path(path).read_bytes())


def member_bytes(archive, member):
    return subprocess.check_output([str(AR), "p", str(archive), member])


def member_names(archive):
    output = subprocess.check_output([str(AR), "t", str(archive)], text=True)
    return sorted(set(line.strip() for line in output.splitlines() if line.strip()))


def section_candidate(archive, member, section_name, obj=None):
    obj = member_bytes(archive, member) if obj is None else obj
    elf = ELFFile(io.BytesIO(obj))
    section = elf.get_section_by_name(section_name)
    if section is None:
        raise ValueError("missing %s(%s)" % (member, section_name))
    data = section.data()
    reloc = elf.get_section_by_name(".rel" + section_name)
    offsets = [] if reloc is None else sorted(set(
        int(item["r_offset"]) for item in reloc.iter_relocations()
        if int(item["r_offset"]) < len(data)))
    masked = bytearray(data)
    mask = bytearray(len(data))
    for offset in offsets:
        end = min(offset + 4, len(data))
        masked[offset:end] = b"\0" * (end - offset)
        mask[offset:end] = b"\1" * (end - offset)
    return {
        "archive_member": member,
        "section": section_name,
        "size": len(data),
        "relocation_count": len(offsets),
        "relocation_offsets": offsets,
        "archive_member_sha256": sha256_bytes(obj),
        "normalized_code_sha256": sha256_bytes(masked),
        "_data": data,
        "_mask": bytes(mask),
    }


def exact_at(candidate, firmware, va):
    offset = va - IMAGE_FLASH_BASE
    data = candidate["_data"]
    actual = bytearray(firmware[offset:offset + len(data)])
    if len(actual) != len(data):
        return False
    for index, masked in enumerate(candidate["_mask"]):
        if masked:
            actual[index] = 0
        elif actual[index] != data[index]:
            return False
    return sha256_bytes(actual) == candidate["normalized_code_sha256"]


def longest_anchor(data, mask):
    best = (0, 0)
    start = 0
    while start < len(data):
        while start < len(data) and mask[start]:
            start += 1
        end = start
        while end < len(data) and not mask[end]:
            end += 1
        if end - start > best[1] - best[0]:
            best = (start, end)
        start = end + 1
    return best


def firmware_hits(candidate, firmware):
    data, mask = candidate["_data"], candidate["_mask"]
    first, last = longest_anchor(data, mask)
    if last - first < 6:
        return []
    region = firmware[VA_START - IMAGE_FLASH_BASE:VA_END - IMAGE_FLASH_BASE]
    anchor = data[first:last]
    hits, cursor = [], 0
    while True:
        found = region.find(anchor, cursor)
        if found < 0:
            break
        begin = found - first
        va = VA_START + begin
        if begin >= 0 and not (va & 1) and exact_at(candidate, firmware, va):
            hits.append(va)
        cursor = found + 1
    return sorted(set(hits))


def public_candidate(candidate, hits):
    return {key: value for key, value in candidate.items() if not key.startswith("_")} | {
        "firmware_hits": ["0x%08x" % va for va in hits]
    }


def name_record(names, va):
    record = names.get("0x%08x" % va, {})
    return {
        "raw_symbol": record.get("raw_name", "FUN_%08x" % va),
        "current_readable_name": record.get("name", "FUN_%08x" % va),
    }


def make_row(va, candidates, names, resolution=None):
    candidates = sorted(candidates, key=lambda item: (
        0 if resolution and item["archive_member"] == resolution.get("archive_member") else 1,
        -item["size"], item["archive_member"], item["section"]))
    representative = candidates[0]
    owners = {(item["archive_member"], item["section"], item["size"],
               item["normalized_code_sha256"]) for item in candidates}
    ambiguity = len(owners) > 1 or any(len(item["firmware_hits"]) > 1
                                       for item in candidates)
    row = {
        "va": "0x%08x" % va,
        **name_record(names, va),
        "size": representative["size"],
        "relocation_count": representative["relocation_count"],
        "representative_index": 0,
        "ambiguity": ambiguity,
        "matches": candidates,
    }
    if ambiguity:
        row["ambiguity_reasons"] = sorted(
            (["multiple_archive_sections"] if len(owners) > 1 else []) +
            (["candidate_matches_multiple_firmware_vas"] if any(
                len(item["firmware_hits"]) > 1 for item in candidates) else []))
    if resolution is not None:
        row["resolution"] = resolution
    return row


def pinned_family(family, entries, alternatives, firmware, names):
    archive = ARCHIVES[family]
    rows = []
    for va, member, section in entries:
        specs = [(member, section)] + alternatives.get(va, [])
        matches = []
        for candidate_member, candidate_section in specs:
            candidate = section_candidate(archive, candidate_member, candidate_section)
            if not exact_at(candidate, firmware, va):
                raise ValueError("normalized mismatch: %s 0x%08x %s(%s)" %
                                 (family, va, candidate_member, candidate_section))
            matches.append(public_candidate(candidate, [va]))
        resolution = None
        if va == 0x75C2C:
            resolution = {
                "readable_name": "asinf",
                "archive_member": "lib_a-wf_asin.o",
                "method": "direct_call_target_disambiguation",
                "evidence": "the wrapper call at 0x00075c36 targets __ieee754_asinf at 0x00075f88",
            }
        rows.append(make_row(va, matches, names, resolution))
    return rows


def libc_rows(firmware, names):
    archive = ARCHIVES["libc_nano"]
    by_va = {}
    for member in member_names(archive):
        obj = member_bytes(archive, member)
        elf = ELFFile(io.BytesIO(obj))
        for section in sorted((item.name for item in elf.iter_sections()
                               if item.name == ".text" or item.name.startswith(".text."))):
            candidate = section_candidate(archive, member, section, obj)
            if candidate["size"] < 8:
                continue
            hits = firmware_hits(candidate, firmware)
            if not hits:
                continue
            public = public_candidate(candidate, hits)
            for va in hits:
                by_va.setdefault(va, []).append(public)
    return [make_row(va, candidates, names)
            for va, candidates in sorted(by_va.items())]


def family_record(family, rows, method):
    representative_members = {
        row["matches"][row["representative_index"]]["archive_member"] for row in rows
    }
    candidate_members = {
        match["archive_member"] for row in rows for match in row["matches"]
    }
    return {
        "family": family,
        "archive": str(ARCHIVES[family]),
        "archive_sha256": ARCHIVE_SHA256[family],
        "scan_method": method,
        "functions": rows,
        "summary": {
            "vas": len(rows),
            "representative_bytes": sum(row["size"] for row in rows),
            "archive_members": len(representative_members),
            "candidate_archive_members": len(candidate_members),
            "relocation_sites": sum(row["relocation_count"] for row in rows),
            "ambiguous_vas": sum(row["ambiguity"] for row in rows),
        },
    }


def build():
    for family, archive in ARCHIVES.items():
        if sha256_file(archive) != ARCHIVE_SHA256[family]:
            raise ValueError("%s archive drift" % family)
    if sha256_file(NANO_SPECS) != NANO_SPECS_SHA256:
        raise ValueError("nano.specs drift")
    firmware = IMAGE.read_bytes()
    names = json.loads(NAMES.read_text())["by_address"]
    archives = [
        family_record("libc_nano", libc_rows(firmware, names),
                      "whole executable relocation-normalized section scan"),
        family_record("libm_nano", pinned_family(
            "libm_nano", LIBM, LIBM_ALTERNATIVES, firmware, names),
            "complete sweep pinned by exact section and firmware VA"),
        family_record("libgcc", pinned_family(
            "libgcc", LIBGCC, {}, firmware, names),
            "complete sweep pinned by exact section and firmware VA"),
    ]
    summaries = [item["summary"] for item in archives]
    return {
        "schema": 1,
        "core": "app",
        "status": "evidence_only",
        "decision": "record_exact_toolchain_matches_no_adoption",
        "policy": {
            "bulk_adoption": False,
            "exclude_reconstructions": False,
            "retain_recovered_c_as_evidence": True,
            "sdc_remains_report_only": True,
            "default_on_ambiguity": "retain_reconstruction",
        },
        "environment": {
            "sdk_label": "0.16.5-1",
            "sdk_equivalent_labels": ["0.16.3", "0.16.4", "0.16.5", "0.16.5-1"],
            "gcc_version": "12.2.0",
            "gcc_commit": "db5fcf3eadd09e69d59d068098854e4666c3b863",
            "newlib_release": "3.3.0",
            "newlib_commit": "4e150303bcc1e44f4d90f3489a4417433980d5ff",
            "multilib": MULTILIB,
            "nano_specs": {"path": str(NANO_SPECS), "sha256": NANO_SPECS_SHA256},
            "firmware_scan": {"image": str(IMAGE), "va_start": "0x%08x" % VA_START,
                              "va_end": "0x%08x" % VA_END},
        },
        "archives": archives,
        "summary": {
            "vas": sum(item["vas"] for item in summaries),
            "representative_bytes": sum(item["representative_bytes"] for item in summaries),
            "relocation_sites": sum(item["relocation_sites"] for item in summaries),
            "ambiguous_vas": sum(item["ambiguous_vas"] for item in summaries),
        },
    }


def render(receipt):
    return json.dumps(receipt, indent=1) + "\n"


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    rendered = render(build())
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != rendered:
            raise SystemExit("toolchain exact-match receipt is stale")
        print("toolchain exact-match receipt is current")
    else:
        OUTPUT.write_text(rendered)
        print("wrote %s" % OUTPUT)


if __name__ == "__main__":
    main()
