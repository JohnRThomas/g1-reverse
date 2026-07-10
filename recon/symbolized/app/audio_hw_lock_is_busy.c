#include "g1_app_symbols.h"
/* named: audio_hw_lock_is_busy */
/* Reconstructed audio_hw_lock_is_busy @ 0x7ef2e  (parity: 300/300 trials, PROVEN) */

unsigned int audio_hw_lock_is_busy(unsigned char *param_1) {
  unsigned int v = *(unsigned int*)(param_1 + 0x14);
  if (v != 0) {
    v = *(volatile unsigned int*)(v + 4) & 1;
  }
  return v;
}

