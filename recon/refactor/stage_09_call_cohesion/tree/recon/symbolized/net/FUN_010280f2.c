#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010280f2 @ 0x010280f2
 * public-name: FUN_010280f2
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010280f2 @ 0x10280f2  (CFG-directed candidate) */
#include <stdint.h>
#include <stdbool.h>
bool FUN_010280f2(uint32_t bits)
{
    bits &= bits << 1;
    bits &= bits << 1;
    bits &= bits << 1;
    bits &= bits << 1;
    bits &= bits << 1;
    return (bits & (bits << 1)) == 0u;
}
