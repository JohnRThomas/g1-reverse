#include "g1_app_symbols.h"
/* named: FUN_00085c12 */
/* Reconstructed FUN_00085c12 @ 0x85c12  (parity: 300/300 trials, PROVEN) */

int FUN_00085c12(int param_1)
{
    if (param_1 != 0 && *(char *)(param_1 + 0x10) != 0) {
        return *(int *)(param_1 + 0xc) == 0;
    }
    return 1;
}

