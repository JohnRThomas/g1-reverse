/* Reconstructed ui_QuickNote_task @ 0x3b824  (parity: 40/40 trials, PROVEN) */
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
extern long long FUN_0003b78c__impl(int, ...);
#define FUN_0003b78c(...) FUN_0003b78c__impl(0, ##__VA_ARGS__)
extern long long FUN_0003b800__impl(int, ...);
#define FUN_0003b800(...) FUN_0003b800__impl(0, ##__VA_ARGS__)
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
extern long long FUN_0004334c__impl(int, ...);
#define FUN_0004334c(...) FUN_0004334c__impl(0, ##__VA_ARGS__)
extern long long FUN_00043484__impl(int, ...);
#define FUN_00043484(...) FUN_00043484__impl(0, ##__VA_ARGS__)
extern long long FUN_0004382c__impl(int, ...);
#define FUN_0004382c(...) FUN_0004382c__impl(0, ##__VA_ARGS__)
extern long long FUN_00043e90__impl(int, ...);
#define FUN_00043e90(...) FUN_00043e90__impl(0, ##__VA_ARGS__)
extern long long FUN_00047260__impl(int, ...);
#define FUN_00047260(...) FUN_00047260__impl(0, ##__VA_ARGS__)
extern long long FUN_00049040__impl(int, ...);
#define FUN_00049040(...) FUN_00049040__impl(0, ##__VA_ARGS__)
extern long long FUN_0007d3ee__impl(int, ...);
#define FUN_0007d3ee(...) FUN_0007d3ee__impl(0, ##__VA_ARGS__)
extern long long FUN_0007d446__impl(int, ...);
#define FUN_0007d446(...) FUN_0007d446__impl(0, ##__VA_ARGS__)
extern long long FUN_00086c78__impl(int, ...);
#define FUN_00086c78(...) FUN_00086c78__impl(0, ##__VA_ARGS__)
extern long long thunk_FUN_00074f68__impl(int, ...);
#define thunk_FUN_00074f68(...) thunk_FUN_00074f68__impl(0, ##__VA_ARGS__)

#define DAT_0003bb28 ((volatile char*)0x20004978UL)
#define DAT_0003bb2c ((volatile int*)0x2000230cUL)
#define DAT_0003bb30 ((volatile int*)0x20007554UL)
#define DAT_0003bb34 (0xa9831UL)
#define DAT_0003bb38 (0xa960dUL)
#define DAT_0003bb3c (0xa9629UL)
#define DAT_0003bb40 (0xa9654UL)
#define DAT_0003bb44 (0xa9679UL)
#define DAT_0003bb48 (0xa9690UL)
#define DAT_0003bb4c (0xaae20UL)
#define DAT_0003bb50 (0xa96acUL)
#define DAT_0003bb54 (0xa96c8UL)
#define DAT_0003bb58 (0xa96e0UL)
#define DAT_0003bb5c (0xa9709UL)
#define DAT_0003bb60 (0xa9727UL)
#define DAT_0003bb64 ((volatile uint32_t*)0xa8c57UL)
#define DAT_0003bde0 (0xa9831UL)
#define DAT_0003bde4 (0xa974bUL)
#define DAT_0003bde8 ((volatile char*)0x2001b817UL)
#define DAT_0003bdec ((volatile int*)0x20007554UL)
#define DAT_0003bdf0 (0xa9775UL)
#define DAT_0003bdf4 ((volatile int*)0x2000230cUL)
#define DAT_0003bdf8 (0xa9797UL)
#define DAT_0003bdfc (0xa9727UL)
#define DAT_0003be00 ((volatile unsigned int*)0x200024e8UL)
#define DAT_0003be04 (0xa97e4UL)
#define DAT_0003be08 (0xa980bUL)
#define DAT_0003be0c (0xa981aUL)
#define DAT_0003be10 (0x0UL) /* unknown lit */
#define DAT_0003be14 (0x0UL) /* unknown lit */


