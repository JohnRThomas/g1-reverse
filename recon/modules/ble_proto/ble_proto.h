/*
 * ble_proto.h  -  Even G1 (nRF5340 app core, NCS 2.5.1)
 *
 * BLE application command dispatch (phone <-> glasses).
 *
 * Parses inbound Even-protocol packets (see even_protocol.h: 0xAA framing,
 * 8-byte header, 2-byte service ID, CRC-16/CCITT) delivered over the Nordic
 * SoftDevice GATT link and routes them to the correct service handler. The
 * core router ble_process_req_dispatch() switches on the 1-byte command/opcode
 * (PUT range 0x01-0x27, GET range 0x29-0x45, and the 0x47-0x50 media/notify
 * family) and either dispatches to ble_process_put_req / ble_process_get_req or
 * calls the per-connection callback stored at conn+0xc. It also owns the BLE
 * security callbacks (bonding, pairing-failed, auth-cancel, SC indication) and
 * the main dispatch thread that spawns the display/flash/proxy worker threads.
 * Outbound replies are fragmented and PKCS#7-padded by
 * subcontracing_send_data_pkcs7() before indication.
 *
 * PUBLIC API BOUNDARY
 * -------------------
 * The prototypes in the "public API" block below are exactly the functions the
 * authoritative Ghidra reference graph shows being called (or address-taken)
 * from OTHER modules. Everything in the "internal" block has only in-module
 * callers and is logically static; it is exposed here only because the
 * reconstruction keeps one translation unit per function. Functions tagged
 * [ENTRY] are entry points (RTOS thread mains or registered callbacks) reached
 * via function pointer rather than a direct in-module call.
 *
 * Function bodies are NOT here; each prototype maps to a reconstructed
 * source file recon/named/<name>.c (or recon/verified/src/<name>.c).
 * Addresses are the app-core flash offsets (link base 0xC200).
 */
#ifndef G1_BLE_PROTO_H
#define G1_BLE_PROTO_H

#include <stdint.h>
#include "device_info.h"      /* struct device_info_t global state */
#include "even_protocol.h"    /* packet framing + service IDs */

/* Ghidra-decompiler type aliases (signatures are as-reconstructed) */
typedef uint8_t  byte; typedef uint8_t  u8; typedef uint8_t  undefined1;
typedef uint16_t u16;  typedef uint16_t undefined2;
typedef uint32_t u32;  typedef uint32_t uint; typedef uint32_t undefined4; typedef uint32_t undefined;
typedef uint64_t u64;  typedef uint64_t undefined8;

/* ======================================================================== *
 *  PUBLIC API  -  the graph's cross-module call/address-taken set (16)      *
 * ======================================================================== */

/* --- BLE security callbacks (address-taken by the BT/SMP stack) [ENTRY] --- */
void bt_send_enabled(int param_1);                                       /* @0x17e3c */
void check_bonded_addr(unsigned int param_1);                            /* @0x183e4 */
void pairing_failed(unsigned int param_1, unsigned int param_2);         /* @0x18444 */
void auth_cancel(unsigned int param_1);                                  /* @0x1849c */
void indicate_sc_cb(unsigned int *param_1, unsigned int param_2, int param_3); /* @0x18a38 [ENTRY] */

/* --- protocol dispatch / crypto / TX --- */
uint32_t FUN_00019b54(int param_1, uint8_t *param_2, uint32_t param_3);  /* @0x19b54  outbound-payload cipher wrapper (-> FUN_0002af4c) */
unsigned int ble_process_req_dispatch(uint8_t *param_1, uint8_t *packet, uint8_t *param_3); /* @0x21460 core opcode router */
unsigned subcontracing_send_data_pkcs7(int param_1, int param_2, unsigned char param_3, void *param_4); /* @0x21a40 fragment + PKCS#7 TX */

