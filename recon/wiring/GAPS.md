# Wiring GAPS — WS2 inventory audit and resolved false positives

The WS2 inventory (`ws2_reliable.json`) was produced by grouping SRAM references
and guessing a type from span/caller shape. It is useful as a chase list, but it
is **not** type evidence. Every one of its eight classic-kernel-object candidates
has now been checked against raw Thumb disassembly, the reference graph, the
CFG-verified reconstruction, and (where applicable) the exact NCS 2.5.1 stock
owner. All eight guesses are false positives.

The machine-readable evidence receipt is
`recon/ownership/app_kernel_object_gap_resolution.json`; its fail-closed test is
`tools/test_app_kernel_object_gap_resolution.py`.

## Resolved priority candidates

| address | WS2 guess | proven object / field | owner and decisive evidence |
|---|---|---|---|
| `0x20004df0` | `k_work` | two 64-bit clock baselines | Application dashboard/clock state. `record_dashboard_startup_snapshot` (`FUN_0004a4b4`) writes caller time at `+0/+4` and current uptime at `+8/+12`; `FUN_0004a4d0` reads both pairs to compute synchronized time. |
| `0x20002c30` | `k_work` | `nrfx_atomic_t available_channels_mask` | Stock nrfx GPIOTE `m_cb+0x70`. `FUN_000659cc/d8` are the exact `nrfx_gpiote_channel_free/alloc` wrappers and pass this word to `nrfx_flag32_free/alloc`. |
| `0x20006448` | `k_work` | `atomic_t gatt_sc.flags[1]` | Stock Zephyr Bluetooth `gatt.c`. `gatt_sc` is based at `0x200063f8`; its actual delayable work is at `+0x20 = 0x20006418`, while its flags are at `+0x50 = 0x20006448`. Raw `bt_gatt_init` initializes the former and performs `atomic_set_bit` on the latter. |
| `0x20009fc0` | `k_work` | `uint32_t last_uptime_ms` | Application elapsed-time state. `FUN_0003629c` reads/writes exactly one 32-bit converted-uptime value. WS2's second cited function `FUN_00047ab8` actually references the distinct pointer at `0x20009fcc`. |
| `0x2000cc24` | `k_work` | `int errno` | Stock C-library syscall/reentrancy glue. `_write_r`, `_sbrk_r`, `_isatty_r`, `_fstat_r`, and the four cited wrappers clear/read this error word around a syscall. |
| `0x20002144` | `k_work_delayable` | `sys_slist_t bt_dev.rx_queue` | Stock Zephyr Bluetooth `hci_core.c`; it is `bt_dev @0x20002000 + 0x144`. Producers/consumer call `net_buf_slist_put/get`. The separately submitted receive work is at `0x20002980`. |
| `0x20006380` | `k_mutex` | `uint8_t db_hash.hash[16]`, base of `struct db_hash` | Stock Zephyr Bluetooth `gatt.c`. `bt_gatt_store_hash` persists exactly 16 bytes from this address and `gatt_db_hash_gen` writes and byte-swaps a 16-byte CMAC there. Its actual delayable work is at `+0x20 = 0x200063a0`. |
| `0x20002000` | `k_mem_slab` | `struct bt_dev` | Stock Zephyr Bluetooth `hci_core.c`. Identity count/table, controller state, flags, and nested queues are accessed throughout this block; `rx_queue` is the field at `+0x144`. No slab API receives this address. |

Therefore none of these addresses may receive `K_WORK_DEFINE`,
`K_WORK_DELAYABLE_DEFINE`, `K_MUTEX_DEFINE`, or `K_MEM_SLAB_DEFINE` storage.
Doing so would overlap real stock/application state and corrupt the reconstructed
layout.

## Real work objects exposed by the audit

Raw `bt_gatt_init` (`FUN_0005a954 @0x0005a954`) proves three private, stock
`subsys/bluetooth/host/gatt.c` delayable works:

| address | containing stock field | handler (Thumb address) | initialization |
|---|---|---|---|
| `0x20006350` | `gatt_delayed_store.work` | `delayed_store @0x00082fa7` | `k_work_init_delayable` |
| `0x200063a0` | `db_hash.work` | `db_hash_process @0x00082cb3` | `k_work_init_delayable`, then initial schedule at 328 ticks |
| `0x20006418` | `gatt_sc.work` | `sc_process @0x0005b4bd` | `k_work_init_delayable` |

These are members of stock-private structs, not application-owned standalone
objects. The stock GATT translation unit supplies their storage and init; adding
parallel `K_WORK_DELAYABLE_DEFINE`s to `app_objects.c` would duplicate them.

The earlier `FUN_0005a954.c` reconstruction had incorrect literal assignments
that shifted these three init operands. It is now corrected to the raw literal
pool (`0x200063a0`, `0x20006418`, `0x20006350`) and CFG side-effect verification
passes.

## Other WS2 entries

The non-classic candidates remain driver/transport structures rather than
application `K_*_DEFINE` gaps: `0x20002bac` (`gpio_driver_api` guess),
`0x2000ad1c` (`log_backend_api`), `0x20002404` and `0x200037f0`
(`virtio_dispatch`), `0x2000253c` (`write_data`), `0x20004948`
(`spi_nrfx_config`), `0x20003868` (`spi_context`), `0x2000ab7c`
(`virtqueue`), and `0x20004ce0` (`pwm_nrfx_config`). They are not grounds for
emitting application kernel-object definitions.

One useful independent correction remains: WS2 typed `0x20003d28` as PWM
configuration, but raw `FUN_0002201c` passes it to `k_timer_init` with expiry
handler `0x00019ff0`. `app_objects.c` correctly records it as
`g_projector_timer`.

## Inventory coverage warning

WS2 misses most already-proven objects, including the nine message queues, two
standalone semaphores, external-flash mutex, projector timer, and reconstructed
thread TCBs in `app_objects.c`. Absence from WS2 is not evidence of absence in
the binary. Kernel-object wiring must continue to be derived from init calls,
field-level API use, raw literal values, and exact stock-owner layouts.
