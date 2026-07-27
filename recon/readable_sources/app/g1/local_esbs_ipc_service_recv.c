#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_esbs_ipc_recv_ctx__param_0025          [param_0025; G1-original]
 *   param_2          => struct g1_layout_esbs_ipc_msg__param_0026               [param_0026; G1-original]
 * Raw function identity: 0x00015960.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00015960 @ 0x00015960
 * public-name: local_esbs_ipc_service_recv
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_99133                             @ 0x00099133   [INLINED -- G6 literal batch]
 *   rodata_99152                             @ 0x00099152   [INLINED -- G6 literal batch]
 *   rodata_99228                             @ 0x00099228   [INLINED -- G6 literal batch]
 *   rodata_99297                             @ 0x00099297   [INLINED -- G6 literal batch]
 *   rodata_992e1                             @ 0x000992e1   [INLINED -- G6 literal batch]
 *   rodata_99b89                             @ 0x00099b89   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   device_info                              @ 0x200069fc
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_esb_notify_sync_substate               @ 0x20018d98
 */
/* local_esbs_ipc_service_recv @ 0x15960 / FUN_00015960 (CFG parity: 16/16, PROVEN) */
#include <stdint.h>
#include <string.h>
#include "../../../headers/g1_log.h"

extern void switch_to_dfu_mode(void *state);
extern int find_message_pool_entry_by_id(int);
extern void msg_queue_init(void);
extern void confirm_message(int);
extern void reset_esb_sync_state(uint32_t reason);
extern unsigned int set_device_sync_timestamp(unsigned long);
extern void firmware_function_0007c010(void *state);
extern void update_persist_task_status(void *context, uint32_t task);
extern void memset_bytes(void*, int, int);

#define LOG_LEVEL       (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define LOG_SINK        (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define MASTER_CONTEXT  (*(volatile uint8_t **)((unsigned long)&device_info) /*=0x200069fc*/)
#define EVEN_AI_STATE   (*(volatile uint8_t *)((unsigned long)&g_esb_notify_sync_substate) /*=0x20018d98*/)
#define LOG_TAG         ((unsigned long)"local_esbs_ipc_service_recv") /*=0x99b89*/

static uint32_t load_u32(const void *pointer)
{
    uint32_t value;
    __builtin_memcpy(&value, pointer, sizeof(value));
    return value;
}

static void store_u32(void *pointer, uint32_t value)
{
    __builtin_memcpy(pointer, &value, sizeof(value));
}

static inline __attribute__((always_inline)) void log_simple(uint32_t format)
{
    if (LOG_SINK == 0)
        log_message(format, LOG_TAG);
    else
        debug_print(format, LOG_TAG);
}

