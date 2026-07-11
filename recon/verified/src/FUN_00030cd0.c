/* Reconstructed FUN_00030cd0 @ 0x30cd0 */
#include <stdint.h>

extern int DEBUG_PRINT(uint32_t, ...);
extern uint32_t FUN_00025950(int, uint8_t *, int, int);
extern uint32_t FUN_0003364c(int, uint8_t *, int, int);

uint32_t FUN_00030cd0(int operation, int context, uint8_t *buffer, int length)
{
    if (context == 0 || buffer == 0 || length == 0 || operation == 2) {
        DEBUG_PRINT(0x000a6589);
        return UINT32_MAX;
    }

    if (operation == 0)
        return FUN_00025950(context, buffer, length, length);
    if (operation == 1)
        return FUN_0003364c(context, buffer, length, length);
    return 0;
}
