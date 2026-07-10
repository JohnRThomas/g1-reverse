#include "g1_app_symbols.h"
/* named: audio_hw_lock_acquire */
/* Reconstructed audio_hw_lock_acquire @ 0x7ef3e  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void audio_hw_lock_acquire(char *param_1) {
    int v = *(int*)(param_1 + 0x14);
    if (v != 0) {
        unsigned int addr = (unsigned int)(v + 4);
        unsigned int rv;
        __asm__ volatile ("ldaex %0, [%1]" : "=r"(rv) : "r"(addr));
        rv |= 1;
        unsigned int st;
        __asm__ volatile ("stlex %0, %1, [%2]" : "=&r"(st) : "r"(rv), "r"(addr) : "memory");
    }
}

