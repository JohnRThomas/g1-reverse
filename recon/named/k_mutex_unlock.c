/* readable reconstruction; identity: FUN_00072558 @ 0x00072558
 * public-name: k_mutex_unlock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 *   z_ready_thread_locked                    <= FUN_000738d4 @ 0x000738d4
 *   z_reschedule                             <= FUN_000739f0 @ 0x000739f0
 *   z_unpend_first_thread                    <= FUN_000744a4 @ 0x000744a4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   k_mutex_owner_prio_check                 <= FUN_000864b2 @ 0x000864b2
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f801f                             @ 0x000f801f
 *   rodata_f813a                             @ 0x000f813a
 *   rodata_f815c                             @ 0x000f815c
 *   rodata_f8181                             @ 0x000f8181
 *   _kernel                                  @ 0x2000b448
 *   mutex_spinlock_b470                      @ 0x2000b470
 */
/* Reconstructed FUN_00072558 @ 0x72558  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern void printk(unsigned,unsigned,unsigned,unsigned);
extern void assert_post_action(unsigned,unsigned);
extern int z_spin_lock_valid(unsigned);
extern int z_spin_unlock_valid(unsigned);
extern void z_spin_lock_set_owner(unsigned);
extern void z_ready_thread_locked(void);
extern void z_reschedule(unsigned,unsigned);
extern int z_unpend_first_thread(int);
extern void k_mutex_owner_prio_check(unsigned,unsigned);
unsigned k_mutex_unlock(int param_1)
{
  unsigned ipsr, basepri; int iVar4, r3;
  ipsr = __get_IPSR();
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
  basepri = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20u);
  __ISB();
  iVar4 = z_spin_lock_valid(0x2000b470);
  if (iVar4 == 0) {
    printk(0x00099cbd,0x000f0920,0x000f08c7,0x72);
    printk(0x000f0935,0x2000b470,0,0);
    assert_post_action(0x000f08c7,0x72);
  }
  z_spin_lock_set_owner(0x2000b470);
  k_mutex_owner_prio_check(*(unsigned*)(param_1+8), *(unsigned*)(param_1+0x10));
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
    __set_BASEPRI(basepri);
    __ISB();
  } else {
    *(volatile int*)(param_1+0x10) = (int)*(signed char*)(iVar4+0xe);
    *(volatile unsigned*)(iVar4+0x90) = ipsr;
    z_ready_thread_locked();
    z_reschedule(0x2000b470, basepri);
  }
  return 0;
}
