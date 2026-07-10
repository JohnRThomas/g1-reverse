#include "g1_app_symbols.h"
/* named: audio_codec_read_gain_step_mode */
/* Reconstructed audio_codec_read_gain_step_mode @ 0x7fc2c  (parity: 300/300 trials, PROVEN) */

extern int audio_codec_select_page(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern int audio_codec_bus_read_trampoline(unsigned int, unsigned int, void*, unsigned int);

int audio_codec_read_gain_step_mode(unsigned int param_1, unsigned char *param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  int iVar2 = 0;
  unsigned char local_14;
  unsigned int uVar3;

  iVar1 = audio_codec_select_page(param_1, 2, param_3, param_4, param_1);
  if (iVar1 == 0) {
    iVar2 = audio_codec_bus_read_trampoline(param_1, 0x5f, &local_14, 1);
    if (iVar2 == 0) {
      uVar3 = (local_14 >> 3) & 3;
      if (uVar3==2 || uVar3==3 || uVar3==1) {
        *param_2 = (unsigned char)uVar3;
      } else {
        *param_2 = 0;
      }
    }
    iVar1 = audio_codec_select_page(param_1, 0, 0, 0, 0);
    iVar1 = iVar1 + iVar2;
  }
  return iVar1;
}

