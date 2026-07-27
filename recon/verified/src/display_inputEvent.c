/* Reconstructed display_inputEvent @ 0x49938 */

#include <stdint.h>

extern void FUN_00086c78(void *destination, int value, uint32_t length);
extern int FUN_000720d0(uint32_t queue, const void *record,
                       uint32_t wait, uint32_t flags);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

uint32_t display_inputEvent(uint8_t input, uint8_t state)
{
    uint8_t command[24];

    FUN_00086c78(command + 1, 0, 23);
    command[0] = 5;
    *(uint16_t *)(command + 2) = 2;
    command[4] = input;
    command[5] = state;

    if (FUN_000720d0(0x200038c4UL, command, 0, 0) != 0) {
        DEBUG_PRINT(0x000ef058UL, 0x000f0151UL);
        return UINT32_MAX;
    }

    if (*(volatile int32_t *)0x2000230cUL > 2) {
        if (*(volatile uint32_t *)0x20007554UL == 0) {
            DEBUG_PRINT(0x000f00bbUL, 0x000f0151UL);
        } else {
            FUN_00019c70(0x000f00bbUL, 0x000f0151UL);
        }
    }
    return 0;
}
