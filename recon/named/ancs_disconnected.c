/* readable reconstruction; identity: FUN_00018adc @ 0x00018adc
 * public-name: ancs_disconnected
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   format_bt_addr_str                       <= FUN_00018334 @ 0x00018334
 *   ancs_cancel_timers                       <= FUN_00018ab0 @ 0x00018ab0
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   bt_conn_get_field_0x90                   <= FUN_00081526 @ 0x00081526
 * address symbols (name @ address):
 *   rodata_9a92a                             @ 0x0009a92a   [INLINED -- G6 literal batch]
 *   rodata_9b1c8                             @ 0x0009b1c8   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_active_conn                       @ 0x20006ab8
 *   g_ancs_conn                              @ 0x20007518
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full ABI-faithful reconstruction ancs_disconnected @ 0x18adc. */
#include <stdint.h>

extern void log_message(uintptr_t format, ...);
extern uint64_t get_device_info(void);
extern void format_bt_addr_str(const void *connection, char *description);
extern void ancs_cancel_timers(void);
extern void debug_print(uintptr_t format, ...);
extern void z_impl_k_sem_take(uint32_t object_low, uint32_t object_high,
                        uint32_t timeout_low, uint32_t timeout_high);
extern uintptr_t bt_conn_get_field_0x90(uint32_t connection);

void ancs_disconnected(uint32_t connection, uint32_t reason)
{
    char description[36];
    uintptr_t device_state = *(volatile uintptr_t *)0x20006ab8u;

    *(volatile uint8_t *)(device_state + 0x365u) = 0;
    *(volatile uint32_t *)0x20007518u = 0;

    uintptr_t active_connection = bt_conn_get_field_0x90(connection);
    format_bt_addr_str((const void *)active_connection, description);
    if (*(volatile int32_t *)0x2000230cu > 0) {
        if (*(volatile uint32_t *)0x20007554u == 0)
            log_message(0x0009a92au, 0x0009b1c8u, description, reason);
        else
            debug_print(0x0009a92au, 0x0009b1c8u, description, reason);
    }

    *(volatile uint8_t *)(*(volatile uintptr_t *)0x20006ab8u + 0x367u) = 0;
    for (;;) {
        uint64_t device = get_device_info();
        if (*(volatile uint32_t *)((uintptr_t)(uint32_t)device + 0x9b4u) == 0)
            break;

        device = get_device_info();
        z_impl_k_sem_take((uint32_t)device + 0x9acu, (uint32_t)(device >> 32),
                     UINT32_MAX, UINT32_MAX);
    }

    ancs_cancel_timers();
}
