#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004906c @ 0x0004906c
 * public-name: FUN_0004906c
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_display_thread_id                      @ 0x2000a09c
 *   g_display_reflash_pending                @ 0x2001d446
 */
/* Reconstructed FUN_0004906c @ 0x4906c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00074554(unsigned int,unsigned int);
void FUN_0004906c(void)
{
  if (*(volatile unsigned char *)((unsigned long)&g_display_reflash_pending) /*=0x2001d446*/ == 1) {
    FUN_00074554(*(volatile unsigned int *)((unsigned long)&g_display_thread_id) /*=0x2000a09c*/, 0xfffffff2u);
    *(volatile unsigned char *)((unsigned long)&g_display_reflash_pending) /*=0x2001d446*/ = 0;
  }
}
