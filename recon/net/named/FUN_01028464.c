/* readable reconstruction; identity: FUN_01028464 @ 0x01028464
 * public-name: FUN_01028464
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 */
/* net-core FUN_01028464 @ 0x1028464  (parity 300 trials PROVEN) */

extern unsigned int sdc_assertion_fail(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

int FUN_01028464(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  switch (param_1) {
  case 1:
  case 2:
    return param_1;
  case 4:
  case 8:
    return 3;
  default:
    (void)sdc_assertion_fail(6, 0x294, param_3,
                       (unsigned int)(param_1 - 1), param_4);
    return 3;
  }
}
