#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002eb78 @ 0x0002eb78
 * public-name: debounce_read_pending_flag_1
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debounce_read_pending_flag_1             <= FUN_0002eb78 @ 0x0002eb78
 * address symbols (name @ address):
 *   rodata_a3e9f                             @ 0x000a3e9f
 *   g_confirmed_state_flag_1                 @ 0x20018da4
 *   g_ancs_inbox_flag_current                @ 0x20018da6
 */
/* Reconstructed FUN_0002eb78 @ 0x2eb78  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
unsigned int debounce_read_pending_flag_1(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned char bVar1 = *(volatile unsigned char *)(((unsigned long)&g_ancs_inbox_flag_current) /*=0x20018da6*/ + 1);
  unsigned int uVar3 = bVar1;
  if (*(volatile unsigned char *)((unsigned long)&g_confirmed_state_flag_1) /*=0x20018da4*/ != uVar3) {
    log_message(((unsigned long)&rodata_a3e9f) /*=0xa3e9f*/, uVar3, param_3, (unsigned int)(*(volatile unsigned char *)((unsigned long)&g_confirmed_state_flag_1) /*=0x20018da4*/), param_4);
  }
  *(volatile unsigned char *)((unsigned long)&g_confirmed_state_flag_1) /*=0x20018da4*/ = bVar1;
  return uVar3;
}
