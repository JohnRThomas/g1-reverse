#!/usr/bin/env python3
"""Build the fail-closed CPUAPP address-taken-function root ledger.

The scan intentionally accepts only aligned little-endian Thumb pointers found
outside capped Ghidra function intervals.  Discovery and link resolution are
separate: the former records original identities missing from a normal-GC ELF,
while the latter may map an identity to a reviewed stock alias or to exactly
one retained recovered definition.  Ambiguous/local/unnamed owners are never
turned into linker roots.
"""

import argparse
import bisect
import gzip
import hashlib
import json
import re
import struct
from collections import Counter, defaultdict, deque
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
CLASSIFIED = ROOT / "recon/catalogs/classified.json.gz"
REFGRAPH = ROOT / "recon/catalogs/refgraph_app.json.gz"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
INVENTORY = ROOT / "recon/catalogs/app_root_inventory.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
OUT_JSON = ROOT / "recon/catalogs/app_address_taken_roots.json"
OUT_MD = ROOT / "recon/analysis/app_address_taken_roots.md"
OUT_CMAKE = ROOT / "recon/generated/app_address_taken_roots.cmake"

EXPECTED = {
    "address_taken_identities": 303,
    "unmaterialized_identities": 198,
    "unmaterialized_capped_bytes": 38076,
    "pre_init_only_identities": 69,
    "post_init_or_collision_review_identities": 130,
}

# Reviewed aliases where the configured stock source changed a private/static
# spelling.  These preserve ownership; they do not rename original identities.
STOCK_ALIASES = {
    0x0006058C: "clock_control_nrf_init",
    0x00062D9C: "uarte_0_init",
    0x00060C00: "qspi_nor_init",
    0x0007EB5C: "ipc_static_vrings_init",
    0x00083CB4: "gpio_npm1300_init",
    0x000639D4: "wdt_npm1300_init",
    0x000620CC: "regulator_npm1300_common_init",
    0x00084418: "regulator_npm1300_init",
    0x00062930: "opt3001_init",
    0x0004C2D4: "sync_rtc_setup",
    0x0006312C: "uarte_nrfx_isr_int",
    0x00065B9C: "nrfx_gpiote_irq_handler",
}


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def load_gz(path):
    with gzip.open(path, "rt") as stream:
        return json.load(stream)


def elf_symbols(path):
    result = defaultdict(list)
    with path.open("rb") as stream:
        elf = ELFFile(stream)
        table = elf.get_section_by_name(".symtab")
        if table is None:
            raise ValueError("normal-GC ELF has no symbol table")
        for symbol in table.iter_symbols():
            if symbol["st_shndx"] != "SHN_UNDEF" and symbol.name:
                result[symbol.name].append({
                    "value": "0x%08x" % symbol["st_value"],
                    "binding": symbol["st_info"]["bind"],
                    "type": symbol["st_info"]["type"],
                })
    return result


def function_catalog():
    rows = sorted(load_gz(CLASSIFIED)["functions"], key=lambda row: row["entry"])
    for index, row in enumerate(rows):
        next_entry = (rows[index + 1]["entry"] if index + 1 < len(rows)
                      else row["entry"] + row["size"])
        row["capped_size"] = min(row["size"], next_entry - row["entry"])
    return rows


def scan_pointers(functions):
    starts = [row["entry"] for row in functions]
    entries = {row["entry"]: row for row in functions}
    image = (ROOT / "app_update.bin").read_bytes()
    refs = defaultdict(list)
    for offset in range(0, len(image) - 3, 4):
        pointer_va = 0xC000 + offset
        index = bisect.bisect_right(starts, pointer_va) - 1
        if index >= 0:
            owner = functions[index]
            if pointer_va < owner["entry"] + owner["capped_size"]:
                continue
        raw = struct.unpack_from("<I", image, offset)[0]
        target = raw & ~1
        if raw & 1 and target in entries:
            refs[target].append(pointer_va)
    return refs


def data_tables():
    tables = []
    for path in sorted((ROOT / "recon/data").glob("rodata_*.c")):
        match = re.search(r"rodata_((?:0x)?[0-9a-fA-F]+)", path.name)
        if not match:
            continue
        base = int(match.group(1), 16)
        text = path.read_text(errors="replace")[:600]
        length = re.search(r"(?:VA\s+0x[0-9a-fA-F]+,\s*)?(\d+) bytes", text)
        if length:
            tables.append((base, base + int(length.group(1)),
                           str(path.relative_to(ROOT))))
    return tables


