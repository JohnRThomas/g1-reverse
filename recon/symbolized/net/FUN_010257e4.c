#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010257e4 @ 0x010257e4
 * public-name: FUN_010257e4
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010257e4 @ 0x010257e4 -- raw backmap retained. */
#include <stdint.h>

extern __attribute__((noreturn)) void FUN_010256dc(uint32_t, uint32_t, ...);
#define controller_fault FUN_010256dc

void FUN_010257e4(uint32_t callback)
{
    volatile uint8_t *const slots = (volatile uint8_t *)G1N_21001c24;
    uint32_t index = 5;

    do {
        index = (uint8_t)(index - 1u);
        if (index == 0xffu)
            controller_fault(0x69, 0x48);
    } while (slots[index * 8u + 4u] != 0);

    *(volatile uint32_t *)(slots + index * 8u) = callback;
    slots[index * 8u + 5u] = 0;
    slots[index * 8u + 6u] = 0;
    slots[index * 8u + 4u] = 1;
}
