/*
 * flash_store.h  -  Even G1 (nRF5340 app core, NCS 2.5.1)
 *
 * Persistent settings & user-data store (external SPI flash + Zephyr settings).
 *
 * Owns the on-flash layout for system settings, user settings, per-app language
 * info, QuickNote text/audio records, and the analytics "burial point" blob,
 * plus the low-level external-flash driver (ext_flash_read/write/api_init) and
 * CRC integrity (calc_flash_crc = CRC-16 over settings, crc32_update/FUN_0002360c
 * = CRC-32 over file payloads). All writes are serialised through one worker:
 * flash_ops_thread() spins draining THREE store-request message queues
 *   - 0x20003890  audio-stream file store queue  -> audioStreamFileManagerHandler
 *   - 0x20003960  QuickNote BKP store queue       -> getQuickNoteBKPQueueCacheData
 *   - 0x20003994  g_flash_store_cmd_msgq (settings)-> SettingStoreHandler
 * each guarded by a global k_mutex (0x20007b54 g_ext_flash_mutex). Handlers run
 * the read-modify-verify cycle (erase, write, read-back compare; skip when
 * unchanged). A persist-task state machine (now_has_persist_task,
 * update_persist_task_status*) tracks pending saves across power transitions.
 *
 * PUBLIC/INTERNAL SPLIT is authoritative from the Ghidra reference graph:
 * only the functions in "Cross-module API" below are actually called from other
 * modules; everything under "Entry points" and "Internal" has no external
 * caller and is module-private (would be static in a single-TU build).
 *
 * Note: several high-address API entries (0x723b8/0x72558 mutex lock/unlock,
 * 0x864c2 sys_dlist_init, 0x4b088/0x4b0dc locked table dispatch, ...) are shared
 * kernel/library primitives that clustered into this module because
 * ext_flash_read/write and the settings path reach them; they are exported
 * helpers, not flash-specific logic.
 *
 * Function bodies are NOT here; each prototype maps to a reconstructed source
 * file recon/named/<name>.c (or recon/verified/src/<name>.c). Addresses are the
 * app-core flash offsets (link base 0xC200).
 */
#ifndef G1_FLASH_STORE_H
#define G1_FLASH_STORE_H

#include <stdint.h>
#include "device_info.h"      /* struct device_info_t global state */

/* Ghidra-decompiler type aliases (signatures are as-reconstructed) */
typedef uint8_t  byte; typedef uint8_t  u8; typedef uint8_t  undefined1;
typedef uint16_t u16;  typedef uint16_t undefined2;
typedef uint32_t u32;  typedef uint32_t uint; typedef uint32_t undefined4; typedef uint32_t undefined;
typedef uint64_t u64;  typedef uint64_t undefined8;

/* =========================================================================
 * CROSS-MODULE API  (== refgraph api set: the ONLY functions other modules call)
 * ========================================================================= */

/* -- settings / burial-point read path -- */
unsigned read_sys_settting_from_flash(unsigned *param_1);                /* @0x232f8 <- display,system */
unsigned FUN_00032254(int param_1, unsigned param_2, unsigned *param_3, unsigned char *param_4); /* @0x32254 usr-setting load helper (calls read_usr_settting_from_flash) */
unsigned int FUN_0002eaa8(void);                                         /* @0x2eaa8 flash-status query <- system(process_pt_data) */

/* -- QuickNote read path -- */
unsigned getQuickNoteDataFromFlash(unsigned param_1, unsigned param_2, int param_3, unsigned param_4, int param_5); /* @0x24534 <- dashboard */

/* -- CRC / guarded write helpers -- */
unsigned int FUN_0002360c(unsigned int param_1, unsigned char *param_2, int param_3); /* @0x2360c crc32_update (table-driven CRC-32) <- audio */
unsigned FUN_00017e84(unsigned param_1, unsigned param_2);               /* @0x17e84 battery/state-guarded flash write (lock 0x20006a1c -> FUN_0004f518) */

/* -- external SPI-flash driver primitives -- */
int ext_flash_read(int param_1, unsigned param_2, unsigned param_3, unsigned param_4); /* @0x2e398 (locks g_ext_flash_mutex 0x20007b54) */
int ext_flash_write(int param_1, unsigned param_2, unsigned param_3, unsigned param_4);/* @0x2e440 (locks g_ext_flash_mutex 0x20007b54) */
uint32_t get_flash_info(int param_1, uint32_t param_2, uint32_t *param_3, uint8_t *param_4); /* @0x32628 */
undefined4 is_ext_flash_burned(unsigned param_1, uint param_2, unsigned param_3); /* @0x32c28 */

