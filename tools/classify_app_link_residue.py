#!/usr/bin/env python3
"""Classify CPUAPP retain-all undefined function-like symbols.

This is a reporting tool: it never edits reconstruction sources.  It combines
the real Zephyr link diagnostics with durable identity/name catalogs, retained
source identities, the adoption manifest, the pinned NCS source tree, and the
ordered library-signature hits used by worklist.py.  The output is intended to
turn one large undefined-symbol count into disjoint remediation queues.
"""

import argparse
import collections
import gzip
import hashlib
import json
import os
import re
import subprocess


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_SCRATCH = ("/private/tmp/claude-501/"
                   "-Users-freedomcoder-Projects-G1disasm2/"
                   "bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad")
UNDEFINED = re.compile(r"undefined reference to [`']([^`']+)[`']")
REF_SITE = re.compile(r"(/[^:]+/recon/symbolized/app/[^:]+\.c):(\d+):")
IDENTITY = re.compile(
    r"identity:\s*FUN_([0-9a-fA-F]{8})\s*@\s*(0x[0-9a-fA-F]+)")
BACKMAP = re.compile(
    r"^\s*\*\s+([A-Za-z_$][\w$]*)\s+<=\s+"
    r"(?:FUN|thunk_FUN)_([0-9a-fA-F]{8})\s+@\s+(0x[0-9a-fA-F]+)", re.M)
ARROW_BACKMAP = re.compile(
    r"^\s*\*\s+([A-Za-z_$][\w$]*)\s+<-\s+"
    r"(?:FUN|thunk_FUN)_([0-9a-fA-F]{8})"
    r"(?:\s+@\s+(0x[0-9a-fA-F]+))?", re.M)
INLINE_BACKMAP = re.compile(
    r"\b([A-Za-z_$][\w$]*)\s*\([^\n;]*\)\s*;[^\n]*/\*\s*"
    r"(?:raw\s+)?(?:FUN|thunk_FUN)_([0-9a-fA-F]{8})")
DEFINE_BACKMAP = re.compile(
    r"^\s*#define\s+(?:FUN|thunk_FUN)_([0-9a-fA-F]{8})\s+"
    r"([A-Za-z_$][\w$]*)", re.M)
RAW_SYMBOL = re.compile(r"FUN_([0-9a-fA-F]{8})(?:_i)?$")

# These spellings are reconstruction/decompiler abstractions, not linkable
# firmware entry identities.  Keeping the small list explicit prevents a
# heuristic from silently hiding future unknown symbols.
PSEUDO_OPS = {
    "ARCH_EXCEPT": "Zephyr architecture exception macro emitted as a call",
    "default_tail": "reconstruction-local name for an unresolved tail path",
    "display_debug_log_boundary":
        "reconstruction-local debug boundary helper with no firmware entry",
}

# Source-version-specific SDK helpers whose reconstruction spelling differs
# from the actual NCS/newlib symbol and therefore will not occur literally in
# the pinned source tree.
SDK_SPELLING_OVERRIDES = {
    "DEBUG_PRINT":
        "distinct variadic vprintf wrapper at 0x0007dda4; it is not "
        "debug_print at 0x00019c70 and requires its own library owner",
    "k_msleep_ticks32768_a": "Zephyr k_msleep/tick-conversion wrapper spelling",
    "strtoll_internal": "newlib-nano internal strtoll implementation spelling",
}


def load_json(path):
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt", encoding="utf-8") as stream:
        return json.load(stream)


