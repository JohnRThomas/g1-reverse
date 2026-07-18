/* readable reconstruction; identity: FUN_0101ded0 @ 0x0101ded0
 * public-name: FUN_0101ded0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_timeout_list                           @ 0x2100113c
 */
/* net-core FUN_0101ded0 @ 0x0101ded0
 * Select a common schedule quantum from the registered node constraints.
 */
#include <stdint.h>

extern __attribute__((noreturn)) void sdc_assertion_fail(
    uint32_t module, uint32_t line, uint32_t context,
    uint32_t node, uint32_t caller_context);

uint32_t FUN_0101ded0(uint32_t minimum, uint32_t requested,
                      uint32_t alignment, uint32_t caller_context)
{
    uint32_t node = *(volatile uint32_t *)0x2100113cu;
    uint32_t shortest = 0u;
    uint32_t node_alignment = 0u;

    while (node != 0u) {
        uint32_t interval = *(volatile uint32_t *)(uintptr_t)(node + 0x10u);
        if (shortest == 0u || interval < shortest) {
            if (interval == 0u) {
                sdc_assertion_fail(0x37u, 0x12cu, alignment, node,
                             caller_context);
            }
            shortest = interval;
            node_alignment = *(volatile uint16_t *)(uintptr_t)(node + 0x14u);
        }
        node = *(volatile uint32_t *)(uintptr_t)(node + 0x18u);
    }

    if (shortest == 0u) {
        return requested;
    }

    if (requested < shortest) {
        uint32_t divisor = (requested - 1u + shortest) / requested;
        uint32_t maximum_divisor = shortest / minimum;
        while (divisor <= maximum_divisor) {
            uint32_t quantum = shortest / divisor;
            if (shortest == divisor * quantum &&
                quantum == alignment * (quantum / alignment) &&
                quantum == node_alignment * (quantum / node_alignment)) {
                return quantum;
            }
            divisor++;
        }
        return requested;
    }

    {
        uint32_t multiplier = requested / shortest;
        uint32_t minimum_multiplier = (minimum - 1u + shortest) / shortest;
        if (minimum_multiplier <= multiplier) {
            uint32_t quantum = shortest * multiplier;
            do {
                if (quantum == shortest * (quantum / shortest) &&
                    quantum == alignment * (quantum / alignment)) {
                    return quantum;
                }
                multiplier--;
                quantum -= shortest;
            } while (minimum_multiplier <= multiplier);
        }
    }
    return requested;
}
