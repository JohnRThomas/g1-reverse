#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_3          => struct g1_layout_lc3_sns_coeff_buffer__param_0381       [param_0381; library]
 * Raw function identity: 0x0006bd74.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0006bd74 @ 0x0006bd74
 * public-name: lc3_sns_unquantize
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_sns_unquantize                       <= FUN_0006bd74 @ 0x0006bd74
 * address symbols (name @ address):
 *   lc3_sns_dct16_matrix                     @ 0x0008ce4c
 *   lc3_sns_vq_gains                         @ 0x000903e8
 *   lc3_sns_hfcb                             @ 0x00090450
 *   lc3_sns_lfcb                             @ 0x00090850
 */
/* Reconstructed FUN_0006bd74 @ 0x6bd74  (parity: 300/300 trials, PROVEN) */
void lc3_sns_unquantize(int param_1, int param_2, float *param_3, int param_4,
                  int param_5, float *param_6)
{
    float fVar2 = 0.0f;                                     /* DAT_0006bfb4 = 0x00000000 */
    float fVar8 = *(volatile float *)
        (*(volatile int *)(((unsigned long)&lc3_sns_vq_gains) /*=0x903e8*/ + param_4 * 8 + 4) + param_5 * 4);
    volatile float *pfVar6 = (volatile float *)(((unsigned long)&lc3_sns_lfcb) /*=0x90850*/ + param_1 * 0x20);
    volatile float *pfVar4 = (volatile float *)((unsigned long)&lc3_sns_dct16_matrix) /*=0x8ce4c*/ + 0x100;
    volatile float *pfVar3 = (volatile float *)(((unsigned long)&lc3_sns_hfcb) /*=0x90450*/ + param_2 * 0x20);
    volatile float *pfVar5 = (volatile float *)((unsigned long)&lc3_sns_dct16_matrix) /*=0x8ce4c*/;
    volatile float *pfVar7 = (volatile float *)param_6;
    float fVar9, fVar10;

    do {
        *pfVar7 = fVar2;
        fVar9 = pfVar5[0];
        fVar10 = param_3[0];
        *pfVar7 = fVar10 * fVar9;
        fVar9 = fVar10 * fVar9 + param_3[1]  * pfVar5[1];  *pfVar7 = fVar9;
        fVar9 = fVar9 + param_3[2]  * pfVar5[2];  *pfVar7 = fVar9;
        fVar9 = fVar9 + param_3[3]  * pfVar5[3];  *pfVar7 = fVar9;
        fVar9 = fVar9 + param_3[4]  * pfVar5[4];  *pfVar7 = fVar9;
        fVar9 = fVar9 + param_3[5]  * pfVar5[5];  *pfVar7 = fVar9;
        fVar9 = fVar9 + param_3[6]  * pfVar5[6];  *pfVar7 = fVar9;
        fVar9 = fVar9 + param_3[7]  * pfVar5[7];  *pfVar7 = fVar9;
        fVar9 = fVar9 + param_3[8]  * pfVar5[8];  *pfVar7 = fVar9;
        fVar9 = fVar9 + param_3[9]  * pfVar5[9];  *pfVar7 = fVar9;
        fVar9 = fVar9 + param_3[10] * pfVar5[10]; *pfVar7 = fVar9;
        fVar9 = fVar9 + param_3[11] * pfVar5[11]; *pfVar7 = fVar9;
        fVar9 = fVar9 + param_3[12] * pfVar5[12]; *pfVar7 = fVar9;
        fVar9 = fVar9 + param_3[13] * pfVar5[13]; *pfVar7 = fVar9;
        fVar9 = fVar9 + param_3[14] * pfVar5[14]; *pfVar7 = fVar9;
        *pfVar7 = fVar9 + param_3[15] * pfVar5[15];
        pfVar5 = pfVar5 + 0x10;
        pfVar7 = pfVar7 + 1;
    } while (pfVar4 != pfVar5);

    volatile float *vp = (volatile float *)param_6;
    vp[0]  = pfVar6[0]  + fVar8 * vp[0];
    vp[1]  = pfVar6[1]  + fVar8 * vp[1];
    vp[2]  = pfVar6[2]  + fVar8 * vp[2];
    vp[3]  = pfVar6[3]  + fVar8 * vp[3];
    vp[4]  = pfVar6[4]  + fVar8 * vp[4];
    vp[5]  = pfVar6[5]  + fVar8 * vp[5];
    vp[6]  = pfVar6[6]  + fVar8 * vp[6];
    vp[7]  = pfVar6[7]  + vp[7]  * fVar8;
    vp[8]  = pfVar3[0]  + fVar8 * vp[8];
    vp[9]  = pfVar3[1]  + vp[9]  * fVar8;
    vp[10] = pfVar3[2]  + fVar8 * vp[10];
    vp[11] = pfVar3[3]  + fVar8 * vp[11];
    vp[12] = pfVar3[4]  + fVar8 * vp[12];
    vp[13] = pfVar3[5]  + fVar8 * vp[13];
    vp[14] = pfVar3[6]  + fVar8 * vp[14];
    vp[15] = pfVar3[7]  + vp[15] * fVar8;
}
