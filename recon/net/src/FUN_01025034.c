/* net-core FUN_01025034 @ 0x1025034 */
#include <stdint.h>

extern uint32_t FUN_01024440(uint32_t counter);

uint64_t FUN_01025034(void)
{
    volatile uint32_t *const timer = (volatile uint32_t *)UINT32_C(0x41011000);
    volatile uint32_t *const epochs = (volatile uint32_t *)UINT32_C(0x21001c08);
    uint32_t counter = timer[0x504 / 4];

    while (timer[0x104 / 4] != 0) {
        *epochs = *epochs + 1;
        timer[0x104 / 4] = 0;
        counter = timer[0x504 / 4];
    }

    uint32_t epoch = *epochs;
    counter = FUN_01024440(counter);
    return (uint64_t)epoch * UINT32_C(0x1e848000) + counter;
}
