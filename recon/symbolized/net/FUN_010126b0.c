#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010126b0 @ 0x010126b0
 * public-name: FUN_010126b0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010126b0 @ 0x10126b0  (parity 300 trials PROVEN) */

unsigned short FUN_010126b0(int param_1) {
    return *(unsigned short *)(param_1 + 2) & 1;
}
