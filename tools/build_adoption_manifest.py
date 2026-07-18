#!/usr/bin/env python3
"""Build the fail-closed upstream adoption/exclusion manifest.

This tool does not edit reconstruction sources or build files.  It turns the
reviewed ownership catalogs into deterministic address-keyed decisions for a
later CMake/source-selection pass.  An ownership claim and permission to omit a
reconstruction are deliberately separate fields.
"""

import argparse
import copy
import hashlib
import json
import os
import re
import subprocess
import sys

from elftools.elf.elffile import ELFFile


BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULTS = {
    "baseline": "recon/ownership/adoption_manifest_baseline.json",
    "lc3": "recon/catalogs/lc3_ownership_app.json",
    "app_lc3_stock":
        "recon/ownership/app_lc3_stock_atomic_adoption.json",
    "tinycrypt": "recon/analysis/tinycrypt_pinned_matches.json",
    "cc312": "recon/catalogs/cc312_archive_ownership.json",
    "crypto": "recon/catalogs/upstream_crypto_ownership.json",
    "app_collisions": "recon/ownership/app_build_collision_ownership.json",
    "app_collision_authorizations":
        "recon/ownership/app_collision_adoption_authorizations.json",
    "app_kernel_config":
        "recon/ownership/app_kernel_config_atomic_adoption.json",
    "app_nrfx_stock":
        "recon/ownership/app_nrfx_stock_atomic_adoption.json",
    "app_bluetooth_stock":
        "recon/ownership/app_bluetooth_stock_atomic_adoption.json",
    "app_settings_stock":
        "recon/ownership/app_settings_stock_atomic_adoption.json",
    "app_mcumgr_stock":
        "recon/ownership/app_mcumgr_stock_atomic_adoption.json",
    "app_lseek_stream_flash":
        "recon/ownership/app_lseek_stream_flash_atomic_adoption.json",
    "app_root_stock":
        "recon/ownership/app_root_stock_atomic_adoption.json",
    "app_img_mgmt_stock":
        "recon/ownership/app_img_mgmt_stock_atomic_adoption.json",
    "app_collision_retention_overrides":
        "recon/ownership/app_collision_retention_overrides.json",
    "library_provenance":
        "recon/catalogs/upstream_library_provenance.json",
    "app_sdk_public": "recon/catalogs/app_sdk_public_ownership.json",
    "net": "recon/ownership/net_function_ownership.json",
    "net_rtc": "recon/catalogs/net_rtc_timer_ownership.json",
    "net_sdk_public": "recon/catalogs/net_sdk_public_ownership.json",
    "net_openamp_stock":
        "recon/ownership/net_openamp_stock_atomic_adoption.json",
    "net_ipc_rpmsg_variant":
        "recon/ownership/net_ipc_rpmsg_variant_ownership.json",
    "net_zephyr_stock":
        "recon/ownership/net_zephyr_stock_atomic_adoption.json",
    "net_alias_resolutions": "recon/catalogs/net_identity_alias_resolutions.json",
    "sdc_benchmark": "recon/ownership/net_sdc_archive_benchmark.md",
    "sdc_catalog": "recon/ownership/net_sdc_archive_ownership.json",
    "app_names": "recon/catalogs/function_names_app.json",
    "net_names": "recon/catalogs/function_names_net.json",
    "output": "recon/ownership/adoption_manifest.json",
}
BASELINE_PROVENANCE = {
    "commit": "7bdee73e",
    "path": "recon/ownership/adoption_manifest.json",
    "sha256": "8012a14b16b6ddd0671cebe93b875629a861c19586e6cb842212c41ed2fcbbbc",
}
KINDS = ("source", "archive", "static_helper", "table", "glue")
KIND_RANK = {"source": 1, "archive": 2, "table": 3,
             "static_helper": 4, "glue": 5}
AR = ("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
      "arm-zephyr-eabi-ar")


def _path(value):
    return value if os.path.isabs(value) else os.path.join(BASE, value)


def _relative(path):
    path = os.path.abspath(path)
    try:
        return os.path.relpath(path, BASE)
    except ValueError:
        return path


def _load_json(path):
    with open(path) as stream:
        return json.load(stream)


def _sha256(path):
    digest = hashlib.sha256()
    with open(path, "rb") as stream:
        for block in iter(lambda: stream.read(1 << 16), b""):
            digest.update(block)
    return digest.hexdigest()


def _archive_member_sha256(archive, member):
    content = subprocess.check_output([AR, "p", archive, member])
    return hashlib.sha256(content).hexdigest()


def _alloc_content_sha256(path):
    """Hash linked content while ignoring volatile ELF debug/build metadata."""
    digest = hashlib.sha256()
    with open(path, "rb") as stream:
        elf = ELFFile(stream)
        for section in elf.iter_sections():
            if (int(section["sh_flags"]) & 0x2 and
                    section["sh_type"] != "SHT_NOBITS"):
                digest.update(section.name.encode("utf-8") + b"\0")
                digest.update(section.data())
    return digest.hexdigest()


def _json_sha256(value):
    encoded = json.dumps(value, sort_keys=True,
                         separators=(",", ":")).encode("utf-8")
    return hashlib.sha256(encoded).hexdigest()


def _kconfig_values(path):
    """Return exact assignments from a generated Zephyr ``.config``."""
    values = {}
    with open(path, encoding="utf-8") as stream:
        for line in stream:
            line = line.strip()
            match = re.match(r"^(CONFIG_[A-Za-z0-9_]+)=(.*)$", line)
            if match:
                values[match.group(1)] = match.group(2)
                continue
            match = re.match(r"^# (CONFIG_[A-Za-z0-9_]+) is not set$", line)
            if match:
                values[match.group(1)] = "n"
    return values


def _address(value):
    return (int(value, 0) if isinstance(value, str) else int(value)) & ~1


def _hex(value):
    return "0x%08x" % _address(value)


def _raw(core, address):
    return "FUN_%08x" % (_address(address),)


def _name_records(path):
    data = _load_json(path)
    return {int(address, 16): record
            for address, record in data.get("by_address", {}).items()}


def _identity(core, address, names):
    value = _address(address)
    record = names[core].get(value, {})
    return record.get("raw_name", _raw(core, value)), record.get(
        "name", record.get("raw_name", _raw(core, value)))


def _evidence(source, evidence_type, **values):
    item = {"source": source, "type": evidence_type}
    item.update({key: value for key, value in values.items()
                 if value is not None})
    return item


def _entry(core, address, names, kind, component, upstream_symbol=None,
           upstream_unit=None, exclude=False, reason=None, evidence=None,
           confidence=None):
    raw, current = _identity(core, address, names)
    return {
        "core": core,
        "va": _hex(address),
        "raw_symbol": raw,
        "current_symbol": current,
        "kind": kind,
        "component": component,
        "upstream_symbol": upstream_symbol,
        "upstream_unit": upstream_unit,
        "confidence": confidence,
        "exclude_reconstruction": bool(exclude),
        "decision": ("adopt_upstream_exclude_reconstruction" if exclude else
                     "retain_reconstruction"),
        "decision_reason": reason or "No explicit exclusion evidence.",
        "evidence": list(evidence or []),
    }


def _merge(entries, candidate):
    """Merge by core+VA, with any retain decision winning fail-closed."""
    key = (candidate["core"], candidate["va"])
    previous = entries.get(key)
    if previous is None:
        entries[key] = candidate
        return
    if KIND_RANK[candidate["kind"]] > KIND_RANK[previous["kind"]]:
        previous["kind"] = candidate["kind"]
    previous["evidence"].extend(candidate["evidence"])
    previous["evidence"] = sorted(
        {json.dumps(item, sort_keys=True): item
         for item in previous["evidence"]}.values(),
        key=lambda item: (item["source"], item["type"],
                          json.dumps(item, sort_keys=True)))
    if not candidate["exclude_reconstruction"]:
        previous["exclude_reconstruction"] = False
        previous["decision"] = "retain_reconstruction"
        previous["decision_reason"] = candidate["decision_reason"]
    for field in ("upstream_symbol", "upstream_unit", "confidence"):
        if not previous.get(field) and candidate.get(field):
            previous[field] = candidate[field]


def _lc3_entries(data, source, names):
    output = []
    commit = data.get("upstream", {}).get("commit")
    for row in data.get("functions", []):
        upstream = row.get("upstream_function")
        kind = "source" if upstream and upstream.startswith("lc3_") else "static_helper"
        eligible = bool(
            row.get("confidence") == "high" and
            str(row.get("proof_status", "")).startswith(
                "relocation_masked_configured_object"))
        output.append(_entry(
            "app", row["address"], names, kind, "liblc3", upstream,
            row.get("upstream_file"), eligible,
            ("Pinned libLC3 source ownership has explicit configured-object "
             "exact evidence." if eligible else
             "LC3 identity evidence lacks configured-object exact replacement "
             "authority; retain fail-closed."),
            [_evidence(source, "lc3_function_match", commit=commit,
                       match_score=row.get("match_score"),
                       proof_status=row.get("proof_status"))],
            row.get("confidence")))
    for row in data.get("tables", []):
        output.append(_entry(
            "app", row["address"], names, "table", "liblc3", row["name"],
            row.get("upstream_file"), True,
            "Pinned libLC3 table identity is explicitly recorded by address.",
            [_evidence(source, "lc3_table_identity", commit=commit)], "high"))
    return output


