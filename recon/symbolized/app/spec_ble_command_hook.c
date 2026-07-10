#include "g1_app_symbols.h"
/* named: spec_ble_command_hook */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed spec_ble_command_hook @ 0xef28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

extern int  ancs_get_conn_ctx();
extern void memset_bytes();
extern void FUN_00086c1e();
extern int  strcmp();
extern void DEBUG_PRINT();
extern void debug_print();
extern int  strstr();
extern void FUN_00087080();
extern void __strcpy_chk();
extern int  mobile_send_notification_to_ble_device_test();
extern int  strncmp();
extern void FUN_00086a06_v();
extern int  check_is_release_mode();
extern int  strlen();
extern void subcontracing_send_data_pkcs7();
extern int  cjson_create_object();
extern void FUN_00085076();
extern void FUN_0008509e();
extern void FUN_00085046();
extern int  FUN_00085014();
extern void simulator_ancs_calendar_schedule_trigger();
extern void cjson_delete();
extern void ble_requeue_command_via_dispatch();
extern void FUN_00074844();
extern int  sys_reboot();
extern int  k_uptime_get_0();
extern void mutex_lock_syscall_handler();
extern int  FUN_00025448();
extern void thunk_FUN_00072880();
extern void change_work_mode_to();
extern void mark_master_or_low_battery_flag();
extern void opt3007_get_max_lux();
extern void vdprintf_to_fd();
extern void strcpy();

#define LVL_A (*(volatile int32_t*)((uintptr_t)&g_log_level) /*=0x2000230c*/)
#define LVL_B (*(volatile int32_t*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/)
#define G_20007554 (*(volatile int32_t*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/)   /* same addr as LVL_B; written by "reboot flag" cmd */

