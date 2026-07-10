#include "g1_app_symbols.h"
/* named: drain_setting_storage_queue */
/* globals referenced:
//   0x20003994  g_flash_store_cmd_msgq       
*/
/* Reconstructed drain_setting_storage_queue @ 0x23acc  (parity: 300/300 trials, PROVEN) */

extern unsigned int k_msgq_get(unsigned int, void *, unsigned int, unsigned int);

unsigned int drain_setting_storage_queue(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, int count)
{
  unsigned int uVar1;
  unsigned int uVar2;
  unsigned int stk[3];

  uVar1 = ((uintptr_t)&g_flash_store_cmd_msgq) /*=0x20003994*/;
  uVar2 = 0;
  stk[0] = param_1;
  stk[1] = param_2;
  stk[2] = param_3;
  for (; count > 0; count--) {
    uVar2 = k_msgq_get(uVar1, stk, 0, 0);
  }
  return uVar2;
}

