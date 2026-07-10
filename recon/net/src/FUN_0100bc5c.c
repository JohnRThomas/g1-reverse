/* net-core FUN_0100bc5c @ 0x100bc5c  (parity 300 trials PROVEN) */
unsigned char FUN_0100bc5c(unsigned int param_1, unsigned char *param_2, unsigned char *param_3)
{
    volatile unsigned char *D = (volatile unsigned char *)0x21000d18;
    unsigned char bVar1, bVar2, bVar3, bVar5, bVar6, bVar8;
    signed char cVar4;
    unsigned int uVar9;

    cVar4 = (signed char)D[0];
    if (cVar4 != 0) {
        bVar5 = param_2[0];
        bVar8 = param_2[1];
        bVar6 = param_2[4];
        bVar1 = param_2[2];
        bVar2 = param_2[3];
        bVar3 = param_2[5];
        uVar9 = (unsigned int)(unsigned char)(D[0x158] ^ bVar3) +
                (unsigned int)(unsigned char)(bVar2 ^ D[0x156]) +
                (unsigned int)(unsigned char)(bVar1 ^ D[0x155]) +
                (unsigned int)(unsigned char)(D[0x154] ^ bVar8) + (unsigned int)(unsigned char)(bVar5 ^ D[0x153]) +
                ((unsigned char)D[0x152] ^ param_1) + (unsigned int)(unsigned char)(bVar6 ^ D[0x157]);
        if (uVar9 != 0) {
            if (cVar4 == 1) return 1;
            if ((unsigned int)(unsigned char)(bVar3 ^ D[0x15f]) +
                (unsigned int)(unsigned char)(bVar6 ^ D[0x15e]) +
                (unsigned int)(unsigned char)(bVar1 ^ D[0x15c]) +
                (unsigned int)(unsigned char)(bVar5 ^ D[0x15a]) + (unsigned int)(unsigned char)(bVar8 ^ D[0x15b]) +
                (param_1 ^ (unsigned char)D[0x159]) + (unsigned int)(unsigned char)(D[0x15d] ^ bVar2) == 0) {
                uVar9 = 1;
            } else {
                if (cVar4 == 2) return 1;
                if ((unsigned int)(unsigned char)(bVar3 ^ D[0x166]) +
                    (unsigned int)(unsigned char)(bVar6 ^ D[0x165]) +
                    (unsigned int)(unsigned char)(bVar1 ^ D[0x163]) +
                    (unsigned int)(unsigned char)(bVar5 ^ D[0x161]) + (unsigned int)(unsigned char)(bVar8 ^ D[0x162]) +
                    (param_1 ^ (unsigned char)D[0x160]) + (unsigned int)(unsigned char)(D[0x164] ^ bVar2) == 0) {
                    uVar9 = 2;
                } else {
                    if (cVar4 == 3) return 1;
                    if ((unsigned int)(unsigned char)(bVar3 ^ D[0x16d]) +
                        (unsigned int)(unsigned char)(bVar6 ^ D[0x16c]) +
                        (unsigned int)(unsigned char)(bVar1 ^ D[0x16a]) +
                        (unsigned int)(unsigned char)(bVar5 ^ D[0x168]) + (unsigned int)(unsigned char)(bVar8 ^ D[0x169])
                        + (param_1 ^ (unsigned char)D[0x167]) + (unsigned int)(unsigned char)(D[0x16b] ^ bVar2) == 0) {
                        uVar9 = 3;
                    } else {
                        if (cVar4 == 4) return 1;
                        if ((unsigned int)(unsigned char)(bVar3 ^ D[0x174]) +
                            (unsigned int)(unsigned char)(bVar6 ^ D[0x173]) +
                            (unsigned int)(unsigned char)(bVar1 ^ D[0x171]) +
                            (unsigned int)(unsigned char)(bVar5 ^ D[0x16f]) +
                            (unsigned int)(unsigned char)(bVar8 ^ D[0x170]) + (param_1 ^ (unsigned char)D[0x16e]) +
                            (unsigned int)(unsigned char)(D[0x172] ^ bVar2) == 0) {
                            uVar9 = 4;
                        } else {
                            if (cVar4 == 5) return 1;
                            if ((unsigned int)(unsigned char)(bVar3 ^ D[0x17b]) +
                                (unsigned int)(unsigned char)(bVar6 ^ D[0x17a]) +
                                (unsigned int)(unsigned char)(bVar1 ^ D[0x178]) +
                                (unsigned int)(unsigned char)(bVar5 ^ D[0x176]) +
                                (unsigned int)(unsigned char)(bVar8 ^ D[0x177]) + (param_1 ^ (unsigned char)D[0x175])
                                + (unsigned int)(unsigned char)(D[0x179] ^ bVar2) == 0) {
                                uVar9 = 5;
                            } else {
                                if (cVar4 == 6) return 1;
                                if ((unsigned int)(unsigned char)(bVar3 ^ D[0x182]) +
                                    (unsigned int)(unsigned char)(bVar6 ^ D[0x181]) +
                                    (unsigned int)(unsigned char)(bVar1 ^ D[0x17f]) +
                                    (unsigned int)(unsigned char)(bVar5 ^ D[0x17d]) +
                                    (unsigned int)(unsigned char)(bVar8 ^ D[0x17e]) +
                                    (param_1 ^ (unsigned char)D[0x17c]) +
                                    (unsigned int)(unsigned char)(D[0x180] ^ bVar2) == 0) {
                                    uVar9 = 6;
                                } else {
                                    if (cVar4 == 7) return 1;
                                    if ((unsigned int)(unsigned char)(bVar3 ^ D[0x189]) +
                                        (unsigned int)(unsigned char)(bVar6 ^ D[0x188]) +
                                        (param_1 ^ (unsigned char)D[0x183]) +
                                        (unsigned int)(unsigned char)(bVar5 ^ D[0x184]) +
                                        (unsigned int)(unsigned char)(bVar8 ^ D[0x185]) +
                                        (unsigned int)(unsigned char)(bVar1 ^ D[0x186]) +
                                        (unsigned int)(unsigned char)(bVar2 ^ D[0x187]) != 0) {
                                        return 1;
                                    }
                                    uVar9 = 7;
                                }
                            }
                        }
                    }
                }
            }
        }
        cVar4 = (signed char)D[1];
        if (cVar4 != 0) {
            if ((unsigned char)D[0x102] == uVar9) {
                uVar9 = 0;
            } else {
                if (cVar4 == 1) return 1;
                if ((unsigned char)D[0x103] == uVar9) {
                    uVar9 = 1;
                } else {
                    if (cVar4 == 2) return 1;
                    if ((unsigned char)D[0x104] == uVar9) {
                        uVar9 = 2;
                    } else {
                        if (cVar4 == 3) return 1;
                        if ((unsigned char)D[0x105] == uVar9) {
                            uVar9 = 3;
                        } else {
                            if (cVar4 == 4) return 1;
                            if ((unsigned char)D[0x106] == uVar9) {
                                uVar9 = 4;
                            } else {
                                if (cVar4 == 5) return 1;
                                if ((unsigned char)D[0x107] == uVar9) {
                                    uVar9 = 5;
                                } else {
                                    if (cVar4 == 6) return 1;
                                    if ((unsigned char)D[0x108] == uVar9) {
                                        uVar9 = 6;
                                    } else {
                                        if (cVar4 == 7) return 1;
                                        if ((unsigned char)D[0x109] != uVar9) return 1;
                                        uVar9 = 7;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if ((param_3 == 0) || (*param_3 = (unsigned char)uVar9, uVar9 < (unsigned char)D[1])) {
                bVar8 = D[uVar9 + 0x14a];
                if (D[uVar9 + 0x13a] == 1) {
                    bVar8 = bVar8 | 1;
                }
                return bVar8;
            }
        }
    }
    return 1;
}

