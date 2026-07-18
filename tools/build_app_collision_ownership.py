#!/usr/bin/env python3
"""Turn a retain-all CPUAPP link failure into fail-closed ownership evidence.

The linker collision proves that the configured SDK build selected a strong
definition.  It does *not* prove that a similarly named firmware function is
the same implementation: stale names and Kconfig-dependent bodies are common.
This tool therefore combines the real link diagnostic with the exact selected
object's DWARF ABI and a firmware/object instruction-shape comparison.

Run from /tmp because the repository contains a local ``struct.py``::

  PYTHONSAFEPATH=1 .../.venv/bin/python .../tools/build_app_collision_ownership.py \
    --link-log /tmp/g1_app_link.log --index /tmp/g1_app_index.json
"""

import argparse
import difflib
import gzip
import hashlib
import json
import os
import re
import subprocess
import sys

from elftools.elf.elffile import ELFFile

sys.path.insert(0, os.path.dirname(__file__))
from build_upstream_index import extract_features
import extract


BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_NAMES = os.path.join(BASE, "recon/catalogs/function_names_app.json")
DEFAULT_CLASSIFIED = os.path.join(BASE, "recon/catalogs/classified.json.gz")
DEFAULT_OUTPUT = os.path.join(BASE, "recon/ownership/app_build_collision_ownership.json")
DEFAULT_MARKDOWN = os.path.join(BASE, "recon/ownership/app_build_collision_ownership.md")
NCS = "/Users/freedomcoder/ncs251"
SOURCE_REPOS = (
    (os.path.join(NCS, "zephyr"), "zephyr"),
    (os.path.join(NCS, "nrf"), "nrf"),
    (os.path.join(NCS, "modules/hal/nordic"), "hal_nordic"),
    (os.path.join(NCS, "modules/hal/libmetal"), "libmetal"),
    (os.path.join(NCS, "modules/lib/open-amp"), "open_amp"),
)
THRESHOLDS = {"opcode": 0.90, "shape": 0.70, "length": 0.80}
ALLOWED_ACTIONS = {
    "retain_reconstruction",
    "adopt_sdk_whole_public_owner",
    "caller_cohesion",
    "blocked",
}
# These configured units contain reviewed local-only SDK helpers whose exact
# semantics must stay scoped to retained callers.  A collision in one of these
# units is never solved by inventing a public alias or duplicate helper body.
CALLER_COHESION_SOURCE_UNITS = {
    "zephyr/kernel/work.c",
    "zephyr/lib/os/heap.c",
    "zephyr/subsys/bluetooth/host/id.c",
    "zephyr/subsys/logging/log_output.c",
}
COLLISION = re.compile(
    r"^(?P<definition>.*?):\s*multiple definition of [`‘](?P<symbol>[^'’]+)['’];\s*"
    r"(?P<reconstruction>.*?):(?P<recon_source>/[^:]+):(?P<recon_line>[0-9]+): "
    r"first defined here$")
OWNER = re.compile(r"ld\.bfd:\s*(?P<input>.*?):\s*in function [`‘].*['’]:$")
SOURCE_LINE = re.compile(r"^(?P<source>/[^:]+):(?P<line>[0-9]+)$")


def sha256(path):
    digest = hashlib.sha256()
    with open(path, "rb") as stream:
        for block in iter(lambda: stream.read(1 << 16), b""):
            digest.update(block)
    return digest.hexdigest()


def load_json(path):
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt") as stream:
        return json.load(stream)


def git_commit(path):
    return subprocess.check_output(
        ["git", "-C", path, "rev-parse", "HEAD"], text=True).strip()


