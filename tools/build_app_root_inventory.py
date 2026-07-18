#!/usr/bin/env python3
"""Build the authoritative CPUAPP boot/root inventory from app_update.bin."""

import argparse
import hashlib
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import extract


ROOT = Path(__file__).resolve().parents[1]
OUTPUT = ROOT / "recon/catalogs/app_root_inventory.json"

VECTOR_NAMES = {
    0: "initial_msp", 1: "Reset_Handler", 2: "NMI_Handler",
    3: "HardFault_Handler", 4: "MemManage_Handler", 5: "BusFault_Handler",
    6: "UsageFault_Handler", 11: "SVC_Handler", 12: "DebugMon_Handler",
    14: "PendSV_Handler", 15: "SysTick_Handler",
    26: "SPIM4_SPIS4_TWIM4_TWIS4_UARTE4_IRQHandler",
    28: "SPIM3_SPIS3_TWIM3_TWIS3_UARTE3_IRQHandler",
}

INIT_LEVELS = {
    "PRE_KERNEL_1": (0x879B0, 0x87A38),
    "PRE_KERNEL_2": (0x87A38, 0x87A40),
    "POST_KERNEL": (0x87A40, 0x87B20),
    "APPLICATION": (0x87B20, 0x87B30),
}

# Even Thumb entry VA -> exact stock owner and selection evidence.
INIT_OWNERS = {
    0x4C144: ("nordicsemi_nrf53_init", "zephyr/soc/arm/nordic_nrf/nrf53/soc.c", ["CONFIG_SOC_SERIES_NRF53X"]),
    0x51198: ("posix_barrier_pool_init", "zephyr/lib/posix/barrier.c", ["CONFIG_POSIX_API"]),
    0x511F0: ("posix_cond_pool_init", "zephyr/lib/posix/cond.c", ["CONFIG_POSIX_API"]),
    0x51230: ("posix_mutex_pool_init", "zephyr/lib/posix/mutex.c", ["CONFIG_POSIX_API"]),
    0x51274: ("posix_thread_pool_init", "zephyr/lib/posix/pthread.c", ["CONFIG_POSIX_API"]),
    0x4CCD4: ("shared_memory_prepare", "zephyr/subsys/ipc/ipc_service/backends/ipc_rpmsg_static_vrings.c", ["CONFIG_IPC_SERVICE"]),
    0x6058C: ("clock_control_nrf_init", "zephyr/drivers/clock_control/clock_control_nrf.c", ["CONFIG_CLOCK_CONTROL_NRF"]),
    0x719A4: ("kheap_init", "zephyr/kernel/kheap.c", ["CONFIG_HEAP_MEM_POOL_SIZE"]),
    0x71BD0: ("init_mem_slab_module", "zephyr/kernel/mem_slab.c", ["CONFIG_MULTITHREADING"]),
    0x61574: ("gpio_nrfx_init", "zephyr/drivers/gpio/gpio_nrfx.c", ["CONFIG_GPIO_NRFX"]),
    0x84D4E: ("nrf_cc3xx_platform_early_init", "nrfxlib/crypto/nrf_cc312_platform", ["CONFIG_NRF_CC3XX_PLATFORM"]),
    0x83892: ("entropy_bt_hci_init", "nrf/drivers/entropy/entropy_bt_hci.c", ["CONFIG_ENTROPY_GENERATOR"]),
    0x838B4: ("entropy_cc3xx_init", "nrf/drivers/entropy/entropy_cc3xx.c", ["CONFIG_ENTROPY_GENERATOR"]),
    0x63B10: ("wdt_nrfx_init", "zephyr/drivers/watchdog/wdt_nrfx.c", ["CONFIG_WDT_NRFX"]),
    0x62D9C: ("uarte_nrfx_init", "zephyr/drivers/serial/uart_nrfx_uarte.c", ["CONFIG_UART_NRFX"]),
    0x608C4: ("uart_console_init", "zephyr/drivers/console/uart_console.c", ["CONFIG_UART_CONSOLE"]),
    0x637B8: ("sys_clock_driver_init", "zephyr/drivers/timer/nrf_rtc_timer.c", ["CONFIG_NRF_RTC_TIMER"]),
    0x4C190: ("rtc_pretick_init", "nrf/soc/arm/nordic_nrf/nrf53/rtc_pretick.c", ["CONFIG_SOC_NRF53_RTC_PRETICK"]),
    0x4D274: ("log_init", "zephyr/subsys/logging/log_core.c", ["CONFIG_LOG"]),
    0x61AEC: ("mbox_nrfx_init", "zephyr/drivers/mbox/mbox_nrfx_ipc.c", ["CONFIG_MBOX_NRFX_IPC"]),
    0x50FF4: ("malloc_prepare", "zephyr/lib/libc/newlib/libc-hooks.c", ["CONFIG_NEWLIB_LIBC"]),
    0x84D52: ("nrf_cc3xx_platform_init", "nrfxlib/crypto/nrf_cc312_platform", ["CONFIG_NRF_CC3XX_PLATFORM"]),
    0x72A7C: ("k_sys_work_q_init", "zephyr/kernel/system_work_q.c", ["CONFIG_SYSTEM_WORKQUEUE_PRIORITY"]),
    0x60C00: ("qspi_nor_init", "zephyr/drivers/flash/flash_nrf_qspi_nor.c", ["CONFIG_FLASH_NRF_QSPI"]),
    0x7EB5C: ("ipc_static_vrings_init", "zephyr/subsys/ipc/ipc_service/backends/ipc_rpmsg_static_vrings.c", ["CONFIG_IPC_SERVICE"]),
    0x5F988: ("adc_nrfx_saadc_init", "zephyr/drivers/adc/adc_nrfx_saadc.c", ["CONFIG_ADC_NRFX_SAADC"]),
    0x61234: ("soc_flash_nrf_init", "zephyr/drivers/flash/soc_flash_nrf.c", ["CONFIG_SOC_FLASH_NRF"]),
    0x617DC: ("i2c_nrfx_twim_init", "zephyr/drivers/i2c/i2c_nrfx_twim.c", ["CONFIG_I2C_NRFX"]),
    0x5129C: ("remoteproc_mgr_boot", "zephyr/boards/arm/nrf5340dk_nrf5340/nrf5340_cpunet_reset.c", ["CONFIG_BOARD_ENABLE_CPUNET"]),
    0x53194: ("long_wq_init", "zephyr/subsys/bluetooth/host/long_wq.c", ["CONFIG_BT_LONG_WQ"]),
    0x60174: ("bt_rpmsg_init", "zephyr/drivers/bluetooth/hci/rpmsg.c", ["CONFIG_BT_RPMSG"]),
    0x61D10: ("mfd_npm1300_init", "zephyr/drivers/mfd/mfd_npm1300.c", ["CONFIG_MFD_NPM1300"]),
    0x83CB4: ("gpio_npm1300_init", "zephyr/drivers/gpio/gpio_npm1300.c", ["CONFIG_GPIO_NPM1300"]),
    0x639D4: ("wdt_npm1300_init", "zephyr/drivers/watchdog/wdt_npm1300.c", ["CONFIG_WDT_NPM1300"]),
    0x620CC: ("regulator_npm1300_common_init", "zephyr/drivers/regulator/regulator_npm1300.c", ["CONFIG_REGULATOR_NPM1300"]),
    0x84418: ("regulator_npm1300_init", "zephyr/drivers/regulator/regulator_npm1300.c", ["CONFIG_REGULATOR_NPM1300"]),
    0x5FF1C: ("pdm_nrfx_init0", "zephyr/drivers/audio/dmic_nrfx_pdm.c", ["CONFIG_AUDIO_DMIC_NRFX_PDM"]),
    0x62930: ("opt3001_init", "zephyr/drivers/sensor/opt3001/opt3001.c", ["CONFIG_OPT3001"]),
    0x62644: ("npm1300_charger_init", "zephyr/drivers/sensor/npm1300_charger/npm1300_charger.c", ["CONFIG_NPM1300_CHARGER"]),
    0x4C2D4: ("sync_rtc_setup", "zephyr/soc/arm/nordic_nrf/nrf53/sync_rtc.c", ["CONFIG_NRF53_SYNC_RTC"]),
    0x51304: ("mcumgr_handlers_init", "zephyr/subsys/mgmt/mcumgr/mgmt/src/mgmt.c", ["CONFIG_MCUMGR"]),
    0x526B4: ("smp_init", "zephyr/subsys/mgmt/mcumgr/transport/src/smp.c", ["CONFIG_MCUMGR"]),
}

