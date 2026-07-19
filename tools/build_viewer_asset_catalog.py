#!/usr/bin/env python3
"""Build the evidence-gated catalog consumed by the G1 asset viewer.

The sweep which discovers viewer assets is intentionally parallel: individual
reports do not have to use an identical envelope, and a report can be replaced
atomically while this program is running.  This builder is the normalization
boundary.  It accepts the report shapes documented by the sweep agents, keeps
their complete records as provenance, and emits one stable schema.

An asset is admitted only when it has all four of the following:

* a canonical firmware address;
* explicit provenance (record evidence or report-level ``generated_from``);
* an explicit semantic meaning (a name alone is not sufficient); and
* a confidence assessment.

Reference-semantics records pass through the same gate.  They are kept in a
separate top-level collection and are also joined onto assets by target
address.  Rejected records and every reason for rejection are written to the
quality report, so a rich-looking UI can never hide weak evidence.

Run from any directory (see AGENTS.md for the required Python invocation):

    PYTHONSAFEPATH=1 .venv/bin/python tools/build_viewer_asset_catalog.py

Use ``--strict`` in CI to fail when any input cannot be read or any candidate
record is rejected.
"""

from __future__ import annotations

import argparse
import copy
import json
import os
import re
import tempfile
import time
from collections import Counter, defaultdict
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Iterable


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_INPUT = ROOT / "recon" / "viewer_sweep"
DEFAULT_OUTPUT = ROOT / "recon" / "viewer_assets" / "catalog.json"
DEFAULT_QUALITY = ROOT / "recon" / "viewer_assets" / "quality_report.json"

SCHEMA_VERSION = "g1-viewer-assets/v1"
QUALITY_SCHEMA_VERSION = "g1-viewer-assets-quality/v1"
ADDRESS_RE = re.compile(r"^(?:0x)?([0-9a-fA-F]{1,16})$")
LEVELS = {"high", "medium", "low"}

# Report envelopes used by the independent sweep lanes.  Order matters: a
# report may have both a human summary and its machine records.
RECORD_KEYS = (
    "assets",
    "records",
    "items",
    "constants",
    "tables",
    "strings",
    "visual_assets",
    "data_assets",
)
SEMANTIC_KEYS = (
    "edges",
    "references",
    "reference_semantics",
    "records",
    "items",
    "usages",
)
POINTER_KEYS = (
    "catalog_files",
    "record_files",
    "source_catalogs",
    "asset_catalogs",
)


def utc_now() -> str:
    return datetime.now(timezone.utc).isoformat().replace("+00:00", "Z")


def atomic_json_write(path: Path, payload: Any, *, pretty: bool = True) -> None:
    """Durably replace *path* without exposing a partial JSON document."""

    path.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix=f".{path.name}.", dir=path.parent)
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as stream:
            os.fchmod(stream.fileno(), 0o644)
            if pretty:
                json.dump(payload, stream, indent=2, sort_keys=False, ensure_ascii=False)
            else:
                # The merged catalog contains tens of thousands of rich edge
                # records.  Compact JSON avoids spending ~40 MB on indentation
                # and keeps the generated artifact comfortably below common
                # source-control per-file limits without dropping context.
                json.dump(payload, stream, separators=(",", ":"), sort_keys=False, ensure_ascii=False)
            stream.write("\n")
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary, path)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)


def read_json_retry(path: Path, attempts: int = 12, delay: float = 0.05) -> Any:
    """Read a report which may be in the middle of a non-atomic rewrite."""

    last_error: Exception | None = None
    for attempt in range(attempts):
        try:
            with path.open(encoding="utf-8") as stream:
                return json.load(stream)
        except (OSError, UnicodeDecodeError, json.JSONDecodeError) as exc:
            last_error = exc
            if attempt + 1 < attempts:
                time.sleep(delay)
    raise RuntimeError(f"could not read stable JSON from {path}: {last_error}")


