/* readable reconstruction; identity: FUN_00068b68 @ 0x00068b68
 * public-name: FUN_00068b68
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_8bc60                             @ 0x0008bc60
 *   rodata_90c50                             @ 0x00090c50
 */
/* Reconstructed FUN_00068b68 @ 0x68b68  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int memset_bytes(void*,int,int);

float * FUN_00068b68(int param_1, int param_2, float *param_3, float *param_4)
{
    int bVar1;
    float *pfVar2;
    int iVar3, iVar4, iVar5, iVar6, iVar8;
    float *pfVar7;
    int *piVar9;
    float fVar10, fVar11;
    float local_28[2];

    iVar5 = *(volatile int *)(0x0008bc60 + (param_1 * 5 + param_2) * 4);
    local_28[0] = 0.0f;
    local_28[1] = 0.0f;
    if (iVar5 < 1) {
        iVar5 = 0;
        iVar3 = iVar5;
    } else {
        pfVar7 = param_4 + iVar5;
        pfVar2 = param_3;
        do {
            fVar10 = *pfVar2;
            pfVar2 = pfVar2 + 1;
            fVar10 = fVar10 * fVar10;
            *param_4 = fVar10;
            param_4 = param_4 + 1;
            local_28[0] = local_28[0] + fVar10;
        } while (param_4 != pfVar7);
        iVar3 = iVar5 << 2;
        param_4 = pfVar7;
    }
    iVar6 = param_2 + 1;
    if (param_2 == 4) {
        iVar6 = 6;
    }
    iVar6 = (param_1 + 3) * iVar6 * 0x14;
    if (0x3f < iVar6) {
        iVar6 = 0x40;
    }
    iVar8 = param_1 * 0x514 + param_2 * 0x104 + 0x00090c50;
    pfVar2 = param_4;
    iVar4 = iVar5;
    fVar10 = 0.0f;
    if (iVar5 < iVar6) {
        piVar9 = (int *)(iVar8 + iVar5 * 4);
        pfVar2 = param_4 + (iVar6 - iVar5);
        iVar3 = *(volatile int *)(iVar8 + iVar3);
        do {
            piVar9 = piVar9 + 1;
            iVar8 = *(volatile int *)piVar9;
            fVar10 = param_3[iVar3] * param_3[iVar3];
            iVar4 = iVar3 + 1;
            if (iVar3 + 1 < iVar8) {
                pfVar7 = param_3 + iVar3 + 1;
                do {
                    fVar11 = *pfVar7;
                    pfVar7 = pfVar7 + 1;
                    fVar10 = fVar10 + fVar11 * fVar11;
                    iVar4 = iVar8;
                } while (pfVar7 != param_3 + iVar8);
            }
            bVar1 = iVar6 + (2 - param_1) * -2 <= iVar5;
            fVar10 = fVar10 / (float)(iVar8 - iVar3);
            fVar11 = local_28[bVar1];
            *param_4 = fVar10;
            param_4 = param_4 + 1;
            local_28[bVar1] = fVar11 + fVar10;
            iVar5 = iVar5 + 1;
            iVar3 = iVar4;
            iVar4 = iVar6;
            fVar10 = local_28[1];
        } while (param_4 != pfVar2);
    }
    fVar11 = local_28[0];
    if (iVar4 < 0x40) {
        pfVar2 = (float *)memset_bytes(pfVar2, 0, (0x40 - iVar4) * 4);
    }
    iVar5 = (unsigned int)(fVar11 * 30.0f < fVar10) << 0x1f;
    if (iVar5 < 0) {
        pfVar2 = (float *)0x1;
    }
    if (-1 < iVar5) {
        pfVar2 = (float *)0x0;
    }
    return pfVar2;
}
