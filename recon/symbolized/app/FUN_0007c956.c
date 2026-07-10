#include "g1_app_symbols.h"
/* named: FUN_0007c956 */
/* Reconstructed FUN_0007c956 @ 0x7c956  (parity: 300/300 trials, PROVEN) */

extern unsigned int ipc_ept_op_b_locked_retry(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

unsigned int FUN_0007c956(unsigned int param_1, int param_2)
{
    if (param_2 != 0) {
        return ipc_ept_op_b_locked_retry(param_1, 0x17, param_2, 1);
    }
    return 0xffffffea;
}

