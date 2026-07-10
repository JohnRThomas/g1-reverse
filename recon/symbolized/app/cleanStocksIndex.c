#include "g1_app_symbols.h"
/* named: cleanStocksIndex */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20004950  g_dashboard_widget_state     
//   0x20007554  g_log_use_alt_sink           
//   0x2001b815  g_stocks_widget_index_raw    
*/
/* Reconstructed cleanStocksIndex @ 0x37154  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(uint32_t,uint32_t,uint32_t,uint32_t);
extern void debug_print(uint32_t,uint32_t);

void cleanStocksIndex(void)
{
  *(volatile uint8_t*)(((uintptr_t)&g_dashboard_widget_state) /*=0x20004950*/+3) = 0;
  *(volatile uint8_t*)((uintptr_t)&g_stocks_widget_index_raw) /*=0x2001b815*/ = 0;
  if (*(volatile int32_t*)((uintptr_t)&g_log_level) /*=0x2000230c*/ <= 2) {
    return;
  }
  if (*(volatile int32_t*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
    debug_print("%s():  %s index = %d\n" /*=0xa8ff3*/, "cleanStocksIndex" /*=0xa95b8*/);
    return;
  }
  DEBUG_PRINT("%s():  %s index = %d\n" /*=0xa8ff3*/, "cleanStocksIndex" /*=0xa95b8*/, "cleanStocksIndex" /*=0xa95b8*/, 0);
}

