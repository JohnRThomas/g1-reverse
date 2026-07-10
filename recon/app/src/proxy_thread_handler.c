/* Reconstructed proxy_thread_handler @ 0x47c48  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

typedef uint8_t  undefined1;
typedef uint32_t undefined4;
typedef uint16_t ushort;
typedef uint8_t  byte;

/* external callees (K&R prototypes: accept any args) */
extern int DEBUG_PRINT();
extern int FUN_000167a8();
extern int FUN_00019c70();
extern int FUN_00023af0();
extern int FUN_00023bfc();
extern int FUN_00023eec();
extern int FUN_0002f910();
extern int FUN_0002f928();
extern int FUN_00047bf8();
extern int FUN_00049a28();
extern int FUN_0004a4d0();
extern int FUN_00072240();
extern int FUN_000745c8();
extern int FUN_00074844();
extern int FUN_0008638c();
extern int FUN_00086c04();
extern int FUN_00086c1e();
extern int FUN_00086c78();
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

    piVar1 = (int *)0x2000230c;
    FUN_00086c78(local_40, 0, 0x18);
    if (*piVar1 < 3) goto LAB_00047c76;
    iVar16 = *(int *)0x20007554;
    uVar9 = 0xef081;
    uVar13 = 0xef76f;
LAB_00047c6a:
    if (iVar16 == 0) {
        DEBUG_PRINT(uVar9, uVar13);
    } else {
        FUN_00019c70();
    }
