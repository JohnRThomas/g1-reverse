#include "g1_app_symbols.h"
/* named: power_for_panel */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x200069fc  device_info                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed power_for_panel @ 0x15df4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int gpio_dt_spec_activate(int,...);
extern int debug_print(int,...);
extern int app_msleep_thunk_a(int,...);
extern int dev_write_reg3(int,...);
extern int dev_reg_modify_bits(int,...);

unsigned power_for_panel(unsigned param_1, unsigned param_2)
{
    int *piVar1; int iVar2; unsigned char *puVar3; int iVar4;
    iVar2 = dev_write_reg3(*(unsigned*)(*(volatile int*)(((uintptr_t)&tbl_87c80) /*=0x87cf8*/+4)+0x1c), 8, 0, 1, param_1, param_2);
    piVar1 = (int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    if(iVar2 < 0){
        if(*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ < 1) return 0;
        iVar2 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        puVar3 = (unsigned char*)"%s(): Could not set ldsw1.\n" /*=0x99329*/;
        goto LAB_00015e1a;
    }
    if(0 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/){
        if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0){ DEBUG_PRINT("%s(): enable ldsw1 1.8v for panel\n" /*=0x99345*/, "power_for_panel" /*=0x99c3e*/); }
        else { debug_print(0); }
    }
    app_msleep_thunk_a(1);
    iVar2 = *(volatile int*)(((uintptr_t)&tbl_87c80) /*=0x87d10*/+4);
    if(*(char*)(*(volatile int*)((uintptr_t)&device_info) /*=0x200069fc*/ + 0xed4) == 1){
        iVar4 = dev_write_reg3(*(unsigned*)(iVar2+0x1c), 4, 10, 1, param_1, param_2);
        if(iVar4 < 0){
            if(*piVar1 < 1) return 0;
            iVar2 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            puVar3 = (unsigned char*)"%s(): Could not set buck2 to 1.1v.\n" /*=0x99368*/;
            goto LAB_00015e1a;
        }
        if(0 < *piVar1){
            iVar4 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            puVar3 = (unsigned char*)"%s(): set buck2 to 1.1v\n" /*=0x9938c*/;
LAB_00015e82:
            if(iVar4 == 0){ DEBUG_PRINT((int)puVar3, "power_for_panel" /*=0x99c3e*/); }
            else { debug_print(0); }
        }
    } else {
        iVar4 = dev_write_reg3(*(unsigned*)(iVar2+0x1c), 4, 10, 2, param_1, param_2);
        if(iVar4 < 0){
            if(*piVar1 < 1) return 0;
            iVar2 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            puVar3 = (unsigned char*)"%s(): Could not set buck2 to 1.2v.\n" /*=0x993a5*/;
            goto LAB_00015e1a;
        }
        if(0 < *piVar1){
            iVar4 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            puVar3 = (unsigned char*)"%s(): set buck2 to 1.2v\n" /*=0x993c9*/;
            goto LAB_00015e82;
        }
    }
    iVar4 = dev_reg_modify_bits(*(unsigned*)(iVar2+0x1c), 4, 0xf, 2, 2);
    if(iVar4 < 0){
        if(*piVar1 < 1) return 0;
        iVar2 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        puVar3 = (unsigned char*)"%s(): Could not enable software control\n" /*=0x993e2*/;
    } else {
        iVar2 = dev_write_reg3(*(unsigned*)(iVar2+0x1c), 4, 2, 1);
        if(iVar2 < 0){
            if(*piVar1 < 1) return 0;
            iVar2 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            puVar3 = (unsigned char*)"%s(): Could not set buck2.\n" /*=0x9940b*/;
        } else {
            if(0 < *piVar1){
                if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0){ DEBUG_PRINT("%s(): enable buck2.\n" /*=0x99427*/, "power_for_panel" /*=0x99c3e*/); }
                else { debug_print(0); }
            }
            app_msleep_thunk_a(1);
            gpio_dt_spec_activate(0);
            app_msleep_thunk_a(0xf);
            if(*piVar1 < 1) return 0;
            iVar2 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            puVar3 = (unsigned char*)"%s(): turn on -2v for panel.\n" /*=0x9943c*/;
        }
    }
LAB_00015e1a:
    if(iVar2 == 0){ DEBUG_PRINT((int)puVar3, "power_for_panel" /*=0x99c3e*/); }
    else { debug_print(0); }
    return 0;
}

