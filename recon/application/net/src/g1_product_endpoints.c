/* Recovered product IPC endpoint ownership.
 *
 * Original initialized-data back-maps:
 *   g1_ipc0_endpoint_config @ 0x21000584
 *   g1_hci_endpoint_config  @ 0x2100059c
 * Callback words remain documented at their shipped runtime Thumb values;
 * this cohesive build expresses them as relocations to the CFG-proven bodies.
 */
#include <stddef.h>
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/ipc/ipc_service.h>

/* P4 iteration 7 — the two endpoint bind semaphores, relocated.
 *
 * FUN_0102ac00 / FUN_0102ace8 (the `bound` callbacks above) k_sem_give the
 * absolute addresses 0x21000914 and 0x2100092c, and FUN_0102ac0c /
 * g1_hci_rpmsg_tx_thread k_sem_take the same two.  Both are `.data` in the
 * shipped netcore image: its .data load image starts at flash 0x0103ed24
 * (RAM 0x21000000; length 0xc3c, ending exactly at the image end 0x0103f960),
 * and the 24 bytes for each read
 *     0x21000914 -> { 0x21000914, 0x21000914, 0, 1, 0x21000924, 0x21000924 }
 *     0x2100092c -> { 0x2100092c, 0x2100092c, 0, 1, 0x2100093c, 0x2100093c }
 * i.e. self-referential wait_q + poll_events, count 0, limit 1 —
 * K_SEM_DEFINE(<name>, 0, 1).  Nothing in the recovered corpus initialises
 * them, and in the cohesive build those addresses are other live objects.
 *
 * MEASURED (iteration 7 Step A): with the app core finally completing the
 * rpmsg bind, the net core reached its own `bound_cb` -> FUN_0102ac00 ->
 * FUN_01036824 (k_sem_give) and the wait_q at 0x21000914 held a bogus thread,
 * tripping `__ASSERT_NO_MSG(thread->base.pended_on)`
 * (zephyr/kernel/sched.c:722, lr = unpend_thread_no_timeout+0x1e) -> kernel
 * panic -> SYSRESETREQ, which reset the whole emulated machine.  Evidence:
 * recon/emulator/reports/our_boot_bringup.md §Iteration 7 Step A. */
K_SEM_DEFINE(g1_ipc0_bound_sem, 0, 1);
K_SEM_DEFINE(g1_hci_bound_sem, 0, 1);

/* The registered endpoint handle (original 0x210045f8) and the "endpoint is
 * usable" flag (original 0x21004600) that FUN_0102ac0c writes and FUN_0102abac
 * reads.  Both are .bss in the shipped image (above its 0xc3c .data end) but
 * in the cohesive build their pins land inside `sdc_mempool`, the SoftDevice
 * Controller heap, so ipc_service_register_endpoint was writing into it. */
struct ipc_ept g1_ipc0_ept;
volatile uint32_t g1_ipc0_ept_ready;

/* ------------------------------------------------------------------------
 * P4 iteration 18 — the two "HCI rpmsg" threads of FUN_0102afbc.
 *
 * FUN_0102afbc is NCS 2.5.1's samples/bluetooth/hci_rpmsg/src/main.c body: it
 * creates the TX and RX threads, names them, opens the ipc0 instance and
 * registers the "nrf_bt_hci" endpoint.  Its shipped storage is
 *
 *     struct k_thread  RX  0x21001d08   stack 0x21006480  0x800 B
 *     struct k_thread  TX  0x21001da0   stack 0x21006cc0  0x600 B
 *     struct ipc_ept   HCI 0x21004608
 *
 * and in the cohesive link EVERY one of those addresses is inside a live
 * linker-allocated object:
 *
 *     0x21001d08 / 0x21001da0 -> backend_data_0  [0x21001cf8..0x21002090]
 *                                (the ipc_rpmsg_static_vrings instance:
 *                                 rpmsg_inst.endpoint[0..1] and
 *                                 rvdev.rdev, whose `endpoints` metal_list
 *                                 head is at +0xe0)
 *     0x21006480 / 0x21006cc0 -> sdc_mempool     [0x21002990..0x21007c51]
 *     0x21004608              -> sdc_mempool
 *
 * MEASURED (Renode watchpoints, iteration 18 §18.1/§18.2): z_setup_new_thread
 * writing thread+0x74 hit 0x21001e14, which is `rdev.ns_ept.node.next`, and
 * z_add_timeout writing the thread's own `_timeout` (thread+0x18) hit
 * 0x21001d30 = `endpoint[0].ep.node.prev`.  With the endpoint dlist broken,
 * OpenAMP's rpmsg_get_endpoint walked a NULL `next` forever (99.3 % of the net
 * core's instructions), the app core's HCI endpoint never bound, and
 * bt_enable() failed with -ENOENT.
 *
 * Give the three objects real storage.  Sizes and priorities are unchanged;
 * only the addresses move, exactly as for g1_ipc0_ept above.
 * ------------------------------------------------------------------------ */
