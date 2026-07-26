/* readable reconstruction; identity: FUN_00073f6c @ 0x00073f6c
 * public-name: z_pend_curr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_swap                                <= FUN_000501d4 @ 0x000501d4
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   pend_locked                              <= FUN_00073f3c @ 0x00073f3c
 *   z_pend_curr                              <= FUN_00073f6c @ 0x00073f6c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f8584                             @ 0x000f8584
 *   _kernel                                  @ 0x2000b448
 *   g_pend_locked_thread_tmp                 @ 0x2000b484
 *   sched_spinlock                           @ 0x2000b490
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_00073f6c @ 0x73f6c  (parity: 300/300 trials, PROVEN) */
extern int z_spin_lock_valid(int,int,int,int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void pend_locked(int,int,int,int);
extern void arch_swap(int);
extern void assert_post_action(int,...);
void z_pend_curr(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6){
  int iVar3 = 0x2000b448;
  int iVar5 = 0x2000b490;
  (void)param_4;
  *(volatile int*)0x2000b484UL = *(volatile int*)(iVar3+8);
  if (param_1 == iVar5){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0x000f8584,0x000f82f4,0x35f);
    assert_post_action(0x000f82f4,0x35f);
    return;
  }
  if (z_spin_lock_valid(iVar5, param_2, 0x20, 0) == 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_lock_valid(l)"),0x000f08c7,0x72);
    printk(((unsigned long)"\tInvalid spinlock %p\n"),iVar5);
    assert_post_action(0x000f08c7,0x72);
    return;
  }
  z_spin_lock_set_owner(iVar5);
  pend_locked(*(volatile int*)(iVar3+8), param_3, param_5, param_6);
  if (z_spin_unlock_valid(param_1) == 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_unlock_valid(l)"),0x000f08c7,0x111);
    printk(((unsigned long)"\tNot my spinlock %p\n"),param_1);
    assert_post_action(0x000f08c7,0x111);
    return;
  }
  if (z_spin_unlock_valid(iVar5) == 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_unlock_valid(l)"),0x000f08c7,0x111);
    printk(((unsigned long)"\tNot my spinlock %p\n"),iVar5);
    assert_post_action(0x000f08c7,0x111);
    return;
  }
  arch_swap(param_2);
}
