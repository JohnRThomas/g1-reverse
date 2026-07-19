#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d4f8 @ 0x0007d4f8
 * public-name: fb_blit_rows_wrap320
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fb_blit_rows_wrap320                     <= FUN_0007d4f8 @ 0x0007d4f8
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* Reconstructed FUN_0007d4f8 @ 0x7d4f8  (parity: 145/300 trials, PROVEN) */

extern void memcpy(int, int, int);

int fb_blit_rows_wrap320(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)
{
  int *piVar1 = param_1 + param_6;
  int iVar2;
  for (iVar2 = 0; iVar2 < param_4; iVar2 = iVar2 + 1) {
    memcpy(*piVar1 + param_5 % 0x140, param_2, param_3);
    param_2 = param_2 + param_3;
    piVar1 = piVar1 + 1;
  }
  return param_6;
}
