#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_array_scan_bounds__param_0009          [param_0009; G1-original]
 * Raw function identity: 0x0000e954.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0000e954 @ 0x0000e954
 * public-name: array_max_skip_nan_a
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   float_is_nan                             <= FUN_0000e938 @ 0x0000e938
 *   array_max_skip_nan_a                     <= FUN_0000e954 @ 0x0000e954
 */
/* Reconstructed FUN_0000e954 @ 0xe954  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int float_is_nan(float);
float array_max_skip_nan_a(float* param_1){
    int r0i = float_is_nan(param_1[0]);
    float fVar3; int cnt;
    if (r0i == 0){
        fVar3 = param_1[0]; cnt = 2;
    } else {
        r0i = float_is_nan(param_1[1]);
        if (r0i != 0){
            r0i = float_is_nan(param_1[2]);
            if (r0i == 0) return param_1[2];
            return param_1[0];
        }
        fVar3 = param_1[1]; cnt = 3;
    }
    unsigned r2 = (unsigned)cnt + 0x40000000u - 1u;
    float* p = (float*)((unsigned)(uintptr_t)param_1 + (r2 << 2));
    while (1){
        float fVar4 = *p;
        p = p + 1;
        fVar3 = (fVar4 > fVar3) ? fVar4 : fVar3;
        if (cnt != 2) break;
        cnt = 3;
    }
    return fVar3;
}
