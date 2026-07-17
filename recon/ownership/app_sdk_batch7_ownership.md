# CPUAPP SDK residue batch 7 ownership

Eight configured owners are retained as separately linkable, CFG-verified C.
The evidence corrects the ATT classifier extent, models the GATT encode callback,
and covers six production-shaped Bluetooth-start states.

| Symbol | VA | Bytes | Prior refs | Pinned owner | CFG |
|---|---:|---:|---:|---|---|
| `atomic_and_0` | `0x0007f3f0` | 22 | 3 | `zephyr/include/zephyr/sys/atomic_builtin.h:atomic_and` | PASS (40) |
| `atomic_and_1` | `0x00081180` | 22 | 3 | `zephyr/include/zephyr/sys/atomic_builtin.h:atomic_and` | PASS (40) |
| `atomic_clear_bit` | `0x0007f5d8` | 22 | 3 | `zephyr/include/zephyr/sys/atomic.h:atomic_clear_bit` | PASS (40) |
| `atomic_clear_bit_0` | `0x00081e14` | 22 | 3 | `zephyr/include/zephyr/sys/atomic.h:atomic_clear_bit` | PASS (40) |
| `atomic_test_and_set_bit_0` | `0x00082236` | 34 | 3 | `zephyr/include/zephyr/sys/atomic.h:atomic_test_and_set_bit` | PASS (40) |
| `att_op_get_type` | `0x000582b8` | 108 | 3 | `zephyr/subsys/bluetooth/host/att.c:att_op_get_type` | PASS (46) |
| `bt_start` | `0x00019308` | 766 | 3 | `firmware application Bluetooth-start owner` | PASS (6) |
| `gatt_req_send` | `0x00082aee` | 128 | 3 | `zephyr/subsys/bluetooth/host/gatt.c:gatt_req_send` | PASS (40) |

Canonical result: **8 functions / 24 prior references**, digest-pinned and CFG-verified.
