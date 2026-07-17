#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010144e4 @ 0x010144e4
 * public-name: FUN_010144e4
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_pdu_type_bits_set                    <= FUN_0100e5dc @ 0x0100e5dc
 * address symbols (name @ address):
 *   g_210001d4                               @ 0x210001d4
 *   g_210001e4                               @ 0x210001e4
 *   g_210001ec                               @ 0x210001ec
 *   g_net_link_ctx_a                         @ 0x21000f68
 */
/* net-core FUN_010144e4 @ 0x10144e4  (parity 300 trials PROVEN) */
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned short u16;

extern int  FUN_0100a904(void *);
extern void sdc_assertion_fail(int, int);
extern void FUN_01025a84(void *, int, int);
extern void sdc_pdu_type_bits_set(void *, int);
extern void FUN_0100e634(void *, uint);
extern void FUN_0100e784(void *, int);
extern void FUN_0100e79c(void *, int);
extern void FUN_01010110(int, void *);
extern void FUN_010100f4(void *);
extern void FUN_0100e8e8(void *, int);
extern void FUN_0100e8f0(void *, int);
extern void FUN_0100e7b0(void *, int);
extern void FUN_0100e7b8(void *, int);
extern void FUN_0100e7c0(void *, int);
extern void FUN_0100e7c8(void *, int);
extern void FUN_0100e65c(void *, unsigned, int);
extern void FUN_0100e5f4(void *, int);
extern void FUN_0100e608(void *, void *);
extern void FUN_0100e808(void *, int);
extern void FUN_01029bda(void *);
extern void FUN_01029bea(void *);
extern void FUN_0100e83c(void *, int, int);
extern int  FUN_0100a934(void);

#define GBASE ((unsigned long)&g_net_link_ctx_a) /*=0x21000f68*/
#define G4  (*(volatile int *)(GBASE + 4))

void FUN_010144e4(uint param_1)
{
    unsigned char frame[12];
    unsigned char *local_18 = frame;
    byte *buf;

    if (FUN_0100a904(frame + 8) == 0) goto L_071e;
    __atomic_signal_fence(__ATOMIC_ACQUIRE);
    buf = *(byte * volatile *)(frame + 8);
    FUN_01025a84(buf, 0, 0x32);
    sdc_pdu_type_bits_set(buf, 3);
    *buf = *buf & 0xef;
    FUN_0100e634(buf, param_1);

    if (param_1 > 0x2a) goto L_0598;
    if (param_1 <= 1)   goto L_05b0;
    if ((param_1 - 2) > 0x28) goto L_05b0;

    switch (param_1) {
    case 2:  case 7:  goto L_057e;
    case 4:           goto L_068e;
    case 5:  case 6:  case 0xb: case 0x12: case 0x13: goto L_058a;
    case 9:           goto L_0684;
    case 0xc:         goto L_0604;
    case 0xd:         goto L_0650;
    case 0xe:         goto L_06da;
    case 0x11:        goto L_06be;
    case 0x14: case 0x15: goto L_05c8;
    case 0x16:        goto L_0610;
    case 0x17:        goto L_061e;
    case 0x1b:        goto L_06e2;
    case 0x1c:        goto L_065e;
    case 0x1d:        goto L_05fc;
    case 0x1e:        goto L_0648;
    case 0x20:        goto L_0638;
    case 0x22:        goto L_066e;
    case 0x23: case 0x24: case 0x25: goto L_05ba;
    case 0x2a:        goto L_06aa;
    default:          goto L_05b0;
    }

L_057e:
    buf[4] = *(volatile byte *)(G4 + 0x150);
    /* fall through */
L_058a:
    if (FUN_0100a934() == 0) goto L_0728;
    return;

L_0598:
    if (param_1 != 0xff) goto L_05b0;
    FUN_0100e65c(buf, *(volatile unsigned *)(G4 + 0x3b8),
                 *(volatile byte *)(G4 + 0x3b7));
    goto L_058a;

L_05b0:
    sdc_assertion_fail(0x31, 0x8e4);
    /* fall through */
L_05ba:
    {
        void (*f)(uint, void *, int) =
            *(void (* volatile *)(uint, void *, int))((unsigned long)&g_210001ec) /*=0x210001ec*/;
        f(param_1, buf, GBASE);
    }
    goto L_058a;

L_05c8:
    FUN_0100e7b0(buf, *(volatile u16 *)(G4 + 0x50));
    FUN_0100e7b8(buf, *(volatile u16 *)(G4 + 0x152));
    FUN_0100e7c0(buf, *(volatile u16 *)(G4 + 0x4c));
    FUN_0100e7c8(buf, *(volatile u16 *)(G4 + 0x150));
    goto L_058a;

L_05fc:
    FUN_01029bda(buf);
    goto L_058a;

L_0604:
    buf[8] = 0x21;
    *(volatile unsigned *)(buf + 4) = 0x0200590d;
    goto L_058a;

L_0610:
    *(volatile u16 *)(buf + 4) = *(volatile u16 *)(G4 + 0x16e);
    goto L_058a;

L_061e:
    {
        u16 v;
        if (*(volatile char *)(G4 + 0x16c) == 1)
            v = *(volatile u16 *)(G4 + 0x16e);
        else
            v = *(volatile u16 *)(G4 + 0x6a);
        *(volatile u16 *)(buf + 4) = v;
    }
    goto L_058a;

L_0638:
    {
        void (*f)(void *, int) = *(void (* volatile *)(void *, int))((unsigned long)&g_210001d4) /*=0x210001d4*/;
        if (f != 0) f(buf, GBASE);
    }
    goto L_058a;

L_0648:
    FUN_01029bea(buf);
    goto L_058a;

L_0650:
    buf[4] = *(volatile byte *)(G4 + 0x14a);
    goto L_058a;

L_065e:
    FUN_0100e808(buf, G4 + 0x179);
    goto L_058a;

L_066e:
    {
        void (*f)(void *, int) = *(void (* volatile *)(void *, int))((unsigned long)&g_210001e4) /*=0x210001e4*/;
        if (f != 0) {
                f(buf, G4 + 0x160);
        }
    }
    goto L_058a;

L_0684:
    FUN_01010110(GBASE, buf);
    goto L_058a;

L_068e:
    FUN_0100e784(buf, G4 + 0x300);
    FUN_0100e79c(buf, G4 + 0x144);
    goto L_058a;

L_06aa:
    FUN_0100e83c(buf, G4 + 0x179, G4 + 0x19b);
    goto L_058a;

L_06be:
    FUN_0100e8e8(buf, *(volatile byte *)(G4 + 0x14b));
    FUN_0100e8f0(buf, *(volatile byte *)(G4 + 0x14a));
    goto L_058a;

L_06da:
    FUN_010100f4(buf);
    goto L_058a;

L_06e2:
    {
        uint u;
        local_18[0] = 0;
        FUN_0100e5f4(buf, 1);
        u = (uint)*(volatile byte *)(G4 + 0x10);
        if (u == 3) u = 0;
        local_18[0] = (*(volatile byte *)(G4 + 0x11) & 0x1f)
                      | (byte)(u << 6)
                      | (local_18[0] & 0x20);
        FUN_0100e608(buf, local_18);
    }
    goto L_058a;

L_071e:
    sdc_assertion_fail(0x31, 0x832);
    /* fall through */
L_0728:
    sdc_assertion_fail(0x31, 0x8e8);
    return;
}
