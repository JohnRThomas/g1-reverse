#include "g1_app_symbols.h"
/* named: debounce_read_pending_flag_2 */
/* globals referenced:
//   0x20018da3  g_confirmed_state_flag_2     
//   0x20018da6  g_ancs_inbox_flag_current    
*/
/* Reconstructed debounce_read_pending_flag_2 @ 0x2eba0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
unsigned int debounce_read_pending_flag_2(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned char bVar1 = *(volatile unsigned char *)(((uintptr_t)&g_ancs_inbox_flag_current) /*=0x20018da6*/ + 2);
  unsigned int uVar3 = bVar1;
  if (*(volatile unsigned char *)((uintptr_t)&g_confirmed_state_flag_2) /*=0x20018da3*/ != uVar3) {
    DEBUG_PRINT("[csh_debug_box] isInCharge is %d \n" /*=0xa3ec1*/, uVar3, param_3, (unsigned int)(*(volatile unsigned char *)((uintptr_t)&g_confirmed_state_flag_2) /*=0x20018da3*/), param_4);
  }
  *(volatile unsigned char *)((uintptr_t)&g_confirmed_state_flag_2) /*=0x20018da3*/ = bVar1;
  return uVar3;
}

