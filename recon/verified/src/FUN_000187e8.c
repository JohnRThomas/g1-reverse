/* Reconstructed FUN_000187e8 @ 0x187e8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int FUN_000167a8(void);
extern int FUN_00032ee4(void);
extern int FUN_0007c08e(u32,u32);
extern int FUN_0004ed8c(u32,void*,u32,u32);
extern void DEBUG_PRINT(unsigned long, ...);
void FUN_000187e8(u32 param_1, int param_2){
    volatile u32* puVar1 = (volatile u32*)0x20006ab4UL;
    char* pcVar2 = (char*)(uintptr_t)FUN_000167a8();
    if(*pcVar2 == 2){
        int iVar3 = FUN_00032ee4();
        if(iVar3 != 1){
            u32 uVar7 = *puVar1;
            *puVar1 = uVar7 | 1;
            if((uVar7 & 1) == 0){
                u32 v = *puVar1;
                int go_tail = 0;
                if((int)(v << 0x1e) < 0){
                    go_tail = 1;
                } else if(param_2 != 0){
                    iVar3 = FUN_0007c08e(0x20006ab4, 0xfffffffb);
                    if((int)(iVar3 << 0x1d) >= 0) go_tail = 1;
                }
                if(go_tail){
                    FUN_0007c08e(0x20006ab4, 0xfffffffe);
                    return;
                }
                u32 local_2c[5];
                u32* src = (u32*)0x00088388;
                for(int i=0;i<4;i++) local_2c[i] = src[i];
                *(u8*)&local_2c[4] = *(u8*)(src+4);
                iVar3 = FUN_0004ed8c(param_1, local_2c, 0x00088a0c, 0x20006ae8);
                if(iVar3 != 0){
                    DEBUG_PRINT(0x0009a65b, iVar3);
                    FUN_0007c08e(0x20006ab4, 0xfffffffe);
                }
            }
        }
    }
}

