#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_g1_ui_box_state__param_0018            [param_0018; G1-original]
 * Raw function identity: 0x000254a0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000254a0 @ 0x000254a0
 * public-name: update_box_presence_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   update_box_field_debounce                <= FUN_00025474 @ 0x00025474
 *   update_box_presence_flag                 <= FUN_000254a0 @ 0x000254a0
 * address symbols (name @ address):
 *   g_box_present_flag                       @ 0x20018c68
 */
/* Reconstructed FUN_000254a0 @ 0x254a0  (parity: 300/300 trials, PROVEN) */

extern int update_box_field_debounce(void);

void update_box_presence_flag(int param_1, unsigned char *param_2)
{
    int iVar1 = update_box_field_debounce();
    *param_2 = (iVar1 != 0);
    volatile unsigned char *flagp = (volatile unsigned char*)((unsigned long)&g_box_present_flag) /*=0x20018c68*/;
    if (iVar1 != 0) {
        if (*flagp == 0) {
            *flagp = 1;
        }
    } else {
        if (*flagp != 0) {
            *flagp = 0;
            if (*(volatile char*)((char*)param_1+2) == 0) {
                *(volatile unsigned char*)((char*)param_1+5) = 1;
            }
        }
    }
}
