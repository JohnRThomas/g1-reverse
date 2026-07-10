#include "g1_app_symbols.h"
/* named: z_reschedule */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed z_reschedule @ 0x739f0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_unlock_valid(int);
extern void FUN_000501d4(int);
extern void assert_post_action(int,int);
extern void printk(int,...);
void z_reschedule(int param_1, int param_2){
  unsigned int r6;
  int r0v;
  if(param_2 == 0){
    __asm volatile("mrs %0, ipsr" : "=r"(r6));
    if(r6 == 0){
      volatile int *g = (volatile int*)((uintptr_t)&g_zephyr_kernel) /*=0x2000b448*/;
      if(g[6] != g[2]){
        r0v = z_spin_unlock_valid(param_1);
        if(r0v != 0){ FUN_000501d4(r6); return; }
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_unlock_valid(l)" /*=0xf08f4*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0x111);
        printk("\tNot my spinlock %p\n" /*=0xf090b*/, param_1);
        assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0x111);
        return;
      }
    }
  }
  r0v = z_spin_unlock_valid(param_1);
  if(r0v != 0){
    __asm volatile("msr basepri, %0" :: "r"(param_2));
    __asm volatile("isb");
    return;
  }
  printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_unlock_valid(l)" /*=0xf08f4*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0xf0);
  printk("\tNot my spinlock %p\n" /*=0xf090b*/, param_1);
  assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0xf0);
}

