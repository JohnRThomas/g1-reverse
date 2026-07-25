#include <zephyr/kernel.h>
#undef NRF_NVMC_S
#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00023a54 @ 0x00023a54
 * public-name: spawn_flash_ops_and_brightness_threads
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   spawn_flash_ops_and_brightness_threads   <= FUN_00023a54 @ 0x00023a54
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 *   z_impl_k_sem_init                        <= FUN_00086534 @ 0x00086534
 * address symbols (name @ address):
 *   ADDR_flash_ops_thread_THUMB              @ 0x00023481
 *   ADDR_FUN_00023844_THUMB                  @ 0x00023845
 *   g_flash_ops_thread                       @ 0x20003e38
 *   g_brightness_thread                      @ 0x20003f10
 *   g_app_language_msgq                      @ 0x200079e4
 *   g_flash_ops_thread_stack                 @ 0x20021968
 *   g_brightness_thread_stack                @ 0x20022168
 */
/* Reconstructed FUN_00023a54 @ 0x23a54  (parity: 300/300 trials, PROVEN) */

void spawn_flash_ops_and_brightness_threads(int param_1){
    k_sem_init((struct k_sem *)((unsigned long)&g_app_language_msgq) /*=0x200079e4*/, 0, 0x14);
    k_thread_create((struct k_thread *)((unsigned long)&g_flash_ops_thread) /*=0x20003e38*/,
                    (k_thread_stack_t *)((unsigned long)&g_flash_ops_thread_stack) /*=0x20021968*/,
                    0x800,
                    (k_thread_entry_t)(unsigned long)(ADDR_flash_ops_thread_THUMB /*=0x23481*/),
                    (void *)(unsigned long)param_1, NULL, NULL,
                    (int)0xfffffff4, 0, K_NO_WAIT);
    k_thread_create((struct k_thread *)((unsigned long)&g_brightness_thread) /*=0x20003f10*/,
                    (k_thread_stack_t *)((unsigned long)&g_brightness_thread_stack) /*=0x20022168*/,
                    0x1400,
                    (k_thread_entry_t)(unsigned long)(ADDR_FUN_00023844_THUMB /*=0x23845*/),
                    (void *)(unsigned long)param_1, NULL, NULL,
                    (int)0xfffffff5, 0, K_NO_WAIT);
}
