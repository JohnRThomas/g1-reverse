/* named: get_synced_clock_time */
/* globals referenced:
//   0x20004df0  g_dashboard_startup_snapshot 
//   0x20004df8  g_sync_baseline_timestamp    
*/
/* Reconstructed get_synced_clock_time @ 0x4a4d0  (parity: 300/300 trials, PROVEN) */

extern long long k_uptime_get_9(void);

void get_synced_clock_time(long long *param_1)
{
  long long lVar1;
  lVar1 = k_uptime_get_9();
  *param_1 = (lVar1 - *(volatile long long*)0x20004df8UL) + *(volatile long long*)0x20004df0UL;
}

