/* named: reset_touch_selection_state */
/* globals referenced:
//   0x20004950  g_dashboard_widget_state     
//   0x2001b816  g_widget0_index_raw          
*/
/* Reconstructed reset_touch_selection_state @ 0x37098  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void set_dashboard_startup_default_language(void);
void reset_touch_selection_state(void)
{
  *(volatile uint8_t*)(0x20004950UL + 1) = 0;
  *(volatile uint8_t*)0x2001b816UL = 0;
  set_dashboard_startup_default_language();
  return;
}

