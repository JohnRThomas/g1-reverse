#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010207cc @ 0x010207cc
 * public-name: FUN_010207cc
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 */
/* net-core FUN_010207cc @ 0x010207cc
 * Program the controller/radio deadline state.
 */
#include <stdint.h>

extern __attribute__((noreturn)) void sdc_assertion_fail(uint32_t, uint32_t);

void FUN_010207cc(uint32_t deadline)
{
    volatile uint8_t *control = (volatile uint8_t *)0x210015f0u;
    volatile uint8_t *radio = (volatile uint8_t *)0x4100c000u;
    uint32_t previous;

    if (*(volatile uint32_t *)(control + 0x24u) >= deadline) {
        sdc_assertion_fail(0x3eu, 0x8d1u);
    }

    *(volatile uint32_t *)(control + 0x10u) = deadline;
    *(volatile uint32_t *)(radio + 0x44u) = 1u;
    previous = *(volatile uint32_t *)(radio + 0x544u);
    *(volatile uint8_t *)(control + 0x0cu) = 1u;

    if (deadline <= previous + 5u) {
        if (*(volatile uint32_t *)(radio - 0x3efcu) == 0u) {
            *(volatile uint32_t *)(radio - 0x3ff0u) = 1u;
        }
        return;
    }

    *(volatile uint32_t *)(radio + 0x144u) = 0u;
    *(volatile uint32_t *)(radio + 0x544u) = deadline;
    *(volatile uint32_t *)(radio + 0x1c4u) = 0x8000000bu;
}
