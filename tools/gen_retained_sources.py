#!/usr/bin/env python3
"""Generate deterministic CMake lists of retained reconstruction sources.

The adoption manifest is the only exclusion authority.  Validated symbolized
trees are the default build inputs; canonical reconstruction trees remain an
explicit diagnostic fallback.  Sources are indexed by firmware VA so renamed
files remain safe, while an unmappable or duplicate VA fails closed instead of
silently changing the link composition.
"""

import argparse
import json
import os
import re
import sys


BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_MANIFEST = "recon/ownership/adoption_manifest.json"
DEFAULTS = {
    "app": {
        "source_dir": "recon/symbolized/app",
        "names": "recon/catalogs/function_names_app.json",
        "output": "recon/generated/app_retained_sources.cmake",
        "strict_symbolized": True,
    },
    "net": {
        "source_dir": "recon/symbolized/net",
        "names": "recon/catalogs/function_names_net.json",
        "output": "recon/generated/net_retained_sources.cmake",
        "strict_symbolized": True,
    },
}
RAW_FILE = re.compile(r"^FUN_([0-9a-fA-F]{8})$")
ENTRY_ADDRESS = re.compile(r"@\s*(0x[0-9a-fA-F]{4,8})")
SYMBOLIZED_IDENTITY = re.compile(
    r"identity:\s*FUN_([0-9a-fA-F]{8})\s*@\s*(0x[0-9a-fA-F]{8})")


def _path(value):
    return value if os.path.isabs(value) else os.path.join(BASE, value)


def _load(path):
    with open(path, encoding="utf-8") as stream:
        return json.load(stream)


def _address(value):
    return (int(value, 0) if isinstance(value, str) else int(value)) & ~1


def _name_map(path):
    data = _load(path)
    if not isinstance(data.get("by_name"), dict):
        raise ValueError("name catalog lacks by_name: %s" % path)
    return {name: _address(value) for name, value in data["by_name"].items()}


def source_address(path, names, strict_symbolized=False):
    """Resolve one source to a VA using durable identity, then its lead comment."""
    stem = os.path.splitext(os.path.basename(path))[0]
    raw = RAW_FILE.fullmatch(stem)
    raw_value = int(raw.group(1), 16) if raw else None
    # Renamed legacy files not yet present in by_name retain an entry address in
    # their leading provenance comment.  Limit the scan so callee back-maps in
    # the function body cannot be mistaken for the source identity.  When both
    # forms exist they must agree; this catches stale symbolization output.
    with open(path, encoding="utf-8", errors="replace") as stream:
        prefix = stream.read(512)
    if strict_symbolized:
        identity = SYMBOLIZED_IDENTITY.search(prefix)
        if not identity:
            raise ValueError("missing symbolized identity header for %s" % path)
        identity_va = int(identity.group(1), 16)
        if int(identity.group(2), 16) != identity_va:
            raise ValueError("inconsistent symbolized identity header for %s" % path)
        expected = raw_value if raw_value is not None else names.get(stem)
        if expected is None:
            raise ValueError("symbolized filename absent from name catalog: %s" % path)
        if expected != identity_va:
            raise ValueError(
                "symbolized filename/header conflict for %s: 0x%08x vs 0x%08x" %
                (path, expected, identity_va))
        return identity_va
    match = ENTRY_ADDRESS.search(prefix)
    if raw_value is not None:
        if match and _address(match.group(1)) != raw_value:
            raise ValueError("catalog/content VA conflict for %s: 0x%08x vs %s" %
                             (path, raw_value, match.group(1)))
        return raw_value
    # For renamed sources the explicit leading provenance is authoritative.
    # A by_name entry can legitimately select a different primary when this
    # filename is also a legacy alias (for example a tail thunk).
    if match:
        return _address(match.group(1))
    if stem in names:
        return names[stem]
    if not match:
        raise ValueError("no VA mapping for canonical source %s" % path)
    raise AssertionError("unreachable")


def index_sources(source_dir, names_path, strict_symbolized=False):
    names = _name_map(names_path)
    by_va = {}
    for filename in sorted(os.listdir(source_dir)):
        if not filename.endswith(".c"):
            continue
        path = os.path.join(source_dir, filename)
        if not os.path.isfile(path):
            continue
        va = source_address(path, names, strict_symbolized)
        if va in by_va:
            raise ValueError("ambiguous canonical VA 0x%08x: %s and %s" %
                             (va, by_va[va], path))
        by_va[va] = path
    return by_va


