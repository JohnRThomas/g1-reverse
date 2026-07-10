/* named: on_triple_click */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed on_triple_click @ 0x289e4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t);
extern void debug_print(void);
extern void FUN_00028964(void);
extern void prepare_system_suspend_state(void);
void on_triple_click(void){
  if(*(volatile uint32_t*)0x20007554UL==0) DEBUG_PRINT(0xa0ae5);
  else debug_print();
  if(*(volatile uint8_t*)0x20018d8bUL==0) FUN_00028964();
  else prepare_system_suspend_state();
}

