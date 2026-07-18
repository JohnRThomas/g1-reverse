/* readable reconstruction; identity: FUN_00064290 @ 0x00064290
 * public-name: cjson_parse_string
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_parse_string                       <= FUN_00064290 @ 0x00064290
 *   hex4_to_uint                             <= FUN_00084e9a @ 0x00084e9a
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 */
/* Reconstructed FUN_00064290 @ 0x64290  (parity: 300/300 trials, PROVEN) */
extern unsigned int hex4_to_uint(void *a0);

int cjson_parse_string(int param_1, int *param_2)
{
    int iVar5, iVar8, iVar9;
    unsigned char *pbVar10, *pbVar11, *pbVar12, *pbVar6, *pbVar2;
    unsigned char bVar1, bVar7;
    unsigned int uVar2, uVar3;
    typedef unsigned char* (*fp1_t)(int);
    typedef void (*fp2_t)(unsigned char*);

    iVar5 = param_2[0];
    iVar8 = param_2[2];
    pbVar10 = (unsigned char*)(iVar8 + 1 + iVar5);
    pbVar2 = (unsigned char*)0;
    if (*(char*)(iVar5 + iVar8) == '"') {
        iVar9 = 0;
        for (pbVar11 = pbVar10; (unsigned int)((int)pbVar11 - iVar5) < (unsigned int)param_2[1]; pbVar11 = pbVar11 + 1) {
            if (*pbVar11 == 0x22) {
                fp1_t f4 = (fp1_t)param_2[4];
                pbVar12 = f4((int)(pbVar11 + ((1 - iVar9) - (iVar5 + iVar8))));
                pbVar2 = pbVar12;
                if (pbVar12 != (unsigned char*)0) goto LAB_642d6;
                break;
            }
            if (*pbVar11 == 0x5c) {
                pbVar11 = pbVar11 + 1;
                if ((unsigned int)param_2[1] <= (unsigned int)((int)pbVar11 - iVar5)) break;
                iVar9 = iVar9 + 1;
            }
        }
        goto LAB_end;
LAB_642d6:
        while (1) {
            if (pbVar11 <= pbVar10) {
                *pbVar12 = 0;
                *(volatile int*)(param_1 + 0xc) = 0x10;
                *(volatile unsigned char**)(param_1 + 0x10) = pbVar2;
                param_2[2] = (int)(pbVar11 + (1 - param_2[0]));
                return 1;
            }
            bVar7 = *pbVar10;
            if (bVar7 == 0x5c) {
                bVar7 = pbVar10[1];
                if (bVar7 > 0x75) goto esc_default;
                if (bVar7 < 0x6e) {
                    if (bVar7 == 0x62) { bVar7 = 8; }
                    else if (bVar7 < 99) {
                        if ((bVar7 != 0x2f) && (bVar7 != 0x5c) && (bVar7 != 0x22)) goto esc_default;
                    } else {
                        if (bVar7 != 0x66) goto esc_default;
                        bVar7 = 0xc;
                    }
                    goto esc_common;
                }
                switch (bVar7) {
                case 0x6e: bVar7 = 10; goto esc_common;
                case 0x72: bVar7 = 0xd; goto esc_common;
                case 0x74: bVar7 = 9; goto esc_common;
                case 0x75: {
                    if (((int)pbVar11 - (int)pbVar10 < 6) ||
                        (uVar2 = hex4_to_uint(pbVar10 + 2), (uVar2 - 0xdc00) < 0x400))
                        goto esc_default;
                    if ((uVar2 - 0xd800) < 0x400) {
                        if (((int)pbVar11 - (int)(pbVar10 + 6) < 6) || (pbVar10[6] != 0x5c) ||
                            (pbVar10[7] != 0x75) ||
                            (uVar3 = hex4_to_uint(pbVar10 + 8), (uVar3 - 0xdc00) > 0x3ff))
                            goto esc_default;
                        iVar5 = 0xc;
                        uVar2 = ((0x000ffc00 & (uVar2 << 10)) | (uVar3 & 0x3ff)) + 0x10000;
                        bVar1 = 0xf0; iVar8 = 4;
                    } else if (uVar2 < 0x80) {
                        iVar5 = 6; bVar1 = 0; iVar8 = 1;
                    } else if (uVar2 < 0x800) {
                        iVar5 = 6; bVar1 = 0xc0; iVar8 = 2;
                    } else {
                        if (0xffff < uVar2) {
                            if (uVar2 < 0x110000) {
                                iVar5 = 6; bVar1 = 0xf0; iVar8 = 4;
                            } else goto esc_default;
                        } else {
                            iVar5 = 6; bVar1 = 0xe0; iVar8 = 3;
                        }
                    }
                    for (pbVar6 = pbVar12 + ((iVar8 - 1U) & 0xff); bVar7 = (unsigned char)uVar2, pbVar12 != pbVar6; pbVar6 = pbVar6 - 1) {
                        *pbVar6 = (bVar7 & 0x3f) | 0x80;
                        uVar2 = uVar2 >> 6;
                    }
                    if (iVar8 == 1) { bVar7 = bVar7 & 0x7f; }
                    else { bVar7 = bVar7 | bVar1; }
                    pbVar6 = pbVar12 + iVar8;
                    pbVar10 = pbVar10 + iVar5;
                    goto store_common;
                }
                default:
esc_default:
                    {
                        fp2_t f5 = (fp2_t)param_2[5];
                        f5(pbVar2);
                    }
                    goto LAB_end;
                }
esc_common:
                pbVar6 = pbVar12 + 1;
                iVar5 = 2;
                pbVar10 = pbVar10 + iVar5;
store_common:
                *pbVar12 = bVar7;
                pbVar12 = pbVar6;
                continue;
            } else {
                pbVar10 = pbVar10 + 1;
                pbVar6 = pbVar12 + 1;
                *pbVar12 = bVar7;
                pbVar12 = pbVar6;
                continue;
            }
        }
    }
LAB_end:
    /* Raw 0x0006446c is this function's internal failure/cleanup island,
     * not a separately callable owner. All paths reaching LAB_end fail. */
    return 0;
}
