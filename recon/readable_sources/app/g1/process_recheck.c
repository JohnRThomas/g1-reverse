#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_onoff_manager__param_0129              [param_0129; library]
 * Raw function identity: 0x0007e18e.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007e18e @ 0x0007e18e
 * public-name: process_recheck
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   process_recheck                          <= FUN_0007e18e @ 0x0007e18e
 */
/* Reconstructed process_recheck @ 0x0007e18e from NCS 2.5.1 onoff.c.
 * Raw backmap: FUN_0007e18e@0x0007e18e. */

#include <stdint.h>
#define process_recheck process_recheck
int process_recheck(const void *manager_arg)
{
    const volatile uint8_t *manager = (const volatile uint8_t *)manager_arg;
    uint32_t state = *(const volatile uint16_t *)(manager + 0x1cu) & 7u;
    uint32_t has_clients = *(const volatile uint32_t *)manager != 0u;
    if (state == 0u) {
        return has_clients ? 3 : 0;
    }
    if (state == 2u) {
        return *(const volatile uint16_t *)(manager + 0x1eu) == 0u ? 4 : 0;
    }
    if (state == 1u) {
        return has_clients ? 5 : 0;
    }
    return 0;
}