def source_identity(path):
    if not path or not os.path.isabs(path) or not os.path.exists(path):
        return {"path": path, "sha256": None, "repository": None, "commit": None}
    real = os.path.realpath(path)
    for root, name in SOURCE_REPOS:
        root = os.path.realpath(root)
        if real == root or real.startswith(root + os.sep):
            return {"path": os.path.relpath(real, NCS), "sha256": sha256(real),
                    "repository": name, "commit": git_commit(root)}
    return {"path": real, "sha256": sha256(real),
            "repository": "external_toolchain", "commit": None}


def parse_collisions(text):
    """Parse and aggregate strong multiple-definition diagnostics by symbol."""
    lines = text.splitlines()
    rows = []
    for index, line in enumerate(lines):
        match = COLLISION.match(line)
        if not match:
            continue
        owner_input = None
        owner_source = None
        owner_line = None
        for prior in range(index - 1, max(-1, index - 4), -1):
            owner = OWNER.search(lines[prior])
            if owner:
                owner_input = owner.group("input")
                break
        definition = match.group("definition")
        source_match = SOURCE_LINE.match(definition)
        if source_match:
            owner_source = source_match.group("source")
            owner_line = int(source_match.group("line"))
        rows.append({
            "symbol": match.group("symbol"),
            "owner_input": owner_input,
            "owner_source": owner_source,
            "owner_line": owner_line,
            "definition_location": definition,
            "reconstruction_input": match.group("reconstruction"),
            "reconstruction_source": match.group("recon_source"),
            "reconstruction_line": int(match.group("recon_line")),
            "diagnostic": line,
        })
    grouped = {}
    for row in rows:
        grouped.setdefault(row["symbol"], []).append(row)
    unique = []
    identity_fields = (
        "owner_input", "owner_source", "definition_location",
        "reconstruction_input", "reconstruction_source")
    for symbol in sorted(grouped):
        occurrences = grouped[symbol]
        for field in identity_fields:
            values = {row.get(field) for row in occurrences}
            if len(values) != 1:
                raise ValueError("ambiguous %s collision owner %s: %s" %
                                 (symbol, field, sorted(values)))
        record = dict(occurrences[0])
        record["diagnostic_occurrences"] = len(occurrences)
        record["diagnostics"] = sorted(row["diagnostic"] for row in occurrences)
        unique.append(record)
    return unique


def sequence_score(left, right):
    if not left and not right:
        return 1.0
    if not left or not right:
        return 0.0
    return difflib.SequenceMatcher(None, left, right, autojunk=False).ratio()


def candidate_code_features(candidate, firmware_extent):
    """Compare code, not an ELF function section's trailing literal pool.

    Zephyr emits each function into its own ``.text.<symbol>`` section.  GCC
    accounts embedded literal pools and their alignment in the ELF symbol
    size, even though Ghidra's firmware extent ends at the final reachable
    Thumb instruction.  Treating those words as Thumb instructions produces
    false-negative ownership scores.  The firmware extent remains the
    authoritative cap; a shorter/missing selected section fails closed.
    """
    path = (candidate or {}).get("object")
    section_name = (candidate or {}).get("section")
    if not path or not section_name or not os.path.exists(path):
        return None, None
    with open(path, "rb") as stream:
        section = ELFFile(stream).get_section_by_name(section_name)
        if section is None:
            return None, None
        data = section.data()
    extent = int(firmware_extent)
    if extent <= 0 or len(data) < extent:
        return None, len(data)
    return extract_features(data[:extent], 0), len(data)


def safe_to_exclude(candidate, scores):
    blockers = []
    if candidate is None:
        blockers.append("selected_owner_not_indexed")
    else:
        if candidate.get("binding") != "STB_GLOBAL":
            blockers.append("owner_not_global_strong")
        if not candidate.get("signature"):
            blockers.append("missing_dwarf_abi")
        if scores["opcode"] < THRESHOLDS["opcode"]:
            blockers.append("opcode_score_below_threshold")
        if scores["shape"] < THRESHOLDS["shape"]:
            blockers.append("operand_shape_score_below_threshold")
        if scores["length"] < THRESHOLDS["length"]:
            blockers.append("instruction_length_score_below_threshold")
    return not blockers, blockers


