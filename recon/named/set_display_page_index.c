/* readable reconstruction; identity: FUN_000369dc @ 0x000369dc
 * public-name: set_display_page_index
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_display_page_index                   <= FUN_000369dc @ 0x000369dc
 * address symbols (name @ address):
 *   g_display_page_index                     @ 0x2001b810
 *   g_display_page_dirty_flag                @ 0x2001b811
 */
/* Reconstructed FUN_000369dc @ 0x369dc  (parity: 300/300 trials, PROVEN) */

void set_display_page_index(unsigned int param_1)
{
  if (param_1 > 4) {
    param_1 = 0;
  }
  *(volatile unsigned char *)0x2001b811UL = 1;
  *(volatile unsigned char *)0x2001b810UL = (unsigned char)param_1;
}
