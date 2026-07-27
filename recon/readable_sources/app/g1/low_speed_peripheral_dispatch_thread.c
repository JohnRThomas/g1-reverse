#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_g1_device_runtime_state__param_0027    [param_0027; G1-original]
 * Raw function identity: 0x0002a8d8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0002a8d8 @ 0x0002a8d8
 * public-name: low_speed_peripheral_dispatch_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   runtime_info_sync                        <= FUN_00016268 @ 0x00016268
 *   get_dashboard_startup_mode_field63       <= FUN_00016580 @ 0x00016580
 *   set_dashboard_startup_mode_field63       <= FUN_0001658c @ 0x0001658c
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   check_device_readiness                   <= FUN_000167b4 @ 0x000167b4
 *   get_ancs_conn_handle                     <= FUN_00019b2c @ 0x00019b2c
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   reset_all_usr_data                       <= FUN_0002316c @ 0x0002316c
 *   handle_box_placement_event               <= FUN_00025528 @ 0x00025528
 *   check_disp_onboarding                    <= FUN_00026a08 @ 0x00026a08
 *   check_bind_status                        <= FUN_00026b88 @ 0x00026b88
 *   check_charging_and_touch_flags           <= FUN_00026c28 @ 0x00026c28
 *   try_enter_low_power_mode                 <= FUN_00026c8c @ 0x00026c8c
 *   esb_send_command_and_wait_ack            <= FUN_00027448 @ 0x00027448
 *   check_sw0_status                         <= FUN_0002a868 @ 0x0002a868
 *   watchdog_feed_retry                      <= FUN_0002ae84 @ 0x0002ae84
 *   disable_watchdog                         <= FUN_0002aeb4 @ 0x0002aeb4
 *   update_persist_task_status_to_idle       <= FUN_0002c0e8 @ 0x0002c0e8
 *   check_ancs_inbox_flag_change             <= FUN_0002eb40 @ 0x0002eb40
 *   debounce_read_pending_flag_1             <= FUN_0002eb78 @ 0x0002eb78
 *   msg_queue_init                           <= FUN_00033c5c @ 0x00033c5c
 *   sys_reboot                               <= FUN_0004c0a8 @ 0x0004c0a8
 *   bt_conn_disconnect_by_state              <= FUN_00056a68 @ 0x00056a68
 *   k_uptime_get_1                           <= FUN_0007cb2c @ 0x0007cb2c
 *   k_msleep                                 <= FUN_0007cb8e @ 0x0007cb8e
 *   resolve_not_disturb_context              <= FUN_0007cbae @ 0x0007cbae
 *   set_shutdown_flag                        <= FUN_0007cbfe @ 0x0007cbfe
 *   errno_wrapped_tick_call                  <= FUN_0007d1d6 @ 0x0007d1d6
 *   g1_recon_bt_conn_set_security            <= FUN_0008149a @ 0x0008149a
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_87d70                             @ 0x00087d70
 *   rodata_9fc8b                             @ 0x0009fc8b   [INLINED -- G6 literal batch]
 *   rodata_a1914                             @ 0x000a1914   [INLINED -- G6 literal batch]
 *   rodata_a193c                             @ 0x000a193c   [INLINED -- G6 literal batch]
 *   rodata_a1962                             @ 0x000a1962   [INLINED -- G6 literal batch]
 *   rodata_a19c0                             @ 0x000a19c0   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_flash_crc_active_flag                  @ 0x2000302c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_flash_crc_skip_watchdog_flag           @ 0x20018d90
 *   g_box_lid_or_charge_state                @ 0x20018d91
 */
/* Full reconstruction low_speed_peripheral_dispatch_thread @ 0x2a8d8,
 * CFG-reviewed extent 1012 bytes (live tail through 0x2acca).
 * CFG_VERIFY_PREFIX_FIRST CFG_VERIFY_PREFIX_K=240
 */
#include <stdint.h>
#include "../../../headers/g1_log.h"

