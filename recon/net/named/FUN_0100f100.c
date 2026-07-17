/* readable reconstruction; identity: FUN_0100f100 @ 0x0100f100
 * public-name: FUN_0100f100
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100f100 @ 0x100f100  (parity 300 trials PROVEN) */

unsigned short FUN_0100f100(char *param_1, unsigned int param_2)
{
  if ((param_2 & 0xc) == 0) {
    return *(unsigned short *)(param_1 + 0x12);
  }
  return 0xa90;
}
