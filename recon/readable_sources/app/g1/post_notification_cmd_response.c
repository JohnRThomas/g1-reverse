#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_6          => struct g1_layout_audio_fw_load_msg__param_0039          [param_0039; G1-original]
 *   param_4          => struct g1_layout_audio_fw_load_notify_ctx__param_0076   [param_0076; G1-original]
 *   param_2          => struct g1_layout_audio_fw_load_notify_ctx__param_0076   [param_0076; G1-original]
 * Raw function identity: 0x000340c4.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000340c4 @ 0x000340c4
 * public-name: post_notification_cmd_response
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   send_data_in_ble_chunks                  <= FUN_0003384c @ 0x0003384c
 *   push_message                             <= FUN_00033f54 @ 0x00033f54
 *   is_on_whitelist_by_identifier            <= FUN_00034bd4 @ 0x00034bd4
 *   strncpy_zero_pad                         <= FUN_0008705a @ 0x0008705a
 * address symbols (name @ address):
 *   rodata_a1f49                             @ 0x000a1f49
 *   rodata_a1f4d                             @ 0x000a1f4d
 *   rodata_a7ef6                             @ 0x000a7ef6
 *   rodata_a7f12                             @ 0x000a7f12
 *   rodata_a7f41                             @ 0x000a7f41
 *   rodata_a7f79                             @ 0x000a7f79
 *   rodata_a7fae                             @ 0x000a7fae
 *   rodata_a8300                             @ 0x000a8300
 *   rodata_a831f                             @ 0x000a831f
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed post_notification_cmd_response @ 0x340c4. */
#include <stdint.h>

extern void log_message(uint32_t format, ...);
extern void debug_print(uint32_t format, ...);
extern void send_data_in_ble_chunks(void *notification);
extern void push_message(void *notification);
extern int is_on_whitelist_by_identifier(const void *classification);
extern void strncpy_zero_pad(void *destination, const void *source, uint32_t length);

struct notification_command {
    uint8_t reserved;
    uint8_t opcode;
    uint16_t length;
};

static inline uint32_t read_u32(const void *address)
{
    return *(const volatile uint32_t *)address;
}

static inline uint16_t read_u16(const void *address)
{
    return *(const volatile uint16_t *)address;
}

static inline uint8_t read_u8(const void *address)
{
    return *(const volatile uint8_t *)address;
}

int post_notification_cmd_response(uint8_t *context, uint8_t *notification,
                                   const struct notification_command *response,
                                   const struct notification_command *command,
                                   const void *payload, uint8_t output[5])
{
    volatile int *log_level = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    volatile int *deferred_logger = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;

    if (context == 0 || notification == 0 || response == 0 || command == 0 ||
        payload == 0 || output == 0) {
        if (*log_level > 1) {
            if (*deferred_logger == 0)
                log_message(((unsigned long)&rodata_a7ef6) /*=0xa7ef6*/, ((unsigned long)&rodata_a831f) /*=0xa831f*/, payload,
                            *deferred_logger,
                            context, notification, response);
            else
                debug_print(((unsigned long)&rodata_a7ef6) /*=0xa7ef6*/, ((unsigned long)&rodata_a831f) /*=0xa831f*/, payload,
                              *deferred_logger,
                              context, notification, response);
        }
        return 0;
    }

    if (*log_level > 2) {
        if (*deferred_logger == 0)
            log_message(((unsigned long)&rodata_a7f12) /*=0xa7f12*/, ((unsigned long)&rodata_a831f) /*=0xa831f*/, command->opcode,
                        *deferred_logger,
                        context, notification, response);
        else
            debug_print(((unsigned long)&rodata_a7f12) /*=0xa7f12*/, ((unsigned long)&rodata_a831f) /*=0xa831f*/, command->opcode,
                          *deferred_logger,
                          context, notification, response);
    }

    if (command->opcode == 4) {
        uint8_t *state = *(uint8_t **)(context + 0xff8);

        strncpy_zero_pad(state + 8, notification + 0x54, 0x10);
        strncpy_zero_pad(state + 0x19, notification + 0x94, 0x96);
        state[0] = 0;
        state[1] = 0;
        state[2] = 0;
        state[3] = 0;
        if (context[0xd5] == 0)
            context[0xb0d] = 1;

        if (*log_level > 2) {
            if (*deferred_logger == 0)
                log_message(((unsigned long)&rodata_a7f41) /*=0xa7f41*/, ((unsigned long)&rodata_a831f) /*=0xa831f*/, state + 8, state + 0x19,
                            *(uint32_t *)state, notification + 0x194);
            else
                debug_print(((unsigned long)&rodata_a7f41) /*=0xa7f41*/, ((unsigned long)&rodata_a831f) /*=0xa831f*/, state + 8,
                              state + 0x19, *(uint32_t *)state,
                              notification + 0x194);
        }
    } else {
        if (command->length != 0x1b4) {
            if (*log_level < 1)
                return 0;
            if (*deferred_logger != 0) {
                debug_print(((unsigned long)&rodata_a7f79) /*=0xa7f79*/, ((unsigned long)&rodata_a831f) /*=0xa831f*/, ((unsigned long)&rodata_a8300) /*=0xa8300*/,
                              0x158u, command->length, notification, response);
                return 0;
            }
            log_message(((unsigned long)&rodata_a7f79) /*=0xa7f79*/, ((unsigned long)&rodata_a831f) /*=0xa831f*/, ((unsigned long)&rodata_a8300) /*=0xa8300*/, 0x158u,
                        command->length, notification, response);
            return 0;
        }

        if (read_u32(notification + 0x1b4) > 1) {
            push_message(notification + 4);
        } else {
            int kind = is_on_whitelist_by_identifier(notification + 0x14);
            uint8_t normalized = (uint8_t)(kind - 2);

            if (normalized <= 1)
                push_message(notification + 4);
            else if (kind == 1)
                send_data_in_ble_chunks(notification + 4);
        }
    }

    if (response->opcode == 4) {
        if (*log_level > 2) {
            if (*deferred_logger == 0)
                log_message(((unsigned long)&rodata_a7fae) /*=0xa7fae*/, ((unsigned long)&rodata_a831f) /*=0xa831f*/);
            else
                debug_print(((unsigned long)&rodata_a7fae) /*=0xa7fae*/, ((unsigned long)&rodata_a831f) /*=0xa831f*/);
        }
    } else if (response->opcode == 6 && *log_level > 2) {
        if (*deferred_logger == 0)
            log_message(0x000a7fe3u, ((unsigned long)&rodata_a831f) /*=0xa831f*/);
        else
            debug_print(0x000a7fe3u, ((unsigned long)&rodata_a831f) /*=0xa831f*/);
    }

    *(uint32_t *)output = read_u32((const void *)((unsigned long)&rodata_a1f49) /*=0xa1f49*/);
    output[4] = read_u8((const void *)((unsigned long)&rodata_a1f4d) /*=0xa1f4d*/);
    return 5;
}
