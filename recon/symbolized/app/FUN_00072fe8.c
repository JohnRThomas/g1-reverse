#include "g1_app_symbols.h"
/* named: FUN_00072fe8 */
/* Reconstructed FUN_00072fe8 @ 0x72fe8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int z_spin_lock_valid(uint32_t);
extern int z_spin_unlock_valid(uint32_t);
extern void z_spin_lock_set_owner(uint32_t);
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,...);
extern uint32_t cancel_async_locked(int);

uint32_t FUN_00072fe8(int param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
  uint32_t sb, uVar4;
  int iVar3;
  if (param_1 == 0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"work != ((void *)0)" /*=0xf82e0*/,"WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/,0x221,param_4);
    assert_post_action("WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/,0x221);
  }
  if ((int32_t)((uint32_t)*(int*)(param_1+0xc) << 0x17) < 0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"!flag_test(&work->flags, K_WORK_DELAYABLE_BIT)" /*=0xf8262*/,"WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/,0x222,param_4);
    assert_post_action("WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/,0x222);
  }
  __asm volatile("mrs %0, basepri" : "=r"(sb));
  __asm volatile("msr basepri_max, %0" :: "r"((uint32_t)0x20));
  __asm volatile("isb sy");
  iVar3 = z_spin_lock_valid(((uintptr_t)&timer_spinlock) /*=0x2000b480*/);
  if (iVar3 == 0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_lock_valid(l)" /*=0xf0920*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0x72,param_4);
    printk("\tInvalid spinlock %p\n" /*=0xf0935*/,((uintptr_t)&timer_spinlock) /*=0x2000b480*/);
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0x72);
  }
  z_spin_lock_set_owner(((uintptr_t)&timer_spinlock) /*=0x2000b480*/);
  uVar4 = cancel_async_locked(param_1);
  iVar3 = z_spin_unlock_valid(((uintptr_t)&timer_spinlock) /*=0x2000b480*/);
  if (iVar3 == 0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_unlock_valid(l)" /*=0xf08f4*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0xf0,param_4);
    printk("\tNot my spinlock %p\n" /*=0xf090b*/,((uintptr_t)&timer_spinlock) /*=0x2000b480*/);
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0xf0);
  }
  __asm volatile("msr basepri, %0" :: "r"(sb));
  __asm volatile("isb sy");
  return uVar4;
}

