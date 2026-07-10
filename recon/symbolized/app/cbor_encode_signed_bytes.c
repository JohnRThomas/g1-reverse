#include "g1_app_symbols.h"
/* named: cbor_encode_signed_bytes */
/* Reconstructed cbor_encode_signed_bytes @ 0x8629e  (parity: 300/300 trials, PROVEN) */

extern void cbor_encode_set_error(int a, int b);
extern int cbor_encode_length_header(int a, int b, void *c);

unsigned int cbor_encode_signed_bytes(int param_1, unsigned char *param_2, unsigned int param_3)
{
    unsigned int uVar1;
    unsigned char *pbVar3;
    unsigned char *outp;

    if (param_3 < 9) {
        unsigned char buf[8];
        pbVar3 = param_2 + param_3;
        outp = param_2;
        if ((signed char)pbVar3[-1] < 0) {
            unsigned char *src = param_2;
            unsigned char *dst = buf;
            while (src != pbVar3) {
                *dst = (unsigned char)~(*src);
                dst++;
                src++;
            }
            uVar1 = 1;
            outp = buf;
        } else {
            uVar1 = 0;
        }
        if (param_3 != 0) {
            uVar1 = cbor_encode_length_header(param_1, uVar1, outp);
            return uVar1;
        }
        uVar1 = 0xe;
    } else {
        uVar1 = 5;
    }
    cbor_encode_set_error(param_1, uVar1);
    return 0;
}

