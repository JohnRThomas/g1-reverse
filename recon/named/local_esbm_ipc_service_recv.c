/* readable reconstruction; identity: FUN_00016bf0 @ 0x00016bf0
 * public-name: local_esbm_ipc_service_recv
 * durable-map: recon/catalogs/function_names_app.json
 * provenance: uncatalogued by Ghidra (gap 0x16bc4..0x16eb8).  0x16bc4..0x16bef
 *   is change_work_mode_to's literal pool; the code extent is
 *   0x16bf0..0x16e88 (0x298 = 664 B, "push {r3,r4,r5,lr}" through the
 *   12-entry tbh switch to the shared "movs r0,#0; pop" exit) and
 *   0x16e88..0x16eb8 is its own literal pool.
 * identity evidence: every log line passes 0x00099b6d, the C string
 *   "local_esbm_ipc_service_recv", as the "%s()" argument.  main() installs
 *   this entry as the handler of IPC service id 6 ("cpunet-esbm-cpu-sync").
 */
/* Reconstructed local_esbm_ipc_service_recv @ 0x16bf0 (uncatalogued Ghidra gap
 * 0x16bc4..0x16eb8; code 0x16bf0..0x16e88, literal pool 0x16e88..0x16eb8).
 *
 * Handler registered by main() for the IPC service id 6
 * ("cpunet-esbm-cpu-sync"); dispatched from ipc0_ept_recv as
 * handler(context, data + 1, length - 1).  The name is self-evidenced: every
 * log line passes 0x00099b6d ("local_esbm_ipc_service_recv") as "%s()".
 */
#include <stdint.h>
#include "../headers/g1_log.h"

extern void msg_queue_init(void);
extern void msg_content_decrement_timer(void);
extern void set_message_pending_state(uint32_t state);
extern void set_shutdown_flag(void *context, uint32_t flag);
extern void get_ui_mode_flag2(void);
extern void update_persist_task_status_to_idle(void *context);
extern void change_work_mode_to(uint32_t mode);
extern void SlaveDoubleClickEventInject(void);
extern void *get_message_entry(uint32_t id);
extern void *pt_queue_get_free_slot(void);
extern void device_info_set_mode(uint32_t mode);
extern void reset_esb_sync_state(uint32_t reason);
extern void FUN_0007c010(void *object);          /* tail thunk -> k_sem_give */

#define LOG_LEVEL   (*(volatile int32_t *)0x2000230cUL)
#define LOG_SINK    (*(volatile int32_t *)0x20007554UL)
#define LOG_TAG     0x00099b6dUL
#define DEVICE_INFO (*(volatile uint8_t * volatile *)0x200069fcUL)

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

static void store_u16(void *pointer, uint16_t value)
{
    __builtin_memcpy(pointer, &value, sizeof(value));
}

static uint16_t load_u16(const void *pointer)
{
    uint16_t value;
    __builtin_memcpy(&value, pointer, sizeof(value));
    return value;
}

