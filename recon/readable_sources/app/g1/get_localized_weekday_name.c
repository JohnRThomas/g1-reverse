#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d4b2 @ 0x0007d4b2
 * public-name: get_localized_weekday_name
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_ui_mode_flag_byte1                   <= FUN_00023ee0 @ 0x00023ee0
 *   get_localized_string_ptr                 <= FUN_000456fc @ 0x000456fc
 *   get_localized_weekday_name               <= FUN_0007d4b2 @ 0x0007d4b2
 */
/* Reconstructed FUN_0007d4b2 @ 0x7d4b2  (parity: 300/300 trials, PROVEN) */

extern int get_ui_mode_flag_byte1(void);
extern void get_localized_string_ptr(int a, int b);
void get_localized_weekday_name(int param_1) {
    int iVar1 = get_ui_mode_flag_byte1();
    if (iVar1 != 6) iVar1 = 2;
    get_localized_string_ptr(iVar1, param_1);
}
