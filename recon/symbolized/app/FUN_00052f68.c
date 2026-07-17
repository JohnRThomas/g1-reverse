#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00052f68 @ 0x00052f68
 * public-name: FUN_00052f68
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_store                        <= FUN_00052f18 @ 0x00052f18
 * address symbols (name @ address):
 *   rodata_88178                             @ 0x00088178
 *   rodata_9a1dd                             @ 0x0009a1dd
 *   rodata_f2c71                             @ 0x000f2c71
 *   g_ble_dev_state                          @ 0x20002000
 */
/* Reconstructed FUN_00052f68 @ 0x52f68  (parity: 300/300 trials, PROVEN) */

extern int bt_settings_store(int,int);
extern void FUN_0004d944(int,int,void*,int);

void FUN_00052f68(void)
{
    unsigned char b = *(volatile unsigned char*)(((unsigned long)&g_ble_dev_state) /*=0x20002000*/ + 7);
    int local_18 = (int)(unsigned)b * 7;
    local_18 = bt_settings_store(((unsigned long)&rodata_9a1dd) /*=0x9a1dd*/, 0);
    if (local_18 != 0) {
        struct { int f0; int f4; int f8; } s;
        s.f0 = 3;
        s.f4 = ((unsigned long)&rodata_f2c71) /*=0xf2c71*/;
        s.f8 = local_18;
        FUN_0004d944(((unsigned long)&rodata_88178) /*=0x88178*/, 0x1840, &s, 0);
    }
}
