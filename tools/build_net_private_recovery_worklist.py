#!/usr/bin/env python3
"""Build the fail-closed CPUNET private SDC/MPSL recovery backlog."""
import argparse
import gzip
import hashlib
import json
import re
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REPORT = ROOT / "recon/catalogs/net_cohesive_undefined_classification.json"
FUNCS = ROOT / "recon/catalogs/net_funcs.json.gz"
GRAPH = ROOT / "recon/catalogs/refgraph_net.json.gz"
NAMES = ROOT / "recon/catalogs/function_names_net.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
OUTPUT = ROOT / "recon/catalogs/net_private_recovery_worklist.json"
MARKDOWN = ROOT / "recon/catalogs/net_private_recovery_worklist.md"

# Catalog-missed direct-call entries. Bounds end at the last owned return/tail
# and exclude the following alignment/literal/independent entry.
MISSED_EXTENTS = {
    0x0100EF08: (0x3C, "tail branch ends 0x0100ef44; literal follows"),
    0x01011664: (0xBA, "tail branch ends 0x0101171e; literals follow"),
    0x01014B18: (0x1188, "final owned back-tail ends 0x01015ca0; literals follow"),
    0x01018DF8: (0x32, "tail branch ends 0x01018e2a; literals follow"),
    0x0101D890: (0x52, "tail branch ends 0x0101d8e2; alignment/literal follows"),
    0x0102665C: (0x20, "ordinary return join ends 0x0102667c; next entry follows"),
    0x010292EC: (0x2E, "ordinary return join ends 0x0102931a; next entry follows"),
    0x0102A1E0: (0x02, "single bx lr; next entry starts 0x0102a1e2"),
}


def load(path):
    with (gzip.open(path, "rt") if path.suffix == ".gz" else path.open()) as f:
        return json.load(f)


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def h(va):
    return f"0x{va:08x}"


def arity(func):
    if not func:
        return None
    text = func.get("decompiled", "")
    match = re.search(r"\b" + re.escape(func["name"]) + r"\s*\(([^)]*)\)", text)
    if not match:
        return None
    args = match.group(1).strip()
    return 0 if not args or args == "void" else len([x for x in args.split(",") if x.strip()])