def choose_candidate(records, collision):
    candidates = [row for row in records if row["name"] == collision["symbol"]]
    candidates = [row for row in candidates
                  if "/Projects/G1disasm2/" not in (row.get("source") or "")]
    candidates = [row for row in candidates if "/hci_rpmsg/" not in row["object"]]
    source = collision.get("owner_source")
    if source:
        exact = [row for row in candidates
                 if os.path.realpath(row.get("source") or "") == os.path.realpath(source)]
        if exact:
            candidates = exact
    owner = collision.get("owner_input") or ""
    member_match = re.search(r"\(([^()]+)\)$", owner)
    if member_match:
        member = member_match.group(1)
        exact = [row for row in candidates if os.path.basename(row["object"]) == member]
        if exact:
            candidates = exact
    candidates.sort(key=lambda row: row["id"])
    if len(candidates) == 1:
        return candidates[0], []
    return (candidates[0] if candidates else None,
            [row["id"] for row in candidates[1:]])


def normalize_repo_path(path):
    if not path:
        return None
    real = os.path.realpath(path)
    base = os.path.realpath(BASE)
    if real == base or real.startswith(base + os.sep):
        return os.path.relpath(real, base)
    ncs = os.path.realpath(NCS)
    if real == ncs or real.startswith(ncs + os.sep):
        return os.path.relpath(real, ncs)
    return path


def split_owner_input(owner_input):
    """Return the exact selected archive/object and optional archive member."""
    owner_input = owner_input or ""
    match = re.match(r"^(?P<archive>.*\.a)\((?P<member>[^()]+)\)$", owner_input)
    if match:
        return {"archive_or_object": match.group("archive"),
                "archive_member": match.group("member")}
    return {"archive_or_object": owner_input or None, "archive_member": None}


def action_for(source_unit, candidate, alternatives, safe):
    if safe:
        return "adopt_sdk_whole_public_owner"
    if candidate is None or alternatives or not candidate.get("signature"):
        return "blocked"
    if source_unit in CALLER_COHESION_SOURCE_UNITS:
        return "caller_cohesion"
    return "retain_reconstruction"


def build_batches(functions):
    grouped = {}
    for row in functions:
        grouped.setdefault(row["implementation_source_unit"], []).append(row)
    batches = []
    for ordinal, source_unit in enumerate(sorted(grouped), 1):
        rows = sorted(grouped[source_unit], key=lambda row: int(row["va"], 16))
        actions = sorted({row["safe_action"] for row in rows})
        if "blocked" in actions:
            risk = "blocked"
        elif "caller_cohesion" in actions or len(actions) > 1:
            risk = "high"
        elif actions == ["adopt_sdk_whole_public_owner"]:
            risk = "low"
        else:
            risk = "medium"
        batches.append({
            "batch": "COLLISION-%02d" % ordinal,
            "source_unit": source_unit,
            "risk": risk,
            "actions": actions,
            "symbols": [row["current_symbol"] for row in rows],
            "count": len(rows),
            "diagnostic_occurrences": sum(
                row["diagnostic_occurrences"] for row in rows),
            "rule": ("one source unit per batch; implement only after explicit "
                     "ownership review"),
        })
    return batches


