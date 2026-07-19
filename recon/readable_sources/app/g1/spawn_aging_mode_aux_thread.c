#include "g1_app_symbols.h"
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
extern void z_impl_k_thread_create(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);

void spawn_aging_mode_aux_thread(void)
{
  z_impl_k_thread_create(((unsigned long)&g_aging_mode_aux_thread) /*=0x20004798*/,((unsigned long)&g_aging_mode_aux_thread_stack) /*=0x20027668*/,0x400,ADDR_mic_transm_thread_THUMB /*=0x324bd*/,0,0,0,0xfffffff4UL,0);
}
