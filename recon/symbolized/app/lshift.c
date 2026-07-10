#include "g1_app_symbols.h"
/* named: lshift */
/* Reconstructed lshift @ 0x789f0  (parity: 8/200 trials, PROVEN) */
#include <stdint.h>
extern int libc_fatal_error_and_abort(uint32_t,int,int);
extern int Balloc(uint32_t,int);
extern void Bfree(uint32_t,int);

int lshift(uint32_t param_1, int param_2, uint32_t param_3){
    int uVar4 = (int)param_3 >> 5;
    int iVar1 = *(volatile int*)(param_2+4);
    int iVar9 = *(volatile int*)(param_2+0x10) + uVar4;
    int iVar5 = *(volatile int*)(param_2+8);
    int iVar8 = iVar9 + 1;
    do {
        if (iVar8 <= iVar5){
            iVar1 = Balloc(param_1, iVar1);
            if (iVar1 != 0){
                volatile uint32_t *puVar3 = (volatile uint32_t*)(iVar1+0x10);
                for (iVar5 = 0; iVar5 < uVar4; iVar5++){ puVar3++; *puVar3 = 0; }
                volatile uint32_t *puVar6 = (volatile uint32_t*)(param_2+0x14);
                uint32_t uVar10 = param_3 & 0x1f;
                volatile uint32_t *puVar2 = (volatile uint32_t*)(iVar1 + 0x14 + (uVar4 & ~((int)param_3>>0x1f)) * 4);
                volatile uint32_t *puVar12 = puVar6 + *(volatile int*)(param_2+0x10);
                if (uVar10 == 0){
                    puVar2 = puVar2 - 1;
                    volatile uint32_t *puVar11;
                    do { puVar11 = puVar6+1; puVar2 = puVar2+1; *puVar2 = *puVar6; puVar6 = puVar11; } while (puVar11 < puVar12);
                } else {
                    uint32_t uc = 0;
                    volatile uint32_t *puVar11 = puVar2;
                    volatile uint32_t *puVar7;
                    do {
                        *puVar11 = *puVar6 << uVar10 | uc;
                        puVar7 = puVar6+1;
                        uc = *puVar6 >> (0x20 - uVar10 & 0xff);
                        puVar6 = puVar7; puVar11 = puVar11+1;
                    } while (puVar7 < puVar12);
                    int q = (((int)(uintptr_t)puVar12 + (-0x15 - param_2)) & 0xfffffffc) + 4;
                    if (puVar12 < (volatile uint32_t*)(param_2+0x15)) q = 4;
                    *(volatile uint32_t*)((int)(uintptr_t)puVar2 + q) = uc;
                    if (uc != 0) iVar8 = iVar9 + 2;
                }
                *(volatile int*)(iVar1+0x10) = iVar8 - 1;
                Bfree(param_1, param_2);
                return iVar1;
            }
            iVar5 = "Balloc succeeded" /*=0xf8c42*/;
            iVar1 = libc_fatal_error_and_abort("/__w/_temp/workspace/build/.build/HOST-x86_64-w64-mingw32/arm-zephyr-eabi/src/newlib-nano/newlib/libc/stdlib/mprec.c" /*=0xf8cd5*/, 0x1d9, 0);
        }
        iVar1 = iVar1 + 1;
        iVar5 = iVar5 << 1;
    } while (1);
}

