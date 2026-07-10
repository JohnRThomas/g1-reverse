/* Reconstructed FUN_00012c18 @ 0x12c18  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0000ddf0(int,int,int,int);
extern int FUN_0000de04(int,int,int,int);
extern int FUN_0000de58(int,int);
extern int FUN_00084fd4(int);
int FUN_00012c18(double darg){
  union { double d; uint32_t w[2]; } u; u.d = darg;
  uint32_t param_1 = u.w[0];
  uint32_t param_2 = u.w[1];
  int iVar1 = FUN_00084fd4(*(volatile uint32_t*)0x20002bacUL);
  if(iVar1 != 0){
    *(volatile uint32_t*)(iVar1+0x18) = param_1;
    *(volatile uint32_t*)(iVar1+0x1c) = param_2;
    *(volatile uint32_t*)(iVar1+0xc) = 8;
    int iVar2 = FUN_0000de04(param_1,param_2,0,0);
    if(iVar2==0){
      iVar2 = FUN_0000ddf0(param_1,param_2,0,0);
      if(iVar2==0){
        int uVar3 = FUN_0000de58(param_1,param_2);
        *(volatile uint32_t*)(iVar1+0x14) = uVar3;
        return iVar1;
      }
      *(volatile uint32_t*)(iVar1+0x14) = 0x80000000UL;
    } else {
      *(volatile uint32_t*)(iVar1+0x14) = 0x7fffffffUL;
    }
  }
  return iVar1;
}

