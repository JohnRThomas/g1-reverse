# misc — cross-module shared runtime (catch-all)

## Responsibility
`misc` is not a feature module. It is the low-level substrate that every real
module reaches into. The topic classifier could not attribute these 181
functions to a feature, but the reference graph shows a consistent character:
**Zephyr kernel-object primitives, ARM MPU config, nrfx/nRF peripheral & sensor
driver init, BLE/settings/SMP glue, and libc/math runtime.** It owns **722**
data objects (constant tables, kernel-object storage, driver state).

Public surface = the graph's `api` set: **55 functions** called from other
modules (declared in `misc.h`). The remaining ~126 are internal — leaf helpers,
jump-table targets, or entry points invoked only through function pointers.

## Key functions (public API, by role)
- **ARM MPU** — `arm_core_mpu_configure` (0x50c54), `mpu_partition_sanity_check_assert`
  (0x50e64): program/verify MPU region partitions.
- **Zephyr driver/timer core** — `driver_register_callback_locked` (0x848d2),
  `driver_stop_active_timer` (0x84c2c, calls `k_timer_stop`), `FUN_00084516`
  (0x84516, µs→ticks scaling via `us_to_ticks_scaled`), `FUN_0008493a`, `FUN_000851f4`.
- **nrfx / nRF peripheral + sensor drivers** — a family that logs via `printk`
  and touches hardware: `FUN_00062930` (`i2c_read_reg16_be` sensor probe),
  `FUN_00062c54` (`pinctrl_apply_state`), `FUN_00067794` (`nrf_gpio_pin_reconfigure`),
  `g1_recon_nrfx_wdt_channel_alloc` (0x67e8c), `FUN_00083778` (`adc_context_start_sampling`),
  plus `FUN_000620cc/639d4/63898/64fa8/65324/65d3c/65d8c/67600`.
- **Display page state** — `set_display_page_index` (0x369dc),
  `advance_display_page_index` (0x369f8).
- **BLE / settings / SMP** — `bt_le_adv_clear_pending_flag` (0x81080),
  `FUN_00052f68` (`bt_settings_store`), `smp_process_request_packet` (0x85cf2, mcumgr).
- **libc / math runtime** — `out` (0x7dd7e, printf/snprintf putc sink),
  `__errno_location` (0x71678), `atan2f` (0x76154).
- **DSP / int16 sample transforms** — `FUN_0006a700`, `FUN_0006aa98`
  (int64 accumulator over int16 strided buffers).
- **buffer/integer helpers** — fills `FUN_000844a8/844e0`, memcpy wrapper
  `FUN_000839fe`, uint16 buffer ops `FUN_0007f894/7faa8/7fae4`, etc.

## Deduced roles of remaining FUN_* (from callers + callees + data)
- The `printk`-fronted, device-handle-taking cluster (0x620cc..0x67794, 0x83778)
  are **driver init / configure / PM** routines for I2C/SPI sensors, GPIO,
  pinctrl, ADC and DPPI — the per-peripheral bring-up code.
- `FUN_0006a700`/`FUN_0006aa98` accumulate over strided `int16_t` sample arrays
  into a 64-bit accumulator → **audio/IMU DSP** (FIR/energy/dot-product).
- `FUN_000839fe`→`memcpy`, `FUN_000844a8/844e0` (dst,val,len) → **block memory
  fill/copy** helpers.
- `FUN_00052d58` takes a `codeptr` argument and `FUN_00060564` takes a jump-table
  pointer → **callback/dispatch registration** helpers.
- Entry-point neighbours (invoked only by pointer) are libc/math: `strtod_*`
  (0xea18/ea4c), `dtoa_get_bias_const` (0x13e50), `__ieee754_scalbn` (0x13e60),
  `crc32_table_init` (0x235dc), `fast_inverse_sqrt` (0x265e8), `orientation_*`
  (0x267ac/267e8/26808), `spi_master_install_ops` (0x2659c),
  `device_info_*` (0x165cc/0x23230).

## Owned data / structs
722 data objects. Notable named globals backing the RTOS objects (see
`wiring.md`): `g_debug_msg_pipe` (0x2000751c), `g_file_msg_pipe` (0x200079a0),
`g_some_module_sem` (0x20007b1c) + its init flag `g_some_module_init_done_flag`
(0x20018d8a). No single unifying struct or dispatch table — the group is a
union of independent runtime facilities.

## Entry points (no in-module caller — invoked via pointer / at init)
Thread/callback/init entries the graph flags for `misc`:
- **RTOS-object init**: `debug_log_queue_init` (0x19bd0), `file_subsystem_queue_init`
  (0x234e8), `some_module_sem_init` (0x2953c) — see `wiring.md`.
- **libc/math leaves**: `strtod_scan_int_prefix` (0xea18),
  `strtod_has_more_digits` (0xea4c), `dtoa_get_bias_const` (0x13e50),
  `__ieee754_scalbn` (0x13e60), `crc32_table_init` (0x235dc),
  `fast_inverse_sqrt` (0x265e8).
- **device / sensor**: `device_info_copy_record_fields` (0x165cc),
  `device_info_register_persistent_fields` (0x23230),
  `spi_master_install_ops` (0x2659c), `orientation_filter_update_dt` (0x267ac),
  `orientation_get_yaw_deg` (0x267e8), `orientation_get_pitch_deg` (0x26808).
- **timing**: `get_elapsed_ms_since_mark` (0x24d2c), `set_time_mark` (0x24d40),
  `arm_timeout_10s` (0x32c0c).
- Unclassified proven entries: 0x16580, 0x1658c, 0x165a4, 0x23eec, 0x269fc,
  0x2a4c0, 0x2c214, 0x2e8fc, 0x30c24, 0x32808, 0x33bc4.

## Guidance
Do not build features on top of `misc` — it has no stable feature surface. When
a function here is identified, name it in `recon/named/`, move its prototype into
the owning module's `.h` + README, and drop it from this bucket.
