#!/usr/bin/env python3
"""Promote only retain-all-proven public CPUAPP SDK/runtime owners.

The broader SDK residue catalog remains report-first.  This narrow catalog is
the machine authority for public exports: every promoted VA must have a unique
reversible name, a public archive member, a pinned config/ABI gate, and the
expected owner selected in an actual retain-all GNU ld map.
"""

import argparse
import hashlib
import json
import os
import re


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_RESIDUE = os.path.join(ROOT, "recon/catalogs/app_sdk_residue_ownership.json")
DEFAULT_NAMES = os.path.join(ROOT, "recon/catalogs/function_names_app.json")
DEFAULT_MAP = "/private/tmp/g1_cpuapp_sdk_public_0717b/zephyr/zephyr_pre0.map"
DEFAULT_OUTPUT = os.path.join(ROOT, "recon/catalogs/app_sdk_public_ownership.json")

ABI_REVIEWS = {
    "ipc_service_send": {
        "prototype": "int(struct ipc_ept *, const void *, size_t)",
        "gate": "three AAPCS words; caller passes endpoint, data, length",
    },
    "bt_att_get_mtu": {
        "prototype": "uint16_t(struct bt_conn *)",
        "gate": "one pointer argument; uint16_t result is consumed narrowed",
    },
    "z_impl_k_timer_start": {
        "prototype": "void(struct k_timer *, k_timeout_t, k_timeout_t)",
        "gate": ("timer in r0; duration aligned in r2:r3; period in the first "
                 "two stack words, matching firmware callers"),
    },
}


def load(path):
    with open(path, encoding="utf-8") as stream:
        return json.load(stream)


def sha256(path):
    digest = hashlib.sha256()
    with open(path, "rb") as stream:
        for block in iter(lambda: stream.read(1 << 16), b""):
            digest.update(block)
    return digest.hexdigest()


def map_owners(path):
    """Return public symbol -> selected input from a GNU ld map."""
    with open(path, encoding="utf-8", errors="replace") as stream:
        lines = stream.read().splitlines()
    owners = {}
    pending = None
    for line in lines:
        section = re.match(r"\s*\.text\.(\S+)\s*$", line)
        if section:
            pending = section.group(1)
            continue
        if pending:
            owner = re.match(r"\s*0x[0-9a-fA-F]+\s+0x[0-9a-fA-F]+\s+(.+)$", line)
            if owner:
                # Link maps can list an unselected weak fallback after the
                # selected strong implementation.  The first loaded input is
                # the authoritative owner for this symbol.
                owners.setdefault(pending, owner.group(1).strip())
                pending = None
            elif line.strip() and not line.startswith(" "):
                pending = None
    # Runtime objects commonly use a plain .text input section.
    for index, line in enumerate(lines):
        symbol = re.match(r"\s*0x[0-9a-fA-F]+\s+([A-Za-z_$][\w$]*)\s*$", line)
        if not symbol or symbol.group(1) in owners:
            continue
        for previous in reversed(lines[max(0, index - 3):index]):
            owner = re.match(r"\s*\.text(?:\.\S+)?\s+0x[0-9a-fA-F]+\s+"
                             r"0x[0-9a-fA-F]+\s+(.+)$", previous)
            if owner:
                owners.setdefault(symbol.group(1), owner.group(1).strip())
                break
    return owners


def member_matches(owner, member):
    return bool(owner and member and
                (owner.endswith("(%s)" % member) or
                 ("(%s)" % member) in owner))


