/* Reconstructed getAppLanguageInfofromFlash @ 0x23d0c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void *FUN_000167a8(void);
extern void FUN_00019c70(uint32_t, ...);
extern int FUN_0008638c(uint32_t);

unsigned char getAppLanguageInfofromFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    volatile int *piVar1;
    volatile unsigned int *puVar2;
    int iVar3;
    unsigned int uVar4;
    int iVar5;
    unsigned char uVar6;
    int iVar7;

    piVar1 = (volatile int*)0x2000230cUL;
    unsigned int local_14 = param_2;

    if (2 < *piVar1) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x0009e9bfUL, 0x0009ed2eUL, param_3, 0, param_1);
        } else {
            FUN_00019c70(0x0009e9bfUL, 0x0009ed2eUL, param_3, 0, param_1);
        }
    }
    puVar2 = (volatile unsigned int*)0x00087bf0UL;
    iVar3 = FUN_0008638c(0x00087bf0UL);
    if (iVar3 == 0) {
        if (0 < *piVar1) {
            if (*(volatile int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x0009e9eaUL, 0x0009ed2eUL, *puVar2, 0, param_1);
            } else {
                FUN_00019c70(0x0009e9eaUL, 0x0009ed2eUL, *puVar2, 0, param_1);
            }
        }
        uVar6 = 0xff;
    } else {
        local_14 = local_14 & 0xff000000UL;
        char *p1 = (char*)FUN_000167a8();
        void *pcVar8 = *(void**)(p1 + 0x1030);
        void *r1arg = FUN_000167a8();
        int (*fn)(void*, unsigned int, void*, int) = (int(*)(void*, unsigned int, void*, int))pcVar8;
        iVar5 = fn(r1arg, 0x13e000, &local_14, 3);
        iVar3 = 0x20018462;
        iVar7 = *piVar1;
        if (iVar5 == 0) {
            if ((char)local_14 == -0x56) {
                uVar6 = (unsigned char)(local_14 >> 8);
            } else {
                uVar6 = 2;
            }
            *(unsigned char*)(intptr_t)(0x20018462 + 1) = uVar6;
            if (3 < iVar7) {
                if (*(volatile int*)0x20007554UL == 0) {
                    DEBUG_PRINT(0x0009ea37UL, 0x0009ed2eUL, (unsigned int)*(unsigned char*)(intptr_t)(iVar3 + 1));
                } else {
                    FUN_00019c70(0x0009ea37UL, 0x0009ed2eUL, (unsigned int)*(unsigned char*)(intptr_t)(iVar3 + 1));
                }
            }
            uVar6 = *(unsigned char*)(intptr_t)(iVar3 + 1);
        } else {
            if (0 < iVar7) {
                if (*(volatile int*)0x20007554UL == 0) {
                    DEBUG_PRINT(0x0009ea0aUL, 0x0009ed2eUL, 0x13e000UL);
                } else {
                    FUN_00019c70(0x0009ea0aUL, 0x0009ed2eUL, 0x13e000UL);
                }
            }
            uVar6 = 0;
        }
    }
    return uVar6;
}

