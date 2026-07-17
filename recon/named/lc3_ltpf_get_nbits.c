/* readable reconstruction; identity: FUN_0006b36c @ 0x0006b36c
 * public-name: lc3_ltpf_get_nbits
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_ltpf_get_nbits                       <= FUN_0006b36c @ 0x0006b36c
 */
/* Reconstructed FUN_0006b36c @ 0x6b36c  (parity: 300/300 trials, PROVEN) */

int lc3_ltpf_get_nbits(int param_1)
{
  return param_1 * 10 + 1;
}