undefined4 ui_QuickNote_task(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  byte bVar2;
  int *piVar3;
  int *piVar4;
  undefined4 *puVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  char *pcVar13;
  char *pcVar14;
  undefined4 uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  undefined4 uVar20;
  int iVar21;
  bool bVar22;
  longlong lVar23;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  pcVar13 = DAT_0003bb28;
  FUN_000431b4(param_1 + 0x24);
  FUN_000432d0();
  piVar7 = DAT_0003bdf4;
  piVar6 = DAT_0003bdec;
  piVar4 = DAT_0003bb30;
  piVar3 = DAT_0003bb2c;
  cVar1 = *pcVar13;
  if (cVar1 != '\x01') {
    if (cVar1 != '\x02') {
      if (cVar1 != '\0') {
        return 0;
      }
      if (2 < *DAT_0003bb2c) {
        if (*DAT_0003bb30 == 0) {
          DEBUG_PRINT(DAT_0003bb38,DAT_0003bb34);
        }
        else {
          FUN_00019c70();
        }
      }
      FUN_00086c78(DAT_0003bb28,0,0x10);
      if (2 < *piVar3) {
        if (*DAT_0003bb30 == 0) {
          iVar8 = FUN_000167a8();
          DEBUG_PRINT(DAT_0003bb3c,DAT_0003bb34,(uint)**(byte **)(iVar8 + 0x1020));
        }
        else {
          iVar8 = FUN_000167a8();
          FUN_00019c70(DAT_0003bb3c,DAT_0003bb34,**(undefined1 **)(iVar8 + 0x1020));
        }
      }
      if (param_3 == 1) {
        iVar8 = FUN_000167a8();
        if (**(char **)(iVar8 + 0x1020) != '\x01') {
          return 0;
        }
        if (2 < *piVar3) {
          if (*DAT_0003bb30 == 0) {
            DEBUG_PRINT(DAT_0003bb40,DAT_0003bb34);
          }
          else {
            FUN_00019c70();
          }
        }
        FUN_000431c0();
        *pcVar13 = '\x01';
        FUN_00043308();
        iVar8 = FUN_00023ee0();
        iVar21 = 0;
        FUN_000432ec();
        do {
          if (iVar8 == 6) {
            iVar9 = FUN_0007d3ee();
            iVar10 = FUN_0007d446();
            iVar11 = FUN_0007d3ee();
            iVar12 = FUN_0007d446();
            FUN_00043e90(0,DAT_0003bb50,0,iVar9 + 0xa0,iVar10 + 0x36,iVar11 + 0x236,iVar12 + 0x51,1,
                         0,0,0,0);
            iVar9 = FUN_0007d3ee();
            iVar10 = FUN_0007d446();
            iVar11 = FUN_0007d3ee();
            iVar12 = FUN_0007d446();
            iVar9 = iVar9 + 0xaa;
            uVar20 = DAT_0003bb54;
          }
          else {
            iVar9 = FUN_0007d3ee();
            iVar10 = FUN_0007d446();
            iVar11 = FUN_0007d3ee();
            iVar12 = FUN_0007d446();
            FUN_00043e90(0,DAT_0003bb44,0,iVar9 + 0xbc,iVar10 + 0x36,iVar11 + 0x236,iVar12 + 0x51,1,
                         0,0,0,0);
            iVar9 = FUN_0007d3ee();
            iVar10 = FUN_0007d446();
            iVar11 = FUN_0007d3ee();
            iVar12 = FUN_0007d446();
            iVar9 = iVar9 + 0xa4;
            uVar20 = DAT_0003bb48;
          }
          FUN_00043e90(0,uVar20,0,iVar9,iVar10 + 0x6c,iVar11 + 0x236,iVar12 + 0x87,1,0,0,0,0);
          puVar5 = DAT_0003bb64;
          uVar19 = 0;
          local_30 = *DAT_0003bb64;
          do {
            iVar9 = 0;
            uStack_2c = puVar5[1];
            do {
              iVar10 = *(int *)(param_1 + 0x24 + uVar19 * 4);
              bVar2 = *(byte *)(iVar10 + iVar9);
              if (bVar2 != 0) {
                *(byte *)(iVar10 + iVar9) =
                     bVar2 & *(byte *)((uint)*(byte *)((int)&local_30 + iVar21) * 0x140 +
                                       (uVar19 % 0x1a) * 0xa00 + DAT_0003bb4c + iVar9);
              }
              iVar9 = iVar9 + 1;
            } while (iVar9 != 0x140);
            uVar19 = uVar19 + 1;
          } while (uVar19 != 199);
          iVar9 = FUN_000167a8();
          uVar20 = *(undefined4 *)(iVar9 + 0xeb4);
          iVar9 = FUN_000167a8();
          iVar21 = iVar21 + 1;
          FUN_00047260(uVar20,*(undefined4 *)(iVar9 + 0xeb8),0,0,0x280,199);
        } while (iVar21 != 4);
        FUN_000432d0();
        pcVar13 = (char *)FUN_000167a8();
        if (*pcVar13 != '\x01') {
          return 0;
        }
        FUN_0003b78c();
        return 0;
      }
      if (param_3 != 2) {
        return 0;
      }
      if (0 < *piVar3) {
        iVar8 = *DAT_0003bb30;
        uVar20 = DAT_0003bb58;
LAB_0003bac4:
        if (iVar8 == 0) {
          DEBUG_PRINT(uVar20,DAT_0003bb34);
        }
        else {
          FUN_00019c70();
        }
      }
      goto LAB_0003bacc;
    }
    if (*DAT_0003bdf4 < 3) {
      if (param_3 != 2) goto LAB_0003bd76;
    }
    else {
      if (*DAT_0003bdec == 0) {
        DEBUG_PRINT(DAT_0003bdf8,DAT_0003bde0);
      }
      else {
        FUN_00019c70();
      }
      if (param_3 != 2) {
LAB_0003bd76:
        lVar23 = thunk_FUN_00074f68();
        pcVar14 = DAT_0003bde8;
        uVar16 = (uint)((ulonglong)(lVar23 * 1000) >> 0x20);
        uVar17 = (uint)(lVar23 * 1000) >> 0xf | uVar16 * 0x20000;
        uVar18 = *(uint *)(pcVar13 + 4);
        uVar19 = uVar18 + *(uint *)(pcVar13 + 8);
        iVar8 = *(int *)(pcVar13 + 0xc) +
                ((int)uVar18 >> 0x1f) + (uint)CARRY4(uVar18,*(uint *)(pcVar13 + 8));
        uVar16 = uVar16 >> 0xf;
        if ((int)((iVar8 - uVar16) - (uint)(uVar19 < uVar17)) < 0 !=
            (SBORROW4(iVar8,uVar16) != SBORROW4(iVar8 - uVar16,(uint)(uVar19 < uVar17)))) {
          if (2 < *piVar7) {
            if (*DAT_0003bdec == 0) {
              DEBUG_PRINT(DAT_0003be10,DAT_0003bde0);
            }
            else {
              FUN_00019c70();
            }
          }
          FUN_0004382c();
          iVar8 = FUN_000167a8();
          uVar20 = DAT_0003be14;
          **(undefined1 **)(iVar8 + 0x1020) = 0;
          FUN_00086c78(uVar20,0,0x10);
          *pcVar14 = '\0';
          return 0;
        }
        uVar18 = *DAT_0003be00;
        iVar8 = (iVar8 - ((int)uVar18 >> 0x1f)) - (uint)(uVar19 < uVar18);
        bVar22 = uVar19 - uVar18 < uVar17;
        if ((int)((iVar8 - uVar16) - (uint)bVar22) < 0 !=
            (SBORROW4(iVar8,uVar16) != SBORROW4(iVar8 - uVar16,(uint)bVar22))) {
          if (*DAT_0003bde8 != '\0') {
            return 0;
          }
          if (2 < *piVar7) {
            if (*DAT_0003bdec == 0) {
              DEBUG_PRINT(DAT_0003be04,DAT_0003bde0);
            }
            else {
              FUN_00019c70();
            }
          }
          FUN_000431c0();
          uVar20 = FUN_0007d3ee();
          iVar8 = FUN_0007d446();
          FUN_00043484(0x3b,uVar20,iVar8 + 0x36,0,0,0);
          iVar8 = FUN_00023ee0();
          if (iVar8 == 6) {
            iVar8 = FUN_0007d3ee();
            iVar21 = FUN_0007d446();
            iVar9 = FUN_0007d3ee();
            iVar10 = FUN_0007d446();
            iVar8 = iVar8 + 0xb8;
            uVar20 = DAT_0003be0c;
          }
          else {
            iVar8 = FUN_0007d3ee();
            iVar21 = FUN_0007d446();
            iVar9 = FUN_0007d3ee();
            iVar10 = FUN_0007d446();
            iVar8 = iVar8 + 0xd6;
            uVar20 = DAT_0003be08;
          }
          FUN_00043e90(0,uVar20,0,iVar8,iVar21 + 0x36,iVar9 + 0x236,iVar10 + 0x6c,2,0,0,0,0);
          *pcVar14 = '\x01';
          return 0;
        }
        if (*DAT_0003bde8 != '\0') {
          return 0;
        }
        uVar20 = FUN_0007d3ee();
        iVar8 = FUN_0007d446();
        uVar15 = 9;
        goto LAB_0003bd6a;
      }
      if (2 < *piVar7) {
        if (*piVar6 == 0) {
          DEBUG_PRINT(DAT_0003bdfc,DAT_0003bde0);
        }
        else {
          FUN_00019c70();
        }
      }
    }
    pcVar13 = (char *)FUN_000167a8();
    if (*pcVar13 == '\x01') {
      FUN_0003b800();
    }
    FUN_0004382c();
    goto LAB_0003bade;
  }
  if (*DAT_0003bb2c < 3) {
    if (param_3 != 2) {
      if (param_3 == 3) goto LAB_0003bb86;
      goto LAB_0003bd4a;
    }
  }
  else {
    if (*DAT_0003bb30 == 0) {
      DEBUG_PRINT(DAT_0003bb5c,DAT_0003bb34);
    }
    else {
      FUN_00019c70();
    }
    if (param_3 != 2) {
      if (param_3 == 3) {
        if (2 < *piVar3) {
          if (*piVar4 == 0) {
            DEBUG_PRINT(DAT_0003bde4,DAT_0003bde0);
          }
          else {
            FUN_00019c70();
          }
        }
LAB_0003bb86:
        pcVar14 = (char *)FUN_000167a8();
        if (*pcVar14 == '\x01') {
          FUN_0003b800();
        }
        uVar20 = FUN_00049040();
        *(undefined4 *)(pcVar13 + 4) = uVar20;
        lVar23 = thunk_FUN_00074f68();
        uVar19 = (uint)((ulonglong)(lVar23 * 1000) >> 0x20);
        *(uint *)(pcVar13 + 8) = (uint)(lVar23 * 1000) >> 0xf | uVar19 * 0x20000;
        *(uint *)(pcVar13 + 0xc) = uVar19 >> 0xf;
        FUN_000431c0();
        *pcVar13 = '\x02';
        *DAT_0003bde8 = '\0';
        FUN_00043308();
        if (*piVar3 < 3) {
          return 0;
        }
        if (*DAT_0003bdec != 0) {
          FUN_00019c70();
          return 0;
        }
        DEBUG_PRINT(DAT_0003bdf0,DAT_0003bde0);
        return 0;
      }
LAB_0003bd4a:
      if (param_3 != 0) {
        return 0;
      }
      uVar20 = FUN_0007d3ee();
      iVar8 = FUN_0007d446();
      uVar15 = 1;
LAB_0003bd6a:
      FUN_0004334c(uVar15,uVar20,iVar8 + 0x36,0,0,0,0);
      return 0;
    }
    if (2 < *piVar3) {
      iVar8 = *piVar4;
      uVar20 = DAT_0003bb60;
      goto LAB_0003bac4;
    }
  }
LAB_0003bacc:
  pcVar13 = (char *)FUN_000167a8();
  if (*pcVar13 == '\x01') {
    FUN_0003b800();
  }
  FUN_000431c0();
LAB_0003bade:
  iVar8 = FUN_000167a8();
  **(undefined1 **)(iVar8 + 0x1020) = 0;
  FUN_00086c78(DAT_0003bb28,0,0x10);
  return 0;
}


