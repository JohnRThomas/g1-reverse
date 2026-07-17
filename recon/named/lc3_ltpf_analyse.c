/* readable reconstruction; identity: FUN_0006ab80 @ 0x0006ab80
 * public-name: lc3_ltpf_analyse
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_ltpf_interpolate                     <= FUN_00069468 @ 0x00069468
 *   lc3_ltpf_resample                        <= FUN_0006954c @ 0x0006954c
 *   lc3_ltpf_analyse                         <= FUN_0006ab80 @ 0x0006ab80
 * address symbols (name @ address):
 *   rodata_8c938                             @ 0x0008c938
 */
/* Reconstructed FUN_0006ab80 @ 0x0006ab80.
 * Genuine code extent: 0x0006ab80..0x0006b32a.  The words at 0x0006acb4
 * and 0x0006b32c are literal-pool/data islands, not executable code.
 * Payload/source identification: liblc3 lc3_ltpf_analyse (NCS 2.5.1).
 */
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

struct lc3_ltpf_hp50_state {
    int64_t s1, s2;
};

struct lc3_ltpf_analysis {
    bool active;
    int pitch;
    float nc[2];
    struct lc3_ltpf_hp50_state hp50;
    int16_t x_12k8[384];
    int16_t x_6k4[178];
    int tc;
};

struct lc3_ltpf_data {
    bool active;
    int pitch_index;
};

typedef void (*resample_12k8_fn)(struct lc3_ltpf_hp50_state *,
    const int16_t *, int16_t *, int);

extern void *FUN_00086c44(void *, const void *, uint32_t);
extern bool FUN_000698d0(struct lc3_ltpf_analysis *, const int16_t *, int, int *);
extern void lc3_ltpf_resample(const int16_t *, const int16_t *, int, float *);
extern void lc3_ltpf_interpolate(const int16_t *, int, int, int16_t *);

#define RESAMPLE_12K8 ((const resample_12k8_fn *)(uintptr_t)0x0008c938u)

static __attribute__((always_inline)) inline float interpolate_corr(const float *x, int d)
{
    static const float h4[4][8] = {
        {  1.53572770e-02f, -4.72963246e-02f,  8.35788573e-02f,
           8.98638285e-01f,  8.35788573e-02f, -4.72963246e-02f,
           1.53572770e-02f, 0.0f },
        {  2.74547165e-03f,  4.59833449e-03f, -7.54404636e-02f,
           8.17488686e-01f,  3.30182571e-01f, -1.05835916e-01f,
           2.86823405e-02f, -2.87456116e-03f },
        { -3.00125103e-03f,  2.95038503e-02f, -1.30305021e-01f,
           6.03297008e-01f,  6.03297008e-01f, -1.30305021e-01f,
           2.95038503e-02f, -3.00125103e-03f },
        { -2.87456116e-03f,  2.86823405e-02f, -1.05835916e-01f,
           3.30182571e-01f,  8.17488686e-01f, -7.54404636e-02f,
           4.59833449e-03f,  2.74547165e-03f },
    };
    const float *h = h4[(4 + d) % 4];
    float y = d < 0 ? x[-4] * *h++ : d > 0 ? x[4] * h[7] : 0.0f;
    y += x[-3] * h[0] + x[-2] * h[1] + x[-1] * h[2] +
         x[0] * h[3] + x[1] * h[4] + x[2] * h[5] + x[3] * h[6];
    return y;
}

static __attribute__((always_inline)) inline int refine_pitch(const int16_t *x, int n, int tc, int *pitch)
{
    float r[17], rm;
    int e, f;
    int r0 = 2 * tc - 4;
    if (r0 < 32) r0 = 32;
    int top = 2 * tc + 4;
    if (top > 228) top = 228;
    int nr = top - r0 + 1;

    lc3_ltpf_resample(x, x - (r0 - 4), n, r);
    int best = 0;
    rm = r[4];
    for (int i = 1; i < nr; i++) {
        if (r[4 + i] > rm) {
            rm = r[4 + i];
            best = i;
        }
    }
    e = r0 + best;
    const float *re = r + 4 + best;

    float dm = interpolate_corr(re, f = 0);
    for (int i = 1; i <= 3; i++) {
        float d;
        if (e < 127 || ((i & 1) == 0 && e < 157)) {
            d = interpolate_corr(re, i);
            if (d > dm) dm = d, f = i;
        }
        if (e > 32) {
            d = interpolate_corr(re, -i);
            if (d > dm) dm = d, f = -i;
        }
    }
    e -= f < 0;
    f += 4 * (f < 0);
    *pitch = 4 * e + f;
    return e < 127 ? 4 * e + f - 128 :
           e < 157 ? 2 * e + (f >> 1) + 126 : e + 283;
}

