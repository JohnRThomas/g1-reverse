/* Reconstructed FUN_00067794 @ 0x67794  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007e2fa(uint32_t,...);
extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_00067548(int,int,int,uint32_t,...);
extern void FUN_000675c0(int,int*);

uint32_t FUN_00067794(int param_1, int *param_2, uint32_t param_3, uint32_t param_4){
    if (param_2 == 0){
        FUN_0007e2fa(0x00099cbd, 0x000f6c00, 0x000f6fef, 0x102);
        FUN_0007e2ec(0x000f6fef, 0x102);
    }
    uint8_t bVar1 = *(volatile uint8_t*)(param_1+4);
    uint32_t iVar3 = (uint32_t)bVar1 * 0x28;
    volatile uint8_t *iVar6 = (volatile uint8_t*)(0x2000b3ccUL + iVar3);
    uint32_t uVar4 = 0x0bad0005;
    if (*(volatile uint8_t*)(iVar6+0x22) == 0){
        *(volatile uint32_t*)(iVar6+8) = 0;
        *(volatile uint32_t*)(iVar6+0) = param_3;
        *(volatile uint32_t*)(iVar6+4) = param_4;
        *(volatile uint8_t*)(iVar6+0x25) = 0;
        *(volatile uint8_t*)(iVar6+0x24) = 0;
        int8_t cVar2 = *(volatile int8_t*)((int)param_2+0xe);
        *(volatile uint8_t*)(iVar6+0x27) = (uint8_t)cVar2;
        if ((uint32_t)param_2[2] < 0xff00000){
            uVar4 = 6;
        } else {
            int bVar7;
            if (param_2[0] == 0x22){
                bVar7 = (param_2[1] == 0x23);
            } else {
                if (param_2[0] != 0x23) return 0x0bad0004;
                bVar7 = (param_2[1] == 0x22);
            }
            if (!bVar7) return 0x0bad0004;
            uVar4 = 0xb;
        }
        if (cVar2 == 0){
            if (param_2[0] == param_2[1]){
                FUN_0007e2fa(0x00099cbd, 0x000f702b, 0x000f6fef, 0xf3);
                FUN_0007e2ec(0x000f6fef, 0xf3);
            }
            FUN_00067548(param_2[0], 0, 3, uVar4, param_4);
            FUN_00067548(param_2[1], 0, 3, uVar4);
        }
        volatile uint8_t *iVar5b = (volatile uint8_t*)(0x2000b3ccUL + iVar3);
        *(volatile uint8_t*)(iVar5b+0x26) = *(volatile uint8_t*)((int)param_2+0xd);
        FUN_000675c0(param_1, param_2);
        uVar4 = 0x0bad0000;
        *(volatile uint8_t*)(iVar5b+0x22) = 1;
    }
    return uVar4;
}

