#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d490 @ 0x0004d490
 * public-name: z_log_dropped_read_and_clear_0
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   log_backend_count                        @ 0x2000a0d4
 */
/* z_log_dropped_read_and_clear_0 @ 0x0004d490; raw FUN_0004d490 */
#include <stdint.h>

uint32_t z_log_dropped_read_and_clear_0(void)
{
    return __atomic_exchange_n((uint32_t *)((unsigned long)&log_backend_count) /*=0x2000a0d4*/, 0,
                               __ATOMIC_SEQ_CST);
}
