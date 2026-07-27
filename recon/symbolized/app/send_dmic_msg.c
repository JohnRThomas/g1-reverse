#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00019ed4 @ 0x00019ed4
 * public-name: send_dmic_msg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_dmic_msgq_count                      <= FUN_0002ecf4 @ 0x0002ecf4
 *   dequeue_dmic                             <= FUN_0002ed00 @ 0x0002ed00
 *   set_shutdown_flag                        <= FUN_0007cbfe @ 0x0007cbfe
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9b45e                             @ 0x0009b45e   [INLINED -- G6 literal batch]
 *   rodata_9b482                             @ 0x0009b482   [INLINED -- G6 literal batch]
 *   rodata_9e0a4                             @ 0x0009e0a4   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_dmic_send_fail_cnt                     @ 0x20007558
 *   g_dmic_send_pos_cnt                      @ 0x2000755c
 *   g_dmic_send_hundreds_cnt                 @ 0x20007560
 *   g_dmic_msg_seq                           @ 0x20010321
 */
/* Reconstructed send_dmic_msg @ 0x19ed4. */

#include <stdint.h>
#include "../../headers/g1_log.h"

struct dmic_message {
    uint32_t header;
    uint8_t tail[199];
};

typedef int (*dmic_send_fn)(const void *message, unsigned int length);

extern int get_device_info(void);
extern unsigned int get_dmic_msgq_count(void);
extern int dequeue_dmic(void *payload);
extern void set_shutdown_flag(void *state, int enabled);
extern void memset_bytes(void*, int, int);
extern unsigned long long thunk_FUN_00074f68(void);

int send_dmic_msg(uint8_t *transport)
{
    volatile uint8_t *sequence = (volatile uint8_t *)((unsigned long)&g_dmic_msg_seq) /*=0x20010321*/;
    volatile int *failure_count = (volatile int *)((unsigned long)&g_dmic_send_fail_cnt) /*=0x20007558*/;
    struct dmic_message message;
    uint8_t old_sequence;
    int result;

    message.header = 0;
    memset_bytes(message.tail, 0, sizeof(message.tail));
    ((uint8_t *)&message.header)[0] = 0xf1;

    do {
        ((uint8_t *)&message.header)[1] = *sequence;
        if (get_dmic_msgq_count() == 0) {
            return 0;
        }

        result = dequeue_dmic((uint8_t *)&message + 2);
        if (result != 0) {
            return result;
        }

        result = (*(dmic_send_fn *)(transport + 0x0c))(&message, 202);
        if (result < 0 && ++*failure_count > 9) {
            set_shutdown_flag(get_device_info(), 1);
            if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
                if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    log_message(((unsigned long)"%s(): BLE send failed for %d times\n") /*=0x9b45e*/, ((unsigned long)"send_dmic_msg") /*=0x9e0a4*/,
                                *failure_count);
                } else {
                    debug_print(((unsigned long)"%s(): BLE send failed for %d times\n") /*=0x9b45e*/, ((unsigned long)"send_dmic_msg") /*=0x9e0a4*/,
                                 *failure_count);
                }
            }
            *failure_count = 0;
            return result;
        }

        if (*(volatile int *)((unsigned long)&g_dmic_send_pos_cnt) /*=0x2000755c*/ + 1 < 100) {
            ++*(volatile int *)((unsigned long)&g_dmic_send_pos_cnt) /*=0x2000755c*/;
        } else {
            unsigned long long timestamp;
            unsigned long long scaled_timestamp;
            int report_count;

            *(volatile int *)((unsigned long)&g_dmic_send_pos_cnt) /*=0x2000755c*/ = 0;
            timestamp = thunk_FUN_00074f68();
            report_count = *(volatile int *)((unsigned long)&g_dmic_send_hundreds_cnt) /*=0x20007560*/;
            *(volatile int *)((unsigned long)&g_dmic_send_hundreds_cnt) /*=0x20007560*/ = report_count + 1;
            if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
                scaled_timestamp = (timestamp * 1000ULL + 0x7fffULL) >> 15;
                if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    log_message(((unsigned long)"%s(): dmic_send_count %d send_fail_count %d time %lld\n") /*=0x9b482*/, ((unsigned long)"send_dmic_msg") /*=0x9e0a4*/,
                                (report_count + 1) * 100, *failure_count,
                                (uint32_t)scaled_timestamp,
                                (uint32_t)(scaled_timestamp >> 32));
                } else {
                    debug_print(((unsigned long)"%s(): dmic_send_count %d send_fail_count %d time %lld\n") /*=0x9b482*/, ((unsigned long)"send_dmic_msg") /*=0x9e0a4*/,
                                 (report_count + 1) * 100, *failure_count,
                                 (uint32_t)scaled_timestamp,
                                 (uint32_t)(scaled_timestamp >> 32));
                }
            }
        }

        old_sequence = *sequence;
        *sequence = old_sequence + 1;
    } while (((old_sequence + 1) & 3) != 0);

    return 0;
}
