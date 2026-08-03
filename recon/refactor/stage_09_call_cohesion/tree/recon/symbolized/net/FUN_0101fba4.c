#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101fba4 @ 0x0101fba4
 * public-name: FUN_0101fba4
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0101fba4 @ 0x101fba4  (parity 300 trials PROVEN) */

unsigned int FUN_0101fba4(void)
{
    volatile unsigned char * const p = (volatile unsigned char * const)G1N_21001498;
    if (p[0x10] == 0) return 0x138;
    return 0x214;
}
