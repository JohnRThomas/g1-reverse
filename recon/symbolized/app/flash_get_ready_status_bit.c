#include "g1_app_symbols.h"
/* named: flash_get_ready_status_bit */
/* Reconstructed flash_get_ready_status_bit @ 0x304f0  (parity: 300/300 trials, PROVEN) */

extern int attr_store_get(unsigned int, int*, unsigned int, int, unsigned int);

int flash_get_ready_status_bit(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    int local_c = 0;
    int iVar1 = attr_store_get(((uintptr_t)&rodata_ff00) /*=0xff00*/, &local_c, param_3, 0, param_1);
    if (iVar1 < 0 || (unsigned int)(0xdfddcdfdU + local_c) > 4) {
        return -1;
    } else {
        return (int)((0x15U >> ((0xdfddcdfdU + local_c) & 0xffU)) & 1) - 1;
    }
}

