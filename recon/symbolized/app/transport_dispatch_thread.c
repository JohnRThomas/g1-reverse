#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002a4f4 @ 0x0002a4f4
 * public-name: transport_dispatch_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   init_nfc_comm                            <= FUN_0002560c @ 0x0002560c
 *   ipc_service_send_with_retry              <= FUN_0002563c @ 0x0002563c
 *   set_delay_deadline                       <= FUN_0002a4d8 @ 0x0002a4d8
 *   transport_dispatch_thread                <= FUN_0002a4f4 @ 0x0002a4f4
 *   set_pending_state_flag                   <= FUN_0002eb28 @ 0x0002eb28
 *   periodic_check_run                       <= FUN_0003271c @ 0x0003271c
 *   arm_timeout_10s                          <= FUN_00032c0c @ 0x00032c0c
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   init_serial_comm                         <= FUN_00033340 @ 0x00033340
 *   k_uptime_get_1                           <= FUN_0007cb2c @ 0x0007cb2c
 *   z_impl_k_sem_init                        <= FUN_00086534 @ 0x00086534
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_a1895                             @ 0x000a1895   [INLINED -- G6 literal batch]
 *   g_delay_deadline_ticks                   @ 0x200040c8
 *   g_misc_dispatch_ctx                      @ 0x20007b00
 *   g_misc_dispatch_pending_flag             @ 0x20018d88
 *   g_low_power_mode_enabled                 @ 0x20018d94
 */
/* Full reconstruction FUN_0002a4f4 @ 0x2a4f4, exact extent 320 bytes.
 * CFG_VERIFY_PREFIX_FIRST */
#include <stdint.h>
#include "../../headers/g1_log.h"

extern int z_impl_k_sem_init(uintptr_t object, uint32_t flags, uint32_t count);
extern uintptr_t get_device_info(void);
extern void set_delay_deadline(uint32_t delay);
extern void arm_timeout_10s(void);
extern void wait_for_event(uint32_t ticks, uint32_t flags);
extern uint64_t is_battery_critical(void);
extern int k_sem_take(uintptr_t object, uint32_t high,
                             uint32_t timeout, uint32_t flags);
extern uint64_t k_uptime_get_1(void);
extern void ipc_service_send_with_retry(uint8_t *status);
extern int init_nfc_comm(void);
extern void set_pending_state_flag(uint32_t channel, uint32_t enabled);
extern int init_serial_comm(void);
extern void periodic_check_run(void);

void transport_dispatch_thread(uint32_t inherited_stack, uint32_t packed_status,
                  uint32_t inherited_r2, uint32_t inherited_r3)
{
    volatile uint8_t *const initialized = (volatile uint8_t *)((unsigned long)&g_misc_dispatch_pending_flag) /*=0x20018d88*/;
    volatile uint64_t *const deadline = (volatile uint64_t *)((unsigned long)&g_delay_deadline_ticks) /*=0x200040c8*/;
    volatile uint8_t *const channels_stopped = (volatile uint8_t *)((unsigned long)&g_low_power_mode_enabled) /*=0x20018d94*/;
    unsigned attempts = 0;

    (void)inherited_stack;
    (void)inherited_r2;
    (void)inherited_r3;
    int init_result = z_impl_k_sem_init(((unsigned long)&g_misc_dispatch_ctx) /*=0x20007b00*/, 0, 10);
    uint32_t stale_r2 = 10;
    if (init_result == 0) {
        *initialized = 1;
        stale_r2 = 1;
    }
    log_message(((unsigned long)"[csh_debug_nfc] g_nfcMsgSemInitOk is %d \n") /*=0xa1895*/, (uint32_t)*initialized, stale_r2, ((unsigned long)&g_misc_dispatch_pending_flag) /*=0x20018d88*/);

    for (;;) {
        if (*(volatile uint8_t *)(get_device_info() + 1) == 8) {
            set_delay_deadline(10000);
            arm_timeout_10s();
            wait_for_event(0x667, 0);
            continue;
        }
        if (*(volatile uint8_t *)(get_device_info() + 1) == 1) {
            wait_for_event(((unsigned long)&rodata_28000) /*=0x28000*/, 0);
            continue;
        }

        uint64_t state = is_battery_critical();
        if ((uint32_t)state == 1) {
            int active = init_nfc_comm();
            if (*(volatile uint8_t *)(get_device_info() + 0x1088) == 1)
                active = init_serial_comm();
            wait_for_event(0x1334, 0);
            if (active == 0)
                periodic_check_run();
            wait_for_event(0x1334, 0);
            continue;
        }

        int wait_result = k_sem_take(((unsigned long)&g_misc_dispatch_ctx) /*=0x20007b00*/,
                                             (uint32_t)(state >> 32),
                                             0x18000, 0);
        if (wait_result != 0) {
            if (*channels_stopped == 0 &&
                *(volatile uint8_t *)(get_device_info() + 1) != 8) {
                uint64_t then = *deadline;
                uint64_t first_now = k_uptime_get_1();
                uint64_t second_now = k_uptime_get_1();
                if (then < second_now && first_now - then >= 3001) {
                    set_pending_state_flag(0, 0);
                    set_pending_state_flag(1, 0);
                    *channels_stopped = 0;
                }
            }
            continue;
        }

        uint8_t status = (uint8_t)(packed_status >> 24);
        uint64_t now = k_uptime_get_1();
        if (*deadline < now)
            set_delay_deadline(0);
        ipc_service_send_with_retry(&status);
        if (status & 0x20) {
            init_nfc_comm();
            set_pending_state_flag(0, 1);
            attempts = 0;
        } else if (++attempts >= 10) {
            set_pending_state_flag(0, 1);
            attempts = 0;
        }
    }
}
