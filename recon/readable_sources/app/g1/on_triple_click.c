#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000289e4 @ 0x000289e4
 * public-name: on_triple_click
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   enter_active_click_mode                  <= FUN_00028964 @ 0x00028964
 *   prepare_system_suspend_state             <= FUN_000289b0 @ 0x000289b0
 * address symbols (name @ address):
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_suspend_pending_flag                   @ 0x20018d8b
 */
/* Reconstructed on_triple_click @ 0x289e4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_message(uint32_t);
extern void debug_print(uint32_t);
extern void enter_active_click_mode(void);
extern void prepare_system_suspend_state(void);
void on_triple_click(void){
  if(*(volatile uint32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/==0) log_message(0xa0ae5);
  else debug_print(0xa0ae5);
  if(*(volatile uint8_t*)((unsigned long)&g_suspend_pending_flag) /*=0x20018d8b*/==0) enter_active_click_mode();
  else prepare_system_suspend_state();
}
