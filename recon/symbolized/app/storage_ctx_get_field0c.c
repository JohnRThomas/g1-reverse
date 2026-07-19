#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007f00e @ 0x0007f00e
 * public-name: storage_ctx_get_field0c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   storage_ctx_get_field0c                  <= FUN_0007f00e @ 0x0007f00e
 */
/* Reconstructed FUN_0007f00e @ 0x7f00e  (parity: 300/300 trials, PROVEN) */

unsigned int storage_ctx_get_field0c(char *param_1){
  return *(unsigned int *)(param_1 + 0xc);
}
