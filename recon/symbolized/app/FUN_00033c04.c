#include "g1_app_symbols.h"
/* named: FUN_00033c04 */
/* globals referenced:
//   0x20007dac  g_message_pool               
*/
/* Reconstructed FUN_00033c04 @ 0x33c04  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint8_t FUN_00033c04(int param_1)
{
  return *(volatile uint8_t*)(param_1 * 0x1b4 + (g_message_pool) /*=0x20007dac*/ + 0xd);
}

