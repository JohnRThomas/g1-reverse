#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085dd2 @ 0x00085dd2
 * public-name: cbor_decode_expect_break
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decode_precheck                     <= FUN_00085d82 @ 0x00085d82
 *   cbor_decode_expect_break                 <= FUN_00085dd2 @ 0x00085dd2
 */
/* Reconstructed FUN_00085dd2 @ 0x85dd2  (parity: 300/300 trials, PROVEN) */

extern int cbor_decode_precheck(void);
extern void FUN_00085d70(unsigned int *a0, int a1);

int cbor_decode_expect_break(unsigned int *param_1)
{
  int iVar1;
  iVar1 = cbor_decode_precheck();
  if (iVar1 != 0) {
    unsigned char *p = (unsigned char *)*param_1;
    if (*p == 0xff) {
      *param_1 = (unsigned int)(p + 1);
      return iVar1;
    }
    FUN_00085d70(param_1, 10);
  }
  return 0;
}
