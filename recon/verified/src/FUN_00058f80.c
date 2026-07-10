/* Reconstructed FUN_00058f80 @ 0x58f80  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00058c34(int, ...);
extern int FUN_00058f34(int,int,int);
extern int FUN_0005f148(int);
extern int FUN_0005f24c(int);
extern int FUN_000821a4(int,int);
extern int FUN_000821f4(int, ...);
extern int FUN_00083740(int, ...);

unsigned int FUN_00058f80(int *param_1, int param_2)
{
    volatile uint32_t *puVar5 = (volatile uint32_t *)0x200029a0;
    char cVar1;
    short sVar4;
    int iVar6;
    unsigned int uVar7;
    int iVar8;
    uint32_t *puVar9;
    uint32_t *puVar10;
    uint32_t *puVar11;
    uint32_t *puVar12;
    unsigned short uVar3;
    unsigned short uVar2;

    iVar8 = 0;
    cVar1 = **(char **)(param_2 + 0xc);
    do {
        if (*(int *)(*param_1 + 0x28) == 0) {
            if (iVar8 == 0) {
                iVar8 = FUN_00058f34((int)param_1, 0x19, 0);
                if (iVar8 == 0) {
                    return 0xe;
                }
                FUN_000821a4((int)param_1, iVar8);
            }
            return 0;
        }
        iVar6 = FUN_0005f148(*param_1 + 0x28);
        *(volatile unsigned short *)(puVar5 + 1) = 0;
        sVar4 = *(short *)(iVar6 + 0x18);
        uVar2 = *(unsigned short *)(iVar6 + 0x10);
        uVar7 = *(unsigned int *)(iVar6 + 0xc);
        *puVar5 = puVar5[2];
        FUN_00083740((int)puVar5, uVar7, uVar2);
        iVar8 = *param_1;
        uVar3 = *(unsigned short *)(iVar6 + 0x1a);
        puVar9 = *(uint32_t **)(iVar8 + 0x28);
        if (puVar9 != (uint32_t *)0x0) {
            puVar10 = (uint32_t *)*puVar9;
            puVar11 = (uint32_t *)0x0;
            while (puVar9 != (uint32_t *)0x0) {
                puVar12 = puVar9;
                if (*(short *)(puVar9 + 6) == sVar4) {
                    if (*(unsigned short *)((int)puVar9 + 0x1a) == 0) break;
                    if ((unsigned int)*(unsigned short *)((int)puVar9 + 0x1a) !=
                        (unsigned int)uVar3 + (unsigned int)*(volatile unsigned short *)(puVar5 + 1)) {
                        uVar7 = 7;
LAB_000590a6:
                        FUN_000821f4((int)param_1, 0x18, sVar4, uVar7);
                        return 0;
                    }
                    if ((unsigned int)*(volatile unsigned short *)((int)puVar5 + 6) <
                        (unsigned int)*(volatile unsigned short *)(puVar5 + 1) + (unsigned int)*(unsigned short *)(puVar9 + 4)) {
                        uVar7 = 0xd;
                        goto LAB_000590a6;
                    }
                    FUN_00083740((int)puVar5, puVar9[3]);
                    uVar7 = *puVar9;
                    if (puVar11 == (uint32_t *)0x0) {
                        *(uint32_t *)(iVar8 + 0x28) = uVar7;
                        if (puVar9 == *(uint32_t **)(iVar8 + 0x2c)) {
                            *(uint32_t *)(iVar8 + 0x2c) = uVar7;
                        }
                    } else {
                        *puVar11 = uVar7;
                        if (puVar9 == *(uint32_t **)(iVar8 + 0x2c)) {
                            *(uint32_t **)(iVar8 + 0x2c) = puVar11;
                        }
                    }
                    *puVar9 = 0;
                    FUN_0005f24c((int)puVar9);
                    puVar12 = puVar11;
                }
                puVar9 = puVar10;
                puVar11 = puVar12;
                if (puVar10 != (uint32_t *)0x0) {
                    puVar10 = (uint32_t *)*puVar10;
                }
            }
        }
        if (cVar1 == '\x01') {
            iVar8 = FUN_00058c34((int)param_1, 0x18, 0, sVar4, *(unsigned short *)(iVar6 + 0x1a), *puVar5,
                                 *(volatile unsigned short *)(puVar5 + 1));
            if (iVar8 != 0) {
                FUN_000821f4((int)param_1, 0x18, *(unsigned short *)(iVar6 + 0x18), iVar8);
            }
        } else {
            iVar8 = 0;
        }
        FUN_0005f24c(iVar6);
    } while (1);
}

