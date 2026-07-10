/* Reconstructed ui_even_ai_task @ 0x3bfe0  (parity: 40/40 trials, PROVEN) */
#include <stdint.h>
#pragma GCC diagnostic warning "-Wint-conversion"
#pragma GCC diagnostic warning "-Wimplicit-int"
#pragma GCC diagnostic warning "-Wimplicit-function-declaration"
#pragma GCC diagnostic warning "-Wint-to-pointer-cast"
#pragma GCC diagnostic warning "-Wpointer-to-int-cast"
#pragma GCC diagnostic warning "-Wincompatible-pointer-types"
#pragma GCC diagnostic warning "-Wdiscarded-qualifiers"
typedef uint8_t undefined1; typedef uint8_t byte; typedef uint8_t undefined; typedef uint8_t uchar;
typedef uint16_t undefined2; typedef uint16_t ushort; typedef uint16_t wchar_t;
typedef uint32_t undefined4; typedef uint32_t uint;
typedef long long code(int,...);
typedef uint64_t undefined8; typedef uint64_t ulonglong;
typedef int64_t longlong; typedef int32_t int32; typedef unsigned int uint3;
static inline int CARRY4(uint a, uint b){return (a+b)<a;}
static inline int CARRY1(uint a, uint b){return ((a&0xff)+(b&0xff))>0xff;}
static inline int CARRY2(uint a, uint b){return ((a&0xffff)+(b&0xffff))>0xffff;}
static inline int SBORROW4(int a,int b){int r=(int)((uint)a-(uint)b);return (((a^b)&(a^r))<0);}
static inline int SBORROW1(int a,int b){signed char r=(signed char)(a-b);return ((((signed char)a^(signed char)b)&((signed char)a^r))<0);}
static inline int SBORROW2(int a,int b){short r=(short)(a-b);return ((((short)a^(short)b)&((short)a^r))<0);}
#define CONCAT11(a,b) ((ushort)(((ushort)(uint8_t)(a)<<8)|(uint8_t)(b)))
#define CONCAT22(a,b) ((uint)(((uint)(ushort)(a)<<16)|(ushort)(b)))
#define CONCAT44(a,b) ((ulonglong)(((ulonglong)(uint)(a)<<32)|(uint)(b)))
#define CONCAT13(a,b) ((uint)(((uint)(uint8_t)(a)<<24)|((uint)(b)&0xffffff)))
#define CONCAT31(a,b) ((uint)(((uint)(a)<<8)|(uint8_t)(b)))
#define CONCAT12(a,b) ((uint)(((uint)(uint8_t)(a)<<16)|(ushort)(b)))
#define CONCAT21(a,b) ((uint)(((uint)(ushort)(a)<<8)|(uint8_t)(b)))
#define CONCAT111(a,b,c) ((uint)(((uint)(uint8_t)(a)<<16)|((uint)(uint8_t)(b)<<8)|(uint8_t)(c)))
#define CONCAT411(a,b,c) ((ulonglong)(((ulonglong)(uint)(a)<<16)|((uint)(uint8_t)(b)<<8)|(uint8_t)(c)))
#define SUB84(x,o) ((uint)((ulonglong)(x)>>((o)*8)))
#define SUB82(x,o) ((ushort)((ulonglong)(x)>>((o)*8)))
#define SUB81(x,o) ((uint8_t)((ulonglong)(x)>>((o)*8)))
#define SUB41(x,o) ((uint8_t)((uint)(x)>>((o)*8)))
#define SUB42(x,o) ((ushort)((uint)(x)>>((o)*8)))
#define SUB21(x,o) ((uint8_t)((ushort)(x)>>((o)*8)))
#define SUBF(v,o,s) ((ulonglong)((ulonglong)(v)>>((o)*8)) & ((s)>=8?~0ULL:((1ULL<<((s)*8))-1)))
#define NAN (__builtin_nanf(""))
#define INFINITY (__builtin_inff())