static __attribute__((always_inline)) inline float dot(const int16_t *x, const int16_t *y, int n)
{
    int64_t s = 0;
    for (int i = 0; i < n; i++) s += (int32_t)x[i] * y[i];
    int32_t s32 = (int32_t)((s + 32) >> 6);
    return (float)s32;
}

bool lc3_ltpf_analyse(int dt, int sr, struct lc3_ltpf_analysis *ltpf,
    const int16_t *x, struct lc3_ltpf_data *data)
{
    const int z_12k8 = 384;
    const int n_12k8 = dt == 0 ? 96 : 128;

    FUN_00086c44(ltpf->x_12k8, ltpf->x_12k8 + n_12k8,
        (uint32_t)((z_12k8 - n_12k8) * sizeof(*ltpf->x_12k8)));
    int16_t *x_12k8 = ltpf->x_12k8 + z_12k8 - n_12k8;
    RESAMPLE_12K8[sr](&ltpf->hp50, x, x_12k8, n_12k8);
    x_12k8 -= dt == 0 ? 44 : 24;

    const int z_6k4 = 178;
    const int n_6k4 = n_12k8 >> 1;
    FUN_00086c44(ltpf->x_6k4, ltpf->x_6k4 + n_6k4,
        (uint32_t)((z_6k4 - n_6k4) * sizeof(*ltpf->x_6k4)));
    int16_t *x_6k4 = ltpf->x_6k4 + z_6k4 - n_6k4;

    const int16_t *p = x_12k8 - 1;
    for (int i = 0; i < n_6k4; i++, p += 2) {
        int32_t v = ((int32_t)p[-2] + p[2]) * 0x1fa9 +
                    (int32_t)p[0] * 0x482d +
                    ((int32_t)p[-1] + p[1]) * 0x3c40;
        x_6k4[i] = (int16_t)(v >> 16);
    }

    int tc, pitch = 0;
    float nc = 0.0f;
    bool pitch_present = FUN_000698d0(ltpf, x_6k4, n_6k4, &tc);

    if (pitch_present) {
        int16_t u[n_12k8], v[n_12k8];
        data->pitch_index = refine_pitch(x_12k8, n_12k8, tc, &pitch);
        lc3_ltpf_interpolate(x_12k8, n_12k8, 0, u);
        lc3_ltpf_interpolate(x_12k8 - (pitch >> 2), n_12k8, pitch & 3, v);
        nc = dot(u, v, n_12k8) /
             __builtin_sqrtf(dot(u, u, n_12k8) * dot(v, v, n_12k8));
    }

    bool active;
    if (ltpf->active) {
        int pitch_diff = pitch > ltpf->pitch ? pitch - ltpf->pitch : ltpf->pitch - pitch;
        float nc_diff = nc - ltpf->nc[0];
        active = pitch_present &&
            (nc > 0.9f || (nc > 0.84f && pitch_diff < 8 && nc_diff > -0.1f));
    } else {
        active = pitch_present &&
            ((dt == 1 || ltpf->nc[1] > 0.94f) &&
             (ltpf->nc[0] > 0.94f && nc > 0.94f));
    }

    float old_nc = ltpf->nc[0];
    *(volatile uint8_t *)&data->active = active;
    *(volatile uint8_t *)&ltpf->active = active;
    *(volatile float *)&ltpf->nc[0] = nc;
    *(volatile int *)&ltpf->pitch = pitch;
    *(volatile float *)&ltpf->nc[1] = old_nc;
    return pitch_present;
}
