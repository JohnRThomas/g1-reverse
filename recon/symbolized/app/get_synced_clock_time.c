#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004a4d0 @ 0x0004a4d0
 * public-name: get_synced_clock_time
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_synced_clock_time                    <= FUN_0004a4d0 @ 0x0004a4d0
 *   k_uptime_get_9                           <= FUN_0007d9a4 @ 0x0007d9a4
 * address symbols (name @ address):
 *   g_dashboard_startup_snapshot             @ 0x20004df0
 *   g_sync_baseline_timestamp                @ 0x20004df8
 */
/* Reconstructed FUN_0004a4d0 @ 0x4a4d0  (parity: 300/300 trials, PROVEN) */

extern unsigned long long k_uptime_get_9(void);

void get_synced_clock_time(long long *param_1)
{
  long long lVar1;
  lVar1 = k_uptime_get_9();
  *param_1 = (lVar1 - *(volatile long long*)((unsigned long)&g_sync_baseline_timestamp) /*=0x20004df8*/) + *(volatile long long*)((unsigned long)&g_dashboard_startup_snapshot) /*=0x20004df0*/;
}
