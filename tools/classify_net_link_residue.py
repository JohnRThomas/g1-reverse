#!/usr/bin/env python3
"""Classify unresolved CPUNET function symbols from the reconstruction link.

The partial link produced by ``tools/full_link.py net`` is intentionally used:
it contains every symbolized reconstruction and every reconstructed data unit,
without letting Zephyr's garbage collection hide unreachable references.  SDK
ownership is then overlaid from the reviewed adoption manifest.

This tool never changes function sources.  It writes a durable per-symbol audit
whose five categories are the remediation choices used by the integration wave.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
from collections import Counter, defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_ELF = ROOT / "build/net_full.elf"
NM = Path(
    "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
    "arm-zephyr-eabi-nm"
)

PRIMARY_RECOVERY_RECEIPTS = (
    "recon/ownership/net_link_gap_recovery.json",
    "recon/analysis/net_link_gap2_recovery_receipt.json",
    "recon/ownership/net_link_gap3_recovery.json",
    "recon/ownership/net_link_gap4_recovery.json",
    "recon/ownership/net_link_gap5_recovery.json",
)
DESCENDANT_RECOVERY_RECEIPTS = (
    "recon/ownership/net_link_gap6_recovery.json",
    "recon/ownership/net_link_gap7_recovery.json",
    "recon/ownership/net_link_gap8_recovery.json",
    "recon/ownership/net_link_gap9_recovery.json",
)
EXPECTED_RECOVERED_GAPS = {
    "FUN_01009224", "FUN_0100f110", "FUN_0100f7e0", "FUN_0100fae4",
    "FUN_010108b8", "FUN_01013d90", "FUN_01016250", "FUN_0101bbc8",
    "FUN_0101e404", "FUN_01025734", "FUN_01025bf8", "FUN_0102689c",
    "FUN_010271da", "FUN_0102722c", "FUN_010278e4", "FUN_01027e1c",
    "FUN_01028010", "FUN_01028034", "FUN_01028134", "FUN_010283b8",
}
EXPECTED_RECOVERED_DESCENDANTS = {
    "FUN_0100d3a0", "FUN_0100f5b4", "FUN_01019088", "FUN_01025fd4",
    "FUN_0102602e", "FUN_0102609e", "FUN_01027894", "FUN_010278bc",
    "FUN_01027ad2", "FUN_01027fa6", "FUN_01028112", "FUN_010283a4",
    "FUN_0100f6b0",
}

CATEGORIES = (
    "true_missing_reconstructed_entry",
    "interior_or_tail_alias",
    "sdk_or_config_symbol",
    "compiler_or_ghidra_pseudo",
    "naming_or_symbolization_defect",
    "data_or_global_alias_gap",
)

DATA_SYMBOL = re.compile(
    r"^(?:g_[0-9a-fA-F]{8}|rodata_[0-9a-fA-F]+|(?:DAT|PTR|LAB)_[0-9a-fA-F]{8})$"
)

# These are public APIs emitted by the selected Zephyr/OpenAMP configuration.
# They have no per-VA adoption record because Ghidra did not create a function
# at every referenced entry.  Their source ownership is nevertheless explicit.
SDK_SYMBOLS = {
    "__aeabi_uldivmod": "ARM EABI compiler runtime division helper",
    "ipc_rpmsg_init": "NCS IPC-service RPMsg backend",
    "ipc_static_vrings_init": "NCS IPC-service static-vrings backend",
    "ipc_static_vrings_shm_size": "NCS IPC-service static-vrings backend",
    "k_work_queue_init": "Zephyr kernel work queue API",
    "k_work_queue_start": "Zephyr kernel work queue API",
    "k_timer_stop": "Zephyr public timer API; exact z_impl_k_timer_stop signature owner",
    "sys_rand_get": "Zephyr random API",
    "sdc_event_publish": "Nordic SoftDevice Controller public event API",
    "z_except_reason": "Zephyr architecture exception API",
    "z_impl_k_thread_abort": "Zephyr kernel thread API",
}

# These names were introduced only to make decompiler output compile.  They do
# not identify firmware functions and must be replaced by C/CMSIS constructs or
# by the real call target.
PSEUDO_SYMBOLS = {
    "FUN_shadow_default": "synthetic decompiler default-path oracle",
    "PHANTOM_BOUNDARY": "synthetic decompiler boundary oracle",
    "PHANTOM_RETRY": "synthetic decompiler retry oracle",
    "g1_arch_runtime_exception": "architecture macro placeholder (ARCH_EXCEPT)",
    "g1_irq_lock": "architecture intrinsic placeholder",
    "g1_irq_unlock": "architecture intrinsic placeholder",
}

# The retained body exists, but its exported spelling differs from a caller's
# spelling.  These are integration/name repairs, not reconstruction work.
NAMING_DEFECTS = {
    "FUN_0101077c_after": "self-local nonreturn label was emitted as an extern",
    "controller_assert": "callers use a stale alias for sdc_assertion_fail",
    "controller_radio_timer_capture_get":
        "readable filename exports thunk_FUN_01025028 instead of its public name",
    "controller_time_now":
        "readable filename exports thunk_FUN_01025034 instead of its public name",
    "rtc_pretick_rtc1_isr_hook":
        "readable filename exports thunk_FUN_0102cfec instead of its public name",
    "sdc_timing_compensation_get":
        "readable filename exports thunk_FUN_010246cc instead of its public name",
}

# Verified directly against netcore_image.bin Thumb bytes.  These references
# enter an existing body/shared return or are one-instruction tail veneers; no
# independent C semantics should be invented for them.
TAIL_ALIASES = {
    "FUN_01008fc0": "shared error return inside the 0x01008e74 controller body",
    "FUN_01008fc6": "shared error return inside the 0x01008e74 controller body",
    "FUN_0100b5f8": "single b.w tail veneer to 0x0100ac34",
}

# Final audit of the thirteen missing entries that are not already explained by
# the manifest's softdevice_controller component.  These dispositions are
# intentionally non-resolving: private SDC bodies remain report-only, and the
# two malformed/C-unexpressible entries do not acquire invented C semantics.
NON_COMPONENT_CLOSEOUT = {
    "FUN_0100ef08": (
        "private_sdc_report_only",
        "internal controller entry at 0x0100ef08 remains a private SDC report-only body",
    ),
    "FUN_01011664": (
        "private_sdc_report_only",
        "private controller entry at 0x01011664 remains report-only",
    ),
    "FUN_01018df8": (
        "private_sdc_report_only",
        "private controller entry at 0x01018df8 remains report-only",
    ),
    "FUN_0101d890": (
        "private_sdc_report_only",
        "private controller entry at 0x0101d890 remains report-only",
    ),
    "FUN_0102665c": (
        "private_sdc_report_only",
        "private controller entry at 0x0102665c remains report-only",
    ),
    "FUN_010292ec": (
        "private_sdc_report_only",
        "private controller entry at 0x010292ec remains report-only",
    ),
    "FUN_0102a1e0": (
        "private_sdc_report_only",
        "private controller entry at 0x0102a1e0 remains report-only",
    ),
    "controller_entry_links_release": (
        "private_sdc_report_only",
        "0x0101df84 is an exact unique private SDC archive match with unpublished ABI",
    ),
    "controller_timing_defaults_apply": (
        "private_sdc_report_only",
        "0x0101e1e4 is an exact unique private SDC archive match with unpublished ABI",
    ),
    "sdc_conn_event_process": (
        "private_sdc_report_only",
        "private SDC connection-event entry at 0x01014b18 remains report-only",
    ),
    "FUN_0102fa84": (
        "blocked_c_unexpressible",
        "entry performs a BASEPRI reset followed by SVC 2; its exception-mediated continuation cannot be represented as an ordinary C call/return body",
    ),
    "FUN_0102d25c": (
        "anomalous_non_executable_target",
        "conditional path branches through literal 0x0103c8a1 into confirmed IPC log-string data; no executable owner or relocation is known",
    ),
    "controller_default_bounds_build": (
        "private_sdc_report_only",
        "0x010282fc is the 126-byte FUN_010282fc body and an exact unique private SDC archive match with unpublished ABI",
    ),
}


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def recovery_rows(receipt_paths: tuple[str, ...]) -> list[dict]:
    """Load exact source/receipt evidence and reject stale recovery claims."""
    rows = []
    seen = set()
    for relative in receipt_paths:
        receipt = ROOT / relative
        data = json.loads(receipt.read_text())
        functions = data.get("functions", data.get("proofs", []))
        if not functions:
            raise ValueError("recovery receipt has no functions: %s" % relative)
        receipt_hash = sha256(receipt)
        for function in functions:
            symbol = function.get("raw_symbol")
            source = function.get("source", function.get("source_path"))
            expected_hash = function.get("source_sha256")
            if not symbol or not source or not expected_hash:
                raise ValueError("incomplete recovery row in %s" % relative)
            if symbol in seen:
                raise ValueError("duplicate recovery owner: %s" % symbol)
            seen.add(symbol)
            source_path = ROOT / source
            if not source_path.is_file():
                raise ValueError("recovered source missing: %s" % source)
            actual_hash = sha256(source_path)
            if actual_hash != expected_hash:
                raise ValueError("recovered source hash drift: %s" % source)
            cfg = function.get("cfg_verify", function.get("cfg_result", {}))
            if cfg and cfg.get("status") != "PASS":
                raise ValueError("recovery CFG proof is not PASS: %s" % symbol)
            rows.append({
                "symbol": symbol,
                "va": function.get("analysis_address"),
                "source": source,
                "source_sha256": actual_hash,
                "receipt": relative,
                "receipt_sha256": receipt_hash,
                "cfg_status": cfg.get("status", "PASS"),
                "true_executable_extent": function.get("true_executable_extent"),
            })
    return sorted(rows, key=lambda row: row["symbol"])


def nm_undefined(path: Path) -> list[str]:
    result = subprocess.run(
        [str(NM), "-u", str(path)], check=True, capture_output=True, text=True
    )
    return sorted({line.split()[-1] for line in result.stdout.splitlines() if line.strip()})


def provided_symbols() -> set[str]:
    provided: set[str] = set()
    for filename in (
        "g1_net_globals.ld",
        "g1_net_aliases.ld",
        "g1_net_function_aliases.ld",
        "g1_net_readable_aliases.ld",
    ):
        for line in (ROOT / "recon/symbols" / filename).read_text().splitlines():
            match = re.search(r"PROVIDE\((\w+)", line)
            if match:
                provided.add(match.group(1))
    return provided


def reference_owners(symbols: set[str]) -> dict[str, list[str]]:
    owners: dict[str, list[str]] = defaultdict(list)
    for obj in sorted((ROOT / "build/net_full_obj").glob("*.o")):
        for symbol in nm_undefined(obj):
            if symbol in symbols:
                owners[symbol].append(obj.name)
    return owners


def load_identity_maps():
    names_path = ROOT / "recon/catalogs/function_names_net.json"
    manifest_path = ROOT / "recon/ownership/adoption_manifest.json"
    readable_path = ROOT / "recon/catalogs/net_readable_alias_resolutions.json"
    names = json.loads(names_path.read_text())
    manifest = json.loads(manifest_path.read_text())
    by_va = names["by_address"]
    by_name = names["by_name"]
    adoption = {
        entry["va"].lower(): entry
        for entry in manifest["cores"]["net"]["entries"]
    }
    readable = json.loads(readable_path.read_text())
    sdk_readable = {row["symbol"]: row for row in readable["sdk_owners"]}
    unresolved_readable = {
        row["symbol"]: row for row in readable["unresolved"]
    }
    return (names_path, manifest_path, readable_path, by_va, by_name,
            adoption, sdk_readable, unresolved_readable)


def symbol_va(symbol: str, by_name: dict[str, str],
              unresolved_readable: dict) -> str | None:
    if symbol in by_name:
        return by_name[symbol].lower()
    if symbol in unresolved_readable:
        return unresolved_readable[symbol]["va"].lower()
    match = re.fullmatch(r"FUN_([0-9a-fA-F]{8})(?:_after)?", symbol)
    if match:
        return "0x" + match.group(1).lower()
    return None


def classify(symbol: str, va: str | None, adoption: dict, sdk_readable: dict):
    if DATA_SYMBOL.fullmatch(symbol):
        return (
            "data_or_global_alias_gap",
            "address-backed data/global spelling lacks a linker pin or reviewed overlap alias",
        )
    if symbol in NAMING_DEFECTS:
        return "naming_or_symbolization_defect", NAMING_DEFECTS[symbol]
    if symbol in PSEUDO_SYMBOLS:
        return "compiler_or_ghidra_pseudo", PSEUDO_SYMBOLS[symbol]
    if symbol in TAIL_ALIASES:
        return "interior_or_tail_alias", TAIL_ALIASES[symbol]
    if symbol in SDK_SYMBOLS:
        return "sdk_or_config_symbol", SDK_SYMBOLS[symbol]
    if symbol in sdk_readable:
        row = sdk_readable[symbol]
        return (
            "sdk_or_config_symbol",
            "canonical readable spelling maps to manifest-approved %s @ %s" %
            (row["upstream_symbol"], row["va"]),
        )
    record = adoption.get(va) if va else None
    if record and record.get("exclude_reconstruction"):
        return (
            "sdk_or_config_symbol",
            "reviewed adoption manifest selects the upstream owner",
        )
    return (
        "true_missing_reconstructed_entry",
        "referenced entry has neither a retained symbolized body nor an adopted owner",
    )


def closeout_disposition(symbol: str, category: str,
                         adoption_record: dict | None):
    if category != "true_missing_reconstructed_entry":
        return None, None, None
    if symbol in NON_COMPONENT_CLOSEOUT:
        disposition, evidence = NON_COMPONENT_CLOSEOUT[symbol]
        return disposition, False, evidence
    component = adoption_record.get("component") if adoption_record else None
    evidence = adoption_record.get("evidence", []) if adoption_record else []
    private_sdc_evidence = any(
        row.get("type") == "sdc_machine_ownership" and
        row.get("safe_to_exclude") is False
        for row in evidence
    )
    if component == "softdevice_controller" or private_sdc_evidence:
        return (
            "private_sdc_report_only",
            False,
            "reviewed SDC ownership remains report-only; no automatic SDC removal is authorized",
        )
    if symbol == "FUN_01025734":
        return (
            "hidden_entry_reconstruction_required",
            True,
            "direct call target is a real compact Thumb entry omitted from the Ghidra function catalog; no retained C owner exists",
        )
    if symbol == "FUN_01025bf8":
        return (
            "retained_reconstruction_required",
            True,
            "catalogued 60-byte controller helper has only an approximate 0.967 stock signature and no retained C owner",
        )
    raise ValueError("true-missing CPUNET symbol lacks closeout disposition: %s" % symbol)


def generate(elf: Path) -> dict:
    (names_path, manifest_path, readable_path, by_va, by_name, adoption,
     sdk_readable, unresolved_readable) = load_identity_maps()
    all_undefined = nm_undefined(elf)
    pins = provided_symbols()
    residue = sorted(symbol for symbol in all_undefined if symbol not in pins)
    recovered = recovery_rows(PRIMARY_RECOVERY_RECEIPTS)
    descendants = recovery_rows(DESCENDANT_RECOVERY_RECEIPTS)
    recovered_symbols = {row["symbol"] for row in recovered}
    descendant_symbols = {row["symbol"] for row in descendants}
    if recovered_symbols != EXPECTED_RECOVERED_GAPS:
        raise ValueError("primary recovery closure drift: missing=%s extra=%s" % (
            sorted(EXPECTED_RECOVERED_GAPS - recovered_symbols),
            sorted(recovered_symbols - EXPECTED_RECOVERED_GAPS)))
    if descendant_symbols != EXPECTED_RECOVERED_DESCENDANTS:
        raise ValueError("descendant recovery closure drift: missing=%s extra=%s" % (
            sorted(EXPECTED_RECOVERED_DESCENDANTS - descendant_symbols),
            sorted(descendant_symbols - EXPECTED_RECOVERED_DESCENDANTS)))
    still_undefined = sorted((recovered_symbols | descendant_symbols) &
                             set(all_undefined))
    if still_undefined:
        raise ValueError("recovered link closure remains undefined: %s" %
                         still_undefined)
    owners = reference_owners(set(residue))

    entries = []
    for symbol in residue:
        va = symbol_va(symbol, by_name, unresolved_readable)
        identity = by_va.get(va) if va else None
        adoption_record = adoption.get(va) if va else None
        category, reason = classify(symbol, va, adoption, sdk_readable)
        disposition, actionable, disposition_evidence = closeout_disposition(
            symbol,
            category,
            adoption_record,
        )
        expected_source = None
        source_exists = False
        if identity:
            expected_source = f"recon/symbolized/net/{identity['name']}.c"
            source_exists = (ROOT / expected_source).exists()
        entries.append(
            {
                "symbol": symbol,
                "va": va,
                "category": category,
                "reason": reason,
                "reference_count": len(owners.get(symbol, [])),
                "reference_objects": owners.get(symbol, []),
                "expected_source": expected_source,
                "expected_source_exists": source_exists,
                "identity_name": identity.get("name") if identity else None,
                "adoption_component": (
                    adoption_record.get("component") if adoption_record else None
                ),
                "adoption_decision": (
                    adoption_record.get("decision") if adoption_record else None
                ),
                "closeout_disposition": disposition,
                "closeout_actionable": actionable,
                "closeout_evidence": disposition_evidence,
            }
        )

    counts = Counter(entry["category"] for entry in entries)
    by_component = Counter(
        entry["adoption_component"] or "unmapped"
        for entry in entries
        if entry["category"] == "true_missing_reconstructed_entry"
    )
    by_disposition = Counter(
        entry["closeout_disposition"]
        for entry in entries
        if entry["closeout_disposition"] is not None
    )
    return {
        "schema": 3,
        "core": "net",
        "scope": "all non-pinned undefined symbols in build/net_full.elf",
        "policy": {
            "sdc_report_only_is_not_an_owner": True,
            "default_without_retained_body_or_adopted_owner":
                "true_missing_reconstructed_entry",
            "canonical_function_semantics_mutated": False,
            "recovered_gap_requires_exact_source_and_receipt_hash": True,
            "expected_unknown_count": 0,
        },
        "inputs": [
            {"path": str(elf.relative_to(ROOT)), "sha256": sha256(elf)},
            {"path": str(names_path.relative_to(ROOT)), "sha256": sha256(names_path)},
            {
                "path": str(manifest_path.relative_to(ROOT)),
                "sha256": sha256(manifest_path),
            },
            {
                "path": str(readable_path.relative_to(ROOT)),
                "sha256": sha256(readable_path),
            },
        ] + [
            {"path": path, "sha256": sha256(ROOT / path)}
            for path in PRIMARY_RECOVERY_RECEIPTS + DESCENDANT_RECOVERY_RECEIPTS
        ],
        "summary": {
            "undefined_total": len(all_undefined),
            "already_pinned_or_aliased": len(all_undefined) - len(residue),
            "classified_residue": len(residue),
            "by_category": {category: counts[category] for category in CATEGORIES},
            "missing_by_adoption_component": dict(sorted(by_component.items())),
            "missing_by_closeout_disposition": dict(sorted(by_disposition.items())),
            "actionable_net_reconstruction_count": sum(
                entry["closeout_actionable"] is True for entry in entries
            ),
            "recovered_link_gap_count": len(recovered),
            "recovered_descendant_count": len(descendants),
            "expected_unknown_count": counts[
                "true_missing_reconstructed_entry"],
        },
        "entries": entries,
        "recovered_link_gaps": recovered,
        "recovered_descendants": descendants,
    }


def render_markdown(report: dict) -> str:
    summary = report["summary"]
    lines = [
        "# CPUNET undefined function residue",
        "",
        "Generated by `tools/classify_net_link_residue.py` from the retain-all",
        "reconstruction partial link. Private SDC ownership remains report-only;",
        "all formerly missing retained bodies are now independently recovered C.",
        "",
        f"- Undefined symbols in partial link: **{summary['undefined_total']}**",
        f"- Already covered by address pins/aliases: **{summary['already_pinned_or_aliased']}**",
        f"- Function/pseudo residue classified here: **{summary['classified_residue']}**",
        f"- Actionable net reconstructions after closeout: **{summary['actionable_net_reconstruction_count']}**",
        f"- Recovered former link gaps: **{summary['recovered_link_gap_count']}**",
        f"- Recovered dependency descendants: **{summary['recovered_descendant_count']}**",
        "",
        "| Category | Count |",
        "|---|---:|",
    ]
    for category in CATEGORIES:
        lines.append(f"| `{category}` | {summary['by_category'][category]} |")
    lines.extend(["", "## Missing-entry closeout", "", "| Disposition | Count |", "|---|---:|"])
    for disposition, count in summary["missing_by_closeout_disposition"].items():
        lines.append(f"| `{disposition}` | {count} |")
    lines.extend(["", "## Per-symbol classification", "", "| Symbol | VA | Category | Disposition | Refs | Evidence |", "|---|---:|---|---|---:|---|"])
    for entry in report["entries"]:
        reason = (entry["closeout_evidence"] or entry["reason"]).replace("|", "\\|")
        lines.append(
            f"| `{entry['symbol']}` | {entry['va'] or ''} | "
            f"`{entry['category']}` | `{entry['closeout_disposition'] or ''}` | "
            f"{entry['reference_count']} | {reason} |"
        )
    for title, key in (("Recovered former UNKNOWNs", "recovered_link_gaps"),
                       ("Recovered closure descendants", "recovered_descendants")):
        lines.extend(["", "## " + title, "", "| Symbol | VA | Source | Receipt |",
                      "|---|---:|---|---|"])
        for entry in report[key]:
            lines.append("| `%s` | %s | `%s` (`%s`) | `%s` (`%s`) |" % (
                entry["symbol"], entry["va"] or "", entry["source"],
                entry["source_sha256"], entry["receipt"],
                entry["receipt_sha256"]))
    return "\n".join(lines) + "\n"


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--elf", type=Path, default=DEFAULT_ELF)
    parser.add_argument(
        "--json", type=Path,
        default=ROOT / "recon/catalogs/net_link_function_residue.json",
    )
    parser.add_argument(
        "--markdown", type=Path,
        default=ROOT / "recon/catalogs/net_link_function_residue.md",
    )
    args = parser.parse_args()
    report = generate(args.elf.resolve())
    args.json.write_text(json.dumps(report, indent=1) + "\n")
    args.markdown.write_text(render_markdown(report))
    print(json.dumps(report["summary"], indent=1))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
