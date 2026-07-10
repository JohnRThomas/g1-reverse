/*
 * g1_types.h  —  Even G1 app-core: consolidated type umbrella.
 *
 * Single include that pulls in every recovered application-level type so the
 * reconstructed code and data units compile against one consistent view:
 *
 *   - struct device_info_t      the big fixed-address global state block
 *                               (recon/application/app/src/device_info.h)
 *   - the 3 recovered app structs g_obj_2000a018 / g_obj_2000b2d0 /
 *                               g_obj_2000ae9c
 *                               (recon/application/app/src/recovered_structs.h)
 *   - the phone<->glasses BLE wire protocol (even_protocol.h)
 *
 * The IPC / L-R sync message structs live in ipc_sync.h and the Zephyr kernel
 * object typedefs live in zephyr_objects.h; include those directly where the
 * transport layer is needed. This header intentionally stays limited to the
 * application data types so it can be included widely without dragging in the
 * RTOS surface.
 *
 * Link base 0xC200; all offsets in the included headers are authoritative,
 * names are best-effort from reverse engineering.
 */
#ifndef G1_TYPES_H
#define G1_TYPES_H

#include <stdint.h>

/* ---- Ghidra decompiler scalar aliases -----------------------------------
 * Shared by the reconstructed .c units; defined once here, guarded so the
 * per-module headers (esb_sync.h / ipc_core.h) that also define them do not
 * clash when both are pulled into the same translation unit. */
#ifndef G1_GHIDRA_TYPE_ALIASES
#define G1_GHIDRA_TYPE_ALIASES
typedef uint8_t  byte;
typedef uint8_t  u8;
typedef uint8_t  undefined1;
typedef uint16_t u16;
typedef uint16_t undefined2;
typedef uint32_t u32;
typedef uint32_t uint;
typedef uint32_t undefined4;
typedef uint32_t undefined;
typedef uint64_t u64;
typedef uint64_t undefined8;
#endif /* G1_GHIDRA_TYPE_ALIASES */

/* Authoritative source headers (kept in their original tree; read-only). */
#include "../application/app/src/device_info.h"      /* struct device_info_t   */
#include "../application/app/src/recovered_structs.h" /* g_obj_2000a018 etc.    */
#include "../application/app/src/even_protocol.h"     /* even_pkt_hdr + SVC_*    */

#endif /* G1_TYPES_H */
