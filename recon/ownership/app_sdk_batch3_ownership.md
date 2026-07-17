# CPUAPP SDK residue batch 3 ownership

These eight firmware identities retain CFG-verified configured C bodies.
The seven SDK-derived helpers are private/static or outlined header inlines;
`flash_settings_read` is application code and is explicitly reclassified.

| Symbol | VA | Bytes | Prior refs | Pinned owner | Decision |
|---|---:|---:|---:|---|---|
| `flash_settings_read` | `0x000225b4` | 150 | 7 | `G1 application flash-settings wrapper` | `retain_cfg_verified_configured_reconstruction` |
| `atomic_or` | `0x00080e6a` | 22 | 7 | `zephyr/include/zephyr/sys/atomic_builtin.h:atomic_or` | `retain_cfg_verified_configured_reconstruction` |
| `atomic_and_2` | `0x000813b4` | 22 | 7 | `zephyr/include/zephyr/sys/atomic_builtin.h:atomic_and` | `retain_cfg_verified_configured_reconstruction` |
| `atomic_or_0` | `0x000826e0` | 22 | 6 | `zephyr/include/zephyr/sys/atomic_builtin.h:atomic_or` | `retain_cfg_verified_configured_reconstruction` |
| `qspi_get_zephyr_ret_code` | `0x00060990` | 24 | 6 | `zephyr/drivers/flash/nrf_qspi_nor.c:qspi_get_zephyr_ret_code` | `retain_cfg_verified_configured_reconstruction` |
| `spim_pin_uninit` | `0x00067138` | 146 | 5 | `modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c:spim_pin_uninit` | `retain_cfg_verified_configured_reconstruction` |
| `qspi_activate` | `0x000664f0` | 40 | 5 | `modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c:qspi_activate` | `retain_cfg_verified_configured_reconstruction` |
| `print_formatted` | `0x0004da6c` | 30 | 5 | `zephyr/subsys/logging/log_output.c:print_formatted` | `retain_cfg_verified_configured_reconstruction` |

Coverage: **8 functions / 48 prior references**. Shared readable and link derivatives are intentionally left to centralized batch consolidation.
