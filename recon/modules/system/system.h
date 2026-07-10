/*
 * system.h  -  Even G1 (nRF5340 app core, NCS 2.5.1)
 *
 * Core system services: work-mode state machine, power, watchdog, device info,
 * factory provisioning (SN / ESB channel), the global event fan-out, message-show
 * UI arbitration, plus the shared timing and buffer/container helpers other
 * modules borrow.
 *
 * The system module is the device lifecycle hub. get_device_info() returns the
 * pointer to the global device_info_t (0x18E0-byte state block); work_mode is
 * driven by change_work_mode_to() / check_work_mode() against charge/wear/box
 * events. Power: global_system_suspend/resume, try_enter_low_power_mode(),
 * switch_to_dfu_mode(). Reliability: init_watchdog() installs the hardware WDT
 * (device @0x87cc8, handle @0x20007b50) and FUN_0002ae84 feeds it.
 *
 * Public/internal split below is graph-derived:
 *   - PUBLIC API  = the exact set of functions called from OTHER modules (60).
 *   - ENTRY POINTS= thread mains / callbacks with no in-module C caller; invoked
 *                   by the app-main orchestrator or via registered pointers.
 *   - INTERNAL    = module-private helpers.
 * This module DEFINES no Zephyr msgq/sem/mutex/work/timer objects of its own
 * (see wiring.md); its code runs on threads owned by the app-main module.
 *
 * Function bodies are NOT here; each prototype maps to recon/named/<name>.c or
 * recon/verified/src/<name>.c. Addresses are app-core flash offsets (base 0xC200).
 */
#ifndef G1_SYSTEM_H
#define G1_SYSTEM_H

#include <stdint.h>
#include "device_info.h"      /* struct device_info_t global state */

/* Ghidra-decompiler type aliases (signatures are as-reconstructed) */
typedef uint8_t  byte; typedef uint8_t  u8; typedef uint8_t  undefined1;
typedef uint16_t u16;  typedef uint16_t undefined2;
typedef uint32_t u32;  typedef uint32_t uint; typedef uint32_t undefined4; typedef uint32_t undefined;
typedef uint64_t u64;  typedef uint64_t undefined8;


