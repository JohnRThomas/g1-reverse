#include "g1_app_symbols.h"
/* named: FUN_00082fa6 */
/* Reconstructed FUN_00082fa6 @ 0x82fa6  (parity: 300/300 trials, PROVEN) */

extern void gatt_store_ccc_cf(unsigned char, int);

void FUN_00082fa6(int param_1)
{
    gatt_store_ccc_cf(*(unsigned char*)(param_1 - 0x28), param_1 - 0x27);
    gatt_store_ccc_cf(*(unsigned char*)(param_1 - 0x1c), param_1 - 0x1b);
    gatt_store_ccc_cf(*(unsigned char*)(param_1 - 0x10), param_1 - 0xf);
    return;
}

