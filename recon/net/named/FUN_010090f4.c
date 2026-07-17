/* readable reconstruction; identity: FUN_010090f4 @ 0x010090f4
 * public-name: FUN_010090f4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_layout_count_table                 @ 0x21000a30
 */
/* net-core FUN_010090f4 @ 0x10090f4  (parity 300 trials PROVEN) */

extern void FUN_0101f69c(void);

unsigned int FUN_010090f4(void)
{
  volatile unsigned char *p = (volatile unsigned char *)0x21000a30;
  if (p[0x2d] == 0 && p[0x2c] == 0) {
    FUN_0101f69c();
    return 0;
  }
  return 0xffffffff;
}
