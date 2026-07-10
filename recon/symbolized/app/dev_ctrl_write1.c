#include "g1_app_symbols.h"
/* named: dev_ctrl_write1 */
/* Reconstructed dev_ctrl_write1 @ 0x83d60  (parity: 300/300 trials, PROVEN) */

typedef void (*fnptr)(int, void*, int, short, void*);
void dev_ctrl_write1(int *param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned int local_14;
  unsigned int uStack_10;
  int base;
  int vt;
  fnptr f;
  unsigned short h;
  local_14 = param_2;
  uStack_10 = param_3;
  base = *param_1;
  vt = *(volatile int*)(base + 8);
  f = (fnptr)(*(volatile int*)(vt + 8));
  h = *(volatile unsigned short*)((char*)param_1 + 4);
  f(base, &local_14, 1, (short)h, param_1);
  return;
}

