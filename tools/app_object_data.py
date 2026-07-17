#!/usr/bin/env python3
"""Decode app-core static k_msgq initializers from the shipped image.

The reset-time copy at 0x74b34 maps the ROM image beginning at 0x000f8d64
onto RAM beginning at 0x20002000.  This exposes the exact Zephyr k_msgq
initializer fields that are otherwise absent from function bodies.
"""

from __future__ import annotations

import json
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
IMAGE = ROOT / "app_update.bin"
ROM_BASE = 0x0000C000
COPY_SITE = 0x00074B34
COPY_LITERALS = 0x00074B50

QUEUES = {
    "g_audio_msgq": 0x20003890,
    "g_display_msgq": 0x200038C4,
    "g_quicknote_flash_msgq": 0x20003960,
    "g_flash_store_cmd_msgq": 0x20003994,
}


def read_words(blob: bytes, address: int, count: int) -> tuple[int, ...]:
    offset = address - ROM_BASE
    return struct.unpack_from(f"<{count}I", blob, offset)


def decode() -> dict[str, object]:
    blob = IMAGE.read_bytes()
    ram_start, ram_end, rom_start = read_words(blob, COPY_LITERALS, 3)
    if (ram_start, ram_end, rom_start) != (
        0x20002000,
        0x20003C50,
        0x000F8D64,
    ):
        raise ValueError("unexpected app .data copy literals at 0x74b50")

    result: dict[str, object] = {
        "source": str(IMAGE.relative_to(ROOT)),
        "copy_site": f"0x{COPY_SITE:08x}",
        "ram_start": f"0x{ram_start:08x}",
        "ram_end": f"0x{ram_end:08x}",
        "rom_start": f"0x{rom_start:08x}",
        "queues": {},
    }
    queues = result["queues"]
    assert isinstance(queues, dict)
    for name, address in QUEUES.items():
        rom_address = rom_start + address - ram_start
        words = read_words(blob, rom_address, 10)
        msg_size, max_msgs = words[3:5]
        buffer_start, buffer_end = words[5:7]
        if words[0:2] != (address, address):
            raise ValueError(f"{name}: invalid self-linked wait queue")
        if buffer_end - buffer_start != msg_size * max_msgs:
            raise ValueError(f"{name}: buffer span disagrees with queue dimensions")
        queues[name] = {
            "address": f"0x{address:08x}",
            "rom_initializer": f"0x{rom_address:08x}",
            "msg_size": msg_size,
            "max_msgs": max_msgs,
            "buffer_start": f"0x{buffer_start:08x}",
            "buffer_end": f"0x{buffer_end:08x}",
            "used_msgs": words[9],
        }
    return result


if __name__ == "__main__":
    print(json.dumps(decode(), indent=2, sort_keys=True))
