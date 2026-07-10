# quicknote — RTOS wiring

Read out of the module's proven bodies (recon/named, recon/verified). Addresses
are app-core flash offsets (link base 0xC200).

## RTOS objects this module DEFINES

**None.** None of the six functions in the quicknote unit contains a
`k_msgq_init` / `k_sem_init` / `k_mutex_init` / `k_thread_create` /
`K_THREAD_DEFINE` / `k_work_*` call. The module owns no thread, queue, sem,
mutex or work item of its own — it is a *user* of objects defined elsewhere,
and `ui_QuickNote_task` is a per-frame handler dispatched by the UI task
(`FUN_00048b5c`), not a standalone `K_THREAD_DEFINE` entry.

## RTOS objects this module USES (defined elsewhere — inputs to wiring)

### `g_quicknote_flash_msgq`  @0x20003960  (message queue)
The QuickNote-flash command queue. **msg_size = 12 bytes** (a 3×u32 message);
element **count is set at its definition site in `flash_store`** (no runtime
`k_msgq_init` for 0x20003960 exists in recon/named or recon/verified — it is a
compile-time `K_MSGQ_DEFINE`, so no init call to read params from here).

Message layout (from `deleteQuickNoteData` @0x244a8):
```
word0  cmd tag     (delete = 0x00010002)
word1  note_num    (byte, zero-extended)
word2  param       (audio-file selector / arg)
```

Endpoints:
- **Producer** `deleteQuickNoteData` @0x244a8 (this module):
  `k_msgq_put(0x20003960, buf, 0, 0)`.
- **Consumer** `getQuickNoteBKPQueueCacheData` @0x24684 (this module):
  `k_msgq_get(0x20003960, &slot, 0, 0)` into a 12-byte slot.
- Other endpoints in **flash_store**: `upgradeQuickNoteDataToFlash` (put),
  `drain_quick_note_data_queue` (get), `FUN_00024678`.

### `g_app_language_msgq`  @0x200079e4  (semaphore)
Signalled by `deleteQuickNoteData` @0x244a8 after a successful enqueue, via
`FUN_00072880(0x200079e4)` (a `k_sem_give`-style wrapper). **Defined in
`system`** — `spawn_flash_ops_and_brightness_threads` does
`z_impl_k_sem_init(0x200079e4, 0, 0x14)` (initial 0, limit 0x14). Used here only
to wake the flash-ops worker; not owned by quicknote.

## Notes for wiring reconstruction
- Wire a producer edge quicknote → `g_quicknote_flash_msgq` (delete commands)
  and a consumer edge quicknote ← `g_quicknote_flash_msgq` (backup-queue cache
  reads); the persistence worker on the far side lives in `flash_store`.
- Wire a signal edge quicknote → `g_app_language_msgq` sem (@0x200079e4).
- No thread/timer/work is contributed by this module.
