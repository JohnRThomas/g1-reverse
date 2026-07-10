/* named: gui_reset_dynamic_bitmap_frame_state */
/* globals referenced:
//   0x2000f6fe  g_gui_dynbmp_cycle_count     
//   0x2000f700  g_gui_dynbmp_frame_index     
//   0x2000f702  g_gui_dynbmp_frame_limit     
*/
/* Reconstructed gui_reset_dynamic_bitmap_frame_state @ 0x43308  (parity: 300/300 trials, PROVEN) */

void gui_reset_dynamic_bitmap_frame_state(void) {
  *(volatile unsigned short*)0x2000f702UL = 0;
  *(volatile unsigned short*)0x2000f700UL = 0;
  *(volatile unsigned short*)0x2000f6feUL = 0;
}

