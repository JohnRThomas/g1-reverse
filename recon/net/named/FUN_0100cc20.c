/* readable reconstruction; identity: FUN_0100cc20 @ 0x0100cc20
 * public-name: FUN_0100cc20
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_buffer_is_zero                <= FUN_0100d2c8 @ 0x0100d2c8
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core FUN_0100cc20 @ 0x100cc20  (parity 300 trials PROVEN) */
extern int controller_buffer_is_zero(unsigned char *a0, unsigned int a1);
extern void FUN_01025a84(void *a0, unsigned int a1);

int FUN_0100cc20(unsigned int param_1, unsigned char *param_2, unsigned int param_3)
{
    volatile unsigned char *D = (volatile unsigned char *)0x21000d18;
    unsigned char bVar1, bVar2, bVar3, bVar4, bVar6, bVar7;
    signed char cVar9;
    int iVar8;

    iVar8 = controller_buffer_is_zero(param_2, 6);
    if (iVar8 == 0) {
        cVar9 = (signed char)D[0];
        if (cVar9 != 0) {
            bVar1 = param_2[0];
            bVar6 = param_2[1];
            bVar7 = param_2[2];
            bVar2 = param_2[3];
            bVar3 = param_2[4];
            bVar4 = param_2[5];
            if ((unsigned int)(unsigned char)(bVar4 ^ D[0x158]) +
                (unsigned int)(unsigned char)(bVar3 ^ D[0x157]) +
                (unsigned int)(unsigned char)(bVar2 ^ D[0x156]) +
                (unsigned int)(unsigned char)(bVar6 ^ D[0x154]) + (unsigned int)(unsigned char)(D[0x153] ^ bVar1) +
                ((unsigned char)D[0x152] ^ param_1) + (unsigned int)(unsigned char)(bVar7 ^ D[0x155]) == 0) {
                cVar9 = 0;
            } else {
                if (cVar9 == 1) return 0;
                if ((unsigned int)(unsigned char)(bVar4 ^ D[0x15f]) +
                    (unsigned int)(unsigned char)(bVar3 ^ D[0x15e]) +
                    (unsigned int)(unsigned char)(bVar7 ^ D[0x15c]) +
                    (unsigned int)(unsigned char)(bVar1 ^ D[0x15a]) + (unsigned int)(unsigned char)(bVar6 ^ D[0x15b]) +
                    (param_1 ^ (unsigned char)D[0x159]) + (unsigned int)(unsigned char)(bVar2 ^ D[0x15d]) == 0) {
                    cVar9 = 1;
                } else {
                    if (cVar9 == 2) return 0;
                    if ((unsigned int)(unsigned char)(bVar4 ^ D[0x166]) +
                        (unsigned int)(unsigned char)(bVar3 ^ D[0x165]) +
                        (unsigned int)(unsigned char)(bVar7 ^ D[0x163]) +
                        (unsigned int)(unsigned char)(bVar1 ^ D[0x161]) + (unsigned int)(unsigned char)(bVar6 ^ D[0x162])
                        + (param_1 ^ (unsigned char)D[0x160]) + (unsigned int)(unsigned char)(bVar2 ^ D[0x164]) == 0) {
                        cVar9 = 2;
                    } else {
                        if (cVar9 == 3) return 0;
                        if ((unsigned int)(unsigned char)(bVar4 ^ D[0x16d]) +
                            (unsigned int)(unsigned char)(bVar3 ^ D[0x16c]) +
                            (unsigned int)(unsigned char)(bVar7 ^ D[0x16a]) +
                            (unsigned int)(unsigned char)(bVar1 ^ D[0x168]) +
                            (unsigned int)(unsigned char)(bVar6 ^ D[0x169]) + (param_1 ^ (unsigned char)D[0x167]) +
                            (unsigned int)(unsigned char)(bVar2 ^ D[0x16b]) == 0) {
                            cVar9 = 3;
                        } else {
                            if (cVar9 == 4) return 0;
                            if ((unsigned int)(unsigned char)(bVar4 ^ D[0x174]) +
                                (unsigned int)(unsigned char)(bVar3 ^ D[0x173]) +
                                (unsigned int)(unsigned char)(bVar7 ^ D[0x171]) +
                                (unsigned int)(unsigned char)(bVar1 ^ D[0x16f]) +
                                (unsigned int)(unsigned char)(bVar6 ^ D[0x170]) + (param_1 ^ (unsigned char)D[0x16e])
                                + (unsigned int)(unsigned char)(bVar2 ^ D[0x172]) == 0) {
                                cVar9 = 4;
                            } else {
                                if (cVar9 == 5) return 0;
                                if ((unsigned int)(unsigned char)(bVar4 ^ D[0x17b]) +
                                    (unsigned int)(unsigned char)(bVar3 ^ D[0x17a]) +
                                    (unsigned int)(unsigned char)(bVar7 ^ D[0x178]) +
                                    (unsigned int)(unsigned char)(bVar1 ^ D[0x176]) +
                                    (unsigned int)(unsigned char)(bVar6 ^ D[0x177]) +
                                    (param_1 ^ (unsigned char)D[0x175]) +
                                    (unsigned int)(unsigned char)(bVar2 ^ D[0x179]) == 0) {
                                    cVar9 = 5;
                                } else {
                                    if (cVar9 == 6) return 0;
                                    if ((unsigned int)(unsigned char)(bVar4 ^ D[0x182]) +
                                        (unsigned int)(unsigned char)(bVar3 ^ D[0x181]) +
                                        (unsigned int)(unsigned char)(bVar7 ^ D[0x17f]) +
                                        (unsigned int)(unsigned char)(bVar1 ^ D[0x17d]) +
                                        (unsigned int)(unsigned char)(bVar6 ^ D[0x17e]) +
                                        (param_1 ^ (unsigned char)D[0x17c]) +
                                        (unsigned int)(unsigned char)(bVar2 ^ D[0x180]) == 0) {
                                        cVar9 = 6;
                                    } else {
                                        if (cVar9 == 7) return 0;
                                        if ((unsigned int)(unsigned char)(bVar4 ^ D[0x189]) +
                                            (unsigned int)(unsigned char)(bVar3 ^ D[0x188]) +
                                            (unsigned int)(unsigned char)(bVar2 ^ D[0x187]) +
                                            (param_1 ^ (unsigned char)D[0x183]) +
                                            (unsigned int)(unsigned char)(bVar1 ^ D[0x184]) +
                                            (unsigned int)(unsigned char)(bVar6 ^ D[0x185]) +
                                            (unsigned int)(unsigned char)(bVar7 ^ D[0x186]) != 0) {
                                            return 0;
                                        }
                                        cVar9 = 7;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            {
                char cVar5 = (char)D[1];
                if (cVar5 != 0) {
                    if (D[0x102] == (unsigned char)cVar9) {
                        iVar8 = 0;
                    } else {
                        if (cVar5 == 1) return 0;
                        if (D[0x103] == (unsigned char)cVar9) {
                            iVar8 = 1;
                        } else {
                            if (cVar5 == 2) return 0;
                            if (D[0x104] == (unsigned char)cVar9) {
                                iVar8 = 2;
                            } else {
                                if (cVar5 == 3) return 0;
                                if (D[0x105] == (unsigned char)cVar9) {
                                    iVar8 = 3;
                                } else {
                                    if (cVar5 == 4) return 0;
                                    if (D[0x106] == (unsigned char)cVar9) {
                                        iVar8 = 4;
                                    } else {
                                        if (cVar5 == 5) return 0;
                                        if (D[0x107] == (unsigned char)cVar9) {
                                            iVar8 = 5;
                                        } else {
                                            if (cVar5 == 6) return 0;
                                            if (D[0x108] == (unsigned char)cVar9) {
                                                iVar8 = 6;
                                            } else {
                                                if (cVar5 == 7) return 0;
                                                if (D[0x109] != (unsigned char)cVar9) return 0;
                                                iVar8 = 7;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    D[iVar8 + 0x13a] = (unsigned char)param_3;
                    return 1;
                }
            }
        }
    } else if (D[1] != 0) {
        FUN_01025a84((void *)(D + 0x13a), param_3);
    }
    return iVar8;
}
