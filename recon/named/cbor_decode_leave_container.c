/* named: cbor_decode_leave_container */
/* Reconstructed cbor_decode_leave_container @ 0x85df6  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int cbor_decode_expect_break(void);
extern int FUN_00085c12(u32*,int,u32,u32);
int cbor_decode_leave_container(u32* param_1, u32 param_2, u32 param_3, u32 param_4){
    u8 r2 = *(u8*)((char*)param_1 + 0x10);
    u32 uVar3 = r2;
    if(r2 != 0){
        int iVar1 = cbor_decode_expect_break();
        if(iVar1 == 0) return 0;
        uVar3 = 0xffffffff;
        *(u8*)((char*)param_1 + 0x10) = 0;
    }
    return FUN_00085c12(param_1, 7, uVar3, param_4);
}

