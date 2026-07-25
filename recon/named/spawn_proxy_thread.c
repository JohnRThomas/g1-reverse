/* readable reconstruction; identity: FUN_00047ad0 @ 0x00047ad0
 * public-name: spawn_proxy_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   spawn_proxy_thread                       <= FUN_00047ad0 @ 0x00047ad0
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 * address symbols (name @ address):
 *   ADDR_proxy_thread_handler_THUMB          @ 0x00047c49
 *   g_proxy_thread                           @ 0x20004c08
 *   g_proxy_thread_id                        @ 0x2000a090
 *   g_proxy_thread_stack                     @ 0x20028668
 */
/* Reconstructed FUN_00047ad0 @ 0x47ad0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
/* CONFIG_TIMEOUT_64BIT: z_impl_k_thread_create's 10th parameter is a
 * 64-bit k_timeout_t delay, AAPCS-placed 8-byte aligned at sp+0x18.
 * The original writes it (strd r,r,[sp,#0x18]); it must be passed. */
extern int z_impl_k_thread_create(int a,int b,int c,int d,int e,int f,int g,int h,int i,unsigned long long delay);
int spawn_proxy_thread(int param_1)
{
  int iVar1;
  iVar1 = z_impl_k_thread_create(0x20004c08,0x20028668,0x800,0x00047c49,param_1,0,0,0xfffffff4,0,0ULL);
  *(volatile int*)0x2000a090UL = iVar1;
  return -(unsigned int)(iVar1 == 0);
}