def discover_reports(directory: Path, settle_seconds: float = 0.0) -> list[Path]:
    """Return a stable snapshot of sweep inputs.

    A short optional settle period is useful when the builder is launched while
    the last sweep agents are still renaming temporary files.  Generated output
    is deliberately outside the input directory, preventing feedback loops.
    """

    def snapshot() -> list[Path]:
        found = set(directory.glob("*_report.json")) if directory.exists() else set()
        reference = directory / "reference_semantics.json"
        if reference.exists():
            found.add(reference)
        return sorted(path.resolve() for path in found if path.is_file())

    paths = snapshot()
    if settle_seconds <= 0:
        return paths
    deadline = time.monotonic() + min(settle_seconds, 60.0)
    signature = None
    stable_rounds = 0
    while time.monotonic() < deadline:
        current = snapshot()
        current_signature = tuple(
            (str(path), path.stat().st_size, path.stat().st_mtime_ns) for path in current
        )
        if current_signature == signature:
            stable_rounds += 1
            if stable_rounds >= 2:
                return current
        else:
            stable_rounds = 0
            signature = current_signature
        paths = current
        time.sleep(min(0.1, max(0.0, deadline - time.monotonic())))
    return paths


def canonical_address(value: Any) -> str | None:
    """Normalize integers/hex strings and reject ambiguous decimal strings."""

    if isinstance(value, bool) or value is None:
        return None
    if isinstance(value, int):
        number = value
    elif isinstance(value, str):
        token = value.strip()
        match = ADDRESS_RE.fullmatch(token)
        if not match:
            return None
        # Firmware reports overwhelmingly use hexadecimal addresses.  Require
        # an explicit prefix unless the token contains a-f or is eight digits.
        if not token.lower().startswith("0x") and not re.search(r"[a-fA-F]", token) and len(token) != 8:
            return None
        number = int(match.group(1), 16)
    else:
        return None
    if number < 0 or number > 0xFFFFFFFF:
        return None
    return f"0x{number:08x}"


def first_present(mapping: dict[str, Any], paths: Iterable[tuple[str, ...]]) -> Any:
    for path in paths:
        value: Any = mapping
        for part in path:
            if not isinstance(value, dict) or part not in value:
                break
            value = value[part]
        else:
            if value not in (None, "", [], {}):
                return value
    return None


def address_from_record(record: dict[str, Any], *, semantic: bool = False) -> str | None:
    ranges = record.get("address_ranges")
    if isinstance(ranges, list):
        for item in ranges:
            if not isinstance(item, dict):
                continue
            value = item.get("address_start") or item.get("pointer_address")
            normalized = canonical_address(value)
            if normalized is not None:
                return normalized
    semantic_paths = (
        ("target_address",),
        ("data_address",),
        ("referenced_address",),
        # A data edge can point into the middle of a containing object.  Keep
        # the byte-exact reference rather than the canonicalized owner base.
        ("target", "referenced_address"),
        ("target", "address"),
        ("target", "start"),
        ("reference", "target_address"),
        ("reference", "target"),
    )
    asset_paths = (
        ("address", "canonical"),
        ("address", "start"),
        ("address", "address"),
        ("address", "value"),
        ("range", "start"),
        ("start_address",),
        ("address_start",),
        ("address",),
        ("va",),
        ("entry",),
        ("symbol", "address"),
        ("symbol", "base_address"),
    )
    value = first_present(record, (*semantic_paths, *asset_paths) if semantic else asset_paths)
    if isinstance(value, dict):
        value = first_present(value, (("canonical",), ("start",), ("address",), ("value",)))
    return canonical_address(value)


def end_address_from_record(record: dict[str, Any]) -> str | None:
    ranges = record.get("address_ranges")
    if isinstance(ranges, list) and ranges and isinstance(ranges[0], dict):
        normalized = canonical_address(
            ranges[0].get("address_end_exclusive") or ranges[0].get("address_end")
        )
        if normalized is not None:
            return normalized
    value = first_present(record, (
        ("address", "end"),
        ("address", "end_exclusive"),
        ("range", "end"),
        ("range", "end_exclusive"),
        ("address_end",),
        ("end_address",),
    ))
    return canonical_address(value)


def normalize_core(record: dict[str, Any], report: dict[str, Any], address: str) -> str:
    value = str(record.get("core") or report.get("core") or "").lower()
    if value in {"app", "cpuapp", "application"}:
        return "app"
    if value in {"net", "cpunet", "network"}:
        return "net"
    space = str(first_present(record, (("address", "space"), ("space",))) or "").lower()
    if "net" in space or int(address, 16) >= 0x01000000:
        return "net"
    return "app"


