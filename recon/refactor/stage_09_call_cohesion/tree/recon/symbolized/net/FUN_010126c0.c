#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010126c0 @ 0x010126c0
 * public-name: FUN_010126c0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010126c0 @ 0x10126c0  (parity 300 trials PROVEN) */

unsigned int FUN_010126c0(int param_1) {
    return ((unsigned int)*(unsigned short *)(param_1 + 2) << 0x1c) >> 0x1f;
}
