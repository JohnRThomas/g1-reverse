#include "g1_app_symbols.h"
/* named: us_to_ticks_scaled */
/* Reconstructed us_to_ticks_scaled @ 0x12580  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint64_t __floatdidf(int32_t, int32_t);
extern void __muldf3(int32_t, int32_t, uint32_t, uint32_t);
extern void __fixdfdi(void);
extern uint32_t __aeabi_ldivmod(void);

void us_to_ticks_scaled(uint32_t *param_1, uint32_t param_2, uint32_t param_3)
{
  uint64_t prod = (uint64_t)param_2 * (uint64_t)param_3;
  int32_t arg0 = (int32_t)prod;
  int32_t arg1 = (int32_t)param_3 * ((int32_t)param_2 >> 31) + (int32_t)(prod >> 32);
  uint64_t uVar3 = __floatdidf(arg0, arg1);
  __muldf3((int32_t)uVar3, (int32_t)(uVar3 >> 32), 0x3a92a305UL, 0x40239d01UL);
  __fixdfdi();
  uint32_t uVar2 = "size" /*=0xf4240*/;
  uint32_t uVar1 = __aeabi_ldivmod();
  param_1[0] = uVar1;
  param_1[1] = uVar2;
}

