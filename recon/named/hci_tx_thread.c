/* readable reconstruction; identity: FUN_000545f0 @ 0x000545f0
 * public-name: hci_tx_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   hci_cmd_complete_handle                  <= FUN_000538f8 @ 0x000538f8
 *   bt_hci_driver_send                       <= FUN_000543c8 @ 0x000543c8
 *   hci_tx_thread                            <= FUN_000545f0 @ 0x000545f0
 *   bt_conn_prepare_tx_events                <= FUN_000565c4 @ 0x000565c4
 *   bt_conn_tx_process                       <= FUN_000571e8 @ 0x000571e8
 *   net_buf_id                               <= FUN_0005ee18 @ 0x0005ee18
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_ref                              <= FUN_0005f2d4 @ 0x0005f2d4
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   mutex_unlock_syscall_handler             <= FUN_000745c8 @ 0x000745c8
 *   z_impl_k_poll                            <= FUN_000755f8 @ 0x000755f8
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 *   net_buf_get                              <= FUN_000836e8 @ 0x000836e8
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_a7a10                             @ 0x000a7a10   [INLINED -- G6 literal batch]
 *   rodata_f2e84                             @ 0x000f2e84
 *   rodata_f3103                             @ 0x000f3103
 *   rodata_f313c                             @ 0x000f313c   [INLINED -- G6 literal batch]
 *   rodata_f3157                             @ 0x000f3157
 *   rodata_f45be                             @ 0x000f45be
 *   g_20002128                               @ 0x20002128
 *   g_20002140                               @ 0x20002140
 *   hci_cmd_pool                             @ 0x2000214c
 *   g_20002944                               @ 0x20002944
 *   g_20002958                               @ 0x20002958
 *   bt_hci_cmd_data                          @ 0x2000abf4
 */
/* Full reconstruction FUN_000545f0 @ 0x000545f0 (348-byte exact extent). */
#include <stdint.h>
#include "../headers/g1_log.h"

extern uint32_t bt_conn_prepare_tx_events(uintptr_t poll_events);
extern uint32_t z_impl_k_poll(uintptr_t events, uint32_t count,
                            uint32_t timeout_lo, uint32_t timeout_hi);
/* Stock Zephyr 3.4 ARMv8-M Mainline ARCH_EXCEPT().  These instructions are
 * embedded at 0x54634..0x5463e and 0x5467e..0x54688 in the shipped function;
 * 0x5463e/0x54688 are SVC sites, not callable function entries. */
#define ARCH_EXCEPT(reason) do { \
    __asm__ volatile ( \
        "eors.n r0, r0\n\t" \
        "msr BASEPRI, r0\n\t" \
        "mov r0, %[why]\n\t" \
        "svc %[id]\n\t" \
        : : [why] "i" (reason), [id] "i" (2) : "memory"); \
    __builtin_unreachable(); \
} while (0)
/* AAPCS aligns the 64-bit timeout in r2:r3, leaving r1 as unused padding. */
extern uintptr_t net_buf_get(uintptr_t queue, uint64_t timeout);
extern int z_impl_k_sem_take(uintptr_t event, uint64_t timeout);
extern void bt_log_forward_3arg(uintptr_t source, uint32_t level, const void *record);
extern void net_buf_unref(void *buffer);
extern uintptr_t net_buf_ref(void *buffer);
extern uint32_t bt_hci_driver_send(void *buffer);
extern uint32_t net_buf_id(void *buffer);
extern void k_sem_give(uintptr_t event);
extern void hci_cmd_complete_handle(uint16_t handle, uint32_t reason, void *buffer);
extern void bt_conn_tx_process(void *connection);
extern void mutex_unlock_syscall_handler(uint32_t inherited);

struct log2 {
    uint32_t count;
    uintptr_t format;
};

struct log3 {
    uint32_t count;
    uintptr_t format;
    uint32_t value;
};

void hci_tx_thread(void)
{
    volatile uint8_t *const event_table = (volatile uint8_t *)0x20002944u;

    for (;;) {
        uint32_t flags = *(volatile uint32_t *)(event_table + 12);
        flags &= 0xffe03fffu;
        *(volatile uint32_t *)(event_table + 12) = flags;

        uint32_t count = bt_conn_prepare_tx_events(0x20002958u) + 1u;
        uint32_t wait_result = z_impl_k_poll(0x20002944u, count,
                                           UINT32_MAX, UINT32_MAX);
        if (wait_result != 0) {
            (void)printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"err == 0"),
                               0x000f2e84u, 0xadeu);
            ARCH_EXCEPT(3);
        }

        volatile uint8_t *event = event_table;
        for (uint32_t remaining = count; remaining != 0;
             --remaining, event += 20) {
            uint32_t type = (*(volatile uint32_t *)(event + 12) >> 14) & 0x7fu;
            if (type <= 2)
                continue;

            if (type == 4) {
                uint8_t state = *(volatile uint8_t *)(event + 12);
                if (state == 0) {
                    uintptr_t dequeued = net_buf_get(0x2000214cu, 0);
                    void *buffer = (void *)dequeued;
                    if (buffer == 0) {
                        (void)printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f45beu,
                                          0x000f2e84u, 0xa70u);
                        ARCH_EXCEPT(3);
                    }

                    z_impl_k_sem_take(0x20002128u, UINT64_MAX);

                    void **const pending = (void **)0x20002140u;
                    if (*pending != 0) {
                        const struct log2 record = {2, 0x000f313cu};
                        bt_log_forward_3arg(0x00088138u, 0x1040u, &record);
                        net_buf_unref(*pending);
                        *pending = 0;
                    }

                    *pending = (void *)net_buf_ref(buffer);
                    uint32_t error = bt_hci_driver_send(buffer);
                    if (error != 0) {
                        const struct log3 record = {3, 0x000f3103u, error};
                        bt_log_forward_3arg(0x00088138u, 0x1840u, &record);
                        k_sem_give(0x20002128u);
                        uint32_t slot = net_buf_id(buffer);
                        uint16_t handle = *(volatile uint16_t *)
                            (0x2000abf4u + slot * 12u + 2u);
                        hci_cmd_complete_handle(handle, 0x1fu, buffer);
                        net_buf_unref(buffer);
                    }
                } else if (state == 1) {
                    bt_conn_tx_process((void *)(uintptr_t)
                                 (*(volatile uintptr_t *)(event + 16) - 0x38u));
                }
            } else {
                const struct log3 record = {3, 0x000f3157u, type};
                bt_log_forward_3arg(0x00088138u, 0x1880u, &record);
            }
        }
        mutex_unlock_syscall_handler(0);
    }
}
