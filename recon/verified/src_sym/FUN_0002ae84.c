/* Reconstructed FUN_0002ae84 @ 0x2ae84  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_00074844(unsigned int a, unsigned int b);
typedef int (*fnptr)(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);

int FUN_0002ae84(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  (void)param_1; (void)param_2;
  volatile unsigned int *puVar1 = (volatile unsigned int *)0x20007b50UL /* device_info.gap_10E0+116 */;
  int iVar4 = 5;
  int iVar5 = *(volatile int*)(0x87cc8UL + 8);
  int iVar2;
  for (;;) {
    fnptr pcVar3 = *(volatile fnptr*)(iVar5 + 0xc);
    iVar2 = pcVar3(0x87cc8, *puVar1, param_3, (unsigned int)(uintptr_t)pcVar3, param_4);
    if (iVar2 == 0) return 0;
    FUN_00074844(0x667, 0);
    iVar4 = iVar4 - 1;
    if (iVar4 == 0) break;
  }
  return iVar2;
}

