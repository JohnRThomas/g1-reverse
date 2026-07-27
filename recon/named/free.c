/* readable reconstruction; identity: FUN_00076d7c @ 0x00076d7c
 * public-name: free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   free                                     <= FUN_00076d7c @ 0x00076d7c
 *   _free_r                                  <= FUN_00076d8c @ 0x00076d8c
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_00076d7c @ 0x76d7c  (parity: 300/300 trials, PROVEN) */

extern void _free_r(unsigned int a0, unsigned int a1);
void free(void*param_1) {
  _free_r(*(volatile unsigned int*)0x20002d20UL, param_1);
}
