/*
 * analytics.h  -  Even G1 (nRF5340 app core, NCS 2.5.1)
 *
 * Usage analytics ("burial point" telemetry).
 *
 * Records aggregated usage counters into the buried_point_data[192] region of
 * device_info_t and persists them via flash_store. Events such as wear are
 * timestamped per day: enter_wear_burial_point() and
 * update_burial_point_day_index() roll counters by day index;
 * load_burial_point()/load_sys_setting() restore them at boot. The persisted
 * blob is uploaded to the phone on request (BLE_GET_BURIAL_POINT_DATA in
 * ble_proto). Sister writer update_burial_point_to_flash lives in flash_store.
 *
 * Function bodies are NOT here; each prototype maps to a reconstructed
 * source file recon/named/<name>.c (or recon/verified/src/<name>.c).
 * Addresses are the app-core flash offsets (link base 0xC200).
 */
#ifndef G1_ANALYTICS_H
#define G1_ANALYTICS_H

#include <stdint.h>
#include "device_info.h"      /* struct device_info_t global state */

/* Ghidra-decompiler type aliases (signatures are as-reconstructed) */
typedef uint8_t  byte; typedef uint8_t  u8; typedef uint8_t  undefined1;
typedef uint16_t u16;  typedef uint16_t undefined2;
typedef uint32_t u32;  typedef uint32_t uint; typedef uint32_t undefined4; typedef uint32_t undefined;
typedef uint64_t u64;  typedef uint64_t undefined8;

/* ---- public / named API ------------------------------------------------- */
undefined4 load_sys_setting(int param_1);                                /* @0x22bd0 */
unsigned int load_burial_point(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x230e0 */
undefined4 update_burial_point_day_index(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* @0x4a5b0 */
void enter_wear_burial_point(void);                                      /* @0x4a890 */

/* ---- internal helpers (auto-named FUN_*, reconstructed) ----------------- */
u32 FUN_000456fc(u32 param_1, u32 param_2);                              /* @0x456fc verified */
uint32_t FUN_0004a1b8(uint param_1, int16_t* param_2);                   /* @0x4a1b8 verified */
void FUN_0004a2a4(int param_1);                                          /* @0x4a2a4 verified */
uint32_t FUN_0004c1f0(void);                                             /* @0x4c1f0 verified */
void FUN_00052bf8(unsigned int param_1, unsigned int param_2);           /* @0x52bf8 verified */
int FUN_00052c40(int param_1, int param_2);                              /* @0x52c40 verified */
unsigned long long FUN_00063610(void);                                   /* @0x63610 verified */
int FUN_00074b68(void);                                                  /* @0x74b68 verified */
int FUN_0007c360(int param_1);                                           /* @0x7c360 verified */
void FUN_0007d1b8(unsigned char *param_1);                               /* @0x7d1b8 verified */
uint32_t FUN_0007d216(void);                                             /* @0x7d216 verified */
int FUN_0007d280(int param_1, int param_2, int param_3);                 /* @0x7d280 verified */
void FUN_0007d4b2(int param_1);                                          /* @0x7d4b2 verified */
void FUN_00084c76(void);                                                 /* @0x84c76 verified */

#endif /* G1_ANALYTICS_H */
