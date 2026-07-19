#!/usr/bin/env python3
"""Collect G1 CPUAPP visual assets and evidence for the symbol viewer.

This is intentionally a presentation-only extractor.  It reads the shipped
image plus the readable source tree and does not alter parity sources.
"""

from __future__ import annotations

import gzip
import hashlib
import json
import re
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
IMAGE = ROOT / "app_update.bin"
SOURCE_DIR = ROOT / "recon/readable_sources/app/g1"
RESOURCE_SOURCE = SOURCE_DIR / "resource_manger_get.c"
MANIFEST = ROOT / "recon/readable_sources/app/manifest.json"
REFGRAPH = ROOT / "recon/catalogs/refgraph_app.json.gz"
OUTPUT = ROOT / "recon/viewer_sweep/visual_assets_report.json"
LINK_BASE = 0xC200
FILE_HEADER = 512


def hx(value: int) -> str:
    return f"0x{value:08x}"


def read_va(blob: bytes, address: int, size: int) -> bytes:
    offset = address - LINK_BASE + FILE_HEADER
    if offset < 0 or offset + size > len(blob):
        raise ValueError(f"range {hx(address)}+{size:#x} is outside app_update.bin")
    return blob[offset : offset + size]


def data_range(blob: bytes, start: int, size: int, raw_symbol: str, name: str) -> dict:
    payload = read_va(blob, start, size)
    return {
        "address_start": hx(start),
        "address_end_exclusive": hx(start + size),
        "size_bytes": size,
        "raw_symbol": raw_symbol,
        "public_name": name,
        "storage": "CPUAPP internal flash",
        "sha256": hashlib.sha256(payload).hexdigest(),
    }


