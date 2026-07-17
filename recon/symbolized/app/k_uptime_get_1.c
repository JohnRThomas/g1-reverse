#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007cb2c @ 0x0007cb2c
 * public-name: k_uptime_get_1
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed k_uptime_get_1 @ 0x7cb2c  (CFG-directed candidate) */
#include <stdint.h>
extern uint64_t uptime_ticks_get(void);
uint64_t k_uptime_get_1(void) {
    return (uptime_ticks_get() * UINT64_C(1000)) >> 15;
}
