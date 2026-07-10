#include "g1_app_symbols.h"
/* named: audio_buf_release */
/* Reconstructed audio_buf_release @ 0x80b0e  (parity: 300/300 trials, PROVEN) */

typedef void (*fp_t)(int);
extern void net_buf_unref(int);
void audio_buf_release(int param_1,int param_2)
{
  if (param_1 != 0) {
    fp_t f = *(volatile fp_t *)(param_2 + 0x38);
    if (f != (fp_t)0) {
      f(param_1 + 0x18);
    }
    net_buf_unref(param_1);
  }
}

