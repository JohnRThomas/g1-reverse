#include "g1_app_symbols.h"
/* named: cbor_decode_tag */
/* Reconstructed cbor_decode_tag @ 0x8603c  (parity: 300/300 trials, PROVEN) */

extern int cbor_decode_check_major_type(void *a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern int cbor_decode_extract_value(void *a, unsigned int b, unsigned int c);

int cbor_decode_tag(char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    iVar1 = cbor_decode_check_major_type(param_1, 6, param_3, param_4, param_4);
    if ((iVar1 == 0) || ((iVar1 = cbor_decode_extract_value(param_1, param_2, 4)), iVar1 == 0)) {
        iVar1 = 0;
    } else {
        *(volatile int*)(param_1 + 8) = *(volatile int*)(param_1 + 8) + 1;
    }
    return iVar1;
}

