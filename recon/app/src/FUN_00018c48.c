/* Reconstructed FUN_00018c48 @ 0x18c48  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int, ...);
extern int FUN_000167a8(void);
extern int FUN_000181fc(int);
extern int FUN_00018bb4(int);
extern int FUN_00019c70(uintptr_t, ...);
extern int FUN_00072880(int);
extern int FUN_0007c0c8(void);
extern int FUN_00086c78(int,int,int);

void FUN_00018c48(int param_1, unsigned char *param_2, int param_3)
{
    volatile uint32_t *puVar1 = (volatile uint32_t*)0x20006aa0;
    volatile char *pcVar2 = (volatile char*)0x2000ff71;
    volatile int *piVar3 = (volatile int*)0x20006aac;
    volatile int *piVar4 = (volatile int*)0x2000230c;
    volatile int *piVar5 = (volatile int*)0x2000231c;
    volatile int *g_d70 = (volatile int*)0x20007554;
    int iVar6, iVar7, iVar8;
    unsigned int uVar9, uVar10;

    iVar6 = FUN_000181fc(param_1);
    if (0 < *piVar4) {
        if (*g_d70 == 0) {
            DEBUG_PRINT(0x9a992, 0x9b20d, (unsigned int)*param_2, 0, param_1, (int)param_2, param_3);
        } else {
            FUN_00019c70(0x9a992, 0x9b20d, (unsigned int)*param_2,
                         *(volatile unsigned int*)0x20007554, param_1,
                         (uintptr_t)param_2, param_3);
        }
    }
    if (*param_2 == 0) {
        if (*(int *)(param_2 + 8) == 0) {
            uVar9 = *(uint32_t *)(param_2 + 8);
            uVar10 = *(uint32_t *)(param_2 + 0xc);
            *puVar1 = *(uint32_t *)(param_2 + 4);
            puVar1[1] = uVar9;
            puVar1[2] = uVar10;
            *pcVar2 = '\x01';
        }
    } else if ((*param_2 == 1) && (*pcVar2 != '\0')) {
        if (*piVar3 != *piVar5) {
            iVar7 = FUN_0007c0c8();
            iVar8 = FUN_000167a8();
            if (9999 < (unsigned int)(iVar7 - *(int *)(iVar8 + 0xae8))) {
                iVar7 = FUN_000167a8();
                if (*(char *)(iVar7 + 0xd5) != '\v') {
                    iVar7 = FUN_000167a8();
                    if (*(char *)(iVar7 + 0xd5) != '\n') {
                        iVar7 = FUN_000167a8();
                        if (*(char *)(iVar7 + 0xd5) != '\t') {
                            iVar7 = FUN_000167a8();
                            if (*(char *)(iVar7 + 0xd5) != '\f') {
                                iVar7 = FUN_000167a8();
                                if ((*(char *)(iVar7 + 0xd5) != '\x10') &&
                                    (iVar7 = FUN_000167a8(), *(char *)(iVar7 + 0xd5) != '\x0e')) {
                                    *piVar5 = *piVar3;
                                    *(unsigned int *)(iVar6 + 0x1e4) = (unsigned int)*(unsigned char *)((int)piVar3 + 4);
                                    FUN_00018bb4(iVar6 + 0x34);
                                    if (0 < *piVar4) {
                                        if (*g_d70 == 0) {
                                            DEBUG_PRINT(0x9a9cd, 0x9b20d, *piVar3, (unsigned int)*(unsigned char *)((int)piVar3 + 4),
                                                        *(uint32_t *)(iVar6 + 0x1e4));
                                        } else {
                                            FUN_00019c70(0x9a9cd, 0x9b20d,
                                                         *piVar3,
                                                         (unsigned int)*(unsigned char *)((int)piVar3 + 4),
                                                         *(uint32_t *)(iVar6 + 0x1e4));
                                        }
                                    }
                                    FUN_00086c78(iVar6 + 0x34, 0, 0x1b4);
                                    FUN_00072880(iVar6 + 0x1e8);
                                    *pcVar2 = '\0';
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}