def normalize_confidence(value: Any) -> dict[str, Any] | None:
    if value in (None, "", [], {}):
        return None
    if isinstance(value, str):
        original = value.strip()
        level = original.lower()
        if level not in LEVELS:
            prefix = next((candidate for candidate in LEVELS
                           if level.startswith(candidate + " ") or level.startswith(candidate + "-")), None)
            level = prefix or level
        if level not in LEVELS:
            return None
        rationale = original if original.lower() != level else None
        return {"level": level, "score": None, "rationale": rationale}
    if isinstance(value, (int, float)) and not isinstance(value, bool):
        score = float(value)
        if score > 1.0 and score <= 100.0:
            score /= 100.0
        if not 0.0 <= score <= 1.0:
            return None
        level = "high" if score >= 0.8 else "medium" if score >= 0.5 else "low"
        return {"level": level, "score": score, "rationale": None}
    if not isinstance(value, dict):
        return None
    result = copy.deepcopy(value)
    level = str(value.get("level") or value.get("rating") or "").strip().lower()
    score = value.get("score", value.get("probability"))
    try:
        if score is not None:
            score = float(score)
            if score > 1.0 and score <= 100.0:
                score /= 100.0
            if not 0.0 <= score <= 1.0:
                score = None
    except (TypeError, ValueError):
        score = None
    if level not in LEVELS and score is not None:
        level = "high" if score >= 0.8 else "medium" if score >= 0.5 else "low"
    if level not in LEVELS:
        return None
    result["level"] = level
    result["score"] = score
    result["rationale"] = first_present(value, (
        ("rationale",), ("basis",), ("reason",), ("notes",),
    ))
    return result


def normalize_meaning(record: dict[str, Any]) -> dict[str, Any] | None:
    value = first_present(record, (
        ("meaning",),
        ("semantic_meaning",),
        ("semantic_role",),
        ("interpretation",),
        ("purpose",),
        ("description",),
        ("behavior",),
        ("decoded", "meaning"),
        ("context", "meaning"),
    ))
    if value in (None, "", [], {}):
        return None
    if isinstance(value, str):
        result: dict[str, Any] = {"summary": value.strip()}
    elif isinstance(value, dict):
        result = copy.deepcopy(value)
        summary = first_present(value, (
            ("summary",), ("description",), ("role",), ("purpose",), ("text",),
        ))
        if not isinstance(summary, str) or not summary.strip():
            # A structured interpretation is meaningful even if it has no
            # prose summary; retain a compact JSON rendering for search/UI.
            summary = json.dumps(value, sort_keys=True, ensure_ascii=False)
        result["summary"] = summary
    else:
        return None
    for key in ("behavior", "subsystem", "protocol_layer", "direction", "category", "caveats"):
        if key in record and record[key] not in (None, "", [], {}):
            result.setdefault(key, copy.deepcopy(record[key]))
    return result


def normalized_evidence(record: dict[str, Any], report: dict[str, Any], report_path: Path) -> list[Any]:
    """Return evidence verbatim; report-level sources are valid provenance."""

    evidence = record.get("evidence")
    if isinstance(evidence, dict):
        evidence = [evidence]
    elif not isinstance(evidence, list):
        evidence = []
    result = copy.deepcopy(evidence)
    provenance = record.get("provenance")
    if isinstance(provenance, dict):
        result.append(copy.deepcopy(provenance))
    elif isinstance(provenance, list):
        result.extend(copy.deepcopy(provenance))
    reference_evidence = record.get("reference_evidence")
    if isinstance(reference_evidence, dict):
        result.append(copy.deepcopy(reference_evidence))
    elif isinstance(reference_evidence, list):
        result.extend(copy.deepcopy(reference_evidence))
    for key in ("defining_source", "source_reference", "source_references"):
        value = record.get(key)
        if value in (None, "", [], {}):
            continue
        values = value if isinstance(value, list) else [value]
        result.extend(copy.deepcopy(values))
    if not result:
        generated = report.get("generated_from") or report.get("provenance")
        if generated not in (None, "", [], {}):
            result.append({
                "kind": "report_provenance",
                "report": str(report_path.relative_to(ROOT)) if report_path.is_relative_to(ROOT) else str(report_path),
                "generated_from": copy.deepcopy(generated),
            })
    return result


