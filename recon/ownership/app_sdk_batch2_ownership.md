# CPUAPP SDK residue batch 2 ownership

All five configured bodies are retained reconstructions of pinned NCS 2.5.1
static or header-inline owners. Each body is digest-pinned and CFG-verified;
the catalog generator fails on source or verified-mirror drift.

| Symbol | VA | Bytes | Prior refs | Pinned owner | Decision |
|---|---:|---:|---:|---|---|
| `bt_addr_le_eq_0` | `0x000826b2` | 16 | 10 | `zephyr/include/zephyr/bluetooth/addr.h:bt_addr_le_eq` | `retain_cfg_verified_configured_reconstruction` |
| `get_pin_idx` | `0x00065434` | 16 | 10 | `modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c:get_pin_idx` | `retain_cfg_verified_configured_reconstruction` |
| `__nrfy_internal_twim_events_process` | `0x0008539a` | 84 | 9 | `modules/hal/nordic/nrfx/haly/nrfy_twim.h:__nrfy_internal_twim_events_process` | `retain_cfg_verified_configured_reconstruction` |
| `k_uptime_get_1` | `0x0007cb2c` | 28 | 9 | `zephyr/include/zephyr/kernel.h:k_uptime_get` | `retain_cfg_verified_configured_reconstruction` |
| `smp_create_pdu` | `0x000830b0` | 62 | 8 | `zephyr/subsys/bluetooth/host/smp.c:smp_create_pdu` | `retain_cfg_verified_configured_reconstruction` |

Configured dependency:

- `__nrfy_internal_twim_event_handle` at `0x00085378` (34 bytes): `modules/hal/nordic/nrfx/haly/nrfy_twim.h:__nrfy_internal_twim_event_handle`; `retain_cfg_verified_configured_dependency`.

Retain-all result: **46 -> 0** target references; one strong owner per target, no target duplicates.
