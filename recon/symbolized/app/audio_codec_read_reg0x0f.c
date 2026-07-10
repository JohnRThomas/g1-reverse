#include "g1_app_symbols.h"
/* named: audio_codec_read_reg0x0f */
/* Reconstructed audio_codec_read_reg0x0f @ 0x7fb3e  (parity: 300/300 trials, PROVEN) */

extern void audio_codec_bus_read_trampoline(int a, int b, int c, int d, int e);
void audio_codec_read_reg0x0f(int param_1, int param_2, int param_3, int param_4)
{
  audio_codec_bus_read_trampoline(param_1, 0xf, param_2, 1, param_4);
  return;
}

