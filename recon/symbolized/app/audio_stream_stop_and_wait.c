#include "g1_app_symbols.h"
/* named: audio_stream_stop_and_wait */
/* Reconstructed audio_stream_stop_and_wait @ 0x838fa  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void mutex_lock_syscall_handler(unsigned int,unsigned int,unsigned int,unsigned int);
void audio_stream_stop_and_wait(unsigned int param_1,unsigned int param_2)
{
  mutex_lock_syscall_handler(param_1,param_2,0xffffffff,0xffffffff);
  return;
}

