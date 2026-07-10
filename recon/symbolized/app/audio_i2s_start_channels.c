#include "g1_app_symbols.h"
/* named: audio_i2s_start_channels */
/* globals referenced:
//   0x500055b8  NRF_I2S0_CONFIG_CHANNELS     
*/
/* Reconstructed audio_i2s_start_channels @ 0x8392e  (parity: 300/300 trials, PROVEN) */

extern void FUN_00072880(int a);
extern void FUN_0007ef56(int a);

void audio_i2s_start_channels(int param_1)
{
  int base = *(int*)(param_1+0x10);
  if (*(char*)(base+0x60) == 0) {
    *(volatile unsigned int*)NRF_I2S0_CONFIG_CHANNELS /*=0x500055b8*/ = 2;
  }
  FUN_00072880(base+0x18);
  FUN_0007ef56(param_1);
}

