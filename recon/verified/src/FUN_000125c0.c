/* Reconstructed FUN_000125c0 @ 0x125c0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint64_t FUN_0000d89c(int32_t, int32_t);
extern uint64_t FUN_0000d8f8(uint32_t, uint32_t, uint32_t, uint32_t);
extern int64_t FUN_0000ec34(uint32_t, uint32_t);

void FUN_000125c0(uint32_t *param_1, uint32_t param_2, uint32_t param_3)
{
  uint64_t product = (uint64_t)param_2 * (uint64_t)param_3;
  uint32_t product_high = (uint32_t)(product >> 32) +
      param_3 * (0u - (param_2 >> 31));
  uint64_t as_double = FUN_0000d89c((int32_t)(uint32_t)product,
                                     (int32_t)product_high);
  uint64_t multiplied = FUN_0000d8f8((uint32_t)as_double,
                                      (uint32_t)(as_double >> 32),
                                      0x63f11168UL, 0x3f91df46UL);
  int64_t scaled = FUN_0000ec34((uint32_t)multiplied,
                                (uint32_t)((uint64_t)multiplied >> 32));
  param_1[0] = (uint32_t)(scaled / 1000000);
  param_1[1] = (uint32_t)(scaled % 1000000);
}
