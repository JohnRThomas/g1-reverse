#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_display_brightness_cmd__param_0092     [param_0092; G1-original]
 * Raw function identity: 0x00032254.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00032254 @ 0x00032254
 * public-name: set_display_brightness
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   read_usr_settting_from_flash             <= FUN_00023400 @ 0x00023400
 *   display_dev_reg_config                   <= FUN_0002eaa8 @ 0x0002eaa8
 *   set_display_brightness                   <= FUN_00032254 @ 0x00032254
 *   save_usr_setting                         <= FUN_0007c28e @ 0x0007c28e
 *   k_msleep_ticks32768_b                    <= FUN_0007d14a @ 0x0007d14a
 * address symbols (name @ address):
 *   rodata_a731c                             @ 0x000a731c   [INLINED -- G6 literal batch]
 *   rodata_a7336                             @ 0x000a7336   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_00032254 @ 0x32254  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned a);
extern int get_device_info(void);
extern int read_usr_settting_from_flash(void*a);
extern void display_dev_reg_config(void);
extern void save_usr_setting(int a, int b);
extern void k_msleep_ticks32768_b(int a);
unsigned set_display_brightness(int param_1, unsigned param_2, unsigned *param_3, unsigned char *param_4){
    unsigned char stk[0x18];
    log_message(((unsigned long)"join in set_charge_limit\n") /*=0xa731c*/);
    if (param_3 == 0 || param_4 == 0){
        log_message(((unsigned long)"set_charge_limit para is NULL\n") /*=0xa7336*/);
        return 0xffffffffu;
    }
    volatile unsigned char *puVar5 = (volatile unsigned char*)*param_3;
    puVar5[0] = 0x40;
    puVar5[2] = 3;
    puVar5[1] = 1;
    puVar5[3] = 1;
    unsigned bVar1 = *(volatile unsigned char*)(param_1 + 4);
    unsigned bVar6 = *(volatile unsigned char*)(param_1 + 5);
    unsigned bVar7 = bVar1;
    if (bVar1 >= 100) bVar7 = 100;
    if (bVar6 >= 100) bVar6 = 100;
    if (bVar1 == 0) display_dev_reg_config();
    *(volatile unsigned char*)(get_device_info() + 0x1090) = (unsigned char)bVar7;
    *(volatile unsigned char*)(get_device_info() + 0x1091) = (unsigned char)bVar6;
    save_usr_setting(get_device_info(), 0);
    unsigned cVar4 = 0;
    for(;;){
        int iVar3 = read_usr_settting_from_flash(stk);
        if (iVar3 == 0 && stk[0x15] == bVar7 && stk[0x16] == bVar6) break;
        cVar4 = (cVar4 + 1) & 0xff;
        k_msleep_ticks32768_b(100);
        if (cVar4 == 5) break;
    }
    puVar5[4] = (cVar4 == 5) ? 1 : 0;
    *param_4 = 5;
    return 0;
}
