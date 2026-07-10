#include "g1_app_symbols.h"
/* named: drain_audio_msgq */
/* globals referenced:
//   0x20003890  g_audio_msgq                 
*/
/* Reconstructed drain_audio_msgq @ 0x2f688  (parity: 300/300 trials, PROVEN) */

extern unsigned int k_msgq_get(int a, void *b, int c, int d);
unsigned int drain_audio_msgq(void)
{
  int iVar1;
  unsigned int uVar2;
  int iVar3;
  unsigned char auStack_dc[208];

  iVar1 = ((uintptr_t)&g_audio_msgq) /*=0x20003890*/;
  uVar2 = 0;
  for (iVar3 = *(volatile int *)(((uintptr_t)&g_audio_msgq) /*=0x20003890*/ + 0x24); 0 < iVar3; iVar3 = iVar3 - 1) {
    uVar2 = k_msgq_get(iVar1, auStack_dc, 0, 0);
  }
  return uVar2;
}

