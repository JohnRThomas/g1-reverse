#include "g1_app_symbols.h"
/* named: z_arm_mpu_fault */
/* Reconstructed z_arm_mpu_fault @ 0x503d8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int assert_post_action(int,...) __attribute__((noreturn));
extern int printk(int,...);
extern int FUN_00080780(int,...);
#define SCB28 (*(volatile int*)0xe000ed28)

unsigned z_arm_mpu_fault(int param_1, unsigned char *param_2)
{
    int iVar1; unsigned uVar2, uVar3; int bVar4;
    unsigned local_40,local_3c,uStack_38,local_20,local_1c;
    local_1c = "***** MPU FAULT *****" /*=0xf1c39*/;
    local_20 = 2;
    FUN_00080780(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x1040, &local_20);
    if(SCB28 << 0x1b < 0){
        local_20 = 2; local_1c = "  Stacking error (context area might be not valid)" /*=0xf1c4f*/;
        FUN_00080780(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x1040, &local_20);
        uVar2 = 0x11;
    } else { uVar2 = 0x10; }
    if(SCB28 << 0x1c < 0){
        local_1c = "  Unstacking error" /*=0xf1c82*/; local_20 = 2;
        FUN_00080780(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x1040, &local_20);
        uVar2 = 0x12;
    }
    iVar1 = 0xe000ed00;
    if(SCB28 << 0x1e < 0){
        local_1c = "  Data Access Violation" /*=0xf1c95*/; local_20 = 2;
        FUN_00080780(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x1040, &local_20);
        if(*(volatile int*)(iVar1+0x28) << 0x18 < 0){
            local_3c = "  MMFAR Address: 0x%x" /*=0xf1cad*/; local_40 = 3;
            uStack_38 = *(volatile unsigned*)(iVar1+0x34);
            FUN_00080780(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x1840, &local_40);
            if(param_1 != 0){
                *(volatile unsigned*)(iVar1+0x28) = *(volatile unsigned*)(iVar1+0x28) & 0xffffff7f;
            }
        }
        uVar2 = 0x13;
    }
    if(SCB28 << 0x1f < 0){
        local_1c = "  Instruction Access Violation" /*=0xf1cc3*/; local_20 = 2;
        FUN_00080780(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x1040, &local_20);
        uVar2 = 0x14;
    }
    if(SCB28 << 0x1a < 0){
        local_1c = "  Floating-point lazy state preservation error" /*=0xf1ce2*/; local_20 = 2;
        FUN_00080780(((uintptr_t)&tbl_880d8) /*=0x88258*/, 0x1040, &local_20);
        uVar2 = 0x15;
    }
    iVar1 = 0xe000ed00;
    if(((SCB28 << 0x1b < 0) || (SCB28 << 0x1e < 0)) && (SCB28 << 0x1b < 0)){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "!(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->CFSR & (1UL << (0U + 4U)))" /*=0xf1d4b*/, "WEST_TOPDIR/zephyr/arch/arm/core/aarch32/cortex_m/fault.c" /*=0xf1d11*/, 0x163);
        printk("\tStacking or Data Access Violation error without stack guard, user-mode or null-pointer detection\n\n" /*=0xf1d95*/);
        assert_post_action("WEST_TOPDIR/zephyr/arch/arm/core/aarch32/cortex_m/fault.c" /*=0xf1d11*/, 0x163);
    }
    uVar3 = SCB28 << 0x1a;
    bVar4 = (int)uVar3 < 0;
    if(bVar4){ uVar3 = *(volatile unsigned*)(iVar1+0x24) & 0xffffdfff; }
    if(bVar4){ *(volatile unsigned*)(iVar1+0x24) = uVar3; }
    *(volatile unsigned*)(iVar1+0x28) = *(volatile unsigned*)(iVar1+0x28) | 0xff;
    *param_2 = 0;
    return uVar2;
}

