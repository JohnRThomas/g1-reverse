/* Reconstructed FUN_000828da @ 0x828da  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void FUN_000828da(uint32_t *param_1, uint32_t *param_2)
{
  *param_1 = *param_2;
  *(uint16_t*)((char*)param_1 + 4) = *(uint16_t*)((char*)param_2 + 4);
  *(uint8_t*)((char*)param_1 + 6) = *(uint8_t*)((char*)param_2 + 6);
  return;
}

