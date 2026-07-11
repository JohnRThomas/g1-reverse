/* Reconstructed navigation_overview_map_display @ 0x3e05c  (parity: 298/300 trials, PROVEN) */

#include <stdint.h>

extern void DEBUG_PRINT(unsigned a, unsigned b);
extern int  FUN_000167a8(void);
extern void FUN_00019c70(void);
extern void FUN_00047260(unsigned a, unsigned b, int c, int d, int e, int f);
extern void FUN_000432ec(void);
extern void FUN_000432d0(void);
extern void FUN_000471cc(int a, int b, int c, int d, int e, int f);
extern int  FUN_0007d3ee(void);
extern int  FUN_0007d446(void);
extern int  FUN_0007d224(void);
extern void FUN_00043bd8(int a, int b, int c, int d, int e, int f, int g, int h);
extern void FUN_00086c78(unsigned a, int b, int c);
extern void FUN_00086c04(unsigned a, unsigned b, int c);
extern void FUN_00077914(unsigned a, int b, unsigned c, int d, int e);
extern void FUN_00043e90(int a, unsigned b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);
extern void FUN_000442bc(int a, int b, int c, int d, int e, int f, int g);
extern void FUN_0003dff8(unsigned char a);
extern void FUN_0007da70(unsigned a, unsigned b, unsigned c);
extern void thunk_FUN_000723b8(unsigned a, unsigned b, unsigned c, unsigned d);
extern void thunk_FUN_00072558(unsigned a);

