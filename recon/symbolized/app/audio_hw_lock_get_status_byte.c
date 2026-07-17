#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007ef1c @ 0x0007ef1c
 * public-name: audio_hw_lock_get_status_byte
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_hw_lock_get_status_byte            <= FUN_0007ef1c @ 0x0007ef1c
 */
/* Reconstructed FUN_0007ef1c @ 0x7ef1c  (parity: 300/300 trials, PROVEN) */

unsigned int audio_hw_lock_get_status_byte(int param_1, unsigned char *param_2)
{
    int p = *(int*)(param_1 + 0x14);
    if (p != 0) {
        *param_2 = *(unsigned char*)(p + 8);
        return 0;
    }
    return 0xffffffa8;
}
