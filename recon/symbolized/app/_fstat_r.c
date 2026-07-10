#include "g1_app_symbols.h"
/* named: _fstat_r */
/* globals referenced:
//   0x2000cc24  g_errno                      
*/
/* Reconstructed _fstat_r @ 0x77e4c  (parity: 300/300 trials, PROVEN) */

extern int _fstat(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void _fstat_r(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  volatile int *piVar1;
  int iVar2;

  piVar1 = (volatile int *)((uintptr_t)&g_errno) /*=0x2000cc24*/;
  *piVar1 = 0;
  iVar2 = _fstat(param_2,param_3,param_3,0,param_4);
  if ((iVar2 == -1) && (*piVar1 != 0)) {
    *param_1 = *piVar1;
  }
  return;
}

