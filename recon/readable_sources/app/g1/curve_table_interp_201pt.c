#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_3          => struct g1_layout_curve_table_201pt__param_0004          [param_0004; G1-original]
 *   param_4          => struct g1_layout_curve_interp_table_201pt__param_0005   [param_0005; G1-original]
 *   param_5          => struct g1_layout_curve_table_201pt__param_0006          [param_0006; G1-original]
 * Raw function identity: 0x0000e3a0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0000e3a0 @ 0x0000e3a0
 * public-name: curve_table_interp_201pt
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   curve_table_interp_201pt                 <= FUN_0000e3a0 @ 0x0000e3a0
 *   float_is_nan                             <= FUN_0000e938 @ 0x0000e938
 *   floorf                                   <= FUN_000868fc @ 0x000868fc
 */
/* Reconstructed FUN_0000e3a0 @ 0xe3a0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern float floorf(float);
extern int float_is_nan(float);

float curve_table_interp_201pt(float param_1, float param_2, float *param_3, float *param_4, float *param_5, int param_6)
{
    float fVar4 = param_3[0];
    float fVar7 = param_3[1] - fVar4;
    float fVar5 = param_3[200];
    float fVar6;
    int r3;

    if (fVar4 < param_1) {
        if (param_1 >= fVar5) goto E3DE;
        if (param_1 < fVar5) goto INTERP;
        fVar6 = 0.0f;
        goto E49C;
    } else {
        if (param_1 < fVar5) {
            if (fVar4 < param_1) r3 = (param_1 < fVar5) ? 1 : 0;
            else r3 = 0;
            {
                float a = __builtin_fmaf(param_5[1], param_2, param_4[1]);
                float b = __builtin_fmaf(param_5[0], param_2, param_4[0]);
                float num = (param_1 - fVar4) * (a - b);
                fVar6 = __builtin_fmaf(param_5[0], param_2, num / fVar7 + param_4[0]);
            }
            if (r3 == 0) goto E49C;
            goto INTERP;
        }
    }
E3DE:
    if (fVar4 < param_1) r3 = (param_1 < fVar5) ? 1 : 0;
    else r3 = 0;
    {
        float a = __builtin_fmaf(param_5[200], param_2, param_4[200]);
        float b = __builtin_fmaf(param_5[199], param_2, param_4[199]);
        float num = (a - b) * (param_1 - fVar5);
        fVar6 = __builtin_fmaf(param_5[200], param_2, num / fVar7 + param_4[200]);
    }
    if (r3 == 0) goto E49C;
    goto INTERP;
INTERP:
    {
        float ft = floorf((param_1 - fVar4) / fVar7);
        int iVar2 = (int)(ft + 2.0f) + 0x3fffffff;
        int iVar1 = (int)(ft + 1.0f) + 0x3fffffff;
        float f = (param_1 - param_3[0]) / fVar7 - ft;
        float s15 = f * param_5[iVar2];
        s15 = __builtin_fmaf(param_5[iVar1], (1.0f - f), s15);
        float s16 = f * param_4[iVar2];
        s16 = __builtin_fmaf(param_4[iVar1], (1.0f - f), s16);
        fVar6 = __builtin_fmaf(param_2, s15, s16);
    }
E49C:
    {
        int e = float_is_nan(param_1);
        return (e == 0) ? fVar6 : 0.0f;
    }
}
