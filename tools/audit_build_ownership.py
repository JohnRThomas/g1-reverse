#!/usr/bin/env python3
"""Audit final-build symbol ownership against the upstream adoption manifest.

The auditor is deliberately read-only and fail-closed.  It can consume an nm
listing, a GNU ld map, and/or compile_commands.json.  Missing build artifacts
are reported as unavailable evidence, not as ownership failures.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import shlex
import subprocess
import sys
from collections import defaultdict
from dataclasses import dataclass, asdict
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RAW_SYMBOL = re.compile(r"^(?:FUN|DAT|PTR|LAB)_[0-9A-Fa-f]{8}$")
NM_LINE = re.compile(
    r"^(?P<origin>.+?):(?P<address>[0-9A-Fa-f]+)\s+"
    r"(?:(?P<size>[0-9A-Fa-f]+)\s+)?(?P<type>[A-Za-z?])\s+(?P<symbol>\S+)$")
MAP_SECTION = re.compile(
    r"^\s*\.(?:text|rodata|data|bss)(?:\.(?P<section_symbol>\S+))?\s+"
    r"0x[0-9A-Fa-f]+\s+0x[0-9A-Fa-f]+\s+(?P<origin>\S.*)$")
MAP_SYMBOL = re.compile(r"^\s*0x[0-9A-Fa-f]+\s+(?P<symbol>[^\s=]+)\s*$")
MAP_SECTION_START = re.compile(
    r"^\s+\.(?:text|rodata|data|bss)(?:\.\S+)?\s*$")
MAP_SECTION_BODY = re.compile(
    r"^\s*0x[0-9A-Fa-f]+\s+0x[0-9A-Fa-f]+\s+(?P<origin>\S.*)$")


@dataclass(frozen=True)
class Definition:
    symbol: str
    origin: str
    owner_class: str
    source: str | None
    evidence: str


def _norm(path: str, base: Path | None = None) -> str:
    value = path.strip().strip('"')
    if base and value and not os.path.isabs(value):
        value = str((base / value).resolve())
    return os.path.normpath(value)


def _output_from_command(row: dict, base: Path) -> str | None:
    args = row.get("arguments")
    if args is None:
        try:
            args = shlex.split(row.get("command", ""))
        except ValueError:
            return None
    for index, arg in enumerate(args):
        if arg == "-o" and index + 1 < len(args):
            return _norm(args[index + 1], Path(row.get("directory", base)))
        if arg.startswith("-o") and len(arg) > 2:
            return _norm(arg[2:], Path(row.get("directory", base)))
    return None


def read_compile_commands(path: Path) -> tuple[dict[str, str], list[str]]:
    """Return object->source provenance and warnings."""
    rows = json.loads(path.read_text())
    if not isinstance(rows, list):
        raise ValueError("compile_commands must contain a JSON array")
    mapping: dict[str, str] = {}
    warnings: list[str] = []
    for row in rows:
        directory = Path(row.get("directory", path.parent))
        source = _norm(row.get("file", ""), directory)
        output = row.get("output")
        output = _norm(output, directory) if output else _output_from_command(row, path.parent)
        if not output:
            warnings.append("compile command has no output for %s" % source)
            continue
        mapping[output] = source
        mapping[os.path.basename(output)] = source
    return mapping, warnings


def owner_class(origin: str, source: str | None) -> str:
    probe = (source or origin).replace("\\", "/")
    if re.search(r"/(?:recon)/(?:app|net)/(?:src|named|symbolized)(?:/|$)", probe):
        return "reconstruction"
    if "/recon/verified/src/" in probe:
        return "reconstruction"
    if source:
        return "upstream"
    if "/recon/" in probe or re.search(r"(?:^|/)FUN_[0-9A-Fa-f]{8}\.o$", probe):
        return "reconstruction"
    if ".a(" in probe or probe.endswith((".a", ".o", ".obj")):
        return "upstream"
    return "unknown"


def _source_for_origin(origin: str, object_sources: dict[str, str]) -> str | None:
    candidates = [origin, os.path.normpath(origin), os.path.basename(origin)]
    # nm archive origins look like lib.a:member.o or lib.a(member.o).
    if ":" in origin:
        candidates.append(origin.rsplit(":", 1)[0])
    for candidate in candidates:
        if candidate in object_sources:
            return object_sources[candidate]
    return None


def parse_nm(text: str, object_sources: dict[str, str], evidence: str) -> tuple[list[Definition], set[str]]:
    definitions: list[Definition] = []
    undefined: set[str] = set()
    for line in text.splitlines():
        line = line.strip()
        if not line:
            continue
        match = NM_LINE.match(line)
        if not match:
            # Also accept traditional undefined lines: origin: U symbol.
            undef = re.match(r"^(?P<origin>.+?):\s+U\s+(?P<symbol>\S+)$", line)
            if undef:
                undefined.add(undef.group("symbol"))
            continue
        if match.group("type").upper() == "U":
            undefined.add(match.group("symbol"))
            continue
        # Only externally linkable definitions participate in build ownership.
        # Lower-case nm types are locals; N/n/a and section/file names are ELF
        # metadata, not multiply-defined program symbols.
        symbol_type = match.group("type")
        if not symbol_type.isupper() or symbol_type in {"N", "U"}:
            continue
        if match.group("symbol").startswith("."):
            continue
        origin = match.group("origin")
        source = _source_for_origin(origin, object_sources)
        definitions.append(Definition(match.group("symbol"), origin,
                                      owner_class(origin, source), source, evidence))
    return definitions, undefined


def parse_map(text: str, object_sources: dict[str, str], evidence: str) -> list[Definition]:
    definitions: list[Definition] = []
    current_origin: str | None = None
    pending_section = False
    for line in text.splitlines():
        section = MAP_SECTION.match(line)
        if section:
            current_origin = section.group("origin").strip()
            pending_section = False
            continue
        # GNU ld wraps long input-section names onto a line of their own. Reset
        # provenance immediately, then accept the address/size/object line that
        # follows. Without this, every later explicit symbol inherits the last
        # short section's object (observed as idle.c.obj in the real net map).
        if MAP_SECTION_START.match(line):
            current_origin = None
            pending_section = True
            continue
        if pending_section:
            body = MAP_SECTION_BODY.match(line)
            pending_section = False
            if body:
                current_origin = body.group("origin").strip()
            continue
        # Any other input/output section starts a new provenance domain. We do
        # not inspect debug, comment, attributes, linker metadata, or fill rows.
        if re.match(r"^\s+\.\S+", line) or re.match(r"^\.\S+", line):
            current_origin = None
            pending_section = False
            continue
        symbol = MAP_SYMBOL.match(line)
        if symbol and current_origin:
            name = symbol.group("symbol")
            if not name.startswith(('.', '*')):
                source = _source_for_origin(current_origin, object_sources)
                definitions.append(Definition(name, current_origin,
                                              owner_class(current_origin, source),
                                              source, evidence))
    return definitions


def _expected_units(entry: dict) -> set[str]:
    units = set()
    def add_unit(value: str) -> None:
        value = value.strip()
        # Strip map address/size prefixes, then retain both archive and member
        # identities. Exact archive catalogs may append :section[...] metadata.
        value = re.sub(r"^0x[0-9A-Fa-f]+\s+0x[0-9A-Fa-f]+\s+", "", value)
        archive = re.search(r"([^/\s]+\.a)\(([^)]+)\)", value)
        if archive:
            units.add("%s(%s)" % (archive.group(1), archive.group(2)))
            units.add(archive.group(2))
            return
        value = value.split(":section[", 1)[0]
        units.add(os.path.basename(value))

    unit = entry.get("upstream_unit")
    if unit and not unit.startswith(".text "):
        add_unit(unit)
    for item in entry.get("evidence", []):
        for key in ("member", "object", "unit"):
            if item.get(key):
                add_unit(str(item[key]))
    return units


def _definition_matches_unit(definition: Definition, units: set[str]) -> bool:
    if not units:
        return True
    probe = " ".join(filter(None, (definition.origin, definition.source)))
    composites = {unit for unit in units if ".a(" in unit}
    candidates = composites if ".a(" in probe and composites else units - composites
    for unit in candidates:
        variants = {unit}
        if unit.endswith((".obj", ".o")):
            variants.add(unit.rsplit(".", 1)[0])
        if any(variant in probe for variant in variants):
            return True
    return False


def audit(manifest: dict, core: str, definitions: list[Definition],
          undefined: set[str], artifact_evidence: bool,
          complete_evidence: bool | None = None) -> dict:
    if complete_evidence is None:
        complete_evidence = artifact_evidence
    by_symbol: dict[str, list[Definition]] = defaultdict(list)
    unique = {(d.symbol, d.origin, d.owner_class, d.source, d.evidence): d for d in definitions}
    definitions = sorted(unique.values(), key=lambda d: (d.symbol, d.origin, d.evidence))
    for definition in definitions:
        by_symbol[definition.symbol].append(definition)

    collisions = []
    for symbol, defs in sorted(by_symbol.items()):
        classes = {item.owner_class for item in defs}
        if {"reconstruction", "upstream"} <= classes:
            collisions.append({"symbol": symbol, "definitions": [asdict(item) for item in defs]})

    excluded_present = []
    missing = []
    wrong_owner = []
    inconclusive_owner = []
    checked = 0
    entries = manifest.get("cores", {}).get(core, {}).get("entries", [])
    for entry in entries:
        if not entry.get("exclude_reconstruction"):
            continue
        checked += 1
        names = {entry.get("raw_symbol"), entry.get("current_symbol"), entry.get("upstream_symbol")}
        names.discard(None)
        found = [item for name in names for item in by_symbol.get(name, [])]
        recon = [item for item in found if item.owner_class == "reconstruction"]
        if recon:
            excluded_present.append({"va": entry["va"], "component": entry["component"],
                                     "symbols": sorted({item.symbol for item in recon}),
                                     "definitions": [asdict(item) for item in recon]})
        if not complete_evidence:
            continue
        upstream = [item for item in found if item.owner_class == "upstream"]
        unknown = [item for item in found if item.owner_class == "unknown"]
        units = _expected_units(entry)
        # A file-static helper is adopted with its complete source unit and is
        # intentionally absent from global nm output. Presence of that exact
        # compiled unit is the ownership evidence for this entry.
        if entry.get("kind") == "static_helper" and units:
            upstream = [item for item in definitions
                        if item.owner_class == "upstream" and
                        _definition_matches_unit(item, units)]
        if not upstream and unknown:
            inconclusive_owner.append({"va": entry["va"], "component": entry["component"],
                                       "reason": "definition exists but merged artifact has no object provenance",
                                       "definitions": [asdict(item) for item in unknown]})
        elif not upstream:
            missing.append({"va": entry["va"], "component": entry["component"],
                            "expected_symbols": sorted(names), "expected_units": sorted(units)})
        elif units and not any(_definition_matches_unit(item, units) for item in upstream):
            wrong_owner.append({"va": entry["va"], "component": entry["component"],
                                "expected_units": sorted(units),
                                "definitions": [asdict(item) for item in upstream]})

    raw = [{"symbol": item.symbol, "origin": item.origin,
            "owner_class": item.owner_class, "source": item.source}
           for item in definitions if RAW_SYMBOL.match(item.symbol)]
    raw_undefined = sorted(symbol for symbol in undefined if RAW_SYMBOL.match(symbol))
    violations = len(collisions) + len(excluded_present) + len(missing) + len(wrong_owner) + len(raw_undefined)
    if violations:
        status = "fail"
    elif complete_evidence:
        status = "pass"
    elif artifact_evidence:
        status = "partial"
    else:
        status = "unavailable"
    return {
        "schema": 1,
        "core": core,
        "status": status,
        "evidence_available": artifact_evidence,
        "evidence_complete": complete_evidence,
        "summary": {
            "definitions": len(definitions), "excluded_entries_checked": checked,
            "collisions": len(collisions),
            "excluded_reconstructions_present": len(excluded_present),
            "excluded_owners_missing": len(missing), "wrong_owners": len(wrong_owner),
            "inconclusive_owners": len(inconclusive_owner),
            "raw_defined_symbols": len(raw), "raw_undefined_symbols": len(raw_undefined),
            "violations": violations,
        },
        "collisions": collisions,
        "excluded_reconstructions_present": excluded_present,
        "excluded_owners_missing": missing,
        "wrong_owners": wrong_owner,
        "inconclusive_owners": inconclusive_owner,
        # Defined raw names are inventory: retained reconstruction may legitimately
        # retain a reversible FUN_* alias. Undefined raw names are failures.
        "raw_defined_symbols": raw,
        "raw_undefined_symbols": raw_undefined,
    }


def _run_nm(nm: str, objects: list[str]) -> str:
    # -g excludes local/section/file pseudo-symbols while retaining undefined
    # globals, which are needed for raw-address residue checks.
    command = [nm, "-A", "-g", "-S"] + objects
    result = subprocess.run(command, text=True, capture_output=True)
    if result.returncode:
        raise RuntimeError("nm failed: %s" % result.stderr.strip())
    return result.stdout


def _run_nm_batched(nm: str, objects: list[str], batch_size: int = 200) -> str:
    return "".join(_run_nm(nm, objects[index:index + batch_size])
                   for index in range(0, len(objects), batch_size))


def concise_report(report: dict, output: Path | None = None, limit: int = 8) -> str:
    summary = report["summary"]
    lines = [
        "ownership audit %s: %s (evidence: %s)" %
        (report["core"], report["status"].upper(),
         "complete" if report["evidence_complete"] else
         ("partial" if report["evidence_available"] else "unavailable")),
        ("definitions=%d collisions=%d excluded-present=%d missing=%d "
         "wrong-owner=%d inconclusive=%d raw-defined=%d raw-undefined=%d") %
        (summary["definitions"], summary["collisions"],
         summary["excluded_reconstructions_present"], summary["excluded_owners_missing"],
         summary["wrong_owners"], summary["inconclusive_owners"],
         summary["raw_defined_symbols"], summary["raw_undefined_symbols"]),
    ]
    findings = []
    findings.extend("collision %s" % item["symbol"] for item in report["collisions"])
    findings.extend("excluded reconstruction %s" % item["va"]
                    for item in report["excluded_reconstructions_present"])
    findings.extend("missing owner %s" % item["va"] for item in report["excluded_owners_missing"])
    findings.extend("wrong owner %s" % item["va"] for item in report["wrong_owners"])
    findings.extend("raw undefined %s" % item for item in report["raw_undefined_symbols"])
    for finding in findings[:limit]:
        lines.append("  " + finding)
    if len(findings) > limit:
        lines.append("  ... %d more violation(s)" % (len(findings) - limit))
    for warning in report.get("warnings", [])[:limit]:
        lines.append("warning: " + warning)
    if output:
        lines.append("full report: %s" % output)
    return "\n".join(lines) + "\n"


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", type=Path, default=DEFAULT_MANIFEST)
    parser.add_argument("--core", choices=("app", "net"), required=True)
    parser.add_argument("--compile-commands", type=Path)
    parser.add_argument("--nm-file", type=Path, action="append", default=[])
    parser.add_argument("--map", dest="maps", type=Path, action="append", default=[])
    parser.add_argument("--object", action="append", default=[], help="object/archive/ELF to inspect with nm")
    parser.add_argument("--nm", default="/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-nm")
    parser.add_argument("--output", type=Path)
    parser.add_argument("--json", action="store_true", help="print the complete JSON report to stdout")
    parser.add_argument("--strict-artifacts", action="store_true",
                        help="return failure when no symbol-bearing artifact exists")
    args = parser.parse_args(argv)

    manifest = json.loads(args.manifest.read_text())
    object_sources: dict[str, str] = {}
    warnings: list[str] = []
    if args.compile_commands:
        if args.compile_commands.exists():
            object_sources, warnings = read_compile_commands(args.compile_commands)
        else:
            warnings.append("compile_commands unavailable: %s" % args.compile_commands)

    definitions: list[Definition] = []
    undefined: set[str] = set()
    evidence_files: list[str] = []
    complete_evidence = False
    for path in args.nm_file:
        if not path.exists():
            warnings.append("nm listing unavailable: %s" % path)
            continue
        found, undef = parse_nm(path.read_text(), object_sources, str(path))
        definitions.extend(found); undefined.update(undef); evidence_files.append(str(path))
        complete_evidence = True
    for path in args.maps:
        if not path.exists():
            warnings.append("linker map unavailable: %s" % path)
            continue
        definitions.extend(parse_map(path.read_text(errors="replace"), object_sources, str(path)))
        evidence_files.append(str(path))
        complete_evidence = True
    # A configured compile database supplies the most reliable reconstruction
    # versus upstream classification. Inspect its objects automatically once a
    # complete set exists; a partial object set remains useful but cannot prove
    # that an expected owner is missing.
    command_objects = sorted({key for key in object_sources
                              if os.path.isabs(key) and Path(key).exists()})
    absolute_outputs = sorted({key for key in object_sources if os.path.isabs(key)})
    if command_objects:
        found, _ = parse_nm(_run_nm_batched(args.nm, command_objects), object_sources,
                                "compile_commands objects")
        definitions.extend(found); evidence_files.extend(command_objects)
        complete_evidence = complete_evidence or len(command_objects) == len(absolute_outputs)
    existing_objects = [item for item in args.object if Path(item).exists()]
    for item in args.object:
        if not Path(item).exists():
            warnings.append("object unavailable: %s" % item)
    if existing_objects:
        found, undef = parse_nm(_run_nm_batched(args.nm, existing_objects), object_sources, "nm")
        definitions.extend(found)
        # Undefined symbols in individual .o/.a inputs are ordinary references
        # that the final link resolves. Only a merged ELF can prove residue.
        if all(Path(item).suffix == ".elf" for item in existing_objects):
            undefined.update(undef)
        evidence_files.extend(existing_objects)

    report = audit(manifest, args.core, definitions, undefined, bool(evidence_files), complete_evidence)
    report["inputs"] = {"manifest": str(args.manifest), "evidence": sorted(evidence_files),
                        "compile_commands": str(args.compile_commands) if args.compile_commands else None}
    report["warnings"] = warnings
    rendered = json.dumps(report, indent=2, sort_keys=True) + "\n"
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(rendered)
    if args.json:
        print(rendered, end="")
    else:
        print(concise_report(report, args.output), end="")
    if report["summary"]["violations"]:
        return 1
    if args.strict_artifacts and not report["evidence_complete"]:
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
