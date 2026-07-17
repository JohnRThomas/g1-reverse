/* readable reconstruction; identity: FUN_000682f0 @ 0x000682f0
 * public-name: lc3_attdet_run
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_attdet_run                           <= FUN_000682f0 @ 0x000682f0
 * address symbols (name @ address):
 *   lc3_attdet_nbytes_ranges                 @ 0x000884d0
 */
/* Reconstructed FUN_000682f0 @ 0x682f0  (parity: 200/200 trials, PROVEN) */
unsigned lc3_attdet_run(int param_1, unsigned param_2, int param_3, int *param_4, int param_5)
{
    int *tbl = (int *)0x000884d0UL;
    int local_58[4];
    int local_48[8];
    int iVar3, iVar4, iVar6, iVar8, iVar9, iVar10, iVar11, iVar14;
    short sVar1, sVar2;
    unsigned uVar5, uVar7;
    int *piVar12, *piVar13;
    int i;

    for (i = 0; i < 8; i++) local_48[i] = tbl[i];

    if (2 < param_2) {
        iVar8 = (int)(param_2 - 3) + param_1 * 2;
        if (local_48[iVar8 * 2] <= param_3 && param_3 <= local_48[iVar8 * 2 + 1]) {
            iVar8 = (param_1 == 0) ? 3 : 4;
            iVar9 = *(short *)(param_5 + -4);
            iVar14 = *(short *)(param_5 + -2);
            piVar12 = local_58;
            do {
                sVar1 = *(short *)(param_5 + -8);
                sVar2 = *(short *)(param_5 + -6);
                piVar13 = piVar12 + 1;
                *piVar12 = 0;
                if (param_2 == 3) {
                    iVar11 = 0;
                    iVar10 = param_5 + 4;
                    iVar4 = (iVar9 + iVar14) >> 1;
                    iVar6 = ((int)sVar2 + (int)sVar1) >> 1;
                    do {
                        iVar3 = iVar4;
                        iVar9 = *(short *)(iVar10 + -4);
                        iVar14 = *(short *)(iVar10 + -2);
                        iVar10 = iVar10 + 4;
                        iVar4 = (iVar9 + iVar14) >> 1;
                        iVar6 = (int)(((iVar9 + iVar14) & 0xfffffffeU) + iVar4 + iVar3 * -4 + iVar6) >> 3;
                        iVar11 = iVar11 + (iVar6 * iVar6 >> 5);
                        iVar6 = iVar3;
                    } while (param_5 + 0xa4 != iVar10);
                    param_5 = param_5 + 0xa0;
                } else {
                    iVar11 = 0;
                    iVar10 = param_5 + 6;
                    iVar4 = ((int)*(short *)(param_5 + -0xc) + (int)*(short *)(param_5 + -10) + (int)sVar1) >> 2;
                    iVar6 = ((int)sVar2 + iVar9 + iVar14) >> 2;
                    do {
                        iVar9 = *(short *)(iVar10 + -4);
                        iVar14 = *(short *)(iVar10 + -2);
                        iVar3 = ((int)*(short *)(iVar10 + -6) + iVar9 + iVar14) >> 2;
                        iVar4 = (iVar3 * 3 + iVar6 * -4 + iVar4) >> 3;
                        iVar10 = iVar10 + 6;
                        iVar11 = iVar11 + (iVar4 * iVar4 >> 5);
                        iVar4 = iVar6;
                        iVar6 = iVar3;
                    } while (param_5 + 0xf6 != iVar10);
                    param_5 = param_5 + 0xf0;
                }
                *piVar12 = iVar11;
                piVar12 = piVar13;
            } while (piVar13 != local_58 + iVar8);

            iVar9 = param_4[1] >> 2;
            if (param_4[1] >> 2 < *param_4) iVar9 = *param_4;
            uVar7 = (unsigned)(iVar9 + (iVar9 >> 4) < local_58[0] >> 3);
            iVar14 = iVar9 >> 2;
            if (iVar9 >> 2 < local_58[0]) iVar14 = local_58[0];
            if (iVar14 + (iVar14 >> 4) < local_58[1] >> 3) uVar7 = 2;
            iVar9 = iVar14 >> 2;
            if (iVar14 >> 2 < local_58[1]) iVar9 = local_58[1];
            if (iVar9 + (iVar9 >> 4) < local_58[2] >> 3) uVar7 = 3;
            if (iVar8 == 4) {
                iVar9 = iVar9 >> 2;
                if (iVar9 < local_58[2]) iVar9 = local_58[2];
                local_58[2] = local_58[3];
                if (iVar9 + (iVar9 >> 4) < local_58[3] >> 3) uVar7 = 4;
            }
            iVar8 = (iVar8 == 3) ? 1 : 2;
            *param_4 = local_58[2];
            param_4[1] = iVar9;
            if (iVar8 < param_4[2]) uVar5 = 1;
            else { uVar5 = uVar7; if (uVar7 != 0) uVar5 = 1; }
            param_4[2] = uVar7;
            return uVar5;
        }
    }
    return 0;
}
