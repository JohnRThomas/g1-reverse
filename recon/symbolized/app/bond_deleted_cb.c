#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_000183ac @ 0x000183ac
 * public-name: bond_deleted_cb
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   format_bt_addr_str                       <= FUN_00018334 @ 0x00018334
 *   bond_deleted_cb                          <= FUN_000183ac @ 0x000183ac
 * address symbols (name @ address):
 *   rodata_9a458                             @ 0x0009a458   [INLINED -- G6 literal batch]
 *   g_ancs_active_conn                       @ 0x20006ab8
 *   g_bonded_count                           @ 0x20007514
 */
/* Reconstructed FUN_000183ac @ 0x183ac  (parity: 300/300 trials, PROVEN) */

extern void format_bt_addr_str(int, int);
void bond_deleted_cb(int param_1, int param_2)
{
    char auStack_28[32];
    format_bt_addr_str(param_2, (int)auStack_28);
    log_message(((unsigned long)"bond_deleted conn: %s\n") /*=0x9a458*/, (int)auStack_28);
    (*(volatile int*)((unsigned long)&g_bonded_count) /*=0x20007514*/)--;
    *(volatile char*)(*(volatile int*)((unsigned long)&g_ancs_active_conn) /*=0x20006ab8*/ + 0x367) = 0;
}
