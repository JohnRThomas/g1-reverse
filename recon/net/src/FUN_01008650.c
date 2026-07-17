/* net-core FUN_01008650 @ 0x1008650 */
#include <stdint.h>

/* Adapter for the firmware's private multi-register return convention.
 * The arithmetic worker returns eight limbs in r0-r7, one in r11, and seven
 * through caller-reserved stack words.  The adapter's public contract is an
 * ordinary three-pointer 256x256 -> 512-bit multiply, so no custom C ABI is
 * needed. */
void FUN_01008650(uint32_t result[16], const uint32_t left[8],
                  const uint32_t right[8])
{
    uint32_t product[16];
    for (unsigned i = 0; i < 16; ++i)
        product[i] = 0;

    for (unsigned i = 0; i < 8; ++i) {
        uint64_t carry = 0;
        for (unsigned j = 0; j < 8; ++j) {
            uint64_t value = (uint64_t)left[i] * right[j] +
                             product[i + j] + carry;
            product[i + j] = (uint32_t)value;
            carry = value >> 32;
        }
        for (unsigned k = i + 8; carry != 0 && k < 16; ++k) {
            uint64_t value = (uint64_t)product[k] + carry;
            product[k] = (uint32_t)value;
            carry = value >> 32;
        }
    }

    /* Preserve the original adapter's externally visible write order. */
    for (unsigned i = 8; i < 16; ++i)
        result[i] = product[i];
    for (unsigned i = 0; i < 8; ++i)
        result[i] = product[i];
}
