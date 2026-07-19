#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00032808 @ 0x00032808
 * public-name: set_glassbox_charge_percent
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_glassbox_charge_percent              <= FUN_00032808 @ 0x00032808
 * address symbols (name @ address):
 *   g_glassbox_charge_status_byte            @ 0x20019ef4
 */
/* Reconstructed FUN_00032808 @ 0x32808  (parity: 300/300 trials, PROVEN) */

unsigned int set_glassbox_charge_percent(unsigned int param_1) {
  volatile unsigned char *p = (volatile unsigned char*)((unsigned long)&g_glassbox_charge_status_byte) /*=0x20019ef4*/;
  unsigned char v = *p;
  v = (v & 0x80) | (param_1 & 0x7f);
  *p = v;
  return param_1 & 0x7f;
}