def _tinycrypt_entries(data, source, names):
    output = []
    commit = data.get("upstream", {}).get("commit")
    for row in data.get("matches", []):
        kind = "static_helper" if row.get("linkage") == "file_static" else "source"
        replacement = row.get("replacement")
        eligible = replacement in ("direct_pinned_source", "compile_source_unit")
        output.append(_entry(
            "app", row["address"], names, kind, "tinycrypt", row.get("symbol"),
            row.get("source"), eligible,
            ("Pinned TinyCrypt match has an explicit source-unit replacement."
             if eligible else "TinyCrypt evidence does not authorize replacement."),
            [_evidence(source, "tinycrypt_pinned_match", commit=commit,
                       rank_score=row.get("rank_score"), gap=row.get("gap"),
                       replacement=replacement, linkage=row.get("linkage"))],
            "high" if eligible else "medium"))
    return output


def _member_for(address, members):
    value = _address(address)
    for member, span in sorted(members.items()):
        if int(span[0], 16) <= value < int(span[1], 16):
            return member
    return None


def _cc312_entries(data, source, names):
    summary = data.get("summary", {})
    exact = (summary.get("all_sections_relocation_normalized_exact") is True and
             summary.get("gaps_or_firmware_glue_inside_span") == 0)
    start = int(summary["start"], 16)
    end = int(summary["end_exclusive"], 16)
    corrections = data.get("inventory_corrections", {})
    output = []
    for address in sorted(value for value in names["app"] if start <= value < end):
        member = _member_for(address, data.get("members", {}))
        symbol = corrections.get(_hex(address), names["app"][address].get("name"))
        output.append(_entry(
            "app", address, names, "archive", "cc312_platform", symbol, member,
            exact,
            ("The exact CC312 archive owns the complete relocation-normalized "
             "span with zero firmware-glue gaps." if exact else
             "CC312 range evidence is not exact and gap-free."),
            [_evidence(source, "relocation_normalized_archive_span",
                       archive_sha256=data.get("archive_sha256"), member=member,
                       exact=exact)], "high" if exact else "medium"))
    return output


def _crypto_entries(data, source, names):
    output = []
    for row in data.get("functions", []):
        ownership = row.get("ownership")
        kind = ownership if ownership in ("source", "archive", "glue") else "glue"
        confidence = row.get("confidence")
        # This catalog is semantic enrichment.  Source/archive entries require
        # high confidence; glue is always retained.
        eligible = kind in ("source", "archive") and confidence == "high"
        if kind == "glue":
            eligible = False
        output.append(_entry(
            row["core"], row["va"], names, kind, row.get("component", "crypto"),
            row.get("upstream_symbol"), row.get("upstream_object") or
            row.get("upstream_path"), eligible,
            ("High-confidence pinned upstream ownership." if eligible else
             "Integration glue or non-high-confidence ownership remains reconstructed."),
            [_evidence(source, "crypto_ownership", ownership=ownership,
                       confidence=confidence, evidence=row.get("evidence"))],
            confidence))
    return output


def _app_collision_entries(data, source, names, authorizations,
                           authorization_source):
    """Adopt only SDK owners proven by the retain-all CPUAPP link catalog."""
    if (authorizations.get("schema") != 1 or
            authorizations.get("core") not in (None, "app")):
        raise ValueError("invalid app collision authorization catalog")
    authorization_rows = [row for row in
                          authorizations.get("authorizations", [])
                          if row.get("status") == "authorized"]
    authorized = {_hex(row["va"]): row for row in authorization_rows}
    if len(authorized) != len(authorization_rows):
        raise ValueError("duplicate app collision authorization VA")
    collision_vas = {_hex(row["va"]) for row in data.get("functions", [])}
    hidden = {va for va, row in authorized.items()
              if row.get("hidden_owner_closure") is True}
    if not set(authorized) - hidden <= collision_vas:
        raise ValueError("authorization absent from collision catalog: %s" %
                         sorted(set(authorized) - hidden - collision_vas))
    for va in hidden:
        row = authorized[va]
        correction = row.get("identity_correction", {})
        closure = row.get("whole_unit_closure", {})
        if not (row.get("instruction_exact") is True and
                row.get("configuration_variant_exact") is True and
                row.get("normalized_code_sha256") and
                row.get("cfg_verify_cases", 0) > 0 and
                correction.get("corrected_upstream_symbol") and
                correction.get("corrected_readable_identity") and
                correction.get("upstream_linkage") in
                ("public", "translation_unit_local") and
                closure.get("safe") is True and
                not closure.get("new_undefined_symbols")):
            raise ValueError("invalid hidden exact-owner closure: %s" % va)
    output = []
    for row in data.get("functions", []):
        row_va = _hex(row["va"])
        upstream = row.get("upstream", {})
        authorization = authorized.get(row_va)
        closure = (authorization or {}).get("whole_unit_closure", {})
        atomic_group = sorted(_hex(value) for value in
                              (authorization or {}).get("atomic_group", []))
        exclude_only = sorted(_hex(value) for value in
                              closure.get("exclude_only", []))
        closure_matches = (exclude_only == [row_va] or
                           (atomic_group and exclude_only == atomic_group and
                            row_va in atomic_group))
        authorization_valid = bool(
            authorization and
            authorization.get("symbol") ==
            (row.get("current_symbol") or upstream.get("symbol")) and
            authorization.get("instruction_exact") is True and
            authorization.get("normalized_code_sha256") and
            authorization.get("cfg_verify_cases", 0) > 0 and
            closure.get("safe") is True and closure_matches and
            not closure.get("new_undefined_symbols"))
        reviewed_inflation_override = bool(
            authorization_valid and
            authorization.get("catalog_extent_inflated") is True and
            authorization.get("firmware_code_size", 0) > 0 and
            authorization.get("firmware_code_size") ==
            authorization.get("upstream_code_size"))
        configuration_variant_override = bool(
            authorization_valid and
            authorization.get("configuration_variant_exact") is True and
            authorization.get("firmware_code_size", 0) > 0 and
            authorization.get("firmware_code_size") ==
            authorization.get("upstream_code_size") and
            authorization.get("required_config"))
        identity_correction = (authorization or {}).get(
            "identity_correction", {})
        if identity_correction and not (
                identity_correction.get("baseline_collision_symbol") ==
                row.get("current_symbol") and
                identity_correction.get("corrected_upstream_symbol") and
                identity_correction.get("corrected_readable_identity") and
                identity_correction.get("upstream_linkage") in
                ("translation_unit_local", "public")):
            authorization_valid = False
            configuration_variant_override = False
        eligible = (row.get("safe_to_exclude") is True or
                    (authorization_valid and
                     ((row.get("identity_threshold_candidate") is True and
                       not row.get("exclusion_blockers")) or
                      reviewed_inflation_override or
                      configuration_variant_override)))
        source_identity = upstream.get("source", {})
        component = source_identity.get("repository") or "cpuapp_selected_sdk"
        evidence = [_evidence(
            source, "cpuapp_selected_owner_collision",
            safe_to_exclude=eligible,
            blockers=row.get("exclusion_blockers"),
            signature_match=row.get("signature_match"),
            abi=upstream.get("abi"),
            upstream_source=source_identity,
            link_provenance=row.get("link_provenance"))]
        if authorization:
            evidence.append(_evidence(
                authorization_source, "explicit_collision_adoption_authority",
                batch=authorization.get("batch"),
                instruction_exact=authorization.get("instruction_exact"),
                normalized_code_sha256=authorization.get(
                    "normalized_code_sha256"),
                cfg_verify_cases=authorization.get("cfg_verify_cases"),
                catalog_extent_inflated=authorization.get(
                    "catalog_extent_inflated"),
                ghidra_catalog_extent=authorization.get(
                    "ghidra_catalog_extent"),
                callers=authorization.get("callers"),
                configuration_variant_exact=authorization.get(
                    "configuration_variant_exact"),
                required_config=authorization.get("required_config"),
                identity_correction=authorization.get("identity_correction"),
                atomic_group=authorization.get("atomic_group"),
                whole_unit_closure=authorization.get("whole_unit_closure")))
        selected_symbol = (identity_correction.get(
            "corrected_upstream_symbol") if identity_correction else
            upstream.get("symbol"))
        selected_unit = ((authorization or {}).get("upstream_object")
                         if ((authorization or {}).get(
                             "configuration_variant_exact") or
                             identity_correction)
                         else upstream.get("object"))
        output.append(_entry(
            "app", row["va"], names, "source", component,
            selected_symbol, selected_unit, eligible,
            ("The configured CPUAPP link selected this strong owner and its "
             "DWARF ABI plus firmware instruction signature passed every "
             "fail-closed threshold." if eligible else
             "The selected same-name CPUAPP owner failed one or more ABI, "
             "identity, or instruction-signature gates; retain fail-closed."),
            evidence,
            "high" if eligible else "low"))
    # A corrected identity can expose an exact public owner that was absent
    # from the original same-name collision catalog.  Such rows are admitted
    # only through the strict hidden-owner checks above and the same atomic
    # whole-unit closure used by the visible collision owners.
    for row_va in sorted(hidden):
        authorization = authorized[row_va]
        correction = authorization["identity_correction"]
        atomic_group = sorted(_hex(value) for value in
                              authorization.get("atomic_group", []))
        exclude_only = sorted(_hex(value) for value in authorization[
            "whole_unit_closure"].get("exclude_only", []))
        if not (atomic_group and row_va in atomic_group and
                exclude_only == atomic_group):
            raise ValueError("hidden owner atomic closure drift: %s" % row_va)
        output.append(_entry(
            "app", row_va, names, "source", "cpuapp_selected_sdk",
            correction["corrected_upstream_symbol"],
            authorization.get("upstream_object"), True,
            "A corrected durable identity exposed an exact configured public "
            "owner inside an atomically adopted SDK source unit.",
            [_evidence(
                authorization_source, "explicit_hidden_owner_adoption_authority",
                batch=authorization.get("batch"),
                instruction_exact=True,
                normalized_code_sha256=authorization.get(
                    "normalized_code_sha256"),
                cfg_verify_cases=authorization.get("cfg_verify_cases"),
                identity_correction=correction,
                atomic_group=authorization.get("atomic_group"),
                whole_unit_closure=authorization.get("whole_unit_closure"))],
            "high"))
    return output


