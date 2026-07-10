/* Reconstructed FUN_0004e3c0 @ 0x4e3c0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef struct { void *a; void *b; } S;

void FUN_0004e3c0(unsigned int *param_1)
{
    *param_1 = 0;
    volatile S *r3 = (volatile S *)0x2000a104UL;
    void *r2 = r3->b;
    if (r2 != 0) {
        *(unsigned int *)r2 = (unsigned int)(uintptr_t)param_1;
        r3->b = param_1;
        return;
    }
    r3->a = param_1;
    r3->b = param_1;
}

