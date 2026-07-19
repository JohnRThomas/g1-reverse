#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085d36 @ 0x00085d36
 * public-name: cbor_decode_is_break
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decode_is_break                     <= FUN_00085d36 @ 0x00085d36
 */
/* Reconstructed FUN_00085d36 @ 0x85d36  (parity: 300/300 trials, PROVEN) */

int cbor_decode_is_break(unsigned int *param_1)
{
  if (*((unsigned char*)param_1 + 0x10) == 0) {
    return param_1[2] == 0;
  }
  if (param_1[0] < param_1[3]) {
    return *(unsigned char*)(param_1[0]) == 0xff;
  }
  return 0;
}
