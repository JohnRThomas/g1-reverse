#!/usr/bin/env python3
"""Audit SDC adoption at archive-member (linker object) granularity.

The SoftDevice Controller archive shipped with NCS 2.5.1 contains one large
relocatable ELF member.  A signature match to one section is not evidence that
the complete member can replace reconstructed firmware owners.  This tool
therefore fails closed unless executable ownership, private ABI ownership,
allocated data/state ownership, collision freedom, and a retain-all link are
all complete for the *whole member*.

It only writes an evidence catalog and report.  It never edits canonical
sources, source-selection lists, aliases, or the adoption manifest.

Run from outside the repository because the historical local ``struct.py``
shadows the standard library::

  cd /tmp
  PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
    /Users/freedomcoder/Projects/G1disasm2/tools/build_sdc_member_adoption_catalog.py
"""
import argparse
import collections
import hashlib
import io
import json
import os
import subprocess

from elftools.elf.elffile import ELFFile


ROOT = "/Users/freedomcoder/Projects/G1disasm2"
NCS = "/Users/freedomcoder/ncs251"
ARCHIVE_REL = ("nrfxlib/softdevice_controller/lib/cortex-m33+nodsp/soft-float/"
               "libsoftdevice_controller_multirole.a")
ARCHIVE = os.path.join(NCS, ARCHIVE_REL)
MEMBER = "libsoftdevice_controller_s140_debug_soft__obfuscated.elf"
AR = ("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
      "arm-zephyr-eabi-ar")
OWNERSHIP = os.path.join(ROOT, "recon/ownership/net_sdc_archive_ownership.json")
RESIDUE = os.path.join(ROOT, "recon/catalogs/net_link_function_residue.json")
EXTRACTION = os.path.join(ROOT, "recon/ownership/net_sdc_build_extraction.json")
OUTPUT = os.path.join(ROOT, "recon/ownership/net_sdc_member_adoption.json")
REPORT = os.path.join(ROOT, "recon/ownership/net_sdc_member_adoption.md")
EXPECTED_ARCHIVE_SHA256 = "f218b3dc4badd8f534f4aa00db678f54a1d4795d7d39721f28401fb49e880e81"


def sha256_bytes(data):
    return hashlib.sha256(data).hexdigest()


