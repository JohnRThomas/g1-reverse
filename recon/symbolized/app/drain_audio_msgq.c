#include "g1_app_symbols.h"
#include <zephyr/sys_clock.h>
/* readable reconstruction; identity: FUN_0002f688 @ 0x0002f688
 * public-name: drain_audio_msgq
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   drain_audio_msgq                         <= FUN_0002f688 @ 0x0002f688
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 * address symbols (name @ address):
 *   g_audio_msgq                             @ 0x20003890
 */
/* Reconstructed FUN_0002f688 @ 0x2f688  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(struct k_msgq *, void *, k_timeout_t);
unsigned int drain_audio_msgq(void)
{
  int iVar1;
  unsigned int uVar2;
  int iVar3;
  unsigned char auStack_dc[208];

  iVar1 = ((unsigned long)&g_audio_msgq) /*=0x20003890*/;
  uVar2 = 0;
  for (iVar3 = *(volatile int *)(((unsigned long)&g_audio_msgq) /*=0x20003890*/ + 0x24); 0 < iVar3; iVar3 = iVar3 - 1) {
    uVar2 = k_msgq_get(iVar1, auStack_dc, (k_timeout_t){ .ticks = 0LL });
  }
  return uVar2;
}
