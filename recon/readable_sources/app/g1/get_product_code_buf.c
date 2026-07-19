#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000232b8 @ 0x000232b8
 * public-name: get_product_code_buf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_product_code_buf                     <= FUN_000232b8 @ 0x000232b8
 * address symbols (name @ address):
 *   g_product_code_buf                       @ 0x20002fe3
 */
/* Reconstructed FUN_000232b8 @ 0x232b8  (parity: 300/300 trials, PROVEN) */

unsigned int get_product_code_buf(void){
  return ((unsigned long)&g_product_code_buf) /*=0x20002fe3*/;
}
