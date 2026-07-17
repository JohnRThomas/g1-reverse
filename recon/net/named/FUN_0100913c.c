/* readable reconstruction; identity: FUN_0100913c @ 0x0100913c
 * public-name: FUN_0100913c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_layout_count_table                 @ 0x21000a30
 */
/* net-core FUN_0100913c @ 0x100913c  (parity 300 trials PROVEN) */

extern void FUN_010294ae(void);

unsigned int FUN_0100913c(void)
{
  volatile unsigned char *p = (volatile unsigned char *)0x21000a30;
  if (p[0x2d] == 0 && p[0x2c] == 0) {
    FUN_010294ae();
    return 0;
  }
  return 0xffffffff;
}
