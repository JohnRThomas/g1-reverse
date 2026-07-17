#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003304c @ 0x0003304c
 * public-name: FUN_0003304c
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   ADDR_FUN_000324bc_THUMB                  @ 0x000324bd
 *   g_aging_mode_aux_thread                  @ 0x20004798
 *   g_aging_mode_aux_thread_stack            @ 0x20027668
 */
/* Reconstructed FUN_0003304c @ 0x3304c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_00071eac(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);

void FUN_0003304c(void)
{
  FUN_00071eac(((unsigned long)&g_aging_mode_aux_thread) /*=0x20004798*/,((unsigned long)&g_aging_mode_aux_thread_stack) /*=0x20027668*/,0x400,ADDR_FUN_000324bc_THUMB /*=0x324bd*/,0,0,0,0xfffffff4UL,0);
}
