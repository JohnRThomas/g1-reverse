/* Readable reconstruction of lc3_spec_encode <= FUN_0006f9c0 @ 0x0006f9c0.
 *
 * This is the upstream liblc3 spectral encoder present in NCS 2.5.1.  The
 * firmware inlined its private helpers, so they remain readable below.  Raw
 * callee/table identities are retained at the boundary macros:
 *   lc3_get_bits_left      <= FUN_00068590 @ 0x00068590
 *   lc3_put_bits_generic   <= FUN_00068908 @ 0x00068908
 *   lc3_ac_write_renorm    <= FUN_0006897c @ 0x0006897c
 *   lc3_spectrum_models    @ 0x0008dc50
 *   lc3_spectrum_lookup    @ 0x0008ed50
 * Exact executable extent: [0x0006f9c0, 0x0006ffd8).
 */

#define lc3_spec_encode       FUN_0006f9c0
#define lc3_get_bits_left     FUN_00068590
#define lc3_put_bits_generic  FUN_00068908
#define lc3_ac_write_renorm   FUN_0006897c

#include "/Users/freedomcoder/ncs251/modules/lib/liblc3/src/bits.h"
#include "/Users/freedomcoder/ncs251/modules/lib/liblc3/src/spec.h"

#define SPECTRUM_MODELS \
    ((const struct lc3_ac_model *)0x0008dc50u)
#define SPECTRUM_LOOKUP \
    ((const uint8_t (*)[2][256][4])0x0008ed50u)

static __attribute__((always_inline)) inline float
absolute_float(float value)
{
    union { float value; uint32_t bits; } converted = { value };
    converted.bits &= 0x7fffffffu;
    return converted.value;
}

static __attribute__((always_inline)) inline void
write_bits(lc3_bits_t *bits, unsigned value, int count)
{
    volatile struct lc3_bits_accu *accumulator = &bits->accu;
    if (accumulator->n + count <= LC3_ACCU_BITS) {
        int previous_count = accumulator->n;
        accumulator->n = previous_count + count;
        accumulator->v = accumulator->v | value << previous_count;
    } else {
        lc3_put_bits_generic(bits, value, count);
    }
}

static __attribute__((always_inline)) inline void
write_bit(lc3_bits_t *bits, int value)
{
    write_bits(bits, value, 1);
}

/* GCC schedules the independent accumulator stores in the late residual loop
 * in value-then-count order.  Keep that observable MMIO-style ordering
 * explicit while retaining the same generic overflow boundary. */
static __attribute__((always_inline)) inline void
write_tail_bit(lc3_bits_t *bits, int value)
{
    volatile struct lc3_bits_accu *accumulator = &bits->accu;
    int previous_count = accumulator->n;
    if (previous_count + 1 <= LC3_ACCU_BITS) {
        accumulator->v = accumulator->v | (unsigned)value << previous_count;
        accumulator->n = previous_count + 1;
    } else {
        lc3_put_bits_generic(bits, value, 1);
    }
}

static __attribute__((always_inline)) inline void
write_symbol(lc3_bits_t *bits, const struct lc3_ac_model *model,
             unsigned symbol)
{
    const struct lc3_ac_symbol *symbols = model->s;
    volatile struct lc3_bits_ac *coder = &bits->ac;
    unsigned range = coder->range >> 10;
    unsigned low = coder->low + range * symbols[symbol].low;
    coder->low = low;
    coder->range = range * symbols[symbol].range;
    coder->carry = coder->carry | low >> 24;
    coder->low = low & 0xffffff;
    if (coder->range < 0x10000)
        lc3_ac_write_renorm(bits);
}

/* In the LSB magnitude loop GCC commits the masked low word before the
 * independent range and carry stores. */
static __attribute__((always_inline)) inline void
write_lsb_level_symbol(lc3_bits_t *bits, const struct lc3_ac_model *model,
                       unsigned symbol)
{
    const struct lc3_ac_symbol *symbols = model->s;
    volatile struct lc3_bits_ac *coder = &bits->ac;
    unsigned range = coder->range >> 10;
    unsigned low = coder->low + range * symbols[symbol].low;
    coder->low = low;
    coder->low = low & 0xffffff;
    coder->range = range * symbols[symbol].range;
    coder->carry = coder->carry | low >> 24;
    if (coder->range < 0x10000)
        lc3_ac_write_renorm(bits);
}

static __attribute__((always_inline)) inline bool
spectrum_high_rate(enum lc3_srate sr, int nbytes)
{
    return nbytes > 20 * (1 + (int)sr);
}

static __attribute__((always_inline)) inline int
estimate_noise_factor(enum lc3_dt dt, enum lc3_bandwidth bw,
    const uint16_t *quantized, int significant_count, const float *spectrum)
{
    int bandwidth_stop = (dt == LC3_DT_7M5 ? 60 : 80) * (1 + bw);
    int window = 2 + dt;
    float sum = 0;
    int i, nonzero_count = 0, zero_run = 0;

    for (i = 6 * (3 + dt) - window;
         i < LC3_MIN(significant_count, bandwidth_stop); i++) {
        zero_run = quantized[i] ? 0 : zero_run + 1;
        if (zero_run > 2 * window) {
            sum += absolute_float(spectrum[i - window]);
            nonzero_count++;
        }
    }

    for (; i < bandwidth_stop + window; i++) {
        if (++zero_run > 2 * window) {
            sum += absolute_float(spectrum[i - window]);
            nonzero_count++;
        }
    }

    int factor = nonzero_count
        ? 8 - (int)((16 * sum) / nonzero_count + 0.5f) : 0;
    return LC3_CLIP(factor, 0, 7);
}

