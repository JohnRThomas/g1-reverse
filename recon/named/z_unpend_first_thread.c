/* readable reconstruction; identity: FUN_000744a4 @ 0x000744a4
 * public-name: z_unpend_first_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   z_abort_thread_timeout                   <= FUN_00074274 @ 0x00074274
 *   z_unpend_first_thread                    <= FUN_000744a4 @ 0x000744a4
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
/* Reconstructed FUN_000744a4 @ 0x744a4  (parity: 300/300 trials, PROVEN) */

extern int z_spin_lock_valid(int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void z_abort_thread_timeout(int);
extern void z_abort_timeout(int);
extern void assert_post_action(int,int);
extern int printk(int,...);
int z_unpend_first_thread(int *param_1){
  int r=z_spin_lock_valid(0x2000b490);
  if(r==0){ printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_lock_valid(l)"),0xf08c7,0x72); printk(((unsigned long)"\tInvalid spinlock %p\n"),0x2000b490); assert_post_action(0xf08c7,0x72); }
  z_spin_lock_set_owner(0x2000b490);
  int *piVar4=(int*)*param_1;
  if(param_1==piVar4) piVar4=0;
  else if(piVar4!=0){ z_abort_thread_timeout((int)piVar4); z_abort_timeout((int)piVar4+0x18); }
  r=z_spin_unlock_valid(0x2000b490);
  if(r!=0) return (int)piVar4;
  printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_unlock_valid(l)"),0xf08c7,0xf0); printk(((unsigned long)"\tNot my spinlock %p\n"),0x2000b490); assert_post_action(0xf08c7,0xf0);
  return 0;
}
