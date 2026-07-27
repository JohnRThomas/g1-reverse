#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000536b8 @ 0x000536b8
 * public-name: bt_hci_core_recv_event
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_core_recv_event                   <= FUN_000536b8 @ 0x000536b8
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_8b190                             @ 0x0008b190
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f2ddb                             @ 0x000f2ddb   [INLINED -- G6 literal batch]
 *   rodata_f2e84                             @ 0x000f2e84
 *   rodata_f2eb8                             @ 0x000f2eb8   [INLINED -- G6 literal batch]
 *   rodata_f2ed1                             @ 0x000f2ed1   [INLINED -- G6 literal batch]
 *   rodata_f2ef5                             @ 0x000f2ef5   [INLINED -- G6 literal batch]
 *   rodata_f2f17                             @ 0x000f2f17   [INLINED -- G6 literal batch]
 *   rodata_f2f45                             @ 0x000f2f45   [INLINED -- G6 literal batch]
 *   g_bt_hci_recv_fifo                       @ 0x20002144
 *   g_bt_hci_rx_work                         @ 0x20002980
 *   bt_workqueue                             @ 0x20005f08
 *   g_bt_hci_acl_frag_conn_handle            @ 0x2000ff08
 */
/* Reconstructed bt_hci_core_recv_event @ 0x000536b8. */
#include <stdint.h>
#include "../../headers/g1_log.h"

extern void dispatch_hci_event(uint32_t event, void *buffer, uint32_t table, uint32_t count); /* FUN_00053658 */
extern void process_number_completed_packets(void *connection, void *buffer, uint32_t count); /* FUN_00056394 */
extern void ble_conn_unref(void *connection); /* FUN_000566a4 */
extern void *ble_conn_lookup_masked(uint32_t handle, uint32_t mask); /* FUN_00056908 */
extern uint32_t net_buf_id(void *buffer); /* FUN_0005ee18 */
extern unsigned int* net_buf_slist_get(unsigned int*); /* FUN_0005f148 */
extern void net_buf_unref(void *buffer); /* FUN_0005f24c */
extern void *net_buf_simple_pull(void *buffer, uint32_t length); /* FUN_0005f594 */
/* FUN_0007e2fa */
extern unsigned int bt_hci_evt_get_flags(unsigned int); /* FUN_00080e14 */
/* FUN_00080ea2 */
extern int k_work_submit_to_queue(void *queue, void *work); /* FUN_000865fc */

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
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"buf->len >= sizeof(*hdr)") /*=0xf2eb8*/, ((unsigned long)&rodata_f2e84) /*=0xf2e84*/, line);
    __asm__ volatile("movs r0, #0\n\tmsr basepri, r0\n\tmovs r0, #3\n\tsvc #2" ::: "r0", "memory");
    __builtin_unreachable();
}

void bt_hci_core_recv_event(void)
{
    void *buffer = net_buf_slist_get((void *)((unsigned long)&g_bt_hci_recv_fifo) /*=0x20002144*/);
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
            printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"bt_hci_evt_get_flags(hdr->evt) & (1UL << (1))") /*=0xf2f17*/, ((unsigned long)&rodata_f2e84) /*=0xf2e84*/, 0x0a61u);
            __asm__ volatile("movs r0, #0\n\tmsr basepri, r0\n\tmovs r0, #3\n\tsvc #2" ::: "r0", "memory");
            __builtin_unreachable();
        }
        dispatch_hci_event(*event, buffer, ((unsigned long)&rodata_8b190) /*=0x8b190*/, 6);
        net_buf_unref(buffer);
    } else if (type == 3) {
        if (*(uint16_t *)((uint8_t *)buffer + 0x10) < 4) {
            fatal_packet_length(0x0200u);
        }
        const uint16_t *completed = net_buf_simple_pull((uint8_t *)buffer + 0x0c, 4);
        uint16_t advertised_length = completed[1];
        uint16_t handle_and_count = completed[0];
        uint32_t id = net_buf_id(buffer);
        volatile uint16_t *handles = (volatile uint16_t *)((unsigned long)&g_bt_hci_acl_frag_conn_handle) /*=0x2000ff08*/;
        handles[id] = handle_and_count & 0x0fffu;

        uint16_t actual_length = *(uint16_t *)((uint8_t *)buffer + 0x10);
        if (advertised_length != actual_length) {
            struct log_record4 mismatch = {
                4, ((unsigned long)"ACL data length mismatch (%u != %u)") /*=0xf2ed1*/, actual_length, advertised_length,
            };
            log_message(((unsigned long)&rodata_88138) /*=0x88138*/, 0x2040u, &mismatch);
            net_buf_unref(buffer);
        } else {
            void *connection = ble_conn_lookup_masked(handles[net_buf_id(buffer)], 0x0fu);
            if (connection != 0) {
                process_number_completed_packets(connection, buffer, handle_and_count >> 12);
                ble_conn_unref(connection);
            } else {
                struct log_record3 missing = {
                    3, ((unsigned long)"Unable to find conn for handle %u") /*=0xf2ef5*/, handles[net_buf_id(buffer)],
                };
                log_message(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1840u, &missing);
                net_buf_unref(buffer);
            }
        }
    } else {
        struct log_record3 unexpected = {3, ((unsigned long)"Unknown buf type %u") /*=0xf2f45*/, type};
        log_message(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1840u, &unexpected);
        net_buf_unref(buffer);
    }

    if (*(volatile uint32_t *)((unsigned long)&g_bt_hci_recv_fifo) /*=0x20002144*/ != 0) {
        int status = k_work_submit_to_queue((void *)((unsigned long)&bt_workqueue) /*=0x20005f08*/,
                                            (void *)((unsigned long)&g_bt_hci_rx_work) /*=0x20002980*/);
        if (status < 0) {
            struct log_record3 failed = {3, ((unsigned long)"Could not submit rx_work: %d") /*=0xf2ddb*/, (uint32_t)status};
            log_message(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1840u, &failed);
        }
    }
}
