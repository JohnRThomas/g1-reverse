/* readable reconstruction; identity: FUN_00076538 @ 0x00076538
 * public-name: logf_core
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   logf_core                                <= FUN_00076538 @ 0x00076538
 */
/* Reconstructed FUN_00076538 @ 0x76538  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
static inline float F(uint32_t b){ union{float f;uint32_t u;}x; x.u=b; return x.f; }
static inline uint32_t B(float f){ union{float f;uint32_t u;}x; x.f=f; return x.u; }

float logf_core(float param_1)
{
    uint32_t r3bits = B(param_1);
    uint32_t r2 = r3bits & 0x7fffffff;
    volatile float zero = 0.0f;

    if (r2 == 0) { float s14 = F(0xcc000000); return s14 / zero; }
    if ((int32_t)r3bits < 0) { float s14 = param_1 - param_1; return s14 / zero; }
    if ((int32_t)r3bits >= 0x7f800000) return param_1 + param_1;

    int32_t r1e;
    uint32_t r2v;
    if ((int32_t)r3bits < 0x800000) {
        float s = param_1 * F(0x4c000000);
        r1e = -0x19;
        r2v = B(s);
    } else {
        r1e = 0;
        r2v = r3bits;
    }
    int32_t r3s = (int32_t)r2v >> 0x17;
    uint32_t uVar2 = r2v & 0x7fffff;
    r3s = r3s - 0x7f;
    uint32_t r0 = 0x004afb20 + uVar2;
    r3s = r3s + r1e;
    uint32_t r1m = (r0 & 0x800000) ^ 0x3f800000;
    r3s = r3s + (int32_t)(r0 >> 23);
    uint32_t r0b = uVar2 + 0xf;
    r1m = r1m | uVar2;
    float fVar3 = F(r1m) - 1.0f;
    uint32_t r1chk = 0x007ffff0 & r0b;

    if (r1chk == 0) {
        if (fVar3 == 0.0f) {
            if (r3s == 0) return F(0x00000000);
            float f = (float)r3s;
            return __builtin_fmaf(f, F(0x3f317180), f * F(0x3717f7d1));
        }
        float s14 = fVar3 * fVar3;
        float s15 = __builtin_fmaf(-fVar3, F(0x3eaaaaab), 0.5f);
        float fVar7 = s14 * s15;
        if (r3s == 0) return fVar3 - fVar7;
        float f = (float)r3s;
        float t = __builtin_fmaf(-f, F(0x3717f7d1), fVar7);
        float u = t - fVar3;
        return __builtin_fmaf(f, F(0x3f317180), -u);
    }

    /* POLY */
    uint32_t r1a = 0xffcf5c30 + uVar2;
    int32_t r2b = (int32_t)(((uint32_t)(0x35c288 - uVar2)) | r1a);
    float fVar5 = fVar3 / (fVar3 + 2.0f);
    float fVar6 = (float)r3s;
    float s10 = fVar5 * fVar5;
    float s14 = s10 * s10;
    float s15 = __builtin_fmaf(s14, F(0x3e1cd04f), F(0x3e638e29));
    float s11 = __builtin_fmaf(s15, s14, F(0x3ecccccd));
    s15 = __builtin_fmaf(s14, F(0x3e178897), F(0x3e3a3325));
    float s9 = __builtin_fmaf(s15, s14, F(0x3e924925));
    s15 = __builtin_fmaf(s9, s14, F(0x3f2aaaab));
    s15 = s15 * s10;
    s15 = __builtin_fmaf(s11, s14, s15);

    if (r2b > 0) {
        float s14b = fVar3 * 0.5f;
        s14b = s14b * fVar3;
        s15 = s15 + s14b;
        s15 = s15 * fVar5;
        if (r3s == 0) {
            float fv7 = s14b - s15;
            return fVar3 - fv7;
        }
        s15 = __builtin_fmaf(fVar6, F(0x3717f7d1), s15);
        s14b = s14b - s15;
        float s0v = s14b - fVar3;
        return __builtin_fmaf(fVar6, F(0x3f317180), -s0v);
    } else {
        s15 = (fVar3 - s15) * fVar5;
        if (r3s == 0) return fVar3 - s15;
        s15 = __builtin_fmaf(-fVar6, F(0x3717f7d1), s15);
        float s0v = s15 - fVar3;
        return __builtin_fmaf(fVar6, F(0x3f317180), -s0v);
    }
}
