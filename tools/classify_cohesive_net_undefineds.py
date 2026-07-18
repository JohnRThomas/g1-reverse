#!/usr/bin/env python3
"""Classify the unresolved symbols in the cohesive CPUNET Zephyr link.

Unlike ``classify_net_link_residue.py``, this reads the actual Zephyr link
inputs.  It computes unresolved symbols as:

    undefined(app/libapp.a) - definitions(all final-link objects/archives)
                               - linker-script PROVIDEs

This remains usable after a failed link and does not require reconfiguration.
Private SDC/MPSL matches are deliberately report-only, including private MPSL
entries which an older adoption decision marked for exclusion.
"""

from __future__ import annotations

import argparse
import gzip
import hashlib
import io
import json
import os
import re
import shlex
import subprocess
from collections import Counter, defaultdict
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_BUILD = Path("/private/tmp/g1-cohesive-net-after-99cff8e1")
NM = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-nm")
READELF = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-readelf")
GCC = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc")
NRFXLIB = Path("/Users/freedomcoder/ncs251/nrfxlib")
NCS_MANIFEST = Path("/Users/freedomcoder/ncs251/nrf")
NET_BINARY = ROOT / "netcore_image.bin"

OUTPUT = ROOT / "recon/catalogs/net_cohesive_undefined_classification.json"
MARKDOWN = ROOT / "recon/catalogs/net_cohesive_undefined_classification.md"

CATEGORIES = (
    "private_sdc_mpsl_report_only",
    "stock_sdk_or_glue",
    "interior_or_anomalous_identity",
)

VERSION_TAGS = ("v2.4.2", "v2.5.0", "v2.5.1", "v2.5.2", "v2.5.3", "v2.6.0")
ARCHIVES = {
    "softdevice_controller": {
        "path": "softdevice_controller/lib/cortex-m33+nodsp/soft-float/libsoftdevice_controller_multirole.a",
        "member": "libsoftdevice_controller_s140_debug_soft__obfuscated.elf",
    },
    "mpsl": {
        "path": "mpsl/lib/cortex-m33+nodsp/soft-float/libmpsl.a",
        "member": "libmpsl_debug_soft__obfuscated.elf",
    },
}

PUBLIC_PROVIDERS = {
    "ipc_static_vrings_shm_size": {
        "symbol": "ipc_static_vrings_shm_size",
        "unit": "zephyr/subsys/ipc/ipc_service/backends/ipc_static_vrings.c",
    },
    "k_timer_stop": {
        "symbol": "z_impl_k_timer_stop",
        "unit": "zephyr/kernel/timer.c",
    },
    "z_except_reason": {
        "symbol": "z_except_reason",
        "unit": "zephyr/arch/arm/core/aarch32/fatal.c",
    },
}


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1 << 20), b""):
            digest.update(block)
    return digest.hexdigest()


def load_json(path: Path):
    if path.suffix == ".gz":
        with gzip.open(path, "rt") as stream:
            return json.load(stream)
    return json.loads(path.read_text())


def run(args: list[str | Path], *, cwd: Path | None = None) -> str:
    return subprocess.check_output(
        [str(arg) for arg in args], cwd=cwd, text=True,
        stderr=subprocess.DEVNULL,
    )


def final_link_command(build: Path) -> str:
    commands = run(["ninja", "-C", build, "-t", "commands", "zephyr/zephyr_pre0.elf"])
    candidates = [line for line in commands.splitlines()
                  if "zephyr_pre0.elf" in line and "arm-zephyr-eabi-gcc" in line]
    if not candidates:
        raise ValueError("could not find zephyr_pre0.elf link command")
    return candidates[-1]


def link_paths(build: Path, command: str) -> list[Path]:
    # CMake emits ``: && gcc ... && cd ...``.  The middle clause is the link.
    clauses = command.split("&&")
    link = next(clause for clause in clauses if "arm-zephyr-eabi-gcc" in clause)
    paths = []
    for token in shlex.split(link):
        if not token.endswith((".a", ".o", ".obj")):
            continue
        path = Path(token)
        if not path.is_absolute():
            path = build / path
        if path.exists():
            paths.append(path.resolve())
    for library in ("libc.a", "libgcc.a"):
        path = Path(run([GCC, "--specs=picolibc.specs", "-print-file-name=" + library]).strip())
        if path.exists():
            paths.append(path.resolve())
    return sorted(set(paths))


