#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000162ec @ 0x000162ec
 * public-name: local_ipc_service_recv
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed local_ipc_service_recv @ 0x162ec (uncatalogued Ghidra gap
 * 0x162d8..0x1655c; code 0x162ec..0x16520, literal pool 0x16520..0x1655c).
 *
 * Handler registered by main() for the IPC service id 1 ("cpuapp-hw-id");
 * dispatched from ipc0_ept_recv as handler(context, data + 1, length - 1).
 * The name is self-evidenced: every log line passes 0x00099b56
 * ("local_ipc_service_recv") as the "%s()" argument.
 */
#include <stdint.h>
#include "../../headers/g1_log.h"

extern int64_t uptime_ticks_get(void);
extern void FUN_0007c010(void *object);          /* tail thunk -> k_sem_give */
extern void app_msleep_thunk_a(uint32_t milliseconds);
extern int sys_reboot(int type);
extern void runtime_info_sync(void *context);
extern void checked_strncpy_zero_pad(void *destination, const void *source,
                                     unsigned int length,
                                     unsigned int destination_size);

#define LOG_LEVEL (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define LOG_SINK  (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define LOG_TAG   ((unsigned long)"local_ipc_service_recv") /*=0x99b56*/

static uint32_t load_u32(const void *pointer)
{
    uint32_t value;
    __builtin_memcpy(&value, pointer, sizeof(value));
    return value;
}

