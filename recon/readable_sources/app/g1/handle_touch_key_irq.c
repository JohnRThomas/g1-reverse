#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00030af0 @ 0x00030af0
 * public-name: handle_touch_key_irq
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_apply_config_table                 <= FUN_00030224 @ 0x00030224
 *   attr_store_get                           <= FUN_000302f8 @ 0x000302f8
 *   handle_touch_key_irq                     <= FUN_00030af0 @ 0x00030af0
 * address symbols (name @ address):
 *   g_touch_key_irq_line_status              @ 0x20019dac
 */
/* Reconstructed FUN_00030af0 @ 0x30af0  (parity: 300/300 trials, PROVEN) */

extern int attr_store_get(int,unsigned int*,int,int,int);
extern void flash_apply_config_table(void);

void handle_touch_key_irq(int param_1, int param_2, int param_3)
{
    unsigned int local_c = 0;
    int iVar1 = attr_store_get(0x4410, &local_c, param_3, 0, param_1);
    if (iVar1 >= 0) {
        if ((int)(local_c << 0x1d) < 0) {
            *(volatile unsigned char*)((unsigned long)&g_touch_key_irq_line_status) /*=0x20019dac*/ = 2;
        }
        if ((local_c & 2) != 0) {
            *(volatile unsigned char*)((unsigned long)&g_touch_key_irq_line_status) /*=0x20019dac*/ = 1;
        }
        if ((local_c & 1) != 0) {
            flash_apply_config_table();
            return;
        }
    }
}
