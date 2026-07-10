#include "g1_app_symbols.h"
/* named: k_uptime_ticks_impl */
/* Reconstructed k_uptime_ticks_impl @ 0x74f68  (parity: 80/80 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(unsigned int);
extern void z_spin_lock_set_owner(unsigned int);
extern unsigned int rtc_get_elapsed_cycles_since_baseline(void);
extern int z_spin_unlock_valid(unsigned int);
extern void printk(unsigned int,...);
extern void assert_post_action(unsigned int,...);
unsigned long long k_uptime_ticks_impl(void){
  unsigned int uVar6=0;
  int iVar2=z_spin_lock_valid(((uintptr_t)&g_timeout_list_spinlock) /*=0x2000b498*/);
  if(iVar2==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_lock_valid(l)" /*=0xf0920*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0x72);
    printk("\tInvalid spinlock %p\n" /*=0xf0935*/,((uintptr_t)&g_timeout_list_spinlock) /*=0x2000b498*/);
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0x72);
  }
  z_spin_lock_set_owner(((uintptr_t)&g_timeout_list_spinlock) /*=0x2000b498*/);
  unsigned int uVar3=rtc_get_elapsed_cycles_since_baseline();
  unsigned int uVar4=*(volatile unsigned int*)((uintptr_t)&g_curr_tick_lo) /*=0x200069e0*/;
  unsigned int uVar5=*(volatile unsigned int*)((uintptr_t)&g_curr_tick_hi) /*=0x200069e4*/;
  int iVar2b=z_spin_unlock_valid(((uintptr_t)&g_timeout_list_spinlock) /*=0x2000b498*/);
  if(iVar2b==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_unlock_valid(l)" /*=0xf08f4*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0xf0);
    printk("\tNot my spinlock %p\n" /*=0xf090b*/,((uintptr_t)&g_timeout_list_spinlock) /*=0x2000b498*/);
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0xf0);
  }
  (void)uVar6;
  unsigned int r0res=uVar3+uVar4;
  unsigned int r1res=uVar5 + (unsigned int)((int)uVar3>>31) + (unsigned int)(((unsigned long long)uVar3+uVar4)>>32);
  return ((unsigned long long)r1res<<32)|r0res;
}

