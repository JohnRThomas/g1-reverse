/* readable reconstruction; identity: FUN_00082c9c @ 0x00082c9c
 * public-name: bt_gatt_foreach_attr_0
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed bt_gatt_foreach_attr_0 @ 0x00082c9c from Zephyr gatt.h.
 * Raw backmap: FUN_00082c9c@0x00082c9c. */

#include <stdint.h>
typedef uint8_t (*bt_gatt_attr_func_t)(const void *, void *);
extern void bt_gatt_foreach_attr_type(uint16_t start, uint16_t end,
                                      const void *uuid, const void *data,
                                      uint16_t matches,
                                      bt_gatt_attr_func_t callback,
                                      void *user_data);
void bt_gatt_foreach_attr_0(unsigned short start, unsigned short end, void*callback, void*user_data) {
    bt_gatt_foreach_attr_type(start, end, 0, 0, 0, callback, user_data);
}
