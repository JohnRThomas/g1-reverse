/* Reconstructed FUN_00076a88 @ 0x76a88 (CFG-directed: 80/80 PASS).
 *
 * This is newlib's nanf(const char *tagp) leaf.  The tag is accepted for the
 * public ABI but this implementation returns the canonical quiet-NaN bits.
 */
#include <stdint.h>

float FUN_00076a88(const char *tagp)
{
    union {
        uint32_t bits;
        float value;
    } result = { 0x7fc00000u };

    (void)tagp;
    return result.value;
}
