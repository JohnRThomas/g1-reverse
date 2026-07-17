/* readable reconstruction; identity: FUN_01016160 @ 0x01016160
 * public-name: FUN_01016160
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_link_ctx_a                         @ 0x21000f68
 */
/* net-core FUN_01016160 @ 0x1016160  (parity 300 trials PROVEN) */

static volatile int * const DAT_0101616c = (volatile int *)0x21000f68;
int FUN_01016160(void)
{
  int v = DAT_0101616c[2];
  if (v != 0) v = 1;
  return v;
}
