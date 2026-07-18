#!/usr/bin/env python3
"""Inventory original APP/NET functions affected by ordered MMIO tracing."""

from __future__ import annotations

import gzip
import hashlib
import json
import argparse
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB
from capstone.arm import ARM_OP_IMM, ARM_OP_MEM, ARM_OP_REG

import extract
import net_extract
import recon_kit
import net_recon_kit
from parity import emu


ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "recon/catalogs"
_MD = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
_MD.detail = True


def _sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def _load_json_gz(path: Path):
    with gzip.open(path, "rt") as stream:
        return json.load(stream)


def _literal_value(core: str, address: int) -> int:
    reader = extract.read if core == "app" else net_extract.read
    return int.from_bytes(reader(address, 4), "little")


def _source_for(core: str, va: int, names: dict) -> tuple[str | None, str]:
    record = names.get("by_address", {}).get(f"0x{va:08x}", {})
    identities = [record.get("name"), record.get("raw_name")]
    identities.extend(record.get("aliases") or ())
    raw = f"FUN_{va:08x}"
    identities.append(raw)
    for identity in identities:
        if not identity:
            continue
        path = ROOT / "recon" / core / "src" / f"{identity}.c"
        if path.is_file():
            return path.relative_to(ROOT).as_posix(), identity
    return None, record.get("name") or raw


def _constant_result(insn, before: dict[str, int]):
    ops = insn.operands
    if not ops or ops[0].type != ARM_OP_REG:
        return None
    dest = insn.reg_name(ops[0].reg)
    mnemonic = insn.mnemonic.split(".", 1)[0]

    def value(op):
        if op.type == ARM_OP_IMM:
            return int(op.imm) & 0xffffffff
        if op.type == ARM_OP_REG:
            return before.get(insn.reg_name(op.reg))
        return None

    if mnemonic.startswith("ldr") and len(ops) >= 2 and ops[1].type == ARM_OP_MEM:
        mem = ops[1].mem
        if insn.reg_name(mem.base) == "pc" and mem.index == 0:
            literal = (((insn.address + 4) & ~3) + mem.disp) & 0xffffffff
            return dest, _literal_value(insn._core_name, literal)
        return None
    if mnemonic in ("mov", "movs", "movw") and len(ops) >= 2:
        result = value(ops[1])
        return (dest, result) if result is not None else None
    if mnemonic == "movt" and len(ops) >= 2 and ops[1].type == ARM_OP_IMM:
        low = before.get(dest, 0) & 0xffff
        return dest, low | ((int(ops[1].imm) & 0xffff) << 16)
    if mnemonic in ("add", "adds", "sub", "subs", "lsl", "lsls"):
        if len(ops) >= 3:
            left, right = value(ops[1]), value(ops[2])
        elif len(ops) == 2:
            left, right = before.get(dest), value(ops[1])
        else:
            return None
        if left is None or right is None:
            return None
        if mnemonic.startswith("add"):
            result = left + right
        elif mnemonic.startswith("sub"):
            result = left - right
        else:
            result = left << (right & 31)
        return dest, result & 0xffffffff
    if mnemonic == "uxth" and len(ops) >= 2:
        result = value(ops[1])
        return (dest, result & 0xffff) if result is not None else None
    return None


def _access_kind(mnemonic: str) -> str | None:
    mnemonic = mnemonic.lower()
    if mnemonic.startswith(("ldr", "ldm", "lda", "ldrex")):
        return "read"
    if mnemonic.startswith(("str", "stm", "stl", "strex")):
        return "write"
    return None


