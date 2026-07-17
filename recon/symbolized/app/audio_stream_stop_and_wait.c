#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000838fa @ 0x000838fa
 * public-name: audio_stream_stop_and_wait
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   audio_stream_stop_and_wait               <= FUN_000838fa @ 0x000838fa
 */
/* Reconstructed FUN_000838fa @ 0x838fa  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void z_impl_k_sem_take(unsigned int,unsigned int,unsigned int,unsigned int);
void audio_stream_stop_and_wait(unsigned int param_1,unsigned int param_2)
{
  z_impl_k_sem_take(param_1,param_2,0xffffffff,0xffffffff);
  return;
}
