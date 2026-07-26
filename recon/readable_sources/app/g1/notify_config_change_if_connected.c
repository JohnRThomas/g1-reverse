#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00017e84 @ 0x00017e84
 * public-name: notify_config_change_if_connected
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   notify_config_change_if_connected        <= FUN_00017e84 @ 0x00017e84
 *   get_ancs_conn_handle                     <= FUN_00019b2c @ 0x00019b2c
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   gatt_notify_config_change                <= FUN_0004f518 @ 0x0004f518
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 * address symbols (name @ address):
 *   rodata_9a155                             @ 0x0009a155   [INLINED -- G6 literal batch]
 *   g_settings_notify_mutex                  @ 0x20006a1c
 */
/* Reconstructed FUN_00017e84 @ 0x17e84  (parity: 300/300 trials, PROVEN) */
extern int get_ancs_conn_handle(void);
extern long long is_battery_critical(void);
extern int get_device_info(void);
extern void k_mutex_lock(unsigned,unsigned,unsigned,unsigned);
extern int gatt_notify_config_change(int,unsigned,unsigned);
extern void k_mutex_unlock(unsigned);
extern void log_message(unsigned,int,unsigned);
unsigned notify_config_change_if_connected(unsigned param_1, unsigned param_2){
    int r6 = get_ancs_conn_handle();
    long long uVar3 = is_battery_critical();
    int r4;
    if ((int)uVar3 != 0) goto L_work;
    if (r6 == 0) goto L_dc;
    {
        int t = get_device_info();
        if (*(char*)(t + 0xae3) != 0) goto L_dc;
        t = get_device_info();
        if (*(int*)(t + 0x9b4) == 0) goto L_dc;
    }
L_work:
    k_mutex_lock(((unsigned long)&g_settings_notify_mutex) /*=0x20006a1c*/, (unsigned)((unsigned long long)uVar3 >> 32), 0xffffffff, 0xffffffff);
    r4 = gatt_notify_config_change(0, param_1, param_2);
    k_mutex_unlock(((unsigned long)&g_settings_notify_mutex) /*=0x20006a1c*/);
    if (r4 == 0) return 0;
    log_message(((unsigned long)"Failed to send data over BLE connection: ret %d len %d \n") /*=0x9a155*/, r4, param_2);
    goto L_dc;
L_dc:
    r4 = -1;
    return (unsigned)r4;
}
