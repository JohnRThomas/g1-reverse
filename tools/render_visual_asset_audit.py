#!/usr/bin/env python3
"""Render every embedded G1 bitmap/font family into deterministic audit sheets."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import math
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont


ROOT = Path(__file__).resolve().parents[1]
SERVER = ROOT / "tools/symbol_browser/server.py"
DEFAULT_OUT = ROOT / "recon/viewer_assets/previews"
BACKGROUND = 13
PANEL = 5
TEXT = 205


def load_index():
    spec = importlib.util.spec_from_file_location("g1_symbol_browser", SERVER)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.INDEX


def records(index, family: str) -> list[dict]:
    result = index.list_assets("", family, 1, 10_000)
    return [index.asset_detail(row["id"]) for row in result["items"]]


def payload(asset: dict, key: str = "bytes") -> bytes:
    value = asset.get(key, "")
    if isinstance(value, str):
        return bytes.fromhex(value)
    return bytes(value or [])


def decode_4bpp(data: bytes, width: int, height: int, *, low_first: bool = False) -> Image.Image:
    pixels: list[int] = []
    for byte in data:
        pair = (byte & 15, byte >> 4) if low_first else (byte >> 4, byte & 15)
        pixels.extend(value * 17 for value in pair)
    needed = width * height
    if len(pixels) < needed:
        raise ValueError(f"short bitmap: {len(pixels)} pixels for {width}x{height}")
    image = Image.new("L", (width, height))
    image.putdata(pixels[:needed])
    return image


def tile(image: Image.Image, title: str, size: tuple[int, int] = (160, 126)) -> Image.Image:
    width, height = size
    result = Image.new("L", size, PANEL)
    draw = ImageDraw.Draw(result)
    limit_w, limit_h = width - 20, height - 34
    scale = max(1, min(limit_w // image.width, limit_h // image.height))
    shown = image.resize((image.width * scale, image.height * scale), Image.Resampling.NEAREST)
    result.paste(shown, ((width - shown.width) // 2, 4 + (limit_h - shown.height) // 2))
    draw.text((6, height - 25), title[:25], fill=TEXT, font=ImageFont.load_default())
    draw.text((6, height - 13), f"{image.width}x{image.height}", fill=120, font=ImageFont.load_default())
    return result


def sheet(tiles: list[Image.Image], columns: int = 8, gap: int = 8) -> Image.Image:
    cell_w = max(image.width for image in tiles)
    cell_h = max(image.height for image in tiles)
    rows = math.ceil(len(tiles) / columns)
    result = Image.new("L", (gap + columns * (cell_w + gap), gap + rows * (cell_h + gap)), BACKGROUND)
    for index, image in enumerate(tiles):
        x = gap + (index % columns) * (cell_w + gap)
        y = gap + (index // columns) * (cell_h + gap)
        result.paste(image, (x, y))
    return result


def save(image: Image.Image, path: Path, artifacts: dict) -> None:
    image.save(path, optimize=True)
    artifacts[path.name] = {
        "width": image.width,
        "height": image.height,
        "sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
    }


def bitmap_dimensions(asset: dict) -> tuple[int, int]:
    return int(asset["width"]), int(asset["height"])


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUT)
    args = parser.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)

    index = load_index()
    visuals = records(index, "visual")
    fonts = [asset for asset in records(index, "fonts") if asset.get("kind") == "font_bank"]
    statics = [asset for asset in visuals if asset.get("kind") == "static_bitmap"]
    builtins = [asset for asset in visuals if asset.get("kind") == "compressed_icon"]
    special = next(asset for asset in statics if asset.get("id") == "builtin_icon_04")
    animations = [asset for asset in visuals if asset.get("kind") == "frame_animation"]
    artifacts: dict[str, dict] = {}
    errors: list[str] = []

    static_tiles = []
    for asset in statics:
        width, height = bitmap_dimensions(asset)
        data = payload(asset)
        expected = math.ceil(width / 2) * height
        if len(data) != expected:
            errors.append(f"{asset['id']}: {len(data)} bytes != {expected}")
        static_tiles.append(tile(decode_4bpp(data, width, height), asset["id"]))
    save(sheet(static_tiles), args.output / "static_bitmaps.png", artifacts)

    icon_tiles = []
    for asset in sorted([*builtins, special], key=lambda row: int(row["id"].rsplit("_", 1)[1], 16)):
        width, height = bitmap_dimensions(asset)
        data = payload(asset)
        if len(data) != math.ceil(width / 2) * height:
            errors.append(f"{asset['id']}: expanded icon size mismatch")
        icon_tiles.append(tile(decode_4bpp(data, width, height, low_first=asset.get("kind") == "compressed_icon"), asset["id"], (170, 150)))
    save(sheet(icon_tiles, columns=5), args.output / "builtin_icons.png", artifacts)

    animation_tiles = []
    frame_total = 0
    for asset in animations:
        width, height = bitmap_dimensions(asset)
        data = payload(asset)
        stride, count = int(asset["frame_stride_bytes"]), int(asset["frame_count"])
        frame_total += count
        if len(data) != stride * count or stride != math.ceil(width / 2) * height:
            errors.append(f"{asset['id']}: frame boundary mismatch")
        for frame_index in sorted({0, count // 2, count - 1}):
            frame = data[frame_index * stride:(frame_index + 1) * stride]
            animation_tiles.append(tile(decode_4bpp(frame, width, height), f"{asset['id']} f{frame_index}/{count-1}"))
    save(sheet(animation_tiles, columns=6), args.output / "animation_triplets.png", artifacts)

    glyph_tiles = []
    glyph_total = 0
    for asset in fonts:
        data = payload(asset, "glyph_payload_hex")
        entries = asset.get("entries", [])
        glyph_total += len(entries)
        for entry in entries:
            offset, size = int(entry["payload_offset"]), int(entry["size_bytes"])
            width, height = int(entry["width_pixels"]), int(entry["height_pixels"])
            if offset + size > len(data) or size != math.ceil(width / 2) * height:
                errors.append(f"{asset['id']} {entry['codepoint']}: glyph boundary mismatch")
                continue
            glyph = decode_4bpp(data[offset:offset + size], width, height)
            label = f"{asset['id']} {entry['codepoint']}"
            glyph_tiles.append(tile(glyph, label, (150, 116)))
    save(sheet(glyph_tiles, columns=9), args.output / "font_glyphs.png", artifacts)

    compare_tiles = []
    for asset in statics[:12]:
        width, height = bitmap_dimensions(asset)
        data = payload(asset)
        compare_tiles.append(tile(decode_4bpp(data, width, height), f"{asset['id']} high-first", (190, 140)))
        compare_tiles.append(tile(decode_4bpp(data, width, height, low_first=True), f"{asset['id']} low-first", (190, 140)))
    bleed_probe = next(asset for asset in builtins if asset["id"] == "builtin_icon_11")
    probe_width, probe_height = bitmap_dimensions(bleed_probe)
    probe_data = payload(bleed_probe)
    compare_tiles.append(tile(decode_4bpp(probe_data, probe_width, probe_height), "icon_11 WRONG high-first", (190, 140)))
    compare_tiles.append(tile(decode_4bpp(probe_data, probe_width, probe_height, low_first=True), "icon_11 LUT low-first", (190, 140)))
    save(sheet(compare_tiles, columns=6), args.output / "nibble_order_comparison.png", artifacts)

    report = {
        "schema": "g1-visual-decode-audit-v1",
        "status": "PASS" if not errors else "FAIL",
        "decoder": {
            "native_pixel_order": "high nibble then low nibble, left-to-right",
            "lut_icon_pixel_order": "low nibble then high nibble after little-endian LUT expansion",
            "intensity": "absolute unsigned 4-bit grayscale; display level = value * 17",
            "normalization": "none",
            "builtin_icons": "stored 1-bpp; firmware 256-entry LUT at 0x000d753a expands each source byte to four output bytes",
            "animation_frames": "ascending-address frames using catalogued frame_stride_bytes",
            "fonts": "per-glyph cumulative payload offsets and row strides from the recovered glyph index",
        },
        "coverage": {
            "static_bitmaps": len(statics),
            "builtin_icons": len(builtins) + 1,
            "animations": len(animations),
            "animation_frames_checked": frame_total,
            "font_banks": len(fonts),
            "glyphs_checked": glyph_total,
        },
        "errors": errors,
        "artifacts": artifacts,
    }
    (args.output / "visual_decode_audit.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
    if errors:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
