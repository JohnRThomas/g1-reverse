#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000869f2 @ 0x000869f2
 * public-name: finitef
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   finitef                                  <= FUN_000869f2 @ 0x000869f2
 */
/* Reconstructed FUN_000869f2 @ 0x869f2  (parity: 300/300 trials, PROVEN) */

int finitef(float x)
{
    /* 0x869f2: vmov r3,s0; bic r0,r3,#0x80000000; cmp.w r0,#0x7f800000;
     * ite ge; movge r0,#0; movlt r0,#1 -- newlib finitef.  The argument is a
     * hard-float value in s0, and the answer is 0 for infinities and NaNs.
     * The previous body ignored s0 and returned 1 unconditionally. */
    union { float f; unsigned int u; } bits;
    bits.f = x;
    return (bits.u & 0x7fffffffu) < 0x7f800000u;
}
