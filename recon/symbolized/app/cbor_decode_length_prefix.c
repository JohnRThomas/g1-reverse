#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085ebc @ 0x00085ebc
 * public-name: cbor_decode_length_prefix
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decode_check_major_type             <= FUN_00085da2 @ 0x00085da2
 *   cbor_decode_undo_and_fail                <= FUN_00085dc4 @ 0x00085dc4
 *   cbor_decode_extract_value                <= FUN_00085e1a @ 0x00085e1a
 *   cbor_decode_length_prefix                <= FUN_00085ebc @ 0x00085ebc
 */
/* Reconstructed FUN_00085ebc @ 0x85ebc  (parity: 300/300 trials, PROVEN) */

extern int cbor_decode_check_major_type(int *, unsigned int, unsigned int, unsigned int, unsigned int);
extern int cbor_decode_extract_value(int *, int *, unsigned int);
extern void cbor_decode_undo_and_fail(int *, int);

int cbor_decode_length_prefix(int *param_1, int *param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  int iVar2;
  iVar1 = cbor_decode_check_major_type(param_1, param_3, param_3, param_4, param_4);
  if (iVar1 != 0) {
    iVar1 = cbor_decode_extract_value(param_1, param_2 + 1, 4);
    if (iVar1 != 0) {
      iVar2 = *param_1;
      *param_2 = iVar2;
      if ((unsigned int)param_2[1] <= (unsigned int)(param_1[3] - iVar2)) {
        return iVar1;
      }
      cbor_decode_undo_and_fail(param_1, 8);
    }
  }
  return 0;
}
