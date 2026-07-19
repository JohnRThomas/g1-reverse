/* readable reconstruction; identity: FUN_000469a8 @ 0x000469a8
 * public-name: dashboard_reflash_index_lookup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dashboard_reflash_index_lookup           <= FUN_000469a8 @ 0x000469a8
 */
/* Reconstructed FUN_000469a8 @ 0x469a8  (parity: 300/300 trials, PROVEN) */

int dashboard_reflash_index_lookup(unsigned int param_1) {
  unsigned int idx = param_1 - 1;
  if (idx <= 0xf) {
    return (int)*(volatile signed char*)(0x000bc073UL + idx);
  }
  return -1;
}
