/* readable reconstruction; identity: FUN_000564cc @ 0x000564cc
 * public-name: bt_conn_send_cb
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_send_cb                          <= FUN_000564cc @ 0x000564cc
 *   net_buf_put                              <= FUN_0005f200 @ 0x0005f200
 *   net_buf_pool_get_727ac                   <= FUN_000727ac @ 0x000727ac
 *   k_current_get                            <= FUN_000748ac @ 0x000748ac
 *   bt_conn_call_4arg_zero                   <= FUN_000813ca @ 0x000813ca
 *   net_pkt_skip                             <= FUN_00086502 @ 0x00086502
 * address symbols (name @ address):
 *   log_module_bt_conn                       @ 0x00088108
 *   rodata_f3bad                             @ 0x000f3bad   [INLINED -- G6 literal batch]
 *   rodata_f3bd2                             @ 0x000f3bd2
 *   rodata_f3be1                             @ 0x000f3be1
 *   g_bt_conn_tx_pending_cnt                 @ 0x20003a60
 *   g_audio_module_spinlock                  @ 0x200068d0
 */
/* Reconstructed FUN_000564cc @ 0x000564cc (bt_conn_send_cb).
 * Raw/address backmap: FUN_000564cc @ 0x000564cc, extent 0x000000de.
 */
#include <stdint.h>

extern int bt_conn_call_4arg_zero(int, int, void*);
extern int k_current_get(void);                 /* k_current_get */
extern unsigned long net_buf_pool_get_727ac(unsigned int*, unsigned int, unsigned int, unsigned int); /* k_fifo_get */
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
        uint32_t package[3] = { 4U, 0x000f3badU, buffer[0x0b] };
        bt_conn_call_4arg_zero(0x00088108U, 0x2040U, package);
        return -22;
    }
    if (connection[0x0d] != 7U) {
        uint32_t package[2] = { 2U, 0x000f3bd2U };
        bt_conn_call_4arg_zero(0x00088108U, 0x1040U, package);
        return -128;
    }

    struct bt_conn_tx_recovered *tx = 0;
    if (callback != 0) {
        void *current = k_current_get();
        volatile uint32_t *const system_workqueue_thread =
            (volatile uint32_t *)0x20003a60U;
        uint32_t timeout = current == (void *)*system_workqueue_thread ? 0U : UINT32_MAX;
        tx = net_buf_pool_get_727ac((void *)0x200068d0U, 0U, timeout, timeout);
        if (tx == 0)
            return -105;
        if (connection[0x0d] != 7U) {
            uint32_t package[2] = { 2U, 0x000f3be1U };
            bt_conn_call_4arg_zero(0x00088108U, 0x1080U, package);
            tx->callback = 0;
            tx->user_data = 0;
            tx->pending_no_callback = 0;
            net_pkt_skip((void *)0x20003a60U, tx);
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
