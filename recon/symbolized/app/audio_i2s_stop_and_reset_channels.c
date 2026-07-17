#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083906 @ 0x00083906
 * public-name: audio_i2s_stop_and_reset_channels
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   audio_hw_lock_acquire                    <= FUN_0007ef3e @ 0x0007ef3e
 *   audio_i2s_stop_and_reset_channels        <= FUN_00083906 @ 0x00083906
 * address symbols (name @ address):
 *   NRF_I2S0_CONFIG_CHANNELS                 @ 0x500055b8
 */
/* Reconstructed FUN_00083906 @ 0x83906  (parity: 300/300 trials, PROVEN) */

extern unsigned long long audio_hw_lock_acquire(void);
extern void z_impl_k_sem_take(int a, int b, unsigned int c, unsigned int d);

void audio_i2s_stop_and_reset_channels(char *param_1)
{
    int iVar1;
    iVar1 = *(volatile int*)(param_1 + 0x10);
    unsigned long long inherited = audio_hw_lock_acquire();
    z_impl_k_sem_take(iVar1 + 0x18, (unsigned)(inherited >> 32), 0xffffffff, 0xffffffff);
    if (*(volatile unsigned char*)(iVar1 + 0x60) == 0) {
        *(volatile unsigned int*)NRF_I2S0_CONFIG_CHANNELS /*=0x500055b8*/ = 0;
    }
}