def symbol_from_record(record: dict[str, Any], address: str) -> dict[str, Any]:
    symbol = record.get("symbol")
    if isinstance(symbol, str):
        result: dict[str, Any] = {"readable": symbol}
    elif isinstance(symbol, dict):
        result = copy.deepcopy(symbol)
    else:
        result = {}
    ranges = record.get("address_ranges")
    primary_range = ranges[0] if isinstance(ranges, list) and ranges and isinstance(ranges[0], dict) else {}
    result.setdefault("readable", result.get("name") or first_present(record, (
        ("name",), ("readable_name",), ("display_name",),
    )) or primary_range.get("public_name") or primary_range.get("pointer_symbol"))
    result.setdefault("raw", first_present(record, (
        ("raw_symbol",), ("raw_name",), ("symbol", "raw"),
    )) or primary_range.get("raw_symbol"))
    result.setdefault("back_map", record.get("back_map"))
    result["address"] = address
    return {key: value for key, value in result.items() if value not in (None, "", [], {})}


def context_from_record(record: dict[str, Any]) -> dict[str, Any]:
    """Collect rich viewer context without guessing away report-specific data."""

    skip = {
        "id", "asset_id", "address", "address_start", "address_end", "start_address",
        "end_address", "va", "entry", "range", "symbol", "raw_symbol", "raw_name",
        "back_map", "name", "readable_name", "display_name", "asset_type", "type", "kind",
        "meaning", "semantic_meaning", "semantic_role", "interpretation", "purpose",
        "description", "confidence", "evidence", "provenance", "core",
    }
    return {key: copy.deepcopy(value) for key, value in record.items()
            if key not in skip and value not in (None, "", [], {})}


def normalize_record(
    record: Any,
    *,
    report: dict[str, Any],
    report_path: Path,
    index: int,
    semantic: bool,
) -> tuple[dict[str, Any] | None, list[str]]:
    reasons: list[str] = []
    if not isinstance(record, dict):
        return None, ["record is not a JSON object"]
    address = address_from_record(record, semantic=semantic)
    if address is None:
        reasons.append("missing or invalid canonical address")
    meaning = normalize_meaning(record)
    if meaning is None:
        reasons.append("missing explicit semantic meaning")
    confidence = normalize_confidence(record.get("confidence"))
    if confidence is None:
        reasons.append("missing or invalid confidence")
    evidence = normalized_evidence(record, report, report_path)
    if not evidence:
        reasons.append("missing provenance/evidence")
    if reasons:
        return None, reasons
    assert address is not None and meaning is not None and confidence is not None

    report_relative = str(report_path.relative_to(ROOT)) if report_path.is_relative_to(ROOT) else str(report_path)
    asset_type = str(first_present(record, (
        ("asset_type",), ("edge_kind",), ("type",), ("category",), ("kind",),
    )) or ("reference_semantics" if semantic else "data_asset"))
    record_id = str(record.get("id") or record.get("asset_id") or
                    f"{report_path.stem}:{asset_type}:{address}")
    ranges = record.get("address_ranges")
    primary_range = ranges[0] if isinstance(ranges, list) and ranges and isinstance(ranges[0], dict) else {}
    result = {
        "id": record_id,
        "core": normalize_core(record, report, address),
        "asset_type": asset_type,
        "address": {
            "start": address,
            "end": end_address_from_record(record),
            "size": first_present(record, (
                ("address", "size"), ("address", "length_bytes"),
                ("address", "storage_bytes"), ("range", "size"), ("size",), ("length",),
            )) or primary_range.get("size_bytes"),
            "space": first_present(record, (("address", "space"), ("space",))) or primary_range.get("storage"),
        },
        "symbol": symbol_from_record(record, address),
        "meaning": meaning,
        "confidence": confidence,
        "evidence": evidence,
        "context": context_from_record(record),
        "sources": [{
            "report": report_relative,
            "record_index": index,
            "report_schema": report.get("schema") or report.get("schema_version"),
        }],
    }
    result["address"] = {key: value for key, value in result["address"].items()
                         if value not in (None, "", [], {})}
    return result, []


