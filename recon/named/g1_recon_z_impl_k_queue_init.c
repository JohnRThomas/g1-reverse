/* readable reconstruction; identity: FUN_000864e8 @ 0x000864e8
 * public-name: g1_recon_z_impl_k_queue_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_z_impl_k_queue_init             <= FUN_000864e8 @ 0x000864e8
 */
/* Reconstructed firmware queue initializer @ 0x000864e8.
 * Raw/address back-map: FUN_000864e8 / 0x000864e8.
 * Readable namespace target: g1_recon_z_impl_k_queue_init.
 * This 28-byte layout includes the firmware's four-byte spinlock at +8.
 */

#define g1_recon_z_impl_k_queue_init g1_recon_z_impl_k_queue_init
void g1_recon_z_impl_k_queue_init(int *param_1)
{
  *(volatile unsigned int *)(param_1) = 0;
  *(volatile unsigned int *)((int)param_1+4) = 0;
  *(volatile unsigned int *)((int)param_1+8) = 0;
  *(volatile unsigned int *)((int)param_1+0xc) = (unsigned int)param_1 + 0xc;
  *(volatile unsigned int *)((int)param_1+0x10) = (unsigned int)param_1 + 0xc;
  *(volatile unsigned int *)((int)param_1+0x14) = (unsigned int)param_1 + 0x14;
  *(volatile unsigned int *)((int)param_1+0x18) = (unsigned int)param_1 + 0x14;
}
