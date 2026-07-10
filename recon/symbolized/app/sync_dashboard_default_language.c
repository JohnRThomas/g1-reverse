#include "g1_app_symbols.h"
/* named: sync_dashboard_default_language */
/* globals referenced:
//   0x20004950  g_dashboard_widget_state     
//   0x2001b816  g_widget0_index_raw          
*/
/* Reconstructed sync_dashboard_default_language @ 0x37060  (parity: 300/300 trials, PROVEN) */

extern void set_dashboard_startup_default_language(void);
unsigned char sync_dashboard_default_language(void)
{
  unsigned int base = ((uintptr_t)&g_dashboard_widget_state) /*=0x20004950*/;
  *(volatile unsigned char *)(base + 1) = *(volatile unsigned char *)((uintptr_t)&g_widget0_index_raw) /*=0x2001b816*/;
  set_dashboard_startup_default_language();
  return *(volatile unsigned char *)(base + 1);
}

