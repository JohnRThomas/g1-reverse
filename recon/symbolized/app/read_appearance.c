#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00082a1a @ 0x00082a1a
 * public-name: read_appearance
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_appearance_value                     <= FUN_00080f8c @ 0x00080f8c
 *   bt_gatt_attr_read                        <= FUN_00082932 @ 0x00082932
 *   read_appearance                          <= FUN_00082a1a @ 0x00082a1a
 */
/* Reconstructed FUN_00082a1a @ 0x82a1a  (parity: 300/300 trials, PROVEN) */

extern unsigned int ble_appearance_value(void);
extern void bt_gatt_attr_read(unsigned int a, unsigned int b, unsigned int c, void *d, unsigned int e);

void read_appearance(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4, unsigned short param_5)
{
    unsigned short local_12[3];
    local_12[0] = (unsigned short)ble_appearance_value();
    bt_gatt_attr_read(param_3, param_4, param_5, local_12, 2);
}
