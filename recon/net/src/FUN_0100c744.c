/* net-core FUN_0100c744 @ 0x100c744  (parity 300 trials PROVEN) */
unsigned int FUN_0100c744(unsigned int param_1, unsigned char *param_2)
{
    volatile unsigned char *D = (volatile unsigned char *)0x21000d18;
    unsigned char bVar1, bVar2, bVar3, bVar4, bVar6, bVar7;
    char cVar5;
    signed char cVar8;
    unsigned int uVar9;

    cVar8 = (signed char)D[0];
    if (cVar8 != 0) {
        bVar6 = param_2[0];
        bVar1 = param_2[1];
        bVar2 = param_2[2];
        bVar7 = param_2[4];
        bVar3 = param_2[3];
        bVar4 = param_2[5];
        if ((unsigned int)(unsigned char)(D[0x158] ^ bVar4) +
            (unsigned int)(unsigned char)(bVar7 ^ D[0x157]) +
            (unsigned int)(unsigned char)(bVar3 ^ D[0x156]) +
            (unsigned int)(unsigned char)(D[0x154] ^ bVar1) + (unsigned int)(unsigned char)(bVar6 ^ D[0x153]) +
            ((unsigned char)D[0x152] ^ param_1) + (unsigned int)(unsigned char)(bVar2 ^ D[0x155]) == 0) {
            cVar8 = 0;
        } else {
            if (cVar8 == 1) return 8;
            if ((unsigned int)(unsigned char)(bVar4 ^ D[0x15f]) +
                (unsigned int)(unsigned char)(bVar7 ^ D[0x15e]) +
                (unsigned int)(unsigned char)(bVar2 ^ D[0x15c]) +
                (unsigned int)(unsigned char)(D[0x15b] ^ bVar1) + (unsigned int)(unsigned char)(bVar6 ^ D[0x15a]) +
                (param_1 ^ (unsigned char)D[0x159]) + (unsigned int)(unsigned char)(D[0x15d] ^ bVar3) == 0) {
                cVar8 = 1;
            } else {
                if (cVar8 == 2) return 8;
                if ((unsigned int)(unsigned char)(bVar4 ^ D[0x166]) +
                    (unsigned int)(unsigned char)(bVar7 ^ D[0x165]) +
                    (unsigned int)(unsigned char)(bVar2 ^ D[0x163]) +
                    (unsigned int)(unsigned char)(bVar6 ^ D[0x161]) + (unsigned int)(unsigned char)(bVar1 ^ D[0x162]) +
                    (param_1 ^ (unsigned char)D[0x160]) + (unsigned int)(unsigned char)(D[0x164] ^ bVar3) == 0) {
                    cVar8 = 2;
                } else {
                    if (cVar8 == 3) return 8;
                    if ((unsigned int)(unsigned char)(bVar4 ^ D[0x16d]) +
                        (unsigned int)(unsigned char)(bVar7 ^ D[0x16c]) +
                        (unsigned int)(unsigned char)(bVar2 ^ D[0x16a]) +
                        (unsigned int)(unsigned char)(bVar6 ^ D[0x168]) + (unsigned int)(unsigned char)(bVar1 ^ D[0x169])
                        + (param_1 ^ (unsigned char)D[0x167]) + (unsigned int)(unsigned char)(D[0x16b] ^ bVar3) == 0) {
                        cVar8 = 3;
                    } else {
                        if (cVar8 == 4) return 8;
                        if ((unsigned int)(unsigned char)(bVar4 ^ D[0x174]) +
                            (unsigned int)(unsigned char)(bVar7 ^ D[0x173]) +
                            (unsigned int)(unsigned char)(bVar2 ^ D[0x171]) +
                            (unsigned int)(unsigned char)(bVar6 ^ D[0x16f]) +
                            (unsigned int)(unsigned char)(bVar1 ^ D[0x170]) + (param_1 ^ (unsigned char)D[0x16e]) +
                            (unsigned int)(unsigned char)(D[0x172] ^ bVar3) == 0) {
                            cVar8 = 4;
                        } else {
                            if (cVar8 == 5) return 8;
                            if ((unsigned int)(unsigned char)(bVar4 ^ D[0x17b]) +
                                (unsigned int)(unsigned char)(bVar7 ^ D[0x17a]) +
                                (unsigned int)(unsigned char)(bVar2 ^ D[0x178]) +
                                (unsigned int)(unsigned char)(bVar6 ^ D[0x176]) +
                                (unsigned int)(unsigned char)(bVar1 ^ D[0x177]) + (param_1 ^ (unsigned char)D[0x175])
                                + (unsigned int)(unsigned char)(D[0x179] ^ bVar3) == 0) {
                                cVar8 = 5;
                            } else {
                                if (cVar8 == 6) return 8;
                                if ((unsigned int)(unsigned char)(bVar4 ^ D[0x182]) +
                                    (unsigned int)(unsigned char)(bVar7 ^ D[0x181]) +
                                    (unsigned int)(unsigned char)(bVar2 ^ D[0x17f]) +
                                    (unsigned int)(unsigned char)(bVar6 ^ D[0x17d]) +
                                    (unsigned int)(unsigned char)(bVar1 ^ D[0x17e]) +
                                    (param_1 ^ (unsigned char)D[0x17c]) +
                                    (unsigned int)(unsigned char)(D[0x180] ^ bVar3) == 0) {
                                    cVar8 = 6;
                                } else {
                                    if (cVar8 == 7) return 8;
                                    if ((unsigned int)(unsigned char)(bVar4 ^ D[0x189]) +
                                        (unsigned int)(unsigned char)(bVar7 ^ D[0x188]) +
                                        (param_1 ^ (unsigned char)D[0x183]) +
                                        (unsigned int)(unsigned char)(bVar6 ^ D[0x184]) +
                                        (unsigned int)(unsigned char)(bVar1 ^ D[0x185]) +
                                        (unsigned int)(unsigned char)(bVar2 ^ D[0x186]) +
                                        (unsigned int)(unsigned char)(bVar3 ^ D[0x187]) != 0) {
                                        return 8;
                                    }
                                    cVar8 = 7;
                                }
                            }
                        }
                    }
                }
            }
        }
        cVar5 = (char)D[1];
        if (cVar5 != 0) {
            if ((char)D[0x102] == cVar8) return 0;
            if (cVar5 != 1) {
                if ((char)D[0x103] == cVar8) return 1;
                if (cVar5 != 2) {
                    if ((char)D[0x104] == cVar8) return 2;
                    if (cVar5 != 3) {
                        if ((char)D[0x105] == cVar8) return 3;
                        if (cVar5 != 4) {
                            if ((char)D[0x106] == cVar8) return 4;
                            if (cVar5 != 5) {
                                if ((char)D[0x107] == cVar8) return 5;
                                if (cVar5 != 6) {
                                    if ((char)D[0x108] == cVar8) return 6;
                                    if (cVar5 != 7) {
                                        if ((char)D[0x109] == cVar8) {
                                            uVar9 = 7;
                                        } else {
                                            uVar9 = 8;
                                        }
                                        return uVar9;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 8;
}

