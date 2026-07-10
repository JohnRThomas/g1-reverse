/* Reconstructed FUN_0002f080 @ 0x2f080  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned short ushort;
extern int DEBUG_PRINT(int,...); extern int FUN_000167a8(int,...); extern int FUN_00019c70(int,...);
extern int FUN_000181fc(int,...); extern int FUN_0002ebd8(int,...); extern int FUN_0008638c(int,...);
typedef int (*cp)(int,...);

uint FUN_0002f080(void)
{
  int iVar7, iVar8; uint uVar12;
  int *puVar2 = (int*)0x87d40;
  iVar7 = FUN_000181fc(0);
  iVar8 = FUN_000167a8(0);
  uVar12 = *(volatile ushort*)(iVar8 + 0x105c) & 2;
  if ((*(volatile ushort*)(iVar8 + 0x105c) & 2) != 0) {
    if (2 < *(volatile int*)0x2000230c) {
      if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0xa4038,0xa41b0);
      else FUN_00019c70(0);
    }
    iVar8 = FUN_0008638c(0x87d40);
    if (iVar8 == 0) {
      if (0 < *(volatile int*)0x2000230c) {
        if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0xa404b,0xa41b0,*(volatile int*)puVar2);
        else FUN_00019c70(0);
      }
    } else {
      if (2 < *(volatile int*)0x2000230c) {
        if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0,0xa41b0,*(volatile int*)puVar2);
        else FUN_00019c70(0);
      }
      iVar8 = FUN_0002ebd8(0);
      if (iVar8 == 0) { for(;;) FUN_0002ebd8(0); }
    }
    uVar12 = 1;
  }
  {
    int p2 = *(volatile int*)(0x87d40 + 8);
    cp fp = *(cp volatile*)(p2 + 4);
    iVar7 = fp(0x87d40, 0);
  }
  (void)iVar7;
  return uVar12;
}

