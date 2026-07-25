#include <zephyr/kernel.h>
#undef NRF_NVMC_S
#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00049638 @ 0x00049638
 * public-name: spawn_display_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   spawn_display_thread                     <= FUN_00049638 @ 0x00049638
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 * address symbols (name @ address):
 *   ADDR_display_thread_handler_THUMB        @ 0x00049091
 *   g_display_thread                         @ 0x20004d18
 *   g_display_thread_id                      @ 0x2000a09c
 *   g_display_thread_stack_buf               @ 0x20028e68
 */
/* Reconstructed FUN_00049638 @ 0x49638  (parity: 300/300 trials, PROVEN) */

unsigned int spawn_display_thread(unsigned int param_1)
{
    k_tid_t tid = k_thread_create((struct k_thread *)((unsigned long)&g_display_thread) /*=0x20004d18*/,
                                  (k_thread_stack_t *)((unsigned long)&g_display_thread_stack_buf) /*=0x20028e68*/,
                                  0x1400,
                                  (k_thread_entry_t)(unsigned long)(ADDR_display_thread_handler_THUMB /*=0x49091*/),
                                  (void *)(unsigned long)param_1, NULL, NULL,
                                  (int)0xfffffff2, 0, K_NO_WAIT);
    *(volatile unsigned int*)((unsigned long)&g_display_thread_id) /*=0x2000a09c*/ = (unsigned int)(unsigned long)tid;
    return 0;
}
