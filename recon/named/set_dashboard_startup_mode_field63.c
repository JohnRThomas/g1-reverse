/* readable reconstruction; identity: FUN_0001658c @ 0x0001658c
 * public-name: set_dashboard_startup_mode_field63
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_dashboard_startup_mode_field63       <= FUN_0001658c @ 0x0001658c
 * address symbols (name @ address):
 *   g_dashboard_startup_mode_info_defaults   @ 0x2007fc00
 */
/* Reconstructed FUN_0001658c @ 0x1658c  (parity: 300/300 trials, PROVEN) */

void set_dashboard_startup_mode_field63(unsigned char param_1)
{
  *(volatile unsigned char *)(0x2007fc00UL + 0x63) = param_1;
}
