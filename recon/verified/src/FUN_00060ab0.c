/* Reconstructed FUN_00060ab0 @ 0x60ab0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern u32 FUN_00060990(u32);
extern u32 FUN_000669f4(void*,u32,u32);
extern void FUN_000838d6(u32,u32,void*);
extern void FUN_00083906(u32);
extern void FUN_0008392e(u32);
u32 FUN_00060ab0(u32 param_1, u8* param_2, u8 param_3){
    int iVar1, iVar2; u32 uVar4, uVar5, uVar6; u32 local_24;
    u32 *puVar3;
    puVar3 = *(u32**)(param_2+4);
    if(puVar3==0){ iVar2=0; uVar4=0; }
    else { uVar4=puVar3[0]; iVar2=(int)puVar3[1]; }
    puVar3 = *(u32**)(param_2+8);
    if(puVar3==0){ iVar1=0; uVar5=0; }
    else {
        uVar5=puVar3[0]; iVar1=(int)puVar3[1];
        if(iVar1!=0 && iVar2!=0){
            if(iVar1!=iVar2) return 0xffffffea;
            local_24 = iVar2 + 1;
            goto LAB;
        }
    }
    local_24 = iVar2 + 1 + iVar1;
LAB: ;
    u8 local_20 = *param_2;
    if(9 < local_24){
        u32 buf[4];
        buf[0]=4; buf[1]=0x000f5c20; buf[2]=*param_2; buf[3]=local_24;
        FUN_000838d6(0x00088270, 0x2080, buf);
        return 0xffffffea;
    }
    struct { u8 b0; u8 b1; uint16_t h2; u8 b4; u8 b5; } frame;
    frame.b0 = local_20;
    frame.b1 = (u8)local_24;
    frame.h2 = 0x0101;
    frame.b4 = 0;
    frame.b5 = param_3;
    FUN_00083906(param_1);
    uVar6 = FUN_000669f4(&frame, uVar4, uVar5);
    FUN_0008392e(param_1);
    uVar6 = FUN_00060990(uVar6);
    return uVar6;
}

