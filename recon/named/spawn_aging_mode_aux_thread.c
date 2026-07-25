/* readable reconstruction; identity: FUN_0003304c @ 0x0003304c
 * public-name: spawn_aging_mode_aux_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   spawn_aging_mode_aux_thread              <= FUN_0003304c @ 0x0003304c
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 * address symbols (name @ address):
 *   ADDR_mic_transm_thread_THUMB             @ 0x000324bd
 *   g_aging_mode_aux_thread                  @ 0x20004798
 *   g_aging_mode_aux_thread_stack            @ 0x20027668
 */
/* Reconstructed FUN_0003304c @ 0x3304c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
/* CONFIG_TIMEOUT_64BIT: z_impl_k_thread_create's 10th parameter is a
 * 64-bit k_timeout_t delay, AAPCS-placed 8-byte aligned at sp+0x18.
 * The original writes it (strd r,r,[sp,#0x18]); it must be passed. */
extern void z_impl_k_thread_create(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint64_t);

void spawn_aging_mode_aux_thread(void)
{
  z_impl_k_thread_create(0x20004798UL,0x20027668UL,0x400,0x324bdUL,0,0,0,0xfffffff4UL,0,0ULL);
}
