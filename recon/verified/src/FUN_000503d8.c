/* Reconstructed FUN_000503d8 @ 0x503d8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"
extern int FUN_0007e2ec(int,...) __attribute__((noreturn));
extern int FUN_0007e2fa(int,...);
extern int FUN_00080780(int,...);
#define SCB28 (*(volatile int*)G1_SCB_CFSR)

unsigned FUN_000503d8(int param_1, unsigned char *param_2)
{
    int iVar1; unsigned uVar2, uVar3; int bVar4;
    struct { unsigned count, format; } log2;
    struct { unsigned count, format, value; } log3;
    log2.count = 2;
    log2.format = 0x000f1c39;
    FUN_00080780(0x00088258, 0x1040, &log2);
    if(SCB28 << 0x1b < 0){
        log2.count = 2; log2.format = 0x000f1c4f;
        FUN_00080780(0x00088258, 0x1040, &log2);
        uVar2 = 0x11;
    } else { uVar2 = 0x10; }
    if(SCB28 << 0x1c < 0){
        log2.format = 0x000f1c82; log2.count = 2;
        FUN_00080780(0x00088258, 0x1040, &log2);
        uVar2 = 0x12;
    }
    iVar1 = G1_SCB_CPUID;
    if(SCB28 << 0x1e < 0){
        log2.format = 0x000f1c95; log2.count = 2;
        FUN_00080780(0x00088258, 0x1040, &log2);
        if(*(volatile int*)(iVar1+0x28) << 0x18 < 0){
            log3.count = 3; log3.format = 0x000f1cad;
            log3.value = *(volatile unsigned*)(iVar1+0x34);
            FUN_00080780(0x00088258, 0x1840, &log3);
            if(param_1 != 0){
                *(volatile unsigned*)(iVar1+0x28) = *(volatile unsigned*)(iVar1+0x28) & 0xffffff7f;
            }
        }
        uVar2 = 0x13;
    }
    if(SCB28 << 0x1f < 0){
        log2.format = 0x000f1cc3; log2.count = 2;
        FUN_00080780(0x00088258, 0x1040, &log2);
        uVar2 = 0x14;
    }
    if(SCB28 << 0x1a < 0){
        log2.format = 0x000f1ce2; log2.count = 2;
        FUN_00080780(0x00088258, 0x1040, &log2);
        uVar2 = 0x15;
    }
    iVar1 = G1_SCB_CPUID;
    if(((SCB28 << 0x1b < 0) || (SCB28 << 0x1e < 0)) && (SCB28 << 0x1b < 0)){
        FUN_0007e2fa(0x00099cbd, 0x000f1d4b, 0x000f1d11, 0x163);
        FUN_0007e2fa(0x000f1d95);
        FUN_0007e2ec(0x000f1d11, 0x163);
    }
    uVar3 = SCB28 << 0x1a;
    bVar4 = (int)uVar3 < 0;
    if(bVar4){ uVar3 = *(volatile unsigned*)(iVar1+0x24) & 0xffffdfff; }
    if(bVar4){ *(volatile unsigned*)(iVar1+0x24) = uVar3; }
    *(volatile unsigned*)(iVar1+0x28) = *(volatile unsigned*)(iVar1+0x28) | 0xff;
    *param_2 = 0;
    return uVar2;
}
