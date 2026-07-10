#include "g1_app_symbols.h"
/* named: FUN_00074a54 */
/* Reconstructed FUN_00074a54 @ 0x74a54  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int z_spin_lock_valid(uint32_t);
extern int z_spin_unlock_valid(uint32_t);
extern void z_spin_lock_set_owner(uint32_t);
extern void sched_ready_queue_insert(void*);
extern void z_abort_thread_timeout(void*);
extern void FUN_00074d74(void*);
extern void assert_post_action(uint32_t, uint32_t);
extern void printk(uint32_t, uint32_t, ...);

int FUN_00074a54(int *param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
  uint32_t sb;
  int iVar3, iVar4;
  int *piVar5;
  __asm volatile("mrs %0, basepri" : "=r"(sb));
  __asm volatile("msr basepri_max, %0" :: "r"((uint32_t)0x20));
  __asm volatile("isb sy");
  iVar3 = z_spin_lock_valid(((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
  if (iVar3 == 0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_lock_valid(l)" /*=0xf0920*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0x72, param_4);
    printk("\tInvalid spinlock %p\n" /*=0xf0935*/, ((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0x72);
  } else {
    z_spin_lock_set_owner(((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
    piVar5 = (int*)*param_1;
    if (param_1 == piVar5) iVar3 = 0;
    else if (piVar5 == 0) iVar3 = 0;
    else {
      piVar5[0x24] = param_2;
      piVar5[5] = param_3;
      z_abort_thread_timeout(piVar5);
      FUN_00074d74(piVar5 + 6);
      sched_ready_queue_insert(piVar5);
    }
    iVar4 = z_spin_unlock_valid(((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
    if (iVar4 != 0){
      __asm volatile("msr basepri, %0" :: "r"(sb));
      __asm volatile("isb sy");
      return iVar3;
    }
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_unlock_valid(l)" /*=0xf08f4*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0xf0, param_4);
    printk("\tNot my spinlock %p\n" /*=0xf090b*/, ((uintptr_t)&sched_spinlock_b490) /*=0x2000b490*/);
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0xf0);
  }
  return iVar3;
}

