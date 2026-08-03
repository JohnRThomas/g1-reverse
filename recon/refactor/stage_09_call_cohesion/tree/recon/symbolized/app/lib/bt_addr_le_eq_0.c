#include "g1_app_symbols.h"
#include <stddef.h>
/* readable reconstruction; identity: FUN_000826b2 @ 0x000826b2
 * public-name: bt_addr_le_eq_0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 */
/* Reconstructed bt_addr_le_eq_0 @ 0x826b2  (CFG-directed candidate) */
#include <stdbool.h>
#include <stdint.h>
extern int memcmp(const void *, const void *, size_t);
int bt_addr_le_eq_0(void*a, unsigned int b) {
    return memcmp(a, b, 7u) == 0;
}
