/* Reconstructed FUN_00086688 @ 0x86688  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int FUN_00086688(void *param_1)
{
    *(volatile uint32_t*)param_1 = (uint32_t)(uintptr_t)param_1;
    *(volatile uint32_t*)((char*)param_1 + 4) = (uint32_t)(uintptr_t)param_1;
    return 0;
}