def source_owners(retained_text):
    owners = defaultdict(list)
    retained_files = []
    for path in sorted((ROOT / "recon/symbolized/app").glob("*.c")):
        if path.name not in retained_text:
            continue
        retained_files.append(path)
        text = path.read_text(errors="replace")
        identity = re.search(r"identity:\s+\S+\s+@\s+(0x[0-9a-fA-F]+)", text[:1000])
        if identity:
            owners[int(identity.group(1), 16)].append(path)
    return owners, retained_files


def has_definition(text, symbol):
    return bool(re.search(
        r"(?ms)^[A-Za-z_][^;{}]*\b" + re.escape(symbol) +
        r"\s*\([^;{}]*\)\s*\{", text))


def classify_pointer(pointer, target, inventory, tables, functions):
    for level in inventory["init_levels"]:
        for entry in level["entries"]:
            if pointer == int(entry["entry_va"], 16):
                return {"class": "init_entry", "table": level["level"],
                        "owner": entry["name"], "source": entry["source"]}
    isr = inventory["sw_isr_table"]
    start = int(isr["start"], 16)
    if start <= pointer < start + isr["count"] * isr["stride"]:
        irq = (pointer - start) // isr["stride"]
        row = next((row for row in isr["non_default"] if row["irq"] == irq), None)
        return {"class": "sw_isr_entry", "table": "irq_%d" % irq,
                "owner": None if row is None else row["name"],
                "source": "recon/catalogs/app_root_inventory.json"}
    devices = inventory["devices"]
    start = int(devices["start"], 16)
    if start <= pointer < start + devices["count"] * devices["stride"]:
        index = (pointer - start) // devices["stride"]
        return {"class": "device_descriptor", "table": devices["entries"][index]["name"],
                "owner": devices["entries"][index]["init"],
                "source": "recon/catalogs/app_root_inventory.json"}
    for thread in inventory["dynamic_threads"]:
        if "0x%08x" % target in thread["entry_candidates"]:
            return {"class": "dynamic_thread_reference", "table": thread["name"],
                    "owner": thread["ownership"],
                    "source": "recon/catalogs/app_root_inventory.json"}
    for start, end, source in tables:
        if start <= pointer < end:
            return {"class": "verified_pointer_table", "table": "0x%08x" % start,
                    "owner": Path(source).stem, "source": source}
    previous = None
    for row in functions:
        if row["entry"] + row["capped_size"] <= pointer:
            previous = row
        else:
            break
    return {"class": "pre_init_gap" if pointer < 0x879B0 else "post_init_gap",
            "table": None,
            "owner": None if previous is None else previous["name"],
            "source": None}


def candidate_names(address, function, name_row, manifest_row):
    names = {function["name"], function["ghidra_name"],
             name_row.get("name"), name_row.get("raw_name")}
    names.update(name_row.get("aliases") or [])
    if manifest_row:
        names.update(manifest_row.get(key) for key in
                     ("raw_symbol", "current_symbol", "upstream_symbol"))
    names.discard(None)
    return sorted(names)


