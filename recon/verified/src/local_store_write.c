/* Reconstructed local_store_write @ 0x22168  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern void DEBUG_PRINT(u32,u32,u32,u32);
extern void FUN_00019c70(u32,u32,u32,u32);
extern int FUN_0004e374(void*,u32,u32);
extern void FUN_00086c78(void*,int,int);
extern void FUN_00086fbe(void*,u32,int);
u32 local_store_write(u32 param_1, u32 param_2, u32 param_3){
    u32 local_98[8];
    u8 auStack_7c[100];
    u32* src = (u32*)0x0009e145;
    u32* dst = local_98;
    do { u32 a=src[0],b=src[1]; src+=2; dst[0]=a; dst[1]=b; dst+=2; } while(src != (u32*)0x0009e145 + 6);
    *dst = *src;
    FUN_00086c78(auStack_7c, 0, 100);
    FUN_00086fbe(local_98, param_1, 0x80);
    int iVar2 = FUN_0004e374(local_98, param_2, param_3);
    u32 uVar1;
    if(iVar2 == 0){
        if(*(volatile int*)0x2000230cUL < 3) return 0;
        iVar2 = *(volatile int*)0x20007554UL;
        uVar1 = 0x0009e187;
    } else {
        if(*(volatile int*)0x2000230cUL < 1) return 0;
        iVar2 = *(volatile int*)0x20007554UL;
        uVar1 = 0x0009e161;
    }
    if(iVar2 == 0){
        DEBUG_PRINT(uVar1, 0x0009e553, param_1, param_3);
    } else {
        FUN_00019c70(uVar1, 0x0009e553, param_1, param_3);
    }
    return 0;
}

