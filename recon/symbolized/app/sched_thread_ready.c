#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00073a78 @ 0x00073a78
 * public-name: sched_thread_ready
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   sched_ready_queue_insert                 <= FUN_00073840 @ 0x00073840
 *   z_reschedule                             <= FUN_000739f0 @ 0x000739f0
 *   sched_thread_ready                       <= FUN_00073a78 @ 0x00073a78
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
/* Reconstructed FUN_00073a78 @ 0x73a78  (parity: 300/300 trials, PROVEN) */

extern int z_spin_lock_valid(int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void sched_ready_queue_insert(int);
extern void z_reschedule(int,int);
extern void assert_post_action(int,int);
extern int printk(int,...);
void sched_thread_ready(int param_1,int param_2,int param_3,int param_4){
  int r=z_spin_lock_valid(((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/);
  if(r==0){ printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f0920) /*=0xf0920*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72,param_4); printk(((unsigned long)&rodata_f0935) /*=0xf0935*/,((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/); assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72); }
  z_spin_lock_set_owner(((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/);
  unsigned char b=*(volatile unsigned char*)(param_1+0xd);
  if((int)((unsigned)b<<0x1d) < 0){
    *(volatile unsigned char*)(param_1+0xd) = b & 0xfb;
    sched_ready_queue_insert(param_1);
    z_reschedule(((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/, 0);
    return;
  }
  r=z_spin_unlock_valid(((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/);
  if(r!=0) return;
  printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f08f4) /*=0xf08f4*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0,param_4); printk(((unsigned long)&rodata_f090b) /*=0xf090b*/,((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/); assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
}
