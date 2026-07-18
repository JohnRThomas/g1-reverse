#!/usr/bin/env python3
"""Gate CPUAPP candidate init/device topology against the firmware inventory."""

import argparse
import re
import shutil
import subprocess
from pathlib import Path


EXPECTED_INIT_COUNTS = {
    "PRE_KERNEL_1": 17,
    "PRE_KERNEL_2": 1,
    "POST_KERNEL": 28,
    "APPLICATION": 2,
}
DEVICE_STRIDE = 24
EXPECTED_DEVICE_COUNT = 26
LSM_OBJECT = "app/libapp.a(g1_lsm6dso_device.c.obj)"


def symbol_address(map_text, symbol):
    match = re.search(r"^\s*(0x[0-9a-fA-F]+)\s+" + re.escape(symbol) +
                      r"(?:\s*=\s*\.)?\s*$",
                      map_text, re.MULTILINE)
    if not match:
        raise ValueError("missing map symbol: %s" % symbol)
    return int(match.group(1), 16)


def topology_from_map(map_text):
    starts = {
        "PRE_KERNEL_1": symbol_address(map_text, "__init_PRE_KERNEL_1_start"),
        "PRE_KERNEL_2": symbol_address(map_text, "__init_PRE_KERNEL_2_start"),
        "POST_KERNEL": symbol_address(map_text, "__init_POST_KERNEL_start"),
        "APPLICATION": symbol_address(map_text, "__init_APPLICATION_start"),
        "SMP": symbol_address(map_text, "__init_SMP_start"),
    }
    counts = {
        "PRE_KERNEL_1": (starts["PRE_KERNEL_2"] - starts["PRE_KERNEL_1"]) // 8,
        "PRE_KERNEL_2": (starts["POST_KERNEL"] - starts["PRE_KERNEL_2"]) // 8,
        "POST_KERNEL": (starts["APPLICATION"] - starts["POST_KERNEL"]) // 8,
        "APPLICATION": (starts["SMP"] - starts["APPLICATION"]) // 8,
    }
    device_start = symbol_address(map_text, "_device_list_start")
    device_end = symbol_address(map_text, "_device_list_end")
    if (device_end - device_start) % DEVICE_STRIDE:
        raise ValueError("candidate device area is not 24-byte aligned")
    return counts, (device_end - device_start) // DEVICE_STRIDE


def ordered(map_text, owners):
    positions = [map_text.find(owner) for owner in owners]
    return all(pos >= 0 for pos in positions) and positions == sorted(positions)


def object_sections(objdump, obj):
    output = subprocess.check_output([objdump, "-h", str(obj)], text=True)
    return {
        name: int(size, 16)
        for name, size in re.findall(
            r"^\s*\d+\s+(\S+)\s+([0-9a-fA-F]+)\s+", output, re.MULTILINE)
    }


def relocation_entries(readelf, obj, section):
    output = subprocess.check_output([readelf, "-rW", str(obj)], text=True)
    section = section.lstrip(".")
    match = re.search(
        r"Relocation section '\.rel\." + re.escape(section) + r"'[^\n]*\n"
        r"(?P<body>.*?)(?=\nRelocation section|\Z)", output, re.DOTALL)
    if not match:
        raise ValueError("missing relocation section for %s" % section)
    return [(int(offset, 16), symbol) for offset, symbol in re.findall(
        r"^([0-9a-fA-F]{8})\s+\S+\s+\S+\s+\S+\s+(\S+)\s*$",
        match.group("body"), re.MULTILINE)]


def section_bytes(readelf, obj, section):
    output = subprocess.check_output(
        [readelf, "-x", section, str(obj)], text=True)
    chunks = []
    for line in output.splitlines():
        match = re.match(r"\s*0x[0-9a-fA-F]+\s+((?:[0-9a-fA-F]{8}\s*)+)", line)
        if match:
            chunks.extend(match.group(1).split())
    return bytes.fromhex("".join(chunks))


