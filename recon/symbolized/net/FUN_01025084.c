#include "g1_net_symbols.h"
/* net-core FUN_01025084 @ 0x1025084 */
#include <stdint.h>

uint64_t FUN_01025084(void)
{
    volatile uint32_t *const timer = (volatile uint32_t *)UINT32_C(0x41011000);
    volatile uint32_t *const epochs = (volatile uint32_t *)UINT32_C(0x21001c08);
    uint32_t counter = timer[0x504 / 4];

    while (timer[0x104 / 4] != 0) {
        *epochs = *epochs + 1;
        timer[0x104 / 4] = 0;
        counter = timer[0x504 / 4];
    }

    return (uint64_t)*epochs * UINT32_C(0x01000000) + counter;
}
