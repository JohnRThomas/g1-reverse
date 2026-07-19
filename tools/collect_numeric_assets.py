#!/usr/bin/env python3
"""Build the CPUAPP numeric-asset catalog consumed by the symbol viewer.

Run from outside the repository so the repository's historical ``struct.py``
does not shadow the Python standard library::

  cd /tmp && PYTHONSAFEPATH=1 <repo>/.venv/bin/python \
      <repo>/tools/collect_numeric_assets.py

The semantic splits below are deliberately explicit.  Several recon/data C
files contain only the bytes observed by one reader, or merge adjacent objects;
their filename span is therefore not a trustworthy asset boundary.
"""

from __future__ import annotations

import json
import math
import re
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
FIRMWARE = ROOT / "app_update.bin"
LINK_BASE = 0xC200
FILE_BASE = 0x200


def asset(
    ident, address, symbol, subsystem, asset_type, meaning, behavior,
    element_type, shape, consumers, pattern, viewer, axes,
    *, scale=None, units="dimensionless", raw_symbol=None, confidence="high",
    rationale="", source_path=None, source_needle=None, upstream_path=None,
    upstream_needle=None, sample_limit=64, related_constants=None,
):
    count = 1
    for dim in shape:
        count *= dim
    width = {"uint8": 1, "int8": 1, "uint16": 2, "int16": 2,
             "uint32": 4, "int32": 4, "float32": 4}[element_type]
    return {
        "id": ident,
        "address": address,
        "symbol": symbol,
        "raw_symbol": raw_symbol or f"rodata_{address:05x}",
        "subsystem": subsystem,
        "asset_type": asset_type,
        "meaning": meaning,
        "behavior": behavior,
        "storage": {
            "element_type": element_type,
            "count": count,
            "shape": shape,
            "endianness": "little",
            "scale": scale,
            "units": units,
        },
        "consumer_addresses": consumers,
        "access_pattern": pattern,
        "visualization": {"viewer": viewer, "axes": axes},
        "confidence": {"level": confidence, "rationale": rationale},
        "source_path": source_path,
        "source_needle": source_needle or symbol,
        "upstream_path": upstream_path,
        "upstream_needle": upstream_needle or symbol,
        "sample_limit": sample_limit,
        "related_constants": related_constants or [],
        "size": count * width,
    }


LC3 = "/Users/freedomcoder/ncs251/modules/lib/liblc3/src/"