def build(args):
    names_data = load_json(args.names)
    by_name = names_data["by_name"]
    classified = {int(row["entry"]): row
                  for row in load_json(args.classified)["functions"]}
    try:
        import cfg_verify
        overrides = cfg_verify.TRUE_SIZE_OVERRIDES
    except Exception:
        overrides = {}
    index = load_json(args.index)
    text = open(args.link_log, encoding="utf-8", errors="replace").read()
    collisions = parse_collisions(text)
    functions = []
    for collision in collisions:
        symbol = collision["symbol"]
        if symbol not in by_name:
            raise ValueError("collision symbol absent from app name map: %s" % symbol)
        va = int(by_name[symbol], 16) & ~1
        catalog = classified.get(va)
        extent = overrides.get(("app", va), (catalog or {}).get("size"))
        candidate, alternatives = choose_candidate(index["records"], collision)
        firmware = None
        scores = {"opcode": 0.0, "shape": 0.0, "length": 0.0,
                  "normalized_exact": False}
        candidate_body = None
        candidate_section_size = None
        if extent and candidate:
            firmware = extract_features(extract.read(va, int(extent)), va)
            candidate_body, candidate_section_size = candidate_code_features(
                candidate, extent)
            compared = candidate_body or candidate
            scores = {
                "opcode": round(sequence_score(firmware["mnemonics"],
                                                compared["mnemonics"]), 6),
                "shape": round(sequence_score(firmware["operand_shapes"],
                                               compared["operand_shapes"]), 6),
                "length": round(min(firmware["instruction_count"],
                                    compared["instruction_count"]) /
                                max(1, firmware["instruction_count"],
                                    compared["instruction_count"]), 6),
                "normalized_exact": (firmware["normalized_sha256"] ==
                                     compared["normalized_sha256"]),
            }
        safe, blockers = safe_to_exclude(candidate, scores)
        if not extent:
            safe = False
            blockers.append("missing_firmware_extent")
        if alternatives:
            safe = False
            blockers.append("selected_owner_index_ambiguous")
        source = source_identity((candidate or {}).get("source") or
                                 collision.get("owner_source"))
        owner = split_owner_input(collision.get("owner_input"))
        source_unit = source.get("path") or owner["archive_or_object"] or "unknown"
        action = action_for(source_unit, candidate, alternatives, safe)
        object_path = (candidate or {}).get("object")
        functions.append({
            "core": "app", "va": "0x%08x" % va,
            "raw_symbol": "FUN_%08x" % va,
            "current_symbol": symbol,
            "diagnostic_occurrences": collision["diagnostic_occurrences"],
            "firmware_extent": extent,
            "firmware_instruction_count": (firmware or {}).get("instruction_count"),
            "retained_owner": {
                "va": "0x%08x" % va,
                "symbol": symbol,
                "source": normalize_repo_path(collision["reconstruction_source"]),
                "archive_or_object": collision["reconstruction_input"],
                "definition_line": collision["reconstruction_line"],
            },
            "link_provenance": {
                "owner_input": collision.get("owner_input"),
                "owner_source_line": collision.get("definition_location"),
                "reconstruction_input": collision["reconstruction_input"],
                "diagnostic_occurrences": collision["diagnostic_occurrences"],
                "diagnostics": collision["diagnostics"],
            },
            "upstream": {
                "symbol": symbol,
                "object": object_path,
                "object_sha256": (sha256(object_path)
                                   if object_path and os.path.exists(object_path)
                                   else None),
                "archive_or_object": owner["archive_or_object"],
                "archive_member": owner["archive_member"],
                "section": (candidate or {}).get("section"),
                "symbol_size": (candidate or {}).get("symbol_size"),
                "code_extent_compared": (int(extent)
                                           if candidate_body is not None else None),
                "trailing_section_bytes": (
                    candidate_section_size - int(extent)
                    if candidate_section_size is not None and extent and
                    candidate_section_size >= int(extent) else None),
                "binding": (candidate or {}).get("binding"),
                "abi": (candidate or {}).get("signature"),
                "source": source,
                "unselected_same_symbol_candidates": alternatives,
            },
            "configured_inclusion": {
                "selected_by_real_link": True,
                "indexed_object_present": bool(object_path and os.path.exists(object_path)),
                "zephyr_config_sha256": (sha256(args.config)
                                          if args.config and os.path.exists(args.config)
                                          else None),
                "proof": "strong owner named by the configured retain-all linker",
            },
            "signature_match": scores,
            "thresholds": dict(THRESHOLDS),
            "identity_threshold_candidate": safe,
            # This audit recommends actions but deliberately grants no source
            # exclusion authority.  build_adoption_manifest.py consumes only
            # an explicit true safe_to_exclude value.
            "safe_to_exclude": False,
            "exclusion_blockers": sorted(set(blockers)),
            "safe_action": action,
            "decision": action,
            "implementation_source_unit": source_unit,
        })
    functions.sort(key=lambda row: int(row["va"], 16))
    batches = build_batches(functions)
    by_action = {action: sum(row["safe_action"] == action for row in functions)
                 for action in sorted(ALLOWED_ACTIONS)}
    by_risk = {risk: sum(batch["risk"] == risk for batch in batches)
               for risk in ("low", "medium", "high", "blocked")}
    result = {
        "schema": 2,
        "generated_by": "tools/build_app_collision_ownership.py",
        "policy": {
            "strong_collision_alone_is_insufficient": True,
            "requires_selected_global_object": True,
            "requires_dwarf_abi": True,
            "thresholds": dict(THRESHOLDS),
            "ambiguity_action": "blocked",
            "allowed_actions": sorted(ALLOWED_ACTIONS),
            "no_implementation_mutations_authorized": True,
            "batch_partition": "one non-overlapping batch per selected source unit",
        },
        "inputs": {
            "link_log_sha256": sha256(args.link_log),
            "upstream_index_sha256": sha256(args.index),
            "names_sha256": sha256(args.names),
            "classified_sha256": sha256(args.classified),
            "build_root": index.get("build_root"),
            "zephyr_config_sha256": (sha256(args.config)
                                      if args.config and os.path.exists(args.config)
                                      else None),
        },
        "summary": {
            "collisions": len(functions),
            "unique_symbols": len(functions),
            "diagnostic_occurrences": sum(
                row["diagnostic_occurrences"] for row in functions),
            "identity_threshold_candidates": sum(
                row["identity_threshold_candidate"] for row in functions),
            "safe_to_exclude": 0,
            "retained_fail_closed": len(functions),
            "source_units": len(batches),
            "batches": len(batches),
            "by_action": by_action,
            "batches_by_risk": by_risk,
        },
        "functions": functions,
        "implementation_batches": batches,
    }
    if args.relink_log:
        relink_text = open(args.relink_log, encoding="utf-8",
                           errors="replace").read()
        actual = {row["symbol"] for row in parse_collisions(relink_text)}
        expected = {row["current_symbol"] for row in functions
                    if not row["safe_to_exclude"]}
        result["relink_validation"] = {
            "log_sha256": sha256(args.relink_log),
            "expected_retained_collisions": len(expected),
            "actual_retained_collisions": len(actual),
            "exact_set_match": actual == expected,
            "unexpected_collisions": sorted(actual - expected),
            "missing_expected_collisions": sorted(expected - actual),
        }
        if actual != expected:
            raise ValueError("post-exclusion collision set differs from fail-closed plan")
    return result


