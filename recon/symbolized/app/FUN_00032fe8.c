#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00032fe8 @ 0x00032fe8
 * public-name: FUN_00032fe8
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_32421                             @ 0x00032421
 *   rodata_a757f                             @ 0x000a757f
 *   rodata_a75c2                             @ 0x000a75c2
 *   g_aging_mode_thread                      @ 0x20004870
 *   g_aging_mode_thread_started_flag         @ 0x20019ef1
 *   g_aging_mode_thread_stack                @ 0x20027a68
 */
/* Reconstructed FUN_00032fe8 @ 0x32fe8  (parity: 300/300 trials, PROVEN) */

extern void log_message(void*, void*, unsigned int);
extern int FUN_00071eac(void*, void*, unsigned int, void*, int, int, int, unsigned int, int);

void FUN_00032fe8(void)
{
  volatile unsigned char *pcVar1 = (volatile unsigned char*)((unsigned long)&g_aging_mode_thread_started_flag) /*=0x20019ef1*/;
  int iVar2;

  if (*pcVar1 != 0) {
    log_message((void*)((unsigned long)&rodata_a757f) /*=0xa757f*/, (void*)((unsigned long)&rodata_a75c2) /*=0xa75c2*/, 0xab8);
    return;
  }
  iVar2 = FUN_00071eac((void*)((unsigned long)&g_aging_mode_thread) /*=0x20004870*/, (void*)((unsigned long)&g_aging_mode_thread_stack) /*=0x20027a68*/, 0xc00, (void*)((unsigned long)&rodata_32421) /*=0x32421*/, 0,0,0,0xfffffff4,0);
  if (iVar2 == 0) {
    *pcVar1 = 1;
  }
  return;
}
