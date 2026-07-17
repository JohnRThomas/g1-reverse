#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101920c @ 0x0101920c
 * public-name: FUN_0101920c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_2100104c                               @ 0x2100104c
 */
/* Reconstructed net-core state teardown @ 0x0101920c. */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t module, uint32_t line);
extern void FUN_010196e0(void);

void FUN_0101920c(uint32_t event, uint32_t notify)
{
    volatile uint8_t *state = (volatile uint8_t *)0x21000f90;

    if (state[0x70] != 3) {
        for (;;)
            sdc_assertion_fail(0x32, 0xc44);
    }
    if (event - 2 > 1) {
        /* These assertions are noreturn in production.  Preserve their
         * physical fall-through order for the differential call oracle. */
        sdc_assertion_fail(0x32, 0xc52);
        for (;;)
            sdc_assertion_fail(0x32, 0xc44);
    }
    if (notify != 0)
        FUN_010196e0();

    *(volatile uint16_t *)(state + 0xba) = 0;
    state[0x70] = 0;
    *(volatile uint8_t *)((unsigned long)&g_2100104c) /*=0x2100104c*/ = 0;
}
