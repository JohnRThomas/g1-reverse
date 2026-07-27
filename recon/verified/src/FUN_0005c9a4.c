/* Reconstructed FUN_0005c9a4 @ 0x0005c9a4 (bt_gatt_disconnected).
 * Raw/address backmap: FUN_0005c9a4 @ 0x0005c9a4, extent 0x000000f6.
 */
#include <stdint.h>
extern void FUN_00082c9c(uint16_t, uint16_t, void *, void *); /* foreach attr */
extern void FUN_00082f3a(uint8_t, const void *); /* gatt_store_ccc_cf */
extern int FUN_00080f92(uint8_t, const void *); /* bt_addr_le_is_bonded */
extern void *FUN_00059c70(void *); /* gatt_sub_find */
extern uint32_t FUN_000826f6(volatile uint32_t *, uint32_t); /* atomic_and */
extern uint32_t FUN_0008270c(volatile uint32_t *); /* atomic_get */
extern void FUN_000828e8(unsigned int, int, unsigned int *, unsigned int *); /* gatt_sub_remove */
extern void FUN_000828da(void *, const void *); /* bt_addr_le_copy */
extern void *FUN_00059c04(void *); /* find_cf_cfg */
extern void FUN_0005a39c(void *); /* reset cf cfg */

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

void FUN_0005c9a4(uint8_t *connection)
{
    const void *peer = connection + 0x90;
    FUN_00082c9c(1U, 0xffffU, (void *)0x0005a3c5U, connection);
    FUN_00082f3a(connection[8], peer);

    int bonded = FUN_00080f92(connection[8], peer);
    if (bonded) {
        struct { const void *address; uint8_t identity; } address_with_id = {
            peer, connection[8]
        };
        FUN_00082c9c(1U, 0xffffU, (void *)0x0005a2d5U,
                     &address_with_id);
    }

    struct gatt_subscription_recovered *subscription = FUN_00059c70(connection);
    if (subscription != 0) {
        uintptr_t previous_link = 0;
        uintptr_t link = subscription->head_node_link;
        while (link != 0) {
            struct gatt_sub_node_recovered *node =
                (struct gatt_sub_node_recovered *)(link - 0x18U);
            uintptr_t next_link = node->next_node_link;
            (void)FUN_000826f6(&node->flags, ~8U);
            if (!bonded || (FUN_0008270c(&node->flags) & 1U) != 0U) {
                node->value = 0;
                FUN_000828e8(connection, subscription,
                             (void *)previous_link, node);
            } else {
                if (subscription->peer[0] == 0U)
                    FUN_000828da(subscription->peer, peer);
                previous_link = (uintptr_t)&node->next_node_link;
            }
            link = next_link;
        }
    }

    uint8_t *cf = FUN_00059c04(connection);
    if (cf == 0)
        return;
    if (!FUN_00080f92(connection[8], peer))
        FUN_0005a39c(cf);
    else
        FUN_000828da(cf + 1, peer);
}
