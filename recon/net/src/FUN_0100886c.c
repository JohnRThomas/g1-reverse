/* net-core FUN_0100886c @ 0x100886c */
#include <stdint.h>

/* Add two little-endian 256-bit integers modulo the NIST P-256 prime. */
void FUN_0100886c(uint32_t out[8], const uint32_t a[8], const uint32_t b[8])
{
    static const uint32_t p[8] = {
        0xffffffffU, 0xffffffffU, 0xffffffffU, 0,
        0, 0, 1, 0xffffffffU
    };
    uint32_t sum[8], reduced[8];
    uint64_t carry = 0;
    for (unsigned i = 0; i < 8; ++i) {
        uint64_t v = (uint64_t)a[i] + b[i] + carry;
        sum[i] = (uint32_t)v;
        carry = v >> 32;
    }

    uint64_t borrow = 0;
    for (unsigned i = 0; i < 8; ++i) {
        uint64_t subtrahend = (uint64_t)p[i] + borrow;
        reduced[i] = (uint32_t)((uint64_t)sum[i] - subtrahend);
        borrow = (uint64_t)sum[i] < subtrahend;
    }
    /* A ninth carry bit means the mathematical sum is certainly at least p. */
    uint32_t use_reduced = (uint32_t)(carry | (borrow ^ 1U));
    uint32_t mask = 0U - use_reduced;
    for (unsigned i = 0; i < 8; ++i)
        out[i] = (reduced[i] & mask) | (sum[i] & ~mask);
}
