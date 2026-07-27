/* Reconstructed FUN_00034524 @ 0x34524  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef uint32_t undefined4; typedef unsigned int uint;
extern int DEBUG_PRINT(int,...); extern int FUN_000167a8(int,...); extern int FUN_00019c70(int,...);
extern int FUN_0002c1fc(int,...); extern int FUN_00033b0c(int,...); extern int FUN_00033b4c(int,...);
extern int FUN_00033cb0(int,...); extern int FUN_00033cdc(int,...); extern int FUN_00033cf8(int,...);
extern int FUN_00033d58(int,...); extern int FUN_00033f24(int,...); extern int FUN_0003444c(int,...);
extern int FUN_0007d224(int,...); extern int FUN_00086c04(int,...); extern int FUN_00086c78(int,...);

void FUN_00034524(int param_1)
{
  char cVar1; int bVar2; byte *pbVar3; volatile byte *puVar4; byte uVar5;
  char *pcVar6; int iVar7; uint uVar8; int iVar9; int iVar10; int iVar13; int iVar14;
  uint uVar12; byte bVar15;
  iVar10 = 0x20008dac;
  if ((*(volatile char*)(iVar10 + 0x118) != 0) &&
      (iVar13 = *(volatile int*)(iVar10 + 0x110), iVar13 == param_1) &&
      (*(volatile char*)(iVar10 + 0x115) == 4)) {
    cVar1 = *(volatile char*)(iVar10 + 0x2b8);
    pcVar6 = (char*)FUN_000167a8(0);
    if ((*pcVar6 == 1) && (cVar1 == 0) && (iVar7 = FUN_00033f24(10,iVar13), iVar7 != 0)) {
      if (0 < *(volatile int*)0x2000230c) {
        if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0xa8174,0xa8255,iVar13);
        else FUN_00019c70(0xa8174,0xa8255,iVar13);
      }
      FUN_00086c78(0x20008eb4,0,0x1b4);
      return;
    }
    puVar4 = (volatile byte*)0x20018d8e;
    *puVar4 = 1;
    iVar13 = FUN_000167a8(0);
    if (*(char*)(iVar13 + 0xd5) != 4) FUN_00033d58(0);
    uVar8 = FUN_00033cdc(0);
    iVar13 = 0x20007dac;
    iVar7 = *(volatile int*)(iVar10 + 0x2b8);
    if (iVar7 == 0) {
      if (uVar8 == 10) {
        iVar7 = 0; iVar14 = 0x20007dac;
        do {
          iVar9 = FUN_00086c04(iVar14,iVar14 + 0x1b4,0x1b4);
          *(char*)(iVar9 + 0xc) = (char)iVar7;
          iVar7 = iVar7 + 1; iVar14 = iVar14 + 0x1b4;
        } while (iVar7 != 9);
        uVar8 = 9;
      }
      iVar14 = uVar8 * 0x1b4;
      iVar10 = FUN_00086c04(iVar13 + iVar14, iVar10 + 0x108);
      iVar7 = *(int*)(iVar13 + iVar14);
      *(char*)(iVar10 + 0xc) = (char)uVar8;
      if (iVar7 == 0) { *(undefined4*)(iVar13 + iVar14) = FUN_0007d224(0); }
      iVar10 = uVar8 * 0x1b4 + iVar13;
      *(char*)(iVar10 + 0xe) = 1;
      if (*(int*)(iVar10 + 4) != 0) { *(undefined4*)(iVar10 + 4) = FUN_0007d224(0); }
    } else if (iVar7 == 2) {
      if (uVar8 != 0) {
        bVar2 = 0; bVar15 = 0; iVar7 = 0x20007dac;
        do {
          if ((*(int*)(iVar7 + 8) == *(int*)(iVar10 + 0x110)) || bVar2) {
            iVar14 = FUN_00086c04(iVar7, iVar7 + 0x1b4, 0x1b4);
            bVar2 = 1; *(byte*)(iVar14 + 0xc) = bVar15;
          }
          bVar15 = bVar15 + 1; iVar7 = iVar7 + 0x1b4;
        } while (bVar15 < uVar8);
        if (bVar2) FUN_00086c78((uVar8 - 1) * 0x1b4 + iVar13, 0);
      }
    } else if ((iVar7 == 1) && (uVar8 != 0)) {
      uVar12 = 0; iVar7 = 0x20007dac;
      do {
        if (*(int*)(iVar7 + 8) == *(int*)(iVar10 + 0x110)) {
          FUN_00086c04(uVar12 * 0x1b4 + 0x20007dac, iVar10 + 0x108); break;
        }
        uVar12 = uVar12 + 1; iVar7 = iVar7 + 0x1b4;
      } while ((uVar12 & 0xff) < uVar8);
    }
    FUN_00086c78(0x20008eb4, 0, 0x1b4);
    pbVar3 = (byte*)0x2001a22b;
    uVar8 = 10;
    while (1) {
      bVar15 = *pbVar3;
      if (bVar15 <= uVar8) break;
      if (*(char*)(uVar8 * 0x1b4 + iVar13 + 0x1c4) == 0) goto LAB_34640;
      iVar10 = FUN_00086c04(iVar13 + uVar8 * 0x1b4, uVar8 * 0x1b4 + 0x1b4 + iVar13, 0x1b4);
      *(char*)(iVar10 + 0xc) = (char)uVar8;
      *(char*)(iVar10 + 0xd) = 0;
      uVar8 = uVar8 + 1 & 0xff;
    }
    if (10 < bVar15) { LAB_34640: *pbVar3 = bVar15 - 1; }
    FUN_00086c78((uint)*pbVar3 * 0x1b4 + iVar13, 0);
    iVar10 = FUN_000167a8(0);
    if (*(char*)(iVar10 + 0xd5) == 4) {
      iVar10 = FUN_000167a8(0);
      uVar5 = FUN_00033cf8(0);
      *(char*)(iVar10 + 0xdd) = uVar5;
    } else FUN_00033d58(0);
    if (cVar1 == 0) {
      iVar10 = FUN_00033cb0(0);
      iVar13 = FUN_000167a8(0);
      if (*(char*)(iVar13 + 0xd5) == 4) {
        if (iVar10 != 0xff) FUN_0002c1fc(0);
      } else {
        iVar10 = FUN_000167a8(0);
        if (((*(char*)(iVar10 + 0xd5) == 0) ||
             ((iVar10 = FUN_000167a8(0), *(char*)(iVar10 + 0x108f) != 0 &&
               (iVar10 = FUN_000167a8(0), *(char*)(iVar10 + 0xd5) == 6)))) &&
            (iVar10 = FUN_0003444c(0), iVar10 != 1)) {
          *(volatile byte*)0x2001a229 = 1;
        }
      }
    }
    if (*(volatile char*)0x20018d9f == 0) { FUN_00033b0c(0); FUN_00033b4c(0); }
    *puVar4 = 0;
  }
  return;
}

