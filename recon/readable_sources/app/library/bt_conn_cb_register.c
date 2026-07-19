#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00056e24 @ 0x00056e24
 * public-name: bt_conn_cb_register
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_cb_register                      <= FUN_00056e24 @ 0x00056e24
 * address symbols (name @ address):
 *   g_ble_conn_cb_list_head                  @ 0x2000ad1c
 */
/* Reconstructed FUN_00056e24 @ 0x00056e24 (bt_conn_cb_register).
 * Exact configured Zephyr conn.c owner; extent 0x0a.
 */
#include <stdint.h>
void bt_conn_cb_register(uint8_t *callback)
{
    uintptr_t previous = *(volatile uintptr_t *)((unsigned long)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/;
    *(volatile uintptr_t *)((unsigned long)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/ = (uintptr_t)callback;
    *(uintptr_t *)(callback + 0x20) = previous;
}