extern void change_work_mode_to(uint32_t);
extern void update_persist_task_status_to_idle(uint8_t *);
extern int sync_to_slave(uint8_t *, uint32_t, uint32_t);
extern unsigned int get_ancs_conn_handle(void);
extern int g1_recon_bt_conn_set_security(int, uint32_t);
extern void fuel_gauge_update(uintptr_t, uint32_t);
extern uint32_t check_ancs_inbox_flag_change(void);
extern uint32_t debounce_read_pending_flag_1(void);
extern void check_bind_status(int, int, int);
extern void runtime_info_sync(uint8_t *);
extern uint32_t esb_send_command_and_wait_ack(uint8_t *, uint32_t, uint32_t);
extern void msg_queue_init(void);
extern void handle_box_placement_event(void);
extern void disable_watchdog(void);
extern void watchdog_feed_retry(void);
extern void errno_wrapped_tick_call(uint8_t *, uint32_t);
extern unsigned long long k_uptime_get_1(void);
extern void k_msleep(uint32_t);
extern uint32_t sys_reboot(uint32_t);
extern void wait_for_event(uint32_t, uint32_t);
extern int get_dashboard_startup_mode_field63(void);
extern void check_device_readiness(void);
extern void set_dashboard_startup_mode_field63(uint32_t);
extern uint32_t check_charging_and_touch_flags(void);
extern void try_enter_low_power_mode(void);
extern void check_work_mode(uint32_t, uint32_t, uint32_t);
extern void check_disp_onboarding(uint32_t);
extern void bt_conn_disconnect_by_state(int, uint32_t);
extern uintptr_t get_device_info(void);
extern void set_shutdown_flag(uintptr_t, uint32_t);
extern void reset_all_usr_data(unsigned char *, int);
extern void check_sw0_status(void);
extern void resolve_not_disturb_context(void);

static inline uint8_t rd8(uint8_t *p, unsigned o) { return *(volatile uint8_t *)(p + o); }
static inline void wr8(uint8_t *p, unsigned o, uint8_t v) { *(volatile uint8_t *)(p + o) = v; }
static inline uint32_t rd32(uint8_t *p, unsigned o) { return *(volatile uint32_t *)(p + o); }
static inline void wr32(uint8_t *p, unsigned o, uint32_t v) { *(volatile uint32_t *)(p + o) = v; }

