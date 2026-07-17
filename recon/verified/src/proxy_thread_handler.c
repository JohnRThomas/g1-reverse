/* Recovered proxy_thread_handler <= FUN_00047c48 @ 0x00047c48.
 * Reviewed image span is 0xbf8 bytes through 0x4883f.  The original catalog
 * stopped inside opcode seven at 0x486f8; live retry/default/atomic tails end
 * at 0x48815, followed by literals and independent FUN_00048840.
 * Durable reverse mapping: recon/catalogs/function_names_app.json.
 */
#include <stdint.h>

typedef uint8_t  undefined1;
typedef uint32_t undefined4;
typedef uint16_t ushort;
typedef uint8_t  byte;

typedef union {
    struct {
        uint8_t opcode;
        uint8_t reserved_01;
        uint16_t payload_length;
        int8_t subtype;
        int8_t value;
        uint8_t payload[18];
    } field;
    uint8_t bytes[24];
} proxy_message_t;

typedef union {
    struct {
        uint32_t low;
        uint32_t high;
    } word;
    uint64_t value;
    uint8_t bytes[8];
} proxy_transfer_packet_t;

typedef struct {
    uint8_t command;
    uint8_t value;
} proxy_short_packet_t;

/* Semantic aliases retain exact raw linker identities. */
#define get_device_info FUN_000167a8
#define debug_print FUN_00019c70
#define upgrade_language_setting FUN_00023af0
#define upgrade_dashboard_start_mode FUN_00023bfc
#define get_pending_language_code FUN_00023eec
#define set_current_audio_segment FUN_0002f910
#define finish_audio_proxy_transfer FUN_0002f928
#define enqueue_proxy_progress FUN_00047bf8
#define display_power_event FUN_00049a28
#define get_proxy_timestamp FUN_0004a4d0
#define receive_proxy_message FUN_00072240
#define reschedule_after_power_event FUN_000745c8
#define wait_for_proxy_event FUN_00074844
#define device_is_ready FUN_0008638c
#define copy_bytes FUN_00086c04
#define checked_copy_bytes FUN_00086c1e
#define clear_bytes FUN_00086c78

