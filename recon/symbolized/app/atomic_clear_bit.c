#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007f5d8 @ 0x0007f5d8
 * public-name: atomic_clear_bit
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed atomic_clear_bit @ 0x0007f5d8 (FUN_0007f5d8; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: include/zephyr/sys/atomic.h. */
#include <stdint.h>
void atomic_clear_bit(volatile int*target, int bit) { (void)__atomic_fetch_and(target, ~((int32_t)1 << bit), __ATOMIC_SEQ_CST); }
