#include "g1_app_symbols.h"
/* named: write_r_capture_errno */
/* globals referenced:
//   0x2000cc24  g_errno                      
*/
/* Reconstructed write_r_capture_errno @ 0x79528  (parity: 300/300 trials, PROVEN) */

extern int fd_table_dispatch_op1(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
void write_r_capture_errno(int *param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  int *piVar1;
  int iVar2;
  piVar1 = (int*)((uintptr_t)&g_errno) /*=0x2000cc24*/;
  *(volatile int*)((uintptr_t)&g_errno) /*=0x2000cc24*/ = 0;
  iVar2 = fd_table_dispatch_op1(param_2,param_3,param_4,param_4,param_4);
  if ((iVar2 == -1) && (*(volatile int*)piVar1 != 0)) {
    *param_1 = *(volatile int*)piVar1;
  }
  return;
}

