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
/* P4 iteration 19 — the +0x40 K_KERNEL_STACK_RESERVED of the SHIPPED build.
 * The recovered z_setup_new_thread (recon/net/src/FUN_01035edc.c) computes
 *     stack_buf_start = stack + 0x40
 *     stack_ptr       = stack + 0x40 + ROUND_UP(size, 8)
 * i.e. the shipped K_KERNEL_STACK_DEFINE reserved 0x40 bytes at the bottom of
 * every stack object (Cortex-M MPU stack guard).  This build's
 * K_THREAD_STACK_DEFINE reserves 0 (nm reports the arrays at exactly their
 * nominal size), so a nominal-size object made every thread run 0x40 bytes
 * past its own array.  Measured on g1-i19c-net with a Renode hook at the two
 * thread entry points: FUN_0102adac entered with sp = 0x21009b88 while
 * g1_hci_rpmsg_tx_stack is 0x21009560..0x21009b60, and FUN_0102acf4 entered
 * with sp = 0x21009588 while g1_hci_rpmsg_rx_stack is 0x21008d60..0x21009560 —
 * both 0x28 past their array end (0x40 reserve minus the 0x18 already pushed
 * at the entry hook).  The TX thread's outermost frames therefore sat on the
 * bottom of _k_thread_stack_mpsl_nonpreemptible_thread_id.  The arrays are
 * sized nominal + 0x40 so the reconstruction's own arithmetic stays inside
 * them. */
#define G1_NET_STACK_RESERVED 0x40
K_THREAD_STACK_DEFINE(g1_hci_rpmsg_tx_stack, 0x600 + G1_NET_STACK_RESERVED);
K_THREAD_STACK_DEFINE(g1_hci_rpmsg_rx_stack, 0x800 + G1_NET_STACK_RESERVED);
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

/* hci_rpmsg.c's controller->host k_fifo, shipped at 0x2100095c: the argument
 * FUN_0102afbc passes to bt_enable_raw (which stores it in hci_raw.c's
 * `raw_rx`) and the queue FUN_0102acf4 consumes.  In the cohesive link
 * 0x2100095c is 0x14 bytes into the STOCK hci_raw.c `hci_cmd_pool`
 * (0x21000948..0x2100097c), so net_buf_get() ran on a net_buf pool: measured
 * in iteration 19 as an unbounded `Unknown type %u` log loop on the CPUNET
 * (289,729,537 instructions in 8 s) with the app core's first HCI Reset never
 * answered. */
K_FIFO_DEFINE(g1_hci_rx_queue);

/* FUN_0102b1c8's ESB worker thread: shipped object 0x21001e38 (inside
 * backend_data_0 in the cohesive link) and stack 0x21007300 (inside
 * sdc_mempool).  See recon/net/src/FUN_0102b1c8.c for the measurement and for
 * the deferred reconstruction of its entry point (analysis 0x0102b204). */
K_THREAD_STACK_DEFINE(g1_esb_worker_stack, 0x600 + G1_NET_STACK_RESERVED);
struct k_thread g1_esb_worker_thread;

/* ------------------------------------------------------------------------
 * P4 iteration 20 — the ESB pipe-address block at 0x21000760.
 *
 * FUN_0102a278 (the "set pair addresses" IPC message handler) writes four
 * identical bytes at 0x21000761, 0x21000763 and 0x21000767; FUN_0102b31c
 * reads the same three; and main (FUN_0102a720) logs the four bytes at
 * 0x21000767 and 0x21000763 through two `%02x` format strings.  Iteration 19
 * independently established that the SHIPPED `_sw_isr_table` began at
 * 0x2100076c (that was z_isr_install's table-base literal), so this recovered
 * object is exactly 0x21000760..0x2100076c, twelve bytes.
 *
 * It is `.data` in the shipped image (below the 0xc3c .data end), and its
 * load image reads, through tools/net_extract.py at .data LMA + 0x760:
 *
 *     01 e9 d3 | a3 a3 a3 a3 | c9 c9 c9 c9 | ff
 *
 * i.e. exactly the {flag, ...} + master-address + slave-address + 0xff
 * placeholder shape the two accessors imply.  In the COHESIVE link the same
 * addresses land at `_sw_isr_table + 0x5c .. + 0x67` (the table is at
 * 0x21000704, 30 entries), so the handler was overwriting `_sw_isr_table[11]`
 * and `[12]`.  Measured mitigation: in this build those two entries are
 * `{NULL, z_irq_spurious}` (IRQ 11/12 use direct vectors on the CPUNET), so
 * the corruption is currently INERT — this is closed because it is a real
 * collision, not because it was observed to fault.
 * ------------------------------------------------------------------------ */
unsigned char g1_esb_pipe_addr_block[12] __attribute__((used, retain)) = {
    0x01, 0xe9, 0xd3,
    0xa3, 0xa3, 0xa3, 0xa3,
    0xc9, 0xc9, 0xc9, 0xc9,
    0xff,
};

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
