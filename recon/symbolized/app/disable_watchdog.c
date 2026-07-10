#include "g1_app_symbols.h"
/* named: disable_watchdog */
/* globals referenced:
//   0x00087cc8  g_watchdog_device            
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed disable_watchdog @ 0x2aeb4  (parity: 151/300 trials, PROVEN) */

extern void FUN_00074844(unsigned int, unsigned int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

typedef int (*fp_t)(unsigned int);

int disable_watchdog(void)
{
    volatile int *piVar1 = (volatile int*)((uintptr_t)&g_wdt_channel_id) /*=0x20007b50*/;
    int iVar5;

    if (*piVar1 < 0) {
        if (3 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): watchdog is disabled\n" /*=0xa1c4e*/, "disable_watchdog" /*=0xa1c85*/, *piVar1, 0, 0);
            } else {
                debug_print();
            }
        }
        iVar5 = 0;
    } else {
        int iVar6 = 5;
        do {
            if (3 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
                if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    DEBUG_PRINT("%s(): disable watchdog...\n" /*=0xa1c6a*/, "disable_watchdog" /*=0xa1c85*/);
                } else {
                    debug_print();
                }
            }
            fp_t f = *(fp_t*)(*(int*)(((uintptr_t)&g_watchdog_device) /*=0x87cc8*/ + 8) + 4);
            iVar5 = f(((uintptr_t)&g_watchdog_device) /*=0x87cc8*/);
            if (iVar5 == 0) {
                *piVar1 = -0x10;
                iVar5 = 0;
                break;
            }
            FUN_00074844(0x667, 0);
            iVar6 = iVar6 - 1;
        } while (iVar6 != 0);
    }
    return iVar5;
}