def global_definitions(paths: list[Path]) -> set[str]:
    result: set[str] = set()
    for path in paths:
        output = run([NM, "-g", "--defined-only", path])
        for line in output.splitlines():
            fields = line.split()
            if len(fields) >= 3:
                result.add(fields[-1])
    return result


def archive_undefined_callers(archive: Path) -> dict[str, list[str]]:
    callers: dict[str, set[str]] = defaultdict(set)
    for line in run([NM, "-u", "-A", archive]).splitlines():
        match = re.match(r".*\.a:([^:]+):\s+U\s+(\S+)$", line)
        if match:
            callers[match.group(2)].add(match.group(1))
    return {symbol: sorted(objects) for symbol, objects in callers.items()}


def text_relocation_counts(archive: Path) -> Counter:
    counts: Counter = Counter()
    in_text = False
    # Wide output is required: otherwise readelf truncates long reconstructed
    # identities and silently undercounts their relocations.
    for line in run([READELF, "-W", "-r", archive]).splitlines():
        if line.startswith("Relocation section "):
            match = re.search(r"'([^']+)'", line)
            in_text = bool(match and match.group(1).startswith(".rel.text"))
            continue
        if not in_text:
            continue
        fields = line.split()
        if len(fields) >= 5 and fields[0].isalnum() and fields[2].startswith("R_ARM_"):
            counts[fields[-1]] += 1
    return counts


def linker_provides(path: Path) -> set[str]:
    return set(re.findall(r"\bPROVIDE\s*\(\s*([A-Za-z_]\w*)", path.read_text()))


def symbol_va(symbol: str, baseline: dict) -> str | None:
    row = baseline.get(symbol)
    if row and row.get("va"):
        return row["va"].lower()
    match = re.fullmatch(r"FUN_([0-9a-fA-F]{8})", symbol)
    return "0x" + match.group(1).lower() if match else None


def is_private_archive_owner(record: dict | None) -> bool:
    if not record:
        return False
    unit = record.get("upstream_unit", "")
    symbol = record.get("upstream_symbol", "")
    private_archive = ("nrfxlib/mpsl/" in unit or "softdevice_controller" in unit)
    return private_archive and symbol.startswith("sym_")


def graph_record(graph: dict, va: str | None) -> dict | None:
    if not va:
        return None
    key = "0x%x" % int(va, 16)
    return graph.get("functions", {}).get(key)


def _ar_members(data: bytes) -> dict[str, bytes]:
    if not data.startswith(b"!<arch>\n"):
        raise ValueError("not an ar archive")
    offset = 8
    strings = b""
    members: dict[str, bytes] = {}
    while offset + 60 <= len(data):
        header = data[offset:offset + 60]
        offset += 60
        size = int(header[48:58])
        payload = data[offset:offset + size]
        offset += size + (size & 1)
        encoded_name = header[:16].decode("ascii").rstrip()
        if encoded_name == "//":
            strings = payload
            continue
        if encoded_name.startswith("#1/"):
            length = int(encoded_name[3:])
            name = payload[:length].decode()
            payload = payload[length:]
        elif encoded_name.startswith("/") and encoded_name[1:].rstrip("/").isdigit():
            start = int(encoded_name[1:].rstrip("/"))
            name = strings[start:].split(b"/\n", 1)[0].decode()
        else:
            name = encoded_name.rstrip("/")
        members[name] = payload
    return members


def _archive_version(tag: str, family: str) -> dict:
    spec = ARCHIVES[family]
    archive = subprocess.check_output(
        ["git", "-C", str(NRFXLIB), "show", f"{tag}:{spec['path']}"]
    )
    member = _ar_members(archive)[spec["member"]]
    elf = ELFFile(io.BytesIO(member))
    symbols: dict[str, set[str]] = defaultdict(set)
    symtab = elf.get_section_by_name(".symtab")
    for symbol in symtab.iter_symbols():
        if (symbol["st_info"]["type"] != "STT_FUNC" or not symbol.name or
                not isinstance(symbol["st_shndx"], int)):
            continue
        section = elf.get_section(symbol["st_shndx"])
        start = (int(symbol["st_value"]) & ~1) - int(section["sh_addr"])
        size = int(symbol["st_size"])
        symbols[symbol.name].add(sha256_bytes(section.data()[start:start + size]))
    return {
        "tag_commit": run(
            ["git", "-C", NRFXLIB, "rev-parse", f"{tag}^{{commit}}"]
        ).strip(),
        "archive_git_blob": run(
            ["git", "-C", NRFXLIB, "rev-parse", f"{tag}:{spec['path']}"]
        ).strip(),
        "archive_size": len(archive),
        "archive_sha256": sha256_bytes(archive),
        "member_sha256": sha256_bytes(member),
        "symbols": symbols,
    }


