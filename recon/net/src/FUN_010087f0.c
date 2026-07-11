/* net-core FUN_010087f0 @ 0x10087f0 */
#include <stdint.h>

/* Zephyr-ABI adapter for the firmware worker's r0-r7 + stack result. */
void FUN_010087f0(uint32_t result[16], const uint32_t value[8])
{
    uint32_t square[16] = {0};

    for (unsigned i = 0; i < 8; ++i) {
        uint64_t carry = 0;
        for (unsigned j = 0; j < 8; ++j) {
            uint64_t limb = (uint64_t)value[i] * value[j] +
                            square[i + j] + carry;
            square[i + j] = (uint32_t)limb;
            carry = limb >> 32;
        }
        for (unsigned k = i + 8; carry != 0 && k < 16; ++k) {
            uint64_t limb = (uint64_t)square[k] + carry;
            square[k] = (uint32_t)limb;
            carry = limb >> 32;
        }
    }

    for (unsigned i = 8; i < 16; ++i)
        result[i] = square[i];
    for (unsigned i = 0; i < 8; ++i)
        result[i] = square[i];
}
