#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00053034 @ 0x00053034
 * public-name: FUN_00053034
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_store                        <= FUN_00052f18 @ 0x00052f18
 * address symbols (name @ address):
 *   rodata_f4ddd                             @ 0x000f4ddd
 */
/* Reconstructed FUN_00053034 @ 0x53034  (parity: 300/300 trials, PROVEN) */

extern void bt_settings_store(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g);

void FUN_00053034(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    bt_settings_store(((unsigned long)&rodata_f4ddd) /*=0xf4ddd*/, param_1, param_2, param_3, param_4, param_2, param_3);
}
