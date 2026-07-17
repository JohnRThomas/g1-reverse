/* readable reconstruction; identity: FUN_00015df4 @ 0x00015df4
 * public-name: power_for_panel
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   power_for_panel                          <= FUN_00015df4 @ 0x00015df4
 *   gpio_dt_spec_activate                    <= FUN_000179ec @ 0x000179ec
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   app_msleep_thunk_a                       <= FUN_0007c038 @ 0x0007c038
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 *   dev_reg_modify_bits                      <= FUN_00083e0e @ 0x00083e0e
 * address symbols (name @ address):
 *   rodata_99329                             @ 0x00099329
 *   rodata_99345                             @ 0x00099345
 *   rodata_9938c                             @ 0x0009938c
 *   rodata_9940b                             @ 0x0009940b
 *   rodata_99427                             @ 0x00099427
 *   rodata_99c3e                             @ 0x00099c3e
 *   g_log_level                              @ 0x2000230c
 *   device_info                              @ 0x200069fc
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_00015df4 @ 0x15df4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int log_message(int,...);
extern int gpio_dt_spec_activate(int,...);
extern void debug_print(int, int);
extern int app_msleep_thunk_a(int,...);
extern int dev_write_reg3(int,...);
extern int dev_reg_modify_bits(int,...);

unsigned power_for_panel(unsigned param_1, unsigned param_2)
{
    int *piVar1; int iVar2; unsigned char *puVar3; int iVar4;
    iVar2 = dev_write_reg3(*(unsigned*)(*(volatile int*)(0x00087cf8+4)+0x1c), 8, 0, 1, param_1, param_2);
    piVar1 = (int*)0x2000230c;
    if(iVar2 < 0){
        if(*(volatile int*)0x2000230c < 1) return 0;
        iVar2 = *(volatile int*)0x20007554;
        puVar3 = (unsigned char*)0x00099329;
        goto LAB_00015e1a;
    }
    if(0 < *(volatile int*)0x2000230c){
        if(*(volatile int*)0x20007554 == 0){ log_message(0x00099345, 0x00099c3e); }
        else { debug_print(0x00099345, 0x00099c3e); }
    }
    app_msleep_thunk_a(1);
    iVar2 = *(volatile int*)(0x00087d10+4);
    if(*(char*)(*(volatile int*)0x200069fc + 0xed4) == 1){
        iVar4 = dev_write_reg3(*(unsigned*)(iVar2+0x1c), 4, 10, 1, param_1, param_2);
        if(iVar4 < 0){
            if(*piVar1 < 1) return 0;
            iVar2 = *(volatile int*)0x20007554;
            puVar3 = (unsigned char*)0x00099368;
            goto LAB_00015e1a;
        }
        if(0 < *piVar1){
            iVar4 = *(volatile int*)0x20007554;
            puVar3 = (unsigned char*)0x0009938c;
LAB_00015e82:
            if(iVar4 == 0){ log_message((int)puVar3, 0x00099c3e); }
            else { debug_print((int)puVar3, 0x00099c3e); }
        }
    } else {
        iVar4 = dev_write_reg3(*(unsigned*)(iVar2+0x1c), 4, 10, 2, param_1, param_2);
        if(iVar4 < 0){
            if(*piVar1 < 1) return 0;
            iVar2 = *(volatile int*)0x20007554;
            puVar3 = (unsigned char*)0x000993a5;
            goto LAB_00015e1a;
        }
        if(0 < *piVar1){
            iVar4 = *(volatile int*)0x20007554;
            puVar3 = (unsigned char*)0x000993c9;
            goto LAB_00015e82;
        }
    }
    iVar4 = dev_reg_modify_bits(*(unsigned*)(iVar2+0x1c), 4, 0xf, 2, 2);
    if(iVar4 < 0){
        if(*piVar1 < 1) return 0;
        iVar2 = *(volatile int*)0x20007554;
        puVar3 = (unsigned char*)0x000993e2;
    } else {
        iVar2 = dev_write_reg3(*(unsigned*)(iVar2+0x1c), 4, 2, 1);
        if(iVar2 < 0){
            if(*piVar1 < 1) return 0;
            iVar2 = *(volatile int*)0x20007554;
            puVar3 = (unsigned char*)0x0009940b;
        } else {
            if(0 < *piVar1){
                if(*(volatile int*)0x20007554 == 0){ log_message(0x00099427, 0x00099c3e); }
                else { debug_print(0x00099427, 0x00099c3e); }
            }
            app_msleep_thunk_a(1);
            gpio_dt_spec_activate(0);
            app_msleep_thunk_a(0xf);
            if(*piVar1 < 1) return 0;
            iVar2 = *(volatile int*)0x20007554;
            puVar3 = (unsigned char*)0x0009943c;
        }
    }
LAB_00015e1a:
    if(iVar2 == 0){ log_message((int)puVar3, 0x00099c3e); }
    else { debug_print((int)puVar3, 0x00099c3e); }
    return 0;
}
