#include "g1_net_symbols.h"
/* net-core FUN_010087f0 @ 0x010087f0 */
#include <stdint.h>

static void square_u256(uint32_t product[16], const uint32_t value[8])
{
    for (unsigned i = 0; i < 16; ++i)
        product[i] = 0;

    for (unsigned i = 0; i < 8; ++i) {
        uint64_t carry = 0;
        for (unsigned j = 0; j < 8; ++j) {
            uint64_t sum = (uint64_t)value[i] * value[j] +
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

/* Convert the arithmetic worker's private 512-bit result into a limb array. */
void FUN_010087f0(uint32_t result[16], const uint32_t value[8])
{
    uint32_t square[16];
    square_u256(square, value);

    /* The firmware worker returns the high half in registers first, then the
     * adapter copies the low half from its caller-reserved stack area. */
    for (unsigned i = 8; i < 16; ++i)
        result[i] = square[i];
    for (unsigned i = 0; i < 8; ++i)
        result[i] = square[i];
}
