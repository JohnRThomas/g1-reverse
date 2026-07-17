#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083090 @ 0x00083090
 * public-name: atomic_set_bit
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed atomic_set_bit @ 0x83090  (CFG-directed candidate) */
typedef long atomic_t;
void atomic_set_bit(atomic_t *target, int bit)
{
    (void)__atomic_fetch_or(target, (atomic_t)1 << bit, __ATOMIC_SEQ_CST);
}
