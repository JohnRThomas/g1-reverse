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
extern void adjust_owner_prio.isra.0(unsigned,unsigned);
unsigned k_mutex_unlock(int param_1)
{
  unsigned ipsr, basepri; int iVar4, r3;
  __asm__ volatile("mrs %0, ipsr":"=r"(ipsr));
  if (ipsr != 0) {
    printk(0x00099cbd,0x000f801f,0x000f813a,0xcd);
    printk(0x000f815c,0,0,0);
    assert_post_action(0x000f813a,0xcd);
  }
  r3 = *(int*)(param_1+8);
  if (r3 == 0) return 0xffffffea;
  if (r3 != *(int*)(0x2000b448+8)) return 0xffffffff;
  iVar4 = *(int*)(param_1+0xc);
  if (iVar4 == 0) {
    printk(0x00099cbd,0x000f8181,0x000f813a,0xe5);
    assert_post_action(0x000f813a,0xe5);
  }
  if (iVar4 != 1) {
    *(volatile int*)(param_1+0xc) = iVar4 - 1;
    return 0;
  }
  __asm__ volatile("mrs %0, basepri":"=r"(basepri));
  __asm__ volatile("msr basepri_max, %0"::"r"(0x20u));
  __asm__ volatile("isb");
  iVar4 = z_spin_lock_valid(0x2000b470);
  if (iVar4 == 0) {
    printk(0x00099cbd,0x000f0920,0x000f08c7,0x72);
    printk(0x000f0935,0x2000b470,0,0);
    assert_post_action(0x000f08c7,0x72);
  }
  z_spin_lock_set_owner(0x2000b470);
  adjust_owner_prio.isra.0(*(unsigned*)(param_1+8), *(unsigned*)(param_1+0x10));
  iVar4 = z_unpend_first_thread(param_1);
  *(volatile int*)(param_1+8) = iVar4;
  if (iVar4 == 0) {
    *(volatile int*)(param_1+0xc) = 0;
    iVar4 = z_spin_unlock_valid(0x2000b470);
    if (iVar4 == 0) {
      printk(0x00099cbd,0x000f08f4,0x000f08c7,0xf0);
      printk(0x000f090b,0x2000b470,0,0);
      assert_post_action(0x000f08c7,0xf0);
    }
    __asm__ volatile("msr basepri, %0"::"r"(basepri));
    __asm__ volatile("isb");
  } else {
    *(volatile int*)(param_1+0x10) = (int)*(signed char*)(iVar4+0xe);
    *(volatile unsigned*)(iVar4+0x90) = ipsr;
    z_ready_thread_locked();
    z_reschedule(0x2000b470, basepri);
  }
  return 0;
}

