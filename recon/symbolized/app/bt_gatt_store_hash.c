#include "g1_app_symbols.h"
/* named: bt_gatt_store_hash */
/* globals referenced:
//   0x20006380  g_bt_gatt_db_hash            
*/
/* Reconstructed bt_gatt_store_hash @ 0x5a250  (parity: 300/300 trials, PROVEN) */

extern int FUN_0005307c(unsigned int a, unsigned int b);
extern void FUN_00082a42(unsigned int a, unsigned int b, void *c);

void bt_gatt_store_hash(void)
{
    struct { unsigned int f0; unsigned int f1; unsigned int f2; } s;
    int r;
    r = FUN_0005307c(((uintptr_t)&g_bt_gatt_db_hash) /*=0x20006380*/, 0x10);
    if (r != 0) {
        s.f0 = 3;
        s.f1 = "Failed to save Database Hash (err %d)" /*=0xf4849*/;
        s.f2 = r;
        FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1840, &s);
    }
}

