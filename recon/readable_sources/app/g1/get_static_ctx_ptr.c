#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00078590 @ 0x00078590
 * public-name: get_static_ctx_ptr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_static_ctx_ptr                       <= FUN_00078590 @ 0x00078590
 * address symbols (name @ address):
 *   g_misc_static_ctx_ptr                    @ 0x20002e74
 */
/* Reconstructed FUN_00078590 @ 0x78590  (parity: 300/300 trials, PROVEN) */

unsigned int get_static_ctx_ptr(void){
  return ((unsigned long)&g_misc_static_ctx_ptr) /*=0x20002e74*/;
}
