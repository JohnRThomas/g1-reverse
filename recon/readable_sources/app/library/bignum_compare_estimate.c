#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   aiStack_2c       => struct g1_layout_bignum_estimate_ints__stack_1573       [stack_1573; G1-original]
 * Raw function identity: 0x000875e4.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000875e4 @ 0x000875e4
 * public-name: bignum_compare_estimate
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __divdf3                                 <= FUN_0000db4c @ 0x0000db4c
 *   d2b                                      <= FUN_00078c44 @ 0x00078c44
 *   bignum_compare_estimate                  <= FUN_000875e4 @ 0x000875e4
 */
/* Reconstructed FUN_000875e4 @ 0x875e4. */
#include <stdint.h>

extern double d2b(int object, int *scale);
extern uint64_t __divdf3(uint32_t left_low, uint32_t left_high,
                             uint32_t right_low, uint32_t right_high);

union double_words {
    double value;
    uint64_t bits;
};

double bignum_compare_estimate(int left, int right)
{
    int left_scale;
    int right_scale;
    union double_words left_value = { .value = d2b(left, &left_scale) };
    union double_words right_value = { .value = d2b(right, &right_scale) };
    uint32_t left_high = (uint32_t)(left_value.bits >> 32);
    uint32_t right_high = (uint32_t)(right_value.bits >> 32);
    int scale_delta = (left_scale - right_scale) +
        (*(volatile int *)(left + 0x10) - *(volatile int *)(right + 0x10)) * 32;

    if (scale_delta <= 0)
        right_high += (uint32_t)(scale_delta * -0x100000);
    else
        left_high += (uint32_t)(scale_delta * 0x100000);

    union double_words result = {
        .bits = __divdf3((uint32_t)left_value.bits, left_high,
                             (uint32_t)right_value.bits, right_high)
    };
    return result.value;
}
