#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00049aa0 @ 0x00049aa0
 * public-name: md5_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   md5_init                                 <= FUN_00049aa0 @ 0x00049aa0
 */
/* Reconstructed FUN_00049aa0 @ 0x49aa0  (parity: 300/300 trials, PROVEN) */

void md5_init(unsigned int *param_1)
{
  unsigned int iVar1;
  param_1[0] = 0;
  param_1[1] = 0;
  iVar1 = 0x67452301;
  param_1[2] = iVar1;
  param_1[3] = iVar1 + 0x88888888;
  param_1[4] = iVar1 + 0x3175b9fd;
  param_1[5] = iVar1 + 0xa8ed3175;
}
