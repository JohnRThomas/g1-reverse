#include "g1_app_symbols.h"
/* named: dev_configure_channel */
/* Reconstructed dev_configure_channel @ 0x84418  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int FUN_00062070(int,int,void*);
extern int dev_write_reg3(u32,int,int,int,int);
extern int dev_channel_validate_and_set(int,int);
extern int dev_write_channel_mode(int,int,int);
extern int z_device_is_ready(u32);
int dev_configure_channel(int param_1, u32 param_2, u32 param_3){
    int iVar4 = *(int*)(param_1+4);
    int iVar3 = param_1;
    union { u32 w; u8 b[4]; } u_1c; u_1c.w = param_2;
    int iVar2;
    iVar2 = z_device_is_ready(*(u32*)(iVar4+0x1c));
    if(iVar2==0){ return -0x13; }
    iVar2 = dev_channel_validate_and_set(param_1, 0);
    if(iVar2 >= 0){
        int r1 = *(int*)(iVar4+0x24);
        if(r1 != 0){
            int iVar5 = *(int*)(param_1+4);
            u8 cVar1 = *(u8*)(iVar5+0x20);
            if(cVar1 != 0 && cVar1 != 1) return -0x86;
            iVar2 = FUN_00062070(r1, r1, &u_1c.b[2]);
            if(iVar2 == -0x16) return -0x16;
            int r2 = (u8)(((unsigned)cVar1<<1)+9);
            u8 r3 = u_1c.b[2];
            iVar3 = dev_write_reg3(*(u32*)(iVar5+0x1c), 4, r2, r3, param_1);
            if(iVar3 != 0) return iVar3;
        }
        iVar2 = dev_write_channel_mode(param_1, iVar4+0x28, 0);
        if(iVar2==0){
            iVar2 = dev_write_channel_mode(param_1, iVar4+0x30, 1);
            if(iVar2==0){
                return dev_write_channel_mode(param_1, iVar4+0x38, 2);
            }
        }
    }
    return iVar2;
}

