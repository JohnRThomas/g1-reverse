#include "g1_app_symbols.h"
/* named: pthread_attr_getstack */
/* Reconstructed pthread_attr_getstack @ 0x7c65c  (parity: 300/300 trials, PROVEN) */

unsigned int pthread_attr_getstack(int param_1, unsigned int *param_2)
{
    if (param_1 != 0 && param_2 != 0) {
        *param_2 = *(unsigned int *)(param_1 + 0xc);
        param_2[1] = *(unsigned int *)(param_1 + 0x10);
        return 0;
    }
    return 7;
}

