/* Reconstructed FUN_00030528 @ 0x30528  (parity: 300/300 trials, PROVEN) */
extern int FUN_00030178(int a0,int a1,int a2,int a3,int a4);
extern int FUN_00030288(int a0);
extern int FUN_0007cf34(int a0,int a1,int a2);
extern int FUN_0007cfac(void);
extern int FUN_0007cfdc(int a0,int a1);
extern int FUN_0007d02a(int a0,int a1,int a2);
extern int FUN_0007d05e(void *a0,int a1);

int FUN_00030528(char *param_1, unsigned int param_2, int param_3, int param_4)
{
    unsigned char *pbVar1, *pbVar2, *pbVar3, *pbVar12;
    unsigned char bVar4;
    unsigned short uVar5;
    int iVar6, iVar7;
    int uVar8;
    unsigned int uVar9, uVar11;
    int *puVar10;
    unsigned int local_1c;

    local_1c = param_2;
    iVar6 = FUN_00030178(0xff20, 0x3c00ffff, param_3, param_4, (int)param_1);
    if ((iVar6 == 0) && (iVar6 = FUN_00030178(0x4444, 0x10000, 0, 0, 0), iVar6 == 0) &&
        (iVar6 = FUN_00030178(0x4820, 6, 0, 0, 0), iVar6 == 0) &&
        (*param_1 != 1 || (iVar6 = FUN_00030178(0x4794, 0x5a637955, 0, 0, 0), iVar6 == 0))) {
        uVar11 = **(unsigned int**)(param_1 + 0x10);
        iVar6 = FUN_00030178(0xff20, 0x3c00f091, 0, 0, 0);
        if ((iVar6 == 0) && (iVar6 = FUN_00030178(0x4820, 6, 0, 0, 0), iVar6 == 0) &&
            (*param_1 != 0 || (iVar6 = FUN_00030178(0x4794, 0x5a637955, 0, 0, 0), iVar6 == 0))) {
            uVar9 = uVar11 & 0x7f;
            if (uVar9 != 0) uVar9 = 1;
            for (iVar6 = 0; uVar9 + (uVar11 >> 7) != (unsigned int)iVar6; iVar6 = iVar6 + 1) {
                iVar7 = FUN_00030178(0x4704, *(int*)(*(int*)(param_1 + 0x10) + 4) + iVar6 * 0x80, 0, 0, 0);
                if (iVar7 != 0) return iVar7;
                iVar7 = FUN_00030178(0x4710, 5, 0, 0, 0);
                if (iVar7 != 0) return iVar7;
                iVar7 = FUN_00030178(0x472c, 0xf0, 0, 0, 0);
                if (iVar7 != 0) return iVar7;
                iVar7 = FUN_00030178(0x4714, 1, 0, 0, 0);
                if (iVar7 != 0) return iVar7;
                iVar7 = FUN_0007cfac();
                if (iVar7 != 0) return iVar7;
            }
            iVar6 = FUN_00030178(0x472c, 0x16, 0, 0, 0);
            if ((iVar6 == 0) && (iVar6 = FUN_00030178(0x4820, 4, 0, 0, 0), iVar6 == 0)) {
                pbVar12 = *(unsigned char**)(param_1 + 4);
                uVar9 = *(unsigned int*)(param_1 + 8);
                uVar5 = *(unsigned short*)(param_1 + 0xc);
                uVar11 = FUN_00030288((unsigned char)*param_1);
                if (uVar11 == 0) {
                    for (; uVar11 < uVar9; uVar11 = uVar11 + 4) {
                        iVar6 = FUN_0007cfdc((uVar5 + uVar11) & 0xffff,
                            ((unsigned int)pbVar12[1] << 0x10) | ((unsigned int)pbVar12[0] << 0x18) |
                            (unsigned int)pbVar12[3] | ((unsigned int)pbVar12[2] << 8));
                        pbVar12 = pbVar12 + 4;
                        if (iVar6 != 0) goto LAB_00030622;
                    }
                    local_1c = FUN_00030178(0x4820, 4, 0, 0, 0);
                    if (local_1c == 0) {
                        pbVar12 = *(unsigned char**)(param_1 + 4);
                        uVar11 = *(unsigned int*)(param_1 + 8);
                        iVar6 = FUN_00030178(0xff20, 0x3c00f091, 0, 0, 0);
                        if ((iVar6 == 0) && (uVar9 = FUN_00030178(0x4820, 4, 0, 0, 0), uVar9 == 0)) {
                            for (; uVar9 < uVar11; uVar9 = uVar9 + 4) {
                                iVar6 = FUN_0007d05e(&local_1c, (*(int*)(param_1 + 0xc) + uVar9) & 0xffff);
                                if (iVar6 != 0) goto LAB_00030622;
                                pbVar1 = pbVar12 + 1; bVar4 = *pbVar12; pbVar2 = pbVar12 + 3;
                                pbVar3 = pbVar12 + 2; pbVar12 = pbVar12 + 4;
                                if ((((unsigned int)*pbVar1 << 0x10) | ((unsigned int)bVar4 << 0x18) |
                                     (unsigned int)*pbVar2 | ((unsigned int)*pbVar3 << 8)) != local_1c)
                                    goto LAB_00030622;
                            }
                            iVar6 = FUN_0007d02a(*(unsigned short*)(*(int*)(param_1 + 0x10) + 8), 0x20222022, (unsigned char)*param_1);
                            if (iVar6 == 0) {
                                puVar10 = *(int**)(param_1 + 0x10);
                                uVar8 = FUN_0007cf34(*(int*)(param_1 + 4), *(int*)(param_1 + 8), *puVar10);
                                iVar6 = FUN_0007d02a(*(unsigned short*)(puVar10 + 3), uVar8, (unsigned char)*param_1);
                                if (iVar6 == 0) {
                                    if (*param_1 != 1) return 0;
                                    iVar6 = FUN_00030178(0x4794, 0, 0, 0, 0);
                                    return iVar6;
                                }
                            }
                        }
                    }
                }
LAB_00030622:
                iVar6 = -1;
            }
        }
    }
    return iVar6;
}

