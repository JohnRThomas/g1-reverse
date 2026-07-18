# ble_proto — RTOS wiring (objects this module DEFINES)

All threads are created dynamically through the module's thread-spawn primitive
`FUN_00071eac` @0x71eac, which is a `k_thread_create` wrapper. Its argument order,
read from the proven body, is:

```
FUN_00071eac(tcb, stack, stack_size, entry, arg0, arg1, arg2, prio, options, ...)
```

`entry` values are Thumb addresses (LSB set); the even function offset is given in
parentheses. Priorities are the raw signed prio argument (Zephyr: negative =
cooperative). All spawns pass `arg0 = param_1` (the caller's mode/config value) and
`arg1 = arg2 = 0`, `options = 0`.

The spawn tree is rooted at the module's own thread `run_main_dispatch_thread`
(`FUN_0002a65c` @0x2a65c), which conditionally invokes the spawner functions below.

## Semaphore

Created by `FUN_00023a54` @0x23a54 via `FUN_00086534` (= `k_sem_init`; returns
`-EINVAL`/0xffffffea on bad params, sets count/limit + wait-q dlists):

| object | addr        | initial | limit |
|--------|-------------|---------|-------|
| sem    | 0x200079e4  | 0       | 0x14 (20) |

Call site: `FUN_00086534(0x200079e4, 0, 0x14)` in `FUN_00023a54` @0x23a54.

## Wait-list / dlist

`run_main_dispatch_thread` @0x2a65c calls `FUN_000864c2` (self-referential
`sys_dlist_init`: `head->next = head->prev = head`) once at startup. The list
object address is passed in a register and is not recoverable from the decompiled
call (`FUN_000864c2()` with lost argument); it is the dispatch wait-queue the
README refers to.

## Threads (k_thread_create via FUN_00071eac)

| # | spawner (addr)            | tcb        | stack      | stack_size    | entry (fn)              | prio       | notes |
|---|---------------------------|------------|------------|---------------|-------------------------|------------|-------|
| 1 | FUN_00023a54 @0x23a54     | 0x20003e38 | 0x20021968 | 0x800  (2048) | 0x23481 (0x23480)       | 0xfffffff4 (-12) | always spawned by main dispatch |
| 2 | FUN_00023a54 @0x23a54     | 0x20003f10 | 0x20022168 | 0x1400 (5120) | 0x23845 (0x23844)       | 0xfffffff5 (-11) | always spawned by main dispatch |
| 3 | FUN_00032fe8 @0x32fe8     | 0x20004870 | 0x20027a68 | 0xc00  (3072) | 0x32421 (0x32420)       | 0xfffffff4 (-12) | spawned when FUN_00032ee4()!=0; guard flag @0x20019ef1 (set 1 after success) |
| 4 | FUN_0003304c @0x3304c     | 0x20004798 | 0x20027668 | 0x400  (1024) | 0x324bd (0x324bc)       | 0xfffffff4 (-12) | spawned when FUN_00032ee4()!=0 |
| 5 | FUN_00047ad0 @0x47ad0     | 0x20004c08 | 0x20028668 | 0x800  (2048) | 0x47c49 (0x47c48)       | 0xfffffff4 (-12) | spawned when mode byte==1; tid stored @0x2000a090; returns 0/-1 on success |
| 6 | FUN_00049638 @0x49638     | 0x20004d18 | 0x20028e68 | 0x1400 (5120) | 0x49091 (0x49090)       | 0xfffffff2 (-14) | spawned when mode byte==1 or ==2; tid stored @0x2000a09c |

`FUN_0007cb66` @0x7cb66 is another thin `FUN_00071eac` wrapper called several times
from `run_main_dispatch_thread`, but its arguments (tcb/stack/entry) are not
present in the decompiled body (`FUN_00071eac()` with lost args) and cannot be
pinned to concrete parameters from the proven code.

## Watchdog

`run_main_dispatch_thread` installs the watchdog via `FUN_0002ace0` @0x2ace0
against the device instance at `0x87cc8` (driver API vtable). `disable_watchdog`
@0x2aeb4 feeds/stops it and tracks channel state at `0x20007b50`. This is a Zephyr
device binding, not a K_* static object.

## Notes for wiring reconstruction
- No `K_THREAD_DEFINE` / `K_MSGQ_DEFINE` static macros are used by this module;
  every thread is a runtime `k_thread_create`. TCBs and stacks are fixed `.bss`
  addresses (listed above), so they can be re-expressed as static definitions.
- Priorities span -14..-11 (all cooperative). Thread #6 (prio -14) is the
  highest-priority worker; threads #1/#3/#4/#5 share prio -12.
- The only classic sync primitive defined here is the single semaphore
  `k_sem_init(0x200079e4, 0, 20)`.

## Stock Bluetooth-host objects reached by this module (not module-owned)

The WS2 kernel-object sweep misclassified several fields of stock Zephyr
Bluetooth globals as standalone application objects. Raw callers and NCS 2.5.1
layouts prove:

- `bt_dev @0x20002000`; `bt_dev.rx_queue @+0x144 = 0x20002144` is a
  `sys_slist_t`, not a slab or delayable work.
- `db_hash.hash[16] @0x20006380`; its real `db_hash.work` is the private
  `k_work_delayable @0x200063a0`.
- `gatt_sc @0x200063f8`; `gatt_sc.work @0x20006418` is the private delayable
  work and `gatt_sc.flags @0x20006448` is one atomic flag word.
- `gatt_delayed_store.work @0x20006350` is the third private GATT delayable
  work.

`bt_gatt_init` (`FUN_0005a954`) initializes those three work fields with raw
handlers `0x00082cb3`, `0x0005b4bd`, and `0x00082fa7`, respectively. Their
storage belongs to stock `subsys/bluetooth/host/gatt.c`; this application module
must not emit duplicate `K_WORK_DELAYABLE_DEFINE`s. See the durable receipt
`recon/ownership/app_kernel_object_gap_resolution.json`.
