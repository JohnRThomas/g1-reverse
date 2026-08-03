#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010344a8 @ 0x010344a8
 * public-name: FUN_010344a8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103e6e2                           @ 0x0103e6e2
 */
/* net-core FUN_010344a8 @ 0x10344a8  (parity 300 trials PROVEN) */

unsigned int FUN_010344a8(unsigned int param_1)
{
    volatile unsigned char * const p = (volatile unsigned char * const)((unsigned long)&rodata_103e6e2) /*=0x103e6e2*/;
    unsigned int r3 = p[param_1 >> 5];
    return ((param_1 & 0x1f) + r3) & 0xff;
}