def _manifest_revision(project: str) -> str:
    """Read one project revision from the released NCS v2.5.1 manifest."""
    manifest = run(["git", "-C", NCS_MANIFEST, "show", "v2.5.1:west.yml"])
    match = re.search(
        rf"(?ms)^\s*- name:\s*{re.escape(project)}\s*$.*?^\s+revision:\s*(\S+)\s*$",
        manifest,
    )
    if not match:
        raise ValueError(f"missing {project} revision in NCS v2.5.1 west.yml")
    return match.group(1)


def firmware_release_provenance() -> dict:
    data = NET_BINARY.read_bytes()
    banner = b"*** Booting nRF Connect SDK v2.5.1 ***"
    offset = data.find(banner)
    if offset < 0:
        raise ValueError("CPUNET NCS v2.5.1 boot banner not found")
    return {
        "binary": str(NET_BINARY),
        "binary_sha256": sha256_file(NET_BINARY),
        "embedded_banner": banner.decode(),
        "image_offset": f"0x{offset:x}",
        "ncs_release": "v2.5.1",
        "ncs_manifest_commit": run(
            ["git", "-C", NCS_MANIFEST, "rev-parse", "v2.5.1^{commit}"]
        ).strip(),
        "released_component_revisions": {
            "zephyr": _manifest_revision("zephyr"),
            "nrfxlib": _manifest_revision("nrfxlib"),
            "mbedtls": _manifest_revision("mbedtls"),
        },
        "interpretation": (
            "The shipped CPUNET image identifies the umbrella SDK release directly. "
            "This selects the NCS v2.5.1 west manifest even where an individual "
            "component's binary payload was unchanged from the preceding tag."
        ),
    }


def version_discrimination(selected: dict[str, set[str]]) -> dict:
    cache: dict[tuple[str, str], dict] = {}
    for family in ARCHIVES:
        for tag in VERSION_TAGS:
            cache[(family, tag)] = _archive_version(tag, family)
    rows = []
    for tag in VERSION_TAGS:
        row = {"tag": tag, "families": {}}
        for family, names in selected.items():
            current = cache[(family, "v2.5.1")]
            candidate = cache[(family, tag)]
            same = different = missing = 0
            for name in names:
                if name not in candidate["symbols"]:
                    missing += 1
                elif current["symbols"].get(name, set()) & candidate["symbols"][name]:
                    same += 1
                else:
                    different += 1
            row["families"][family] = {
                "tag_commit": candidate["tag_commit"],
                "archive_git_blob": candidate["archive_git_blob"],
                "archive_size": candidate["archive_size"],
                "archive_sha256": candidate["archive_sha256"],
                "member_sha256": candidate["member_sha256"],
                "selected_identity_count": len(names),
                "selected_body_byte_identical": same,
                "selected_body_different": different,
                "selected_identity_missing": missing,
                "whole_archive_identical_to_v2_5_1": (
                    candidate["archive_sha256"] == current["archive_sha256"]
                ),
            }
        rows.append(row)
    return {
        "repository": str(NRFXLIB),
        "manifest_selected_tag": "v2.5.1",
        "firmware_release_provenance": firmware_release_provenance(),
        "binary_archive_indistinguishable_tags": ["v2.5.0", "v2.5.1"],
        "conclusion": (
            "The selected SDC and MPSL archives and every selected private body are "
            "byte-identical in nrfxlib v2.5.0 and v2.5.1, so those archive bytes alone "
            "select only that two-tag interval. The shipped CPUNET image independently "
            "embeds the NCS v2.5.1 boot banner, selecting the released v2.5.1 west manifest. "
            "v2.4.2, v2.5.2/v2.5.3, and v2.6.0 are rejected as exact archive pairs."
        ),
        "tags": rows,
    }


