/* Reconstructed FUN_00026c8c @ 0x26c8c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef unsigned int uint;
extern int FUN_00025448(int,...); extern int FUN_000167a8(int,...);
extern int FUN_0002aeb4(int,...);

void FUN_00026c8c(void)
{
  byte *pbVar1; int iVar7;
  uint uVar6 = FUN_00025448(0);
  if (((4999 < uVar6) ||
       (iVar7 = FUN_000167a8(0), pbVar1 = (byte*)0x20018d94, *(byte *)(iVar7 + 0xfc0) < 0x62)) ||
      (*(volatile byte*)0x20018d94 == 0)) {
    return;
  }
  (void)pbVar1;
  FUN_0002aeb4(0);
  for(;;) FUN_0002aeb4(0);
}

