#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100b180 @ 0x0100b180
 * public-name: FUN_0100b180
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_duration_to_units             <= FUN_0100d538 @ 0x0100d538
 *   controller_radio_request_configure       <= FUN_0101fdd0 @ 0x0101fdd0
 * address symbols (name @ address):
 *   g_21000050                               @ 0x21000050
 *   g_net_radio_drv_ctx                      @ 0x21000c48
 *   g_ll_conn_trace_ctx_addr                 @ 0x21000cd0
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_0100b180 @ 0x100b180  (parity 21 trials PROVEN) */
#define P6  ((volatile unsigned char *)((unsigned long)&g_net_radio_drv_ctx) /*=0x21000c48*/)
#define P7C ((volatile unsigned char *)((unsigned long)&g_ll_conn_trace_ctx_addr) /*=0x21000cd0*/)
#define PGL ((volatile unsigned char *)REG_41008000 /*=0x41008000*/)

#define RB(p,o)  (*(volatile unsigned char *)((unsigned char*)(p)+(o)))
#define RSB(p,o) (*(volatile signed char *)((unsigned char*)(p)+(o)))
#define RH(p,o)  (*(volatile unsigned short *)((unsigned char*)(p)+(o)))
#define RW(p,o)  (*(volatile unsigned int *)((unsigned char*)(p)+(o)))

extern unsigned int sdc_assertion_fail(int, int);
extern unsigned int FUN_010203d0(void);
extern unsigned int FUN_0101ff4c(void);
extern unsigned int FUN_010204d4(int);
extern unsigned int FUN_0102072c(unsigned int);
extern unsigned int FUN_010204e0(unsigned int);
extern unsigned int FUN_010204f4(unsigned int);
extern unsigned int FUN_01025c44(int);
extern unsigned int FUN_010208e4(int);
extern unsigned int FUN_01020270(int);
extern unsigned int FUN_010212ec(int, unsigned int);
extern unsigned int FUN_01020738(unsigned int);
extern unsigned int FUN_0100a17c(unsigned int);
extern unsigned int FUN_0100a118(unsigned int);
extern unsigned int FUN_01022a50(unsigned int, unsigned int, int);
extern unsigned int controller_duration_to_units(unsigned int, unsigned int);
extern unsigned int FUN_0100f100(volatile unsigned char *, unsigned int);
extern unsigned int FUN_0100f5cc(void);
extern unsigned int controller_radio_request_configure(unsigned int, unsigned int, unsigned int, unsigned int, int);
extern unsigned int FUN_0100ac98(int);
extern unsigned int FUN_0100af3c(int);

