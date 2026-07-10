#include "g1_app_symbols.h"
/* named: _sbrk_r */
/* globals referenced:
//   0x2000cc24  g_errno                      
*/
/* Reconstructed _sbrk_r @ 0x778f4  (parity: 300/300 trials, PROVEN) */

extern int sbrk_impl(unsigned int);
void _sbrk_r(int *param_1,unsigned int param_2)
{
  *(volatile int *)((uintptr_t)&g_errno) /*=0x2000cc24*/ = 0;
  int iVar2 = sbrk_impl(param_2);
  if (iVar2 == -1) {
    int v = *(volatile int *)((uintptr_t)&g_errno) /*=0x2000cc24*/;
    if (v != 0) {
      *(volatile int *)param_1 = v;
    }
  }
}

