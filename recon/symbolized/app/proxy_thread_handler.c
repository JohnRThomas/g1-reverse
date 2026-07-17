#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00047c48 @ 0x00047c48
 * public-name: proxy_thread_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   upgradeAppLanguageInfoToFlash            <= FUN_00023af0 @ 0x00023af0
 *   upgradeDashboardStartupModeInfoToFlash   <= FUN_00023bfc @ 0x00023bfc
 *   z_log_dropped_read_and_clear             <= FUN_0002f928 @ 0x0002f928
 *   sendAudioStreamFileToApp                 <= FUN_00047bf8 @ 0x00047bf8
 *   display_powerEvent                       <= FUN_00049a28 @ 0x00049a28
 *   get_synced_clock_time                    <= FUN_0004a4d0 @ 0x0004a4d0
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   mutex_unlock_syscall_handler             <= FUN_000745c8 @ 0x000745c8
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_9e9ea                             @ 0x0009e9ea
 *   rodata_9ea0a                             @ 0x0009ea0a
 *   rodata_a1027                             @ 0x000a1027
 *   rodata_a116d                             @ 0x000a116d
 *   rodata_a125e                             @ 0x000a125e
 *   rodata_ef081                             @ 0x000ef081
 *   rodata_ef0a1                             @ 0x000ef0a1
 *   rodata_ef0c9                             @ 0x000ef0c9
 *   rodata_ef0fb                             @ 0x000ef0fb
 *   rodata_ef135                             @ 0x000ef135
 *   rodata_ef16d                             @ 0x000ef16d
 *   rodata_ef1a8                             @ 0x000ef1a8
 *   rodata_ef1ea                             @ 0x000ef1ea
 *   rodata_ef214                             @ 0x000ef214
 *   rodata_ef260                             @ 0x000ef260
 *   rodata_ef29b                             @ 0x000ef29b
 *   rodata_ef2df                             @ 0x000ef2df
 *   rodata_ef2fc                             @ 0x000ef2fc
 *   rodata_ef338                             @ 0x000ef338
 *   rodata_ef377                             @ 0x000ef377
 *   rodata_ef3e2                             @ 0x000ef3e2
 *   rodata_ef40d                             @ 0x000ef40d
 *   rodata_ef437                             @ 0x000ef437
 *   rodata_ef472                             @ 0x000ef472
 *   rodata_ef76f                             @ 0x000ef76f
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_response_msgq                @ 0x2000392c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20007b38                               @ 0x20007b38
 *   g_2000a078                               @ 0x2000a078
 *   g_2000a07c                               @ 0x2000a07c
 *   g_2000a080                               @ 0x2000a080
 *   g_2000a084                               @ 0x2000a084
 *   g_2000a088                               @ 0x2000a088
 *   g_2000a08c                               @ 0x2000a08c
 *   g_2000ff04                               @ 0x2000ff04
 *   g_20011d81                               @ 0x20011d81
 *   g_2001d262                               @ 0x2001d262
 *   g_2001d263                               @ 0x2001d263
 *   g_2001d264                               @ 0x2001d264
 *   g_2001d26a                               @ 0x2001d26a
 *   g_2001d26e                               @ 0x2001d26e
 *   g_2001d34a                               @ 0x2001d34a
 *   g_2001d34b                               @ 0x2001d34b
 *   g_2001d431                               @ 0x2001d431
 *   g_2001d432                               @ 0x2001d432
 */
/* Reconstructed proxy_thread_handler @ 0x47c48  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

typedef uint8_t  undefined1;
typedef uint32_t undefined4;
typedef uint16_t ushort;
typedef uint8_t  byte;

/* external callees (K&R prototypes: accept any args) */
extern int DEBUG_PRINT();
extern int get_device_info();
extern int debug_print();
extern int upgradeAppLanguageInfoToFlash();
extern int upgradeDashboardStartupModeInfoToFlash();
extern int FUN_00023eec();
extern int FUN_0002f910();
extern int z_log_dropped_read_and_clear();
extern int sendAudioStreamFileToApp();
extern int display_powerEvent();
extern int get_synced_clock_time();
extern int k_msgq_get();
extern int mutex_unlock_syscall_handler();
extern int FUN_00074844();
extern int z_device_is_ready();
extern int memcpy();
extern int FUN_00086c1e();
extern int memset_bytes();
extern int change_work_mode_to();
extern int sync_to_slave();

