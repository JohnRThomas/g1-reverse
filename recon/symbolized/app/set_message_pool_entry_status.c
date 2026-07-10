#include "g1_app_symbols.h"
/* named: set_message_pool_entry_status */
/* globals referenced:
//   0x20007dac  g_message_pool               
*/
/* Reconstructed set_message_pool_entry_status @ 0x33bf0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void set_message_pool_entry_status(int param_1, uint8_t param_2)
{
  *(volatile uint8_t*)(param_1 * 0x1b4 + (g_message_pool) /*=0x20007dac*/ + 0xd) = param_2;
  return;
}

