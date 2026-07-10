/*
 * quicknote.h  -  Even G1 (nRF5340 app core, NCS 2.5.1)
 *
 * QuickNote capture (voice-note text + audio records).
 *
 * The QuickNote feature captures a note that carries a title + text plus an
 * associated audio record. This module owns:
 *   - the QuickNote screen state-machine / renderer (ui_QuickNote_task), driven
 *     per-frame by the main UI dispatcher (FUN_00048b5c);
 *   - the QuickNote *mode entry* (prepare_quick_note_mode), which arms the lens
 *     into QuickNote "slave" mode from a touch/gesture + BLE command;
 *   - the producer/consumer wrappers over the QuickNote-flash command queue
 *     g_quicknote_flash_msgq @0x20003960 (deleteQuickNoteData enqueues,
 *     getQuickNoteBKPQueueCacheData dequeues a backup-queue cache entry).
 *
 * The persistent records themselves and the store/verify handlers
 * (upgradeQuickNoteDataToFlash / getQuickNoteDataFromFlash / QuickNoteStoreHandler /
 * drain_quick_note_data_queue) live in flash_store, which is the other endpoint
 * of g_quicknote_flash_msgq. Inbound note title/text/audio commands arrive over
 * BLE (ble_proto).
 *
 * PUBLIC API (graph api set): the ONLY functions called from other modules by
 * symbol are getQuickNoteBKPQueueCacheData() and prepare_quick_note_mode().
 * ui_QuickNote_task() and deleteQuickNoteData() are entry points reached by
 * dispatch/registration (UI task switch / command handler), not part of the
 * curated cross-module surface -> declared below but grouped separately.
 *
 * Function bodies are NOT here; each prototype maps to a reconstructed source
 * file recon/named/<name>.c (or recon/verified/src/<name>.c). Addresses are the
 * app-core flash offsets (link base 0xC200). All four named bodies + both
 * helpers are Unicorn-parity PROVEN.
 */
#ifndef G1_QUICKNOTE_H
#define G1_QUICKNOTE_H

#include <stdint.h>
#include "device_info.h"      /* struct device_info_t global state */
#include "even_protocol.h"    /* packet framing + service IDs */

/* Ghidra-decompiler type aliases (signatures are as-reconstructed) */
typedef uint8_t  byte; typedef uint8_t  u8; typedef uint8_t  undefined1;
typedef uint16_t u16;  typedef uint16_t undefined2;
typedef uint32_t u32;  typedef uint32_t uint; typedef uint32_t undefined4; typedef uint32_t undefined;
typedef uint64_t u64;  typedef uint64_t undefined8;

/* ---- public API (graph api set: called from OTHER modules) -------------- */

/* @0x24684  Dequeue one entry from the QuickNote-flash backup queue cache
 * (g_quicknote_flash_msgq @0x20003960, 12-byte messages) into the caller's
 * 3-word slot; returns 0 on success, -1 on empty/failure. */
int getQuickNoteBKPQueueCacheData(uint param_1, uint param_2, undefined4 param_3); /* @0x24684 */

/* @0x7cdb6  Arm QuickNote "slave" mode: if battery is not critical and the
 * current screen id (param_1[0xd5]) is 6 or 4, optionally emit an event status,
 * force the persist task to idle and clear the capture buffer. */
void prepare_quick_note_mode(unsigned char *param_1, int param_2,
                             unsigned int param_3, unsigned int param_4);          /* @0x7cdb6 */

/* ---- entry points (reached by dispatch/registration, not called by symbol) */

/* @0x3b824  QuickNote screen state-machine / renderer. Invoked per UI frame by
 * the main UI dispatcher (FUN_00048b5c) with (ctx, _, phase). Walks a 3-state
 * UI byte g_quicknote_ui_state @0x20004978 (0=arm/record, 1=recording,
 * 2=review/timeout), drives dmic_record_start, renders via gui_*, and runs the
 * delay-exit countdown seeded from getDelayExitValue(). */
undefined4 ui_QuickNote_task(int param_1, undefined4 param_2, int param_3);        /* @0x3b824 */

/* @0x244a8  Enqueue a QuickNote delete command (msg {0x00010002, note_num,
 * param_3}) onto g_quicknote_flash_msgq, then poke g_app_language_msgq sem;
 * returns 0 on success, 0xffffffff on queue-full. */
unsigned int deleteQuickNoteData(unsigned int param_1, unsigned int param_2,
                                 unsigned int param_3);                             /* @0x244a8 */

/* ---- internal helpers (auto-named FUN_*, reconstructed, PROVEN) ---------- */

/* @0x37098  Reset the dashboard/widget scroll-index state: zero
 * g_dashboard_widget_state[1] (news index @0x20004951) and g_widget0_index_raw
 * (@0x2001b816), then clear shared-RAM control byte 0x2007fc69 via FUN_0001672c.
 * A cross-cutting reset reused by the QuickNote backup-queue read and by the
 * dashboard flows (callers 0x2316c, 0x3727c). NOT QuickNote-specific. */
void FUN_00037098(void);                                                            /* @0x37098 */

/* @0x49040  getDelayExitValue(): return g_delay_exit_value @0x2000a094 (the
 * QuickNote slave delay-exit countdown seed). Address-identical to the named
 * getDelayExitValue; ui_QuickNote_task calls it under that alias. */
uint32_t FUN_00049040(void);                                                        /* @0x49040 */

#endif /* G1_QUICKNOTE_H */
