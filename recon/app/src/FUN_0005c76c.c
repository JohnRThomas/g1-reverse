/* Reconstructed FUN_0005c76c @ 0x0005c76c (bt_gatt_att_max_mtu_changed).
 * Raw/address backmap: FUN_0005c76c @ 0x0005c76c, extent 0x00000024.
 */
#include <stdint.h>
struct gatt_callback_recovered {
    void (*att_mtu_updated)(void *, uint16_t, uint16_t);
    struct gatt_callback_recovered *next;
};
void FUN_0005c76c(void *connection, uint16_t tx_mtu, uint16_t rx_mtu,
                  uint32_t unused)
{
    (void)unused;
    struct gatt_callback_recovered *callback =
        *(struct gatt_callback_recovered **)0x2000af10U;
    while (callback != 0) {
        if (callback->att_mtu_updated != 0)
            callback->att_mtu_updated(connection, tx_mtu, rx_mtu);
        callback = callback->next;
    }
}
