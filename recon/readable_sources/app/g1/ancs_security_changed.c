#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000184f0 @ 0x000184f0
 * public-name: ancs_security_changed
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   ancs_discover_start                      <= FUN_000182c8 @ 0x000182c8
 *   format_bt_addr_str                       <= FUN_00018334 @ 0x00018334
 *   ancs_security_changed                    <= FUN_000184f0 @ 0x000184f0
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   sys_reboot                               <= FUN_0004c0a8 @ 0x0004c0a8
 *   k_msleep_ticks32768_d                    <= FUN_0007c0a8 @ 0x0007c0a8
 *   g1_recon_bt_conn_set_security            <= FUN_0008149a @ 0x0008149a
 *   bt_conn_get_security                     <= FUN_000814e2 @ 0x000814e2
 *   bt_conn_get_field_0x90                   <= FUN_00081526 @ 0x00081526
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   rodata_9a52b                             @ 0x0009a52b   [INLINED -- G6 literal batch]
 *   rodata_9a53f                             @ 0x0009a53f   [INLINED -- G6 literal batch]
 *   rodata_9a56b                             @ 0x0009a56b   [INLINED -- G6 literal batch]
 *   rodata_9b229                             @ 0x0009b229   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_security_fail_cnt                 @ 0x20006a34
 *   g_gatt_discovery_flags                   @ 0x20006ab4
 *   g_ancs_active_conn                       @ 0x20006ab8
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full ABI-faithful reconstruction FUN_000184f0 @ 0x184f0. */
#include <stdint.h>
#include "../../../headers/g1_log.h"

extern uintptr_t get_device_info(void);
extern void ancs_discover_start(uint32_t connection);
extern void format_bt_addr_str(const void *connection, char *description);
extern int32_t is_battery_critical(void);
extern void sys_reboot(uint32_t enabled);
extern void k_msleep_ticks32768_d(int);
extern void g1_recon_bt_conn_set_security(uint32_t connection, uint32_t state);
extern uint32_t bt_conn_get_security(uint32_t connection);
extern uintptr_t bt_conn_get_field_0x90(uint32_t connection);
extern int32_t memcmp(void *destination, uintptr_t source, uint32_t length);

void ancs_security_changed(uint32_t connection, uint32_t level, int32_t error)
{
    char description[32];
    uintptr_t active_connection = bt_conn_get_field_0x90(connection);

    format_bt_addr_str((const void *)active_connection, description);
    if (error == 0) {
        if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
            if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                log_message(((unsigned long)"%s(): %s level %u\n\n") /*=0x9a52b*/, ((unsigned long)"ancs_security_changed") /*=0x9b229*/, description, level);
            else
                debug_print(((unsigned long)"%s(): %s level %u\n\n") /*=0x9a52b*/, ((unsigned long)"ancs_security_changed") /*=0x9b229*/, description, level);
        }

        if (bt_conn_get_security(connection) > 1u) {
            *(volatile uint32_t *)((unsigned long)&g_gatt_discovery_flags) /*=0x20006ab4*/ = 0;
            active_connection = bt_conn_get_field_0x90(connection);
            if (is_battery_critical() == 0) {
                uintptr_t device = get_device_info();
                if (*(volatile uint8_t *)(device + 0x1070u) == 1u) {
                    device = get_device_info();
                    if (memcmp((void *)(device + 0x1069u),
                                     active_connection, 7u) == 0)
                        ancs_discover_start(connection);
                }
            }
        }

        *(volatile uint8_t *)(*(volatile uintptr_t *)((unsigned long)&g_ancs_active_conn) /*=0x20006ab8*/ + 0x367u) = 0;
        *(volatile uint32_t *)((unsigned long)&g_ancs_security_fail_cnt) /*=0x20006a34*/ = 0;
        return;
    }

    if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            log_message(((unsigned long)"%s(): Security failed: %s level %u err %d\n\n") /*=0x9a53f*/, ((unsigned long)"ancs_security_changed") /*=0x9b229*/, description, level, error);
        else
            debug_print(((unsigned long)"%s(): Security failed: %s level %u err %d\n\n") /*=0x9a53f*/, ((unsigned long)"ancs_security_changed") /*=0x9b229*/, description, level, error);
    }

    for (;;) {
        int32_t attempts = *(volatile int32_t *)((unsigned long)&g_ancs_security_fail_cnt) /*=0x20006a34*/ + 1;
        *(volatile int32_t *)((unsigned long)&g_ancs_security_fail_cnt) /*=0x20006a34*/ = attempts;
        if (attempts < 10)
            break;

        if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
            if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                log_message(((unsigned long)"%s(): reboot because Security failed exceed 10 times, so reboot\r\n\n") /*=0x9a56b*/, ((unsigned long)"ancs_security_changed") /*=0x9b229*/);
            else
                debug_print(((unsigned long)"%s(): reboot because Security failed exceed 10 times, so reboot\r\n\n") /*=0x9a56b*/, ((unsigned long)"ancs_security_changed") /*=0x9b229*/);
        }
        k_msleep_ticks32768_d(500u);
        sys_reboot(1u);
        log_message(((unsigned long)"%s(): Security failed: %s level %u err %d\n\n") /*=0x9a53f*/, ((unsigned long)"ancs_security_changed") /*=0x9b229*/, description, level, error);
    }

    g1_recon_bt_conn_set_security(connection, 2u);
}
