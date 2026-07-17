/* readable reconstruction; identity: FUN_00076d7c @ 0x00076d7c
 * public-name: heap_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   heap_free                                <= FUN_00076d7c @ 0x00076d7c
 *   heap_free_core                           <= FUN_00076d8c @ 0x00076d8c
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_00076d7c @ 0x76d7c  (parity: 300/300 trials, PROVEN) */

extern void heap_free_core(unsigned int a0, unsigned int a1);
void heap_free(unsigned int param_1)
{
  heap_free_core(*(volatile unsigned int*)0x20002d20UL, param_1);
}
