#include "g1_app_symbols.h"
/* named: FUN_00054dd8 */
/* Reconstructed FUN_00054dd8 @ 0x54dd8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
extern int bt_addr_le_eq(int,int);
extern int memcmp(int,void*,int);
extern void memset_bytes(void*,int,int);

void FUN_00054dd8(int param_1, int *param_2){
    unsigned char auStack_30[24];
    unsigned uVar3;
    if (param_2 == 0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "conflict != ((void *)0)" /*=0xf3537*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/id.c" /*=0xf3509*/, 0x36c);
        uVar3=0x36c; assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/id.c" /*=0xf3509*/, uVar3); return;
    }
    int iVar4 = *param_2;
    if (iVar4 == 0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "conflict->candidate != ((void *)0)" /*=0xf354f*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/id.c" /*=0xf3509*/, 0x36d);
        uVar3=0x36d; assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/id.c" /*=0xf3509*/, uVar3); return;
    } else if (param_1 == 0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "resident != ((void *)0)" /*=0xf3572*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/id.c" /*=0xf3509*/, 0x36e);
        uVar3=0x36e; assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/id.c" /*=0xf3509*/, uVar3); return;
    } else {
        if (-1 < (int)((unsigned)*(unsigned char*)(iVar4+8) << 0x1d)){
            if (param_2[1] == 0 && (int)((unsigned)*(unsigned char*)(param_1+8) << 0x1d) < 0){
                int iVar1 = bt_addr_le_eq(iVar4+1, param_1+1);
                memset_bytes(auStack_30, 0, 0x16);
                int iVar2 = memcmp(iVar4+0x2a, auStack_30, 0x10);
                if ((iVar2 != 0 && memcmp(iVar4+0x2a, (void*)(param_1+0x2a), 0x10) == 0) || iVar1 != 0){
                    param_2[1] = param_1;
                }
            }
            return;
        }
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "(conflict->candidate->state & BT_KEYS_ID_ADDED) == 0" /*=0xf358a*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/id.c" /*=0xf3509*/, 0x370);
        uVar3=0x370; assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/id.c" /*=0xf3509*/, uVar3); return;
    }
}