/* K&R prototypes are retained only at variadic/decompiler boundaries. */
extern int DEBUG_PRINT();
extern int get_device_info();
extern int debug_print();
extern int upgrade_language_setting();
extern int upgrade_dashboard_start_mode();
extern int get_pending_language_code();
extern int set_current_audio_segment();
extern int finish_audio_proxy_transfer();
extern int enqueue_proxy_progress();
extern int display_power_event();
extern int get_proxy_timestamp();
extern int receive_proxy_message();
extern int reschedule_after_power_event();
extern int wait_for_proxy_event();
extern int device_is_ready();
extern int copy_bytes();
extern int checked_copy_bytes();
extern int clear_bytes();
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
    proxy_short_packet_t short_packet;
    proxy_transfer_packet_t transfer_packet;
    proxy_message_t message;

    piVar1 = (int *)0x2000230c;
    clear_bytes(message.bytes, 0, 0x18);
    if (*piVar1 < 3) goto LAB_00047c76;
    iVar16 = *(int *)0x20007554;
    uVar9 = 0xef081;
    uVar13 = 0xef76f;
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
            clear_bytes(message.bytes, 0, 0x18);
            iVar16 = receive_proxy_message((void *)0x2000392c, message.bytes, 0xffffffff, 0xffffffff);
            cVar23 = message.field.subtype;
            if (iVar16 == 0) {
                switch (message.field.opcode) {
                case 0:
                    if (2 < *piVar1) {
                        if (*(int *)0x20007554 == 0) {
                            DEBUG_PRINT(0xef0a1, 0xef76f);
                        } else {
                            debug_print();
                        }
                    }
                    clear_bytes((void *)0x2001d432, 0, 0x14);
                    uVar18 = message.field.payload_length;
                    if (0x13 < message.field.payload_length) {
                        uVar18 = 0x14;
                    }
                    copy_bytes((void *)0x2001d432, &message.field.subtype, uVar18);
                    *(ushort *)0x2000ff04 = uVar18;
                    *(char *)0x2001d431 = '\x01';
                    goto LAB_00047c76;
                case 1:
                    if (2 < *piVar1) {
                        if (*(int *)0x20007554 == 0) {
                            DEBUG_PRINT(0xef0c9, 0xef76f);
                        } else {
                            debug_print();
                        }
                    }
                    pcVar11 = (char *)0x2001d431;
                    puVar2 = (ushort *)0x2000ff04;
                    if (*(char *)0x2001d431 != '\0') {
                        iVar16 = (*(int (**)())(param_1 + 0x788))((void *)0x2001d432, *(ushort *)0x2000ff04);
                        if ((iVar16 < 0) && (1 < *piVar1)) {
                            if (*(int *)0x20007554 == 0) {
                                DEBUG_PRINT(0xef0fb, 0xef76f);
                            } else {
                                debug_print();
                            }
                        }
                        transfer_packet.value = 0;
                        get_proxy_timestamp(transfer_packet.bytes);
                        if (2 < *piVar1) {
                            if (*(int *)0x20007554 == 0) {
                                DEBUG_PRINT(0xef135, 0xef76f,
                                            transfer_packet.word.low,
                                            transfer_packet.word.high);
                            } else {
                                debug_print(0xef135, 0xef76f);
                            }
                        }
                        *pcVar11 = '\0';
                        *puVar2 = 0;
                    }
                    goto LAB_00047c76;
                case 2:
                    if (2 < *piVar1) {
                        if (*(int *)0x20007554 == 0) {
                            DEBUG_PRINT(0xef16d, 0xef76f);
                        } else {
                            debug_print();
                        }
                    }
                    pcVar8 = (char *)0x2001d263;
                    piVar7 = (int *)0x2000a080;
                    piVar6 = (int *)0x2000a078;
                    pcVar11 = (char *)0x2001d262;
                    piVar5 = (int *)0x2000a07c;
                    piVar4 = (int *)0x2000a084;
                    piVar19 = (int *)0x2000a08c;
                    pbVar3 = (byte *)0x2001d34a;
                    if (message.field.subtype == '\0') {
                        *(byte *)0x2001d34a = message.field.value - 1;
                        piVar19 = (int *)0x87bf0;
                        iVar16 = device_is_ready((void *)0x87bf0);
                        piVar4 = (int *)0x2001d34b;
                        if (iVar16 == 0) goto LAB_00047de2;
                        clear_bytes((void *)0x2001d34b, 0, 0xe6);
                        iVar16 = get_device_info();
                        pcVar20 = *(int (***)())(iVar16 + 0x1030);
                        uVar9 = get_device_info();
                        iVar16 = (*pcVar20)(uVar9, 0x400000, piVar4, 0xe6);
                        piVar19 = (int *)0x2000a08c;
                        if (iVar16 == 0) {
                            if ((*piVar4 == 0x5aa5aa5a) && (piVar4[(uint32_t)*pbVar3 * 5 + 2] == 2)) {
                                *(int *)0x2000a08c = piVar4[(uint32_t)*pbVar3 * 5 + 3];
                                *(int *)0x2000a088 = piVar4[(uint32_t)*pbVar3 * 5 + 4];
                            }
                            if (2 < *piVar1) {
                                if (*(int *)0x20007554 == 0) {
                                    DEBUG_PRINT(0xef1a8, 0xef76f);
                                } else {
                                    debug_print();
                                }
                            }
                            clear_bytes((void *)0x2001d34b, 0, 0xe6);
                            iVar16 = get_device_info();
                            pcVar20 = *(int (***)())(iVar16 + 0x1030);
                            uVar9 = get_device_info();
                            iVar16 = (*pcVar20)(uVar9, *piVar19, (void *)0x2001d34b, 0xbe);
                            piVar5 = (int *)0x2000a084;
                            piVar4 = (int *)0x2000a088;
                            if (iVar16 == 0) {
                                *(int *)0x2000a084 = (*(int *)0x2000a088 - *piVar19) / 0xbe;
                                iVar16 = *piVar4 - *piVar19;
                                if (iVar16 != (iVar16 / 0xbe) * 0xbe) {
                                    *piVar5 = *piVar5 + 1;
                                }
                                pcVar11 = (char *)0x2001d263;
                                piVar7 = (int *)0x2000a080;
                                piVar6 = (int *)0x2000a078;
                                piVar5 = (int *)0x2000a07c;
                                puVar10 = (undefined1 *)0x2001d264;
                                *(int *)0x2000a080 = *piVar4 - *piVar19;
                                *pcVar11 = '\0';
                                *piVar5 = 0;
                                *piVar6 = 0;
                                clear_bytes(puVar10, 0, 0xe6);
                                *puVar10 = 0x1e;
                                puVar10[2] = 0;
                                piVar19 = (int *)0x2000a084;
                                puVar10[3] = *pcVar11;
                                uVar9 = 0x2001d34b;
                                *pcVar11 = *pcVar11 + '\x01';
                                puVar10[4] = 2;
                                iVar16 = 3;
                                puVar10[5] = (char)*piVar19;
                                uVar13 = 0x2001d26e;
                                puVar10[6] = (char)((uint32_t)*piVar19 >> 8);
                                puVar22 = (undefined1 *)0x2001d264;
                                *piVar5 = *piVar5 + 1;
                                puVar10[7] = (char)*piVar5;
                                puVar10[8] = (char)((uint32_t)*piVar5 >> 8);
                                puVar10[9] = *pbVar3 + 1;
                                piVar19 = (int *)0x20007554;
                                if (*piVar7 - *piVar6 < 0xbe) {
                                    iVar12 = *piVar7 - *piVar6;
                                } else {
                                    iVar12 = 0xbe;
                                }
                                checked_copy_bytes(uVar13, uVar9, iVar12, 0xdc);
                                puVar10[1] = (char)iVar12 + '\n';
                                while (iVar15 = (*(int (**)())(param_1 + 0x788))(puVar22, puVar10[1]), iVar15 < 0) {
                                    if (1 < *piVar1) {
                                        if (*piVar19 == 0) {
                                            DEBUG_PRINT(0xef1ea, 0xef76f);
                                        } else {
                                            debug_print();
                                        }
                                    }
                                    iVar16 = iVar16 + -1;
                                    if (iVar16 == 0) {
                                        if (*piVar1 < 2) goto LAB_00047c76;
                                        iVar16 = *(int *)0x20007554;
                                        uVar9 = 0xef214;
                                        uVar13 = 0xef76f;
                                        goto LAB_00047c6a;
                                    }
                                    if (1 < *piVar1) {
                                        if (*piVar19 == 0) {
                                            DEBUG_PRINT(0xef214, 0xef76f);
                                        } else {
                                            debug_print();
                                        }
                                    }
                                }
                                *(char *)0x2001d262 = '\x01';
                                *piVar6 = *piVar6 + iVar12;
                                set_current_audio_segment(*pbVar3);
                                goto LAB_00048054;
                            }
                        }
LAB_00047e22:
                        if (0 < *piVar1) {
                            iVar16 = 0x400000;
                            iVar12 = *(int *)0x20007554;
                            uVar9 = 0x9ea0a;
                            uVar13 = 0xef76f;
                            goto LAB_00047e36;
                        }
                        goto LAB_00047c76;
                    }
                    if (message.field.subtype != '\x01') goto LAB_00047c76;
                    if (*(char *)0x2001d262 == '\0') {
                        if (2 < *piVar1) {
                            if (*(int *)0x20007554 == 0) {
                                DEBUG_PRINT(0xef260, 0xef76f);
                            } else {
                                debug_print();
                            }
                        }
LAB_00048082:
                        finish_audio_proxy_transfer();
                        goto LAB_00047c76;
                    }
                    if (*(int *)0x2000a078 < *(int *)0x2000a080) {
                        clear_bytes((void *)0x2001d264, 0, 0xe6);
                        puVar10 = (undefined1 *)0x2001d264;
                        if (*(int *)0x2000a080 - *piVar6 < 0xbe) {
                            iVar16 = 0;
                            if (*(int *)0x2000a080 - *piVar6 < 0xbe) {
                                iVar16 = *(int *)0x2000a080 - *piVar6;
                            }
                        } else {
                            iVar16 = 0xbe;
                        }
                        *(undefined1 *)0x2001d264 = 0x1e;
                        puVar10[1] = (char)iVar16 + '\n';
                        puVar10[2] = 0;
                        uVar9 = 0x2001d34b;
                        puVar10[3] = *pcVar8;
                        *pcVar8 = *pcVar8 + '\x01';
                        puVar10[4] = 2;
                        puVar10[5] = (char)*piVar4;
                        puVar10[6] = (char)((uint32_t)*piVar4 >> 8);
                        *piVar5 = *piVar5 + 1;
                        puVar10[7] = (char)*piVar5;
                        piVar4 = (int *)0x2000a078;
                        puVar10[8] = (char)((uint32_t)*piVar5 >> 8);
                        puVar10[9] = *(char *)0x2001d34a + '\x01';
                        clear_bytes(uVar9, 0, 0xe6);
                        iVar12 = get_device_info();
                        pcVar20 = *(int (***)())(iVar12 + 0x1030);
                        uVar9 = get_device_info();
                        iVar12 = (*pcVar20)(uVar9, *piVar4 + *piVar19, (void *)0x2001d34b, iVar16);
                        if (iVar12 != 0) {
                            if (0 < *piVar1) {
                                if (*(int *)0x20007554 == 0) {
                                    DEBUG_PRINT(0x9ea0a, 0xef76f, 0x400000);
                                } else {
                                    debug_print();
                                }
                            }
LAB_0004820e:
                            *pcVar11 = '\0';
                            goto LAB_00048082;
                        }
                        checked_copy_bytes(puVar10 + 10, (void *)0x2001d34b, iVar16, 0xdc);
                        piVar19 = (int *)0x20007554;
                        iVar12 = 3;
                        while (iVar15 = (*(int (**)())(param_1 + 0x788))(puVar10, puVar10[1]), iVar15 < 0) {
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(0xef2df, 0xef76f);
                                } else {
                                    debug_print();
                                }
                            }
                            iVar12 = iVar12 + -1;
                            if (iVar12 == 0) {
                                if (1 < *piVar1) {
                                    if (*(int *)0x20007554 == 0) {
                                        DEBUG_PRINT(0xef214, 0xef76f);
                                    } else {
                                        debug_print();
                                    }
                                }
                                goto LAB_0004820e;
                            }
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(0xef2df, 0xef76f);
                                } else {
                                    debug_print();
                                }
                            }
                        }
                        *piVar4 = *piVar4 + iVar16;
                        if (2 < *piVar1) {
                            if (*(int *)0x20007554 == 0) {
                                DEBUG_PRINT(0xef2fc, 0xef76f, iVar16, *piVar4);
                            } else {
                                debug_print(0xef2fc, 0xef76f, iVar16, *piVar4);
                            }
                        }
