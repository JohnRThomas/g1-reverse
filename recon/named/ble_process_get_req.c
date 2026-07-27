/* readable reconstruction; identity: FUN_0001a064 @ 0x0001a064
 * public-name: ble_process_get_req
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_type                          <= FUN_00016568 @ 0x00016568
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   audio_fw_load_get_wrapper                <= FUN_00019b54 @ 0x00019b54
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_notification_counts_cmd_process      <= FUN_00033abc @ 0x00033abc
 *   send_whitelist_json_chunked              <= FUN_00035498 @ 0x00035498
 *   SendSystemLanguageInfoToSlave            <= FUN_00048998 @ 0x00048998
 *   debug_print_hex_dump                     <= FUN_0004a424 @ 0x0004a424
 *   is_system_idle_ready                     <= FUN_0007ce00 @ 0x0007ce00
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   safe_memcpy_checked                      <= FUN_00086c1e @ 0x00086c1e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   strcpy                                   <= FUN_00086fee @ 0x00086fee
 * address symbols (name @ address):
 *   rodata_9b5dd                             @ 0x0009b5dd   [INLINED -- G6 literal batch]
 *   rodata_9b98b                             @ 0x0009b98b   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ui_mode_flag                           @ 0x20018462
 */
/* Reconstructed ble_process_get_req @ 0x1a064 */
#include <stdint.h>
#include "../headers/g1_log.h"

extern int  get_device_type(void);
extern int  get_device_info(void);
extern unsigned long audio_fw_load_get_wrapper(int, unsigned char*, unsigned long);
extern void get_notification_counts_cmd_process(void *, void *, void *);
extern void send_whitelist_json_chunked(void *, void *);
extern void SendSystemLanguageInfoToSlave(uint32_t);
extern void debug_print_hex_dump(int, int, int);
extern int  is_system_idle_ready(void);
extern void memcpy(int, int, int);
extern void safe_memcpy_checked(void *, const void *, uint32_t, uint32_t);
extern void memset_bytes(void*, int, int);
extern void strcpy(void *, const void *);

#define LOG_LEVEL (*(volatile int32_t *)0x2000230cu)
#define LOG_MODE  (*(volatile int32_t *)0x20007554u)
#define AUDIO_LOAD_STATUS (*(volatile uint8_t *)0x20018462u)

typedef void (*send_response_fn)(const void *, uint32_t);

static __attribute__((always_inline)) inline void copy_bytes(volatile uint8_t *dst,
                              const volatile uint8_t *src, uint32_t count)
{
    while (count--)
        *dst++ = *src++;
}

#define LOG_AT(level) do {                         \
    if (LOG_LEVEL > (level)) {                     \
        if (LOG_MODE == 0) log_message(0);         \
        else debug_print(0);                      \
    }                                              \
} while (0)

