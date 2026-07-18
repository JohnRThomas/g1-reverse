/* readable reconstruction; identity: FUN_00075f88 @ 0x00075f88
 * public-name: __ieee754_asinf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __ieee754_asinf                          <= FUN_00075f88 @ 0x00075f88
 *   fabsf                                    <= FUN_000868ee @ 0x000868ee
 */
/* Reconstructed FUN_00075f88 @ 0x75f88  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern float fabsf(void);
extern float FUN_000869c6(float);

static inline float F(uint32_t b){ union{float f;uint32_t u;}x; x.u=b; return x.f; }
static inline uint32_t B(float f){ union{float f;uint32_t u;}x; x.f=f; return x.u; }

float __ieee754_asinf(float param_1)
{
    uint32_t r5 = B(param_1);
    uint32_t r4 = r5 & 0x7fffffff;
    float s0 = param_1;

    if (r4 == 0x3f800000) {
        float s15 = param_1 * F(0xb33bbd2e);
        s15 = __builtin_fmaf(param_1, F(0x3fc90fdb), s15);
        return s15;
    }
    if (r4 > 0x3f800000) {
        float s15 = param_1 - param_1;
        return s15 / s15;
    }
    float s17 = 1.0f;
    if (r4 < 0x3f000000) {
        if (r4 >= 0x32000000) {
            float s15 = param_1 * param_1;
            float s14 = __builtin_fmaf(s15, F(0x3811ef08), F(0x3a4f7f04));
            float s13 = __builtin_fmaf(s14, s15, F(0xbd241146));
            s14 = __builtin_fmaf(s13, s15, F(0x3e4e0aa8));
            s13 = __builtin_fmaf(s14, s15, F(0xbea6b090));
            s14 = __builtin_fmaf(s13, s15, F(0x3e2aaaab));
            s13 = __builtin_fmaf(s15, F(0x3d9dc62e), F(0xbf303361));
            s14 = s14 * s15;
            float s12 = __builtin_fmaf(s13, s15, F(0x4001572d));
            s13 = __builtin_fmaf(s12, s15, F(0xc019d139));
            s17 = __builtin_fmaf(s13, s15, s17);
            s15 = s14 / s17;
            s0 = __builtin_fmaf(s0, s15, s0);
            return s0;
        }
        float s15 = param_1 + F(0x7149f2ca);
        if (s15 > 1.0f) return param_1;
    }
    /* CALL1 */
    float ret1 = fabsf();
    float s16 = (1.0f - ret1) * 0.5f;
    float s14 = __builtin_fmaf(s16, F(0x3811ef08), F(0x3a4f7f04));
    float s15 = __builtin_fmaf(s14, s16, F(0xbd241146));
    s14 = __builtin_fmaf(s15, s16, F(0x3e4e0aa8));
    s15 = __builtin_fmaf(s14, s16, F(0xbea6b090));
    float s18 = __builtin_fmaf(s15, s16, F(0x3e2aaaab));
    float s15b = __builtin_fmaf(s16, F(0x3d9dc62e), F(0xbf303361));
    s18 = s18 * s16;
    s14 = __builtin_fmaf(s15b, s16, F(0x4001572d));
    s15b = __builtin_fmaf(s14, s16, F(0xc019d139));
    s17 = __builtin_fmaf(s15b, s16, s17);
    float ret2 = FUN_000869c6(s16);
    float s12 = s18 / s17;

    if (r4 > 0x3f799999) {
        float s0r = __builtin_fmaf(ret2, s12, ret2);
        float s15c = __builtin_fmaf(s0r, 2.0f, F(0x333bbd2e));
        float res = F(0x3fc90fdb) - s15c;
        if ((int)r5 <= 0) res = -res;
        return res;
    } else {
        uint32_t r3 = B(ret2) & 0xfffff000u;
        float s11 = ret2 + ret2;
        float s14b = F(r3);
        float s16b = __builtin_fmaf(-s14b, s14b, s16);
        float s0d = ret2 + s14b;
        float s10 = s16b / s0d;
        float s15d = __builtin_fmaf(-s10, 2.0f, F(0xb33bbd2e));
        s15d = __builtin_fmaf(s11, s12, -s15d);
        float s12b = __builtin_fmaf(-s14b, 2.0f, F(0x3f490fdb));
        s15d = s15d - s12b;
        float res = F(0x3f490fdb) - s15d;
        if ((int)r5 <= 0) res = -res;
        return res;
    }
}
