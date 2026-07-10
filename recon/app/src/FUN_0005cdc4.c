/* Reconstructed FUN_0005cdc4 @ 0x5cdc4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int FUN_0005cb38(int,int,int);
extern void FUN_0005f24c(int);
extern u32 FUN_0005f5d0(int,int);
extern void FUN_0008304c(int,int);
extern void FUN_00083074(u32,int,void*);
extern int FUN_000830b0(int,int);
extern int FUN_000835ea(u32,int,int,unsigned);
static inline u32 lsr(u32 v, u32 n){ n&=0xff; return n>=32?0:v>>n; }
u32 FUN_0005cdc4(int param_1){
    unsigned uVar3 = *(u8*)(param_1+8);
    if(uVar3 < 3){
        if(uVar3 != 0){
            uVar3 = (lsr(*(u32*)(param_1+0xd8), *(u8*)(param_1+0xdc)) & 1) | 0x80;
        }
    } else {
        if(uVar3 != 3){
            u32 local[3];
            local[0]=3; local[1]=0x000f4e7a; local[2]=uVar3;
            FUN_00083074(0x00088180, 0x1840, local);
            return 8;
        }
        uVar3 = 0;
    }
    int iVar1 = FUN_000830b0(param_1, 3);
    if(iVar1 != 0){
        (void)FUN_0005f5d0(iVar1+0xc, 0x10);
        int iVar2 = FUN_000835ea(*(volatile u32*)0x2000af48UL, param_1+0x57, param_1+0x27, uVar3);
        if(iVar2 == 0){
            FUN_0005cb38(param_1, iVar1, 0);
            FUN_0008304c(param_1+4, 0);
            return 0;
        }
        FUN_0005f24c(iVar1);
    }
    return 8;
}

