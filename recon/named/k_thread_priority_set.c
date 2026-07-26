/* readable reconstruction; identity: FUN_00074554 @ 0x00074554
 * public-name: k_thread_priority_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_thread_priority_set                    <= FUN_00074184 @ 0x00074184
 *   k_thread_priority_set                    <= FUN_00074554 @ 0x00074554
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f7fee                             @ 0x000f7fee
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f85d2                             @ 0x000f85d2
 */
/* Reconstructed FUN_00074554 @ 0x74554  (parity: 300/300 trials, PROVEN) */

extern void z_thread_priority_set(int,int);
extern void assert_post_action(int,int);
extern int printk(int,...);
void k_thread_priority_set(int param_1,int param_2){
  if((unsigned)(param_2+0x10) >= 0x1f){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0xf85d2,0xf82f4,0x53d);
    printk(0xf7fee,param_2,0xe,0xfffffff0);
    assert_post_action(0xf82f4,0x53d);
  }
  z_thread_priority_set(param_1,param_2);
}
