/* readable reconstruction; identity: FUN_0000ea70 @ 0x0000ea70
 * public-name: spline_interp_pair_2out
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   float_is_nan                             <= FUN_0000e938 @ 0x0000e938
 *   spline_interp_pair_2out                  <= FUN_0000ea70 @ 0x0000ea70
 * address symbols (name @ address):
 *   g_spline_nan_sentinel                    @ 0x20002d1c
 */
/* Reconstructed FUN_0000ea70 @ 0xea70  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int float_is_nan(float);
void spline_interp_pair_2out(float param_1, float *param_2, unsigned int *param_3, float *param_4)
{
  unsigned int *puVar2 = param_3, *puVar3;
  float local_58[6];
  float *pfVar4 = local_58;
  do { puVar3 = puVar2+1; *(unsigned int*)pfVar4 = *puVar2; puVar2=puVar3; pfVar4++; } while (param_3+6 != puVar3);
  float fVar14 = *param_2, fVar13 = param_2[2];
  pfVar4 = param_2;
  int iVar1;
  do { float fVar5 = *pfVar4; pfVar4++; iVar1 = float_is_nan(fVar5); if (iVar1 != 0) return; } while (param_2+3 != pfVar4);
  float fVar11 = param_2[1];
  float fVar10 = local_58[0], fVar5 = local_58[3], fVar12 = local_58[5], fVar6 = local_58[2];
  if ((int)((unsigned)(fVar11 < *param_2) << 0x1f) < 0) {
    fVar14 = param_2[2]; fVar13 = *param_2; fVar10 = local_58[2]; fVar5 = local_58[5]; fVar12 = local_58[3]; fVar6 = local_58[0];
  }
  iVar1 = float_is_nan(param_1);
  if (iVar1 == 0) {
    float fVar7 = fVar11 - fVar14;
    float fVar8 = (local_58[1] - fVar10)/fVar7;
    float fVar9 = (local_58[4] - fVar5)/fVar7;
    fVar6 = ((fVar6 - local_58[1])/(fVar13 - fVar11) - fVar8)/(fVar13 - fVar14);
    fVar13 = ((fVar12 - local_58[4])/(fVar13 - fVar11) - fVar9)/(fVar13 - fVar14);
    param_1 = param_1 - fVar14;
    /* shipped 0xea70: vfms.f32 x2, vfma.f32 x4 -- fused, so spell them fused. */
    {
        float a = __builtin_fmaf(-fVar7, fVar6, fVar8);
        float b = __builtin_fmaf(-fVar7, fVar13, fVar9);
        a = __builtin_fmaf(fVar6, param_1, a);
        b = __builtin_fmaf(fVar13, param_1, b);
        fVar10 = __builtin_fmaf(a, param_1, fVar10);
        fVar5 = __builtin_fmaf(b, param_1, fVar5);
    }
  } else {
    fVar10 = *(volatile float*)0x20002d1cUL;
    fVar5 = fVar10;
  }
  param_4[1] = fVar5;
  *param_4 = fVar10;
}
