/* net-core FUN_01031248 @ 0x1031248 */
#include <stdint.h>

uint32_t FUN_01031248(uint32_t channel)
{
    uint32_t shift = channel & 255u;
    uint32_t bit = shift < 32u ? 1u << shift : 0u;
    volatile uint32_t *enabled = (volatile uint32_t *)0x2100496cu;
    uint32_t previous = *enabled;
    *enabled = previous & ~bit;
    *(volatile uint32_t *)0x41016308u = shift < 16u ? 0x10000u << shift : 0u;
    return (previous & bit) != 0;
}
