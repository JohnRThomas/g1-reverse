/* Reconstructed FUN_0005a464 @ 0x5a464  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00059c48(int,int);
extern void FUN_00059d24(int,int,int);
extern void FUN_000825c0(int,int);
extern void FUN_000828da(void*,int);
extern void FUN_00082a42(uint32_t,int,void*);

int FUN_0005a464(int param_1, int param_2, uint16_t *param_3, int param_4, short param_5){
    int iVar5 = *(volatile int*)(param_2+0xc);
    uint32_t local_28, local_24;
    if (param_5 == 0){
        if ((uint32_t)(param_4 - 1) < 2){
            uint16_t uVar4 = (uint16_t)(uint8_t)*(volatile uint8_t*)param_3;
            if (param_4 != 1) uVar4 = *(volatile uint16_t*)param_3;
            volatile uint8_t *puVar2 = (volatile uint8_t*)FUN_00059c48(param_1, iVar5);
            if (puVar2 == 0){
                if (uVar4 == 0) return param_4;
                puVar2 = (volatile uint8_t*)FUN_00059c48(0, iVar5);
                if (puVar2 == 0){
                    local_24 = 0x000f486f; local_28 = 2;
                    FUN_00082a42(0x00088128, 0x1080, &local_28);
                    return -0x11;
                }
                FUN_000828da((void*)(puVar2+1), param_1+0x90);
                *puVar2 = *(volatile uint8_t*)(param_1+8);
            }
            {
                volatile uint32_t *cp = (volatile uint32_t*)(iVar5+0x10);
                if (*cp != 0){
                    int iVar3 = ((int(*)(int,int,uint16_t))(*cp))(param_1,param_2,uVar4);
                    if (iVar3 < 0) return iVar3;
                    if ((uint32_t)(iVar3 - 1) > 1) return -0xe;
                }
            }
            uint16_t uVar1 = *(volatile uint16_t*)(puVar2+8);
            *(volatile uint16_t*)(puVar2+8) = uVar4;
            if (*(volatile uint16_t*)(iVar5+10) != uVar4) FUN_000825c0(param_2, iVar5);
            if (uVar1 != uVar4) FUN_00059d24(*(volatile uint8_t*)(param_1+8), param_1+0x90, 0);
            if (uVar4 == 0){
                FUN_000828da((void*)(puVar2+1), 0x000f2b3a);
                *puVar2 = 0;
                *(volatile uint16_t*)(puVar2+8) = 0;
            }
        } else param_4 = -0xd;
    } else param_4 = -7;
    return param_4;
}

