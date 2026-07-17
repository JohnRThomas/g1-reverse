/* Reconstructed FUN_000875e4 @ 0x875e4. */
#include <stdint.h>

extern double FUN_00078c44(int object, int *scale);
extern uint64_t FUN_0000db4c(uint32_t left_low, uint32_t left_high,
                             uint32_t right_low, uint32_t right_high);

union double_words {
    double value;
    uint64_t bits;
};

double FUN_000875e4(int left, int right)
{
    int left_scale;
    int right_scale;
    union double_words left_value = { .value = FUN_00078c44(left, &left_scale) };
    union double_words right_value = { .value = FUN_00078c44(right, &right_scale) };
    uint32_t left_high = (uint32_t)(left_value.bits >> 32);
    uint32_t right_high = (uint32_t)(right_value.bits >> 32);
    int scale_delta = (left_scale - right_scale) +
        (*(volatile int *)(left + 0x10) - *(volatile int *)(right + 0x10)) * 32;

    if (scale_delta <= 0)
        right_high += (uint32_t)(scale_delta * -0x100000);
    else
        left_high += (uint32_t)(scale_delta * 0x100000);

    union double_words result = {
        .bits = FUN_0000db4c((uint32_t)left_value.bits, left_high,
                             (uint32_t)right_value.bits, right_high)
    };
    return result.value;
}