def render_markdown(result):
    summary = result["summary"]
    lines = [
        "# CPUAPP retain-all collision ownership",
        "",
        "Deterministic report-only audit of the current real retain-all link.",
        "It does not authorize source removal, aliases, CMake changes, or weak owners.",
        "",
        "## Current snapshot",
        "",
        "| Metric | Count |",
        "|---|---:|",
        "| Strong duplicate symbols | %d |" % summary["unique_symbols"],
        "| Diagnostic occurrences | %d |" % summary["diagnostic_occurrences"],
        "| Selected source units / batches | %d |" % summary["source_units"],
        "| Exact-threshold SDK adoption candidates | %d |" %
        summary["identity_threshold_candidates"],
        "| Automatically authorized exclusions | %d |" % summary["safe_to_exclude"],
        "| Fail-closed retained/other | %d |" % summary["retained_fail_closed"],
        "",
        "## Safe-action partition",
        "",
        "| Action | Symbols |",
        "|---|---:|",
    ]
    for action, count in sorted(summary["by_action"].items()):
        lines.append("| `%s` | %d |" % (action, count))
    lines += [
        "",
        "`adopt_sdk_whole_public_owner` is only a candidate when the selected",
        "global object has DWARF ABI evidence and clears every configured shape",
        "threshold. `caller_cohesion` keeps local SDK helpers scoped to callers;",
        "`blocked` has missing or ambiguous indexed ownership.",
        "",
        "## Non-overlapping implementation batches",
        "",
        "| Batch | Source unit | Risk | Symbols | Actions |",
        "|---|---|---|---:|---|",
    ]
    for batch in result["implementation_batches"]:
        lines.append("| `{batch}` | `{source_unit}` | `{risk}` | {count} | {actions} |".format(
            batch=batch["batch"], source_unit=batch["source_unit"],
            risk=batch["risk"], count=batch["count"],
            actions=", ".join("`%s`" % action for action in batch["actions"])))
    lines += [
        "",
        "Each source unit occurs in exactly one batch. Symbols remain individually",
        "address-keyed in the JSON with retained source/VA, exact selected archive",
        "and object hashes, configured-link proof, ABI, and instruction-shape evidence.",
        "",
    ]
    return "\n".join(lines)