DEVICE_NAMES = [
    "clock", "gpio0", "gpio1", "entropy_bt_hci", "entropy_cc3xx", "wdt0",
    "uart0", "mbox0", "qspi_nor", "ipc0", "adc0", "soc_flash", "i2c2",
    "i2c1", "npm1300_mfd", "npm1300_gpio", "npm1300_regulator_parent",
    "npm1300_wdt", "npm1300_ldo2", "npm1300_ldo1", "npm1300_buck2",
    "npm1300_buck1", "pdm0", "lsm6dso", "npm1300_charger", "opt3001",
]

ISR_OWNERS = {
    5: "clock_power_isr", 8: "uarte_nrfx_isr", 9: "nrfx_serial_irq_9",
    11: "nrfx_serial_irq_11", 13: "gpio_nrfx_isr", 14: "adc_nrfx_saadc_isr",
    21: "rtc_nrf_isr", 24: "mbox_nrfx_isr", 38: "nrfx_pdm_irq_handler",
    42: "soc_flash_irq", 43: "nrfx_qspi_irq_handler",
}

DYNAMIC_THREADS = [
    ("ancs", 0x20003C50, 0x2001D568, 0x1400, [0x19718], -11, "application"),
    ("ble_projector", 0x20003D60, 0x2001E968, 0x3000, [0x21DA8], -15, "application"),
    ("flash", 0x20003E38, 0x20021968, 0x800, [0x23480], -12, "application"),
    ("brightness", 0x20003F10, 0x20022168, 0x1400, [0x23844], -11, "application"),
    ("run_main_a", 0x200046B8, 0x20026A68, 0xC00, [0x2A8D8, 0x2685C], -10, "application"),
    ("run_main_b", 0x200041A8, 0x20024868, 0x400, [0x286F8], -10, "application"),
    ("run_main_c", 0x200040D0, 0x20023C68, 0xC00, [0x2A4F4], -9, "application"),
    ("run_main_d", 0x200045E0, 0x20026268, 0x800, [0x28BEC], -13, "application"),
    ("run_main_e", 0x20004508, 0x20025A68, 0x800, [0x2692C], -12, "application"),
    ("run_main_f", 0x20004430, 0x20025468, 0x600, [0x27CFC], -11, "application_conditional"),
    ("run_main_g", 0x20004358, 0x20025068, 0x400, [0x2A0D8, 0x28A1C], -14, "application"),
    ("run_main_h", 0x20004280, 0x20024C68, 0x400, [0x2955C], -13, "application"),
    ("aging_a", 0x20004870, 0x20027A68, 0xC00, [0x32420], -12, "application"),
    ("aging_b", 0x20004798, 0x20027668, 0x400, [0x324BC], -12, "application"),
    ("proxy", 0x20004C08, 0x20028668, 0x800, [0x47C48], -12, "application"),
    ("display", 0x20004D18, 0x20028E68, 0x1400, [0x49090], -14, "application"),
    ("bt_rx", 0x20005E30, 0x2002BB80, 0x400, [0x545F0], -9, "stock_zephyr_bt"),
]