def _scan_function(core: str, va: int, size: int, data: bytes) -> list[dict]:
    constants: dict[str, int] = {}
    accesses = []
    seen = set()
    for insn in _MD.disasm(data, va):
        if insn.address >= va + size:
            break
        # Attach core only for the PC-literal helper; Capstone instruction
        # objects permit ordinary Python attributes.
        insn._core_name = core
        before = dict(constants)
        kind = _access_kind(insn.mnemonic)
        if kind:
            for operand in insn.operands:
                if operand.type != ARM_OP_MEM:
                    continue
                base_name = insn.reg_name(operand.mem.base)
                base = before.get(base_name)
                if base is None or base_name == "pc":
                    continue
                index_name = insn.reg_name(operand.mem.index) if operand.mem.index else None
                index = before.get(index_name) if index_name else 0
                exact = index is not None
                address = ((base + operand.mem.disp + index) & 0xffffffff
                           if exact else base)
                if not emu._is_nrf53_mmio(address):
                    continue
                width = max(1, int(getattr(operand, "size", 0) or 4))
                key = (insn.address, kind, address, exact, width)
                if key in seen:
                    continue
                seen.add(key)
                accesses.append({
                    "instruction_address": f"0x{insn.address:08x}",
                    "instruction": f"{insn.mnemonic} {insn.op_str}".strip(),
                    "kind": kind,
                    "address": f"0x{address:08x}",
                    "address_precision": "exact" if exact else "base_only",
                    "width": width,
                })

        try:
            _reads, writes = insn.regs_access()
        except Exception:
            writes = ()
        for register in writes:
            constants.pop(insn.reg_name(register), None)
        result = _constant_result(insn, before)
        if result is not None:
            constants[result[0]] = result[1]
    return accesses


def build_static() -> dict:
    inputs = []
    functions = []
    for core in ("app", "net"):
        funcs_path = CATALOG / f"{core}_funcs.json.gz"
        refs_path = CATALOG / f"refgraph_{core}.json.gz"
        names_path = CATALOG / f"function_names_{core}.json"
        inputs.extend({"path": path.relative_to(ROOT).as_posix(),
                       "sha256": _sha256(path)}
                      for path in (funcs_path, refs_path, names_path))
        catalog = _load_json_gz(funcs_path)["functions"]
        refs = _load_json_gz(refs_path)["functions"]
        names = json.loads(names_path.read_text())
        overrides = (recon_kit.TRUE_SIZE_OVERRIDES if core == "app"
                     else net_recon_kit.TRUE_SIZE_OVERRIDES)
        reader = extract.read if core == "app" else net_extract.read
        for function in sorted(catalog, key=lambda row: row["entry"]):
            va = int(function["entry"])
            size = int(overrides.get(va, function["size"]))
            accesses = _scan_function(core, va, size, reader(va, size))
            graph = refs.get(hex(va), {})
            mmio_ref_values = set()
            for value in graph.get("data_refs", ()):
                try:
                    address = int(value, 16)
                except (TypeError, ValueError):
                    continue
                if emu._is_nrf53_mmio(address):
                    mmio_ref_values.add(f"0x{address:08x}")
            mmio_refs = sorted(mmio_ref_values)
            if not accesses and not mmio_refs:
                continue
            source, verify_name = _source_for(core, va, names)
            functions.append({
                "core": core,
                "analysis_address": f"0x{va:08x}",
                "name": names.get("by_address", {}).get(
                    f"0x{va:08x}", {}).get("name") or function["name"],
                "verify_name": verify_name,
                "true_executable_extent": size,
                "canonical_source": source,
                "source_sha256": (_sha256(ROOT / source) if source else None),
                "original_mmio_accesses": accesses,
                "refgraph_mmio_refs": mmio_refs,
                "ordered_read_trace_affected": any(
                    access["kind"] == "read" for access in accesses),
            })

    all_mmio_functions = functions
    affected = [row for row in all_mmio_functions
                if row["ordered_read_trace_affected"]]
    compact_affected = []
    for row in affected:
        grouped_reads = {}
        for access in row["original_mmio_accesses"]:
            if access["kind"] != "read":
                continue
            key = (access["address"], access["address_precision"])
            grouped_reads.setdefault(key, []).append(
                access["instruction_address"])
        compact = {key: value for key, value in row.items()
                   if key != "original_mmio_accesses"}
        compact["original_mmio_reads"] = [
            {"address": address, "address_precision": precision,
             "instruction_addresses": sorted(addresses)}
            for (address, precision), addresses in sorted(grouped_reads.items())
        ]
        compact["original_mmio_write_count"] = sum(
            access["kind"] == "write"
            for access in row["original_mmio_accesses"])
        compact_affected.append(compact)
    by_core = {
        core: {
            "mmio_reference_functions": sum(row["core"] == core
                                              for row in all_mmio_functions),
            "ordered_read_trace_functions": sum(row["core"] == core
                                                  for row in affected),
            "canonical_read_trace_targets": sum(
                row["core"] == core and row["canonical_source"] is not None
                for row in affected),
        }
        for core in ("app", "net")
    }
    return {
        "schema": "g1.parity.mmio_coverage_inventory.v1",
        "method": {
            "binary_analysis": "conservative linear register-constant propagation",
            "cross_check": "Ghidra refgraph direct MMIO data references",
            "mmio_windows": [
                {"start": f"0x{start:08x}", "end_exclusive": f"0x{end:08x}"}
                for start, end in emu.NRF53_MMIO_WINDOWS
            ],
            "target_gate": "original binary contains a statically resolved MMIO read",
        },
        "inputs": inputs,
        "summary": {
            "by_core": by_core,
            "mmio_reference_functions": len(all_mmio_functions),
            "ordered_read_trace_functions": len(affected),
            "canonical_read_trace_targets": sum(
                row["canonical_source"] is not None for row in affected),
        },
        # Only read-bearing functions are semantically affected by the new
        # ordered-read gate.  Write-only/reference-only totals remain above.
        "functions": compact_affected,
    }


