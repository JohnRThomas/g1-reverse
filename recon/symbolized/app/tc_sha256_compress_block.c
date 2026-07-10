#include "g1_app_symbols.h"
/* named: tc_sha256_compress_block */
/* Reconstructed tc_sha256_compress_block @ 0x4fadc  (parity: 300/300 trials, PROVEN) */
void tc_sha256_compress_block(unsigned *param_1, int param_2)
{
    unsigned uVar1, uVar2, uVar3, uVar4, uVar5, uVar6, uVar7, uVar8, uVar9;
    unsigned uVar10, uVar11, uVar12, uVar13, uVar14, uVar15, uVar17, uVar20, uVar21, uVar22, uVar23;
    unsigned local_98, local_94;
    int iVar16, iVar18;
    const unsigned *piVar19;
    const unsigned *local_6c;
    unsigned local_68[17];

    iVar16 = 0;
    uVar2 = param_1[0]; uVar3 = param_1[1]; uVar4 = param_1[2]; uVar5 = param_1[3];
    uVar6 = param_1[4]; uVar7 = param_1[5]; uVar8 = param_1[6]; uVar9 = param_1[7];
    uVar14 = uVar6; uVar10 = uVar2; uVar12 = uVar3; uVar17 = uVar9;
    piVar19 = (const unsigned *)((uintptr_t)&tbl_8af10) /*=0x8af10*/;
    uVar13 = uVar4; uVar11 = uVar7; uVar23 = uVar5; uVar1 = uVar8;
    do {
        local_94 = uVar1;
        uVar1 = uVar11;
        uVar21 = uVar13;
        uVar13 = uVar12;
        uVar12 = uVar10;
        uVar11 = uVar14;
        uVar14 = *(unsigned *)(param_2 + iVar16);
        uVar14 = uVar14 << 0x18 | (uVar14 >> 8 & 0xff) << 0x10 | (uVar14 >> 0x10 & 0xff) << 8 |
                 uVar14 >> 0x18;
        iVar18 = (int)*piVar19;
        *(unsigned *)((int)local_68 + iVar16) = uVar14;
        iVar18 = ((uVar11 >> 0xb | uVar11 << 0x15) ^ (uVar11 >> 6 | uVar11 << 0x1a) ^
                 (uVar11 >> 0x19 | uVar11 << 7)) + iVar18 + uVar14 +
                 (local_94 & ~uVar11 ^ uVar11 & uVar1) + uVar17;
        iVar16 = iVar16 + 4;
        uVar14 = iVar18 + uVar23;
        uVar10 = iVar18 + ((uVar12 >> 0xd | uVar12 << 0x13) ^ (uVar12 >> 2 | uVar12 << 0x1e) ^
                          (uVar12 >> 0x16 | uVar12 << 10)) +
                          ((uVar13 ^ uVar21) & uVar12 ^ uVar13 & uVar21);
        uVar17 = local_94;
        piVar19 = piVar19 + 1;
        uVar23 = uVar21;
    } while (iVar16 != 0x40);

    local_6c = (const unsigned *)((uintptr_t)&tbl_8af10) /*=0x8af4c*/;
    uVar17 = 0x10;
    do {
        local_98 = uVar10;
        uVar22 = uVar1;
        uVar15 = uVar13;
        uVar23 = uVar14;
        uVar13 = uVar12;
        uVar1 = uVar11;
        uVar20 = uVar17 + 1;
        uVar11 = local_68[uVar20 & 0xf];
        uVar14 = local_68[uVar17 + 0xe & 0xf];
        uVar11 = local_68[uVar17 + 9 & 0xf] + local_68[uVar17 & 0xf] +
                 ((uVar11 >> 0x12 | uVar11 << 0xe) ^ (uVar11 >> 7 | uVar11 << 0x19) ^ uVar11 >> 3) +
                 ((uVar14 >> 0x13 | uVar14 << 0xd) ^ (uVar14 >> 0x11 | uVar14 << 0xf) ^ uVar14 >> 10);
        local_6c = local_6c + 1;
        iVar16 = (int)*local_6c;
        local_68[uVar17 & 0xf] = uVar11;
        iVar16 = local_94 +
                 (uVar22 & ~uVar23 ^ uVar23 & uVar1) +
                 ((uVar23 >> 0xb | uVar23 << 0x15) ^ (uVar23 >> 6 | uVar23 << 0x1a) ^
                 (uVar23 >> 0x19 | uVar23 << 7)) + iVar16 + uVar11;
        uVar14 = iVar16 + uVar21;
        uVar10 = ((uVar13 ^ uVar15) & local_98 ^ uVar13 & uVar15) +
                 ((local_98 >> 0xd | local_98 << 0x13) ^ (local_98 >> 2 | local_98 << 0x1e) ^
                 (local_98 >> 0x16 | local_98 << 10)) + iVar16;
        uVar11 = uVar23;
        uVar12 = local_98;
        uVar17 = uVar20;
        uVar21 = uVar15;
        local_94 = uVar22;
    } while (uVar20 != 0x40);

    param_1[0] = uVar2 + uVar10;
    param_1[1] = uVar3 + local_98;
    param_1[2] = uVar4 + uVar13;
    param_1[3] = uVar5 + uVar15;
    param_1[4] = uVar6 + uVar14;
    param_1[5] = uVar7 + uVar23;
    param_1[6] = uVar8 + uVar1;
    param_1[7] = uVar9 + uVar22;
}

