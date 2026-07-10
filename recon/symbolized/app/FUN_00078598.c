#include "g1_app_symbols.h"
/* named: FUN_00078598 */
/* globals referenced:
//   0x2000cc24  g_errno                      
*/
/* Reconstructed FUN_00078598 @ 0x78598  (parity: 300/300 trials, PROVEN) */

extern int lseek(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
void FUN_00078598(int *param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  int *piVar1;
  int iVar2;
  piVar1 = (int*)((uintptr_t)&g_errno) /*=0x2000cc24*/;
  *(volatile int*)((uintptr_t)&g_errno) /*=0x2000cc24*/ = 0;
  iVar2 = lseek(param_2,param_3,param_4,param_4,param_4);
  if ((iVar2 == -1) && (*(volatile int*)piVar1 != 0)) {
    *param_1 = *(volatile int*)piVar1;
  }
  return;
}

