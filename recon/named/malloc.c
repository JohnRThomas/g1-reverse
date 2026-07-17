/* readable reconstruction; identity: FUN_00076d6c @ 0x00076d6c
 * public-name: malloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   _malloc_r                                <= FUN_00076e20 @ 0x00076e20
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_00076d6c @ 0x76d6c  (parity: 300/300 trials, PROVEN) */

extern void _malloc_r(unsigned int *, unsigned int,
                         unsigned int, unsigned int);

void malloc(unsigned int param_1, unsigned int unused_2,
                   unsigned int param_3, unsigned int unused_4)
{
  volatile unsigned int **heap_context =
      (volatile unsigned int **)0x20002d20UL;

  _malloc_r((unsigned int *)*heap_context, param_1, param_3,
               (unsigned int)(unsigned long)heap_context);
}
