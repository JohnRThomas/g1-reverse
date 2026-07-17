/* net-core FUN_0100a960 @ 0x100a960  (CFG-directed candidate) */

#include <stdint.h>
uint32_t FUN_0100a960(void **result)
{
    volatile uint8_t *state = (volatile uint8_t *)0x21000bf8u;
    if (*(volatile uint16_t *)(state + 0x34u) != *(volatile uint16_t *)(state + 0x38u)) return 0u;
    if (state[0x32u] == 0u) return 0u;
    *result = (void *)state;
    return 1u;
}
