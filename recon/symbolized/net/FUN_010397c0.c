#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010397c0 @ 0x010397c0
 * public-name: FUN_010397c0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010397c0 @ 0x10397c0  (parity 300 trials PROVEN) */

unsigned int FUN_010397c0(unsigned int param_1, int param_2)
{
    int iVar1;
    if (param_1 < 0x8000) {
        iVar1 = 4;
    } else {
        iVar1 = 8;
    }
    return (unsigned int)(param_2 + 7 + iVar1) >> 3;
}
