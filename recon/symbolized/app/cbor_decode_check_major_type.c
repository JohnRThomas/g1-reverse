#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085da2 @ 0x00085da2
 * public-name: cbor_decode_check_major_type
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   zcbor_backup_store_count                 <= FUN_00085d70 @ 0x00085d70
 *   cbor_decode_precheck                     <= FUN_00085d82 @ 0x00085d82
 *   cbor_decode_check_major_type             <= FUN_00085da2 @ 0x00085da2
 */
/* Reconstructed FUN_00085da2 @ 0x85da2  (parity: 300/300 trials, PROVEN) */

extern int cbor_decode_precheck(void);
extern void zcbor_backup_store_count(int *a, int b, int c, unsigned char d, int e);
int cbor_decode_check_major_type(int **param_1, unsigned int param_2, int param_3, int param_4)
{
  int iVar1;
  iVar1 = cbor_decode_precheck();
  if (iVar1 != 0) {
    unsigned char *p = (unsigned char *)*param_1;
    if (param_2 == (unsigned int)(*(volatile unsigned char *)p >> 5)) {
      return iVar1;
    }
    zcbor_backup_store_count((int *)param_1, 10, param_3, *(volatile unsigned char *)p, param_4);
  }
  return 0;
}
