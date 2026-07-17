#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00052b48 @ 0x00052b48
 * public-name: FUN_00052b48
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_200028b8                               @ 0x200028b8
 */
/* Reconstructed FUN_00052b48 @ 0x52b48  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_0005ad38(void *service);

unsigned int FUN_00052b48(void)
{
    return FUN_0005ad38((void *)((unsigned long)&g_200028b8) /*=0x200028b8*/);
}
