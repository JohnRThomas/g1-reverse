#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00073418 @ 0x00073418
 * public-name: FUN_00073418
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_audio_module_spinlock                  @ 0x200068d0
 */
/* Reconstructed FUN_00073418 @ 0x73418  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007332c(unsigned int, unsigned int, unsigned int, unsigned int);
void FUN_00073418(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    FUN_0007332c(((unsigned long)&g_audio_module_spinlock) /*=0x200068d0*/, param_1, param_3, param_4);
}
