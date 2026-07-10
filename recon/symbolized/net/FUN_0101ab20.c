#include "g1_net_symbols.h"
/* net-core FUN_0101ab20 @ 0x101ab20  (parity 300 trials PROVEN) */

void FUN_0101ab20(unsigned param_1, unsigned param_2){
  volatile unsigned char *g2e = (volatile unsigned char*)0x2e;
  extern int FUN_01019204(void);
  extern void FUN_01008d00(int,int);
  extern int FUN_0101a130(void);
  extern int FUN_01018dac(void*);
  volatile int sink;
  sink = FUN_01019204();
  FUN_01008d00(0x21,0x217);
  sink = FUN_0101a130();
  *g2e = (unsigned char)param_2;
  sink = FUN_01018dac((void*)0);
  FUN_01008d00(0x21,0x1ce);
  FUN_01008d00(0x21,0x7e6);
  for(;;){ FUN_01008d00(0,0); }
}