void proxy_thread_handler(int param_1)
{
    int *piVar1;
    ushort *puVar2;
    byte *pbVar3;
    int *piVar4;
    int *piVar5;
    int *piVar6;
    int *piVar7;
    char *pcVar8;
    undefined4 uVar9;
    undefined1 *puVar10;
    char *pcVar11;
    int iVar12;
    undefined4 uVar13;
    undefined1 uVar14;
    int iVar15;
    int iVar16;
    int iVar17;
    ushort uVar18;
    int *piVar19;
    int (**pcVar20)();
    int iVar21;
    undefined1 *puVar22;
    char cVar23;
    undefined1 local_4c;
    char local_4b;
    undefined4 local_48;
    undefined4 local_44;
    undefined1 local_40[2];
    ushort local_3e;
    char local_3c;
    char local_3b;

    piVar1 = (int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    memset_bytes(local_40, 0, 0x18);
    if (*piVar1 < 3) goto LAB_00047c76;
    iVar16 = *(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar9 = ((unsigned long)&rodata_ef081) /*=0xef081*/;
    uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
LAB_00047c6a:
    if (iVar16 == 0) {
        DEBUG_PRINT(uVar9, uVar13);
    } else {
        debug_print();
    }
LAB_00047c76:
    do {
        if ((*(char *)(param_1 + 1) != '\x01') && (*(char *)(param_1 + 1) != '\b')) {
            if (-1 < (int)((uint32_t)*(ushort *)(param_1 + 0x105c) << 0x18)) {
                uVar9 = 0x8000;
                goto LAB_00047c86;
            }
            memset_bytes(local_40, 0, 0x18);
            iVar16 = k_msgq_get((void *)((unsigned long)&g_dashboard_response_msgq) /*=0x2000392c*/, local_40, 0xffffffff, 0xffffffff);
            cVar23 = local_3c;
            if (iVar16 == 0) {
                switch (local_40[0]) {
                case 0:
                    if (2 < *piVar1) {
                        if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            DEBUG_PRINT(((unsigned long)&rodata_ef0a1) /*=0xef0a1*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                        } else {
                            debug_print();
                        }
                    }
                    memset_bytes((void *)((unsigned long)&g_2001d432) /*=0x2001d432*/, 0, 0x14);
                    uVar18 = local_3e;
                    if (0x13 < local_3e) {
                        uVar18 = 0x14;
                    }
                    memcpy((void *)((unsigned long)&g_2001d432) /*=0x2001d432*/, &local_3c, uVar18);
                    *(ushort *)((unsigned long)&g_2000ff04) /*=0x2000ff04*/ = uVar18;
                    *(char *)((unsigned long)&g_2001d431) /*=0x2001d431*/ = '\x01';
                    goto LAB_00047c76;
                case 1:
                    if (2 < *piVar1) {
                        if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            DEBUG_PRINT(((unsigned long)&rodata_ef0c9) /*=0xef0c9*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                        } else {
                            debug_print();
                        }
                    }
                    pcVar11 = (char *)((unsigned long)&g_2001d431) /*=0x2001d431*/;
                    puVar2 = (ushort *)((unsigned long)&g_2000ff04) /*=0x2000ff04*/;
                    if (*(char *)((unsigned long)&g_2001d431) /*=0x2001d431*/ != '\0') {
                        iVar16 = (*(int (**)())(param_1 + 0x788))((void *)((unsigned long)&g_2001d432) /*=0x2001d432*/, *(ushort *)((unsigned long)&g_2000ff04) /*=0x2000ff04*/);
                        if ((iVar16 < 0) && (1 < *piVar1)) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                DEBUG_PRINT(((unsigned long)&rodata_ef0fb) /*=0xef0fb*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                            } else {
                                debug_print();
                            }
                        }
                        local_48 = 0;
                        local_44 = 0;
                        get_synced_clock_time(&local_48);
                        if (2 < *piVar1) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                DEBUG_PRINT(((unsigned long)&rodata_ef135) /*=0xef135*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, local_48, local_44);
                            } else {
                                debug_print(((unsigned long)&rodata_ef135) /*=0xef135*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                            }
                        }
                        *pcVar11 = '\0';
                        *puVar2 = 0;
                    }
                    goto LAB_00047c76;
                case 2:
                    if (2 < *piVar1) {
                        if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            DEBUG_PRINT(((unsigned long)&rodata_ef16d) /*=0xef16d*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                        } else {
                            debug_print();
                        }
                    }
                    pcVar8 = (char *)((unsigned long)&g_2001d263) /*=0x2001d263*/;
                    piVar7 = (int *)((unsigned long)&g_2000a080) /*=0x2000a080*/;
                    piVar6 = (int *)((unsigned long)&g_2000a078) /*=0x2000a078*/;
                    pcVar11 = (char *)((unsigned long)&g_2001d262) /*=0x2001d262*/;
                    piVar5 = (int *)((unsigned long)&g_2000a07c) /*=0x2000a07c*/;
                    piVar4 = (int *)((unsigned long)&g_2000a084) /*=0x2000a084*/;
                    piVar19 = (int *)((unsigned long)&g_2000a08c) /*=0x2000a08c*/;
                    pbVar3 = (byte *)((unsigned long)&g_2001d34a) /*=0x2001d34a*/;
                    if (local_3c == '\0') {
                        *(byte *)((unsigned long)&g_2001d34a) /*=0x2001d34a*/ = local_3b - 1;
                        piVar19 = (int *)((unsigned long)&rodata_87bf0) /*=0x87bf0*/;
                        iVar16 = z_device_is_ready((void *)((unsigned long)&rodata_87bf0) /*=0x87bf0*/);
                        piVar4 = (int *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/;
                        if (iVar16 == 0) goto LAB_00047de2;
                        memset_bytes((void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, 0, 0xe6);
                        iVar16 = get_device_info();
                        pcVar20 = *(int (***)())(iVar16 + 0x1030);
                        uVar9 = get_device_info();
                        iVar16 = (*pcVar20)(uVar9, 0x400000, piVar4, 0xe6);
                        piVar19 = (int *)((unsigned long)&g_2000a08c) /*=0x2000a08c*/;
                        if (iVar16 == 0) {
                            if ((*piVar4 == 0x5aa5aa5a) && (piVar4[(uint32_t)*pbVar3 * 5 + 2] == 2)) {
                                *(int *)((unsigned long)&g_2000a08c) /*=0x2000a08c*/ = piVar4[(uint32_t)*pbVar3 * 5 + 3];
                                *(int *)((unsigned long)&g_2000a088) /*=0x2000a088*/ = piVar4[(uint32_t)*pbVar3 * 5 + 4];
                            }
                            if (2 < *piVar1) {
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    DEBUG_PRINT(((unsigned long)&rodata_ef1a8) /*=0xef1a8*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print();
                                }
                            }
                            memset_bytes((void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, 0, 0xe6);
                            iVar16 = get_device_info();
                            pcVar20 = *(int (***)())(iVar16 + 0x1030);
                            uVar9 = get_device_info();
                            iVar16 = (*pcVar20)(uVar9, *piVar19, (void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, 0xbe);
                            piVar5 = (int *)((unsigned long)&g_2000a084) /*=0x2000a084*/;
                            piVar4 = (int *)((unsigned long)&g_2000a088) /*=0x2000a088*/;
                            if (iVar16 == 0) {
                                *(int *)((unsigned long)&g_2000a084) /*=0x2000a084*/ = (*(int *)((unsigned long)&g_2000a088) /*=0x2000a088*/ - *piVar19) / 0xbe;
                                iVar16 = *piVar4 - *piVar19;
                                if (iVar16 != (iVar16 / 0xbe) * 0xbe) {
                                    *piVar5 = *piVar5 + 1;
                                }
                                pcVar11 = (char *)((unsigned long)&g_2001d263) /*=0x2001d263*/;
                                piVar7 = (int *)((unsigned long)&g_2000a080) /*=0x2000a080*/;
                                piVar6 = (int *)((unsigned long)&g_2000a078) /*=0x2000a078*/;
                                piVar5 = (int *)((unsigned long)&g_2000a07c) /*=0x2000a07c*/;
                                puVar10 = (undefined1 *)((unsigned long)&g_2001d264) /*=0x2001d264*/;
                                *(int *)((unsigned long)&g_2000a080) /*=0x2000a080*/ = *piVar4 - *piVar19;
                                *pcVar11 = '\0';
                                *piVar5 = 0;
                                *piVar6 = 0;
                                memset_bytes(puVar10, 0, 0xe6);
                                *puVar10 = 0x1e;
                                puVar10[2] = 0;
                                piVar19 = (int *)((unsigned long)&g_2000a084) /*=0x2000a084*/;
                                puVar10[3] = *pcVar11;
                                uVar9 = ((unsigned long)&g_2001d34b) /*=0x2001d34b*/;
                                *pcVar11 = *pcVar11 + '\x01';
                                puVar10[4] = 2;
                                iVar16 = 3;
                                puVar10[5] = (char)*piVar19;
                                uVar13 = ((unsigned long)&g_2001d26e) /*=0x2001d26e*/;
                                puVar10[6] = (char)((uint32_t)*piVar19 >> 8);
                                puVar22 = (undefined1 *)((unsigned long)&g_2001d264) /*=0x2001d264*/;
                                *piVar5 = *piVar5 + 1;
                                puVar10[7] = (char)*piVar5;
                                puVar10[8] = (char)((uint32_t)*piVar5 >> 8);
                                puVar10[9] = *pbVar3 + 1;
                                piVar19 = (int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                                if (*piVar7 - *piVar6 < 0xbe) {
                                    iVar12 = *piVar7 - *piVar6;
                                } else {
                                    iVar12 = 0xbe;
                                }
                                FUN_00086c1e(uVar13, uVar9, iVar12, 0xdc);
                                puVar10[1] = (char)iVar12 + '\n';
                                while (iVar15 = (*(int (**)())(param_1 + 0x788))(puVar22, puVar10[1]), iVar15 < 0) {
                                    if (1 < *piVar1) {
                                        if (*piVar19 == 0) {
                                            DEBUG_PRINT(((unsigned long)&rodata_ef1ea) /*=0xef1ea*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                        } else {
                                            debug_print();
                                        }
                                    }
                                    iVar16 = iVar16 + -1;
                                    if (iVar16 == 0) {
                                        if (*piVar1 < 2) goto LAB_00047c76;
                                        iVar16 = *(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                                        uVar9 = ((unsigned long)&rodata_ef214) /*=0xef214*/;
                                        uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                                        goto LAB_00047c6a;
                                    }
                                    if (1 < *piVar1) {
                                        if (*piVar19 == 0) {
                                            DEBUG_PRINT(((unsigned long)&rodata_ef214) /*=0xef214*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                        } else {
                                            debug_print();
                                        }
                                    }
                                }
                                *(char *)((unsigned long)&g_2001d262) /*=0x2001d262*/ = '\x01';
                                *piVar6 = *piVar6 + iVar12;
                                FUN_0002f910(*pbVar3);
                                goto LAB_00048054;
                            }
                        }
LAB_00047e22:
                        if (0 < *piVar1) {
                            iVar16 = 0x400000;
                            iVar12 = *(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                            uVar9 = ((unsigned long)&rodata_9ea0a) /*=0x9ea0a*/;
                            uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                            goto LAB_00047e36;
                        }
                        goto LAB_00047c76;
                    }
                    if (local_3c != '\x01') goto LAB_00047c76;
                    if (*(char *)((unsigned long)&g_2001d262) /*=0x2001d262*/ == '\0') {
                        if (2 < *piVar1) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                DEBUG_PRINT(((unsigned long)&rodata_ef260) /*=0xef260*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                            } else {
                                debug_print();
                            }
                        }
LAB_00048082:
                        z_log_dropped_read_and_clear();
                        goto LAB_00047c76;
                    }
                    if (*(int *)((unsigned long)&g_2000a078) /*=0x2000a078*/ < *(int *)((unsigned long)&g_2000a080) /*=0x2000a080*/) {
                        memset_bytes((void *)((unsigned long)&g_2001d264) /*=0x2001d264*/, 0, 0xe6);
                        puVar10 = (undefined1 *)((unsigned long)&g_2001d264) /*=0x2001d264*/;
                        if (*(int *)((unsigned long)&g_2000a080) /*=0x2000a080*/ - *piVar6 < 0xbe) {
                            iVar16 = 0;
                            if (*(int *)((unsigned long)&g_2000a080) /*=0x2000a080*/ - *piVar6 < 0xbe) {
                                iVar16 = *(int *)((unsigned long)&g_2000a080) /*=0x2000a080*/ - *piVar6;
                            }
                        } else {
                            iVar16 = 0xbe;
                        }
                        *(undefined1 *)((unsigned long)&g_2001d264) /*=0x2001d264*/ = 0x1e;
                        puVar10[1] = (char)iVar16 + '\n';
                        puVar10[2] = 0;
                        uVar9 = ((unsigned long)&g_2001d34b) /*=0x2001d34b*/;
                        puVar10[3] = *pcVar8;
                        *pcVar8 = *pcVar8 + '\x01';
                        puVar10[4] = 2;
                        puVar10[5] = (char)*piVar4;
                        puVar10[6] = (char)((uint32_t)*piVar4 >> 8);
                        *piVar5 = *piVar5 + 1;
                        puVar10[7] = (char)*piVar5;
                        piVar4 = (int *)((unsigned long)&g_2000a078) /*=0x2000a078*/;
                        puVar10[8] = (char)((uint32_t)*piVar5 >> 8);
                        puVar10[9] = *(char *)((unsigned long)&g_2001d34a) /*=0x2001d34a*/ + '\x01';
                        memset_bytes(uVar9, 0, 0xe6);
                        iVar12 = get_device_info();
                        pcVar20 = *(int (***)())(iVar12 + 0x1030);
                        uVar9 = get_device_info();
                        iVar12 = (*pcVar20)(uVar9, *piVar4 + *piVar19, (void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, iVar16);
                        if (iVar12 != 0) {
                            if (0 < *piVar1) {
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    DEBUG_PRINT(((unsigned long)&rodata_9ea0a) /*=0x9ea0a*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, 0x400000);
                                } else {
                                    debug_print();
                                }
                            }
LAB_0004820e:
                            *pcVar11 = '\0';
                            goto LAB_00048082;
                        }
                        FUN_00086c1e(puVar10 + 10, (void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, iVar16, 0xdc);
                        piVar19 = (int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                        iVar12 = 3;
                        while (iVar15 = (*(int (**)())(param_1 + 0x788))(puVar10, puVar10[1]), iVar15 < 0) {
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(((unsigned long)&rodata_ef2df) /*=0xef2df*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print();
                                }
                            }
                            iVar12 = iVar12 + -1;
                            if (iVar12 == 0) {
                                if (1 < *piVar1) {
                                    if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                        DEBUG_PRINT(((unsigned long)&rodata_ef214) /*=0xef214*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                    } else {
                                        debug_print();
                                    }
                                }
                                goto LAB_0004820e;
                            }
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(((unsigned long)&rodata_ef2df) /*=0xef2df*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print();
                                }
                            }
                        }
                        *piVar4 = *piVar4 + iVar16;
                        if (2 < *piVar1) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                DEBUG_PRINT(((unsigned long)&rodata_ef2fc) /*=0xef2fc*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16, *piVar4);
                            } else {
                                debug_print(((unsigned long)&rodata_ef2fc) /*=0xef2fc*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16, *piVar4);
                            }
                        }
LAB_00048054:
                        sendAudioStreamFileToApp(1, 0);
                        goto LAB_00047c76;
                    }
                    *(char *)((unsigned long)&g_2001d262) /*=0x2001d262*/ = '\0';
                    *piVar4 = 0;
                    *piVar7 = 0;
                    piVar4 = (int *)((unsigned long)&g_2000a088) /*=0x2000a088*/;
                    *piVar6 = 0;
                    *pcVar8 = '\0';
                    *piVar5 = 0;
                    *piVar4 = 0;
                    *piVar19 = 0;
                    z_log_dropped_read_and_clear();
                    if (*piVar1 < 1) goto LAB_00047c76;
                    if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                        iVar16 = get_device_info();
                        iVar16 = **(int **)(iVar16 + 0xfec);
                        uVar9 = ((unsigned long)&rodata_ef29b) /*=0xef29b*/;
                        uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                        goto LAB_000480f4;
                    }
                    iVar16 = get_device_info();
                    iVar16 = **(int **)(iVar16 + 0xfec);
                    uVar9 = ((unsigned long)&rodata_ef29b) /*=0xef29b*/;
                    uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                    break;
                case 3:
                    if (2 < *piVar1) {
                        if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            DEBUG_PRINT(((unsigned long)&rodata_ef338) /*=0xef338*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                        } else {
                            debug_print();
                        }
                    }
                    piVar19 = (int *)((unsigned long)&rodata_87bf0) /*=0x87bf0*/;
                    iVar16 = z_device_is_ready((void *)((unsigned long)&rodata_87bf0) /*=0x87bf0*/);
                    if (iVar16 == 0) {
LAB_00047de2:
                        if (*piVar1 < 1) goto LAB_00047c76;
                        iVar16 = *piVar19;
                        iVar12 = *(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                        uVar9 = ((unsigned long)&rodata_9e9ea) /*=0x9e9ea*/;
                        uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                    } else {
                        memset_bytes((void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, 0, 0xe6);
                        iVar16 = get_device_info();
                        pcVar20 = *(int (***)())(iVar16 + 0x1030);
                        uVar9 = get_device_info();
                        iVar16 = (*pcVar20)(uVar9, 0x400000, (void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, 0xe6);
                        if (iVar16 != 0) goto LAB_00047e22;
                        puVar10 = (undefined1 *)memset_bytes((void *)((unsigned long)&g_2001d264) /*=0x2001d264*/, 0, 0xe6);
                        pcVar11 = (char *)((unsigned long)&g_2001d263) /*=0x2001d263*/;
                        if (local_3c == '\0') {
                            uVar14 = 0x1e;
                        } else {
                            uVar14 = 0x21;
                        }
                        *puVar10 = uVar14;
                        puVar10[2] = 0;
                        cVar23 = '\0';
                        puVar10[3] = *pcVar11;
                        *pcVar11 = *pcVar11 + '\x01';
                        puVar22 = (undefined1 *)((unsigned long)&g_2001d26a) /*=0x2001d26a*/;
                        iVar16 = ((unsigned long)&g_2001d34b) /*=0x2001d34b*/;
                        puVar10[4] = 1;
                        iVar12 = 0;
                        do {
                            iVar15 = iVar12 * 0x14 + iVar16;
                            iVar21 = iVar12 + 1;
                            if (2 < *piVar1) {
                                iVar17 = *(int *)(iVar15 + 0xc);
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    uVar9 = 0xef077;
                                    if (*(int *)(iVar15 + 8) != 2) {
                                        uVar9 = 0xef07c;
                                    }
                                    DEBUG_PRINT(((unsigned long)&rodata_ef377) /*=0xef377*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar21, uVar9, *(undefined4 *)(iVar15 + 0x14),
                                                *(undefined4 *)(iVar15 + 0x18), iVar17, *(int *)(iVar15 + 0x10),
                                                *(int *)(iVar15 + 0x10) - iVar17);
                                } else {
                                    uVar9 = 0xef077;
                                    if (*(int *)(iVar15 + 8) != 2) {
                                        uVar9 = 0xef07c;
                                    }
                                    debug_print(((unsigned long)&rodata_ef377) /*=0xef377*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar21, uVar9, *(undefined4 *)(iVar15 + 0x14),
                                                 *(undefined4 *)(iVar15 + 0x18), iVar17, *(int *)(iVar15 + 0x10),
                                                 *(int *)(iVar15 + 0x10) - iVar17);
                                }
                            }
                            iVar12 = iVar12 * 0x14 + iVar16;
                            puVar10 = puVar22;
                            if (*(int *)(iVar12 + 8) == 2) {
                                *puVar22 = (char)iVar21;
                                uVar9 = *(undefined4 *)(iVar12 + 0x14);
                                cVar23 = cVar23 + '\x01';
                                puVar22[1] = (char)uVar9;
                                puVar22[2] = (char)((uint32_t)uVar9 >> 8);
                                puVar22[3] = (char)((uint32_t)uVar9 >> 0x10);
                                puVar22[4] = (char)((uint32_t)uVar9 >> 0x18);
                                uVar9 = *(undefined4 *)(iVar12 + 0x18);
                                puVar10 = puVar22 + 9;
                                puVar22[5] = (char)uVar9;
                                puVar22[6] = (char)((uint32_t)uVar9 >> 8);
                                puVar22[7] = (char)((uint32_t)uVar9 >> 0x10);
                                puVar22[8] = (char)((uint32_t)uVar9 >> 0x18);
                            }
                            iVar15 = ((unsigned long)&g_2001d264) /*=0x2001d264*/;
                            iVar12 = iVar21;
                            puVar22 = puVar10;
                        } while (iVar21 != 4);
                        *(char *)(((unsigned long)&g_2001d264) /*=0x2001d264*/ + 1) = cVar23 * '\t' + '\x06';
                        piVar19 = (int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                        *(char *)(iVar15 + 5) = cVar23;
                        uVar13 = ((unsigned long)&rodata_ef3e2) /*=0xef3e2*/;
                        uVar9 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                        for (iVar16 = 0; iVar16 < (int)(uint32_t)*(byte *)(iVar15 + 1); iVar16 = iVar16 + 1) {
                            if (3 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(uVar13, uVar9, iVar16, (uint32_t)*(byte *)(iVar15 + iVar16));
                                } else {
                                    debug_print(uVar13, uVar9, iVar16, *(undefined1 *)(iVar15 + iVar16));
                                }
                            }
                        }
                        iVar16 = (*(int (**)())(param_1 + 0x788))((void *)((unsigned long)&g_2001d264) /*=0x2001d264*/, *(undefined1 *)(iVar15 + 1));
                        if ((-1 < iVar16) || (*piVar1 < 2)) goto LAB_00047c76;
                        iVar12 = *(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                        uVar9 = ((unsigned long)&rodata_ef0fb) /*=0xef0fb*/;
                        uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                    }
LAB_00047e36:
                    if (iVar12 == 0) {
LAB_000480f4:
                        DEBUG_PRINT(uVar9, uVar13, iVar16);
                        goto LAB_00047c76;
                    }
                    break;
                case 4:
                    iVar16 = 1;
                    *(uint16_t *)&local_48 = ((uint16_t)(uint8_t)local_3c << 8) | 7;
                    do {
                        uVar9 = get_device_info();
                        iVar12 = sync_to_slave(uVar9, 6, &local_48, 2);
                        if (iVar12 < 5000) {
                            if (2 < *piVar1) {
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    DEBUG_PRINT(((unsigned long)&rodata_ef40d) /*=0xef40d*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print();
                                }
                            }
                            display_powerEvent(cVar23);
                            mutex_unlock_syscall_handler();
                            break;
                        }
                        if (1 < *piVar1) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                DEBUG_PRINT(((unsigned long)&rodata_a125e) /*=0xa125e*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                            } else {
                                debug_print();
                            }
                        }
                        iVar16 = iVar16 + 1;
                    } while (iVar16 != 4);
                    goto LAB_00047c76;
                case 5:
                    iVar16 = 1;
                    *(uint16_t *)&local_48 = ((uint16_t)(uint8_t)local_3c << 8) | 8;
                    do {
                        uVar9 = get_device_info();
                        iVar12 = sync_to_slave(uVar9, 6, &local_48, 2);
                        if (iVar12 < 5000) {
                            if (2 < *piVar1) {
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    DEBUG_PRINT(((unsigned long)&rodata_ef437) /*=0xef437*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print();
                                }
                            }
                            upgradeAppLanguageInfoToFlash(cVar23);
                            break;
                        }
                        if (1 < *piVar1) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                DEBUG_PRINT(((unsigned long)&rodata_a125e) /*=0xa125e*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                            } else {
                                debug_print();
                            }
                        }
                        iVar16 = iVar16 + 1;
                    } while (iVar16 != 4);
                    goto LAB_00047c76;
                case 6:
                    iVar16 = 1;
                    local_4c = 9;
                    local_4b = local_3c;
                    do {
                        uVar9 = get_device_info();
                        iVar12 = sync_to_slave(uVar9, 6, &local_4c, 2);
                        if (iVar12 < 5000) {
                            if (2 < *piVar1) {
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    DEBUG_PRINT(((unsigned long)&rodata_ef472) /*=0xef472*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print();
                                }
                            }
                            local_48 = ((uint32_t)(uint8_t)*(char *)((unsigned long)&g_20011d81) /*=0x20011d81*/ << 24) | 0x608;
                            local_44 = (((uint32_t)((uint16_t)local_44 << 16) | ((uint8_t)cVar23 << 8)) & 0xffffff00) | 3;
                            iVar16 = (*(int (**)())(param_1 + 0x788))(&local_48, 6);
                            if ((iVar16 < 0) && (1 < *piVar1)) {
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    DEBUG_PRINT(((unsigned long)&rodata_ef0fb) /*=0xef0fb*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print();
                                }
                            }
                            upgradeDashboardStartupModeInfoToFlash(cVar23);
                            break;
                        }
                        if (1 < *piVar1) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                DEBUG_PRINT(((unsigned long)&rodata_a125e) /*=0xa125e*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                            } else {
                                debug_print();
                            }
                        }
                        iVar16 = iVar16 + 1;
                    } while (iVar16 != 4);
                    goto LAB_00047c76;
                case 7:
                    iVar16 = FUN_00023eec();
                    if (((iVar16 == 1) && (iVar16 = get_device_info(), *(char *)(iVar16 + 0xd5) == '\0')) &&
                        (pcVar11 = (char *)get_device_info(), *pcVar11 == '\x01')) {
                        iVar16 = get_device_info();
                        *(undefined1 *)(iVar16 + 0xfe6) = 5;
                        iVar16 = get_device_info();
                        iVar12 = get_device_info();
                        piVar19 = (int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                        *(undefined1 *)(iVar12 + 0xcb) = *(undefined1 *)(iVar16 + 0xed5);
                        uVar9 = get_device_info();
                        sync_to_slave(uVar9, 2, 0, 0);
                        change_work_mode_to(2);
                        *(uint16_t *)((char *)&local_48 + 0) = 0x10a;
                        iVar16 = 1;
                        do {
                            uVar9 = get_device_info();
                            iVar12 = sync_to_slave(uVar9, 6, &local_48, 2);
                            if (iVar12 < 5000) {
                                if (2 < *piVar1) {
                                    if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                        DEBUG_PRINT(((unsigned long)&rodata_a116d) /*=0xa116d*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                    } else {
                                        debug_print();
                                    }
                                }
                                *(int *)((unsigned long)&g_20007b38) /*=0x20007b38*/ = *(int *)((unsigned long)&g_20007b38) /*=0x20007b38*/ | 2;
                                break;
                            }
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(((unsigned long)&rodata_a1027) /*=0xa1027*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                                } else {
                                    debug_print();
                                }
                            }
                            iVar16 = iVar16 + 1;
                        } while (iVar16 != 4);
                    }
                    iVar16 = FUN_00023eec();
                    if ((((iVar16 == 1) && (iVar16 = get_device_info(), *(char *)(iVar16 + 0xd5) == '\x06')) ||
                         ((iVar16 = FUN_00023eec(), iVar16 == 2 &&
                          (iVar16 = get_device_info(), *(char *)(iVar16 + 0xd5) == '\x06')))) &&
                        (pcVar11 = (char *)get_device_info(), piVar19 = (int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/, *pcVar11 == '\x01')) {
                        *(uint16_t *)((char *)&local_48 + 0) = 0x10a;
                        iVar16 = 1;
                        do {
                            uVar9 = get_device_info();
                            iVar12 = sync_to_slave(uVar9, 6, &local_48, 2);
                            if (iVar12 < 5000) {
                                if (2 < *piVar1) {
                                    if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                        DEBUG_PRINT(((unsigned long)&rodata_a116d) /*=0xa116d*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                    } else {
                                        debug_print();
                                    }
                                }
                                *(int *)((unsigned long)&g_20007b38) /*=0x20007b38*/ = *(int *)((unsigned long)&g_20007b38) /*=0x20007b38*/ | 2;
                                break;
                            }
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(((unsigned long)&rodata_a1027) /*=0xa1027*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                                } else {
                                    debug_print();
                                }
                            }
                            iVar16 = iVar16 + 1;
                        } while (iVar16 != 4);
                    }
                    goto LAB_00047c76;
                default:
                    goto switchD_00047ccc_caseD_8;
                }
                debug_print(uVar9, uVar13, iVar16);
            }
            goto LAB_00047c76;
        }
        uVar9 = ((unsigned long)&rodata_28000) /*=0x28000*/;
LAB_00047c86:
        FUN_00074844(uVar9, 0);
    } while (1);
switchD_00047ccc_caseD_8:
    if (0 < *piVar1) goto code_r0x0004880a;
    goto LAB_00047c76;
code_r0x0004880a:
    iVar16 = *(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar9 = 0xef4b1;
    uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
    goto LAB_00047c6a;
}
