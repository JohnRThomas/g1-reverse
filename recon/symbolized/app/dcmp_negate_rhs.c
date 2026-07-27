#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0000d588 @ 0x0000d588
 * public-name: dcmp_negate_rhs
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dcmp_negate_rhs                          <= FUN_0000d588 @ 0x0000d588
 *   __aeabi_dadd                             <= FUN_0000d58c @ 0x0000d58c
 */
/* Reconstructed FUN_0000d588 @ 0xd588  (parity: 300/300 trials, PROVEN) */

extern unsigned long long __aeabi_dadd(unsigned int, unsigned int, unsigned int, unsigned int);
long long dcmp_negate_rhs(int param_1, int param_2, int param_3, int param_4) {
    param_4 = param_4 ^ 0x80000000;
    return __aeabi_dadd(param_1, param_2, param_3, param_4);
}
