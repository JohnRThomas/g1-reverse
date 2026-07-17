/* readable reconstruction; identity: FUN_01033af8 @ 0x01033af8
 * public-name: FUN_01033af8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_esb_state                              @ 0x21004a94
 *   g_net_radio_busy_flag                    @ 0x21006458
 */
/* net-core FUN_01033af8 @ 0x1033af8  (parity 300 trials PROVEN) */

volatile unsigned char *DAT_01033b10 = (volatile unsigned char *)0x21006458;
unsigned int FUN_01033af8(unsigned char param_1) {
  unsigned char bVar1 = *DAT_01033b10;
  if (bVar1 == 0) {
    *(volatile unsigned char *)(0x21004a94 + 0xa) = param_1;
    return (unsigned int)bVar1;
  }
  return 0xfffffff0;
}
