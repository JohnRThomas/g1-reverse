#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01026122 @ 0x01026122
 * public-name: FUN_01026122
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_feature_bit_enabled           <= FUN_0100938c @ 0x0100938c
 */
/* net-core FUN_01026122 @ 0x1026122  (parity 300 trials PROVEN) */
extern void sdc_assertion_fail(unsigned int, unsigned int) __attribute__((noreturn));
extern unsigned int controller_feature_bit_enabled(unsigned int);
extern void FUN_01025998(unsigned char *, unsigned char *, unsigned int);

#define WB(p,o,v) (*(volatile unsigned char *)((p)+(o)) = (unsigned char)(v))
#define WH(p,o,v) (*(volatile unsigned short *)((p)+(o)) = (unsigned short)(v))
#define WW(p,o,v) (*(volatile unsigned int  *)((p)+(o)) = (unsigned int)(v))
#define RB(p,o) (*(unsigned char  *)((p)+(o)))
#define RH(p,o) (*(unsigned short *)((p)+(o)))
#define RW(p,o) (*(unsigned int   *)((p)+(o)))

unsigned int FUN_01026122(unsigned char *p1, unsigned char *p2,
                          unsigned int param_3, unsigned int param_4)
{
    unsigned int S = p2[0];
    unsigned int uVar8 = 0;
    unsigned int uVar6 = 0;
    unsigned int uVar3 = 0;
    unsigned int uVar4res = 0;
    (void)param_3; (void)param_4;

    switch (S) {
    case 1:  WB(p2,0,0x0c); uVar8=0x08; goto L_ae;
    case 2:  WB(p2,0,0x1a); uVar8=0x01; goto L_ae;
    case 3:  WB(p2,0,0x3e); WB(p2,2,0x02); goto L_b0;
    case 4:  goto C4;
    case 6:  WB(p2,0,0x3e); WB(p2,1,0x04); WB(p2,2,0x14); goto L_b0;
    case 7:  WB(p2,0,0x3e); WB(p2,1,0x0c); WB(p2,2,0x04); goto L_b0;
    case 8:  WB(p2,0,0x3e); WB(p2,1,0x0a); WB(p2,2,0x03); goto L_b0;
    case 9:  WB(p2,0,0x3e); WB(p2,1,0x0d); WB(p2,2,0x05); goto L_b0;
    case 10: WB(p2,0,0x05); uVar8=0x04; goto L_ae;
    case 11: WB(p2,0,0x08); uVar8=0x04; goto L_ae;
    case 12: WB(p2,0,0x30); uVar8=0x03; goto L_ae;
    case 13: goto Cd;
    case 14: WB(p2,0,0x57); uVar8=0x02; goto L_ae;
    case 15: WB(p2,0,0x0e);
             if (RH(p2,3) != 0x2083) { uVar3=0x31; goto L_c2; }
             uVar8=0x06; goto L_ae;
    case 17: WB(p2,0,0x3e); WB(p2,1,0x12); WB(p2,2,0x0b); goto L_b0;
    case 19: goto C13;
    case 20: goto C14;
    case 21: WB(p2,0,0x3e); WB(p2,1,0x06); WB(p2,2,0x0c); goto L_b0;
    case 22: WB(p2,0,0x3e); WB(p2,1,0x06); WB(p2,2,0x12); goto L_b0;
    case 23: WB(p2,0,0x3e); WB(p2,1,0x09); WB(p2,2,0x13); goto L_b0;
    case 24: WB(p2,0,0x3e); WB(p2,1,0x01); WB(p2,2,0x11); goto L_b0;
    case 26: goto C1a;
    case 28: goto C1c;
    case 29: WB(p2,0,0x3e); WB(p2,1,0x03); WB(p2,2,0x10); goto L_b0;
    case 30: WB(p2,0,0x3e); WB(p2,1,0x05); WB(p2,2,0x20); goto L_b0;
    case 31: WB(p2,0,0x3e); WB(p2,1,0x09); WB(p2,2,0x21); goto L_b0;
    case 33: goto C21;
    case 34: WB(p2,0,0x3e); WB(p2,1,0x04); WB(p2,2,0x27); goto L_b0;
    case 35: goto C23;
    case 36: WB(p2,0,0x3e); WB(p2,1,0x1d); WB(p2,2,0x19); goto L_b0;
    case 37: WB(p2,0,0x3e); WB(p2,1,0x07); WB(p2,2,0x1a); goto L_b0;
    case 38: WB(p2,0,0x3e); WB(p2,1,0x05); WB(p2,2,0x1f); goto L_b0;
    case 39: WB(p2,0,0x3e); WB(p2,1,0x14); WB(p2,2,0x22); goto L_b0;
    case 40: WB(p2,0,0x3e); WB(p2,1,(RB(p2,0x14)*2+0x13)); WB(p2,2,0x1b); goto L_b0;
    case 41: WB(p2,0,0x3e); WB(p2,1,0x03); WB(p2,2,0x1c); goto L_b0;
    case 42: WB(p2,0,0x3e); WB(p2,1,(RB(p2,0x10)*2+0x0f)); WB(p2,2,0x1d); goto L_b0;
    case 43: WB(p2,0,0x3e); WB(p2,1,0x03); WB(p2,2,0x1e); goto L_b0;
    case 44:
    case 45: WB(p2,0,0x3e); goto L_b0;
    case 46: WB(p2,0,0xff); WB(p2,1,0x05); WB(p2,2,0xa4); goto L_b0;
    case 47: WB(p2,0,0xff); WB(p2,1,0x0b); WB(p2,2,0xa2); goto L_b0;
    case 48: WB(p2,0,0xff); WB(p2,1,0x05); WB(p2,2,0xa3); goto L_b0;
    case 49: goto C31;
    case 50: WB(p2,0,0xff); WB(p2,1,0x0d); WB(p2,2,0x80); goto L_b0;
    default: uVar3=0x287; goto L_c2;
    }

L_c2:
    sdc_assertion_fail(0xc7, uVar3);
L_ae:
    WB(p2,1,uVar8);
L_b0:
    {
        unsigned int bv = p2[1];
        FUN_01025998(p1, p2, bv + 2);
        return bv + 2;
    }

C4:
    WB(p1,0,0x3e);
    WB(p1,2,0x0d);
    WB(p1,3,RB(p2,3));
    WH(p1,4,RH(p2,0xd));
    WB(p1,6,RB(p2,4));
    WW(p1,7,RW(p2,5));
    WH(p1,0xb,RH(p2,9));
    WB(p1,0xd,RB(p2,0xf));
    WB(p1,0xe,RB(p2,0x10));
    WB(p1,0xf,RB(p2,0x11));
    WB(p1,0x10,RB(p2,0x1d));
    WB(p1,0x11,RB(p2,0xc));
    WH(p1,0x12,RH(p2,0x14));
    WB(p1,0x14,RB(p2,0x16));
    WW(p1,0x15,RW(p2,0x17));
    WH(p1,0x19,RH(p2,0x1b));
    {
        unsigned int r6 = RB(p2,0xb);
        WB(p1,0x1b,r6);
        if (r6 >= 0xe5) r6 = 0xe5;
        FUN_01025998(p1 + 0x1c, p2 + 0x1f, r6);
        uVar6 = (r6 + 0x1a) & 0xff;
    }
    goto L_274;

Cd:
    WB(p1,2,RB(p2,2));
    if (RB(p2,2) == 1) {
        unsigned short a = RH(p2,3);
        unsigned short b = RH(p2,5);
        WB(p1,0,0x13);
        WB(p1,3,a);
        WB(p1,4,a>>8);
        WB(p1,5,b);
        WB(p1,6,b>>8);
        uVar4res = 5;
    } else {
        uVar4res = 0;
    }
    goto L_386;

C13:
    if (controller_feature_bit_enabled(0x29) != 0) {
        WB(p2,0,0x3e); WB(p2,1,0x22); WB(p2,2,0x29); goto L_b0;
    }
    WB(p1,0,0x3e);
    if (controller_feature_bit_enabled(0x0a) != 0) {
        WB(p1,2,0x0a);
        WB(p1,3,RB(p2,3));
        WB(p1,4,RH(p2,4));
        WB(p1,5,RH(p2,4)>>8);
        WB(p1,6,RB(p2,6));
        WB(p1,7,RB(p2,7));
        WW(p1,8,RW(p2,8));
        WH(p1,0xc,RH(p2,0xc));
        WW(p1,0xe,RW(p2,0xe));
        WH(p1,0x12,RH(p2,0x12));
        WW(p1,0x14,RW(p2,0x14));
        WH(p1,0x18,RH(p2,0x18));
        WB(p1,0x1a,RH(p2,0x1a));
        WB(p1,0x1b,RH(p2,0x1a)>>8);
        WB(p1,0x1c,RH(p2,0x1c));
        WB(p1,0x1d,RH(p2,0x1c)>>8);
        WB(p1,0x1e,RH(p2,0x1e));
        WB(p1,0x1f,RH(p2,0x1e)>>8);
        WB(p1,0x20,RB(p2,0x20));
        uVar6=0x1f;
    } else {
        WB(p1,2,0x01);
        WB(p1,3,RB(p2,3));
        WB(p1,4,RH(p2,4));
        WB(p1,5,RH(p2,4)>>8);
        WB(p1,6,RB(p2,6));
        WB(p1,7,RB(p2,7)&1);
        WW(p1,8,RW(p2,8));
        WH(p1,0xc,RH(p2,0xc));
        WB(p1,0xe,RH(p2,0x1a));
        WB(p1,0xf,RH(p2,0x1a)>>8);
        WB(p1,0x10,RH(p2,0x1c));
        WB(p1,0x11,RH(p2,0x1c)>>8);
        WB(p1,0x12,RH(p2,0x1e));
        WB(p1,0x13,RH(p2,0x1e)>>8);
        WB(p1,0x14,RB(p2,0x20));
        uVar6=0x13;
    }
    goto L_274;

C14:
    WB(p1,0,0x3e);
    WB(p1,2,0x07);
    WB(p1,3,RH(p2,2));
    WB(p1,4,RH(p2,2)>>8);
    WB(p1,5,RH(p2,4));
    WB(p1,6,RH(p2,4)>>8);
    WB(p1,7,RH(p2,6));
    WB(p1,8,RH(p2,6)>>8);
    WB(p1,9,RH(p2,8));
    WB(p1,10,RH(p2,8)>>8);
    WB(p1,0xb,RH(p2,0xa));
    WB(p1,0xc,RH(p2,0xa)>>8);
    uVar6=0x0b;
    goto L_274;

C1a:
    WB(p1,0,0x3e);
    {
        unsigned int uVar7, iv;
        if (controller_feature_bit_enabled(0x24) != 0) { uVar7=0x24; iv=0x13; }
        else { uVar7=0x0e; iv=0x0f; }
        WB(p1,2,uVar7);
        FUN_01025998(p1 + 3, p2 + 2, iv);
        uVar6 = iv + 1;
    }
    goto L_274;

C1c:
    WB(p1,0,0x3e);
    {
        unsigned int iv;
        if (controller_feature_bit_enabled(0x25) == 0) {
            iv=7;
            WB(p1,2,0x0f);
            WH(p1,3,RH(p2,2));
            WB(p1,5,RB(p2,4));
            WB(p1,6,RB(p2,5));
            WB(p1,7,RB(p2,6));
            WB(p1,8,RB(p2,0xa));
            WB(p1,9,RB(p2,0xb));
        } else {
            iv=0x0a;
            WB(p1,2,0x25);
            WW(p1,3,RW(p2,2));
            WW(p1,7,RW(p2,6));
            WH(p1,0xb,RH(p2,0xa));
        }
        FUN_01025998(p1 + iv + 3, p2 + 0xc, RB(p2,0xb));
        uVar6 = (unsigned int)RB(p2,0xb) + 1 + iv;
    }
    goto L_274;

C21:
    WB(p1,0,0x3e);
    {
        unsigned int uVar7, iv;
        if (controller_feature_bit_enabled(0x26) != 0) { uVar7=0x26; iv=0x17; }
        else { uVar7=0x18; iv=0x13; }
        WB(p1,2,uVar7);
        FUN_01025998(p1 + 3, p2 + 2, iv);
        uVar6 = iv + 1;
    }
    goto L_274;

C23:
    WB(p1,0,0x3e);
    WB(p1,2,0x28);
    {
        unsigned char *pv = p1+3;
        unsigned int u6=0, u4=0;
        WW(pv,0,RW(p2,2));
        for (;;) {
            if (!( RB(p1,6) > (u4 & 0xff) )) { uVar4res = u6 + 5; break; }
            WW(pv, u6+4, RW(p2, u6+6));
            WH(pv, u6+8, RH(p2, u6+0xa));
            {
                unsigned int tb = RB(pv, u6+9);
                FUN_01025998(pv + u6 + 10, p2 + u6 + 0xc, tb);
                u6 = (u6 + tb + 6) & 0xffff;
            }
            u4 = u4 + 1;
        }
    }
    goto L_386;

C31:
    WB(p1,0,0xff);
    WB(p1,2,0x81);
    {
        unsigned int *src = *(unsigned int **)(p2+3);
        unsigned char *dst = p1+3;
        unsigned int i;
        for (i = 0; i < 10; i++) {
            WW(dst, i*4, src[i]);
        }
        uVar6 = 0x29;
    }
    goto L_274;

L_386:
    uVar6 = uVar4res & 0xffff;
    if (uVar6 == 0) goto L_b0;
L_274:
    WB(p1,1,uVar6);
    return (uVar6 + 2) & 0xffff;
}
