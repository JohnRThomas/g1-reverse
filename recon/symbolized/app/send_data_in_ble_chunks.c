#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003384c @ 0x0003384c
 * public-name: send_data_in_ble_chunks
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   send_notification_app_whitelist          <= FUN_00033730 @ 0x00033730
 *   send_data_in_ble_chunks                  <= FUN_0003384c @ 0x0003384c
 *   strncmp                                  <= FUN_00087036 @ 0x00087036
 * address symbols (name @ address):
 *   rodata_883c8                             @ 0x000883c8
 *   rodata_a7bf5                             @ 0x000a7bf5   [INLINED -- G6 literal batch]
 *   rodata_a833e                             @ 0x000a833e   [INLINED -- G6 literal batch]
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full owned-CFG reconstruction FUN_0003384c @ 0x3384c. */
#include <stdint.h>
#include "../../headers/g1_log.h"

extern uint32_t strlen(uint32_t command);
extern uintptr_t get_device_info(void);
extern uint32_t send_notification_app_whitelist(void *transport, const void *name,
                             const void *payload, uint32_t reserved);
extern int strncmp(uint32_t command, const void *name, uint32_t value);

/* G7-B2 defect fix.  The body was `uint32_t` and `return`ed the result of the
 * logging call.  Both sinks are `void` (recon/headers/g1_log.h), and the
 * shipped function never computes a return value: 0x338d4 (the NULL-request
 * path) pops straight to pc with the incoming NULL still in r0, and all three
 * other exits are TAIL calls -- `b.w 0x19c70`, `b.w 0x7dda4` and
 * `b.w 0x33730` -- so r0 is always the callee's scratch.  Both call sites,
 * ancs_notification_forward.c and post_notification_cmd_response.c, already
 * declared it `extern void send_data_in_ble_chunks(void *)`; this definition
 * was the odd one out.  As `void` every exit stays a tail call and the
 * emitted sequence is unchanged. */
void send_data_in_ble_chunks(const uint8_t *request)
{
    const uint32_t *commands = (const uint32_t *)((unsigned long)&rodata_883c8) /*=0x883c8*/;
    uint32_t command_copy[9];
    unsigned int i;

    if (request == 0)
        return;

    for (i = 0; i < 9; ++i)
        command_copy[i] = commands[i];

    for (i = 0; i < 9; ++i) {
        uint32_t value = strlen(command_copy[i]);
        if (strncmp(command_copy[i], request + 0x10, value) == 0) {
            /* 0xa7bf5 has three specifiers, so four arguments; 0x3388c and
             * 0x338a0 load exactly r0..r3.  Only the `return` was wrong. */
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"[%s-%d] special package nane:%s,need not send to app !\n") /*=0xa7bf5*/, ((unsigned long)"send_whilelist_app_info_wrapper") /*=0xa833e*/,
                            0x137, request + 0x10);
                return;
            }
            debug_print(((unsigned long)"[%s-%d] special package nane:%s,need not send to app !\n") /*=0xa7bf5*/, ((unsigned long)"send_whilelist_app_info_wrapper") /*=0xa833e*/,
                        0x137, request + 0x10);
            return;
        }
    }

    send_notification_app_whitelist((void *)(get_device_info() + 0x77c),
                         request + 0x10, request + 0x30, 0);
}
