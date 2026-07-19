#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00054ce0 @ 0x00054ce0
 * public-name: bt_dev_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_dev_get                               <= FUN_00054ce0 @ 0x00054ce0
 * address symbols (name @ address):
 *   g_bt_dev_name                            @ 0x2000216c
 */
/* Reconstructed FUN_00054ce0 @ 0x54ce0  (parity: 300/300 trials, PROVEN) */

unsigned int bt_dev_get(void){
  return ((unsigned long)g_bt_dev_name) /*=0x2000216c*/;
}
