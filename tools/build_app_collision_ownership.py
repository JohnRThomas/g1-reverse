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

sys.path.insert(0, os.path.dirname(__file__))
from build_upstream_index import extract_features
import extract


BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_NAMES = os.path.join(BASE, "recon/catalogs/function_names_app.json")
DEFAULT_CLASSIFIED = os.path.join(BASE, "recon/catalogs/classified.json.gz")
DEFAULT_OUTPUT = os.path.join(BASE, "recon/ownership/app_build_collision_ownership.json")
NCS = "/Users/freedomcoder/ncs251"
SOURCE_REPOS = (
    (os.path.join(NCS, "zephyr"), "zephyr"),
    (os.path.join(NCS, "nrf"), "nrf"),
    (os.path.join(NCS, "modules/hal/nordic"), "hal_nordic"),
    (os.path.join(NCS, "modules/hal/libmetal"), "libmetal"),
)
THRESHOLDS = {"opcode": 0.90, "shape": 0.70, "length": 0.80}
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
    """Parse one record per strong multiple-definition diagnostic."""
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
    unique = {}
    for row in rows:
        previous = unique.get(row["symbol"])
        if previous and previous != row:
            raise ValueError("non-identical duplicate collision for %s" % row["symbol"])
        unique[row["symbol"]] = row
    return [unique[name] for name in sorted(unique)]


def sequence_score(left, right):
    if not left and not right:
        return 1.0
    if not left or not right:
        return 0.0
    return difflib.SequenceMatcher(None, left, right, autojunk=False).ratio()


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
        if extent and candidate:
            firmware = extract_features(extract.read(va, int(extent)), va)
            scores = {
                "opcode": round(sequence_score(firmware["mnemonics"],
                                                candidate["mnemonics"]), 6),
                "shape": round(sequence_score(firmware["operand_shapes"],
                                               candidate["operand_shapes"]), 6),
                "length": round(min(firmware["instruction_count"],
                                    candidate["instruction_count"]) /
                                max(1, firmware["instruction_count"],
                                    candidate["instruction_count"]), 6),
                "normalized_exact": (firmware["normalized_sha256"] ==
                                     candidate["normalized_sha256"]),
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
        functions.append({
            "core": "app", "va": "0x%08x" % va,
            "raw_symbol": "FUN_%08x" % va,
            "current_symbol": symbol,
            "firmware_extent": extent,
            "firmware_instruction_count": (firmware or {}).get("instruction_count"),
            "link_provenance": {
                "owner_input": collision.get("owner_input"),
                "owner_source_line": collision.get("definition_location"),
                "reconstruction_input": collision["reconstruction_input"],
                "diagnostic": collision["diagnostic"],
            },
            "upstream": {
                "symbol": symbol,
                "object": (candidate or {}).get("object"),
                "section": (candidate or {}).get("section"),
                "symbol_size": (candidate or {}).get("symbol_size"),
                "binding": (candidate or {}).get("binding"),
                "abi": (candidate or {}).get("signature"),
                "source": source,
                "unselected_same_symbol_candidates": alternatives,
            },
            "signature_match": scores,
            "thresholds": dict(THRESHOLDS),
            "safe_to_exclude": safe,
            "exclusion_blockers": sorted(set(blockers)),
            "decision": ("adopt_selected_upstream_owner" if safe else
                         "retain_reconstruction_fail_closed"),
        })
    functions.sort(key=lambda row: int(row["va"], 16))
    result = {
        "schema": 1,
        "generated_by": "tools/build_app_collision_ownership.py",
        "policy": {
            "strong_collision_alone_is_insufficient": True,
            "requires_selected_global_object": True,
            "requires_dwarf_abi": True,
            "thresholds": dict(THRESHOLDS),
            "ambiguity_action": "retain_reconstruction",
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
            "safe_to_exclude": sum(row["safe_to_exclude"] for row in functions),
            "retained_fail_closed": sum(not row["safe_to_exclude"] for row in functions),
        },
        "functions": functions,
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


def self_test():
    text = ("ld.bfd: zephyr/lib.a(foo.c.obj): in function `foo':\n"
            "/ncs/foo.c:7: multiple definition of `foo'; "
            "app/libapp.a(foo.c.obj):/repo/foo.c:3: first defined here\n")
    rows = parse_collisions(text)
    assert len(rows) == 1 and rows[0]["owner_input"] == "zephyr/lib.a(foo.c.obj)"
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
    if args.check:
        existing = open(args.output).read() if os.path.exists(args.output) else None
        if existing != rendered:
            print("collision ownership catalog stale", file=sys.stderr)
            return 2
    else:
        os.makedirs(os.path.dirname(args.output), exist_ok=True)
        with open(args.output, "w") as stream:
            stream.write(rendered)
    summary = result["summary"]
    print("CPUAPP collisions: %(collisions)d; promote %(safe_to_exclude)d; "
          "retain %(retained_fail_closed)d" % summary)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
