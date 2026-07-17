/* readable reconstruction; identity: FUN_0007c030 @ 0x0007c030
 * public-name: FUN_0007c030
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_impl_k_sem_init                        <= FUN_00086534 @ 0x00086534
 */
/* Reconstructed FUN_0007c030 @ 0x7c030  (parity: 300/300 trials, PROVEN) */

extern void z_impl_k_sem_init(unsigned int, unsigned int, unsigned int);
void FUN_0007c030(unsigned int param_1, unsigned int param_2)
{
    z_impl_k_sem_init(param_1, 0, param_2);
}