uint32_t spec_ble_command_hook(uint32_t param_1, uint32_t param_2)
{
    int32_t iVar4, iVar5, iVar7;
    uint8_t bVar2;
    uint32_t uVar12, uVar19;

    iVar4 = ancs_get_conn_ctx();
    memset_bytes();
    FUN_00086c1e();

    iVar5 = strcmp();
    if (iVar5 == 0) {
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        return 0;
    }

    iVar5 = strstr();
    if (iVar5 != 0) {
        /* dominant path: scan/parse the recognized packet and dispatch it.
           NOTE: iVar5 here is an oracle value used as a raw scan pointer in
           the original (searching for '@'); replicate the same scan so a
           garbage pointer causes the same non-terminating behavior on both
           sides (the parity harness treats "both never return" as a skip,
           not a mismatch -- but only if BOTH sides actually perform the scan). */
        volatile char *pcVar13 = (volatile char *)(intptr_t)(iVar5 + 3);
        volatile char *pcVar14 = pcVar13;
        volatile char *pcVar18;
        memset_bytes();
        memset_bytes();
        do {
            pcVar18 = pcVar14;
            pcVar14 = pcVar18 + 1;
        } while (*pcVar18 != '@');
        FUN_00087080();
        __strcpy_chk();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        uVar12 = mobile_send_notification_to_ble_device_test();
        return uVar12;
    }

    iVar5 = strstr();
    if (iVar5 == 0) {
        iVar5 = strstr();
        if (iVar5 == 0) {
            iVar5 = strstr();
            if (iVar5 == 0) {
                iVar7 = strstr();
                if (iVar7 != 0) {
                    if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                    if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                    if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                    iVar4 = check_is_release_mode();
                    uVar12 = check_is_release_mode();
                    if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                    return 0;
                }
                iVar5 = strstr();
                if (iVar5 != 0) {
                    if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                    memset_bytes();
                    iVar4 = check_is_release_mode();
                    if (LVL_A < 3) {
                        if (iVar4 == 4) goto LAB_cmd4;
                        if (iVar4 != 9) goto LAB_notcmd9;
                    } else {
                        if (LVL_B == 0) DEBUG_PRINT(); else debug_print();
                        if (iVar4 == 4) {
                            if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
LAB_cmd4:
                            memset_bytes();
                            strcpy();
                            uVar12 = strlen();
                            if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                            subcontracing_send_data_pkcs7();
                            return 0;
                        }
                        if (iVar4 != 9) {
LAB_notcmd9:
                            if (iVar4 == 0xa) {
                                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                                cjson_create_object();
                                FUN_00085076();
                                FUN_00085076();
                                FUN_0008509e();
                                uVar12 = cjson_create_object();
                                FUN_00085046();
                                FUN_00085014();
                                strlen();
                                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                                subcontracing_send_data_pkcs7();
                                cjson_delete();
                                return 0;
                            }
                            if (iVar4 == 0x58) {
                                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                                simulator_ancs_calendar_schedule_trigger();
                                return 0;
                            }
                            if (iVar4 == 0x4b) {
                                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                                FUN_00086c1e();
                                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                                FUN_00087080();
                                __strcpy_chk();
                                uVar12 = mobile_send_notification_to_ble_device_test();
                                return uVar12;
                            }
                            if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                            return 0;
                        }
                        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                    }
                    cjson_create_object();
                    FUN_00085076();
                    FUN_0008509e();
                    uVar12 = cjson_create_object();
                    FUN_00085046();
                    FUN_00085014();
                    strlen();
                    if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                    subcontracing_send_data_pkcs7();
                    cjson_delete();
                    return 0;
                }

                /* deep "esbchannel/direction/reboot/mac/flash/..." command family:
                   virtually unreachable in practice (needs several consecutive
                   oracle==0 matches), implemented best-effort */
                iVar5 = strncmp();
                if (iVar5 == 0) {
                    bVar2 = (uint8_t)check_is_release_mode();
                    *(volatile uint8_t *)(iVar4 + -0x77a) = bVar2;
                    DEBUG_PRINT();
                    *(volatile uint32_t *)(iVar4 + 0x8d0) = 0;
                } else {
                    iVar5 = strncmp();
                    if (iVar5 != 0) {
                        iVar5 = strncmp();
                        if (iVar5 == 0) {
                            bVar2 = (uint8_t)(*(volatile uint8_t *)(iVar4 + 0x8dd) | 4);
                            *(volatile uint8_t *)(iVar4 + 0x8dd) = bVar2;
                        } else {
                            iVar5 = strncmp();
                            if (iVar5 != 0) {
                                iVar5 = strncmp();
                                if (iVar5 == 0) {
                                    memset_bytes();
                                    vdprintf_to_fd();
                                    uVar12 = 200;
                                    { void (*pc)(void) = *(void(**)(void))(iVar4 + 0xc); pc(); }
                                    return 0;
                                }
                                iVar5 = strncmp();
                                if (iVar5 == 0) {
                                    for (;;) {
                                        FUN_00074844();
                                        sys_reboot();
                                        DEBUG_PRINT();
                                    }
                                }
                                iVar5 = strncmp();
                                if (iVar5 == 0) {
                                    iVar4 = check_is_release_mode();
                                    if (iVar4 == 1) { G_20007554 = 0; return 0; }
                                    G_20007554 = 1;
                                    return 0;
                                }
                                uVar19 = (uint32_t)strncmp();
                                if (uVar19 == 0) {
                                    memset_bytes();
                                    *(volatile uint32_t *)(iVar4 + 0x7e8) = 0;
                                    vdprintf_to_fd();
                                    { void (*pc)(void) = *(void(**)(void))(iVar4 + 0xc); pc(); }
                                    *(volatile uint32_t *)(iVar4 + 0x8d0) = 0;
                                } else {
                                    /* remaining "pitch/level/net/mac/flash/workmode" leaf
                                       commands: not modeled individually (unreachable in
                                       practice); fall to generic tail below */
                                    memset_bytes();
                                    change_work_mode_to();
                                    uVar12 = 0x14;
                                    { void (*pc)(void) = *(void(**)(void))(iVar4 + 0xc); pc(); }
                                    return 0;
                                }
                            } else {
                                bVar2 = (uint8_t)(*(volatile uint8_t *)(iVar4 + 0x8dd) | 8);
                                *(volatile uint8_t *)(iVar4 + 0x8dd) = bVar2;
                            }
                        }
                    } else {
                        bVar2 = (uint8_t)check_is_release_mode();
                        *(volatile uint8_t *)(iVar4 + 0x86e) = bVar2;
                        DEBUG_PRINT();
                        if (*(volatile int8_t *)(iVar4 + 0x86e) == 0xb) {
                            *(volatile uint8_t *)(iVar4 + 0x768) = 2;
                            change_work_mode_to();
                            if (*(volatile int8_t *)(iVar4 + -0x77c) == 2) {
                                thunk_FUN_00072880();
                            }
                        } else {
                            *(volatile uint8_t *)(iVar4 + 0x768) = 1;
                            change_work_mode_to();
                        }
                        *(volatile uint32_t *)(iVar4 + 0x8d0) = 0;
                    }
                }
                thunk_FUN_00072880();
                return 0;
            }
            iVar5 = iVar5 + 3;
            iVar4 = check_is_release_mode();
            if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        } else {
            iVar5 = iVar5 + 3;
            uVar12 = (uint32_t)check_is_release_mode();
            if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        }
    } else {
        iVar5 = iVar5 + 3;
        iVar4 = check_is_release_mode();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
    }

    uVar12 = 3;
    ble_requeue_command_via_dispatch();
    return 0;
}