def sha256_file(path):
    digest = hashlib.sha256()
    with open(path, "rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def load_json(path):
    with open(path) as stream:
        return json.load(stream)


def archive_members(path=ARCHIVE):
    output = subprocess.check_output([AR, "t", path], text=True)
    return [line.strip() for line in output.splitlines() if line.strip()]


def member_elf(path=ARCHIVE, member=MEMBER):
    payload = subprocess.check_output([AR, "p", path, member])
    return payload, ELFFile(io.BytesIO(payload))


def inspect_member(elf):
    """Return durable whole-member code, state, import, and relocation counts."""
    symtab = elf.get_section_by_name(".symtab")
    if symtab is None:
        raise ValueError("archive member has no symbol table")

    executable = [section for section in elf.iter_sections()
                  if int(section["sh_flags"]) & 0x2 and
                  int(section["sh_flags"]) & 0x4]
    allocated_data = [section for section in elf.iter_sections()
                      if int(section["sh_flags"]) & 0x2 and
                      not int(section["sh_flags"]) & 0x4 and
                      section["sh_type"] in ("SHT_PROGBITS", "SHT_NOBITS")]
    relocations = [section for section in elf.iter_sections()
                   if section["sh_type"] in ("SHT_REL", "SHT_RELA")]

    functions = []
    objects = []
    undefined = set()
    for symbol in symtab.iter_symbols():
        defined = isinstance(symbol["st_shndx"], int)
        if not defined and symbol.name and symbol["st_shndx"] == "SHN_UNDEF":
            undefined.add(symbol.name)
        if not defined or not symbol.name:
            continue
        row = {
            "name": symbol.name,
            "binding": symbol["st_info"]["bind"],
            "visibility": symbol["st_other"]["visibility"],
            "size": int(symbol["st_size"]),
        }
        if symbol["st_info"]["type"] == "STT_FUNC":
            functions.append(row)
        elif symbol["st_info"]["type"] == "STT_OBJECT":
            objects.append(row)

    return {
        "elf_type": elf.header["e_type"],
        "machine": elf.header["e_machine"],
        "section_count": elf.num_sections(),
        "executable_sections": len(executable),
        "executable_bytes": sum(int(section["sh_size"]) for section in executable),
        "defined_functions": len(functions),
        "global_functions": sum(row["binding"] == "STB_GLOBAL" for row in functions),
        "local_functions": sum(row["binding"] == "STB_LOCAL" for row in functions),
        "public_sdc_named_functions": sum(row["name"].startswith("sdc_")
                                          for row in functions),
        "obfuscated_sym_functions": sum(row["name"].startswith("sym_")
                                        for row in functions),
        "allocated_data_sections": len(allocated_data),
        "allocated_data_bytes": sum(int(section["sh_size"])
                                    for section in allocated_data),
        "defined_object_symbols": len(objects),
        "defined_object_bytes": sum(row["size"] for row in objects),
        "relocation_sections": len(relocations),
        "relocations": sum(section.num_relocations() for section in relocations),
        "undefined_imports": len(undefined),
        "undefined_import_names": sorted(undefined),
    }


def evaluate_member(member_stats, matched_rows, target_rows, extraction,
                    data_owner_mappings=0, retain_all_proof=None):
    """Apply the fail-closed complete-object adoption gate.

    This pure decision function is intentionally easy to mutation-test.  A
    member is promotable only when all of its code and state are accounted for,
    every target is mapped, no private ABI remains unpublished, and a durable
    retain-all build proves collision-free ownership.
    """
    retain_all_proof = retain_all_proof or {}
    exact_unique = [row for row in matched_rows
                    if row.get("match_kind") == "exact" and
                    row.get("unique_identity") is True]
    unpublished = [row for row in matched_rows
                   if row.get("abi_status") == "private_unpublished"]
    abi_accounted = [row for row in matched_rows
                     if row.get("abi_status") and
                     row.get("abi_status") != "private_unpublished"]
    matched_addresses = {row["address"] for row in matched_rows}
    target_addresses = {row["va"] for row in target_rows}

    gates = {
        "archive_hash_pinned": extraction.get("archive", {}).get("sha256") ==
                               EXPECTED_ARCHIVE_SHA256,
        "member_selected_by_link": extraction.get("archive", {}).get(
                                   "selected_by_link") is True,
        "every_target_residue_mapped": target_addresses <= matched_addresses,
        "every_executable_owner_exact_unique":
            len(exact_unique) == member_stats["defined_functions"] and
            member_stats["executable_sections"] == member_stats["defined_functions"],
        "every_private_abi_accounted":
            len(abi_accounted) == member_stats["defined_functions"],
        "every_allocated_data_section_owned":
            data_owner_mappings == member_stats["allocated_data_sections"],
        "retain_all_link_completed": retain_all_proof.get("build_completed") is True,
        "retain_all_collision_free": retain_all_proof.get("collision_free") is True,
        "retain_all_hidden_state_preserved":
            retain_all_proof.get("hidden_state_preserved") is True,
    }
    blockers = [name for name, passed in gates.items() if not passed]
    return {
        "gates": gates,
        "blockers": blockers,
        "safe_to_adopt_complete_member": not blockers,
        "decision": ("adopt_complete_archive_member" if not blockers else
                     "report_only_no_member_promotion"),
        "coverage": {
            "catalog_matches": len(matched_rows),
            "exact_unique_executable_owners": len(exact_unique),
            "defined_functions": member_stats["defined_functions"],
            "target_residue_total": len(target_addresses),
            "target_residue_mapped": len(target_addresses & matched_addresses),
            "private_unpublished_abis": len(unpublished),
            "explicit_abi_owners": len(abi_accounted),
            "allocated_data_sections": member_stats["allocated_data_sections"],
            "allocated_data_owner_mappings": data_owner_mappings,
        },
    }


def build_catalog(archive=ARCHIVE, ownership_path=OWNERSHIP,
                  residue_path=RESIDUE, extraction_path=EXTRACTION):
    digest = sha256_file(archive)
    if digest != EXPECTED_ARCHIVE_SHA256:
        raise ValueError("unexpected SDC archive SHA-256: %s" % digest)
    members = archive_members(archive)
    if members != [MEMBER]:
        raise ValueError("expected exactly the pinned SDC ELF member, got %r" % members)

    payload, elf = member_elf(archive, MEMBER)
    stats = inspect_member(elf)
    ownership = load_json(ownership_path)
    residue = load_json(residue_path)
    extraction = load_json(extraction_path)
    matched_rows = [row for row in ownership.get("functions", [])
                    if row.get("best", {}).get("archive_member") == MEMBER]
    target_rows = [row for row in residue.get("entries", [])
                   if row.get("category") == "true_missing_reconstructed_entry" and
                   row.get("adoption_component") == "softdevice_controller"]

    # No committed artifact currently claims a complete state map or a
    # collision-free retain-all link for this member.  The older extraction
    # proof is intentionally scoped to one public API and a normal-GC link.
    decision = evaluate_member(stats, matched_rows, target_rows, extraction)
    target_matches = {row["address"]: row for row in matched_rows}
    target_summary = collections.Counter()
    for target in target_rows:
        match = target_matches.get(target["va"])
        if match is None:
            target_summary["unmatched"] += 1
        else:
            target_summary[match["match_kind"]] += 1
            if match.get("unique_identity"):
                target_summary["unique_identity"] += 1
            if match.get("abi_status") == "private_unpublished":
                target_summary["private_unpublished_abi"] += 1
    unmatched_targets = [{"address": row["va"], "symbol": row["symbol"]}
                         for row in target_rows if row["va"] not in target_matches]

    return {
        "schema_version": 1,
        "core": "net",
        "component": "softdevice_controller",
        "scope": "complete archive-member adoption; no per-function extraction",
        "policy": {
            "unit_of_adoption": "archive_member_object",
            "private_symbol_extraction_forbidden": True,
            "per_function_private_sdc_removal_forbidden": True,
            "canonical_semantics_mutated": False,
            "default": "report_only_no_member_promotion",
        },
        "inputs": [
            {"path": ARCHIVE_REL, "sha256": digest},
            {"path": os.path.relpath(ownership_path, ROOT),
             "sha256": sha256_file(ownership_path)},
            {"path": os.path.relpath(residue_path, ROOT),
             "sha256": sha256_file(residue_path)},
            {"path": os.path.relpath(extraction_path, ROOT),
             "sha256": sha256_file(extraction_path)},
        ],
        "summary": {
            "archive_members": len(members),
            "candidate_members": 1,
            "safe_members": int(decision["safe_to_adopt_complete_member"]),
            "promoted_members": 0,
            "target_residue_total": len(target_rows),
            "target_residue_matched": len(target_rows) - target_summary["unmatched"],
            "target_residue_unmatched": target_summary["unmatched"],
            "target_exact_matches": target_summary["exact"],
            "target_approximate_matches": target_summary["approximate"],
            "target_unique_identities": target_summary["unique_identity"],
            "target_private_unpublished_abis": target_summary["private_unpublished_abi"],
            "target_ambiguous_identities":
                summary_ambiguous(target_rows, target_matches),
        },
        "target_residue_evidence": {
            "source": os.path.relpath(residue_path, ROOT),
            "per_address_match_source": os.path.relpath(ownership_path, ROOT),
            "unmatched": unmatched_targets,
            "note": ("The existing per-address catalog remains authoritative for all 131 "
                     "matched rows; this catalog evaluates only the complete linker member."),
        },
        "members": [{
            "archive_member": MEMBER,
            "member_sha256": sha256_bytes(payload),
            "member_size": len(payload),
            "stats": stats,
            "decision": decision,
            "retain_all_evidence": {
                "available": False,
                "reason": ("The committed extraction proof selects this member but is scoped "
                           "to sdc_default_tx_power_set and a normal-GC final link; it does "
                           "not prove complete-member collision or state ownership."),
            },
            "state_ownership_evidence": {
                "mapped_allocated_data_sections": 0,
                "reason": ("No committed member-section to firmware data/state map accounts "
                           "for all allocated .data/.bss/.rodata sections."),
            },
            "promotion": None,
        }],
    }


def render_markdown(catalog):
    summary = catalog["summary"]
    member = catalog["members"][0]
    stats = member["stats"]
    decision = member["decision"]
    coverage = decision["coverage"]
    lines = [
        "# SoftDevice Controller whole-member adoption audit",
        "",
        "Generated by `tools/build_sdc_member_adoption_catalog.py`; JSON is authoritative.",
        "The audit treats the linker-extracted ELF member as the smallest allowed private-SDC",
        "adoption unit. It does not authorize private function extraction or aliases.",
        "",
        "## Result",
        "",
        "**No complete archive member is safe to promote. All private SDC rows remain report-only.**",
        "",
        "| Measure | Count |",
        "|---|---:|",
        "| Archive members | %d |" % summary["archive_members"],
        "| Defined functions in the sole member | %d |" % stats["defined_functions"],
        "| Executable sections | %d |" % stats["executable_sections"],
        "| Exact unique executable owners | %d |" % coverage["exact_unique_executable_owners"],
        "| Allocated data/state sections | %d |" % stats["allocated_data_sections"],
        "| Mapped allocated data/state sections | %d |" % coverage["allocated_data_owner_mappings"],
        "| Target private-SDC residue | %d |" % summary["target_residue_total"],
        "| Target residue matched by signature | %d |" % summary["target_residue_matched"],
        "| Target residue with unpublished private ABI | %d |" %
            summary["target_private_unpublished_abis"],
        "| Target residue with ambiguous identity | %d |" %
            summary["target_ambiguous_identities"],
        "| Safe/promoted members | %d / %d |" %
            (summary["safe_members"], summary["promoted_members"]),
        "",
        "## Fail-closed blockers",
        "",
    ]
    for blocker in decision["blockers"]:
        lines.append("- `%s`" % blocker)
    lines.extend([
        "",
        "The member contains %d executable sections (%d bytes), %d allocated data/state "
        "sections (%d bytes), %d relocations, and %d imports. Existing signature evidence "
        "covers only part of that object and publishes no ABI for the %d matched private "
        "target functions. One of the %d target residue entries is not matched at all." % (
            stats["executable_sections"], stats["executable_bytes"],
            stats["allocated_data_sections"], stats["allocated_data_bytes"],
            stats["relocations"], stats["undefined_imports"],
            summary["target_private_unpublished_abis"], summary["target_residue_total"]),
        "",
        "The earlier `net_sdc_build_extraction.json` proves selection of this exact member for",
        "one public API. It is not a complete-member retain-all proof, and therefore cannot",
        "justify removing or aliasing private reconstructed owners.",
        "",
    ])
    return "\n".join(lines)


def summary_ambiguous(target_rows, matches):
    return sum(matches.get(row["va"]) is not None and
               matches[row["va"]].get("unique_identity") is not True
               for row in target_rows)


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("--output", default=OUTPUT)
    parser.add_argument("--report", default=REPORT)
    parser.add_argument("--check", action="store_true",
                        help="verify generated files are current without writing")
    args = parser.parse_args(argv)
    catalog = build_catalog()
    encoded = json.dumps(catalog, indent=2, sort_keys=True) + "\n"
    report = render_markdown(catalog)
    if args.check:
        if open(args.output).read() != encoded or open(args.report).read() != report:
            raise SystemExit("SDC member adoption catalogs are stale")
    else:
        with open(args.output, "w") as stream:
            stream.write(encoded)
        with open(args.report, "w") as stream:
            stream.write(report)
    print("SDC member adoption: %d safe, %d promoted; %d blockers" % (
        catalog["summary"]["safe_members"], catalog["summary"]["promoted_members"],
        len(catalog["members"][0]["decision"]["blockers"])))


if __name__ == "__main__":
    main()
