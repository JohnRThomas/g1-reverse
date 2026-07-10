# gui_text — RTOS wiring

## RTOS objects DEFINED by this module
**None.**

`gui_text` is a pure rendering library. Reading every proven body of its member
functions (draw_message, ui_even_ai_task, gui_area_clear, the gui_utf_draw_* and
gui_bmp_* families, resource_manger_get, and all helpers) shows **no**
`k_thread_create` / `K_THREAD_DEFINE`, `k_msgq_init` / `K_MSGQ_DEFINE`,
`k_sem_init`, `k_mutex_init`, `k_work_init`, or `k_timer_init` call. The module
allocates no thread, queue, semaphore, mutex, work item, or timer.

Its two thread-shaped entry points do not define their own thread objects:
- `ui_even_ai_task` (0x3bfe0) is a **thread main** — the `K_THREAD_DEFINE`
  (entry / stack / priority) that binds it lives in the module that spawns the
  UI tasks, not here.
- `draw_message` (0x35afc) and the other UI-dispatch entry points are **callback
  targets** invoked synchronously from another module's UI-command dispatch
  table; they run on the caller's thread.

## External RTOS objects this module DEPENDS ON (inputs for wiring)
These are referenced but **defined elsewhere** — record them so the owning
module can be matched during wiring reconstruction.

- **Even-AI text-buffer mutex** — locked/unlocked inside `ui_even_ai_task`
  (0x3bfe0). The proven body calls:
  - `k_mutex_lock(mutex, …, 0xffffffff, 0xffffffff)`  → `FUN_000723b8` (k_mutex_lock)
  - `k_mutex_unlock(mutex)`                            → `FUN_00072558` (k_mutex_unlock)
  The mutex pointer and the guarded ~400-byte text buffer come from the function's
  literal pool (decompiler placeholders `DAT_0003c644` = buffer base,
  `DAT_0003c648` = mutex, `DAT_0003c64c` = a status word; `memset(buffer,0,400)`
  precedes the lock). The mutex object itself is `k_mutex_init`'d in the module
  that owns the Even-AI text pipeline, not in gui_text.
  Cite: `recon/named/ui_even_ai_task.c` (~lines 359–365), function @0x3bfe0.

## Panel / canvas coupling (not RTOS objects, but wiring-relevant)
gui_text reaches the panel through the `display` module's singletons rather than
any RTOS primitive:
- `get_device_info()` (0x167a8) — device_info struct; canvas fields at +0xb90
  (fb base for clean_fb_data), +0xeb4/+0xeb8 (reflash args), panel cursor fields
  at +0x1072 (column) / +0x1074 (row) read by gui_panel_col/row_cursor.
- `get_projector_controller()` — projector controller; `+0x35c` gated in
  gui_area_clear (0x43228) before `reflash_fb_data_to_lcd`.
These belong to `display`; gui_text only reads/writes through them.
