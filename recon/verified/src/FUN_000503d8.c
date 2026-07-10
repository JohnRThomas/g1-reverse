/* Reconstructed FUN_000503d8 @ 0x503d8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0007e2ec(int,...) __attribute__((noreturn));
extern int FUN_0007e2fa(int,...);
extern int FUN_00080780(int,...);
#define SCB28 (*(volatile int*)0xe000ed28)

unsigned FUN_000503d8(int param_1, unsigned char *param_2)
{
    int iVar1; unsigned uVar2, uVar3; int bVar4;
    unsigned local_40,local_3c,uStack_38,local_20,local_1c;
    local_1c = 0x000f1c39;
    local_20 = 2;
    FUN_00080780(0x00088258, 0x1040, &local_20);
    if(SCB28 << 0x1b < 0){
        local_20 = 2; local_1c = 0x000f1c4f;
        FUN_00080780(0x00088258, 0x1040, &local_20);
        uVar2 = 0x11;
    } else { uVar2 = 0x10; }
    if(SCB28 << 0x1c < 0){
        local_1c = 0x000f1c82; local_20 = 2;
        FUN_00080780(0x00088258, 0x1040, &local_20);
        uVar2 = 0x12;
    }
    iVar1 = 0xe000ed00;
    if(SCB28 << 0x1e < 0){
        local_1c = 0x000f1c95; local_20 = 2;
        FUN_00080780(0x00088258, 0x1040, &local_20);
        if(*(volatile int*)(iVar1+0x28) << 0x18 < 0){
            local_3c = 0x000f1cad; local_40 = 3;
            uStack_38 = *(volatile unsigned*)(iVar1+0x34);
            FUN_00080780(0x00088258, 0x1840, &local_40);
            if(param_1 != 0){
                *(volatile unsigned*)(iVar1+0x28) = *(volatile unsigned*)(iVar1+0x28) & 0xffffff7f;
            }
        }
        uVar2 = 0x13;
    }
    if(SCB28 << 0x1f < 0){
        local_1c = 0x000f1cc3; local_20 = 2;
        FUN_00080780(0x00088258, 0x1040, &local_20);
        uVar2 = 0x14;
    }
    if(SCB28 << 0x1a < 0){
        local_1c = 0x000f1ce2; local_20 = 2;
        FUN_00080780(0x00088258, 0x1040, &local_20);
        uVar2 = 0x15;
    }
    iVar1 = 0xe000ed00;
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

