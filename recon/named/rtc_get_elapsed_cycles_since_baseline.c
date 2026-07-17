/* readable reconstruction; identity: FUN_00074b68 @ 0x00074b68
 * public-name: rtc_get_elapsed_cycles_since_baseline
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rtc_read_extended_cycle_count            <= FUN_00063610 @ 0x00063610
 *   rtc_get_elapsed_cycles_since_baseline    <= FUN_00074b68 @ 0x00074b68
 * address symbols (name @ address):
 *   g_rtc_elapsed_calc_disabled_flag         @ 0x2000b494
 */
/* Reconstructed FUN_00074b68 @ 0x74b68  (parity: 300/300 trials, PROVEN) */

extern int rtc_read_extended_cycle_count(void);
int rtc_get_elapsed_cycles_since_baseline(void)
{
  if (*(volatile unsigned int *)0x2000b494UL == 0) {
    return rtc_read_extended_cycle_count();
  }
  return 0;
}
