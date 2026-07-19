#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00050af8 @ 0x00050af8
 * public-name: nrf_cc3xx_platform_abort
 * durable-map: recon/catalogs/function_names_app.json
 */
/* nrf_cc3xx_platform_abort @ 0x00050af8; raw FUN_00050af8 */
#include <stdint.h>

void nrf_cc3xx_platform_abort(void)
{
    volatile uint32_t *aircr = (volatile uint32_t *)0xe000ed0cu;

    *aircr = 0x05fa0004u | (*aircr & 0x700u);
    for (;;) {
    }
}
