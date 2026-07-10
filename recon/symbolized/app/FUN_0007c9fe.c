#include "g1_app_symbols.h"
/* named: FUN_0007c9fe */
/* Reconstructed FUN_0007c9fe @ 0x7c9fe  (parity: 300/300 trials, PROVEN) */

extern void ipc_ept_op_a_locked_retry(unsigned int,unsigned int,void*,unsigned int,unsigned int,unsigned int);
void FUN_0007c9fe(unsigned int param_1,unsigned int param_2)
{
  unsigned char b = (unsigned char)param_2;
  ipc_ept_op_a_locked_retry(param_1,0x2002,&b,1,param_1,param_2);
}

