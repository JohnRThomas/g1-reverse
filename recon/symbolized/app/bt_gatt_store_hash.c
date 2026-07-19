#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005a250 @ 0x0005a250
 * public-name: bt_gatt_store_hash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   store_gatt_db_hash_setting               <= FUN_0005307c @ 0x0005307c
 *   bt_gatt_store_hash                       <= FUN_0005a250 @ 0x0005a250
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f4849                             @ 0x000f4849
 *   g_bt_gatt_db_hash                        @ 0x20006380
 */
/* Reconstructed FUN_0005a250 @ 0x5a250  (parity: 300/300 trials, PROVEN) */

extern int store_gatt_db_hash_setting(unsigned int a, unsigned int b);
extern void log_msg_create_3arg(unsigned int a, unsigned int b, void *c);

void bt_gatt_store_hash(void)
{
    struct { unsigned int f0; unsigned int f1; unsigned int f2; } s;
    int r;
    r = store_gatt_db_hash_setting(((unsigned long)&g_bt_gatt_db_hash) /*=0x20006380*/, 0x10);
    if (r != 0) {
        s.f0 = 3;
        s.f1 = ((unsigned long)&rodata_f4849) /*=0xf4849*/;
        s.f2 = r;
        log_msg_create_3arg(((unsigned long)&rodata_88128) /*=0x88128*/, 0x1840, &s);
    }
}
