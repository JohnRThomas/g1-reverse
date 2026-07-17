/* Reconstructed smp_rx_remove_invalid @ 0x00052760 (0x76 bytes).
 * Raw identity/back-map: FUN_00052760.
 * Exact NCS 2.5.1 source correspondence: Zephyr mcumgr transport/src/smp.c.
 */
#include <stdbool.h>
#include <stdint.h>

struct net_buf;
struct k_work { uint8_t opaque[0x10]; };
struct k_fifo { uint8_t opaque[0x1c]; };
struct k_work_q;

typedef bool (*smp_transport_query_valid_check_fn)(struct net_buf *nb,
                                                    void *arg);

struct smp_transport_api {
    void *output;
    void *get_mtu;
    void *ud_copy;
    void *ud_free;
    smp_transport_query_valid_check_fn query_valid_check;
};

struct smp_transport {
    struct k_work work;
    struct k_fifo fifo;
    struct smp_transport_api functions;
};

typedef struct { int64_t ticks; } k_timeout_t;
#define K_NO_WAIT ((k_timeout_t){ 0 })

extern unsigned int k_work_busy_get(const struct k_work *work); /* FUN_00072e9c */
extern int k_work_cancel(struct k_work *work); /* FUN_00072fe8 */
extern void k_fifo_init(struct k_fifo *fifo); /* FUN_000864e8 */
extern struct net_buf *net_buf_get(struct k_fifo *fifo,
                                   k_timeout_t timeout); /* FUN_000836e8 */
extern void net_buf_put(struct k_fifo *fifo, struct net_buf *buf); /* FUN_0005f200 */
extern void smp_free_buf(void *buf, void *arg); /* FUN_00080b0e */
extern int k_work_submit_to_queue(struct k_work_q *queue,
                                  struct k_work *work); /* FUN_000865fc */

#define smp_work_queue (*(struct k_work_q *)0x20005bb8u) /* address back-map */

static bool k_fifo_is_empty(const struct k_fifo *fifo)
{
    return *(void *const *)fifo == 0;
}

void smp_rx_remove_invalid(struct smp_transport *transport, void *arg)
{
    struct net_buf *buffer;
    struct k_fifo retained;

    if (transport->functions.query_valid_check == 0) {
        return;
    }

    if (k_work_busy_get(&transport->work) & 5u) {
        k_work_cancel(&transport->work);
    }

    k_fifo_init(&retained);

    while ((buffer = net_buf_get(&transport->fifo, K_NO_WAIT)) != 0) {
        if (!transport->functions.query_valid_check(buffer, arg)) {
            smp_free_buf(buffer, transport);
        } else {
            net_buf_put(&retained, buffer);
        }
    }

    while ((buffer = net_buf_get(&retained, K_NO_WAIT)) != 0) {
        net_buf_put(&transport->fifo, buffer);
    }

    if (!k_fifo_is_empty(&transport->fifo)) {
        k_work_submit_to_queue(&smp_work_queue, &transport->work);
    }
}
