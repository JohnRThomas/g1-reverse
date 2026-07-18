/* readable reconstruction; identity: FUN_0007440c @ 0x0007440c
 * public-name: FUN_0007440c
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
 *   sched_spinlock                           @ 0x2000b490
 */
/* Reconstructed FUN_0007440c @ 0x7440c  (parity: 300/300 trials, PROVEN) */

extern int z_spin_lock_valid(int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void z_abort_thread_timeout(int);
extern void assert_post_action(int,int);
extern int printk(int,...);
int FUN_0007440c(int *param_1){
  int r=z_spin_lock_valid(0x2000b490);
  if(r==0){ printk(0x99cbd,0xf0920,0xf08c7,0x72); printk(0xf0935,0x2000b490); assert_post_action(0xf08c7,0x72); }
  z_spin_lock_set_owner(0x2000b490);
  int *piVar4=(int*)*param_1;
  if(param_1==piVar4) piVar4=0;
  else if(piVar4!=0) z_abort_thread_timeout((int)piVar4);
  r=z_spin_unlock_valid(0x2000b490);
  if(r!=0) return (int)piVar4;
  printk(0x99cbd,0xf08f4,0xf08c7,0xf0); printk(0xf090b,0x2000b490); assert_post_action(0xf08c7,0xf0);
  return 0;
}
