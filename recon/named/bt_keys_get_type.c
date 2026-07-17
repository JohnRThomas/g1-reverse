/* readable reconstruction; identity: FUN_0005e9d0 @ 0x0005e9d0
 * public-name: bt_keys_get_type
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_keys_get_addr                         <= FUN_0005e6a8 @ 0x0005e6a8
 *   bt_keys_find                             <= FUN_0005e7c8 @ 0x0005e7c8
 *   bt_keys_add_type                         <= FUN_0005e9a0 @ 0x0005e9a0
 *   bt_keys_get_type                         <= FUN_0005e9d0 @ 0x0005e9d0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f5268                             @ 0x000f5268
 *   rodata_f52ac                             @ 0x000f52ac
 */
/* Reconstructed FUN_0005e9d0 @ 0x5e9d0  (parity: 300/300 trials, PROVEN) */

extern int printk(int a,int b,int c,int d,int e);
extern void assert_post_action(int a,int b);
extern int bt_keys_find(void);
extern int bt_keys_get_addr(int a,int b);
extern void bt_keys_add_type(int a,int b);
int bt_keys_get_type(int param_1,int param_2,int param_3,int param_4)
{
  int iVar1;
  if (param_3 == 0) {
    printk(0x99cbd,0xf52ac,0xf5268,0xd2,param_4);
    assert_post_action(0xf5268,0xd2);
  }
  iVar1 = bt_keys_find();
  if (iVar1 == 0 && (iVar1 = bt_keys_get_addr(param_2,param_3), iVar1 != 0)) {
    bt_keys_add_type(iVar1,param_1);
  }
  return iVar1;
}
