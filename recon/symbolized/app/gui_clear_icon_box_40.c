#include "g1_app_symbols.h"
/* named: gui_clear_icon_box_40 */
/* globals referenced:
//   0x2000a034  g_gui_active_canvas          
*/
/* Reconstructed gui_clear_icon_box_40 @ 0x43324  (parity: 300/300 trials, PROVEN) */

extern void clean_fb_data(int a, int b, int c, int d, int e, int f, int g);
unsigned int gui_clear_icon_box_40(int param_1, int param_2, unsigned int param_3)
{
  clean_fb_data(*(volatile int *)((uintptr_t)&g_gui_active_canvas) /*=0x2000a034*/, 0, param_1, param_2, param_1 + 0x28, param_2 + 0x28, param_3);
  return 0;
}