def generate(build: Path) -> dict:
    build = build.resolve()
    app_archive = build / "app/libapp.a"
    linker = build / "zephyr/linker_zephyr_pre0.cmd"
    command = final_link_command(build)
    paths = link_paths(build, command)
    callers = archive_undefined_callers(app_archive)
    relocations = text_relocation_counts(app_archive)
    unresolved = sorted(set(callers) - global_definitions(paths) - linker_provides(linker))

    baseline_path = ROOT / "recon/catalogs/net_link_function_residue.json"
    aliases_path = ROOT / "recon/catalogs/net_readable_alias_resolutions.json"
    manifest_path = ROOT / "recon/ownership/adoption_manifest.json"
    sdc_path = ROOT / "recon/ownership/net_sdc_archive_ownership.json"
    spaces_path = ROOT / "recon/catalogs/net_address_spaces.json"
    graph_path = ROOT / "recon/catalogs/refgraph_net.json.gz"
    anomaly_path = ROOT / "recon/catalogs/net_fun_0102d25c_identity_audit.json"

    baseline_report = load_json(baseline_path)
    baseline = {row["symbol"]: row for row in baseline_report["entries"]}
    aliases = load_json(aliases_path)
    retained_aliases = {row["symbol"]: row for row in aliases["retained_aliases"]}
    sdk_aliases = {row["symbol"]: row for row in aliases["sdk_owners"]}
    manifest = {row["va"].lower(): row for row in
                load_json(manifest_path)["cores"]["net"]["entries"]}
    sdc = {row["address"].lower(): row for row in load_json(sdc_path)["functions"]}
    spaces = {row["analysis_address"].lower(): row for row in
              load_json(spaces_path)["functions"]}
    graph = load_json(graph_path)

    entries = []
    selected = {"softdevice_controller": set(), "mpsl": set()}
    for symbol in unresolved:
        base = baseline.get(symbol, {})
        va = symbol_va(symbol, baseline)
        adoption = manifest.get(va) if va else None
        provider = None
        policy_conflict = False

        if base.get("closeout_disposition") in {
            "anomalous_non_executable_target", "blocked_c_unexpressible"
        }:
            category = "interior_or_anomalous_identity"
            resolution_kind = base["closeout_disposition"]
            provider = {"status": "no_valid_provider", "evidence": base.get("closeout_evidence")}
        elif base.get("closeout_disposition") == "private_sdc_report_only":
            category = "private_sdc_mpsl_report_only"
            resolution_kind = "private_sdc_report_only"
            owner = sdc.get(va) if va else None
            if owner:
                selected["softdevice_controller"].add(owner["best"]["symbol"])
                provider = {
                    "status": "archive_identity_report_only",
                    "family": "softdevice_controller",
                    "archive_symbol": owner["best"]["symbol"],
                    "archive_member": owner["best"]["archive_member"],
                    "match_kind": owner["match_kind"],
                    "score": owner["score"],
                    "unique_identity": owner["unique_identity"],
                    "safe_to_auto_resolve": False,
                }
            else:
                provider = {
                    "status": "uncatalogued_private_controller_entry",
                    "family": "softdevice_controller",
                    "archive_symbol": None,
                    "safe_to_auto_resolve": False,
                    "evidence": base.get("closeout_evidence"),
                }
        elif is_private_archive_owner(adoption):
            category = "private_sdc_mpsl_report_only"
            family = "mpsl" if "nrfxlib/mpsl/" in adoption["upstream_unit"] else "softdevice_controller"
            resolution_kind = "private_obfuscated_archive_identity"
            selected[family].add(adoption["upstream_symbol"])
            policy_conflict = adoption.get("exclude_reconstruction") is True
            provider = {
                "status": "archive_identity_report_only",
                "family": family,
                "archive_symbol": adoption["upstream_symbol"],
                "archive_member_or_map_unit": adoption["upstream_unit"],
                "signature_confidence": adoption.get("confidence"),
                "signature_evidence": adoption.get("evidence", []),
                "per_va_unique_archive_identity_proven": False,
                "member_selection_state_closure_proven": False,
                "safe_to_auto_resolve": False,
                "manifest_exclusion_conflict": policy_conflict,
                "recommended_disposition": "retain_or_restore_report_only",
            }
        elif symbol in retained_aliases:
            category = "stock_sdk_or_glue"
            resolution_kind = "existing_readable_alias_not_linked"
            alias = retained_aliases[symbol]
            provider = {
                "status": "existing_reviewed_alias",
                "symbol": alias["target"],
                "analysis_address": alias["va"],
                "linker_fragment": "recon/symbols/g1_net_readable_aliases.ld",
            }
        else:
            category = "stock_sdk_or_glue"
            resolution_kind = "stock_provider_requires_call_identity_integration"
            if adoption and adoption.get("exclude_reconstruction"):
                provider = {
                    "status": "manifest_approved_upstream_owner",
                    "symbol": adoption.get("upstream_symbol"),
                    "unit": adoption.get("upstream_unit"),
                    "component": adoption.get("component"),
                }
            elif symbol in sdk_aliases:
                alias = sdk_aliases[symbol]
                provider = {
                    "status": "manifest_approved_upstream_owner",
                    "symbol": alias["upstream_symbol"],
                    "analysis_address": alias["va"],
                }
            elif symbol in PUBLIC_PROVIDERS:
                provider = {"status": "selected_public_sdk_api", **PUBLIC_PROVIDERS[symbol]}
            else:
                provider = {
                    "status": "stock_or_glue_identity_from_prior_link_audit",
                    "evidence": base.get("reason"),
                }

        address = spaces.get(va) if va else None
        graph_row = graph_record(graph, va)
        entries.append({
            "symbol": symbol,
            "analysis_address": va,
            "runtime_address": address.get("runtime_address") if address else None,
            "category": category,
            "resolution_kind": resolution_kind,
            "link_reference_count": relocations[symbol],
            "caller_count": len(callers[symbol]),
            "caller_objects": callers[symbol],
            "refgraph_callers": graph_row.get("callers", []) if graph_row else [],
            "provider": provider,
            "manifest_policy_conflict": policy_conflict,
        })

    counts = Counter(row["category"] for row in entries)
    kinds = Counter(row["resolution_kind"] for row in entries)
    private_families = Counter(
        row["provider"].get("family", "unknown") for row in entries
        if row["category"] == "private_sdc_mpsl_report_only"
    )
    private_unique_identities = {
        family: len({
            row["provider"].get("archive_symbol")
            for row in entries
            if row["category"] == "private_sdc_mpsl_report_only"
            and row["provider"].get("family") == family
            and row["provider"].get("archive_symbol")
        })
        for family in ("softdevice_controller", "mpsl")
    }
    queue = [
        {
            "priority": 0,
            "action": "restore private MPSL entries to report-only policy",
            "symbol_count": sum(row["manifest_policy_conflict"] for row in entries),
            "symbols": [row["symbol"] for row in entries if row["manifest_policy_conflict"]],
            "automatic_action_authorized": False,
        },
        {
            "priority": 1,
            "action": "include the already-reviewed readable alias fragment in the cohesive CPUNET link",
            "symbol_count": kinds["existing_readable_alias_not_linked"],
            "symbols": [row["symbol"] for row in entries
                        if row["resolution_kind"] == "existing_readable_alias_not_linked"],
            "provider": "recon/symbols/g1_net_readable_aliases.ld",
        },
        {
            "priority": 2,
            "action": "replace raw caller identities with selected public/stock SDK provider symbols",
            "symbol_count": kinds["stock_provider_requires_call_identity_integration"],
            "symbols": [row["symbol"] for row in entries
                        if row["resolution_kind"] == "stock_provider_requires_call_identity_integration"],
        },
        {
            "priority": 3,
            "action": "resolve anomalous control-flow identities with assembly/relocation evidence",
            "symbol_count": counts["interior_or_anomalous_identity"],
            "symbols": [row["symbol"] for row in entries
                        if row["category"] == "interior_or_anomalous_identity"],
            "automatic_action_authorized": False,
        },
    ]

    inputs = [baseline_path, aliases_path, manifest_path, sdc_path, spaces_path,
              graph_path, anomaly_path, app_archive, linker]
    return {
        "schema": "g1.net.cohesive_undefined.v1",
        "core": "net",
        "build_directory": str(build),
        "method": "undefined app archive symbols minus all final-link definitions and linker PROVIDEs",
        "policy": {
            "private_sdc_mpsl_report_only": True,
            "automatic_private_archive_alias_or_removal": False,
            "canonical_sources_modified": False,
        },
        "inputs": [{"path": str(path), "sha256": sha256_file(path)} for path in inputs],
        "link_command_sha256": sha256_bytes(command.encode()),
        "summary": {
            "undefined_symbols": len(entries),
            "link_reference_relocations": sum(row["link_reference_count"] for row in entries),
            "by_category": {name: counts[name] for name in CATEGORIES},
            "by_resolution_kind": dict(sorted(kinds.items())),
            "private_by_family": dict(sorted(private_families.items())),
            "private_unique_archive_identities": private_unique_identities,
            "private_manifest_policy_conflicts": sum(row["manifest_policy_conflict"] for row in entries),
            "non_private_actionable_symbols": counts["stock_sdk_or_glue"],
        },
        "action_queue": queue,
        "archive_version_discrimination": version_discrimination(selected),
        "entries": entries,
    }


