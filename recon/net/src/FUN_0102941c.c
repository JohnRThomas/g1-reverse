/* net-core FUN_0102941c @ 0x0102941c
 * Apply one normalized enable flag to both controller domains.
 */
#include <stdint.h>

extern void FUN_0101bbb4(uint32_t enabled);
extern void FUN_01013d28(uint32_t enabled);

uint32_t FUN_0102941c(const uint8_t *enabled)
{
    uint32_t normalized = enabled[0] != 0u;
    FUN_0101bbb4(normalized);
    normalized = enabled[0] != 0u;
    FUN_01013d28(normalized);
    return 0u;
}