def self_test():
    text = ("ld.bfd: zephyr/lib.a(foo.c.obj): in function `foo':\n"
            "/ncs/foo.c:7: multiple definition of `foo'; "
            "app/libapp.a(foo.c.obj):/repo/foo.c:3: first defined here\n")
    rows = parse_collisions(text)
    assert len(rows) == 1 and rows[0]["owner_input"] == "zephyr/lib.a(foo.c.obj)"
    assert rows[0]["diagnostic_occurrences"] == 1
    candidate = {"binding": "STB_GLOBAL", "signature": {"return": "int"}}
    ok, blockers = safe_to_exclude(candidate, {"opcode": .95, "shape": .9,
                                               "length": .9})
    assert ok and not blockers
    ok, blockers = safe_to_exclude(candidate, {"opcode": .2, "shape": .9,
                                               "length": .9})
    assert not ok and "opcode_score_below_threshold" in blockers
    print("build_app_collision_ownership self-test: PASS")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--link-log")
    parser.add_argument("--index")
    parser.add_argument("--names", default=DEFAULT_NAMES)
    parser.add_argument("--classified", default=DEFAULT_CLASSIFIED)
    parser.add_argument("--config")
    parser.add_argument("--relink-log",
                        help="post-exclusion link log; its collision set must equal all retains")
    parser.add_argument("--output", default=DEFAULT_OUTPUT)
    parser.add_argument("--markdown", default=DEFAULT_MARKDOWN)
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        self_test()
        if not args.link_log and not args.index:
            return 0
    if not args.link_log or not args.index:
        parser.error("--link-log and --index are required")
    result = build(args)
    rendered = json.dumps(result, indent=1) + "\n"
    markdown = render_markdown(result)
    if args.check:
        existing = open(args.output).read() if os.path.exists(args.output) else None
        existing_md = (open(args.markdown).read()
                       if os.path.exists(args.markdown) else None)
        if existing != rendered or existing_md != markdown:
            print("collision ownership catalog stale", file=sys.stderr)
            return 2
    else:
        os.makedirs(os.path.dirname(args.output), exist_ok=True)
        with open(args.output, "w") as stream:
            stream.write(rendered)
        with open(args.markdown, "w") as stream:
            stream.write(markdown)
    summary = result["summary"]
    print("CPUAPP collisions: %(unique_symbols)d unique / "
          "%(diagnostic_occurrences)d diagnostics; candidates "
          "%(identity_threshold_candidates)d; "
          "retain %(retained_fail_closed)d; batches %(batches)d" % summary)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