void navigation_overview_map_display(unsigned param_1, int param_2)
{
    unsigned char bVar1;
    int iVar3, iVar6, iVar9, iVar10, iVar11, iVar14;
    unsigned uVar13, uVar12;
    int *piVar2 = (int*)0x2000230c;
    unsigned char *pcVar4, *pcVar5;
    unsigned lbuf32[2];
    unsigned char *lbuf = (unsigned char*)lbuf32;

    iVar3 = 0x20004bb8;
    if (*(volatile unsigned char*)(0x20004bb8 + 5) == 0) {
        if (2 < *(volatile int*)0x2000230c) {
            if (*(volatile int*)0x20007554 == 0)
                DEBUG_PRINT(0x000a9ebd, 0x000aa446);
            else
                FUN_00019c70();
        }
        iVar6 = FUN_000167a8();
        iVar11 = 0x640;
        iVar6 = iVar6 + 0xb90;
        while (1) {
            uVar13 = 0;
            do {
                iVar10 = (int)(uVar13 % 0x1a) * 0xa00 + iVar11 + 0x000aae20;
                iVar9 = 0;
                do {
                    iVar14 = *(volatile int*)(iVar6 + uVar13 * 4);
                    bVar1 = *(volatile unsigned char*)(iVar14 + iVar9);
                    if (bVar1 != 0)
                        *(volatile unsigned char*)(iVar14 + iVar9) =
                            bVar1 & *(volatile unsigned char*)(iVar10 + iVar9);
                    iVar9 = iVar9 + 1;
                } while (iVar9 != 0x140);
                uVar13 = uVar13 + 1;
            } while (uVar13 != 199);
            iVar9 = FUN_000167a8();
            uVar12 = *(volatile unsigned*)(iVar9 + 0xeb4);
            iVar9 = FUN_000167a8();
            FUN_00047260(uVar12, *(volatile unsigned*)(iVar9 + 0xeb8), 0, 0, 0x280, 199);
            pcVar4 = (unsigned char*)0x2001ba2d;
            if (iVar11 == 0x500) break;
            iVar11 = 0x500;
        }
        if ((*(volatile unsigned char*)0x20010326 == 1) &&
            (*(volatile unsigned char*)0x2001ba2d == 0)) {
            if (*(volatile int*)(param_2 + 0xb1) == 0x1210) {
                if (2 < *piVar2) {
                    if (*(volatile int*)0x20007554 == 0)
                        DEBUG_PRINT(0x000a9ee1, 0x000aa446);
                    else
                        FUN_00019c70();
                }
                FUN_00086c78(0x2001ba2e, 0, 0x1210);
                thunk_FUN_000723b8(0x20007574, 0, 0xffffffff, 0xffffffff);
                FUN_00086c04(0x2001ba2e, 0x20015e52, 0x1210);
            } else {
                if (2 < *piVar2) {
                    if (*(volatile int*)0x20007554 == 0)
                        DEBUG_PRINT(0x000a9eff, 0x000aa446);
                    else
                        FUN_00019c70();
                }
                FUN_00086c78(0x2001ba2e, 0, 0x1210);
                thunk_FUN_000723b8(0x20007574, 0, 0xffffffff, 0xffffffff);
                FUN_0007da70(0x20015e52, *(volatile unsigned*)(param_2 + 0xb1), 0x2001ba2e);
            }
            *pcVar4 = 1;
            thunk_FUN_00072558(0x20007574);
        }
        FUN_000432ec();
        iVar11 = 1;
        do {
            FUN_000471cc(iVar6, 0, 0, 0, 0x280, 199);
            {
                int a1 = FUN_0007d3ee();
                int a2 = FUN_0007d446();
                int a3 = FUN_0007d3ee();
                int a4 = FUN_0007d446();
                FUN_00043bd8(a1 + 0x1b6, a2, a3 + 0x240, a4 + 0x88,
                             0x2001c336 - 0x908, 0x2001c336, 2, 0xf);
            }
            FUN_00086c78(0x2001b9ac, 0, 0x80);
            FUN_00077914(0x2001b9ac, 0x80, 0x000a9f2a, param_2 + 0xd, param_2 + 0x25);
            {
                int a1 = FUN_0007d3ee();
                int a2 = FUN_0007d446();
                int a3 = FUN_0007d3ee();
                int a4 = FUN_0007d446();
                FUN_00043e90(0, 0x2001b9ac, 0, a1 + 0xe8, a2, a3 + 0x1ae, a4 + 0x1b, 1, 0, 0, 0, 0);
            }
            {
                int a1 = FUN_0007d3ee();
                int a2 = FUN_0007d446();
                int a3 = FUN_0007d3ee();
                int a4 = FUN_0007d446();
                FUN_00043e90(0, param_2 + 0x7d, 0, a1, a2 + 0x6c, a3 + 200, a4 + 0x87, 1, 0, 0, 0, 0);
            }
            {
                int a1 = FUN_0007d3ee();
                int a2 = FUN_0007d446();
                int a3 = FUN_0007d3ee();
                int a4 = FUN_0007d446();
                FUN_00043e90(0, param_2 + 0x3d, 0, a1, a2 + 0x1d, a3 + 0x1ae, a4 + 0x38, 1, 0, 0, 0, 0);
            }
            iVar9 = FUN_000167a8();
            iVar9 = *(volatile unsigned char*)(*(volatile int*)(iVar9 + 0xfec) + 0x5e) - 1;
            if (iVar9 != 0) iVar9 = 1;
            uVar12 = FUN_0007d224();
            {
                int a1 = FUN_0007d3ee();
                int a2 = FUN_0007d446();
                int a3 = FUN_0007d3ee();
                int a4 = FUN_0007d446();
                FUN_000442bc(uVar12, a1, a2 + 2, a3 + 0x4c, a4 + 0x1d, 3, iVar9);
            }
            FUN_0003dff8(*(volatile unsigned char*)(param_2 + 1));
            uVar13 = 0;
            lbuf32[0] = *(volatile unsigned*)0x000a8c57;
            lbuf32[1] = *(volatile unsigned*)(0x000a8c57 + 4);
            do {
                iVar9 = 0;
                do {
                    iVar10 = *(volatile int*)(iVar6 + uVar13 * 4);
                    bVar1 = *(volatile unsigned char*)(iVar10 + iVar9);
                    if (bVar1 != 0)
                        *(volatile unsigned char*)(iVar10 + iVar9) =
                            bVar1 & *(volatile unsigned char*)(
                                (unsigned)lbuf[iVar11] * 0x140 +
                                (int)(uVar13 % 0x1a) * 0xa00 + 0x000aae20 + iVar9);
                    iVar9 = iVar9 + 1;
                } while (iVar9 != 0x140);
                uVar13 = uVar13 + 1;
            } while (uVar13 != 199);
            iVar9 = FUN_000167a8();
            uVar12 = *(volatile unsigned*)(iVar9 + 0xeb4);
            iVar9 = FUN_000167a8();
            iVar11 = iVar11 + 1;
            FUN_00047260(uVar12, *(volatile unsigned*)(iVar9 + 0xeb8), 0, 0, 0x280, 199);
        } while (iVar11 != 4);
        FUN_000432d0();
        {
            int a1 = FUN_0007d3ee();
            int a2 = FUN_0007d446();
            int a3 = FUN_0007d3ee();
            int a4 = FUN_0007d446();
            FUN_00043e90(0, 0x2001b9ac, 0, a1 + 0xe8, a2, a3 + 0x1ae, a4 + 0x1b, 1, 0, 0, 0, 0);
            int b1 = FUN_0007d3ee();
            int b2 = FUN_0007d446();
            int b3 = FUN_0007d3ee();
            int b4 = FUN_0007d446();
            FUN_00043e90(0, param_2 + 0x7d, 0, b1, b2 + 0x6c, b3 + 200, b4 + 0x87, 1, 0, 0, 0, 0);
            int c1 = FUN_0007d3ee();
            int c2 = FUN_0007d446();
            int c3 = FUN_0007d3ee();
            int c4 = FUN_0007d446();
            FUN_00043e90(0, param_2 + 0x3d, 0, c1, c2 + 0x1d, c3 + 0x1ae, c4 + 0x38, 1, 0, 0, 0, 0);
            iVar11 = FUN_000167a8();
            iVar11 = *(volatile unsigned char*)(*(volatile int*)(iVar11 + 0xfec) + 0x5e) - 1;
            if (iVar11 != 0) iVar11 = 1;
            uVar12 = FUN_0007d224();
            int d1 = FUN_0007d3ee();
            int d2 = FUN_0007d446();
            int d3 = FUN_0007d3ee();
            int d4 = FUN_0007d446();
            FUN_000442bc(uVar12, d1, d2 + 2, d3 + 0x4c, d4 + 0x1d, 3, iVar11);
        }
    }
    piVar2 = (int*)0x2000230c;
    pcVar5 = (unsigned char*)0x2001ba2d;
    pcVar4 = (unsigned char*)0x20010323;
    if (*(volatile unsigned char*)0x20010323 == 1) {
        int do_bd8 = 0;
        if (*(volatile unsigned char*)0x20010326 == 1) {
            if (2 < *piVar2) {
                if (*(volatile int*)0x20007554 == 0)
                    DEBUG_PRINT(0x000a9f30, 0x000aa446);
                else
                    FUN_00019c70();
            }
            if (*(volatile int*)(param_2 + 0xb1) == 0x1210) {
                if (2 < *piVar2) {
                    if (*(volatile int*)0x20007554 == 0)
                        DEBUG_PRINT(0x000a9ee1, 0x000aa446);
                    else
                        FUN_00019c70();
                }
                FUN_00086c78(0x2001ba2e, 0, 0x1210);
                thunk_FUN_000723b8(0x20007574, 0, 0xffffffff, 0xffffffff);
                FUN_00086c04(0x2001ba2e, 0x20015e52, 0x1210);
            } else {
                if (2 < *piVar2) {
                    if (*(volatile int*)0x20007554 == 0)
                        DEBUG_PRINT(0x000a9eff, 0x000aa446);
                    else
                        FUN_00019c70();
                }
                FUN_00086c78(0x2001ba2e, 0, 0x1210);
                thunk_FUN_000723b8(0x20007574, 0, 0xffffffff, 0xffffffff);
                FUN_0007da70(0x20015e52, *(volatile unsigned*)(param_2 + 0xb1), 0x2001ba2e);
            }
            *pcVar5 = 1;
            thunk_FUN_00072558(0x20007574);
            do_bd8 = 1;
        } else if (*(volatile unsigned char*)0x2001ba2d == 1) {
            do_bd8 = 1;
        }
        if (do_bd8) {
            int a1 = FUN_0007d3ee();
            int a2 = FUN_0007d446();
            int a3 = FUN_0007d3ee();
            int a4 = FUN_0007d446();
            FUN_00043bd8(a1 + 0x1b6, a2, a3 + 0x240, a4 + 0x88,
                         0x2001c336 - 0x908, 0x2001c336, 2, 0xf);
        }
        *pcVar4 = 0;
    }
    pcVar4 = (unsigned char*)0x20010324;
    if (*(volatile unsigned char*)0x20010324 == 1) {
        if (2 < *(volatile int*)0x2000230c) {
            if (*(volatile int*)0x20007554 == 0)
                DEBUG_PRINT(0x000a9f51, 0x000aa446);
            else
                FUN_00019c70();
        }
        FUN_00086c78(0x2001b9ac, 0, 0x80);
        FUN_00077914(0x2001b9ac, 0x80, 0x000a9f2a, param_2 + 0xd, param_2 + 0x25);
        {
            int a1 = FUN_0007d3ee();
            int a2 = FUN_0007d446();
            int a3 = FUN_0007d3ee();
            int a4 = FUN_0007d446();
            FUN_00043e90(0, 0x2001b9ac, 0, a1 + 0xe8, a2, a3 + 0x1ae, a4 + 0x1b, 1, 0, 0, 0, 0);
            int b1 = FUN_0007d3ee();
            int b2 = FUN_0007d446();
            int b3 = FUN_0007d3ee();
            int b4 = FUN_0007d446();
            FUN_00043e90(0, param_2 + 0x3d, 0, b1, b2 + 0x1d, b3 + 0x1ae, b4 + 0x38, 1, 0, 0, 0, 0);
            int c1 = FUN_0007d3ee();
            int c2 = FUN_0007d446();
            int c3 = FUN_0007d3ee();
            int c4 = FUN_0007d446();
            FUN_00043e90(0, param_2 + 0x7d, 0, c1, c2 + 0x6c, c3 + 200, c4 + 0x87, 1, 0, 0, 0, 0);
            iVar11 = FUN_000167a8();
            iVar11 = *(volatile unsigned char*)(*(volatile int*)(iVar11 + 0xfec) + 0x5e) - 1;
            if (iVar11 != 0) iVar11 = 1;
            uVar12 = FUN_0007d224();
            int d1 = FUN_0007d3ee();
            int d2 = FUN_0007d446();
            int d3 = FUN_0007d3ee();
            int d4 = FUN_0007d446();
            FUN_000442bc(uVar12, d1, d2 + 2, d3 + 0x4c, d4 + 0x1d, 3, iVar11);
        }
        FUN_0003dff8(*(volatile unsigned char*)(param_2 + 1));
        *pcVar4 = 0;
    }
    *(volatile unsigned char*)(iVar3 + 4) = 0;
    *(volatile unsigned char*)(iVar3 + 5) = 1;
    *(volatile unsigned char*)(iVar3 + 0x15) = 0;
}

