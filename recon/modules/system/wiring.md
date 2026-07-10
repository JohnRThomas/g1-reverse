# system — RTOS wiring

Input to the whole-firmware wiring reconstruction. Everything below is read out
of the module's own *proven* function bodies (recon/verified/src, recon/named)
and cross-checked against the reference graph (refgraph_app.json). Addresses are
app-core flash offsets (link base 0xC200).

## Summary: this module defines NO classic Zephyr kernel objects

Graph fact (checked mechanically over all 266 functions in the `system` topic
group): **not one** of them calls any of
`k_msgq_init` (0x86420), `z_impl_k_sem_init` (0x86534), `k_mutex_init`,
`k_work_init` (0x72e50), `k_work_queue_init/start` (0x730b4/0x730e8),
`k_timer_init` (0x86726), or `k_thread_create/z_impl_k_thread_create`.

So the system module declares no `K_MSGQ_DEFINE`, `K_SEM_DEFINE`,
`K_MUTEX_DEFINE`, `K_WORK*`, `K_TIMER_DEFINE`, or `K_THREAD_DEFINE` of its own.
Its code runs on threads owned by the **app-main orchestrator** module (the
neighbouring group that contains the thread mains), and it reaches shared state
through the single `device_info_t` block rather than through kernel queues.

The one kernel-adjacent object the module DOES own is the **hardware watchdog**.

## Watchdog (WDT) — the module's one owned kernel/driver object

- **Install / setup:** `init_watchdog` @0x2ace0
  (recon/verified/src/FUN_0002ace0.c). Uses the WDT device instance whose
  `struct device` lives at **0x00087cc8**. It:
  1. checks the driver is ready via `FUN_0008638c(0x87cc8)` (device-ready),
  2. zeroes a 0x10-byte `wdt_timeout_cfg` on the stack,
  3. calls the driver `install_timeout` op (op table `dev->api`, slot `+8`) to
     register a timeout channel; the returned **channel id is stored at
     0x20007b50** (`*piVar4 = iVar5`); a `-0x86` (`-EBUSY`) result is retried
     once,
  4. calls the `setup` op (slot `+0`, mode arg `2`) to start the watchdog,
  5. feeds the channel 5× (`feed` op, slot `+0xc`) with `FUN_00074844(0x667,0)`
     delays between feeds.
  The generic driver-side install helper is `FUN_00063984` @0x63984
  (writes the WDT CRV/CONFIG registers via `FUN_00083e70` / `FUN_00083dc8`).

- **Feed:** `FUN_0002ae84` @0x2ae84 (recon/verified/src/FUN_0002ae84.c).
  Reads the channel id from **0x20007b50**, calls the driver `feed` op
  (`dev->api` slot `+0xc`) on device 0x87cc8, retrying up to 5× with
  `FUN_00074844(0x667,0)` back-off. Called from the main system thread
  (0x2a8d8, app-main group) once per loop — this is the periodic WDT pet.

- **Related keepalive:** `FUN_0001793c` @0x1793c pets a task-watchdog channel at
  `device_info + 0xb0` when its arg is 0x200 (a subsystem heartbeat hook).

## Thread entry points owned/hosted by this module

These are the thread *mains* / callbacks that have no in-module C caller
(they are wired by the app-main orchestrator via `K_THREAD_DEFINE`, or invoked
through registered function pointers). The `system` module owns one thread main
outright and provides the bodies that several neighbouring thread mains drive:

- **`FUN_00028a1c` @0x28a1c** — THREAD MAIN (in `system`). Infinite key/click
  interaction loop: polls `FUN_00032fdc`, dispatches single-click
  (`FUN_0002893c`), double, triple (`on_triple_click`), and long-press / factory
  paths, sleeping with `FUN_0007cb8e(5000)` / `FUN_0007cb8e(500)`.
- **Entry callbacks (no in-module caller):** `FUN_0001793c`, `FUN_00018300`
  (event handlers), `FUN_00031bd8`, `FUN_00031dd8`, `set_glasses_sn_info`
  @0x31ee8, `get_assign_channel_info` @0x31fd8, `set_device_sn_info` @0x32164
  (BLE/dispatch-table provisioning callbacks, reached via function pointers).

Neighbouring thread mains (app-main group, `in_system=False`) that call almost
exclusively into this module — listed so the wiring pass can attribute them:
- `FUN_0002a8d8` — main system/state thread: drives `check_work_mode`,
  `try_enter_low_power_mode`, `FUN_0002ae84` (WDT feed), `change_work_mode_to`.
- `key_event_thread` @0x2955c — key/event thread: drives `FUN_0002c3dc`,
  work-mode substate accessors (0x33cdc/0x3441c/0x3443c).
- `FUN_0002c99c` — mode/state worker: drives `process_for_message_show`,
  `FUN_0002c2b0`, substate accessors.
- `FUN_00016eb8` — system init (no callers): calls `serialization_init`,
  `switch_to_dfu_mode`, `FUN_00025290`, `FUN_0002ea78`, `FUN_00030c90`,
  `FUN_0002a65c` → `init_watchdog`.

## Timing / delay primitives this module exports (not kernel objects)

Widely shared by other modules; documented here because they are the module's
"scheduling surface":
- `FUN_00074844` @0x74844 — ms uptime read + delay (ticks→ms via
  `(ticks*1000)>>15`); ISR-safe branch. The canonical busy/delay helper.
- `FUN_0007cb8e` @0x7cb8e — sleep-ms wrapper (calls the 0x74844 path).

## Persistent-state backing (not RTOS, but wiring-relevant)

- Settings/SN block in flash at **0x130000**, reset by `FUN_00022b00` @0x22b00
  (zero + program 0x78/0x84 bytes) and read/verify/rewritten by `FUN_00022834`
  @0x22834 (10× retry). Config-register table replay from **0x0008a0a8**
  (0x58 entries) by `FUN_00030224` @0x30224.
- All cross-module runtime state: the single `device_info_t` at the pointer
  returned by `get_device_info` @0x167a8; watchdog channel id at 0x20007b50;
  status word at 0x20007518; latch pair 0x20007a34→0x20007a24.
