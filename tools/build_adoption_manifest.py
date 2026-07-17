#!/usr/bin/env python3
"""Build the fail-closed upstream adoption/exclusion manifest.

This tool does not edit reconstruction sources or build files.  It turns the
reviewed ownership catalogs into deterministic address-keyed decisions for a
later CMake/source-selection pass.  An ownership claim and permission to omit a
reconstruction are deliberately separate fields.
"""

import argparse
import hashlib
import json
import os
import re
import sys


BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULTS = {
    "lc3": "recon/catalogs/lc3_ownership_app.json",
    "tinycrypt": "recon/analysis/tinycrypt_pinned_matches.json",
    "cc312": "recon/catalogs/cc312_archive_ownership.json",
    "crypto": "recon/catalogs/upstream_crypto_ownership.json",
    "net": "recon/ownership/net_function_ownership.json",
    "sdc_benchmark": "recon/ownership/net_sdc_archive_benchmark.md",
    "app_names": "recon/catalogs/function_names_app.json",
    "net_names": "recon/catalogs/function_names_net.json",
    "output": "recon/ownership/adoption_manifest.json",
}
KINDS = ("source", "archive", "static_helper", "table", "glue")
KIND_RANK = {"source": 1, "archive": 2, "table": 3,
             "static_helper": 4, "glue": 5}


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
        eligible = row.get("confidence") == "high" and row.get("match_score", 0) >= 0.90
        output.append(_entry(
            "app", row["address"], names, kind, "liblc3", upstream,
            row.get("upstream_file"), eligible,
            ("Pinned libLC3 source ownership has explicit high-confidence "
             "function evidence." if eligible else
             "LC3 candidate lacks the high-confidence score required for exclusion."),
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


def _net_entries(data, source, benchmark_source, benchmark, names):
    output = []
    for va, row in sorted(data.get("entries", {}).items()):
        match = row.get("signature_match")
        provenance = (match or {}).get("provenance", "")
        symbol = (match or {}).get("symbol")
        ratio = (match or {}).get("ratio")
        threshold = (match or {}).get("threshold")
        is_sdc = "softdevice_controller" in provenance
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
            "softdevice_controller" if is_sdc else "net_sdk_or_glue",
            symbol, provenance or None, eligible, reason, evidence,
            row.get("confidence")))
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
    if errors:
        raise ValueError("invalid adoption manifest:\n" + "\n".join(errors))


def build(paths):
    resolved = {key: _path(value) for key, value in paths.items()}
    names = {"app": _name_records(resolved["app_names"]),
             "net": _name_records(resolved["net_names"])}
    benchmark = _parse_sdc_benchmark(resolved["sdc_benchmark"])
    entries = {}
    producers = (
        _lc3_entries(_load_json(resolved["lc3"]), paths["lc3"], names),
        _tinycrypt_entries(_load_json(resolved["tinycrypt"]), paths["tinycrypt"], names),
        _cc312_entries(_load_json(resolved["cc312"]), paths["cc312"], names),
        _crypto_entries(_load_json(resolved["crypto"]), paths["crypto"], names),
        _net_entries(_load_json(resolved["net"]), paths["net"],
                     paths["sdc_benchmark"], benchmark, names),
    )
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
    input_keys = ("lc3", "tinycrypt", "cc312", "crypto", "net", "sdc_benchmark")
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
                   for key in input_keys],
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
