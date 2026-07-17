#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00073960 @ 0x00073960
 * public-name: FUN_00073960
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
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
 *   sched_spinlock_b490                      @ 0x2000b490
 */
/* Reconstructed FUN_00073960 @ 0x73960  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(uint32_t);
extern int z_spin_unlock_valid(uint32_t);
extern void z_spin_lock_set_owner(uint32_t);
extern void z_abort_thread_timeout(int);
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
void FUN_00073960(int param_1,uint32_t p2,uint32_t p3,uint32_t p4){
  int iVar3=z_spin_lock_valid(((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/);
  if(iVar3==0){
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f0920) /*=0xf0920*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72,p4);
    printk(((unsigned long)&rodata_f0935) /*=0xf0935*/,((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/,0,0,0);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72);
    return;
  }
  z_spin_lock_set_owner(((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/);
  if(*(volatile int*)(param_1+8)!=0) z_abort_thread_timeout(param_1);
  iVar3=z_spin_unlock_valid(((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/);
  if(iVar3!=0) return;
  printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f08f4) /*=0xf08f4*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0,p4);
  printk(((unsigned long)&rodata_f090b) /*=0xf090b*/,((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/,0,0,0);
  assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
}
