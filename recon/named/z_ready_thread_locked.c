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
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   sched_spinlock_b490                      @ 0x2000b490
 */
/* Reconstructed FUN_000738d4 @ 0x738d4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(uint32_t);
extern int z_spin_unlock_valid(uint32_t);
extern void z_spin_lock_set_owner(uint32_t);
extern void sched_ready_queue_insert(int);
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
void z_ready_thread_locked(int param_1,uint32_t p2,uint32_t p3,uint32_t p4){
  int iVar3=z_spin_lock_valid(0x2000b490);
  if(iVar3==0){
    printk(0x99cbd,0xf0920,0xf08c7,0x72,p4);
    printk(0xf0935,0x2000b490,0,0,0);
    assert_post_action(0xf08c7,0x72);
    return;
  }
  z_spin_lock_set_owner(0x2000b490);
  sched_ready_queue_insert(param_1);
  iVar3=z_spin_unlock_valid(0x2000b490);
  if(iVar3!=0){ return; }
  printk(0x99cbd,0xf08f4,0xf08c7,0xf0,p4);
  printk(0xf090b,0x2000b490,0,0,0);
  assert_post_action(0xf08c7,0xf0);
}