extern long long DEBUG_PRINT__impl(int, ...);
#define DEBUG_PRINT(...) DEBUG_PRINT__impl(0, ##__VA_ARGS__)
extern long long FUN_000167a8__impl(int, ...);
#define FUN_000167a8(...) FUN_000167a8__impl(0, ##__VA_ARGS__)
extern long long FUN_00019c70__impl(int, ...);
#define FUN_00019c70(...) FUN_00019c70__impl(0, ##__VA_ARGS__)
extern long long FUN_00023ee0__impl(int, ...);
#define FUN_00023ee0(...) FUN_00023ee0__impl(0, ##__VA_ARGS__)
extern long long FUN_0003be18__impl(int, ...);
#define FUN_0003be18(...) FUN_0003be18__impl(0, ##__VA_ARGS__)
extern long long FUN_000431b4__impl(int, ...);
#define FUN_000431b4(...) FUN_000431b4__impl(0, ##__VA_ARGS__)
extern long long FUN_000431c0__impl(int, ...);
#define FUN_000431c0(...) FUN_000431c0__impl(0, ##__VA_ARGS__)
extern long long FUN_000432d0__impl(int, ...);
#define FUN_000432d0(...) FUN_000432d0__impl(0, ##__VA_ARGS__)
extern long long FUN_000432ec__impl(int, ...);
#define FUN_000432ec(...) FUN_000432ec__impl(0, ##__VA_ARGS__)
extern long long FUN_00043308__impl(int, ...);
#define FUN_00043308(...) FUN_00043308__impl(0, ##__VA_ARGS__)
extern long long FUN_00043484__impl(int, ...);
#define FUN_00043484(...) FUN_00043484__impl(0, ##__VA_ARGS__)
extern long long FUN_000436f8__impl(int, ...);
#define FUN_000436f8(...) FUN_000436f8__impl(0, ##__VA_ARGS__)
extern long long FUN_0004382c__impl(int, ...);
#define FUN_0004382c(...) FUN_0004382c__impl(0, ##__VA_ARGS__)
extern long long FUN_0004396c__impl(int, ...);
#define FUN_0004396c(...) FUN_0004396c__impl(0, ##__VA_ARGS__)
extern long long FUN_00043e90__impl(int, ...);
#define FUN_00043e90(...) FUN_00043e90__impl(0, ##__VA_ARGS__)
extern long long FUN_000440ec__impl(int, ...);
#define FUN_000440ec(...) FUN_000440ec__impl(0, ##__VA_ARGS__)
extern long long FUN_00044bd8__impl(int, ...);
#define FUN_00044bd8(...) FUN_00044bd8__impl(0, ##__VA_ARGS__)
extern long long FUN_000471cc__impl(int, ...);
#define FUN_000471cc(...) FUN_000471cc__impl(0, ##__VA_ARGS__)
extern long long FUN_00047260__impl(int, ...);
#define FUN_00047260(...) FUN_00047260__impl(0, ##__VA_ARGS__)
extern long long FUN_000723b8__impl(int, ...);
#define FUN_000723b8(...) FUN_000723b8__impl(0, ##__VA_ARGS__)
extern long long FUN_00072558__impl(int, ...);
#define FUN_00072558(...) FUN_00072558__impl(0, ##__VA_ARGS__)
extern long long FUN_0007d3dc__impl(int, ...);
#define FUN_0007d3dc(...) FUN_0007d3dc__impl(0, ##__VA_ARGS__)
extern long long FUN_0007d3ee__impl(int, ...);
#define FUN_0007d3ee(...) FUN_0007d3ee__impl(0, ##__VA_ARGS__)
extern long long FUN_0007d446__impl(int, ...);
#define FUN_0007d446(...) FUN_0007d446__impl(0, ##__VA_ARGS__)
extern long long FUN_00086c1e__impl(int, ...);
#define FUN_00086c1e(...) FUN_00086c1e__impl(0, ##__VA_ARGS__)
extern long long FUN_00086c78__impl(int, ...);
#define FUN_00086c78(...) FUN_00086c78__impl(0, ##__VA_ARGS__)

