/* Reconstructed display_thread_handler @ 0x49090  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

extern void    DEBUG_PRINT(unsigned a, unsigned b, unsigned c);
extern int     FUN_00019c70(void);
extern int64_t FUN_0000e244(int, int, int, int);
extern int     FUN_000167a8(void);
extern void    FUN_000431b4(int);
extern void    FUN_00048e28(int, int, int, int);
extern void    FUN_00048ff4(void);
extern int     FUN_00049000(int);
extern void    FUN_0004906c(void);
extern int     FUN_00072240(int, void *, int, int);
extern void    FUN_00074844(int, int);
extern void    FUN_0007d6f4(int);
extern void    FUN_00086726(int, int, int);
extern void    FUN_00086c78(void *, int, int);

/* globals (absolute addresses from literal pool) */
#define PIV5   (*(volatile int *)0x2000230c)   /* DAT_00049310 : verbosity level */
#define PIV6   (*(volatile int *)0x20007554)   /* DAT_00049314 / DAT_000495cc    */
#define P30    (*(volatile int *)0x20002544)   /* DAT_00049330                   */
#define PC8    (*(volatile signed char *)0x2001d447)   /* DAT_0004932c[0] */
#define PC8_1  (*(volatile signed char *)0x2001d448)   /* DAT_0004932c[1] */
#define PC16   (*(volatile short *)0x2001d447)         /* 16-bit store form */

void display_thread_handler(int param_1)
{
    volatile signed char *base = (volatile signed char *)param_1;
    unsigned char local[24];
    int  iVar13, iVar9;
    int  bVar3;
    signed char cVar1;
    short local_3e;
    unsigned lo, b1;
    unsigned uVar12, uVar10, uVar8;

    if (2 < PIV5) {
        if (PIV6 == 0) DEBUG_PRINT(0xefb2e, 0xf01aa, 0);
        else FUN_00019c70();
    }
    FUN_00086c78(local, 0, 0x18);
    iVar13 = param_1 + 0xd4;
    if (2 < PIV5) {
        if (PIV6 == 0) DEBUG_PRINT(0xefb50, 0xf01aa, 0);
        else FUN_00019c70();
    }
    FUN_00086726(0x20004ce0, 0x7d86d, 0);
    FUN_000431b4(param_1 + 0xb90);
    PC16 = 0;

    do {
        while (base[1] == 1 || base[1] == 8) {
            if (2 < PIV5) {
                if (PIV6 == 0) DEBUG_PRINT(0xefb7a, 0xf01aa, 0);
                else FUN_00019c70();
            }
            FUN_00074844(0x28000, 0);
        }
        FUN_00086c78(local, 0, 0x18);
        bVar3 = 0;
        {
            int x = P30;
            int t = x & ~(x >> 31);
            int64_t lVar2 = (int64_t)t * 0x8000 + 999;
            int64_t uVar14 = FUN_0000e244((int)lVar2, (int)((uint64_t)lVar2 >> 32), 1000, 0);
            iVar9 = FUN_00072240(0x200038c4, local, (int)uVar14, (int)((uint64_t)uVar14 >> 32));
        }
        local_3e   = *(short *)(local + 2);
        lo         = local[4];
        b1         = local[5];
        uVar8      = *(unsigned *)(local + 4);
        if (iVar9 == 0) bVar3 = 1;
        else if (iVar9 == -0x23 || iVar9 == -0xb) bVar3 = 0;

        cVar1 = PC8;
        if (cVar1 == 1) {
            if (!bVar3) {
                if (base[0xd5] != 0) { uVar12 = 0; uVar10 = (unsigned char)base[0xd5]; goto LAB_492ee; }
                /* second identical test is dead */
                if (3 < PIV5) {
                    if (PIV6 == 0) DEBUG_PRINT(0xefebc, 0xf01aa, (unsigned char)base[0xd5]);
                    else FUN_00019c70();
                }
                if (PIV5 < 1) goto LAB_495ba;
                iVar9 = PIV6;
                uVar12 = 0xeff0e; { unsigned uVar11 = 0xf01aa;
LAB_495a8:
                if (iVar9 == 0) DEBUG_PRINT(uVar12, uVar11, 0);
                else FUN_00019c70(); }
                goto LAB_495ba;
            }
            if (local[0] == 2) {
                if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefcdf, 0xf01aa, 0); else FUN_00019c70(); }
                if (local_3e == 0) {
                    if (3 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefd03, 0xf01aa, 0); else FUN_00019c70(); }
                    uVar12 = 1; uVar10 = (unsigned char)base[0xd5]; goto LAB_492ee;
                }
                if (local_3e == 2) {
                    if (lo == 1) {
                        if (3 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefd2d, 0xf01aa, b1); else FUN_00019c70(); }
                        uVar12 = 1;
LAB_492e8:
                        uVar10 = b1; goto LAB_492ee;
                    }
                    if (0 < PIV5) {
                        iVar9 = PIV6; { unsigned u12 = 0xefd45, u11 = 0xf01aa;
LAB_49270:
                        if (iVar9 == 0) DEBUG_PRINT(u12, u11, 0); else FUN_00019c70(); }
                    }
                }
            } else {
                switch (local[0]) {
                case 3:
                    if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefd6f, 0xf01aa, 0); else FUN_00019c70(); }
                    PC8 = 2;
                    if (local_3e == 0) {
                        if (3 < PIV5) { iVar9 = PIV6; uVar12 = 0xefd03;
LAB_4943a:
                            if (iVar9 == 0) DEBUG_PRINT(uVar12, 0xf01aa, 0); else FUN_00019c70();
                        }
LAB_49442:
                        uVar10 = (unsigned char)base[0xd5];
LAB_4947e:
                        FUN_00048e28(param_1, uVar10, iVar13, 2);
                    } else if (local_3e == 2) {
                        if ((signed char)lo != 1) {
                            if (0 < PIV5) { iVar9 = PIV6; uVar12 = 0xefd45; goto LAB_4943a; }
                            goto LAB_49442;
                        }
                        if (3 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefd2d, 0xf01aa, b1); else FUN_00019c70(); }
                        uVar10 = b1; goto LAB_4947e;
                    }
                    FUN_00048ff4();
                    goto LAB_49488;
                case 4:
                    if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefe74, 0xf01aa, uVar8); else FUN_00019c70(); }
                    FUN_00049000(uVar8); uVar12 = 3; uVar10 = (unsigned char)base[0xd5]; break;
                case 5:
                    if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefebc, 0xf01aa, 0); else FUN_00019c70(); }
                    uVar12 = 4; uVar10 = (unsigned char)base[0xd5]; break;
                case 6:
                    if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefef4, 0xf01aa, 0); else FUN_00019c70(); }
                    uVar12 = 5; uVar10 = (unsigned char)base[0xd5]; break;
                case 7:
                    if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xeff2c, 0xf01aa, 0); else FUN_00019c70(); }
                    uVar12 = 6; uVar10 = (unsigned char)base[0xd5]; break;
                case 8:
                    if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xeff5c, 0xf01aa, 0); else FUN_00019c70(); }
                    uVar12 = 7; uVar10 = (unsigned char)base[0xd5]; break;
                default:
                    goto LAB_switchD;
                }
