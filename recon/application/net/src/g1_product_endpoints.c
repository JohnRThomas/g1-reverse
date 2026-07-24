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
