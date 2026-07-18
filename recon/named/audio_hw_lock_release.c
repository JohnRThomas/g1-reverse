/* readable reconstruction; identity: FUN_0007ef56 @ 0x0007ef56
 * public-name: audio_hw_lock_release
 * durable-map: recon/catalogs/function_names_app.json
 */
/* audio_hw_lock_release @ 0x0007ef56; raw FUN_0007ef56 */
#include <stdint.h>

void audio_hw_lock_release(uint8_t *device)
{
    uint8_t *state = *(uint8_t **)(device + 0x14);

    if (state != 0) {
        __atomic_fetch_and((uint32_t *)(state + 4), ~1u, __ATOMIC_SEQ_CST);
    }
}
