# CPUAPP SDK residue batch 5 ownership

Eight pinned NCS 2.5.1/Zephyr 3.4.99 configured owners are retained as
separately linkable, CFG-verified C. `FUN_00066e70` is identified as
`pin_init`; its raw public identity remains the reversible address backmap.

| Symbol | VA | Bytes | Prior refs | Pinned owner | CFG |
|---|---:|---:|---:|---|---|
| `gatt_discover_next` | `0x00082d2e` | 60 | 5 | `zephyr/subsys/bluetooth/host/gatt.c:gatt_discover_next` | PASS (42 checked) |
| `flash_settings_write_and_verify` | `0x00022658` | 332 | 5 | `firmware application settings-flash owner` | PASS (40 checked) |
| `bt_addr_le_eq` | `0x00080fa4` | 16 | 5 | `zephyr/include/zephyr/bluetooth/addr.h:bt_addr_le_eq` | PASS (40 checked) |
| `atomic_clear_bit_1` | `0x0008304c` | 22 | 5 | `zephyr/include/zephyr/sys/atomic.h:atomic_clear_bit` | PASS (40 checked) |
| `atomic_and_3` | `0x00080ea8` | 16 | 5 | `zephyr/include/zephyr/sys/atomic_builtin.h:atomic_and` | PASS (40 checked) |
| `atomic_and` | `0x0007c08e` | 22 | 5 | `zephyr/include/zephyr/sys/atomic_builtin.h:atomic_and` | PASS (40 checked) |
| `FUN_00066e70` | `0x00066e70` | 76 | 5 | `modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c:pin_init` | PASS (43 checked) |
| `qspi_nor_write_protection_set` | `0x00083954` | 42 | 4 | `zephyr/drivers/flash/nrf_qspi_nor.c:qspi_nor_write_protection_set` | PASS (40 checked) |

Canonical result: **8 functions / 39 prior references**, all digest-pinned and CFG-verified.
