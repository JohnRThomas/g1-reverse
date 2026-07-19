#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00082988 @ 0x00082988
 * public-name: bt_gatt_attr_read_service
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_attr_read                        <= FUN_00082932 @ 0x00082932
 *   bt_gatt_attr_read_service                <= FUN_00082988 @ 0x00082988
 */
/* Reconstructed FUN_00082988 @ 0x82988  (parity: 300/300 trials, PROVEN) */

extern void bt_gatt_attr_read(int a, int b, int c, int d, ...);

void bt_gatt_attr_read_service(void *param_1, char *param_2, int param_3, int param_4, unsigned short param_5)
{
    char *pcVar1;
    pcVar1 = *(char **)(param_2 + 0xc);
    if (*pcVar1 != 0) {
        bt_gatt_attr_read(param_3, param_4, param_5, (int)(pcVar1 + 1));
        return;
    }
    bt_gatt_attr_read(param_3, param_4, param_5, 0, 2, (int)param_2, param_3, 0);
}
