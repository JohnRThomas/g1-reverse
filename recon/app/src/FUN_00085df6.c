/* Reconstructed FUN_00085df6 @ 0x85df6  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int FUN_00085dd2(void);
extern int FUN_00085c12(u32*,int,u32,u32);
int FUN_00085df6(u32* param_1, u32 param_2, u32 param_3, u32 param_4){
    u8 r2 = *(u8*)((char*)param_1 + 0x10);
    u32 uVar3 = r2;
    if(r2 != 0){
        int iVar1 = FUN_00085dd2();
        if(iVar1 == 0) return 0;
        uVar3 = 0xffffffff;
        *(u8*)((char*)param_1 + 0x10) = 0;
    }
    return FUN_00085c12(param_1, 7, uVar3, param_4);
}