def build(elf_path):
    functions = function_catalog()
    by_address = {row["entry"]: row for row in functions}
    refs = scan_pointers(functions)
    if len(refs) != EXPECTED["address_taken_identities"]:
        raise ValueError("address-taken identity drift: %d" % len(refs))
    names = json.loads(NAMES.read_text())["by_address"]
    manifest = json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]
    manifest = {int(row["va"], 16): row for row in manifest}
    inventory = json.loads(INVENTORY.read_text())
    retained_text = RETAINED.read_text()
    identity_owners, retained_files = source_owners(retained_text)
    texts = {path: path.read_text(errors="replace") for path in retained_files}
    symbols = elf_symbols(elf_path)
    tables = data_tables()

    unmaterialized = []
    all_materialized = 0
    for address, pointers in sorted(refs.items()):
        function = by_address[address]
        address_text = "0x%08x" % address
        name_row = names[address_text]
        manifest_row = manifest.get(address)
        candidates = candidate_names(address, function, name_row, manifest_row)
        hits = {name: symbols[name] for name in candidates if name in symbols}
        collision = any(len(owners) != 1 for owners in hits.values())
        if hits and not collision:
            all_materialized += 1
            continue

        semantic_alias = STOCK_ALIASES.get(address)
        alias_owners = symbols.get(semantic_alias, []) if semantic_alias else []
        source_paths = identity_owners.get(address, [])
        current = name_row["name"]
        defining = [path for path in source_paths if has_definition(texts[path], current)]
        manifest_owner = None if manifest_row is None else manifest_row.get("upstream_unit")
        occurrences = [classify_pointer(pointer, address, inventory, tables, functions)
                       | {"pointer_va": "0x%08x" % pointer}
                       for pointer in pointers]

        emitted = False
        resolution = "unresolved_report_only"
        owner_kind = "catalog_only"
        exact_source = None
        link_symbol = None
        blockers = []
        if collision:
            resolution = "ambiguous_live_owner_rejected"
            blockers.append("candidate alias has multiple live ELF owners")
        elif semantic_alias and len(alias_owners) == 1:
            resolution = "resolved_existing_stock_alias"
            owner_kind = "stock_alias"
            exact_source = next((item["source"] for item in occurrences
                                 if item["class"] == "init_entry"), manifest_owner)
            link_symbol = semantic_alias
        elif name_row.get("human") and len(defining) == 1:
            resolution = "emitted_unique_recovered_root"
            owner_kind = "retained_reconstruction"
            exact_source = str(defining[0].relative_to(ROOT))
            link_symbol = current
            emitted = True
        elif not name_row.get("human"):
            blockers.append("no reviewed human-readable symbol")
        elif len(defining) != 1:
            blockers.append("retained definition owner count is %d" % len(defining))
        if manifest_owner and exact_source is None:
            exact_source = manifest_owner
            owner_kind = "reviewed_upstream_owner"

        unmaterialized.append({
            "original_va": address_text,
            "original_name": function["name"],
            "current_symbol": current,
            "upstream_alias": semantic_alias or
                (None if manifest_row is None else manifest_row.get("upstream_symbol")),
            "catalog_size": function["size"],
            "capped_size": function["capped_size"],
            "discovery_candidates": candidates,
            "live_candidate_owners": hits,
            "pointer_occurrences": occurrences,
            "source_ownership": {"kind": owner_kind, "exact_source": exact_source,
                                 "retained_identity_sources":
                                     [str(path.relative_to(ROOT)) for path in source_paths]},
            "resolution": resolution,
            "link_symbol": link_symbol,
            "emitted_root": emitted,
            "blockers": blockers,
        })

    pre_only = sum(all(int(item["pointer_va"], 16) < 0x879B0
                       for item in row["pointer_occurrences"])
                   for row in unmaterialized)
    post = sum(any(int(item["pointer_va"], 16) >= 0x879B0
                   for item in row["pointer_occurrences"]) for row in unmaterialized)
    collision_addresses = {
        row["original_va"] for row in unmaterialized
        if row["resolution"] == "ambiguous_live_owner_rejected"
    }
    post_or_collision = sum(
        any(int(item["pointer_va"], 16) >= 0x879B0
            for item in row["pointer_occurrences"])
        or row["original_va"] in collision_addresses
        for row in unmaterialized)
    summary = {
        "address_taken_identities": len(refs),
        "materialized_identities": all_materialized,
        "unmaterialized_identities": len(unmaterialized),
        "unmaterialized_capped_bytes": sum(row["capped_size"] for row in unmaterialized),
        "pre_init_only_identities": pre_only,
        "post_init_pointer_identities": post,
        "post_init_or_collision_review_identities": post_or_collision,
        "emitted_named_roots": sum(row["emitted_root"] for row in unmaterialized),
        "resolved_existing_stock_aliases": sum(
            row["resolution"] == "resolved_existing_stock_alias" for row in unmaterialized),
        "ambiguous_rejected": sum(
            row["resolution"] == "ambiguous_live_owner_rejected" for row in unmaterialized),
    }
    for key, value in EXPECTED.items():
        if summary[key] != value:
            raise ValueError("%s drift: %r != %r" % (key, summary[key], value))

    # Report the full original call closure as an audit bound.  This does not
    # authorize retention of unnamed descendants.
    graph = load_gz(REFGRAPH)["functions"]
    queue = deque(int(row["original_va"], 16) for row in unmaterialized)
    closure = set(queue)
    while queue:
        node = queue.popleft()
        record = graph.get(hex(node), {})
        for callee in record.get("calls", []):
            target = int(callee, 16)
            if target in by_address and target not in closure:
                closure.add(target)
                queue.append(target)
    summary["union_call_closure_identities"] = len(closure)
    summary["union_call_closure_capped_bytes"] = sum(
        by_address[address]["capped_size"] for address in closure)

    return {
        "schema": 1, "core": "app", "status": "fail_closed",
        "policy": "aligned Thumb pointers outside capped functions; named unique owners only; SDC report-only",
        "inputs": {
            "image": {"path": "app_update.bin", "sha256": sha256(ROOT / "app_update.bin")},
            "normal_gc_elf": {"path": str(elf_path), "sha256": sha256(elf_path)},
            "classified": {"path": str(CLASSIFIED.relative_to(ROOT)), "sha256": sha256(CLASSIFIED)},
            "function_names": {"path": str(NAMES.relative_to(ROOT)), "sha256": sha256(NAMES)},
            "adoption_manifest": {"path": str(MANIFEST.relative_to(ROOT)), "sha256": sha256(MANIFEST)},
        },
        "gates": EXPECTED,
        "summary": summary,
        "entries": unmaterialized,
    }


