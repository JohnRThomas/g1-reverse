#include "g1_app_symbols.h"
/* named: audio_i2s_stop_and_reset_channels */
/* globals referenced:
//   0x500055b8  NRF_I2S0_CONFIG_CHANNELS     
*/
/* Reconstructed audio_i2s_stop_and_reset_channels @ 0x83906  (parity: 300/300 trials, PROVEN) */

extern void audio_hw_lock_acquire(void);
extern void mutex_lock_syscall_handler(int a, int b, unsigned int c, unsigned int d);

void audio_i2s_stop_and_reset_channels(char *param_1)
{
    int iVar1;
    iVar1 = *(volatile int*)(param_1 + 0x10);
    audio_hw_lock_acquire();
    mutex_lock_syscall_handler(iVar1 + 0x18, 0, 0xffffffff, 0xffffffff);
    if (*(volatile unsigned char*)(iVar1 + 0x60) == 0) {
        *(volatile unsigned int*)NRF_I2S0_CONFIG_CHANNELS /*=0x500055b8*/ = 0;
    }
}

