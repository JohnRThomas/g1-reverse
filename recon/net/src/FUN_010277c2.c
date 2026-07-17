/* net-core FUN_010277c2 @ 0x10277c2  (CFG-directed candidate) */
#include <stdint.h>
extern uint32_t FUN_0102771a(uint16_t, uint16_t, uint16_t); /* =FUN_0102771a */
uint32_t FUN_010277c2(uint16_t first, uint16_t second)
{
    volatile uint16_t saved_first = first;
    volatile uint16_t saved_second = second;
    return (uint16_t)((FUN_0102771a(saved_first, 10u, saved_second) + 3u) & ~3u);
}
