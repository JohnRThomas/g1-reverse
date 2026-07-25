#include <zephyr/kernel.h>
#undef NRF_NVMC_S
#include "g1_app_symbols.h"
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

int spawn_proxy_thread(int param_1)
{
  k_tid_t tid = k_thread_create((struct k_thread *)((unsigned long)&g_proxy_thread) /*=0x20004c08*/,
                                (k_thread_stack_t *)((unsigned long)&g_proxy_thread_stack) /*=0x20028668*/,
                                0x800,
                                (k_thread_entry_t)(unsigned long)(ADDR_proxy_thread_handler_THUMB /*=0x47c49*/),
                                (void *)(unsigned long)param_1, NULL, NULL,
                                (int)0xfffffff4, 0, K_NO_WAIT);
  *(volatile int*)((unsigned long)&g_proxy_thread_id) /*=0x2000a090*/ = (int)(unsigned long)tid;
  return -(int)(unsigned int)(tid == 0);
}
