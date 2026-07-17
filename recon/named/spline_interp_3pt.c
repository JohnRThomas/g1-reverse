/* readable reconstruction; identity: FUN_0000eb7c @ 0x0000eb7c
 * public-name: spline_interp_3pt
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   float_is_nan                             <= FUN_0000e938 @ 0x0000e938
 *   spline_interp_3pt                        <= FUN_0000eb7c @ 0x0000eb7c
 * address symbols (name @ address):
 *   g_spline_nan_sentinel                    @ 0x20002d1c
 */
/* Reconstructed FUN_0000eb7c @ 0xeb7c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int float_is_nan(float);

float spline_interp_3pt(float param_1, float *param_2, float *param_3){
    float unaff_s16 = 0.0f;
    float fVar7=*param_2, fVar8=*param_3, fVar6=param_3[2], fVar5=param_2[2];
    float *pfVar2=param_2, fVar3;
    do {
        fVar3=*pfVar2; pfVar2=pfVar2+1;
        if (float_is_nan(fVar3) != 0) return unaff_s16;
    } while (param_2+3 != pfVar2);
    fVar3 = param_2[1];
    if (fVar3 < *param_2){ fVar7=param_2[2]; fVar8=param_3[2]; fVar6=*param_3; fVar5=*param_2; }
    float fVar9 = param_3[1];
    if (float_is_nan(param_1) != 0) return *(float*)0x20002d1c;
    float fVar4 = (fVar9-fVar8)/(fVar3-fVar7);
    fVar5 = ((fVar6-fVar9)/(fVar5-fVar3) - fVar4)/(fVar5-fVar7);
    return fVar8 + (fVar4 + -(fVar3-fVar7)*fVar5 + fVar5*(param_1-fVar7))*(param_1-fVar7);
}
