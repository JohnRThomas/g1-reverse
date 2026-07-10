/* Reconstructed FUN_000639d4 @ 0x639d4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef unsigned (*codep)(int,unsigned,unsigned);
extern void FUN_0007e2ec(int,unsigned);
extern void FUN_0007e2fa(int,...);
extern int FUN_0008638c(int);
unsigned FUN_000639d4(int param_1){
  unsigned char bVar1; int iVar2; unsigned uVar3; unsigned uVar4; unsigned *puVar5; unsigned uVar6; unsigned uVar7;
  puVar5 = *(unsigned **)(param_1 + 4);
  iVar2 = FUN_0008638c(*puVar5);
  if (iVar2 != 0) {
    if (puVar5[1] == 0) { return 0; }
    iVar2 = FUN_0008638c(0);
    if (iVar2 != 0) {
      uVar7 = (unsigned)*(unsigned short *)((int)puVar5 + 10);
      iVar2 = puVar5[1];
      bVar1 = *(unsigned char *)(puVar5 + 2);
      puVar5 = *(unsigned **)(iVar2 + 8);
      if ((uVar7 & 0x30) == 0x30) {
        FUN_0007e2fa(0x00099cbd,0x00099c84,0x00099c53,0x3ca);
        FUN_0007e2fa(0x00099cda);
        uVar3 = 0x3ca;
      } else if ((uVar7 & 6) == 4) {
        FUN_0007e2fa(0x00099cbd,0x00099dad,0x00099c53,0x3d1);
        uVar3 = 0x3d1;
      } else {
        uVar6 = 1u << (unsigned)bVar1;
        if ((uVar6 & **(unsigned **)(iVar2 + 4)) != 0) {
          uVar4 = **(unsigned **)(iVar2 + 0x10);
          if ((int)(uVar7 << 0x1f) < 0) { uVar4 = uVar4 | uVar6; }
          else { uVar4 = uVar4 & ~uVar6; }
          **(unsigned **)(iVar2 + 0x10) = uVar4;
          uVar3 = ((codep)*puVar5)(iVar2,(unsigned)bVar1,uVar7 | 0x400);
          return uVar3;
        }
        FUN_0007e2fa(0x00099cbd,0x00099de0,0x00099c53,0x3e4);
        FUN_0007e2fa(0x00099e1e);
        uVar3 = 0x3e4;
      }
      FUN_0007e2ec(0x00099c53,uVar3);
    }
  }
  return 0xffffffed;
}

