/* readable reconstruction; identity: FUN_01020270 @ 0x01020270
 * public-name: FUN_01020270
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 */
/* net-core FUN_01020270 @ 0x1020270  (parity 300 trials PROVEN) */

extern void sdc_assertion_fail(unsigned int, unsigned int, unsigned int, unsigned int) __attribute__((noreturn));
void FUN_01020270(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4){
  if (param_1 < 0x97) {
    *(volatile short *)(0x210015f0 + 0x1c) = (short)param_1;
    return;
  }
  sdc_assertion_fail(0x3e, 0x1f5, param_3, param_4);
  __builtin_unreachable();
}
