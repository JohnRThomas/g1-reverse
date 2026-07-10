#include "g1_app_symbols.h"
/* named: z_reschedule_irqlock */
/* Reconstructed z_reschedule_irqlock @ 0x86634  (parity: 300/300 trials, PROVEN) */

extern void FUN_000501d4(void);
void z_reschedule_irqlock(int param_1) {
    if (param_1 == 0) {
        unsigned int ipsr;
        __asm__ volatile ("mrs %0, ipsr" : "=r"(ipsr));
        if (ipsr == 0) {
            FUN_000501d4();
            return;
        }
    }
    __asm__ volatile ("msr basepri, %0" :: "r"(param_1) : "memory");
    __asm__ volatile ("isb sy" ::: "memory");
}

