/* Reconstructed post_notification_cmd_response @ 0x340c4. */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_0003384c(void *notification);
extern void FUN_00033f54(void *notification);
extern int FUN_00034bd4(const void *classification);
extern void FUN_0008705a(void *destination, const void *source, uint32_t length);

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
    volatile int *log_level = (volatile int *)0x2000230cu;
    volatile int *deferred_logger = (volatile int *)0x20007554u;

    if (context == 0 || notification == 0 || response == 0 || command == 0 ||
        payload == 0 || output == 0) {
        if (*log_level > 1) {
            if (*deferred_logger == 0)
                DEBUG_PRINT(0x000a7ef6u, 0x000a831fu, payload,
                            *deferred_logger,
                            context, notification, response);
            else
                FUN_00019c70(0x000a7ef6u, 0x000a831fu, payload,
                              *deferred_logger,
                              context, notification, response);
        }
        return 0;
    }

    if (*log_level > 2) {
        if (*deferred_logger == 0)
            DEBUG_PRINT(0x000a7f12u, 0x000a831fu, command->opcode,
                        *deferred_logger,
                        context, notification, response);
        else
            FUN_00019c70(0x000a7f12u, 0x000a831fu, command->opcode,
                          *deferred_logger,
                          context, notification, response);
    }

    if (command->opcode == 4) {
        uint8_t *state = *(uint8_t **)(context + 0xff8);

        FUN_0008705a(state + 8, notification + 0x54, 0x10);
        FUN_0008705a(state + 0x19, notification + 0x94, 0x96);
        state[0] = 0;
        state[1] = 0;
        state[2] = 0;
        state[3] = 0;
        if (context[0xd5] == 0)
            context[0xb0d] = 1;

        if (*log_level > 2) {
            if (*deferred_logger == 0)
                DEBUG_PRINT(0x000a7f41u, 0x000a831fu, state + 8, state + 0x19,
                            *(uint32_t *)state, notification + 0x194);
            else
                FUN_00019c70(0x000a7f41u, 0x000a831fu, state + 8,
                              state + 0x19, *(uint32_t *)state,
                              notification + 0x194);
        }
    } else {
        if (command->length != 0x1b4) {
            if (*log_level < 1)
                return 0;
            if (*deferred_logger != 0) {
                FUN_00019c70(0x000a7f79u, 0x000a831fu, 0x000a8300u,
                              0x158u, command->length, notification, response);
                return 0;
            }
            DEBUG_PRINT(0x000a7f79u, 0x000a831fu, 0x000a8300u, 0x158u,
                        command->length, notification, response);
            return 0;
        }

        if (read_u32(notification + 0x1b4) > 1) {
            FUN_00033f54(notification + 4);
        } else {
            int kind = FUN_00034bd4(notification + 0x14);
            uint8_t normalized = (uint8_t)(kind - 2);

            if (normalized <= 1)
                FUN_00033f54(notification + 4);
            else if (kind == 1)
                FUN_0003384c(notification + 4);
        }
    }

    if (response->opcode == 4) {
        if (*log_level > 2) {
            if (*deferred_logger == 0)
                DEBUG_PRINT(0x000a7faeu, 0x000a831fu);
            else
                FUN_00019c70(0x000a7faeu, 0x000a831fu);
        }
    } else if (response->opcode == 6 && *log_level > 2) {
        if (*deferred_logger == 0)
            DEBUG_PRINT(0x000a7fe3u, 0x000a831fu);
        else
            FUN_00019c70(0x000a7fe3u, 0x000a831fu);
    }

    *(uint32_t *)output = read_u32((const void *)0x000a1f49u);
    output[4] = read_u8((const void *)0x000a1f4du);
    return 5;
}
