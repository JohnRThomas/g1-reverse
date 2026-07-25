/* net-core FUN_0102acf4 @ 0x0102acf4
 * Readable identity: g1_hci_rpmsg_tx_thread.
 * Raw back-map: FUN_0102afbc stores runtime Thumb pointer 0x0102b4f5.
 */
#include <stdint.h>

#ifdef G1_COHESIVE_BUILD
/* P4 iteration 7 — relocated net-core IPC objects.  See
 * recon/application/net/src/g1_product_endpoints.c for the decode of the two
 * K_SEM_DEFINE(...,0,1) bind semaphores (original 0x21000914 / 0x2100092c) and
 * of the `struct ipc_ept` + ready flag (original 0x210045f8 / 0x21004600),
 * plus the measured sched.c:722 kernel panic they caused.  Parity builds keep
 * the original literals. */
#include <zephyr/kernel.h>
#include <zephyr/ipc/ipc_service.h>
extern struct k_sem g1_ipc0_bound_sem;
extern struct k_sem g1_hci_bound_sem;
extern struct ipc_ept g1_ipc0_ept;
extern volatile uint32_t g1_ipc0_ept_ready;
#define G1_IPC0_BOUND_SEM ((void *)&g1_ipc0_bound_sem)
#define G1_HCI_BOUND_SEM  ((void *)&g1_hci_bound_sem)
#define G1_IPC0_EPT       ((void *)&g1_ipc0_ept)
#define G1_IPC0_EPT_READY (g1_ipc0_ept_ready)
#else
#define G1_IPC0_BOUND_SEM ((void *)UINT32_C(0x21000914))
#define G1_HCI_BOUND_SEM  ((void *)UINT32_C(0x2100092c))
#define G1_IPC0_EPT       ((void *)UINT32_C(0x210045f8))
#define G1_IPC0_EPT_READY (*(volatile uint32_t *)UINT32_C(0x21004600))
#endif

#ifdef G1_COHESIVE_BUILD
#include <zephyr/ipc/ipc_service.h>
#include <zephyr/kernel.h>
#include <zephyr/net/buf.h>
#define FUN_0103a456(fifo, timeout) net_buf_get((struct k_fifo *)(fifo), K_FOREVER)
#define FUN_0103a45a(simple, byte) \
    net_buf_simple_push_u8((struct net_buf_simple *)(simple), (byte))
#define FUN_0102d618(endpoint, data, size) \
    ipc_service_send((struct ipc_ept *)(endpoint), (data), (size))
#define FUN_01037a60() k_yield()
#else
extern void *FUN_0103a456(void *fifo, int64_t timeout);
extern void FUN_0103a45a(void *simple, uint32_t byte);
extern int FUN_0102d618(void *endpoint, const void *data, uint32_t size);
extern void FUN_01037a60(void);
#endif

/* P4 iteration 19 — two more shipped absolute CPUNET objects that this file
 * still spelled as raw literals (iteration 18 §18.8 open item 4: raw
 * 0x21xxxxxx literals inside net sources are invisible to the RAM-pin gate).
 *
 *  * 0x2100095c is hci_rpmsg.c's controller->host `rx_queue`, the k_fifo that
 *    FUN_0102afbc hands to bt_enable_raw and that this thread consumes.  In
 *    the cohesive link 0x2100095c is 0x14 bytes into the STOCK hci_raw.c
 *    `hci_cmd_pool` (0x21000948..0x2100097c), so net_buf_get() ran on a
 *    net_buf pool.  Measured consequence (iteration 19): the thread received a
 *    garbage "buffer" on every iteration, fell through to the `Unknown type
 *    %u` branch and spun; the CPUNET burned 289,729,537 instructions in 8 s
 *    with cbvprintf_package/mpsc_pbuf_alloc as the top consumers, and the
 *    HCI Reset the app core had just sent was never answered.
 *  * 0x21004608 is the `struct ipc_ept` this thread sends on.  It is the same
 *    object FUN_0102afbc registers, which iteration 18 already relocated to
 *    g1_hci_ept; unrelocated here it aliases sdc_mempool.
 *
 * Both are bound to the real objects in
 * recon/application/net/src/g1_product_endpoints.c.  Parity builds keep the
 * original literals. */
#ifdef G1_COHESIVE_BUILD
extern struct k_fifo g1_hci_rx_queue;
extern struct ipc_ept g1_hci_ept;
#define G1_HCI_RX_QUEUE ((void *)&g1_hci_rx_queue)
#define G1_HCI_EPT      ((void *)&g1_hci_ept)
#else
#define G1_HCI_RX_QUEUE ((void *)UINT32_C(0x2100095c))
#define G1_HCI_EPT      ((void *)UINT32_C(0x21004608))
#endif

#define g1_hci_rpmsg_tx_thread FUN_0102acf4

extern int FUN_0103689c(void *sem, int64_t timeout);
extern void FUN_0102ff94(void *buffer);
extern void FUN_01039722(const char *format, ...);

struct g1_net_buf {
    uint8_t reserved[12];
    const void *data;
    uint16_t len;
    uint8_t reserved2[6];
    uint8_t type;
};

void g1_hci_rpmsg_tx_thread(void)
{
    FUN_0103689c(G1_HCI_BOUND_SEM, -1);
    for (;;) {
        struct g1_net_buf *buffer = FUN_0103a456(G1_HCI_RX_QUEUE, -1);
        *(volatile uint32_t *)0x418c0508u = 0x40000000u;
        uint32_t indicator;
        if (buffer->type == 3)
            indicator = 2;
        else if (buffer->type == 5)
            indicator = 5;
        else if (buffer->type == 1)
            indicator = 4;
        else {
            if (*(volatile int32_t *)0x21000580u > 0)
                FUN_01039722((const char *)0x0103cf17u, buffer->type);
            FUN_0102ff94(buffer);
            *(volatile uint32_t *)0x418c050cu = 0x40000000u;
            continue;
        }
        FUN_0103a45a((uint8_t *)buffer + 12, indicator);
        uint8_t failures = 0;
        while (FUN_0102d618(G1_HCI_EPT,
                            buffer->data, buffer->len) < 0) {
            failures = (uint8_t)(failures + 1u);
            if (failures == 11) {
                if (*(volatile int32_t *)0x21000580u > 1)
                    FUN_01039722((const char *)0x0103cf28u);
                failures = 0;
            }
            FUN_01037a60();
        }
        FUN_0102ff94(buffer);
        *(volatile uint32_t *)0x418c050cu = 0x40000000u;
    }
}
