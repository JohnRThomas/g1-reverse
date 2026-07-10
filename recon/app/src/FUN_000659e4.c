/* Reconstructed FUN_000659e4 @ 0x659e4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00065434(uint32_t);
extern int FUN_00065460(uint32_t);
extern int FUN_00065478(void);
extern int FUN_00065494(uint32_t);
extern int FUN_000654ac(uint32_t);
extern int FUN_00065584(void*);
extern int FUN_000655ec(void);
extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(uint32_t,...);
extern void FUN_000851ca(uint32_t,int);

void FUN_000659e4(uint32_t param_1, uint32_t param_2){
    int iVar1;
    uint32_t uVar2 = param_1;
    iVar1 = FUN_00065478();
    if (iVar1 == 0){
        FUN_0007e2fa(0x00099cbd,0x000f6b87,0x000f6b00,0x364,uVar2);
        goto Lec_364;
    }
  L_a08:
    iVar1 = FUN_00065460(param_1);
    if (iVar1 != 0 && (iVar1 = FUN_00065494(param_1)) == 0){
        uVar2 = FUN_000654ac(param_1);
        iVar1 = FUN_000655ec();
        *(volatile uint32_t*)((uint32_t)iVar1 + 0x5000d000UL) = 0;
        int t = (int)(int16_t)uVar2 * 4;
        *(volatile uint32_t*)((uint32_t)t + 0x5000d510UL) |= 1;
        if (param_2 != 0){
            *(volatile int*)(0x5000d000UL + 0x304) = 1 << (uVar2 & 0xff);
        }
        return;
    }
    if (param_2 != 0){
        int r = FUN_00065434(param_1);
        uint32_t s = ((uint32_t)*(volatile uint16_t*)(0x20002bc0UL + (uint32_t)(r + 8) * 2) << 0x1b) >> 0x1d;
        int iv;
        if (s == 4) iv = 3;
        else if (s == 5) iv = 2;
        else {
            uint32_t local_14 = param_1;
            int q = FUN_00065584(&local_14);
            iv = (int)((*(volatile uint32_t*)(q + 0x10) >> (local_14 & 0xff)) & 1) + 2;
        }
        FUN_000851ca(param_1, iv);
        return;
    }
    FUN_0007e2fa(0x00099cbd,0x000f6b9c,0x000f6b00,0x373,uVar2);
    FUN_0007e2ec(0x000f6b00,0x373);
    goto L_a08;
  Lec_364:
    FUN_0007e2ec(0x000f6b00,0x364);
    goto L_a08;
}

