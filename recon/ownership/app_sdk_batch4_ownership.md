# CPUAPP SDK residue batch 4 ownership

Eight pinned NCS 2.5.1/Zephyr 3.4.99 static or header-inline owners are
retained as separately linkable, CFG-verified configured C bodies. Raw identities
remain in each source as address backmaps. Derivative integration is deliberately
left to the centralized batch 3+4 consolidation.

| Symbol | VA | Bytes | Prior refs | Pinned owner | CFG |
|---|---:|---:|---:|---|---|
| `pin_in_use_by_te` | `0x00065460` | 20 | 5 | `modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c:pin_in_use_by_te` | PASS (0+40) |
| `pin_is_output` | `0x00065494` | 20 | 5 | `modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c:pin_is_output` | PASS (0+40) |
| `nrf_gpio_cfg_sense_set` | `0x000851ca` | 30 | 5 | `modules/hal/nordic/nrfx/hal/nrf_gpio.h:nrf_gpio_cfg_sense_set` | PASS (0+40) |
| `net_buf_frags_len` | `0x00081616` | 16 | 5 | `zephyr/include/zephyr/net/buf.h:net_buf_frags_len` | PASS (2+40) |
| `k_uptime_get_6` | `0x0007d33a` | 28 | 5 | `zephyr/include/zephyr/kernel.h:k_uptime_get` | PASS (0+40) |
| `k_uptime_get_8` | `0x0007d382` | 28 | 5 | `zephyr/include/zephyr/kernel.h:k_uptime_get` | PASS (0+40) |
| `k_uptime_get_9` | `0x0007d9a4` | 28 | 5 | `zephyr/include/zephyr/kernel.h:k_uptime_get` | PASS (0+40) |
| `k_uptime_get_10` | `0x0007daa4` | 28 | 5 | `zephyr/include/zephyr/kernel.h:k_uptime_get` | PASS (0+40) |

Canonical result: **8 functions / 40 prior references**, all digest-pinned and CFG-verified.