def generate(shard_count=8):
    report = load(REPORT)
    funcs = {f["entry"]: f for f in load(FUNCS)["functions"]}
    graph = {int(k, 16): v for k, v in load(GRAPH)["functions"].items()}
    names = load(NAMES)["by_address"]
    manifest = {int(e["va"], 16): e for e in load(MANIFEST)["cores"]["net"]["entries"]}
    rows = [r for r in report["entries"] if r["category"] == "private_sdc_mpsl_report_only"]
    grouped = defaultdict(list)
    for row in rows:
        grouped[int(row["analysis_address"], 16)].append(row)
    if len(grouped) != 92:
        raise ValueError(f"expected 92 unique private VAs, got {len(grouped)}")
    private = set(grouped)
    entries = []
    for va in sorted(private):
        source_rows = grouped[va]
        func = funcs.get(va)
        name_row = names.get(h(va), {})
        spellings = sorted({r["symbol"] for r in source_rows} | set(name_row.get("aliases", [])) |
                           {name_row.get("raw_name", f"FUN_{va:08x}")})
        readable = sorted(r["symbol"] for r in source_rows if not r["symbol"].startswith("FUN_"))
        primary = name_row.get("name") if name_row.get("human") else (readable[0] if readable else source_rows[0]["symbol"])
        if va in MISSED_EXTENTS:
            true_extent, boundary = MISSED_EXTENTS[va]
            declared = None
            basis = "reviewed_catalog_missed_boundary"
        else:
            declared = func["size"]
            true_extent = declared
            boundary = "catalog allocation; no private-backlog true-size override"
            basis = "net_funcs_declared_and_current_verifier_extent"
        direct = set()
        if va in graph:
            direct.update(int(x, 16) for x in graph[va].get("calls", []))
        if func:
            for callee in func.get("callees", []):
                m = re.fullmatch(r"(?:thunk_)?FUN_([0-9A-Fa-f]{8})", callee)
                if m:
                    direct.add(int(m.group(1), 16))
        deps = sorted(direct & private)
        man = manifest.get(va)
        archive_symbols = sorted({r["provider"].get("archive_symbol") for r in source_rows
                                  if r["provider"].get("archive_symbol")})
        existing = [str(p.relative_to(ROOT)) for spelling in spellings
                    for p in [ROOT / "recon/net/src" / f"{spelling}.c"] if p.exists()]
        entries.append({
            "analysis_address": h(va),
            "runtime_address": h(va + 0x800),
            "primary_symbol": primary,
            "required_spellings": spellings,
            "same_va_alias_required": len(source_rows) > 1,
            "archive_family": source_rows[0]["provider"]["family"],
            "archive_identities": archive_symbols,
            "archive_identity_is_provenance_only": True,
            "catalogued_start": func is not None,
            "declared_extent": declared,
            "true_executable_extent": true_extent,
            "extent_basis": basis,
            "boundary_evidence": boundary,
            "callees": [h(x) for x in sorted(direct)],
            "private_dependencies": [h(x) for x in deps],
            "callers": sorted({x for r in source_rows for x in r.get("refgraph_callers", [])}),
            "current_provider": {"status": "absent" if not existing else "present", "paths": existing},
            "manifest": None if not man else {
                "decision": man["decision"], "exclude_reconstruction": man["exclude_reconstruction"]},
            "cfg": {
                "status": "not_run_source_absent" if not existing else "requires_fresh_cfg_verify",
                "entrypoint": f"cfg_verify.verify('net', '{primary}')",
                "input_strategy": "derive branch/switch cases from original CFG plus random trials",
                "decompiler_argument_count": arity(func),
            },
            "completion_gate": "canonical C exists and authoritative cfg_verify passes",
        })

    identity_users = defaultdict(set)
    for e in entries:
        for identity in e["archive_identities"]:
            identity_users[(e["archive_family"], identity)].add(e["analysis_address"])
    for e in entries:
        peers = sorted({address for identity in e["archive_identities"]
                        for address in identity_users[(e["archive_family"], identity)]
                        if address != e["analysis_address"]})
        e["archive_identity_peers"] = peers
        e["same_archive_identity_distinct_va"] = bool(peers)
        e["archive_identity_alias_safe"] = not peers

    # Weak dependency components are indivisible, then greedily balanced by bytes.
    adjacent = {va: set() for va in private}
    by_va = {int(e["analysis_address"], 16): e for e in entries}
    for va, e in by_va.items():
        for dep in map(lambda x: int(x, 16), e["private_dependencies"]):
            adjacent[va].add(dep); adjacent[dep].add(va)
    components = []
    unseen = set(private)
    while unseen:
        stack = [min(unseen)]; comp = set()
        while stack:
            va = stack.pop()
            if va in comp: continue
            comp.add(va); unseen.discard(va); stack.extend(adjacent[va] - comp)
        components.append(sorted(comp))
    bins = [{"id": f"net-private-{i+1}", "addresses": [], "total_true_extent": 0}
            for i in range(shard_count)]
    for comp in sorted(components, key=lambda c: (-sum(by_va[v]["true_executable_extent"] for v in c), c)):
        target = min(bins, key=lambda b: (b["total_true_extent"], b["id"]))
        target["addresses"].extend(h(v) for v in comp)
        target["total_true_extent"] += sum(by_va[v]["true_executable_extent"] for v in comp)
    for b in bins:
        b["addresses"].sort(); b["function_count"] = len(b["addresses"])
        for addr in b["addresses"]: by_va[int(addr, 16)]["suggested_shard"] = b["id"]
    shard_of = {address: b["id"] for b in bins for address in b["addresses"]}
    for e in entries:
        if any(shard_of[d] != e["suggested_shard"] for d in e["private_dependencies"]):
            raise ValueError(f"dependency-open shard for {e['analysis_address']}")
    return {
        "schema": "g1.net.private_recovery_worklist.v1",
        "policy": {"no_blobs": True, "private_sdc_mpsl_report_only": True,
                   "archive_replacement_forbidden": True, "fail_closed": True},
        "inputs": [{"path": str(p.relative_to(ROOT)), "sha256": sha(p)}
                   for p in (REPORT, FUNCS, GRAPH, NAMES, MANIFEST)],
        "summary": {"symbol_rows": len(rows), "unique_functions": len(entries),
                    "catalogued": sum(e["catalogued_start"] for e in entries),
                    "catalog_missed": sum(not e["catalogued_start"] for e in entries),
                    "provider_absent": sum(e["current_provider"]["status"] == "absent" for e in entries),
                    "total_true_extent": sum(e["true_executable_extent"] for e in entries),
                    "dependency_components": len(components), "suggested_shards": shard_count},
        "shards": bins,
        "entries": entries,
    }


def render(data):
    s = data["summary"]
    lines = ["# CPUNET private SDC/MPSL recovery worklist", "",
             "Fail-closed backlog: archive identities are provenance only. Each entry must retain C and pass `cfg_verify`; no blobs or archive replacement are authorized.", "",
             f"- Unique functions: **{s['unique_functions']}** ({s['catalogued']} catalogued, {s['catalog_missed']} catalog-missed)",
             f"- Current providers absent: **{s['provider_absent']}**", f"- Dependency components: **{s['dependency_components']}**", "",
             "## Suggested dependency-closed shards", "", "| Shard | Functions | True extent | Addresses |", "|---|---:|---:|---|"]
    for b in data["shards"]:
        lines.append(f"| `{b['id']}` | {b['function_count']} | {b['total_true_extent']} | " + ", ".join(f"`{x}`" for x in b["addresses"]) + " |")
    lines += ["", "## Functions", "", "| Address | Primary | Family | Declared / true | Dependencies | Shard |", "|---|---|---|---:|---|---|"]
    for e in data["entries"]:
        lines.append(f"| `{e['analysis_address']}` | `{e['primary_symbol']}` | `{e['archive_family']}` | {e['declared_extent']} / {e['true_executable_extent']} | " + ", ".join(f"`{x}`" for x in e["private_dependencies"]) + f" | `{e['suggested_shard']}` |")
    return "\n".join(lines) + "\n"


def main():
    ap = argparse.ArgumentParser(); ap.add_argument("--check", action="store_true"); args = ap.parse_args()
    data = generate(); encoded = json.dumps(data, indent=1) + "\n"; md = render(data)
    if args.check:
        if OUTPUT.read_text() != encoded or MARKDOWN.read_text() != md: raise SystemExit("private recovery worklist stale")
        print("CPUNET private recovery worklist: PASS"); return
    OUTPUT.write_text(encoded); MARKDOWN.write_text(md); print(json.dumps(data["summary"], indent=1))


if __name__ == "__main__": main()
