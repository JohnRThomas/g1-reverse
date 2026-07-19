#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00053168 @ 0x00053168
 * public-name: bt_keys_settings_store
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_store                        <= FUN_00052f18 @ 0x00052f18
 *   bt_keys_settings_store                   <= FUN_00053168 @ 0x00053168
 * address symbols (name @ address):
 *   rodata_f5373                             @ 0x000f5373
 */
/* Reconstructed FUN_00053168 @ 0x53168  (parity: 300/300 trials, PROVEN) */

extern void bt_settings_store(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void bt_keys_settings_store(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    bt_settings_store(((unsigned long)&rodata_f5373) /*=0xf5373*/, param_1, param_2, param_3, param_4, param_2, param_3);
}
