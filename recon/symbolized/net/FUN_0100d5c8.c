#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100d5c8 @ 0x0100d5c8
 * public-name: FUN_0100d5c8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_timing_defaults_apply         <= FUN_0101e1e4 @ 0x0101e1e4
 */
/* net-core FUN_0100d5c8 @ 0x100d5c8  (parity 300 trials PROVEN) */

extern void controller_timing_defaults_apply(int,int);
void FUN_0100d5c8(int param_1, int param_2) {
    *(volatile unsigned char *)(param_1 + 0x72) = (unsigned char)param_2;
    controller_timing_defaults_apply(param_1, param_2);
}
