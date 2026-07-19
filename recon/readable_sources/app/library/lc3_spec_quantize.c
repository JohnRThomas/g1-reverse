#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0006f164 @ 0x0006f164
 * public-name: lc3_spec_quantize
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_spec_quantize                        <= FUN_0006f164 @ 0x0006f164
 * address symbols (name @ address):
 *   rodata_8d24c                             @ 0x0008d24c
 */
/* Reconstructed FUN_0006f164 @ 0x6f164, exact extent 282 bytes. */
#include <stdint.h>

static __attribute__((always_inline)) inline uint16_t encode_scaled_sample(float sample)
{
    union { float f; uint32_t u; } bits = { sample };
    bits.u &= 0x7fffffffu;
    float magnitude = bits.f + 0.375f;
    union { float f; uint32_t u; } rounded = { magnitude };
    if (((rounded.u & 0x7f800000u) == 0x7f800000u &&
         (rounded.u & 0x007fffffu) != 0u) || magnitude > 32767.0f)
        magnitude = 32767.0f;
    uint16_t integer = (uint16_t)(uint32_t)magnitude;
    uint32_t sign = integer != 0u && sample < 0.0f;
    return (uint16_t)((uint32_t)integer * 2u + sign);
}

void lc3_spec_quantize(uint32_t width, int32_t rows, int32_t exponent,
                  volatile float *samples, volatile uint16_t *encoded,
                  volatile int32_t *remaining)
{
    uint32_t magnitude = exponent < 0
        ? (uint32_t)(0u - (uint32_t)exponent) : (uint32_t)exponent;
    const float *scale_table = (const float *)((unsigned long)&rodata_8d24c) /*=0x8d24c*/;
    float scale = scale_table[magnitude & 0x3fu];
    for (uint32_t block = magnitude >> 6; block != 0u; --block)
        scale *= 193.0697784423828125f;
    if (exponent >= 0)
        scale = 1.0f / scale;

    int32_t total = (rows * (int32_t)(width + 3u) + (int32_t)(width + 3u)) * 20;
    *remaining = total;

    for (int32_t index = 0; index < total; index += 2) {
        samples[index] *= scale;
        samples[index + 1] *= scale;
        uint16_t first = encode_scaled_sample(samples[index]);
        uint16_t second = encode_scaled_sample(samples[index + 1]);
        encoded[index] = first;
        encoded[index + 1] = second;
        if ((first | second) == 0u)
            *remaining -= 2;
        else
            *remaining = total;
    }
}
