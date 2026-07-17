#include "g1_net_symbols.h"
/* net-core FUN_0103a344 @ 0x103a344  (parity 300 trials PROVEN) */

typedef int (*fnptr)(int,int,unsigned int);
extern void FUN_0103a32a(fnptr fn, int a, int b, unsigned int c);

void FUN_0103a344(unsigned int *param_1)
{
  unsigned int *p1 = (unsigned int *)param_1[1];
  FUN_0103a32a((fnptr)param_1[0], (int)param_1[2], (int)p1[0], p1[1]);
  p1[0] = 0;
}
