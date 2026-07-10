#include "g1_app_symbols.h"
/* named: k_mutex_unlock */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed k_mutex_unlock @ 0x72558  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned,unsigned,unsigned,unsigned);
extern void assert_post_action(unsigned,unsigned);
extern int z_spin_lock_valid(unsigned);
extern int z_spin_unlock_valid(unsigned);
extern void z_spin_lock_set_owner(unsigned);
extern void z_ready_thread_locked(void);
extern void z_reschedule(unsigned,unsigned);
extern int z_unpend_first_thread(int);
extern void adjust_owner_prio /*compiler-clone .isra.0*/(unsigned,unsigned);
unsigned k_mutex_unlock(int param_1)
{
  unsigned ipsr, basepri; int iVar4, r3;
  __asm__ volatile("mrs %0, ipsr":"=r"(ipsr));
  if (ipsr != 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"!arch_is_in_isr()" /*=0xf801f*/,"WEST_TOPDIR/zephyr/kernel/mutex.c" /*=0xf813a*/,0xcd);
    printk("\tmutexes cannot be used inside ISRs\n" /*=0xf815c*/,0,0,0);
    assert_post_action("WEST_TOPDIR/zephyr/kernel/mutex.c" /*=0xf813a*/,0xcd);
  }
  r3 = *(int*)(param_1+8);
  if (r3 == 0) return 0xffffffea;
  if (r3 != *(int*)(((uintptr_t)&g_zephyr_kernel) /*=0x2000b448*/+8)) return 0xffffffff;
  iVar4 = *(int*)(param_1+0xc);
  if (iVar4 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"mutex->lock_count > 0U" /*=0xf8181*/,"WEST_TOPDIR/zephyr/kernel/mutex.c" /*=0xf813a*/,0xe5);
    assert_post_action("WEST_TOPDIR/zephyr/kernel/mutex.c" /*=0xf813a*/,0xe5);
  }
  if (iVar4 != 1) {
    *(volatile int*)(param_1+0xc) = iVar4 - 1;
    return 0;
  }
  __asm__ volatile("mrs %0, basepri":"=r"(basepri));
  __asm__ volatile("msr basepri_max, %0"::"r"(0x20u));
  __asm__ volatile("isb");
  iVar4 = z_spin_lock_valid(((uintptr_t)&sched_spinlock) /*=0x2000b470*/);
  if (iVar4 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_lock_valid(l)" /*=0xf0920*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0x72);
    printk("\tInvalid spinlock %p\n" /*=0xf0935*/,((uintptr_t)&sched_spinlock) /*=0x2000b470*/,0,0);
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0x72);
  }
  z_spin_lock_set_owner(((uintptr_t)&sched_spinlock) /*=0x2000b470*/);
  adjust_owner_prio /*compiler-clone .isra.0*/(*(unsigned*)(param_1+8), *(unsigned*)(param_1+0x10));
  iVar4 = z_unpend_first_thread(param_1);
  *(volatile int*)(param_1+8) = iVar4;
  if (iVar4 == 0) {
    *(volatile int*)(param_1+0xc) = 0;
    iVar4 = z_spin_unlock_valid(((uintptr_t)&sched_spinlock) /*=0x2000b470*/);
    if (iVar4 == 0) {
      printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_unlock_valid(l)" /*=0xf08f4*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0xf0);
      printk("\tNot my spinlock %p\n" /*=0xf090b*/,((uintptr_t)&sched_spinlock) /*=0x2000b470*/,0,0);
      assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0xf0);
    }
    __asm__ volatile("msr basepri, %0"::"r"(basepri));
    __asm__ volatile("isb");
  } else {
    *(volatile int*)(param_1+0x10) = (int)*(signed char*)(iVar4+0xe);
    *(volatile unsigned*)(iVar4+0x90) = ipsr;
    z_ready_thread_locked();
    z_reschedule(((uintptr_t)&sched_spinlock) /*=0x2000b470*/, basepri);
  }
  return 0;
}

