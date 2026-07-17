/* readable reconstruction; identity: FUN_0102028c @ 0x0102028c
 * public-name: FUN_0102028c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c4d0                           @ 0x0103c4d0
 */
/* net-core FUN_0102028c @ 0x102028c  (parity 300 trials PROVEN) */

volatile unsigned char *const DAT_01020298 = (volatile unsigned char *)0x0103c4d0;
int FUN_0102028c(int param_1)
{
  return (int)DAT_01020298[param_1] + 0x960;
}
