#include "g1_app_symbols.h"
/* named: l2cap_reassemble_frag */
/* Reconstructed l2cap_reassemble_frag @ 0x82e04  (parity: 300/300 trials, PROVEN) */
extern void ext5c310(int,int,void*);
void l2cap_reassemble_frag(int param_1,int param_2,int param_3,int param_4,void **param_5){
  (void)param_4;
  if (param_2 != 0){
    (*(void(*)(int,int,void*))*param_5)(param_1,param_2,param_5);
  } else {
    ext5c310(param_1,param_3,param_5);
  }
}

