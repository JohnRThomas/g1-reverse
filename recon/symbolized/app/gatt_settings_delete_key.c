#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005306c @ 0x0005306c
 * public-name: gatt_settings_delete_key
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_delete                       <= FUN_00052fbc @ 0x00052fbc
 *   gatt_settings_delete_key                 <= FUN_0005306c @ 0x0005306c
 * address symbols (name @ address):
 *   rodata_f4aa1                             @ 0x000f4aa1
 */
/* Reconstructed FUN_0005306c @ 0x5306c  (parity: 300/300 trials, PROVEN) */

extern unsigned int bt_settings_delete(unsigned int a0, unsigned char *a1, int a2);
unsigned int gatt_settings_delete_key(unsigned char *param_1, int param_2)
{
  return bt_settings_delete(((unsigned long)&rodata_f4aa1) /*=0xf4aa1*/, param_1, param_2);
}
