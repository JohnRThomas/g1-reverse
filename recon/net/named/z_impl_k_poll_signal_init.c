/* readable reconstruction; identity: FUN_0103b512 @ 0x0103b512
 * public-name: z_impl_k_poll_signal_init
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_k_poll_signal_init                <= FUN_0103b512 @ 0x0103b512
 */
/* net-core FUN_0103b512 @ 0x103b512  (parity 300 trials PROVEN) */

void z_impl_k_poll_signal_init(int param_1)
{
  *(int *)param_1 = param_1;
  *(int *)(param_1 + 4) = param_1;
  *(unsigned int *)(param_1 + 8) = 0;
  return;
}
