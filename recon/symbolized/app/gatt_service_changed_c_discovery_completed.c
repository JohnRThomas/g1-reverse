#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007f8dc @ 0x0007f8dc
 * public-name: gatt_service_changed_c_discovery_completed
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_dm_attr_service_val              <= FUN_0007f460 @ 0x0007f460
 *   bt_gatt_dm_conn_get                      <= FUN_0007f4c8 @ 0x0007f4c8
 *   bt_gatt_dm_service_get                   <= FUN_0007f4d2 @ 0x0007f4d2
 *   gatt_service_changed_c_discovery_completed <= FUN_0007f8dc @ 0x0007f8dc
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 */
/* Reconstructed FUN_0007f8dc @ 0x7f8dc  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004ed3c(unsigned a, void*b);
extern unsigned bt_gatt_dm_attr_service_val(void);
extern unsigned bt_gatt_dm_conn_get(unsigned a);
extern void bt_gatt_dm_service_get(void);
extern int FUN_0007f570(unsigned a, int b, void*c);
extern int bt_uuid_cmp(unsigned a, void*b);
unsigned gatt_service_changed_c_discovery_completed(unsigned param_1, unsigned *param_2, unsigned param_3, unsigned param_4){
    unsigned char local_24[4], local_20[4], local_1c[4];
    volatile unsigned *p2 = (volatile unsigned*)param_2;
    bt_gatt_dm_service_get();
    unsigned *puVar2 = (unsigned*)bt_gatt_dm_attr_service_val();
    unsigned pv = *(volatile unsigned*)puVar2;
    local_1c[0] = 0;
    *(volatile unsigned short*)(local_1c + 2) = 0x1801;
    int iVar3 = bt_uuid_cmp(pv, local_1c);
    if (iVar3 != 0) return 0xffffff7au;
    p2[0] = 0; p2[1] = 0; p2[10] = 0;
    local_24[0] = 0;
    *(volatile unsigned short*)(local_24 + 2) = 0x2a05;
    int h = FUN_0004ed3c(param_1, local_24);
    if (h == 0) return 0xffffffeau;
    local_20[0] = 0;
    *(volatile unsigned short*)(local_20 + 2) = 0x2a05;
    int iVar4 = FUN_0007f570(param_1, h, local_20);
    if (iVar4 == 0) return 0xffffffeau;
    *(volatile unsigned short*)((char*)param_2 + 4) = *(volatile unsigned short*)(iVar4 + 4);
    local_1c[0] = 0;
    *(volatile unsigned short*)(local_1c + 2) = 0x2902;
    int iVar3b = FUN_0007f570(param_1, h, local_1c);
    if (iVar3b == 0) return 0xffffffeau;
    *(volatile unsigned short*)((char*)param_2 + 6) = *(volatile unsigned short*)(iVar3b + 4);
    unsigned uVar5 = bt_gatt_dm_conn_get(param_1);
    p2[0] = uVar5;
    return 0;
}