def sha256(path):
    digest = hashlib.sha256()
    with open(path, "rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def parse_link_log(path):
    refs = collections.defaultdict(set)
    with open(path, encoding="utf-8", errors="replace") as stream:
        for line in stream:
            match = UNDEFINED.search(line)
            if not match:
                continue
            symbol = match.group(1)
            site = REF_SITE.search(line)
            if site:
                refs[symbol].add("%s:%s" % (os.path.basename(site.group(1)),
                                             site.group(2)))
            else:
                refs[symbol]
    return refs


def retained_evidence(names):
    source_by_va = {}
    backmaps = collections.defaultdict(set)
    source_dir = os.path.join(ROOT, "recon/symbolized/app")

    # The durable name catalog is itself back-mapping evidence, including
    # legacy aliases intentionally omitted from by_name.
    for name, value in names.get("by_name", {}).items():
        backmaps[name].add(int(value, 0) & ~1)
    for address, record in names.get("by_address", {}).items():
        va = int(address, 0) & ~1
        for alias in record.get("aliases", []):
            backmaps[alias].add(va)

    for filename in sorted(os.listdir(source_dir)):
        if not filename.endswith(".c"):
            continue
        path = os.path.join(source_dir, filename)
        with open(path, encoding="utf-8", errors="replace") as stream:
            data = stream.read()
        identity = IDENTITY.search(data[:1024])
        if identity:
            source_by_va[int(identity.group(2), 16) & ~1] = filename
        for name, _raw, address in BACKMAP.findall(data[:4096]):
            backmaps[name].add(int(address, 16) & ~1)
        for name, raw, address in ARROW_BACKMAP.findall(data[:4096]):
            backmaps[name].add(int(address or raw, 16) & ~1)
        for name, raw in INLINE_BACKMAP.findall(data):
            backmaps[name].add(int(raw, 16) & ~1)
        for raw, name in DEFINE_BACKMAP.findall(data):
            backmaps[name].add(int(raw, 16) & ~1)
    return source_by_va, backmaps


def sdk_literal_hits(symbols, ncs_root):
    """Return one pinned-NCS source hit for every literal unresolved spelling."""
    patterns = [symbol for symbol in symbols if not symbol.startswith((
        "FUN_", "tail_", "thunk_FUN_", "ext"))]
    if not patterns or not ncs_root:
        return {}
    command = ["rg", "-n", "-o", "-F"]
    for pattern in patterns:
        command += ["-e", pattern]
    command += ["--glob", "*.c", "--glob", "*.h", "--glob", "*.S",
                os.path.join(ncs_root, "zephyr"), os.path.join(ncs_root, "nrf"),
                os.path.join(ncs_root, "modules")]
    result = subprocess.run(command, capture_output=True, text=True)
    if result.returncode not in (0, 1):
        raise RuntimeError("SDK source scan failed: %s" % result.stderr.strip())
    hits = {}
    for line in result.stdout.splitlines():
        parts = line.rsplit(":", 2)
        if len(parts) != 3:
            continue
        path, lineno, symbol = parts
        if symbol in patterns:
            candidate = "%s:%s" % (os.path.relpath(path, ncs_root), lineno)
            if symbol not in hits or candidate < hits[symbol]:
                hits[symbol] = candidate
    return hits


def classify(args):
    names_path = os.path.join(ROOT, "recon/catalogs/function_names_app.json")
    classified_path = os.path.join(ROOT, "recon/catalogs/classified.json.gz")
    manifest_path = os.path.join(ROOT, "recon/ownership/adoption_manifest.json")
    refs = parse_link_log(args.log)
    names = load_json(names_path)
    classified = load_json(classified_path)["functions"]
    by_va = {record["entry"]: record for record in classified}
    manifest = load_json(manifest_path)
    adopted = {int(record["va"], 0): record
               for record in manifest["cores"]["app"]["entries"]}
    signature_hits = load_json(args.library_hits) if args.library_hits else {}
    signature_hits = {int(address, 0): record
                      for address, record in signature_hits.items()}
    source_by_va, backmaps = retained_evidence(names)
    sdk_hits = sdk_literal_hits(refs, args.ncs_root)

    rows = []
    for symbol in sorted(refs):
        vas = set(backmaps.get(symbol, ()))
        raw = RAW_SYMBOL.fullmatch(symbol)
        if raw:
            vas.add(int(raw.group(1), 16) & ~1)
        identities = []
        for va in sorted(vas):
            catalog = by_va.get(va)
            name_record = names.get("by_address", {}).get("0x%08x" % va, {})
            identities.append({
                "va": "0x%08x" % va,
                "catalog_entry": bool(catalog),
                "catalog_class": catalog.get("class") if catalog else None,
                "catalog_name": catalog.get("name") if catalog else None,
                "is_thunk": bool(catalog and catalog.get("is_thunk")),
                "display_name": name_record.get("display_name"),
                "retained_source": source_by_va.get(va),
                "adopted_component": adopted.get(va, {}).get("component"),
                "library_signature": signature_hits.get(va),
            })

        reason = None
        if symbol in PSEUDO_OPS:
            category = "compiler_or_ghidra_pseudo_op"
            reason = PSEUDO_OPS[symbol]
        elif symbol.startswith(("tail_", "thunk_FUN_", "ext")) or symbol.endswith("_i"):
            category = "interior_or_tail_alias"
            reason = "symbol spelling explicitly denotes a tail/thunk/interior label"
        elif any(item["is_thunk"] or
                 str(item.get("display_name") or "").startswith("thunk_")
                 for item in identities):
            category = "interior_or_tail_alias"
            reason = "back-mapped catalog identity is a tail thunk/veneer"
        elif any(item["retained_source"] for item in identities):
            category = "naming_or_symbolization_defect"
            reason = "back-mapped VA already has a retained reconstructed owner"
        elif any(not item["catalog_entry"] for item in identities):
            category = "interior_or_tail_alias"
            reason = "referenced VA is not a catalog function entry"
        elif symbol in SDK_SPELLING_OVERRIDES:
            category = "sdk_or_config_symbol"
            reason = SDK_SPELLING_OVERRIDES[symbol]
        elif (symbol in sdk_hits or
              any(item["catalog_class"] == "LIBRARY" or
                  item["adopted_component"] or item["library_signature"]
                  for item in identities)):
            category = "sdk_or_config_symbol"
            reason = "pinned SDK, adoption, catalog, or library-signature evidence"
        else:
            category = "true_missing_reconstructed_entry"
            reason = "no retained owner, alias target, adopted owner, or SDK evidence"
        rows.append({
            "symbol": symbol,
            "category": category,
            "reason": reason,
            "reference_count": len(refs[symbol]),
            "reference_sites": sorted(refs[symbol]),
            "identities": identities,
            "sdk_source_hit": sdk_hits.get(symbol),
        })

    counts = collections.Counter(row["category"] for row in rows)
    return {
        "schema": 1,
        "core": "app",
        "scope": "unique function-like undefined symbols from CPUAPP retain-all link",
        "policy": {
            "report_only": True,
            "no_function_semantics_changed": True,
            "categories_are_disjoint": True,
        },
        "inputs": [
            {"path": os.path.abspath(args.log), "sha256": sha256(args.log)},
            {"path": os.path.relpath(names_path, ROOT), "sha256": sha256(names_path)},
            {"path": os.path.relpath(classified_path, ROOT),
             "sha256": sha256(classified_path)},
            {"path": os.path.relpath(manifest_path, ROOT),
             "sha256": sha256(manifest_path)},
            {"path": os.path.abspath(args.library_hits),
             "sha256": sha256(args.library_hits)} if args.library_hits else None,
        ],
        "summary": {
            "unique_symbols": len(rows),
            "by_category": dict(sorted(counts.items())),
            "true_missing_reconstructed_entries":
                counts.get("true_missing_reconstructed_entry", 0),
        },
        "entries": rows,
    }


def write_markdown(report, path):
    summary = report["summary"]
    lines = [
        "# CPUAPP retain-all undefined-function residue",
        "",
        "This is a report-only classification of the real post-pin link log; it does not",
        "change function semantics or authorize automatic source removal.",
        "",
        "## Summary",
        "",
        "| Category | Unique symbols | Next action |",
        "|---|---:|---|",
    ]
    actions = {
        "naming_or_symbolization_defect": "repair call spelling/back-map or exported alias",
        "interior_or_tail_alias": "materialize a safe veneer/alias after overlap review",
        "sdk_or_config_symbol": "enable/pin the owning NCS unit or reconcile static linkage",
        "compiler_or_ghidra_pseudo_op": "replace the pseudo call with its C/macro semantics",
        "true_missing_reconstructed_entry": "reconstruct and CFG-verify the missing entry",
    }
    for category, count in summary["by_category"].items():
        lines.append("| `%s` | %d | %s |" %
                     (category, count, actions[category]))
    lines += [
        "",
        "Total: **%d** unique symbols. True missing reconstructed entries: **%d**."
        % (summary["unique_symbols"],
           summary["true_missing_reconstructed_entries"]),
        "",
        "## Action queues",
        "",
    ]
    grouped = collections.defaultdict(list)
    for row in report["entries"]:
        grouped[row["category"]].append(row["symbol"])
    for category in sorted(grouped):
        lines += ["### `%s` (%d)" % (category, len(grouped[category])), "",
                  ", ".join("`%s`" % symbol for symbol in grouped[category]), ""]
    with open(path, "w", encoding="utf-8") as stream:
        stream.write("\n".join(lines) + "\n")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--log", required=True)
    parser.add_argument("--library-hits",
                        default=os.path.join(DEFAULT_SCRATCH, "lib_sig2_hits.json"))
    parser.add_argument("--ncs-root", default="/Users/freedomcoder/ncs251")
    parser.add_argument("--json", default=os.path.join(
        ROOT, "recon/analysis/app_link_residue.json"))
    parser.add_argument("--markdown", default=os.path.join(
        ROOT, "recon/analysis/app_link_residue.md"))
    args = parser.parse_args()
    report = classify(args)
    report["inputs"] = [item for item in report["inputs"] if item]
    os.makedirs(os.path.dirname(args.json), exist_ok=True)
    with open(args.json, "w", encoding="utf-8") as stream:
        json.dump(report, stream, indent=1, sort_keys=False)
        stream.write("\n")
    write_markdown(report, args.markdown)
    print(json.dumps(report["summary"], sort_keys=True))


if __name__ == "__main__":
    main()
