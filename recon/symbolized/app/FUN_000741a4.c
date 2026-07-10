#include "g1_app_symbols.h"
/* named: FUN_000741a4 */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed FUN_000741a4 @ 0x741a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(void*);
extern int z_spin_unlock_valid(void*);
extern void z_spin_lock_set_owner(void*);
extern void FUN_000737d8(int);
extern void dlist_unlink_node(void*,void*);
extern void FUN_00074d74(void*);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
extern void z_reschedule_irqlock(unsigned);

void FUN_000741a4(uint8_t *param_1){
    unsigned uVar6=0;
    FUN_00074d74(param_1+0x18);
    int iVar4 = z_spin_lock_valid((void*)((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
    if (iVar4==0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_lock_valid(l)" /*=0xf0920*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0x72);
        printk("\tInvalid spinlock %p\n" /*=0xf0935*/,((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
        uVar6=0x72;
        assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,uVar6);
        return;
    }
    z_spin_lock_set_owner((void*)((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
    if ((int8_t)param_1[0xd] < 0){
        param_1[0xd] = param_1[0xd] & 0x7f;
        dlist_unlink_node((void*)((uintptr_t)&g_sched_ready_runq) /*=0x2000b464*/, param_1);
    }
    int iVar5 = *(int*)(((uintptr_t)&g_zephyr_kernel) /*=0x2000b448*/+8);
    param_1[0xd] = param_1[0xd] | 0x10;
    FUN_000737d8(iVar5 == (int)(intptr_t)param_1);
    iVar5 = z_spin_unlock_valid((void*)((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
    if (iVar5 != 0){
        if (*(int*)(((uintptr_t)&g_zephyr_kernel) /*=0x2000b448*/+8) != (int)(intptr_t)param_1) return;
        z_reschedule_irqlock(uVar6);
        return;
    }
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_unlock_valid(l)" /*=0xf08f4*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0xf0);
    printk("\tNot my spinlock %p\n" /*=0xf090b*/,((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
    uVar6=0xf0;
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,uVar6);
}

