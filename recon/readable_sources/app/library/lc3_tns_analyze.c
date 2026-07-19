#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_5          => struct g1_layout_lc3_tns_params__param_0391             [param_0391; library]
 *   local_154        => struct g1_layout_lc3_tns_analyze_local__stack_1387      [stack_1387; G1-original]
 *   local_11c        => struct g1_layout_lc3_tns_scratch5__stack_1388           [stack_1388; G1-original]
 * Raw function identity: 0x0006ffd8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0006ffd8 @ 0x0006ffd8
 * public-name: lc3_tns_analyze
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   lc3_tns_subdivision_table                @ 0x0008853c
 *   lc3_tns_rc_levels                        @ 0x00098540
 *   lc3_tns_rc_thresholds                    @ 0x00098564
 */
/* Reconstructed lc3_tns_analyze @ 0x0006ffd8.
 * Raw identity: FUN_0006ffd8. Exact executable extent: 0x9ee bytes,
 * [0x0006ffd8,0x000709c6]. The branch over [0x00070398,0x000703c4)
 * owns a 44-byte float literal island; trailing literals start at 0x709c8.
 *
 * Semantic match: NCS 2.5.1 modules/lib/liblc3/src/tns.c. Fixed-address
 * tables retain the shipped image identity rather than manufacturing copies. */
#include <stdbool.h>
#include <stdint.h>

enum lc3_dt {
    LC3_DT_7M5 = 0,
    LC3_DT_10M = 1,
};

enum lc3_bandwidth {
    LC3_BANDWIDTH_NB = 0,
    LC3_BANDWIDTH_WB = 1,
    LC3_BANDWIDTH_SSWB = 2,
    LC3_BANDWIDTH_SWB = 3,
    LC3_BANDWIDTH_FB = 4,
};

struct lc3_tns_data {
    int nfilters;
    bool lpc_weighting;
    int rc_order[2];
    int rc[2][8];
};

_Static_assert(sizeof(struct lc3_tns_data) == 80, "LC3 TNS ABI");

/* Address -> semantic table back-map. */
#define LC3_TNS_SUBDIVISION_TABLE \
    ((const int *const (*)[5])(uintptr_t)((unsigned long)&lc3_tns_subdivision_table) /*=0x8853c*/)
#define LC3_TNS_RC_THRESHOLDS \
    ((const float *)(uintptr_t)((unsigned long)&lc3_tns_rc_thresholds) /*=0x98564*/)
#define LC3_TNS_RC_LEVELS \
    ((const float *)(uintptr_t)((unsigned long)&lc3_tns_rc_levels) /*=0x98540*/)

static inline int lc3_ne(enum lc3_dt dt, enum lc3_bandwidth bw)
{
    return 20 * (3 + dt) * (1 + bw);
}

static inline bool resolve_lpc_weighting(enum lc3_dt dt, int nbytes)
{
    return nbytes < (dt == LC3_DT_7M5 ? 45 : 60);
}

static inline float dot_product(const float *left, const float *right, int count)
{
    float sum = 0.0f;
    while (count--)
        sum += *left++ * *right++;
    return sum;
}

static void compute_lpc_coefficients(enum lc3_dt dt, enum lc3_bandwidth bw,
                                     const float *spectrum,
                                     float prediction_gain[2],
                                     float coefficients[2][9])
{
    static const float lag_window[9] = {
        1.00000000e+00f, 9.98028026e-01f, 9.92135406e-01f,
        9.82391584e-01f, 9.68910791e-01f, 9.51849807e-01f,
        9.31404933e-01f, 9.07808230e-01f, 8.81323137e-01f,
    };
    const int *subdivision = LC3_TNS_SUBDIVISION_TABLE[dt][bw];
    int filter_count = 1 + (bw >= LC3_BANDWIDTH_SWB);
    const float *sub_start;
    const float *sub_end = spectrum + *subdivision;
    float autocorrelation[2][9];

    for (int filter = 0; filter < filter_count; ++filter) {
        float correlation[9][3];
        for (int sub = 0; sub < 3; ++sub) {
            sub_start = sub_end;
            sub_end = spectrum + *++subdivision;
            for (int lag = 0; lag < 9; ++lag)
                correlation[lag][sub] = dot_product(
                    sub_start, sub_start + lag,
                    (int)(sub_end - sub_start) - lag);
        }

        float energy0 = correlation[0][0];
        float energy1 = correlation[0][1];
        float energy2 = correlation[0][2];
        autocorrelation[filter][0] = 3.0f;
        for (int lag = 1; lag < 9; ++lag) {
            autocorrelation[filter][lag] =
                energy0 == 0.0f || energy1 == 0.0f || energy2 == 0.0f
                ? 0.0f
                : (correlation[lag][0] / energy0 +
                   correlation[lag][1] / energy1 +
                   correlation[lag][2] / energy2) * lag_window[lag];
        }
    }

    for (int filter = 0; filter < filter_count; ++filter) {
        float *even = coefficients[filter];
        float odd[9];
        float error = autocorrelation[filter][0];
        prediction_gain[filter] = error;
        even[0] = 1.0f;

        for (int order = 1; order < 9;) {
            float reflection = -autocorrelation[filter][order];
            for (int i = 1; i < order; ++i)
                reflection -= even[i] * autocorrelation[filter][order - i];
            reflection /= error;
            error *= 1.0f - reflection * reflection;
            for (int i = 1; i < order; ++i)
                odd[i] = even[i] + reflection * even[order - i];
            odd[order++] = reflection;

            reflection = -autocorrelation[filter][order];
            for (int i = 1; i < order; ++i)
                reflection -= odd[i] * autocorrelation[filter][order - i];
            reflection /= error;
            error *= 1.0f - reflection * reflection;
            for (int i = 1; i < order; ++i)
                even[i] = odd[i] + reflection * odd[order - i];
            even[order++] = reflection;
        }
        prediction_gain[filter] /= error;
    }
}

