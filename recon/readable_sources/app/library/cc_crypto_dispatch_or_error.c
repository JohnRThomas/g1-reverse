#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   0x0007a3c8       => struct g1_layout_cc_crypto_workspace__global_1452       [global_1452; G1-original]
 * Raw function identity: 0x0007a2b8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007a2b8 @ 0x0007a2b8
 * public-name: cc_crypto_dispatch_or_error
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cc_crypto_dispatch_or_error              <= FUN_0007a2b8 @ 0x0007a2b8
 */
/* Reconstructed FUN_0007a2b8 @ 0x7a2b8  (parity: 300/300 trials, PROVEN) */

extern unsigned int firmware_function_0007a3a4(unsigned int);

unsigned int cc_crypto_dispatch_or_error(unsigned int param_1)
{
    if (param_1 == 0) {
        return 0xf50000U;
    }
    return firmware_function_0007a3a4(param_1);
}
