#include "g1_app_symbols.h"
/* named: FUN_00032fe8 */
/* Reconstructed FUN_00032fe8 @ 0x32fe8  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void*, void*, unsigned int);
extern int FUN_00071eac(void*, void*, unsigned int, void*, int, int, int, unsigned int, int);

void FUN_00032fe8(void)
{
  volatile unsigned char *pcVar1 = (volatile unsigned char*)((uintptr_t)&g_aging_mode_thread_started_flag) /*=0x20019ef1*/;
  int iVar2;

  if (*pcVar1 != 0) {
    DEBUG_PRINT((void*)"[%s-%d], thread has started !\n" /*=0xa757f*/, (void*)"start_aging_mode_thread" /*=0xa75c2*/, 0xab8);
    return;
  }
  iVar2 = FUN_00071eac((void*)((uintptr_t)&g_aging_mode_thread) /*=0x20004870*/, (void*)((uintptr_t)&g_aging_mode_thread_stack) /*=0x20027a68*/, 0xc00, (void*)((uintptr_t)&rodata_32421) /*=0x32421*/, 0,0,0,0xfffffff4,0);
  if (iVar2 == 0) {
    *pcVar1 = 1;
  }
  return;
}

