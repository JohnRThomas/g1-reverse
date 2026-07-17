/* readable reconstruction; identity: FUN_000768e0 @ 0x000768e0
 * public-name: FUN_000768e0
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_000768e0 @ 0x768e0 */
#include <stdint.h>

typedef unsigned uint;
extern float FUN_000868ee(float);
static inline uint bits(float f) { union { float f; uint u; } v = { f }; return v.u; }
static inline int sbits(float f) { union { float f; int i; } v = { f }; return v.i; }
static inline float fp(uint u) { union { uint u; float f; } v = { u }; return v.f; }

float FUN_000768e0(float x)
{
    float ax = fp(bits(x) & 0x7fffffffU);
    float reduced, square, fourth, odd, even;
    int octant;

    if (bits(ax) < 0x50800000U) {
        if (bits(ax) > 0x3edfffffU) {
            reduced = FUN_000868ee(x);
            if (bits(ax) > 0x3f97ffffU) {
                if (bits(ax) > 0x401bffffU) {
                    octant = 3;
                    reduced = -1.0f / reduced;
                } else {
                    octant = 2;
                    reduced = (reduced - 1.5f) / (reduced * 1.5f + 1.0f);
                }
            } else if (bits(ax) > 0x3f2fffffU) {
                octant = 1;
                reduced = (reduced - 1.0f) / (reduced + 1.0f);
            } else {
                octant = 0;
                reduced = (reduced * 2.0f - 1.0f) / (reduced + 2.0f);
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
        odd = square * (fp(0x3eaaaaab) + fourth *
            (fp(0x3e124925) + fourth * (fp(0x3dba2e6e) + fourth *
            (fp(0x3d886b35) + fourth * (fp(0x3d4bda59) + fourth * fp(0x3c8569d7))))));
        even = fourth * (fp(0xbe4ccccd) + fourth *
            (fp(0xbde38e38) + fourth * (fp(0xbd9d8795) + fourth *
            (fp(0xbd6ef16b) + fourth * fp(0xbd15a221)))));
        if (octant == -1) {
            return reduced - reduced * (odd + even);
        } else {
            reduced = *(volatile float *)(0x000986cc + octant * 4) -
                      ((reduced * (odd + even) -
                        *(volatile float *)(0x000986bc + octant * 4)) - reduced);
            if (sbits(x) < 0)
                reduced = -reduced;
        }
        return reduced;
    }
    if (bits(ax) < 0x7f800001U)
        return sbits(x) > 0 ? fp(0x3fc90fdb) : fp(0xbfc90fdb);
    return x + x;
}
