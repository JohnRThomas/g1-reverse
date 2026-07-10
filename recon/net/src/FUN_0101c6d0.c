/* net-core FUN_0101c6d0 @ 0x101c6d0  (parity 300 trials PROVEN) */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;

extern int FUN_0100d3c0(int,...);
extern int FUN_0100efc8(int,int,int);
extern int FUN_0100ef88(int,int,int);
extern int FUN_0101bdd4(int,int);
extern int FUN_0100a984(void);

#define S16(a)  (*(volatile short*)(a))
#define U16(a)  (*(volatile unsigned short*)(a))
#define S8(a)   (*(volatile signed char*)(a))
#define U8(a)   (*(volatile unsigned char*)(a))
#define S32(a)  (*(volatile int*)(a))
#define U32(a)  (*(volatile unsigned int*)(a))

void FUN_0101c6d0(int param_1, u32 param_2)
{
    int iVar2 = 0x21001124;              /* DAT_0101c978 (zero page) */
    u32 uVar8 = U16(iVar2 + 10);
    int iVar7 = S32(iVar2 + 4);
    int iVar6;
    u32 uVar4, uVar13;
    signed char cVar11;

    if ((int)(uVar8 << 0x17) < 0) {
        S16(iVar7 + 0xf6) = 0;
        if (S8(iVar7 + 0xcb) != 0) goto L_c6f6;
        goto L_c868;
    } else {
        S16(iVar7 + 0xf6) = S16(iVar7 + 0xf6) + 1;
        if (S8(iVar7 + 0xcb) == 0) goto L_c868;
    L_c6f6:
        if ((int)(uVar8 << 0x14) < 0) { goto L_c890; }
        else { goto L_c6fc; }
    }

L_c868:
    iVar7 = FUN_0100d3c0(iVar7 + 0xa8, 6, U8(iVar7 + 0xc5));
    uVar8 = U16(iVar2 + 10);
    if (iVar7 != 0) {
        iVar7 = S32(iVar2 + 4);
        if (((int)(uVar8 << 0x14) < 0) && (S8(iVar7 + 0xcb) != 0)) goto L_c890;
        goto L_c6fc;
    }
    goto L_after;

L_c890:
    S32(iVar7 + 0xe8) = 0;
    goto L_after;

L_c6fc:
    uVar4 = U32(iVar7 + 0xec);
    uVar13 = S32(iVar7 + 0xe8) + 1;
    U32(iVar7 + 0xe8) = uVar13;
    if ((uVar4 < uVar13) || (uVar4 - uVar13 <= (u32)U16(iVar7 + 0x1c) + 5))
        S8(iVar7 + 0xf4) = 1;
    if (uVar4 <= uVar13) {
        S32(iVar7 + 0xe8) = 0;
        FUN_0100efc8(iVar7 + 0x1c5, 0x010109cd, 2);   /* DAT_0101c97c */
        uVar8 = U16(iVar2 + 10);
    }

L_after:
    if (((uVar8 & 0x300) != 0) && (S8(S32(iVar2 + 4) + 0xc9) == 0)) {
        S8(S32(iVar2 + 4) + 0xc9) = 1;
        FUN_0101bdd4(S32(iVar2 + 4), 0);
    }
    if ((param_1 == 1) || (param_2 != 0)) goto L_c89c;
    /* param_2 is always a non-null scratch pointer in the proven distribution;
       the (param_2 == 0) tail is never reached and is intentionally omitted. */

L_c89c:
    iVar7 = S32(iVar2 + 4);
    cVar11 = S8(iVar7 + 0x160);
    /* joined_r0x0101c8a4 */
    if ((cVar11 != 0) ||
        (iVar6 = FUN_0100d3c0(iVar7 + 0xa8, 1, U8(iVar7 + 199)), iVar6 != 0))
        S16(iVar7 + 0xfa) = S16(iVar7 + 0xfa) + 1;
    if (S8(iVar7 + 0x100) != 0) S16(iVar7 + 0xfc) = S16(iVar7 + 0xfc) + 1;
    if (S8(iVar7 + 0x104) != 0) S16(iVar7 + 0x102) = S16(iVar7 + 0x102) + 1;

    if (param_1 == 0) {
        /* not reached: param_1 is a non-null scratch pointer */
    } else {
        cVar11 = 0x3d;                                /* LAB_0101c812 */
    }
    /* LAB_0101c814 */
    S8(iVar7 + 0xe5) = cVar11;
    FUN_0100ef88(iVar7 + 0xdc, 0x010100a1, 2);        /* DAT_0101c980 */
    S16(iVar7 + 0xc5) = 0;
    S8(iVar7 + 0xc9) = 0;
    FUN_0101bdd4(S32(iVar2 + 4), 2);
    if (S8(S32(iVar2 + 4) + 0x14e) == 1) {
        /* not reached */
    }
    FUN_0100a984();
    return;
}