def check(build_dir, objdump, readelf):
    map_path = build_dir / "zephyr/zephyr_pre0.map"
    obj_path = build_dir / "CMakeFiles/app.dir/src/g1_lsm6dso_device.c.obj"
    map_text = map_path.read_text()
    counts, devices = topology_from_map(map_text)
    if counts != EXPECTED_INIT_COUNTS:
        raise ValueError("init counts differ: %r" % counts)
    if devices != EXPECTED_DEVICE_COUNT:
        raise ValueError("device count differs: %d" % devices)

    post_order = (
        "opt3001.c.obj", "npm1300_charger.c.obj", LSM_OBJECT,
        "sync_rtc.c.obj",
    )
    device_order = (
        "dmic_nrfx_pdm.c.obj", LSM_OBJECT, "npm1300_charger.c.obj",
        "opt3001.c.obj",
    )
    post_block = map_text[map_text.index("__init_POST_KERNEL_start"):
                          map_text.index("__init_APPLICATION_start")]
    if not ordered(post_block, post_order):
        raise ValueError("LSM POST_KERNEL order differs from firmware")
    # Search from device_area onward so init-level occurrences cannot satisfy it.
    if not ordered(map_text[map_text.index("device_area"):], device_order):
        raise ValueError("LSM device order differs from firmware")

    sections = object_sections(objdump, obj_path)
    expected_sections = {
        ".z_init_POST_KERNEL90_00155_": 8,
        "._device.static.3_90_": 24,
        ".rodata.lsm6dso_config_0": 32,
        ".rodata.lsm6dso_driver_api": 28,
        ".bss.lsm6dso_data_0": 36,
    }
    for name, size in expected_sections.items():
        if sections.get(name) != size:
            raise ValueError("%s size differs: %r" % (name, sections.get(name)))
    # The first word has no relocation and is therefore literal zero.  The
    # sole relocation at +4 owns the device pointer.
    init_section = ".z_init_POST_KERNEL90_00155_"
    if [offset for offset, _ in relocation_entries(
            readelf, obj_path, init_section)] != [4]:
        raise ValueError("LSM init entry is not { NULL, &device }")

    config_relocs = relocation_entries(
        readelf, obj_path, "rodata.lsm6dso_config_0")
    if [offset for offset, _ in config_relocs] != [0, 4, 8, 12, 16]:
        raise ValueError("LSM config ownership relocations differ")
    if [symbol for _, symbol in config_relocs[:3]] != [
            "stmemsc_i2c_write", "stmemsc_i2c_read", "stmemsc_mdelay"]:
        raise ValueError("LSM stock bus/delay owners differ")
    config_bytes = section_bytes(
        readelf, obj_path, ".rodata.lsm6dso_config_0")
    if config_bytes[20:] != bytes.fromhex("6b0000000100000100000000"):
        raise ValueError("LSM address/power-mode/default config bytes differ")

    api_relocs = relocation_entries(
        readelf, obj_path, "rodata.lsm6dso_driver_api")
    if [offset for offset, _ in api_relocs] != [0, 12, 16]:
        raise ValueError("LSM API non-NULL slot mask differs")
    device_relocs = relocation_entries(
        readelf, obj_path, "_device.static.3_90_")
    if [offset for offset, _ in device_relocs] != [0, 4, 8, 12, 16]:
        raise ValueError("LSM descriptor ownership/NULL PM shape differs")

    lsm_va = symbol_address(map_text, "__device_dts_ord_155")
    if symbol_address(map_text, "rodata_87d58") != lsm_va:
        raise ValueError("original 0x87d58 backmap does not resolve to LSM device")

    config = (build_dir / "zephyr/.config").read_text()
    if "CONFIG_LSM6DSO=y" in config:
        raise ValueError("stock non-NULL lsm6dso_init owner is enabled")
    print("CPUAPP root topology exact: 17/1/28/2 init, 26 devices, LSM NULL init")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("build_dir", type=Path)
    parser.add_argument("--objdump", default=shutil.which("arm-zephyr-eabi-objdump"))
    parser.add_argument("--readelf", default=shutil.which("arm-zephyr-eabi-readelf"))
    args = parser.parse_args()
    if not args.objdump or not args.readelf:
        parser.error("arm-zephyr-eabi objdump/readelf must be on PATH or supplied")
    check(args.build_dir, args.objdump, args.readelf)


if __name__ == "__main__":
    main()
