#include "g1_app_symbols.h"
/* named: power_down_panel */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed power_down_panel @ 0x15fdc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void panel_pwr_gpio_deassert(void);
extern void debug_print(uint32_t, ...);
extern int app_msleep_thunk_a(int);
extern int dev_write_reg3(int, ...);

unsigned int power_down_panel(void)
{
    volatile int *piVar1 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    int iVar2;
    unsigned int format_string;

    app_msleep_thunk_a(2);
    panel_pwr_gpio_deassert();
    if (0 < *piVar1) {
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): turn off -2v for panel.\n" /*=0x9949a*/, "power_down_panel" /*=0x99c17*/);
        } else {
            debug_print("%s(): turn off -2v for panel.\n" /*=0x9949a*/, "power_down_panel" /*=0x99c17*/);
        }
    }
    app_msleep_thunk_a(0x10);
    iVar2 = dev_write_reg3(*(volatile uint32_t*)(*(volatile uint32_t*)(((uintptr_t)&tbl_87c80) /*=0x87d10*/ + 4) + 0x1c), 4, 3, 1);
    if (iVar2 < 0) {
        if (*piVar1 < 1) {
            return 0;
        }
        iVar2 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        format_string = "%s(): Could not set buck2.\n" /*=0x9940b*/;
    } else {
        if (0 < *piVar1) {
            if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): disable buck2 1.2v\n" /*=0x994b9*/, "power_down_panel" /*=0x99c17*/);
            } else {
                debug_print("%s(): disable buck2 1.2v\n" /*=0x994b9*/, "power_down_panel" /*=0x99c17*/);
            }
        }
        app_msleep_thunk_a(5);
        iVar2 = dev_write_reg3(*(volatile uint32_t*)(*(volatile uint32_t*)(((uintptr_t)&tbl_87c80) /*=0x87cf8*/ + 4) + 0x1c), 8, 1);
        if (iVar2 < 0) {
            if (*piVar1 < 1) {
                return 0;
            }
            iVar2 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            format_string = "%s(): Could not set ldsw1.\n" /*=0x99329*/;
        } else {
            if (*piVar1 < 1) {
                return 0;
            }
            iVar2 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            format_string = "%s(): disable ldsw1 1.8v for panel\n" /*=0x994d3*/;
        }
    }
    if (iVar2 == 0) {
        DEBUG_PRINT(format_string, "power_down_panel" /*=0x99c17*/);
    } else {
        debug_print(format_string, "power_down_panel" /*=0x99c17*/);
    }
    return 0;
}

