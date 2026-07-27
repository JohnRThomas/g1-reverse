#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000768e0 @ 0x000768e0
 * public-name: atanf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atanf                                    <= FUN_000768e0 @ 0x000768e0
 *   fabsf                                    <= FUN_000868ee @ 0x000868ee
 */
/* Reconstructed FUN_000768e0 @ 0x768e0 */
#include <stdint.h>

typedef unsigned uint;
extern float fabsf(float);
static inline uint bits(float f) { union { float f; uint u; } v = { f }; return v.u; }
static inline int sbits(float f) { union { float f; int i; } v = { f }; return v.i; }
static inline float fp(uint u) { union { uint u; float f; } v = { u }; return v.f; }

float atanf(float x)
{
    float ax = fp(bits(x) & 0x7fffffffU);
    float reduced, square, fourth, odd, even;
    int octant;

    if (bits(ax) < 0x50800000U) {
        if (bits(ax) > 0x3edfffffU) {
            reduced = fabsf(x);
            if (bits(ax) > 0x3f97ffffU) {
                if (bits(ax) > 0x401bffffU) {
                    octant = 3;
                    reduced = -1.0f / reduced;
                } else {
                    octant = 2;
                    reduced = (reduced - 1.5f) / __builtin_fmaf(reduced, 1.5f, 1.0f);
                }
            } else if (bits(ax) > 0x3f2fffffU) {
                octant = 1;
                reduced = (reduced - 1.0f) / (reduced + 1.0f);
            } else {
                octant = 0;
                reduced = __builtin_fmaf(reduced, 2.0f, -1.0f) / (reduced + 2.0f);
            }
        } else {
            if (bits(ax) < 0x31000000U) {
                float rounded = x + fp(0x7149f2ca);
                if (rounded != 1.0f && ((rounded < 1.0f) == (rounded != rounded)))
                    return x;
            }
            octant = -1;
            reduced = x;
        }

        square = reduced * reduced;
        fourth = square * square;
        /* shipped 0x76966..0x769b6: both Horner chains are vfma.f32 */
        odd = __builtin_fmaf(fourth, fp(0x3c8569d7), fp(0x3d4bda59));
        odd = __builtin_fmaf(fourth, odd, fp(0x3d886b35));
        odd = __builtin_fmaf(fourth, odd, fp(0x3dba2e6e));
        odd = __builtin_fmaf(fourth, odd, fp(0x3e124925));
        odd = __builtin_fmaf(fourth, odd, fp(0x3eaaaaab));
        even = __builtin_fmaf(fourth, fp(0xbd15a221), fp(0xbd6ef16b));
        even = __builtin_fmaf(fourth, even, fp(0xbd9d8795));
        even = __builtin_fmaf(fourth, even, fp(0xbde38e38));
        even = fourth * __builtin_fmaf(fourth, even, fp(0xbe4ccccd));
        /* shipped 0x769be `vmul s14,s14,s13` then 0x769c2 `vfma.f32 s14,s11,s12`:
         * the (odd + even) sum is itself ONE fused op, `even + odd_inner*square`,
         * and `odd` is never multiplied out on its own.  Everything after it --
         * 0x769c6 vmul / 0x769cc vsub / 0x76a22..0x76a2e vsub -- is UNFUSED in
         * the shipped image, so those must stay plain `a - b*c`. */
        {
            const float sum = __builtin_fmaf(odd, square, even);
            if (octant == -1) {
                return reduced - reduced * sum;
            }
            reduced = *(volatile float *)(0x000986cc + octant * 4) -
                      ((reduced * sum -
                        *(volatile float *)(0x000986bc + octant * 4)) - reduced);
        }
        {
            if (sbits(x) < 0)
                reduced = -reduced;
        }
        return reduced;
    }
    if (bits(ax) < 0x7f800001U)
        return sbits(x) > 0 ? fp(0x3fc90fdb) : fp(0xbfc90fdb);
    return x + x;
}
