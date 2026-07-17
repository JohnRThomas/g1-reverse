#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004c4d0 @ 0x0004c4d0
 * public-name: FUN_0004c4d0
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   REG_50004500                             @ 0x50004500
 */
/* Reconstructed FUN_0004c4d0 @ 0x4c4d0, exact extent 16 bytes.
 * CFG_VERIFY_PREFIX_FIRST: hardware poweroff idle loop after observable MMIO. */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

void FUN_0004c4d0(void)
{
    *(volatile uint32_t *)REG_50004500 /*=0x50004500*/ = 1u;
    __DSB();
    for (;;)
        __WFE();
}