def _build_from_baseline(paths, resolved, names):
    """Apply explicit collision receipts to the pinned pre-overlay manifest."""
    baseline_path = resolved["baseline"]
    baseline_digest = _sha256(baseline_path)
    if baseline_digest != BASELINE_PROVENANCE["sha256"]:
        raise ValueError("adoption baseline digest mismatch: %s" %
                         baseline_digest)
    baseline = _load_json(baseline_path)
    validate_manifest(baseline)

    lc3_stock_path = resolved["app_lc3_stock"]
    lc3_stock = _load_json(lc3_stock_path)
    if (lc3_stock.get("schema") != 1 or lc3_stock.get("core") != "app" or
            lc3_stock.get("status") != "authorized_atomic" or
            lc3_stock.get("summary", {}).get("unmatched_functions") != 0 or
            lc3_stock.get("version_identity", {}).get("west_manifest_pin") !=
            "448f3de31f49a838988a162ef1e23a89ddf2d2ed"):
        raise ValueError("invalid libLC3 configured-object adoption catalog")
    lc3_authorizations = lc3_stock.get("authorizations", [])
    if (len(lc3_authorizations) != 41 or
            len({_hex(row["va"]) for row in lc3_authorizations}) != 41):
        raise ValueError("incomplete libLC3 function closure")
    config_receipt = lc3_stock.get("configured_build", {})
    if (_sha256(config_receipt["config"]) !=
            config_receipt.get("config_sha256")):
        raise ValueError("libLC3 configured build changed")
    for row in lc3_authorizations:
        if (row.get("status") != "authorized" or
                row.get("match") not in {
                    "relocation_masked_full_section_exact",
                    "relocation_masked_executable_prefix_exact"} or
                row.get("raw_mapping_preserved") is not True or
                not all(check.get("exact") is True
                        for check in row.get("call_target_checks", []))):
            raise ValueError("incomplete libLC3 exact proof: %s" % row["va"])
        if (_sha256(row["upstream_object"]) !=
                row.get("upstream_object_sha256") or
                _sha256(row["upstream_source"]) !=
                row.get("upstream_source_sha256")):
            raise ValueError("libLC3 source/object changed: %s" % row["va"])

    collision_path = resolved["app_collisions"]
    authorization_path = resolved["app_collision_authorizations"]
    collisions = _load_json(collision_path)
    authorizations = _load_json(authorization_path)
    kernel_path = resolved["app_kernel_config"]
    kernel = _load_json(kernel_path)
    if (kernel.get("schema") != 1 or kernel.get("core") != "app" or
            kernel.get("status") != "authorized_atomic"):
        raise ValueError("invalid app kernel-config atomic adoption catalog")
    collisions = copy.deepcopy(collisions)
    collisions["functions"].extend(kernel.get("variant_collisions", []))
    authorizations = copy.deepcopy(authorizations)
    authorizations["authorizations"].extend(kernel.get("authorizations", []))
    authorizations["configured_build_receipts"] = sorted(set(
        authorizations.get("configured_build_receipts", []) +
        kernel.get("configured_build_receipts", [])))
    nrfx_path = resolved["app_nrfx_stock"]
    nrfx = _load_json(nrfx_path)
    if (nrfx.get("schema") != 1 or nrfx.get("core") != "app" or
            nrfx.get("status") != "authorized_atomic"):
        raise ValueError("invalid NRFX stock atomic adoption catalog")
    authorizations["authorizations"].extend(
        nrfx.get("authorizations", []))
    authorizations["configured_build_receipts"] = sorted(set(
        authorizations.get("configured_build_receipts", []) +
        nrfx.get("configured_build_receipts", [])))
    bluetooth_path = resolved["app_bluetooth_stock"]
    bluetooth = _load_json(bluetooth_path)
    if (bluetooth.get("schema") != 1 or bluetooth.get("core") != "app" or
            bluetooth.get("status") != "authorized_atomic"):
        raise ValueError("invalid Bluetooth stock atomic adoption catalog")
    authorizations["authorizations"].extend(bluetooth.get("authorizations", []))
    authorizations["configured_build_receipts"] = sorted(set(
        authorizations.get("configured_build_receipts", []) +
        bluetooth.get("configured_build_receipts", [])))
    settings_path = resolved["app_settings_stock"]
    settings = _load_json(settings_path)
    if (settings.get("schema") != 1 or settings.get("core") != "app" or
            settings.get("status") != "authorized_atomic"):
        raise ValueError("invalid settings stock atomic adoption catalog")
    authorizations["authorizations"].extend(settings.get("authorizations", []))
    authorizations["configured_build_receipts"] = sorted(set(
        authorizations.get("configured_build_receipts", []) +
        settings.get("configured_build_receipts", [])))
    mcumgr_path = resolved["app_mcumgr_stock"]
    mcumgr = _load_json(mcumgr_path)
    if (mcumgr.get("schema") != 1 or mcumgr.get("core") != "app" or
            mcumgr.get("status") != "authorized_atomic"):
        raise ValueError("invalid mcumgr exact5 atomic adoption catalog")
    authorizations["authorizations"].extend(mcumgr.get("authorizations", []))
    authorizations["configured_build_receipts"] = sorted(set(
        authorizations.get("configured_build_receipts", []) +
        mcumgr.get("configured_build_receipts", [])))
    lseek_stream_path = resolved["app_lseek_stream_flash"]
    lseek_stream = _load_json(lseek_stream_path)
    if (lseek_stream.get("schema") != 1 or lseek_stream.get("core") != "app" or
            lseek_stream.get("status") != "authorized_atomic"):
        raise ValueError("invalid lseek/stream-flash atomic adoption catalog")
    authorizations["authorizations"].extend(
        lseek_stream.get("authorizations", []))
    authorizations["configured_build_receipts"] = sorted(set(
        authorizations.get("configured_build_receipts", []) +
        lseek_stream.get("configured_build_receipts", [])))
    root_stock_path = resolved["app_root_stock"]
    root_stock = _load_json(root_stock_path)
    if (root_stock.get("schema") != 1 or root_stock.get("core") != "app" or
            root_stock.get("status") != "authorized_atomic"):
        raise ValueError("invalid root-stock exact5 atomic adoption catalog")
    collisions["functions"].extend(root_stock.get("variant_collisions", []))
    authorizations["authorizations"].extend(
        root_stock.get("authorizations", []))
    authorizations["configured_build_receipts"] = sorted(set(
        authorizations.get("configured_build_receipts", []) +
        root_stock.get("configured_build_receipts", [])))
    img_mgmt_path = resolved["app_img_mgmt_stock"]
    img_mgmt = _load_json(img_mgmt_path)
    if (img_mgmt.get("schema") != 1 or img_mgmt.get("core") != "app" or
            img_mgmt.get("status") != "authorized_atomic"):
        raise ValueError("invalid img_mgmt exact5 atomic adoption catalog")
    collisions["functions"].extend(img_mgmt.get("variant_collisions", []))
    authorizations["authorizations"].extend(
        img_mgmt.get("authorizations", []))
    authorizations["configured_build_receipts"] = sorted(set(
        authorizations.get("configured_build_receipts", []) +
        img_mgmt.get("configured_build_receipts", [])))
    net_openamp_path = resolved["net_openamp_stock"]
    net_openamp = _load_json(net_openamp_path)
    if (net_openamp.get("schema") != 1 or
            net_openamp.get("core") != "net" or
            net_openamp.get("component") != "openamp_rpmsg" or
            net_openamp.get("safe") is not True or
            net_openamp.get("mutable_state_sections")):
        raise ValueError("invalid net OpenAMP rpmsg.c atomic adoption catalog")
    upstream_openamp = net_openamp.get("upstream", {})
    for key in ("source", "object", "configured_build"):
        digest = upstream_openamp.get(key + "_sha256")
        if not digest or _sha256(upstream_openamp[key]) != digest:
            raise ValueError("net OpenAMP %s receipt changed" % key)
    for row in net_openamp.get("manifest_functions", []):
        if row.get("reconstruction_present"):
            source_path = _path(row["reconstruction_source"])
            if _sha256(source_path) != row.get("reconstruction_source_sha256"):
                raise ValueError("net OpenAMP reconstruction changed: %s" %
                                 row["va"])
    net_ipc_path = resolved["net_ipc_rpmsg_variant"]
    net_ipc = _load_json(net_ipc_path)
    if (net_ipc.get("schema") != 1 or net_ipc.get("core") != "net" or
            net_ipc.get("component") != "zephyr_ipc_rpmsg_variant" or
            net_ipc.get("status") != "required_retain" or
            net_ipc.get("safe") is not True or
            net_ipc.get("mutable_state_sections") or
            net_ipc.get("state_closure", {}).get("complete") is not True or
            len(net_ipc.get("source_unit_sections", [])) != 5 or
            len(net_ipc.get("call_target_mismatches", [])) != 2):
        raise ValueError("invalid net IPC RPMsg variant retention catalog")
    upstream_ipc = net_ipc["upstream"]
    for path_key, digest_key in (
            ("source_path", "source_sha256"),
            ("object_path", "object_sha256"),
            ("linker_map", "linker_map_sha256")):
        if _sha256(upstream_ipc[path_key]) != upstream_ipc.get(digest_key):
            raise ValueError("net IPC RPMsg %s receipt changed" % path_key)
    config_path = os.path.join(upstream_ipc["configured_build"],
                               "zephyr/.config")
    if _sha256(config_path) != upstream_ipc.get("configured_build_sha256"):
        raise ValueError("net IPC RPMsg configured build changed")
    for row in net_ipc.get("retained_functions", []):
        source_path = _path(row["reconstruction_source"])
        if (_sha256(source_path) != row.get("reconstruction_source_sha256") or
                row.get("exclude_reconstruction") is not False):
            raise ValueError("net IPC RPMsg retained variant changed: %s" %
                             row["va"])
    net_zephyr_path = resolved["net_zephyr_stock"]
    net_zephyr = _load_json(net_zephyr_path)
    if (net_zephyr.get("schema") != 1 or
            net_zephyr.get("core") != "net" or
            net_zephyr.get("component") != "zephyr_os_kernel_stock" or
            net_zephyr.get("status") != "authorized_atomic" or
            net_zephyr.get("safe") is not True or
            len(net_zephyr.get("section_matches", [])) != 40 or
            len(net_zephyr.get("private_state_sections", [])) != 5):
        raise ValueError("invalid net Zephyr OS/kernel atomic adoption catalog")
    if (_sha256(net_zephyr["upstream"]["configured_build"] +
                "/zephyr/.config") !=
            net_zephyr["upstream"].get("configured_build_sha256")):
        raise ValueError("net Zephyr configured build changed")
    for unit in net_zephyr.get("source_units", []):
        if (_sha256(os.path.join("/Users/freedomcoder/ncs251", unit["source"])) !=
                unit.get("source_sha256") or
                _sha256(os.path.join(net_zephyr["upstream"]["configured_build"],
                                     unit["object"])) !=
                unit.get("object_sha256")):
            raise ValueError("net Zephyr source/object changed: %s" % unit["unit"])
    for row in net_zephyr.get("manifest_functions", []):
        if row.get("reconstruction_present"):
            source_path = _path(row["reconstruction_source"])
            if _sha256(source_path) != row.get("reconstruction_source_sha256"):
                raise ValueError("net Zephyr reconstruction changed: %s" %
                                 row["va"])
    retention_path = resolved["app_collision_retention_overrides"]
    retentions = _load_json(retention_path)
    if (retentions.get("schema") != 1 or
            retentions.get("core") not in (None, "app")):
        raise ValueError("invalid app collision retention override catalog")
    retention_rows = [row for row in retentions.get("overrides", [])
                      if row.get("status") == "required_retain"]
    metadata_corrections = retentions.get("metadata_corrections", [])
    retention_vas = [_hex(row["va"]) for row in retention_rows]
    if len(set(retention_vas)) != len(retention_vas):
        raise ValueError("duplicate app collision retention override VA")
    collision_rows = {_hex(row["va"]): row
                      for row in collisions.get("functions", [])}
    authorized_rows = [row for row in authorizations.get("authorizations", [])
                       if row.get("status") == "authorized"]
    generated = {_hex(row["va"]): row for row in _app_collision_entries(
        collisions, paths["app_collisions"], names, authorizations,
        paths["app_collision_authorizations"])
        if row.get("exclude_reconstruction")}

    result = copy.deepcopy(baseline)
    result["generated_by"] = "tools/build_adoption_manifest.py"
    result["baseline_provenance"] = dict(BASELINE_PROVENANCE)
    result["overlay_inputs"] = [
        {"path": paths["app_collisions"], "sha256": _sha256(collision_path)},
        {"path": paths["app_collision_authorizations"],
         "sha256": _sha256(authorization_path)},
        {"path": paths["app_kernel_config"],
         "sha256": _sha256(kernel_path)},
        {"path": paths["app_nrfx_stock"],
         "sha256": _sha256(nrfx_path)},
        {"path": paths["app_bluetooth_stock"],
         "sha256": _sha256(bluetooth_path)},
        {"path": paths["app_settings_stock"],
         "sha256": _sha256(settings_path)},
        {"path": paths["app_mcumgr_stock"],
         "sha256": _sha256(mcumgr_path)},
        {"path": paths["app_lseek_stream_flash"],
         "sha256": _sha256(lseek_stream_path)},
        {"path": paths["app_root_stock"],
         "sha256": _sha256(root_stock_path)},
        {"path": paths["app_img_mgmt_stock"],
         "sha256": _sha256(img_mgmt_path)},
        {"path": paths["app_lc3_stock"],
         "sha256": _sha256(lc3_stock_path)},
        {"path": paths["net_openamp_stock"],
         "sha256": _sha256(net_openamp_path)},
        {"path": paths["net_ipc_rpmsg_variant"],
         "sha256": _sha256(net_ipc_path)},
        {"path": paths["net_zephyr_stock"],
         "sha256": _sha256(net_zephyr_path)},
        {"path": paths["app_collision_retention_overrides"],
         "sha256": _sha256(retention_path)},
        {"path": paths["library_provenance"],
         "sha256": _sha256(resolved["library_provenance"])},
    ]
    app_rows = {row["va"]: row for row in result["cores"]["app"]["entries"]}
    for authorization in lc3_authorizations:
        va = _hex(authorization["va"])
        previous = app_rows.get(va)
        if (previous is None or previous.get("component") != "liblc3" or
                previous.get("exclude_reconstruction") is not True or
                previous.get("raw_symbol") != authorization["raw_symbol"]):
            raise ValueError("libLC3 baseline ownership drift: %s" % va)
        corrected = names["app"].get(int(va, 16), {}).get("name")
        if corrected != authorization["symbol"]:
            raise ValueError("libLC3 durable name drift: %s" % va)
        previous["current_symbol"] = corrected
        previous["upstream_symbol"] = authorization["upstream_symbol"]
        previous["upstream_unit"] = authorization["upstream_source"]
        previous["decision_reason"] = (
            "Pinned configured libLC3 owner is relocation-masked byte-exact "
            "over the complete firmware code extent with call targets checked.")
        previous.setdefault("evidence", []).append(_evidence(
            paths["app_lc3_stock"],
            "liblc3_configured_object_exact_owner",
            match=authorization["match"],
            upstream_section=authorization["upstream_section"],
            unmasked_prefix_sha256=authorization["unmasked_prefix_sha256"],
            call_targets_checked=len(authorization.get(
                "call_target_checks", [])),
            manifest_pin=lc3_stock["version_identity"]["west_manifest_pin"],
            raw_mapping_preserved=True))
    authorized_by_va = {_hex(row["va"]): row for row in authorized_rows}
    for authorization in authorized_rows:
        va = _hex(authorization["va"])
        atomic_group = sorted(_hex(value) for value in
                              authorization.get("atomic_group", []))
        if atomic_group:
            if va not in atomic_group:
                raise ValueError("authorization absent from atomic group: %s" % va)
            closure_group = sorted(_hex(value) for value in authorization.get(
                "whole_unit_closure", {}).get("exclude_only", []))
            if closure_group != atomic_group:
                raise ValueError("atomic closure mismatch: %s" % va)
            for member in atomic_group:
                peer = authorized_by_va.get(member)
                if peer is None or sorted(_hex(value) for value in peer.get(
                        "atomic_group", [])) != atomic_group:
                    raise ValueError("incomplete atomic authorization: %s" % va)
        collision = collision_rows.get(va)
        hidden_owner = authorization.get("hidden_owner_closure") is True
        if collision is None and not hidden_owner:
            raise ValueError("authorization absent from current collision catalog: %s" % va)
        if collision is not None and authorization.get(
                "collision_receipt_sha256") != _json_sha256(collision):
            raise ValueError("collision receipt digest mismatch: %s" % va)
        upstream = (collision or {}).get("upstream", {})
        source = upstream.get("source", {})
        configured = (collision or {}).get("configured_inclusion", {})
        identity_correction = authorization.get("identity_correction", {})
        archive_member_exact = authorization.get(
            "archive_member_exact") is True
        if hidden_owner:
            receipts = ()
        elif archive_member_exact:
            receipts = (("baseline_configured_build_sha256",
                         configured.get("zephyr_config_sha256")),)
        elif identity_correction:
            receipts = (
                ("baseline_upstream_source_sha256", source.get("sha256")),
                ("baseline_configured_build_sha256",
                 configured.get("zephyr_config_sha256")),
            )
        elif authorization.get("configuration_variant_exact") is True:
            receipts = (
                ("baseline_upstream_object_sha256", upstream.get("object_sha256")),
                ("upstream_source_sha256", source.get("sha256")),
                ("baseline_configured_build_sha256",
                 configured.get("zephyr_config_sha256")),
            )
        else:
            receipts = (
                ("upstream_object_sha256", upstream.get("object_sha256")),
                ("upstream_source_sha256", source.get("sha256")),
                ("configured_build_sha256", configured.get("zephyr_config_sha256")),
            )
        for key, expected in receipts:
            if not expected or authorization.get(key) != expected:
                raise ValueError("%s receipt mismatch: %s" % (key, va))
        object_path = authorization.get("upstream_object")
        if not object_path:
            raise ValueError("upstream object missing: %s" % va)
        object_exact = (_sha256(object_path) == authorization[
            "upstream_object_sha256"])
        content_digest = authorization.get("upstream_object_alloc_sha256")
        if (not object_exact and
                (not content_digest or
                 _alloc_content_sha256(object_path) != content_digest)):
            raise ValueError("upstream object changed: %s" % va)
        if archive_member_exact:
            if (authorization.get("upstream_archive_sha256") !=
                    authorization.get("upstream_object_sha256") or
                    not authorization.get("archive_member") or
                    _archive_member_sha256(
                        object_path, authorization["archive_member"]) !=
                    authorization.get("archive_member_sha256")):
                raise ValueError("exact archive-member receipt mismatch: %s" % va)
            if not (authorization.get("newlib_release") and
                    authorization.get("newlib_commit") and
                    authorization.get("upstream_source")):
                raise ValueError("archive source provenance incomplete: %s" % va)
        else:
            expected_source = (
                identity_correction.get("corrected_upstream_source") or
                authorization.get("upstream_source")
                if identity_correction else source.get("path"))
            if authorization.get("upstream_source") != expected_source:
                raise ValueError("upstream source identity changed: %s" % va)
            source_path = os.path.join("/Users/freedomcoder/ncs251",
                                       authorization["upstream_source"])
            if _sha256(source_path) != authorization["upstream_source_sha256"]:
                raise ValueError("upstream source changed: %s" % va)
        config_paths = ([authorization.get("configured_build")] +
                        authorizations.get("configured_build_receipts", []))
        valid_config_paths = [
            path and os.path.exists(path) and
            path for path in config_paths
            if path and os.path.exists(path) and
            _sha256(path) == authorization["configured_build_sha256"]]
        if not valid_config_paths:
            raise ValueError("configured build changed: %s" % va)
        required_config = authorization.get("required_config", {})
        if authorization.get("configuration_variant_exact") is True:
            if not required_config:
                raise ValueError("configuration variant has no config gate: %s" % va)
            actual_config = _kconfig_values(valid_config_paths[0])
            mismatches = {key: {"expected": value,
                                "actual": actual_config.get(key)}
                          for key, value in required_config.items()
                          if actual_config.get(key) != value}
            if mismatches:
                raise ValueError("required config mismatch %s: %s" %
                                 (va, mismatches))
        canonical = authorization.get("reconstruction_source")
        canonical = (_path(canonical) if canonical else
                     os.path.join(BASE, "recon", "app", "src",
                                  authorization.get("raw_symbol", "") + ".c"))
        if (_sha256(canonical) !=
                authorization.get("reconstruction_source_sha256")):
            raise ValueError("reconstruction source changed: %s" % va)
        overlay = generated.get(va)
        if overlay is None:
            raise ValueError("authorization did not pass exclusion gates: %s" % va)
        previous = app_rows.get(va)
        if previous is not None and previous.get("raw_symbol") != overlay[
                "raw_symbol"]:
            raise ValueError("baseline identity mismatch: %s" % va)
        app_rows[va] = overlay

    # Retention overrides are deliberately one-way and fail closed.  They can
    # revoke a stale baseline exclusion, but can never authorize a new one.
    # This keeps the pinned baseline immutable while making a corrected
    # address identity immediately safe for source selection.
    for retention in retention_rows:
        va = _hex(retention["va"])
        previous = app_rows.get(va)
        if previous is None:
            raise ValueError("retention override absent from baseline: %s" % va)
        if previous.get("raw_symbol") != retention.get("raw_symbol"):
            raise ValueError("retention override raw identity mismatch: %s" % va)
        if previous.get("current_symbol") != retention.get(
                "baseline_current_symbol"):
            raise ValueError("retention override baseline symbol mismatch: %s" % va)
        if previous.get("exclude_reconstruction") is not True:
            raise ValueError("retention override is not revoking an exclusion: %s" % va)
        corrected = names["app"].get(int(va, 16), {}).get("name")
        if corrected != retention.get("corrected_symbol"):
            raise ValueError("retention override corrected symbol mismatch: %s" % va)
        previous["current_symbol"] = corrected
        previous["exclude_reconstruction"] = False
        previous["decision"] = "retain_reconstruction"
        previous["decision_reason"] = retention["reason"]
        previous.setdefault("evidence", []).append(_evidence(
            paths["app_collision_retention_overrides"],
            "explicit_fail_closed_retention_override",
            batch=retention.get("batch"),
            baseline_current_symbol=retention.get("baseline_current_symbol"),
            corrected_symbol=corrected,
            identity_evidence=retention.get("identity_evidence"),
            cfg_verify=retention.get("cfg_verify")))

    # Metadata corrections describe an already-retained body and are forbidden
    # from changing its source-selection decision in either direction.
    for correction in metadata_corrections:
        va = _hex(correction["va"])
        previous = app_rows.get(va)
        if previous is None or previous.get("raw_symbol") != correction.get("raw_symbol"):
            raise ValueError("metadata correction identity mismatch: %s" % va)
        if previous.get("exclude_reconstruction") is not False:
            raise ValueError("metadata correction may only describe retained source: %s" % va)
        if previous.get("current_symbol") != correction.get("baseline_current_symbol"):
            raise ValueError("metadata correction baseline symbol mismatch: %s" % va)
        corrected = names["app"].get(int(va, 16), {}).get("name")
        if corrected != correction.get("corrected_symbol"):
            raise ValueError("metadata correction durable name mismatch: %s" % va)
        previous["current_symbol"] = corrected
        previous["upstream_symbol"] = correction.get("upstream_symbol")
        previous["upstream_unit"] = correction.get("upstream_source")
        previous["decision_reason"] = correction["reason"]
        previous.setdefault("evidence", []).append(_evidence(
            paths["app_collision_retention_overrides"],
            "retained_identity_metadata_correction",
            semantic_owner=correction.get("semantic_owner"),
            upstream_source=correction.get("upstream_source"),
            exclusion_unchanged=True))

    # Provenance corrections are metadata-only.  They may repair a repository
    # classification inherited from the pinned baseline, but can never change
    # source ownership, exclusion state, symbol identity, or decision text.
    provenance = _load_json(resolved["library_provenance"])
    if provenance.get("schema") != 1:
        raise ValueError("invalid upstream library provenance catalog")
    _apply_provenance_corrections(
        app_rows, provenance, paths["library_provenance"],
        "/Users/freedomcoder/ncs251")

    result["cores"]["app"]["entries"] = sorted(
        app_rows.values(), key=lambda row: int(row["va"], 16))
    net_rows = {row["va"]: row for row in result["cores"]["net"]["entries"]}
    for row in _net_openamp_stock_entries(
            net_openamp, paths["net_openamp_stock"], names):
        if row.get("exclude_reconstruction") is not True:
            raise ValueError("incomplete net OpenAMP exclusion: %s" % row["va"])
        net_rows[row["va"]] = row
    for row in _net_ipc_rpmsg_variant_entries(
            net_ipc, paths["net_ipc_rpmsg_variant"], names):
        if row.get("exclude_reconstruction") is not False:
            raise ValueError("unsafe net IPC RPMsg variant exclusion: %s" %
                             row["va"])
        net_rows[row["va"]] = row
    for row in _net_zephyr_stock_entries(
            net_zephyr, paths["net_zephyr_stock"], names):
        if row.get("exclude_reconstruction") is not True:
            raise ValueError("incomplete net Zephyr exclusion: %s" % row["va"])
        net_rows[row["va"]] = row
    result["cores"]["net"]["entries"] = sorted(
        net_rows.values(), key=lambda row: int(row["va"], 16))
    for core in ("app", "net"):
        rows = result["cores"][core]["entries"]
        result["cores"][core]["summary"] = {
            "entries": len(rows),
            "exclude_reconstruction": sum(
                row["exclude_reconstruction"] for row in rows),
            "retain_reconstruction": sum(
                not row["exclude_reconstruction"] for row in rows),
            "by_kind": {kind: sum(row["kind"] == kind for row in rows)
                        for kind in KINDS},
        }
    validate_manifest(result)
    return result


