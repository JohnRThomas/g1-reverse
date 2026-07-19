/* readable reconstruction; identity: FUN_0005c9a4 @ 0x0005c9a4
 * public-name: bt_gatt_disconnected
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_cf_cfg                              <= FUN_00059c04 @ 0x00059c04
 *   gatt_find_conn_in_known_table            <= FUN_00059c70 @ 0x00059c70
 *   gatt_cf_cfg_clear                        <= FUN_0005a39c @ 0x0005a39c
 *   bt_gatt_disconnected                     <= FUN_0005c9a4 @ 0x0005c9a4
 *   bt_addr_le_is_bonded                     <= FUN_00080f92 @ 0x00080f92
 *   atomic_and_4                             <= FUN_000826f6 @ 0x000826f6
 *   read_struct_first_word                   <= FUN_0008270c @ 0x0008270c
 *   bt_addr_le_copy_828da                    <= FUN_000828da @ 0x000828da
 *   list_unlink_and_release                  <= FUN_000828e8 @ 0x000828e8
 *   bt_gatt_foreach_attr_0                   <= FUN_00082c9c @ 0x00082c9c
 *   gatt_store_ccc_cf                        <= FUN_00082f3a @ 0x00082f3a
 * address symbols (name @ address):
 *   rodata_5a2d5                             @ 0x0005a2d5
 *   ADDR_gatt_remove_peer_from_attr_THUMB    @ 0x0005a3c5
 */
/* Reconstructed FUN_0005c9a4 @ 0x0005c9a4 (bt_gatt_disconnected).
 * Raw/address backmap: FUN_0005c9a4 @ 0x0005c9a4, extent 0x000000f6.
 */
#include <stdint.h>
extern void bt_gatt_foreach_attr_0(uint16_t, uint16_t, void *, void *); /* foreach attr */
extern void gatt_store_ccc_cf(uint8_t, const void *); /* gatt_store_ccc_cf */
extern int bt_addr_le_is_bonded(uint8_t, const void *); /* bt_addr_le_is_bonded */
extern void *gatt_find_conn_in_known_table(void *); /* gatt_sub_find */
extern uint32_t atomic_and_4(volatile uint32_t *, uint32_t); /* atomic_and */
extern uint32_t read_struct_first_word(volatile uint32_t *); /* atomic_get */
extern void list_unlink_and_release(void *, void *, void *, void *); /* gatt_sub_remove */
extern void bt_addr_le_copy_828da(void *, const void *); /* bt_addr_le_copy */
extern void *find_cf_cfg(void *); /* find_cf_cfg */
extern void gatt_cf_cfg_clear(void *); /* reset cf cfg */

struct gatt_subscription_recovered {
    uint8_t identity;
    uint8_t peer[7];
    uintptr_t head_node_link;
    uintptr_t tail_link;
};
struct gatt_sub_node_recovered {
    uint8_t opaque[0x10];
    uint16_t value;
    uint16_t reserved;
    volatile uint32_t flags;
    uintptr_t next_node_link;
};

void bt_gatt_disconnected(uint8_t *connection)
{
    const void *peer = connection + 0x90;
    bt_gatt_foreach_attr_0(1U, 0xffffU, (void *)0x0005a3c5U, connection);
    gatt_store_ccc_cf(connection[8], peer);

    int bonded = bt_addr_le_is_bonded(connection[8], peer);
    if (bonded) {
        struct { const void *address; uint8_t identity; } address_with_id = {
            peer, connection[8]
        };
        bt_gatt_foreach_attr_0(1U, 0xffffU, (void *)0x0005a2d5U,
                     &address_with_id);
    }

    struct gatt_subscription_recovered *subscription = gatt_find_conn_in_known_table(connection);
    if (subscription != 0) {
        uintptr_t previous_link = 0;
        uintptr_t link = subscription->head_node_link;
        while (link != 0) {
            struct gatt_sub_node_recovered *node =
                (struct gatt_sub_node_recovered *)(link - 0x18U);
            uintptr_t next_link = node->next_node_link;
            (void)atomic_and_4(&node->flags, ~8U);
            if (!bonded || (read_struct_first_word(&node->flags) & 1U) != 0U) {
                node->value = 0;
                list_unlink_and_release(connection, subscription,
                             (void *)previous_link, node);
            } else {
                if (subscription->peer[0] == 0U)
                    bt_addr_le_copy_828da(subscription->peer, peer);
                previous_link = (uintptr_t)&node->next_node_link;
            }
            link = next_link;
        }
    }

    uint8_t *cf = find_cf_cfg(connection);
    if (cf == 0)
        return;
    if (!bt_addr_le_is_bonded(connection[8], peer))
        gatt_cf_cfg_clear(cf);
    else
        bt_addr_le_copy_828da(cf + 1, peer);
}
