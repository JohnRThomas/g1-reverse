#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007ef2e @ 0x0007ef2e
 * public-name: audio_hw_lock_is_busy
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_hw_lock_is_busy                    <= FUN_0007ef2e @ 0x0007ef2e
 */
/* Reconstructed FUN_0007ef2e @ 0x7ef2e  (parity: 300/300 trials, PROVEN) */

int audio_hw_lock_is_busy(unsigned long param_1) {
  unsigned int v = *(unsigned int*)(param_1 + 0x14);
  if (v != 0) {
    v = *(volatile unsigned int*)(v + 4) & 1;
  }
  return v;
}