def _apply_provenance_corrections(app_rows, provenance, source_label,
                                  ncs_root):
    """Apply fail-closed metadata repairs without changing ownership."""
    for correction in provenance.get("provenance_corrections", []):
        if correction.get("core") != "app":
            raise ValueError("unsupported provenance correction core")
        va = _hex(correction["va"])
        row = app_rows.get(va)
        if row is None or row.get("raw_symbol") != correction.get("raw_symbol"):
            raise ValueError("provenance correction identity mismatch: %s" % va)
        if row.get("component") != correction.get("from_component"):
            raise ValueError("provenance correction source drift: %s" % va)
        immutable = (row.get("exclude_reconstruction"), row.get("decision"),
                     row.get("upstream_symbol"), row.get("upstream_unit"))
        source_path = os.path.join(ncs_root, correction["source"])
        if not os.path.isfile(source_path):
            raise ValueError("provenance correction source absent: %s" % va)
        row["component"] = correction["to_component"]
        repaired = False
        for evidence in row.get("evidence", []):
            source = evidence.get("upstream_source")
            if not isinstance(source, dict):
                continue
            if source.get("sha256") != _sha256(source_path):
                continue
            source["path"] = correction["source"]
            source["repository"] = correction["repository"]
            source["commit"] = correction["commit"]
            repaired = True
        if not repaired:
            raise ValueError("provenance correction evidence absent: %s" % va)
        row.setdefault("evidence", []).append(_evidence(
            source_label, "metadata_only_provenance_correction",
            from_component=correction["from_component"],
            to_component=correction["to_component"],
            repository=correction["repository"],
            commit=correction["commit"], upstream_source=correction["source"],
            ownership_decision_changed=False))
        if immutable != (row.get("exclude_reconstruction"), row.get("decision"),
                         row.get("upstream_symbol"), row.get("upstream_unit")):
            raise ValueError("provenance correction changed ownership: %s" % va)


