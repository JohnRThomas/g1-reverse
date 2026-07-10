#include "g1_net_symbols.h"
/* net-core FUN_0100d878 @ 0x100d878  (parity 300 trials PROVEN) */
typedef unsigned int uint;
typedef unsigned char byte;

extern void FUN_01008d00(int, int, unsigned int, unsigned int, unsigned int);

static inline __attribute__((always_inline)) uint rev8(uint x)
{
    uint r = 0, i;
    x &= 0xff;
    for (i = 0; i < 8; i++) { r = (r << 1) | (x & 1); x >>= 1; }
    return r;
}

#define BIT(mask, D, LBL) \
    if (V & (mask)) { u3 = (u3 - 1) & 0xff; if (u3 == 0) { u3 = (D); goto LBL; } }

uint FUN_0100d878(byte *p1, uint param_2, uint param_3, uint param_4)
{
    uint k, h, v16, b1, b2, prod, u3, u7, V, V1;
    int iv = 0;

    k = (param_2 ^ (param_2 >> 0x10)) & 0xffff;
    b1 = (byte)(param_3 ^ k);
    b2 = (byte)((param_3 ^ k) >> 8);

    v16 = ((rev8(b2) << 8) | rev8(b1)) * 0x11 + k;
    b2 = (byte)(v16 >> 8);
    b1 = (byte)v16;

    v16 = ((rev8(b2) << 8) | rev8(b1)) * 0x11 + k;
    b2 = (byte)(v16 >> 8);
    b1 = (byte)v16;

    h = ((((rev8(b2) << 8) | rev8(b1)) * 0x11 + k) ^ k) & 0xffff;

    {
        uint hi = (uint)(((unsigned long long)0xbacf914dULL * (unsigned long long)h) >> 0x20);
        uint d  = h - hi;
        uint q  = (hi + (d >> 1)) >> 5;
        uint mv = h - q * 0x25;              /* h % 37 */
        if ((p1[((mv * 0x1000000) >> 0x1b) + 1] & (1u << (mv & 7))) != 0) {
            return mv & 0xff;
        }
    }

    prod = p1[0xb] * h;
    u7 = prod >> 0x10;
    u3 = (u7 + 1) & 0xff;

    if (u3 <= p1[6]) goto L_9e0;
    u3 = (u3 - p1[6]) & 0xff;
L_92c:
    if (p1[7] >= u3) goto L_da6a;
    u3 = (u3 - p1[7]) & 0xff;
L_93a:
    if (u3 <= p1[8]) goto L_daf6;
    u3 = (u3 - p1[8]) & 0xff;
L_948:
    if (u3 <= p1[9]) goto L_966;
    u3 = (u3 - p1[9]) & 0xff;
L_954:
    if (p1[10] >= u3) goto L_db84;
L_95e:
    FUN_01008d00(0x46, 0x9d, u3, 0, param_4);
    /* FUN_01008d00 does not return in reality; oracle returns and falls
       through into the param_1[4] cascade */
L_966:
    V = p1[4];
    BIT(0x01, 3, R_da7e) BIT(0x02, 3, R_d9fc) BIT(0x04, 3, R_da12) BIT(0x08, 3, R_da22)
    BIT(0x10, 3, R_da32) BIT(0x20, 3, R_da42) BIT(0x40, 3, R_da52)
    if (V & 0x80) { u3 = (u3 - 1) & 0xff; if (u3 == 0) { u3 = 3; goto R_da66; } }
    goto L_954;

L_da6a:
    V = p1[2];
    BIT(0x01, 1, R_da7e) BIT(0x02, 1, R_d9fc) BIT(0x04, 1, R_da12) BIT(0x08, 1, R_da22)
    BIT(0x10, 1, R_da32) BIT(0x20, 1, R_da42) BIT(0x40, 1, R_da52)
    if (V & 0x80) { u3 = (u3 - 1) & 0xff; if (u3 == 0) { u3 = 1; goto R_da66; } }
    goto L_93a;

L_daf6:
    V = p1[3];
    BIT(0x01, 2, R_da7e) BIT(0x02, 2, R_d9fc) BIT(0x04, 2, R_da12) BIT(0x08, 2, R_da22)
    BIT(0x10, 2, R_da32) BIT(0x20, 2, R_da42) BIT(0x40, 2, R_da52)
    if (V & 0x80) { u3 = (u3 - 1) & 0xff; if (u3 == 0) { u3 = 2; goto R_da66; } }
    goto L_948;

L_db84:
    V = p1[5];
    BIT(0x01, 4, R_da7e) BIT(0x02, 4, R_d9fc) BIT(0x04, 4, R_da12) BIT(0x08, 4, R_da22)
    BIT(0x10, 4, R_da32) BIT(0x20, 4, R_da42) BIT(0x40, 4, R_da52)
    if (V & 0x80) { if (u3 == 1) { u3 = 4; goto R_da66; } }
    goto L_95e;

L_9e0:
    V1 = p1[1];
    if (V1 & 1) { if (u7 == 0) { u3 = 0; goto R_da7e; } u3 = u7; }
    if (V1 & 0x02) { u3 = (u3 - 1) & 0xff; if (u3 == 0) goto R_d9fc; }
    if (V1 & 0x04) { u3 = (u3 - 1) & 0xff; if (u3 == 0) goto R_da12; }
    if (V1 & 0x08) { u3 = (u3 - 1) & 0xff; if (u3 == 0) goto R_da22; }
    if (V1 & 0x10) { u3 = (u3 - 1) & 0xff; if (u3 == 0) goto R_da32; }
    if (V1 & 0x20) { u3 = (u3 - 1) & 0xff; if (u3 == 0) goto R_da42; }
    if (V1 & 0x40) { u3 = (u3 - 1) & 0xff; if (u3 == 0) goto R_da52; }
    if (V1 & 0x80) { u3 = (u3 - 1) & 0xff; if (u3 == 0) goto R_da66; }
    goto L_92c;

R_da7e: iv = 0; goto R_9fe;
R_d9fc: iv = 1; goto R_9fe;
R_da12: iv = 2; goto R_9fe;
R_da22: iv = 3; goto R_9fe;
R_da32: iv = 4; goto R_9fe;
R_da42: iv = 5; goto R_9fe;
R_da52: iv = 6; goto R_9fe;
R_da66: iv = 7; goto R_9fe;
R_9fe:
    return (iv + u3 * 8) & 0xff;
}