static uint16_t load_u16(const void *pointer)
{
    uint16_t value;
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

/* k_uptime_get(): ceil-convert the 32768 Hz tick counter to milliseconds. */
static uint64_t uptime_milliseconds(int64_t ticks)
{
    return (((uint64_t)ticks * 1000ULL) + 0x7fffULL) >> 15;
}

int local_ipc_service_recv(uint8_t *context, const uint8_t *packet, int length)
{
    uint64_t uptime;
    int64_t ticks;
    uint32_t value;
    uint32_t second;
    uint8_t *name;

    switch (packet[0]) {
    case 1:
        uptime_ticks_get();
        goto notify_ready;

    case 2:
        ticks = uptime_ticks_get();
        uptime = uptime_milliseconds(ticks);
        if (LOG_LEVEL > 1) {
            if (LOG_SINK == 0)
                goto uptime_log;
            debug_print(((unsigned long)"%s(): cpunet request send info uptime %lld\n") /*=0x995d9*/, LOG_TAG, uptime);
        }
    uptime_check:
        if (uptime >= 0x2711ULL) {
            if (LOG_LEVEL > 0) {
                if (LOG_SINK == 0)
                    goto reboot_log;
                debug_print(((unsigned long)"%s(): sys reboot because recv cpunet sync package\n") /*=0x99605*/, LOG_TAG);
            }
        reboot:
            app_msleep_thunk_a(500);
            sys_reboot(1);
            /* The shipped code has no return path here: it falls through
             * into the out-of-line log blocks below. */
        uptime_log:
            log_message(((unsigned long)"%s(): cpunet request send info uptime %lld\n") /*=0x995d9*/, LOG_TAG, uptime);
            goto uptime_check;
        reboot_log:
            log_message(((unsigned long)"%s(): sys reboot because recv cpunet sync package\n") /*=0x99605*/, LOG_TAG);
            goto reboot;
        }
        runtime_info_sync(context);
        return 0;

    case 3:
        ticks = uptime_ticks_get();
        value = load_u32(packet + 1);
        if (**(volatile uint8_t * volatile *)((unsigned long)&device_info) /*=0x200069fc*/ == 1) {
            store_u32(context + 0xfda, value);
            store_u16(context + 0xfde, load_u16(packet + 5));
        } else {
            store_u32(context + 0xfe0, value);
            store_u16(context + 0xfe4, load_u16(packet + 5));
        }
        if (LOG_LEVEL > 1) {
            uptime = uptime_milliseconds(ticks);
            if (LOG_SINK == 0)
                log_message(((unsigned long)"%s(): cpunet request update macaddr info uptime %lld bt macaddr esb_master_addr %02X esb_slave_addr %02X \n") /*=0x99638*/, LOG_TAG, uptime,
                            (uint32_t)context[3], (uint32_t)context[4]);
            else
                debug_print(((unsigned long)"%s(): cpunet request update macaddr info uptime %lld bt macaddr esb_master_addr %02X esb_slave_addr %02X \n") /*=0x99638*/, LOG_TAG, uptime,
                            (uint32_t)context[3], (uint32_t)context[4]);
        }
    notify_ready:
        if (*(volatile uint32_t *)(context + 0x10) == 0)
            FUN_0007c010(context + 8);
        return 0;

    case 4:
        store_u32(context + 0xfda, load_u32(packet + 1));
        store_u16(context + 0xfde, load_u16(packet + 5));
        store_u32(context + 0xfe0, load_u32(packet + 7));
        store_u16(context + 0xfe4, load_u16(packet + 0xb));
        return 0;

    case 6:
        if (context[0x1058] == 0)
            context[0x1058] = 1;
        if (LOG_LEVEL > 1) {
            if (LOG_SINK == 0)
                log_message(((unsigned long)"%s(): bt_ready\n") /*=0x996a3*/, LOG_TAG);
            else
                debug_print(((unsigned long)"%s(): bt_ready\n") /*=0x996a3*/, LOG_TAG);
        }
        if (*(volatile uint32_t *)(context + 0x10) == 0)
            FUN_0007c010(context + 8);
        name = (uint8_t *)((unsigned long)&g_2000ff4e) /*=0x2000ff4e*/;
        checked_strncpy_zero_pad(name, packet + 1,
                                 (unsigned int)(length - 1), 0x20u);
        name[0x1f] = 0;
        return 0;

    case 7:
        value = load_u32(packet + 1);
        *(volatile uint32_t *)((unsigned long)&g_200069f4) /*=0x200069f4*/ = value;
        second = load_u32(packet + 5);
        *(volatile uint32_t *)((unsigned long)&g_200069f0) /*=0x200069f0*/ = second;
        *(volatile uint32_t *)((unsigned long)&g_200069ec) /*=0x200069ec*/ = load_u32(packet + 9);
        *(volatile uint32_t *)((unsigned long)&g_battery_percent) /*=0x200069e8*/ = load_u32(packet + 0xd);
        if (context[0x108d] == 0)
            *(volatile uint32_t *)((unsigned long)&g_battery_percent) /*=0x200069e8*/ = 0x46;
        if (LOG_LEVEL > 1) {
            if (LOG_SINK == 0)
                log_message(((unsigned long)"%s(): IPC_RESP_CPUNET_ESB_PACKAGES %d %d %d %d\n") /*=0x996b3*/, LOG_TAG, value, second,
                            load_u32(packet + 9),
                            *(volatile uint32_t *)((unsigned long)&g_battery_percent) /*=0x200069e8*/);
            else
                debug_print(((unsigned long)"%s(): IPC_RESP_CPUNET_ESB_PACKAGES %d %d %d %d\n") /*=0x996b3*/, LOG_TAG, value, second,
                            load_u32(packet + 9),
                            *(volatile uint32_t *)((unsigned long)&g_battery_percent) /*=0x200069e8*/);
        }
        return 0;

    case 13:
        context[0x105a] = packet[1];
        return 0;

    default:
        if (LOG_LEVEL > 1) {
            if (LOG_SINK == 0)
                debug_print(((unsigned long)"%s(): sync fail! len: %d, data=%s\n\n") /*=0x996e3*/, LOG_TAG, length, packet);
            else
                log_message(((unsigned long)"%s(): sync fail! len: %d, data=%s\n\n") /*=0x996e3*/, LOG_TAG, length, packet);
        }
        return 0;
    }
}
