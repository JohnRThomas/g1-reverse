#include "g1_app_symbols.h"
/* named: switch_to_dfu_mode */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x200069fc  device_info                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed switch_to_dfu_mode @ 0x158bc  (parity: 300/300 trials, PROVEN) */

typedef unsigned char u8;
typedef unsigned int u32;
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int, unsigned int, unsigned int);
extern int k_is_in_isr(void);
extern void app_msleep_thunk_a(int);
extern int sys_reboot(int);
extern void thunk_FUN_00072880(unsigned int);

void switch_to_dfu_mode(unsigned int param_1)
{
    volatile u8 *puVar1 = (volatile u8*)((uintptr_t)&g_runtime_mode_flag) /*=0x2000ff6e*/;
    int iVar2;
    unsigned int r2val;
    typedef int (*fnptr)(unsigned int, void*, int);

    *puVar1 = 1;
    iVar2 = k_is_in_isr();
    if (iVar2 != 0) {
        thunk_FUN_00072880(param_1);
        return;
    }
    {
        fnptr f = *(fnptr*)((*(volatile u32*)((uintptr_t)&device_info) /*=0x200069fc*/) + 0x1040);
        iVar2 = f("runtime_mode" /*=0x990cf*/, (void*)puVar1, 1);
    }
    if (iVar2 == 0) {
        if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 0) {
            if (*(volatile u32*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
                debug_print("%s(): sys reboot because system reset %d, %d\n" /*=0x99105*/, "switch_to_dfu_mode" /*=0x99b2a*/, 0, *puVar1);
                goto loop_start;
            } else {
                r2val = 0;
                goto print_lab;
            }
        }
        goto loop_start;
    } else {
        if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ < 1) return;
        if (*(volatile u32*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
            debug_print("%s(): failed to switch to ble mode [%d]\n" /*=0x990dc*/, "switch_to_dfu_mode" /*=0x99b2a*/, (unsigned int)iVar2, 0);
            return;
        }
        DEBUG_PRINT("%s(): failed to switch to ble mode [%d]\n" /*=0x990dc*/, "switch_to_dfu_mode" /*=0x99b2a*/);
        return;
    }
loop_start:
    for (;;) {
        app_msleep_thunk_a(500);
        r2val = (unsigned int)sys_reboot(1);
print_lab:
        DEBUG_PRINT("%s(): sys reboot because system reset %d, %d\n" /*=0x99105*/, "switch_to_dfu_mode" /*=0x99b2a*/, r2val);
    }
}

