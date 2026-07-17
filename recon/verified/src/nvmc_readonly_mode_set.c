/* NCS 2.5.1 nvmc_readonly_mode_set @ 0x00065ef0 (FUN_00065ef0). */
#include <stdint.h>

void nvmc_readonly_mode_set(void)
{
    volatile uint32_t *const nvmc = (volatile uint32_t *)0x50039000u;
    nvmc[0x584u / 4u] = 0u;
    nvmc[0x504u / 4u] = 0u;
}
