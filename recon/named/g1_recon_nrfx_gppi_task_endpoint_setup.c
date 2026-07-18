/* readable reconstruction; identity: FUN_00064f78 @ 0x00064f78
 * public-name: g1_recon_nrfx_gppi_task_endpoint_setup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6a09                             @ 0x000f6a09
 *   rodata_f6a4a                             @ 0x000f6a4a
 */
/* Reconstructed g1_recon_nrfx_gppi_task_endpoint_setup @ 0x64f78.
 * Raw identity/back-map: FUN_00064f78.  Parity: 300/300 trials, PROVEN.
 */

extern void printk(int a, int b, int c, int d, int e);
extern unsigned int assert_post_action(int a, int b);
void g1_recon_nrfx_gppi_task_endpoint_setup(
    unsigned int channel, int task_endpoint,
    unsigned int param_3, unsigned int param_4)
{
  unsigned int val = channel;
  if (task_endpoint == 0) {
    printk(0x00099cbdUL, 0x000f6a4aUL, 0x000f6a09UL, 0x4a, param_4);
    val = assert_post_action(0x000f6a09UL, 0x4a);
  }
  *(volatile unsigned int *)(task_endpoint + 0x80) = val | 0x80000000UL;
}
