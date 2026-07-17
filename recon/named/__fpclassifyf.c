/* readable reconstruction; identity: FUN_00075980 @ 0x00075980
 * public-name: __fpclassifyf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __fpclassifyf                            <= FUN_00075980 @ 0x00075980
 */
/* Reconstructed FUN_00075980 @ 0x75980  (parity: 300/300 trials, PROVEN) */

typedef unsigned int u32;

int __fpclassifyf(float param_1)
{
    union { float f; u32 u; } cvt;
    cvt.f = param_1;
    u32 p = cvt.u & 0x7fffffffUL;
    if (p == 0) return 2;
    if ((p - 0x800000UL) > 0x7effffffUL) {
        if ((p - 1) > 0x7ffffeUL) {
            return p == 0x7f800000UL;
        }
        return 3;
    }
    return 4;
}