LAB_492ee:
                FUN_00048e28(param_1, uVar10, iVar13, uVar12);
            }
        } else {
            if (cVar1 == 2) {
LAB_49488:
                if (2 < PIV5) {
                    iVar9 = PIV6; uVar12 = 0xeff70; unsigned uVar11 = 0xf01aa;
                    if (iVar9 == 0) DEBUG_PRINT(uVar12, uVar11, 0); else FUN_00019c70();
                }
            } else {
                if (cVar1 == 0) {
                    if (bVar3) {
                        if (local[0] == 2) {
                            if (base[0xd5] == 0x10) {
                                iVar9 = FUN_000167a8();
                                if (**(unsigned char **)(iVar9 + 0x100c) < 0xc) FUN_0007d6f4(0);
                            }
                            if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefb9f, 0xf01aa, 0); else FUN_00019c70(); }
                            if (local_3e == 0) {
                                if (3 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefbb7, 0xf01aa, 0); else FUN_00019c70(); }
                                cVar1 = base[0xd5]; PC8_1 = base[0xd5];
LAB_49204:
                                FUN_00048e28(param_1, cVar1, iVar13, 1); PC8 = 1;
                            } else if (local_3e == 2) {
                                if (lo == 1) {
                                    if (3 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefbe5, 0xf01aa, b1); else FUN_00019c70(); }
                                    PC8_1 = (signed char)b1; cVar1 = (signed char)b1; goto LAB_49204;
                                }
                                if (0 < PIV5) { iVar9 = PIV6; uVar12 = 0xefc00; unsigned uVar11 = 0xf01aa;
                                    if (iVar9 == 0) DEBUG_PRINT(uVar12, uVar11, 0); else FUN_00019c70(); }
                            }
                        } else if (local[0] == 3) {
                            if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefc2d, 0xf01aa, 0); else FUN_00019c70(); }
                            PC16 = 0;
                            if (local_3e == 0) {
                                if (3 < PIV5) { iVar9 = PIV6; uVar12 = 0xefc62;
LAB_492ac:
                                    if (iVar9 == 0) DEBUG_PRINT(uVar12, 0xf01aa, 0); else FUN_00019c70();
                                }
                            } else {
                                if (local_3e != 2) goto LAB_switchD;
                                if ((signed char)lo == 1) {
                                    if (3 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefc92, 0xf01aa, b1); else FUN_00019c70(); }
                                    uVar12 = 2; goto LAB_492e8;
                                }
                                if (0 < PIV5) { iVar9 = PIV6; uVar12 = 0xefcaf; goto LAB_492ac; }
                            }
                            uVar12 = 2; uVar10 = (unsigned char)base[0xd5]; goto LAB_492ee;
                        }
                    }
                    goto LAB_switchD;
                }
                if (0 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xeffaf, 0xf01aa, 0); else FUN_00019c70(); }
                FUN_00048e28(param_1, (unsigned char)base[0xd5], iVar13, 2);
            }
LAB_495ba:
            FUN_0007d6f4(0); FUN_00048ff4(); PC16 = 0;
        }
LAB_switchD:
        FUN_0004906c();
    } while (1);
}

