#include "g1_app_symbols.h"
/* named: audio_codec_select_page */
/* Reconstructed audio_codec_select_page @ 0x7fb20  (parity: 300/300 trials, PROVEN) */

extern int audio_codec_bus_write_trampoline(unsigned int, unsigned int, void *, unsigned int, unsigned int);

void audio_codec_select_page(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned char local_c;
  volatile unsigned int uStack_8;
  uStack_8 = param_3;
  local_c = (unsigned char)((param_2 & 3) << 6);
  audio_codec_bus_write_trampoline(param_1, 1, &local_c, 1, param_1);
  return;
}

