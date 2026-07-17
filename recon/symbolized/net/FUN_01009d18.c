#include "g1_net_symbols.h"
/* net-core FUN_01009d18 @ 0x1009d18 */
#include <stdint.h>

extern int8_t FUN_01027470(uint32_t object, uint16_t value);
extern uint32_t FUN_010274ea(uint32_t object, uint8_t selector);

uint32_t FUN_01009d18(uint32_t param_1, uint32_t param_2)
{
    volatile uint32_t *const objects = (volatile uint32_t *)0x21000b7cu;
    uint16_t value = (uint16_t)param_1;
    uint8_t index = (uint8_t)param_2;
    uint32_t object = objects[index];
    uint8_t selector = (uint8_t)FUN_01027470(object, value);

    if (selector == UINT8_MAX) {
        return 0;
    }
    return FUN_010274ea(object, selector);
}
