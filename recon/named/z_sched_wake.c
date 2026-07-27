/* readable reconstruction; identity: FUN_00074a54 @ 0x00074a54
 * public-name: z_sched_wake
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   sched_ready_queue_insert                 <= FUN_00073840 @ 0x00073840
 *   z_abort_thread_timeout                   <= FUN_00074274 @ 0x00074274
 *   z_sched_wake                             <= FUN_00074a54 @ 0x00074a54
 *   z_abort_timeout                          <= FUN_00074d74 @ 0x00074d74
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   sched_spinlock                           @ 0x2000b490
 */
/* Reconstructed FUN_00074a54 @ 0x74a54  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../headers/g1_log.h"
extern int z_spin_lock_valid(unsigned int*);
extern int z_spin_unlock_valid(uint32_t);
extern int z_spin_lock_set_owner(unsigned int*);
extern void sched_ready_queue_insert(void*);
extern void z_abort_thread_timeout(void*);
extern void z_abort_timeout(void*);
extern int assert_post_action(int, int);

int z_sched_wake(int *param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
  uint32_t sb;
  int iVar3, iVar4;
  int *piVar5;
  __asm volatile("mrs %0, basepri" : "=r"(sb));
  __asm volatile("msr basepri_max, %0" :: "r"((uint32_t)0x20));
  __asm volatile("isb sy");
  iVar3 = z_spin_lock_valid(0x2000b490);
  if (iVar3 == 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"z_spin_lock_valid(l)"), 0xf08c7, 0x72, param_4);
    printk(((unsigned long)"\tInvalid spinlock %p\n"), 0x2000b490);
    assert_post_action(0xf08c7, 0x72);
  } else {
    z_spin_lock_set_owner(0x2000b490);
    piVar5 = (int*)*param_1;
    if (param_1 == piVar5) iVar3 = 0;
    else if (piVar5 == 0) iVar3 = 0;
    else {
      piVar5[0x24] = param_2;
      piVar5[5] = param_3;
      z_abort_thread_timeout(piVar5);
      z_abort_timeout(piVar5 + 6);
      sched_ready_queue_insert(piVar5);
    }
    iVar4 = z_spin_unlock_valid(0x2000b490);
    if (iVar4 != 0){
      __asm volatile("msr basepri, %0" :: "r"(sb));
      __asm volatile("isb sy");
      return iVar3;
    }
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"z_spin_unlock_valid(l)"), 0xf08c7, 0xf0, param_4);
    printk(((unsigned long)"\tNot my spinlock %p\n"), 0x2000b490);
    assert_post_action(0xf08c7, 0xf0);
  }
  return iVar3;
}
