# ancs_notify — RTOS wiring

RTOS objects this module DEFINES, read out of its proven init functions. All
params below are taken verbatim from the PROVEN (300/300 parity) bodies in
`recon/verified/src/` and `recon/named/`. Zephyr primitive wrappers are the
`FUN_*` thunks noted per line.

## Message queue — g_ancs_msgq @ 0x20006a6c

Defined in `init_msgq_ancs` @ **0x18b6c**:

```
FUN_00086448(0x20006a6c, 0x1b4, 10);   // k_msgq_init(&g_ancs_msgq, msg_size=436, max_msgs=10)
```

Equivalent to `K_MSGQ_DEFINE(g_ancs_msgq, 436, 10, /*align*/4)`.

- msgq control block / buffer base: **0x20006a6c**
- message size: **0x1b4 = 436 bytes** (one full parsed-notification record)
- depth / max_msgs: **10**
- `FUN_00086448` = `k_msgq_init` wrapper.

Confirmed by the queue ends:
- `enqueue_ancs` @ 0x18bb4 — zeroes a 436-byte stack buf, and when the queue is
  full (`*(0x20006a6c+0x24) == 10`) drops the oldest via `k_msgq_get`, then
  `memcpy(buf, src, 0x1b4)` and `k_msgq_put(0x20006a6c, buf, 0, 0)`.
- `dequeue_ancs` @ 0x18d94 — `k_msgq_get(0x20006a6c, buf, 0, 0)` then
  `memcpy(out, buf, 0x1b4)`.
- Offsets used: `+0x10` (msgq initialised / buffer_start non-null guard),
  `+0x24` (used_msgs count, compared against 10).

## Worker thread — ancs thread

Defined in `start_ancs_work_thread` @ **0x198cc**:

```
FUN_00071eac(0x20003c50,   // &thread struct  (k_thread)
             0x2001d568,   // stack base
             0x1400,       // stack size = 5120 bytes
             0x19719,      // entry (thumb)  -> thread body ancs_main @ 0x19950
             param_1,      // p1 = ANCS connection handle
             0, 0,         // p2, p3
             0xfffffff5,   // priority = -11  (cooperative)
             0);           // options / delay = 0
```

Equivalent to
`K_THREAD_DEFINE(ancs_thread, 0x1400, ancs_main, conn, NULL, NULL, -11, 0, 0)`
created dynamically (via `k_thread_create` = `FUN_00071eac`).

- thread control block: **0x20003c50**
- stack: **0x2001d568**, size **0x1400 = 5120 bytes**
- entry: **0x19719** (thumb) — the thread body is `ancs_main` @ **0x19950**
- entry arg p1: the ANCS connection handle (`param_1`)
- priority: **-11** (`0xfffffff5`), i.e. cooperative
- options / start-delay: **0**

Guards before creation (in start_ancs_work_thread): only starts when
`get_device_info()[0] == 2` (phone type / iOS) AND `is_battery_critical() != 1`.

Self-restart pattern: the thread body `ancs_main` @ 0x19950 latches the active
connection into `g_ancs_active_conn` @ 0x20006ab8 on entry, runs the ingest
loop, and on normal exit calls `start_ancs_work_thread` (0x198cc) again to
respawn a fresh worker for the next connection.

## Semaphores / mutexes / work items

None are DEFINED in this module's proven init paths. The ANCS ingest loop is
purely msgq-driven (no k_sem/k_mutex/k_work init observed in init_msgq_ancs,
start_ancs_work_thread, or ancs_main). The 0x4d000-0x5a000 spillover cluster
calls lock-like thunks `FUN_0007e2ec` / `FUN_0007e2fa` and a critical-section
helper `FUN_000507d4` (isCurrentModePrivileged/setBasePriority/ISB), but those
objects are not defined here — they belong to the low-level library those
functions are part of, not to the ANCS subsystem.

## Related globals (state owned/latched, not RTOS objects)

- `g_ancs_msgq`        @ 0x20006a6c  — the msgq above
- `g_ancs_active_conn` @ 0x20006ab8  — latched by ancs_main on entry
- `g_ancs_client`      @ 0x20006ae8  — ANCS GATT client ctx (ancs_c_init / request_ancs_attr_ext)
- ancs attr scratch    @ 0x20006aa0 / 0x20006aac  — request_ancs_attr_ext
- `g_log_level`        @ 0x2000230c, `g_log_use_alt_sink` @ 0x20007554  — logging gate (engine-wide)
```
