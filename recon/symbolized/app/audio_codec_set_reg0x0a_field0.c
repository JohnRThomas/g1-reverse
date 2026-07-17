#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007fbd6 @ 0x0007fbd6
 * public-name: audio_codec_set_reg0x0a_field0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_set_reg0x0a_field0           <= FUN_0007fbd6 @ 0x0007fbd6
 */
/* Reconstructed FUN_0007fbd6 @ 0x7fbd6  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0007f97c(uint32_t,uint32_t,void*,uint32_t,uint32_t);
extern void FUN_0007f98a(uint32_t,uint32_t,void*,uint32_t);

void audio_codec_set_reg0x0a_field0(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t local[2];
  int iVar1;
  local[0] = param_2;
  local[1] = param_3;
  iVar1 = FUN_0007f97c(param_1,10,local,1,param_1);
  if (iVar1==0) {
    uint8_t *b = (uint8_t*)local;
    b[0] = (uint8_t)((b[0] & 0xf8) | (param_2 & 7));
    FUN_0007f98a(param_1,10,local,1);
  }
}
