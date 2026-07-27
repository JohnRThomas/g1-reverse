#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007f460 @ 0x0007f460
 * public-name: bt_gatt_dm_attr_service_val
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_dm_attr_service_val              <= FUN_0007f460 @ 0x0007f460
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 */
/* Reconstructed FUN_0007f460 @ 0x7f460  (parity: 300/300 trials, PROVEN) */

extern int bt_uuid_cmp(int, int);

int bt_gatt_dm_attr_service_val(int *param_1, int param_2, int param_3)
{
    int iVar2;
    unsigned char b0; unsigned short h1;
    struct { unsigned char b0; unsigned char b1; unsigned short h1; } local;
    local.b0 = 0;
    local.h1 = 0x2800;
    iVar2 = bt_uuid_cmp(&local, *param_1);
    if (iVar2 != 0) {
        struct { unsigned char b0; unsigned char b1; unsigned short h1; } local2;
        local2.b0 = 0;
        local2.h1 = 0x2801;
        iVar2 = bt_uuid_cmp(&local2, *param_1);
        if (iVar2 != 0) return 0;
    }
    return *param_1 - 8;
}
