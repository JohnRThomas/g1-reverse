#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085f6c @ 0x00085f6c
 * public-name: cbor_decode_uint
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decode_check_major_type             <= FUN_00085da2 @ 0x00085da2
 *   cbor_decode_extract_value                <= FUN_00085e1a @ 0x00085e1a
 *   cbor_decode_uint                         <= FUN_00085f6c @ 0x00085f6c
 */
/* Reconstructed FUN_00085f6c @ 0x85f6c  (parity: 300/300 trials, PROVEN) */

extern int cbor_decode_check_major_type(int param_1, int param_2);
extern int cbor_decode_extract_value(int*, unsigned char*, unsigned long);

void cbor_decode_uint(int param_1, int param_2, int param_3)
{
  int iVar1;
  iVar1 = cbor_decode_check_major_type(param_1, 0);
  if (iVar1 != 0) {
    cbor_decode_extract_value(param_1, param_2, param_3);
  }
}
