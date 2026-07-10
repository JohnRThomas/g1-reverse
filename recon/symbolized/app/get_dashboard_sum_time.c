#include "g1_app_symbols.h"
/* named: get_dashboard_sum_time */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed get_dashboard_sum_time @ 0x4a960  (parity: 300/300 trials, PROVEN) */

extern unsigned long long k_uptime_get_10(void);
extern unsigned int get_device_info(void);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int, unsigned int, unsigned int);

long long get_dashboard_sum_time(void)
{
    unsigned long long uVar7;
    unsigned int iVar1;
    unsigned long long field;
    long long lVar8;

    uVar7 = k_uptime_get_10();
    iVar1 = get_device_info();
    field = *(volatile unsigned long long*)(iVar1 + 0x1094);
    if ((long long)field >= (long long)uVar7) {
        iVar1 = get_device_info();
        field = *(volatile unsigned long long*)(iVar1 + 0x1094);
        uVar7 = k_uptime_get_10();
        lVar8 = (long long)(field - uVar7);
    } else {
        uVar7 = k_uptime_get_10();
        iVar1 = get_device_info();
        field = *(volatile unsigned long long*)(iVar1 + 0x1094);
        lVar8 = (long long)(uVar7 - field);
    }
    if (1 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
        unsigned int loP = (unsigned int)lVar8;
        unsigned int hiP = (unsigned int)((unsigned long long)lVar8 >> 32);
        if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): get_dashboard_sum_time is %d\n" /*=0xf0369*/, "get_dashboard_sum_time" /*=0xf0492*/, loP, hiP);
        } else {
            debug_print("%s(): get_dashboard_sum_time is %d\n" /*=0xf0369*/, "get_dashboard_sum_time" /*=0xf0492*/, loP, hiP);
        }
    }
    return lVar8;
}

