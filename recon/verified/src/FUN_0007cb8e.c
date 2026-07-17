/* Reconstructed FUN_0007cb8e @ 0x7cb8e  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>

extern uint64_t FUN_0000e244(int,int,int,int);
extern void thunk_FUN_00074844(uint32_t,uint32_t,uint32_t,uint32_t);

void FUN_0007cb8e(int param_1, uint32_t unused_1, uint32_t unused_2,
                  uint32_t forwarded_3)
{
  uint64_t result = FUN_0000e244(param_1 * 0x8000 + 999,
                                 param_1 >> 0x11, 1000, 0);
  (void)unused_1;
  (void)unused_2;
  thunk_FUN_00074844((uint32_t)result, (uint32_t)(result >> 32),
                     1000, forwarded_3);
}