#define DAT_0003c2dc ((volatile int*)0x200024ecUL)
#define DAT_0003c2e0 (0x8a3a8UL)
#define DAT_0003c2e4 ((volatile char*)0x2001b9a8UL)
#define DAT_0003c2e8 (0x8a370UL)
#define DAT_0003c2ec ((volatile int*)0x2000230cUL)
#define DAT_0003c2f0 (0x2001b818UL)
#define DAT_0003c2f4 ((volatile int*)0x20007554UL)
#define DAT_0003c2f8 (0xa98ceUL)
#define DAT_0003c2fc (0xa9855UL)
#define DAT_0003c300 (0xa9879UL)
#define DAT_0003c304 ((volatile int*)0x20009fd8UL)
#define DAT_0003c308 ((volatile undefined4*)0x2000a038UL)
#define DAT_0003c30c (0x2001cdd7UL)
#define DAT_0003c310 (0xaae20UL)
#define DAT_0003c314 (0xa989fUL)
#define DAT_0003c318 ((volatile undefined4*)0xa8e98UL)
#define DAT_0003c644 (0x0UL) /* unknown lit */
#define DAT_0003c648 (0x0UL) /* unknown lit */
#define DAT_0003c64c ((volatile int*)0x0UL)
#define DAT_0003c650 (0x0UL) /* unknown lit */
#define DAT_0003c654 ((volatile int*)0x0UL)
#define DAT_0003c658 ((volatile undefined4*)0x0UL)
#define DAT_0003c9a8 (0x0UL) /* unknown lit */
#define DAT_0003c9ac (0x0UL) /* unknown lit */
#define DAT_0003c9b0 ((volatile int*)0x0UL)
#define DAT_0003cb2c (0x0UL) /* unknown lit */
#define DAT_0003cb30 ((volatile int*)0x0UL)
#define DAT_0003cb34 ((volatile int*)0x0UL)
#define DAT_0003cb38 (0x0UL) /* unknown lit */
#define DAT_0003cb3c ((volatile int*)0x0UL)
#define DAT_0003cb40 ((volatile int*)0x0UL)
#define DAT_0003cb44 (0x0UL) /* unknown lit */
#define DAT_0003cb48 (0x0UL) /* unknown lit */


