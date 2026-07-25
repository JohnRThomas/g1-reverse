/* Reconstructed FUN_00047ad0 @ 0x47ad0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
/* CONFIG_TIMEOUT_64BIT: z_impl_k_thread_create's 10th parameter is a
 * 64-bit k_timeout_t delay, AAPCS-placed 8-byte aligned at sp+0x18.
 * The original writes it (strd r,r,[sp,#0x18]); it must be passed. */
extern int FUN_00071eac(int a,int b,int c,int d,int e,int f,int g,int h,int i,unsigned long long delay);
int FUN_00047ad0(int param_1)
{
  int iVar1;
  iVar1 = FUN_00071eac(0x20004c08,0x20028668,0x800,0x00047c49,param_1,0,0,0xfffffff4,0,0ULL);
  *(volatile int*)0x2000a090UL = iVar1;
  return -(unsigned int)(iVar1 == 0);
}

