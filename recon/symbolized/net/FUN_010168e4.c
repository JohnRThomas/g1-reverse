#include "g1_net_symbols.h"
/* net-core FUN_010168e4 @ 0x10168e4  (parity 300 trials PROVEN) */
extern int FUN_01008d00(int,int);
extern int FUN_0100aa3c(int,int,int,int);
extern int FUN_0100aaac(int,int);
extern int FUN_0100bc04(int);
extern int FUN_0100ca68(int);
extern int FUN_01016828(void);
extern int FUN_01019750(int,int,int,int,int,int,int);
extern int FUN_01020500(void);

#define IVAR9 0x21000f90u
#define P14 ((volatile signed char*)((unsigned long)&g_net_ble_pending_channel_idx) /*=0x2100001c*/)
#define G(off) (*(volatile unsigned char*)(IVAR9+(off)))
#define GS(off) (*(volatile signed char*)(IVAR9+(off)))

int FUN_010168e4(int param_1, int param_2)
{
    switch (param_2) {
    case 0: {
        if (G(0x82) != 0) {
            signed char cVar3 = GS(0x54);
            if (cVar3 == 2) {
                signed char c14 = *P14;
                if (c14 != 0x7f) {
                    *P14 = 0x7f;
                    FUN_01019750(0,0,0,0,0,0,0);
                    G(0xa8) = 1;
                    return 0xb;
                }
            } else {
                if (cVar3 != 1) {
                    if (cVar3 != 3) {
                        return FUN_01008d00(0x32,0xed2);
                    }
                    {
                        volatile unsigned char *pc = (volatile unsigned char*)(*(volatile int*)(param_1+4));
                        if (pc[0]==G(0x5c) && pc[1]==G(0x5d) && pc[2]==G(0x5e) &&
                            pc[3]==G(0x5f) && pc[4]==G(0x60) && pc[5]==G(0x61) &&
                            *(volatile unsigned char*)(param_1+0x11)==G(0x5b)) {
                            return 0xc;
                        }
                        if (G(0x56)==1) return 0xc;
                        if (G(0x7b)!=8 && G(0x78)==G(0x7b)) return 0xc;
                    }
                    break;
                }
                {
                    signed char cc4 = *P14;
                    if (cc4 != 0x7f) {
                        *P14 = 0x7f;
                        FUN_01019750(0,0,0,0,0,0,0);
                        return 5;
                    }
                }
            }
            return FUN_01016828();
        }
        break;
    }
    case 1: {
        signed char cVar3 = GS(0x82);
        unsigned int uVar11 = (unsigned int)(G(0x7d) ^ 1);
        int bVar13;
        int iVar8;
        unsigned char bVar7, bVar12;
        if (*(volatile unsigned char*)(param_1+0x12)==1 &&
            (*(volatile unsigned char*)((*(volatile int*)(param_1+8))+5) & 0xc0)==0x40) {
            bVar13 = 1;
        } else bVar13 = 0;
        iVar8 = FUN_0100ca68(0);
        if (iVar8 == 0) {
            bVar7 = G(0x45);
            bVar12 = bVar7;
        } else {
            unsigned int uVar5 = (unsigned int)FUN_0100bc04(0);
            if (uVar5 != 0) uVar11 = uVar5;
            if (!bVar13) {
                iVar8 = 0;
                bVar7 = G(0x45);
                bVar12 = bVar7;
            } else {
                iVar8 = FUN_0100aaac(0,0);
                bVar7 = G(0x45);
                bVar12 = bVar7;
                if (iVar8 != 0) bVar12 = bVar7 | 2;
            }
        }
        if (GS(0x54) != 3) {
            FUN_01020500();
            if (cVar3 == 0) return 5;
            {
                int iVar6 = FUN_0100aa3c(0,0,0,0);
                if (iVar6==0 && iVar8==0) {
                    if ((unsigned char)(G(0x55)-2) > 1) return 5;
                    if (!bVar13) return 5;
                    {
                        signed char c14 = *P14;
                        if (c14 != 0x7f) {
                            *P14 = 0x7f;
                            FUN_01019750(0,0,0,0,0,0,0);
                            return 5;
                        }
                    }
                } else {
                    signed char c14 = *P14;
                    if (c14 != 0x7f) {
                        *P14 = 0x7f;
                        FUN_01019750(0,0,0,0,0,0,0);
                        return 5;
                    }
                }
            }
            return FUN_01016828();
        }
        {
            volatile unsigned char *pc = (volatile unsigned char*)(*(volatile int*)(param_1+4));
            int b2;
            if (pc[0]==G(0x5c) && pc[1]==G(0x5d) && pc[2]==G(0x5e) && pc[3]==G(0x5f) &&
                pc[4]==G(0x60) && pc[5]==G(0x61)) {
                b2 = (*(volatile unsigned char*)(param_1+0x11) == G(0x5b));
            } else b2 = 0;
            if (G(0x78) != 8 && G(0x7b) == G(0x78)) b2 = 1;
            if (iVar8 == 0) {
                if (uVar11 != 0) {
                    uVar11 = (unsigned int)FUN_0100aa3c(0,0,0,0);
                }
            } else {
                uVar11 = 1;
            }
            if (cVar3 != 0 &&
                ((G(0x56)==1 || (G(0x56)==0 && b2)) && uVar11 != 0)) {
                return 0xc;
            }
        }
        break;
    }
    case 2: {
        FUN_01020500();
        if (G(0x82) == 0) return 5;
        if ((unsigned char)(G(0x54)-1) > 1) return 5;
        {
            signed char c14 = *P14;
            if (c14 != 0x7f) {
                *P14 = 0x7f;
                FUN_01019750(0,0,0,0,0,0,0);
                return 5;
            }
        }
        return FUN_01016828();
    }
    case 6: {
        if (G(0x82) != 0) {
            if (G(0x54) == 2) {
                signed char c14 = *P14;
                if (c14 != 0x7f) {
                    *P14 = 0x7f;
                    FUN_01019750(0,0,0,0,0,0,0);
                    G(0xa8) = 0;
                    return 0xb;
                }
            } else {
                if (G(0x54) != 1) break;
                {
                    signed char c14 = *P14;
                    if (c14 != 0x7f) {
                        *P14 = 0x7f;
                        FUN_01019750(0,0,0,0,0,0,0);
                        return 5;
                    }
                }
            }
            return FUN_01016828();
        }
        break;
    }
    }
    FUN_01020500();
    return 5;
}
