#include "g1_app_symbols.h"
/* named: l2cap_chan_add */
/* Reconstructed l2cap_chan_add @ 0x57874  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8; typedef uint16_t u16;
extern uint64_t bt_l2cap_le_lookup_tx_cid(int,unsigned);
extern void FUN_00081746(u32,int,void*);
extern void FUN_000732d4(int,u32);
extern void k_work_init(int,u32);
extern void z_impl_k_queue_init(int);
u32 l2cap_chan_add(int param_1, int param_2, int param_3){
    if(*(volatile short*)(param_2+0x14) == 0){
        unsigned uVar2 = 0x40;
        do {
            uint64_t uVar4 = bt_l2cap_le_lookup_tx_cid(param_1, uVar2);
            if((int)(u32)uVar4 == 0){
                *(volatile short*)(param_2+0x14) = (short)(u32)(uVar4 >> 32);
                goto LAB;
            }
            uVar2 = (((u32)(uVar4 >> 32)) + 1) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
        } while(uVar2 != 0x80);
        u32 local[2];
        local[0] = 2;
        FUN_00081746(((uintptr_t)&tbl_880d8) /*=0x88160*/, 0x1040, local);
        return 0;
    }
LAB: ;
    *(volatile u32*)(param_2+0x10) = 0;
    *(volatile u32*)(param_2+8) = 0;
    int piVar3 = param_2 + 8;
    if(*(void* volatile*)(param_1+0x58) == 0){
        *(int* volatile*)(param_1+0x54) = (int*)piVar3;
        *(int* volatile*)(param_1+0x58) = (int*)piVar3;
    } else {
        int r1 = *(int* volatile*)(param_1+0x58) ? (int)*(int* volatile*)(param_1+0x58) : 0;
        *(int* volatile*)r1 = (int*)piVar3;
        *(int* volatile*)(param_1+0x58) = (int*)piVar3;
    }
    *(volatile int*)param_2 = param_1;
    *(volatile int*)(param_2+0xc) = param_3;
    FUN_000732d4(param_2 + 0xc0, ((uintptr_t)&tbl_574e4) /*=0x57525*/);
    if((u16)((u16)(*(volatile u16*)(param_2+0x14)) - 0x40) <= 0x3f){
        k_work_init(param_2 + 0x88, ((uintptr_t)&rodata_81b83) /*=0x81b83*/);
        z_impl_k_queue_init(param_2 + 0x98);
        *(volatile u8*)(param_2 + 0xb4) = 1;
    }
    return 1;
}

