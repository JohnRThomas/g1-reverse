#include "g1_app_symbols.h"
/* named: ble_notify_le_param_updated */
/* globals referenced:
//   0x2000ad1c  g_ble_conn_cb_list_head      
*/
/* Reconstructed ble_notify_le_param_updated @ 0x56ae0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint16_t u16;
typedef void (*fp)(int,u32,u32,u32);
extern void atomic_and_2(int*,u32,int,int,u32);
extern void printk(u32,...);
extern void assert_post_action(u32,u32);
void ble_notify_le_param_updated(int param_1, u32 p2, u32 p3, u32 p4){
    if( ((int)(*(volatile u32*)(param_1+4) << 0x16) < 0)
        && (*(u16*)(param_1+0xa8) <= *(u16*)(param_1+0xa6))
        && (*(u16*)(param_1+0xa6) <= *(u16*)(param_1+0xaa)) ){
        if(*(int*)(param_1+0xac) == *(int*)(param_1+0xb0)){
            atomic_and_2((int*)(param_1+4), 0xfffffdff, *(int*)(param_1+0xac), *(int*)(param_1+0xb0), p4);
        }
    }
    int iVar2 = *(volatile int*)((uintptr_t)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/;
    for(; iVar2 != 0; iVar2 = *(int*)(iVar2+0x20)){
        fp f = *(fp*)(iVar2+0xc);
        if(f != 0) f(param_1, *(u16*)(param_1+0xa6), *(u16*)(param_1+0xac), *(u16*)(param_1+0xae));
    }
    u32 uVar1 = ((uintptr_t)&tbl_88058) /*=0x88058*/;
    u32 uVar3 = ((uintptr_t)&tbl_87fc8) /*=0x87fec*/;
    while(1){
        if(uVar1 < uVar3){
            printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "cb <= _bt_conn_cb_list_end" /*=0xf3a8d*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/, 0x634);
            printk("\tunexpected list end location\n" /*=0xf0d20*/);
            assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/, 0x634);
        }
        if(uVar1 <= uVar3) break;
        fp f = *(fp*)(uVar3+0xc);
        if(f != 0) f(param_1, *(u16*)(param_1+0xa6), *(u16*)(param_1+0xac), *(u16*)(param_1+0xae));
        uVar3 += 0x24;
    }
}

