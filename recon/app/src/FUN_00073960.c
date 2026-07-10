/* Reconstructed FUN_00073960 @ 0x73960  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00072040(uint32_t);
extern int FUN_0007205c(uint32_t);
extern void FUN_00072078(uint32_t);
extern void FUN_00074274(int);
extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
void FUN_00073960(int param_1,uint32_t p2,uint32_t p3,uint32_t p4){
  int iVar3=FUN_00072040(0x2000b490);
  if(iVar3==0){
    FUN_0007e2fa(0x99cbd,0xf0920,0xf08c7,0x72,p4);
    FUN_0007e2fa(0xf0935,0x2000b490,0,0,0);
    FUN_0007e2ec(0xf08c7,0x72);
    return;
  }
  FUN_00072078(0x2000b490);
  if(*(volatile int*)(param_1+8)!=0) FUN_00074274(param_1);
  iVar3=FUN_0007205c(0x2000b490);
  if(iVar3!=0) return;
  FUN_0007e2fa(0x99cbd,0xf08f4,0xf08c7,0xf0,p4);
  FUN_0007e2fa(0xf090b,0x2000b490,0,0,0);
  FUN_0007e2ec(0xf08c7,0xf0);
}

