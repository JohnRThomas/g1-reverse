/* Reconstructed FUN_0007c48a @ 0x7c48a  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int FUN_0007c48a(uint8_t *param_1, int *param_2)
{
    uint8_t bVar1;
    if (param_1 != (uint8_t*)0 && param_2 != (int*)0) {
        if (*param_2 == 0) {
            if ((char)*((uint8_t*)param_2 + 4) != 0) {
                return 7;
            }
            bVar1 = *param_1 & 0xf7;
        } else {
            bVar1 = *param_1 | 8;
        }
        *param_1 = bVar1;
        *(int*)(param_1 + 8) = *param_2;
        param_1[2] = *((uint8_t*)param_2 + 4);
        return 0;
    }
    return 7;
}

