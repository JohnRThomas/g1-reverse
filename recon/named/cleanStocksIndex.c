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
  *(volatile uint8_t*)(0x20004950UL+3) = 0;
  *(volatile uint8_t*)0x2001b815UL = 0;
  if (*(volatile int32_t*)0x2000230cUL <= 2) {
    return;
  }
  if (*(volatile int32_t*)0x20007554UL != 0) {
    debug_print(0xa8ff3UL, 0xa95b8UL);
    return;
  }
  DEBUG_PRINT(0xa8ff3UL, 0xa95b8UL, 0xa95b8UL, 0);
}

