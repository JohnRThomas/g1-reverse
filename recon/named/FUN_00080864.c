/* named: FUN_00080864 */
/* Reconstructed FUN_00080864 @ 0x80864  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void FUN_00080864(uint32_t *param_1, uint32_t *param_2)
{
  volatile uint32_t *puVar1 = *(volatile uint32_t **)((char*)0 + *param_1 + 0xc);
  *puVar1 = *param_2;
  puVar1[1] = param_2[1];
  return;
}

