/* readable reconstruction; identity: FUN_00076290 @ 0x00076290
 * public-name: __ieee754_expf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __ieee754_expf                           <= FUN_00076290 @ 0x00076290
 * address symbols (name @ address):
 *   rodata_9869c                             @ 0x0009869c
 *   rodata_986a4                             @ 0x000986a4
 *   rodata_986ac                             @ 0x000986ac
 */
/* Reconstructed FUN_00076290 @ 0x76290 */
#include <stdint.h>

typedef unsigned uint;
static inline uint bits(float f) { union { float f; uint u; } v = { f }; return v.u; }
static inline int sbits(float f) { union { float f; int i; } v = { f }; return v.i; }
static inline float fp(uint u) { union { uint u; float f; } v = { u }; return v.f; }
static inline int signed_add_overflows(int a, int b)
{
    uint sum = (uint)a + (uint)b;
    return (int)(~((uint)a ^ (uint)b) & ((uint)a ^ sum)) < 0;
}

float __ieee754_expf(float x)
{
    float ax = fp(bits(x) & 0x7fffffffU);
    int reduction;
    float high = 0.0f, low = 0.0f;

    if (bits(ax) > 0x7f800000U)
        return x + x;
    if (bits(ax) == 0x7f800000U)
        return sbits(x) >= 0 ? x : 0.0f;
    if (sbits(x) > 0x42b17217) {
        float huge = fp(0x7149f2ca);
        return huge * huge;
    }
    if (sbits(x) < 0 && bits(ax) > 0x42cff1b5U)
        return 0.0f;

    if (bits(ax) > 0x3eb17218U) {
        int table_offset = (sbits(x) >> 31) * -4;
        if (bits(ax) > 0x3f851591U) {
            float t;
            /* shipped 0x762fa vfma.f32, 0x76308 vfms.f32 */
            reduction = (int)__builtin_fmaf(x, fp(0x3fb8aa3b),
                              *(volatile float *)(0x000986ac + table_offset));
            t = (float)reduction;
            high = __builtin_fmaf(-t, fp(0x3f317180), x);
            low = t * fp(0x3717f7d1);
        } else {
            high = x - *(volatile float *)(0x000986a4 + table_offset);
            reduction = (sbits(x) >> 31) * 2 + 1;
            low = *(volatile float *)(0x0009869c + table_offset);
        }
        x = high - low;
    } else {
        if (bits(ax) < 0x31800000U) {
            float rounded = x + fp(0x7149f2ca);
            if (rounded != 1.0f && ((rounded < 1.0f) == (rounded != rounded)))
                return x + 1.0f;
        }
        reduction = 0;
    }

    /* shipped 0x76340..0x7635c: vfma.f32 x4 (Horner) then vfms.f32 (the x - P*s) */
    float square = x * x;
    float horner = __builtin_fmaf(square, fp(0x3331bb4c), fp(0xb5ddea0e));
    horner = __builtin_fmaf(horner, square, fp(0x388ab355));
    horner = __builtin_fmaf(horner, square, fp(0xbb360b61));
    horner = __builtin_fmaf(horner, square, fp(0x3e2aaaab));
    float poly = __builtin_fmaf(-horner, square, x);

    if (reduction != 0) {
        int overflow = signed_add_overflows(reduction, 0x7d);
        int negative = reduction + 0x7d < 0;
        if (negative != overflow)
            reduction += 100;
        poly = 1.0f - ((low - (x * poly) / (2.0f - poly)) - high);
        poly = fp((uint)(sbits(poly) + reduction * 0x800000));
        if (negative != overflow)
            poly *= fp(0x0d800000);
        return poly;
    }
    return 1.0f - ((x * poly) / (poly - 2.0f) - x);
}