/* -- persist-task state machine -- */
uint update_persist_task_status(int param_1, uint param_2, uint param_3); /* @0x2bef4 <- ble_proto,esb_sync,onboarding */
int update_persist_task_status_to_idle(int param_1);                     /* @0x2c0e8 <- ancs,battery,quicknote,system */
unsigned int update_persist_task_status_to_wait_blow_head(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x2c180 <- ancs */
void FUN_0007cdf8(void);                                                 /* @0x7cdf8 persist-task notify wrapper -> FUN_00074844(0x21,0) */

/* -- targeted setting write -- */
unsigned set_imu_pitch_reflash(void);                                    /* @0x469bc <- imu_motion */

/* -- storage worker (also invoked as a thread entry, see wiring.md) -- */
void flash_ops_thread(void);                                             /* @0x23480 */

/* -- shared kernel / library primitives reached via flash + fb paths -- */
void FUN_000723b8(int a,int b,int c,int d);                              /* @0x723b8 k_mutex/spinlock LOCK  <- display,gui_text */
unsigned FUN_00072558(int param_1);                                      /* @0x72558 k_mutex/spinlock UNLOCK <- display,gui_text */
void FUN_000864c2(unsigned int *param_1);                                /* @0x864c2 sys_dlist_init (self-ref node) <- ble_proto */
unsigned int FUN_0004b088(int param_1, unsigned int param_2, unsigned int param_3); /* @0x4b088 locked handler-table dispatch (tbl@0x20002548) <- gui_text */
unsigned int FUN_0004b0dc(int param_1, unsigned int param_2, unsigned int param_3); /* @0x4b0dc locked handler-table dispatch <- gui_text */

/* -- init that also spawns a worker + timer (settings/projector) -- */
int FUN_0002201c(int param_1);                                           /* @0x2201c dlist_init + k_timer_init(0x20003d28) + k_thread_create(entry 0x21da8) */

/* -- remaining cross-module helpers (accessors / flash records; callers noted) -- */
void FUN_00047698(unsigned int param_1, unsigned int param_2);           /* @0x47698 <- display */
void FUN_000476a8(void);                                                 /* @0x476a8 <- display */
int FUN_0004e124(int param_1,unsigned int param_2);                      /* @0x4e124 <- ancs_notify */
int FUN_0004e780(int param_1, unsigned param_2);                         /* @0x4e780 */
void FUN_000510fc(int param_1, int param_2);                             /* @0x510fc <- system */
void FUN_00051134(int param_1, int param_2, int param_3, int param_4);   /* @0x51134 <- system */
int FUN_00053184(unsigned char *param_1, int param_2);                   /* @0x53184 <- ancs_notify */
void FUN_00058bfc(int *param_1);                                         /* @0x58bfc */
uint32_t FUN_00076ad0(int param_1,int param_2);                          /* @0x76ad0 <- system */
void FUN_00076bcc(int param_1);                                          /* @0x76bcc <- ancs_notify,system */
int FUN_00076ed4(int param_1, int param_2, unsigned char *param_3, uint *param_4); /* @0x76ed4 <- system */
int FUN_000778d4(int param_1);                                           /* @0x778d4 <- gui_text (utf8) */
void FUN_0007d7b6(int param_1,unsigned int param_2);                     /* @0x7d7b6 <- display */
unsigned int FUN_0007f192(unsigned int param_1, unsigned int param_2);   /* @0x7f192 <- ancs_notify */
void FUN_00081c22(u32* param_1);                                         /* @0x81c22 buffer op */
int FUN_00083e0e(int param_1, unsigned param_2, unsigned param_3);       /* @0x83e0e <- display(power_for_panel) */
uint32_t FUN_000841fc(int param_1,int param_2,char param_3,uint32_t param_4,char param_5); /* @0x841fc <- system */
int FUN_00084348(int param_1, int param_2, int param_3);                 /* @0x84348 */
void FUN_00086f5a(int* param_1, int param_2, int param_3, int param_4);  /* @0x86f5a */

/* =========================================================================
 * ENTRY POINTS  (external linkage but NOT a cross-module call API: boot init,
 *                dispatch/message handlers, callbacks; see README/wiring)
 * ========================================================================= */
void sett_init(int *param_1);                                            /* @0x22518 Zephyr settings subsys init + register */
unsigned int ext_flash_api_init(unsigned int *param_1, unsigned int *param_2, unsigned int *param_3, unsigned int param_4); /* @0x2e4e8 driver init: mutex + device_is_ready */
void spawn_flash_ops_and_brightness_threads(int param_1);                /* @0x23a54 defines flash_ops_thread + brightness thread + sem (see wiring.md) */
uint SettingStoreHandler(void);                                          /* @0x23f04 settings msgq consumer (called only by flash_ops_thread) */
void try_to_save_file(int param_1);                                      /* @0x23634 file-save enqueue/worker step */
unsigned int update_burial_point_to_flash(char *param_1);                /* @0x23014 persist analytics blob */
unsigned int upgradeAppLanguageInfoToFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3); /* @0x23af0 */
unsigned char getAppLanguageInfofromFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3);  /* @0x23d0c */
int upgradeQuickNoteDataToFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3); /* @0x24420 */

