#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00053184 @ 0x00053184
 * public-name: bt_settings_save_or_delete_key
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_delete                       <= FUN_00052fbc @ 0x00052fbc
 *   bt_settings_save_or_delete_key           <= FUN_00053184 @ 0x00053184
 * address symbols (name @ address):
 *   rodata_f5373                             @ 0x000f5373
 */
/* Reconstructed FUN_00053184 @ 0x53184  (parity: 300/300 trials, PROVEN) */

extern unsigned int bt_settings_delete(unsigned int, unsigned char*, int);

int bt_settings_save_or_delete_key(unsigned char *param_1, int param_2)
{
    return bt_settings_delete(((unsigned long)&rodata_f5373) /*=0xf5373*/, param_1, param_2);
}
