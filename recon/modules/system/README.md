# system — Core system services

**Role.** Device lifecycle hub: the work-mode state machine, power management,
watchdog, DFU entry, device-info accessor, factory provisioning (SN / ESB
channel), the global event fan-out, and message-show UI arbitration. It also
exports the shared **timing** (`FUN_00074844`, `FUN_0007cb8e`) and
**buffer/container** helpers (the 0x76xxx–0x78xxx cluster) that other modules
borrow. Almost all cross-module state lives in one `device_info_t` block
(0x18E0 bytes); `get_device_info()` returns its pointer and nearly every other
module reaches state through it.

Boundaries below are graph-derived: **60** functions are called from other
modules (the public API), **17** more are entry-only (thread mains / callbacks),
and the remaining **189** are module-private helpers. The module **defines no
Zephyr kernel objects of its own** — see `wiring.md`.

## Key functions

### Device info & identity / provisioning
- `get_device_info()` @0x167a8 — returns the pointer to the global `device_info_t`.
- `reset_all_static_info(...)` @0x16738 — clears the static/global state block.
- `serialization_init()` @0x25c54 — init of the serialisation/state block.
- `set_glasses_sn_info` @0x31ee8 / `set_device_sn_info` @0x32164 /
  `get_assign_channel_info` @0x31fd8 — factory provisioning of serial numbers and
  the assigned ESB channel (BLE-dispatch callbacks; flash-backed).
- `FUN_00031bd8` / `FUN_00031dd8` / `FUN_00032308` — SN/provisioning field
  read (0x31bd8) and write-with-flash-erase (0x31dd8 / 0x32308).

### Work-mode state machine
- `get_current_work_mode()` @0x16940 — read `device_info_t.work_mode`.
- `change_work_mode_to(mode)` @0x1694c — transition work mode; can enter ship mode.
- `check_work_mode(a,b,c)` @0x27758 — evaluates charge/wear/box events and drives
  mode (`EVENT_ENTER_WARED`, `EVENT_GLASS_BOX_*`, `EVENT_GLASS_HAS_FINISH_BIND`,
  `MODE_CHARGING_LOW_POWER_ID`).
- Substate accessors: `FUN_00033c5c` (box/bind read), `FUN_00033cdc`,
  `FUN_00033cf8`, `FUN_0003439c` (apply/notify), `FUN_0003441c`, `FUN_0003443c`
  (reset), `FUN_00033b0c` (log), `FUN_0002c324` (post-charge/box settle+rebind).
- `FUN_00018300` — event handler: on code 0x1f2 forces `change_work_mode_to(1)`.

### Power
- `global_system_suspend(...)` @0x2bd7c / `global_system_resume(...)` @0x16854 —
  full suspend/resume.
- `try_enter_low_power_mode()` @0x26c8c — gates sleep on charger Vdc + battery,
  then spins into the sleep path (`FUN_0002aeb4`).
- `switch_to_dfu_mode(arg)` @0x158bc — sets `dfu_soc_flag_1=0x83`,
  `dfu_soc_flag_2=1` and reboots into DFU.

### Reliability (watchdog) — see wiring.md
- `init_watchdog(...)` @0x2ace0 — installs the hardware WDT (device @0x87cc8),
  storing the channel handle at 0x20007b50, then feeds it 5×.
- `FUN_0002ae84` @0x2ae84 — periodic **WDT feed** (feed-op retry via the handle);
  called each iteration of the main system thread.
- `FUN_0001793c` @0x1793c — task-watchdog keepalive hook (pets `device_info+0xb0`).
- `process_pt_data(cmd)` @0x330ec — production-test / control command handler;
  several commands force a reboot (`PTP_DEVICE_RESTART`).

### Events & UI arbitration
- `send_event(type,a,b)` @0x276ec — global event fan-out to interested subsystems.
- `process_for_message_show(...)` @0x2c714 / `pull_message(...)` @0x342e0 —
  arbitrate which message/notification UI is shown, with stuck-screen recovery.
- `FUN_000362e8` / `FUN_000440ec` / `FUN_000429f8` — status/notification frame
  composition and draw helpers into the display pipeline.