def _app_sdk_public_entries(data, source, names):
    """Adopt only public SDK/runtime owners proven in retain-all output."""
    output = []
    for row in data.get("functions", []):
        eligible = bool(row.get("safe_to_adopt") is True and
                        row.get("exclude_reconstruction") is True and
                        not row.get("blockers") and
                        row.get("selected_link_owner") and
                        row.get("upstream_member") and
                        row.get("required_config"))
        output.append(_entry(
            "app", row["va"], names, "archive", "app_sdk_public",
            row.get("upstream_symbol"), row.get("selected_link_owner"), eligible,
            ("Pinned public export passed identity, ABI/config, and actual "
             "retain-all selected-owner gates." if eligible else
             "Public SDK candidate failed one or more fail-closed gates."),
            [_evidence(source, "app_sdk_public_selected_owner",
                       raw_symbol=row.get("raw_symbol"),
                       member=row.get("upstream_member"),
                       selected_link_owner=row.get("selected_link_owner"),
                       signature_ratio=row.get("signature_ratio"),
                       signature_gate=row.get("signature_gate"),
                       abi=row.get("abi"), config=row.get("required_config"),
                       safe_to_adopt=eligible, blockers=row.get("blockers"))],
            "high" if eligible else "low"))
    return output


def _parse_sdc_benchmark(path):
    """Read benchmark metadata, but never turn prose uniqueness into exclusion."""
    with open(path) as stream:
        text = stream.read()
    values = {}
    for label, key in (("Controller archive total", "archive_total"),
                       ("Controller archive, exact unique identity", "exact_unique"),
                       ("Controller archive, exact duplicate/ambiguous identity", "exact_ambiguous"),
                       ("Controller archive, high-confidence approximate unique identity", "approx_unique"),
                       ("Controller archive, high-confidence approximate ambiguous identity", "approx_ambiguous")):
        match = re.search(r"\|\s*\*{0,2}%s\*{0,2}\s*\|\s*\*{0,2}([0-9,]+)" % re.escape(label), text)
        if match:
            values[key] = int(match.group(1).replace(",", ""))
    sha = re.search(r"SHA-256:\s*`([0-9a-f]{64})`", text)
    if sha:
        values["archive_sha256"] = sha.group(1)
    values["machine_exclusion_authority"] = False
    values["note"] = ("The benchmark prose supplies aggregate archive statistics but no "
                      "per-VA machine-readable uniqueness field; it cannot authorize "
                      "private SDC exclusions.")
    return values


