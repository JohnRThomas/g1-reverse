#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000531d8 @ 0x000531d8
 * public-name: FUN_000531d8
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_sys_work_q                             @ 0x20005d38
 */
/* Reconstructed FUN_000531d8 @ 0x531d8  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00073424(unsigned int a, void *b);
unsigned int FUN_000531d8(void *param_1)
{
    return FUN_00073424(((unsigned long)&g_sys_work_q) /*=0x20005d38*/, param_1);
}