def cmake(data):
    roots = sorted({row["link_symbol"] for row in data["entries"] if row["emitted_root"]})
    return "\n".join([
        "# Generated by tools/build_app_address_taken_roots.py; do not edit.",
        "# Fail-closed: only unique named retained definitions; never numeric VAs.",
        "set(G1_ADDRESS_TAKEN_RECOVERED_ROOTS",
        *["  %s" % symbol for symbol in roots],
        ")", "",
    ])


def markdown(data):
    summary = data["summary"]
    lines = [
        "# CPUAPP address-taken root ledger", "",
        "The shipped image was scanned at aligned words outside capped true function "
        "intervals. Only odd Thumb pointers to exact catalog entries were accepted. "
        "Original identities absent from the normal-GC ELF remain explicit; only "
        "human-readable symbols with one retained definition are emitted as roots. "
        "Ambiguous aliases, raw addresses, and unnamed functions are report-only.", "",
        "- Address-taken identities: **%d**" % summary["address_taken_identities"],
        "- Unmaterialized original identities: **%d / %d capped bytes**" %
            (summary["unmaterialized_identities"], summary["unmaterialized_capped_bytes"]),
        "- Pre-init-only identities: **%d**" % summary["pre_init_only_identities"],
        "- Post-init pointer identities: **%d**; post-init-or-collision review set: **%d**" %
            (summary["post_init_pointer_identities"],
             summary["post_init_or_collision_review_identities"]),
        "- Emitted unique named roots: **%d**" % summary["emitted_named_roots"],
        "- Existing reviewed stock aliases: **%d**" % summary["resolved_existing_stock_aliases"],
        "- Ambiguous aliases rejected: **%d**" % summary["ambiguous_rejected"],
        "- Original union call closure: **%d identities / %d capped bytes**" %
            (summary["union_call_closure_identities"],
             summary["union_call_closure_capped_bytes"]), "",
        "| Original | Current / stock alias | Pointer owner classes | Resolution | Source |",
        "|---|---|---|---|---|",
    ]
    for row in data["entries"]:
        classes = ", ".join(sorted({item["class"] for item in row["pointer_occurrences"]}))
        alias = row["current_symbol"]
        if row["upstream_alias"] and row["upstream_alias"] != alias:
            alias += " / " + row["upstream_alias"]
        lines.append("| `%s` %s | `%s` | %s | %s | %s |" % (
            row["original_va"], row["original_name"], alias, classes,
            row["resolution"], row["source_ownership"]["exact_source"] or "—"))
    lines.append("")
    return "\n".join(lines)


def update(path, content, check):
    old = path.read_text() if path.exists() else None
    if check and old != content:
        raise ValueError("stale generated file: %s" % path)
    if not check and old != content:
        path.write_text(content)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--elf", type=Path,
                        default=Path("/private/tmp/g1-cohesive-app-head-f49a3b86/zephyr/zephyr.elf"))
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build(args.elf)
    update(OUT_JSON, json.dumps(data, indent=1, sort_keys=True) + "\n", args.check)
    update(OUT_MD, markdown(data), args.check)
    update(OUT_CMAKE, cmake(data), args.check)
    print(json.dumps(data["summary"], sort_keys=True))


if __name__ == "__main__":
    main()
