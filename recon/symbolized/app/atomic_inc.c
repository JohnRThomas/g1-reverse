#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007ee2c @ 0x0007ee2c
 * public-name: atomic_inc
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed atomic_inc @ 0x0007ee2c.
 * Raw/address back-map: FUN_0007ee2c / 0x0007ee2c.
 */
#include <stdint.h>

unsigned long atomic_inc(volatile unsigned long*target) {
    return __atomic_fetch_add(target, 1, __ATOMIC_SEQ_CST);
}
