/*
 * onboarding.h  -  Even G1 (nRF5340 app core, NCS 2.5.1)
 *
 * First-run onboarding flow (guided pairing / tutorial UI) + step retry watchdog.
 *
 * The module drives the onboarding UI state machine that runs until
 * onboarding completes (device_info_t.onboarding_state @0xCD).  The live
 * onboarding UI block lives at *(device_info + 0x1014):
 *   [0]   active flag        (cleared by onboarding_clear_active_flag)
 *   +2    action_cmd / step  (the current onboarding step id)
 *   +3    sub_step
 *   +4..  last-progress timestamp (uptime, 64-bit)
 *   +0x20 saved step snapshot
 *
 * Inbound onboarding action packets are decoded in ble_proto
 * (onboarding_ble_process, "ble rcv onboarding action:%d"), and each step is
 * mirrored to the slave lens in esb_sync (onboarding_sync_data,
 * "SYNC onboarding action_cmd %d and sub_step %d to slave").  This module is the
 * on-glass consumer: it decides when to present the screen, advances the UI, and
 * runs a per-step retry/timeout watchdog.
 *
 * PUBLIC API (called from OTHER modules per the reference graph):
 *   - onboarding_retry_watchdog_update()   @0x40708
 *
 * ENTRY POINTS (invoked by host dispatchers/threads, no in-module caller):
 *   - check_disp_onboarding()   @0x26a08  (from FUN_0002a8d8, display/work-mode path)
 *   - ui_onboarding_task()      @0x42d44  (from FUN_00048b5c, onboarding action handler)
 *
 * This module DEFINES NO RTOS objects of its own (no k_thread/k_msgq/k_sem/k_work
 * init in any owned function); it runs on threads owned by other modules.
 *
 * Function bodies are NOT here; each prototype maps to a reconstructed
 * source file recon/named/<name>.c (or recon/verified/src/<name>.c).
 * Addresses are the app-core flash offsets (link base 0xC200).
 */
#ifndef G1_ONBOARDING_H
#define G1_ONBOARDING_H

#include <stdint.h>
#include "device_info.h"      /* struct device_info_t global state */
#include "even_protocol.h"    /* packet framing + service IDs */

/* Ghidra-decompiler type aliases (signatures are as-reconstructed) */
typedef uint8_t  byte; typedef uint8_t  u8; typedef uint8_t  undefined1;
typedef uint16_t u16;  typedef uint16_t undefined2;
typedef uint32_t u32;  typedef uint32_t uint; typedef uint32_t undefined4; typedef uint32_t undefined;
typedef uint64_t u64;  typedef uint64_t undefined8;

/* ---- public API (called from other modules) ---------------------------- */
/* Runs on the current onboarding step: caches the step id (0x200034F5) and,
 * when the step changes to one outside {5,0x13,0x14,0x15}, resets the retry
 * (0x2001CDD1) and attempt (0x2001CDD2) counters, then raises the watchdog
 * active flag (0x2001CDD3).  Also called from slave_display_thread (esb_sync)
 * and the BLE-put path FUN_00042a64. */
void onboarding_retry_watchdog_update(void);                             /* @0x40708 verified */

/* ---- entry points (host-driven; not called within this module) --------- */
/* Display gate: decides whether the onboarding screen should be shown; on the
 * transition it starts the flow (update_persist_task_status(ctx,0xE,2)) and
 * writes onboarding_state (device_info+0xCD). */
void check_disp_onboarding(int param_1, unsigned int param_2, unsigned int param_3); /* @0x26a08 */
/* Onboarding action handler / UI step advance: applies an inbound action
 * (param_3 = action class), runs the per-step retry watchdog (gives up after 20
 * tries at >1s spacing -> step 0x14, action_cmd 0xB), mirrors sync flags and
 * updates onboarding_state. */
undefined4 ui_onboarding_task(int param_1, undefined4 param_2, int param_3); /* @0x42d44 */

/* ---- internal helpers -------------------------------------------------- */
/* In-module only (single caller check_disp_onboarding): clears the onboarding
 * UI active flag *(device_info+0x1014)[0] if set. Candidate `static`. */
void onboarding_clear_active_flag(void);                                 /* @0x7d39e verified */
/* Shared 64-bit absolute-difference helper (|a-b|); used here for the retry
 * timestamp delta but NOT owned by onboarding (also called by FUN_0003cf44,
 * FUN_00048b5c). Declared here only because ui_onboarding_task references it. */
long long FUN_0007d3c2(unsigned int param_1,int param_2,unsigned int param_3,int param_4); /* @0x7d3c2 verified */

#endif /* G1_ONBOARDING_H */