void low_speed_peripheral_dispatch_thread(uint8_t *ctx)
{
    volatile int *const log_level = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    volatile uint8_t *const phase_hold = (volatile uint8_t *)((unsigned long)&g_box_lid_or_charge_state) /*=0x20018d91*/;
    uint8_t tick = 0;
    int8_t connected_runs = 0;

    change_work_mode_to(3);
    update_persist_task_status_to_idle(ctx);
    if (*log_level > 1) {
        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            log_message(((unsigned long)"%s(): #enter\n") /*=0x9fc8b*/, ((unsigned long)"low_speed_peripheral_dispatch_thread") /*=0xa19c0*/);
        else
            debug_print(((unsigned long)"%s(): #enter\n") /*=0x9fc8b*/, ((unsigned long)"low_speed_peripheral_dispatch_thread") /*=0xa19c0*/);
    }
    *(volatile uint16_t *)(ctx + 0xfc4) = 0x8000;
    *(volatile uint16_t *)(ctx + 0xfc0) = 0;
    if (rd8(ctx, 0) == 1)
        sync_to_slave(ctx, rd8(ctx, 0xfea) == 12 ? 4 : 5, 0);

    for (;;) {
        tick = (uint8_t)(tick + 1);
        if (tick % 5 == 0) {
            int connection = get_ancs_conn_handle();
            if (connection == 0 || rd8(ctx, 0xae2) == 0 ||
                rd8(ctx, 0xae3) == 0 || rd32(ctx, 0x9b4) == 0) {
                connected_runs = 0;
            } else if (++connected_runs > 4) {
                int error = g1_recon_bt_conn_set_security(connection, 2);
                if (error != 0 && *log_level > 2) {
                    if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                        log_message(((unsigned long)"%s(): Failed to set security (err %d)\n\n") /*=0xa1914*/, ((unsigned long)"low_speed_peripheral_dispatch_thread") /*=0xa19c0*/, error);
                    else
                        debug_print(((unsigned long)"%s(): Failed to set security (err %d)\n\n") /*=0xa1914*/, ((unsigned long)"low_speed_peripheral_dispatch_thread") /*=0xa19c0*/, error);
                }
                connected_runs = -5;
            }

            uint8_t a = rd8(ctx, 0xfc0), b = rd8(ctx, 0xfc1);
            wr8(ctx, 0xde, a <= b ? a : b);
            fuel_gauge_update(((unsigned long)&rodata_87d70) /*=0x87d70*/, 0);
            uint32_t power = check_ancs_inbox_flag_change();
            uint32_t thermal = debounce_read_pending_flag_1();
            uint32_t side = 0;

            check_bind_status(ctx, power, thermal);
            if (rd8(ctx, 0) == 1) {
                runtime_info_sync(ctx);
                if (connection != 0 && rd8(ctx, 0xae3) == 0 && rd32(ctx, 0x9b4) != 0 &&
                    (rd8(ctx, 0x6de) & 1)) {
                    wr8(ctx, 0xe4, rd8(ctx, 0xe4) | 3);
                    *phase_hold = 3;
                    side = 1;
                } else if (*phase_hold != 0) {
                    --*phase_hold;
                } else {
                    wr8(ctx, 0xe4, rd8(ctx, 0xe4) & 0xfcu);
                }
                int elapsed = sync_to_slave(ctx, 12, 0);
                if (elapsed < 500 && (rd8(ctx, 0xe4) & 4)) {
                    msg_queue_init();
                    wr8(ctx, 0xe4, rd8(ctx, 0xe4) & 0xfbu);
                }
            } else {
                if (connection != 0 && rd8(ctx, 0xae3) == 0 && rd32(ctx, 0x9b4) != 0) {
                    *phase_hold = 3;
                    wr8(ctx, 0x6de, rd8(ctx, 0x6de) | 1);
                    side = 1;
                } else if (*phase_hold != 0) {
                    --*phase_hold;
                } else {
                    wr8(ctx, 0x6de, rd8(ctx, 0x6de) & 0xfeu);
                }
                if ((rd8(ctx, 0xe4) ^ rd8(ctx, 0x6de)) & 1)
                    wr8(ctx, 0x6df, (uint8_t)(rd8(ctx, 0x6df) + 1));
                uint32_t elapsed = esb_send_command_and_wait_ack(ctx, 1, 0);
                if (elapsed < 500 && (rd8(ctx, 0x6de) & 4)) {
                    msg_queue_init();
                    wr8(ctx, 0x6de, rd8(ctx, 0x6de) & 0xfbu);
                    wr8(ctx, 0xe4, rd8(ctx, 0xe4) & 0xfbu);
                }
            }

            handle_box_placement_event();
            while (rd8(ctx, 1) == 1) {
                disable_watchdog();
                if (rd8(ctx, 0) == 1)
                    errno_wrapped_tick_call(ctx, rd32(ctx, 0xfec));
                if ((int64_t)(k_uptime_get_1() -
                              *(volatile uint64_t *)(ctx + 0x1060)) > 0x927bf) {
                    if (*log_level > 0) {
                        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
                            debug_print(((unsigned long)"%s(): reboot because dfu exceed time\n") /*=0xa193c*/, ((unsigned long)"low_speed_peripheral_dispatch_thread") /*=0xa19c0*/);
                        else
                            log_message(((unsigned long)"%s(): reboot because dfu exceed time\n") /*=0xa193c*/, ((unsigned long)"low_speed_peripheral_dispatch_thread") /*=0xa19c0*/);
                    }
                    for (;;) {
                        k_msleep(500);
                        uint32_t printed = sys_reboot(1);
                        log_message(printed);
                    }
                }
                wait_for_event(((unsigned long)&rodata_28000) /*=0x28000*/, 0);
            }
            if (*(volatile uint8_t *)((unsigned long)&g_flash_crc_active_flag) /*=0x2000302c*/ == 0)
                disable_watchdog();
            else if (*(volatile uint8_t *)((unsigned long)&g_flash_crc_skip_watchdog_flag) /*=0x20018d90*/ == 0)
                watchdog_feed_retry();
            if (rd8(ctx, 0) == 1)
                errno_wrapped_tick_call(ctx, rd32(ctx, 0xfec));
            if (get_dashboard_startup_mode_field63() != 0 && (int64_t)k_uptime_get_1() >= 60000) {
                check_device_readiness();
                set_dashboard_startup_mode_field63(0);
            }
            if (*log_level > 1) {
                uint32_t mode = rd8(ctx, 0xfea);
                uint32_t value = check_charging_and_touch_flags();
                if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                    log_message(((unsigned long)"%s(): Global Working Mode: %d get_glasses_ble_status %d ble_is_connected %d\n") /*=0xa1962*/, ((unsigned long)"low_speed_peripheral_dispatch_thread") /*=0xa19c0*/, mode, value, side);
                else
                    debug_print(((unsigned long)"%s(): Global Working Mode: %d get_glasses_ble_status %d ble_is_connected %d\n") /*=0xa1962*/, ((unsigned long)"low_speed_peripheral_dispatch_thread") /*=0xa19c0*/, mode, value, side);
            }
            try_enter_low_power_mode();
            check_work_mode(power, thermal, side);
            check_disp_onboarding(power);
            if (connection != 0 && rd8(ctx, 0x1068) == 0 &&
                (uint32_t)k_uptime_get_1() - rd32(ctx, 0xae4) > 30000 && rd8(ctx, 1) != 1) {
                wr32(ctx, 0xae4, (uint32_t)k_uptime_get_1());
                bt_conn_disconnect_by_state(connection, 0x13);
            }
            if (rd8(ctx, 0x108e) != 0) {
                wr8(ctx, 0x108e, 0);
                set_shutdown_flag(get_device_info(), 0);
                reset_all_usr_data(ctx, 1);
            }
            check_sw0_status();
            tick = 0;
        }
        resolve_not_disturb_context();
        if (*(volatile uint8_t *)((unsigned long)&g_flash_crc_skip_watchdog_flag) /*=0x20018d90*/ == 0)
            watchdog_feed_retry();
        wait_for_event(0x199a, 0);
    }
}
