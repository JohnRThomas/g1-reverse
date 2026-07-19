/* readable reconstruction; identity: FUN_000850c8 @ 0x000850c8
 * public-name: cjson_is_array
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_is_array                           <= FUN_000850c8 @ 0x000850c8
 */
/* Reconstructed FUN_000850c8 @ 0x850c8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int cjson_is_array(unsigned char *param_1) {
  unsigned int result = (unsigned int)(uintptr_t)param_1;
  if (param_1 != 0) {
    result = (unsigned int)(param_1[0xc] == 0x20);
  }
  return result;
}