def as_record_list(payload: Any, *, semantic: bool) -> tuple[list[Any], str | None]:
    if isinstance(payload, list):
        return payload, "<root>"
    if not isinstance(payload, dict):
        return [], None
    keys = SEMANTIC_KEYS if semantic else RECORD_KEYS
    for key in keys:
        value = payload.get(key)
        if isinstance(value, list):
            return value, key
        if isinstance(value, dict):
            # Some catalogs are address-keyed maps.
            records = []
            for map_key, item in value.items():
                if isinstance(item, dict):
                    item = copy.deepcopy(item)
                    item.setdefault("id", str(map_key))
                records.append(item)
            return records, key
    return [], None


def pointer_paths(payload: Any, report_path: Path) -> list[Path]:
    """Follow explicit catalog pointers from summary-only reports."""

    if not isinstance(payload, dict):
        return []
    values: list[Any] = []
    for key in POINTER_KEYS:
        value = payload.get(key)
        if value is None:
            continue
        values.extend(value if isinstance(value, list) else [value])
    result = []
    for value in values:
        if isinstance(value, dict):
            value = value.get("path") or value.get("file")
        if not isinstance(value, str):
            continue
        candidate = Path(value).expanduser()
        if not candidate.is_absolute():
            candidate = (report_path.parent / candidate).resolve()
            if not candidate.exists():
                candidate = (ROOT / value).resolve()
        if candidate.suffix == ".json" and candidate.exists():
            result.append(candidate)
    return sorted(set(result))


def merge_unique(left: list[Any], right: list[Any]) -> list[Any]:
    result = copy.deepcopy(left)
    seen = {json.dumps(item, sort_keys=True, ensure_ascii=False) for item in result}
    for item in right:
        key = json.dumps(item, sort_keys=True, ensure_ascii=False)
        if key not in seen:
            result.append(copy.deepcopy(item))
            seen.add(key)
    return result


def merge_assets(existing: dict[str, Any], incoming: dict[str, Any], warnings: list[dict[str, Any]]) -> None:
    """Merge duplicate discoveries without discarding competing conclusions."""

    for field in ("evidence", "sources"):
        existing[field] = merge_unique(existing.get(field, []), incoming.get(field, []))
    existing.setdefault("alternate_meanings", [])
    if existing["meaning"] != incoming["meaning"]:
        existing["alternate_meanings"] = merge_unique(
            existing["alternate_meanings"], [incoming["meaning"]]
        )
        warnings.append({
            "kind": "meaning_conflict",
            "asset_id": existing["id"],
            "address": existing["address"]["start"],
            "kept": existing["meaning"],
            "alternate": incoming["meaning"],
        })
    existing_score = existing["confidence"].get("score")
    incoming_score = incoming["confidence"].get("score")
    ranks = {"low": 1, "medium": 2, "high": 3}
    existing_rank = (existing_score if existing_score is not None else
                     ranks[existing["confidence"]["level"]] / 3)
    incoming_rank = (incoming_score if incoming_score is not None else
                     ranks[incoming["confidence"]["level"]] / 3)
    if incoming_rank > existing_rank:
        existing.setdefault("alternate_confidence", []).append(existing["confidence"])
        existing["confidence"] = incoming["confidence"]
    elif incoming["confidence"] != existing["confidence"]:
        existing.setdefault("alternate_confidence", []).append(incoming["confidence"])
    for key, value in incoming.get("context", {}).items():
        if key not in existing["context"]:
            existing["context"][key] = copy.deepcopy(value)
        elif existing["context"][key] != value:
            existing["context"].setdefault("report_variants", {}).setdefault(key, []).append(
                copy.deepcopy(value)
            )


def dedupe_key(asset: dict[str, Any]) -> tuple[str, str, str]:
    symbol = asset.get("symbol", {})
    identity = symbol.get("raw") or symbol.get("readable") or asset["id"]
    return (asset["core"], asset["address"]["start"],
            f"{asset['asset_type'].lower()}:{str(identity).lower()}")


def report_kind(path: Path) -> str:
    return "reference_semantics" if path.name == "reference_semantics.json" else "assets"


