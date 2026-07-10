#include "g1_net_symbols.h"
/* net-core FUN_0100a1e0 @ 0x100a1e0  (parity 300 trials PROVEN) */

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int i32;

#define A_0100a310 ((uintptr_t)&g_net_bufpool_slot_cnt) /*=0x21000bb8*/
#define A_0100a314 ((uintptr_t)&g_net_bufpool_base_ptr) /*=0x21000bbc*/
#define A_0100a318 ((uintptr_t)&g_net_storage_area_id) /*=0x21000bc0*/

extern void FUN_01008d00(u32 a, u32 b);

u32 FUN_0100a1e0(u32 param_1, u32 param_2_raw, u32 param_3_raw, u32 param_4_raw)
{
    u32 uVar3 = param_1;
    u8 param_2 = (u8)param_2_raw;
    u8 param_3 = (u8)param_3_raw;
    u16 param_4 = (u16)param_4_raw;
    char cVar2;
    u16 local_e;
    u16 uVar1;
    i32 local_c;
    u8 local_f;
    if (param_1 == 0) uVar3 = 1;
    cVar2 = (char)uVar3;
    if (param_1 != 0) cVar2 = 0;
    *(volatile u8*)A_0100a310 = (u8)(param_3 + param_2);
    if ((param_1 & 3) != 0) {
        FUN_01008d00(9, 0x4e);
    }
    if (param_4 < 0x20) {
        local_e = (u16)(param_4 << 2);
    } else if (param_4 < 0x100) {
        if ((u32)param_4 * 2 <= 0x7c) {
            local_e = 0x7c;
        } else {
            local_e = (u16)((u32)param_4 * 2);
        }
    } else {
        if ((u32)param_4 + 0xff >= (u32)param_4 * 2) {
            local_e = (u16)((u32)param_4 * 2);
        } else {
            local_e = (u16)((u32)param_4 + 0xff);
        }
    }
    uVar1 = (u16)((local_e + 3U) & 0xfffc);
    if (cVar2 != 1) {
        *(volatile u32*)A_0100a314 = param_1;
        *(volatile u16*)A_0100a318 = uVar1;
    }
    local_c = (i32)(*(volatile u8*)A_0100a310) * 0x28;
    for (local_f = 0; local_f < *(volatile u8*)A_0100a310; local_f = local_f + 1) {
        if (cVar2 != 1) {
            *(volatile u8*)((u32)local_f * 0x28 + *(volatile u32*)A_0100a314) = 1;
            *(volatile u32*)((u32)local_f * 0x28 + *(volatile u32*)A_0100a314 + 4) = local_c + param_1;
        }
        local_c = uVar1 + local_c;
    }
    return (local_c + 7U) & 0xfffffff8;
}


