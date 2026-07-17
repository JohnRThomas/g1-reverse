#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000873b6 @ 0x000873b6
 * public-name: bignum_parse_hex_literal
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   hex_nibble_from_ascii                    <= FUN_00087340 @ 0x00087340
 *   bignum_limbs_merge_shift_left            <= FUN_0008736a @ 0x0008736a
 *   bignum_parse_hex_literal                 <= FUN_000873b6 @ 0x000873b6
 */
/* Reconstructed FUN_000873b6 @ 0x873b6  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int hex_nibble_from_ascii(int);
extern int bignum_limbs_merge_shift_left(int,int,int);
typedef volatile unsigned int VU;

unsigned int bignum_parse_hex_literal(int *param_1, unsigned int *param_2, unsigned int *param_3)
{
    unsigned char bVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    int iVar4;
    VU *puVar5;
    unsigned int uVar6;
    int iVar7;
    VU *puVar8;
    VU *puVar10;
    VU *puVar11;
    int iVar12;
    VU *puVar13;
    int iVar14;
    int local_38;
    VU *puVar9;

    iVar4 = *param_1;
    uVar6 = *param_2 & 0x1f;
    iVar12 = 0;
    puVar10 = (VU *)(param_3 + ((int)*param_2 >> 5));
    iVar14 = 0;
    if (uVar6 != 0) {
        puVar10 = puVar10 + 1;
    }
    local_38 = 0;
    puVar13 = puVar10 + -1;
    puVar10[-1] = 0;
    puVar11 = puVar13;
    puVar5 = puVar13;
LAB_000873e6:
    while (1) {
        iVar7 = iVar4 + 1;
        bVar1 = *(unsigned char *)(iVar4 + 1);
        if (bVar1 == 0) break;
        uVar2 = hex_nibble_from_ascii(bVar1);
        if (uVar2 != 0) {
            iVar12 = iVar12 + 1;
            iVar14 = iVar14 + 1;
            if (8 < iVar12) goto code_r0x000874aa;
            goto LAB_000874b6;
        }
        if (0x20 < bVar1) {
            if (bVar1 != 0x29) goto LAB_000874e8;
            *param_1 = iVar4 + 2;
            break;
        }
        iVar4 = iVar7;
        if (local_38 < iVar14) {
            if ((puVar11 < puVar5) && (iVar12 < 8)) {
                bignum_limbs_merge_shift_left((int)puVar11, (int)puVar5, iVar12);
            }
            if (param_3 < (unsigned int *)puVar11) {
                puVar5 = puVar11 + -1;
                puVar11[-1] = 0;
                iVar12 = 0;
                puVar11 = puVar5;
                local_38 = iVar14;
            } else {
                iVar12 = 8;
            }
        }
    }
    if (iVar14 == 0) {
LAB_000874e8:
        uVar3 = 4;
    } else {
        if ((puVar11 < puVar5) && (iVar12 < 8)) {
            bignum_limbs_merge_shift_left((int)puVar11, (int)puVar5, iVar12);
        }
        if (param_3 < (unsigned int *)puVar11) {
            puVar5 = (VU *)(param_3 + -1);
            puVar8 = puVar11;
            do {
                puVar9 = puVar8 + 1;
                puVar5 = puVar5 + 1;
                *puVar5 = *puVar8;
                puVar8 = puVar9;
            } while (puVar9 <= puVar13);
            iVar4 = ((int)puVar13 - (int)puVar11 & 0xfffffffcU) + 4;
            if ((int)puVar10 - 3U < (int)puVar11 + 1U) {
                iVar4 = 4;
            }
            puVar10 = (VU *)(iVar4 + (int)param_3);
            do {
                puVar11 = puVar10 + 1;
                *puVar10 = 0;
                puVar10 = puVar11;
            } while (puVar11 <= puVar13);
        } else if (uVar6 != 0) {
            puVar10[-1] = puVar10[-1] & 0xffffffffU >> (0x20 - uVar6 & 0xff);
        }
        for (; *puVar13 == 0; puVar13 = puVar13 + -1) {
            if (puVar13 == (VU *)param_3) {
                *puVar13 = 1;
                break;
            }
        }
        uVar3 = 5;
    }
    return uVar3;
code_r0x000874aa:
    iVar4 = iVar7;
    if (param_3 < (unsigned int *)puVar11) {
        puVar11 = puVar11 + -1;
        iVar12 = 1;
        *puVar11 = 0;
LAB_000874b6:
        *puVar11 = (uVar2 & 0xf) | *puVar11 << 4;
        iVar4 = iVar7;
    }
    goto LAB_000873e6;
}
