/* Reconstructed FUN_00026828 @ 0x26828 */
#include <stdint.h>

extern void FUN_0007cab4(void);

float FUN_00026828(uint8_t *state)
{
    if (state[0x28] == 0)
        FUN_0007cab4();
    return 180.0f + *(volatile float *)(state + 0x34) * 57.295f;
}