uint32_t local_esbs_ipc_service_recv(uint8_t *context,
                                     const uint8_t *packet)
{
    uint8_t received[22];
    uint32_t header;
    uint8_t command;
    uint8_t direction;
    uint8_t work_mode;
    uint8_t sequence;
    uint8_t *master;
    uint8_t *screen_state;
    uint32_t timestamp;
    uint32_t message_id;
    void *message;

    /* Raw code clears the stack record, then copies packet[11..31]. */
    store_u32(received, 0);
    memset_bytes(received + 4, 0, 18);
    __builtin_memcpy(received, packet + 11, 21);
    header = load_u32(received);
    command = (uint8_t)(header & 0x3fu);
    direction = (uint8_t)(header & 0xc0u);
    work_mode = received[1];
    sequence = received[6];

    if (sequence == context[0xda]) {
        if (LOG_LEVEL > 0)
            log_simple(((unsigned long)"%s(): slave recv same package\n") /*=0x99133*/);
        return 0;
    }
    if (sequence != (uint8_t)(context[0xda] + 1u) && LOG_LEVEL > 0)
        log_simple(((unsigned long)"%s(): ###############loss package new_data_pkg->package_id %d data_pkg->package_id %d\n") /*=0x99152*/);

    if (command == 1 && context[0xfe6] == 1) {
        context[0xda]++;
        if (LOG_LEVEL > 0)
            log_simple(0x000991a9u);
        return 0;
    }
    if (command == 2 && context[0xfe6] == 0) {
        context[0xda]++;
        if (LOG_LEVEL > 0)
            log_simple(0x000991cbu);
        return 0;
    }

    if (context[0xd5] == 9 || context[0xd5] == 11 || context[0xd5] == 10) {
        if ((direction == 0x80 && context[0xce] != 0) ||
            (direction == 0x40 && context[0xcf] != 0)) {
            context[0xda]++;
            if (LOG_LEVEL > 0)
                log_simple(direction == 0x80 ? 0x000991ecu : 0x00099209u);
            return 0;
        }
    } else if (context[0xd5] == 16 && context[0xce] != 0) {
        if (LOG_LEVEL > 0)
            log_simple(((unsigned long)"%s(): slave even ai recv down recving\n") /*=0x99228*/);
        context[0xda]++;
        return 0;
    }

    if (work_mode != 6 && work_mode != 0) {
        context[0xe9] = packet[3];
        context[0xea] = packet[4];
        if (command == 0) {
            master = (uint8_t *)MASTER_CONTEXT;
            screen_state = *(uint8_t **)(master + 0x100c);
            if (direction == 0x80 ||
                (work_mode == 16 && (uint8_t)(*screen_state - 6u) < 4u)) {
                uint8_t *alternate = *(uint8_t **)(context + 0x1024);
                if (context[0xcc] != packet[3] &&
                    alternate[0x200] != packet[3]) {
                    context[0xda]++;
                    if (LOG_LEVEL > 0)
                        log_simple(0x0009924fu);
                    return 0;
                }
            } else {
                uint8_t *alternate = *(uint8_t **)(context + 0x1028);
                if (context[0xcd] != packet[4] &&
                    alternate[0x200] != packet[4]) {
                    context[0xda]++;
                    if (LOG_LEVEL > 0)
                        log_simple(0x00099272u);
                    return 0;
                }
            }
        }
    }

    context[0xc9] = (uint8_t)((context[0xc9] & 0xc0u) | (packet[0] & 0x3fu));
    context[0xca] = packet[1];
    context[0xcb] = packet[2];
    timestamp = load_u32(packet + 7);
    set_device_sync_timestamp(timestamp);

    received[1] = context[0xd5];
    __builtin_memcpy(context + 0xd4, received, 21);
    context[0xee4] = (uint8_t)(received[0] >> 6);
    store_u32(*(void **)(context + 0xfec), timestamp);
    {
        uint8_t *mirror = *(uint8_t **)(context + 0xff4);
        uint32_t *mirror_timestamp = (uint32_t *)(mirror + 0x164);
        if (*mirror_timestamp != 0)
            *mirror_timestamp = timestamp;
    }
    context[0xeb] = (uint8_t)(received[0] >> 6);
    context[0xec] = context[0xd5];

    if ((received[16] & 4u) != 0) {
        msg_queue_init();
        context[0xe4] &= 0xfbu;
    }

    message_id = load_u32(received + 17);
    master = (uint8_t *)MASTER_CONTEXT;
    screen_state = *(uint8_t **)(master + 0x100c);
    switch (command) {
    case 10:
        if ((master[0x6de] & 4u) != 0)
            return 0;
        message = find_message_pool_entry_by_id(message_id);
        if (LOG_LEVEL > 0) {
            if (LOG_SINK == 0)
                log_message(((unsigned long)"%s(): ##########%s %d SYNC_DISPLAY_CMD_COMFIRM_NOTIFY_FIRST slave before\n") /*=0x99297*/, LOG_TAG, LOG_TAG, 0x2fdu);
            else
                debug_print(((unsigned long)"%s(): ##########%s %d SYNC_DISPLAY_CMD_COMFIRM_NOTIFY_FIRST slave before\n") /*=0x99297*/, LOG_TAG, LOG_TAG, 0x2fdu);
        }
        if (message != 0 && *((uint8_t *)message + 13) == 0)
            *((uint8_t *)message + 13) = 2;
        break;
    case 11:
        if ((master[0x6de] & 4u) != 0)
            return 0;
        message = find_message_pool_entry_by_id(message_id);
        if (LOG_LEVEL > 0) {
            if (LOG_SINK == 0)
                log_message(((unsigned long)"%s(): ##########%s %d SYNC_DISPLAY_CMD_COMFIRM_NOTIFY_END slave before\n") /*=0x992e1*/, LOG_TAG, LOG_TAG, 0x30au);
            else
                debug_print(((unsigned long)"%s(): ##########%s %d SYNC_DISPLAY_CMD_COMFIRM_NOTIFY_END slave before\n") /*=0x992e1*/, LOG_TAG, LOG_TAG, 0x30au);
        }
        if (message != 0 && *((uint8_t *)message + 13) == 2) {
            *((uint8_t *)message + 13) = 4;
            confirm_message(message_id);
            EVEN_AI_STATE = 0;
        }
        break;
    case 12:
        break;
    case 13:
        reset_esb_sync_state(0);
        *screen_state = 2;
        if (**(uint32_t **)(master + 0x1054) != 16)
            update_persist_task_status(master, 16);
        break;
    case 14: *screen_state = 4; break;
    case 15: *screen_state = 6; break;
    case 16: *screen_state = 11; master[0xdb] = 8; break;
    case 17: *screen_state = 14; break;
    case 18: *screen_state = 16; break;
    default:
        firmware_function_0007c010(context + 0x20);
        break;
    }

    if ((context[0xc9] & 0x3fu) == 3 &&
        (context[0xc9] & 0xc0u) == 0x80 && context[0xca] == 1)
        switch_to_dfu_mode(context + 0x68);
    return 0;
}
