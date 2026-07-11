/* Reconstructed FUN_00030cd0 @ 0x30cd0 */
#include <stdint.h>

extern int DEBUG_PRINT(int, ...);
extern uint32_t FUN_00025950(int, int, uint8_t *, int);
extern uint32_t FUN_0003364c(int, int, uint8_t *, int);

uint32_t FUN_00030cd0(int param_1, int param_2, uint8_t *param_3, int param_4)
{
    if (param_2 == 0 || param_3 == 0 || param_4 == 0 || param_1 == 2) {
        DEBUG_PRINT(0x000a6589);
        return UINT32_MAX;
    }
    if (param_1 == 0)
        return FUN_00025950(param_1, param_2, param_3, param_4);
    if (param_1 == 1)
        return FUN_0003364c(param_1, param_2, param_3, param_4);
    return 0;
}
