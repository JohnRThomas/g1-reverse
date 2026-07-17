#include "g1_net_symbols.h"
/* net-core FUN_010083dc @ 0x10083dc  (parity 200 trials PROVEN) */
/* net-core FUN_010083dc @ 0x10083dc  (parity 500 trials PROVEN) */
#include <stdint.h>

uint64_t FUN_010083dc(uint32_t param_1, uint32_t *param_2, uint32_t *param_3)
{
    (void)param_1;
    uint32_t a[8], b[8];
    for (int i = 0; i < 8; i++) { a[i] = param_2[i]; b[i] = param_3[i]; }
    uint32_t r[16];
    for (int i = 0; i < 16; i++) r[i] = 0;
    for (int i = 0; i < 8; i++) {
        uint64_t carry = 0;
        for (int j = 0; j < 8; j++) {
            uint64_t t = (uint64_t)a[i] * (uint64_t)b[j] + (uint64_t)r[i + j] + carry;
            r[i + j] = (uint32_t)t;
            carry = t >> 32;
        }
        int k = i + 8;
        while (carry) {
            uint64_t t = (uint64_t)r[k] + carry;
            r[k] = (uint32_t)t;
            carry = t >> 32;
            k++;
        }
    }
    return ((uint64_t)r[9] << 32) | (uint64_t)r[8];
}
