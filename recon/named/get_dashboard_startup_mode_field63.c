/* readable reconstruction; identity: FUN_00016580 @ 0x00016580
 * public-name: get_dashboard_startup_mode_field63
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_dashboard_startup_mode_field63       <= FUN_00016580 @ 0x00016580
 * address symbols (name @ address):
 *   g_dashboard_startup_mode_info_defaults   @ 0x2007fc00
 */
/* Reconstructed FUN_00016580 @ 0x16580  (parity: 300/300 trials, PROVEN) */

unsigned char get_dashboard_startup_mode_field63(void)
{
  return *(volatile unsigned char *)(0x2007fc00UL + 0x63);
}
