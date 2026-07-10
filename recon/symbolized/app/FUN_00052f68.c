#include "g1_app_symbols.h"
/* named: FUN_00052f68 */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
*/
/* Reconstructed FUN_00052f68 @ 0x52f68  (parity: 300/300 trials, PROVEN) */

extern int bt_settings_store(int,int);
extern void FUN_0004d944(int,int,void*,int);

void FUN_00052f68(void)
{
    unsigned char b = *(volatile unsigned char*)(((uintptr_t)&g_ble_dev_state) /*=0x20002000*/ + 7);
    int local_18 = (int)(unsigned)b * 7;
    local_18 = bt_settings_store("id" /*=0x9a1dd*/, 0);
    if (local_18 != 0) {
        struct { int f0; int f4; int f8; } s;
        s.f0 = 3;
        s.f4 = "Failed to save ID (err %d)" /*=0xf2c71*/;
        s.f8 = local_18;
        FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88178*/, 0x1840, &s, 0);
    }
}

