/* Reconstructed FUN_0004d8f8 @ 0x4d8f8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

extern void FUN_0007e2fa(unsigned long, ...);
extern uint64_t FUN_0007e2ec(int a, int b);
extern void FUN_0004d44c(void);

void FUN_0004d8f8(int param_1, unsigned int param_2, unsigned char param_3)
{
    volatile unsigned char index =
        (unsigned char)(((param_1 - 0x882a0) >> 4) + 1);
    if (param_1 == 0) {
        uint64_t assertion_result;
        FUN_0007e2fa(0x99cbd, 0xf0ddf, 0xf0da7, 0xdf);
        assertion_result = FUN_0007e2ec(0xf0da7, 0xdf);
        param_1 = (int)assertion_result;
        /* The assertion backend is expected not to return.  The original has
         * no recovery path: if it does return, the live caller-saved argument
         * registers flow into the subsequent record stores. */
        index = 0xdf;
        param_2 = (unsigned int)(assertion_result >> 32);
        param_3 = 0xa7;
    }
    *(unsigned char *)(*(int *)(param_1 + 4) + 4) = index;
    *(unsigned char *)(*(int *)(param_1 + 4) + 6) = param_3;
    **(unsigned int **)(param_1 + 4) = param_2;
    *(unsigned char *)(*(int *)(param_1 + 4) + 5) = 1;
    FUN_0004d44c();
}
