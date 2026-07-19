/* readable reconstruction; identity: FUN_0004df88 @ 0x0004df88
 * public-name: log_backend_uart_check_ready
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_backend_uart_check_ready             <= FUN_0004df88 @ 0x0004df88
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_87bc0                             @ 0x00087bc0
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f0f71                             @ 0x000f0f71
 *   rodata_f0faf                             @ 0x000f0faf
 */
/* Reconstructed FUN_0004df88 @ 0x4df88  (parity: 300/300 trials, PROVEN) */

extern int z_device_is_ready(unsigned int);
extern void printk(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void assert_post_action(unsigned int,unsigned int);
void log_backend_uart_check_ready(void)
{
  int iVar1;
  iVar1 = z_device_is_ready(0x00087bc0UL);
  if (iVar1 == 0) {
    printk(0x00099cbdUL,0x000f0fafUL,0x000f0f71UL,0x7f,0);
    assert_post_action(0x000f0f71UL,0x7f);
  }
  return;
}