undefined4 ui_even_ai_task(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined4 extraout_r1;
  undefined4 uVar13;
  int iVar14;
  int *piVar15;
  int *piVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  int iVar19;
  undefined4 uVar20;
  int iVar21;
  int iVar22;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  iVar14 = param_3;
  iVar5 = FUN_000167a8();
  param_1 = param_1 + 0x24;
  iVar6 = FUN_00023ee0();
  piVar15 = (int *)(uint)*(byte *)(iVar5 + 0xef);
  piVar16 = piVar15;
  if (piVar15 != (int *)0x7) {
    iVar14 = -1;
    piVar16 = DAT_0003c2dc;
  }
  uVar7 = iVar6 - 1U & 0xff;
  if (piVar15 != (int *)0x7) {
    *piVar16 = iVar14;
  }
  pcVar3 = DAT_0003c2e4;
  if (uVar7 < 0xe) {
    uVar20 = *(undefined4 *)(DAT_0003c2e0 + uVar7 * 4);
    uVar18 = *(undefined4 *)(DAT_0003c2e8 + uVar7 * 4);
  }
  else {
    uVar18 = 0;
    uVar20 = uVar18;
  }
  FUN_000431b4(param_1);
  FUN_000432d0();
  piVar16 = DAT_0003c2ec;
  if (*pcVar3 == '\0') {
    if (param_3 == 1) {
      FUN_00086c78(DAT_0003c2f0,0,400);
      if (0 < *piVar16) {
        if (*DAT_0003c2f4 == 0) {
          DEBUG_PRINT(DAT_0003c2fc,DAT_0003c2f8);
        }
        else {
          FUN_00019c70();
        }
      }
      if (pcVar3[1] != '\0') {
        return 0;
      }
      if (0 < *piVar16) {
        if (*DAT_0003c2f4 == 0) {
          DEBUG_PRINT(DAT_0003c300,DAT_0003c2f8);
        }
        else {
          FUN_00019c70();
        }
      }
      FUN_0007d3dc();
      if (*(byte *)(iVar5 + 0xef) < 0xc) {
        FUN_000431c0();
      }
      iVar14 = 0;
      *DAT_0003c304 = 0;
      FUN_000436f8();
      puVar4 = DAT_0003c308;
      DAT_0003c308[7] = 0x80;
      uVar8 = DAT_0003c30c;
      puVar4[2] = 0;
      puVar4[3] = 0;
      *puVar4 = uVar8;
      puVar4[5] = 0;
      puVar4[6] = 0;
      puVar4[1] = 0;
      puVar4[4] = 0;
      pcVar3[1] = '\x01';
      *pcVar3 = '\x01';
      FUN_00043308();
      uVar8 = FUN_000432ec();
      do {
        uVar7 = (uint)*(byte *)(iVar5 + 0xef);
        if (uVar7 == 0xb) {
          uVar8 = FUN_0007d3ee();
          iVar6 = FUN_0007d446();
          FUN_00043484(0x49,uVar8,iVar6 + 0x36,0,0,0);
          iVar10 = FUN_0007d3ee();
          iVar11 = FUN_0007d446();
          iVar6 = FUN_0007d3ee();
          iVar9 = FUN_0007d446();
          iVar11 = iVar11 + 0x36;
          uVar13 = 3;
          iVar9 = iVar9 + 0x87;
          iVar6 = iVar6 + 0x230;
          iVar10 = iVar10 + 0x58;
          uVar8 = uVar18;
LAB_0003c12a:
          FUN_00043e90(0,uVar8,0,iVar10,iVar11,iVar6,iVar9,uVar13,0,0,0,0);
        }
        else {
          if (uVar7 - 0xc < 3) {
            if (uVar7 != 0xe) {
              return uVar8;
            }
            iVar14 = FUN_000167a8();
            uVar20 = *(undefined4 *)(iVar14 + 0xeb4);
            iVar14 = FUN_000167a8();
            FUN_00047260(uVar20,*(undefined4 *)(iVar14 + 0xeb8),0,0,0x27f,199);
            break;
          }
          if (uVar7 - 0xf < 2) {
            if (uVar7 != 0x10) {
              return uVar8;
            }
            FUN_00086c1e(DAT_0003c2f0,iVar5 + 0xf6,*(undefined2 *)(iVar5 + 0x286),400);
            iVar10 = FUN_0007d3ee();
            iVar11 = FUN_0007d446();
            iVar6 = FUN_0007d3ee();
            iVar9 = FUN_0007d446();
            iVar9 = iVar9 + 0x88;
            iVar6 = iVar6 + 0x240;
            uVar13 = 5;
            uVar8 = DAT_0003c2f0;
            goto LAB_0003c12a;
          }
          uVar8 = FUN_0007d3ee();
          iVar6 = FUN_0007d446();
          iVar9 = FUN_0007d3ee();
          iVar10 = FUN_0007d446();
          FUN_00044bd8(0,uVar20,0,uVar8,iVar6 + 0x36,iVar9 + 0x236,iVar10 + 0x87,3,0,0,0,0);
        }
        puVar4 = DAT_0003c318;
        uVar7 = 0;
        local_30 = *DAT_0003c318;
        do {
          uStack_2c = puVar4[1];
          iVar6 = 0;
          do {
            iVar9 = *(int *)(param_1 + uVar7 * 4);
            bVar2 = *(byte *)(iVar9 + iVar6);
            if (bVar2 != 0) {
              *(byte *)(iVar9 + iVar6) =
                   bVar2 & *(byte *)((uint)*(byte *)((int)&local_30 + iVar14) * 0x140 +
                                     (uVar7 % 0x1a) * 0xa00 + DAT_0003c310 + iVar6);
            }
            iVar6 = iVar6 + 1;
          } while (iVar6 != 0x140);
          uVar7 = uVar7 + 1;
        } while (uVar7 != 199);
        iVar6 = FUN_000167a8();
        uVar8 = *(undefined4 *)(iVar6 + 0xeb4);
        iVar6 = FUN_000167a8();
        iVar14 = iVar14 + 1;
        uVar8 = FUN_00047260(uVar8,*(undefined4 *)(iVar6 + 0xeb8),0,0,0x280,199);
      } while (iVar14 != 8);
LAB_0003c204:
      FUN_000432d0();
      return 0;
    }
    if (param_3 != 2) {
      return 0;
    }
    if (2 < *DAT_0003c2ec) {
      if (*DAT_0003c2f4 == 0) {
        DEBUG_PRINT(DAT_0003c314,DAT_0003c2f8);
      }
      else {
        FUN_00019c70();
      }
    }
    FUN_000431c0();
LAB_0003c2be:
    FUN_0007d3dc();
    puVar4 = DAT_0003c308;
    pcVar3[0] = '\0';
    pcVar3[1] = '\0';
    puVar4[2] = 0;
    puVar4[3] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[1] = 0;
    puVar4[4] = 0;
    return 0;
  }
  if (*pcVar3 != '\x01') {
    return 0;
  }
  iVar14 = iVar5 + 0xef;
  if (param_3 != 1) {
    if (param_3 == 0) {
      FUN_0003be18(iVar14);
      return 0;
    }
    if (param_3 != 2) {
      return 0;
    }
    if (2 < *DAT_0003cb3c) {
      if (*DAT_0003cb40 == 0) {
        DEBUG_PRINT(DAT_0003cb48,DAT_0003cb44);
      }
      else {
        FUN_00019c70();
      }
    }
    FUN_0004382c();
    goto LAB_0003c2be;
  }
  FUN_00086c78(DAT_0003c644,0,400);
  FUN_000723b8(DAT_0003c648,extraout_r1,0xffffffff,0xffffffff);
  cVar1 = *(char *)(iVar5 + 0xf0);
  uVar8 = FUN_00072558(DAT_0003c648);
  uVar7 = (uint)*(byte *)(iVar5 + 0xef);
  if (uVar7 == 7) {
    if ((*DAT_0003c64c == 0xffffffff) && (cVar1 == '\x03')) {
      iVar14 = 0;
      *DAT_0003c64c = (uint)*(byte *)(iVar5 + 0xf5);
      FUN_000432ec();
      uVar20 = DAT_0003c644;
      do {
        FUN_00086c1e(uVar20,iVar5 + 0xf6,*(undefined2 *)(iVar5 + 0x286),400);
        iVar6 = FUN_0007d3ee();
        uVar18 = FUN_0007d446();
        iVar9 = FUN_0007d3ee();
        iVar10 = FUN_0007d446();
        FUN_00043e90(0,uVar20,0,iVar6 + 0x58,uVar18,iVar9 + 0x230,iVar10 + 0x88,5,0,0,0,0);
        if (*(char *)(iVar5 + 0xf4) != '\x01') {
          iVar6 = FUN_0007d3ee();
          uVar18 = FUN_0007d446();
          iVar9 = FUN_0007d3ee();
          iVar10 = FUN_0007d446();
          FUN_0004396c(iVar6 + 0x23c,uVar18,iVar9 + 0x23c,iVar10 + 0x88,1,
                       *(undefined1 *)(iVar5 + 0xf3),0);
        }
        puVar4 = DAT_0003c658;
        uVar7 = 0;
        local_30 = *DAT_0003c658;
        do {
          iVar6 = 0;
          uStack_2c = puVar4[1];
          do {
            iVar9 = *(int *)(param_1 + uVar7 * 4);
            bVar2 = *(byte *)(iVar9 + iVar6);
            if (bVar2 != 0) {
              *(byte *)(iVar9 + iVar6) =
                   bVar2 & *(byte *)((uint)*(byte *)((int)&local_30 + iVar14) * 0x140 +
                                     (uVar7 % 0x1a) * 0xa00 + DAT_0003c650 + iVar6);
            }
            iVar6 = iVar6 + 1;
          } while (iVar6 != 0x140);
          uVar7 = uVar7 + 1;
        } while (uVar7 != 199);
        iVar6 = FUN_000167a8();
        uVar18 = *(undefined4 *)(iVar6 + 0xeb4);
        iVar6 = FUN_000167a8();
        iVar14 = iVar14 + 1;
        FUN_00047260(uVar18,*(undefined4 *)(iVar6 + 0xeb8),0,0,0x280,199);
      } while (iVar14 != 8);
      goto LAB_0003c204;
    }
    if (cVar1 == '\x04') goto LAB_0003c366;
  }
  else {
    if (cVar1 == '\x04') {
LAB_0003c366:
      iVar6 = 0x640;
      *DAT_0003c64c = (uint)*(byte *)(iVar5 + 0xf5);
      iVar9 = FUN_000167a8();
      while( true ) {
        for (iVar10 = FUN_0007d446(); iVar11 = FUN_0007d446(), iVar10 <= iVar11 + 0x87;
            iVar10 = iVar10 + 1) {
          iVar11 = FUN_0007d3ee();
          iVar12 = (iVar10 % 0x1a) * 0xa00 + iVar6 + DAT_0003c9a8;
          for (iVar11 = iVar11 + 0x58; iVar21 = FUN_0007d3ee(), iVar11 < (iVar21 + 0x230) / 2;
              iVar11 = iVar11 + 1) {
            iVar21 = *(int *)(iVar9 + 0xb90 + iVar10 * 4);
            bVar2 = *(byte *)(iVar21 + iVar11);
            if (bVar2 != 0) {
              *(byte *)(iVar21 + iVar11) = bVar2 & *(byte *)(iVar12 + iVar11);
            }
          }
        }
        iVar10 = FUN_000167a8();
        uVar17 = *(undefined4 *)(iVar10 + 0xeb4);
        iVar10 = FUN_000167a8();
        uVar13 = *(undefined4 *)(iVar10 + 0xeb8);
        iVar10 = FUN_0007d3ee();
        uVar8 = FUN_0007d446();
        iVar11 = FUN_0007d3ee();
        iVar12 = FUN_0007d446();
        FUN_00047260(uVar17,uVar13,iVar10 + 0x58,uVar8,iVar11 + 0x230,iVar12 + 0x88);
        if (iVar6 == 0x500) break;
        iVar6 = 0x500;
      }
      FUN_000471cc(iVar9 + 0xb90,0,0,0x10,0x280,0xb8);
      FUN_0003be18(iVar14);
      uVar8 = FUN_000432ec();
      uVar7 = (uint)*(byte *)(iVar5 + 0xef);
      if (uVar7 < 6) {
        uVar18 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        iVar6 = FUN_0007d3ee();
        iVar10 = FUN_0007d446();
        FUN_00044bd8(0,uVar20,0,uVar18,iVar5 + 0x36,iVar6 + 0x236,iVar10 + 0x87,3,0,0,0,0);
      }
      else if (uVar7 == 0xb) {
        uVar20 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        FUN_00043484(0x49,uVar20,iVar5 + 0x36,0,0,0);
        iVar10 = FUN_0007d3ee();
        iVar11 = FUN_0007d446();
        iVar5 = FUN_0007d3ee();
        iVar6 = FUN_0007d446();
        iVar6 = iVar6 + 0x87;
        iVar5 = iVar5 + 0x230;
        iVar11 = iVar11 + 0x36;
        uVar20 = 3;
        iVar10 = iVar10 + 0x58;
LAB_0003c704:
        FUN_00043e90(0,uVar18,0,iVar10,iVar11,iVar5,iVar6,uVar20,0,0,0,0);
      }
      else if (uVar7 - 0xc < 3) {
        if (uVar7 != 0xe) {
          return uVar8;
        }
        iVar5 = FUN_000167a8();
        uVar20 = *(undefined4 *)(iVar5 + 0xeb4);
        iVar5 = FUN_000167a8();
        FUN_00047260(uVar20,*(undefined4 *)(iVar5 + 0xeb8),0,0,0x27f,199);
      }
      else {
        if (uVar7 - 0xf < 2) {
          if (uVar7 != 0x10) {
            return uVar8;
          }
          FUN_00086c1e(DAT_0003c9ac,iVar5 + 0xf6,*(undefined2 *)(iVar5 + 0x286),400);
          iVar10 = FUN_0007d3ee();
          iVar11 = FUN_0007d446();
          iVar5 = FUN_0007d3ee();
          iVar6 = FUN_0007d446();
          iVar6 = iVar6 + 0x88;
          iVar5 = iVar5 + 0x240;
          uVar20 = 5;
          uVar18 = DAT_0003c9ac;
          goto LAB_0003c704;
        }
        FUN_00086c1e(DAT_0003c9ac,iVar5 + 0xf6,*(undefined2 *)(iVar5 + 0x286),400);
        iVar6 = FUN_0007d3ee();
        uVar20 = FUN_0007d446();
        iVar10 = FUN_0007d3ee();
        iVar11 = FUN_0007d446();
        FUN_00043e90(0,DAT_0003c9ac,0,iVar6 + 0x58,uVar20,iVar10 + 0x230,iVar11 + 0x88,5,0,0,0,0);
        if (*(char *)(iVar5 + 0xf4) != '\x01') {
          iVar6 = FUN_0007d3ee();
          uVar20 = FUN_0007d446();
          iVar10 = FUN_0007d3ee();
          iVar11 = FUN_0007d446();
          FUN_0004396c(iVar6 + 0x23c,uVar20,iVar10 + 0x23c,iVar11 + 0x88,1,
                       *(undefined1 *)(iVar5 + 0xf3),0);
        }
      }
      puVar4 = DAT_0003c658;
      iVar5 = 0;
      do {
        iVar6 = FUN_0007d3ee();
        iVar6 = iVar6 + 0x58;
        iVar10 = FUN_0007d3ee();
        iVar11 = FUN_0007d446();
        iVar12 = FUN_0007d446();
        for (uVar7 = 0; (int)uVar7 < (iVar12 + 0x88) - iVar11; uVar7 = uVar7 + 1) {
          for (iVar21 = 0; iVar21 < ((iVar10 + 0x230) - iVar6) / 2; iVar21 = iVar21 + 1) {
            local_30 = *puVar4;
            uStack_2c = puVar4[1];
            iVar22 = iVar6 / 2 + iVar21;
            iVar19 = *(int *)(iVar9 + iVar11 * 4 + 0xb90 + uVar7 * 4);
            bVar2 = *(byte *)(iVar19 + iVar22);
            if (bVar2 != 0) {
              *(byte *)(iVar19 + iVar22) =
                   bVar2 & *(byte *)((uint)*(byte *)((int)&local_30 + iVar5) * 0x140 +
                                     (uVar7 % 0x1a) * 0xa00 + DAT_0003c9a8 + iVar21);
            }
          }
        }
        iVar21 = FUN_000167a8();
        uVar20 = *(undefined4 *)(iVar21 + 0xeb4);
        iVar21 = FUN_000167a8();
        iVar5 = iVar5 + 1;
        FUN_00047260(uVar20,*(undefined4 *)(iVar21 + 0xeb8),iVar6,iVar11,iVar10 + 0x230,
                     iVar12 + 0x88);
      } while (iVar5 != 8);
      FUN_000432d0();
      FUN_0003be18(iVar14);
      goto LAB_0003c89e;
    }
    if (uVar7 < 5) {
      if (*DAT_0003c654 != 0) {
        *DAT_0003c654 = 0;
        FUN_000431c0();
      }
      uVar18 = FUN_0007d3ee();
      iVar14 = FUN_0007d446();
      iVar5 = FUN_0007d3ee();
      iVar6 = FUN_0007d446();
      FUN_00044bd8(0,uVar20,0,uVar18,iVar14 + 0x36,iVar5 + 0x236,iVar6 + 0x87,3,0,0,0,0);
      return 0;
    }
    if (uVar7 == 0xb) {
      if (*DAT_0003c9b0 != 0) {
        *DAT_0003c9b0 = 0;
        FUN_000431c0();
      }
      uVar20 = FUN_0007d3ee();
      iVar14 = FUN_0007d446();
      FUN_00043484(0x49,uVar20,iVar14 + 0x36,0,0,0);
      iVar6 = FUN_0007d3ee();
      iVar9 = FUN_0007d446();
      iVar14 = FUN_0007d3ee();
      iVar5 = FUN_0007d446();
      iVar5 = iVar5 + 0x87;
      iVar14 = iVar14 + 0x230;
      iVar9 = iVar9 + 0x36;
      uVar20 = 3;
      iVar6 = iVar6 + 0x58;
LAB_0003c910:
      FUN_00043e90(0,uVar18,0,iVar6,iVar9,iVar14,iVar5,uVar20,0,0,0,0);
      return 0;
    }
    if (uVar7 - 0xc < 3) {
      if (uVar7 == 0xe) {
        iVar14 = FUN_000167a8();
        uVar20 = *(undefined4 *)(iVar14 + 0xeb4);
        iVar14 = FUN_000167a8();
        FUN_00047260(uVar20,*(undefined4 *)(iVar14 + 0xeb8),0,0,0x27f,199);
        return 0;
      }
      return uVar8;
    }
    if (uVar7 - 0xf < 2) {
      if (uVar7 != 0x10) {
        return uVar8;
      }
      FUN_00086c1e(DAT_0003c9ac,iVar5 + 0xf6,*(undefined2 *)(iVar5 + 0x286),400);
      iVar6 = FUN_0007d3ee();
      iVar9 = FUN_0007d446();
      iVar14 = FUN_0007d3ee();
      iVar5 = FUN_0007d446();
      iVar5 = iVar5 + 0x88;
      iVar14 = iVar14 + 0x240;
      uVar20 = 5;
      uVar18 = DAT_0003c9ac;
      goto LAB_0003c910;
    }
    if (uVar7 < 7) {
      iVar14 = FUN_0007d3ee();
      iVar5 = FUN_0007d446();
      iVar6 = FUN_0007d3ee();
      iVar9 = FUN_0007d446();
      FUN_00043e90(0,DAT_0003cb2c,0,iVar14 + 0x58,iVar5 + 0x36,iVar6 + 0x230,iVar9 + 0x87,5,0,0,0,0)
      ;
      *DAT_0003cb30 = 1;
      *DAT_0003cb34 = 0;
      return 0;
    }
  }
  FUN_00086c78(DAT_0003cb38,0,400);
  FUN_00086c1e(DAT_0003cb38,iVar5 + 0xf6,*(undefined2 *)(iVar5 + 0x286),400);
  piVar16 = DAT_0003cb34;
  if ((*(byte *)(iVar5 + 0xef) - 8 < 2) || (*DAT_0003cb34 == 0)) {
    iVar14 = FUN_0007d3ee();
    uVar20 = FUN_0007d446();
    iVar6 = FUN_0007d3ee();
    iVar9 = FUN_0007d446();
    FUN_00043e90(0,DAT_0003cb38,0,iVar14 + 0x58,uVar20,iVar6 + 0x230,iVar9 + 0x88,5,0,0,0,0);
    if (*piVar16 == 0) {
      *piVar16 = 1;
    }
  }
  else {
    iVar14 = FUN_0007d3ee();
    iVar6 = FUN_0007d446();
    iVar9 = FUN_0007d3ee();
    iVar10 = FUN_0007d446();
    FUN_000440ec(0,DAT_0003cb38,0,iVar14 + 0x58,iVar6 + 1,iVar9 + 0x230,iVar10 + 0x88,5,0);
  }
  if (*(char *)(iVar5 + 0xf4) != '\x01') {
    iVar14 = FUN_0007d3ee();
    uVar20 = FUN_0007d446();
    iVar6 = FUN_0007d3ee();
    iVar9 = FUN_0007d446();
    FUN_0004396c(iVar14 + 0x23c,uVar20,iVar6 + 0x23c,iVar9 + 0x88,1,*(undefined1 *)(iVar5 + 0xf3),0)
    ;
  }
LAB_0003c89e:
  *DAT_0003c9b0 = 1;
  return 0;
}