LAB_00047c76:
    do {
        if ((*(char *)(param_1 + 1) != '\x01') && (*(char *)(param_1 + 1) != '\b')) {
            if (-1 < (int)((uint32_t)*(ushort *)(param_1 + 0x105c) << 0x18)) {
                uVar9 = 0x8000;
                goto LAB_00047c86;
            }
            FUN_00086c78(local_40, 0, 0x18);
            iVar16 = FUN_00072240((void *)0x2000392c, local_40, 0xffffffff, 0xffffffff);
            cVar23 = local_3c;
            if (iVar16 == 0) {
                switch (local_40[0]) {
                case 0:
                    if (2 < *piVar1) {
                        if (*(int *)0x20007554 == 0) {
                            DEBUG_PRINT(0xef0a1, 0xef76f);
                        } else {
                            FUN_00019c70();
                        }
                    }
                    FUN_00086c78((void *)0x2001d432, 0, 0x14);
                    uVar18 = local_3e;
                    if (0x13 < local_3e) {
                        uVar18 = 0x14;
                    }
                    FUN_00086c04((void *)0x2001d432, &local_3c, uVar18);
                    *(ushort *)0x2000ff04 = uVar18;
                    *(char *)0x2001d431 = '\x01';
                    goto LAB_00047c76;
                case 1:
                    if (2 < *piVar1) {
                        if (*(int *)0x20007554 == 0) {
                            DEBUG_PRINT(0xef0c9, 0xef76f);
                        } else {
                            FUN_00019c70();
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
                                FUN_00019c70();
                            }
                        }
                        local_48 = 0;
                        local_44 = 0;
                        FUN_0004a4d0(&local_48);
                        if (2 < *piVar1) {
                            if (*(int *)0x20007554 == 0) {
                                DEBUG_PRINT(0xef135, 0xef76f, local_48, local_44);
                            } else {
                                FUN_00019c70(0xef135, 0xef76f);
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
                            FUN_00019c70();
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
                    if (local_3c == '\0') {
                        *(byte *)0x2001d34a = local_3b - 1;
                        piVar19 = (int *)0x87bf0;
                        iVar16 = FUN_0008638c((void *)0x87bf0);
                        piVar4 = (int *)0x2001d34b;
                        if (iVar16 == 0) goto LAB_00047de2;
                        FUN_00086c78((void *)0x2001d34b, 0, 0xe6);
                        iVar16 = FUN_000167a8();
                        pcVar20 = *(int (***)())(iVar16 + 0x1030);
                        uVar9 = FUN_000167a8();
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
                                    FUN_00019c70();
                                }
                            }
                            FUN_00086c78((void *)0x2001d34b, 0, 0xe6);
                            iVar16 = FUN_000167a8();
                            pcVar20 = *(int (***)())(iVar16 + 0x1030);
                            uVar9 = FUN_000167a8();
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
                                FUN_00086c78(puVar10, 0, 0xe6);
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
                                FUN_00086c1e(uVar13, uVar9, iVar12, 0xdc);
                                puVar10[1] = (char)iVar12 + '\n';
                                while (iVar15 = (*(int (**)())(param_1 + 0x788))(puVar22, puVar10[1]), iVar15 < 0) {
                                    if (1 < *piVar1) {
                                        if (*piVar19 == 0) {
                                            DEBUG_PRINT(0xef1ea, 0xef76f);
                                        } else {
                                            FUN_00019c70();
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
                                            FUN_00019c70();
                                        }
                                    }
                                }
                                *(char *)0x2001d262 = '\x01';
                                *piVar6 = *piVar6 + iVar12;
                                FUN_0002f910(*pbVar3);
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
                    if (local_3c != '\x01') goto LAB_00047c76;
                    if (*(char *)0x2001d262 == '\0') {
                        if (2 < *piVar1) {
                            if (*(int *)0x20007554 == 0) {
                                DEBUG_PRINT(0xef260, 0xef76f);
                            } else {
                                FUN_00019c70();
                            }
                        }
LAB_00048082:
                        FUN_0002f928();
                        goto LAB_00047c76;
                    }
                    if (*(int *)0x2000a078 < *(int *)0x2000a080) {
                        FUN_00086c78((void *)0x2001d264, 0, 0xe6);
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
                        FUN_00086c78(uVar9, 0, 0xe6);
                        iVar12 = FUN_000167a8();
                        pcVar20 = *(int (***)())(iVar12 + 0x1030);
                        uVar9 = FUN_000167a8();
                        iVar12 = (*pcVar20)(uVar9, *piVar4 + *piVar19, (void *)0x2001d34b, iVar16);
                        if (iVar12 != 0) {
                            if (0 < *piVar1) {
                                if (*(int *)0x20007554 == 0) {
                                    DEBUG_PRINT(0x9ea0a, 0xef76f, 0x400000);
                                } else {
                                    FUN_00019c70();
                                }
                            }
LAB_0004820e:
                            *pcVar11 = '\0';
                            goto LAB_00048082;
                        }
                        FUN_00086c1e(puVar10 + 10, (void *)0x2001d34b, iVar16, 0xdc);
                        piVar19 = (int *)0x20007554;
                        iVar12 = 3;
                        while (iVar15 = (*(int (**)())(param_1 + 0x788))(puVar10, puVar10[1]), iVar15 < 0) {
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(0xef2df, 0xef76f);
                                } else {
                                    FUN_00019c70();
                                }
                            }
                            iVar12 = iVar12 + -1;
                            if (iVar12 == 0) {
                                if (1 < *piVar1) {
                                    if (*(int *)0x20007554 == 0) {
                                        DEBUG_PRINT(0xef214, 0xef76f);
                                    } else {
                                        FUN_00019c70();
                                    }
                                }
                                goto LAB_0004820e;
                            }
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(0xef2df, 0xef76f);
                                } else {
                                    FUN_00019c70();
                                }
                            }
                        }
                        *piVar4 = *piVar4 + iVar16;
                        if (2 < *piVar1) {
                            if (*(int *)0x20007554 == 0) {
                                DEBUG_PRINT(0xef2fc, 0xef76f, iVar16, *piVar4);
                            } else {
                                FUN_00019c70(0xef2fc, 0xef76f, iVar16, *piVar4);
                            }
                        }
LAB_00048054:
                        FUN_00047bf8(1, 0);
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
                    FUN_0002f928();
                    if (*piVar1 < 1) goto LAB_00047c76;
                    if (*(int *)0x20007554 == 0) {
                        iVar16 = FUN_000167a8();
                        iVar16 = **(int **)(iVar16 + 0xfec);
                        uVar9 = 0xef29b;
                        uVar13 = 0xef76f;
                        goto LAB_000480f4;
                    }
                    iVar16 = FUN_000167a8();
                    iVar16 = **(int **)(iVar16 + 0xfec);
                    uVar9 = 0xef29b;
                    uVar13 = 0xef76f;
                    break;
                case 3:
                    if (2 < *piVar1) {
                        if (*(int *)0x20007554 == 0) {
                            DEBUG_PRINT(0xef338, 0xef76f);
                        } else {
                            FUN_00019c70();
                        }
                    }
                    piVar19 = (int *)0x87bf0;
                    iVar16 = FUN_0008638c((void *)0x87bf0);
                    if (iVar16 == 0) {
LAB_00047de2:
                        if (*piVar1 < 1) goto LAB_00047c76;
                        iVar16 = *piVar19;
                        iVar12 = *(int *)0x20007554;
                        uVar9 = 0x9e9ea;
                        uVar13 = 0xef76f;
                    } else {
                        FUN_00086c78((void *)0x2001d34b, 0, 0xe6);
                        iVar16 = FUN_000167a8();
                        pcVar20 = *(int (***)())(iVar16 + 0x1030);
                        uVar9 = FUN_000167a8();
                        iVar16 = (*pcVar20)(uVar9, 0x400000, (void *)0x2001d34b, 0xe6);
                        if (iVar16 != 0) goto LAB_00047e22;
                        puVar10 = (undefined1 *)FUN_00086c78((void *)0x2001d264, 0, 0xe6);
                        pcVar11 = (char *)0x2001d263;
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
                                    FUN_00019c70(0xef377, 0xef76f, iVar21, uVar9, *(undefined4 *)(iVar15 + 0x14),
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
                                    FUN_00019c70(uVar13, uVar9, iVar16, *(undefined1 *)(iVar15 + iVar16));
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
                    *(uint16_t *)&local_48 = ((uint16_t)(uint8_t)local_3c << 8) | 7;
                    do {
                        uVar9 = FUN_000167a8();
                        iVar12 = sync_to_slave(uVar9, 6, &local_48, 2);
                        if (iVar12 < 5000) {
                            if (2 < *piVar1) {
                                if (*(int *)0x20007554 == 0) {
                                    DEBUG_PRINT(0xef40d, 0xef76f);
                                } else {
                                    FUN_00019c70();
                                }
                            }
                            FUN_00049a28(cVar23);
                            FUN_000745c8();
                            break;
                        }
                        if (1 < *piVar1) {
                            if (*(int *)0x20007554 == 0) {
                                DEBUG_PRINT(0xa125e, 0xef76f, iVar16);
                            } else {
                                FUN_00019c70();
                            }
                        }
                        iVar16 = iVar16 + 1;
                    } while (iVar16 != 4);
                    goto LAB_00047c76;
                case 5:
                    iVar16 = 1;
                    *(uint16_t *)&local_48 = ((uint16_t)(uint8_t)local_3c << 8) | 8;
                    do {
                        uVar9 = FUN_000167a8();
                        iVar12 = sync_to_slave(uVar9, 6, &local_48, 2);
                        if (iVar12 < 5000) {
                            if (2 < *piVar1) {
                                if (*(int *)0x20007554 == 0) {
                                    DEBUG_PRINT(0xef437, 0xef76f);
                                } else {
                                    FUN_00019c70();
                                }
                            }
                            FUN_00023af0(cVar23);
                            break;
                        }
                        if (1 < *piVar1) {
                            if (*(int *)0x20007554 == 0) {
                                DEBUG_PRINT(0xa125e, 0xef76f, iVar16);
                            } else {
                                FUN_00019c70();
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
                        uVar9 = FUN_000167a8();
                        iVar12 = sync_to_slave(uVar9, 6, &local_4c, 2);
                        if (iVar12 < 5000) {
                            if (2 < *piVar1) {
                                if (*(int *)0x20007554 == 0) {
                                    DEBUG_PRINT(0xef472, 0xef76f);
                                } else {
                                    FUN_00019c70();
                                }
                            }
                            local_48 = ((uint32_t)(uint8_t)*(char *)0x20011d81 << 24) | 0x608;
                            local_44 = (((uint32_t)((uint16_t)local_44 << 16) | ((uint8_t)cVar23 << 8)) & 0xffffff00) | 3;
                            iVar16 = (*(int (**)())(param_1 + 0x788))(&local_48, 6);
                            if ((iVar16 < 0) && (1 < *piVar1)) {
                                if (*(int *)0x20007554 == 0) {
                                    DEBUG_PRINT(0xef0fb, 0xef76f);
                                } else {
                                    FUN_00019c70();
                                }
                            }
                            FUN_00023bfc(cVar23);
                            break;
                        }
                        if (1 < *piVar1) {
                            if (*(int *)0x20007554 == 0) {
                                DEBUG_PRINT(0xa125e, 0xef76f, iVar16);
                            } else {
                                FUN_00019c70();
                            }
                        }
                        iVar16 = iVar16 + 1;
                    } while (iVar16 != 4);
                    goto LAB_00047c76;
                case 7:
                    iVar16 = FUN_00023eec();
                    if (((iVar16 == 1) && (iVar16 = FUN_000167a8(), *(char *)(iVar16 + 0xd5) == '\0')) &&
                        (pcVar11 = (char *)FUN_000167a8(), *pcVar11 == '\x01')) {
                        iVar16 = FUN_000167a8();
                        *(undefined1 *)(iVar16 + 0xfe6) = 5;
                        iVar16 = FUN_000167a8();
                        iVar12 = FUN_000167a8();
                        piVar19 = (int *)0x20007554;
                        *(undefined1 *)(iVar12 + 0xcb) = *(undefined1 *)(iVar16 + 0xed5);
                        uVar9 = FUN_000167a8();
                        sync_to_slave(uVar9, 2, 0, 0);
                        change_work_mode_to(2);
                        *(uint16_t *)((char *)&local_48 + 0) = 0x10a;
                        iVar16 = 1;
                        do {
                            uVar9 = FUN_000167a8();
                            iVar12 = sync_to_slave(uVar9, 6, &local_48, 2);
                            if (iVar12 < 5000) {
                                if (2 < *piVar1) {
                                    if (*(int *)0x20007554 == 0) {
                                        DEBUG_PRINT(0xa116d, 0xef76f);
                                    } else {
                                        FUN_00019c70();
                                    }
                                }
                                *(int *)0x20007b38 = *(int *)0x20007b38 | 2;
                                break;
                            }
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(0xa1027, 0xef76f, iVar16);
                                } else {
                                    FUN_00019c70();
                                }
                            }
                            iVar16 = iVar16 + 1;
                        } while (iVar16 != 4);
                    }
                    iVar16 = FUN_00023eec();
                    if ((((iVar16 == 1) && (iVar16 = FUN_000167a8(), *(char *)(iVar16 + 0xd5) == '\x06')) ||
                         ((iVar16 = FUN_00023eec(), iVar16 == 2 &&
                          (iVar16 = FUN_000167a8(), *(char *)(iVar16 + 0xd5) == '\x06')))) &&
                        (pcVar11 = (char *)FUN_000167a8(), piVar19 = (int *)0x20007554, *pcVar11 == '\x01')) {
                        *(uint16_t *)((char *)&local_48 + 0) = 0x10a;
                        iVar16 = 1;
                        do {
                            uVar9 = FUN_000167a8();
                            iVar12 = sync_to_slave(uVar9, 6, &local_48, 2);
                            if (iVar12 < 5000) {
                                if (2 < *piVar1) {
                                    if (*(int *)0x20007554 == 0) {
                                        DEBUG_PRINT(0xa116d, 0xef76f);
                                    } else {
                                        FUN_00019c70();
                                    }
                                }
                                *(int *)0x20007b38 = *(int *)0x20007b38 | 2;
                                break;
                            }
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    DEBUG_PRINT(0xa1027, 0xef76f, iVar16);
                                } else {
                                    FUN_00019c70();
                                }
                            }
                            iVar16 = iVar16 + 1;
                        } while (iVar16 != 4);
                    }
                    goto LAB_00047c76;
                default:
                    goto switchD_00047ccc_caseD_8;
                }
                FUN_00019c70(uVar9, uVar13, iVar16);
            }
            goto LAB_00047c76;
        }
        uVar9 = 0x28000;
LAB_00047c86:
        FUN_00074844(uVar9, 0);
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

