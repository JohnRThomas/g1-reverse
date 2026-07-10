#include "g1_app_symbols.h"
/* named: trigger_touch_key_hw_reset */
/* globals referenced:
//   0x20007b1c  g_some_module_sem            
//   0x20018d8a  g_some_module_init_done_flag 
*/
/* Reconstructed trigger_touch_key_hw_reset @ 0x2a0c0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void thunk_FUN_00072880(unsigned int);
void trigger_touch_key_hw_reset(void)
{
  if (*(volatile uint8_t*)((uintptr_t)&g_some_module_init_done_flag) /*=0x20018d8a*/ != 0) {
    thunk_FUN_00072880(((uintptr_t)&g_some_module_sem) /*=0x20007b1c*/);
    return;
  }
  return;
}

