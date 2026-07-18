#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000564cc @ 0x000564cc
 * public-name: bt_conn_send_cb
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_send_cb                          <= FUN_000564cc @ 0x000564cc
 *   net_buf_put                              <= FUN_0005f200 @ 0x0005f200
 *   k_current_get                            <= FUN_000748ac @ 0x000748ac
 *   net_pkt_skip                             <= FUN_00086502 @ 0x00086502
 * address symbols (name @ address):
 *   log_module_bt_conn                       @ 0x00088108
 *   rodata_f3bad                             @ 0x000f3bad
 *   rodata_f3bd2                             @ 0x000f3bd2
 *   rodata_f3be1                             @ 0x000f3be1
 *   g_bt_conn_tx_pending_cnt                 @ 0x20003a60
 *   g_audio_module_spinlock                  @ 0x200068d0
 */
/* Reconstructed FUN_000564cc @ 0x000564cc (bt_conn_send_cb).
 * Raw/address backmap: FUN_000564cc @ 0x000564cc, extent 0x000000de.
 */
#include <stdint.h>

extern void FUN_000813ca(uint32_t, uint32_t, const void *);
extern void *k_current_get(void);                 /* k_current_get */
extern void *FUN_000727ac(void *, uint32_t, uint32_t, uint32_t); /* k_fifo_get */
extern void net_pkt_skip(void *, void *);        /* k_fifo_put */
extern void net_buf_put(void *, void *);        /* net_buf_put */

struct bt_conn_tx_recovered {
    uint32_t node;
    void (*callback)(void *, void *, uint8_t);
    void *user_data;
    uint32_t pending_no_callback;
};

int bt_conn_send_cb(uint8_t *connection, uint8_t *buffer,
                 void (*callback)(void *, void *, uint8_t), void *user_data)
{
    if (buffer[0x0b] < 8U) {
        uint32_t package[3] = { 4U, ((unsigned long)&rodata_f3bad) /*=0xf3bad*/, buffer[0x0b] };
        FUN_000813ca(((unsigned long)&log_module_bt_conn) /*=0x88108*/, 0x2040U, package);
        return -22;
    }
    if (connection[0x0d] != 7U) {
        uint32_t package[2] = { 2U, ((unsigned long)&rodata_f3bd2) /*=0xf3bd2*/ };
        FUN_000813ca(((unsigned long)&log_module_bt_conn) /*=0x88108*/, 0x1040U, package);
        return -128;
    }

    struct bt_conn_tx_recovered *tx = 0;
    if (callback != 0) {
        void *current = k_current_get();
        volatile uint32_t *const system_workqueue_thread =
            (volatile uint32_t *)((unsigned long)&g_bt_conn_tx_pending_cnt) /*=0x20003a60*/;
        uint32_t timeout = current == (void *)*system_workqueue_thread ? 0U : UINT32_MAX;
        tx = FUN_000727ac((void *)((unsigned long)&g_audio_module_spinlock) /*=0x200068d0*/, 0U, timeout, timeout);
        if (tx == 0)
            return -105;
        if (connection[0x0d] != 7U) {
            uint32_t package[2] = { 2U, ((unsigned long)&rodata_f3be1) /*=0xf3be1*/ };
            FUN_000813ca(((unsigned long)&log_module_bt_conn) /*=0x88108*/, 0x1080U, package);
            tx->callback = 0;
            tx->user_data = 0;
            tx->pending_no_callback = 0;
            net_pkt_skip((void *)((unsigned long)&g_bt_conn_tx_pending_cnt) /*=0x20003a60*/, tx);
            return -128;
        }
        tx->callback = callback;
        tx->user_data = user_data;
        tx->pending_no_callback = 0;
    }

    *(struct bt_conn_tx_recovered **)(buffer + 0x18) = tx;
    buffer[0x1c] = 0;
    net_buf_put(connection + 0x38, buffer);
    return 0;
}
