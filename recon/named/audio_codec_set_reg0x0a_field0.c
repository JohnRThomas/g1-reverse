/* named: audio_codec_set_reg0x0a_field0 */
/* Reconstructed audio_codec_set_reg0x0a_field0 @ 0x7fbd6  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int audio_codec_bus_read_trampoline(uint32_t,uint32_t,void*,uint32_t,uint32_t);
extern void audio_codec_bus_write_trampoline(uint32_t,uint32_t,void*,uint32_t);

void audio_codec_set_reg0x0a_field0(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t local[2];
  int iVar1;
  local[0] = param_2;
  local[1] = param_3;
  iVar1 = audio_codec_bus_read_trampoline(param_1,10,local,1,param_1);
  if (iVar1==0) {
    uint8_t *b = (uint8_t*)local;
    b[0] = (uint8_t)((b[0] & 0xf8) | (param_2 & 7));
    audio_codec_bus_write_trampoline(param_1,10,local,1);
  }
}

