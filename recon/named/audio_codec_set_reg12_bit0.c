/* readable reconstruction; identity: FUN_0007fb4c @ 0x0007fb4c
 * public-name: audio_codec_set_reg12_bit0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_set_reg12_bit0               <= FUN_0007fb4c @ 0x0007fb4c
 */
/* Reconstructed FUN_0007fb4c @ 0x7fb4c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0007f97c(uint32_t,uint32_t,void*,uint32_t,uint32_t);
extern void FUN_0007f98a(uint32_t,uint32_t,void*,uint32_t);

void audio_codec_set_reg12_bit0(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t local[2];
  int iVar1;
  local[0] = param_2;
  local[1] = param_3;
  iVar1 = FUN_0007f97c(param_1,0x12,local,1,param_1);
  if (iVar1==0) {
    uint8_t *b = (uint8_t*)local;
    b[0] = (uint8_t)((b[0] & 0xfe) | (param_2 & 1));
    FUN_0007f98a(param_1,0x12,local,1);
  }
}
