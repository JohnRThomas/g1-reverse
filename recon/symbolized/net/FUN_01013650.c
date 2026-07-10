#include "g1_net_symbols.h"
/* net-core FUN_01013650 @ 0x1013650  (parity 300 trials PROVEN) */

void FUN_01013650(int param_1, unsigned param_2){
  extern int FUN_01008d00(int,int);
  extern int FUN_0100f0fc(int);
  extern int FUN_010209f0(int);
  extern int FUN_01023dec(int,int,int);
  extern int FUN_01023ea8(int,int);
  extern int FUN_0100f368(int,int,int);
  extern void FUN_01023d38(int,int,int);
  volatile unsigned *w=(volatile unsigned*)((uintptr_t)&g_net_txbuf_alloc_idx) /*=0x21000f60*/;
  volatile int s;
  unsigned v;
  s=FUN_01008d00(0x30,0x97);
  s=FUN_0100f0fc(0);
  s=FUN_010209f0(0);
  s=FUN_01023dec(0,0,0);
  s=FUN_01023ea8(0,0);
  v=FUN_0100f368(0,0,0);
  *w=v;
  s=FUN_010209f0(0);
  FUN_01023d38(0,0,0);
}

