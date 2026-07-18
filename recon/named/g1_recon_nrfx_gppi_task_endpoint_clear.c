/* readable reconstruction; identity: FUN_00064fd4 @ 0x00064fd4
 * public-name: g1_recon_nrfx_gppi_task_endpoint_clear
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6a09                             @ 0x000f6a09
 *   rodata_f6a4a                             @ 0x000f6a4a
 */
/* Reconstructed g1_recon_nrfx_gppi_task_endpoint_clear @ 0x64fd4.
 * Raw identity/back-map: FUN_00064fd4.  Parity: 300/300 trials, PROVEN.
 */

extern unsigned long long assert_post_action(unsigned int,unsigned int);
extern void printk(unsigned int,unsigned int,unsigned int,unsigned int);
void g1_recon_nrfx_gppi_task_endpoint_clear(
    unsigned int channel, int task_endpoint,
    unsigned int param_3, unsigned int param_4)
{
  if (task_endpoint == 0) {
    printk(0x00099cbdUL,0x000f6a4aUL,0x000f6a09UL,99);
    task_endpoint = (int)(assert_post_action(0x000f6a09UL,99) >> 32);
  }
  *(unsigned int *)(task_endpoint + 0x80) = 0;
  return;
}
