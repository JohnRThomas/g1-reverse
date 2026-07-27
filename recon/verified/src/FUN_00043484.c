/* Reconstructed FUN_00043484 @ 0x43484  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern long long FUN_000431a8(void);
extern int FUN_0004588c(int,int,void*,void*,void*,int);
extern int FUN_000471cc(int,int,int,int,int,int);
extern int FUN_00047260(int,int,int,int,int,int);
extern int FUN_00047a4c(int,int);
extern int FUN_0007d53a(int,int,int,int,int,int);

int FUN_00043484(unsigned int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    volatile uint32_t *puVar1 = (volatile uint32_t *)0x2000a034;
    int iVar2;
    unsigned int uVar3;
    int iVar4, iVar5;
    int uVar6;
    unsigned long long uVar7;
    int local_24;
    int local_20, local_1c;
    volatile int *g5c0 = (volatile int *)0x2000230c;
    volatile int *g5c4 = (volatile int *)0x20007554;

    if (((param_4 == 0) && (param_5 == 0)) && (param_6 == 0)) {
        local_20 = param_6;
        local_1c = param_6;
        if (param_1 - 0x16 < 0x67) {
            iVar2 = FUN_0004588c(4, param_1, &local_20, &local_1c, &local_24, 0);
            if (iVar2 < 0) {
                if (1 < *g5c0) {
                    if (*g5c4 == 0) {
                        DEBUG_PRINT(0x000aa8eb, 0x000aadd0);
                    } else {
                        FUN_00019c70(0);
                    }
                }
                return 0xffffffff;
            }
            uVar3 = (unsigned int)FUN_000431a8();
            if ((uVar3 & 2) != 0) {
                FUN_000471cc((int)*puVar1, 0, param_2, param_3, local_20 + 2 + param_2, local_1c + param_3);
            }
            FUN_0007d53a((int)*puVar1, local_24, local_20 / 2, local_1c, param_2, param_3);
            iVar2 = (int)FUN_000431a8();
            if (-1 < iVar2 << 0x1e) {
                return 0;
            }
            iVar2 = FUN_000167a8();
            uVar6 = *(int *)(iVar2 + 0xeb4);
            iVar2 = FUN_000167a8();
            iVar4 = local_1c + param_3;
            iVar5 = local_20 + 2 + param_2;
        } else {
            uVar7 = (unsigned long long)FUN_000431a8();
            iVar2 = (int)(uVar7 >> 0x20);
            if ((uVar7 & 2) != 0) {
                FUN_000471cc((int)*puVar1, 0, iVar2, param_3, iVar2 + 0x18, param_3 + 0x18);
            }
            local_24 = FUN_00047a4c(param_1 & 0xff, 0x120);
            FUN_0007d53a((int)*puVar1, local_24, 0xc, 0x18, param_2, param_3);
            iVar2 = (int)FUN_000431a8();
            if (-1 < iVar2 << 0x1e) {
                return 0;
            }
            iVar2 = FUN_000167a8();
            uVar6 = *(int *)(iVar2 + 0xeb4);
            iVar2 = FUN_000167a8();
            iVar4 = param_3 + 0x18;
            iVar5 = param_2 + 0x18;
        }
        FUN_00047260(uVar6, *(int *)(iVar2 + 0xeb8), param_2, param_3, iVar5, iVar4);
    }
    return 0;
}

