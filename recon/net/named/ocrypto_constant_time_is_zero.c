/* readable reconstruction; identity: FUN_01008838 @ 0x01008838
 * public-name: ocrypto_constant_time_is_zero
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   ocrypto_constant_time_is_zero            <= FUN_01008838 @ 0x01008838
 */
/* net-core FUN_01008838 @ 0x1008838  (parity 300 trials PROVEN) */

unsigned int ocrypto_constant_time_is_zero(unsigned char *param_1, int param_2) {
  unsigned int uVar1 = 0;
  do {
    param_2 = param_2 - 1;
    uVar1 |= *param_1;
    param_1++;
  } while (param_2 != 0);
  return (uVar1 - 1) >> 0x1f;
}
