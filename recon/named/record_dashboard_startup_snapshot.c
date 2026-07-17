/* readable reconstruction; identity: FUN_0004a4b4 @ 0x0004a4b4
 * public-name: record_dashboard_startup_snapshot
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   record_dashboard_startup_snapshot        <= FUN_0004a4b4 @ 0x0004a4b4
 *   k_uptime_get_9                           <= FUN_0007d9a4 @ 0x0007d9a4
 * address symbols (name @ address):
 *   g_dashboard_startup_snapshot             @ 0x20004df0
 *   g_dashboard_dwell_base_hi                @ 0x20004df4
 *   g_sync_baseline_timestamp                @ 0x20004df8
 *   g_dashboard_dwell_start_ts_hi            @ 0x20004dfc
 */
/* Reconstructed FUN_0004a4b4 @ 0x4a4b4  (parity: 300/300 trials, PROVEN) */

extern unsigned long long k_uptime_get_9(void);

void record_dashboard_startup_snapshot(unsigned int param_1, unsigned int param_2)
{
    *(volatile unsigned int*)0x20004df0UL = param_1;
    *(volatile unsigned int*)0x20004df4UL = param_2;
    unsigned long long uVar2 = k_uptime_get_9();
    *(volatile unsigned int*)0x20004df8UL = (unsigned int)uVar2;
    *(volatile unsigned int*)0x20004dfcUL = (unsigned int)(uVar2 >> 32);
}
