#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_k_work_delayable__param_0181           [param_0181; library]
 * Raw function identity: 0x00073418.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00073418 @ 0x00073418
 * public-name: k_work_schedule
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_schedule_for_queue                <= FUN_0007332c @ 0x0007332c
 *   k_work_schedule                          <= FUN_00073418 @ 0x00073418
 * address symbols (name @ address):
 *   g_audio_module_spinlock                  @ 0x200068d0
 */
/* Reconstructed FUN_00073418 @ 0x73418  (parity: 300/300 trials, PROVEN) */

extern void k_work_schedule_for_queue(unsigned int, unsigned int, unsigned int, unsigned int);
void k_work_schedule(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    k_work_schedule_for_queue(((unsigned long)&g_audio_module_spinlock) /*=0x200068d0*/, param_1, param_3, param_4);
}
