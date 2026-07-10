#include "g1_app_symbols.h"
/* named: FUN_00073bf4 */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed FUN_00073bf4 @ 0x73bf4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(void*);
extern int z_spin_unlock_valid(void*);
extern void z_spin_lock_set_owner(void*);
extern void FUN_000737d8(void);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
extern void z_reschedule_irqlock(unsigned);

void FUN_00073bf4(void){
    int iVar3 = z_spin_lock_valid((void*)((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
    if (iVar3 == 0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_lock_valid(l)" /*=0xf0920*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0x72);
        printk("\tInvalid spinlock %p\n" /*=0xf0935*/, ((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
        assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0x72);
        return;
    }
    z_spin_lock_set_owner((void*)((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
    char cVar1 = *(char*)(*(int*)(((uintptr_t)&g_zephyr_kernel) /*=0x2000b448*/+8)+0xf);
    unsigned r2 = (unsigned)*(int*)(((uintptr_t)&g_zephyr_kernel) /*=0x2000b448*/+8);
    unsigned r3 = (unsigned char)cVar1;
    if (cVar1 == 0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "_kernel.cpus[0].current->base.sched_locked != 0U" /*=0xf8553*/, "WEST_TOPDIR/zephyr/kernel/sched.c" /*=0xf82f4*/, 0x3f8);
        printk("\t\n" /*=0xf53ff*/);
        assert_post_action("WEST_TOPDIR/zephyr/kernel/sched.c" /*=0xf82f4*/, 0x3f8);
        r2 = "WEST_TOPDIR/zephyr/kernel/sched.c" /*=0xf82f4*/;
        r3 = 0x3f8;
        /* fall through in emulation (ipsr==0) */
    }
    *(char*)(r2 + 0xf) = (char)(r3 + 1);
    FUN_000737d8();
    iVar3 = z_spin_unlock_valid((void*)((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
    if (iVar3 != 0){
        z_reschedule_irqlock(0);
        return;
    }
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_unlock_valid(l)" /*=0xf08f4*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0xf0);
    printk("\tNot my spinlock %p\n" /*=0xf090b*/, ((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0xf0);
}

