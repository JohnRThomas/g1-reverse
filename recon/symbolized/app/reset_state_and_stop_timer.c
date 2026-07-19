#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084d36 @ 0x00084d36
 * public-name: reset_state_and_stop_timer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   app_event_manager_submit                 <= FUN_0004f770 @ 0x0004f770
 *   app_event_submit_power                   <= FUN_00063bcc @ 0x00063bcc
 *   power_manager_set_system_off_flag        <= FUN_00063c14 @ 0x00063c14
 *   reset_state_and_stop_timer               <= FUN_00084d36 @ 0x00084d36
 */
/* Reconstructed FUN_00084d36 @ 0x84d36  (parity: 300/300 trials, PROVEN) */

extern char *app_event_submit_power(void);
extern void app_event_manager_submit(void);
extern void power_manager_set_system_off_flag(int a);
void reset_state_and_stop_timer(void) {
    char *p = app_event_submit_power();
    *(volatile unsigned char*)(p + 8) = 0;
    app_event_manager_submit();
    power_manager_set_system_off_flag(5);
}
