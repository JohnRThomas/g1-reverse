#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00053380 @ 0x00053380
 * public-name: unpair
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_bt_conn_auth_info_cb_list              @ 0x2000ad20
 */
/* unpair @ 0x00053380; raw FUN_00053380 */
#include <stdint.h>

struct auth_node {
    struct auth_node *next;
};

struct auth_listener {
    uint8_t reserved[8];
    void (*bond_deleted)(uint8_t, const void *);
    struct auth_node node;
};

extern uint8_t *bt_conn_lookup_addr_le(uint8_t, const void *); /* FUN_00056e74 */
extern int bt_conn_disconnect(void *, uint8_t); /* FUN_00056a68 */
extern void ble_conn_unref(int); /* FUN_000566a4 */
extern void *bt_keys_find_addr(uint8_t, const void *); /* FUN_0005e938 */
extern void bt_keys_clear(void *); /* FUN_0005ea18 */
extern void bt_gatt_clear(uint8_t, const void *); /* FUN_0005c8d8 */

void unpair(uint8_t identity, const void *address)
{
    void *keys = 0;
    uint8_t *connection = bt_conn_lookup_addr_le(identity, address);

    if (connection) {
        if (connection[2] == 1) {
            keys = *(void **)(connection + 0xc0);
            *(void **)(connection + 0xc0) = 0;
        }
        bt_conn_disconnect(connection, 0x13);
        ble_conn_unref(connection);
    }
    if (!keys) {
        keys = bt_keys_find_addr(identity, address);
    }
    if (keys) {
        bt_keys_clear(keys);
    }

    bt_gatt_clear(identity, address);

    struct auth_node *node = *(struct auth_node **)((unsigned long)&g_bt_conn_auth_info_cb_list) /*=0x2000ad20*/;
    while (node) {
        struct auth_listener *listener =
            (struct auth_listener *)((uint8_t *)node - 12);
        node = node->next;
        if (listener->bond_deleted) {
            listener->bond_deleted(identity, address);
        }
    }
}