void ble_process_get_req(uint8_t *context, const uint8_t *packet,
                         const uint8_t *request_data)
{
    /* The wire response is command, response opcode, then payload.  Command
       0x3e is the large 192-byte payload; 0x33/0x34 copy 16-byte records. */
    uint8_t response[194];
    uint8_t data[244];
    uint8_t command = packet[0];
    uint32_t response_length = 0x14;

    *(uint32_t *)response = 0;
    memset_bytes(response + 4, 0, 0x11);
    **(uint32_t **)(context + 0x10) = *(const uint32_t *)packet;
    *(uint32_t *)(context + 0x14) = *(const uint16_t *)(packet + 2);
    response[0] = command;

    switch (command) {
    case 0x29:
        audio_fw_load_get_wrapper(context, data, 1);
        response[1] = 0x65;
        response[2] = data[0];
        response[3] = data[1];
        LOG_AT(2);
        break;
    case 0x2a:
        audio_fw_load_get_wrapper(context, data, 1);
        response[1] = 0x68;
        response[2] = data[0];
        LOG_AT(2);
        break;
    case 0x2b:
        audio_fw_load_get_wrapper(context, data, 1);
        response[1] = 0x69;
        response[2] = data[0];
        response[3] = data[1];
        LOG_AT(2);
        break;
    case 0x2c:
        if ((int8_t)request_data[1] == 1)
            context[0x8ec] = 0;
        else if ((int8_t)request_data[1] == 2)
            context[0x8ec] = 1;
        LOG_AT(2);
        audio_fw_load_get_wrapper(context, data, 0x18);
        response[1] = 0x66;
        copy_bytes(response + 2, data, 17);
        LOG_AT(2);
        break;
    case 0x2d:
        audio_fw_load_get_wrapper(context, data, 0x0c);
        response[1] = 0x67;
        debug_print_hex_dump((void *)0x0009b5ddu, data, 0x0c);
        copy_bytes(response + 2, data, 12);
        LOG_AT(2);
        break;
    case 0x2e:
        send_whitelist_json_chunked(context, response);
        return;

    /* 0x2f, 0x30 and 0x31 are reserved and use the standard error reply. */
    case 0x32:
        audio_fw_load_get_wrapper(context, data, 1);
        response[1] = 0x6d;
        response[2] = data[0];
        response[3] = data[1];
        LOG_AT(2);
        break;
    case 0x33:
        audio_fw_load_get_wrapper(context, data, 1);
        response[1] = 0x33;
        copy_bytes(response + 2, data, 16);
        LOG_AT(2);
        break;
    case 0x34:
        audio_fw_load_get_wrapper(context, data, 1);
        response[1] = 0x34;
        copy_bytes(response + 2, data, 16);
        LOG_AT(2);
        break;
    case 0x35:
        audio_fw_load_get_wrapper(context, data, 1);
        response[1] = 0xc9;
        response[2] = data[0];
        LOG_AT(2);
        break;
    case 0x36:
        get_notification_counts_cmd_process(context, data, response);
        return;
    case 0x37:
        audio_fw_load_get_wrapper(context, data, 1);
        response[1] = 0x37;
        copy_bytes(response + 2, data, 5);
        break;
    case 0x38:
        response[1] = 0xc9;
        response[2] = context[0x8f4];
        LOG_AT(0);
        break;
    case 0x39:
        if (*(const int16_t *)(request_data + 1) ==
            *(const int16_t *)(packet + 2)) {
            memset_bytes(response + 5, 0, 0x10);
            copy_bytes(response, request_data, 5);
            if (is_system_idle_ready() == 0) {
                response[5] = context[-0x6a7] ? context[-0x6a7] : 0xff;
                LOG_AT(2);
            } else {
                response[5] = 0;
                LOG_AT(2);
            }
        } else {
            LOG_AT(0);
            memset_bytes(response + 6, 0, 0x0f);
            copy_bytes(response, request_data, 5);
            response[5] = 0xff;
        }
        (*(send_response_fn *)(context + 0x0c))(response, 6);
        return;
    case 0x3a:
        response[1] = 0xc9;
        response[2] = context[0x911];
        LOG_AT(0);
        break;
    case 0x3b:
        response[1] = 0xc9;
        response[2] = context[0x744];
        response[3] = context[0x745];
        LOG_AT(2);
        break;
    case 0x3c:
        response[1] = 0xc9;
        response[2] = context[0x913];
        LOG_AT(0);
        break;
    case 0x3d: {
        uint16_t request_id = *(const uint16_t *)(request_data + 1);
        uint16_t packet_id = *(const uint16_t *)(packet + 2);
        if (request_id != packet_id) {
            if (LOG_LEVEL < 2)
                return;
            if (LOG_MODE == 0) log_message(0); else debug_print(0);
            return;
        }
        uint8_t load_status = request_data[5];
        memset_bytes(response, 0, 0x15);
        safe_memcpy_checked(response, request_data, request_id, 0x15);
        int accepted = get_device_type();
        AUDIO_LOAD_STATUS = load_status;
        if (accepted == 1)
            SendSystemLanguageInfoToSlave(load_status);
        (*(send_response_fn *)(context + 0x0c))(response, request_id);
        return;
    }
    case 0x3e: {
        LOG_AT(0);
        uintptr_t source = (uintptr_t)get_device_info();
        memcpy(response + 0x18, source + 0x10c6, 0xc0);
        data[0] = command;
        data[1] = 0xc9;
        memcpy(data + 2, (uintptr_t)(response + 0x18), 0xc0);
        (*(send_response_fn *)(context + 0x0c))(data, 0xc2);
        return;
    }
    default:
        LOG_AT(1);
        response[1] = 0xca;
        response[2] = 0x14;
        strcpy(response + 2, (void *)0x0009b98bu);
        break;
    }

    (*(send_response_fn *)(context + 0x0c))(response, response_length);
}