# Canonical object boundaries are supported by the consumer's typed indexing
# and, for libLC3, by the pinned NCS 2.5.1 declarations/definitions.
ASSETS = [
    asset("imu-motion-axis-thresholds", 0x88A44, "g_imu_motion_axis_thresholds",
          "G1/IMU fusion", "threshold_vector",
          "Per-axis absolute motion thresholds used by the stationary/motion classifier.",
          "Each corrected axis delta is compared as fabs(delta) < threshold; repeated over-threshold signs drive the five-sample motion state transition.",
          "float32", [3], [0x0FE88], "threshold[k], k=0..2, selected alongside corrected X/Y/Z deltas",
          "axis-bars", {"x": ["X", "Y", "Z"], "y": "absolute delta threshold"},
          units="fusion-output units", source_path="recon/readable_sources/app/g1/imu_fusion_thread.c",
          source_needle="float thr = F(((unsigned long)&rodata_88a44)",
          rationale="Exact float reads and axis loop are visible in recovered G1 code."),
    asset("scroll-short-refresh-phases", 0x883EC, "g_scroll_short_refresh_phases",
          "G1/display UI", "animation_timeline",
          "Nine monotonically increasing control values for short-text display refresh passes.",
          "Passed in order to reflash_fb_data_to_lcd_ex after rendering text in the short-height branch.",
          "int32", [9], [0x440EC], "sequential glyphs[i], i=0..8; one display refresh per value",
          "timeline", {"x": "refresh pass 0..8", "y": "driver control value"},
          source_path="recon/readable_sources/app/g1/ui_render_scroll_text_frame.c",
          source_needle="rodata_883ec", rationale="Exact nine-word copy and ordered display calls are reconstructed."),
    asset("scroll-tall-refresh-phases", 0x88410, "g_scroll_tall_refresh_phases",
          "G1/display UI", "animation_timeline",
          "Nine increasing negative-to-zero control values for tall-text display refresh passes.",
          "Passed in order to reflash_fb_data_to_lcd_ex in the tall-height branch.",
          "int32", [9], [0x440EC], "sequential glyphs[i], i=0..8; one display refresh per value",
          "timeline", {"x": "refresh pass 0..8", "y": "driver control value"},
          source_path="recon/readable_sources/app/g1/ui_render_scroll_text_frame.c",
          source_needle="rodata_88410", rationale="Exact nine-word copy and ordered display calls are reconstructed."),
    asset("wordwrap-break-codepoints-a", 0x88434, "g_wordwrap_break_codepoints_a",
          "G1/text layout", "codepoint_set",
          "Five UTF-16 punctuation codepoints consulted by the word-wrap renderer.",
          "Indexed as a uint16 table while classifying candidate wrap positions.",
          "uint16", [5], [0x451E0], "tbl1(i), uint16 stride, five grounded entries before adjacent table",
          "codepoint-chips", {"x": "table index", "y": "Unicode codepoint"},
          units="UTF-16 code unit", source_path="recon/readable_sources/app/g1/gui_utf_Wordwrap_draw.c",
          source_needle="static u16 tbl1", rationale="Typed uint16 access and adjacent-table boundary are explicit."),
    asset("wordwrap-break-codepoints-b", 0x8843E, "g_wordwrap_break_codepoints_b",
          "G1/text layout", "codepoint_set",
          "Second five-entry UTF-16 punctuation class used by word wrapping.",
          "Indexed independently as a uint16 table; shipped values equal the first class.",
          "uint16", [5], [0x451E0], "tbl2(i), uint16 stride",
          "codepoint-chips", {"x": "table index", "y": "Unicode codepoint"},
          units="UTF-16 code unit", source_path="recon/readable_sources/app/g1/gui_utf_Wordwrap_draw.c",
          source_needle="static u16 tbl2", rationale="Typed uint16 access and exact five-entry extent are explicit."),
    asset("battery-model-bootstrap-descriptor", 0x88570, "g_battery_model_bootstrap_descriptor",
          "G1/battery/fuel gauge", "parameter_block",
          "Sixteen-word immutable parameter block copied into the battery curve workspace before interpolation.",
          "The estimator copies all 0x40 bytes, then combines the initialized workspace with a caller-supplied 0x1600-byte curve/model payload.",
          "uint32", [16], [0xE2B4, 0xE53C], "whole-struct 64-byte load, then memcpy into workspace[2..17]",
          "hex-float-table", {"x": "word offset", "y": "raw uint32 / float32 interpretation"},
          confidence="medium", source_path="recon/readable_sources/app/g1/batt_soc_curve_estimate.c",
          source_needle="table = *(const interpolation_table_t *)",
          rationale="Boundary and copy are exact; individual field semantics are not yet recovered."),

    asset("lc3-attack-byte-ranges", 0x884D0, "lc3_attdet_nbytes_ranges", "libLC3/attack detector",
          "range_matrix", "Permitted encoded-byte ranges for enabling attack detection by frame duration and high sample rate.",
          "Rows select 7.5/10 ms; columns select 32/48 kHz; each cell is [minimum, maximum] bytes.",
          "int32", [2, 2, 2], [0x682F0], "nbytes_ranges[dt][sr-32k][min_or_max]",
          "range-bars", {"x": ["7.5 ms / 32k", "7.5 ms / 48k", "10 ms / 32k", "10 ms / 48k"], "y": "encoded frame bytes"},
          upstream_path=LC3+"attdet.c", upstream_needle="const int nbytes_ranges", rationale="Pinned libLC3 source gives exact dimensions and semantics."),
    asset("lc3-bandwidth-drop-thresholds", 0x884F0, "lc3_bwdet_thresholds", "libLC3/bandwidth detector",
          "threshold_vector", "Energy-drop ratios used to confirm NB/WB/SSWB/SWB bandwidth cutoffs.",
          "The selected ratio multiplies energy above a candidate cutoff; lower-band energy must exceed it.",
          "float32", [4], [0x68A10], "threshold[bw0]",
          "axis-bars", {"x": ["NB", "WB", "SSWB", "SWB"], "y": "energy ratio"},
          upstream_path=LC3+"bwdet.c", upstream_needle="Tc[] = 10 ^", rationale="Consumer and pinned formula identify all four values."),
    asset("lc3-tns-subdivision-grid", 0x8853C, "lc3_tns_subdivision_table", "libLC3/TNS",
          "pointer_grid", "Pointers to the spectral subdivision-boundary vectors used for TNS autocorrelation.",
          "Frame duration and bandwidth select one boundary vector; three consecutive subdivisions feed each LPC filter.",
          "uint32", [2, 5], [0x6FFD8], "subdivision_table[duration][bandwidth] -> int boundary vector",
          "pointer-grid", {"x": ["NB", "WB", "SSWB", "SWB", "FB"], "y": ["7.5 ms", "10 ms"], "cell": "target address"},
          units="CPUAPP flash address", source_path="recon/readable_sources/app/library/lc3_tns_analyze.c",
          source_needle="LC3_TNS_SUBDIVISION_TABLE",
          rationale="Exact 2×5 pointer extent is fixed by the recovered consumer's typed indexing."),
    asset("lc3-bandwidth-lookback-lengths", 0x8BBC0, "lc3_bwdet_l_table", "libLC3/bandwidth detector",
          "index_matrix", "Spectral look-back lengths by frame duration and candidate bandwidth.",
          "Controls the number of energy bands compared around each candidate cutoff.",
          "int32", [2, 4], [0x68A10], "l_table[dt][bw0]",
          "heatmap", {"x": ["NB", "WB", "SSWB", "SWB"], "y": ["7.5 ms", "10 ms"]},
          upstream_path=LC3+"bwdet.c", upstream_needle="static const int l_table", rationale="Exact upstream declaration matches recovered typed indexing."),
    asset("lc3-bandwidth-regions", 0x8BBE0, "lc3_bwdet_bws_table", "libLC3/bandwidth detector",
          "region_matrix", "Start/end energy-band regions used for each bandwidth candidate.",
          "For each duration and target bandwidth, the detector sums bands in one or more [start,end) regions.",
          "int8", [2, 4, 4, 4], [0x68A10], "packed compiler bitfield records; consumer reads start/end bytes from each 4-byte cell",
          "region-heatmap", {"x": "candidate bandwidth / region", "y": ["7.5 ms", "10 ms"]},
          upstream_path=LC3+"bwdet.c", upstream_needle="static const struct region bws_table", rationale="Compiler layout is confirmed by recovered byte accesses; unused cells are zero."),
    asset("lc3-energy-single-bin-counts", 0x8BC60, "lc3_energy_n1_table", "libLC3/energy",
          "index_matrix", "Count of initial one-coefficient spectral bands for each duration/sample-rate mode.",
          "The first n1 energy bands are squared directly before the remaining bands use band-limit averaging.",
          "int32", [2, 5], [0x68B68], "n1_table[dt][sr]",
          "heatmap", {"x": ["8k", "16k", "24k", "32k", "48k"], "y": ["7.5 ms", "10 ms"]},
          upstream_path=LC3+"energy.c", upstream_needle="static const int n1_table", rationale="Exact 2x5 table and use are in pinned source."),
    asset("lc3-ltpf-resampler-8k", 0x8BCB8, "lc3_ltpf_resample_8k_12k8_coeffs", "libLC3/LTPF",
          "fir_polyphase", "Q15 polyphase FIR coefficients for resampling 8 kHz PCM to 12.8 kHz.",
          "Two alignment banks, eight phases, twelve taps per phase feed the ARM SIMD resampler.",
          "int16", [2, 8, 12], [0x6AA98], "h[bank][phase][tap], consumed as aligned int16x2 pairs",
          "fir-bank", {"x": "tap 0..11", "series": "bank × phase", "y": "Q15 coefficient"},
          scale="1/32768", units="normalized coefficient", upstream_path=LC3+"ltpf_arm.h",
          upstream_needle="arm_resample_8k_12k8", rationale="Full binary sequence matches pinned static h[2*8*12]."),
    asset("lc3-ltpf-resampler-24k", 0x8BFB8, "lc3_ltpf_resample_24k_12k8_coeffs", "libLC3/LTPF",
          "fir_polyphase", "Q15 polyphase FIR coefficients for resampling 24 kHz PCM to 12.8 kHz.",
          "Two alignment banks, eight phases, thirty-two taps per phase feed the ARM SIMD resampler.",
          "int16", [2, 8, 32], [0x6A700], "h[bank][phase][tap], consumed as aligned int16x2 pairs",
          "fir-bank", {"x": "tap 0..31", "series": "bank × phase", "y": "Q15 coefficient"},
          scale="1/32768", units="normalized coefficient", upstream_path=LC3+"ltpf_arm.h",
          upstream_needle="arm_resample_24k_12k8", rationale="Full binary sequence matches pinned static h[2*8*32]."),
    asset("lc3-sns-dct16", 0x8CE4C, "lc3_sns_dct16_matrix", "libLC3/SNS",
          "transform_matrix", "16×16 DCT matrix used by spectral noise shaping analysis and synthesis.",
          "Forward analysis multiplies columns; inverse reconstruction multiplies rows.",
          "float32", [16, 16], [0x6C778, 0x6BD74], "matrix[j][i] for forward DCT and matrix[i][j] for inverse DCT",
          "matrix-heatmap", {"x": "DCT component", "y": "scale-factor band", "color": "coefficient"},
          upstream_path=LC3+"sns.c", upstream_needle="static const float dct16_m", rationale="256-float split excludes the adjacent word incorrectly merged by recon/data."),
    asset("lc3-spectrum-fast-db-lut", 0x8D350, "lc3_spec_fast_db_lut", "libLC3/spectral quantization",
          "piecewise_linear_lut", "Thirty-two fixed-point intercept/slope pairs for the optimized base-10 log estimator used during gain search.",
          "The top mantissa bits select a segment; the low mantissa fraction interpolates between the pair before an exponent term is added.",
          "uint16", [32, 2], [0x6F4A0], "lut[segment][intercept_or_slope]; segment=(float_bits>>18)&31",
          "paired-lines", {"x": "mantissa segment 0..31", "series": ["intercept", "slope"], "y": "fixed-point correction"},
          raw_symbol="lc3_spec_iq_table", units="internal fixed-point log units",
          source_path="recon/readable_sources/app/library/lc3_spec_analyze.c", source_needle="const uint16_t *t=",
          confidence="high", rationale="Recovered implementation performs explicit uint16 pair interpolation; the older iq_table label is retained only as a back-map alias."),
    asset("lc3-spectrum-bit-costs", 0x8D3D0, "lc3_spectrum_bits", "libLC3/spectral arithmetic coding",
          "cost_matrix", "Fractional bit costs for 64 arithmetic spectrum models and 17 symbols.",
          "Accumulates coding cost in units of 1/2048 bit while selecting the spectral gain and LSB mode.",
          "uint16", [64, 17], [0x6F28C], "bits[model][symbol]",
          "matrix-heatmap", {"x": "symbol 0..16", "y": "model 0..63", "color": "1/2048 bit"},
          scale="1/2048", units="bits", upstream_path=LC3+"tables.c", upstream_needle="const uint16_t lc3_spectrum_bits", rationale="Address gap to spectrum models is exactly 64×17×2 bytes."),
    asset("lc3-spectrum-model-lookup", 0x8ED50, "lc3_spectrum_lookup", "libLC3/spectral arithmetic coding",
          "state_lookup", "Maps rate/half/state/MSB-depth to one of 64 spectrum arithmetic models.",
          "Selects the arithmetic model from high-rate mode, spectrum half, 8-bit coder state, and capped MSB level.",
          "uint8", [2, 2, 256, 4], [0x6F28C, 0x6F9C0], "lookup[high_rate][half][state][min(level,3)]",
          "state-heatmap", {"facet": ["rate", "half", "MSB depth"], "x": "coder state 0..255", "color": "model index"},
          upstream_path=LC3+"tables.c", upstream_needle="const uint8_t lc3_spectrum_lookup", rationale="Public declaration and firmware consumers agree on 4096-byte shape."),
    asset("lc3-tns-coefficient-bit-costs", 0x8FD50, "lc3_tns_coeffs_bits", "libLC3/TNS",
          "cost_matrix", "Fractional bit costs for eight TNS coefficient positions and seventeen quantized reflection values.",
          "Adds per-coefficient costs while estimating TNS side-information size.",
          "uint16", [8, 17], [0x709D8], "bits[position][quantized_coefficient+8]",
          "matrix-heatmap", {"x": "quantized coefficient -8..8", "y": "coefficient position 0..7", "color": "1/2048 bit"},
          scale="1/2048", units="bits", upstream_path=LC3+"tables.c", upstream_needle="const uint16_t lc3_tns_coeffs_bits", rationale="Exact 8×17 extent ends at the following model table."),
    asset("lc3-tns-coefficient-models", 0x8FE60, "lc3_tns_coeffs_models", "libLC3/TNS",
          "arithmetic_models", "Eight 17-symbol cumulative-frequency models for TNS reflection coefficients.",
          "The coefficient position selects a model; each symbol stores cumulative start and frequency over a 1024-point total.",
          "uint16", [8, 17, 2], [0x70B38], "models[position].symbol[value+8].{cumulative,frequency}",
          "distribution-small-multiples", {"x": "coefficient symbol -8..8", "series": "position 0..7", "y": "frequency / 1024"},
          scale="1/1024", units="probability", upstream_path=LC3+"tables.c", upstream_needle="const struct lc3_ac_model lc3_tns_coeffs_models", rationale="Eight 68-byte rows align with all row symbols in the recovered symbol map."),
    asset("lc3-tns-order-bit-costs", 0x90080, "lc3_tns_order_bits", "libLC3/TNS",
          "cost_matrix", "Fractional bit costs for TNS filter orders 1..8 in one- and two-filter modes.",
          "Selected by filter-count mode and encoded order during TNS side-bit estimation.",
          "uint16", [2, 8], [0x709D8], "order_bits[nfilters-1][order-1]",
          "grouped-bars", {"x": "filter order 1..8", "series": ["one filter", "two filters"], "y": "1/2048 bit"},
          scale="1/2048", units="bits", upstream_path=LC3+"tables.c", upstream_needle="const uint16_t lc3_tns_order_bits", rationale="Pinned declaration fixes exact 2×8 shape."),
    asset("lc3-tns-reflection-levels", 0x98540, "lc3_tns_rc_levels", "libLC3/TNS",
          "quantization_levels", "Nine non-negative reconstruction levels sin(pi*i/17) for quantized TNS reflection coefficients.",
          "Absolute quantizer indices select a level; the encoded sign is restored afterward.",
          "float32", [9], [0x6FFD8], "level[abs(quantized_rc)], then sign restore",
          "line", {"x": "absolute quantizer index 0..8", "y": "reflection coefficient"},
          source_path="recon/readable_sources/app/library/lc3_tns_analyze.c", source_needle="LC3_TNS_RC_LEVELS",
          upstream_path=LC3+"tns.c", upstream_needle="static float q_inv", rationale="Firmware floats match the pinned sin(pi*i/17) table exactly."),
    asset("lc3-tns-reflection-thresholds", 0x98564, "lc3_tns_rc_thresholds", "libLC3/TNS",
          "quantization_thresholds", "Eight decision thresholds sin(pi*(i+0.5)/17) for TNS reflection-coefficient quantization.",
          "Magnitude is compared against the ordered thresholds to select an integer code from zero through eight.",
          "float32", [8], [0x6FFD8], "threshold progression during reflection-coefficient magnitude quantization",
          "line", {"x": "decision boundary 0..7", "y": "reflection coefficient magnitude"},
          source_path="recon/readable_sources/app/library/lc3_tns_analyze.c", source_needle="LC3_TNS_RC_THRESHOLDS",
          upstream_path=LC3+"tns.c", upstream_needle="static float q_thr", rationale="Firmware floats match the pinned sin(pi*(i+0.5)/17) table exactly."),
    asset("lc3-sns-vq-high-codebook", 0x90450, "lc3_sns_hfcb", "libLC3/SNS",
          "vector_codebook", "32 eight-dimensional high-frequency SNS codebook vectors.",
          "Index selection supplies the upper eight scale-factor coefficients during SNS vector quantization.",
          "float32", [32, 8], [0x6C778, 0x6BD74], "hfcb[codebook_index][dimension]",
          "codebook-heatmap", {"x": "dimension 0..7", "y": "vector 0..31", "color": "coefficient"},
          upstream_path=LC3+"tables.c", upstream_needle="const float lc3_sns_hfcb", rationale="Exact 32×8 object ends at lc3_sns_lfcb."),
    asset("lc3-sns-vq-low-codebook", 0x90850, "lc3_sns_lfcb", "libLC3/SNS",
          "vector_codebook", "32 eight-dimensional low-frequency SNS codebook vectors.",
          "Index selection supplies the lower eight scale-factor coefficients during SNS vector quantization.",
          "float32", [32, 8], [0x6C778, 0x6BD74], "lfcb[codebook_index][dimension]",
          "codebook-heatmap", {"x": "dimension 0..7", "y": "vector 0..31", "color": "coefficient"},
          upstream_path=LC3+"tables.c", upstream_needle="const float lc3_sns_lfcb", rationale="Exact 32×8 object ends at lc3_band_lim."),
    asset("lc3-band-limits", 0x90C50, "lc3_band_lim", "libLC3/filter bank",
          "boundary_tensor", "Spectral-bin boundaries for 64 LC3 bands across two frame durations and five sample rates.",
          "Energy and SNS stages convert coefficient bins into LC3 bands using consecutive [limit[i],limit[i+1]) spans.",
          "int32", [2, 5, 65], [0x68B68, 0x6C778, 0x6BFC8], "band_lim[duration][sample_rate][boundary]",
          "multi-line", {"x": "band boundary 0..64", "series": "duration × sample rate", "y": "spectral-bin index"},
          units="spectral bin", upstream_path=LC3+"tables.c", upstream_needle="const int lc3_band_lim", rationale="Public declaration fixes complete 2×5×65 shape."),
]


