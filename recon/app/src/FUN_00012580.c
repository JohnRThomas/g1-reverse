/* Reconstructed FUN_00012580 @ 0x12580  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint64_t FUN_0000d89c(int32_t, int32_t);
extern void FUN_0000d8f8(int32_t, int32_t, uint32_t, uint32_t);
extern void FUN_0000ec34(void);
extern uint32_t FUN_0000e1a4(void);

void FUN_00012580(uint32_t *param_1, uint32_t param_2, uint32_t param_3)
{
  uint64_t prod = (uint64_t)param_2 * (uint64_t)param_3;
  int32_t arg0 = (int32_t)prod;
  int32_t arg1 = (int32_t)param_3 * ((int32_t)param_2 >> 31) + (int32_t)(prod >> 32);
  uint64_t uVar3 = FUN_0000d89c(arg0, arg1);
  FUN_0000d8f8((int32_t)uVar3, (int32_t)(uVar3 >> 32), 0x3a92a305UL, 0x40239d01UL);
  FUN_0000ec34();
  uint32_t uVar2 = 0xf4240UL;
  uint32_t uVar1 = FUN_0000e1a4();
  param_1[0] = uVar1;
  param_1[1] = uVar2;
}

