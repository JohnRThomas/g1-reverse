#include "g1_app_symbols.h"
/* named: record_dashboard_startup_snapshot */
/* globals referenced:
//   0x20004df0  g_dashboard_startup_snapshot 
//   0x20004df8  g_sync_baseline_timestamp    
*/
/* Reconstructed record_dashboard_startup_snapshot @ 0x4a4b4  (parity: 300/300 trials, PROVEN) */

extern unsigned long long k_uptime_get_9(void);

void record_dashboard_startup_snapshot(unsigned int param_1, unsigned int param_2)
{
    *(volatile unsigned int*)((uintptr_t)&g_dashboard_startup_snapshot) /*=0x20004df0*/ = param_1;
    *(volatile unsigned int*)((uintptr_t)&g_dashboard_dwell_base_hi) /*=0x20004df4*/ = param_2;
    unsigned long long uVar2 = k_uptime_get_9();
    *(volatile unsigned int*)((uintptr_t)&g_sync_baseline_timestamp) /*=0x20004df8*/ = (unsigned int)uVar2;
    *(volatile unsigned int*)((uintptr_t)&g_dashboard_dwell_start_ts_hi) /*=0x20004dfc*/ = (unsigned int)(uVar2 >> 32);
}