def _report_only_sdc(row):
    if row.get("component") != "softdevice_controller":
        return False
    for evidence in row.get("evidence", []):
        if evidence.get("per_va_unique_identity") is False:
            return True
        if evidence.get("type") == "sdc_archive_benchmark_summary":
            return True
    return False


def exclusions(manifest, core):
    try:
        rows = manifest["cores"][core]["entries"]
    except (KeyError, TypeError):
        raise ValueError("manifest lacks cores.%s.entries" % core)
    result = set()
    seen = set()
    for row in rows:
        if row.get("core") != core:
            raise ValueError("wrong core in %s manifest row: %r" % (core, row))
        va = _address(row["va"])
        if va in seen:
            raise ValueError("duplicate manifest identity %s 0x%08x" % (core, va))
        seen.add(va)
        exclude = row.get("exclude_reconstruction")
        if not isinstance(exclude, bool):
            raise ValueError("non-boolean exclusion for %s 0x%08x" % (core, va))
        if exclude and _report_only_sdc(row):
            raise ValueError("unsafe report-only SDC exclusion at 0x%08x" % va)
        if exclude:
            result.add(va)
    return result


def render(core, source_dir, output_path, retained, excluded_rows, matched):
    rel_source = os.path.relpath(
        source_dir, os.path.dirname(output_path)).replace(os.sep, "/")
    lines = [
        "# Generated by tools/gen_retained_sources.py; do not edit.",
        "# Core: %s; retained: %d; manifest exclusions: %d; matched sources: %d." %
        (core, len(retained), excluded_rows, matched),
        "set(G1_RETAINED_SOURCES",
    ]
    for path in retained:
        filename = os.path.basename(path)
        lines.append('  "${CMAKE_CURRENT_LIST_DIR}/%s/%s"' %
                     (rel_source, filename))
    lines.extend((")", ""))
    return "\n".join(lines)


def build(manifest_path, configs=None):
    manifest = _load(manifest_path)
    configs = configs or DEFAULTS
    outputs = {}
    for core in ("app", "net"):
        config = configs[core]
        source_dir = _path(config["source_dir"])
        source_index = index_sources(source_dir, _path(config["names"]),
                                     config.get("strict_symbolized", False))
        excluded = exclusions(manifest, core)
        matched = excluded.intersection(source_index)
        retained = [source_index[va] for va in sorted(source_index)
                    if va not in excluded]
        output_path = _path(config["output"])
        outputs[output_path] = render(
            core, source_dir, output_path, retained, len(excluded), len(matched))
    return outputs


def update(outputs, check=False):
    stale = []
    for path, content in sorted(outputs.items()):
        old = None
        try:
            with open(path, encoding="utf-8") as stream:
                old = stream.read()
        except FileNotFoundError:
            pass
        if old == content:
            continue
        stale.append(os.path.relpath(path, BASE))
        if not check:
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w", encoding="utf-8", newline="\n") as stream:
                stream.write(content)
    if check and stale:
        raise ValueError("generated retained source lists are stale: %s" %
                         ", ".join(stale))
    return stale


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", default=DEFAULT_MANIFEST)
    parser.add_argument("--check", action="store_true",
                        help="fail if generated output differs; write nothing")
    parser.add_argument(
        "--source-tree", choices=("symbolized", "canonical"),
        default="symbolized",
        help="build input tree (canonical is an explicit diagnostic fallback)")
    args = parser.parse_args(argv)
    configs = DEFAULTS
    if args.source_tree == "canonical":
        configs = {core: dict(values) for core, values in DEFAULTS.items()}
        for core in ("app", "net"):
            configs[core]["source_dir"] = "recon/%s/src" % core
            configs[core]["strict_symbolized"] = False
    try:
        changed = update(build(_path(args.manifest), configs), args.check)
    except (OSError, ValueError, KeyError, json.JSONDecodeError) as error:
        print("error: %s" % error, file=sys.stderr)
        return 1
    if args.check:
        print("retained source lists are current")
    else:
        print("updated %d retained source list(s)" % len(changed))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
