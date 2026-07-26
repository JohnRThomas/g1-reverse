/* Reconstructed FUN_00050304 @ 0x50304  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>

unsigned long long FUN_00050304(int param_1, unsigned int param_2)
{
    volatile uint32_t *g = (volatile uint32_t*)0x2000b450UL;
    uint32_t iVar5 = *g;
    if (iVar5 == (uint32_t)param_1) {
        uint32_t ipsr = __get_IPSR();
        if (ipsr == 0) {
            uint32_t old_basepri = __get_BASEPRI();
            __set_BASEPRI_MAX(0x20);
            __ISB();
            volatile uint8_t *cbyte = (volatile uint8_t*)(uintptr_t)(iVar5 + 0xc);
            *cbyte = *cbyte & 0xfd;
            uint32_t control = __get_CONTROL();
            control &= ~4u;
            __set_CONTROL(control);
            __set_BASEPRI(old_basepri);
            __ISB();
            return ((unsigned long long)old_basepri << 32) | 0u;
        }
    }
    return ((unsigned long long)param_2 << 32) | 0xffffffeaULL;
}
