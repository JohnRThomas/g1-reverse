# flash_store — Persistent settings & user-data store

**Role.** Owns everything that survives a reboot: system settings, user settings,
per-app language info, QuickNote text/audio records, and the analytics
"burial-point" blob — plus the low-level external SPI-flash driver and CRC
integrity checking. All writes are serialised through a single worker thread
(`flash_ops_thread`) so concurrent producers never corrupt a sector.

The public/internal split in `flash_store.h` is authoritative from the Ghidra
reference graph: **41 functions are the real cross-module API** (called from
other modules); the rest are entry points (boot init, msgq handlers) or
module-private helpers.

## Key functions (name — role)

### Worker + dispatch
- `flash_ops_thread` (@0x23480) — **the storage thread**. Infinite loop that
  locks a global spinlock then drains three `k_msgq` store queues until empty
  (audio-file → QuickNote → settings). See `wiring.md`.
- `SettingStoreHandler` (@0x23f04) — settings msgq consumer; read-modify-verify
  (erase, write, read-back compare, skip when unchanged). Called only by the
  thread (entry point, not API).
- `try_to_save_file` (@0x23634) — file-save worker step; writes font/file payload
  with verify and updates the CRC-32 (`crc32_update`).

### CRC / integrity
- `FUN_0002360c` = **`crc32_update`** (@0x2360c) — table-driven CRC-32 over a
  payload (table in `device_info.projector_controller+56`). Public (used by
  `try_to_save_file` and the audio module). **[API]**
- `calc_flash_crc` (@0x22974) — CRC-16 over a settings blob. Internal.

### Producers (enqueue) / readers
- `read_sys_settting_from_flash` (@0x232f8) **[API]** — load system settings to
  RAM (`<- display, system`).
- `FUN_00032254` (@0x32254) **[API]** — user-setting load helper (wraps
  `read_usr_settting_from_flash` + `get_device_info`).
- `FUN_0002eaa8` (@0x2eaa8) **[API]** — flash-status query (`<- system`).
- `getQuickNoteDataFromFlash` (@0x24534) **[API]** — QuickNote read (`<- dashboard`).
- `update_burial_point_to_flash`, `upgradeAppLanguageInfoToFlash`,
  `getAppLanguageInfofromFlash`, `upgradeQuickNoteDataToFlash`,
  `read_usr_settting_from_flash` — entry points / internal (no direct
  cross-module caller in the graph; reached via dispatch or boot).

### External SPI-flash driver
- `ext_flash_read` (@0x2e398) / `ext_flash_write` (@0x2e440) **[API]** —
  driver primitives, both take `g_ext_flash_mutex` (0x20007b54).
- `ext_flash_api_init` (@0x2e4e8) — driver init (mutex + `device_is_ready`,
  installs read/write/erase fn pointers). Entry point.
- `get_flash_info` (@0x32628) / `is_ext_flash_burned` (@0x32c28) **[API]** —
  flash identity / provisioning check.

### Persist-task state machine (a save survives power transitions)
- `update_persist_task_status` (@0x2bef4) **[API]** (`<- ble_proto, esb_sync, onboarding`)
- `update_persist_task_status_to_idle` (@0x2c0e8) **[API]** (`<- ancs, battery, quicknote, system`)
- `update_persist_task_status_to_wait_blow_head` (@0x2c180) **[API]** (`<- ancs`)
- `FUN_0007cdf8` (@0x7cdf8) **[API]** — persist-task notify wrapper
  (`FUN_00074844(0x21,0)`); called by all of the above plus battery/ancs.
- `now_has_persist_task` (@0x2be64) — internal predicate.

### Targeted writes
- `set_imu_pitch_reflash` (@0x469bc) **[API]** (`<- imu_motion`).
- `update_not_disturb_settings` (@0x3cb4c) — internal DND write.

### Init
- `sett_init` (@0x22518) — Zephyr settings subsys init + register. Entry point.
- `spawn_flash_ops_and_brightness_threads` (@0x23a54) — defines the worker
  thread(s) + a semaphore (see `wiring.md`). Entry point.
- `FUN_0002201c` (@0x2201c) **[API]** — settings/projector init: `sys_dlist_init`
  + `k_timer_init(0x20003d28)` + spawns a worker thread (entry 0x21da8, prio -15).

## Deduced FUN_ roles (previously unlabelled)
- `FUN_0002360c` → **crc32_update** (CRC-32).
- `FUN_00023ef8` / `FUN_00024678` / `FUN_0002f758` → **store-queue used-msgs
  accessors** for the settings (0x20003994), QuickNote (0x20003960) and
  audio-file (0x20003890) msgqs — read the `k_msgq.used_msgs` field (+0x24).
- `FUN_000723b8` / `FUN_00072558` → **k_mutex/spinlock LOCK / UNLOCK** primitives.
- `FUN_000864c2` → **sys_dlist_init** (self-referential list node init).
- `FUN_0004b088` / `FUN_0004b0dc` → **locked handler-table dispatch** (table at
  0x20002548, stride 0x28), guarded by the mutex lock/unlock pair; called by gui_text.
- `FUN_00017e84` → **battery/state-guarded flash write** (takes lock 0x20006a1c,
  calls `FUN_0004f518`, aborts when battery critical).
- `FUN_0002201c` → settings/projector **init** (timer + thread + dlist).
- Note: many high-address API members (0x723b8, 0x72558, 0x864c2, 0x4c548, ...)
  are shared kernel/library primitives that clustered here because
  `ext_flash_read/write` and the settings path reach them — they are exported
  helpers, not flash-specific logic.

## State it owns / structs
- On-flash layout: system-settings region, user-settings region, app-language
  table, QuickNote record area, 192-byte burial-point blob.
- Three store-request `k_msgq` objects (0x20003890 audio-file, 0x20003960
  QuickNote, 0x20003994 `g_flash_store_cmd_msgq` settings) — compile-time
  `K_MSGQ_DEFINE`, drained by `flash_ops_thread`.
- `g_ext_flash_mutex` @0x20007b54, `g_ext_flash_dev` @0x20007b68.
- Persist-task status (via `device_info_t.task_status_ptr`).
- In-RAM mirrors are `device_info_t` fields (`settings_save_*`,
  `buried_point_data[192]`, language/QuickNote caches).

## Entry points
- **Threads:** `flash_ops_thread` (@0x23480) — the storage worker; a projector
  worker (entry 0x21da8) spawned by `FUN_0002201c`.
- **Boot init:** `sett_init`, `ext_flash_api_init`,
  `spawn_flash_ops_and_brightness_threads`, `FUN_0002201c`.
- **Msgq handlers:** `SettingStoreHandler`, `audioStreamFileManagerHandler`,
  `getQuickNoteBKPQueueCacheData` (dispatched by the thread).
- **Enqueue API:** `upgrade*ToFlash` / `update_burial_point_to_flash` /
  `try_to_save_file`.
- **Read API:** `read_sys_settting_from_flash`, `FUN_00032254`,
  `getQuickNoteDataFromFlash`, `getAppLanguageInfofromFlash`.

## Cross-module coupling
- Backing store for `analytics`, `translate` (language), `quicknote`, `system`
  (settings, SN/channel), `display`/`gui_text` (framebuffer via the shared mutex
  + ext-flash driver), and DND (`esb_sync` syncs the value, `flash_store`
  persists it).
