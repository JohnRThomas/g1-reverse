/* readable reconstruction; identity: FUN_00032c0c @ 0x00032c0c
 * public-name: arm_timeout_10s
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arm_timeout_10s                          <= FUN_00032c0c @ 0x00032c0c
 *   k_uptime_get_4                           <= FUN_0007d12e @ 0x0007d12e
 * address symbols (name @ address):
 *   g_deadline_10s                           @ 0x20004948
 */
/* Reconstructed FUN_00032c0c @ 0x32c0c  (parity: 300/300 trials, PROVEN) */

extern long long k_uptime_get_4(void);

void arm_timeout_10s(void)
{
    long long lVar1 = k_uptime_get_4();
    *(volatile long long*)0x20004948UL = lVar1 + 10000;
}
