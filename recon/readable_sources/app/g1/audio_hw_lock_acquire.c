#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007ef3e @ 0x0007ef3e
 * public-name: audio_hw_lock_acquire
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_hw_lock_acquire                    <= FUN_0007ef3e @ 0x0007ef3e
 */
/* Reconstructed FUN_0007ef3e @ 0x7ef3e */
#include <stdint.h>

void audio_hw_lock_acquire(void *object)
{
    uint8_t *base = object;
    uintptr_t member = *(uintptr_t *)(base + 0x14);
    if (member) {
        volatile uint32_t *flags = (volatile uint32_t *)(member + 4);
        (void)__atomic_fetch_or((uint32_t *)flags, 1u, __ATOMIC_ACQ_REL);
    }
}
