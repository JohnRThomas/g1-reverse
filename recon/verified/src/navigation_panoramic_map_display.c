/* Reconstructed navigation_panoramic_map_display @ 0x3e7f8  (parity: 298/300 trials, PROVEN) */
#include <stdint.h>
typedef uint8_t undefined1; typedef uint8_t byte; typedef uint8_t undefined; typedef uint8_t uchar;
typedef uint16_t undefined2; typedef uint16_t ushort; typedef uint16_t wchar_t;
typedef uint32_t undefined4; typedef uint32_t uint;
typedef uint64_t undefined8; typedef uint64_t ulonglong;
typedef int64_t longlong;

extern long long DEBUG_PRINT(int, ...);
extern long long FUN_00019c70(int, ...);
extern long long FUN_000167a8(int, ...);
extern long long FUN_00047260(int, ...);
extern long long FUN_000432ec(int, ...);
extern long long FUN_000471cc(int, ...);
extern long long FUN_0007d3ee(int, ...);
extern long long FUN_0007d446(int, ...);
extern long long FUN_00043bd8(int, ...);
extern long long FUN_00043d78(int, ...);
extern long long FUN_00043e90(int, ...);
extern long long FUN_00023ee0(int, ...);
extern long long FUN_0007d224(int, ...);
extern long long FUN_000442bc(int, ...);
extern long long FUN_000432d0(int, ...);
extern long long FUN_00086c78(int, ...);
extern long long thunk_FUN_000723b8(int, ...);
extern long long FUN_00086c04(int, ...);
extern long long FUN_0007da70(int, ...);
extern long long thunk_FUN_00072558(int, ...);
extern long long FUN_0007d376(int, ...);
extern long long FUN_0007d37a(uint32_t);

#define DAT_0003e8b0 (0x20004bb8)
#define DAT_0003e8b4 ((volatile int*)0x2000230cUL)
#define DAT_0003e8b8 ((volatile int*)0x20007554UL)
#define DAT_0003e8bc (0xaa425)
#define DAT_0003e8c0 (0xa9f6f)
#define DAT_0003e8c4 (0xaae20)
#define DAT_0003ec44 ((volatile char*)0x20010325UL)
#define DAT_0003ec48 (0x20013dea)
#define DAT_0003ec4c (0x20011d82)
#define DAT_0003ec50 (0xaae20)
#define DAT_0003ec54 ((volatile char*)0x20010322UL)
#define DAT_0003ec58 ((volatile undefined1*)0x2001ba2cUL)
#define DAT_0003ec5c ((volatile undefined4*)0xa8c57UL)
#define DAT_0003ef48 (0x20013dea)
#define DAT_0003ef4c (0x20011d82)
#define DAT_0003ef50 ((volatile char*)0x2001ba2cUL)
#define DAT_0003ef54 ((volatile char*)0x20010324UL)
#define DAT_0003ef58 ((volatile char*)0x20010325UL)
#define DAT_0003ef5c ((volatile char*)0x20010323UL)
#define DAT_0003ef60 ((volatile int*)0x2000230cUL)
#define DAT_0003ef64 ((volatile undefined1*)0x2001ba2dUL)
#define DAT_0003ef68 ((volatile int*)0x20007554UL)
#define DAT_0003ef6c (0xaa425)
#define DAT_0003ef70 (0xa9ee1)
#define DAT_0003ef74 (0x2001ba2e)
#define DAT_0003ef78 (0x20007574)
#define DAT_0003ef7c (0x20015e52)
#define DAT_0003ef80 (0xa9f93)
#define DAT_0003f278 (0xa9fcd)
#define DAT_0003f27c (0xa9fe6)
#define DAT_0003f280 (0xa9ff7)
#define DAT_0003f284 (0xaa01a)
#define DAT_0003f288 ((volatile int*)0x2000230cUL)
#define DAT_0003f28c ((volatile int*)0x20007554UL)
#define DAT_0003f290 (0xaa425)
#define DAT_0003f294 (0xa9f93)
#define DAT_0003f298 (0xa9eff)
#define DAT_0003f29c (0x2001ba2e)
#define DAT_0003f2a0 (0x20007574)
#define DAT_0003f2a4 (0x20015e52)

