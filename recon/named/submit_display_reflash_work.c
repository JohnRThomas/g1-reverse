/* readable reconstruction; identity: FUN_0004904c @ 0x0004904c
 * public-name: submit_display_reflash_work
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   submit_display_reflash_work              <= FUN_0004904c @ 0x0004904c
 *   k_thread_priority_set                    <= FUN_00074554 @ 0x00074554
 * address symbols (name @ address):
 *   g_display_thread_id                      @ 0x2000a09c
 *   g_display_reflash_pending                @ 0x2001d446
 */
/* Reconstructed FUN_0004904c @ 0x4904c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void k_thread_priority_set(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void submit_display_reflash_work(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile uint32_t *p = (volatile uint32_t *)0x2000a09cUL;
    k_thread_priority_set(*p, 0xfffffff0U, param_3, (unsigned int)(uintptr_t)p, param_4);
    *(volatile uint8_t *)0x2001d446UL = 1;
}
