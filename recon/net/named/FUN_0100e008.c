/* readable reconstruction; identity: FUN_0100e008 @ 0x0100e008
 * public-name: FUN_0100e008
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100e008 @ 0x100e008  (parity 300 trials PROVEN) */

void FUN_0100e008(char *param_1, unsigned int *param_2)
{
  *(unsigned int *)(param_1 + 3) = param_2[0];
  *(unsigned short *)(param_1 + 7) = *(unsigned short *)((char*)param_2 + 4);
}
