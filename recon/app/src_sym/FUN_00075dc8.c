/* Reconstructed FUN_00075dc8 @ 0x75dc8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern float FUN_000869c6(void);
extern int *thunk_FUN_00071678(void);

float FUN_00075dc8(float param_1)
{
  float fVar3 = FUN_000869c6();
  float fVar1 = 0.0f;
  if ((*(volatile int8_t*)0x200035afUL != -1) && (param_1 < fVar1)) {
    unsigned int *puVar2 = thunk_FUN_00071678();
    fVar3 = fVar1 / fVar1;
    *puVar2 = 0x21;
  }
  return fVar3;
}

