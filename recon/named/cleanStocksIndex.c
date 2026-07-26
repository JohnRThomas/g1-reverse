/* readable reconstruction; identity: FUN_00037154 @ 0x00037154
 * public-name: cleanStocksIndex
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_a8ff3                             @ 0x000a8ff3   [INLINED -- G6 literal batch]
 *   rodata_a95b8                             @ 0x000a95b8   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_widget_state                 @ 0x20004950
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_stocks_widget_index_raw                @ 0x2001b815
 */
/* Reconstructed cleanStocksIndex @ 0x37154  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void log_message(uint32_t,uint32_t,uint32_t,uint32_t);
extern void debug_print(uint32_t,uint32_t,uint32_t,uint32_t);

void cleanStocksIndex(void)
{
  *(volatile uint8_t*)(0x20004950UL+3) = 0;
  *(volatile uint8_t*)0x2001b815UL = 0;
  if (*(volatile int32_t*)0x2000230cUL <= 2) {
    return;
  }
  if (*(volatile int32_t*)0x20007554UL != 0) {
    debug_print(0xa8ff3UL, 0xa95b8UL, 0xa95b8UL, 0);
    return;
  }
  log_message(0xa8ff3UL, 0xa95b8UL, 0xa95b8UL, 0);
}
