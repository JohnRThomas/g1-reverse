/* readable reconstruction; identity: FUN_010339e4 @ 0x010339e4
 * public-name: FUN_010339e4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_crc_scratch                  @ 0x21000684
 *   g_net_radio_busy_flag                    @ 0x21006458
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_010339e4 @ 0x10339e4  (parity 300 trials PROVEN) */

extern unsigned long long FUN_0103a80c(unsigned int *p);

unsigned int FUN_010339e4(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r1v = *(volatile unsigned char *)0x21006458u;
  if (r1v == 0) {
    if (param_1 == 0) {
      return 0xffffffea;
    } else {
      unsigned int uVar3 = *param_1;
      *(volatile unsigned int *)0x21000684u = uVar3;
      unsigned long long rv = FUN_0103a80c((unsigned int *)0x21000684u);
      unsigned int rev = __builtin_bswap32((unsigned int)rv);
      *(volatile unsigned int *)(0x41008000u + 0x51c) = rev;
      return (unsigned int)(rv >> 32);
    }
  } else {
    return 0xfffffff0;
  }
}
