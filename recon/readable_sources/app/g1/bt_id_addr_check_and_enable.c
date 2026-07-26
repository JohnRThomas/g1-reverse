#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000549ec @ 0x000549ec
 * public-name: bt_id_addr_check_and_enable
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_dev_show_info                         <= FUN_000548b8 @ 0x000548b8
 *   bt_id_addr_check_and_enable              <= FUN_000549ec @ 0x000549ec
 *   atomic_or                                <= FUN_00080e6a @ 0x00080e6a
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f322e                             @ 0x000f322e   [INLINED -- G6 literal batch]
 *   g_ble_dev_state                          @ 0x20002000
 */
/* Reconstructed FUN_000549ec @ 0x549ec  (parity: 300/300 trials, PROVEN) */

extern void bt_log_forward_3arg(unsigned int a, unsigned int b, void *c);
extern void atomic_or(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void bt_dev_show_info(void);

unsigned int bt_id_addr_check_and_enable(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile unsigned char *base = (volatile unsigned char*)((unsigned long)&g_ble_dev_state) /*=0x20002000*/;
    unsigned char flag = base[7];
    if (flag == 0) {
        struct { unsigned int f0; unsigned int f1; } s;
        s.f0 = 2;
        s.f1 = ((unsigned long)"No ID address. App must call settings_load()") /*=0xf322e*/;
        bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x10c0, &s);
    } else {
        atomic_or(((unsigned long)&g_ble_dev_state) /*=0x20002000*/ + 0xd4, 8, param_3, flag);
        bt_dev_show_info();
    }
    return 0;
}
