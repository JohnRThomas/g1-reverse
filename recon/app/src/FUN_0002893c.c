/* Reconstructed FUN_0002893c @ 0x2893c (uncatalogued exact click-event entry). */

#include <stdint.h>

extern uint32_t FUN_00019c70(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint32_t FUN_0007dda4(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint32_t FUN_00032fd0(uint32_t);

uint32_t FUN_0002893c(uint32_t unused0, uint32_t arg1,
                      uint32_t arg2, uint32_t unused3)
{
    uint32_t logger = *(volatile uint32_t *)0x20007554UL;

    (void)unused0;
    (void)unused3;
    if (logger != 0U) {
        FUN_00019c70(0x000a0a97U, arg1, arg2, logger);
    } else {
        FUN_0007dda4(0x000a0a97U, arg1, arg2, 0U);
    }
    return FUN_00032fd0(2U);
}
