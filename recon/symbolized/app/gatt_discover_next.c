#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00082d2e @ 0x00082d2e
 * public-name: gatt_discover_next
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_discover                         <= FUN_0005b9cc @ 0x0005b9cc
 */
/* Reconstructed gatt_discover_next @ 0x00082d2e (FUN_00082d2e; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: subsys/bluetooth/host/gatt.c. */
#include <stdint.h>
typedef void (*discover_cb_t)(void *, const void *, void *);
extern int bt_gatt_discover(int, int *);
void gatt_discover_next(void *conn, uint16_t last_handle, void *opaque)
{
    volatile uint8_t *params = (volatile uint8_t *)opaque;
    if (last_handle != 0) {
        if (last_handle == UINT16_MAX) {
            *(volatile uint16_t *)(params + 8) = UINT16_MAX;
        } else {
            uint16_t next = (uint16_t)(last_handle + 1u);
            *(volatile uint16_t *)(params + 8) = next;
            if (next <= *(volatile uint16_t *)(params + 14)) {
                if (bt_gatt_discover(conn, opaque) == 0) return;
            }
        }
    } else if (bt_gatt_discover(conn, opaque) == 0) {
        return;
    }
    ((discover_cb_t)*(volatile uintptr_t *)(params + 4))(conn, 0, opaque);
}
