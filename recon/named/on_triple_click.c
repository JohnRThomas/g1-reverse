/* readable reconstruction; identity: FUN_000289e4 @ 0x000289e4
 * public-name: on_triple_click
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   prepare_system_suspend_state             <= FUN_000289b0 @ 0x000289b0
 * address symbols (name @ address):
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_suspend_pending_flag                   @ 0x20018d8b
 */
/* Reconstructed on_triple_click @ 0x289e4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t);
extern void debug_print(uint32_t);
extern void FUN_00028964(void);
extern void prepare_system_suspend_state(void);
void on_triple_click(void){
  if(*(volatile uint32_t*)0x20007554UL==0) DEBUG_PRINT(0xa0ae5);
  else debug_print(0xa0ae5);
  if(*(volatile uint8_t*)0x20018d8bUL==0) FUN_00028964();
  else prepare_system_suspend_state();
}