/* =========================================================================
 * INTERNAL  (module-private helpers, reconstructed; no external caller)
 * ========================================================================= */
unsigned calc_flash_crc(unsigned short *param_1, int param_2, uint param_3);    /* @0x22974 CRC-16 over a settings blob */
unsigned int read_usr_settting_from_flash(unsigned char *param_1);              /* @0x23400 */
unsigned char now_has_persist_task(unsigned char *param_1, unsigned int param_2);/* @0x2be64 */
void update_not_disturb_settings(void);                                         /* @0x3cb4c targeted DND setting write */

/* store-queue used-msgs accessors, drained by flash_ops_thread (k_msgq +0x24) */
unsigned int FUN_00023ef8(void);                                         /* @0x23ef8 settings msgq  0x20003994 used-count */
unsigned int FUN_00024678(void);                                         /* @0x24678 quicknote msgq 0x20003960 used-count */
unsigned int FUN_0002f758(void);                                         /* @0x2f758 audio-file msgq 0x20003890 used-count */

void FUN_00019b38(unsigned int param_1, unsigned int param_2);           /* @0x19b38 */
void FUN_00019b48(void);                                                 /* @0x19b48 */
void FUN_00026850(void);                                                 /* @0x26850 <- display_dispatch_thread */
void FUN_00047148(int* param_1);                                         /* @0x47148 */
unsigned int FUN_0004b01c(unsigned int param_1);                         /* @0x4b01c */
int FUN_0004c548(undefined4 *param_1);                                   /* @0x4c548 cortex-M control-reg helper */
unsigned FUN_0004c8f8(int param_1, unsigned param_2, int param_3, unsigned param_4); /* @0x4c8f8 */
uint FUN_0004cab4(int param_1, uint param_2, unsigned param_3, uint param_4, unsigned short param_5); /* @0x4cab4 */
unsigned int FUN_0004e434(unsigned int param_1, unsigned int param_2, unsigned int param_3); /* @0x4e434 */
unsigned FUN_0004e494(unsigned *param_1, unsigned param_2);              /* @0x4e494 */
uint32_t* FUN_0004e540(uint32_t param_1, uint32_t *param_2, uint32_t param_3); /* @0x4e540 */
u32 FUN_0004e604(u32 param_1,u32 param_2,u32 param_3,u32 param_4,int* param_5); /* @0x4e604 */
int FUN_0004e6a8(int param_1,unsigned param_2,unsigned param_3,unsigned param_4); /* @0x4e6a8 */
void FUN_0005109c(int *param_1);                                         /* @0x5109c */
void FUN_00052e7c(int param_1,int param_2,int param_3,uint8_t *param_4,int param_5); /* @0x52e7c */
void FUN_00078598(int *param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4); /* @0x78598 */
void FUN_0007c080(void);                                                 /* @0x7c080 */
void FUN_0007c082(void);                                                 /* @0x7c082 */
char* FUN_0007cbae(int p1,int p2,int p3);                                /* @0x7cbae */
unsigned FUN_0007d9c0(unsigned param_1, unsigned param_2, unsigned param_3, int param_4, char param_5, unsigned char *param_6, int param_7); /* @0x7d9c0 */
unsigned int FUN_0007da4a(unsigned int param_1, int param_2, int param_3, unsigned int param_4); /* @0x7da4a */
void FUN_0007e658(void);                                                 /* @0x7e658 */
void FUN_0007e9d4(unsigned int param_1, unsigned int param_2);           /* @0x7e9d4 */
void FUN_0007e9dc(void);                                                 /* @0x7e9dc */
void FUN_0007f198(unsigned int param_1);                                 /* @0x7f198 */
uint32_t FUN_00083a92(int param_1,int param_2,int param_3);              /* @0x83a92 */
void FUN_00084300(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x84300 */
unsigned FUN_00086c88(int param_1, unsigned param_2, int *param_3);      /* @0x86c88 */
int FUN_00086cb6(unsigned int param_1, unsigned int param_2, unsigned char *param_3, int param_4); /* @0x86cb6 */

#endif /* G1_FLASH_STORE_H */
