#include "g1_app_symbols.h"
/* named: net_buf_slist_put */
/* Reconstructed net_buf_slist_put @ 0x5f074  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(void*);
extern int z_spin_unlock_valid(void*);
extern void z_spin_lock_set_owner(void*);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);

void net_buf_slist_put(uint32_t *param_1, uint32_t *param_2){
    unsigned uVar3=0, uVar5;
    if (param_1 == 0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"list" /*=0xf3630*/,"WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/,0x1ad);
        uVar5=0x1ad; uVar3="WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/;
    } else if (param_2 == 0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"buf" /*=0xf45be*/,"WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/,0x1ae);
        uVar5=0x1ae; uVar3="WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/;
    } else {
        int iVar4 = z_spin_lock_valid((void*)((uintptr_t)&g_net_buf_slist_lock) /*=0x2000b004*/);
        if (iVar4==0){
            printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_lock_valid(l)" /*=0xf0920*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0x72);
            printk("\tInvalid spinlock %p\n" /*=0xf0935*/,((uintptr_t)&g_net_buf_slist_lock) /*=0x2000b004*/);
            uVar5=0x72; uVar3="WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/;
        } else {
            z_spin_lock_set_owner((void*)((uintptr_t)&g_net_buf_slist_lock) /*=0x2000b004*/);
            *param_2 = 0;
            if (param_1[1]==0){
                param_1[0] = (uint32_t)param_2;
                param_1[1] = (uint32_t)param_2;
            } else {
                *((uint32_t*)param_1[1]) = (uint32_t)param_2;
                param_1[1] = (uint32_t)param_2;
            }
            iVar4 = z_spin_unlock_valid((void*)((uintptr_t)&g_net_buf_slist_lock) /*=0x2000b004*/);
            if (iVar4 != 0){
                return;
            }
            printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_unlock_valid(l)" /*=0xf08f4*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0xf0);
            printk("\tNot my spinlock %p\n" /*=0xf090b*/,((uintptr_t)&g_net_buf_slist_lock) /*=0x2000b004*/);
            uVar5=0xf0; uVar3="WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/;
        }
    }
    assert_post_action(uVar3,uVar5);
}

