/* Reconstructed panel_set_brightness_level @ 0x46ce8  (CFG-directed candidate) */

#include <stdint.h>
extern void DEBUG_PRINT(uint32_t format, ...);
extern void FUN_00019c70(uint32_t format, ...);

uint32_t panel_set_brightness_level(uint8_t *context, uint32_t level)
{
    if (*(volatile uint8_t *)(context + 0x369) != level) {
        *(volatile uint8_t *)(context + 0x369) = (uint8_t)level;
        if (*(volatile int *)0x2000230cUL > 2) {
            if (*(volatile int *)0x20007554UL == 0) {
                DEBUG_PRINT(0x000d720fu, 0x000d732cu, level);
            } else {
                FUN_00019c70(0x000d720fu, 0x000d732cu, level);
            }
        }
    }
    return level;
}
