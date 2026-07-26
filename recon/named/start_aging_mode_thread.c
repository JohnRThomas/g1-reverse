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
#include "../headers/g1_log.h"
/* Reconstructed FUN_00032fe8 @ 0x32fe8  (parity: 300/300 trials, PROVEN) */

/* CONFIG_TIMEOUT_64BIT: z_impl_k_thread_create's 10th parameter is a
 * 64-bit k_timeout_t delay, AAPCS-placed 8-byte aligned at sp+0x18.
 * The original writes it (strd r,r,[sp,#0x18]); it must be passed. */
extern int z_impl_k_thread_create(void*, void*, unsigned int, void*, int, int, int, unsigned int, int, unsigned long long);

void start_aging_mode_thread(void)
{
  volatile unsigned char *pcVar1 = (volatile unsigned char*)0x20019ef1UL;
  int iVar2;

  if (*pcVar1 != 0) {
    log_message((void*)0xa757fUL, (void*)0xa75c2UL, 0xab8);
    return;
  }
  iVar2 = z_impl_k_thread_create((void*)0x20004870UL, (void*)0x20027a68UL, 0xc00, (void*)0x32421UL, 0,0,0,0xfffffff4,0,0ULL);
  if (iVar2 == 0) {
    *pcVar1 = 1;
  }
  return;
}
