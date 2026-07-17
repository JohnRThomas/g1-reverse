#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00053024 @ 0x00053024
 * public-name: FUN_00053024
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_delete                       <= FUN_00052fbc @ 0x00052fbc
 * address symbols (name @ address):
 *   rodata_f4de3                             @ 0x000f4de3
 */
/* Reconstructed FUN_00053024 @ 0x53024  (parity: 300/300 trials, PROVEN) */

extern unsigned int bt_settings_delete(unsigned int a0, unsigned char *a1, int a2);
unsigned int FUN_00053024(unsigned char *param_1, int param_2)
{
  return bt_settings_delete(((unsigned long)&rodata_f4de3) /*=0xf4de3*/, param_1, param_2);
}