def read_blob(address: int, size: int) -> bytes:
    data = FIRMWARE.read_bytes()
    offset = address - LINK_BASE + FILE_BASE
    return data[offset:offset + size]


def unpack_values(blob: bytes, element_type: str):
    formats = {"uint8": "B", "int8": "b", "uint16": "H", "int16": "h",
               "uint32": "I", "int32": "i", "float32": "f"}
    fmt = formats[element_type]
    width = struct.calcsize(fmt)
    values = list(struct.unpack("<" + fmt * (len(blob) // width), blob))
    if element_type == "float32":
        return [round(v, 9) if math.isfinite(v) else str(v) for v in values]
    return values


def line_evidence(relative: str | None, needle: str | None, kind: str):
    if not relative:
        return None
    path = Path(relative)
    absolute = path if path.is_absolute() else ROOT / path
    if not absolute.exists():
        return {"kind": kind, "path": str(path), "line": None, "detail": "referenced evidence path is unavailable"}
    lines = absolute.read_text(errors="replace").splitlines()
    line = next((i for i, text in enumerate(lines, 1) if needle and needle in text), None)
    return {"kind": kind, "path": str(path), "line": line,
            "detail": (f"{needle!r} identifies the typed declaration/access" if line is not None
                       else f"evidence path exists but {needle!r} was not found")}


def main():
    name_map = json.loads((ROOT / "recon/catalogs/function_names_app.json").read_text())["by_address"]
    manifest = json.loads((ROOT / "recon/readable_sources/app/manifest.json").read_text())
    source_by_addr = {int(row["address"], 16): row for row in manifest["sources"]}
    records = []

    for spec in ASSETS:
        address, size = spec["address"], spec.pop("size")
        blob = read_blob(address, size)
        values = unpack_values(blob, spec["storage"]["element_type"])
        limit = spec.pop("sample_limit")
        if len(values) <= limit:
            samples = values
            sample_indices = list(range(len(values)))
        else:
            step = max(1, len(values) // limit)
            sample_indices = list(range(0, len(values), step))[:limit]
            samples = [values[i] for i in sample_indices]

        consumers = []
        structs = []
        for function_address in spec.pop("consumer_addresses"):
            key = f"0x{function_address:08x}"
            named = name_map.get(key, {})
            src = source_by_addr.get(function_address, {})
            consumers.append({
                "address": key,
                "raw_name": named.get("raw_name", f"FUN_{function_address:08x}"),
                "name": named.get("name", src.get("public_name", f"firmware_function_{function_address:08x}")),
                "source": src.get("output"),
            })
            for binding in src.get("structure_bindings", []):
                candidate = {"cid": binding.get("cid"), "type": binding.get("type"), "base": binding.get("base")}
                if candidate not in structs:
                    structs.append(candidate)

        raw_symbol = spec["raw_symbol"]
        confidence_scores = {"high": 0.98, "medium": 0.75, "low": 0.45}
        spec["confidence"]["score"] = confidence_scores[spec["confidence"]["level"]]
        configured_constants = spec.pop("related_constants")
        if spec["subsystem"].startswith("libLC3/"):
            configured_constants.append({"name": "LC3_NUM_DT", "value": 2,
                                         "labels": ["7.5 ms", "10 ms"], "kind": "codec-mode"})
        if spec["subsystem"] == "G1/display UI":
            configured_constants.extend([
                {"name": "refresh_pass_count", "value": 9, "kind": "behavior"},
                {"name": "scroll_row_block", "value": 27, "units": "rows", "kind": "behavior"},
            ])
        elif spec["id"] == "imu-motion-axis-thresholds":
            configured_constants.append({"name": "consecutive_motion_count", "value": 5, "kind": "behavior"})
        elif spec["id"] == "battery-model-bootstrap-descriptor":
            configured_constants.extend([
                {"name": "descriptor_copy_size", "value": 64, "units": "bytes", "kind": "behavior"},
                {"name": "curve_payload_copy_size", "value": 5632, "units": "bytes", "kind": "behavior"},
                {"name": "workspace_clear_size", "value": 6008, "units": "bytes", "kind": "behavior"},
            ])
        configured_constants.extend([
            {"name": "element_count", "value": len(values), "kind": "layout"},
            {"name": "byte_size", "value": size, "kind": "layout"},
        ])
        spec.update({
            "address": f"0x{address:08x}",
            "address_end": f"0x{address + size:08x}",
            "size": size,
            "back_map": {"raw_symbol": raw_symbol, "address": f"0x{address:08x}"},
            "access": {"producers": [], "producer_note": "immutable CPUAPP rodata; no runtime producer function",
                       "consumers": consumers, "pattern": spec.pop("access_pattern")},
            "related": {"constants": configured_constants, "structs": structs, "assets": []},
            "decoded": {"values": values},
        })
        spec["visualization"].update({
            "sample_indices": sample_indices,
            "samples": samples,
            "sampled": len(values) > limit,
            "full_value_count": len(values),
        })
        if spec["asset_type"] == "codepoint_set":
            spec["visualization"]["decoded_labels"] = [chr(v) for v in values]
            spec["decoded"]["labels"] = [chr(v) for v in values]
        if spec["storage"]["element_type"] in ("uint32", "int32"):
            spec["decoded"]["hex_values"] = [f"0x{(v & 0xffffffff):08x}" for v in values]
        if spec["id"] == "battery-model-bootstrap-descriptor":
            floats = unpack_values(blob, "float32")
            spec["visualization"]["float32_interpretation"] = floats
            spec["visualization"]["hex_words"] = [f"0x{v:08x}" for v in values]

        evidence = [{"kind": "firmware-bytes", "path": "app_update.bin",
                     "address": f"0x{address:08x}", "size": size,
                     "detail": "decoded directly from the shipped MCUBoot payload using the CPUAPP VA mapping"}]
        ev = line_evidence(spec.pop("source_path"), spec.pop("source_needle"), "recovered-consumer")
        if ev:
            evidence.append(ev)
        ev = line_evidence(spec.pop("upstream_path"), spec.pop("upstream_needle"), "pinned-upstream")
        if ev:
            evidence.append(ev)
        spec["evidence"] = evidence
        records.append(spec)

    subsystem_counts = {}
    viewer_counts = {}
    for row in records:
        subsystem_counts[row["subsystem"]] = subsystem_counts.get(row["subsystem"], 0) + 1
        viewer = row["visualization"]["viewer"]
        viewer_counts[viewer] = viewer_counts.get(viewer, 0) + 1
    report = {
        "schema": 1,
        "core": "CPUAPP",
        "generated_by": "tools/collect_numeric_assets.py",
        "scope": "Grounded immutable numeric assets with a meaningful custom viewer; generic pointer pools and untyped adjacent bytes are intentionally excluded.",
        "summary": {
            "assets": len(records),
            "g1_original": sum(r["subsystem"].startswith("G1/") for r in records),
            "stock_library": sum(r["subsystem"].startswith("libLC3/") for r in records),
            "subsystems": subsystem_counts,
            "viewer_types": viewer_counts,
            "all_samples_from_shipped_binary": True,
        },
        "assets": records,
    }
    output = ROOT / "recon/viewer_sweep/numeric_tables_report.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    print(f"wrote {len(records)} assets to {output}")


if __name__ == "__main__":
    main()
