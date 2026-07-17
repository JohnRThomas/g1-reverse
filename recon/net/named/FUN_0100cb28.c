/* readable reconstruction; identity: FUN_0100cb28 @ 0x0100cb28
 * public-name: FUN_0100cb28
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core FUN_0100cb28 @ 0x100cb28  (parity 300 trials PROVEN) */

extern void FUN_0101fc40(unsigned int a, unsigned int b, unsigned int c);
extern void FUN_0101fcf4(void);

void FUN_0100cb28(unsigned int param_1, int param_2)
{
  FUN_0101fc40(0x21000d18 + param_2 * 0x10 + 0x82, 1, param_1);
  FUN_0101fcf4();
}