def main() -> None:
    blob = IMAGE.read_bytes()
    source = RESOURCE_SOURCE.read_text()
    manifest = json.loads(MANIFEST.read_text())
    refgraph = json.load(gzip.open(REFGRAPH, "rt"))["functions"]
    functions = {row["public_name"]: row for row in manifest["sources"]}

    def fn(name: str) -> dict:
        row = functions[name]
        return {
            "public_name": row["public_name"],
            "raw_symbol": row["raw_symbol"],
            "address": row["address"],
            "source": row["output"],
        }

    def layouts(names: list[str]) -> list[dict]:
        out, seen = [], set()
        for name in names:
            row = functions.get(name)
            if not row:
                continue
            for binding in row.get("structure_bindings", []):
                key = (binding["cid"], binding.get("base"))
                if key not in seen:
                    seen.add(key)
                    out.append({**binding, "via_function": name})
        return out

    macro_targets = {
        match.group(1): (match.group(2), int(match.group(3), 16))
        for match in re.finditer(
            r"#define\s+(firmware_data_[0-9a-f]+)\s+"
            r"\(\(\(unsigned long\)&(rodata_([0-9a-f]+))",
            source,
        )
    }

    # Resolve direct constant bitmap calls and source-local symbolic defines.
    usage_by_id: dict[int, list[dict]] = {}
    for path in sorted(SOURCE_DIR.glob("*.c")):
        text = path.read_text(errors="replace")
        local_defines = {
            name: int(value, 0)
            for name, value in re.findall(
                r"^\s*#define\s+([A-Za-z_]\w*)\s+(0x[0-9a-fA-F]+|\d+)[uUlL]*\s*$",
                text,
                re.MULTILINE,
            )
        }
        public = path.stem
        for match in re.finditer(r"gui_(?:bmp_bitmap_draw|4bit_bitmap_override)\s*\(\s*([A-Za-z_]\w*|0x[0-9a-fA-F]+|\d+)", text):
            token = match.group(1)
            if token in {"unsigned", "param_1"}:
                continue
            try:
                asset_id = int(token, 0)
            except ValueError:
                if token not in local_defines:
                    continue
                asset_id = local_defines[token]
            line = text.count("\n", 0, match.start()) + 1
            usage_by_id.setdefault(asset_id, []).append(
                {
                    "function": fn(public) if public in functions else {"public_name": public},
                    "source_line": line,
                    "expression": text.splitlines()[line - 1].strip(),
                    "semantic_label": token if token != hex(asset_id) else None,
                    "evidence_kind": "constant call-site",
                }
            )

    static_visuals = {
        0x16: "A compact list/menu marker with three horizontal entries and a left rail.",
        0x17: "A tiny outlined square used as a movable progress marker.",
        0x18: "A three-line text/list symbol.",
        0x19: "A pause symbol inside a small square.",
        0x1A: "A pause symbol with a stronger double bar.",
        0x1B: "A small filled center dot.",
        0x1C: "An outlined center dot.",
        0x1D: "A checked selection box.",
        0x1E: "A boxed numeral 1.",
        0x1F: "A boxed numeral 2.",
        0x20: "A boxed numeral 3.",
        0x21: "A boxed numeral 4.",
        0x22: "A dotted circular loading/status ring.",
        0x23: "A question-mark help/status symbol.",
        0x24: "A home/house outline.",
        0x25: "A home/house outline with a filled roof accent.",
        0x26: "A home symbol with a horizontal base.",
        0x27: "A home symbol with a dotted lower detail.",
        0x28: "A building/storefront-like home symbol.",
        0x29: "A building/home symbol with a bright central doorway.",
        0x2A: "A wireless/radio signal mark.",
        0x2B: "A lightning/charging bolt.",
        0x2C: "A sun/brightness glyph.",
        0x2D: "A layered up-chevron or stacked-page marker.",
        0x2E: "A layered up-chevron with additional bars.",
        0x2F: "A small device/card status symbol.",
        0x30: "A right-aligned horizontal status-bar icon.",
        0x31: "A descending horizontal status-bar icon.",
        0x32: "An envelope/mail glyph.",
        0x33: "A small notification or bell-like glyph.",
        0x36: "A linked-chain/connection symbol.",
        0x37: "A linked-chain/connection symbol with a small badge.",
        0x38: "A message/speech-bubble glyph.",
        0x39: "A calendar glyph.",
        0x3A: "A folder/document glyph.",
        0x3B: "A document/message card glyph.",
        0x3C: "A notification bell glyph.",
        0x3E: "A Bluetooth glyph.",
        0x3F: "A crossed-out/disabled document glyph.",
        0x41: "A wide digital clock/status tile.",
        0x42: "A small device/phone outline.",
        0x43: "An ascending signal-strength graph.",
        0x44: "An upward chevron.",
        0x45: "A downward chevron.",
        0x46: "A horizontal minus/divider.",
        0x47: "A stacked document/news glyph.",
        0x48: "A crescent moon/night-mode glyph.",
        0x49: "A boxed exclamation warning glyph.",
        0x4A: "A wide, faint horizontal rule or separator.",
        0x4B: "A full-width horizontal rule or separator.",
        0x4C: "A wide, faint horizontal rule or separator.",
        0x4D: "A full-width horizontal rule or separator.",
        0x4E: "A one-pixel vertical divider.",
        0x4F: "A one-pixel vertical divider.",
        0x50: "A tiny square point marker.",
        0x51: "A tiny square point marker.",
        0x52: "A tiny square point marker.",
        0x53: "A tiny square point marker.",
        0x54: "A 14×13 navigation-position marker used on panoramic maps.",
        0x7A: "A short single-pixel horizontal line segment.",
        0x7B: "A short single-pixel horizontal line segment.",
        0x7C: "A long single-pixel horizontal calibration line.",
    }

    nav_descriptions = {
        0x56: "a straight-ahead arrow", 0x57: "a slight-left/veer arrow",
        0x58: "a slight-right/veer arrow", 0x59: "a left-turn corner",
        0x5A: "a right-turn corner", 0x5B: "a left fork", 0x5C: "a right fork",
        0x5D: "a hard-left bend", 0x5E: "a hard-right bend", 0x5F: "a U-turn",
        0x60: "an alternate U-turn", 0x61: "a roundabout/loop exit",
        0x62: "a roundabout/loop exit", 0x63: "a merge/fork maneuver",
        0x64: "a merge/fork maneuver", 0x65: "a roundabout turn",
        0x66: "a roundabout turn", 0x67: "a curved right turn",
        0x68: "a curved left turn", 0x69: "a roundabout/loop maneuver",
        0x6A: "a roundabout/loop maneuver", 0x6B: "a wide right arc",
        0x6C: "a wide left arc", 0x6D: "a tight hooked right turn",
        0x6E: "a tight hooked left turn", 0x6F: "a U-turn with exit marker",
        0x70: "a U-turn with exit marker", 0x71: "a diagonal right branch",
        0x72: "a diagonal left branch", 0x73: "a right-side merge",
        0x74: "a left-side merge", 0x75: "a sharp diagonal right turn",
        0x76: "a sharp diagonal left turn", 0x77: "a split/Y junction",
        0x78: "an alternate split/Y junction",
    }
    for asset_id, description in nav_descriptions.items():
        static_visuals[asset_id] = f"A 50×50 navigation maneuver pictogram showing {description}."

    assets: list[dict] = []
    section = source[source.index("  case 4:") : source.index("  case 5:", source.index("  case 4:"))]
    cases = list(re.finditer(r"\n\s*case\s+(0x[0-9a-f]+|\d+):", section))
    for index, match in enumerate(cases):
        block = section[match.end() : cases[index + 1].start() if index + 1 < len(cases) else len(section)]
        asset_id = int(match.group(1), 0)
        pointer_macro = re.search(r"\*param_5\s*=\s*(firmware_data_[0-9a-f]+)", block).group(1)
        width = int(re.search(r"\*param_3\s*=\s*(0x[0-9a-f]+|\d+)", block).group(1), 0)
        height = int(re.search(r"\*param_4\s*=\s*(0x[0-9a-f]+|\d+)", block).group(1), 0)
        raw_symbol, address = macro_targets[pointer_macro]
        size = ((width + 1) // 2) * height
        consumers = list(usage_by_id.get(asset_id, []))
        consumer_names = [item["function"]["public_name"] for item in consumers]
        consumers.append({
            "function": fn("gui_bmp_bitmap_draw"),
            "evidence_kind": "generic static-bitmap draw path",
            "expression": "resource_manger_get(4, bitmap_id, ...) then fb_blit_rows_copy(...)"
        })
        consumer_names.append("gui_bmp_bitmap_draw")
        if 0x56 <= asset_id <= 0x78:
            consumers.append({
                "function": fn("navigation_direction_img_display"),
                "source_line": 32,
                "expression": "gui_bmp_bitmap_draw(param_1 + 0x55, ...)",
                "semantic_label": f"navigation direction code {asset_id - 0x55}",
                "evidence_kind": "bounded computed asset ID (1..35)",
            })
            consumer_names.append("navigation_direction_img_display")
        assets.append({
            "id": f"static_bitmap_{asset_id:02x}",
            "asset_id": asset_id,
            "title": f"Static UI bitmap 0x{asset_id:02X}",
            "kind": "static_bitmap",
            "subsystem": "navigation" if 0x56 <= asset_id <= 0x78 else "G1 UI",
            "address_ranges": [data_range(blob, address, size, raw_symbol, f"ui_bitmap_{asset_id:02x}")],
            "encoding": {
                "format": "packed 4-bit grayscale",
                "bits_per_pixel": 4,
                "width_pixels": width,
                "height_pixels": height,
                "row_stride_bytes": (width + 1) // 2,
                "pixel_order": "high nibble then low nibble, left-to-right",
                "endianness": "byte-addressed; no word-endian transform",
            },
            "behavior": "Resolved by resource type 4 and copied or OR-composited into the active framebuffer.",
            "visual_description": static_visuals.get(asset_id, "A small monochrome UI pictogram or layout primitive."),
            "plain_language": "On the glasses this appears as " + (
                static_visuals.get(asset_id, "A small status or control icon.")[:1].lower()
                + static_visuals.get(asset_id, "A small status or control icon.")[1:]
            ),
            "producers": [fn("resource_manger_get")],
            "consumers": consumers,
            "reference_evidence": [{
                "kind": "Ghidra-grounded source data reference",
                "function": fn("resource_manger_get"),
                "target": hx(address),
                "source_case": f"resource type 4, ID 0x{asset_id:02x}",
            }],
            "related_constants": [
                {"name": "resource_type", "value": 4, "meaning": "static bitmap"},
                {"name": "framebuffer_stride", "value": 320, "meaning": "640 pixels / 2 pixels per byte"},
            ],
            "related_structures": layouts(["resource_manger_get", *consumer_names]),
            "related_strings": [],
            "renderer": {
                "viewer": "grayscale bitmap",
                "strategy": "Read row_stride*height bytes; emit the high and low nibbles as adjacent pixels; scale nibble 0..15 to alpha or luminance 0..255.",
                "safe_bounds": "Use the exact address range; never scan to the next symbol.",
            },
            "confidence": "high",
            "caveats": ["The icon's semantic name is inferred from its decoded pixels and call sites; the firmware stores numeric IDs only."],
        })

    # Twenty 24x24 icons use a byte->uint32 LUT expansion.  ID 4 has a special
    # already-expanded copy at 0x88697; the other slices are 72-byte 2-bpp data.
    builtin_names = {
        0: "empty battery", 1: "one-bar battery", 2: "two-bar battery",
        3: "three-bar/full battery", 4: "notification bell", 5: "Bluetooth",
        6: "calendar", 7: "clock", 8: "hourglass/status", 9: "hourglass/activity",
        10: "mail envelope", 11: "message card", 12: "navigation/attention arrow",
        13: "music note", 14: "person/activity", 15: "vibration",
        16: "brightness/display", 17: "note/list", 18: "activity/person",
        19: "assistant face/chat",
    }
    for asset_id in range(20):
        if asset_id == 4:
            address, size, raw = 0x88697, 0x120, "rodata_88697"
            compressed = False
        else:
            address, size, raw = 0xE123A + asset_id * 72, 72, "rodata_e123a"
            compressed = True
        consumers = list(usage_by_id.get(asset_id, []))
        consumers.append({
            "function": fn("gui_bmp_bitmap_draw"),
            "evidence_kind": "fallback built-in-icon draw path",
            "expression": "load_icon_bitmap_expanded(icon_id, 0x120) then 24x24 framebuffer blit",
        })
        assets.append({
            "id": f"builtin_icon_{asset_id:02x}",
            "asset_id": asset_id,
            "title": f"Built-in 24×24 {builtin_names[asset_id]} icon",
            "kind": "compressed_icon" if compressed else "static_bitmap",
            "subsystem": "system status / quick UI",
            "address_ranges": [data_range(blob, address, size, raw, f"builtin_icon_{asset_id:02x}")],
            "encoding": {
                "format": "2-bit packed with LUT expansion to packed 4-bit grayscale" if compressed else "packed 4-bit grayscale",
                "bits_per_pixel_stored": 2 if compressed else 4,
                "bits_per_pixel_rendered": 4,
                "width_pixels": 24,
                "height_pixels": 24,
                "stored_size_bytes": size,
                "rendered_stride_bytes": 12,
                "pixel_order": "firmware LUT at 0x000d753a defines the exact byte expansion" if compressed else "high nibble then low nibble",
                "endianness": "LUT entries are little-endian uint32 words" if compressed else "byte-addressed",
            },
            "behavior": "load_icon_bitmap_expanded expands this icon into g_icon_bitmap_buf before a 24×24 framebuffer blit.",
            "visual_description": f"A crisp pixel-art {builtin_names[asset_id]} symbol.",
            "plain_language": f"On the glasses this is the small {builtin_names[asset_id]} status icon.",
            "producers": [fn("load_icon_bitmap_expanded"), fn("expand_bytes_via_lut32")],
            "consumers": consumers,
            "reference_evidence": [{
                "kind": "address arithmetic in proven source",
                "function": fn("load_icon_bitmap_expanded"),
                "target": hx(address),
                "expression": "rodata_e123a + icon_id * 72, expanded 4:1" if compressed else "special ID 4 memcpy of 0x120 bytes",
            }],
            "related_constants": [
                {"name": "compressed_icon_bytes", "value": 72},
                {"name": "expanded_icon_bytes", "value": 288},
                {"name": "expansion_lut", "value": "0x000d753a", "size_bytes": 1024},
                {"name": "destination", "value": "g_icon_bitmap_buf", "address": "0x2001d142"},
            ],
            "related_structures": layouts(["load_icon_bitmap_expanded", *[u["function"]["public_name"] for u in consumers]]),
            "related_strings": [],
            "renderer": {
                "viewer": "grayscale icon",
                "strategy": "For each stored byte b, copy the four little-endian bytes of LUT[b] from 0x000d753a; then decode each output byte as two 4-bit pixels.",
                "safe_bounds": "Use exactly 72 source bytes (or 288 bytes for special ID 4) and a fixed 256-entry LUT.",
            },
            "confidence": "high",
            "caveats": ["IDs 20 and 21 fall outside the confirmed 20-slice atlas and must not be rendered by reading past 0x000e17da."],
        })

    dynamic_meta = {
        1: (0xD43BF, 20, 26, 45, "a symmetric expanding/contracting three-block pulse"),
        2: (0xD328F, 20, 20, 22, "an upward arrow that grows and collapses"),
        3: (0xD215F, 20, 20, 22, "a downward arrow that grows and collapses"),
        4: (0xD15A7, 20, 20, 15, "a focus reticle morphing through square, circle and plus forms"),
        5: (0xD0E9F, 20, 20, 9, "a document/message tile being drawn into view"),
        6: (0xD06CF, 20, 20, 10, "a crescent-and-dot activity sweep"),
        7: (0xCFF13, 22, 20, 9, "a crescent closing into a circular activity ring"),
        8: (0xCE483, 20, 20, 34, "a dotted path drawing a right-angle turn and dispersing"),
        9: (0xCD5AB, 20, 20, 19, "a diagonal stepped wipe moving across the tile"),
        10: (0xCC863, 20, 20, 17, "horizontal scan lines with a moving center marker"),
        11: (0xCB7FB, 20, 20, 21, "a square pulse expanding into rings and returning"),
        12: (0xCA153, 20, 20, 29, "an alternating square, star and focus-bracket pulse"),
    }
    dynamic_usage: dict[int, list[dict]] = {}
    for path in sorted(SOURCE_DIR.glob("*.c")):
        text = path.read_text(errors="replace")
        for match in re.finditer(r"gui_bmp_dynamic_bitmap_draw\s*\(\s*(0x[0-9a-fA-F]+|\d+)[uUlL]*", text):
            asset_id = int(match.group(1), 0)
            if asset_id not in dynamic_meta:
                continue
            line = text.count("\n", 0, match.start()) + 1
            dynamic_usage.setdefault(asset_id, []).append({
                "function": fn(path.stem), "source_line": line,
                "expression": text.splitlines()[line - 1].strip(),
                "evidence_kind": "constant animation call-site",
            })
    for asset_id, (address, width, height, frames, visual) in dynamic_meta.items():
        stride = width // 2
        frame_size = stride * height
        size = frame_size * frames
        consumers = dynamic_usage.get(asset_id, [])
        # Computed IDs are selected by status/onboarding state in these callers.
        for computed in ("draw_status_icon_by_state", "render_onboarding_screen", "ui_QuickNote_task"):
            if computed in functions:
                consumers.append({"function": fn(computed), "evidence_kind": "computed animation ID/state dispatch"})
        assets.append({
            "id": f"dynamic_bitmap_{asset_id:02x}", "asset_id": asset_id,
            "title": f"UI animation {asset_id}", "kind": "frame_animation",
            "subsystem": "onboarding / activity / status UI",
            "address_ranges": [data_range(blob, address, size, f"rodata_{address:x}", f"ui_animation_{asset_id:02x}")],
            "encoding": {
                "format": "contiguous packed 4-bit grayscale frames",
                "bits_per_pixel": 4, "width_pixels": width, "height_pixels": height,
                "row_stride_bytes": stride, "frame_stride_bytes": frame_size,
                "frame_count": frames, "pixel_order": "high nibble then low nibble",
                "frame_order": "ascending address",
            },
            "behavior": "gui_bmp_dynamic_bitmap_draw advances a shared frame index, wraps at frame_count, and optionally repeats for a requested cycle count.",
            "visual_description": visual.capitalize() + ".",
            "plain_language": f"On the glasses the user sees {visual}.",
            "producers": [fn("resource_manger_get")], "consumers": consumers,
            "reference_evidence": [{
                "kind": "resource type 5 dispatch table",
                "function": fn("resource_manger_get"), "target": hx(address),
                "source_case": f"animation ID {asset_id}; {frames} frames",
            }],
            "related_constants": [
                {"name": "frame_count", "value": frames},
                {"name": "frame_stride_bytes", "value": frame_size},
                {"name": "shared_frame_index", "address": "0x2000f700"},
                {"name": "shared_cycle_count", "address": "0x2000f6fe"},
            ],
            "related_structures": layouts(["gui_bmp_dynamic_bitmap_draw", *[u["function"]["public_name"] for u in consumers]]),
            "related_strings": [{"address": "0x000aade4", "text": "gui_bmp_dynamic_bitmap_draw"}],
            "renderer": {
                "viewer": "frame scrubber / looping animation",
                "strategy": "Slice frame_count chunks of frame_stride bytes, decode packed nibbles, and expose play/pause, frame stepping and speed controls.",
                "safe_bounds": "Do not infer termination from blank frames; use the dispatch-table frame count.",
            },
            "confidence": "high", "caveats": ["Playback timing is controlled by the calling UI task, not stored in the asset."],
        })

    font_specs = [
        ("font_style3", 0x8AC2C, 0x98E3C, 0xE17DA, 26, "font style 3"),
        ("clock_digits_small", 0x8AC30, 0x98FBC, 0xE4408, 32, "small clock digits and colon"),
        ("clock_digits_large", 0x8AC34, 0x98FE8, 0xE5248, 39, "large clock digits and colon"),
        ("default_font", 0x8AC28, 0x9890C, 0xE5F62, 26, "default multilingual UI font"),
    ]
    font_functions = {
        "font_style3": "get_font_style3_glyph_offset",
        "clock_digits_small": "get_clock_digit_glyph_offset_small",
        "clock_digits_large": "get_clock_digit_glyph_offset_large",
        "default_font": "get_default_font_glyph_offset",
    }
    for key, count_address, table_address, payload_address, height, description in font_specs:
        count = struct.unpack("<I", read_va(blob, count_address, 4))[0]
        table = read_va(blob, table_address, count * 4)
        entries, cursor = [], 0
        for index in range(count):
            codepoint, half_width, reserved = struct.unpack_from("<HBB", table, index * 4)
            size = half_width * height
            entries.append({
                "index": index, "codepoint": f"U+{codepoint:04X}",
                "character": chr(codepoint) if codepoint >= 0x20 and not 0xD800 <= codepoint <= 0xDFFF else None,
                "width_pixels": half_width * 2, "height_pixels": height,
                "row_stride_bytes": half_width, "payload_offset": cursor,
                "address_start": hx(payload_address + cursor), "size_bytes": size,
                "reserved_byte": reserved,
            })
            cursor += size
        resolver = font_functions[key]
        assets.append({
            "id": key, "title": description.title(), "kind": "font_bank",
            "subsystem": "text rendering / clock UI",
            "address_ranges": [
                data_range(blob, count_address, 4, f"rodata_{count_address:x}", f"{key}_count"),
                data_range(blob, table_address, count * 4, f"rodata_{table_address:x}", f"{key}_glyph_index"),
                data_range(blob, payload_address, cursor, f"rodata_{payload_address:x}", f"{key}_pixels"),
            ],
            "encoding": {
                "format": "variable-width packed 4-bit grayscale glyphs",
                "bits_per_pixel": 4, "height_pixels": height,
                "index_entry": "little-endian uint16 codepoint, uint8 half_width/row_stride, uint8 reserved",
                "glyph_offset_rule": "cumulative sum of half_width * height",
                "pixel_order": "high nibble then low nibble",
                "glyph_count": count, "payload_size_bytes": cursor,
            },
            "entries": entries,
            "behavior": f"{resolver} resolves Unicode/codepoint metadata; resource_manger_get returns the glyph pixels to GUI text routines.",
            "visual_description": f"A grid of {count} crisp variable-width {description} glyphs.",
            "plain_language": f"These are the actual letters, symbols and digits that the glasses draw for the {description}.",
            "producers": [fn(resolver), fn("resource_manger_get")],
            "consumers": [fn(name) for name in ("gui_utf_draw", "gui_string_draw", "gui_clock_draw") if name in functions],
            "reference_evidence": [{
                "kind": "proven cumulative-offset resolver",
                "function": fn(resolver), "target": hx(payload_address),
                "expression": f"sum(width/2 * {height}) over preceding index entries",
            }],
            "related_constants": [
                {"name": "glyph_count", "address": hx(count_address), "value": count},
                {"name": "glyph_height", "value": height},
            ],
            "related_structures": layouts([resolver, "resource_manger_get", "gui_utf_draw", "gui_clock_draw"]),
            "related_strings": [],
            "renderer": {
                "viewer": "searchable glyph grid and glyph inspector",
                "strategy": "Parse fixed 4-byte index entries, compute cumulative offsets, then decode each row_stride*height glyph as packed 4-bit pixels.",
                "safe_bounds": "The computed payload length exactly reaches the next font payload (or 0x000ef01c for the default bank).",
            },
            "confidence": "high", "caveats": ["The stored width byte is half the logical pixel width because two pixels share each byte."],
        })

    mask_start, mask_size = 0xAAE20, 26 * 8 * 320
    assets.append({
        "id": "display_fade_mask_atlas", "title": "Display fade/dither mask atlas",
        "kind": "transition_mask_atlas", "subsystem": "full-screen display transitions",
        "address_ranges": [data_range(blob, mask_start, mask_size, "rodata_aae20", "display_fade_mask_atlas")],
        "encoding": {
            "format": "8 AND-mask frames interleaved by 26 row phases",
            "bits_per_pixel": 4, "logical_width_pixels": 640,
            "phase_rows": 26, "frame_count": 8, "bytes_per_mask_row": 320,
            "phase_block_stride_bytes": 2560,
            "frame_row_offset_rule": "phase*0xA00 + 0x8C0 - frame*0x140",
            "display_expansion": "tile phase row y % 26 over 199 visible rows",
        },
        "behavior": "Each transition step ANDs one mask frame into every nonzero framebuffer byte, then refreshes the 640×199 display.",
        "visual_description": "Eight ordered dither masks that progressively erase or reveal a full screen in repeating 26-row bands.",
        "plain_language": "The user sees the current screen dissolve in a patterned eight-step fade rather than disappear instantly.",
        "producers": [],
        "consumers": [fn(name) for name in ("gui_screen_fade_out_transition", "display_fade_out_mask_bands", "navigation_panoramic_map_display")],
        "reference_evidence": [
            {"kind": "indexed mask read", "function": fn("gui_screen_fade_out_transition"), "target": "0x000ab6e0", "expression": "rodata_aae20 + 0x8c0 + (row % 26)*0xa00 - frame*0x140"},
            {"kind": "indexed mask read", "function": fn("navigation_panoramic_map_display"), "target": hx(mask_start), "expression": "same mask atlas used for navigation transitions"},
        ],
        "related_constants": [
            {"name": "visible_width", "value": 640}, {"name": "visible_rows", "value": 199},
            {"name": "frame_count", "value": 8}, {"name": "phase_period_rows", "value": 26},
        ],
        "related_structures": layouts(["gui_screen_fade_out_transition", "display_fade_out_mask_bands", "navigation_panoramic_map_display"]),
        "related_strings": [],
        "renderer": {
            "viewer": "transition preview with before/after test card",
            "strategy": "For frame 0..7 and output row y, select the 320-byte row at (y%26)*0xA00 + 0x8C0-frame*0x140 and AND it with a 4-bpp test framebuffer.",
            "safe_bounds": "Use exactly 26 phase blocks; the address expression remains inside 0x000aae20..0x000bb220.",
        },
        "confidence": "high", "caveats": ["The mask is an effect operand, not a standalone picture; preview it over a test image."],
    })

    scroll_up = list(struct.unpack("<9i", read_va(blob, 0x883EC, 36)))
    scroll_down = list(struct.unpack("<9i", read_va(blob, 0x88410, 36)))
    for key, address, values, direction in (
        ("scroll_text_forward_curve", 0x883EC, scroll_up, "forward/downward"),
        ("scroll_text_reverse_curve", 0x88410, scroll_down, "reverse/upward"),
    ):
        assets.append({
            "id": key, "title": direction.title() + " text-scroll curve",
            "kind": "animation_curve", "subsystem": "scrolling text",
            "address_ranges": [data_range(blob, address, 36, f"rodata_{address:x}", key)],
            "encoding": {"format": "nine little-endian signed int32 frame parameters", "values": values, "frame_count": 9},
            "behavior": "ui_render_scroll_text_frame passes each value to reflash_fb_data_to_lcd_ex while shifting a 27-pixel text band.",
            "visual_description": f"A nine-step {direction} text-strip motion sequence.",
            "plain_language": f"The user sees text slide {direction} smoothly instead of jumping between pages.",
            "producers": [], "consumers": [fn("ui_render_scroll_text_frame")],
            "reference_evidence": [{"kind": "fixed nine-entry loop", "function": fn("ui_render_scroll_text_frame"), "target": hx(address)}],
            "related_constants": [{"name": "frame_count", "value": 9}, {"name": "shift_height_pixels", "value": 27}],
            "related_structures": layouts(["ui_render_scroll_text_frame"]), "related_strings": [],
            "renderer": {"viewer": "timeline/curve plot plus simulated text strip", "strategy": "Plot the nine signed values and allow stepping the corresponding 27-pixel band shift.", "safe_bounds": "Read exactly nine int32 values."},
            "confidence": "high", "caveats": ["The integers are LCD refresh parameters/offsets; their exact controller-level interpretation is not named in the firmware."],
        })

    # Runtime/external visual stores are included so the viewer can explain why
    # pixels are referenced but cannot be read from app_update.bin alone.
    assets.extend([
        {
            "id": "active_display_framebuffer", "title": "Active projector framebuffer",
            "kind": "runtime_framebuffer", "subsystem": "projector/display driver",
            "address_ranges": [{"pointer_symbol": "g_gui_active_canvas", "pointer_address": "0x2000a034", "storage": "runtime SRAM row-pointer table"}],
            "encoding": {"format": "packed 4-bit grayscale", "bits_per_pixel": 4, "width_pixels": 640, "allocated_height_pixels": 200, "normally_refreshed_rows": 199, "row_stride_bytes": 320, "total_bytes": 64000, "pixel_order": "high nibble then low nibble"},
            "behavior": "All GUI renderers composite into row pointers here; projector_fill_framebuffer confirms the 64,000-byte 640×200 allocation.",
            "visual_description": "The complete current glasses display image.",
            "plain_language": "This is the final 640-pixel-wide grayscale frame that the wearer sees, but it exists only while firmware is running.",
            "producers": [fn(name) for name in ("gui_utf_draw", "gui_bmp_bitmap_draw", "gui_bmp_dynamic_bitmap_draw", "projector_fill_framebuffer")],
            "consumers": [fn(name) for name in ("reflash_fb_data_to_lcd", "projector_write_pixel_data") if name in functions],
            "reference_evidence": [{"kind": "allocation-sized memset", "function": fn("projector_fill_framebuffer"), "expression": "memset(..., 64000)"}],
            "related_constants": [{"name": "framebuffer_bytes", "value": 64000}, {"name": "transfer_rows", "value": 192}],
            "related_structures": layouts(["projector_fill_framebuffer", "projector_write_pixel_data"]), "related_strings": [],
            "renderer": {"viewer": "runtime framebuffer", "strategy": "Enable only when a RAM snapshot supplies the row-pointer targets; decode 320 bytes per row.", "safe_bounds": "Never dereference firmware RAM pointers in the static viewer."},
            "confidence": "high", "caveats": ["No framebuffer pixels are present in app_update.bin; a live or captured SRAM image is required."],
        },
        {
            "id": "qspi_demo_bmp_bank", "title": "External demo-image BMP bank",
            "kind": "external_image_bank", "subsystem": "factory/demo display",
            "address_ranges": [{"address_start": "0x00180000", "address_end_exclusive": hx(0x180000 + 5 * 0x3EBE), "slot_count": 5, "slot_stride_bytes": 0x3EBE, "storage": "external QSPI flash"}],
            "encoding": {"format": "Windows BMP", "signature": "BM", "accepted_bit_depth": 1, "row_alignment": "32-bit BMP rows", "decoded_format": "packed 4-bit grayscale", "decoded_width_pixels": 640, "decoded_row_stride_bytes": 320, "likely_max_height_pixels": 199},
            "behavior": "get_demo_image_source reads one of five slots, validates BM and 1-bpp metadata, reads rows bottom-up, inverts them, and expands them into the projector framebuffer.",
            "visual_description": "Five full-screen monochrome factory/demo pictures stored outside the CPU image.",
            "plain_language": "These would appear as full-screen demonstration images; their actual artwork is not recoverable without the glasses' QSPI flash dump.",
            "producers": [fn("get_demo_image_source")], "consumers": [fn("update_demo_image_display")],
            "reference_evidence": [{"kind": "external-flash address arithmetic", "function": fn("get_demo_image_source"), "expression": "0x180000 + mode*0x3ebe; mode clamped to 0..4"}],
            "related_constants": [{"name": "BMP_signature", "address": "0x000a8da5", "value": "BM"}, {"name": "slot_count", "value": 5}, {"name": "slot_stride", "value": 16062}],
            "related_structures": layouts(["get_demo_image_source", "update_demo_image_display"]),
            "related_strings": [{"address": "0x000a8da8", "text": "File is not BMP format"}, {"address": "0x000a8dc1", "text": "Unsupported bit depth - %d"}],
            "renderer": {"viewer": "disabled BMP gallery until QSPI dump is supplied", "strategy": "Given a QSPI dump, parse each fixed slot as a bounded BMP and render only when signature, dimensions, bit depth and payload bounds validate.", "safe_bounds": "Never interpret app_update.bin at these addresses; they are a different storage device."},
            "confidence": "high for layout; unknown content", "caveats": ["External QSPI bytes are absent from this repository.", "640×199 is inferred from the 320-byte destination rows and display geometry; honor BMP metadata if a dump is supplied."],
        },
        {
            "id": "qspi_multilingual_glyph_store", "title": "External multilingual/Chinese glyph store",
            "kind": "external_font_bank", "subsystem": "Unicode text rendering",
            "address_ranges": [
                {"address_start": "0x00140000", "storage": "external QSPI flash", "meaning": "Unicode-to-glyph index table"},
                {"address_start": "0x00200000", "storage": "external QSPI flash", "meaning": "compressed 24×26-class glyph payloads"},
                {"address_start": "0x00520000", "storage": "external QSPI flash", "meaning": "compressed 16×26-class glyph payloads"},
                {"address_start": "0x00a40000", "storage": "external QSPI flash", "meaning": "compressed 24×26-class glyph payloads"},
            ],
            "encoding": {"format": "2-bit packed glyphs expanded by the 256-entry LUT at 0x000d753a", "stored_to_rendered_ratio": "1:4 bytes", "rendered_format": "packed 4-bit grayscale", "index_entry_bytes": 4, "known_rendered_sizes": [208, 312]},
            "behavior": "resource_manger_get selects embedded Latin glyphs first, then reads Unicode index tables and compressed CJK glyph payloads through the device storage callback.",
            "visual_description": "Downloadable Chinese and other multilingual character glyphs matching the embedded UI font style.",
            "plain_language": "These are the non-Latin characters shown in translated text; only their lookup/decoder logic is in this firmware image, while the character artwork lives in external flash.",
            "producers": [fn("find_chinese_bitmap_by_unicode"), fn("resource_manger_get"), fn("expand_bytes_via_lut32")],
            "consumers": [fn("gui_utf_draw"), fn("gui_string_draw")],
            "reference_evidence": [{"kind": "external Unicode index/payload lookup", "function": fn("find_chinese_bitmap_by_unicode"), "expression": "index=0x140000+(codepoint-0xa4)*4; payload=0x200000+index*(width*height/4)"}],
            "related_constants": [{"name": "expansion_lut", "address": "0x000d753a", "entries": 256}, {"name": "glyph_cache", "address": "0x2001cf92"}],
            "related_structures": layouts(["find_chinese_bitmap_by_unicode", "resource_manger_get"]),
            "related_strings": [{"address": "0x000d74f4", "text": "unicode=%x, offset=%d"}],
            "renderer": {"viewer": "disabled glyph browser until QSPI dump is supplied", "strategy": "Use the exact firmware index arithmetic and LUT expansion; expose codepoint search and glyph preview after validating every external range.", "safe_bounds": "Do not conflate QSPI addresses with CPUAPP virtual addresses."},
            "confidence": "high for lookup and encoding; unknown content", "caveats": ["External QSPI bytes are absent.", "Several Unicode ranges select different index bases; the viewer should delegate lookup to a bounded decoder rather than assume one contiguous table."],
        },
    ])

    counts = {}
    for asset in assets:
        counts[asset["kind"]] = counts.get(asset["kind"], 0) + 1
    report = {
        "schema": 1,
        "core": "CPUAPP",
        "purpose": "G1 visual-asset evidence and safe viewer decoder specifications",
        "inputs": [
            "app_update.bin", "recon/readable_sources/app/g1/",
            "recon/readable_sources/app/manifest.json", "recon/catalogs/refgraph_app.json.gz",
        ],
        "summary": {
            "asset_records": len(assets), "records_by_kind": counts,
            "static_bitmap_records": 97, "builtin_icon_records": 20,
            "animation_records": 12, "animation_frames": sum(v[3] for v in dynamic_meta.values()),
            "embedded_font_banks": 4, "embedded_glyphs": sum(a["encoding"]["glyph_count"] for a in assets if a["kind"] == "font_bank"),
            "external_or_runtime_records": sum(a["kind"].startswith("external_") or a["kind"] == "runtime_framebuffer" for a in assets),
        },
        "display_model": {
            "logical_width_pixels": 640, "allocated_height_pixels": 200,
            "normally_refreshed_rows": 199, "bits_per_pixel": 4,
            "row_stride_bytes": 320, "framebuffer_bytes": 64000,
            "pixel_order": "high nibble then low nibble",
            "evidence": ["projector_fill_framebuffer memset size 64000", "GUI refresh rectangles use width 0x280 and height 199", "bitmap blitters use width/2 byte strides"],
        },
        "decoder_safety": [
            "Treat address_end_exclusive as authoritative and reject reads beyond it.",
            "Do not dereference RAM pointer symbols in a static viewer.",
            "Do not read QSPI addresses from app_update.bin; require a separately supplied QSPI dump.",
            "Use dispatch-table frame/glyph counts even when leading or trailing frames are visually blank.",
            "Show semantic labels as inferred unless corroborated by a named call-site constant.",
        ],
        "assets": assets,
        "refgraph_note": {
            "resource_manager_data_refs": refgraph["0x4588c"]["data_refs"],
            "meaning": "Ghidra's exported data-reference set independently contains the static/dynamic rodata targets resolved above.",
        },
    }
    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    OUTPUT.write_text(json.dumps(report, indent=2, ensure_ascii=False) + "\n")
    print(json.dumps(report["summary"], indent=2))
    print(OUTPUT)


if __name__ == "__main__":
    main()
