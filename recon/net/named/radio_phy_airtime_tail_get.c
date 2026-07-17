/* readable reconstruction; identity: FUN_010209e0 @ 0x010209e0
 * public-name: radio_phy_airtime_tail_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   radio_phy_airtime_tail_get               <= FUN_010209e0 @ 0x010209e0
 * address symbols (name @ address):
 *   rodata_103c4d0                           @ 0x0103c4d0
 */
/* net-core FUN_010209e0 @ 0x10209e0  (parity 300 trials PROVEN) */

volatile unsigned int *const DAT_010209ec = (volatile unsigned int *)0x0103c4d0;
unsigned int radio_phy_airtime_tail_get(int param_1)
{
  return *(volatile unsigned int *)((char *)DAT_010209ec + param_1 * 4 + 0x28);
}
