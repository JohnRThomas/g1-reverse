#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_000742b4 @ 0x000742b4
 * public-name: unpend_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   z_abort_thread_timeout                   <= FUN_00074274 @ 0x00074274
 *   unpend_thread                            <= FUN_000742b4 @ 0x000742b4
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
/* Reconstructed FUN_000742b4 @ 0x742b4  (parity: 300/300 trials, PROVEN) */

extern int z_spin_lock_valid(unsigned int*);
extern int z_spin_unlock_valid(int);
extern int z_spin_lock_set_owner(unsigned int*);
extern void z_abort_thread_timeout(int);
extern void z_abort_timeout(int);
extern int assert_post_action(int, int);
void unpend_thread(int param_1,int param_2,int param_3,int param_4){
  int r=z_spin_lock_valid(((unsigned long)&sched_spinlock) /*=0x2000b490*/);
  if(r==0){ printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"z_spin_lock_valid(l)") /*=0xf0920*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72,param_4); printk(((unsigned long)"\tInvalid spinlock %p\n") /*=0xf0935*/,((unsigned long)&sched_spinlock) /*=0x2000b490*/); assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72); }
  z_spin_lock_set_owner(((unsigned long)&sched_spinlock) /*=0x2000b490*/);
  if(*(int*)(param_1+8)!=0) z_abort_thread_timeout(param_1);
  r=z_spin_unlock_valid(((unsigned long)&sched_spinlock) /*=0x2000b490*/);
  if(r!=0){ z_abort_timeout(param_1+0x18); return; }
  printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0,param_4); printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/,((unsigned long)&sched_spinlock) /*=0x2000b490*/); assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
}
