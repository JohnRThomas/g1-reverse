#include "g1_app_symbols.h"
/* named: FUN_00074844 */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed FUN_00074844 @ 0x74844  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000741a4(int);
extern int FUN_000746fc(void);
extern int assert_post_action(int,int);
extern int printk(int,...);
uint32_t FUN_00074844(int param_1,int param_2,int param_3,int param_4){
  uint32_t ipsr;
  __asm volatile("mrs %0, ipsr":"=r"(ipsr));
  if(ipsr != 0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "!arch_is_in_isr()" /*=0xf801f*/, "WEST_TOPDIR/zephyr/kernel/sched.c" /*=0xf82f4*/, 0x5c1, param_4);
    printk("\t\n" /*=0xf53ff*/);
    assert_post_action("WEST_TOPDIR/zephyr/kernel/sched.c" /*=0xf82f4*/, 0x5c1);
  }
  if(param_2==-1 && param_1==-1){
    FUN_000741a4(*(volatile int*)(((uintptr_t)&g_zephyr_kernel) /*=0x2000b448*/+8));
    return 0xffffffff;
  }
  int iVar2 = FUN_000746fc();
  return (uint32_t)(((int64_t)iVar2 * 1000) >> 15);
}

