#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00033cb0 @ 0x00033cb0
 * public-name: get_active_message_count
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_active_message_count                 <= FUN_00033cb0 @ 0x00033cb0
 * address symbols (name @ address):
 *   g_message_pool                           @ 0x20007dac
 *   g_message_pool_index                     @ 0x2001a22a
 */
/* Reconstructed FUN_00033cb0 @ 0x33cb0  (parity: 300/300 trials, PROVEN) */

unsigned int get_active_message_count(void)
{
  unsigned char uVar1;
  unsigned int uVar2;
  unsigned int uVar3;
  int iVar4;

  uVar2 = 9;
  iVar4 = ((unsigned long)g_message_pool) /*=0x20007dac*/;
  do {
    if (*(volatile char *)(iVar4 + 0xf63) != 0) {
      uVar3 = uVar2 & 0xff;
      uVar1 = (unsigned char)uVar2;
      goto LAB_00033cc6;
    }
    uVar2 = uVar2 - 1;
    iVar4 = iVar4 + -0x1b4;
  } while (uVar2 != 0xffffffff);
  uVar3 = 0xff;
  uVar1 = 0;
LAB_00033cc6:
  *(volatile unsigned char *)((unsigned long)&g_message_pool_index) /*=0x2001a22a*/ = uVar1;
  return uVar3;
}
