#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085fd2 @ 0x00085fd2
 * public-name: cbor_decode_simple_value
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   zcbor_backup_store_count                 <= FUN_00085d70 @ 0x00085d70
 *   cbor_decode_check_major_type             <= FUN_00085da2 @ 0x00085da2
 *   cbor_decode_extract_value                <= FUN_00085e1a @ 0x00085e1a
 *   cbor_decode_simple_value                 <= FUN_00085fd2 @ 0x00085fd2
 */
/* Reconstructed FUN_00085fd2 @ 0x85fd2  (parity: 300/300 trials, PROVEN) */

extern int cbor_decode_check_major_type(unsigned int *, unsigned int);
extern int cbor_decode_extract_value(unsigned int *, unsigned int, unsigned int, unsigned int);
extern void zcbor_backup_store_count(unsigned int *, unsigned int);

unsigned int cbor_decode_simple_value(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int uVar2;
  iVar1 = cbor_decode_check_major_type(param_1, 7);
  if (iVar1 != 0) {
    if ((*(unsigned char *)*param_1 & 0x1f) < 0x19) {
      uVar2 = cbor_decode_extract_value(param_1, param_2, 1, param_4);
      return uVar2;
    }
    zcbor_backup_store_count(param_1, 10);
  }
  return 0;
}
