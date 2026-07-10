#include "g1_app_symbols.h"
/* named: dcmp_negate_rhs */
/* Reconstructed dcmp_negate_rhs @ 0xd588  (parity: 300/300 trials, PROVEN) */

extern unsigned long long __aeabi_dadd(unsigned int, unsigned int, unsigned int, unsigned int);
unsigned long long dcmp_negate_rhs(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    param_4 = param_4 ^ 0x80000000;
    return __aeabi_dadd(param_1, param_2, param_3, param_4);
}

