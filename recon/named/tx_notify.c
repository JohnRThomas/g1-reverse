/* readable reconstruction; identity: FUN_00056020 @ 0x00056020
 * public-name: tx_notify
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_bt_conn_tx_pending_cnt                 @ 0x20003a60
 */
/* Reconstructed tx_notify @ 0x56020  (CFG-directed candidate) */
/* Owner: NCS 2.5.1 Bluetooth host conn.c; raw backmap FUN_00056020@0x00056020. */
#include <stdint.h>
typedef void (*bt_conn_tx_callback)(void *connection, void *user_data, int32_t error);
extern void k_fifo_put(void *fifo, void *item); /* FUN_00086502 */
void tx_notify(void *connection_arg)
{
    uint8_t *connection = (uint8_t *)connection_arg;
    for (;;) {
        uint8_t *tx = *(uint8_t **)(connection + 0x20u);
        if (tx == 0) {
            return;
        }
        uint8_t *next = *(uint8_t **)tx;
        if (tx == *(uint8_t **)(connection + 0x24u)) {
            *(uint8_t **)(connection + 0x24u) = next;
        }
        *(uint8_t **)(connection + 0x20u) = next;

        bt_conn_tx_callback callback = *(bt_conn_tx_callback *)(tx + 4u);
        void *user_data = *(void **)(tx + 8u);
        volatile uint32_t *tx_words = (volatile uint32_t *)tx;
        tx_words[1] = 0u;
        tx_words[2] = 0u;
        tx_words[3] = 0u;
        k_fifo_put((void *)0x20003a60u, tx);
        callback(connection, user_data, 0);
    }
}
