#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00032fe8 @ 0x00032fe8
 * public-name: start_aging_mode_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   start_aging_mode_thread                  <= FUN_00032fe8 @ 0x00032fe8
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 * address symbols (name @ address):
 *   rodata_32421                             @ 0x00032421
 *   rodata_a757f                             @ 0x000a757f   [INLINED -- G6 literal batch]
 *   rodata_a75c2                             @ 0x000a75c2   [INLINED -- G6 literal batch]
 *   g_aging_mode_thread                      @ 0x20004870
 *   g_aging_mode_thread_started_flag         @ 0x20019ef1
 *   g_aging_mode_thread_stack                @ 0x20027a68
 */
/* Reconstructed FUN_00032fe8 @ 0x32fe8  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_thread_create(void*, void*, unsigned int, void*, int, int, int, unsigned int, int);

void start_aging_mode_thread(void)
{
  volatile unsigned char *pcVar1 = (volatile unsigned char*)((unsigned long)&g_aging_mode_thread_started_flag) /*=0x20019ef1*/;
  int iVar2;

  if (*pcVar1 != 0) {
    log_message((void*)((unsigned long)"[%s-%d], thread has started !\n") /*=0xa757f*/, (void*)((unsigned long)"start_aging_mode_thread") /*=0xa75c2*/, 0xab8);
    return;
  }
  iVar2 = z_impl_k_thread_create((void*)((unsigned long)&g_aging_mode_thread) /*=0x20004870*/, (void*)((unsigned long)&g_aging_mode_thread_stack) /*=0x20027a68*/, 0xc00, (void*)((unsigned long)&rodata_32421) /*=0x32421*/, 0,0,0,0xfffffff4,0);
  if (iVar2 == 0) {
    *pcVar1 = 1;
  }
  return;
}
