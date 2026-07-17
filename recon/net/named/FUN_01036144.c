/* readable reconstruction; identity: FUN_01036144 @ 0x01036144
 * public-name: FUN_01036144
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01036144 @ 0x1036144  (parity 300 trials PROVEN) */

static volatile unsigned char * const DAT_01036150 = (volatile unsigned char *)0x21004b28;
void FUN_01036144(unsigned int *param_1)
{
  unsigned int a = *(volatile unsigned int *)(DAT_01036150 + 8);
  unsigned int b = DAT_01036150[0x10];
  *param_1 = a | b;
}
