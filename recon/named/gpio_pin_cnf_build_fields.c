/* named: gpio_pin_cnf_build_fields */
/* Reconstructed gpio_pin_cnf_build_fields @ 0x85130  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int FUN_00065584(int*);
void gpio_pin_cnf_build_fields(int param_1, u8* param_2, u8* param_3, u8* param_4, u8* param_5, u8* param_6){
    int local_1c = param_1;
    int iVar1 = FUN_00065584(&local_1c);
    iVar1 = iVar1 + local_1c * 4;
    u32 pbVar2 = (param_3 != 0) ? 1 : 0;
    u32 pbVar7 = (param_2 != 0) ? 1 : 0;
    u32 uVar3 = (param_4 != 0) ? 0xc : 0;
    u32 uVar4 = (param_5 != 0) ? 0xf00 : 0;
    u32 uVar5 = (param_6 != 0) ? 0x30000 : 0;
    u32 v2 = (param_2 != 0) ? (u32)*param_2 : 0;
    u32 v3 = (param_3 != 0) ? ((u32)*param_3 << 1) : 0;
    u32 v4 = (param_4 != 0) ? ((u32)*param_4 << 2) : 0;
    u32 uVar6 = (param_5 != 0) ? ((u32)*param_5 << 8) : 0;
    u32 v6 = (param_6 != 0) ? ((u32)*param_6 << 0x10) : 0;
    u32 mask = ~(pbVar7 | (pbVar2 << 1) | uVar3 | uVar4 | uVar5);
    *(volatile u32*)(iVar1+0x200) = uVar6 | v2 | (*(volatile u32*)(iVar1+0x200) & mask) | v3 | v4 | v6;
}

