#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0006b364 @ 0x0006b364
 * public-name: lc3_ltpf_disable
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_ltpf_disable                         <= FUN_0006b364 @ 0x0006b364
 */
/* Reconstructed FUN_0006b364 @ 0x6b364  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void lc3_ltpf_disable(volatile uint8_t *param_1) {
    *param_1 = 0;
}