def _sdc_entries(data, source, names):
    """Convert the per-address SDC catalog into fail-closed decisions."""
    output = []
    for row in data.get("functions", []):
        best = row.get("best", {})
        eligible = bool(row.get("safe_to_exclude"))
        output.append(_entry(
            "net", row["address"], names, "archive", "softdevice_controller",
            best.get("symbol"), best.get("identity"), eligible,
            ("Pinned public SDC symbol has per-VA unique identity, published ABI, "
             "CFG verification, and exact build-extraction evidence." if eligible else
             "SDC identity remains report-only under the per-VA machine policy."),
            [_evidence(
                source, "sdc_machine_ownership",
                archive_sha256=data.get("inputs", {}).get("archive_sha256"),
                match_kind=row.get("match_kind"), score=row.get("score"),
                per_va_unique_identity=row.get("unique_identity"),
                public_api=row.get("public_api"),
                build_extraction_verified=row.get("build_extraction_verified"),
                safe_to_exclude=eligible,
                blockers=row.get("exclusion_blockers"))],
            "high" if eligible else "medium"))
    return output


def _net_entries(data, source, benchmark_source, benchmark, names,
                 machine_sdc_addresses=None, machine_public_addresses=None,
                 machine_openamp_addresses=None,
                 machine_zephyr_addresses=None):
    output = []
    machine_sdc_addresses = set(machine_sdc_addresses or ())
    machine_public_addresses = set(machine_public_addresses or ())
    machine_openamp_addresses = set(machine_openamp_addresses or ())
    machine_zephyr_addresses = set(machine_zephyr_addresses or ())
    for va, row in sorted(data.get("entries", {}).items()):
        match = row.get("signature_match")
        provenance = (match or {}).get("provenance", "")
        symbol = (match or {}).get("symbol")
        ratio = (match or {}).get("ratio")
        threshold = (match or {}).get("threshold")
        is_sdc = "softdevice_controller" in provenance
        is_rtc = "nrf_rtc_timer.c.obj" in provenance
        if is_sdc and _hex(va) in machine_sdc_addresses:
            # The per-address catalog supersedes the older generic signature
            # row. Otherwise its blanket retain decision would mask a narrowly
            # proven public-symbol promotion during merge.
            continue
        if _hex(va) in machine_public_addresses:
            # The exact public-owner catalog records source, object, ABI,
            # configuration and complete instruction equality.  It therefore
            # supersedes the older generic signature row for the same VA;
            # merging both would let the generic retain fallback mask the
            # narrowly proven public-source adoption.
            continue
        if _hex(va) in machine_openamp_addresses:
            # Operand-level, whole-source-unit OpenAMP evidence supersedes the
            # old mnemonic-only catalog (which confused raw and nocopy).
            continue
        if _hex(va) in machine_zephyr_addresses:
            # Exact configured code/call/state closure supersedes generic SDK
            # and the stale mnemonic-only SDC fingerprint for add_mem.
            continue
        is_archive = ".a(" in provenance
        explicit_match = (match is not None and ratio is not None and threshold is not None
                          and ratio >= threshold)
        if is_sdc:
            kind = "archive"
            eligible = False
            reason = ("Private/obfuscated SDC ownership lacks a per-VA "
                      "machine-readable unique-identity field; retain fail-closed.")
        elif is_archive and explicit_match:
            kind = "archive"
            eligible = True
            reason = "Explicit threshold-passing archive signature and provenance."
        else:
            kind = "glue"
            eligible = False
            reason = ("Generic SDK ownership or missing specific provenance does not "
                      "identify an adoptable source/archive unit.")
        evidence = [_evidence(source, "net_signature_match", symbol=symbol,
                              ratio=ratio, threshold=threshold,
                              provenance=provenance or None)]
        if is_sdc:
            evidence.append(_evidence(benchmark_source, "sdc_archive_benchmark_summary",
                                      archive_sha256=benchmark.get("archive_sha256"),
                                      per_va_unique_identity=False))
        output.append(_entry(
            "net", va, names, kind,
            ("softdevice_controller" if is_sdc else
             "zephyr_nrf_rtc_timer" if is_rtc else "net_sdk_or_glue"),
            symbol, provenance or None, eligible, reason, evidence,
            row.get("confidence")))
    return output


