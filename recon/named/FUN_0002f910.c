/* readable reconstruction; identity: FUN_0002f910 @ 0x0002f910
 * public-name: FUN_0002f910
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_atomic_scratch_20007bb0                @ 0x20007bb0
 */
/* Reconstructed FUN_0002f910 @ 0x2f910  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_0002f910(unsigned int param_1)
{
  volatile unsigned int *p = (volatile unsigned int *)0x20007bb0UL;
  unsigned int old = *p;
  *p = param_1;
  return old;
}