def render_markdown(report: dict) -> str:
    summary = report["summary"]
    provenance = report["archive_version_discrimination"]["firmware_release_provenance"]
    lines = [
        "# Cohesive CPUNET undefined-symbol classification", "",
        "This is the unresolved surface of the actual Zephyr cohesive link, computed from its",
        "archive/object inputs. Private SDC/MPSL identities remain report-only; this report",
        "does not authorize aliases, removals, or source replacement for them.", "",
        f"- Undefined symbols: **{summary['undefined_symbols']}**",
        f"- Text relocation references: **{summary['link_reference_relocations']}**",
        f"- Private SDC/MPSL report-only: **{summary['by_category']['private_sdc_mpsl_report_only']}**",
        f"- Stock SDK/glue: **{summary['by_category']['stock_sdk_or_glue']}**",
        f"- Interior/anomalous: **{summary['by_category']['interior_or_anomalous_identity']}**",
        f"- Private MPSL manifest-policy conflicts: **{summary['private_manifest_policy_conflicts']}**",
        f"- MPSL rows / unique private archive identities: **{summary['private_by_family'].get('mpsl', 0)} / {summary['private_unique_archive_identities'].get('mpsl', 0)}**",
        "", "## Version discrimination", "",
        report["archive_version_discrimination"]["conclusion"], "",
        f"- Firmware evidence: `{provenance['embedded_banner']}` at CPUNET image offset "
        f"`{provenance['image_offset']}`.",
        f"- Released nrfxlib revision: `{provenance['released_component_revisions']['nrfxlib']}`.",
        f"- Released Zephyr revision: `{provenance['released_component_revisions']['zephyr']}`.",
        "",
        "| Tag | SDC archive exact | SDC selected same/different/missing | MPSL archive exact | MPSL selected same/different/missing |",
        "|---|---|---:|---|---:|",
    ]
    for row in report["archive_version_discrimination"]["tags"]:
        sdc = row["families"]["softdevice_controller"]
        mpsl = row["families"]["mpsl"]
        lines.append(
            f"| `{row['tag']}` | {sdc['whole_archive_identical_to_v2_5_1']} | "
            f"{sdc['selected_body_byte_identical']}/{sdc['selected_body_different']}/{sdc['selected_identity_missing']} | "
            f"{mpsl['whole_archive_identical_to_v2_5_1']} | "
            f"{mpsl['selected_body_byte_identical']}/{mpsl['selected_body_different']}/{mpsl['selected_identity_missing']} |"
        )
    lines.extend(["", "## Prioritized non-SDC action queue", ""])
    for action in report["action_queue"]:
        lines.append(f"{action['priority'] + 1}. **P{action['priority']}** — {action['action']} ({action['symbol_count']} symbols).")
    lines.extend(["", "## Per-symbol evidence", "",
                  "| Symbol | Analysis / runtime | Category | Kind | Refs | Callers | Provider |",
                  "|---|---|---|---|---:|---:|---|"])
    for row in report["entries"]:
        provider = row["provider"]
        owner = provider.get("symbol") or provider.get("archive_symbol") or provider.get("status")
        lines.append(
            f"| `{row['symbol']}` | {row['analysis_address'] or ''} / {row['runtime_address'] or ''} | "
            f"`{row['category']}` | `{row['resolution_kind']}` | {row['link_reference_count']} | "
            f"{row['caller_count']} | `{owner}` |"
        )
    return "\n".join(lines) + "\n"


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--build-dir", type=Path, default=DEFAULT_BUILD)
    parser.add_argument("--output", type=Path, default=OUTPUT)
    parser.add_argument("--markdown", type=Path, default=MARKDOWN)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    report = generate(args.build_dir)
    encoded = json.dumps(report, indent=1) + "\n"
    rendered = render_markdown(report)
    if args.check:
        if args.output.read_text() != encoded or args.markdown.read_text() != rendered:
            raise SystemExit("cohesive CPUNET undefined report is stale")
        print("cohesive CPUNET undefined report: PASS")
        return 0
    args.output.write_text(encoded)
    args.markdown.write_text(rendered)
    print(json.dumps(report["summary"], indent=1))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
