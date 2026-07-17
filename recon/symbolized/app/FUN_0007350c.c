#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007350c @ 0x0007350c
 * public-name: FUN_0007350c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_reschedule_for_queue              <= FUN_00073424 @ 0x00073424
 * address symbols (name @ address):
 *   g_audio_module_spinlock                  @ 0x200068d0
 */
/* Reconstructed FUN_0007350c @ 0x7350c  (parity: 300/300 trials, PROVEN) */

extern void k_work_reschedule_for_queue(unsigned int, unsigned int, unsigned int, unsigned int);
void FUN_0007350c(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    k_work_reschedule_for_queue(((unsigned long)&g_audio_module_spinlock) /*=0x200068d0*/, param_1, param_3, param_4);
}
