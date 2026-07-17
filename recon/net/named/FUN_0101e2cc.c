/* readable reconstruction; identity: FUN_0101e2cc @ 0x0101e2cc
 * public-name: FUN_0101e2cc
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 */
/* net-core FUN_0101e2cc @ 0x101e2cc  (parity 300 trials PROVEN) */

extern void sdc_assertion_fail(unsigned int, unsigned int) __attribute__((noreturn));

unsigned int FUN_0101e2cc(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  switch (param_1) {
  case 1:
    return 0;
  case 2:
    return 1;
  case 4:
    return 3;
  case 8:
    return 2;
  }
  sdc_assertion_fail(0x78, 0x2a8);
  __builtin_unreachable();
}
