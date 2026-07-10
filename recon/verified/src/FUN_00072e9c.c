/* Reconstructed FUN_00072e9c @ 0x72e9c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00072040(uint32_t);
extern int FUN_0007205c(uint32_t);
extern void FUN_00072078(uint32_t);
extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
unsigned FUN_00072e9c(int param_1,uint32_t p2,uint32_t p3,uint32_t p4){
  int iVar2=FUN_00072040(0x2000b480);
  if(iVar2==0){
    FUN_0007e2fa(0x99cbd,0xf0920,0xf08c7,0x72,p4);
    FUN_0007e2fa(0xf0935,0x2000b480,0,0,0);
    FUN_0007e2ec(0xf08c7,0x72);
    return 0;
  }
  FUN_00072078(0x2000b480);
  unsigned uVar3=*(volatile unsigned*)(param_1+0xc) & 0xf;
  iVar2=FUN_0007205c(0x2000b480);
  if(iVar2!=0) return uVar3;
  FUN_0007e2fa(0x99cbd,0xf08f4,0xf08c7,0xf0,p4);
  FUN_0007e2fa(0xf090b,0x2000b480,0,0,0);
  FUN_0007e2ec(0xf08c7,0xf0);
  return 0;
}

