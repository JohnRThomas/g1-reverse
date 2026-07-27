#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_param_0299_driver_data_collision__param_0299 [param_0299; G1-original]
 * Raw function identity: 0x0008392e.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0008392e @ 0x0008392e
 * public-name: audio_i2s_start_channels
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   audio_hw_lock_release                    <= FUN_0007ef56 @ 0x0007ef56
 *   audio_i2s_start_channels                 <= FUN_0008392e @ 0x0008392e
 * address symbols (name @ address):
 *   NRF_I2S0_CONFIG_CHANNELS                 @ 0x500055b8
 */
/* Reconstructed FUN_0008392e @ 0x8392e  (parity: 300/300 trials, PROVEN) */

extern void k_sem_give(int a);
extern void audio_hw_lock_release(unsigned char *);

void audio_i2s_start_channels(int param_1)
{
  int base = *(int*)(param_1+0x10);
  if (*(char*)(base+0x60) == 0) {
    *(volatile unsigned int*)NRF_I2S0_CONFIG_CHANNELS /*=0x500055b8*/ = 2;
  }
  k_sem_give(base+0x18);
  audio_hw_lock_release(param_1);
}