static __attribute__((always_inline)) inline void
put_noise_factor(lc3_bits_t *bits, int factor)
{
    write_bits(bits, factor, 3);
}

static __attribute__((always_inline)) inline void
put_quantized_spectrum(lc3_bits_t *bits,
    enum lc3_dt dt, enum lc3_srate sr, int nbytes,
    const uint16_t *quantized, int significant_count, bool lsb_mode)
{
    int encoded_samples = LC3_NE(dt, sr);
    bool high_rate = spectrum_high_rate(sr, nbytes);
    uint8_t state = 0;

    for (int i = 0, half = 0; half < 2; half++) {
        const uint8_t (*coefficient_lookup)[4] =
            SPECTRUM_LOOKUP[high_rate][half];

        for (; i < LC3_MIN(significant_count,
                           (encoded_samples + 2) >> (1 - half)); i += 2) {
            const uint8_t *lookup = coefficient_lookup[state];
            uint16_t first = quantized[i] >> 1;
            uint16_t second = quantized[i + 1] >> 1;
            int magnitude = (first | second) >> 2;
            int level = 0, shift = 0;

            if (magnitude) {
                if (lsb_mode)
                    write_symbol(bits,
                        SPECTRUM_MODELS + lookup[level++], 16);

                for (magnitude >>= lsb_mode; magnitude;
                     magnitude >>= 1, level++) {
                    write_bit(bits, (first >> level) & 1);
                    write_bit(bits, (second >> level) & 1);
                    if (lsb_mode)
                        write_lsb_level_symbol(bits, SPECTRUM_MODELS +
                            lookup[LC3_MIN(level, 3)], 16);
                    else
                        write_symbol(bits, SPECTRUM_MODELS +
                            lookup[LC3_MIN(level, 3)], 16);
                }

                first >>= lsb_mode;
                second >>= lsb_mode;
                shift = level - lsb_mode;
                level = LC3_MIN(level, 3);
            }

            if (first)
                write_bit(bits, quantized[i] & 1);
            if (second)
                write_bit(bits, quantized[i + 1] & 1);

            first >>= shift;
            second >>= shift;
            write_symbol(bits, SPECTRUM_MODELS + lookup[level],
                           first + 4 * second);

            state = (state << 4) +
                (level > 1 ? 12 + level
                           : 1 + (first + second) * (level + 1));
        }
    }
}

static __attribute__((always_inline)) inline void
put_residual_bits(lc3_bits_t *bits, int bit_budget,
    const uint16_t *quantized, int count, const float *spectrum)
{
    for (int i = 0; i < count && bit_budget > 0; i++) {
        if (quantized[i] == 0)
            continue;

        float quantized_value = quantized[i] & 1
            ? -(quantized[i] >> 1) : (quantized[i] >> 1);
        write_tail_bit(bits, spectrum[i] >= quantized_value);
        bit_budget--;
    }
}

static __attribute__((always_inline)) inline void
put_lsb_bits(lc3_bits_t *bits, int bit_budget,
    const uint16_t *quantized, int count)
{
    for (int i = 0; i < count && bit_budget > 0; i += 2) {
        uint16_t first = quantized[i] >> 1;
        uint16_t second = quantized[i + 1] >> 1;
        int first_negative = quantized[i] & 1;
        int second_negative = quantized[i + 1] & 1;

        if ((first | second) >> 2 == 0)
            continue;

        if (bit_budget-- > 0)
            write_bit(bits, first & 1);
        if (first == 1 && bit_budget-- > 0)
            write_bit(bits, first_negative);
        if (bit_budget-- > 0)
            write_bit(bits, second & 1);
        if (second == 1 && bit_budget-- > 0)
            write_bit(bits, second_negative);
    }
}

void lc3_spec_encode(lc3_bits_t *bits,
    enum lc3_dt dt, enum lc3_srate sr, enum lc3_bandwidth bandwidth,
    int nbytes, const uint16_t *quantized,
    const lc3_spec_side_t *side, const float *spectrum)
{
    bool lsb_mode = side->lsb_mode;
    int significant_count = side->nq;

    put_noise_factor(bits, estimate_noise_factor(dt, bandwidth,
        quantized, significant_count, spectrum));
    put_quantized_spectrum(bits, dt, sr, nbytes,
                           quantized, significant_count, lsb_mode);

    int bits_left = lc3_get_bits_left(bits);
    if (lsb_mode)
        put_lsb_bits(bits, bits_left, quantized, significant_count);
    else
        put_residual_bits(bits, bits_left, quantized,
                          significant_count, spectrum);
}
