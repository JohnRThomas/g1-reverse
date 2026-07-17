#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000133f8 @ 0x000133f8
 * public-name: FUN_000133f8
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_88878                             @ 0x00088878
 *   rodata_88888                             @ 0x00088888
 *   g_sram_base_word                         @ 0x20000000
 */
/* Reconstructed FUN_000133f8 @ 0x133f8  (parity: 300/300 trials, PROVEN) */
typedef unsigned int u32;
typedef unsigned long long u64;
extern u64 orc(void);

double FUN_000133f8(double xd, double yd)
{
    union U { double d; u64 u; } X, Y, R;
    X.d = xd; Y.d = yd;
    u32 xlo = (u32)X.u, xhi = (u32)(X.u >> 32);
    u32 ylo = (u32)Y.u, yhi = (u32)(Y.u >> 32);

    u32 r0=0,r1=0,r2=0,r3=0,r4=0,r5=0,r6=0,r7=0,r8=0,r9=0,r10=0,r11=0;
    u32 sp00=0,sp04=0,sp08=0,sp0c=0,sp10=0,sp14=0,sp18=0,sp1c=0,
        sp24=0,sp28=0,sp2c=0,sp30=0,sp34=0,sp38=0,sp3c=0;
    u64 _t;
#define CALL()  do{ _t = orc(); r0=(u32)_t; r1=(u32)(_t>>32);}while(0)
#define CALLV() do{ (void)orc(); }while(0)

    /* entry 0x133f8 */
    sp00 = ylo; sp04 = yhi;
    r3 = sp00; r8 = sp04;
    r6 = xlo; r7 = xhi;
    r9 = r8 & 0x7fffffff;
    r2 = r9 | r3; if (r2 == 0) goto L13560;
    r4 = r7 & 0x7fffffff;
    r2 = 0x7ff00000;
    r5 = r7; r10 = r6;
    sp08 = r4;
    if (r4 > r2) goto L1345a;
    if (r4 != r2) goto L13450;
    if (r6 != 0) goto L13468;
    if (r9 > r4) goto L13468;
    if (r9 != r4) goto L13474;
    if (r3 != 0) goto L13468;

L13432:
    r3 = 0x3fefffff;
    if (r4 <= r3) goto L13566;
    if ((int)r8 >= 0) goto L13dd0;
    r0 = 0; r1 = 0;
L13446:
    R.u = ((u64)r1 << 32) | r0;
    return R.d;

L13450:
    if (r9 > r2) goto L1345a;
    if (r9 != r2) goto L13474;
    if (r3 == 0) goto L13552;
L1345a:
    r4 = r4 + (u32)(-0x40000000);
    r4 = r4 + 0x100000;
    r4 = r4 | r10;
    if (r4 == 0) goto L13560;
L13468:
    CALLV();
    return xd;

L13474:
    if ((int)r5 >= 0) goto L1348a;
    r2 = 0x433fffff;
    if (r9 <= r2) goto L13496;
    if (r3 == 0) goto L135c8;
L13484:
    r11 = 2;
    goto L134d2;

L1348a:
    if (r3 == 0) goto L135a6;
    r11 = 0;
    goto L134d2;

L13496:
    r2 = 0x3fefffff;
    if (r9 > r2) goto L134aa;
L1349c:
    if (r3 != 0) goto L13490;
L134a0:
    if (r8 == 0x40000000) goto L1357e;
L134a6:
    r11 = r3;
    goto L134d2;

L13490:
    r11 = 0;
    goto L134d2;

L134aa:
    r2 = (u32)((int)r9 >> 0x14);
    r2 = r2 - 0x3ff;
    if ((int)r2 <= 0x14) goto L13528;
    r2 = 0x34 - r2;
    r1 = r3 >> r2;
    { u32 tmp = r1 << r2; if (tmp != r3) goto L1349c; }
    r1 = r1 & 1;
    r11 = 2 - r1;
    if (r3 == 0) goto L13578;
    goto L134d2;

L13528:
    if (r3 != 0) goto L13490;
    { u32 sh = 0x14 - r2;
      r1 = (u32)((int)r9 >> sh);
      u32 shifted = r1 << sh;
      u32 ne = (shifted != r9);
      r2 = 0x3ff00000;
      if (ne) goto L1358c;
    }
    if (r9 == r2) goto L13590;
    if (r8 == 0x40000000) goto L1357e;
    r1 = r1 & 1;
    r11 = 2 - r1;
    goto L134d2;

L13552:
    r3 = r4 + (u32)(-0x40000000);
    r3 = r3 + 0x100000;
    r3 = r3 | r6;
    if (r3 != 0) goto L13432;
L13560:
    r0 = 0; r1 = 0x3ff00000;
    goto L13446;

L13566:
    if ((int)r8 >= 0) goto L13442;
    r0 = sp00; r3 = sp04;
    r1 = r3 + 0x80000000u;
    goto L13446;
L13442:
    r0 = 0; r1 = 0;
    goto L13446;

L13578:
    if (r8 != 0x40000000) goto L134d2;
L1357e:
    r2 = r6; r3 = r7;
L13582:
    r0 = r2; r1 = r3;
L13586:
    CALL();
    goto L13446;

L1358c:
    if (r9 != 0x3ff00000) goto L134a0;
L13590:
    if ((int)r8 >= 0) goto L13dd8;
    r2 = r6; r3 = r7; r0 = 0; r1 = 0x3ff00000;
L135a0:
    CALL();
    goto L13446;

L135a6:
    r2 = 0x3ff00000;
    if (r9 == r2) goto L13590;
    if (r8 == 0x40000000) goto L1357e;
    r2 = 0x3fe00000;
    if (r8 != r2) goto L134a6;
    CALLV();
    R.u = ((u64)r7 << 32) | r6;
    return R.d;

L135c8:
    if (r8 != 0x40000000) goto L13484;
    goto L1357e;

L135d2:
    if (r11 != 1) goto L13446;
    r3 = r1 + 0x80000000u;
    r1 = r3;
    goto L13446;

L134d2:
    CALLV();
    r0 = r6; r1 = r7;
    if (r10 != 0) goto L135e2;
    r2 = r5 & ~0xc0000000u;
    r3 = 0x3ff00000;
    if (r2 == r3) goto L134f2;
    if (r4 != 0) goto L135e2;
L134f2:
    if ((int)r8 >= 0) goto L13504;
    r2 = r0; r3 = r1; r0 = 0; r1 = 0x3ff00000;
    CALL();
L13504:
    if ((int)r5 >= 0) goto L13446;
    r4 = r4 + (u32)(-0x40000000);
    r4 = r4 + 0x100000;
    r4 = r4 | r11;
    if (r4 != 0) goto L135d2;
    r2 = r0; r3 = r1;
L1351a:
    r0 = r2; r1 = r3;
    CALL();
    r2 = r0; r3 = r1;
    goto L135a0;

L135e2:
    r3 = r5 >> 0x1f;
    r3 = r3 - 1;
    sp30 = r3;
    r3 = r11 | r3;
    if (r3 != 0) goto L135f4;
    r2 = r6; r3 = r7;
    goto L1351a;
L135f4:
    r3 = 0x41e00000;
    if (r9 <= r3) goto L137f8;
    r3 = r3 + 0x2100000;
    { u32 cc = (r9 <= r3); r3 = 0x3fefffff; if (cc) goto L1361a; }
    if (r4 > r3) goto L13624;
L1360a:
    if ((int)r8 >= 0) goto L13442;
L13612:
    r2 = 0x8800759c; r3 = 0x7e37e43c;
    goto L13582;
L1361a:
    if (r4 < r3) goto L1360a;
    r3 = 0x3ff00000;
    if (r4 <= r3) goto L13654;
L13624:
    if ((int)r8 > 0) goto L13612;
    goto L13442;

    /* ---- block A (0x13654) ---- */
L13654:
    r2 = 0; r3 = 0x3ff00000;
    CALL();
    r4 = r0; r5 = r1;
    r2 = 0x60000000; r3 = 0x3ff71547;
    CALL();
    r6 = r0; r7 = r1;
    r0 = r4; r1 = r5;
    r2 = 0xf85ddf44; r3 = 0x3e54ae0b;
    CALL();
    r2 = 0; r3 = 0x3fd00000;
    sp08 = r0; sp0c = r1;
    r0 = r4; r1 = r5;
    CALL();
    r2 = r0; r3 = r1;
    r0 = 0x55555555; r1 = 0x3fd55555;
    CALL();
    r2 = r4; r3 = r5;
    CALL();
    r2 = r0; r3 = r1;
    r0 = 0; r1 = 0x3fe00000;
    CALL();
    r8 = r0; r9 = r1;
    r2 = r4; r3 = r5;
    r0 = r4; r1 = r5;
    r4 = 0;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r8; r1 = r9;
    CALL();
    r2 = 0x652b82fe; r3 = 0x3ff71547;
    CALL();
    r2 = r0; r3 = r1;
    r0 = sp08; r1 = sp0c;
    CALL();
    r2 = r0; r3 = r1;
    r8 = r0; r9 = r1;
    r0 = r6; r1 = r7;
    CALL();
    r2 = r6; r3 = r7;
    r0 = r4;
    r5 = r1;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r8; r1 = r9;
L13706:
    CALL();
    r3 = r11 - 1;
    r2 = sp30;
    r6 = r0; r7 = r1;
    r3 = r3 | r2;
L1371a:
    r2 = sp00; r3 = sp04;
    r0 = sp00; r1 = sp04;
    sp10 = r2; sp14 = r3;
    r3 = 0;
    sp10 = 0;
    r10 = sp10; r11 = sp14;
    sp08 = 0; sp0c = 0;
    r3 = r11; r2 = r10;
    CALL();
    r2 = r4; r3 = r5;
    CALL();
    r8 = r0; r9 = r1;
    r0 = r6; r1 = r7;
    r2 = sp00; r3 = sp04;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r8; r1 = r9;
    CALL();
    r6 = r0; r7 = r1;
    r3 = r11; r2 = r10;
    r0 = r4; r1 = r5;
    CALL();
    r3 = r1; r2 = r0; r8 = r0; r9 = r1;
    r0 = r6; r1 = r7;
    CALL();
    r4 = r0; r5 = r1;
    r11 = r1;
    if ((int)r1 <= (int)0x408fffff) goto L13bac;
    r3 = r1 + (u32)(-0x41000000);
    r3 = r3 + 0x700000;
    r3 = r3 | r0;
    if (r3 == 0) goto L13b76;
L1379e:
    r2 = 0x8800759c; r3 = 0x7e37e43c;
    r0 = sp08; r1 = sp0c;
    CALL();
    r2 = 0x8800759c; r3 = 0x7e37e43c;
    goto L13586;

L13b6a:
    r10 = 1;
    goto L13842;

L13b70:
    goto L1371a;

L13b76:
    r2 = 0x652b82fe; r3 = 0x3c971547;
    r0 = r6; r1 = r7;
    CALL();
    r2 = r8; r3 = r9;
    sp00 = r0; sp04 = r1;
    r0 = r4; r1 = r5;
    CALL();
    r2 = r0; r3 = r1;
    r0 = sp00; r1 = sp04;
    CALL();
    if (r0 != 0) goto L1379e;
    goto L13ba6;

    /* ---- block B (0x137f8) ---- */
L137f8:
    r3 = 0x7ff00000;
    r2 = 0;
    r3 = r3 & r5;
    if (r3 != 0) goto Lx1380c;
    r3 = 0x43400000;
    CALL();
    r2 = (u32)(~0x34);
    sp08 = r1;
Lx1380c:
    r3 = sp08;
    r3 = (u32)((int)r3 >> 0x14);
    r3 = r3 - 0x3ff;
    r3 = r3 + r2;
    sp24 = r3;
    r3 = sp08;
    r10 = r3 & 0xfffff;
    r3 = 0x0003988e;
    r5 = r10 | 0x3fc00000;
    r5 = r5 | 0x300000;
    if ((int)r10 <= (int)r3) goto Lx1383e;
    r3 = 0x000bb679;
    if ((int)r10 <= (int)r3) goto L13b6a;
    r3 = sp24;
    r5 = r5 - 0x100000;
    r3 = r3 + 1;
    sp24 = r3;
Lx1383e:
    r10 = 0;
L13842:
    r3 = r10 << 3;
    r1 = r5;
    r5 = (u32)((int)r5 >> 1);
    sp34 = r3;
    r5 = r5 | ((unsigned long)&g_sram_base_word) /*=0x20000000*/;
    r5 = r5 + 0x80000;
    r2 = 0; r3 = 0;
    sp28 = r0; sp2c = r1;
    sp18 = 0; sp1c = 0;
    CALL();
    r6 = r0; r7 = r1;
    r2 = sp28; r3 = sp2c;
    r0 = sp18; r1 = sp1c;
    CALL();
    r2 = r0; r3 = r1;
    r0 = 0; r1 = 0x3ff00000;
    CALL();
    r2 = r0; r3 = r1;
    sp38 = r0; sp3c = r1;
    r0 = r6; r1 = r7;
    CALL();
    r2 = 0;
    sp10 = r0; sp14 = r1;
    r3 = sp10; r4 = sp14;
    sp08 = r3; sp0c = r4;
    r3 = 0;
    r4 = r2;
    sp08 = r3;
    r3 = r5 + (r10 << 18);
    r8 = sp08; r9 = sp0c;
    r5 = r3;
    r0 = r8; r1 = r9;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r6; r1 = r7;
    CALL();
    r6 = r0; r7 = r1;
    r0 = r4; r1 = r5;
    r2 = sp18; r3 = sp1c;
    CALL();
    r2 = r0; r3 = r1;
    r0 = sp28; r1 = sp2c;
    CALL();
    r2 = r8; r3 = r9;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r6; r1 = r7;
    CALL();
    r2 = sp38; r3 = sp3c;
    CALL();
    r2 = sp10; r3 = sp14;
    sp18 = r0; sp1c = r1;
    r0 = r2; r1 = r3;
    CALL();
    r4 = r0; r5 = r1;
    r2 = 0x4a454eef; r3 = 0x3fca7e28;
    CALL();
    r2 = 0x93c9db65; r3 = 0x3fcd864a;
    CALL();
    r2 = r4; r3 = r5;
    CALL();
    r2 = 0xa91d4101; r3 = 0x3fd17460;
    CALL();
    r2 = r4; r3 = r5;
    CALL();
    r2 = 0x518f264d; r3 = 0x3fd55555;
    CALL();
    r2 = r4; r3 = r5;
    CALL();
    r2 = 0xdb6fabff; r3 = 0x3fdb6db6;
    CALL();
    r2 = r4; r3 = r5;
    CALL();
    r2 = 0x33333303; r3 = 0x3fe33333;
    CALL();
    r6 = r0; r7 = r1;
    r2 = r4; r3 = r5; r0 = r4; r1 = r5;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r6; r1 = r7;
    CALL();
    r2 = r8; r3 = r9;
    r4 = r0; r5 = r1;
    r0 = sp10; r1 = sp14;
    CALL();
    r2 = sp18; r3 = sp1c;
    CALL();
    r2 = r4; r3 = r5;
    r4 = 0;
    CALL();
    r2 = r8; r3 = r9;
    sp28 = r0; sp2c = r1;
    r0 = r8; r1 = r9;
    CALL();
    r2 = 0; r3 = 0x40080000;
    r6 = r0; r7 = r1;
    CALL();
    r2 = sp28; r3 = sp2c;
    CALL();
    r5 = r1;
    r2 = r4; r3 = r1;
    r0 = r8; r1 = r9;
    CALL();
    r2 = 0;
    r8 = r0; r9 = r1;
    r3 = 0x40080000;
    r0 = r4; r1 = r5;
    CALL();
    r2 = r6; r3 = r7;
    CALL();
    r2 = r0; r3 = r1;
    r0 = sp28; r1 = sp2c;
    CALL();
    r2 = sp10; r3 = sp14;
    CALL();
    r6 = r0; r7 = r1;
    r2 = r4; r3 = r5;
    r4 = 0;
    r0 = sp18; r1 = sp1c;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r6; r1 = r7;
    CALL();
    r6 = r0; r7 = r1;
    r2 = r0; r3 = r1;
    r0 = r8; r1 = r9;
    CALL();
    r5 = r1;
    r0 = r4;
    r2 = 0xe0000000; r3 = 0x3feec709;
    CALL();
    r2 = r8; r3 = r9;
    sp10 = r0; sp14 = r1;
    r0 = r4; r1 = r5;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r6; r1 = r7;
    CALL();
    r2 = 0xdc3a03fd; r3 = 0x3feec709;
    CALL();
    r6 = r0; r7 = r1;
    r0 = r4; r1 = r5;
    r4 = 0;
    r2 = 0x145b01f5; r3 = 0xbe3e2fe0;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r6; r1 = r7;
    CALL();
    r2 = sp34;
    r3 = ((unsigned long)&rodata_88878) /*=0x88878*/; r3 = r3 + r2;
    r2 = 0; r3 = 0;
    CALL();
    sp18 = r0; sp1c = r1;
    r0 = sp24;
    CALL();
    r2 = sp34;
    r3 = ((unsigned long)&rodata_88888) /*=0x88888*/; r3 = r3 + r2;
    r6 = r0; r7 = r1;
    r8 = 0; r9 = 0;
    r0 = sp10; r1 = sp14;
    r2 = sp18; r3 = sp1c;
    CALL();
    r2 = r8; r3 = r9;
    CALL();
    r2 = r6; r3 = r7;
    CALL();
    r2 = r6; r3 = r7;
    r0 = r4; r5 = r1;
    CALL();
    r2 = r8; r3 = r9;
    CALL();
    r2 = sp10; r3 = sp14;
    CALL();
    r2 = r0; r3 = r1;
L13b64:
    r0 = sp18; r1 = sp1c;
    goto L13706;

    /* ---- z small (0x13bac) ---- */
L13bac:
    r3 = r1 & 0x7fffffff;
    r4 = 0x4090cbff;
    if (r3 <= r4) goto L13bea;
    r3 = 0x3f6f3400;
    r3 = r3 + r1;
    r3 = r3 | r0;
    if (r3 == 0) goto L13bd4;
L13bbe:
    r2 = 0xc2f8f359; r3 = 0x01a56e1f;
    r0 = sp08; r1 = sp0c;
    CALL();
    r2 = 0xc2f8f359; r3 = 0x01a56e1f;
    goto L13586;
L13bd4:
    r2 = r8; r3 = r9;
    CALL();
    r2 = r6; r3 = r7;
    CALL();
    if (r0 == 0) goto L13ba6;
    goto L13bbe;
L13bea:
    r2 = 0x3fe00000;
    if (r3 <= r2) goto L13dc2;
    r3 = (u32)((int)r3 >> 0x14);
L13bf4:
    r3 = r3 - 0x3fe;
    r10 = 0x100000;
    r0 = 0xfff00000;
    r10 = (u32)((int)r10 >> r3);
    r2 = 0;
    r10 = r10 + r11;
    r1 = (r10 >> 0x14) & 0x7ff;
    r1 = r1 - 0x3ff;
    r0 = (u32)((int)r0 >> r1);
    r1 = 0x14 - r1;
    r3 = r0 & r10;
    r10 = r10 & 0xfffff;
    r0 = r8;
    r10 = r10 | 0x100000;
    r10 = (u32)((int)r10 >> r1);
    r1 = r9;
    if ((int)r11 < 0) r10 = (u32)(-(int)r10);
    CALL();
    r8 = r0; r9 = r1;
L13c3e:
    r4 = 0;
    r2 = r6; r3 = r7;
    r0 = r8; r1 = r9;
    CALL();
    r5 = r1;
    r0 = r4;
    r2 = 0x00000000; r3 = 0x3fe62e43;
    CALL();
    r2 = r8; r3 = r9;
    sp00 = r0; sp04 = r1;
    r0 = r4; r1 = r5;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r6; r1 = r7;
    CALL();
    r2 = 0xfefa39ef; r3 = 0x3fe62e42;
    CALL();
    r8 = r0; r9 = r1;
    r0 = r4; r1 = r5;
    r2 = 0x0ca86c39; r3 = 0xbe205c61;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r8; r1 = r9;
    CALL();
    r4 = r0; r5 = r1;
    r2 = r0; r3 = r1;
    r0 = sp00; r1 = sp04;
    CALL();
    r8 = r0; r9 = r1;
    r2 = sp00; r3 = sp04;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r4; r1 = r5;
    CALL();
    r2 = r8; r3 = r9;
    r6 = r0; r7 = r1;
    r0 = r8; r1 = r9;
    CALL();
    r4 = r0; r5 = r1;
    r2 = 0x72bea4d0; r3 = 0x3e663769;
    CALL();
    r2 = 0xc5d26bf1; r3 = 0x3ebbbd41;
    CALL();
    r2 = r4; r3 = r5;
    CALL();
    r2 = 0xaf25de2c; r3 = 0x3f11566a;
    CALL();
    r2 = r4; r3 = r5;
    CALL();
    r2 = 0x16bebd93; r3 = 0x3f66c16c;
    CALL();
    r2 = r4; r3 = r5;
    CALL();
    r2 = 0x5555553e; r3 = 0x3fc55555;
    CALL();
    r2 = r4; r3 = r5;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r8; r1 = r9;
    CALL();
    r4 = r0; r5 = r1;
    r2 = r0; r3 = r1;
    r0 = r8; r1 = r9;
    CALL();
    r2 = 0; r3 = 0x40000000;
    sp00 = r0; sp04 = r1;
    r0 = r4; r1 = r5;
    CALL();
    r2 = r0; r3 = r1;
    r0 = sp00; r1 = sp04;
    CALL();
    r2 = r6;
    r4 = r0; r5 = r1;
    r3 = r7;
    r0 = r8; r1 = r9;
    CALL();
    r2 = r6; r3 = r7;
    CALL();
    r2 = r0; r3 = r1;
    r0 = r4; r1 = r5;
    CALL();
    r2 = r8; r3 = r9;
    CALL();
    r3 = r1; r2 = r0;
    r1 = 0x3ff00000;
    r0 = 0;
    CALL();
    r3 = r1;
    r3 = r3 + (r10 << 20);
    if ((int)r3 >= 0x100000) goto L13dc8;
    CALLV();
L13dba:
    r2 = sp08; r3 = sp0c;
    goto L13586;
L13dc8:
    r1 = r3;
    goto L13dba;

L13ba6:
    r3 = 0x409;
    goto L13bf4;

L13dc2:
    r10 = sp10;
    goto L13c3e;

L13dd0:
    r0 = sp00; r1 = sp04;
    goto L13446;
L13dd8:
    r0 = r6; r1 = r7;
    goto L13446;
}