K_THREAD_STACK_DEFINE(g1_hci_rpmsg_tx_stack, 0x600);
K_THREAD_STACK_DEFINE(g1_hci_rpmsg_rx_stack, 0x800);
struct k_thread g1_hci_rpmsg_tx_thread;
struct k_thread g1_hci_rpmsg_rx_thread;
struct ipc_ept g1_hci_ept;

/* The two k_thread_name_set() arguments.  0x0103d088 / 0x0103d095 are stored
 * pointer VALUES, i.e. CPUNET *runtime* addresses (tools/net_address_space.py);
 * their analysis addresses 0x0103c888 / 0x0103c895 read
 * "HCI rpmsg TX" / "HCI rpmsg RX" out of netcore_image.bin. */
const char g1_hci_rpmsg_tx_name[] = "HCI rpmsg TX";
const char g1_hci_rpmsg_rx_name[] = "HCI rpmsg RX";

/* hci_rpmsg.c's `static K_FIFO_DEFINE(tx_queue);` — shipped at 0x21000978,
 * which in the cohesive link is 0x18 bytes into net_buf_pool_area's third
 * `struct net_buf_pool` (the section runs 0x210008f8..0x21000994).  The RX
 * endpoint callback (FUN_0102adf0) puts into it and the TX thread
 * (FUN_0102adac) does net_buf_get() on it, so unrelocated the two of them
 * treat a net_buf pool as a k_fifo. */
K_FIFO_DEFINE(g1_hci_tx_queue);

/* FUN_0102b1c8's ESB worker thread: shipped object 0x21001e38 (inside
 * backend_data_0 in the cohesive link) and stack 0x21007300 (inside
 * sdc_mempool).  See recon/net/src/FUN_0102b1c8.c for the measurement and for
 * the deferred reconstruction of its entry point (analysis 0x0102b204). */
K_THREAD_STACK_DEFINE(g1_esb_worker_stack, 0x600);
struct k_thread g1_esb_worker_thread;

extern void FUN_0102ac00(void *priv); /*=0x0102b401*/
extern void FUN_0102ab14(const uint8_t *data, size_t size, void *priv); /*=0x0102b315*/
extern void FUN_0102ace8(void *priv); /*=0x0102b4e9*/
extern void FUN_0102adf0(uint8_t *data, uint32_t size); /*=0x0102b5f1*/

struct ipc_ept_cfg g1_ipc0_endpoint_config = {
    .name = "ipc0",
    .prio = 0,
    .cb = {
        .bound = FUN_0102ac00,
        .received = (void (*)(const void *, size_t, void *))FUN_0102ab14,
        .error = NULL,
    },
    .priv = NULL,
};

struct ipc_ept_cfg g1_hci_endpoint_config = {
    .name = "nrf_bt_hci",
    .prio = 0,
    .cb = {
        .bound = FUN_0102ace8,
        .received = (void (*)(const void *, size_t, void *))FUN_0102adf0,
        .error = NULL,
    },
    .priv = NULL,
};
