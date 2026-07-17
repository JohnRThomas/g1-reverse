#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000869dc @ 0x000869dc
 * public-name: FUN_000869dc
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_000869dc @ 0x869dc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>

unsigned int FUN_000869dc(double param_1)
{
    uint64_t bits;
    __builtin_memcpy(&bits, &param_1, 8);
    unsigned int hi = (unsigned int)(bits >> 32);
    return ((hi | 0x80000000u) + 0x100000u) >> 0x1f;
}
