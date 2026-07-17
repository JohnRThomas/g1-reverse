/* readable reconstruction; identity: FUN_0101f924 @ 0x0101f924
 * public-name: FUN_0101f924
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_tx_power_level               @ 0x2100144a
 */
/* net-core FUN_0101f924 @ 0x101f924  (parity 300 trials PROVEN) */

volatile unsigned char *const DAT_0101f930 = (volatile unsigned char *)0x2100144a;
unsigned char FUN_0101f924(void)
{
  return *DAT_0101f930 & 7;
}
