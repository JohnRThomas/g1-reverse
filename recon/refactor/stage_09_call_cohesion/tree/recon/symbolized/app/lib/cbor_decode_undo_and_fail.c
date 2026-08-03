#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085dc4 @ 0x00085dc4
 * public-name: cbor_decode_undo_and_fail
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   zcbor_backup_store_count                 <= FUN_00085d70 @ 0x00085d70
 *   cbor_decode_undo_and_fail                <= FUN_00085dc4 @ 0x00085dc4
 */
/* Reconstructed FUN_00085dc4 @ 0x85dc4  (parity: 300/300 trials, PROVEN) */

extern void zcbor_backup_store_count(void);
void cbor_decode_undo_and_fail(unsigned int *param_1) {
  param_1[0] = param_1[1];
  param_1[2] = param_1[2] + 1;
  zcbor_backup_store_count();
}
