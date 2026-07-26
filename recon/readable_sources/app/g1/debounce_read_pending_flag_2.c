#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0002eba0 @ 0x0002eba0
 * public-name: debounce_read_pending_flag_2
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debounce_read_pending_flag_2             <= FUN_0002eba0 @ 0x0002eba0
 * address symbols (name @ address):
 *   rodata_a3ec1                             @ 0x000a3ec1   [INLINED -- G6 literal batch]
 *   g_confirmed_state_flag_2                 @ 0x20018da3
 *   g_ancs_inbox_flag_current                @ 0x20018da6
 */
/* Reconstructed FUN_0002eba0 @ 0x2eba0  (parity: 300/300 trials, PROVEN) */

unsigned int debounce_read_pending_flag_2(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned char bVar1 = *(volatile unsigned char *)(((unsigned long)&g_ancs_inbox_flag_current) /*=0x20018da6*/ + 2);
  unsigned int uVar3 = bVar1;
  if (*(volatile unsigned char *)((unsigned long)&g_confirmed_state_flag_2) /*=0x20018da3*/ != uVar3) {
    log_message(((unsigned long)"[csh_debug_box] isInCharge is %d \n") /*=0xa3ec1*/, uVar3, param_3, (unsigned int)(*(volatile unsigned char *)((unsigned long)&g_confirmed_state_flag_2) /*=0x20018da3*/), param_4);
  }
  *(volatile unsigned char *)((unsigned long)&g_confirmed_state_flag_2) /*=0x20018da3*/ = bVar1;
  return uVar3;
}
