/* net-core FUN_010089f8 @ 0x010089f8 */
#include <stdint.h>

static inline
void multiply_u256(uint32_t product[16], const uint32_t left[8],
                   const uint32_t right[8])
{
    for (unsigned i = 0; i < 16; ++i)
        product[i] = 0;

    for (unsigned i = 0; i < 8; ++i) {
        uint64_t carry = 0;
        for (unsigned j = 0; j < 8; ++j) {
            uint64_t sum = (uint64_t)left[i] * right[j] +
                           product[i + j] + carry;
            product[i + j] = (uint32_t)sum;
            carry = sum >> 32;
        }
        for (unsigned k = i + 8; carry != 0 && k < 16; ++k) {
            uint64_t sum = (uint64_t)product[k] + carry;
            product[k] = (uint32_t)sum;
            carry = sum >> 32;
        }
    }
}

static inline
int at_least_p256(const uint32_t value[9])
{
    static const uint32_t prime[8] = {
        0xffffffff, 0xffffffff, 0xffffffff, 0x00000000,
        0x00000000, 0x00000000, 0x00000001, 0xffffffff
    };

    uint32_t greater = 0;
    uint32_t equal = 1;

    for (int i = 7; i >= 0; --i) {
        greater |= equal & (value[i] > prime[i]);
        equal &= value[i] == prime[i];
    }
    return value[8] != 0 || greater || equal;
}

static inline
void subtract_p256(uint32_t value[9])
{
    static const uint32_t prime[8] = {
        0xffffffff, 0xffffffff, 0xffffffff, 0x00000000,
        0x00000000, 0x00000000, 0x00000001, 0xffffffff
    };
    uint32_t borrow = 0;

    for (unsigned i = 0; i < 8; ++i) {
        uint32_t subtrahend = prime[i] + borrow;
        uint32_t overflow = subtrahend < prime[i];
        uint32_t old = value[i];
        value[i] = old - subtrahend;
        borrow = overflow || old < subtrahend;
    }
    value[8] -= borrow;
}

static inline
void reduce_p256(uint32_t result[8], const uint32_t product[16])
{
    uint32_t remainder[9];

    for (unsigned i = 0; i < 9; ++i)
        remainder[i] = 0;

    for (int bit = 511; bit >= 0; --bit) {
        uint32_t carry = (product[(unsigned)bit >> 5] >> (bit & 31)) & 1;
        for (unsigned i = 0; i < 9; ++i) {
            uint32_t next = remainder[i] >> 31;
            remainder[i] = (remainder[i] << 1) | carry;
            carry = next;
        }
        if (at_least_p256(remainder))
            subtract_p256(remainder);
    }

    for (unsigned i = 0; i < 8; ++i)
        result[i] = remainder[i];
}

/* Multiply two 256-bit integers and reduce modulo the NIST P-256 field prime. */
void FUN_010089f8(uint32_t out[8], const uint32_t left[8],
                  const uint32_t right[8])
{
    uint32_t product[16];
    multiply_u256(product, left, right);
    reduce_p256(out, product);
}
