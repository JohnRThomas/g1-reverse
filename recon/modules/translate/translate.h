/*
 * translate.h  -  Even G1 (nRF5340 app core, NCS 2.5.1)
 *
 * App-language / Translate configuration (reset path).
 *
 * This is a one-function module in the authoritative reference graph. Its sole
 * member, cleanAppLanguageInfo() @0x23b78, posts a "reset app-language info"
 * command message onto a shared kernel message queue and wakes the reader that
 * services it. It does NOT itself parse BLE or touch input -- it is invoked by
 * the touch-key thread (touch_key_thread cluster, FUN_0002316c @0x2316c) as the
 * app-language reset action.
 *
 * The persistent form of the app-language table lives in the neighboring
 * flash-store cluster (upgradeAppLanguageInfoToFlash @0x23af0,
 * getAppLanguageInfofromFlash @0x23d0c) -- assigned to flash_store, not here.
 *
 * PUBLIC API (graph 'api' set): EMPTY. The graph classifies cleanAppLanguageInfo
 * as an ENTRY POINT (no in-module caller; its only caller, 0x2316c, is in the
 * touch_key module). It is exposed below as the module's single externally
 * reachable entry; there are no other public symbols.
 *
 * Function bodies are NOT here; the prototype maps to the reconstructed source
 * recon/verified/src/cleanAppLanguageInfo.c (parity 300/300, PROVEN).
 * Addresses are app-core flash offsets (link base 0xC200).
 */
#ifndef G1_TRANSLATE_H
#define G1_TRANSLATE_H

#include <stdint.h>

/* Ghidra-decompiler type aliases (signatures are as-reconstructed) */
typedef uint8_t  byte; typedef uint8_t  u8; typedef uint8_t  undefined1;
typedef uint16_t u16;  typedef uint16_t undefined2;
typedef uint32_t u32;  typedef uint32_t uint; typedef uint32_t undefined4; typedef uint32_t undefined;
typedef uint64_t u64;  typedef uint64_t undefined8;

/* ---- entry point (graph 'api' set is empty) ----------------------------- */
/*
 * cleanAppLanguageInfo -- enqueue a reset-app-language command.
 *   Builds an 8-byte message {opcode=2, 0,0,0,0, 0, ...}, k_msgq_put()s it onto
 *   the app-language command msgq @0x20003994, then signals the paired wait/poll
 *   object @0x200079e4. Returns 0 on successful enqueue, -1 if the queue is full.
 *   Both params are ignored by the proven body (present in the ABI signature).
 *   Caller: touch_key_thread cluster (FUN_0002316c @0x2316c).
 */
int cleanAppLanguageInfo(unsigned int param_1, unsigned int param_2);    /* @0x23b78, ENTRY */

#endif /* G1_TRANSLATE_H */