void navigation_panoramic_map_display(undefined4 param_1,int param_2)
{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  int iVar13;
  undefined4 uVar14;
  int iVar15;
  uint uVar16;
  undefined4 uVar17;
  undefined8 uVar32;
  undefined4 local_30;
  undefined4 uStack_2c;

  iVar4 = DAT_0003e8b0;
  if (*(char *)(DAT_0003e8b0 + 4) == '\0') {
    if (2 < *DAT_0003e8b4) {
      if (*DAT_0003e8b8 == 0) {
        DEBUG_PRINT(DAT_0003e8c0,DAT_0003e8bc);
      }
      else {
        ((long long (*)(void))FUN_00019c70)();
      }
    }
    iVar7 = ((long long (*)(void))FUN_000167a8)();
    iVar8 = DAT_0003e8c4;
    iVar15 = 0x640;
    iVar7 = iVar7 + 0xb90;
    while( 1 ) {
      uVar16 = 0;
      do {
        iVar12 = 0;
        do {
          iVar13 = *(int *)(iVar7 + uVar16 * 4);
          bVar1 = *(byte *)(iVar13 + iVar12);
          if (bVar1 != 0) {
            *(byte *)(iVar13 + iVar12) =
                 bVar1 & *(byte *)((uVar16 % 0x1a) * 0xa00 + iVar15 + iVar8 + iVar12);
          }
          iVar12 = iVar12 + 1;
        } while (iVar12 != 0x140);
        uVar16 = uVar16 + 1;
      } while (uVar16 != 199);
      iVar12 = ((long long (*)(void))FUN_000167a8)();
      uVar14 = *(undefined4 *)(iVar12 + 0xeb4);
      iVar12 = ((long long (*)(void))FUN_000167a8)();
      FUN_00047260(uVar14,*(undefined4 *)(iVar12 + 0xeb8),0,0,0x280,199);
      if (iVar15 == 0x500) break;
      iVar15 = 0x500;
    }
    ((long long (*)(void))FUN_000432ec)();
    iVar15 = 1;
    do {
      FUN_000471cc(iVar7,0,0,0,0x280,199);
      puVar5 = (undefined1 *)DAT_0003ec58;
      if (*DAT_0003ec44 == '\x01') {
        iVar8 = ((long long (*)(void))FUN_0007d3ee)();
        uVar14 = ((long long (*)(void))FUN_0007d446)();
        iVar12 = ((long long (*)(void))FUN_0007d3ee)();
        iVar13 = ((long long (*)(void))FUN_0007d446)();
        FUN_00043bd8(iVar8 + 0x58,uVar14,iVar12 + 0x240,iVar13 + 0x88,DAT_0003ec4c,DAT_0003ec48,2,
                     0xf);
        uVar2 = *(ushort *)(param_2 + 8);
        if ((uVar2 < 0x1e9) && (*(ushort *)(param_2 + 10) < 0x89)) {
          iVar8 = ((long long (*)(void))FUN_0007d3ee)();
          uVar3 = *(ushort *)(param_2 + 10);
          iVar12 = ((long long (*)(void))FUN_0007d446)();
          FUN_00043d78(0x54,(uint)uVar2 + iVar8 + 0x52,(uVar3 - 6) + iVar12);
        }
        else if (0 < *DAT_0003ef60) {
          if (*DAT_0003ef68 == 0) {
            DEBUG_PRINT(DAT_0003ef80,DAT_0003ef6c);
          }
          else {
            ((long long (*)(void))FUN_00019c70)();
          }
        }
        uVar14 = ((long long (*)(void))FUN_0007d3ee)();
        iVar8 = ((long long (*)(void))FUN_0007d446)();
        iVar12 = ((long long (*)(void))FUN_0007d3ee)();
        iVar13 = ((long long (*)(void))FUN_0007d446)();
        FUN_00043e90(0,param_2 + 0x95,0,uVar14,iVar8 + 0x37,iVar12 + 0x4c,iVar13 + 0x52,1,0,0,0,0);
        uVar14 = ((long long (*)(void))FUN_0007d3ee)();
        iVar8 = ((long long (*)(void))FUN_0007d446)();
        iVar12 = ((long long (*)(void))FUN_0007d3ee)();
        iVar13 = ((long long (*)(void))FUN_0007d446)();
        FUN_00043e90(0,param_2 + 0xd,0,uVar14,iVar8 + 0x52,iVar12 + 0x4c,iVar13 + 0x6d,1,0,0,0,0);
        uVar14 = ((long long (*)(void))FUN_0007d3ee)();
        iVar8 = ((long long (*)(void))FUN_0007d446)();
        iVar12 = ((long long (*)(void))FUN_0007d3ee)();
        iVar13 = ((long long (*)(void))FUN_0007d446)();
        FUN_00043e90(0,param_2 + 0x25,0,uVar14,iVar8 + 0x6d,iVar12 + 0x4c,iVar13 + 0x88,1,0,0,0,0);
        *puVar5 = 1;
      }
      else {
        iVar8 = ((long long (*)(void))FUN_00023ee0)();
        if (iVar8 == 6) {
          iVar8 = ((long long (*)(void))FUN_0007d3ee)();
          iVar12 = ((long long (*)(void))FUN_0007d446)();
          iVar13 = ((long long (*)(void))FUN_0007d3ee)();
          iVar10 = ((long long (*)(void))FUN_0007d446)();
          FUN_00043e90(0,DAT_0003f280,0,iVar8 + 0x7a,iVar12 + 0x37,iVar13 + 0x23a,iVar10 + 0x52,1,0,
                       0,0,0);
          iVar12 = ((long long (*)(void))FUN_0007d3ee)();
          iVar11 = ((long long (*)(void))FUN_0007d446)();
          iVar13 = ((long long (*)(void))FUN_0007d3ee)();
          iVar10 = ((long long (*)(void))FUN_0007d446)();
          iVar13 = iVar13 + 0x23a;
          iVar12 = iVar12 + 0xd1;
          iVar8 = DAT_0003f284;
        }
        else {
          iVar8 = ((long long (*)(void))FUN_0007d3ee)();
          iVar12 = ((long long (*)(void))FUN_0007d446)();
          iVar13 = ((long long (*)(void))FUN_0007d3ee)();
          iVar10 = ((long long (*)(void))FUN_0007d446)();
          FUN_00043e90(0,DAT_0003f278,0,iVar8 + 0xb0,iVar12 + 0x37,iVar13 + 0x226,iVar10 + 0x52,1,0,
                       0,0,0);
          iVar12 = ((long long (*)(void))FUN_0007d3ee)();
          iVar11 = ((long long (*)(void))FUN_0007d446)();
          iVar13 = ((long long (*)(void))FUN_0007d3ee)();
          iVar10 = ((long long (*)(void))FUN_0007d446)();
          iVar13 = iVar13 + 0x226;
          iVar12 = iVar12 + 0xda;
          iVar8 = DAT_0003f27c;
        }
        FUN_00043e90(0,iVar8,0,iVar12,iVar11 + 0x52,iVar13,iVar10 + 0x6d,1,0,0,0,0);
        *puVar5 = 0;
      }
      iVar8 = ((long long (*)(void))FUN_000167a8)();
      iVar8 = *(byte *)(*(int *)(iVar8 + 0xfec) + 0x5e) - 1;
      if (iVar8 != 0) {
        iVar8 = 1;
      }
      uVar14 = ((long long (*)(void))FUN_0007d224)();
      uVar9 = ((long long (*)(void))FUN_0007d3ee)();
      iVar12 = ((long long (*)(void))FUN_0007d446)();
      iVar13 = ((long long (*)(void))FUN_0007d3ee)();
      iVar10 = ((long long (*)(void))FUN_0007d446)();
      FUN_000442bc(uVar14,uVar9,iVar12 + 2,iVar13 + 0x4c,iVar10 + 0x1d,3,iVar8);
      puVar6 = (undefined4 *)DAT_0003ec5c;
      uVar16 = 0;
      local_30 = *DAT_0003ec5c;
      do {
        iVar8 = 0;
        uStack_2c = puVar6[1];
        do {
          iVar12 = *(int *)(iVar7 + uVar16 * 4);
          bVar1 = *(byte *)(iVar12 + iVar8);
          if (bVar1 != 0) {
            *(byte *)(iVar12 + iVar8) =
                 bVar1 & *(byte *)((uint)*(byte *)((int)&local_30 + iVar15) * 0x140 +
                                   (uVar16 % 0x1a) * 0xa00 + DAT_0003ec50 + iVar8);
          }
          iVar8 = iVar8 + 1;
        } while (iVar8 != 0x140);
        uVar16 = uVar16 + 1;
      } while (uVar16 != 199);
      iVar8 = ((long long (*)(void))FUN_000167a8)();
      uVar14 = *(undefined4 *)(iVar8 + 0xeb4);
      iVar8 = ((long long (*)(void))FUN_000167a8)();
      iVar15 = iVar15 + 1;
      FUN_00047260(uVar14,*(undefined4 *)(iVar8 + 0xeb8),0,0,0x280,199);
    } while (iVar15 != 4);
    ((long long (*)(void))FUN_000432d0)();
    if (*DAT_0003ec44 == '\x01') {
      uVar14 = ((long long (*)(void))FUN_0007d3ee)();
      iVar15 = ((long long (*)(void))FUN_0007d446)();
      iVar8 = ((long long (*)(void))FUN_0007d3ee)();
      iVar7 = ((long long (*)(void))FUN_0007d446)();
      FUN_00043e90(0,param_2 + 0x95,0,uVar14,iVar15 + 0x37,iVar8 + 0x4c,iVar7 + 0x52,1,0,0,0,0);
      uVar14 = ((long long (*)(void))FUN_0007d3ee)();
      iVar15 = ((long long (*)(void))FUN_0007d446)();
      iVar8 = ((long long (*)(void))FUN_0007d3ee)();
      iVar7 = ((long long (*)(void))FUN_0007d446)();
      FUN_00043e90(0,param_2 + 0xd,0,uVar14,iVar15 + 0x52,iVar8 + 0x4c,iVar7 + 0x6d,1,0,0,0,0);
      uVar14 = ((long long (*)(void))FUN_0007d3ee)();
      iVar15 = ((long long (*)(void))FUN_0007d446)();
      iVar8 = ((long long (*)(void))FUN_0007d3ee)();
      iVar7 = ((long long (*)(void))FUN_0007d446)();
      FUN_00043e90(0,param_2 + 0x25,0,uVar14,iVar15 + 0x6d,iVar8 + 0x4c,iVar7 + 0x88,1,0,0,0,0);
    }
    iVar15 = ((long long (*)(void))FUN_000167a8)();
    iVar15 = *(byte *)(*(int *)(iVar15 + 0xfec) + 0x5e) - 1;
    if (iVar15 != 0) {
      iVar15 = 1;
    }
    uVar14 = ((long long (*)(void))FUN_0007d224)();
    uVar9 = ((long long (*)(void))FUN_0007d3ee)();
    iVar8 = ((long long (*)(void))FUN_0007d446)();
    iVar7 = ((long long (*)(void))FUN_0007d3ee)();
    iVar12 = ((long long (*)(void))FUN_0007d446)();
    FUN_000442bc(uVar14,uVar9,iVar8 + 2,iVar7 + 0x4c,iVar12 + 0x1d,3,iVar15);
  }
  if (*DAT_0003ec54 == '\x01') {
    *DAT_0003ec54 = '\0';
    if (*DAT_0003ec44 == '\x01') {
      iVar15 = ((long long (*)(void))FUN_0007d3ee)();
      uVar14 = ((long long (*)(void))FUN_0007d446)();
      iVar8 = ((long long (*)(void))FUN_0007d3ee)();
      iVar7 = ((long long (*)(void))FUN_0007d446)();
      FUN_00043bd8(iVar15 + 0x58,uVar14,iVar8 + 0x240,iVar7 + 0x88,DAT_0003ef4c,DAT_0003ef48,2,0xf);
      uVar2 = *(ushort *)(param_2 + 8);
      if ((uVar2 < 0x1e9) && (*(ushort *)(param_2 + 10) < 0x89)) {
        iVar15 = ((long long (*)(void))FUN_0007d3ee)();
        uVar3 = *(ushort *)(param_2 + 10);
        iVar8 = ((long long (*)(void))FUN_0007d446)();
        FUN_00043d78(0x54,(uint)uVar2 + iVar15 + 0x52,(uVar3 - 6) + iVar8);
      }
      else if (0 < *DAT_0003f288) {
        if (*DAT_0003f28c == 0) {
          DEBUG_PRINT(DAT_0003f294,DAT_0003f290);
        }
        else {
          ((long long (*)(void))FUN_00019c70)();
        }
      }
      if (*DAT_0003ef50 != '\0') goto LAB_0003ed90;
      uVar14 = ((long long (*)(void))FUN_0007d3ee)();
      iVar15 = ((long long (*)(void))FUN_0007d446)();
      iVar8 = ((long long (*)(void))FUN_0007d3ee)();
      iVar7 = ((long long (*)(void))FUN_0007d446)();
      FUN_00043e90(0,param_2 + 0x95,0,uVar14,iVar15 + 0x37,iVar8 + 0x4c,iVar7 + 0x52,1,0,0,0,0);
      uVar14 = ((long long (*)(void))FUN_0007d3ee)();
      iVar15 = ((long long (*)(void))FUN_0007d446)();
      iVar8 = ((long long (*)(void))FUN_0007d3ee)();
      iVar7 = ((long long (*)(void))FUN_0007d446)();
      FUN_00043e90(0,param_2 + 0xd,0,uVar14,iVar15 + 0x52,iVar8 + 0x4c,iVar7 + 0x6d,1,0,0,0,0);
      iVar8 = ((long long (*)(void))FUN_0007d3ee)();
      iVar7 = ((long long (*)(void))FUN_0007d446)();
      iVar12 = ((long long (*)(void))FUN_0007d3ee)();
      iVar13 = ((long long (*)(void))FUN_0007d446)();
      iVar12 = iVar12 + 0x4c;
      iVar13 = iVar13 + 0x88;
      iVar7 = iVar7 + 0x6d;
      iVar15 = param_2 + 0x25;
    }
    else {
      iVar15 = ((long long (*)(void))FUN_000167a8)();
      iVar8 = ((long long (*)(void))FUN_0007d3ee)();
      uVar14 = ((long long (*)(void))FUN_0007d446)();
      iVar7 = ((long long (*)(void))FUN_0007d3ee)();
      iVar12 = ((long long (*)(void))FUN_0007d446)();
      FUN_000471cc(iVar15 + 0xb90,0,iVar8 + 0x58,uVar14,iVar7 + 0x240,iVar12 + 0x88);
      iVar15 = ((long long (*)(void))FUN_000167a8)();
      uVar9 = *(undefined4 *)(iVar15 + 0xeb4);
      iVar15 = ((long long (*)(void))FUN_000167a8)();
      uVar17 = *(undefined4 *)(iVar15 + 0xeb8);
      iVar15 = ((long long (*)(void))FUN_0007d3ee)();
      uVar14 = ((long long (*)(void))FUN_0007d446)();
      iVar8 = ((long long (*)(void))FUN_0007d3ee)();
      iVar7 = ((long long (*)(void))FUN_0007d446)();
      FUN_00047260(uVar9,uVar17,iVar15 + 0x58,uVar14,iVar8 + 0x240,iVar7 + 0x88);
      iVar15 = ((long long (*)(void))FUN_00023ee0)();
      if (iVar15 == 6) {
        iVar15 = ((long long (*)(void))FUN_0007d3ee)();
        iVar8 = ((long long (*)(void))FUN_0007d446)();
        iVar7 = ((long long (*)(void))FUN_0007d3ee)();
        iVar12 = ((long long (*)(void))FUN_0007d446)();
        FUN_00043e90(0,DAT_0003f280,0,iVar15 + 0x7a,iVar8 + 0x37,iVar7 + 0x23a,iVar12 + 0x52,1,0,0,0
                     ,0);
        iVar8 = ((long long (*)(void))FUN_0007d3ee)();
        iVar7 = ((long long (*)(void))FUN_0007d446)();
        iVar12 = ((long long (*)(void))FUN_0007d3ee)();
        iVar13 = ((long long (*)(void))FUN_0007d446)();
        iVar7 = iVar7 + 0x52;
        iVar12 = iVar12 + 0x23a;
        iVar13 = iVar13 + 0x6d;
        iVar8 = iVar8 + 0xd1;
        iVar15 = DAT_0003f284;
      }
      else {
        iVar15 = ((long long (*)(void))FUN_0007d3ee)();
        iVar8 = ((long long (*)(void))FUN_0007d446)();
        iVar7 = ((long long (*)(void))FUN_0007d3ee)();
        iVar12 = ((long long (*)(void))FUN_0007d446)();
        FUN_00043e90(0,DAT_0003f278,0,iVar15 + 0xb0,iVar8 + 0x37,iVar7 + 0x226,iVar12 + 0x52,1,0,0,0
                     ,0);
        iVar8 = ((long long (*)(void))FUN_0007d3ee)();
        iVar7 = ((long long (*)(void))FUN_0007d446)();
        iVar12 = ((long long (*)(void))FUN_0007d3ee)();
        iVar13 = ((long long (*)(void))FUN_0007d446)();
        iVar7 = iVar7 + 0x52;
        iVar12 = iVar12 + 0x226;
        iVar13 = iVar13 + 0x6d;
        iVar8 = iVar8 + 0xda;
        iVar15 = DAT_0003f27c;
      }
    }
    FUN_00043e90(0,iVar15,0,iVar8,iVar7,iVar12,iVar13,1,0,0,0,0);
  }
LAB_0003ed90:
  if (*DAT_0003ef54 == '\x01') {
    *DAT_0003ef54 = '\0';
    if (*DAT_0003ef58 == '\x01') {
      uVar14 = ((long long (*)(void))FUN_0007d3ee)();
      iVar15 = ((long long (*)(void))FUN_0007d446)();
      iVar8 = ((long long (*)(void))FUN_0007d3ee)();
      iVar7 = ((long long (*)(void))FUN_0007d446)();
      FUN_00043e90(0,param_2 + 0x95,0,uVar14,iVar15 + 0x37,iVar8 + 0x4c,iVar7 + 0x52,1,0,0,0,0);
      uVar14 = ((long long (*)(void))FUN_0007d3ee)();
      iVar15 = ((long long (*)(void))FUN_0007d446)();
      iVar8 = ((long long (*)(void))FUN_0007d3ee)();
      iVar7 = ((long long (*)(void))FUN_0007d446)();
      FUN_00043e90(0,param_2 + 0xd,0,uVar14,iVar15 + 0x52,iVar8 + 0x4c,iVar7 + 0x6d,1,0,0,0,0);
      uVar14 = ((long long (*)(void))FUN_0007d3ee)();
      iVar15 = ((long long (*)(void))FUN_0007d446)();
      iVar8 = ((long long (*)(void))FUN_0007d3ee)();
      iVar7 = ((long long (*)(void))FUN_0007d446)();
      FUN_00043e90(0,param_2 + 0x25,0,uVar14,iVar15 + 0x6d,iVar8 + 0x4c,iVar7 + 0x88,1,0,0,0,0);
    }
    iVar15 = ((long long (*)(void))FUN_000167a8)();
    iVar15 = *(byte *)(*(int *)(iVar15 + 0xfec) + 0x5e) - 1;
    if (iVar15 != 0) {
      iVar15 = 1;
    }
    uVar14 = ((long long (*)(void))FUN_0007d224)();
    uVar9 = ((long long (*)(void))FUN_0007d3ee)();
    iVar8 = ((long long (*)(void))FUN_0007d446)();
    iVar7 = ((long long (*)(void))FUN_0007d3ee)();
    iVar12 = ((long long (*)(void))FUN_0007d446)();
    FUN_000442bc(uVar14,uVar9,iVar8 + 2,iVar7 + 0x4c,iVar12 + 0x1d,3,iVar15);
  }
  if (*DAT_0003ef5c == '\x01') {
    *DAT_0003ef5c = '\0';
    puVar5 = (undefined1 *)DAT_0003ef64;
    if (*(int *)(param_2 + 0xb1) == 0x1210) {
      if (2 < *DAT_0003ef60) {
        if (*DAT_0003ef68 == 0) {
          DEBUG_PRINT(DAT_0003ef70,DAT_0003ef6c);
        }
        else {
          FUN_00019c70(DAT_0003ef70,DAT_0003ef6c);
        }
      }
      uVar32 = FUN_00086c78(DAT_0003ef74,0,0x1210);
      FUN_0007d376(DAT_0003ef78,(uint)(uVar32 >> 32),0xffffffff,0xffffffff);
      FUN_00086c04(DAT_0003ef74,DAT_0003ef7c,0x1210);
    }
    else {
      if (2 < *DAT_0003ef60) {
        if (*DAT_0003f28c == 0) {
          DEBUG_PRINT(DAT_0003f298,DAT_0003f290);
        }
        else {
          ((long long (*)(void))FUN_00019c70)();
        }
      }
      FUN_00086c78(DAT_0003f29c,0,0x1210);
      thunk_FUN_000723b8(DAT_0003f2a0,extraout_r1_00,0xffffffff,0xffffffff);
      FUN_0007da70(DAT_0003f2a4,*(undefined4 *)(param_2 + 0xb1),DAT_0003f29c);
    }
    uVar14 = DAT_0003ef78;
    *puVar5 = 1;
    FUN_0007d37a(uVar14);
  }
  *(undefined1 *)(iVar4 + 4) = 1;
  *(undefined1 *)(iVar4 + 5) = 0;
  *(undefined1 *)(iVar4 + 0x15) = 0;
  return;
}
