#include <zephyr/kernel.h>
#undef NRF_NVMC_S
#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002201c @ 0x0002201c
 * public-name: init_ble_work_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   init_ble_work_thread                     <= FUN_0002201c @ 0x0002201c
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 *   kmutex_dlist_init                        <= FUN_000864c2 @ 0x000864c2
 *   k_timer_init                             <= FUN_00086726 @ 0x00086726
 * address symbols (name @ address):
 *   rodata_19ff1                             @ 0x00019ff1
 *   ADDR_FUN_00021da8_THUMB                  @ 0x00021da9
 *   g_ble_work_timer                         @ 0x20003d28
 *   g_ble_work_thread                        @ 0x20003d60
 *   g_ble_work_queue                         @ 0x20007574
 *   g_ble_work_thread_stack                  @ 0x2001e968
 */
/* Reconstructed FUN_0002201c @ 0x2201c  (parity: 300/300 trials, PROVEN) */

extern void kmutex_dlist_init(int);

int init_ble_work_thread(int param_1)
{
    kmutex_dlist_init(((unsigned long)&g_ble_work_queue) /*=0x20007574*/);
    k_timer_init((struct k_timer *)((unsigned long)&g_ble_work_timer) /*=0x20003d28*/,
                 (k_timer_expiry_t)(unsigned long)((unsigned long)&rodata_19ff1) /*=0x19ff1*/, NULL);
    k_thread_create((struct k_thread *)((unsigned long)&g_ble_work_thread) /*=0x20003d60*/,
                    (k_thread_stack_t *)((unsigned long)&g_ble_work_thread_stack) /*=0x2001e968*/,
                    0x3000,
                    (k_thread_entry_t)(unsigned long)(ADDR_FUN_00021da8_THUMB /*=0x21da9*/),
                    (void *)(unsigned long)param_1, NULL, NULL,
                    (int)0xfffffff1, 0, K_NO_WAIT);
    return 0;
}