STATIC_MSGQS = [
    ("audio", 0x20003890, 204, 18),
    ("display", 0x200038C4, 24, 30),
    ("quicknote", 0x20003960, 6, 20),
    ("flash_cmd", 0x20003994, 6, 5),
]


def sha(data):
    return hashlib.sha256(data).hexdigest()


def ptr(value):
    return {"raw": "0x%08x" % value,
            "va": None if value == 0 else "0x%08x" % (value & ~1),
            "thumb": bool(value & 1)}


def build():
    vector_data = extract.read(0xC200, 85 * 4)
    vectors = []
    for index, (value,) in enumerate(struct.iter_unpack("<I", vector_data)):
        name = VECTOR_NAMES.get(index)
        if index >= 16 and name is None:
            name = "z_arm_irq_wrapper"
        vectors.append({"index": index, "name": name, "target": ptr(value)})

    levels = []
    init_device_owner = {}
    for level, (start, end) in INIT_LEVELS.items():
        entries = []
        for entry_va in range(start, end, 8):
            function, device = struct.unpack("<II", extract.read(entry_va, 8))
            even = function & ~1
            owner = INIT_OWNERS.get(even)
            if function and owner is None:
                raise ValueError("unclassified init owner: 0x%08x" % even)
            row = {
                "entry_va": "0x%08x" % entry_va,
                "function": ptr(function),
                "name": None if owner is None else owner[0],
                "source": None if owner is None else owner[1],
                "required_kconfig": [] if owner is None else owner[2],
                "device_va": None if device == 0 else "0x%08x" % device,
                "ownership": "stock" if function else "null_device_entry",
            }
            entries.append(row)
            if device:
                init_device_owner[device] = row["name"]
        levels.append({"level": level, "start": "0x%08x" % start,
                       "end": "0x%08x" % end, "count": len(entries),
                       "sha256": sha(extract.read(start, end - start)),
                       "entries": entries})

    devices = []
    device_data = extract.read(0x87B30, 26 * 0x18)
    for index in range(26):
        va = 0x87B30 + index * 0x18
        words = struct.unpack("<6I", device_data[index * 0x18:(index + 1) * 0x18])
        devices.append({
            "index": index, "va": "0x%08x" % va, "name": DEVICE_NAMES[index],
            "descriptor_words": ["0x%08x" % word for word in words],
            "init": init_device_owner.get(va),
            "pm_field_present": True,
        })

    isr_data = extract.read(0x87DA0, 69 * 8)
    isrs = []
    for irq in range(69):
        argument, function = struct.unpack("<II", isr_data[irq * 8:(irq + 1) * 8])
        default = argument == 0 and function == 0x80763
        if not default:
            isrs.append({"irq": irq, "argument": ptr(argument),
                         "function": ptr(function), "name": ISR_OWNERS.get(irq)})
    if set(ISR_OWNERS) != {row["irq"] for row in isrs}:
        raise ValueError("non-default ISR inventory drift")

    threads = []
    for name, tcb, stack, size, entries, priority, ownership in DYNAMIC_THREADS:
        threads.append({"name": name, "tcb": "0x%08x" % tcb,
                        "stack": "0x%08x" % stack, "stack_size": size,
                        "entry_candidates": ["0x%08x" % entry for entry in entries],
                        "priority": priority, "ownership": ownership,
                        "lifecycle": "runtime_k_thread_create"})
    msgqs = [{"name": name, "object_va": "0x%08x" % va,
              "message_size": size, "max_messages": count,
              "lifecycle": "rom_static_initializer"}
             for name, va, size, count in STATIC_MSGQS]

    return {
        "schema": 1, "core": "app", "generated_by": "tools/build_app_root_inventory.py",
        "image": {"path": "app_update.bin", "sha256": sha((ROOT / "app_update.bin").read_bytes()),
                  "link_base": "0x0000c200", "mcuboot_header_size": 512},
        "vectors": {"start": "0x0000c200", "word_count": 85,
                    "sha256": sha(vector_data), "entries": vectors},
        "init_levels": levels,
        "devices": {"start": "0x00087b30", "count": 26, "stride": 24,
                    "sha256": sha(device_data), "required_kconfig": ["CONFIG_PM_DEVICE"],
                    "entries": devices},
        "sw_isr_table": {"start": "0x00087da0", "count": 69, "stride": 8,
                         "default_function": "0x00080762", "sha256": sha(isr_data),
                         "non_default": isrs},
        "dynamic_threads": threads,
        "static_msgqs": msgqs,
        "gates": {
            "init_level_counts": [17, 1, 28, 2],
            "device_count": 26, "vector_word_count": 85,
            "non_default_isr_count": 11,
            "all_verified_rodata_must_be_live": 993,
            "numeric_function_pointers_forbidden_in_production_roots": True,
            "retain_all_is_audit_only": True,
            "sdc_policy": "report_only",
        },
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    rendered = json.dumps(build(), indent=1, sort_keys=False) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != rendered:
            raise SystemExit("CPUAPP root inventory is stale")
        print("CPUAPP root inventory current")
        return
    OUTPUT.write_text(rendered)
    print("wrote %s" % OUTPUT.relative_to(ROOT))


if __name__ == "__main__":
    main()
