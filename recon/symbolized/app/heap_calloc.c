#include "g1_app_symbols.h"
/* named: heap_calloc */
/* Reconstructed heap_calloc @ 0x876d0  (parity: 300/300 trials, PROVEN) */

extern int _malloc_r(unsigned int, int, int, unsigned int, unsigned int);
extern void memset_bytes(int, int, int);

int heap_calloc(unsigned int param_1,int param_2,int param_3,unsigned int param_4)
{
  int iVar1;

  iVar1 = _malloc_r(param_1,param_3 * param_2,param_3,param_4,param_4);
  if (iVar1 != 0) {
    memset_bytes(iVar1,0,param_3 * param_2);
  }
  return iVar1;
}