int local_esbm_ipc_service_recv(uint8_t *context, const uint8_t *packet)
{
    uint32_t command = packet[0] & 0x3fu;
    uint8_t *entry;
    uint8_t *slot;
    uint8_t *screen;

    if (command != 0 && (command - 0xbu) > 1u) {
        uint8_t sequence = packet[0x15];

        if (*(volatile uint8_t *)0x2000ff4aUL == sequence)
            return 0;
        *(volatile uint8_t *)0x2000ff4aUL = sequence;

        context[0xfcf] = context[0x6cd];
        context[0xfd0] = context[0x6ce];
        context[0xfd1] = context[0x6cf];
        context[0xfc1] = context[0x6d0];
        store_u32(context + 0xfe0, load_u32(context + 0x6d8));
        store_u16(context + 0xfe4, load_u16(context + 0x6dc));
        __builtin_memcpy(context + 0x6cc, packet, 22);
        if ((packet[0x12] & 4u) != 0) {
            msg_queue_init();
            context[0x6de] &= (uint8_t)~4u;
        }
    }

    switch (packet[0] & 0x3fu) {
    case 4:
        if (DEVICE_INFO[0xd5] == 4) {
            msg_content_decrement_timer();
            set_message_pending_state(DEVICE_INFO[0xdd] != 0 ? 6u : 0u);
        }
        __atomic_fetch_or((volatile uint32_t *)0x20007b34UL, 2u,
                          __ATOMIC_SEQ_CST);
        set_shutdown_flag(context, 1);
        if (context[0xee4] == 2)
            get_ui_mode_flag2();
        update_persist_task_status_to_idle(context);
        return 0;

    case 5:
        set_shutdown_flag(context, 1);
        change_work_mode_to(7);
        return 0;

    case 7:
        set_shutdown_flag(context, 1);
        context[0xfea] = 0xc;
        goto shutdown_tail;

    case 8:
        context[0xfea] = 0xa;
    shutdown_tail:
        store_u32(context + 0x104c, 3);
        FUN_0007c010(context + 0x80);
        return 0;

    case 6:
        if (LOG_LEVEL > 2) {
            if (LOG_SINK == 0)
                log_message(0x00099789UL, LOG_TAG);
            else
                debug_print(0x00099789UL, LOG_TAG);
        }
        SlaveDoubleClickEventInject();
        return 0;

    case 9:
        *(volatile uint8_t *)0x2000ff4dUL = 1;
        return 0;

    case 11:
        if (((DEVICE_INFO[0xe4] & 4u) |
             *(volatile uint8_t *)0x20018d8eUL) != 0)
            return 0;
        entry = get_message_entry(packet[0xd]);
        if (entry == 0 || entry[0xe] != 0)
            return 0;
        if (load_u32(packet + 9) == load_u32(entry + 8) &&
            load_u32(packet + 1) == load_u32(entry) &&
            entry[0xd] == 1)
            return 0;
        __builtin_memcpy(entry, packet + 1, 0xda);
        entry[0xd] = 1;
        return 0;

    case 12:
        if (((DEVICE_INFO[0xe4] & 4u) |
             *(volatile uint8_t *)0x20018d8eUL) != 0)
            return 0;
        slot = pt_queue_get_free_slot();
        if (slot == 0 || slot[0xe] != 0 || slot[0xd] == 3)
            return 0;
        __builtin_memcpy(slot + 0xda, packet + 1, 0xda);
        slot[0xd] = 3;
        return 0;

    case 13:
        if (LOG_LEVEL > 2) {
            if (LOG_SINK == 0)
                log_message(0x000997b2UL, LOG_TAG);
            else
                debug_print(0x000997b2UL, LOG_TAG);
        }
        if (context[0x6df] == 4) {
            if (LOG_LEVEL > 2) {
                if (LOG_SINK == 0)
                    log_message(0x000997d9UL, LOG_TAG,
                                (uint32_t)context[0x6e0]);
                else
                    debug_print(0x000997d9UL, LOG_TAG,
                                (uint32_t)context[0x6e0]);
            }
            screen = *(uint8_t * volatile *)(DEVICE_INFO + 0x1014);
            screen[2] = context[0x6e0];
            return 0;
        }
        if (context[0x6df] != 5)
            return 0;
        if (LOG_LEVEL > 2) {
            if (LOG_SINK == 0)
                log_message(0x00099805UL, LOG_TAG, (uint32_t)context[0x6e0]);
            else
                debug_print(0x00099805UL, LOG_TAG, (uint32_t)context[0x6e0]);
        }
        device_info_set_mode(context[0x6e0]);
        return 0;

    case 14:
        screen = *(uint8_t * volatile *)(DEVICE_INFO + 0x100c);
        if (screen[0] == 1)
            return 0;
        reset_esb_sync_state(0);
        screen = *(uint8_t * volatile *)(DEVICE_INFO + 0x100c);
        screen[0] = 1;
        return 0;

    case 15:
        screen = *(uint8_t * volatile *)(DEVICE_INFO + 0x100c);
        if (screen[0] != 4)
            return 0;
        screen[0] = 5;
        return 0;

    default:
        return 0;
    }
}
