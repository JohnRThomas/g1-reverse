#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100a5b4 @ 0x0100a5b4
 * public-name: FUN_0100a5b4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_sdc_last_cfg_param3                    @ 0x21000bc9
 */
/* net-core FUN_0100a5b4 @ 0x100a5b4  (parity 300 trials PROVEN) */

unsigned char FUN_0100a5b4(void)
{
    volatile unsigned char * const p = (volatile unsigned char * const)((unsigned long)&g_sdc_last_cfg_param3) /*=0x21000bc9*/;
    return *p;
}