### Persistence & config (flash-backed)
- `FUN_00022834` @0x22834 — read-verify-rewrite a flash settings block (10× retry).
- `FUN_00022b00` @0x22b00 — zero + erase a settings block in flash @0x130000.
- `FUN_00030224` @0x30224 — replay a display/peripheral config-register table
  from 0x8a0a8 (0x58 registers).
- `FUN_0003483c` @0x3483c — settings/NVS key write helper.

### Shared utility surface (exported to other modules)
- **Timing:** `FUN_00074844` @0x74844 (ms uptime/delay), `FUN_0007cb8e` @0x7cb8e
  (sleep-ms).
- **Buffer/container library:** `FUN_00076a94`, `FUN_00076cec`, `FUN_00076d6c`,
  `FUN_00077594`, `FUN_000777f0`, `FUN_00077e70`, `FUN_000785bc`, `FUN_000785c8`,
  `FUN_00078d90` — list/ring/copy ops built on `FUN_00086bc8` (memcpy) etc.
- **`device_info_t` typed accessors** used from the BLE/IPC paths: `FUN_0007c038`,
  `FUN_0007c132`, `FUN_0007c176`, `FUN_0007c1aa`, `FUN_0007c61e`, `FUN_0007ce00`,
  `FUN_0007d14a`, and the mutex-locked `FUN_0007db02`, `FUN_00083bca`, `FUN_00083bf0`.
- `FUN_00019b2c` @0x19b2c — status-word getter (0x20007518); `FUN_0002542c`
  @0x2542c — counter latch (0x20007a34→0x20007a24).
- `reset_usr_setting` @0x22ddc, `get_boot_seconds` @0x4a51c, `nullsub_2`.

## State it owns / structs
- The global `device_info_t` (`device_info.h`): `work_mode`, `dfu_soc_flag_*`,
  `sync_*`, `system_status_*`, `display_*`, SN/MAC/channel fields,
  `wear_detection_mode`, etc.
- Watchdog channel handle @0x20007b50; WDT device @0x87cc8.
- Flash settings/SN block @0x130000; config-register table @0x8a0a8.
- Status word @0x20007518; latch pair @0x20007a34/0x20007a24.

## Entry points (graph-derived)
Thread mains / callbacks with no in-module C caller — invoked by the app-main
orchestrator (via `K_THREAD_DEFINE`) or through registered function pointers:

- **Thread main:** `FUN_00028a1c` @0x28a1c — key/click interaction loop
  (single/double/triple click, long-press/factory), sleeps via `FUN_0007cb8e`.
- **Event / handler callbacks:** `FUN_0001793c`, `FUN_00018300`,
  `check_work_mode` @0x27758, `process_for_message_show` @0x2c714,
  `FUN_0002c2b0`, `FUN_0002c3dc`, `try_enter_low_power_mode` @0x26c8c.
- **Init / one-shot (called only by system-init 0x16eb8 / boot):**
  `reset_all_static_info` @0x16738, `serialization_init` @0x25c54,
  `init_watchdog` @0x2ace0, `FUN_00016110`, `FUN_00025290`, `FUN_000254a0`,
  `FUN_0002560c`, `FUN_0002563c`, `FUN_00026c28`, `FUN_000289b0`,
  `FUN_0002ea78`, `FUN_0002efe4`, `FUN_000250f8`.
- **BLE-dispatch provisioning callbacks:** `set_glasses_sn_info` @0x31ee8,
  `get_assign_channel_info` @0x31fd8, `set_device_sn_info` @0x32164,
  `FUN_00031bd8`, `FUN_00031dd8`.

## Cross-module coupling
- Consumed by every module via `get_device_info()`.
- Hosts the shared timing + buffer/container helpers used firmware-wide.
- Uses `flash_store` for settings/SN persistence, `ipc_core`/`esb_sync` for
  power/language/mode propagation to the net core and slave lens, and drives the
  display pipeline through `device_info_t.display_*` fields and `send_event`.
- Its code runs on threads DEFINED by the app-main module (main system thread
  0x2a8d8, key_event_thread 0x2955c, mode worker 0x2c99c); see `wiring.md`.
