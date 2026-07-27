#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000243fc @ 0x000243fc
 * public-name: drain_quick_note_data_queue
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   drain_quick_note_data_queue              <= FUN_000243fc @ 0x000243fc
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 * address symbols (name @ address):
 *   g_quicknote_flash_msgq                   @ 0x20003960
 */
/* Reconstructed FUN_000243fc @ 0x243fc  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(int, unsigned int, int, int);

unsigned int drain_quick_note_data_queue(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int uVar1;
  unsigned int uVar2;
  int iVar3;
  unsigned int stk[3];

  uVar1 = ((unsigned long)&g_quicknote_flash_msgq) /*=0x20003960*/;
  uVar2 = 0;
  stk[0] = param_1;
  stk[1] = param_2;
  stk[2] = param_3;
  for (iVar3 = *(volatile int *)(((unsigned long)&g_quicknote_flash_msgq) /*=0x20003960*/ + 0x24); iVar3 > 0; iVar3--) {
    uVar2 = k_msgq_get(uVar1, stk, 0, 0);
  }
  return uVar2;
}