/* ===== PUBLIC API (called from other modules; graph api set, 60) ===== */
void switch_to_dfu_mode(unsigned int param_1);                           /* @0x158bc */
unsigned int get_device_info(void);                                      /* @0x167a8 */
unsigned char get_current_work_mode(void);                               /* @0x16940 */
void change_work_mode_to(unsigned int work_mode);                        /* @0x1694c */
void FUN_0001793c(int param_1, int param_2, int param_3);                /* @0x1793c */  /* watchdog/keepalive callback: pets task @+0xb0 when arg==0x200 */
void FUN_00018300(int param_1, unsigned int param_2);                    /* @0x18300 */  /* event handler: on code 0x1f2 forces change_work_mode_to(1) */
unsigned int FUN_00019b2c(void);                                         /* @0x19b2c */  /* getter: reads global status word @0x20007518 */
int FUN_00022834(int param_1, int param_2, int param_3);                 /* @0x22834 verified */  /* flash settings read+verify+rewrite w/ retry (10x) */
int FUN_00022b00(int param_1);                                           /* @0x22b00 verified */  /* zero+erase a 0x78B settings block in flash @0x130000 */
unsigned int reset_usr_setting(char *param_1);                           /* @0x22ddc */
void FUN_0002542c(void);                                                 /* @0x2542c verified */  /* latch/snapshot counter 0x20007a34 -> 0x20007a24 */
void send_event(int param_1, unsigned int param_2, unsigned int param_3); /* @0x276ec */
void FUN_00028a1c(char *param_1, int32_t param_2, uint32_t param_3);     /* @0x28a1c verified */  /* THREAD MAIN: key/click loop (single/double/triple click, factory) */
int init_watchdog(int param_1,int param_2,int param_3,int param_4);      /* @0x2ace0 */
int FUN_0002ae84(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x2ae84 verified */  /* watchdog feed: WDT feed-op retry via handle @0x20007b50 */
void FUN_0002c324(void);                                                 /* @0x2c324 verified */  /* post-charge/box state settle + rebind */
int FUN_00030224(void);                                                  /* @0x30224 verified */  /* replay display/periph config table @0x8a0a8 (0x58 regs) */
int FUN_000302f8(unsigned int param_1, unsigned int *param_2, int param_3); /* @0x302f8 verified */  /* thin wrapper of FUN_0003016c */
void FUN_00030c90(void);                                                 /* @0x30c90 verified */  /* getter wrapper (FUN_00030b3c) */
unsigned FUN_00031bd8(int param_1, unsigned param_2, uint32_t *param_3, uint8_t *param_4); /* @0x31bd8 */  /* SN/provisioning field read from device_info */
unsigned FUN_00031dd8(unsigned param_1, unsigned param_2, unsigned **param_3, unsigned char *param_4); /* @0x31dd8 */  /* SN/provisioning write (flash erase+program) */
uint32_t set_glasses_sn_info(int param_1, uint32_t param_2, uint32_t *param_3, uint8_t *param_4); /* @0x31ee8 */
unsigned get_assign_channel_info(int param_1, unsigned param_2, unsigned *param_3, unsigned char *param_4); /* @0x31fd8 */
uint32_t set_device_sn_info(int param_1, uint32_t param_2, uint32_t *param_3, uint8_t *param_4); /* @0x32164 */
int FUN_00032308(int param_1, unsigned param_2, uint32_t *param_3, uint8_t *param_4); /* @0x32308 */  /* SN/provisioning write variant (flash erase+program) */
void FUN_00033b0c(unsigned int param_1, unsigned int param_2, unsigned int param_3); /* @0x33b0c verified */  /* work-mode substate debug/log setter */
void FUN_00033c5c(void);                                                 /* @0x33c5c verified */  /* glass-box/bind substate read from device_info */
unsigned int FUN_00033cdc(void);                                         /* @0x33cdc verified */  /* work-mode substate getter */
uint32_t FUN_00033cf8(void);                                             /* @0x33cf8 verified */  /* work-mode/box substate getter */
void FUN_0003439c(void);                                                 /* @0x3439c verified */  /* work-mode substate apply/notify */
void FUN_0003441c(void);                                                 /* @0x3441c verified */  /* work-mode substate getter */
void FUN_0003443c(int param_1);                                          /* @0x3443c */  /* work-mode substate reset (calls 0x3441c) */
int FUN_0003483c(int param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4); /* @0x3483c verified */  /* settings/NVS key write helper */
undefined4 FUN_000362e8(int param_1,undefined4 param_2);                 /* @0x362e8 */  /* status/notification frame composer (display) */
void FUN_000429f8(void);                                                 /* @0x429f8 */  /* display-state getter from device_info */
void FUN_000440ec(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9); /* @0x440ec */  /* draw/format routine (9-arg render) */
unsigned FUN_0004d334(int param_1,int param_2);                          /* @0x4d334 */  /* peripheral sequence w/ delay */
unsigned int FUN_00062070(int param_1, int param_2, unsigned short *param_3); /* @0x62070 */  /* small getter */
void FUN_00062f28(int param_1, unsigned char param_2);                   /* @0x62f28 */  /* I2C/register RMW under mutex */
uint32_t FUN_00074844(int param_1,int param_2,int param_3,int param_4);  /* @0x74844 */  /* TIMING PRIMITIVE: ms delay/sleep (widely shared) */
void FUN_00076a94(void);                                                 /* @0x76a94 verified */  /* container/buffer library op */
void FUN_00076cec(int param_1,int *param_2,int param_3);                 /* @0x76cec verified */  /* container/buffer library op */
void FUN_00076d6c(unsigned int param_1);                                 /* @0x76d6c verified */  /* container/buffer library op */
u32 FUN_00077594(u32 param_1, u32 *param_2, u32 param_3, u32 param_4, int *param_5); /* @0x77594 verified */  /* container/buffer library op */
void FUN_000777f0(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x777f0 verified */  /* container/buffer library op */
undefined4 FUN_00077e70(volatile undefined4 *param_1,volatile uint *param_2,volatile undefined4 *param_3); /* @0x77e70 verified */  /* container/buffer library op */
void FUN_000785bc(void);                                                 /* @0x785bc verified */  /* container/buffer library op */
void FUN_000785c8(void);                                                 /* @0x785c8 verified */  /* container/buffer library op */
int FUN_00078d90(undefined4 *param_1, int *param_2, byte *param_3, uint *param_4); /* @0x78d90 */  /* container/buffer library op */
void FUN_0007c038(int param_1);                                          /* @0x7c038 verified */  /* device_info typed accessor */
int FUN_0007c132(unsigned int param_1, unsigned int param_2);            /* @0x7c132 */  /* device_info typed accessor */
void FUN_0007c176(unsigned char param_1, unsigned char param_2);         /* @0x7c176 */  /* device_info setter (BLE put-req path) */
unsigned int FUN_0007c1aa(unsigned int param_1, unsigned int param_2, unsigned char param_3, int param_4); /* @0x7c1aa */  /* device_info setter (BLE put-req path) */
unsigned int FUN_0007c61e(unsigned char *param_1, unsigned char *param_2); /* @0x7c61e */  /* device_info accessor (via 0x7c408) */
void FUN_0007cb8e(int param_1);                                          /* @0x7cb8e verified */  /* TIMING PRIMITIVE: ms sleep wrapper */
int FUN_0007ce00(void);                                                  /* @0x7ce00 verified */  /* device_info accessor (BLE get/put path) */
void FUN_0007d14a(int param_1);                                          /* @0x7d14a verified */  /* device_info accessor */
void FUN_0007db02(int param_1, int param_2, int param_3, int param_4);   /* @0x7db02 verified */  /* locked accessor / status */
void FUN_00083bca(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x83bca verified */  /* locked accessor (crc/compose) */
int FUN_00083bf0(int param_1, unsigned param_2, int param_3);            /* @0x83bf0 verified */  /* locked accessor under mutex */

/* ===== ENTRY POINTS (thread mains / callbacks; no in-module caller) ===== */
int FUN_00016110(int param_1, unsigned int param_2, int param_3);        /* @0x16110 */
void reset_all_static_info(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x16738 */
int FUN_000250f8(char *param_1, char *param_2, char *param_3);           /* @0x250f8 */
int FUN_00025290(void);                                                  /* @0x25290 verified */
void FUN_000254a0(int param_1, unsigned char *param_2);                  /* @0x254a0 verified */
int FUN_0002560c(void);                                                  /* @0x2560c verified */
int FUN_0002563c(int param_1);                                           /* @0x2563c verified */
unsigned int serialization_init(void);                                   /* @0x25c54 */
int FUN_00026c28(void);                                                  /* @0x26c28 verified */
void try_enter_low_power_mode(void);                                     /* @0x26c8c */
void check_work_mode(int param_1,int param_2,int param_3);               /* @0x27758 */
void FUN_000289b0(void);                                                 /* @0x289b0 verified */
void FUN_0002c2b0(void);                                                 /* @0x2c2b0 verified */
unsigned FUN_0002c3dc(void);                                             /* @0x2c3dc verified */
undefined4 process_for_message_show(char *param_1,int param_2,byte *param_3,undefined4 *param_4); /* @0x2c714 */
unsigned int FUN_0002ea78(void);                                         /* @0x2ea78 */
unsigned int FUN_0002efe4(int param_1);                                  /* @0x2efe4 verified */

/* ===== INTERNAL HELPERS (module-private; auto-named FUN_*, reconstructed) ===== */
byte FUN_00010840(void);                                                 /* @0x10840 */
double FUN_00012c80(int param_1, double dparam);                         /* @0x12c80 */
double FUN_00012db0(double xd, u4 param_1, u4 param_2, u4 param_3, u4 param_4); /* @0x12db0 */
unsigned int FUN_000167f4(void);                                         /* @0x167f4 verified */
unsigned int global_system_resume(unsigned int param_1, int param_2);    /* @0x16854 */
unsigned int FUN_000232b0(void);                                         /* @0x232b0 */
unsigned int FUN_000232c0(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4); /* @0x232c0 */
unsigned int FUN_000232dc(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4); /* @0x232dc */
char FUN_00024cc8(int param_1);                                          /* @0x24cc8 verified */
int FUN_00024d50(unsigned int param_1, unsigned int param_2, unsigned int param_3); /* @0x24d50 */
int FUN_00024d74(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x24d74 verified */
int FUN_00024dac(unsigned param_1, unsigned param_2, unsigned param_3, unsigned param_4); /* @0x24dac verified */
int FUN_00024f08(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x24f08 verified */
void FUN_00024f40(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x24f40 verified */
int FUN_00024f78(void);                                                  /* @0x24f78 verified */
unsigned int FUN_00024fe8(unsigned int param_1, unsigned short param_2); /* @0x24fe8 verified */
unsigned int FUN_00025090(unsigned char *param_1, unsigned int *param_2); /* @0x25090 */
unsigned int FUN_000250c4(unsigned char *param_1, unsigned int *param_2); /* @0x250c4 */
unsigned int FUN_00025364(void);                                         /* @0x25364 verified */
unsigned int FUN_00025458(void);                                         /* @0x25458 verified */
unsigned int FUN_00025474(void);                                         /* @0x25474 verified */
void FUN_000254d8(int param_1, char* param_2);                           /* @0x254d8 verified */
uint32_t FUN_00025528(uint32_t param_1, uint32_t param_2);               /* @0x25528 verified */
int FUN_000256dc(int param_1, unsigned param_2, unsigned param_3, int param_4); /* @0x256dc verified */
int FUN_00025740(int param_1, int param_2, unsigned int param_3, int param_4, int param_5); /* @0x25740 verified */
int FUN_00025788(int param_1, unsigned param_2, unsigned param_3, int param_4); /* @0x25788 verified */
int FUN_000257ec(int param_1, unsigned param_2, unsigned param_3, int param_4); /* @0x257ec verified */
int FUN_00025850(int param_1, unsigned param_2, unsigned param_3, int param_4); /* @0x25850 verified */
int FUN_000259d4(void);                                                  /* @0x259d4 verified */
void FUN_0002a4d8(unsigned int param_1);                                 /* @0x2a4d8 verified */
unsigned int global_system_suspend(void *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x2bd7c */
unsigned int FUN_0002ead8(int param_1, unsigned int param_2);            /* @0x2ead8 */
void FUN_0002eb28(unsigned int param_1,int param_2);                     /* @0x2eb28 verified */
unsigned int FUN_0002eb78(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4); /* @0x2eb78 verified */
unsigned int FUN_0002eba0(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4); /* @0x2eba0 verified */
void FUN_0002ebc8(void);                                                 /* @0x2ebc8 verified */
void FUN_0003016c(void);                                                 /* @0x3016c verified */
unsigned int FUN_00030178(unsigned int param_1, unsigned int param_2, unsigned int param_3); /* @0x30178 verified */
int FUN_000301bc(unsigned p1,unsigned p2,unsigned p3,unsigned p4);       /* @0x301bc verified */
int FUN_00030288(int param_1);                                           /* @0x30288 verified */
int FUN_000302cc(void);                                                  /* @0x302cc verified */
int FUN_000304f0(unsigned int param_1, unsigned int param_2, unsigned int param_3); /* @0x304f0 verified */
int FUN_00030528(char *param_1, unsigned int param_2, int param_3, int param_4); /* @0x30528 verified */
int FUN_00030710(void);                                                  /* @0x30710 verified */
undefined4 FUN_00030754(int param_1);                                    /* @0x30754 verified */
int FUN_00030b3c(int *param_1);                                          /* @0x30b3c verified */
void FUN_00030cb8(void);                                                 /* @0x30cb8 verified */
void FUN_00030cc4(void);                                                 /* @0x30cc4 verified */
unsigned int FUN_00030cd0(int param_1,int param_2,unsigned char *param_3,int param_4); /* @0x30cd0 verified */
uint32_t FUN_00031b60(int param_1,uint32_t param_2,uint32_t *param_3,char *param_4); /* @0x31b60 */
void FUN_0003271c(void);                                                 /* @0x3271c */
uint32_t FUN_00032b24(int param_1, char* param_2, int param_3, int* param_4, uint8_t* param_5, uint32_t param_6); /* @0x32b24 */
void FUN_00032fd0(unsigned char param_1);                                /* @0x32fd0 */
int FUN_00033088(int param_1);                                           /* @0x33088 */
unsigned int FUN_000330a8(unsigned int param_1);                         /* @0x330a8 */
unsigned process_pt_data(unsigned param_1);                              /* @0x330ec */
unsigned int FUN_000332dc(void);                                         /* @0x332dc verified */
int FUN_00033340(void);                                                  /* @0x33340 verified */
uint8_t FUN_00033c04(int param_1);                                       /* @0x33c04 */
unsigned char FUN_00034274(void);                                        /* @0x34274 verified */
unsigned char pull_message(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x342e0 */
unsigned char FUN_00034410(void);                                        /* @0x34410 */
int FUN_000347cc(void);                                                  /* @0x347cc verified */
int FUN_00034808(void);                                                  /* @0x34808 */
void FUN_00036558(int param_1,int param_2,int param_3,int param_4);      /* @0x36558 verified */
void FUN_000365ec(void);                                                 /* @0x365ec verified */
void FUN_0003678c(int param_1,int param_2,unsigned param_3,unsigned param_4); /* @0x3678c verified */
void FUN_00036820(unsigned param_1);                                     /* @0x36820 verified */
unsigned FUN_00036a18(int param_1,unsigned param_2,int param_3,int param_4); /* @0x36a18 verified */
unsigned int FUN_000406e4(void);                                         /* @0x406e4 */
int FUN_00047a84(int param_1, int *param_2, int *param_3);               /* @0x47a84 */
void FUN_00047ab8(void);                                                 /* @0x47ab8 */
int get_boot_seconds(void);                                              /* @0x4a51c */
uint32_t FUN_0004cbec(int param_1, int *param_2, int param_3);           /* @0x4cbec */
void FUN_0004df88(void);                                                 /* @0x4df88 */
int FUN_00051074(int param_1);                                           /* @0x51074 verified */
uint FUN_000559fc(void);                                                 /* @0x559fc */
int FUN_00062644(int param_1);                                           /* @0x62644 */
int FUN_00063984(int param_1, int *param_2, unsigned int param_3, unsigned int param_4); /* @0x63984 */
void FUN_00076cc8(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4); /* @0x76cc8 verified */
uint FUN_00076e20(uint *param_1, uint param_2, uint param_3, uint param_4); /* @0x76e20 verified */
void FUN_000778f4(int *param_1,unsigned int param_2);                    /* @0x778f4 verified */
void FUN_00077e4c(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x77e4c verified */
byte *FUN_00078110(int param_1, int *param_2, int *param_3, int *param_4, int *param_5, uint param_6); /* @0x78110 verified */
void FUN_00078570(int *param_1,unsigned int param_2);                    /* @0x78570 verified */
unsigned int* FUN_000785d4(int param_1,unsigned int param_2);            /* @0x785d4 verified */
void FUN_00078654(int param_1, unsigned int *param_2);                   /* @0x78654 verified */
int FUN_00078698(int param_1,int param_2,int param_3,unsigned param_4);  /* @0x78698 verified */
void FUN_00078728(unsigned param_1, int param_2, int param_3, int param_4, unsigned param_5); /* @0x78728 verified */
void FUN_000787bc(int param_1, int param_2);                             /* @0x787bc verified */
void FUN_000787e8(unsigned param_1, int param_2, int param_3);           /* @0x787e8 verified */
uint32_t FUN_0007893c(int param_1, uint32_t param_2, uint param_3, uint32_t param_4); /* @0x7893c verified */
int FUN_000789f0(uint32_t param_1, int param_2, uint32_t param_3);       /* @0x789f0 verified */
int FUN_00078ac8(int param_1,int param_2,int param_3,int param_4);       /* @0x78ac8 verified */
double FUN_00078c44(int param_1);                                        /* @0x78c44 verified */
int FUN_00078ce0(unsigned a0, unsigned a1, unsigned a2);                 /* @0x78ce0 */
int FUN_0007c108(void);                                                  /* @0x7c108 */
unsigned int FUN_0007c1dc(unsigned char param_1, unsigned char param_2, int param_3); /* @0x7c1dc */
void FUN_0007c26e(int param_1);                                          /* @0x7c26e verified */
int FUN_0007c3d0(unsigned param_1, unsigned param_2);                    /* @0x7c3d0 */
unsigned char * FUN_0007c3ea(unsigned char *param_1);                    /* @0x7c3ea verified */
unsigned int FUN_0007c408(int param_1);                                  /* @0x7c408 verified */
int FUN_0007c41c(unsigned int param_1);                                  /* @0x7c41c verified */
unsigned int FUN_0007c430(unsigned char *param_1, unsigned int param_2, int *param_3); /* @0x7c430 verified */
int FUN_0007c456(unsigned char *param_1, int *param_2);                  /* @0x7c456 verified */
unsigned int FUN_0007c48a(uint8_t *param_1, int *param_2);               /* @0x7c48a verified */
unsigned int FUN_0007c4b6(unsigned char *param_1);                       /* @0x7c4b6 verified */
unsigned FUN_0007c4f4(int *param_1, unsigned char *param_2);             /* @0x7c4f4 verified */
unsigned FUN_0007c5ba(unsigned char* param_1, int* param_2);             /* @0x7c5ba */
int FUN_0007c670(int param_1, int *param_2, int param_3);                /* @0x7c670 */
int FUN_0007c6a0(int param_1, int *param_2);                             /* @0x7c6a0 */
int FUN_0007c754(int *param_1, int *param_2);                            /* @0x7c754 verified */
int FUN_0007c77e(int *param_1,int *param_2,int param_3,unsigned param_4); /* @0x7c77e */
unsigned int FUN_0007c7de(unsigned int *param_1, unsigned char *param_2); /* @0x7c7de verified */
unsigned int FUN_0007c830(int *param_1);                                 /* @0x7c830 */
void FUN_0007c842(int param_1);                                          /* @0x7c842 */
void FUN_0007c87a(void);                                                 /* @0x7c87a verified */
void FUN_0007c882(void *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x7c882 verified */
void FUN_0007c8d0(int param_1, int param_2);                             /* @0x7c8d0 */
unsigned int FUN_0007c8e8(unsigned int param_1, int param_2);            /* @0x7c8e8 */
void FUN_0007c8fa(int param_1, int param_2);                             /* @0x7c8fa */
unsigned int FUN_0007c932(unsigned int param_1, int param_2);            /* @0x7c932 */
unsigned int FUN_0007c944(unsigned int param_1, int param_2);            /* @0x7c944 */
unsigned int FUN_0007c956(unsigned int param_1, int param_2);            /* @0x7c956 */
int FUN_0007c968(unsigned int param_1, unsigned int *param_2, unsigned int param_3); /* @0x7c968 */
void FUN_0007c99e(int param_1, uint32_t *param_2);                       /* @0x7c99e */
void FUN_0007c9f2(unsigned int param_1,unsigned int param_2);            /* @0x7c9f2 */
void FUN_0007c9fe(unsigned int param_1,unsigned int param_2);            /* @0x7c9fe */
void FUN_0007ca18(unsigned int param_1,unsigned int param_2);            /* @0x7ca18 */
void FUN_0007ca24(int param_1, unsigned char *param_2);                  /* @0x7ca24 verified */
int FUN_0007cf70(void);                                                  /* @0x7cf70 verified */
int FUN_0007cfac(void);                                                  /* @0x7cfac verified */
int FUN_0007cfdc(unsigned int param_1, unsigned int param_2);            /* @0x7cfdc verified */
int FUN_0007d02a(unsigned int param_1, unsigned int param_2, unsigned int param_3); /* @0x7d02a verified */
int FUN_0007d05e(unsigned int param_1);                                  /* @0x7d05e verified */
unsigned FUN_0007d0e8(int param_1, int param_2, void *param_3, void *param_4); /* @0x7d0e8 */
int FUN_0007d16a(int *param_1, unsigned char *param_2);                  /* @0x7d16a */
void FUN_0007d194(int param_1);                                          /* @0x7d194 verified */
unsigned int FUN_0007d1c8(unsigned int *param_1);                        /* @0x7d1c8 */
void nullsub_2(void);                                                    /* @0x7d2d6 */
void FUN_0007d2f8(unsigned int param_1);                                 /* @0x7d2f8 */
int FUN_0007d4f8(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* @0x7d4f8 verified */
void FUN_0007d5f2(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7); /* @0x7d5f2 verified */
int FUN_0007d850(unsigned int param_1, unsigned int param_2, unsigned int param_3); /* @0x7d850 verified */
void FUN_0007dada(void);                                                 /* @0x7dada verified */
void FUN_0007e9ea(void);                                                 /* @0x7e9ea */
int FUN_000807de(int param_1);                                           /* @0x807de verified */
unsigned int FUN_000807e8(unsigned int param_1, int param_2);            /* @0x807e8 verified */
void FUN_00081320(int param_1);                                          /* @0x81320 */
int FUN_00083b62(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x83b62 verified */
int FUN_00083ba6(int param_1, unsigned int *param_2);                    /* @0x83ba6 verified */
void FUN_00083d60(int *param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4); /* @0x83d60 verified */
void FUN_00083d80(int param_1, unsigned char param_2, unsigned char param_3, unsigned int param_4, unsigned int param_5); /* @0x83d80 verified */
void FUN_00083dba(void);                                                 /* @0x83dba verified */
void FUN_00083dc8(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4); /* @0x83dc8 verified */
void FUN_00083de6(int *param_1, unsigned char param_2, unsigned int param_3, unsigned char param_4, unsigned char param_5); /* @0x83de6 verified */
int FUN_00083e70(int param_1, unsigned int param_2);                     /* @0x83e70 verified */
int FUN_00084068(int *param_1, int param_2, int param_3);                /* @0x84068 verified */
int FUN_00084090(int param_1, unsigned int param_2);                     /* @0x84090 verified */
int FUN_000840cc(int param_1, int param_2);                              /* @0x840cc verified */
void FUN_000842cc(int param_1, int param_2, unsigned int param_3, unsigned int param_4); /* @0x842cc */
unsigned FUN_000843ba(int param_1, int* param_2, int param_3);           /* @0x843ba verified */
int FUN_00084418(int param_1, u32 param_2, u32 param_3);                 /* @0x84418 verified */
unsigned FUN_00084602(int *param_1,int param_2,unsigned param_3,unsigned short *param_4); /* @0x84602 */
int FUN_00084774(int *param_1, int param_2);                             /* @0x84774 */
void FUN_0008496c(int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4); /* @0x8496c */
void FUN_00084ade(unsigned int param_1);                                 /* @0x84ade */
unsigned int FUN_00084c7e(void *param_1, int param_2);                   /* @0x84c7e */
unsigned int FUN_00084cb0(int param_1);                                  /* @0x84cb0 */
unsigned int FUN_000869dc(double param_1);                               /* @0x869dc */
unsigned int* FUN_00086b14(unsigned int param_1, int param_2);           /* @0x86b14 */
unsigned int FUN_00086b7e(unsigned int param_1,int param_2,unsigned int *param_3,unsigned int *param_4); /* @0x86b7e */
char * FUN_00086bc8(char *param_1, unsigned int param_2, int param_3);   /* @0x86bc8 verified */
uint32_t FUN_00086e1c(int param_1, uint* param_2, uint* param_3, int param_4, codef param_5); /* @0x86e1c */
unsigned int FUN_00087184(void *param_1, void *param_2);                 /* @0x87184 verified */
void FUN_0008729e(int param_1, uint param_2);                            /* @0x8729e verified */
char FUN_00087340(int param_1);                                          /* @0x87340 verified */
void FUN_0008736a(unsigned int *param_1, unsigned int *param_2, int param_3); /* @0x8736a verified */
unsigned int FUN_000873b6(int *param_1, unsigned int *param_2, unsigned int *param_3); /* @0x873b6 verified */
int FUN_00087510(unsigned int param_1);                                  /* @0x87510 verified */
int FUN_00087554(unsigned* param_1);                                     /* @0x87554 verified */
int FUN_000875ae(int param_1,int param_2);                               /* @0x875ae verified */
unsigned long long FUN_000875e4(int param_1, int param_2);               /* @0x875e4 verified */
int FUN_0008768e(char *param_1, unsigned int param_2);                   /* @0x8768e verified */
int FUN_000876d0(unsigned int param_1,int param_2,int param_3,unsigned int param_4); /* @0x876d0 verified */
int FUN_000876ec(unsigned int param_1,int param_2,unsigned int param_3,unsigned int param_4); /* @0x876ec verified */
unsigned FUN_00087736(uint32_t *param_1, int *param_2, unsigned param_3, unsigned param_4); /* @0x87736 verified */
uint32_t FUN_0008790e(uint32_t param_1,volatile int* param_2);           /* @0x8790e verified */
int FUN_00087996(unsigned int param_1,char *param_2);                    /* @0x87996 verified */

#endif /* G1_SYSTEM_H */