def build(input_dir: Path, *, settle_seconds: float = 0.0) -> tuple[dict[str, Any], dict[str, Any]]:
    discovered = discover_reports(input_dir, settle_seconds)
    queue = list(discovered)
    queued = set(queue)
    processed: set[Path] = set()
    accepted_assets: list[dict[str, Any]] = []
    accepted_semantics: list[dict[str, Any]] = []
    rejections: list[dict[str, Any]] = []
    warnings: list[dict[str, Any]] = []
    report_rows: list[dict[str, Any]] = []
    read_errors: list[dict[str, str]] = []

    while queue:
        path = queue.pop(0)
        if path in processed:
            continue
        processed.add(path)
        semantic = report_kind(path) == "reference_semantics"
        try:
            payload = read_json_retry(path)
        except RuntimeError as exc:
            read_errors.append({"report": str(path), "error": str(exc)})
            continue
        report = payload if isinstance(payload, dict) else {}
        records, record_key = as_record_list(payload, semantic=semantic)
        row = {
            "path": str(path.relative_to(ROOT)) if path.is_relative_to(ROOT) else str(path),
            "kind": "reference_semantics" if semantic else "assets",
            "schema": report.get("schema") or report.get("schema_version"),
            "record_key": record_key,
            "records_seen": len(records),
            "accepted": 0,
            "rejected": 0,
        }
        pointed_paths = pointer_paths(payload, path)
        if not records and not pointed_paths:
            warnings.append({"kind": "no_records", "report": row["path"]})
        for index, record in enumerate(records):
            normalized, reasons = normalize_record(
                record,
                report=report,
                report_path=path,
                index=index,
                semantic=semantic,
            )
            if normalized is None:
                row["rejected"] += 1
                rejections.append({
                    "report": row["path"],
                    "record_index": index,
                    "record_id": record.get("id") if isinstance(record, dict) else None,
                    "reasons": reasons,
                    "record": copy.deepcopy(record),
                })
                continue
            row["accepted"] += 1
            (accepted_semantics if semantic else accepted_assets).append(normalized)
        report_rows.append(row)

        # Summary reports may explicitly point at a larger machine catalog.
        for pointed in pointed_paths:
            if pointed not in queued:
                queue.append(pointed)
                queued.add(pointed)

    by_key: dict[tuple[str, str, str], dict[str, Any]] = {}
    for asset in accepted_assets:
        key = dedupe_key(asset)
        if key in by_key:
            merge_assets(by_key[key], asset, warnings)
        else:
            by_key[key] = asset
    assets = sorted(by_key.values(), key=lambda item: (
        item["core"], int(item["address"]["start"], 16), item["asset_type"], item["id"]
    ))

    semantics_by_address: dict[tuple[str, str], list[dict[str, Any]]] = defaultdict(list)
    for semantic in accepted_semantics:
        semantics_by_address[(semantic["core"], semantic["address"]["start"])].append(semantic)
    for asset in assets:
        matches = semantics_by_address.get((asset["core"], asset["address"]["start"]), [])
        if matches:
            # Keep a lossless normalized semantics table once, and join by ID.
            # This avoids embedding thousands of duplicate source snippets in
            # assets which have many readers while retaining instant lookup.
            asset.setdefault("references", {})["decoded_usage_ids"] = [
                item["id"] for item in matches
            ]

    semantics = sorted(accepted_semantics, key=lambda item: (
        item["core"], int(item["address"]["start"], 16), item["id"]
    ))
    type_counts = Counter(asset["asset_type"] for asset in assets)
    confidence_counts = Counter(asset["confidence"]["level"] for asset in assets)
    semantic_matches = sum(bool(asset.get("references", {}).get("decoded_usage_ids")) for asset in assets)
    relation_keys = {"access", "consumers", "producers", "dispatch_functions", "functions", "related"}
    visual_keys = {"visualization", "renderer", "viewer_hints", "encoding"}
    decoded_keys = {"decoded", "value", "layout", "storage", "identifiers", "related_constants"}
    context_coverage = {
        "with_context": sum(bool(asset.get("context")) for asset in assets),
        "with_symbol": sum(bool(asset.get("symbol")) for asset in assets),
        "with_size": sum(asset.get("address", {}).get("size") is not None for asset in assets),
        "with_end_address": sum(asset.get("address", {}).get("end") is not None for asset in assets),
        "with_relationships": sum(bool(relation_keys & set(asset.get("context", {}))) for asset in assets),
        "with_visualization_or_encoding": sum(bool(visual_keys & set(asset.get("context", {}))) for asset in assets),
        "with_decoded_data_or_layout": sum(bool(decoded_keys & set(asset.get("context", {}))) for asset in assets),
        "with_decoded_usages": semantic_matches,
        "with_multiple_evidence_items": sum(len(asset.get("evidence", [])) > 1 for asset in assets),
    }
    assets_by_address: dict[str, list[str]] = defaultdict(list)
    assets_by_type: dict[str, list[str]] = defaultdict(list)
    semantics_by_target: dict[str, list[str]] = defaultdict(list)
    for asset in assets:
        assets_by_address[asset["address"]["start"]].append(asset["id"])
        assets_by_type[asset["asset_type"]].append(asset["id"])
    for item in semantics:
        semantics_by_target[item["address"]["start"]].append(item["id"])
    generated_at = utc_now()
    catalog = {
        "schema_version": SCHEMA_VERSION,
        "generated_at": generated_at,
        "quality_contract": {
            "required": ["address.start", "evidence", "meaning.summary", "confidence.level"],
            "confidence_levels": ["high", "medium", "low"],
            "address_format": "0x followed by eight lowercase hexadecimal digits",
            "evidence_policy": "record evidence/provenance or explicit report-level generated_from",
            "source_preservation": "evidence is verbatim; report-specific fields are retained under context; sources identify the input record",
        },
        "summary": {
            "assets": len(assets),
            "reference_semantics": len(semantics),
            "assets_with_decoded_usages": semantic_matches,
            "asset_types": dict(sorted(type_counts.items())),
            "confidence": dict(sorted(confidence_counts.items())),
            "context_coverage": context_coverage,
        },
        "assets": assets,
        "reference_semantics": semantics,
        "indices": {
            "assets_by_address": dict(sorted(assets_by_address.items())),
            "assets_by_type": dict(sorted(assets_by_type.items())),
            "semantics_by_target": dict(sorted(semantics_by_target.items())),
        },
    }
    quality = {
        "schema_version": QUALITY_SCHEMA_VERSION,
        "generated_at": generated_at,
        "input_directory": str(input_dir.relative_to(ROOT)) if input_dir.is_relative_to(ROOT) else str(input_dir),
        "summary": {
            "reports_discovered": len(discovered),
            "reports_processed": len(report_rows),
            "pointed_catalogs_processed": max(0, len(report_rows) - len(discovered)),
            "read_errors": len(read_errors),
            "records_seen": sum(row["records_seen"] for row in report_rows),
            "records_accepted": sum(row["accepted"] for row in report_rows),
            "records_rejected": sum(row["rejected"] for row in report_rows),
            "assets_before_deduplication": len(accepted_assets),
            "assets_after_deduplication": len(assets),
            "reference_semantics": len(semantics),
            "assets_with_decoded_usages": semantic_matches,
            "warnings": len(warnings),
        },
        "context_coverage": context_coverage,
        "quality_gates": {
            "canonical_address": True,
            "explicit_meaning": True,
            "confidence": True,
            "provenance": True,
            "all_inputs_read": not read_errors,
            "zero_rejections": not rejections,
        },
        "reports": report_rows,
        "read_errors": read_errors,
        "rejections": rejections,
        "warnings": warnings,
    }
    return catalog, quality


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--input-dir", type=Path, default=DEFAULT_INPUT)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    parser.add_argument("--quality-report", type=Path, default=DEFAULT_QUALITY)
    parser.add_argument(
        "--settle-seconds",
        type=float,
        default=0.0,
        help="wait up to this many seconds for the asynchronously written report set to stabilize",
    )
    parser.add_argument(
        "--strict",
        action="store_true",
        help="exit non-zero if a report is unreadable or any record fails the quality contract",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    catalog, quality = build(args.input_dir.resolve(), settle_seconds=max(0.0, args.settle_seconds))
    atomic_json_write(args.output.resolve(), catalog, pretty=False)
    atomic_json_write(args.quality_report.resolve(), quality)
    summary = quality["summary"]
    print(
        "viewer asset catalog: "
        f"{catalog['summary']['assets']} assets, "
        f"{catalog['summary']['reference_semantics']} reference semantics, "
        f"{summary['records_rejected']} rejected, {summary['read_errors']} read errors"
    )
    if args.strict and (summary["records_rejected"] or summary["read_errors"]):
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
