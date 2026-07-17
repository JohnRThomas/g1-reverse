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
 *   bt_conn_set_security                     <= FUN_0008149a @ 0x0008149a
 *   bt_conn_get_security                     <= FUN_000814e2 @ 0x000814e2
 * address symbols (name @ address):
 *   rodata_9a52b                             @ 0x0009a52b
 *   rodata_9a53f                             @ 0x0009a53f
 *   rodata_9a56b                             @ 0x0009a56b
 *   rodata_9b229                             @ 0x0009b229
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_security_fail_cnt                 @ 0x20006a34
 *   g_gatt_discovery_flags                   @ 0x20006ab4
 *   g_ancs_active_conn                       @ 0x20006ab8
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full ABI-faithful reconstruction FUN_000184f0 @ 0x184f0. */
#include <stdint.h>

extern void log_message(uintptr_t format, ...);
extern uintptr_t get_device_info(void);
extern void ancs_discover_start(uint32_t connection);
extern void format_bt_addr_str(const void *connection, char *description);
extern void debug_print(uintptr_t format, ...);
extern int32_t is_battery_critical(void);
extern void sys_reboot(uint32_t enabled);
extern void FUN_0007c0a8(uint32_t milliseconds);
extern void bt_conn_set_security(uint32_t connection, uint32_t state);
extern uint32_t bt_conn_get_security(uint32_t connection);
extern uintptr_t FUN_00081526(uint32_t connection);
extern int32_t FUN_00086be4(void *destination, uintptr_t source, uint32_t length);

void ancs_security_changed(uint32_t connection, uint32_t level, int32_t error)
{
    char description[32];
    uintptr_t active_connection = FUN_00081526(connection);

    format_bt_addr_str((const void *)active_connection, description);
    if (error == 0) {
        if (*(volatile int32_t *)0x2000230cu > 2) {
            if (*(volatile uint32_t *)0x20007554u == 0)
                log_message(0x0009a52bu, 0x0009b229u, description, level);
            else
                debug_print(0x0009a52bu, 0x0009b229u, description, level);
        }

        if (bt_conn_get_security(connection) > 1u) {
            *(volatile uint32_t *)0x20006ab4u = 0;
            active_connection = FUN_00081526(connection);
            if (is_battery_critical() == 0) {
                uintptr_t device = get_device_info();
                if (*(volatile uint8_t *)(device + 0x1070u) == 1u) {
                    device = get_device_info();
                    if (FUN_00086be4((void *)(device + 0x1069u),
                                     active_connection, 7u) == 0)
                        ancs_discover_start(connection);
                }
            }
        }

        *(volatile uint8_t *)(*(volatile uintptr_t *)0x20006ab8u + 0x367u) = 0;
        *(volatile uint32_t *)0x20006a34u = 0;
        return;
    }

    if (*(volatile int32_t *)0x2000230cu > 2) {
        if (*(volatile uint32_t *)0x20007554u == 0)
            log_message(0x0009a53fu, 0x0009b229u, description, level, error);
        else
            debug_print(0x0009a53fu, 0x0009b229u, description, level, error);
    }

    for (;;) {
        int32_t attempts = *(volatile int32_t *)0x20006a34u + 1;
        *(volatile int32_t *)0x20006a34u = attempts;
        if (attempts < 10)
            break;

        if (*(volatile int32_t *)0x2000230cu > 0) {
            if (*(volatile uint32_t *)0x20007554u == 0)
                log_message(0x0009a56bu, 0x0009b229u);
            else
                debug_print(0x0009a56bu, 0x0009b229u);
        }
        FUN_0007c0a8(500u);
        sys_reboot(1u);
        log_message(0x0009a53fu, 0x0009b229u, description, level, error);
    }

    bt_conn_set_security(connection, 2u);
}
