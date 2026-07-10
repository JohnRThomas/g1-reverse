/* Reconstructed FUN_0005a3c4 @ 0x5a3c4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8; typedef uint16_t u16;
typedef void (*fp)(int);
extern void FUN_000566a4(void);
extern int FUN_00056e74(int,void*);
extern void FUN_0005a090(int);
extern int FUN_00080f92(int,int);
extern int FUN_000814e6(int,int,void*);
extern void FUN_000828da(void*,u32);
u32 FUN_0005a3c4(int param_1, u32 param_2, int param_3){
    if( (*(int*)(param_1+8) == 0x0005a465)
        && (({u8* puVar2 = *(u8**)(param_1+0xc); *(short*)(puVar2+10) != 0;})) ){
        u8* puVar2 = *(u8**)(param_1+0xc);
        if(*(short*)(puVar2+8) != 0){
            u8* puVar3 = puVar2+1;
            int iVar1 = FUN_000814e6(param_3, *puVar2, puVar3);
            if(iVar1 == 0){
                iVar1 = FUN_00056e74(*puVar2, puVar3);
                if(iVar1 != 0){
                    if(*(char*)(iVar1+0xd) == 7){ FUN_000566a4(); return 1; }
                    FUN_000566a4();
                }
            } else {
                iVar1 = FUN_00080f92(*(u8*)(param_3+8), param_3+0x90);
                if(iVar1 == 0){
                    if(puVar2 == (u8*)0x20002a20UL) FUN_0005a090(param_3);
                    FUN_000828da(puVar3, 0x000f2b3a);
                    *puVar2 = 0;
                    *(u16*)(puVar2+8) = 0;
                } else {
                    FUN_000828da(puVar3, param_3+0x90);
                }
            }
        }
        *(u16*)(puVar2+10) = 0;
        if(*(fp*)(puVar2+0xc) != 0){
            (*(fp*)(puVar2+0xc))(param_1);
        }
    }
    return 1;
}

