/*
 * ipc_core.h  -  Even G1 (nRF5340 app core, NCS 2.5.1)
 *
 * Inter-core IPC transport + dashboard response bridge.
 *
 * Two cooperating jobs live in this module:
 *
 *  1. Zephyr ipc_service / RPMsg transport between the nRF5340 application
 *     core and the network (radio) core. register_ipc_service_context()
 *     installs the endpoint context (callback thunks + g_ipc0_endpoint);
 *     ipc0_ept_recv() is the RX callback that demuxes an inbound buffer by
 *     its first byte and dispatches to the matching registered handler;
 *     global_ipc_service_send() is the blocking TX path that retries and,
 *     on unrecoverable failure, reboots the SoC ("sys reboot because ipc
 *     failed", via sys_reboot at FUN_0004c0a8).
 *
 *  2. A "dashboard response" path that assembles small status packets from
 *     device state and pushes them into the app-core response message queue
 *     (g_dashboard_response_msgq @0x2000392c) via k_msgq_put:
 *     send_response_data_to_msgqueue() (copies a <=0x14-byte payload) and
 *     send_response_data_to_ble() (enqueues a fixed type-1 control record);
 *     send_dashboard_status_sync[_compact]() build the 10-/8-byte dashboard
 *     status frames using getStocksIndex()/getNewsIndex() and post them.
 *
 * The public surface below is exactly the module's cross-module API set
 * (functions called from OTHER modules, per the Ghidra reference graph).
 * init_msgq_uid() and register_ipc_service_context() are internal platform
 * init entry-points (invoked once from the boot/init sequence, not part of
 * the steady-state API) and are declared static/internal.
 *
 * Function bodies are NOT here; each maps to a reconstructed source file
 * recon/verified/src/<name>.c (all PROVEN, 300/300 parity trials).
 * Addresses are app-core flash offsets (link base 0xC200).
 */
#ifndef G1_IPC_CORE_H
#define G1_IPC_CORE_H

#include <stdint.h>
#include "device_info.h"      /* struct device_info_t global state */

/* Ghidra-decompiler type aliases (signatures are as-reconstructed) */
typedef uint8_t  byte; typedef uint8_t  u8; typedef uint8_t  undefined1;
typedef uint16_t u16;  typedef uint16_t undefined2;
typedef uint32_t u32;  typedef uint32_t uint; typedef uint32_t undefined4; typedef uint32_t undefined;
typedef uint64_t u64;  typedef uint64_t undefined8;

/* ---- public API (graph api set: called from other modules) -------------- */

/* IPC transport */
void ipc0_ept_recv(unsigned char *buf, int len);                        /* @0x25a48  RX callback, endpoint 0 */
int  global_ipc_service_send(unsigned int data, unsigned int len);      /* @0x25b78  blocking TX, reboots on failure */

/* dashboard response bridge (app-core response msgq @0x2000392c) */
unsigned int send_response_data_to_msgqueue(void *payload, unsigned int len); /* @0x47b1c  k_msgq_put, len<=0x14 */
unsigned int send_response_data_to_ble(u32 p1, u32 p2, u32 p3, u32 p4);       /* @0x47ba8 (FUN_00047ba8) type-1 record */

/* dashboard status frame builders */
void send_dashboard_status_sync(u32 p1, u32 p2, u32 p3, u32 p4);        /* @0x3ae6c (FUN_0003ae6c) 10-byte frame */
void send_dashboard_status_sync_compact(u32 p1, u32 p2, u32 p3, u32 p4);/* @0x3af04 (FUN_0003af04) 8-byte frame */
unsigned char getStocksIndex(void);                                     /* @0x370bc  dashboard stocks widget index */
unsigned char getNewsIndex(void);                                       /* @0x3719c  dashboard news widget index */

/* ---- internal / platform-init entry points (NOT cross-module API) ------- */
/* Called once from the boot/init sequence; declared here for reference only. */
#ifdef IPC_CORE_INTERNAL
static int init_msgq_uid(void);                                         /* @0x18e04  k_msgq_alloc_init(g_uid_pipe,8,10) */
static unsigned int register_ipc_service_context(int ctx, unsigned int a, unsigned int b, unsigned int c); /* @0x25d40 */
#endif

#endif /* G1_IPC_CORE_H */
