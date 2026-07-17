/* readable reconstruction; identity: FUN_01025d28 @ 0x01025d28
 * public-name: FUN_01025d28
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_task_state_struct                  @ 0x21001c88
 */
/* net-core FUN_01025d28 @ 0x1025d28  (parity 300 trials PROVEN) */

static volatile unsigned char * const DAT_01025d34 = (volatile unsigned char *)0x21001c88;
signed char FUN_01025d28(void)
{
  unsigned int v = DAT_01025d34[1];
  if (v != 0) v = 1;
  return (signed char)v;
}
