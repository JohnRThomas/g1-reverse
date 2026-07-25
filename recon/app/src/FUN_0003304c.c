/* Reconstructed FUN_0003304c @ 0x3304c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
/* CONFIG_TIMEOUT_64BIT: z_impl_k_thread_create's 10th parameter is a
 * 64-bit k_timeout_t delay, AAPCS-placed 8-byte aligned at sp+0x18.
 * The original writes it (strd r,r,[sp,#0x18]); it must be passed. */
extern void FUN_00071eac(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint64_t);

void FUN_0003304c(void)
{
  FUN_00071eac(0x20004798UL,0x20027668UL,0x400,0x324bdUL,0,0,0,0xfffffff4UL,0,0ULL);
}

