/* Reconstructed bt_hci_core_recv_event @ 0x000536b8. */
#include <stdint.h>

extern void dispatch_hci_event(uint32_t event, void *buffer, uint32_t table, uint32_t count); /* FUN_00053658 */
extern void process_number_completed_packets(void *connection, void *buffer, uint32_t count); /* FUN_00056394 */
extern void ble_conn_unref(void *connection); /* FUN_000566a4 */
extern void *ble_conn_lookup_masked(uint32_t handle, uint32_t mask); /* FUN_00056908 */
extern uint32_t net_buf_id(void *buffer); /* FUN_0005ee18 */
extern unsigned int* net_buf_slist_get(unsigned int*); /* FUN_0005f148 */
extern void net_buf_unref(void *buffer); /* FUN_0005f24c */
extern void *net_buf_simple_pull(void *buffer, uint32_t length); /* FUN_0005f594 */
extern void printk(unsigned long, ...); /* FUN_0007e2fa */
extern unsigned int bt_hci_evt_get_flags(unsigned int); /* FUN_00080e14 */
extern void log_message(unsigned long, ...); /* FUN_00080ea2 */
extern int k_work_submit_to_queue(struct k_work_q *, struct k_work *); /* FUN_000865fc */

struct log_record3 {
    uint32_t argument_count;
    uint32_t format;
    uint32_t argument0;
};

struct log_record4 {
    uint32_t argument_count;
    uint32_t format;
    uint32_t argument0;
    uint32_t argument1;
};

__attribute__((noreturn, always_inline)) static inline void fatal_packet_length(uint32_t line)
{
    printk(0x00099cbdu, 0x000f2eb8u, 0x000f2e84u, line);
    __asm__ volatile("movs r0, #0\n\tmsr basepri, r0\n\tmovs r0, #3\n\tsvc #2" ::: "r0", "memory");
    __builtin_unreachable();
}

void FUN_000536b8(void)
{
    void *buffer = net_buf_slist_get((void *)0x20002144u);
    if (buffer == 0) {
        return;
    }

    uint8_t type = *(uint8_t *)((uint8_t *)buffer + 0x18);
    if (type == 1) {
        if (*(uint16_t *)((uint8_t *)buffer + 0x10) < 2) {
            fatal_packet_length(0x0a5du);
        }
        uint8_t *event = net_buf_simple_pull((uint8_t *)buffer + 0x0c, 2);
        if ((bt_hci_evt_get_flags(*event) & 2) == 0) {
            printk(0x00099cbdu, 0x000f2f17u, 0x000f2e84u, 0x0a61u);
            __asm__ volatile("movs r0, #0\n\tmsr basepri, r0\n\tmovs r0, #3\n\tsvc #2" ::: "r0", "memory");
            __builtin_unreachable();
        }
        dispatch_hci_event(*event, buffer, 0x0008b190u, 6);
        net_buf_unref(buffer);
    } else if (type == 3) {
        if (*(uint16_t *)((uint8_t *)buffer + 0x10) < 4) {
            fatal_packet_length(0x0200u);
        }
        const uint16_t *completed = net_buf_simple_pull((uint8_t *)buffer + 0x0c, 4);
        uint16_t advertised_length = completed[1];
        uint16_t handle_and_count = completed[0];
        uint32_t id = net_buf_id(buffer);
        volatile uint16_t *handles = (volatile uint16_t *)0x2000ff08u;
        handles[id] = handle_and_count & 0x0fffu;

        uint16_t actual_length = *(uint16_t *)((uint8_t *)buffer + 0x10);
        if (advertised_length != actual_length) {
            struct log_record4 mismatch = {
                4, 0x000f2ed1u, actual_length, advertised_length,
            };
            log_message(0x00088138u, 0x2040u, &mismatch);
            net_buf_unref(buffer);
        } else {
            void *connection = ble_conn_lookup_masked(handles[net_buf_id(buffer)], 0x0fu);
            if (connection != 0) {
                process_number_completed_packets(connection, buffer, handle_and_count >> 12);
                ble_conn_unref(connection);
            } else {
                struct log_record3 missing = {
                    3, 0x000f2ef5u, handles[net_buf_id(buffer)],
                };
                log_message(0x00088138u, 0x1840u, &missing);
                net_buf_unref(buffer);
            }
        }
    } else {
        struct log_record3 unexpected = {3, 0x000f2f45u, type};
        log_message(0x00088138u, 0x1840u, &unexpected);
        net_buf_unref(buffer);
    }

    if (*(volatile uint32_t *)0x20002144u != 0) {
        int status = k_work_submit_to_queue((void *)0x20005f08u,
                                            (void *)0x20002980u);
        if (status < 0) {
            struct log_record3 failed = {3, 0x000f2ddbu, (uint32_t)status};
            log_message(0x00088138u, 0x1840u, &failed);
        }
    }
}