def build(residue_path, names_path, map_path):
    residue = load(residue_path)
    names = load(names_path)
    owners = map_owners(map_path)
    address_by_name = names.get("by_name", {})
    rows = []
    candidates = [row for row in residue["entries"]
                  if row.get("safe_automatic_link_owner") or
                  row["symbol"] == "z_log_dropped_read_and_clear_0"]
    for source in candidates:
        identities = source.get("firmware_identities", [])
        va = identities[0] if len(identities) == 1 else None
        symbol = source["semantic_owner"]
        export = source.get("archive_evidence") or {}
        owner = owners.get(symbol)
        exact = source.get("signature_ratio") == 1.0
        direct = source.get("adoption_evidence_gate") == "direct_symbol_and_archive_export"
        abi_review = ABI_REVIEWS.get(symbol)
        abi_ok = exact or (abi_review is not None) or direct
        mapped_va = address_by_name.get(symbol)
        competing_va = mapped_va if mapped_va and mapped_va != va else None
        blockers = []
        if not source.get("safe_automatic_link_owner"):
            blockers.append("source_catalog_not_public_safe")
        if not va:
            blockers.append("non_unique_firmware_identity")
        if export.get("linkage") != "public" or not str(export.get("nm_type", "")).isupper():
            blockers.append("not_a_public_export")
        if not source.get("owning_config"):
            blockers.append("missing_pinned_config")
        if not abi_ok:
            blockers.append("approximate_signature_without_abi_gate")
        if mapped_va != va:
            blockers.append("reversible_name_not_owned_by_firmware_va")
        if competing_va:
            blockers.append("public_name_owned_by_distinct_firmware_va")
        if not member_matches(owner, export.get("member")):
            blockers.append("retain_all_selected_owner_missing_or_wrong")
        safe = not blockers
        rows.append({
            "core": "app", "va": va, "raw_symbol": source["symbol"],
            "upstream_symbol": symbol,
            "upstream_member": export.get("member"),
            "upstream_archive": export.get("archive"),
            "selected_link_owner": owner,
            "signature_ratio": source.get("signature_ratio"),
            "signature_gate": source.get("adoption_evidence_gate"),
            "abi": abi_review or {"gate": "exact/direct public identity"},
            "required_config": source.get("owning_config", []),
            "competing_firmware_va": competing_va,
            "exclude_reconstruction": safe,
            "safe_to_adopt": safe,
            "blockers": blockers,
            "reference_count": source.get("reference_count", 0),
        })
    rows.sort(key=lambda row: (row["va"] or "", row["raw_symbol"]))
    return {
        "schema": 1,
        "core": "app",
        "policy": {
            "default_on_ambiguity": "retain_reconstruction",
            "public_export_required": True,
            "retain_all_selected_owner_required": True,
            "approximate_signature_requires_abi_review": True,
            "canonical_sources_mutated": False,
        },
        "inputs": {
            "residue": os.path.relpath(residue_path, ROOT),
            "residue_sha256": sha256(residue_path),
            "names": os.path.relpath(names_path, ROOT),
            "names_sha256": sha256(names_path),
            "retain_all_map": map_path,
            "retain_all_map_sha256": sha256(map_path),
            "pinned_environment": residue["pinned_environment"],
        },
        "summary": {
            "candidates": len(rows),
            "adopted": sum(row["safe_to_adopt"] for row in rows),
            "retained_fail_closed": sum(not row["safe_to_adopt"] for row in rows),
            "resolved_reference_count": sum(row["reference_count"]
                                            for row in rows if row["safe_to_adopt"]),
        },
        "functions": rows,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--residue", default=DEFAULT_RESIDUE)
    parser.add_argument("--names", default=DEFAULT_NAMES)
    parser.add_argument("--map", default=DEFAULT_MAP)
    parser.add_argument("--output", default=DEFAULT_OUTPUT)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build(args.residue, args.names, args.map)
    rendered = json.dumps(data, indent=1) + "\n"
    if args.check:
        if not os.path.exists(args.output) or open(args.output).read() != rendered:
            raise SystemExit("app SDK public ownership catalog is stale")
    else:
        with open(args.output, "w") as stream:
            stream.write(rendered)
    print(json.dumps(data["summary"], sort_keys=True))


if __name__ == "__main__":
    main()