static inline void apply_lpc_weighting(float prediction_gain,
                                       float coefficients[9])
{
    float gamma = 1.0f - (1.0f - 0.85f) *
                  (2.0f - prediction_gain) / (2.0f - 1.5f);
    float power = 1.0f;
    for (int i = 1; i < 9; ++i)
        coefficients[i] *= (power *= gamma);
}

static void lpc_to_reflection(const float coefficients[9], float reflection[8])
{
    float error;
    float workspace[2][7];
    float *current = workspace[1];

    reflection[7] = coefficients[8];
    error = 1.0f - reflection[7] * reflection[7];
    for (int i = 0; i < 7; ++i)
        current[i] = (coefficients[1 + i] -
                      reflection[7] * coefficients[7 - i]) / error;

    for (int order = 6; order > 0; --order) {
        float *previous = current;
        current = workspace[order & 1];
        reflection[order] = previous[order];
        error = 1.0f - reflection[order] * reflection[order];
        for (int i = 0; i < order; ++i)
            current[i] = (previous[i] -
                          reflection[order] * previous[order - 1 - i]) / error;
    }
    reflection[0] = current[0];
}

static void quantize_reflection(const float reflection[8], int *order,
                                int quantized[8])
{
    const float *threshold = LC3_TNS_RC_THRESHOLDS;
    *order = 8;
    for (int i = 0; i < 8; ++i) {
        float magnitude = __builtin_fabsf(reflection[i]);
        quantized[i] = 4 * (magnitude >= threshold[4]);
        for (int j = 0; j < 4 && magnitude >= threshold[quantized[i]];
             ++j, ++quantized[i]) {}
        if (reflection[i] < 0.0f)
            quantized[i] = -quantized[i];
        *order = quantized[i] != 0 ? 8 : *order - 1;
    }
}

static void unquantize_reflection(const int quantized[8], int order,
                                  float reflection[8])
{
    const float *level = LC3_TNS_RC_LEVELS;
    for (int i = 0; i < order; ++i) {
        int index = quantized[i] < 0 ? -quantized[i] : quantized[i];
        float magnitude = level[index];
        reflection[i] = quantized[i] < 0 ? -magnitude : magnitude;
    }
}

static void forward_filter(enum lc3_dt dt, enum lc3_bandwidth bw,
                           const int order[2], const float reflection[2][8],
                           float spectrum[])
{
    int filter_count = 1 + (bw >= LC3_BANDWIDTH_SWB);
    int band_length = lc3_ne(dt, bw) >> (filter_count - 1);
    int begin;
    int end = 3 * (3 + dt);
    float state[8] = { 0.0f };

    for (int filter = 0; filter < filter_count; ++filter) {
        begin = end;
        end = band_length * (1 + filter);
        if (!order[filter])
            continue;
        for (int i = begin; i < end; ++i) {
            float sample = spectrum[i];
            float previous;
            float propagated = sample;
            for (int k = 0; k < order[filter]; ++k) {
                previous = state[k];
                state[k] = propagated;
                propagated = reflection[filter][k] * sample + previous;
                sample += reflection[filter][k] * previous;
            }
            spectrum[i] = sample;
        }
    }
}

void lc3_tns_analyze(enum lc3_dt dt, enum lc3_bandwidth bw,
                     bool near_nyquist, int frame_bytes,
                     struct lc3_tns_data *data, float spectrum[])
{
    float prediction_gain[2];
    float coefficients[2][9];
    float reflection[2][8];

    /* Pinned upstream declares these in the opposite source order.  The
     * shipped -O3 schedule publishes the independent weighting byte first;
     * retain that observable write order for differential trace parity. */
    data->lpc_weighting = resolve_lpc_weighting(dt, frame_bytes);
    data->nfilters = 1 + (bw >= LC3_BANDWIDTH_SWB);
    compute_lpc_coefficients(dt, bw, spectrum, prediction_gain, coefficients);

    for (int filter = 0; filter < data->nfilters; ++filter) {
        data->rc_order[filter] = 0;
        if (near_nyquist || prediction_gain[filter] <= 1.5f)
            continue;
        if (data->lpc_weighting && prediction_gain[filter] < 2.0f)
            apply_lpc_weighting(prediction_gain[filter], coefficients[filter]);
        lpc_to_reflection(coefficients[filter], reflection[filter]);
        quantize_reflection(reflection[filter], &data->rc_order[filter],
                            data->rc[filter]);
        unquantize_reflection(data->rc[filter], data->rc_order[filter],
                              reflection[filter]);
    }
    forward_filter(dt, bw, data->rc_order, reflection, spectrum);
}
