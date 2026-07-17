#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007cef6 @ 0x0007cef6
 * public-name: sensor_channel_get_trampoline
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sensor_channel_get_trampoline            <= FUN_0007cef6 @ 0x0007cef6
 */
/* Reconstructed FUN_0007cef6 @ 0x7cef6  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(void);
void sensor_channel_get_trampoline(int param_1)
{
    fn_t f = *(fn_t*)(*(int*)(param_1 + 8) + 0x10);
    f();
}
