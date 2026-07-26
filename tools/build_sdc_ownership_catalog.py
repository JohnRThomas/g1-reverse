#!/usr/bin/env python3
"""Generate per-address SoftDevice Controller archive ownership evidence.

This tool intentionally does not edit source trees or adoption manifests.  Its
``safe_to_exclude`` decision is conservative: only an exact, unique match to a
public symbol declared by the pinned SDC headers may be marked safe.  Private
obfuscated symbols and duplicate bodies remain report-only even when their
archive-family ownership is certain.

Run outside the repository because its historical ``struct.py`` shadows the
standard library::

  cd /tmp
  PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
    /Users/freedomcoder/Projects/G1disasm2/tools/build_sdc_ownership_catalog.py
"""

# Resolvable pipeline scratchpad (tools/g1_paths.py).  This used to be one
# literal /private/tmp path belonging to a finished agent session; see that
# module for the resolution order and the fail-closed catalog fallback.
import os as _g1_os, sys as _g1_sys
_G1_TOOLS = _g1_os.path.dirname(_g1_os.path.abspath(__file__))
if _g1_os.path.basename(_G1_TOOLS) != "tools":
    _G1_TOOLS = _g1_os.path.dirname(_G1_TOOLS)
if _G1_TOOLS not in _g1_sys.path:
    _g1_sys.path.insert(0, _G1_TOOLS)
import g1_paths as _g1_paths
import argparse
import collections
import difflib
import gzip
import hashlib
import io
import json
import os
import re
import subprocess
import sys

from capstone import Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB
from elftools.elf.elffile import ELFFile

BASE = "/Users/freedomcoder/Projects/G1disasm2"
SCR = (_g1_paths.scratchpad())
NCS = "/Users/freedomcoder/ncs251"
ARCHIVE_REL = ("nrfxlib/softdevice_controller/lib/cortex-m33+nodsp/soft-float/"
               "libsoftdevice_controller_multirole.a")
ARCHIVE = os.path.join(NCS, ARCHIVE_REL)
MEMBER = "libsoftdevice_controller_s140_debug_soft__obfuscated.elf"
HEADERS = os.path.join(NCS, "nrfxlib/softdevice_controller/include")
OUTPUT = os.path.join(BASE, "recon/ownership/net_sdc_archive_ownership.json")
REPORT = os.path.join(BASE, "recon/ownership/net_sdc_archive_ownership.md")
EXTRACTION = os.path.join(BASE, "recon/ownership/net_sdc_build_extraction.json")
AR = ("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
      "arm-zephyr-eabi-ar")
THRESHOLD = 0.90
UNIQUE_GAP = 0.03
MIN_SIZE = 16
MIN_OPS = 6

# Established configuration variant from net_sdc_archive_benchmark.md.
SPECIAL = {0x0101FDD0: {"length_tolerance": 11, "minimum": 0.90}}

MD = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)


def opcodes(code, address=0):
    return tuple(insn.mnemonic.split(".")[0] for insn in MD.disasm(code, address))


