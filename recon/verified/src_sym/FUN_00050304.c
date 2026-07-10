/* Reconstructed FUN_00050304 @ 0x50304  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

unsigned long long FUN_00050304(int param_1, unsigned int param_2)
{
    volatile uint32_t *g = (volatile uint32_t*)0x2000b450UL;
    uint32_t iVar5 = *g;
    if (iVar5 == (uint32_t)param_1) {
        uint32_t ipsr;
        __asm__ volatile ("mrs %0, ipsr" : "=r"(ipsr));
        if (ipsr == 0) {
            uint32_t old_basepri;
            __asm__ volatile ("mrs %0, basepri" : "=r"(old_basepri));
            __asm__ volatile ("msr basepri_max, %0" :: "r"(0x20) : "memory");
            __asm__ volatile ("isb sy" ::: "memory");
            volatile uint8_t *cbyte = (volatile uint8_t*)(uintptr_t)(iVar5 + 0xc);
            *cbyte = *cbyte & 0xfd;
            uint32_t control;
            __asm__ volatile ("mrs %0, control" : "=r"(control));
            control &= ~4u;
            __asm__ volatile ("msr control, %0" :: "r"(control) : "memory");
            __asm__ volatile ("isb sy" ::: "memory");
            __asm__ volatile ("msr basepri, %0" :: "r"(old_basepri) : "memory");
            __asm__ volatile ("isb sy" ::: "memory");
            return ((unsigned long long)old_basepri << 32) | 0u;
        }
    }
    return ((unsigned long long)param_2 << 32) | 0xffffffeaULL;
}
