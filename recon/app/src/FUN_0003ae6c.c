/* Reconstructed FUN_0003ae6c @ 0x3ae6c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int FUN_000167a8(void);
extern int FUN_00033cf8(void);
extern int FUN_00037060(void);
extern int FUN_000370bc(void);
extern int FUN_0003719c(void);
extern void FUN_00047b1c(void*,int);
extern void FUN_00047ba8(void);
void FUN_0003ae6c(u32 param_1,u32 param_2,u32 param_3,u32 param_4){
    u32 local[5];
    local[0]=param_1; local[1]=param_2; local[2]=param_3; local[3]=param_4;
    char* pcVar3 = (char*)FUN_000167a8();
    if(*pcVar3 == 2) return;
    local[0]=0xa22; local[2]=0; local[3]=0; local[1]=1;
    int uVar1 = FUN_00033cf8();
    ((u8*)local)[5] = (u8)uVar1;
    int iVar4;
    iVar4 = FUN_000167a8();
    ((u8*)local)[6] = *(u8*)(*(int*)(iVar4+0xfec)+0x5f);
    iVar4 = FUN_000167a8();
    ((u8*)local)[7] = *(u8*)(*(int*)(iVar4+0xfec)+0x64);
    iVar4 = FUN_000167a8();
    ((u8*)local)[8] = *(u8*)(*(int*)(iVar4+0xfec)+0x65);
    char cVar2 = *(volatile char*)(0x20004950UL+0x1a);
    if(cVar2 == 0){ cVar2 = (char)FUN_00037060(); }
    else if(cVar2 == 1){ cVar2 = (char)FUN_000370bc(); }
    else {
        if(cVar2 != 2) goto LAB;
        cVar2 = (char)FUN_0003719c();
    }
    ((u8*)local)[9] = (u8)(cVar2 + 1);
LAB:
    FUN_00047b1c(local, 10);
    FUN_00047ba8();
}

