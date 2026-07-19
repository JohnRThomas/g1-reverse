#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_3          => struct g1_layout_notif_count_out__param_0098            [param_0098; G1-original]
 * Raw function identity: 0x00033abc.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00033abc @ 0x00033abc
 * public-name: get_notification_counts_cmd_process
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   audio_fw_load_trigger_passthrough        <= FUN_0007c1fe @ 0x0007c1fe
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 * address symbols (name @ address):
 *   rodata_9b74b                             @ 0x0009b74b
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed get_notification_counts_cmd_process @ 0x33abc  (parity: 79/300 trials, PROVEN) */

typedef void (*response_fn)(unsigned char *response, unsigned int length);
extern void log_message(unsigned int message, unsigned int function);
extern void debug_print(void);
extern void audio_fw_load_trigger_passthrough(unsigned char *request, unsigned char *payload,
                         unsigned int count, unsigned int capacity);

void get_notification_counts_cmd_process(unsigned char *param_1, unsigned char *param_2, unsigned char *param_3)
{
    audio_fw_load_trigger_passthrough(param_1, param_2, 1, 0x1e);
    param_3[1] = 0xc9;
    unsigned char v = param_2[0];
    param_3[2] = v;
    if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)&rodata_9b74b) /*=0x9b74b*/, 0xa827b);
        } else {
            debug_print();
        }
    }
    response_fn respond = *(response_fn *)(param_1 + 0xc);
    respond(param_3, 0x14);
}
