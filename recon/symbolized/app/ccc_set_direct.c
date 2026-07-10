#include "g1_app_symbols.h"
/* named: ccc_set_direct */
/* Reconstructed ccc_set_direct @ 0x59edc  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00082a42(unsigned int,unsigned int,void*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
unsigned int ccc_set_direct(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned int local[4];
  local[0]=2;
  local[1]="Invalid key" /*=0xf471e*/;
  FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/,0x1040,&local[0],2,param_1,param_2,param_3,param_4);
  return 0xffffffea;
}

