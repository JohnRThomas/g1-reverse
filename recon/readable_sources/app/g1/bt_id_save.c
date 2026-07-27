#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00052f68 @ 0x00052f68
 * public-name: bt_id_save
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   bt_settings_store                        <= FUN_00052f18 @ 0x00052f18
 *   bt_id_save                               <= FUN_00052f68 @ 0x00052f68
 * address symbols (name @ address):
 *   rodata_88178                             @ 0x00088178
 *   rodata_9a1dd                             @ 0x0009a1dd
 *   rodata_f2c71                             @ 0x000f2c71
 *   g_ble_dev_state                          @ 0x20002000
 */
/* Reconstructed FUN_00052f68 @ 0x52f68  (parity: 300/300 trials, PROVEN) */

extern int bt_settings_store(int,int);
extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);

void bt_id_save(void)
{
    unsigned char b = *(volatile unsigned char*)(((unsigned long)&g_ble_dev_state) /*=0x20002000*/ + 7);
    int local_18 = (int)(unsigned)b * 7;
    local_18 = bt_settings_store(((unsigned long)&rodata_9a1dd) /*=0x9a1dd*/, 0);
    if (local_18 != 0) {
        struct { int f0; int f4; int f8; } s;
        s.f0 = 3;
        s.f4 = ((unsigned long)&rodata_f2c71) /*=0xf2c71*/;
        s.f8 = local_18;
        z_log_msg_runtime_create(((unsigned long)&rodata_88178) /*=0x88178*/, 0x1840, &s, 0);
    }
}
