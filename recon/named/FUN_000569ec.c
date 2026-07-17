/* readable reconstruction; identity: FUN_000569ec @ 0x000569ec
 * public-name: FUN_000569ec
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_reserve                   <= FUN_0005f4d4 @ 0x0005f4d4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   k_is_in_isr                              <= FUN_00086406 @ 0x00086406
 * address symbols (name @ address):
 *   log_module_bt_conn                       @ 0x00088108
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f3d75                             @ 0x000f3d75
 *   rodata_f3d84                             @ 0x000f3d84
 *   acl_tx_pool                              @ 0x20003a7c
 */
/* Reconstructed FUN_000569ec @ 0x569ec  (parity: 300/300 trials, PROVEN) */

extern int net_buf_simple_reserve(int,int);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
extern int FUN_000813ca(unsigned,unsigned,void*);
extern int FUN_000836de(int,unsigned,unsigned,unsigned);
extern int k_is_in_isr(void);
int FUN_000569ec(int param_1,int param_2,unsigned param_3,unsigned param_4){
  int iVar1; unsigned local_20, local_1c;
  iVar1 = k_is_in_isr();
  if(iVar1!=0){
    printk(0x99cbd,0xf3d75,0xf3a5d,0x55f);
    assert_post_action(0xf3a5d,0x55f);
  }
  if(param_1==0) param_1=0x20003a7c;
  iVar1=FUN_000836de(param_1,0x20003a7c,param_3,param_4);
  if(iVar1==0){
    local_1c=0xf3d84; local_20=2;
    FUN_000813ca(0x88108,0x1080,&local_20);
  } else {
    net_buf_simple_reserve(iVar1+0xc, param_2+5);
  }
  return iVar1;
}
