# flash_store — RTOS object wiring

RTOS objects this module **defines** (created in its own init/spawn functions),
read out of the proven decompiled bodies. `k_thread_create` is `FUN_00071eac`
(Zephyr `z_impl_k_thread_create`); `k_timer_init` and `z_impl_k_sem_init` are
already symbol-named. Priorities are signed (0xffffffff4 = -12 → cooperative).

## Threads

Defined in **`spawn_flash_ops_and_brightness_threads` @ 0x23a54**
(`recon/named/spawn_flash_ops_and_brightness_threads.c`):

```
k_thread_create(tcb=0x20003e38, stack=0x20021968, stack_size=0x800 (2048),
                entry=0x23481 (flash_ops_thread @0x23480, thumb+1),
                arg1=param_1, arg2=0, arg3=0, prio=0xfffffff4 (-12), opts=0)

k_thread_create(tcb=0x20003f10, stack=0x20022168, stack_size=0x1400 (5120),
                entry=0x23845 (brightness thread @0x23844, thumb+1),
                arg1=param_1, arg2=0, arg3=0, prio=0xfffffff5 (-11), opts=0)
```

- **flash_ops_thread** — the storage worker. tcb 0x20003e38, 2 KB stack
  @0x20021968, prio -12. The second thread (entry 0x23844, 5 KB stack, prio -11)
  is the display-brightness worker; it is spawned by the same init but is not a
  flash_store entity.

Defined in **`FUN_0002201c` @ 0x2201c** (`recon/verified/src_sym/FUN_0002201c.c`,
settings/projector init — a flash_store api member):

```
FUN_000864c2(0x20007574)                 // sys_dlist_init (projector_controller+0xc)
k_timer_init(timer=0x20003d28, expiry_fn=0x19ff0, stop_fn=0)
k_thread_create(tcb=0x20003d60, stack=0x2001e968, stack_size=0x3000 (12288),
                entry=0x21da9 (@0x21da8, thumb+1),
                arg1=param_1, prio=0xfffffff1 (-15), opts=0)
```

## Message queues (store-request queues drained by flash_ops_thread)

`flash_ops_thread` spins over three `k_msgq` objects, testing each queue's
`used_msgs` field (struct offset **+0x24**) via a tiny accessor and calling the
matching handler until empty:

| k_msgq address | used-count accessor | consumer handler | payload |
|---|---|---|---|
| `0x20003890` | `FUN_0002f758` (@0x2f758) | `audioStreamFileManagerHandler` | audio-stream file store |
| `0x20003960` | `FUN_00024678` (@0x24678) | `getQuickNoteBKPQueueCacheData` | QuickNote BKP store |
| `0x20003994` `g_flash_store_cmd_msgq` | `FUN_00023ef8` (@0x23ef8) | `SettingStoreHandler` (@0x23f04) | settings command (4-byte msg, byte[0] = opcode) |

- `SettingStoreHandler` reads with `k_msgq_get(0x20003994, buf, 0, 0)` into a
  4-byte buffer and `switch`es on `buf[0]` (command discriminant).
- No runtime `k_msgq_init` call exists for any of the three → they are
  compile-time `K_MSGQ_DEFINE` objects (buffer/msg_size/max_msgs fixed at build
  time; only the queue struct addresses are recoverable from the binary).

## Mutex

- **`g_ext_flash_mutex` @ 0x20007b54** — initialised in **`ext_flash_api_init`
  @ 0x2e4e8** via `kmutex_dlist_init(0x20007b54)` (k_mutex wait-queue /
  `sys_dlist_init`). Taken/released by `ext_flash_read` (@0x2e398) and
  `ext_flash_write` (@0x2e440) with
  `k_mutex_lock(0x20007b54, prio, K_FOREVER, K_FOREVER)` /
  `k_mutex_unlock(0x20007b54)`.
- `FUN_000723b8` (@0x723b8, LOCK) / `FUN_00072558` (@0x72558, UNLOCK) are the
  shared low-level k_mutex/spinlock primitives that several members
  (`FUN_00017e84`, `FUN_0004b088/0x4b0dc`) use to guard framebuffer/handler-table
  access; the guarded spinlock is `0x2000b474` (see
  `mutex_lock_syscall_handler` @0x72908, called once per flash_ops_thread loop).

## Semaphore

- **@ 0x200079e4** (labelled `g_app_language_msgq` in the export, but it is a
  semaphore) — `z_impl_k_sem_init(0x200079e4, initial=0, limit=0x14 (20))`,
  from `spawn_flash_ops_and_brightness_threads` @0x23a54.

## Timer

- **@ 0x20003d28** — `k_timer_init(0x20003d28, expiry=0x19ff0, stop=0)`, from
  `FUN_0002201c` @0x2201c.