void FUN_0100b180(unsigned int param_1, unsigned int param_2,
                  int param_3, int param_4, int param_5)
{
    volatile unsigned char *p16;
    volatile unsigned char *p7;
    unsigned int uVar13, uVar11, uVar8, uVar10, uVar14, uVar15;
    unsigned int uVar17, uVar2, uVar4;
    int cVar12, cVar3, c;
    int iVar9;
    unsigned char bVar5;

    if ((RB(P6,0x44) != 0) || (param_4 == 0 || param_3 == 0) || (param_5 == 0)) {
        sdc_assertion_fail(0x27, 0x153); return;
    }

    RW(P6,0xc0) = param_4;
    RW(P6,0x40) = param_5;
    RW(P6,0x34) = param_3;
    RB(P6,0x3c) = 0;
    RB(P6,0x3d) = 0;
    RB(P6,0xc4) = 0;
    RB(P6,0x3e) = 0;
    RB(P6,0xb0) = 0;
    RH(P6,0x32) = 0;
    RH(P6,0x30) = 0;
    RW(P6,0x24) = param_1;
    RW(P6,0x28) = param_2;

    p16 = (volatile unsigned char *)param_2;
    p7  = p16 + 0xa8;

    FUN_010203d0();
    FUN_0101ff4c();
    FUN_010204d4((int)RSB(p16,0x72));
    FUN_0102072c(RW(p16,0x20));
    FUN_010204e0(RW(p16,0x18));
    FUN_010204f4(RB(p7,0x33));

    if (RB(P6,0x24) == 0) {
        FUN_01025c44(3);
        if (RW(p16,0x14) < 0x1d4c) { FUN_010208e4(1); FUN_01020270(0x4d); }
        else                       { FUN_01020270(0x96); }
        iVar9 = (int)FUN_010212ec(0, RB(p16,0x6e));
    } else {
        FUN_01025c44(4);
        if (RW(p16,0x14) < 0x1d4c) { FUN_010208e4(1); FUN_01020270(0x4d); }
        else                       { FUN_01020270(0x96); }
        iVar9 = (int)FUN_010212ec(1, RB(p16,0x6f));
    }

    if (iVar9 == 0) return;

    FUN_01020738(RW((volatile unsigned char*)((unsigned long)&g_21000050) /*=0x21000050*/, 0));
    RW(P6,0x80) = FUN_0100a17c(RH(p16,0x0));
    RW(P6,0xc8) = FUN_0100a118(RH(p16,0x0));
    cVar12 = RB(p16,0x7b);
    if ((cVar12 == 0) && (RW(p16,0x74) != 0) && (RH(p16,0xbc) == RH(p16,0xf2))) {
        RH(p16,0xf2) = (unsigned short)(RH(p16,0xbc) + RH(p16,0x78));
        FUN_01022a50(RB(p16,0x7a), RW(p16,0x74), 1);
    }

    uVar15 = RW(p16,0x13c);
    uVar10 = RW(p16,0x134);
    uVar14 = RW(p16,0x138);
    RW(P7C,0x0) = RW(p16,0x130);
    RW(P7C,0x4) = uVar10;
    RW(P7C,0x8) = uVar14;
    RW(P7C,0xc) = uVar15;
    RW(P6,0xa1)  = RW(p16,0x140);
    RW(P7C,0x1d) = RW(p16,0x144);

    if (RB(P6,0x24) == 0) {
        if (((unsigned)(RB(p16,0xc5) - 0x26) < 2u) || (RB(p16,0xc6) == 0x26)) {
            c = RB(p16,0x31a);
            uVar13 = RB(p16,0x6e);
            if (c != 0) {
                if (uVar13==8 || uVar13==4 || c==8 || c==4) goto L4e6;
                if (uVar13==1 || c==1) goto L454;
                goto L480;
            }
            goto L2ba;
        } else {
            uVar13 = RB(p16,0x6e);
            if (uVar13 == 4) goto L4e6;
        }
    L2ba:
        uVar8 = RH(p16,0x3c);
        if ((uVar13 & 0xc) != 0) uVar8 = 0xa90;
        goto L2c6;
    } else {
        if (((unsigned)(RB(p16,0xc5) - 0x26) < 2u) || ((cVar12 = RB(p16,0xc6)) == 0x26)) {
            c = RB(p16,0x3be);
            uVar13 = RB(p16,0x6e);
            if (c != 0) {
                if (((uVar13!=8) && (uVar13!=4)) && (c!=8) && (c!=4)) {
                    if (uVar13==1 || c==1) goto L454;
                L480:
                    uVar13 = 2;
                    goto L456;
                }
                goto L4e6;
            }
            goto L2ba;
        }
        if ((unsigned)(RB(p16,0xc5) - 0x21) < 2u) {
            if (cVar12 == 0x24) goto L3de;
            uVar11 = RB(p16,0x16e);
            uVar13 = RB(p16,0x6e);
            if ((int)(uVar11 << 0x1d) >= 0) {
                if ((RB(p16,0x16e) & 1) == 0) {
                    if ((int)(uVar11 << 0x1e) >= 0) goto L2ba;
                    if (uVar13==8 || uVar13==4) goto L4e6;
                L404:
                    if (uVar13 != 1) uVar13 = 2;
                    goto L456;
                }
                if (uVar13==8 || uVar13==4) goto L4e6;
            L574:
                uVar13 = uVar11 & 1;
                goto L456;
            }
        } else {
            if (cVar12 != 0x24) goto L2b0;
        L3de:
            bVar5 = (unsigned char)(RB(p16,0x16e) & RB(p16,0x67));
            uVar11 = bVar5;
            uVar13 = RB(p16,0x6e);
            if ((int)(uVar11 << 0x1d) >= 0) {
                if ((bVar5 & 1) == 0) {
                    if ((int)(uVar11 << 0x1e) >= 0) goto L2ba;
                    if ((uVar13!=4) && (uVar13!=8)) goto L404;
                } else if ((uVar13!=4) && (uVar13!=8)) goto L574;
            }
        }
    L4e6:
        uVar13 = 8;
        uVar8 = 0xa90;
        goto L2c6;

    L2b0:
        uVar13 = RB(p16,0x6e);
        if (uVar13 == 4) goto L4e6;
        goto L2ba;

    L454:
        uVar13 = 1;
    L456:
        uVar8 = RH(p16,0x3c);
        goto L2c6;
    }

L2c6:
    uVar11 = controller_duration_to_units(uVar8, uVar13);
    uVar2 = RB(p16,0x6f);
    uVar13 = (unsigned short)RH(p16,0x38);
    if (uVar11 <= (unsigned short)RH(p16,0x38)) uVar13 = uVar11;
    RB(P6,0x7b) = (unsigned char)uVar13;
    uVar10 = FUN_0100f100(p16 + 0x30, uVar2);
    cVar12 = RB(p16,0x6f);
    cVar3  = RB(p16,0xcb);
    uVar4  = RH(p16,0x40);
    if (cVar12 == 8) cVar12 = 4;
    uVar13 = controller_duration_to_units(uVar10, (unsigned int)cVar12);
    if (cVar3 == 0) uVar13 = (uVar13 + 4) & 0xffff;
    if (uVar4 <= uVar13) uVar13 = uVar4;
    uVar11 = uVar13 & 0xff;
    RB(P6,0xcc) = (unsigned char)uVar13;
    if ((int)FUN_0100f5cc() != 0 && uVar11 < 0x2b) uVar11 = 0x2b;
    RB(P6,0x7a) = (unsigned char)uVar11;

    if (RB(P6,0x24) == 0) {
        if (RB(p16,0xca) != 0) {
            uVar2 = RB(p16,0x6e);
            RB(P6,0xa0) = 1;
            uVar10 = RW(p16,0x124);
            RW(P6,0x98) = RW(p16,0x120);
            RW(P6,0x9c) = uVar10;
            if (RW(p16,0x14) < 0x1d4c) uVar10 = 4; else uVar10 = 0;
            uVar17 = 0;
            switch (uVar2) {
            case 1: break;
            case 2: uVar17 = 1; break;
            default: sdc_assertion_fail(6, 0x3c5); for(;;){}
            case 4: uVar17 = 3; break;
            case 8: uVar17 = 2; break;
            }
            controller_radio_request_configure(uVar10, ((unsigned long)&g_ll_conn_trace_ctx_addr) /*=0x21000cd0*/, 0xfb, uVar17, 0);
        }
        FUN_0100ac98(1);
    } else {
        if (RB(p16,0xcb) != 0) {
            uVar2 = RB(p16,0x6f);
            RB(P6,0xa0) = 1;
            RW(P6,0x98) = RW(p16,0x128);
            RW(P6,0x9c) = RW(p16,0x12c);
            uVar17 = 0;
            switch (uVar2) {
            case 1: break;
            case 2: uVar17 = 1; break;
            default: sdc_assertion_fail(6, 0x3c5); for(;;){}
            case 4: uVar17 = 3; break;
            case 8: uVar17 = 2; break;
            }
            controller_radio_request_configure(1, ((unsigned long)&g_ll_conn_trace_ctx_addr) /*=0x21000cd0*/, uVar11, uVar17, 0);
        }
        FUN_0100af3c(1);
    }

    if ((RW(PGL,0x550) & 0xfffffff7u) != 3) {
        unsigned short s_bc = RH(p16,0xbc);
        unsigned char  b_db = RB(p16,0xdb);
        unsigned short s_0  = RH(p16,0x0);
        RW(P6,0x8) = 0;
        RW(P6,0x0) = 0;
        RW(P6,0x4) = 0;
        RH(P6,0x2) = s_bc;
        RB(P6,0x4) = b_db;
        RH(P6,0x0) = s_0;
        return;
    }
    sdc_assertion_fail(0x27, 0x208); return;
}
