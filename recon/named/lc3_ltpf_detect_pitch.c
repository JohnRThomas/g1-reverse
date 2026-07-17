/* readable reconstruction; identity: FUN_000698d0 @ 0x000698d0
 * public-name: lc3_ltpf_detect_pitch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_ltpf_arm_correlate                   <= FUN_0006954c @ 0x0006954c
 *   lc3_ltpf_detect_pitch                    <= FUN_000698d0 @ 0x000698d0
 */
/* Recovered liblc3 detect_pitch @ 0x000698d0 (true CFG extent 3202 bytes). */
#include <stdint.h>
#include <stdbool.h>

extern void lc3_ltpf_arm_correlate(const int16_t *, const int16_t *, int, float *, int);

static __attribute__((always_inline)) inline float dot(const int16_t *a, const int16_t *b, int n)
{
    int64_t v = 0;
    for (int i = 0; i < (n >> 4); ++i)
        for (int j = 0; j < 16; ++j) v += *a++ * *b++;
    return (float)(int32_t)((v + 32) >> 6);
}

static __attribute__((always_inline)) inline int argmax(const float *x, int n, float *maximum)
{
    int arg = 0; *maximum = x[0];
    for (int i = 1; i < n; ++i)
        if (*maximum < x[i]) *maximum = x[arg = i];
    return arg;
}

static __attribute__((always_inline)) inline int argmax_weighted(const float *x, int n, float increment, float *maximum)
{
    int arg = 0;
    float weighted_maximum = (*maximum = x[0]);
    float weight = 1.0f + increment;
    for (int i = 1; i < n; ++i, weight += increment) {
        if (weighted_maximum < x[i] * weight)
            weighted_maximum = (*maximum = x[arg = i]) * weight;
    }
    return arg;
}

__attribute__((optimize("fast-math")))
bool lc3_ltpf_detect_pitch(void *analysis, const int16_t *x, int n, int *pitch_lag)
{
    float rm1, rm2, correlation[98];
    int previous = *(int32_t *)((uint8_t *)analysis + 0x484);
    int k0 = previous - 4; if (k0 < 0) k0 = 0;
    int top = previous + 4; if (top > 97) top = 97;
    int nk = top - k0 + 1;

    lc3_ltpf_arm_correlate(x, x - 17, n, correlation, 98);
    int t1 = argmax_weighted(correlation, 98, -0.5f / 97.0f, &rm1);
    int t2 = k0 + argmax(correlation + k0, nk, &rm2);
    const int16_t *x1 = x - (17 + t1);
    const int16_t *x2 = x - (17 + t2);
    float nc1 = rm1 <= 0.0f ? 0.0f :
        rm1 / __builtin_sqrtf(dot(x, x, n) * dot(x1, x1, n));
    float nc2 = rm2 <= 0.0f ? 0.0f :
        rm2 / __builtin_sqrtf(dot(x, x, n) * dot(x2, x2, n));
    int choose_first = nc2 <= 0.85f * nc1;
    *(int32_t *)((uint8_t *)analysis + 0x484) = choose_first ? t1 : t2;
    *pitch_lag = 17 + *(int32_t *)((uint8_t *)analysis + 0x484);
    return (choose_first ? nc1 : nc2) > 0.6f;
}
