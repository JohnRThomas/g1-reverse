#include "g1_app_symbols.h"
/* named: FUN_00072e9c */
/* Reconstructed FUN_00072e9c @ 0x72e9c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(uint32_t);
extern int z_spin_unlock_valid(uint32_t);
extern void z_spin_lock_set_owner(uint32_t);
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
unsigned FUN_00072e9c(int param_1,uint32_t p2,uint32_t p3,uint32_t p4){
  int iVar2=z_spin_lock_valid(((uintptr_t)&timer_spinlock) /*=0x2000b480*/);
  if(iVar2==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_lock_valid(l)" /*=0xf0920*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0x72,p4);
    printk("\tInvalid spinlock %p\n" /*=0xf0935*/,((uintptr_t)&timer_spinlock) /*=0x2000b480*/,0,0,0);
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0x72);
    return 0;
  }
  z_spin_lock_set_owner(((uintptr_t)&timer_spinlock) /*=0x2000b480*/);
  unsigned uVar3=*(volatile unsigned*)(param_1+0xc) & 0xf;
  iVar2=z_spin_unlock_valid(((uintptr_t)&timer_spinlock) /*=0x2000b480*/);
  if(iVar2!=0) return uVar3;
  printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_unlock_valid(l)" /*=0xf08f4*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0xf0,p4);
  printk("\tNot my spinlock %p\n" /*=0xf090b*/,((uintptr_t)&timer_spinlock) /*=0x2000b480*/,0,0,0);
  assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0xf0);
  return 0;
}