LAB_00048054:
                        enqueue_proxy_progress(1, 0);
                        goto LAB_00047c76;
                    }
                    *(char *)0x2001d262 = '\0';
                    *piVar4 = 0;
                    *piVar7 = 0;
                    piVar4 = (int *)0x2000a088;
                    *piVar6 = 0;
                    *pcVar8 = '\0';
                    *piVar5 = 0;
                    *piVar4 = 0;
                    *piVar19 = 0;
                    finish_audio_proxy_transfer();
                    if (*piVar1 < 1) goto LAB_00047c76;
                    if (*(int *)0x20007554 == 0) {
                        iVar16 = get_device_info();
                        iVar16 = **(int **)(iVar16 + 0xfec);
                        uVar9 = 0xef29b;
                        uVar13 = 0xef76f;
                        goto LAB_000480f4;
                    }
                    iVar16 = get_device_info();
                    iVar16 = **(int **)(iVar16 + 0xfec);
                    uVar9 = 0xef29b;
                    uVar13 = 0xef76f;
                    break;
                case 3:
                    if (2 < *piVar1) {
                        if (*(int *)0x20007554 == 0) {
                            DEBUG_PRINT(0xef338, 0xef76f);
                        } else {
                            debug_print();
                        }
                    }
                    piVar19 = (int *)0x87bf0;
                    iVar16 = device_is_ready((void *)0x87bf0);
                    if (iVar16 == 0) {
LAB_00047de2:
                        if (*piVar1 < 1) goto LAB_00047c76;
                        iVar16 = *piVar19;
                        iVar12 = *(int *)0x20007554;
                        uVar9 = 0x9e9ea;
                        uVar13 = 0xef76f;
                    } else {
                        clear_bytes((void *)0x2001d34b, 0, 0xe6);
                        iVar16 = get_device_info();
                        pcVar20 = *(int (***)())(iVar16 + 0x1030);
                        uVar9 = get_device_info();
                        iVar16 = (*pcVar20)(uVar9, 0x400000, (void *)0x2001d34b, 0xe6);
                        if (iVar16 != 0) goto LAB_00047e22;
                        puVar10 = (undefined1 *)clear_bytes((void *)0x2001d264, 0, 0xe6);
                        pcVar11 = (char *)0x2001d263;
                        if (message.field.subtype == '\0') {
                            uVar14 = 0x1e;
                        } else {
                            uVar14 = 0x21;
                        }
                        *puVar10 = uVar14;
                        puVar10[2] = 0;
                        cVar23 = '\0';
                        puVar10[3] = *pcVar11;
                        *pcVar11 = *pcVar11 + '\x01';
                        puVar22 = (undefined1 *)0x2001d26a;
                        iVar16 = 0x2001d34b;
                        puVar10[4] = 1;
                        iVar12 = 0;
                        do {
                            iVar15 = iVar12 * 0x14 + iVar16;
                            iVar21 = iVar12 + 1;
                            if (2 < *piVar1) {
                                iVar17 = *(int *)(iVar15 + 0xc);
                                if (*(int *)0x20007554 == 0) {
                                    uVar9 = 0xef077;
                                    if (*(int *)(iVar15 + 8) != 2) {
                                        uVar9 = 0xef07c;
                                    }
                                    DEBUG_PRINT(0xef377, 0xef76f, iVar21, uVar9, *(undefined4 *)(iVar15 + 0x14),
                                                *(undefined4 *)(iVar15 + 0x18), iVar17, *(int *)(iVar15 + 0x10),
                                                *(int *)(iVar15 + 0x10) - iVar17);
                                } else {
                                    uVar9 = 0xef077;
                                    if (*(int *)(iVar15 + 8) != 2) {
                                        uVar9 = 0xef07c;
                                    }
                                    debug_print(0xef377, 0xef76f, iVar21, uVar9, *(undefined4 *)(iVar15 + 0x14),
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
                            iVar15 = 0x2001d264;
                            iVar12 = iVar21;
                            puVar22 = puVar10;
                        } while (iVar21 != 4);
                        *(char *)(0x2001d264 + 1) = cVar23 * '\t' + '\x06';
                        piVar19 = (int *)0x20007554;
                        *(char *)(iVar15 + 5) = cVar23;
                        uVar13 = 0xef3e2;
                        uVar9 = 0xef76f;
                        for (iVar16 = 0; iVar16 < (int)(uint32_t)*(byte *)(iVar15 + 1); iVar16 = iVar16 + 1) {
                            if (3 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(uVar13, uVar9, iVar16, (uint32_t)*(byte *)(iVar15 + iVar16));
                                } else {
                                    debug_print(uVar13, uVar9, iVar16, *(undefined1 *)(iVar15 + iVar16));
                                }
                            }
                        }
                        iVar16 = (*(int (**)())(param_1 + 0x788))((void *)0x2001d264, *(undefined1 *)(iVar15 + 1));
                        if ((-1 < iVar16) || (*piVar1 < 2)) goto LAB_00047c76;
                        iVar12 = *(int *)0x20007554;
                        uVar9 = 0xef0fb;
                        uVar13 = 0xef76f;
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
                    *(uint16_t *)transfer_packet.bytes =
                        ((uint16_t)(uint8_t)message.field.subtype << 8) | 7;
                    do {
                        uVar9 = get_device_info();
                        iVar12 = sync_to_slave(uVar9, 6,
                                              transfer_packet.bytes, 2);
                        if (iVar12 < 5000) {
                            if (2 < *piVar1) {
                                if (*(int *)0x20007554 == 0) {
                                    DEBUG_PRINT(0xef40d, 0xef76f);
                                } else {
                                    debug_print();
                                }
                            }
                            display_power_event(cVar23);
                            reschedule_after_power_event();
                            break;
                        }
                        if (1 < *piVar1) {
                            if (*(int *)0x20007554 == 0) {
                                DEBUG_PRINT(0xa125e, 0xef76f, iVar16);
                            } else {
                                debug_print();
                            }
                        }
                        iVar16 = iVar16 + 1;
                    } while (iVar16 != 4);
                    goto LAB_00047c76;
                case 5:
                    iVar16 = 1;
                    *(uint16_t *)transfer_packet.bytes =
                        ((uint16_t)(uint8_t)message.field.subtype << 8) | 8;
                    do {
                        uVar9 = get_device_info();
                        iVar12 = sync_to_slave(uVar9, 6,
                                              transfer_packet.bytes, 2);
                        if (iVar12 < 5000) {
                            if (2 < *piVar1) {
                                if (*(int *)0x20007554 == 0) {
                                    DEBUG_PRINT(0xef437, 0xef76f);
                                } else {
                                    debug_print();
                                }
                            }
                            upgrade_language_setting(cVar23);
                            break;
                        }
                        if (1 < *piVar1) {
                            if (*(int *)0x20007554 == 0) {
                                DEBUG_PRINT(0xa125e, 0xef76f, iVar16);
                            } else {
                                debug_print();
                            }
                        }
                        iVar16 = iVar16 + 1;
                    } while (iVar16 != 4);
                    goto LAB_00047c76;
                case 6:
                    iVar16 = 1;
                    short_packet.command = 9;
                    short_packet.value = message.field.subtype;
                    do {
                        uVar9 = get_device_info();
                        iVar12 = sync_to_slave(uVar9, 6, &short_packet, 2);
                        if (iVar12 < 5000) {
                            if (2 < *piVar1) {
                                if (*(int *)0x20007554 == 0) {
                                    DEBUG_PRINT(0xef472, 0xef76f);
                                } else {
                                    debug_print();
                                }
                            }
                            transfer_packet.word.low =
                                ((uint32_t)(uint8_t)*(char *)0x20011d81 << 24) |
                                0x608;
                            transfer_packet.word.high =
                                (((uint32_t)((uint16_t)transfer_packet.word.high << 16) |
                                  ((uint8_t)cVar23 << 8)) & 0xffffff00) | 3;
                            iVar16 = (*(int (**)())(param_1 + 0x788))(
                                transfer_packet.bytes, 6);
                            if ((iVar16 < 0) && (1 < *piVar1)) {
                                if (*(int *)0x20007554 == 0) {
                                    DEBUG_PRINT(0xef0fb, 0xef76f);
                                } else {
                                    debug_print();
                                }
                            }
                            upgrade_dashboard_start_mode(cVar23);
                            break;
                        }
                        if (1 < *piVar1) {
                            if (*(int *)0x20007554 == 0) {
                                DEBUG_PRINT(0xa125e, 0xef76f, iVar16);
                            } else {
                                debug_print();
                            }
                        }
                        iVar16 = iVar16 + 1;
                    } while (iVar16 != 4);
                    goto LAB_00047c76;
                case 7:
                    iVar16 = get_pending_language_code();
                    if (((iVar16 == 1) && (iVar16 = get_device_info(), *(char *)(iVar16 + 0xd5) == '\0')) &&
                        (pcVar11 = (char *)get_device_info(), *pcVar11 == '\x01')) {
                        iVar16 = get_device_info();
                        *(undefined1 *)(iVar16 + 0xfe6) = 5;
                        iVar16 = get_device_info();
                        iVar12 = get_device_info();
                        piVar19 = (int *)0x20007554;
                        *(undefined1 *)(iVar12 + 0xcb) = *(undefined1 *)(iVar16 + 0xed5);
                        uVar9 = get_device_info();
                        sync_to_slave(uVar9, 2, 0, 0);
                        change_work_mode_to(2);
                        *(uint16_t *)transfer_packet.bytes = 0x10a;
                        iVar16 = 1;
                        do {
                            uVar9 = get_device_info();
                            iVar12 = sync_to_slave(uVar9, 6,
                                                  transfer_packet.bytes, 2);
                            if (iVar12 < 5000) {
                                if (2 < *piVar1) {
                                    if (*(int *)0x20007554 == 0) {
                                        DEBUG_PRINT(0xa116d, 0xef76f);
                                    } else {
                                        debug_print();
                                    }
                                }
                                *(int *)0x20007b38 = *(int *)0x20007b38 | 2;
                                break;
                            }
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(0xa1027, 0xef76f, iVar16);
                                } else {
                                    debug_print();
                                }
                            }
                            iVar16 = iVar16 + 1;
                        } while (iVar16 != 4);
                    }
                    iVar16 = get_pending_language_code();
                    if ((((iVar16 == 1) && (iVar16 = get_device_info(), *(char *)(iVar16 + 0xd5) == '\x06')) ||
                         ((iVar16 = get_pending_language_code(), iVar16 == 2 &&
                          (iVar16 = get_device_info(), *(char *)(iVar16 + 0xd5) == '\x06')))) &&
                        (pcVar11 = (char *)get_device_info(), piVar19 = (int *)0x20007554, *pcVar11 == '\x01')) {
                        *(uint16_t *)transfer_packet.bytes = 0x10a;
                        iVar16 = 1;
                        do {
                            uVar9 = get_device_info();
                            iVar12 = sync_to_slave(uVar9, 6,
                                                  transfer_packet.bytes, 2);
                            if (iVar12 < 5000) {
                                if (2 < *piVar1) {
                                    if (*(int *)0x20007554 == 0) {
                                        DEBUG_PRINT(0xa116d, 0xef76f);
                                    } else {
                                        debug_print();
                                    }
                                }
                                *(int *)0x20007b38 = *(int *)0x20007b38 | 2;
                                break;
                            }
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(0xa1027, 0xef76f, iVar16);
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
        uVar9 = 0x28000;
LAB_00047c86:
        wait_for_proxy_event(uVar9, 0);
    } while (1);
switchD_00047ccc_caseD_8:
    if (0 < *piVar1) goto code_r0x0004880a;
    goto LAB_00047c76;
code_r0x0004880a:
    iVar16 = *(int *)0x20007554;
    uVar9 = 0xef4b1;
    uVar13 = 0xef76f;
    goto LAB_00047c6a;
}
