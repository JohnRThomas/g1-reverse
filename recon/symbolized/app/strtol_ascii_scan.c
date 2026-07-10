#include "g1_app_symbols.h"
/* named: strtol_ascii_scan */
/* globals referenced:
//   0x20002d20  g_libc_heap_ctrl             
*/
/* Reconstructed strtol_ascii_scan @ 0x77c1c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern unsigned FUN_00077b38(int, unsigned char*, void*, unsigned);
unsigned strtol_ascii_scan(unsigned char *param_1, void *param_2, unsigned param_3)
{
  return FUN_00077b38(*(volatile int*)((uintptr_t)&g_libc_heap_ctrl) /*=0x20002d20*/, param_1, param_2, param_3);
}