def _net_rtc_entries(data, source, names):
    output = []
    upstream = data["upstream"]
    config = data["required_config"]
    for row in data.get("functions", []):
        eligible = (row.get("exclude_reconstruction") is True and
                    row.get("match_score") == 1.0 and
                    row.get("firmware_size") == row.get("reference_size"))
        output.append(_entry(
            "net", row["va"], names,
            "static_helper" if row.get("linkage") == "file_static" else "source",
            "zephyr_nrf_rtc_timer", row["upstream_symbol"],
            upstream["object"], eligible,
            ("Pinned Zephyr timer object is exact for this VA and is selected "
             "by the recorded net-core configuration." if eligible else
             "RTC timer evidence is incomplete; retain fail-closed."),
            [_evidence(source, "net_rtc_exact_owner",
                       commit=upstream.get("commit"),
                       source_sha256=upstream.get("source_sha256"),
                       match=row.get("match"), match_score=row.get("match_score"),
                       abi=row.get("abi"), config=config,
                       object=upstream.get("object"))],
            "high" if eligible else "medium"))
    return output


def _net_sdk_public_entries(data, source, names):
    output = []
    upstream = data["upstream"]
    config = data["required_config"]
    for row in data.get("functions", []):
        eligible = (row.get("exclude_reconstruction") is True and
                    row.get("match_score") == 1.0 and
                    row.get("firmware_code_size") ==
                    row.get("reference_code_size"))
        output.append(_entry(
            "net", row["va"], names, "source", "net_sdk_public",
            row["upstream_symbol"], row["object"], eligible,
            ("Pinned public SDK owner is instruction-exact under the recorded "
             "configuration." if eligible else
             "Public SDK ownership evidence is incomplete; retain fail-closed."),
            [_evidence(source, "net_sdk_public_exact_owner",
                       zephyr_commit=upstream.get("zephyr_commit"),
                       match=row.get("match"), match_score=row.get("match_score"),
                       abi=row.get("abi"),
                       config=row.get("required_config", config),
                       source_unit=row.get("source"), object=row.get("object"))],
            "high" if eligible else "medium"))
    return output


def _net_openamp_stock_entries(data, source, names):
    """Adopt the complete selected section closure of pinned rpmsg.c."""
    output = []
    upstream = data["upstream"]
    if not data.get("safe") or data.get("mutable_state_sections"):
        raise ValueError("unsafe OpenAMP rpmsg.c source-unit receipt")
    matched = {row["symbol"] for row in data.get("section_matches", [])
               if row.get("match") == "relocation-masked-byte-exact"}
    for row in data.get("manifest_functions", []):
        eligible = bool(
            row.get("safe_to_adopt") is True and
            row.get("exclude_reconstruction") is True and
            row.get("whole_source_unit_selected") is True and
            row.get("upstream_symbol") in matched)
        output.append(_entry(
            "net", row["va"], names,
            "static_helper" if row.get("upstream_linkage") == "file_static"
            else "source",
            "openamp_rpmsg", row.get("upstream_symbol"),
            row.get("upstream_source"), eligible,
            ("Pinned OpenAMP rpmsg.c owner is relocation-masked byte-exact "
             "inside the complete selected source-unit closure." if eligible else
             "OpenAMP source-unit evidence is incomplete; retain fail-closed."),
            [_evidence(source, "net_openamp_source_unit_exact_owner",
                       repository=upstream.get("repository"),
                       commit=upstream.get("commit"),
                       source_sha256=upstream.get("source_sha256"),
                       object_sha256=upstream.get("object_sha256"),
                       config=upstream.get("required_config"),
                       upstream_linkage=row.get("upstream_linkage"),
                       reconstruction_present=row.get(
                           "reconstruction_present"),
                       safe_to_adopt=eligible)],
            "high" if eligible else "low"))
    return output


def _net_ipc_rpmsg_variant_entries(data, source, names):
    """Retain the shipped IPC wrapper when a live relocation differs."""
    output = []
    upstream = data["upstream"]
    mismatches = data.get("call_target_mismatches", [])
    closure = data.get("state_closure", {})
    safe_retain = bool(
        data.get("safe") is True and data.get("status") == "required_retain" and
        len(mismatches) == 2 and
        all(row.get("equivalent") is False for row in mismatches) and
        closure.get("complete") is True and
        not closure.get("mutable_state_sections"))
    if not safe_retain:
        raise ValueError("incomplete net IPC RPMsg variant closure")
    for row in data.get("retained_functions", []):
        output.append(_entry(
            "net", row["va"], names, "source",
            "zephyr_ipc_rpmsg_variant", row.get("stock_symbol"),
            upstream.get("source"), False,
            ("Retain the recovered firmware variant: the pinned stock owner "
             "matches all non-relocation bytes, but two live unbind callback "
             "relocations resolve to a different target."),
            [_evidence(source, "net_ipc_rpmsg_variant_required_retain",
                       repository=upstream.get("repository"),
                       commit=upstream.get("commit"),
                       source_sha256=upstream.get("source_sha256"),
                       object_sha256=upstream.get("object_sha256"),
                       variant_symbol=row.get("variant_symbol"),
                       raw_mapping_preserved=True,
                       call_target_mismatches=len(mismatches),
                       state_closure_complete=True,
                       sdc_policy=data.get("policy", {}).get("sdc_policy"))],
            "high"))
    return output


def _net_zephyr_stock_entries(data, source, names):
    """Adopt the proved CPUNET Zephyr code and private-state closures."""
    output = []
    upstream = data["upstream"]
    if (data.get("safe") is not True or
            len(data.get("private_state_sections", [])) != 5):
        raise ValueError("unsafe CPUNET Zephyr source-unit receipt")
    matched = {row["symbol"] for row in data.get("section_matches", [])
               if row.get("match") == "relocation-masked-byte-exact"}
    checked_callers = {row["caller"]
                       for row in data.get("call_target_checks", [])}
    for row in data.get("manifest_functions", []):
        symbol = row.get("upstream_symbol")
        # Leaf functions legitimately have no call relocation; all non-leaves
        # must occur in the checked caller set.
        section = next((item for item in data["section_matches"]
                        if item["symbol"] == symbol), None)
        has_calls = any(relocation["type"] in (10, 30)
                        for relocation in section.get("relocations", []))
        eligible = bool(
            row.get("safe_to_adopt") is True and
            row.get("exclude_reconstruction") is True and
            row.get("whole_source_unit_selected") is True and
            row.get("call_targets_checked") is True and
            symbol in matched and
            (not has_calls or symbol in checked_callers))
        output.append(_entry(
            "net", row["va"], names,
            "static_helper" if row.get("upstream_linkage") == "file_static"
            else "source",
            "zephyr_os_kernel_stock", symbol,
            row.get("upstream_source"), eligible,
            ("Pinned configured Zephyr owner is relocation-masked byte-exact "
             "with resolved call targets and atomic private state." if eligible
             else "Zephyr source-unit evidence is incomplete; retain fail-closed."),
            [_evidence(source, "net_zephyr_source_unit_exact_owner",
                       commit=upstream.get("commit"),
                       config=upstream.get("required_config"),
                       upstream_linkage=row.get("upstream_linkage"),
                       call_targets_checked=row.get("call_targets_checked"),
                       private_state_sections=len(
                           data.get("private_state_sections", [])),
                       reconstruction_present=row.get(
                           "reconstruction_present"),
                       safe_to_adopt=eligible)],
            "high" if eligible else "low"))
    return output


