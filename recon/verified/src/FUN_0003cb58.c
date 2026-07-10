/* Reconstructed FUN_0003cb58 @ 0x3cb58  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned long long undefined8;
extern int FUN_000167a8(int,...); extern int FUN_000431b4(int,...); extern int FUN_000431c0(int,...);
extern int FUN_000432d0(int,...); extern int FUN_00043308(int,...); extern int FUN_0004334c(int,...);
extern int FUN_00043484(int,...); extern int FUN_00043e90(int,...);
extern unsigned long long FUN_0007d2d8(int,...);
extern int FUN_0007d3ee(int,...); extern int FUN_0007d446(int,...); extern int FUN_0007d4b2(int,...);

undefined4 FUN_0003cb58(int param_1,undefined4 param_2,int param_3)
{
  char cVar1; uint uVar2; uint uVar3; volatile char *pcVar4; int iVar5; int iVar6; undefined4 uVar7;
  int iVar8; int iVar9; uint uVar10; unsigned long long uVar11; int base;
  FUN_000431b4(param_1 + 0x24);
  pcVar4 = (volatile char*)0x2001b9aa;
  if (param_3 == 2) {
    FUN_000431c0(0);
    iVar5 = FUN_000167a8(0);
    *(volatile char*)(*(int*)(iVar5 + 0x1010)) = 0;
    *pcVar4 = 0;
  }
  else if (*pcVar4 == 0) {
    FUN_000431c0(0); FUN_000432d0(0); FUN_00043308(0);
    *pcVar4 = 1;
    uVar11 = FUN_0007d2d8(0);
    iVar5 = FUN_000167a8(0);
    base = *(int*)(iVar5 + 0x1010);
    *(volatile uint*)(base + 7) = (uint)(uVar11 >> 32);
    *(volatile uint*)(base + 3) = (uint)uVar11;
    cVar1 = *(volatile char*)0x2001b9ab;
    if (cVar1 == 1) {
      iVar5 = FUN_0007d3ee(0); iVar6 = FUN_0007d446(0);
      FUN_0004334c(7,iVar5 + 0xd8,iVar6 + 0x3a,0,0,0,1);
      uVar7 = FUN_0007d4b2(0x27);
      iVar5 = FUN_0007d3ee(0); iVar6 = FUN_0007d446(0);
      iVar8 = FUN_0007d3ee(0); iVar9 = FUN_0007d446(0);
      iVar5 = iVar5 + 0x10c;
    } else if (cVar1 == 2) {
      uVar7 = FUN_0007d3ee(0); iVar5 = FUN_0007d446(0);
      FUN_00043484(0x48,uVar7,iVar5 + 0x3a,0,0,0);
      uVar7 = FUN_0007d4b2(0x26);
      iVar5 = FUN_0007d3ee(0); iVar6 = FUN_0007d446(0);
      iVar8 = FUN_0007d3ee(0); iVar9 = FUN_0007d446(0);
      iVar5 = iVar5 + 0x58;
    } else {
      if (cVar1 != 0) return 0;
      iVar5 = FUN_0007d3ee(0); iVar6 = FUN_0007d446(0);
      FUN_0004334c(6,iVar5 + 0xec,iVar6 + 0x3a,0,0,0,1);
      uVar7 = FUN_0007d4b2(0x25);
      iVar5 = FUN_0007d3ee(0); iVar6 = FUN_0007d446(0);
      iVar8 = FUN_0007d3ee(0); iVar9 = FUN_0007d446(0);
      iVar5 = iVar5 + 0x120;
    }
    FUN_00043e90(0,uVar7,0,iVar5,iVar6 + 0x37,iVar8 + 0x240,iVar9 + 0x88,2,0,0,0,0);
  }
  else if (*pcVar4 == 1) {
    cVar1 = *(volatile char*)0x2001b9ab;
    if (cVar1 == 1) {
      iVar5 = FUN_0007d3ee(0); iVar6 = FUN_0007d446(0);
      FUN_0004334c(7,iVar5 + 0xd8,iVar6 + 0x3a,0,0,0,1);
      uVar11 = FUN_0007d2d8(0);
      iVar5 = FUN_000167a8(0);
      base = *(int*)(iVar5 + 0x1010);
      uVar10 = *(uint*)(base + 3);
      uVar2 = (int)(uVar11 >> 32) - *(int*)(base + 7);
      uVar3 = (uint)((uint)uVar11 < uVar10);
      if (uVar2 != uVar3 || uVar2 - uVar3 < (uint)(0x5db < (uint)uVar11 - uVar10)) {
        iVar5 = FUN_000167a8(0);
        *(volatile char*)(*(int*)(iVar5 + 0x1010)) = 0;
      }
    } else {
      if (cVar1 == 2) {
        uVar11 = FUN_0007d2d8(0);
        iVar5 = FUN_000167a8(0);
        base = *(int*)(iVar5 + 0x1010);
        uVar10 = *(uint*)(base + 3);
        uVar2 = (int)(uVar11 >> 32) - *(int*)(base + 7);
        uVar3 = (uint)((uint)uVar11 < uVar10);
        if (uVar2 == uVar3 && (uint)(0x5db < (uint)uVar11 - uVar10) <= uVar2 - uVar3) return 0;
      } else if (cVar1 == 0) {
        iVar5 = FUN_0007d3ee(0); iVar6 = FUN_0007d446(0);
        FUN_0004334c(6,iVar5 + 0xec,iVar6 + 0x3a,0,0,0,1);
        uVar11 = FUN_0007d2d8(0);
        iVar5 = FUN_000167a8(0);
        base = *(int*)(iVar5 + 0x1010);
        uVar10 = *(uint*)(base + 3);
        uVar2 = (int)(uVar11 >> 32) - *(int*)(base + 7);
        uVar3 = (uint)((uint)uVar11 < uVar10);
        if (uVar2 == uVar3 && (uint)(0x5db < (uint)uVar11 - uVar10) <= uVar2 - uVar3) return 0;
        iVar5 = FUN_000167a8(0);
        *(volatile char*)(*(int*)(iVar5 + 0x1010)) = 0;
        return 0;
      }
      iVar5 = FUN_000167a8(0);
      *(volatile char*)(*(int*)(iVar5 + 0x1010)) = 0;
    }
  }
  return 0;
}

