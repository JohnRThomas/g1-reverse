/* readable reconstruction; identity: FUN_00084c76 @ 0x00084c76
 * public-name: sys_clock_cycle_get_32
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rtc_read_extended_cycle_count            <= FUN_00063610 @ 0x00063610
 *   sys_clock_cycle_get_32                   <= FUN_00084c76 @ 0x00084c76
 */
/* Reconstructed FUN_00084c76 @ 0x84c76  (parity: 300/300 trials, PROVEN) */

extern void rtc_read_extended_cycle_count(void);
void sys_clock_cycle_get_32(void)
{
    rtc_read_extended_cycle_count();
}
