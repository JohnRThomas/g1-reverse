/* readable reconstruction; identity: FUN_00043308 @ 0x00043308
 * public-name: gui_reset_dynamic_bitmap_frame_state
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gui_reset_dynamic_bitmap_frame_state     <= FUN_00043308 @ 0x00043308
 * address symbols (name @ address):
 *   g_gui_dynbmp_cycle_count                 @ 0x2000f6fe
 *   g_gui_dynbmp_frame_index                 @ 0x2000f700
 *   g_gui_dynbmp_frame_limit                 @ 0x2000f702
 */
/* Reconstructed FUN_00043308 @ 0x43308  (parity: 300/300 trials, PROVEN) */

unsigned int gui_reset_dynamic_bitmap_frame_state(void) {
  *(volatile unsigned short*)0x2000f702UL = 0;
  *(volatile unsigned short*)0x2000f700UL = 0;
  *(volatile unsigned short*)0x2000f6feUL = 0;
}
