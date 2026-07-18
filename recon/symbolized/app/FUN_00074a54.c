#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00074a54 @ 0x00074a54
 * public-name: FUN_00074a54
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   sched_ready_queue_insert                 <= FUN_00073840 @ 0x00073840
 *   z_abort_thread_timeout                   <= FUN_00074274 @ 0x00074274
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   sched_spinlock                           @ 0x2000b490
 */
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
  iVar3 = z_spin_lock_valid(((unsigned long)&sched_spinlock) /*=0x2000b490*/);
  if (iVar3 == 0){
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f0920) /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72, param_4);
    printk(((unsigned long)&rodata_f0935) /*=0xf0935*/, ((unsigned long)&sched_spinlock) /*=0x2000b490*/);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
  } else {
    z_spin_lock_set_owner(((unsigned long)&sched_spinlock) /*=0x2000b490*/);
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
    iVar4 = z_spin_unlock_valid(((unsigned long)&sched_spinlock) /*=0x2000b490*/);
    if (iVar4 != 0){
      __asm volatile("msr basepri, %0" :: "r"(sb));
      __asm volatile("isb sy");
      return iVar3;
    }
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f08f4) /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0, param_4);
    printk(((unsigned long)&rodata_f090b) /*=0xf090b*/, ((unsigned long)&sched_spinlock) /*=0x2000b490*/);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
  }
  return iVar3;
}
