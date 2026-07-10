#include "g1_app_symbols.h"
/* named: gatt_ccc_changed */
/* Reconstructed gatt_ccc_changed @ 0x825c0  (parity: 300/300 trials, PROVEN) */

typedef void (*fnptr_t)(void);

void gatt_ccc_changed(unsigned int param_1, int param_2)
{
    unsigned short a = *(unsigned short *)(param_2 + 8);
    if (*(unsigned short *)(param_2 + 10) != a) {
        *(unsigned short *)(param_2 + 10) = a;
        fnptr_t fn = *(fnptr_t *)(param_2 + 0xc);
        if (fn != 0) {
            fn();
        }
    }
}

