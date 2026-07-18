/* readable reconstruction; identity: FUN_000868b4 @ 0x000868b4
 * public-name: FUN_000868b4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_heap_free                              <= FUN_00071b2c @ 0x00071b2c
 */
/* Reconstructed FUN_000868b4 @ 0x868b4  (parity: 300/300 trials, PROVEN) */

extern int k_heap_free(int, int, unsigned int, unsigned int);

void FUN_000868b4(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4) {
  (void)param_2;
  if (param_1 == 0) return;
  (void)k_heap_free(*(int *)(param_1 - 4), param_1 - 4, param_3, param_4);
}