def add_reverify(static: dict, results_path: Path,
                 diagnostics_path: Path) -> dict:
    targets = {
        (row["core"], row["analysis_address"]): row
        for row in static["functions"] if row["canonical_source"] is not None
    }
    results = []
    for line in results_path.read_text().splitlines():
        if line.strip():
            results.append(json.loads(line))
    by_key = {(row["core"], row["va"]): row for row in results}
    if len(by_key) != len(results) or set(by_key) != set(targets):
        raise RuntimeError("targeted reverify result set is incomplete or duplicated")
    diagnostics = {
        (row["core"], row["va"]): row
        for row in json.loads(diagnostics_path.read_text())
    }
    failed = {key for key, row in by_key.items() if row["status"] != "PASS"}
    if set(diagnostics) != failed:
        raise RuntimeError("failure diagnostic set does not match reverify failures")

    rows = []
    for key in sorted(targets):
        result = dict(by_key[key])
        diagnostic = diagnostics.get(key)
        result["source"] = targets[key]["canonical_source"]
        result["source_sha256"] = targets[key]["source_sha256"]
        if diagnostic is not None:
            result["detail_kind"] = diagnostic["detail_kind"]
            result["first_event_divergence"] = diagnostic[
                "first_event_divergence"]
            events = diagnostic["first_event_divergence"] or {}
            original = events.get("original") or []
            candidate = events.get("candidate") or []
            result["classification"] = (
                "ordered_mmio_read_divergence"
                if ((original and original[0] == "R") or
                    (candidate and candidate[0] == "R"))
                else "preexisting_non_mmio_verifier_gate"
            )
        else:
            result["classification"] = "pass"
        rows.append(result)

    counts = {}
    for row in rows:
        counts[row["classification"]] = counts.get(row["classification"], 0) + 1
    static["targeted_reverify"] = {
        "verifier": "tools/cfg_verify.py",
        "trials_random": 1,
        "coverage": "one seeded trial plus every existing reviewed CFG/state case",
        "summary": {
            "targets": len(rows),
            "status_counts": {
                status: sum(row["status"] == status for row in rows)
                for status in sorted({row["status"] for row in rows})
            },
            "classification_counts": counts,
        },
        "functions": rows,
    }
    return static


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--results", type=Path)
    parser.add_argument("--diagnostics", type=Path)
    args = parser.parse_args()
    document = build_static()
    if bool(args.results) != bool(args.diagnostics):
        parser.error("--results and --diagnostics must be supplied together")
    if args.results:
        document = add_reverify(document, args.results, args.diagnostics)
    print(json.dumps(document, indent=1, sort_keys=True))
