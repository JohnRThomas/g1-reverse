/* readable reconstruction; identity: FUN_0008392e @ 0x0008392e
 * public-name: audio_i2s_start_channels
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   audio_i2s_start_channels                 <= FUN_0008392e @ 0x0008392e
 * address symbols (name @ address):
 *   NRF_I2S0_CONFIG_CHANNELS                 @ 0x500055b8
 */
/* Reconstructed FUN_0008392e @ 0x8392e  (parity: 300/300 trials, PROVEN) */

extern void k_sem_give(int a);
extern void FUN_0007ef56(int a);

void audio_i2s_start_channels(int param_1)
{
  int base = *(int*)(param_1+0x10);
  if (*(char*)(base+0x60) == 0) {
    *(volatile unsigned int*)0x500055b8UL = 2;
  }
  k_sem_give(base+0x18);
  FUN_0007ef56(param_1);
}