/* --- shared helpers reused by other modules --- */
unsigned int FUN_00025448(void);                                         /* @0x25448  read refreshed status word @0x20007a24 */
int disable_watchdog(void);                                              /* @0x2aeb4  feed/stop watchdog device @0x87cc8 */
unsigned int FUN_0002efc0(void);                                         /* @0x2efc0  set restart/mode flag byte @0x2000302f */
void FUN_0003b800(void);                                                 /* @0x3b800  clear counter @0x20007b78 + re-eval mode [ENTRY] */
unsigned int SlaveDoubleClickEventInject(void);                          /* @0x48ad4  inject synthesized double-click to slave lens [ENTRY] */
int FUN_00056a68(unsigned short *param_1, unsigned char param_2);        /* @0x56a68  connection state-machine step (state @+0xd) */
int FUN_00071eac(int param_1,int p2,int p3,int p4,int s0,int s1,int s2,int s3,int s4,int s5,int s6,int s7); /* @0x71eac  k_thread_create wrapper */
void FUN_00085014(unsigned int param_1);                                 /* @0x85014  enable/trigger (-> FUN_00064a88(x,1)) */

/* ======================================================================== *
 *  INTERNAL  -  in-module only; logically static (one TU per function)      *
 * ======================================================================== */
uint32_t spec_ble_command_hook(uint32_t param_1, uint32_t param_2);      /* @0xef28  vendor/special command interception */
unsigned char FUN_00016568(void);                                        /* @0x16568  read paired-state byte via ptr @0x200069fc */
void ble_process_get_req(uint8_t *param_1, uint8_t *packet, uint8_t *param_3); /* @0x1a064  GET-side handlers */
void FUN_00021d78(unsigned int param_1, unsigned int param_2, int param_3); /* @0x21d78 [ENTRY] hook-then-dispatch trampoline */
void FUN_00023a54(int param_1);                                          /* @0x23a54  spawns 2 worker threads + inits sem @0x200079e4 */
int FUN_00025ecc(char *param_1);                                         /* @0x25ecc [ENTRY] recompute display geometry/brightness */
void run_main_dispatch_thread(char *param_1);                            /* @0x2a65c [ENTRY] main dispatch thread: brings worker threads online */
unsigned int FUN_0002eb40(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x2eb40  logging/status helper */
void FUN_00032fe8(void);                                                 /* @0x32fe8  spawn thread @entry 0x32420 (guard @0x20019ef1) */
void FUN_0003304c(void);                                                 /* @0x3304c  spawn thread @entry 0x324bc */
u32 onboarding_ble_process(u32 param_1, u32 param_2, u32 param_3, u32 param_4); /* @0x42a64 [ENTRY] SVC_ONBOARDING action decode */
int FUN_00047ad0(int param_1);                                           /* @0x47ad0  spawn thread @entry 0x47c48 (tid @0x2000a090) */
unsigned int FUN_00049638(unsigned int param_1);                         /* @0x49638  spawn thread @entry 0x49090 (tid @0x2000a09c) */
void FUN_0004a424(int param_1, int param_2, int param_3);                /* @0x4a424  hex-dump debug helper */
unsigned int FUN_0007c20a(int param_1);                                  /* @0x7c20a  BLE RX worker loop -> conn cb @+0xc */
void FUN_0007c244(unsigned char *param_1, unsigned int param_2, unsigned int param_3); /* @0x7c244  build header + re-enter dispatch */
void FUN_0007cb66(void);                                                 /* @0x7cb66  thin k_thread_create wrapper */
void FUN_00084c94(int param_1);                                          /* @0x84c94  clear flag after driver call FUN_00083dc8 */
unsigned int FUN_00085076(unsigned int param_1, unsigned int param_2);   /* @0x85076  alloc + queue op (-> FUN_0006466c) */
unsigned int check_is_release_mode(int param_1);                         /* @0x86a06  build/mode gate */
void FUN_00087080(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x87080  bounded-random helper (-> RNG FUN_00051164) */

#endif /* G1_BLE_PROTO_H */
