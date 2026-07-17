/* readable reconstruction; identity: FUN_00032808 @ 0x00032808
 * public-name: FUN_00032808
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_glassbox_charge_status_byte            @ 0x20019ef4
 */
/* Reconstructed FUN_00032808 @ 0x32808  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00032808(unsigned int param_1) {
  volatile unsigned char *p = (volatile unsigned char*)0x20019ef4UL;
  unsigned char v = *p;
  v = (v & 0x80) | (param_1 & 0x7f);
  *p = v;
  return param_1 & 0x7f;
}
