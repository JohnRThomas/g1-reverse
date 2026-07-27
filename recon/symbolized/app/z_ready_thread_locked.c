#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000738d4 @ 0x000738d4
 * public-name: z_ready_thread_locked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   sched_ready_queue_insert                 <= FUN_00073840 @ 0x00073840
 *   z_ready_thread_locked                    <= FUN_000738d4 @ 0x000738d4
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
/* Reconstructed FUN_000738d4 @ 0x738d4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern int z_spin_lock_valid(unsigned int*);
extern int z_spin_unlock_valid(uint32_t);
extern int z_spin_lock_set_owner(unsigned int*);
extern void sched_ready_queue_insert(int);
extern int assert_post_action(int, int);
void z_ready_thread_locked(int param_1,uint32_t p2,uint32_t p3,uint32_t p4){
  int iVar3=z_spin_lock_valid(((unsigned long)&sched_spinlock) /*=0x2000b490*/);
  if(iVar3==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"z_spin_lock_valid(l)") /*=0xf0920*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72,p4);
    printk(((unsigned long)"\tInvalid spinlock %p\n") /*=0xf0935*/,((unsigned long)&sched_spinlock) /*=0x2000b490*/,0,0,0);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72);
    return;
  }
  z_spin_lock_set_owner(((unsigned long)&sched_spinlock) /*=0x2000b490*/);
  sched_ready_queue_insert(param_1);
  iVar3=z_spin_unlock_valid(((unsigned long)&sched_spinlock) /*=0x2000b490*/);
  if(iVar3!=0){ return; }
  printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0,p4);
  printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/,((unsigned long)&sched_spinlock) /*=0x2000b490*/,0,0,0);
  assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
}
