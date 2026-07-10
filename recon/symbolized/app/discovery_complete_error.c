#include "g1_app_symbols.h"
/* named: discovery_complete_error */
/* Reconstructed discovery_complete_error @ 0x7f40c  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(unsigned int, unsigned int, unsigned int);
extern void svc_attr_memory_release(void);
extern void atomic_and_0(unsigned int*, unsigned int);

void discovery_complete_error(unsigned int *param_1, unsigned int param_2)
{
    svc_attr_memory_release();
    atomic_and_0(param_1 + 0x4e, 0xfffffffeU);
    fn_t f = *(fn_t*)(param_1[0x57] + 8);
    if (f != (fn_t)0) {
        f(param_1[0], param_2, param_1[1]);
        return;
    }
    return;
}