def _net_alias_resolution_entries(data, source, names):
    """Preserve selected public owners for exact firmware tail veneers."""
    output = []
    for row in data.get("resolutions", []):
        if row.get("resolution") != "adopt_selected_upstream_public_owner":
            continue
        raw = row.get("raw_identity", "")
        match = re.fullmatch(r"FUN_([0-9a-fA-F]{8})", raw)
        if not match:
            raise ValueError("invalid adopted net alias raw identity: %r" % raw)
        address = int(match.group(1), 16)
        output.append(_entry(
            "net", address, names, "source", "net_selected_public_alias",
            row.get("symbol"), row.get("upstream_object"), True,
            "Reviewed Thumb tail veneer resolves to the selected public SDK owner.",
            [_evidence(source, "net_public_tail_veneer",
                       image_sha256=data.get("image_sha256"),
                       target=row.get("veneer_target"),
                       thumb_evidence=row.get("thumb_evidence"),
                       historical_alias=row.get("historical_alias"))],
            "high"))
    return output


def validate_manifest(data):
    errors = []
    if data.get("schema") != 1:
        errors.append("schema must be 1")
    seen = set()
    for core in ("app", "net"):
        rows = data.get("cores", {}).get(core, {}).get("entries", [])
        for row in rows:
            key = (core, row.get("va"))
            if key in seen:
                errors.append("duplicate entry %s:%s" % key)
            seen.add(key)
            if row.get("core") != core:
                errors.append("core mismatch %s" % (key,))
            if row.get("kind") not in KINDS:
                errors.append("invalid kind %r at %s" % (row.get("kind"), key))
            if row.get("raw_symbol") != _raw(core, row["va"]):
                errors.append("raw symbol mismatch at %s" % (key,))
            if (row.get("component") == "softdevice_controller" and
                    row.get("upstream_symbol", "").startswith("sym_") and
                    row.get("exclude_reconstruction")):
                errors.append("unsafe private SDC exclusion at %s" % (key,))
            if (row.get("component") == "softdevice_controller" and
                    row.get("exclude_reconstruction")):
                authority = [item for item in row.get("evidence", [])
                             if item.get("type") == "sdc_machine_ownership"]
                if not authority or not any(
                        item.get("safe_to_exclude") is True and
                        item.get("public_api") is True and
                        item.get("per_va_unique_identity") is True and
                        item.get("build_extraction_verified") is True
                        for item in authority):
                    errors.append("SDC exclusion lacks public build authority at %s" %
                                  (key,))
    if errors:
        raise ValueError("invalid adoption manifest:\n" + "\n".join(errors))


def build(paths):
    resolved = {key: _path(value) for key, value in paths.items()}
    names = {"app": _name_records(resolved["app_names"]),
             "net": _name_records(resolved["net_names"])}
    if "baseline" in paths:
        return _build_from_baseline(paths, resolved, names)
    benchmark = _parse_sdc_benchmark(resolved["sdc_benchmark"])
    sdc_catalog = _load_json(resolved["sdc_catalog"])
    net_sdk_public = _load_json(resolved["net_sdk_public"])
    net_openamp_stock = (_load_json(resolved["net_openamp_stock"])
                         if "net_openamp_stock" in resolved else None)
    net_zephyr_stock = (_load_json(resolved["net_zephyr_stock"])
                        if "net_zephyr_stock" in resolved else None)
    machine_sdc_addresses = {row["address"]
                             for row in sdc_catalog.get("functions", [])}
    machine_public_addresses = {row["va"]
                                for row in net_sdk_public.get("functions", [])}
    machine_openamp_addresses = {
        row["va"] for row in (net_openamp_stock or {}).get(
            "manifest_functions", [])}
    machine_zephyr_addresses = {
        row["va"] for row in (net_zephyr_stock or {}).get(
            "manifest_functions", [])}
    entries = {}
    producers = (
        _lc3_entries(_load_json(resolved["lc3"]), paths["lc3"], names),
        _tinycrypt_entries(_load_json(resolved["tinycrypt"]), paths["tinycrypt"], names),
        _cc312_entries(_load_json(resolved["cc312"]), paths["cc312"], names),
        _crypto_entries(_load_json(resolved["crypto"]), paths["crypto"], names),
        _app_collision_entries(_load_json(resolved["app_collisions"]),
                               paths["app_collisions"], names,
                               _load_json(resolved[
                                   "app_collision_authorizations"]),
                               paths["app_collision_authorizations"]),
        _app_sdk_public_entries(_load_json(resolved["app_sdk_public"]),
                                paths["app_sdk_public"], names),
        _net_entries(_load_json(resolved["net"]), paths["net"],
                     paths["sdc_benchmark"], benchmark, names,
                     machine_sdc_addresses, machine_public_addresses,
                     machine_openamp_addresses, machine_zephyr_addresses),
        _net_rtc_entries(_load_json(resolved["net_rtc"]), paths["net_rtc"], names),
        _net_sdk_public_entries(net_sdk_public,
                                paths["net_sdk_public"], names),
        _net_alias_resolution_entries(
            _load_json(resolved["net_alias_resolutions"]),
            paths["net_alias_resolutions"], names),
        _sdc_entries(sdc_catalog, paths["sdc_catalog"], names),
    )
    if net_openamp_stock is not None:
        producers += (_net_openamp_stock_entries(
            net_openamp_stock, paths["net_openamp_stock"], names),)
    if net_zephyr_stock is not None:
        producers += (_net_zephyr_stock_entries(
            net_zephyr_stock, paths["net_zephyr_stock"], names),)
    for rows in producers:
        for row in rows:
            _merge(entries, row)
    cores = {}
    for core in ("app", "net"):
        rows = sorted((row for (entry_core, _), row in entries.items()
                       if entry_core == core), key=lambda row: int(row["va"], 16))
        cores[core] = {
            "summary": {
                "entries": len(rows),
                "exclude_reconstruction": sum(
                    row["exclude_reconstruction"] for row in rows),
                "retain_reconstruction": sum(
                    not row["exclude_reconstruction"] for row in rows),
                "by_kind": {kind: sum(row["kind"] == kind for row in rows)
                            for kind in KINDS},
            },
            "entries": rows,
        }
    input_keys = ("lc3", "tinycrypt", "cc312", "crypto", "app_collisions",
                  "app_collision_authorizations",
                  "app_sdk_public",
                  "net", "net_rtc",
                  "net_sdk_public", "net_openamp_stock", "net_zephyr_stock",
                  "net_alias_resolutions",
                  "sdc_benchmark", "sdc_catalog")
    result = {
        "schema": 1,
        "generated_by": "tools/build_adoption_manifest.py",
        "identity": "core + even virtual address",
        "policy": {
            "exclusion_is_not_parity": True,
            "canonical_bodies_mutated": False,
            "cmake_mutated": False,
            "private_sdc_requires_per_va_machine_unique_identity": True,
            "default_on_ambiguity": "retain_reconstruction",
        },
        "inputs": [{"path": paths[key], "sha256": _sha256(resolved[key])}
                   for key in input_keys if key in paths],
        "sdc_benchmark": benchmark,
        "cores": cores,
    }
    validate_manifest(result)
    return result


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    for key, default in DEFAULTS.items():
        parser.add_argument("--" + key.replace("_", "-"), default=default)
    parser.add_argument("--check", action="store_true",
                        help="fail if the existing output differs; do not write")
    args = parser.parse_args(argv)
    paths = {key: getattr(args, key) for key in DEFAULTS}
    result = build(paths)
    rendered = json.dumps(result, indent=1, sort_keys=False) + "\n"
    output = _path(paths["output"])
    if args.check:
        existing = open(output).read() if os.path.exists(output) else None
        if existing != rendered:
            print("adoption manifest is stale: %s" % paths["output"], file=sys.stderr)
            return 2
        print("adoption manifest current: %s" % paths["output"])
        return 0
    os.makedirs(os.path.dirname(output), exist_ok=True)
    with open(output, "w") as stream:
        stream.write(rendered)
    for core in ("app", "net"):
        summary = result["cores"][core]["summary"]
        print("[%s] %d ownership entries: %d exclude, %d retain" %
              (core, summary["entries"], summary["exclude_reconstruction"],
               summary["retain_reconstruction"]))
    print("wrote %s" % paths["output"])
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