def sha256_file(path):
    digest = hashlib.sha256()
    with open(path, "rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def load_catalog(name):
    scratch = os.path.join(SCR, name + ".json")
    if os.path.exists(scratch):
        return json.load(open(scratch))
    backup = os.path.join(BASE, "recon/catalogs", name + ".json.gz")
    with gzip.open(backup, "rt") as stream:
        return json.load(stream)


def archive_member(path=ARCHIVE, member=MEMBER):
    data = subprocess.check_output([AR, "p", path, member])
    return data, ELFFile(io.BytesIO(data))


def archive_functions(elf, archive_path=ARCHIVE, member=MEMBER):
    """Preserve section-qualified identities, including repeated local names."""
    symtab = elf.get_section_by_name(".symtab")
    if symtab is None:
        raise ValueError("archive member has no symbol table")
    rows = []
    for ordinal, symbol in enumerate(symtab.iter_symbols()):
        if symbol["st_info"]["type"] != "STT_FUNC" or not symbol.name:
            continue
        size = int(symbol["st_size"])
        section_index = symbol["st_shndx"]
        if size < MIN_SIZE or not isinstance(section_index, int):
            continue
        section = elf.get_section(section_index)
        if section is None:
            continue
        data = section.data()
        offset = (int(symbol["st_value"]) & ~1) - int(section["sh_addr"])
        if offset < 0 or offset + size > len(data):
            continue
        seq = opcodes(data[offset:offset + size], int(symbol["st_value"]) & ~1)
        if len(seq) < MIN_OPS:
            continue
        identity = "%s(%s):section[%d]:%s:%s#%d" % (
            os.path.basename(archive_path), member, section_index,
            section.name, symbol.name, ordinal)
        rows.append({
            "identity": identity,
            "archive_member": member,
            "section_index": section_index,
            "section": section.name,
            "symbol_table_ordinal": ordinal,
            "symbol": symbol.name,
            "symbol_binding": symbol["st_info"]["bind"],
            "symbol_visibility": symbol["st_other"]["visibility"],
            "symbol_value": int(symbol["st_value"]),
            "symbol_size": size,
            "instruction_count": len(seq),
            "opcodes": seq,
        })
    rows.sort(key=lambda row: row["identity"])
    return rows


def public_declarations(root=HEADERS):
    """Return declared SDC API names and compact source-header provenance."""
    result = {}
    block_comment = re.compile(r"/\*.*?\*/", re.S)
    for directory, _, files in os.walk(root):
        for filename in sorted(files):
            if not filename.endswith(".h"):
                continue
            path = os.path.join(directory, filename)
            text = block_comment.sub(" ", open(path, errors="replace").read())
            text = re.sub(r"//.*", "", text)
            # Declarations can span lines.  A public function name followed by
            # '(' and eventually ';' is enough to distinguish it from the
            # archive's obfuscated private symbols; retain the text as evidence,
            # not as a C parser's ABI assertion.
            for match in re.finditer(r"([^;{}]*\b(sdc_[A-Za-z0-9_]+)\s*\([^;{}]*\)\s*;)",
                                     text, re.S):
                declaration = " ".join(match.group(1).split())
                name = match.group(2)
                line = text.count("\n", 0, match.start(2)) + 1
                result.setdefault(name, {
                    "header": os.path.relpath(path, NCS),
                    "line": line,
                    "declaration": declaration,
                })
    return result


def rank_sequence(sequence, candidates, tolerance=2):
    """Return all ranked identities in the operation-count window."""
    ranked = []
    length = len(sequence)
    for candidate in candidates:
        if abs(candidate["instruction_count"] - length) > tolerance:
            continue
        ratio = difflib.SequenceMatcher(
            None, sequence, candidate["opcodes"], autojunk=False).ratio()
        ranked.append((ratio, candidate))
    ranked.sort(key=lambda pair: (-pair[0], pair[1]["identity"]))
    return ranked


def classify(ranked, threshold=THRESHOLD, unique_gap=UNIQUE_GAP):
    """Classify identity uniqueness without collapsing duplicate bodies."""
    if not ranked or ranked[0][0] < threshold:
        return None
    best_score = ranked[0][0]
    best = ranked[0][1]
    runner_score = ranked[1][0] if len(ranked) > 1 else None
    gap = best_score - runner_score if runner_score is not None else None
    tied = [candidate for score, candidate in ranked
            if abs(score - best_score) < 1e-12]
    exact = abs(best_score - 1.0) < 1e-12
    # For an exact opcode match, only another exact identity makes the symbol
    # ambiguous.  The 0.03 gap rule is for approximate matches, where a close
    # non-identical runner-up is meaningful uncertainty.
    unique = (len(tied) == 1 and
              (exact or runner_score is None or gap >= unique_gap))
    return {
        "best": best,
        "score": best_score,
        "exact_opcode_sequence": exact,
        "runner_up": ranked[1][1] if len(ranked) > 1 else None,
        "runner_up_score": runner_score,
        "runner_up_gap": gap,
        "tied_best": tied,
        "unique_identity": unique,
    }


def firmware_names():
    path = os.path.join(BASE, "recon/catalogs/function_names_net.json")
    return json.load(open(path)).get("by_address", {})


def firmware_bytes(va, size):
    sys.path.insert(0, os.path.join(BASE, "tools"))
    import net_extract
    return net_extract.func_bytes_padded(va, size, 0)


def _candidate_json(candidate):
    if candidate is None:
        return None
    return {key: value for key, value in candidate.items() if key != "opcodes"}


def build_rows(functions, candidates, declarations, legacy=None, graph=None,
               extraction=None, archive_sha256=None):
    names = firmware_names()
    legacy = legacy or {}
    graph = graph or {}
    extraction = extraction or {}
    promotions = extraction.get("promotions", {})
    rows = []
    for function in functions:
        va = int(function["entry"]) & ~1
        size = int(function["size"])
        if function.get("is_thunk") or size < MIN_SIZE:
            continue
        sequence = opcodes(firmware_bytes(va, size), va)
        if len(sequence) < MIN_OPS:
            continue
        tolerance = SPECIAL.get(va, {}).get("length_tolerance", 2)
        result = classify(rank_sequence(sequence, candidates, tolerance))
        if result is None:
            continue
        best = result["best"]
        declaration = declarations.get(best["symbol"])
        public = (declaration is not None and
                  best["symbol_binding"] == "STB_GLOBAL" and
                  best["symbol_visibility"] == "STV_DEFAULT")
        # A public symbol with a different firmware catalog name is useful
        # ownership evidence, but not safe automatic substitution.
        name_record = names.get("0x%08x" % va, {})
        catalog_name = name_record.get("name") or function.get("name")
        legacy_row = legacy.get("0x%08x" % va) or legacy.get("0x%x" % va)
        graph_row = graph.get("0x%x" % va, {})
        public_name_aligned = catalog_name == best["symbol"]
        promotion = promotions.get("0x%08x" % va)
        build_extraction_verified = bool(
            promotion and
            promotion.get("status") == "verified_public_archive_extraction" and
            promotion.get("symbol") == best["symbol"] and
            extraction.get("archive", {}).get("sha256") == archive_sha256 and
            extraction.get("archive", {}).get("member") == best["archive_member"] and
            extraction.get("archive", {}).get("selected_by_link") is True)
        safe = bool(result["unique_identity"] and public and public_name_aligned and
                    (result["exact_opcode_sequence"] or build_extraction_verified))
        reasons = []
        if not result["exact_opcode_sequence"] and not build_extraction_verified:
            reasons.append("approximate_opcode_match")
        if not result["unique_identity"]:
            reasons.append("duplicate_or_low_gap_identity")
        if not public:
            reasons.append("private_abi_unpublished")
        elif not public_name_aligned:
            reasons.append("public_symbol_name_not_aligned")
        row = {
            "address": "0x%08x" % va,
            "raw_name": "FUN_%08x" % va,
            "catalog_name": catalog_name,
            "firmware_signature": function.get("signature"),
            "catalog_size": size,
            "match_extent": size,
            "extent_source": "net_funcs catalog",
            "firmware_instruction_count": len(sequence),
            "match_kind": ("exact" if result["exact_opcode_sequence"] else
                           "approximate"),
            "score": round(result["score"], 6),
            "best": _candidate_json(best),
            "runner_up": _candidate_json(result["runner_up"]),
            "runner_up_score": (round(result["runner_up_score"], 6)
                                if result["runner_up_score"] is not None else None),
            "runner_up_gap": (round(result["runner_up_gap"], 6)
                              if result["runner_up_gap"] is not None else None),
            "tied_best_identities": [c["identity"] for c in result["tied_best"]],
            "unique_identity": result["unique_identity"],
            "public_api": public,
            "public_declaration": declaration,
            "public_name_aligned": public_name_aligned,
            "build_extraction_verified": build_extraction_verified,
            "build_extraction_evidence": promotion,
            "abi_status": ("published_header_declaration" if public else
                           "private_unpublished"),
            "call_graph": {
                "callers": graph_row.get("callers", []),
                "callees": graph_row.get("calls", []),
            },
            "legacy_ownership": ({
                "status": legacy_row.get("status"),
                "confidence": legacy_row.get("confidence"),
                "matched_symbol": legacy_row.get("signature_match", {}).get("symbol"),
                "score": legacy_row.get("signature_match", {}).get("ratio"),
                "reference_link_provenance":
                    legacy_row.get("signature_match", {}).get("provenance"),
            } if legacy_row else None),
            "archive_extraction": {
                "member_is_single_archive_payload": True,
                "private_functions_not_independently_extractable": not public,
                "note": ("the archive extracts the containing ELF member; private symbols "
                         "cannot be requested independently"),
            },
            "safe_to_exclude": safe,
            "exclusion_blockers": reasons,
            "matching": {
                "feature": "ordered normalized Thumb mnemonic sequence",
                "threshold": THRESHOLD,
                "length_tolerance_instructions": tolerance,
                "unique_gap_required": UNIQUE_GAP,
                "exact_means_opcode_sequence_not_bytes": True,
            },
        }
        rows.append(row)
    return sorted(rows, key=lambda row: row["address"])


def summarize(rows):
    counter = collections.Counter()
    for row in rows:
        counter["total"] += 1
        counter[row["match_kind"]] += 1
        counter[row["match_kind"] + ("_unique" if row["unique_identity"]
                                     else "_ambiguous")] += 1
        if row["public_api"]:
            counter["public_api"] += 1
        if row["safe_to_exclude"]:
            counter["safe_to_exclude"] += 1
        counter["catalog_bytes"] += row["catalog_size"]
    return dict(sorted(counter.items()))


def render_report(catalog):
    summary = catalog["summary"]
    lines = [
        "# Per-address NCS 2.5.1 SoftDevice Controller ownership",
        "",
        "Generated by `tools/build_sdc_ownership_catalog.py`; JSON is authoritative.",
        "The generator does not edit sources or the adoption manifest.",
        "",
        "| Classification | Functions |",
        "|---|---:|",
        "| Exact, unique identity | %d |" % summary.get("exact_unique", 0),
        "| Exact, ambiguous identity | %d |" % summary.get("exact_ambiguous", 0),
        "| Approximate, unique identity | %d |" % summary.get("approximate_unique", 0),
        "| Approximate, ambiguous identity | %d |" % summary.get("approximate_ambiguous", 0),
        "| **Archive-owned total** | **%d** |" % summary.get("total", 0),
        "| Public API matches | %d |" % summary.get("public_api", 0),
        "| Safe exclusion candidates | %d |" % summary.get("safe_to_exclude", 0),
        "",
        "Private and ambiguous identities fail closed. `safe_to_exclude` requires a",
        "unique public-header identity plus either an exact opcode match or exact",
        "build-extraction evidence for that public symbol.",
        "Link integration must still validate that the archive member is selected and",
        "that no duplicate definitions remain before applying exclusions.",
        "",
        "## Safe public candidates",
        "",
        "| Firmware VA | Symbol | Score | Header |",
        "|---|---|---:|---|",
    ]
    for row in catalog["functions"]:
        if not row["safe_to_exclude"]:
            continue
        decl = row["public_declaration"]
        lines.append("| `%s` | `%s` | %.3f | `%s:%d` |" % (
            row["address"], row["best"]["symbol"], row["score"],
            decl["header"], decl["line"]))
    lines += ["", "## Ambiguous identities", "",
              "These are archive-family matches only; their private identity is not resolved.",
              "", "| Firmware VA | Best symbol | Score | Tied identities |",
              "|---|---|---:|---:|"]
    for row in catalog["functions"]:
        if row["unique_identity"]:
            continue
        lines.append("| `%s` | `%s` | %.3f | %d |" % (
            row["address"], row["best"]["symbol"], row["score"],
            len(row["tied_best_identities"])))
    return "\n".join(lines) + "\n"


def self_test():
    def candidate(identity, seq, name="sym_PRIVATE", binding="STB_LOCAL"):
        return {"identity": identity, "opcodes": tuple(seq),
                "instruction_count": len(seq), "symbol": name,
                "symbol_binding": binding, "symbol_visibility": "STV_DEFAULT"}
    seq = ("push", "mov", "cmp", "beq", "str", "pop")
    unique = classify(rank_sequence(seq, [candidate("a", seq),
                                          candidate("b", seq[:-1] + ("bx",))]))
    assert unique and unique["exact_opcode_sequence"] and unique["unique_identity"]
    duplicate = classify(rank_sequence(seq, [candidate("a", seq),
                                             candidate("b", seq)]))
    assert duplicate and not duplicate["unique_identity"]
    assert len(duplicate["tied_best"]) == 2
    assert classify(rank_sequence(seq, [candidate("x", ("nop",) * 6)])) is None
    print("build_sdc_ownership_catalog self-test: PASS")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--archive", default=ARCHIVE)
    parser.add_argument("--member", default=MEMBER)
    parser.add_argument("--headers", default=HEADERS)
    parser.add_argument("--output", default=OUTPUT)
    parser.add_argument("--report", default=REPORT)
    parser.add_argument("--extraction-evidence", default=EXTRACTION)
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        self_test()
        return
    _, elf = archive_member(args.archive, args.member)
    candidates = archive_functions(elf, args.archive, args.member)
    declarations = public_declarations(args.headers)
    functions = load_catalog("net_funcs")["functions"]
    legacy_catalog = json.load(open(os.path.join(
        BASE, "recon/ownership/net_function_ownership.json")))
    legacy = legacy_catalog.get("entries", {})
    graph = load_catalog("refgraph_net").get("functions", {})
    extraction = (json.load(open(args.extraction_evidence))
                  if os.path.exists(args.extraction_evidence) else {})
    archive_sha256 = sha256_file(args.archive)
    rows = build_rows(functions, candidates, declarations, legacy, graph,
                      extraction, archive_sha256)
    link_map = "/Users/freedomcoder/ncs251/netref_build/zephyr/zephyr.map"
    member_token = os.path.basename(args.archive) + "(" + args.member + ")"
    map_text = open(link_map, errors="replace").read()
    catalog = {
        "schema_version": 1,
        "core": "net",
        "component": "softdevice_controller",
        "generated_date": "2026-07-17",
        "inputs": {
            "ncs_version": "v2.5.1",
            "nrfxlib_commit": "ab72f33c86db7252dbf9a3ffec86c6b7fc6a9da7",
            "archive": os.path.relpath(args.archive, NCS),
            "archive_sha256": archive_sha256,
            "archive_member": args.member,
            "abi": "ARM EABI v5, Cortex-M33+nodsp, soft-float",
            "headers": os.path.relpath(args.headers, NCS),
            "firmware_catalog": "net_funcs.json",
            "legacy_ownership": "recon/ownership/net_function_ownership.json",
            "link_map": link_map,
            "link_map_member_present": member_token in map_text,
            "link_map_member_reference_count": map_text.count(member_token),
        },
        "policy": {
            "ownership_threshold": THRESHOLD,
            "unique_runner_up_gap": UNIQUE_GAP,
            "safe_exclusion_requires": [
                "unique archive section/symbol identity",
                "global default-visible symbol declared in pinned public headers",
                "firmware catalog name aligned to public symbol",
                "exact normalized opcode sequence OR verified exact build extraction",
            ],
            "integration_warning": ("safe_to_exclude is catalog authority only; the build "
                                    "must still prove member extraction and collision freedom"),
        },
        "archive_index": {
            "eligible_functions": len(candidates),
            "public_header_declarations": len(declarations),
        },
        "build_extraction_input": {
            "path": os.path.relpath(args.extraction_evidence, BASE),
            "sha256": (sha256_file(args.extraction_evidence)
                       if os.path.exists(args.extraction_evidence) else None),
        },
        "summary": summarize(rows),
        "functions": rows,
    }
    os.makedirs(os.path.dirname(args.output), exist_ok=True)
    with open(args.output, "w") as stream:
        json.dump(catalog, stream, indent=2, sort_keys=True)
        stream.write("\n")
    with open(args.report, "w") as stream:
        stream.write(render_report(catalog))
    print(json.dumps(catalog["summary"], sort_keys=True))
    print(args.output)


if __name__ == "__main__":
    main()
