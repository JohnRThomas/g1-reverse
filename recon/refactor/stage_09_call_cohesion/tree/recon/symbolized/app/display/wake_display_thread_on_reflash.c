#include "g1_app_symbols.h"
struct k_thread;
/* readable reconstruction; identity: FUN_0004906c @ 0x0004906c
 * public-name: wake_display_thread_on_reflash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   wake_display_thread_on_reflash           <= FUN_0004906c @ 0x0004906c
 *   k_thread_priority_set                    <= FUN_00074554 @ 0x00074554
 * address symbols (name @ address):
 *   g_display_thread_id                      @ 0x2000a09c
 *   g_display_reflash_pending                @ 0x2001d446
 */
/* Reconstructed FUN_0004906c @ 0x4906c  (parity: 300/300 trials, PROVEN) */

extern void k_thread_priority_set(struct k_thread *, int);
void wake_display_thread_on_reflash(void)
{
  if (*(volatile unsigned char *)((unsigned long)&g_display_reflash_pending) /*=0x2001d446*/ == 1) {
    k_thread_priority_set(*(volatile unsigned int *)((unsigned long)&g_display_thread_id) /*=0x2000a09c*/, 0xfffffff2u);
    *(volatile unsigned char *)((unsigned long)&g_display_reflash_pending) /*=0x2001d446*/ = 0;
  }
}
