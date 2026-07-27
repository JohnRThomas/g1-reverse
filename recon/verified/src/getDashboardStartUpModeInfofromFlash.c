/* Reconstructed getDashboardStartUpModeInfofromFlash @ 0x23df4  (parity: 100/100 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void *FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_0008638c(uint32_t);

unsigned char getDashboardStartUpModeInfofromFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    volatile int *piVar1;
    volatile unsigned int *puVar2;
    unsigned char uVar3;
    int iVar4;
    unsigned int uVar5;
    int iVar6;
    int iVar7;

    piVar1 = (volatile int*)0x2000230cUL;
    volatile unsigned int local_14 = param_2;

    if (2 < *piVar1) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x0009e9bfUL, 0x0009ed09UL, param_3,
                        *(volatile unsigned int*)0x20007554UL);
        } else {
            FUN_00019c70(0x0009e9bfUL, 0x0009ed09UL, param_3,
                         *(volatile unsigned int*)0x20007554UL);
        }
    }
    puVar2 = (volatile unsigned int*)0x00087bf0UL;
    iVar4 = FUN_0008638c(0x00087bf0UL);
    if (iVar4 == 0) {
        if (0 < *piVar1) {
            if (*(volatile int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x0009e9eaUL, 0x0009ed09UL, *puVar2,
                            *(volatile unsigned int*)0x20007554UL);
            } else {
                FUN_00019c70(0x0009e9eaUL, 0x0009ed09UL, *puVar2,
                             *(volatile unsigned int*)0x20007554UL);
            }
        }
        uVar3 = 0xff;
    } else {
        local_14 = local_14 & 0xff000000UL;
        char *p1 = (char*)FUN_000167a8();
        void *pcVar8 = *(void**)(p1 + 0x1030);
        void *r1arg = FUN_000167a8();
        int (*fn)(void*, unsigned int, void*, int) = (int(*)(void*, unsigned int, void*, int))pcVar8;
        iVar6 = fn(r1arg, 0x13e000, (void *)&local_14, 3);
        iVar4 = 0x20018462;
        iVar7 = *piVar1;
        if (iVar6 == 0) {
            if (((unsigned char)local_14 == 0xaa) &&
                ((unsigned char)(local_14 >> 16) != 0xff)) {
                *(unsigned char*)(intptr_t)(0x20018462 + 2) = (unsigned char)(local_14 >> 16);
            } else {
                *(unsigned char*)(intptr_t)(0x20018462 + 2) = 0;
            }
            if (0 < iVar7) {
                if (*(volatile int*)0x20007554UL == 0) {
                    DEBUG_PRINT(0x0009ea58UL, 0x0009ed09UL, (unsigned int)*(unsigned char*)(intptr_t)(iVar4 + 2),
                                *(volatile unsigned int*)0x20007554UL);
                } else {
                    FUN_00019c70(0x0009ea58UL, 0x0009ed09UL, (unsigned int)*(unsigned char*)(intptr_t)(iVar4 + 2),
                                 *(volatile unsigned int*)0x20007554UL);
                }
            }
            uVar3 = *(unsigned char*)(intptr_t)(iVar4 + 2);
        } else {
            if (0 < iVar7) {
                if (*(volatile int*)0x20007554UL == 0) {
                    DEBUG_PRINT(0x0009ea0aUL, 0x0009ed09UL, 0x13e000UL,
                                *(volatile unsigned int*)0x20007554UL);
                } else {
                    FUN_00019c70(0x0009ea0aUL, 0x0009ed09UL, 0x13e000UL,
                                 *(volatile unsigned int*)0x20007554UL);
                }
            }
            uVar3 = 0;
        }
    }
    return uVar3;
}
