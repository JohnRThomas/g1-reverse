#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081e14 @ 0x00081e14
 * public-name: atomic_clear_bit_0
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed atomic_clear_bit_0 @ 0x00081e14 (FUN_00081e14; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: include/zephyr/sys/atomic.h. */
#include <stdint.h>
void atomic_clear_bit_0(volatile int32_t *target, int bit)
{ (void)__atomic_fetch_and(target, ~((int32_t)1 << bit), __ATOMIC_SEQ_CST); }
