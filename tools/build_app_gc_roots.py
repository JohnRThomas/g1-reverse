#!/usr/bin/env python3
"""Generate fail-closed CPUAPP section-GC roots from binary-derived evidence."""

import argparse
import hashlib
import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
INVENTORY = ROOT / "recon/catalogs/app_root_inventory.json"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
OUT_CMAKE = ROOT / "recon/generated/app_gc_roots.cmake"
OUT_JSON = ROOT / "recon/catalogs/app_gc_roots.json"
OUT_MD = ROOT / "recon/catalogs/app_gc_roots.md"

# The durable name map still exposes these three sources by raw identity while
# their proven C definitions already carry a readable public symbol.
LINK_SYMBOL_OVERRIDES = {
    0x00021DA8: "ble_work_thread",
    0x00023844: "brightness_level",
    0x0002A8D8: "low_speed_peripheral_dispatch_thread",
}
EXPECTED_UNRESOLVED = {0x0002692C, 0x00027CFC, 0x00032420}
MAIN_VA = 0x00016EB8


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def source_index():
    result = {}
    pattern = re.compile(r"identity:\s+\S+\s+@\s+(0x[0-9a-fA-F]+)")
    for path in sorted((ROOT / "recon/symbolized/app").glob("*.c")):
        text = path.read_text(errors="replace")
        match = pattern.search(text[:1000])
        if match:
            result[int(match.group(1), 16)] = (path, text)
    return result


def has_definition(text, symbol):
    pattern = re.compile(
        r"(?ms)^[A-Za-z_][^;{}]*\b" + re.escape(symbol) +
        r"\s*\([^;{}]*\)\s*\{")
    return bool(pattern.search(text))


def build():
    inventory = json.loads(INVENTORY.read_text())
    names = json.loads(NAMES.read_text())["by_address"]
    retained = RETAINED.read_text()
    sources = source_index()
    if inventory["image"]["sha256"] != sha256(ROOT / "app_update.bin"):
        raise ValueError("CPUAPP root inventory image hash drift")
    gates = inventory["gates"]
    if gates.get("retain_all_is_audit_only") is not True:
        raise ValueError("inventory no longer authorizes normal section GC")
    if gates.get("numeric_function_pointers_forbidden_in_production_roots") is not True:
        raise ValueError("numeric production-root policy drift")

    rows = []
    main_path, main_text = sources[MAIN_VA]
    if not has_definition(main_text, "main"):
        raise ValueError("recovered main definition missing")
    rows.append({
        "kind": "zephyr_application_main", "thread": "main",
        "address": f"0x{MAIN_VA:08x}", "symbol": "main",
        "source": str(main_path.relative_to(ROOT)), "resolved": True,
    })

    unresolved = set()
    for thread in inventory["dynamic_threads"]:
        if thread["ownership"] == "stock_zephyr_bt":
            continue
        for address_text in thread["entry_candidates"]:
            address = int(address_text, 16)
            name_row = names.get(address_text)
            if name_row is None or address not in sources:
                unresolved.add(address)
                rows.append({
                    "kind": "dynamic_thread_entry_candidate",
                    "thread": thread["name"], "ownership": thread["ownership"],
                    "address": address_text, "symbol": None, "source": None,
                    "resolved": False,
                })
                continue
            path, text = sources[address]
            symbol = LINK_SYMBOL_OVERRIDES.get(address, name_row["name"])
            if not has_definition(text, symbol):
                raise ValueError(f"{address_text} does not define {symbol}")
            if path.name not in retained:
                raise ValueError(f"GC root source is not retained: {path.name}")
            rows.append({
                "kind": "dynamic_thread_entry_candidate",
                "thread": thread["name"], "ownership": thread["ownership"],
                "address": address_text, "symbol": symbol,
                "source": str(path.relative_to(ROOT)), "resolved": True,
            })
    if unresolved != EXPECTED_UNRESOLVED:
        raise ValueError("unresolved root-candidate drift: %r" %
                         sorted(f"0x{x:08x}" for x in unresolved))
    symbols = [row["symbol"] for row in rows if row["resolved"]]
    if len(symbols) != len(set(symbols)):
        raise ValueError("duplicate named CPUAPP GC root")
    return {
        "schema": 1, "core": "app", "status": "partial_fail_closed",
        "policy": "named roots only; numeric addresses forbidden; SDC report-only",
        "inventory": str(INVENTORY.relative_to(ROOT)),
        "inventory_sha256": sha256(INVENTORY),
        "summary": {
            "named_roots": len(symbols),
            "resolved_dynamic_candidates": len(symbols) - 1,
            "unresolved_dynamic_candidates": len(unresolved),
            "complete_root_graph": False,
        },
        "unresolved_addresses": sorted(f"0x{x:08x}" for x in unresolved),
        "roots": rows,
    }


def cmake(data):
    lines = [
        "# Generated by tools/build_app_gc_roots.py; do not edit.",
        "# Numeric firmware addresses are intentionally never linker roots.",
        "set(G1_RECOVERED_GC_ROOTS",
    ]
    for row in data["roots"]:
        if row["resolved"]:
            lines.append(f"  {row['symbol']}")
    lines += [")", "set(G1_UNRESOLVED_GC_ROOT_ADDRESSES"]
    lines += [f'  "{address}"' for address in data["unresolved_addresses"]]
    lines += [")", ""]
    return "\n".join(lines)


def markdown(data):
    lines = [
        "# CPUAPP section-GC root receipt", "",
        "Normal section GC is authorized by the binary-derived root inventory. "
        "Only named recovered definitions are passed to the linker; numeric "
        "firmware addresses are never forced as roots.", "",
        f"- Named roots: **{data['summary']['named_roots']}**",
        f"- Unresolved candidates: **{data['summary']['unresolved_dynamic_candidates']}**",
        "- Complete recovered root graph: **no**", "",
        "| Thread | Firmware candidate | Link symbol | State |", "|---|---:|---|---|",
    ]
    for row in data["roots"]:
        lines.append("| `%s` | `%s` | %s | %s |" % (
            row["thread"], row["address"],
            "`%s`" % row["symbol"] if row["symbol"] else "—",
            "named root" if row["resolved"] else "unresolved; not forced"))
    lines.append("")
    return "\n".join(lines)


def update(path, content, check):
    old = path.read_text() if path.exists() else None
    if check and old != content:
        raise ValueError(f"stale generated file: {path}")
    if not check and old != content:
        path.write_text(content)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build()
    update(OUT_JSON, json.dumps(data, indent=1, sort_keys=True) + "\n", args.check)
    update(OUT_CMAKE, cmake(data), args.check)
    update(OUT_MD, markdown(data), args.check)
    print(json.dumps(data["summary"], sort_keys=True))


if __name__ == "__main__":
    main()
