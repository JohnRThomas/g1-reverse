# translate — App-language reset command

**Role.** A single-function module in the reference graph. It provides the
app-language "reset" action: it posts a reset command message onto a shared
kernel message queue and wakes the reader that services it. The persistent
app-language table itself is managed by the neighboring `flash_store` cluster.

## Key functions
- `cleanAppLanguageInfo(a, b)` — @0x23b78 (PROVEN 300/300). Builds an 8-byte
  message `{opcode=2, 0,0,0,0, 0, …}` on the stack, calls `k_msgq_put`
  (`FUN_000720d0` @0x720d0) to enqueue it on the app-language command msgq
  @`0x20003994`. On success it signals the paired wait/poll object @`0x200079e4`
  (`FUN_00072880` @0x72880, a Zephyr unpend-first-waiter / poll-event notify).
  Debug output on both success and full-queue paths is gated on the global log
  level `g_log_level` @`0x2000230c` and routed through either `DEBUG_PRINT`
  (`FUN_0007dda4`) or the alt sink `FUN_00019c70` depending on
  `g_log_use_alt_sink` @`0x20007554`. Returns `0` on enqueue, `-1` if the queue
  is full. Both parameters are ignored by the proven body.

Related (owned by OTHER modules — referenced, not defined here):
- `upgradeAppLanguageInfoToFlash` @0x23af0 / `getAppLanguageInfofromFlash`
  @0x23d0c — persist/restore the app-language table (**flash_store** cluster;
  they share the same msgq @0x20003994 and poll object @0x200079e4).
- `k_msgq_put` @0x720d0, `FUN_00072880` @0x72880 — Zephyr kernel primitives.

## State it owns / structs
- Read-only per-function constants at `0x23be0…0x23bf8` (the function's own flash
  region; message template / literals). No writable state of its own.
- It does **not** own the msgq @0x20003994 or the poll object @0x200079e4 — those
  are shared kernel objects defined by the flash-store/app-language cluster
  (referenced by 6 and 12 functions respectively across that cluster).

## Entry points
- **`cleanAppLanguageInfo` @0x23b78** — the only entry. Graph `api` set is empty;
  the function is classified as an ENTRY POINT (no in-module caller). Its single
  caller is `FUN_0002316c` @0x2316c in the **touch_key** module
  (`touch_key_thread` cluster) — i.e. a touch-key handler triggers the
  app-language reset.

## Cross-module coupling
- **touch_key** — sole caller (entry).
- **flash_store** — co-owner of the app-language msgq @0x20003994 / poll object
  @0x200079e4 and persistence of the table.
- **Kernel** — `k_msgq_put` and the wait-queue signal primitive.
