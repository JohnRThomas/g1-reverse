#include "g1_app_symbols.h"
/* named: ble_notify_remote_info_available */
/* globals referenced:
//   0x2000ad1c  g_ble_conn_cb_list_head      
*/
/* Reconstructed ble_notify_remote_info_available @ 0x56da8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_000819ea(void);
extern void printk(unsigned,...);
extern void assert_post_action(unsigned,unsigned);
typedef void (*fp)(int,...);
void ble_notify_remote_info_available(int param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    *(unsigned char*)(param_1 + 10) = *(unsigned char*)(param_1 + 9);
    FUN_000819ea();
    int iVar3 = *(volatile int*)((uintptr_t)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/;
    while (iVar3 != 0){
        fp pcVar2 = *(fp*)(iVar3 + 0x14);
        if (pcVar2 != 0){
            pcVar2(param_1, *(unsigned char*)(param_1+9), param_3, pcVar2, param_4);
        }
        iVar3 = *(int*)(iVar3 + 0x20);
    }
    unsigned uVar4 = ((uintptr_t)&tbl_87fc8) /*=0x87fec*/;
    unsigned uVar1 = ((uintptr_t)&tbl_88058) /*=0x88058*/;
    while (1){
        if (uVar1 < uVar4){
            printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "cb <= _bt_conn_cb_list_end" /*=0xf3a8d*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/, 0x8ca);
            printk("\tunexpected list end location\n" /*=0xf0d20*/);
            assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c" /*=0xf3a5d*/, 0x8ca);
        }
        if (uVar1 <= uVar4) break;
        if (*(fp*)(uVar4 + 0x14) != 0){
            (*(fp*)(uVar4 + 0x14))(param_1, *(unsigned char*)(param_1+9), param_3);
        }
        uVar4 = uVar4 + 0x24;
    }
}

