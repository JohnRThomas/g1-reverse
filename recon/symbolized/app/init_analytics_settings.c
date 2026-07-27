#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c360 @ 0x0007c360
 * public-name: init_analytics_settings
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   load_sys_setting                         <= FUN_00022bd0 @ 0x00022bd0
 *   load_usr_setting                         <= FUN_00022e78 @ 0x00022e78
 *   load_burial_point                        <= FUN_000230e0 @ 0x000230e0
 *   init_analytics_settings                  <= FUN_0007c360 @ 0x0007c360
 *   reset_countdown_timer_default            <= FUN_0007d1b8 @ 0x0007d1b8
 */
/* Reconstructed FUN_0007c360 @ 0x7c360  (parity: 300/300 trials, PROVEN) */

extern int load_sys_setting(unsigned int);
extern int load_usr_setting(int);
extern int load_burial_point(int);
extern int get_device_info(void);
extern void reset_countdown_timer_default(int);
int init_analytics_settings(int param_1)
{
    int iVar1 = load_sys_setting(param_1);
    if (iVar1 == 0 && (iVar1 = load_usr_setting(param_1)) == 0 &&
        (iVar1 = load_burial_point(param_1)) == 0) {
        int r = get_device_info();
        reset_countdown_timer_default(*(int*)(r + 0xff0));
    }
    return 0;
}
