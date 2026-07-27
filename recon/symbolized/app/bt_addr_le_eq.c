#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080fa4 @ 0x00080fa4
 * public-name: bt_addr_le_eq
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 */
/* Reconstructed bt_addr_le_eq @ 0x00080fa4 (FUN_00080fa4; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: include/zephyr/bluetooth/addr.h. */
#include <stdbool.h>
#include <stdint.h>
extern int memcmp(const void *, const void *, uint32_t);
int bt_addr_le_eq(int a, int b) {
    return memcmp(a, b, 7u) == 0;
}
